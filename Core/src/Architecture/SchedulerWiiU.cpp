#include <Architecture/SchedulerWiiU.h>

#include <Architecture/Job.h>
#include <Content/Resource.h>
#include <Content/ResourcePtr.h>
#include <Utility/Log.h>

#include <cafe.h>
#include <list>

/**
 * Load a resource.
 */
class ResourceLoaderJob : public Job
{

	ResourceHolder *holder_;
	Resource *resource_;

public:

	ResourceLoaderJob( ResourceHolder *holder, Resource *resource ) :
		holder_( holder ),
		resource_( resource )
	{
	}

	void Do()
	{
		resource_->Load();
		resource_->GpuCreate();

		if( !resource_->IsLoaded() )
		{
			LOG.Write( "Failed: %s\n", resource_->GetPath().c_str() );
			return;
		}

		LOG.Write( "Loaded: %s\n", resource_->GetPath().c_str() );
		holder_->SetResource( resource_ );
	}

};

struct SchedulerInternal
{
	bool WorkersRunning;
	
	std::list< Job * > JobQueue;
	OSMutex JobQueueMutex;
	OSSemaphore JobQueueSemaphore;

	OSThread *Threads[2];
};

/// Bootstrap for worker thread.
static int ThreadProc( int argc, void *argv )
{
	LOG.Write( "Scheduler running on thread %s\n", OSGetThreadName( OSGetCurrentThread() ) );
	SchedulerWiiU *scheduler = reinterpret_cast< SchedulerWiiU * >( argv );
	scheduler->WorkerThread();

	return 0;
}

SchedulerWiiU::SchedulerWiiU() :
	internal_( new SchedulerInternal )
{
	internal_->WorkersRunning = true;

	OSInitMutex( &internal_->JobQueueMutex );
	OSInitSemaphore( &internal_->JobQueueSemaphore, 0 );

	internal_->Threads[ 0 ] = OSGetDefaultThread( 2 );
	OSRunThread( internal_->Threads[ 0 ], ThreadProc, 1, this );
}

SchedulerWiiU::~SchedulerWiiU()
{
	internal_->WorkersRunning = false;

	for( int i = 0; i < 2; ++i )
		OSSignalSemaphore( &internal_->JobQueueSemaphore );

	OSJoinThread( internal_->Threads[ 0 ], NULL );

	LOG.Write( "Worker threads shut down.\n" );

	delete internal_;
}

void SchedulerWiiU::MainThread()
{
}

void SchedulerWiiU::RunJob( Job *job )
{
	OSLockMutex( &internal_->JobQueueMutex );
	internal_->JobQueue.push_back( job );
	OSUnlockMutex( &internal_->JobQueueMutex );
	OSSignalSemaphore( &internal_->JobQueueSemaphore );
}

void SchedulerWiiU::CreateResource( ResourceHolder *holder, Resource *resource )
{
	resource->Load();
	resource->GpuCreate();

	if( !resource->IsLoaded() )
	{
		LOG.Write( "Failed: %s\n", resource->GetPath().c_str() );
		return;
	}

	LOG.Write( "Loaded: %s\n", resource->GetPath().c_str() );
	holder->SetResource( resource );

	CreateGpuResource( holder, resource );
}

void SchedulerWiiU::CreateGpuResource( ResourceHolder *holder, Resource *resource )
{
	/*resource->GpuCreate();
	holder->SetResource( resource );*/
}

void SchedulerWiiU::WorkerThread()
{
	while( internal_->WorkersRunning )
	{
		OSWaitSemaphore( &internal_->JobQueueSemaphore );

		Job *job = 0;
		OSLockMutex( &internal_->JobQueueMutex );
		if( !internal_->JobQueue.empty() )
		{
			job = internal_->JobQueue.front();
			internal_->JobQueue.pop_front();
		}
		OSUnlockMutex( &internal_->JobQueueMutex );

		if( !job )
			continue;

		job->Do();
		delete job;
	}
}
