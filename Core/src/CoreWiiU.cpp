#include <CoreWiiU.h>

#include <Architecture/Scheduler.h>
#include <cafe/demo.h>
#include <cafe/gx2.h>
#include <cafe/procui.h>
#include <Content/Wad.h>
#include <cstdlib>
#include <GameLoop.h>
#include <Graphics/QuadDrawer.h>
#include <Graphics/TextDrawer.h>
#include <Utility/Log.h>

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
	DEMODRCInit( 0, NULL );

	// Allocate space for MEM1 for process switching.
	u32 mem1Size;
	OSGetMemBound( OSMem_MEM1, ( u32 * )&mem1Storage_, &mem1Size );
	mem1Storage_ = MEMAllocFromDefaultHeap( mem1Size );
	ProcUISetMEM1Storage( mem1Storage_, mem1Size );

	scheduler_ = new Scheduler;

	qd_ = new QuadDrawer;

	content_ = new Wad( "" );

	td_ = new TextDrawer;
}

CoreWiiU::~CoreWiiU()
{
	LOG.Write( "SHUTDOWN START\n" );
	delete td_;

	delete qd_;

	delete content_;

	delete scheduler_;

	// Free MEM1 backup.
	ProcUISetMEM1Storage( NULL, 0 );
	MEMFreeToDefaultHeap( mem1Storage_ );

	DEMODRCShutdown();
	DEMOGfxShutdown();
	DEMOTestShutdown();
	DEMOShutdown();
	LOG.Write( "SHUTDOWN END\n" );
}

int CoreWiiU::Run()
{
	running_ = true;
	
	game_.Initialize();

	while( DEMOIsRunning() )
	{
		game_.Update();

		if( DEMODRCGetStatus() != GX2_DRC_NONE )
		{
			DEMODRCBeforeRender();

			GX2SetContextState( DEMODRCContextState );

			qd_->Flush();

			GX2SetContextState( DEMODRCContextState );

			DEMODRCDoneRender();
		}

		DEMOGfxBeforeRender();
		GX2ClearColor( &DEMOColorBuffer, 0, 0, 0, 0 );
		GX2ClearDepthStencil( &DEMODepthBuffer, GX2_CLEAR_BOTH );

		DEMOGfxSetContextState();

		qd_->Flush();

		DEMOGfxDoneRender();

		// Close down.
		if( !running_ )
		{
			DEMOStopRunning();
			dynamic_cast< QuadDrawerWiiU * >( qd_ )->Unlock();
		}
	}

	return 0;
}

void CoreWiiU::Exit()
{
	running_ = false;
}
