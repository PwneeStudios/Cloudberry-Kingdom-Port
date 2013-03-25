#include "BinaryWriter.h"

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


MemoryBinaryWriter::MemoryBinaryWriter( size_t size )
{
	buffer_.reserve( size );
}

MemoryBinaryWriter::~MemoryBinaryWriter()
{
}

void MemoryBinaryWriter::Write( const unsigned char *buffer, int offset, int length )
{
	buffer_.insert( buffer_.end(), buffer + offset, buffer + offset + length );
}

void MemoryBinaryWriter::Write( int i )
{
	Write( reinterpret_cast< const unsigned char * >( &i ), 0, sizeof( int ) );
}

void MemoryBinaryWriter::Write( unsigned int i )
{
	Write( reinterpret_cast< const unsigned char * >( &i ), 0, sizeof( unsigned int ) );
}

void MemoryBinaryWriter::Write( unsigned long long i )
{
	Write( reinterpret_cast< const unsigned char * >( &i ), 0, sizeof( unsigned long long ) );
}

void MemoryBinaryWriter::Write( const Vector2 &v )
{
	Write( v.X );
	Write( v.Y );
}

void MemoryBinaryWriter::Write( const std::wstring &s )
{
	std::string bytes( WstringToUtf8( s ) );

	size_t length = bytes.length();
	for( length; length >= 128u; length >>= 7 )
		Write( static_cast<unsigned char>( length | 128u ) );
	Write( static_cast<unsigned char>( length ) );

	Write( reinterpret_cast< const unsigned char * >( bytes.c_str() ), 0, bytes.length() );
}

void MemoryBinaryWriter::Write( float v )
{
	Write( reinterpret_cast< const unsigned char * >( &v ), 0, sizeof( float ) );
}

void MemoryBinaryWriter::Write( unsigned char c )
{
	buffer_.push_back( c );
}

#ifdef CAFE

static FSClient gClient;
static FSCmdBlock gCmd;

void InitSaveFS()
{
	FSAddClient( &gClient, FS_RET_NO_ERROR );
	FSInitCmdBlock( &gCmd );
}

void TerminateSaveFS()
{
	FSDelClient( &gClient, FS_RET_NO_ERROR );
}

struct SaveWriterWiiUInternal
{
	/*FSClient Client;
	FSCmdBlock Cmd;*/
	FSFileHandle FileHandle;

	u8 AccountSlot;
	u32 PersistentID;

	FSStatus OpenStatus;
	FSFileHandle Fh;
	bool IsOpen;

	void *AlignedBuffer;
};

const int ALIGNED_BUFFER_SIZE = 512;

static void stateChangeCallback( FSClient *pClient, FSVolumeState state, void *pContext )
{
	FSError lastError = FSGetLastError( pClient );
	LOG_WRITE( "Volume state of client 0X%08X changed to %d\n", pClient, state );
	LOG_WRITE( "Last error: %d\n", lastError );
}

SaveWriterWiiU::SaveWriterWiiU( const std::string &path, bool global )
	: internal_( new SaveWriterWiiUInternal )
{
	memset( internal_, 0, sizeof( SaveWriterWiiUInternal ) );

	internal_->AccountSlot = nn::act::GetSlotNo();
	internal_->PersistentID = nn::act::GetPersistentIdEx( internal_->AccountSlot );

	/*FSAddClient( &internal_->Client, FS_RET_NO_ERROR );
	FSInitCmdBlock( &internal_->Cmd );*/

	FSStateChangeParams stateChangeParams = {
		.userCallback = stateChangeCallback,
		.userContext = NULL,
		.ioMsgQueue = NULL
	};

	internal_->IsOpen = false;
	/*internal_->OpenStatus = SAVEOpenFile( &internal_->Client, &internal_->Cmd,
		global ? ACT_SLOT_NO_COMMON : internal_->AccountSlot,
		path.c_str(), "w", &internal_->Fh, FS_RET_ALL_ERROR );*/
	internal_->OpenStatus = SAVEOpenFile( &gClient, &gCmd,
		global ? ACT_SLOT_NO_COMMON : internal_->AccountSlot,
		path.c_str(), "w", &internal_->Fh, FS_RET_ALL_ERROR );

	if( internal_->OpenStatus == FS_STATUS_OK && internal_->Fh > 0 )
	{
		internal_->IsOpen = true;

		internal_->AlignedBuffer = MEMAllocFromDefaultHeapEx( ALIGNED_BUFFER_SIZE, FS_IO_BUFFER_ALIGN );
	}
}

void FlushCallback( FSClient *client, FSCmdBlock *block, FSStatus result, void *context )
{
}

SaveWriterWiiU::~SaveWriterWiiU()
{
	if( internal_->AlignedBuffer )
	{
		MEMFreeToDefaultHeap( internal_->AlignedBuffer );
	}

	if( internal_->IsOpen )
	{
		internal_->IsOpen = false;
		/*FSCloseFile( &internal_->Client, &internal_->Cmd, internal_->Fh, FS_RET_NO_ERROR );
	
		SAVEFlushQuota( &internal_->Client, &internal_->Cmd, internal_->AccountSlot, FS_RET_NO_ERROR );*/
		FSCloseFile( &gClient, &gCmd, internal_->Fh, FS_RET_NO_ERROR );
	
		//SAVEFlushQuota( &gClient, &gCmd, internal_->AccountSlot, FS_RET_NO_ERROR );

		FSAsyncParams asyncParams;
		memset( &asyncParams, 0, sizeof( asyncParams ) );
		
		asyncParams.userCallback = FlushCallback;
		asyncParams.userContext = NULL;
		asyncParams.ioMsgQueue = NULL;
		
		SAVEFlushQuotaAsync( &gClient, &gCmd, internal_->AccountSlot, FS_RET_NO_ERROR, &asyncParams );
	}

	//FSDelClient( &internal_->Client, FS_RET_NO_ERROR );

	delete internal_;
}

