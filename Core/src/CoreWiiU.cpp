#include <CoreWiiU.h>

#include <Architecture/Scheduler.h>
#include <Audio/MediaPlayer.h>
#include <cafe/demo.h>
#include <cafe/gx2.h>
#include <cafe/procui.h>
#include <cafe/sci/sciEnum.h>
#include <cafe/sci/sciPublicApi.h>
#include <cafe/sysapp.h>
#include <Content/Wad.h>
#include <Core.h>
#include <cstdlib>
#include <GameLoop.h>
#include <Graphics/QuadDrawer.h>
#include <Graphics/TextDrawer.h>
#include <Input/GamePad.h>
#include <nn/act.h>
#include <nn/save.h>
#include <nn/erreula.h>
#include <Utility/Error.h>
#include <Utility/Limits.h>
#include <Utility/Log.h>
#include "Graphics/WiiU/videorender.h"
#include "Graphics/RenderTarget2DWiiUInternal.h"

#include <fmod.h>
#include <fmodwiiu.h>

// FIXME: This is done in order to get access to update the FMOD system every frame.
// This should really be done through a method like MediaPlayer::Update().
//extern FMOD::System *FMODSystem;
extern FMOD_SYSTEM *FMODSystem;

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

	if( !nn::erreula::IsAppearHomeNixSign() )
	{
		nn::erreula::HomeNixSignArg nixArg;
		AppearHomeNixSign( nixArg );
	}
	else
		LOG.Write( "ALREADY VISIBLE!\n" );

	return 0;
}

/*u32 SaveOnExitCallback( void *context )
{
	OSSavesDone_ReadyToRelease();

	return 0;
}*/

GX2ColorBuffer TheColorBuffer;
GX2Texture TheColorBufferTexture;

// Kill the video player if it's still alive, we don't want stuff running in the background in case we are exiting.
extern void ForceKillVideoPlayer();

extern void StopScheduler();
extern void ResumeScheduler();

extern std::vector< RenderTarget2DInternal * > GlobalRenderTargets;

void FinalReleaseCallback()
{
	LOG.Write( "Releasing while video is playing.  Kill the player\n" );
	ForceKillVideoPlayer();

	StopScheduler();

	ProcUIDrawDoneRelease();
}

u32 ReleaseForegroundCallback( void *context )
//void ReleaseForegroundCallback()
{
	DEMOGfxFreeMEM1( TheColorBuffer.surface.imagePtr );

	// Free up render targets.
	LOG.Write( "Freeing %d render targets\n", GlobalRenderTargets.size() );
	std::vector< RenderTarget2DInternal * >::iterator i;
	for( i = GlobalRenderTargets.begin(); i != GlobalRenderTargets.end(); ++i )
	{
		DEMOGfxFreeMEM1( ( *i )->ColorBuffer.surface.imagePtr );
	}

	return 0;
}

u32 AcquireForegroundCallback( void *context )
{
	GX2InitColorBuffer( &TheColorBuffer, 1280, 720, DEMOColorBuffer.surface.format/*GX2_SURFACE_FORMAT_TCS_R8_G8_B8_A8_UNORM*/, GX2_AA_MODE_1X );
	void *ptr = DEMOGfxAllocMEM1( TheColorBuffer.surface.imageSize, TheColorBuffer.surface.alignment );
	GX2Invalidate( GX2_INVALIDATE_CPU, ptr, TheColorBuffer.surface.imageSize );
	GX2InitColorBufferPtr( &TheColorBuffer, ptr );
	
	GX2InitTexture( &TheColorBufferTexture, 1280, 720, 1, 0, DEMOColorBuffer.surface.format/*GX2_SURFACE_FORMAT_TCS_R8_G8_B8_A8_UNORM*/,
		GX2_SURFACE_DIM_2D );
	GX2InitTexturePtrs( &TheColorBufferTexture, TheColorBuffer.surface.imagePtr, 0 );

	// Restore render targets.
	LOG.Write( "Restoring %d render targets\n", GlobalRenderTargets.size() );
	std::vector< RenderTarget2DInternal * >::iterator i;
	for( i = GlobalRenderTargets.begin(); i != GlobalRenderTargets.end(); ++i )
	{
		GX2InitColorBufferPtr( &( *i )->ColorBuffer, DEMOGfxAllocMEM1(
			( *i )->ColorBuffer.surface.imageSize,
			( *i )->ColorBuffer.surface.alignment
		) );
		GX2Invalidate( GX2_INVALIDATE_CPU, ( *i )->ColorBuffer.surface.imagePtr,
			( *i )->ColorBuffer.surface.imageSize );
	}

	ResumeScheduler();

	return 0;
}

