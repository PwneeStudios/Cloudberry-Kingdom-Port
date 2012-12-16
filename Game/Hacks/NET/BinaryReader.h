#ifndef _BINARY_READER_H_
#define _BINARY_READER_H_

#include <Math/Vectors.h>
#include <memory>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <string>

// Forward declarations.
class File;

struct BinaryReader
{

	boost::shared_ptr<File> file_;

	BinaryReader( const std::wstring &path );

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

#endif
