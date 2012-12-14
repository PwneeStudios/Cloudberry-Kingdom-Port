#ifndef _COMPARE_H_
#define _COMPARE_H_

template<class T>
int Compare( const T a, const T b )
{
	// C# style compare:
	//if ( a > b ) return 1;
	//else if ( a < b ) return -1;
	//else return 0;

	if ( a >= b ) return 1;
	else return 0;
}

#endif
