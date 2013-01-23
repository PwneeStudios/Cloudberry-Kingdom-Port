#include <Architecture/SchedulerPS3.h>

#include <Architecture/Job.h>
#include <Architecture/Scheduler.h>
#include <Content/Resource.h>
#include <Content/ResourcePtr.h>
#include <Core.h>
#include <Datastructures/Freelist.h>
#include <Utility/Log.h>

#define NUM_THREADS 1

#include <iostream>
#include <pthread.h>
#include <semaphore.h>

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
	pthread_t Threads[ NUM_THREADS ];
	bool WorkersRunning;

	std::list< Job * > JobQueue;
	pthread_mutex_t JobQueueMutex;
	sem_t JobQueueSemaphore;
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

	for( int i = 0; i < NUM_THREADS; ++i )
	{
		ret = pthread_create( &internal_->Threads[ i ], NULL, ThreadProc, this );
		assert( !ret );
	}
}

SchedulerPS3::~SchedulerPS3()
{
	internal_->WorkersRunning = false;

	for( int i = 0; i < NUM_THREADS; ++i )
		sem_post( &internal_->JobQueueSemaphore );

	for( int i = 0; i < NUM_THREADS; ++i )
	{
		pthread_join( internal_->Threads[ i ], NULL );
		pthread_detach( internal_->Threads[ i ] );
	}

	pthread_mutex_destroy( &internal_->JobQueueMutex );

	std::list< Job * >::iterator i;
	for( i = internal_->JobQueue.begin(); i != internal_->JobQueue.end(); ++i )
		delete *i;

	delete internal_;
}

void SchedulerPS3::MainThread()
{
}

void SchedulerPS3::RunJob( Job *job )
{
	pthread_mutex_lock( &internal_->JobQueueMutex );
	internal_->JobQueue.push_back( job );
	pthread_mutex_unlock( &internal_->JobQueueMutex );
	sem_post( &internal_->JobQueueSemaphore );
}

void SchedulerPS3::CreateResource( ResourceHolder *holder, Resource *resource )
{
	ResourceLoaderJob job( holder, resource, true );
	job.Do();
}

void SchedulerPS3::CreateGpuResource( ResourceHolder *holder, Resource *resource )
{
	ResourceCreatorJob job( holder, resource );
	job.Do();
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
