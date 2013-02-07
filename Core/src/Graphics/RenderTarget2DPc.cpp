#include <Graphics/RenderTarget2D.h>

RenderTarget2D::RenderTarget2D( const boost::shared_ptr<GraphicsDevice> &device, int width, int height, bool mipmap, int surfaceFormat, int depthFormat, int sampleCount, bool discard )
	: Texture2D( device, width, height )
{
}

RenderTarget2D::~RenderTarget2D()
{
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