// Draw a texture to the DRC.  Declared in videorenderer.cpp.
extern void drawDRCTextureFrame( GX2Texture * texture );

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
	char *drcArgs[] = { "DEMO_DRC_CB_FORMAT 8_8_8_8", "DEMO_DRC_SCAN_FORMAT 8_8_8_8" };
	DEMOGfxInit( 2, gfxArgs );
	DEMODRCInit( 2, drcArgs );

	//DEMOSetReleaseCallback( ForegroundReleaseCallback );

	// Allocate space for MEM1 for process switching.
	u32 mem1Size;
	OSGetMemBound( OSMem_MEM1, ( u32 * )&mem1Storage_, &mem1Size );
	mem1Storage_ = MEMAllocFromDefaultHeap( mem1Size );
	ProcUISetMEM1Storage( mem1Storage_, mem1Size );

	GX2InitColorBuffer( &TheColorBuffer, 1280, 720, DEMOColorBuffer.surface.format/*GX2_SURFACE_FORMAT_TCS_R8_G8_B8_A8_UNORM*/,
		GX2_AA_MODE_1X );
	void *ptr = DEMOGfxAllocMEM1( TheColorBuffer.surface.imageSize, TheColorBuffer.surface.alignment );
	GX2Invalidate( GX2_INVALIDATE_CPU, ptr, TheColorBuffer.surface.imageSize );
	GX2InitColorBufferPtr( &TheColorBuffer, ptr );

	GX2InitTexture( &TheColorBufferTexture, 1280, 720, 1, 0, DEMOColorBuffer.surface.format/*GX2_SURFACE_FORMAT_TCS_R8_G8_B8_A8_UNORM*/,
		GX2_SURFACE_DIM_2D );
	GX2InitTexturePtrs( &TheColorBufferTexture, TheColorBuffer.surface.imagePtr, 0 );

	// Error viewer.
	LOG.Write( "nn::erreula::GetWorkMemorySize() = %d MB\n", nn::erreula::GetWorkMemorySize() / ( 1024 * 1024 ) );

	nn::erreula::CreateArg createArg;
	u8 *workBuffer = new u8[ nn::erreula::GetWorkMemorySize() ];
	ErrorViewerWorkArea = workBuffer;
	createArg.mBuffer = workBuffer;
	createArg.mFSClient = GLOBAL_FSClient;

	// Set up error viewer region.
	createArg.mRegion = nn::erreula::cRegionType_Us;
	SCIPlatformRegion region;
	SCIStatus status = SCIGetPlatformRegion( &region );
	if( status == SCI_STATUS_SUCCESS )
	{
		switch( region )
		{
		case SCI_PLATFORM_REGION_JPN:
			createArg.mRegion = nn::erreula::cRegionType_Jp;
			break;
		case SCI_PLATFORM_REGION_USA:
			createArg.mRegion = nn::erreula::cRegionType_Us;
			break;
		case SCI_PLATFORM_REGION_EUR:
		case SCI_PLATFORM_REGION_AUS:
			createArg.mRegion = nn::erreula::cRegionType_Eu;
			break;
		case SCI_PLATFORM_REGION_CHN:  // These are not supported by the error viewer and are thus
		case SCI_PLATFORM_REGION_KOR:  // defaulted to English.
		case SCI_PLATFORM_REGION_TWN:
		default:
			// By default the region is US.
			break;
		}
	}

	createArg.mLang = nn::erreula::cLangType_En;
	SCICafeLanguage language;
	status = SCIGetCafeLanguage( &language );
	if( status == SCI_STATUS_SUCCESS )
		createArg.mLang = static_cast< nn::erreula::LangType >( language );

	nn::erreula::Create( createArg );
	ReEnableHomeButton = false;
	// End error viewer.

	ProcUIRegisterCallback( PROCUI_MESSAGE_HBDENIED, HomeButtonDeniedCallback, NULL, 100 );
	ProcUIRegisterCallback( PROCUI_MESSAGE_RELEASE, ReleaseForegroundCallback, NULL, 250 );
	DEMOSetReleaseCallback( FinalReleaseCallback );
	ProcUIRegisterCallback( PROCUI_MESSAGE_ACQUIRE, AcquireForegroundCallback, NULL, 250 );
	//ProcUISetSaveCallback( SaveOnExitCallback, NULL );

	// Initialize shaders for video renderer.
	InitShader();
	InitAttribData();

	scheduler_ = new Scheduler;

	content_ = new Wad( "" );

	qd_ = new QuadDrawer;

	td_ = new TextDrawer;

	GamePad::Initialize();
	MediaPlayer::Initialize();

	InitializeErrorSystem();
}

