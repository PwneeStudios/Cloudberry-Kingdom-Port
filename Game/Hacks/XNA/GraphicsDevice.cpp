#include "GraphicsDevice.h"
#include "PresentationParameters.h"

GraphicsDevice::GraphicsDevice()
{
	SamplerStates.resize( 3 );

	PP = std::make_shared<PresentationParameters>();

}

void GraphicsDevice::SetRenderTarget( const std::shared_ptr<RenderTarget2D> &rt )
{
}

void GraphicsDevice::Clear( const Color &color)
{
}

void GraphicsDevice::DrawUserPrimitives( GfxPrimitiveType type, const std::vector<CloudberryKingdom::MyOwnVertexFormat> &vertices, int base, int count)
{
}
