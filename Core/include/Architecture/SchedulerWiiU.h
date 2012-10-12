#ifndef _SCHEDULER_WIIU_H_
#define _SCHEDULER_WIIU_H_

#include <ForwardDeclarations.h>

class SchedulerWiiU
{

	// Internal bits.
	struct SchedulerInternal *internal_;

private:

	/// No copying.
	SchedulerWiiU( const SchedulerWiiU & ) { }

	/// No assignment.
	SchedulerWiiU &operator = ( const SchedulerWiiU & ) { return *this; }

public:

	SchedulerWiiU();
	~SchedulerWiiU();

	/**
	 * @see Scheduler::MainThread()
	 */
	void MainThread();

	/**
	 * @see Scheduler::CreateResource()
	 */
	void CreateResource( ResourceHolder *holder, Resource *resource );

	/**
	 * @see Scheduler::CreateGpuResource()
	 */
	void CreateGpuResource( ResourceHolder *holder, Resource *resource );

	/// Do worker thread processing.
	void WorkerThread();

private:

};

#endif
