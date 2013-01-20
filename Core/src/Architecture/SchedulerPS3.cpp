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
};

SchedulerPS3::SchedulerPS3() :
	internal_( new SchedulerInternal )
{
}

SchedulerPS3::~SchedulerPS3()
{
	delete internal_;
}

void SchedulerPS3::MainThread()
{
}

void SchedulerPS3::RunJob( Job *job )
{
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
}
