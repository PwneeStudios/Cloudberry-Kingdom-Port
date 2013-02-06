#ifndef _TEXTURE2D_H_
#define _TEXTURE2D_H_

#include <memory>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <vector>

#include <Content/ResourcePtr.h>

struct GraphicsDevice;

struct Texture2D
{

	ResourcePtr<Texture> texture_;

	int Width;

	int Height;

	Texture2D( const boost::shared_ptr<GraphicsDevice> &device, int width, int height );
	virtual ~Texture2D() { }

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
