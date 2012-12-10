#ifndef _GRAPHICSDEVICE_H_
#define _GRAPHICSDEVICE_H_

#include "Hacks/Queue.h"

#include "Hacks/XNA/Viewport.h"

struct GraphicsDevice
{



	std::shared_ptr<struct PresentationParameters> PP;
	std::vector<std::shared_ptr<struct SamplerState> > SamplerStates;
	GfxRasterizerState RasterizerState;
	GfxBlendState BlendState;
	GfxDepthStencilState DepthStencilState;

	Viewport VP;

	GraphicsDevice()
	{
		SamplerStates.resize( 3 );
	}

	void SetRenderTarget( const std::shared_ptr<struct RenderTarget2D> &rt )
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
