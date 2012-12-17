#include "Texture2D.h"

Texture2D::Texture2D( const boost::shared_ptr<GraphicsDevice> &device, int width, int height ) :
	Width( width ), Height( height )
{
}

// FIXME: Implement this.
void Texture2D::Dispose() { }

bool Texture2D::IsDisposed()
{
	return false;
}