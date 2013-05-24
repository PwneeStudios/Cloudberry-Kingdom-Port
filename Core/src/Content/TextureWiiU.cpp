#include <Content/TextureWiiU.h>

#include <Content/File.h>
#include <Content/Filesystem.h>
#include <Content/TextureWiiUInternal.h>
#include <cafe/demo.h>
#include <cafe/fs.h>
#include <cafe/gx2.h>
#include <cafe/mem.h>
#include <Utility/Log.h>


TextureWiiU::TextureWiiU() :
	internal_( new TextureInternal )
{
}

TextureWiiU::~TextureWiiU()
{
	delete internal_;
}

static MEMHeapHandle IntermediateTextureHeap;

// Global filesystem interface from FilesystemWiiU.cpp.
extern FSClient *GLOBAL_FSClient;

// Command block for texture subsystem.
static FSCmdBlock *CommandBlock = NULL;

static bool HeapAvailable = false;

void InitializeIntermediateTextureHeap()
{
	LOG_WRITE( "Initialize intermediate texture heap\n" );
	const u32 heapSize = 128 * 1024 * 1024;
	void *heapBase = MEMAllocFromDefaultHeap( heapSize );
	IntermediateTextureHeap = MEMCreateExpHeapEx( heapBase, heapSize, MEM_HEAP_OPT_THREAD_SAFE );

	CommandBlock = reinterpret_cast< FSCmdBlock * >( MEMAllocFromDefaultHeap( sizeof( FSCmdBlock ) ) );
	FSInitCmdBlock( CommandBlock );

	HeapAvailable = true;
	OSMemoryBarrier();
}

void FreeIntermediateTextureHeap()
{
	LOG_WRITE( "Free intermediate texture heap\n" );
	HeapAvailable = false;
	OSMemoryBarrier();

	MEMFreeToDefaultHeap( CommandBlock );

	void *heapBase = MEMDestroyExpHeap( IntermediateTextureHeap );
	MEMFreeToDefaultHeap( heapBase );
}

void TextureWiiU::Load()
{
	FSCmdBlock CommandBlock;
	FSInitCmdBlock( &CommandBlock );

	u32 len;

	std::string path = GetPath();

	std::string extension = path.substr( path.length() - 3, 3 );
	if( extension == "png" )
	{
		path[ path.length() - 3 ] = 'g';
		path[ path.length() - 2 ] = 't';
		path[ path.length() - 1 ] = 'x';
	}

	std::string localPath = ( path[ 0 ] == '/' ? "/vol/content/0010" : "/vol/content/0010/" ) + path;
		
	if( HeapAvailable )
	{
		FSFileHandle fh;
		FSStat stat;

		LOG_WRITE( "Loading texture %s\n", localPath.c_str() );

		FSOpenFile( GLOBAL_FSClient, &CommandBlock, localPath.c_str(), "r", &fh, FS_RET_NO_ERROR );

		LOG_WRITE( "Intermeidate step after open\n" );

		memset( &stat, 0, sizeof( FSStat ) );
		FSGetStatFile( GLOBAL_FSClient, &CommandBlock, fh, &stat, FS_RET_NO_ERROR );

		LOG_WRITE( "Intermediate step after stat\n" );

		internal_->Buffer = NULL;
		while( internal_->Buffer == NULL )
		{
			internal_->Buffer = reinterpret_cast< char * >( MEMAllocFromExpHeapEx( IntermediateTextureHeap, stat.size, FS_IO_BUFFER_ALIGN ) );
			if( internal_->Buffer )
				break;

			OSYieldThread();
		}
		
		LOG_WRITE( "Intermeidate step, buffer = %x\n", internal_->Buffer );

		FSReadFile( GLOBAL_FSClient, &CommandBlock, internal_->Buffer, stat.size, 1, fh, 0, FS_RET_NO_ERROR );

		LOG_WRITE( "Intermediate step, before close\n" );
		FSCloseFile( GLOBAL_FSClient, &CommandBlock, fh, FS_RET_NO_ERROR );

		setLoaded( true );
	}
	else
	{
		LOG_WRITE( "HEAP NOT AVAILABLE FOR: %s\n", localPath.c_str() );

		setLoaded( false );
	}
	/*boost::shared_ptr<File> file = FILESYSTEM.Open( path );

	if( file->IsOpen() )
	{
		internal_->Buffer = NULL;
		while( internal_->Buffer == NULL )
		{
			internal_->Buffer = reinterpret_cast< char * >( MEMAllocFromExpHeap( IntermediateTextureHeap, file->Size() ) );
			if( internal_->Buffer )
				break;

			OSYieldThread();
		}

		file->Read( internal_->Buffer, file->Size() );

		setLoaded( true );
	}
	else
		setLoaded( false );*/
}

void TextureWiiU::Unload()
{
}

void TextureWiiU::GpuCreate()
{
	BOOL ok;
	
	ok = DEMOGFDReadTexture( &internal_->Texture, 0, internal_->Buffer );

	MEMFreeToExpHeap( IntermediateTextureHeap, internal_->Buffer );
	internal_->Buffer = NULL;

	if( ok )
		setLoaded( true );
}

void TextureWiiU::GpuDestroy()
{
	DEMOGFDFreeTexture( internal_->Texture );
}

void TextureWiiU::Activate( unsigned int sampler )
{
	GX2SetPixelTexture( internal_->Texture, sampler );
}
