#ifndef _QUEUE_H_
#define _QUEUE_H_

#include <algorithm>
#include <cstring>
#include <vector>

template<class T>
inline int Clear( const std::queue<T> &v )
{
	using namespace std;

	queue<shared_ptr<AnimQueueEntry> > empty;
	swap( AnimQueue, empty );
}

#endif
