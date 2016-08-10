#include "FileReader.h"

#include <Content/File.h>
#include <Content/Filesystem.h>

#include <Hacks/String.h>

FileReader::FileReader( const std::wstring &path ) :
	file_( FILESYSTEM.Open( WstringToUtf8( path ) ) )
{
	assert( file_->IsOpen() );
}

FileReader::~FileReader()
{
}

std::wstring FileReader::ReadLine()
{
	std::string s = file_->ReadLine();
	std::wstring ws;

	for ( int i = 0; i < s.length(); i++ )
	{
		if ( ( s[ i ] & 0x80 ) == 0x80 /* 1000000 */ ) 
		{
			int BytesToRead = 0;
			char FirstMask;

			if		( ( s[ i ] & 0xF0 ) == 0xF0 /* 11110000 */ ) { BytesToRead = 4; FirstMask = 0x0F; /* 00001111 */ }
			else if ( ( s[ i ] & 0xE0 ) == 0xE0 /* 11100000 */ ) { BytesToRead = 3; FirstMask = 0x1F; /* 00011111 */ }
			else if ( ( s[ i ] & 0xC0 ) == 0xC0 /* 11000000 */ ) { BytesToRead = 2; FirstMask = 0x3F; /* 00111111 */ }
			else { return ws; /* not a valid UTF-8 string */ } 

			int val = s[ i ] & FirstMask;
			int shift = 0;
			for ( int j = 0; j < BytesToRead - 1; ++j)
			{
				++i;

				val = val << 6;
				val += static_cast<int>( s[ i ] & 0x3F /* 00111111 */ );
			}
			ws.push_back( static_cast<wchar_t>( val ) );
		}
		else
		{
			if ( s[ i ] != 13 )
				ws.push_back( static_cast<wchar_t>( s[ i ] ) ); 
		}
	}

	return ws;

	/*
	std::wstring s = Utf8ToWstring( file_->ReadLine() );
	// FIXME: get rid of this hack. file_->ReadLine should itself not include \r or \n at the end.

	if ( s.length() > 0 && s[ s.length() - 1 ] == L'\r' )
		s[ s.length() - 1 ] = L'\n';
	//if ( static_cast<int>( s.rfind( L"\r" ) ) >= 0 )
		//s.resize( s.size() - 1 );

	return s;*/
}
