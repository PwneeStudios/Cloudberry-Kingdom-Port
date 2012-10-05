#include <Architecture/SchedulerPc.h>

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

};

class ResourceCreatorJob : public Job
{

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
