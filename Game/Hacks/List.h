#ifndef _LIST_H_
#define _LIST_H_

#include <algorithm>
#include <cstring>
#include <vector>

template<class T>
inline int IndexOf( const std::vector<T> &v, const T &o )
{
	using namespace std;

	vector<T>::iterator i = find( v.begin(), v.end(), o );
	return i - v.begin();
}

#endif
