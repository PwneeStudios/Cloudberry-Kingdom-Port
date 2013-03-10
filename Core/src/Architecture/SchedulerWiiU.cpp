#include <Architecture/SchedulerWiiU.h>

#include <Architecture/Job.h>
#include <Architecture/Scheduler.h>
#include <Content/Resource.h>
#include <Content/ResourcePtr.h>
#include <Core.h>
#include <Datastructures/Freelist.h>
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

	ResourceLoaderJob()
		: holder_( NULL )
		, resource_( NULL )
	{
	}

	ResourceLoaderJob( ResourceHolder *holder, Resource *resource ) :
		holder_( holder ),
		resource_( resource )
	{
	}

	void Do()
	{
		resource_->Load();

		if( !resource_->IsLoaded() )
		{
			LOG.Write( "Failed: %s\n", resource_->GetPath().c_str() );
			return;
		}

		LOG.Write( "Loaded: %s\n", resource_->GetPath().c_str() );

		SCHEDULER->CreateGpuResource( holder_, resource_ );
	}

	void *operator new( size_t size );
	void operator delete( void *addr );
};

static Freelist< ResourceLoaderJob, 800 > *ResourceLoaderFreelist;
OSMutex ResourceLoaderMutex;

void *ResourceLoaderJob::operator new( size_t size )
{
	OSLockMutex( &ResourceLoaderMutex );
	void *addr = ResourceLoaderFreelist->Allocate();
	OSUnlockMutex( &ResourceLoaderMutex );
	return addr;
}

void ResourceLoaderJob::operator delete( void *addr )
{
	OSLockMutex( &ResourceLoaderMutex );
	ResourceLoaderFreelist->Free( reinterpret_cast< ResourceLoaderJob * >( addr ) );
	OSUnlockMutex( &ResourceLoaderMutex );
}

class ResourceCreatorJob : public Job
{

	ResourceHolder *holder_;
	Resource *resource_;

public:

	ResourceCreatorJob()
		: holder_( NULL )
		, resource_( NULL )
	{
	}

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

	void *operator new( size_t size );
	void operator delete( void *addr );
};

static Freelist< class ResourceCreatorJob, 800 > *ResourceCreatorFreelist;
OSMutex ResourceCreatorMutex;

void *ResourceCreatorJob::operator new( size_t size )
{
	OSLockMutex( &ResourceCreatorMutex );
	void *addr = ResourceCreatorFreelist->Allocate();
	OSUnlockMutex( &ResourceCreatorMutex );
	return addr;
}

void ResourceCreatorJob::operator delete( void *addr )
{
	OSLockMutex( &ResourceCreatorMutex );
	ResourceCreatorFreelist->Free( reinterpret_cast< ResourceCreatorJob * >( addr ) );
	OSUnlockMutex( &ResourceCreatorMutex );
}

struct SchedulerInternal
{
	bool WorkersRunning;
	
	std::list< Job * > JobQueue;
	OSMutex JobQueueMutex;
	OSSemaphore JobQueueSemaphore;

	std::list< Job * > MainThreadJobQueue;
	OSMutex MainThreadJobQueueMutex;

	//OSThread *Threads[2];
	OSThread Threads[2];
	void *Stack;
};

/// Bootstrap for worker thread.
static int ThreadProc( int argc, void *argv )
{
	LOG.Write( "Scheduler running on thread %s\n", OSGetThreadName( OSGetCurrentThread() ) );
	SchedulerWiiU *scheduler = reinterpret_cast< SchedulerWiiU * >( argv );
	scheduler->WorkerThread();

	return 0;
}

static SchedulerInternal *External = NULL;

class ExitSchedulerJob : public Job
{
	
public:
	ExitSchedulerJob()
	{
	}


	void Do()
	{
		OSExitThread( 0 );
	}
};

class PauseSchedulerJob : public Job
{
public:
	PauseSchedulerJob()
	{
	}

	void Do()
	{
		OSSuspendThread( &External->Threads[ 0 ] );
	}
};

void StopScheduler()
{
	SCHEDULER->RunJobASAP( new PauseSchedulerJob );
}

void ResumeScheduler()
{
	OSContinueThread( &External->Threads[ 0 ] );
}

SchedulerWiiU::SchedulerWiiU() :
	internal_( new SchedulerInternal )
{
	External = internal_;
	internal_->WorkersRunning = true;

	OSInitMutex( &internal_->JobQueueMutex );
	OSInitSemaphore( &internal_->JobQueueSemaphore, 0 );
	OSInitMutex( &internal_->MainThreadJobQueueMutex );

	ResourceLoaderFreelist = new Freelist< ResourceLoaderJob, 800 >();
	OSInitMutex( &ResourceLoaderMutex );
	ResourceCreatorFreelist = new Freelist< ResourceCreatorJob, 800 >();
	OSInitMutex( &ResourceCreatorMutex );

	/*internal_->Threads[ 0 ] = OSGetDefaultThread( 2 );
	OSSetThreadPriority( internal_->Threads[ 0 ], 20 );
	OSRunThread( internal_->Threads[ 0 ], ThreadProc, 1, this );*/
	const u32 stackSize = 1024 * 1024;
	internal_->Stack = new char[ stackSize ];
	BOOL ret = OSCreateThread( &internal_->Threads[ 0 ], ThreadProc, 1, this,
		internal_->Stack + stackSize, stackSize, 20, OS_THREAD_ATTR_AFFINITY_CORE2 );
	OSSetThreadName( &internal_->Threads[ 0 ], "SchedulerThread" );

	if( !ret )
		LOG.Write( "NO JOB SYSTEM!" );

	OSResumeThread( &internal_->Threads[ 0 ] );
}

SchedulerWiiU::~SchedulerWiiU()
{
	internal_->WorkersRunning = false;

	ExitSchedulerJob exitSchedulerJob;
	RunJobASAP( &exitSchedulerJob );
	if( OSIsThreadSuspended( &internal_->Threads[ 0 ] ) )
		ResumeScheduler();

	for( int i = 0; i < 2; ++i )
		OSSignalSemaphore( &internal_->JobQueueSemaphore );

	//OSJoinThread( internal_->Threads[ 0 ], NULL );
	OSJoinThread( &internal_->Threads[ 0 ], NULL );
	delete[] internal_->Stack;

	delete ResourceLoaderFreelist;
	delete ResourceCreatorFreelist;

	LOG.Write( "Worker threads shut down.\n" );

	delete internal_;
}

void SchedulerWiiU::MainThread()
{
	OSLockMutex( &internal_->MainThreadJobQueueMutex );
	if( !internal_->MainThreadJobQueue.empty() )
	{
		Job *job = internal_->MainThreadJobQueue.front();
		internal_->MainThreadJobQueue.pop_front();

		job->Do();
		delete job;
	}
	OSUnlockMutex( &internal_->MainThreadJobQueueMutex );
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
	OSLockMutex( &internal_->MainThreadJobQueueMutex );
	internal_->MainThreadJobQueue.push_back( new ResourceCreatorJob( holder, resource ) );
	OSUnlockMutex( &internal_->MainThreadJobQueueMutex );
	/*resource->GpuCreate();
	holder->SetResource( resource );*/
}

void SchedulerWiiU::WorkerThread()
{
	OSSetThreadCancelState( TRUE );

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
