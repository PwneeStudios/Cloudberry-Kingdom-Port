#ifndef _CORE_PS3_H_
#define _CORE_PS3_H_

#include "ForwardDeclarations.h"

/**
 * PC Core.
 */
class CorePS3
{

	/// Is the game currently running?
	bool running_;

	/// The game.
	GameLoop &game_;

	// Components.

	QuadDrawer *qd_;

	Wad *content_;

	Scheduler *scheduler_;

	TextDrawer *td_;

private:

	/// No copying.
	CorePS3( const CorePS3 & );

	/// No assignment.
	CorePS3 &operator = ( const CorePS3 & );

public:

	CorePS3( GameLoop &game );
	~CorePS3();

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
		return td_;
	}

};

#endif
