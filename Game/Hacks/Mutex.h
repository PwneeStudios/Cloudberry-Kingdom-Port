#ifndef _MUTEX_H_
#define _MUTEX_H_

struct Mutex
{

	Mutex();
	~Mutex();
	void Lock();
	void Unlock();

};

#endif