#include <Input/GamePad.h>

#include "PS3/gfxPad.h"
#include <Utility/Error.h>

void GamePad::Initialize()
{
	gfxInitPad();
}

bool AutoCloseWhenConnected()
{
	gfxPadRead();

	int numConnected = 0;
	
	for( int i = 0; i < 4; ++i )
	{
		if( gfxPadConnected( i ) )
			++numConnected;
	}

	return numConnected != 0;
}

void GamePad::Update()
{
	gfxPadRead();

	int numConnected = 0;
	for( int i = 0; i < 4; ++i )
	{
		if( gfxPadConnected( i ) )
			++numConnected;
	}

	if( numConnected == 0 )
	{
		DisplayError( ErrorType(
			"Error:\nNo Gamepad detected\nPlease press the PS button if the gamepad is connected",
			NULL,
			ErrorType::DEFAULT,
			AutoCloseWhenConnected
		) );
	}
}

GamePadState GamePad::GetState( PlayerIndex index )
{
	int i = static_cast< int >( index );

	GamePadState gs;

	if( !gfxPadConnected( i ) )
		return gs;

	gs.IsConnected = true;

	gs.DPad.Left = gfxDpadLeft (i ) ? ButtonState_Pressed : ButtonState_Released;
	gs.DPad.Right = gfxDpadRight( i ) ? ButtonState_Pressed : ButtonState_Released;
	gs.DPad.Up = gfxDpadUp( i ) ? ButtonState_Pressed : ButtonState_Released;
	gs.DPad.Down = gfxDpadDown( i ) ? ButtonState_Pressed : ButtonState_Released;

	gs.Triggers.Left = gfxL2Down( i ) ? ButtonState_Pressed : ButtonState_Released;
	gs.Triggers.Right = gfxR2Down( i ) ? ButtonState_Pressed : ButtonState_Released;

	gs.Buttons.A = gfxDpadCross( i ) ? ButtonState_Pressed : ButtonState_Released;
	gs.Buttons.B = gfxDpadCircle( i ) ? ButtonState_Pressed : ButtonState_Released;
	gs.Buttons.X = gfxDpadSquare( i ) ? ButtonState_Pressed : ButtonState_Released;
	gs.Buttons.Y = gfxDpadTri( i ) ? ButtonState_Pressed : ButtonState_Released;

	gs.Buttons.Back = gfxSelectDown( i ) ? ButtonState_Pressed : ButtonState_Released;
	gs.Buttons.Start = gfxStartDown( i ) ? ButtonState_Pressed : ButtonState_Released;

	( void )gs.Buttons.BigButton;

	gs.Buttons.LeftShoulder = gfxL1Down( i ) ? ButtonState_Pressed : ButtonState_Released;
	gs.Buttons.RightShoulder = gfxR1Down( i ) ? ButtonState_Pressed : ButtonState_Released;

	gs.Buttons.LeftStick = gfxL3Down( i ) ? ButtonState_Pressed : ButtonState_Released;
	gs.Buttons.RightStick = gfxR3Down( i ) ? ButtonState_Pressed : ButtonState_Released;

	gs.Triggers.Left = gfxL2Pressure( i );
	gs.Triggers.Right = gfxR2Pressure( i );

	gfxLeftStick( i, gs.ThumbSticks.Left.X, gs.ThumbSticks.Left.Y );
	gfxRightStick( i, gs.ThumbSticks.Right.X, gs.ThumbSticks.Right.Y );

	return gs;
}

void GamePad::SetVibration( PlayerIndex index, float left, float right )
{
}

void GamePad::Shutdown()
{
	gfxPadEnd();
}

void GamePad::DisableController( PlayerIndex index )
{
}
