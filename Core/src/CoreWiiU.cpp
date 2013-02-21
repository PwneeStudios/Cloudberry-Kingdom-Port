#include <CoreWiiU.h>

#include <Architecture/Scheduler.h>
#include <Audio/MediaPlayer.h>
#include <cafe/demo.h>
#include <cafe/gx2.h>
#include <cafe/procui.h>
#include <cafe/sci/sciEnum.h>
#include <cafe/sci/sciPublicApi.h>
#include <Content/Wad.h>
#include <cstdlib>
#include <GameLoop.h>
#include <Graphics/QuadDrawer.h>
#include <Graphics/TextDrawer.h>
#include <Input/GamePad.h>
#include <nn/act.h>
#include <nn/save.h>
#include <nn/erreula.h>
#include <Utility/Limits.h>
#include <Utility/Log.h>

#include <fmod.hpp>

// FIXME: This is done in order to get access to update the FMOD system every frame.
// This should really be done through a method like MediaPlayer::Update().
extern FMOD::System *FMODSystem;

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

char *GLOBAL_ACCOUNT_NAME;
static char LOCAL_ACCOUNT_NAME[ ACT_ACCOUNT_ID_SIZE ];
static u8 *ErrorViewerWorkArea = NULL;
extern FSClient *GLOBAL_FSClient;
bool ReEnableHomeButton = false;

u32 HomeButtonDeniedCallback( void *context )
{
	LOG.Write( "HOME BUTTON DENIED!\n" );

	if( !ReEnableHomeButton )
	{
		nn::erreula::HomeNixSignArg nixArg;
		AppearHomeNixSign( nixArg );
	}

	return 0;
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
	char *gfxArgs[] = { "DEMO_CB_FORMAT 8_8_8_8", "DEMO_SCAN_FORMAT 8_8_8_8" };
	DEMOGfxInit( 2, gfxArgs );
	DEMODRCInit( 0, NULL );

	// Allocate space for MEM1 for process switching.
	u32 mem1Size;
	OSGetMemBound( OSMem_MEM1, ( u32 * )&mem1Storage_, &mem1Size );
	mem1Storage_ = MEMAllocFromDefaultHeap( mem1Size );
	ProcUISetMEM1Storage( mem1Storage_, mem1Size );

	// Error viewer.
	LOG.Write( "nn::erreula::GetWorkMemorySize() = %d MB\n", nn::erreula::GetWorkMemorySize() / ( 1024 * 1024 ) );

	nn::erreula::CreateArg createArg;
	u8 *workBuffer = new u8[ nn::erreula::GetWorkMemorySize() ];
	ErrorViewerWorkArea = workBuffer;
	createArg.mBuffer = workBuffer;
	createArg.mFSClient = GLOBAL_FSClient;

	// FIXME: This is where the region is changed for the errorviewer.
	createArg.mRegion = nn::erreula::cRegionType_Us;

	SCICafeLanguage language;
	SCIStatus status = SCIGetCafeLanguage( &language );
	if( status == SCI_STATUS_SUCCESS )
		createArg.mLang = static_cast< nn::erreula::LangType >( language );

	nn::erreula::Create( createArg );
	ReEnableHomeButton = false;
	// End error viewer.

	ProcUIRegisterCallback( PROCUI_MESSAGE_HBDENIED, HomeButtonDeniedCallback, NULL, 0 );

	scheduler_ = new Scheduler;

	content_ = new Wad( "" );

	qd_ = new QuadDrawer;

	td_ = new TextDrawer;

	GamePad::Initialize();
	MediaPlayer::Initialize();


	// FIXME: Docs say to delay this as much as possible.
	SAVEInit();
	nn::act::Initialize();

	u8 accountSlot = nn::act::GetSlotNo();
	u32 persistentId = nn::act::GetPersistentIdEx( accountSlot );

	if( nn::act::IsSlotOccupied( accountSlot ) )
	{
		LOG.Write( "Creating account for slot %d with id 0x%X\n", accountSlot, persistentId );

		if( SAVEInitSaveDir( accountSlot ) != SAVE_STATUS_OK )
		{
			LOG.Write( "Failed to create save directory.\n" );
		}
	}

	GLOBAL_ACCOUNT_NAME = LOCAL_ACCOUNT_NAME;
	memset( LOCAL_ACCOUNT_NAME, 0, sizeof( LOCAL_ACCOUNT_NAME ) );
	sprintf( LOCAL_ACCOUNT_NAME, "Errorberry" );
	nn::act::GetAccountId( LOCAL_ACCOUNT_NAME );
	
	LOG.Write( "Creating global directory\n" );
	if( SAVEInitSaveDir( ACT_SLOT_NO_COMMON ) != SAVE_STATUS_OK )
		LOG.Write( "Failed to create common directory.\n" );
}

