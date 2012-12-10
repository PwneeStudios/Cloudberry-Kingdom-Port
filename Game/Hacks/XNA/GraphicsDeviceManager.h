#ifndef _GRAPHICSDEVICEMANAGER_H_
#define _GRAPHICSDEVICEMANAGER_H_

struct GraphicsDeviceManager
{



	std::shared_ptr<GraphicsDevice> MyGraphicsDevice;

	bool IsFullScreen;
	int PreferredBackBufferWidth;
	int PreferredBackBufferHeight;

	void ToggleFullScreen()
	{
	}

	void ApplyChanges()
	{
		// After settings have been changed, this function propogates the changes to the device.
	}
};

#endif
