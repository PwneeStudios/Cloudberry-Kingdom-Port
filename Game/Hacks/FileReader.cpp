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
	return Utf8ToWstring( file_->ReadLine() );
}
