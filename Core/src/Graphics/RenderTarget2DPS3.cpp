#include <Graphics/RenderTarget2D.h>

#include <Content/Texture.h>
#include <PSGL/psgl.h>
#include <PSGL/psglu.h>

#include "../Content/PS3/psglGtfLoader.h"
#include <Content/TexturePS3Internal.h>

struct RenderTarget2DInternal
{
	//GLuint Rid;
	GLuint Fid;
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

	// FIXME: MASSIVE ABSTRACTION VIOLATION (WILL NEVER BE FIXED!).
	GLuint texture;
	glGenTextures( 1, &texture );
	internal_->RTTexture->impl_.internal_->Ref.textureID = texture;

	glBindTexture( GL_TEXTURE_2D, texture );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_ALLOCATION_HINT_SCE, GL_TEXTURE_TILED_GPU_SCE );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexImage2D( GL_TEXTURE_2D, 0, GL_ARGB_SCE, width, height, 0,
		GL_BGRA, GL_UNSIGNED_INT_8_8_8_8_REV, NULL );
	
	/*glGenRenderbuffersOES( 1, &internal_->Rid );
	glBindRenderbufferOES( GL_RENDERBUFFER_OES, internal_->Rid );
	glRenderbufferStorageOES( GL_RENDERBUFFER_OES, GL_DEPTH_COMPONENT, width, height );*/

	glGenFramebuffersOES( 1, &internal_->Fid );
	glBindFramebufferOES( GL_FRAMEBUFFER_OES, internal_->Fid );

	glFramebufferTexture2DOES( GL_FRAMEBUFFER_OES, GL_COLOR_ATTACHMENT0_EXT,
		GL_TEXTURE_2D, texture, 0 );
	/*glFramebufferRenderbufferOES( GL_FRAMEBUFFER_OES, GL_DEPTH_ATTACHMENT_OES,
		GL_RENDERBUFFER_OES, internal_->Rid );*/

	glBindFramebufferOES( GL_FRAMEBUFFER_OES, 0 );

	internal_->Holder = internal_->RTTexture;
	texture_ = ResourcePtr< Texture >( &internal_->Holder );
}

RenderTarget2D::~RenderTarget2D()
{
	//glDeleteRenderbuffersOES( 1, &internal_->Rid );
	glDeleteTextures( 1, &internal_->RTTexture->impl_.internal_->Ref.textureID );
	glDeleteFramebuffersOES( 1, &internal_->Fid );

	delete internal_;
}

void RenderTarget2D::Set()
{
	glBindFramebufferOES( GL_FRAMEBUFFER_OES, internal_->Fid );

	glViewport( 0, 0, internal_->Width, internal_->Height );
	glScissor( 0, 0, internal_->Width, internal_->Height );

	glBlendFuncSeparate( GL_ONE, GL_ONE, GL_ONE, GL_ONE_MINUS_SRC_ALPHA );
	
}

void RenderTarget2D::SetDefault()
{
	glBindFramebufferOES( GL_FRAMEBUFFER_OES, 0 );

	// FIXME: Hardcoded sizes.
	glViewport( 0, 0, 1280, 1080 );
	glScissor( 0, 0, 1280, 1080 );

	glClearColor( 0.f, 0.f, 0.f, 1.f );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	glBlendFunc( GL_ONE, GL_ONE_MINUS_SRC_ALPHA );
}

void RenderTarget2D::Clear( float r, float g, float b, float a )
{
	glClearColor( r, g, b, a );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}