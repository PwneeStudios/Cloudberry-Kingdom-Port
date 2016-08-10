#ifndef _SCHEDULER_VITA_H_
#define _SCHEDULER_VITA_H_

#include <ForwardDeclarations.h>

class SchedulerVita
{

	// Internal bits.
	struct SchedulerInternal *internal_;

private:

	/// No copying.
	SchedulerVita( const SchedulerVita & ) { }

	/// No assignment.
	SchedulerVita &operator = ( const SchedulerVita & ) { return *this; }

public:

	SchedulerVita();
	~SchedulerVita();

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
