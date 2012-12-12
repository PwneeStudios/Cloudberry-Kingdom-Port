#include "BinaryWriter.h"

#include <Content/File.h>
#include <Content/Filesystem.h>

#include <Hacks/String.h>

BinaryWriter::BinaryWriter( std::wstring path ) :
	file_( FILESYSTEM.Open( WstringToUtf8( path ), true ) )
{
	assert( file_->IsOpen() );
}

BinaryWriter::~BinaryWriter()
{
}

void BinaryWriter::Write( const unsigned char *buffer, int offset, int length )
{
	file_->Write( reinterpret_cast<const char *>( buffer + offset ), length );
}

void BinaryWriter::Write( int i )
{
	file_->Write( reinterpret_cast<const char *>( &i ), 4 );
}

void BinaryWriter::Write( unsigned int i )
{
	file_->Write( reinterpret_cast<const char *>( &i ), 4 );
}

void BinaryWriter::Write( unsigned long long i )
{
	file_->Write( reinterpret_cast<const char *>( &i ), 8 );
}

void BinaryWriter::Write( const Vector2 &v )
{
	Write( v.X );
	Write( v.Y );
}

void BinaryWriter::Write( const std::wstring &s )
{
	std::string bytes( WstringToUtf8( s ) );

	size_t length = bytes.length();
	for( length; length >= 128u; length >>= 7 )
		Write( static_cast<unsigned char>( length | 128u ) );
	Write( static_cast<unsigned char>( length ) );

	file_->Write( bytes.c_str(), bytes.length() );
}

void BinaryWriter::Write( float v )
{
	file_->Write( reinterpret_cast<const char *>( &v ), 4 );
}

void BinaryWriter::Write( unsigned char c )
{
	file_->Write( reinterpret_cast<const char *>( &c ), 1 );
}