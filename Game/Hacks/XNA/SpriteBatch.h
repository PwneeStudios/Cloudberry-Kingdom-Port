#ifndef _SPRITEBATCH_H_
#define _SPRITEBATCH_H_

#include "Hacks/XNA/Rectangle.h"
#include "Graphics/Effect.h"

struct SpriteBatch
{



	SpriteBatch()
	{
	}

	void DrawString( const std::shared_ptr<struct SpriteFont> &font, const std::wstring &str, const Vector2 &loc, const Color &c, float rotation, const Vector2 &origin, const Vector2 &scale, SpriteEffects se, float depth )
	{
	}

	void Draw( const std::shared_ptr<struct Texture2D> &texture, const Vector2 &position, Rectangle *rect, const Color &c, float rotation, const Vector2 &origin, const Vector2 &scale, SpriteEffects se, float depth )
	{
	}

	void Begin( SpriteSortMode ssm, GfxBlendState bs, GfxSamplerState ss, GfxDepthStencilState dss, GfxRasterizerState rs, const std::shared_ptr<Effect> &effect, const Matrix &transform )
	{
	}

	void End()
	{
	}

};

#endif
