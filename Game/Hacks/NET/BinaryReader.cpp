#include "BinaryReader.h"

#include <Content/File.h>
#include <Content/Filesystem.h>
#include <Hacks/String.h>
#include <Utility/Log.h>

#ifdef CAFE
#include <cafe.h>
#include <cafe/fs.h>
#include <nn/save.h>
#include <nn/act.h>
#endif

#if defined( CAFE ) || defined( PS3 )
#define NTOHS( x ) ( ( ( ( x ) & 0xff ) << 8 ) | ( ( ( x ) >> 8 ) & 0xff ) )
#define NTOHL( x ) ( ( NTOHS( x & 0xffff ) << 16 ) | NTOHS( ( x >> 16 ) & 0xffff ) )
#define NTOHLL( x ) ( ( NTOHL( x & 0xffffffff ) << 32 ) | NTOHL( ( x >> 32 ) & 0xffffffff ) )
#else
#define NTOHS( x ) ( x )
#define NTOHL( x ) ( x )
#define NTOHLL( x ) ( x )
#endif

// FIXME: Delete this.
std::wstring BytesToWstring( const char *start, const char *end )
{
	std::wstring result;
	result.reserve( end - start );
	for( const char *c = start; c != end; ++c )
		result.push_back( static_cast<char>( *c ) );

	return result;
	/*std::wstring_convert<std::codecvt_utf8<wchar_t> > myconv;
	return myconv.from_bytes( start, end );*/
}

FileBinaryReader::FileBinaryReader( const std::wstring &path ) :
	file_( FILESYSTEM.Open( WstringToUtf8( path ) ) )
{
	assert( file_->IsOpen() );
}

void FileBinaryReader::Close()
{
}

int FileBinaryReader::ReadInt32()
{
	int t;
	file_->Read( reinterpret_cast<char *>( &t ), 4 );
	t = NTOHL( t );
	return t;
}

unsigned int FileBinaryReader::ReadUInt32()
{
	unsigned int t;
	file_->Read( reinterpret_cast<char *>( &t ), 4 );
	t = NTOHL( t );
	return t;
}

// FIXME: This may actually need to return a 64 bit unsigned integer.
unsigned long FileBinaryReader::ReadUInt64()
{
	unsigned long long t;
	file_->Read( reinterpret_cast<char *>( &t ), 8 );
	t = NTOHLL( t );
	return static_cast<unsigned long>( t );
}

std::wstring FileBinaryReader::ReadString()
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
	delete[] buffer;

	return str;
}

Vector2 FileBinaryReader::ReadVector2()
{
	Vector2 v;
	v.X = ReadSingle();
	v.Y = ReadSingle();
	return v;
}

bool FileBinaryReader::ReadBoolean()
{
	bool b;
	file_->Read( reinterpret_cast<char *>( &b ), 1 );
	return b;
}

float FileBinaryReader::ReadSingle()
{
	unsigned int t;
	file_->Read( reinterpret_cast<char *>( &t ), 4 );
	t = NTOHL( t );
	return *reinterpret_cast<float *>( &t );
}

unsigned char FileBinaryReader::ReadByte()
{
	unsigned char c;
	file_->Read( reinterpret_cast<char *>( &c ), 1 );
	return c;
}

unsigned char FileBinaryReader::PeekChar()
{
	return static_cast<unsigned char>( file_->Peek() );;
}

#ifdef CAFE

struct SaveReaderWiiUInternal
{
	FSClient Client;
	FSCmdBlock Cmd;

	FSStatus OpenStatus;
	FSFileHandle Fh;

	u8 AccountSlot;
};

static void stateChangeCallback( FSClient *pClient, FSVolumeState state, void *pContext )
{
	FSError lastError = FSGetLastError( pClient );
	LOG.Write( "Volume state of client 0X%08X changed to %d\n", pClient, state );
	LOG.Write( "Last error: %d\n", lastError );
}

SaveReaderWiiU::SaveReaderWiiU( const std::string &path, bool global )
	: internal_( new SaveReaderWiiUInternal )
{
	memset( internal_, 0, sizeof( SaveReaderWiiUInternal ) );

	FSAddClient( &internal_->Client, FS_RET_NO_ERROR );
	FSInitCmdBlock( &internal_->Cmd );

	FSStateChangeParams stateChangeParams = {
		.userCallback = stateChangeCallback,
		.userContext = NULL,
		.ioMsgQueue = NULL
	};

	FSSetStateChangeNotification( &internal_->Client, &stateChangeParams );

	internal_->AccountSlot = global ? ACT_SLOT_NO_COMMON : nn::act::GetSlotNo();

	internal_->OpenStatus = SAVEOpenFile( &internal_->Client, &internal_->Cmd,
		internal_->AccountSlot, path.c_str(), "r", &internal_->Fh, FS_RET_ALL_ERROR );
}

SaveReaderWiiU::~SaveReaderWiiU()
{
	FSStatus ret;
	if( internal_->Fh != FS_INVALID_HANDLE_VALUE && internal_->Fh > 0 )
		ret = FSCloseFile( &internal_->Client, &internal_->Cmd, internal_->Fh, FS_RET_ALL_ERROR );

	FSDelClient( &internal_->Client, FS_RET_NO_ERROR );

	delete internal_;
}

bool SaveReaderWiiU::ReadEverything( std::vector< unsigned char > &data )
{
	if( internal_->OpenStatus != FS_STATUS_OK || internal_->Fh <= 0 )
		return false;

	FSStat stat;
	FSStatus ret = FSGetStatFile( &internal_->Client, &internal_->Cmd, internal_->Fh, &stat, FS_RET_ALL_ERROR );

	if( ret != FS_STATUS_OK || stat.size == 0 )
		return false;

	data.resize( stat.size );
	unsigned char *aligned = reinterpret_cast< unsigned char * >( MEMAllocFromDefaultHeapEx( stat.size, FS_IO_BUFFER_ALIGN ) );
	ret = FSReadFile( &internal_->Client, &internal_->Cmd, aligned, data.size(), 1,
		internal_->Fh, 0, FS_RET_ALL_ERROR );
	data.assign( aligned, aligned + stat.size );
	MEMFreeToDefaultHeap( aligned );

	if( ret < 0 )
		return false;

	if( ret == FS_STATUS_OK )
		return true;

	// Make sure 1 element was read.
	return ret == 1;
}


#endif
