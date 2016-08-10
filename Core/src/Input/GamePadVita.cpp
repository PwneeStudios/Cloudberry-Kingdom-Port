#include <Input/GamePad.h>

#include <Utility/ConsoleInformation.h>
#include <Utility/Error.h>
#include <Utility/Log.h>

#include <ctrl.h>

static bool asianButtonConfiguration = false;

// Buffer for making sure disconnect messages don't show up for going from
// wired to wireless mode.
static int gBufferedIsConnected[ 4 ];
const int gBufferingSize = 80;//32;

static SceCtrlData gCtrlData;

void GamePad::Initialize()
{
	sceCtrlSetSamplingMode( SCE_CTRL_MODE_DIGITALANALOG );

	memset( &gCtrlData, 0, sizeof( SceCtrlData ) );

	asianButtonConfiguration = IsAsianButtonConfiguration();

	memset( gBufferedIsConnected, 0, sizeof( gBufferedIsConnected ) );
}

bool AutoCloseWhenConnected()
{
	//gfxPadRead();

	int numConnected = 0;
	
	for( int i = 0; i < 4; ++i )
	{
		//if( gfxPadConnected( i ) )
		//	++numConnected;
	}

	return numConnected != 0;
}

void GamePad::Update()
{
	//gfxPadRead();

	int numConnected = 0;
	for( int i = 0; i < 4; ++i )
	{
		//if( gfxPadConnected( i ) )
		//	++numConnected;
	}

	sceCtrlPeekBufferPositive( 0, &gCtrlData, 1 );
}

GamePadState GamePad::GetState( PlayerIndex index )
{
	int i = static_cast< int >( index );

	GamePadState gs;

	memset( &gs, 0, sizeof( gs ) );

	if( index != PlayerIndex_One )
		return gs;

	//bool isGamepadConnected = gfxPadConnected( i );

	gs.IsConnected = true;

#define CHECK( x ) ( ( x ) != 0 ? ButtonState_Pressed : ButtonState_Released )

	gs.DPad.Left = CHECK( gCtrlData.buttons & SCE_CTRL_LEFT );
	gs.DPad.Right = CHECK( gCtrlData.buttons & SCE_CTRL_RIGHT );
	gs.DPad.Up = CHECK( gCtrlData.buttons & SCE_CTRL_UP );
	gs.DPad.Down = CHECK( gCtrlData.buttons & SCE_CTRL_DOWN );

	if( !asianButtonConfiguration )
	{
		gs.Buttons.A = CHECK( gCtrlData.buttons & SCE_CTRL_CROSS );
		gs.Buttons.B = CHECK( gCtrlData.buttons & SCE_CTRL_CIRCLE );
	}
	else
	{
		gs.Buttons.B = CHECK( gCtrlData.buttons & SCE_CTRL_CROSS );
		gs.Buttons.A = CHECK( gCtrlData.buttons & SCE_CTRL_CIRCLE );
	}

	gs.Buttons.X = CHECK( gCtrlData.buttons & SCE_CTRL_SQUARE );
	gs.Buttons.Y = CHECK( gCtrlData.buttons & SCE_CTRL_TRIANGLE );
	gs.Buttons.Back = CHECK( gCtrlData.buttons & SCE_CTRL_SELECT );
	gs.Buttons.Start = CHECK( gCtrlData.buttons & SCE_CTRL_START );

	gs.Buttons.LeftShoulder = CHECK( gCtrlData.buttons & SCE_CTRL_L );
	gs.Buttons.RightShoulder = CHECK( gCtrlData.buttons & SCE_CTRL_R );

#undef CHECK

	gs.ThumbSticks.Left.X = 2.f * ( gCtrlData.lx / 255.f ) - 1.f;
	gs.ThumbSticks.Left.Y = -2.f * ( gCtrlData.ly / 255.f ) + 1.f;
	
	gs.ThumbSticks.Right.X = 2.f * ( gCtrlData.rx / 255.f ) - 1.f;
	gs.ThumbSticks.Right.Y = -2.f * ( gCtrlData.ry / 255.f ) + 1.f;
	//if( !isGamepadConnected )
	//	++gBufferedIsConnected[ i ];
	//else
	//	gBufferedIsConnected[ i ] = 0;

	//if( !isGamepadConnected )
	//	return gs;

	//gs.DPad.Left = gfxDpadLeft (i ) ? ButtonState_Pressed : ButtonState_Released;
	//gs.DPad.Right = gfxDpadRight( i ) ? ButtonState_Pressed : ButtonState_Released;
	//gs.DPad.Up = gfxDpadUp( i ) ? ButtonState_Pressed : ButtonState_Released;
	//gs.DPad.Down = gfxDpadDown( i ) ? ButtonState_Pressed : ButtonState_Released;

	//gs.Triggers.Left = gfxL2Down( i ) ? ButtonState_Pressed : ButtonState_Released;
	//gs.Triggers.Right = gfxR2Down( i ) ? ButtonState_Pressed : ButtonState_Released;

	//if( !asianButtonConfiguration )
	//{
	//	gs.Buttons.A = gfxDpadCross( i ) ? ButtonState_Pressed : ButtonState_Released;
	//	gs.Buttons.B = gfxDpadCircle( i ) ? ButtonState_Pressed : ButtonState_Released;
	//}
	//else
	//{
	//	gs.Buttons.B = gfxDpadCross( i ) ? ButtonState_Pressed : ButtonState_Released;
	//	gs.Buttons.A = gfxDpadCircle( i ) ? ButtonState_Pressed : ButtonState_Released;
	//}

	//gs.Buttons.X = gfxDpadSquare( i ) ? ButtonState_Pressed : ButtonState_Released;
	//gs.Buttons.Y = gfxDpadTri( i ) ? ButtonState_Pressed : ButtonState_Released;

	//gs.Buttons.Back = gfxSelectDown( i ) ? ButtonState_Pressed : ButtonState_Released;
	//gs.Buttons.Start = gfxStartDown( i ) ? ButtonState_Pressed : ButtonState_Released;

	//( void )gs.Buttons.BigButton;

	//gs.Buttons.LeftShoulder = gfxL1Down( i ) ? ButtonState_Pressed : ButtonState_Released;
	//gs.Buttons.RightShoulder = gfxR1Down( i ) ? ButtonState_Pressed : ButtonState_Released;

	//gs.Buttons.LeftStick = gfxL3Down( i ) ? ButtonState_Pressed : ButtonState_Released;
	//gs.Buttons.RightStick = gfxR3Down( i ) ? ButtonState_Pressed : ButtonState_Released;
	//
	//gs.Triggers.Left = gfxL2Pressure( i );
	//gs.Triggers.Right = gfxR2Pressure( i );

	//gfxLeftStick( i, gs.ThumbSticks.Left.X, gs.ThumbSticks.Left.Y );
	//gfxRightStick( i, gs.ThumbSticks.Right.X, gs.ThumbSticks.Right.Y );

	return gs;
}

void GamePad::SetVibration( PlayerIndex index, float left, float right )
{
}

void GamePad::Shutdown()
{
	//gfxPadEnd();
}

void GamePad::DisableController( PlayerIndex index )
{
}
