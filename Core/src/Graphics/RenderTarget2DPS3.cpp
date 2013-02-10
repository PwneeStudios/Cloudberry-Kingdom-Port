#include <Graphics/RenderTarget2D.h>

#include <Content/Texture.h>
#include <PSGL/psgl.h>
#include <PSGL/psglu.h>

#include "../Content/PS3/psglGtfLoader.h"
#include <Content/TexturePS3Internal.h>

struct RenderTarget2DInternal
{
	GLuint Rid;
};

RenderTarget2D::RenderTarget2D( const boost::shared_ptr<GraphicsDevice> &device, int width, int height, bool mipmap, int surfaceFormat, int depthFormat, int sampleCount, bool discard )
	: Texture2D( device, width, height )
	, internal_( new RenderTarget2DInternal )
{
	memset( internal_, 0, sizeof( RenderTarget2DInternal ) );

	glGenRenderbuffersOES( 1, &internal_->Rid );
	glBindRenderbufferOES( GL_RENDERBUFFER_OES, internal_->Rid );
	glRenderbufferStorageOES( GL_RENDERBUFFER_OES, GL_DEPTH_COMPONENT, width, height );
}

RenderTarget2D::~RenderTarget2D()
{
	glDeleteRenderbuffersOES( 1, &internal_->Rid );

	delete internal_;
}

void RenderTarget2D::Set()
{
}

void RenderTarget2D::SetDefault()
{
}

void RenderTarget2D::Clear( float r, float g, float b, float a )
{
}