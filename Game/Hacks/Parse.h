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
	return _T( "" );
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

inline int ParseInt( const std::wstring &s )
{
	using namespace std;

	int num = 0;
	wstringstream converter;

	converter << s;
	converter >> num;

	return num;
}

// FIXME: do we need to specify precision or anything here?
inline float ParseFloat( const std::wstring &s )
{
	using namespace std;

	float num = 0;
	wstringstream converter;

	converter << s;
	converter >> num;

	return num;
}

#endif
