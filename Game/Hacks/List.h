#ifndef _LIST_H_
#define _LIST_H_

#include <algorithm>
#include <cstring>
#include <vector>

template<class T>
int IndexOf( const std::vector<T> &v, const T &o )
{
	using namespace std;

	vector<T>::const_iterator i = find( v.begin(), v.end(), o );
	return i - v.begin();
}

template<class T>
void AddRange( std::vector<T> &dst, const std::vector<T> &src )
{
	using namespace std;
	vector<T>::const_iterator i;
	for( i = src.begin(); i != src.end(); ++i )
		dst.push_back( *i );
}

template<class T>
void Remove( std::vector<T> &v, const T &o )
{
	using namespace std;
	vector<T>::iterator i = remove( v.begin(), v.end(), o );
	v.erase( i, v.end() );
}

template<class T>
void CopyFromTo( const std::vector<T> &v1, std::vector<T> &v2 )
{
	//v2.assign( v1.begin(), v1.end() );
	std::copy( v1.begin(), v1.end(), v2.begin() );
}

template<class T, class Predicate>
void Sort( std::vector<T> &v, const Predicate &pred )
{
	std::sort( v.begin(), v.end(), pred );
}

template<class T, size_t N>
std::vector<T> VecFromArray( T (&a)[N] )
{
	//return std::vector<T>( a, a + sizeof( a ) / sizeof( T ) );
	//return std::vector<T>( a, a + sizeof( a ) / sizeof( a[0] ) );
	return std::vector<T>( a, a + N );
}

template<class T>
void Insert( std::vector<T> v, int index, T a )
{
	v.insert( v.begin() + index, a );
}

template<class T>
T Sum( std::vector<T> v )
{
	T s = T( 0 );
	for( std::vector<T>::iterator i = v.begin(); i != v.end(); ++i )
		s += *i;
	return s;
}

template<typename Key, typename Value>
void GetKeys( const std::map<Key, Value> &m, std::vector<Key> &keys)
{
	for( std::map<Key, Value>::const_iterator i = m.begin(); i != m.end(); ++i )
		keys.push_back( i->first );
}

#endif
