#include <Architecture/SchedulerPS3.h>

#include <Architecture/Job.h>
#include <Architecture/Scheduler.h>
#include <Content/Resource.h>
#include <Content/ResourcePtr.h>
#include <Core.h>
#include <Datastructures/Freelist.h>
#include <Utility/Log.h>

#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <sys/ppu_thread.h>
#include <sys/timer.h>

#define NUM_THREADS 1
#define MAIN_QUEUE_SIZE 6

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
			LOG_WRITE( "Failed: %s\n", resource_->GetPath().c_str() );
			return;
		}

		LOG_WRITE( "Loaded: %s\n", resource_->GetPath().c_str() );

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
	pthread_t Threads[ NUM_THREADS ];
	bool WorkersRunning;

	std::list< Job * > JobQueue;
	pthread_mutex_t JobQueueMutex;
	sem_t JobQueueSemaphore;

	std::list< Job * > MainThreadJobQueue;
	pthread_mutex_t MainThreadJobQueueMutex;
	sem_t MainThreadSemaphore;
};

static void *ThreadProc( void *context )
{
	SchedulerPS3 *scheduler = reinterpret_cast< SchedulerPS3 * >( context );
	scheduler->WorkerThread();

	return NULL;
}

SchedulerPS3::SchedulerPS3() :
	internal_( new SchedulerInternal )
{
	internal_->WorkersRunning = true;

	int ret = pthread_mutex_init( &internal_->JobQueueMutex, NULL );
	assert( !ret );

	ret = sem_init( &internal_->JobQueueSemaphore, 0, 0 );
	assert( !ret );

	ret = pthread_mutex_init( &internal_->MainThreadJobQueueMutex, NULL );
	assert( !ret );

	ret = sem_init( &internal_->MainThreadSemaphore, 0, MAIN_QUEUE_SIZE );
	assert( !ret );

	for( int i = 0; i < NUM_THREADS; ++i )
	{
		ret = pthread_create( &internal_->Threads[ i ], NULL, ThreadProc, this );
		assert( !ret );
	}
}

class ExitSchedulerJob : public Job
{
public:

	void Do()
	{
		pthread_exit( NULL );
	}
};

SchedulerPS3::~SchedulerPS3()
{
	internal_->WorkersRunning = false;

	RunJobASAP( new ExitSchedulerJob );

	// This frees up space for the current stalled job to execute and lets
	// the exit scheduler job terminate.
	sem_post( &internal_->MainThreadSemaphore );

	for( int i = 0; i < NUM_THREADS; ++i )
		sem_post( &internal_->JobQueueSemaphore );

	for( int i = 0; i < NUM_THREADS; ++i )
	{
		pthread_join( internal_->Threads[ i ], NULL );
		pthread_detach( internal_->Threads[ i ] );
	}

	pthread_mutex_destroy( &internal_->JobQueueMutex );
	pthread_mutex_destroy( &internal_->MainThreadJobQueueMutex );

	std::list< Job * >::iterator i;
	for( i = internal_->JobQueue.begin(); i != internal_->JobQueue.end(); ++i )
		delete *i;

	delete internal_;
}

void SchedulerPS3::MainThread()
{
	pthread_mutex_lock( &internal_->MainThreadJobQueueMutex );
	while( internal_->MainThreadJobQueue.size() != 0 )
	{
		Job *job = internal_->MainThreadJobQueue.front();
		internal_->MainThreadJobQueue.pop_front();

		job->Do();
		delete job;

		sem_post( &internal_->MainThreadSemaphore );
	}
	pthread_mutex_unlock( &internal_->MainThreadJobQueueMutex );
}

void SchedulerPS3::RunJob( Job *job )
{
	pthread_mutex_lock( &internal_->JobQueueMutex );
	internal_->JobQueue.push_back( job );
	pthread_mutex_unlock( &internal_->JobQueueMutex );
	sem_post( &internal_->JobQueueSemaphore );
}

static void RunJobASAPThread( uint64_t context )
{
	Job *job = reinterpret_cast< Job * >( context );

	job->Do();
	delete job;
}

void SchedulerPS3::RunJobASAP( Job *job )
{
	pthread_mutex_lock( &internal_->JobQueueMutex );
	internal_->JobQueue.push_front( job );
	pthread_mutex_unlock( &internal_->JobQueueMutex );
	sem_post( &internal_->JobQueueSemaphore );
	/*sys_ppu_thread_t tid;
	int ret = sys_ppu_thread_create( &tid, RunJobASAPThread,
		reinterpret_cast< uint64_t >( job ), 1001, 16 * 1024, 0, "RunJobASAPThread" );

	if( ret != 0 )
		LOG_WRITE( "Load thread failed!" );*/
}

void SchedulerPS3::CreateResource( ResourceHolder *holder, Resource *resource )
{
	ResourceLoaderJob *job = new ResourceLoaderJob( holder, resource, true );

	pthread_mutex_lock( &internal_->JobQueueMutex );
	internal_->JobQueue.push_back( job );
	pthread_mutex_unlock( &internal_->JobQueueMutex );
	sem_post( &internal_->JobQueueSemaphore );
	/*ResourceLoaderJob job( holder, resource, false );
	job.Do();

	CreateGpuResource( holder, resource );*/
}

void SchedulerPS3::CreateGpuResource( ResourceHolder *holder, Resource *resource )
{
	ResourceCreatorJob *job = new ResourceCreatorJob( holder, resource );

	sem_wait( &internal_->MainThreadSemaphore );

	pthread_mutex_lock( &internal_->MainThreadJobQueueMutex );
	internal_->MainThreadJobQueue.push_back( job );
	pthread_mutex_unlock( &internal_->MainThreadJobQueueMutex );

	/*ResourceCreatorJob job( holder, resource );
	job.Do();*/
}

void SchedulerPS3::WorkerThread()
{
	while( internal_->WorkersRunning )
	{
		sem_wait( &internal_->JobQueueSemaphore );

		Job *job = NULL;
		pthread_mutex_lock( &internal_->JobQueueMutex );
		if( !internal_->JobQueue.empty() )
		{
			job = internal_->JobQueue.front();
			internal_->JobQueue.pop_front();
		}
		pthread_mutex_unlock( &internal_->JobQueueMutex );

		if( !job )
			continue;

		job->Do();
		delete job;
	}
}
