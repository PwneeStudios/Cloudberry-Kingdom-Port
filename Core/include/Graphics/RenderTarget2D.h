#ifndef _RENDERTARGET2D_H_
#define _RENDERTARGET2D_H_

#include <Graphics/Texture2D.h>

struct GraphicsDevice;

struct RenderTarget2D : public Texture2D
{

	struct RenderTarget2DInternal *internal_;

	RenderTarget2D( const boost::shared_ptr<GraphicsDevice> &device, int width, int height, bool mipmap, int surfaceFormat, int depthFormat, int sampleCount, bool discard );
	~RenderTarget2D();

	void Set();
	static void SetDefault();
	void Clear( float r, float g, float b, float a );

};

#endif
