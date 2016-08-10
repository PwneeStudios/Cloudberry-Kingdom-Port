#include <Content/FilesystemWiiU.h>

#include <Content/File.h>
#include <Utility/Error.h>
#include <Utility/Log.h>
#include <Utility/Mutex.h>

#include <cafe.h>
#include <cafe/fs.h>
#include <nn/act.h>
#include <nn/save.h>
#include <sstream>

/**
 * File implementation for Pc.
 */
class FileWiiU : public File
{

	const char *buffer_;
	size_t length_;
	size_t get_;

private:

	/// No copying.
	FileWiiU( const FileWiiU & ) { }

	/// No assignment.
	FileWiiU &operator = ( const FileWiiU & ) {	return *this; }

public:

	FileWiiU( const char *buffer, size_t length ) :
		buffer_( buffer ),
		length_( length ),
		get_( 0 )
	{
	}

	~FileWiiU()
	{
		MEMFreeToDefaultHeap( const_cast< char * >( buffer_ ) );
	}

	/**
	 * @see File::Read()
	 */
	size_t Read( char *buffer, size_t length )
	{
		// Current position plus requested length goes beyond the buffer.
		if( get_ + length >= length_ )
		{
			memcpy( buffer, buffer_ + get_, length_ - get_ );
			get_ = length_;
			return length_ - get_;
		}

		memcpy( buffer, buffer_ + get_, length );
		get_ += length;
		return length;
	}

	/**
	 * @see File::Write()
	 */
	size_t Write( const char *buffer, size_t length )
	{
		assert( !"File writing not yet implemented." );
	}

	/**
	 * @see File::ReadLine()
	 */
	std::string ReadLine()
	{
		const char *start = buffer_ + get_;
		while( get_ < length_ && buffer_[ get_ ] != '\n' )
			++get_;

		++get_;
		return std::string( start, buffer_ + get_ - 1 );
	}
	
	/**
	 * @see File::Peek()
	 */
	int Peek()
	{
		return buffer_[ get_ ];
	}

	/**
	 * @see File::IsOpen()
	 */
	bool IsOpen()
	{
		return true;
	}

	/**
	 * @see File::EOF()
	 */
	bool IsEOF()
	{
		return get_ >= length_;
	}

	/**
	 * @see File::Size()
	 */
	unsigned int Size()
	{
		return length_;
	}
};

class SaveFile : public File
{

public:

	virtual ~SaveFile() { }

	/**
	 * @see File::Read()
	 */
	virtual size_t Read( char *buffer, size_t length )
	{
		return 0;
	}

	/**
	 * @see File::Write()
	 */
	virtual size_t Write( const char *buffer, size_t length )
	{
		return 0;
	}

	/**
	 * @see File::ReadLine()
	 */
	virtual std::string ReadLine()
	{
		return "";
	}

	/**
	 * @see File::Peek()
	 */
	virtual int Peek()
	{
		return 0;
	}

	/**
	 * @see File::IsOpen()
	 */
	virtual bool IsOpen()
	{
		return false;
	}

	/**
	 * @see File::IsEOF()
	 */
	virtual bool IsEOF()
	{
		return true;
	}

	/**
	 * @see File::Size()
	 */
	virtual unsigned int Size()
	{
		return 0;
	}

};

FSClient *GLOBAL_FSClient = NULL;
Mutex *GLOBSL_FSMutex = NULL;

struct FilesystemWiiUInternal
{
	FSClient *Client;
	FSCmdBlock *Cmd;

	Mutex FileSystemMutex;
};

void StateChangeCallback( FSClient *client, FSVolumeState state, void *context )
{
	LOG_WRITE( "StateChangeCallback on 0x%x: 0x%x\n", client, state );

	if( FSGetVolumeState( client ) != FS_VOLSTATE_READY )
	{
		s32 errorCode = FSGetLastErrorCodeForViewer( client );
		LOG_WRITE( "Error code: 0x%x\n", errorCode );
		DisplayError( errorCode );
	}
}

FilesystemWiiU::FilesystemWiiU() :
	internal_( new FilesystemWiiUInternal )
{
	FSInit();
	LOG_WRITE( "Filesystem initialized\n" );

	internal_->Client = reinterpret_cast< FSClient * >( MEMAllocFromDefaultHeap( sizeof( FSClient ) ) );
	if( !internal_->Client )
		OSHalt( "Error: cannot allocate filesystem client.\n" );
	internal_->Cmd = reinterpret_cast< FSCmdBlock * >( MEMAllocFromDefaultHeap( sizeof( FSCmdBlock ) ) );
	if( !internal_->Cmd )
		OSHalt( "Error: cannot allocate command queue.\n" );

	FSStateChangeParams changeParams =
	{
		.userCallback = StateChangeCallback,
		.userContext = NULL,
		.ioMsgQueue = NULL
	};

	FSSetStateChangeNotification( internal_->Client, &changeParams );

	FSAddClient( internal_->Client, FS_RET_NO_ERROR );
	LOG_WRITE( "Client added\n" );

	FSInitCmdBlock( internal_->Cmd );
	LOG_WRITE( "Command block ready\n" );

	GLOBAL_FSClient = internal_->Client;
}

FilesystemWiiU::~FilesystemWiiU()
{
	GLOBAL_FSClient = NULL;

	FSDelClient( internal_->Client, 0 );

	FSShutdown();

	MEMFreeToDefaultHeap( internal_->Client );
	MEMFreeToDefaultHeap( internal_->Cmd );

	delete internal_;
}

boost::shared_ptr<File> FilesystemWiiU::Open( const std::string &path, bool write )
{
		FSFileHandle fh;
		FSStat stat;

		std::string localPath = ( path[ 0 ] == '/' ? "/vol/content/0010" : "/vol/content/0010/" ) + path;
		LOG_WRITE( "Opening %s\n", localPath.c_str() );

		// FIXME: The mutex might not be necessary if the file system supports multithreading.
		internal_->FileSystemMutex.Lock();
		FSOpenFile( internal_->Client, internal_->Cmd, localPath.c_str(), "r", &fh, FS_RET_NO_ERROR );

		memset( &stat, 0, sizeof( FSStat ) );
		FSGetStatFile( internal_->Client, internal_->Cmd, fh, &stat, FS_RET_NO_ERROR );

		char *buffer = reinterpret_cast< char * >( MEMAllocFromDefaultHeapEx( stat.size, FS_IO_BUFFER_ALIGN ) );
		FSReadFile( internal_->Client, internal_->Cmd, buffer, stat.size, 1, fh, 0, FS_RET_NO_ERROR );
		FSCloseFile( internal_->Client, internal_->Cmd, fh, FS_RET_NO_ERROR );
		internal_->FileSystemMutex.Unlock();

		return boost::static_pointer_cast<File>( boost::make_shared<FileWiiU>( buffer, stat.size ) );
}
