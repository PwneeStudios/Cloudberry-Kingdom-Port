#ifndef _CORE_VITA_H_
#define _CORE_VITA_H_

#include "ForwardDeclarations.h"

/**
 * Vita Core.
 */
class CoreVita
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
	CoreVita( const CoreVita & );

	/// No assignment.
	CoreVita &operator = ( const CoreVita & );

public:

	CoreVita( GameLoop &game );
	~CoreVita();

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
