#ifndef _SPRITEBATCH_H_
#define _SPRITEBATCH_H_

#include <enums.h>

#include <Graphics/Effect.h>
#include <Graphics/Color.h>
#include <Hacks/XNA/Rectangle.h>
#include <Math/Vectors.h>
#include <memory>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <string>

struct SpriteBatch
{

	struct SpriteBatchInternal *internal_;

	SpriteBatch();
	~SpriteBatch();

	void DrawString( const boost::shared_ptr<struct SpriteFont> &font, const std::wstring &str, const Vector2 &loc, const Color &c, float rotation, const Vector2 &origin, const Vector2 &scale, SpriteEffects se, float depth );
	void Draw( const boost::shared_ptr<struct Texture2D> &texture, const Vector2 &position, Rectangle *rect, const Color &c, float rotation, const Vector2 &origin, const Vector2 &scale, SpriteEffects se, float depth );
	void Begin( SpriteSortMode ssm, GfxBlendState bs, GfxSamplerState ss, GfxDepthStencilState dss, GfxRasterizerState rs, const boost::shared_ptr<Effect> &effect, const Matrix &transform );
	void End();

};

#endif
