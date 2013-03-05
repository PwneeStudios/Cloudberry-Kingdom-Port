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

std::wstring Utf8ToWstring( const std::string& str )
{
#ifdef PS3
#endif
	std::wstring result;
	result.reserve( str.length() );
	for( std::string::const_iterator i = str.begin(); i != str.end(); ++i )
		result.push_back( static_cast<wchar_t>( *i ) );

	return result;
	/*std::wstring_convert<std::codecvt_utf8<wchar_t> > myconv;
	return myconv.from_bytes( str );*/
}

std::wstring BytesToWstring( const char *start, const char *end )
{
	std::wstring result;
	result.reserve( end - start );
	for( const char *c = start; c != end; ++c )
		result.push_back( static_cast<char>( *c ) );

	return result;
	/*std::wstring_convert<std::codecvt_utf8<wchar_t> > myconv;
	return myconv.from_bytes( start, end );*/
}

std::string WstringToUtf8( const std::wstring& str )
{
#ifdef PS3
	char utf8[ 512 ];
	size_t inSize = str.size();
	size_t outSize = sizeof( utf8 );
	if( l10n_convert_str( l10n_get_converter( L10N_UTF16, L10N_UTF8 ), str.c_str(), &inSize, utf8, &outSize ) != ConversionOK )
		return "";

	return std::string( utf8, utf8 + outSize );
#else
	std::string result;
	result.reserve( str.length() );
	for( std::wstring::const_iterator i = str.begin(); i != str.end(); ++i )
		result.push_back( static_cast<char>( *i ) );
	return result;
#endif
	/*std::wstring_convert<std::codecvt_utf8<wchar_t> > myconv;
	return myconv.to_bytes( str );*/
}