#ifndef _GRAPHICSDEVICEMANAGER_H_
#define _GRAPHICSDEVICEMANAGER_H_

#include <memory>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/enable_shared_from_this.hpp>

struct GraphicsDevice;

struct GraphicsDeviceManager
{

	boost::shared_ptr<GraphicsDevice> MyGraphicsDevice;

	bool IsFullScreen;
	int PreferredBackBufferWidth;
	int PreferredBackBufferHeight;

	GraphicsDeviceManager();

	void ToggleFullScreen();

	void ApplyChanges();

};

#endif
