#include "BinaryReader.h"

#include <Content/File.h>
#include <Content/Filesystem.h>

#include <Hacks/String.h>

BinaryReader::BinaryReader( const std::wstring &path ) :
	file_( FILESYSTEM.Open( WstringToUtf8( path ) ) )
{
	assert( file_->IsOpen() );
}

void BinaryReader::Close()
{
}

int BinaryReader::ReadInt32()
{
	int t;
	file_->Read( reinterpret_cast<char *>( &t ), 4 );
	return t;
}

unsigned int BinaryReader::ReadUInt32()
{
	unsigned int t;
	file_->Read( reinterpret_cast<char *>( &t ), 4 );
	return t;
}

// FIXME: This may actually need to return a 64 bit unsigned integer.
unsigned long BinaryReader::ReadUInt64()
{
	unsigned long long t;
	file_->Read( reinterpret_cast<char *>( &t ), 8 );
	return static_cast<unsigned long>( t );
}

std::wstring BinaryReader::ReadString()
{
	int length = 0;
	int num2 = 0;
	while (num2 != 35)
	{
		unsigned char b = ReadByte();
		length |= static_cast<int>( b & 127 ) << num2;
		num2 += 7;
		if ( ( b & 128 ) == 0)
			break;
	}

	if( length == 0 )
		return std::wstring( L"" );
	
	assert( length > 0 );

	char *buffer = new char[ length + 1 ];
	file_->Read( buffer, length );
	buffer[ length ] = '\0';
	std::wstring str = BytesToWstring( buffer, buffer + length );
	delete buffer;

	return str;
}

Vector2 BinaryReader::ReadVector2()
{
	Vector2 v;
	v.X = ReadSingle();
	v.Y = ReadSingle();
	return v;
}

bool BinaryReader::ReadBoolean()
{
	bool b;
	file_->Read( reinterpret_cast<char *>( &b ), 1 );
	return b;
}

float BinaryReader::ReadSingle()
{
	float f;
	file_->Read( reinterpret_cast<char *>( &f ), 4 );
	return f;
}

unsigned char BinaryReader::ReadByte()
{
	unsigned char c;
	file_->Read( reinterpret_cast<char *>( &c ), 1 );
	return c;
}

unsigned char BinaryReader::PeekChar()
{
	return static_cast<unsigned char>( file_->Peek() );;
}
