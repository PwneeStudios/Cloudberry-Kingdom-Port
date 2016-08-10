#include <Graphics/RenderTarget2D.h>

#include <Content/Texture.h>

#include <Content/TextureVitaInternal.h>

#include <gxt.h>

extern void *graphicsAlloc(SceKernelMemBlockType type, uint32_t size, uint32_t alignment, uint32_t attribs, SceUID *uid);
extern void graphicsFree(SceUID uid);

struct RenderTarget2DInternal
{
	int Width;
	int Height;

	Texture *RTTexture;
	ResourceHolder Holder;
};

RenderTarget2D::RenderTarget2D( const boost::shared_ptr<GraphicsDevice> &device, int width, int height, bool mipmap, int surfaceFormat, int depthFormat, int sampleCount, bool discard )
	: Texture2D( device, width, height )
	, internal_( new RenderTarget2DInternal )
{
	memset( internal_, 0, sizeof( RenderTarget2DInternal ) );

	internal_->Width = width;
	internal_->Height = height;

	internal_->RTTexture = new Texture();

	TextureVitaInternal *texInt = internal_->RTTexture->impl_.internal_;

	//texInt->TextureData = graphicsAlloc(
	//	SCE_KERNEL_MEMBLOCK_TYPE_USER_CDRAM_RWDATA,

	// ...

	internal_->Holder = internal_->RTTexture;
	texture_ = ResourcePtr< Texture >( &internal_->Holder );
}

RenderTarget2D::~RenderTarget2D()
{
	delete internal_;
}

void RenderTarget2D::Set()
{
}

// Screen width and height from CorePS3.cpp.
extern int GLOBAL_WIDTH;
extern int GLOBAL_HEIGHT;

void RenderTarget2D::SetDefault()
{
}

void RenderTarget2D::Clear( float r, float g, float b, float a )
{
}