#ifndef _DICT_H_
#define _DICT_H_

#include <algorithm>
#include <cstring>
#include <string>

#include "String.h"

template<class key, class item>
bool Contains( const std::map<key, item> &m, const key &k )
{
	using namespace std;

	return m.find( k ) != m.end();
}

template<class item>
void Add( std::map<std::wstring, item> &m, const std::wstring &k, const item &o )
{
	using namespace std;

	m[ ToLower( k ) ] = o;
}

#endif
