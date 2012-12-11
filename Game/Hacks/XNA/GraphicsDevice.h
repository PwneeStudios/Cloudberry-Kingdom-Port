#ifndef _GRAPHICSDEVICE_H_
#define _GRAPHICSDEVICE_H_

#include <memory>
#include <vector>

#include <enums.h>

#include <Core/Graphics/VertexFormat.h>

#include "Viewport.h"

struct PresentationParameters;
struct SamplerState;
struct RenderTarget2D;

struct GraphicsDevice
{

	std::shared_ptr<PresentationParameters> PP;
	std::vector<std::shared_ptr<SamplerState> > SamplerStates;
	GfxRasterizerState RasterizerState;
	GfxBlendState BlendState;
	GfxDepthStencilState DepthStencilState;

	Viewport VP;

	GraphicsDevice();

	void SetRenderTarget( const std::shared_ptr<RenderTarget2D> &rt );

	void Clear( const Color &color);

	////template<class T>
	////void DrawUserPrimitives( GfxPrimitiveType type, const std::vector<T> &vertices, int base, int count);

	void DrawUserPrimitives( GfxPrimitiveType type, const std::vector<CloudberryKingdom::MyOwnVertexFormat> &vertices, int base, int count);

};

#endif