bool SaveWriterWiiU::IsOpen()
{
	return internal_->IsOpen;
}

void SaveWriterWiiU::Write( const unsigned char *buffer, int offset, int length )
{
	if( !internal_->IsOpen )
	{
		LOG_WRITE( "Write failed\n" );
		return;
	}

	void *buf = internal_->AlignedBuffer;
	if( length > ALIGNED_BUFFER_SIZE )
		buf = MEMAllocFromDefaultHeapEx( length, FS_IO_BUFFER_ALIGN );

	memcpy( buf, buffer + offset, length );

	/*FSStatus stat = FSWriteFile( &internal_->Client, &internal_->Cmd, buf, length,
		sizeof( unsigned char ), internal_->Fh, 0, FS_RET_ALL_ERROR );*/
	FSStatus stat = FSWriteFile( &gClient, &gCmd, buf, length,
		sizeof( unsigned char ), internal_->Fh, 0, FS_RET_ALL_ERROR );

	if( buf != internal_->AlignedBuffer )
		MEMFreeToDefaultHeap( buf );
}

void SaveWriterWiiU::Write( int i )
{
	if( !internal_->IsOpen )
	{
		LOG_WRITE( "Write failed\n" );
		return;
	}

	memcpy( internal_->AlignedBuffer, &i, sizeof( int ) );
	/*FSStatus stat = FSWriteFile( &internal_->Client, &internal_->Cmd, internal_->AlignedBuffer, sizeof( int ), 1,
		internal_->Fh, 0, FS_RET_NO_ERROR );*/
	FSStatus stat = FSWriteFile( &gClient, &gCmd, internal_->AlignedBuffer, sizeof( int ), 1,
		internal_->Fh, 0, FS_RET_NO_ERROR );
}

void SaveWriterWiiU::Write( unsigned int i )
{
	if( !internal_->IsOpen )
	{
		LOG_WRITE( "Write failed\n" );
		return;
	}

	memcpy( internal_->AlignedBuffer, &i, sizeof( unsigned int ) );
	/*FSWriteFile( &internal_->Client, &internal_->Cmd, internal_->AlignedBuffer, sizeof( unsigned int ), 1,
		internal_->Fh, 0, FS_RET_NO_ERROR );*/
	FSWriteFile( &gClient, &gCmd, internal_->AlignedBuffer, sizeof( unsigned int ), 1,
		internal_->Fh, 0, FS_RET_NO_ERROR );
}

void SaveWriterWiiU::Write( unsigned long long i )
{
	if( !internal_->IsOpen )
	{
		LOG_WRITE( "Write failed\n" );
		return;
	}

	memcpy( internal_->AlignedBuffer, &i, sizeof( unsigned long long ) );
	/*FSWriteFile( &internal_->Client, &internal_->Cmd, internal_->AlignedBuffer, sizeof( unsigned long long ), 1,
		internal_->Fh, 0, FS_RET_NO_ERROR );*/
	FSWriteFile( &gClient, &gCmd, internal_->AlignedBuffer, sizeof( unsigned long long ), 1,
		internal_->Fh, 0, FS_RET_NO_ERROR );
}

void SaveWriterWiiU::Write( const Vector2 &v )
{
	Write( v.X );
	Write( v.Y );
}

void SaveWriterWiiU::Write( const std::wstring &s )
{
	if( !internal_->IsOpen )
	{
		LOG_WRITE( "Write failed\n" );
		return;
	}

	std::string bytes( WstringToUtf8( s ) );

	size_t length = bytes.length();
	for( length; length >= 128u; length >>= 7 )
		Write( static_cast<unsigned char>( length | 128u ) );
	Write( static_cast<unsigned char>( length ) );

	Write( reinterpret_cast< const unsigned char * >( bytes.c_str() ), 0, bytes.length() );
}

void SaveWriterWiiU::Write( float v )
{
	if( !internal_->IsOpen )
	{
		LOG_WRITE( "Write failed\n" );
		return;
	}

	memcpy( internal_->AlignedBuffer, &v, sizeof( float ) );
	/*FSWriteFile( &internal_->Client, &internal_->Cmd, internal_->AlignedBuffer, sizeof( float ), 1,
		internal_->Fh, 0, FS_RET_NO_ERROR );*/
	FSWriteFile( &gClient, &gCmd, internal_->AlignedBuffer, sizeof( float ), 1,
		internal_->Fh, 0, FS_RET_NO_ERROR );
}

void SaveWriterWiiU::Write( unsigned char c )
{
	if( !internal_->IsOpen )
	{
		LOG_WRITE( "Write failed\n" );
		return;
	}

	unsigned char *buf = reinterpret_cast< unsigned char * >( internal_->AlignedBuffer );
	buf[ 0 ] = c;
	FSWriteFile( &gClient, &gCmd, buf, sizeof( unsigned char ), 1,
		internal_->Fh, 0, FS_RET_NO_ERROR );
}

#endif