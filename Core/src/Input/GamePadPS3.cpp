#include <Input/GamePad.h>

#include "PS3/gfxPad.h"

void GamePad::Initialize()
{
	gfxInitPad();
}

void GamePad::Update()
{
	gfxPadRead();
}

GamePadState GamePad::GetState( PlayerIndex index )
{
	int i = static_cast< int >( index );

	GamePadState gs;

	if( !gfxPadConnected( i ) )
		return gs;

	gs.IsConnected = true;

	gs.DPad.Left = gfxDpadLeft( i ) ? ButtonState_Pressed : ButtonState_Released;
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

	gs.Buttons.BigButton;

	gs.Buttons.LeftShoulder = gfxL1Down( i ) ? ButtonState_Pressed : ButtonState_Released;
	gs.Buttons.RightShoulder = gfxR1Down( i ) ? ButtonState_Pressed : ButtonState_Released;

	gs.Buttons.LeftStick;
	gs.Buttons.RightStick;

	return gs;
}

void GamePad::SetVibration( PlayerIndex index, float left, float right )
{
}

void GamePad::Shutdown()
{
	gfxPadEnd();
}
