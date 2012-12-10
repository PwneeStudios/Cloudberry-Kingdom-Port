#ifndef _GRAPHICSDEVICEMANAGER_H_
#define _GRAPHICSDEVICEMANAGER_H_

class GraphicsDeviceManager
{

public:

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
