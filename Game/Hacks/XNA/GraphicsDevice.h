#ifndef _GRAPHICSDEVICE_H_
#define _GRAPHICSDEVICE_H_

#include "Hacks/Queue.h"

#include "Hacks/XNA/Viewport.h"

class GraphicsDevice
{

public:

	std::shared_ptr<class PresentationParameters> PP;
	std::vector<std::shared_ptr<class SamplerState> > SamplerStates;
	GfxRasterizerState RasterizerState;
	GfxBlendState BlendState;
	GfxDepthStencilState DepthStencilState;

	Viewport VP;

	GraphicsDevice()
	{
		SamplerStates.resize( 3 );
	}

	void SetRenderTarget( const std::shared_ptr<class RenderTarget2D> &rt )
	{
	}

	void Clear( const Color &color)
	{
	}

	template<class T>
	void DrawUserPrimitives( GfxPrimitiveType type, const std::vector<T> &vertices, int base, int count)
	{
	}

};

#endif
