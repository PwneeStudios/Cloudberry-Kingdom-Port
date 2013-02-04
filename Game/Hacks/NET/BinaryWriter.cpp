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

#ifdef CAFE

struct SaveWriterWiiUInternal
{
	FSClient Client;
	FSCmdBlock Cmd;
	FSFileHandle FileHandle;

	u8 AccountSlot;
	u32 PersistentID;

	FSFileHandle Fh;
	bool IsOpen;
};

SaveWriterWiiU::SaveWriterWiiU( const std::string &path, bool global )
	: internal_( new SaveWriterWiiUInternal )
{
	memset( internal_, 0, sizeof( SaveWriterWiiUInternal ) );

	internal_->AccountSlot = nn::act::GetSlotNo();
	internal_->PersistentID = nn::act::GetPersistentIdEx( internal_->AccountSlot );

	FSAddClient( &internal_->Client, FS_RET_NO_ERROR );
	FSInitCmdBlock( &internal_->Cmd );

	if( nn::act::IsSlotOccupied( internal_->AccountSlot ) )
	{
		LOG.Write( "Creating account for slot %d with id 0x%X\n", internal_->AccountSlot, internal_->PersistentID );

		if( SAVEInitSaveDir( internal_->AccountSlot ) != SAVE_STATUS_OK )
		{
			LOG.Write( "Failed to create save directory.\n" );
		}
	}

	if( SAVEInitSaveDir( ACT_SLOT_NO_COMMON ) != SAVE_STATUS_OK )
	{
		LOG.Write( "Failed to create common directory.\n" );
	}

	SAVEOpenFile( &internal_->Client, &internal_->Cmd, internal_->AccountSlot, path.c_str(), "w", &internal_->Fh, FS_RET_NO_ERROR );
	internal_->IsOpen = true;
	//SAVEMakeDir( &internal_->Client, &internal_->Cmd, internal_->AccountSlot
}

SaveWriterWiiU::~SaveWriterWiiU()
{
	FSCloseFile( &internal_->Client, &internal_->Cmd, internal_->Fh, FS_RET_NO_ERROR );
	internal_->IsOpen = false;

	SAVEFlushQuota( &internal_->Client, &internal_->Cmd, internal_->AccountSlot, FS_RET_NO_ERROR );

	FSDelClient( &internal_->Client, FS_RET_NO_ERROR );

	delete internal_;
}

bool SaveWriterWiiU::IsOpen()
{
	return internal_->IsOpen;
}

void SaveWriterWiiU::Write( const unsigned char *buffer, int offset, int length )
{
	FSWriteFile( &internal_->Client, &internal_->Cmd, buffer + offset, sizeof( unsigned char ),
		length, internal_->Fh, 0, FS_RET_NO_ERROR );
}

void SaveWriterWiiU::Write( int i )
{
	FSWriteFile( &internal_->Client, &internal_->Cmd, &i, sizeof( int ), 1,
		internal_->Fh, 0, FS_RET_NO_ERROR );
}

void SaveWriterWiiU::Write( unsigned int i )
{
	FSWriteFile( &internal_->Client, &internal_->Cmd, &i, sizeof( unsigned int ), 1,
		internal_->Fh, 0, FS_RET_NO_ERROR );
}

void SaveWriterWiiU::Write( unsigned long long i )
{
	FSWriteFile( &internal_->Client, &internal_->Cmd, &i, sizeof( unsigned long long ), 1,
		internal_->Fh, 0, FS_RET_NO_ERROR );
}

void SaveWriterWiiU::Write( const Vector2 &v )
{
	Write( v.X );
	Write( v.Y );
}

void SaveWriterWiiU::Write( const std::wstring &s )
{
	std::string bytes( WstringToUtf8( s ) );

	size_t length = bytes.length();
	for( length; length >= 128u; length >>= 7 )
		Write( static_cast<unsigned char>( length | 128u ) );
	Write( static_cast<unsigned char>( length ) );

	FSWriteFile( &internal_->Client, &internal_->Cmd, bytes.c_str(), 1, bytes.length(),
		internal_->Fh, 0, FS_RET_NO_ERROR );
}

void SaveWriterWiiU::Write( float v )
{
	FSWriteFile( &internal_->Client, &internal_->Cmd, &v, sizeof( float ), 1,
		internal_->Fh, 0, FS_RET_NO_ERROR );
}

void SaveWriterWiiU::Write( unsigned char c )
{
	FSWriteFile( &internal_->Client, &internal_->Cmd, &c, sizeof( unsigned char ), 1,
		internal_->Fh, 0, FS_RET_NO_ERROR );
}

#endif