CoreWiiU::~CoreWiiU()
{
	LOG.Write( "SHUTDOWN START\n" );
	
	nn::act::Finalize();
	SAVEShutdown();

	ShutdownErrorSystem();

	MediaPlayer::Shutdown();
	GamePad::Shutdown();

	delete td_;

	FreeShader();
	FreeAttribData();

	delete qd_;

	delete scheduler_;

	delete content_;

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
extern std::list< ErrorType > GLOBAL_ERROR_QUEUE;
extern VPADStatus vpadStatus;
extern s32 readLength;
extern KPADStatus kpadStatus[ WPAD_MAX_CONTROLLERS ];
extern s32 kpadReadLength[ WPAD_MAX_CONTROLLERS ];
extern bool vpadConnected;
extern bool anythingElseConnected;

void DebugFrame( float r, float g, float b )
{
}

int CoreWiiU::Run()
{
	running_ = true;
	
	game_.Initialize();

	//bool viewerVisible = false;

	//GLOBAL_ERROR_QUEUE.push_back( 1010102 );

	s32 currentErrorCode = 0;
	ErrorType currentError( 0 );

	while( DEMOIsRunning() )
	{
		// Error viewer bits.
		if( nn::erreula::GetStateErrorViewer() == nn::erreula::cState_Blank )
		{
			if( GLOBAL_ERROR_QUEUE.size() > 0 )
			{
				FMOD_WiiU_SetMute( TRUE );

				ErrorType error = GLOBAL_ERROR_QUEUE.front();
				currentErrorCode = error.GetCode();
				currentError = error;
				GLOBAL_ERROR_QUEUE.pop_front();

				nn::erreula::AppearArg appearArg;
				appearArg.setControllerType( nn::erreula::cControllerType_Remo0 );
				appearArg.setScreenType( nn::erreula::cScreenType_Dual );
				appearArg.setErrorCode( currentErrorCode );
				nn::erreula::AppearErrorViewer( appearArg );
				//viewerVisible = true;
			}
		}

		GamePad::Update();

		VPADStatus vpad_status;
		//KPADStatus wpad_status[ WPAD_MAX_CONTROLLERS ];
		nn::erreula::ControllerInfo info;
		memset( &info, 0, sizeof( info ) );

		//s32 readLength = VPADRead( 0, &vpad_status, 1, NULL );
		if( readLength > 0 && vpadConnected )
		{
			// Set calibrated values
			VPADGetTPCalibratedPoint( 0, &vpadStatus.tpData, &vpadStatus.tpData );
			info.vpad_status = &vpadStatus;
		}
		else
			info.vpad_status = NULL;

		/*for ( int i = 0; i < WPAD_MAX_CONTROLLERS; ++i )
		{
			//s32 kpad_read_length = KPADRead( i, &wpad_status[i], 1 );
			if( kpadReadLength[ i ] > 0 )
			{
				info.kpad_status[ i ] = &kpadStatus[ i ];
			}
			else
			{
				// Pass NULL if it could not be read
				info.kpad_status[ i ] = NULL;
			}
		}*/

		nn::erreula::Calc( info );

		nn::erreula::State viewerState = nn::erreula::GetStateErrorViewer();
		if( viewerState != nn::erreula::cState_Blank )
		{
			if( nn::erreula::IsDecideSelectButtonError() )
			{
				// Exit and jump to data management!
				if( currentErrorCode == 1550100 )
				{
					SysStandardArgsIn standardArgs;
					memset( &standardArgs, 0, sizeof( standardArgs ) );

					SysSettingsArgsIn cpArgs;
					cpArgs.stdIn = standardArgs;
					cpArgs.jumpTo = SYS_SETTINGS_JUMP_TO_DATA_MANAGE;
					SYSLaunchSettings( &cpArgs );

					DEMOStopRunning();
				}

				if( nn::erreula::GetStateErrorViewer() == nn::erreula::cState_Display )
				{
					nn::erreula::DisappearErrorViewer();
					FMOD_WiiU_SetMute( FALSE );
					//viewerVisible = false;
				}
			}
			else if( currentErrorCode == 1520100 || currentErrorCode == 1650101 )
			{
				if( nn::erreula::GetStateErrorViewer() == nn::erreula::cState_Display
					/*&& ( anythingElseConnected || vpadConnected )*/
					&& currentError.GetAutoClose()() )
				{
					nn::erreula::DisappearErrorViewer();
					FMOD_WiiU_SetMute( FALSE );
					currentErrorCode = 0;
				}
			}
			/*else if( currentErrorCode == 1650101 )
			{
				if( vpadConnected || anythingElseConnected )
				{
					nn::erreula::DisappearErrorViewer();
					FMOD_WiiU_SetMute( FALSE );
					currentErrorCode = 0;
				}
			}*/

			if( !GLOBAL_VIDEO_OVERRIDE )
			{
				if( DEMODRCGetStatus() != GX2_DRC_NONE )
				{
					DEMODRCBeforeRender();

					GX2SetContextState( DEMODRCContextState );

					GX2SurfaceFormat f = DEMODRCColorBuffer.surface.format;
					DEMODRCColorBuffer.surface.format = static_cast< GX2SurfaceFormat >( f | 0x00000400 );
					GX2InitColorBufferRegs(&DEMODRCColorBuffer);
					GX2SetColorBuffer(&DEMODRCColorBuffer, GX2_RENDER_TARGET_0);

					nn::erreula::DrawDRC();

					DEMODRCColorBuffer.surface.format = f;
					GX2InitColorBufferRegs(&DEMODRCColorBuffer);
					GX2SetColorBuffer(&DEMODRCColorBuffer, GX2_RENDER_TARGET_0);

					GX2SetContextState( DEMODRCContextState );

					DEMODRCDoneRender();
				}

				DEMOGfxSetContextState();

				GX2SurfaceFormat f = DEMOColorBuffer.surface.format;
				DEMOColorBuffer.surface.format = static_cast< GX2SurfaceFormat >( f | 0x00000400 );
				GX2InitColorBufferRegs( &DEMOColorBuffer );
				GX2SetColorBuffer( &DEMOColorBuffer, GX2_RENDER_TARGET_0 );

				nn::erreula::DrawTV();

				DEMOColorBuffer.surface.format = f;
				GX2InitColorBufferRegs( &DEMOColorBuffer );
				GX2SetColorBuffer( &DEMOColorBuffer, GX2_RENDER_TARGET_0 );

				DEMOGfxDoneRender();
			}

			continue;
		}
		// End error viewer bits.
		//FMODSystem->update();
		FMOD_System_Update( FMODSystem );

		// Set custom render target and update the game.
		if( !GLOBAL_VIDEO_OVERRIDE )
		{
			SCHEDULER->MainThread();

			DEMOGfxBeforeRender();

			GX2SetColorBuffer( &TheColorBuffer, GX2_RENDER_TARGET_0 );
			GX2SetViewport( 0.f, 0.f, 1280.f, 720.f, 0.f, 1.f );
			GX2SetScissor( 0, 0, 1280, 720 );

			GX2SetDepthOnlyControl( GX2_FALSE, GX2_FALSE, GX2_COMPARE_ALWAYS );
			GX2SetColorControl( GX2_LOGIC_OP_COPY, 0x1, GX2_DISABLE, GX2_ENABLE );
			GX2SetBlendControl( GX2_RENDER_TARGET_0,
				GX2_BLEND_ONE, GX2_BLEND_ONE_MINUS_SRC_ALPHA, GX2_BLEND_COMBINE_ADD,
				GX2_TRUE, GX2_BLEND_ONE, GX2_BLEND_ONE_MINUS_SRC_ALPHA, GX2_BLEND_COMBINE_ADD );

			GX2ClearColor( &TheColorBuffer, 0, 0, 0, 0 );
			GX2ClearDepthStencil( &DEMODepthBuffer, GX2_CLEAR_BOTH );

			DEMOGfxSetContextState();
		}

		game_.Update();

		// Restore default render target and draw our frame to it.
		if( !GLOBAL_VIDEO_OVERRIDE )
		{
			DEMOGfxDrawDone();

			if( DEMODRCGetStatus() != GX2_DRC_NONE )
			{
				DEMODRCBeforeRender();
				
				float r = (float)rand() / RAND_MAX;
				float g = (float)rand() / RAND_MAX;
				float b = (float)rand() / RAND_MAX;
				GX2ClearColor( &DEMODRCColorBuffer, r, g, b, 1 );
				GX2ClearDepthStencil( &DEMODRCDepthBuffer, GX2_CLEAR_BOTH );

				GX2SetContextState( DEMODRCContextState );

				drawDRCTextureFrame( &TheColorBufferTexture );

				GX2SetContextState( DEMODRCContextState );

				DEMODRCDoneRender();
			}

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

			DEMOGfxSetContextState();

			GX2CopySurface( &TheColorBuffer.surface, 0, 0, &DEMOColorBuffer.surface, 0, 0 );

			DEMOGfxSetContextState();

			DEMOGfxDoneRender();
		}
		else
			DEMOGfxWaitForSwap( 1, 100 );

		/*game_.Update();

		if( !GLOBAL_VIDEO_OVERRIDE )
		{
			DEMOGfxSetContextState();

			GX2SurfaceFormat f = DEMOColorBuffer.surface.format;
			DEMOColorBuffer.surface.format = static_cast< GX2SurfaceFormat >( f | 0x00000400 );
			GX2InitColorBufferRegs( &DEMOColorBuffer );
			GX2SetColorBuffer( &DEMOColorBuffer, GX2_RENDER_TARGET_0 );

			nn::erreula::DrawTV();

			DEMOColorBuffer.surface.format = f;
			GX2InitColorBufferRegs( &DEMOColorBuffer );
			GX2SetColorBuffer( &DEMOColorBuffer, GX2_RENDER_TARGET_0 );

			DEMOGfxDoneRender();
		}
		else
		{
			DEMOGfxWaitForSwap( 1, 100 );
		}*/

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
