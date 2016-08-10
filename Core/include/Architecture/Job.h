/**
 * @file
 *
 * Base job interface.
 */
#ifndef _JOB_H_
#define _JOB_H_

/**
 * Base job.
 */
class Job
{

public:

	virtual ~Job() { }

	virtual void Do() = 0 ;

};

#endif
