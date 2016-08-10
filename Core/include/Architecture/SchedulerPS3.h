#ifndef _SCHEDULER_PS3_H_
#define _SCHEDULER_PS3_H_

#include <ForwardDeclarations.h>

class SchedulerPS3
{

	// Internal bits.
	struct SchedulerInternal *internal_;

private:

	/// No copying.
	SchedulerPS3( const SchedulerPS3 & ) { }

	/// No assignment.
	SchedulerPS3 &operator = ( const SchedulerPS3 & ) { return *this; }

public:

	SchedulerPS3();
	~SchedulerPS3();

	/**
	 * @see Scheduler::MainThread()
	 */
	void MainThread();

	/**
	 * @see Scheduler::RunJob()
	 */
	void RunJob( Job *job );

	/**
	 * @see Schduler::RunJobASAP()
	 */
	void RunJobASAP( Job *job );

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
