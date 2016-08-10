#ifndef _COMPARE_H_
#define _COMPARE_H_

//#if defined(DEBUG)
//#include <Utility\Log.h>
//#include <Hacks\String.h>
//#endif

template<class T>
int Compare( const T a, const T b )
{
//#if defined(DEBUG)
//	LOG_WRITE( WstringToUtf8( ToString( a ) + L" " + ToString( b ) + L"\n" ).c_str() );
//#endif

	// C# style compare:
	//if ( a > b ) return 1;
	//else if ( a < b ) return -1;
	//else return 0;

	if ( a < b ) return 1;
	else return 0;
}

#endif
