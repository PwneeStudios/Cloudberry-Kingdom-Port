#include <CoreWiiU.h>

#include <Architecture/Scheduler.h>
#include <cafe/demo.h>
#include <cafe/gx2.h>
#include <cafe/procui.h>
#include <Content/Wad.h>
#include <cstdlib>
#include <GameLoop.h>
#include <Graphics/QuadDrawer.h>

// Private.
CoreWiiU::CoreWiiU( const CoreWiiU &other ) :
	game_( other.game_ ),
	qd_( other.qd_ )
{

}

// Private.
CoreWiiU &CoreWiiU::operator = ( const CoreWiiU &rhs )
{
	return *this;
}

CoreWiiU::CoreWiiU( GameLoop &game ) :
	running_( false ),
	game_( game ),
	qd_( 0 ),
	content_( 0 ),
	scheduler_( 0 )
{
	GX2DebugCaptureInit( NULL );

	DEMOInit();
	DEMOTestInit( 0, NULL );
	DEMOGfxInit( 0, NULL );

	// Allocate space for MEM1 for process switching.
	u32 mem1Size;
	OSGetMemBound( OSMem_MEM1, ( u32 * )&mem1Storage_, &mem1Size );
	mem1Storage_ = MEMAllocFromDefaultHeap( mem1Size );
	ProcUISetMEM1Storage( mem1Storage_, mem1Size );

	scheduler_ = new Scheduler;

	qd_ = new QuadDrawer;

	content_ = new Wad( "./" );
}

CoreWiiU::~CoreWiiU()
{
	delete qd_;

	delete content_;

	delete scheduler_;

	// Free MEM1 backup.
	ProcUISetMEM1Storage( NULL, 0 );
	MEMFreeToDefaultHeap( mem1Storage_ );

	DEMOGfxShutdown();
	DEMOTestShutdown();
	DEMOShutdown();
}

int CoreWiiU::Run()
{
	running_ = true;
	
	game_.Initialize();

	//while( running_ && DEMOIsRunning() )
	{
		DEMOGfxBeforeRender();
		GX2ClearColor( &DEMOColorBuffer, 0, 0, 0, 1 );
		GX2ClearDepthStencil( &DEMODepthBuffer, GX2_CLEAR_BOTH );

		DEMOGfxSetContextState();

		game_.Update();

		qd_->Flush();

		DEMOGfxDoneRender();
	}

	return 0;
}

void CoreWiiU::Exit()
{
	running_ = false;
}
