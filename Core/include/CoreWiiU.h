#ifndef _CORE_WIIU_H_
#define _CORE_WIIU_H_

#include "ForwardDeclarations.h"

/**
 * WiiU Core.
 */
class CoreWiiU
{

	/// Is the game currently running?
	bool running_;

	/// The game.
	GameLoop &game_;

	// Components.

	QuadDrawer *qd_;

	Wad *content_;

	Scheduler *scheduler_;

	/// Location 
	void *mem1Storage_;

private:

	/// No copyig.
	CoreWiiU( const CoreWiiU & );

	/// No assignment.
	CoreWiiU &operator = ( const CoreWiiU & );

public:

	CoreWiiU( GameLoop &game );
	~CoreWiiU();

	/**
	 * @see Core::Run()
	 */
	int Run();

	/**
	 * @see Core::Exit()
	 */
	void Exit();

	// Accessors to components.
	
	QuadDrawer *GetQuadDrawer()
	{
		return qd_;
	}

	Wad *GetContent()
	{
		return content_;
	}

	Scheduler *GetScheduler()
	{
		return scheduler_;
	}

	TextDrawer *GetTextDrawer()
	{
		return 0;
	}

};

#endif
