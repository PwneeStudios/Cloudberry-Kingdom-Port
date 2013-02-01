#ifndef _PARSE_H_
#define _PARSE_H_

#include <sstream>

#include "Hacks/NET/DateTime.h"

template <typename T>
std::wstring ToString( const T &t )
{
	std::wstringstream wss;
	wss << t;
	return wss.str();
}

template <>
inline std::wstring ToString<DateTime>( const DateTime &dt )
{
	// FIXME: implement
	return L"";
}

//template <typename T>
//inline std::wstring ToString( const T i )
//{
//	using namespace std;
//
//	std::wstring s;
//	wstringstream converter;
//
//	converter << i;
//	s = converter.str();
//
//	return s;
//}

inline bool ParseInt( const std::wstring &s, int &val )
{
	using namespace std;

	wstringstream converter;

	converter << s;
	converter >> val;

	if ( !converter ) return false;

	return true;
}

// FIXME: do we need to specify precision or anything here?
inline bool ParseFloat( const std::wstring &s, float &val )
{
	using namespace std;

	wstringstream converter;

	converter << s;
	converter >> val;

	if ( !converter ) return false;

	return true;
}

#endif
