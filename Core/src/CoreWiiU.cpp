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
#include <Input/GamePad.h>
#include <Utility/Limits.h>
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

	GamePad::Initialize();
}

CoreWiiU::~CoreWiiU()
{
	LOG.Write( "SHUTDOWN START\n" );
	
	GamePad::Shutdown();

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
		GamePad::Update();

		/*if( DEMODRCGetStatus() != GX2_DRC_NONE )
		{
			DEMODRCBeforeRender();
			//GX2ClearColor( &DEMODRCColorBuffer, 0, 0, 0, 0 );
			//GX2ClearDepthStencil( &DEMODRCDepthBuffer, GX2_CLEAR_BOTH );

			GX2SetContextState( DEMODRCContextState );

			qd_->Flush();

			GX2SetContextState( DEMODRCContextState );

			DEMODRCDoneRender();
		}*/

		DEMOGfxBeforeRender();
		GX2ClearColor( &DEMOColorBuffer, 0, 0, 0, 0 );
		GX2ClearDepthStencil( &DEMODepthBuffer, GX2_CLEAR_BOTH );

		DEMOGfxSetContextState();

		GX2SetDepthOnlyControl( GX2_FALSE, GX2_FALSE, GX2_COMPARE_ALWAYS );
		GX2SetColorControl( GX2_LOGIC_OP_COPY, 0x1, GX2_DISABLE, GX2_ENABLE );

		game_.Update();

		DEMOGfxSetContextState();

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
