#ifndef _STRING_H_
#define _STRING_H_

#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <sstream>

inline std::wstring ToLower( const std::wstring &s )
{
	std::wstring lower = s;
	std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);

	return lower;
}

inline int CompareIgnoreCase( const std::wstring &s1, const std::wstring &s2)
{
	std::wstring::const_iterator it1, it2;
	
	for( it1 = s1.begin(), it2 = s2.begin(); it1 != s1.end() && it2 != s2.end(); ++it1, ++it2 )
	{
		int cmp = tolower( *it1 ) - tolower( *it2 );

		if( cmp != 0 )
		{
			return cmp;
		}
	}

	if( it1 == s1.end() && it2 == s2.end() )
		return 0;

	return ( it1 == s1.end() ) ? -1 : 1;
}

inline std::wstring Format( const wchar_t *fmt, ... )
{
	// FIXME: Implement this.
	return _T( "" );
}

inline void Split( const std::wstring &str, wchar_t c, std::vector<std::wstring> &parts )
{
	using namespace std;

	wstringstream wss( str );
	wstring part;
	while( getline( wss, part, c ) )
		parts.push_back( part );
}

template<class T>
T Parse( const std::wstring &str )
{
	using namespace std;
	wstringstream wss( str );

	T temp;
	wss >> temp;

	if( wss.fail() )
		return T( 0 );

	return temp;
}

// Specialization for unsigned characters.
template<>
unsigned char Parse<unsigned char>( const std::wstring &str )
{
	using namespace std;
	wstringstream wss( str );

	int temp;
	wss >> temp;

	if( wss.fail() )
		return 0;

	return static_cast<unsigned char>( temp );
}

#endif