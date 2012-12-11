#ifndef _GRAPHICSDEVICEMANAGER_H_
#define _GRAPHICSDEVICEMANAGER_H_

#include <memory>

struct GraphicsDevice;

struct GraphicsDeviceManager
{

	std::shared_ptr<GraphicsDevice> MyGraphicsDevice;

	bool IsFullScreen;
	int PreferredBackBufferWidth;
	int PreferredBackBufferHeight;

	GraphicsDeviceManager();

	void ToggleFullScreen();

	void ApplyChanges();

};

#endif
