#include "GraphicsDevice.h"
#include "GraphicsDeviceManager.h"
#include "PresentationParameters.h"

GraphicsDeviceManager::GraphicsDeviceManager()
{
	MyGraphicsDevice = std::make_shared<GraphicsDevice>();

	IsFullScreen = false;
	
	MyGraphicsDevice->PP->BackBufferWidth = PreferredBackBufferWidth = 1280;
	MyGraphicsDevice->PP->BackBufferHeight = PreferredBackBufferHeight = 720;
}

void GraphicsDeviceManager::ToggleFullScreen()
{
}

void GraphicsDeviceManager::ApplyChanges()
{
	// After settings have been changed, this function propogates the changes to the device.
}
