#include <Architecture/SchedulerWiiU.h>

#include <Content/Resource.h>
#include <Content/ResourcePtr.h>
#include <Utility/Log.h>

struct SchedulerInternal
{
};

SchedulerWiiU::SchedulerWiiU()
{
}

SchedulerWiiU::~SchedulerWiiU()
{
}

void SchedulerWiiU::MainThread()
{
}

void SchedulerWiiU::RunJob( Job *job )
{
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
}
