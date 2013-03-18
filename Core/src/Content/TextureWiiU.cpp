#include <Content/TextureWiiU.h>

#include <Content/File.h>
#include <Content/Filesystem.h>
#include <Content/TextureWiiUInternal.h>
#include <cafe/demo.h>
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

void InitializeIntermediateTextureHeap()
{
	const u32 heapSize = 256 * 1024 * 1024;
	void *heapBase = MEMAllocFromDefaultHeap( heapSize );
	IntermediateTextureHeap = MEMCreateExpHeapEx( heapBase, heapSize, MEM_HEAP_OPT_THREAD_SAFE );
}

void FreeIntermediateTextureHeap()
{
	void *heapBase = MEMDestroyExpHeap( IntermediateTextureHeap );
	MEMFreeToDefaultHeap( heapBase );
}

void TextureWiiU::Load()
{
	u32 len;

	std::string path = GetPath();

	std::string extension = path.substr( path.length() - 3, 3 );
	if( extension == "png" )
	{
		path[ path.length() - 3 ] = 'g';
		path[ path.length() - 2 ] = 't';
		path[ path.length() - 1 ] = 'x';
	}

	boost::shared_ptr<File> file = FILESYSTEM.Open( path );

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
		setLoaded( false );
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
