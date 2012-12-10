#ifndef _TEXTURE2D_H_
#define _TEXTURE2D_H_

#include "Hacks/XNA/GraphicsDevice.h"

class Texture2D
{
public:

	int Width;

	int Height;

	Texture2D( const std::shared_ptr<GraphicsDevice> &device, int width, int height )
	{
	}

	// FIXME: Implement this.
	void Dispose() { }

	bool IsDisposed()
	{
		return false;
	}

	template<class T>
	void GetData( std::vector<T> &data )
	{
	}

	template<class T>
	void SetData( std::vector<T> &data )
	{
	}

};

#endif
