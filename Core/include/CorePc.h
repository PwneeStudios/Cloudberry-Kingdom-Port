#ifndef _CORE_PC_H_
#define _CORE_PC_H_

#include "ForwardDeclarations.h"

/**
 * PC Core.
 */
class CorePc
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
	CorePc( const CorePc & );

	/// No assignment.
	CorePc &operator = ( const CorePc & );

public:

	CorePc( GameLoop &game );
	~CorePc();

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
