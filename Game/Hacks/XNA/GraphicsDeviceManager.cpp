#include "GraphicsDevice.h"
#include "GraphicsDeviceManager.h"
#include "PresentationParameters.h"

GraphicsDeviceManager::GraphicsDeviceManager() :
	IsFullScreen( false ),
	PreferredBackBufferWidth( 1280 ),
	PreferredBackBufferHeight( 720 )
{
	MyGraphicsDevice = std::make_shared<GraphicsDevice>();
	
	MyGraphicsDevice->PP->BackBufferWidth = PreferredBackBufferWidth;
	MyGraphicsDevice->PP->BackBufferHeight = PreferredBackBufferHeight;
}

void GraphicsDeviceManager::ToggleFullScreen()
{
}

void GraphicsDeviceManager::ApplyChanges()
{
	// After settings have been changed, this function propogates the changes to the device.
}
