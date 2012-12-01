#ifndef _BINARY_WRITER_H_
#define _BINARY_WRITER_H_

#include <Math/Vectors.h>
#include <string>

class BinaryWriter
{

public:

	BinaryWriter( std::wstring path )
	{
		// C# Binary Writer takes a stream in the constructor, but we always have a string made from a file.
	}

	~BinaryWriter()
	{
	}

	void Write( const unsigned char *buffer, int offset, int length )
	{
		// FIXME: Implement this.
	}

	void Write( int i )
	{
	}

	void Write( const Vector2 &v )
	{
	}

	void Write( const std::wstring &s )
	{
	}

	void Write( float v )
	{
	}

};

#endif
