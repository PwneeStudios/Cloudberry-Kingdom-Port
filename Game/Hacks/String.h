#ifndef _STRING_H_
#define _STRING_H_

#include <algorithm>
#include <cstdarg>
#include <iostream>
#include <iterator>
#include <string>
#include <sstream>

#include "Hacks/Parse.h"

inline int GetHashCode( const std::wstring &s )
{
	// FIXME
	return 0;
}

inline std::wstring ToLower( const std::wstring &s )
{
	std::wstring lower = s;
	std::transform( lower.begin(), lower.end(), lower.begin(), ::tolower );

	return lower;
}

inline bool Contains( const std::wstring big_string, const std::wstring inside_string )
{
	return big_string.find( inside_string ) != std::wstring::npos;
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

struct IgnoreCaseComparator
{



	bool operator() ( const std::wstring &lhs, const std::wstring &rhs ) const
	{
		return CompareIgnoreCase( lhs, rhs ) < 0;
	}

};

//inline std::wstring Format( const wchar_t *fmt, ... )
//{
//	// FIXME: Implement this.
//	return _T( "" );
//}

/*template<class T1>
inline std::wstring Format( std::wstring s, T1 t1 )
{
	std::vector<std::wstring> params;
	params.push_back( ToString( t1 ) );

	return Format( s, params );
}

template<class T1, class T2>
inline std::wstring Format( std::wstring s, T1 t1, T2 t2 )
{
	std::vector<std::wstring> params;
	params.push_back( ToString( t1 ) );
	params.push_back( ToString( t2 ) );

	return Format( s, params );
}

template<class T1, class T2, class T3>
inline std::wstring Format( std::wstring s, T1 t1, T2 t2, T3 t3 )
{
	std::vector<std::wstring> params;
	params.push_back( ToString( t1 ) );
	params.push_back( ToString( t2 ) );
	params.push_back( ToString( t3 ) );

	return Format( s, params );
}

template<class T1, class T2, class T3, class T4>
inline std::wstring Format( std::wstring s, T1 t1, T2 t2, T3 t3, T4 t4 )
{
	std::vector<std::wstring> params;
	params.push_back( ToString( t1 ) );
	params.push_back( ToString( t2 ) );
	params.push_back( ToString( t3 ) );
	params.push_back( ToString( t4 ) );

	return Format( s, params );
}

template<class T1, class T2, class T3, class T4, class T5>
inline std::wstring Format( std::wstring s, T1 t1, T2 t2, T3 t3, T4 t4, T5 t5 )
{
	std::vector<std::wstring> params;
	params.push_back( ToString( t1 ) );
	params.push_back( ToString( t2 ) );
	params.push_back( ToString( t3 ) );
	params.push_back( ToString( t4 ) );
	params.push_back( ToString( t5 ) );

	return Format( s, params );
}

template<class T1, class T2, class T3, class T4, class T5, class T6>
inline std::wstring Format( std::wstring s, T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6 )
{
	std::vector<std::wstring> params;
	params.push_back( ToString( t1 ) );
	params.push_back( ToString( t2 ) );
	params.push_back( ToString( t3 ) );
	params.push_back( ToString( t4 ) );
	params.push_back( ToString( t5 ) );
	params.push_back( ToString( t6 ) );

	return Format( s, params );
}*/

inline std::wstring Format( wchar_t *format, ... )
{
	wchar_t buffer[512];

	va_list args;
	va_start( args, format );
	vswprintf( buffer, sizeof( buffer ) / sizeof( wchar_t ), format, args );
	va_end( args );

	return std::wstring( buffer );
}

inline std::wstring FormatWithSeparators( int i )
{
	std::wstringstream wss;
	wss.imbue( std::locale( "en_US.UTF-8" ) );
	wss << i;
	return wss.str();
}


// FIXME: Do not understand why format doesn't take a wstring like this method (Used in VerifyDeleteSeed.cpp, other Format wouldn't compile)
//inline std::wstring Format( std::wstring s, ... )
//{
//	// FIXME: Implement this. 
//	return _T( "" );
//}

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
inline unsigned char Parse<unsigned char>( const std::wstring &str )
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

inline void Replace( std::wstring &s, wchar_t x, wchar_t y )
{
	for( std::wstring::iterator i = s.begin(); i != s.end(); ++i )
	{
		if( *i == x )
			*i = y;
	}
}

//std::wstring operator += ( std::wstring &LHS, const std::wstring &RHS )
//{
//	LHS.append( RHS );
//	return LHS;
//}
//
//std::wstring operator + ( const std::wstring &s1, const std::wstring &s2 )
//{
//	std::wstring sum = s1;
//	::operator+=( sum, s2 );
//
//	return sum;
//}

#endif