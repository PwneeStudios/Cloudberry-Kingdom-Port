#ifndef _GRAPHICSDEVICE_H_
#define _GRAPHICSDEVICE_H_

#include <memory>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <vector>

#include <enums.h>

#include <Core/Graphics/VertexFormat.h>

#include "Viewport.h"

struct PresentationParameters;
struct SamplerState;
struct RenderTarget2D;

struct GraphicsDevice
{

	boost::shared_ptr<PresentationParameters> PP;
	std::vector<boost::shared_ptr<SamplerState> > SamplerStates;
	GfxRasterizerState RasterizerState;
	GfxBlendState BlendState;
	GfxDepthStencilState DepthStencilState;

	Viewport VP;

	GraphicsDevice();

	void SetRenderTarget( const boost::shared_ptr<RenderTarget2D> &rt );

	void Clear( const Color &color);

	////template<class T>
	////void DrawUserPrimitives( GfxPrimitiveType type, const std::vector<T> &vertices, int base, int count);

	void DrawUserPrimitives( GfxPrimitiveType type, const std::vector<CloudberryKingdom::MyOwnVertexFormat> &vertices, int base, int count);

};

#endif
