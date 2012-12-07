#ifndef _QUEUE_H_
#define _QUEUE_H_

#include <algorithm>
#include <cstring>
#include <vector>

template<class T>
void Clear( std::queue<T> &v )
{
	using namespace std;

	queue<T> empty;
	swap( v, empty );
}

#endif
