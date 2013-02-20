#include "String.h"

#include <string>

std::wstring FormatWithSeparators( int i )
{
	std::wstringstream wss;
	//wss.imbue( std::locale( "en_US.UTF-8" ) );
#ifdef PS3
	wss.imbue( std::locale( "C" ) );
#else
	wss.imbue( std::locale( "" ) ); // This should using the local culture's version of number formating. Test it?
#endif
	wss << i;

	return wss.str();
}