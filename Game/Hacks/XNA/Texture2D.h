#ifndef _TEXTURE2D_H_
#define _TEXTURE2D_H_

#include <memory>
#include <vector>

struct GraphicsDevice;

struct Texture2D
{

	int Width;

	int Height;

	Texture2D( const std::shared_ptr<GraphicsDevice> &device, int width, int height );

	// FIXME: Implement this.
	void Dispose();

	bool IsDisposed();

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
