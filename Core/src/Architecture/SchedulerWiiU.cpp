#include <Architecture/SchedulerWiiU.h>

#include <Architecture/Job.h>
#include <Architecture/Scheduler.h>
#include <Content/Resource.h>
#include <Content/ResourcePtr.h>
#include <Core.h>
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
	//OSThread Threads[2];
	void *Stack;
};

static SchedulerInternal *External = NULL;

class SuspendSchedulerJob : public Job
{
public:
	
	SuspendSchedulerJob()
	{
	}

	void Do()
	{
		OSSuspendThread( External->Threads[ 0 ] );
	}
};

void StopScheduler()
{
	SCHEDULER->RunJobASAP( new SuspendSchedulerJob() );
}

void ResumeScheduler()
{
	OSResumeThread( External->Threads[ 0 ] );
}

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
	External = internal_;
	internal_->WorkersRunning = true;

	OSInitMutex( &internal_->JobQueueMutex );
	OSInitSemaphore( &internal_->JobQueueSemaphore, 0 );

	internal_->Threads[ 0 ] = OSGetDefaultThread( 2 );
	OSSetThreadPriority( internal_->Threads[ 0 ], 20 );
	OSRunThread( internal_->Threads[ 0 ], ThreadProc, 1, this );
	/*internal_->Stack = new char[ 1024 * 1024 ];
	BOOL ret = OSCreateThread( &internal_->Threads[ 0 ], ThreadProc, 1, this,
		internal_->Stack, 1024 * 1024, 20, OS_THREAD_ATTR_AFFINITY_CORE2 );
	OSSetThreadName( &internal_->Threads[ 0 ], "SchedulerThread" );

	if( !ret )
		LOG.Write( "NO JOB SYSTEM!" );

	OSResumeThread( &internal_->Threads[ 0 ] );*/
}

SchedulerWiiU::~SchedulerWiiU()
{
	internal_->WorkersRunning = false;

	for( int i = 0; i < 2; ++i )
		OSSignalSemaphore( &internal_->JobQueueSemaphore );

	OSJoinThread( internal_->Threads[ 0 ], NULL );
	//OSJoinThread( &internal_->Threads[ 0 ], NULL );

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

void SchedulerWiiU::RunJobASAP( Job *job )
{
	OSLockMutex( &internal_->JobQueueMutex );
	internal_->JobQueue.push_front( job );
	OSUnlockMutex( &internal_->JobQueueMutex );
	OSSignalSemaphore( &internal_->JobQueueSemaphore );
}

void SchedulerWiiU::CreateResource( ResourceHolder *holder, Resource *resource )
{
	RunJob( new ResourceLoaderJob( holder, resource ) );
	/*resource->Load();
	resource->GpuCreate();

	if( !resource->IsLoaded() )
	{
		LOG.Write( "Failed: %s\n", resource->GetPath().c_str() );
		return;
	}

	LOG.Write( "Loaded: %s\n", resource->GetPath().c_str() );
	holder->SetResource( resource );

	CreateGpuResource( holder, resource );*/
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
