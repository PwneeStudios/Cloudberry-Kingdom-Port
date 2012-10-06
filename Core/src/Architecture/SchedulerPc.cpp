#include <Architecture/SchedulerPc.h>

#include <Content/Resource.h>
#include <Datastructures/Freelist.h>
#include <GL/glfw.h>

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

		if( resource_->IsLoaded() && gpuCreate_ )
		{

		}
	}

};

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
	}

};

struct SchedulerInternal
{
	GLFWthread Threads[ NUM_THREADS ];
	bool WorkersRunning;
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

	// Start up some worker threads.
	for( int i = 0; i < NUM_THREADS; ++i )
		internal_->Threads[ i ] = glfwCreateThread( ThreadProc, this );
}

SchedulerPc::~SchedulerPc()
{
	internal_->WorkersRunning = false;

	for( int i = 0; i < NUM_THREADS; ++i )
		glfwWaitThread( internal_->Threads[ i ], GLFW_WAIT );

	delete internal_;
}

void SchedulerPc::MainThread()
{

}

void SchedulerPc::CreateResource( ResourceHolder *holder, Resource *resource )
{

}

void SchedulerPc::WorkerThread()
{
	while( internal_->WorkersRunning )
	{
		glfwSleep( 1 );
	}
}
