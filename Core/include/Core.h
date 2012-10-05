#ifndef _CORE_H_
#define _CORE_H_

#include "Architecture/Singleton.h"
#include "ForwardDeclarations.h"

// Pick implementation.
#ifdef CAFE
	#include "CoreWiiU.h"
#else
	#include "CorePc.h"
#endif

/**
 * The alpha and the omega.
 */
class Core : public Singleton< Core >
{

	/// Core implementation.
#ifdef CAFE
	CoreWiiU impl_;
#else
	CorePc impl_;
#endif

	/// Reference to game for later use.
	GameLoop &game_;

private:

	/// No copying.
	Core( const Core & );

	/// No assignment.
	Core &operator = ( const Core & );

public:

	Core( GameLoop &game );
	~Core();

	/// Run application.
	/**
	 * @return 0 on success and 1 on failure.
	 */
	int Run()
	{
		return impl_.Run();
	}

	/// Exit application.
	void Exit()
	{
		impl_.Exit();
	}

	// Accessors to components.
	
	QuadDrawer *GetQuadDrawer()
	{
		return impl_.GetQuadDrawer();
	}

	Wad *GetContent()
	{
		return impl_.GetContent();
	}

	Scheduler *GetScheduler()
	{
		return impl_.GetScheduler();
	}

	/// Get core singleton.
	static Core &GetSingleton();

};

/// The core! 
#define CORE Core::GetSingleton()

/// Drawer of quads.
#define QUAD_DRAWER CORE.GetQuadDrawer()

/// Assets.
#define CONTENT CORE.GetContent()

/// Job scheduler.
#define SCHEDULER CORE.GetScheduler()

#endif
