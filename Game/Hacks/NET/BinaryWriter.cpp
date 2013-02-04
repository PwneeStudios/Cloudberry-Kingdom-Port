#include "BinaryWriter.h"

#include <Content/File.h>
#include <Content/Filesystem.h>

#include <Hacks/String.h>

FileBinaryWriter::FileBinaryWriter( std::wstring path ) :
	file_( FILESYSTEM.Open( WstringToUtf8( path ), true ) )
{
	assert( file_->IsOpen() );
}

FileBinaryWriter::~FileBinaryWriter()
{
}

void FileBinaryWriter::Write( const unsigned char *buffer, int offset, int length )
{
	file_->Write( reinterpret_cast<const char *>( buffer + offset ), length );
}

void FileBinaryWriter::Write( int i )
{
	file_->Write( reinterpret_cast<const char *>( &i ), 4 );
}

void FileBinaryWriter::Write( unsigned int i )
{
	file_->Write( reinterpret_cast<const char *>( &i ), 4 );
}

void FileBinaryWriter::Write( unsigned long long i )
{
	file_->Write( reinterpret_cast<const char *>( &i ), 8 );
}

void FileBinaryWriter::Write( const Vector2 &v )
{
	Write( v.X );
	Write( v.Y );
}

void FileBinaryWriter::Write( const std::wstring &s )
{
	std::string bytes( WstringToUtf8( s ) );

	size_t length = bytes.length();
	for( length; length >= 128u; length >>= 7 )
		Write( static_cast<unsigned char>( length | 128u ) );
	Write( static_cast<unsigned char>( length ) );

	file_->Write( bytes.c_str(), bytes.length() );
}

void FileBinaryWriter::Write( float v )
{
	file_->Write( reinterpret_cast<const char *>( &v ), 4 );
}

void FileBinaryWriter::Write( unsigned char c )
{
	file_->Write( reinterpret_cast<const char *>( &c ), 1 );
}