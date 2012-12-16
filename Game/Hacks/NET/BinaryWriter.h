#ifndef _BINARY_WRITER_H_
#define _BINARY_WRITER_H_

#include <Math/Vectors.h>
#include <memory>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <string>

// Forward declarations.
class File;

struct BinaryWriter
{

	boost::shared_ptr<File> file_;

	BinaryWriter( std::wstring path );
	~BinaryWriter();
	void Write( const unsigned char *buffer, int offset, int length );
	void Write( int i );
	void Write( unsigned int i );
	void Write( unsigned long long i );
	void Write( const Vector2 &v );
	void Write( const std::wstring &s );
	void Write( float v );
	void Write( unsigned char c );

};

#endif
