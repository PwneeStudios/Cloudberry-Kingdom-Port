#ifndef _BINARY_WRITER_H_
#define _BINARY_WRITER_H_

#include <Math/Vectors.h>
#include <memory>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <string>
#include <vector>

// Forward declarations.
class File;

struct BinaryWriter
{

	BinaryWriter() { }
	virtual ~BinaryWriter() { }
	virtual void Write( const unsigned char *buffer, int offset, int length ) = 0;
	virtual void Write( int i ) = 0;
	virtual void Write( unsigned int i ) = 0;
	virtual void Write( unsigned long long i ) = 0;
	virtual void Write( const Vector2 &v ) = 0;
	virtual void Write( const std::wstring &s ) = 0;
	virtual void Write( float v ) = 0;
	virtual void Write( unsigned char c ) = 0;

};

struct FileBinaryWriter : public BinaryWriter
{
	boost::shared_ptr<File> file_;

	FileBinaryWriter( std::wstring path );
	~FileBinaryWriter();
	virtual void Write( const unsigned char *buffer, int offset, int length );
	virtual void Write( int i );
	virtual void Write( unsigned int i );
	virtual void Write( unsigned long long i );
	virtual void Write( const Vector2 &v );
	virtual void Write( const std::wstring &s );
	virtual void Write( float v );
	virtual void Write( unsigned char c );
};

struct MemoryBinaryWriter : public BinaryWriter
{
private:

	std::vector< unsigned char > buffer_;

public:

	MemoryBinaryWriter( size_t size );
	~MemoryBinaryWriter();
	virtual void Write( const unsigned char *buffer, int offset, int length );
	virtual void Write( int i );
	virtual void Write( unsigned int i );
	virtual void Write( unsigned long long i );
	virtual void Write( const Vector2 &v );
	virtual void Write( const std::wstring &s );
	virtual void Write( float v );
	virtual void Write( unsigned char c );

	const std::vector< unsigned char > &GetBuffer() const { return buffer_; }
};

#ifdef CAFE

struct SaveWriterWiiU : public BinaryWriter
{

private:

	struct SaveWriterWiiUInternal *internal_;

public:

	SaveWriterWiiU( const std::string &path, bool global );
	~SaveWriterWiiU();
	
	bool IsOpen();
	virtual void Write( const unsigned char *buffer, int offset, int length );
	virtual void Write( int i );
	virtual void Write( unsigned int i );
	virtual void Write( unsigned long long i );
	virtual void Write( const Vector2 &v );
	virtual void Write( const std::wstring &s );
	virtual void Write( float v );
	virtual void Write( unsigned char c );

};

#endif

#endif
