#include <Architecture/SchedulerPc.h>

#include <Architecture/Scheduler.h>
#include <Content/Resource.h>
#include <Content/ResourcePtr.h>
#include <Core.h>
#include <Datastructures/Freelist.h>
#include <GL/glfw.h>
#include <Utility/Log.h>

#define NUM_THREADS 4

/**
 * Base job.
 */
class Job
{

public:

	virtual ~Job() { }

	virtual void Do() = 0 ;

};

#include <iostream>

/**
 * Load a resource.
 */
class ResourceLoaderJob : public Job
{

	ResourceHolder *holder_;
	Resource *resource_;
	bool gpuCreate_;

public:

	ResourceLoaderJob() :
		holder_( 0 ),
		resource_( 0 ),
		gpuCreate_( false )
	{
	}

	ResourceLoaderJob( ResourceHolder *holder, Resource *resource, bool gpuCreate ) :
		holder_( holder ),
		resource_( resource ),
		gpuCreate_( gpuCreate )
	{
	}

	void Do()
	{
		resource_->Load();

		// If there is an error, stop.
		if( !resource_->IsLoaded() )
		{
			LOG.Write( "Failed: %s\n", resource_->GetPath().c_str() );
			return;
		}

		LOG.Write( "Loaded: %s\n", resource_->GetPath().c_str() );

		// Kick off a creation job.
		if( gpuCreate_ )
		{
			SCHEDULER->CreateGpuResource( holder_, resource_ );
		}
	}

};

/**
 * Create a resource.
 */
class ResourceCreatorJob : public Job
{

	ResourceHolder *holder_;
	Resource *resource_;

public:

	ResourceCreatorJob( ResourceHolder *holder, Resource *resource ) :
		holder_( holder ),
		resource_( resource )
	{
	}

	void Do()
	{
		resource_->GpuCreate();
		holder_->SetResource( resource_ );
	}

};

struct SchedulerInternal
{
	GLFWthread Threads[ NUM_THREADS ];
	bool WorkersRunning;

	std::list< Job * > JobQueue;
	GLFWmutex JobQueueMutex;
	GLFWcond JobQueueCV;

	std::list< Job * > MainThreadJobQueue;
	GLFWmutex MainThreadJobQueueMutex;
};

/// Bootstrap for worker thread.
static void ThreadProc( void *context )
{
	SchedulerPc *scheduler = reinterpret_cast< SchedulerPc * >( context );
	scheduler->WorkerThread();
}

SchedulerPc::SchedulerPc() :
	internal_( new SchedulerInternal )
{
	internal_->WorkersRunning = true;

	internal_->JobQueueMutex = glfwCreateMutex();
	internal_->MainThreadJobQueueMutex = glfwCreateMutex();

	internal_->JobQueueCV = glfwCreateCond();

	// Start up some worker threads.
	for( int i = 0; i < NUM_THREADS; ++i )
		internal_->Threads[ i ] = glfwCreateThread( ThreadProc, this );
}

SchedulerPc::~SchedulerPc()
{
	internal_->WorkersRunning = false;

	// Wake up all the workers to force them to quit.
	for( int i = 0; i < NUM_THREADS; ++i )
	{
		while( GL_FALSE == glfwWaitThread( internal_->Threads[ i ], GLFW_NOWAIT ) )
			glfwSignalCond( internal_->JobQueueCV );
	}

	glfwDestroyMutex( internal_->JobQueueMutex );
	glfwDestroyMutex( internal_->MainThreadJobQueueMutex );

	glfwDestroyCond( internal_->JobQueueCV );

	// Delete remaining jobs.
	std::list< Job * >::iterator i;
	
	for( i = internal_->JobQueue.begin(); i != internal_->JobQueue.end(); ++i )
		delete ( *i );

	for( i = internal_->MainThreadJobQueue.begin();
		 i != internal_->MainThreadJobQueue.end(); ++i )
		 delete ( *i );

	delete internal_;
}

void SchedulerPc::MainThread()
{
	// Make a copy of the current job thread so no one adds extra jobs
	// while we are processing them one by one.
	glfwLockMutex( internal_->MainThreadJobQueueMutex );
	std::list< Job * > currentJobs( internal_->MainThreadJobQueue );
	internal_->MainThreadJobQueue.clear();
	glfwUnlockMutex( internal_->MainThreadJobQueueMutex );

	std::list< Job * >::iterator i;
	for( i = currentJobs.begin(); i != currentJobs.end(); ++i )
	{
		( *i )->Do();
		delete ( *i );
	}
}

void SchedulerPc::CreateResource( ResourceHolder *holder, Resource *resource )
{
	glfwLockMutex( internal_->JobQueueMutex );
	internal_->JobQueue.push_back( new ResourceLoaderJob( holder, resource, true ) );
	glfwUnlockMutex( internal_->JobQueueMutex );

	// Notify worker thread about the new job.
	glfwSignalCond( internal_->JobQueueCV );
}

void SchedulerPc::CreateGpuResource( ResourceHolder *holder, Resource *resource )
{
	glfwLockMutex( internal_->MainThreadJobQueueMutex );
	internal_->MainThreadJobQueue.push_back( new ResourceCreatorJob( holder, resource ) );
	glfwUnlockMutex( internal_->MainThreadJobQueueMutex );
}

void SchedulerPc::WorkerThread()
{
	while( internal_->WorkersRunning )
	{
		glfwLockMutex( internal_->JobQueueMutex );

		// Keep trying to wait on the condition variable while the job queue is empty.
		while( internal_->JobQueue.size() == 0 )
		{
			glfwWaitCond( internal_->JobQueueCV, internal_->JobQueueMutex, GLFW_INFINITY );

			// Check if we were awoken in order to be shut down.
			if( !internal_->WorkersRunning )
			{
				glfwUnlockMutex( internal_->JobQueueMutex );
				return;
			}
		}

		Job *job = internal_->JobQueue.front();
		internal_->JobQueue.pop_front();
		glfwUnlockMutex( internal_->JobQueueMutex );

		job->Do();
		delete job;
	}
}
