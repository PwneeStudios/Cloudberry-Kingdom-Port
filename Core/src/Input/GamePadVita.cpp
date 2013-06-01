#include <Input/GamePad.h>

#include <Utility/ConsoleInformation.h>
#include <Utility/Error.h>
#include <Utility/Log.h>

static bool asianButtonConfiguration = false;

// Buffer for making sure disconnect messages don't show up for going from
// wired to wireless mode.
static int gBufferedIsConnected[ 4 ];
const int gBufferingSize = 80;//32;

void GamePad::Initialize()
{
	//gfxInitPad();

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
}

GamePadState GamePad::GetState( PlayerIndex index )
{
	int i = static_cast< int >( index );

	GamePadState gs;

	//bool isGamepadConnected = gfxPadConnected( i );

	gs.IsConnected = gBufferedIsConnected[ i ] < gBufferingSize;

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