CoreWiiU::~CoreWiiU()
{
	LOG.Write( "SHUTDOWN START\n" );
	
	nn::act::Finalize();
	SAVEShutdown();

	MediaPlayer::Shutdown();
	GamePad::Shutdown();

	delete td_;

	delete qd_;

	delete content_;

	delete scheduler_;

	nn::erreula::Destroy();

	delete ErrorViewerWorkArea;

	// Free MEM1 backup.
	ProcUISetMEM1Storage( NULL, 0 );
	MEMFreeToDefaultHeap( mem1Storage_ );

	DEMODRCShutdown();
	DEMOGfxShutdown();
	DEMOTestShutdown();
	DEMOShutdown();
	LOG.Write( "SHUTDOWN END\n" );
}

extern bool GLOBAL_VIDEO_OVERRIDE;

int CoreWiiU::Run()
{
	running_ = true;
	
	game_.Initialize();

	while( DEMOIsRunning() )
	{
		FMODSystem->update();

		GamePad::Update();
		
		nn::erreula::ControllerInfo controllerInfo;
		nn::erreula::Calc( controllerInfo );

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

		if( !GLOBAL_VIDEO_OVERRIDE )
		{
			DEMOGfxBeforeRender();
			GX2ClearColor( &DEMOColorBuffer, 0, 0, 0, 0 );
			GX2ClearDepthStencil( &DEMODepthBuffer, GX2_CLEAR_BOTH );

			DEMOGfxSetContextState();

			GX2SetColorBuffer(&DEMOColorBuffer, GX2_RENDER_TARGET_0);
			GX2SetDepthBuffer(&DEMODepthBuffer);

			GX2SetDepthOnlyControl( GX2_FALSE, GX2_FALSE, GX2_COMPARE_ALWAYS );
			GX2SetColorControl( GX2_LOGIC_OP_COPY, 0x1, GX2_DISABLE, GX2_ENABLE );
			GX2SetBlendControl( GX2_RENDER_TARGET_0,
				GX2_BLEND_ONE, GX2_BLEND_ONE_MINUS_SRC_ALPHA, GX2_BLEND_COMBINE_ADD,
				GX2_TRUE, GX2_BLEND_ONE, GX2_BLEND_ONE_MINUS_SRC_ALPHA, GX2_BLEND_COMBINE_ADD );
		}

		//GX2SetDepthOnlyControl( GX2_FALSE, GX2_FALSE, GX2_COMPARE_ALWAYS );
		//GX2SetColorControl( GX2_LOGIC_OP_COPY, 0x1, GX2_DISABLE, GX2_ENABLE );
		/*GX2SetBlendControl( GX2_RENDER_TARGET_0,
			GX2_BLEND_SRC_COLOR, GX2_BLEND_DST_COLOR, GX2_BLEND_COMBINE_ADD,
			GX2_TRUE, GX2_BLEND_SRC_ALPHA, GX2_BLEND_ZERO, GX2_BLEND_COMBINE_ADD );*/
		/*GX2SetBlendControl( GX2_RENDER_TARGET_0,
			GX2_BLEND_ONE, GX2_BLEND_ONE_MINUS_SRC_ALPHA, GX2_BLEND_COMBINE_ADD,
			GX2_TRUE, GX2_BLEND_ONE, GX2_BLEND_ONE_MINUS_SRC_ALPHA, GX2_BLEND_COMBINE_ADD );*/

		game_.Update();

		if( !GLOBAL_VIDEO_OVERRIDE )
		{
			DEMOGfxSetContextState();

			nn::erreula::DrawTV();

			DEMOGfxDoneRender();
		}
		else
		{
			DEMOGfxWaitForSwap( 1, 100 );
		}

		// Close down.
		if( !running_ )
		{
			DEMOStopRunning();
			dynamic_cast< QuadDrawerWiiU * >( qd_ )->Unlock();
		}

		// Enable home button when the disable home button sign is no longer visible.
		if( ReEnableHomeButton && !nn::erreula::IsAppearHomeNixSign() )
		{
			OSEnableHomeButtonMenu( TRUE );

			ReEnableHomeButton = false;
		}
	}

	return 0;
}

void CoreWiiU::Exit()
{
	running_ = false;
}
