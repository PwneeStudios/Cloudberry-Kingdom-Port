#include <Input/GamePad.h>

#include <cafe/pad.h>
#include <cafe/vpad.h>
#include <cafe/wenc.h>
#include <cafe/pads/wpad/wpad.h>

#include <Utility/Error.h>

GamePadState PAD_STATE[ PAD_MAX_CONTROLLERS ];

VPADStatus vpadStatus;
s32 readLength;
bool vpadConnected;

static void ConnectCallback( s32 chan, s32 reason )
{
	if( reason >= 0 )
	{
		WPADSetDataFormat( chan, WPAD_FMT_CORE );
		WPADControlSpeaker( chan, WPAD_SPEAKER_OFF, NULL );
		WPADControlDpd( chan, WPAD_DPD_OFF, NULL );
	}
}

void GamePad::Initialize()
{
	PADInit();
	WPADInit();

	for( int i = 0; i < WPAD_MAX_CONTROLLERS; i++ )
		WPADSetConnectCallback( i, ConnectCallback );

	memset( &vpadStatus, 0, sizeof( VPADStatus ) );
	vpadConnected = true;
}

void GamePad::Update()
{
	memset( PAD_STATE, 0, sizeof( PAD_STATE ) );

	for( int i = 0; i < PAD_MAX_CONTROLLERS; ++i )
		PAD_STATE[ i ].Type = GamePadState::ControllerType_Standard;

	// Update Wiimotes.
	for( int i = 0; i < __min( WPAD_MAX_CONTROLLERS, WPAD_MAX_CONTROLLERS ); i++ )
	{
		u32 type;
		s32 status = WPADProbe( i, &type );

		if( status != WPAD_ERR_NO_CONTROLLER )
		{
			WPADStatus      cr;
			WPADFSStatus    fs;
			WPADCLStatus    cl;

			u16 button;
			WPADRead( i, &cr );

			if( /*cr.err == WPAD_ERR_NONE
				|| */cr.err == WPAD_ERR_CORRUPTED )
				continue;

			
			PAD_STATE[ i ].IsConnected = true;
			
			PAD_STATE[ i ].Buttons.A = ( cr.button & WPAD_BUTTON_2 ) ? ButtonState_Pressed : ButtonState_Released;
			PAD_STATE[ i ].Buttons.B = ( cr.button & WPAD_BUTTON_1 ) ? ButtonState_Pressed : ButtonState_Released;
			PAD_STATE[ i ].Buttons.X = ( cr.button & WPAD_BUTTON_B ) ? ButtonState_Pressed : ButtonState_Released;
			PAD_STATE[ i ].Buttons.Y = ( cr.button & WPAD_BUTTON_A
										|| cr.button & WPAD_BUTTON_MINUS ) ? ButtonState_Pressed : ButtonState_Released;

			PAD_STATE[ i ].Buttons.Start = ( cr.button & WPAD_BUTTON_PLUS ) ? ButtonState_Pressed : ButtonState_Released;

			PAD_STATE[ i ].DPad.Down = ( cr.button & WPAD_BUTTON_LEFT ) ? ButtonState_Pressed : ButtonState_Released;
			PAD_STATE[ i ].DPad.Left = ( cr.button & WPAD_BUTTON_UP ) ? ButtonState_Pressed : ButtonState_Released;
			PAD_STATE[ i ].DPad.Right = ( cr.button & WPAD_BUTTON_DOWN ) ? ButtonState_Pressed : ButtonState_Released;
			PAD_STATE[ i ].DPad.Up = ( cr.button & WPAD_BUTTON_RIGHT ) ? ButtonState_Pressed : ButtonState_Released;

			if( PAD_STATE[ i ].Buttons.A || PAD_STATE[ i ].Buttons.B || PAD_STATE[ i ].Buttons.X || PAD_STATE[ i ].Buttons.Y )
				PAD_STATE[ i ].Type = GamePadState::ControllerType_Mini;
		}
	}

	// Update gamepad.
	PADStatus status[ PAD_MAX_CONTROLLERS ];
	memset( status, 0, sizeof( status ) );
	PADRead( status );
	static Vector2 textPos( 0, 0 );

	for( int i = 0; i < PAD_MAX_CONTROLLERS; ++i )
	{
		if( status[ i ].err == PAD_ERR_NO_CONTROLLER
			&& status[ i ].err == PAD_ERR_NOT_READY )
		{
			PAD_STATE[ i ].IsConnected = false;
			continue;
		}

		PAD_STATE[ i ].IsConnected |= true;

		// Mapping is inverse of XBox.
		PAD_STATE[ i ].Buttons.A = __max( PAD_STATE[ i ].Buttons.A, ( status[ i ].button & PAD_BUTTON_A ) ? ButtonState_Pressed : ButtonState_Released );
		PAD_STATE[ i ].Buttons.B = __max( PAD_STATE[ i ].Buttons.B, ( status[ i ].button & PAD_BUTTON_B ) ? ButtonState_Pressed : ButtonState_Released );
		PAD_STATE[ i ].Buttons.Y = __max( PAD_STATE[ i ].Buttons.Y, ( status[ i ].button & PAD_BUTTON_X ) ? ButtonState_Pressed : ButtonState_Released );
		PAD_STATE[ i ].Buttons.X = __max( PAD_STATE[ i ].Buttons.X, ( status[ i ].button & PAD_BUTTON_Y ) ? ButtonState_Pressed : ButtonState_Released );

		PAD_STATE[ i ].Buttons.LeftShoulder = __max( PAD_STATE[ i ].Buttons.LeftShoulder, ( status[ i ].button & PAD_BUTTON_L ) ? ButtonState_Pressed : ButtonState_Released );
		PAD_STATE[ i ].Buttons.RightShoulder = __max( PAD_STATE[ i ].Buttons.RightShoulder, ( status[ i ].button & PAD_BUTTON_R ) ? ButtonState_Pressed : ButtonState_Released );
		PAD_STATE[ i ].Buttons.Start = __max( PAD_STATE[ i ].Buttons.Start, ( status[ i ].button & PAD_BUTTON_START ) ? ButtonState_Pressed : ButtonState_Released );

		PAD_STATE[ i ].DPad.Down = __max( PAD_STATE[ i ].DPad.Down, ( status[ i ].button & PAD_BUTTON_DOWN ) ? ButtonState_Pressed : ButtonState_Released );
		PAD_STATE[ i ].DPad.Left = __max( PAD_STATE[ i ].DPad.Left, ( status[ i ].button & PAD_BUTTON_LEFT ) ? ButtonState_Pressed : ButtonState_Released );
		PAD_STATE[ i ].DPad.Right = __max( PAD_STATE[ i ].DPad.Right, ( status[ i ].button & PAD_BUTTON_RIGHT ) ? ButtonState_Pressed : ButtonState_Released );
		PAD_STATE[ i ].DPad.Up = __max( PAD_STATE[ i ].DPad.Up, ( status[ i ].button & PAD_BUTTON_UP ) ? ButtonState_Pressed : ButtonState_Released );
		/*PAD_STATE[ i ].Buttons.LeftStick = ( status[ i ].button & PAD_BUTTON_START ) ? ButtonState_Pressed : ButtonState_Released;
		PAD_STATE[ i ].Buttons.RightStick = ( status[ i ].button & PAD_BUTTON_START ) ? ButtonState_Pressed : ButtonState_Released;
		PAD_STATE[ i ].Buttons.Back = ( status[ i ].button & PAD_BUTTON_START ) ? ButtonState_Pressed : ButtonState_Released;
		PAD_STATE[ i ].Buttons.BigButton = ( status[ i ].button & PAD_BUTTON_MENU ) ? ButtonState_Pressed : ButtonState_Released;*/

		PAD_STATE[ i ].Triggers.Left = status[ i ].triggerLeft / 255.f;
		PAD_STATE[ i ].Triggers.Right = status[ i ].triggerRight / 255.f;

		PAD_STATE[ i ].ThumbSticks.Left = Vector2( status[ i ].stickX / 128.f, status[ i ].stickY / 128.f );
		PAD_STATE[ i ].ThumbSticks.Right = Vector2( status[ i ].substickX / 128.f, status[ i ].substickY / 128.f );
	}

	// Update DRC.
	s32 error;
	for( int i = 0; i < 1/*VPAD_MAX_CONTROLLERS*/; ++i )
	{
		readLength = VPADRead( VPADBASE_CHAN0 + i, &vpadStatus, 1, &error );

		if( error == VPAD_READ_ERR_NONE )
		{
			vpadConnected = true;

			// Mapping is inverse of XBox.
			PAD_STATE[ i ].Buttons.A = __max( PAD_STATE[ i ].Buttons.A, vpadStatus.hold & VPAD_BUTTON_A ? ButtonState_Pressed : ButtonState_Released );
			PAD_STATE[ i ].Buttons.B = __max( PAD_STATE[ i ].Buttons.B, vpadStatus.hold & VPAD_BUTTON_B ? ButtonState_Pressed : ButtonState_Released );
			PAD_STATE[ i ].Buttons.Y = __max( PAD_STATE[ i ].Buttons.Y, vpadStatus.hold & VPAD_BUTTON_X ? ButtonState_Pressed : ButtonState_Released );
			PAD_STATE[ i ].Buttons.X = __max( PAD_STATE[ i ].Buttons.X, vpadStatus.hold & VPAD_BUTTON_Y ? ButtonState_Pressed : ButtonState_Released );

			PAD_STATE[ i ].Buttons.LeftShoulder = __max( PAD_STATE[ i ].Buttons.LeftShoulder, vpadStatus.hold & VPAD_BUTTON_L ? ButtonState_Pressed : ButtonState_Released );
			PAD_STATE[ i ].Buttons.RightShoulder = __max( PAD_STATE[ i ].Buttons.RightShoulder, vpadStatus.hold & VPAD_BUTTON_R ? ButtonState_Pressed : ButtonState_Released );
			PAD_STATE[ i ].Buttons.Start = __max( PAD_STATE[ i ].Buttons.Start, vpadStatus.hold & VPAD_BUTTON_PLUS ? ButtonState_Pressed : ButtonState_Released );

			PAD_STATE[ i ].DPad.Down = __max( PAD_STATE[ i ].DPad.Down, vpadStatus.hold & VPAD_BUTTON_DOWN ? ButtonState_Pressed : ButtonState_Released );
			PAD_STATE[ i ].DPad.Left = __max( PAD_STATE[ i ].DPad.Left, vpadStatus.hold & VPAD_BUTTON_LEFT ? ButtonState_Pressed : ButtonState_Released );
			PAD_STATE[ i ].DPad.Right = __max( PAD_STATE[ i ].DPad.Right, vpadStatus.hold & VPAD_BUTTON_RIGHT ? ButtonState_Pressed : ButtonState_Released );
			PAD_STATE[ i ].DPad.Up = __max( PAD_STATE[ i ].DPad.Up, vpadStatus.hold & VPAD_BUTTON_UP ? ButtonState_Pressed : ButtonState_Released );
			
			PAD_STATE[ i ].Buttons.LeftStick = vpadStatus.hold & VPAD_BUTTON_STICK_L ? ButtonState_Pressed : ButtonState_Released;
			PAD_STATE[ i ].Buttons.RightStick = vpadStatus.hold & VPAD_BUTTON_STICK_R ? ButtonState_Pressed : ButtonState_Released;
			/*PAD_STATE[ i ].Buttons.LeftStick = ( status[ i ].button & PAD_BUTTON_START ) ? ButtonState_Pressed : ButtonState_Released;
			PAD_STATE[ i ].Buttons.RightStick = ( status[ i ].button & PAD_BUTTON_START ) ? ButtonState_Pressed : ButtonState_Released;
			PAD_STATE[ i ].Buttons.Back = ( status[ i ].button & PAD_BUTTON_START ) ? ButtonState_Pressed : ButtonState_Released;
			PAD_STATE[ i ].Buttons.BigButton = ( status[ i ].button & PAD_BUTTON_MENU ) ? ButtonState_Pressed : ButtonState_Released;*/

			PAD_STATE[ i ].Triggers.Left =  ( vpadStatus.hold & VPAD_TRIGGER_ZL ) / VPAD_TRIGGER_ZL ? ButtonState_Pressed : ButtonState_Released;
			PAD_STATE[ i ].Triggers.Right = ( vpadStatus.hold & VPAD_TRIGGER_ZR ) / VPAD_TRIGGER_ZR ? ButtonState_Pressed : ButtonState_Released;

			PAD_STATE[ i ].ThumbSticks.Left = Vector2( vpadStatus.lStick.x, vpadStatus.lStick.y );
			PAD_STATE[ i ].ThumbSticks.Right = Vector2( vpadStatus.lStick.x, vpadStatus.lStick.y );
		}
		else if( error == VPAD_READ_ERR_NO_CONTROLLER && vpadConnected == true )
		{
			vpadConnected = false;

			// Unable to communicate with the WiiU gamepad.
			DisplayError( 1650101 );
		}
	}
}

GamePadState GamePad::GetState( PlayerIndex index )
{
	return PAD_STATE[ static_cast<int>( index ) ];
}

void GamePad::SetVibration( PlayerIndex index, float left, float right )
{
}

void GamePad::Shutdown()
{
}

void GamePad::DisableController( PlayerIndex index )
{
	WPADDisconnect( static_cast< s32 >( index ) );
}
