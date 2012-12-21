#ifndef _MUTEX_H_
#define _MUTEX_H_

struct Mutex
{

	struct MutexInternal *internal_;

	Mutex();
	~Mutex();
	void Lock();
	void Unlock();

};

#endif