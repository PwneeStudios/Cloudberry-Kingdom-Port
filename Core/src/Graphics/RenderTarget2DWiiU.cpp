#include <Graphics/RenderTarget2D.h>

#include <cafe/demo.h>
#include <cafe/gx2.h>
#include <Content/Texture.h>
#include <Content/TextureWiiUInternal.h>

#include "RenderTarget2DWiiUInternal.h"

std::vector< RenderTarget2DInternal * > GlobalRenderTargets;

RenderTarget2D::RenderTarget2D( const boost::shared_ptr<GraphicsDevice> &device, int width, int height, bool mipmap, int surfaceFormat, int depthFormat, int sampleCount, bool discard )
	: Texture2D( device, width, height )
	, internal_( new RenderTarget2DInternal )
{
	memset( internal_, 0, sizeof( internal_ ) );
	GX2InitColorBuffer( &internal_->ColorBuffer,
		width, height, GX2_SURFACE_FORMAT_TCS_R8_G8_B8_A8_UNORM,
		GX2_AA_MODE_1X );
	GX2InitColorBufferPtr( &internal_->ColorBuffer,
		DEMOGfxAllocMEM1( internal_->ColorBuffer.surface.imageSize,
			internal_->ColorBuffer.surface.alignment ) );
	GX2Invalidate( GX2_INVALIDATE_CPU, internal_->ColorBuffer.surface.imagePtr,
		internal_->ColorBuffer.surface.imageSize );

	internal_->RTTexture = new Texture();

	// FIXME: MASSIVE ABSTRACTION VIOLATION (WILL NEVER BE FIXED!).
	internal_->RTTexture->impl_.internal_->Texture = 
		reinterpret_cast< GX2Texture * >( DEMOAllocEx( sizeof( GX2Texture ), PPC_IO_BUFFER_ALIGN ) );
	GX2InitTexture( internal_->RTTexture->impl_.internal_->Texture,
		width, height, 1, 0, GX2_SURFACE_FORMAT_TCS_R8_G8_B8_A8_UNORM,
		GX2_SURFACE_DIM_2D );

	GX2InitTexturePtrs( internal_->RTTexture->impl_.internal_->Texture,
		internal_->ColorBuffer.surface.imagePtr, 0 );

	internal_->Holder = internal_->RTTexture;
	texture_ = ResourcePtr< Texture >( &internal_->Holder );

	GlobalRenderTargets.push_back( internal_ );
}

static RenderTarget2DInternal *LastRT = 0;

RenderTarget2D::~RenderTarget2D()
{
	std::vector< RenderTarget2DInternal * >::iterator i;
	i = std::find( GlobalRenderTargets.begin(), GlobalRenderTargets.end(), internal_ );

	if( LastRT == internal_ )
		LastRT = 0;

	DEMOGfxFreeMEM1( internal_->ColorBuffer.surface.imagePtr );
	DEMOFree( internal_->RTTexture->impl_.internal_->Texture );

	delete internal_->RTTexture;
	delete internal_;
}

void RenderTarget2D::Set()
{
	if( LastRT )
	{
		GX2Invalidate( GX2_INVALIDATE_COLOR_BUFFER,
			LastRT->ColorBuffer.surface.imagePtr,
			LastRT->ColorBuffer.surface.imageSize );
		GX2Invalidate( GX2_INVALIDATE_TEXTURE,
			LastRT->RTTexture->impl_.internal_->Texture->surface.imagePtr,
			LastRT->RTTexture->impl_.internal_->Texture->surface.imageSize );
		LastRT = 0;
	}

	GX2SetColorBuffer( &internal_->ColorBuffer, GX2_RENDER_TARGET_0 );
	GX2SetViewport( 0.f, 0.f,
		static_cast< float >( Width ), static_cast< float >( Height ),
		0.f, 1.f );
	GX2SetScissor( 0, 0, Width, Height );

	GX2SetBlendControl( GX2_RENDER_TARGET_0,
		GX2_BLEND_ONE, GX2_BLEND_ONE, GX2_BLEND_COMBINE_ADD,
		GX2_TRUE, GX2_BLEND_ONE, GX2_BLEND_ONE_MINUS_SRC_ALPHA, GX2_BLEND_COMBINE_ADD );

	LastRT = internal_;
}

extern GX2ColorBuffer TheColorBuffer;

void RenderTarget2D::SetDefault()
{
	if( LastRT )
	{
		GX2Invalidate( GX2_INVALIDATE_COLOR_BUFFER,
			LastRT->ColorBuffer.surface.imagePtr,
			LastRT->ColorBuffer.surface.imageSize );
		GX2Invalidate( GX2_INVALIDATE_TEXTURE,
			LastRT->RTTexture->impl_.internal_->Texture->surface.imagePtr,
			LastRT->RTTexture->impl_.internal_->Texture->surface.imageSize );
		LastRT = 0;
	}

	int width = TheColorBuffer.surface.width;
	int height = TheColorBuffer.surface.height;

	GX2SetColorBuffer( &TheColorBuffer, GX2_RENDER_TARGET_0 );
	GX2SetDepthBuffer( &DEMODepthBuffer );
	GX2SetViewport( 0.f, 0.f,
		static_cast< float >( width ), static_cast< float >( height ),
		0.f, 1.f );
	GX2SetScissor( 0, 0, width, height );

	GX2SetDepthOnlyControl( GX2_FALSE, GX2_FALSE, GX2_COMPARE_ALWAYS );
			GX2SetColorControl( GX2_LOGIC_OP_COPY, 0x1, GX2_DISABLE, GX2_ENABLE );
	GX2SetBlendControl( GX2_RENDER_TARGET_0,
		GX2_BLEND_ONE, GX2_BLEND_ONE_MINUS_SRC_ALPHA, GX2_BLEND_COMBINE_ADD,
		GX2_TRUE, GX2_BLEND_ONE, GX2_BLEND_ONE_MINUS_SRC_ALPHA, GX2_BLEND_COMBINE_ADD );

	DEMOGfxSetContextState();
}

void RenderTarget2D::Clear( float r, float g, float b, float a )
{
	GX2ClearColor( &internal_->ColorBuffer, r, g, b, a );
	GX2ClearDepthStencil( &DEMODepthBuffer, GX2_CLEAR_BOTH );

	DEMOGfxSetContextState();
}