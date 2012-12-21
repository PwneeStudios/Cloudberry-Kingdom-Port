#ifndef _DICT_H_
#define _DICT_H_

#include <algorithm>
#include <cstring>
#include <string>
#include <map>

#include "String.h"

template<class key, class item>
bool Contains( const std::map<key, item> &m, const key &k )
{
	using namespace std;

	return m.find( k ) != m.end();
}

template< class item>
bool Contains( const std::map<std::wstring, item> &m, const std::wstring &k )
{
	using namespace std;

	return m.find( ToLower( k ) ) != m.end();
}

template<class item>
void Add( std::map<std::wstring, item> &m, const std::wstring &k, const item &o )
{
	using namespace std;

	m[ ToLower( k ) ] = o;
}

template<typename Key, typename Value>
void GetKeys( const std::map<Key, Value> &m, std::vector<Key> &keys)
{
	for( std::map<Key, Value>::const_iterator i = m.begin(); i != m.end(); ++i )
		keys.push_back( i->first );
}

#endif
