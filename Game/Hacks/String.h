#ifndef _STRING_H_
#define _STRING_H_

#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <sstream>

int GetHashCode( const std::wstring &s )
{
	// FIXME
	return 0;
}

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

class IgnoreCaseComparator
{

public:

	bool operator() ( const std::wstring &lhs, const std::wstring &rhs ) const
	{
		return CompareIgnoreCase( lhs, rhs ) < 0;
	}

};

inline std::wstring Format( const wchar_t *fmt, ... )
{
	// FIXME: Implement this.
	return _T( "" );
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

inline std::vector<std::wstring> &Split( const std::wstring &s, wchar_t delim, std::vector<std::wstring> &elems )
{
    std::wstringstream ss( s );
    std::wstring item;

    while( std::getline( ss, item, delim ) )
        elems.push_back( item );

    return elems;
}


inline std::vector<std::wstring> Split( const std::wstring &s, wchar_t delim )
{
    std::vector<std::wstring> elems;
    return Split( s, delim, elems );
}

#endif