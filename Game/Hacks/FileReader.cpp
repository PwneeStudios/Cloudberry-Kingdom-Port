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
	std::wstring s = Utf8ToWstring( file_->ReadLine() );
	// FIXME: get rid of this hack. file_->ReadLine should itself not include \r or \n at the end.

	if ( s.length() > 0 && s[ s.length() - 1 ] == L'\r' )
		s[ s.length() - 1 ] = L'\n';
	//if ( static_cast<int>( s.rfind( L"\r" ) ) >= 0 )
		//s.resize( s.size() - 1 );

	return s;
}
