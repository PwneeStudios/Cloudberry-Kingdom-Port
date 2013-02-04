#ifndef _BINARY_READER_H_
#define _BINARY_READER_H_

#include <Math/Vectors.h>
#include <memory>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <string>
#include <vector>

// Forward declarations.
class File;

struct BinaryReader
{

	BinaryReader() { }
	virtual ~BinaryReader() { }

	virtual void Close() = 0;
	virtual int ReadInt32() = 0;
	virtual unsigned int ReadUInt32() = 0;
	virtual unsigned long ReadUInt64() = 0;
	virtual std::wstring ReadString() = 0;
	virtual Vector2 ReadVector2() = 0;
	virtual bool ReadBoolean() = 0;
	virtual float ReadSingle() = 0;
	virtual unsigned char ReadByte() = 0;
	virtual unsigned char PeekChar() = 0;

};

struct FileBinaryReader : public BinaryReader
{

	boost::shared_ptr<File> file_;

	FileBinaryReader( const std::wstring &path );

	void Close();

	int ReadInt32();

	unsigned int ReadUInt32();

	unsigned long ReadUInt64();

	std::wstring ReadString();

	Vector2 ReadVector2();

	bool ReadBoolean();

	float ReadSingle();

	unsigned char ReadByte();

	unsigned char PeekChar();

};

#ifdef CAFE

struct SaveReaderWiiU
{

private:

	struct SaveReaderWiiUInternal *internal_;

public:

	SaveReaderWiiU( const std::string &path, bool global );
	~SaveReaderWiiU();

	bool ReadEverything( std::vector< unsigned char > &data );

};

#endif

#endif
