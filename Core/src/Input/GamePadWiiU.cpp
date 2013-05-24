#include <Input/GamePad.h>

#include <algorithm>
#include <cafe/pad.h>
#include <cafe/vpad.h>
#include <cafe/wenc.h>
//#include <cafe/pads/wpad/wpad.h>
#include <cafe/pads/kpad/kpad.h>
#include <list>

#include <Utility/Error.h>
#include <Utility/Log.h>

GamePadState PAD_STATE[ PAD_MAX_CONTROLLERS ];

VPADStatus vpadStatus;
s32 readLength;
bool vpadConnected;
bool anythingElseConnected;
bool vpadActive;

KPADStatus kpadStatus[ WPAD_MAX_CONTROLLERS ];
s32 kpadReadLength[ WPAD_MAX_CONTROLLERS ];
bool kpadIsConnected[ WPAD_MAX_CONTROLLERS ];
bool kpadIsURCC[ WPAD_MAX_CONTROLLERS ];

// List of the connection status of all devices.
// 0	- WiiU gamepad.
// 1-4  - WiiMote.
bool GLOBAL_CONNECTION_STATUS[ 5 ];

bool GLOBAL_SHOW_VERSION = false;
bool GLOBAL_PLAYER0_DOWN = false;
bool GLOBAL_PLAYER0_MINI_B = false;

static void ConnectCallback( s32 chan, s32 reason )
{
	if( reason >= 0 )
	{
		u32 dataFormat = WPADGetDataFormat( chan );

		WPADControlSpeaker( chan, WPAD_SPEAKER_OFF, NULL );
		//WPADControlDpd( chan, WPAD_DPD_OFF, NULL );
		KPADDisableDPD( chan );
		KPADDisableMpls( chan );
		LOG_WRITE( "Gamepad connected, format = %d\n", dataFormat );
	}
	else if( reason == WPAD_ERR_NO_CONTROLLER )
	{
		LOG_WRITE( "Gamepad disconnected\n" );
	}
}

void GamePad::Initialize()
{
	PADInit();
	KPADInit();
	WPADEnableURCC( TRUE );

	for( int i = 0; i < WPAD_MAX_CONTROLLERS; ++i )
		KPADSetConnectCallback( i, ConnectCallback );

	memset( &vpadStatus, 0, sizeof( VPADStatus ) );
	vpadConnected = false;
	readLength = 0;

	// FIXME: Should not always be active.
	vpadActive = true;

	memset( kpadStatus, 0, sizeof( kpadStatus ) );
	memset( kpadReadLength, 0, sizeof( kpadReadLength ) );
	memset( kpadIsConnected, 0, sizeof( kpadIsConnected ) );
	memset( GLOBAL_CONNECTION_STATUS, 0, sizeof( GLOBAL_CONNECTION_STATUS ) );
	memset( kpadIsURCC, 0, sizeof( kpadIsURCC ) );
}

void GamePad::Update()
{
	bool versionComboDown = false;
	GLOBAL_PLAYER0_DOWN = false;
	GLOBAL_PLAYER0_MINI_B = false;

	// Save controller types
	GamePadState::ControllerType SaveType[4];
	for ( int i = 0; i < 4; ++i ) SaveType[ i ] = PAD_STATE[ i ].Type;

	// Reset states
	memset( PAD_STATE, 0, sizeof( PAD_STATE ) );

	// Reset controller types to what they were before memset
	for ( int i = 0; i < 4; ++i ) PAD_STATE[ i ].Type = SaveType[ i ];

	// Is anything else other than the vpad connected?
	anythingElseConnected = false;

	//bool wiiMoteActive = false;
	bool channel0ThumbsticksWritten = false;

	// We need to re-map the Wii motes so that player 4 overlaps with the GamePad.
	static const int WIIMOTE_REMAP[] = { 1, 2, 3, 0 };

	// Update Wiimotes.
	for( int i = 0; i < WPAD_MAX_CONTROLLERS; i++ )
	{
		s32 error;
		kpadReadLength[ WIIMOTE_REMAP[ i ] ] = KPADReadEx( i, &kpadStatus[ WIIMOTE_REMAP[ i ] ], 1, &error);

		PAD_STATE[ WIIMOTE_REMAP[ i ] ].IsConnected = error != KPAD_READ_ERR_NO_CONTROLLER;
		GLOBAL_CONNECTION_STATUS[ WIIMOTE_REMAP[ i ] + 1 ] = PAD_STATE[ WIIMOTE_REMAP[ i ] ].IsConnected;

		/*if( kpadIsConnected[ i ] && !PAD_STATE[ i ].IsConnected )
		{
			DisconnectController( i + 1 );
		}
		else if( !kpadIsConnected[ i ] && PAD_STATE[ i ].IsConnected )
		{
			ReconnectController( i + 1 );
		}*/

		kpadIsConnected[ WIIMOTE_REMAP[ i ] ] = PAD_STATE[ WIIMOTE_REMAP[ i ] ].IsConnected;

		if( !PAD_STATE[ WIIMOTE_REMAP[ i ] ].IsConnected )
			continue;

		anythingElseConnected = true;

		if( kpadStatus[ WIIMOTE_REMAP[ i ] ].wpad_err == WPAD_ERR_CORRUPTED )
			continue;
		
		if( kpadStatus[ WIIMOTE_REMAP[ i ] ].data_format != WPAD_FMT_URCC
			&& kpadStatus[ WIIMOTE_REMAP[ i ] ].data_format != WPAD_FMT_BALANCE_CHECKER
			/*kpadStatus[ WIIMOTE_REMAP[ i ] ].data_format == WPAD_FMT_CORE
			|| kpadStatus[ WIIMOTE_REMAP[ i ] ].data_format == WPAD_FMT_CORE_ACC
			|| kpadStatus[ WIIMOTE_REMAP[ i ] ].data_format == WPAD_FMT_CORE_ACC_DPD*/ )
		{
			if( kpadStatus[ WIIMOTE_REMAP[ i ] ].hold != 0 )
				vpadActive = false;

			u32 hold = kpadStatus[ WIIMOTE_REMAP[ i ] ].hold;

			PAD_STATE[ WIIMOTE_REMAP[ i ] ].Buttons.A = ( hold & KPAD_BUTTON_2 ) ? ButtonState_Pressed : ButtonState_Released;
			PAD_STATE[ WIIMOTE_REMAP[ i ] ].Buttons.B = ( hold & KPAD_BUTTON_1 ) ? ButtonState_Pressed : ButtonState_Released;
			PAD_STATE[ WIIMOTE_REMAP[ i ] ].Buttons.X = ( hold & KPAD_BUTTON_A ) ? ButtonState_Pressed : ButtonState_Released;
			PAD_STATE[ WIIMOTE_REMAP[ i ] ].Buttons.Y = ( 
										//kpadStatus[ i ].hold & KPAD_BUTTON_A ||
										hold & KPAD_BUTTON_MINUS ) ? ButtonState_Pressed : ButtonState_Released;

			PAD_STATE[ WIIMOTE_REMAP[ i ] ].Buttons.Start = ( hold & KPAD_BUTTON_PLUS ) ? ButtonState_Pressed : ButtonState_Released;
			
			PAD_STATE[ WIIMOTE_REMAP[ i ] ].Buttons.Back = ( hold & KPAD_BUTTON_MINUS ) ? ButtonState_Pressed : ButtonState_Released;

			PAD_STATE[ WIIMOTE_REMAP[ i ] ].DPad.Down =  ( hold & KPAD_BUTTON_LEFT  ) ? ButtonState_Pressed : ButtonState_Released;
			PAD_STATE[ WIIMOTE_REMAP[ i ] ].DPad.Left =  ( hold & KPAD_BUTTON_UP    ) ? ButtonState_Pressed : ButtonState_Released;
			PAD_STATE[ WIIMOTE_REMAP[ i ] ].DPad.Right = ( hold & KPAD_BUTTON_DOWN  ) ? ButtonState_Pressed : ButtonState_Released;
			PAD_STATE[ WIIMOTE_REMAP[ i ] ].DPad.Up =    ( hold & KPAD_BUTTON_RIGHT ) ? ButtonState_Pressed : ButtonState_Released;

			if( WIIMOTE_REMAP[ i ] == 0 )
				GLOBAL_PLAYER0_MINI_B = ( hold & KPAD_BUTTON_B ) ? ButtonState_Pressed : ButtonState_Released;

			if( GLOBAL_PLAYER0_MINI_B || PAD_STATE[ WIIMOTE_REMAP[ i ] ].Buttons.A || PAD_STATE[ WIIMOTE_REMAP[ i ] ].Buttons.B || PAD_STATE[ WIIMOTE_REMAP[ i ] ].Buttons.X || PAD_STATE[ WIIMOTE_REMAP[ i ] ].Buttons.Y )
			{
				PAD_STATE[ WIIMOTE_REMAP[ i ] ].Type = GamePadState::ControllerType_Mini;
				//if ( i == 1 ) LOG_WRITE( "Controller %d is mini.\n", i );
			}

			versionComboDown |= ( hold & ( KPAD_BUTTON_1 | KPAD_BUTTON_2 | KPAD_BUTTON_PLUS ) ) == ( KPAD_BUTTON_1 | KPAD_BUTTON_2 | KPAD_BUTTON_PLUS );
		}
		else if( kpadStatus[ WIIMOTE_REMAP[ i ] ].data_format == WPAD_FMT_URCC )
		{
			u32 hold = kpadStatus[ WIIMOTE_REMAP[ i ] ].ex_status.uc.hold;
			Vec2 lStick = kpadStatus[ WIIMOTE_REMAP[ i ] ].ex_status.uc.lstick;
			Vec2 rStick = kpadStatus[ WIIMOTE_REMAP[ i ] ].ex_status.uc.rstick;

			if( hold != 0 )
			{
				vpadActive = true;
				PAD_STATE[ WIIMOTE_REMAP[ i ] ].Type = GamePadState::ControllerType_Standard;
				//if ( i == 1 ) LOG_WRITE( "Controller %d is standard.\n", i );
			}

			PAD_STATE[ WIIMOTE_REMAP[ i ] ].Buttons.A = __max( PAD_STATE[ WIIMOTE_REMAP[ i ] ].Buttons.A, ( hold & KPAD_UC_BUTTON_A ) ? ButtonState_Pressed : ButtonState_Released );
			PAD_STATE[ WIIMOTE_REMAP[ i ] ].Buttons.B = __max( PAD_STATE[ WIIMOTE_REMAP[ i ] ].Buttons.B, ( hold & KPAD_UC_BUTTON_B ) ? ButtonState_Pressed : ButtonState_Released );
			PAD_STATE[ WIIMOTE_REMAP[ i ] ].Buttons.Y = __max( PAD_STATE[ WIIMOTE_REMAP[ i ] ].Buttons.Y, ( hold & KPAD_UC_BUTTON_X ) ? ButtonState_Pressed : ButtonState_Released );
			PAD_STATE[ WIIMOTE_REMAP[ i ] ].Buttons.X = __max( PAD_STATE[ WIIMOTE_REMAP[ i ] ].Buttons.X, ( hold & KPAD_UC_BUTTON_Y ) ? ButtonState_Pressed : ButtonState_Released );

			PAD_STATE[ WIIMOTE_REMAP[ i ] ].Buttons.LeftShoulder = __max( PAD_STATE[ WIIMOTE_REMAP[ i ] ].Buttons.LeftShoulder, ( hold & KPAD_UC_BUTTON_L ) ? ButtonState_Pressed : ButtonState_Released );
			PAD_STATE[ WIIMOTE_REMAP[ i ] ].Buttons.RightShoulder = __max( PAD_STATE[ WIIMOTE_REMAP[ i ] ].Buttons.RightShoulder, ( hold & KPAD_UC_BUTTON_R ) ? ButtonState_Pressed : ButtonState_Released );
			PAD_STATE[ WIIMOTE_REMAP[ i ] ].Buttons.Start = __max( PAD_STATE[ WIIMOTE_REMAP[ i ] ].Buttons.Start, ( hold & KPAD_UC_BUTTON_PLUS ) ? ButtonState_Pressed : ButtonState_Released );
			PAD_STATE[ WIIMOTE_REMAP[ i ] ].Buttons.Back = __max( PAD_STATE[ WIIMOTE_REMAP[ i ] ].Buttons.Back, ( hold & KPAD_UC_BUTTON_MINUS ) ? ButtonState_Pressed : ButtonState_Released );

			PAD_STATE[ WIIMOTE_REMAP[ i ] ].DPad.Down = __max( PAD_STATE[ WIIMOTE_REMAP[ i ] ].DPad.Down, ( hold & KPAD_UC_BUTTON_DOWN ) ? ButtonState_Pressed : ButtonState_Released );
			PAD_STATE[ WIIMOTE_REMAP[ i ] ].DPad.Left = __max( PAD_STATE[ WIIMOTE_REMAP[ i ] ].DPad.Left, ( hold & KPAD_UC_BUTTON_LEFT ) ? ButtonState_Pressed : ButtonState_Released );
			PAD_STATE[ WIIMOTE_REMAP[ i ] ].DPad.Right = __max( PAD_STATE[ WIIMOTE_REMAP[ i ] ].DPad.Right, ( hold & KPAD_UC_BUTTON_RIGHT ) ? ButtonState_Pressed : ButtonState_Released );
			PAD_STATE[ WIIMOTE_REMAP[ i ] ].DPad.Up = __max( PAD_STATE[ WIIMOTE_REMAP[ i ] ].DPad.Up, ( hold & KPAD_UC_BUTTON_UP ) ? ButtonState_Pressed : ButtonState_Released );

			PAD_STATE[ WIIMOTE_REMAP[ i ] ].Triggers.Left =  ( hold & KPAD_UC_TRIGGER_ZL ) / KPAD_UC_TRIGGER_ZL ? ButtonState_Pressed : ButtonState_Released;
			PAD_STATE[ WIIMOTE_REMAP[ i ] ].Triggers.Right = ( hold & KPAD_UC_TRIGGER_ZR ) / KPAD_UC_TRIGGER_ZR ? ButtonState_Pressed : ButtonState_Released;

			PAD_STATE[ WIIMOTE_REMAP[ i ] ].ThumbSticks.Left = Vector2( lStick.x, lStick.y );
			PAD_STATE[ WIIMOTE_REMAP[ i ] ].ThumbSticks.Right = Vector2( rStick.x, rStick.y );

			if( 0 == WIIMOTE_REMAP[ i ] )
				channel0ThumbsticksWritten = true;

			versionComboDown |= ( hold & ( KPAD_UC_BUTTON_A | KPAD_UC_BUTTON_B | KPAD_UC_BUTTON_PLUS ) ) == ( KPAD_UC_BUTTON_A | KPAD_UC_BUTTON_B | KPAD_UC_BUTTON_PLUS );
		}
	}

	// Update gamepad.
	PADStatus status[ PAD_MAX_CONTROLLERS ];
	memset( status, 0, sizeof( status ) );
	PADRead( status );
	static Vector2 textPos( 0, 0 );

	for( int i = 0; i < PAD_MAX_CONTROLLERS; ++i )
	{
		if( status[ i ].err == PAD_ERR_NO_CONTROLLER )
		{
			continue;
		}

		if( status[ i ].err == PAD_ERR_NOT_READY
			|| status[ i ].err == PAD_ERR_TRANSFER )
		{
			continue;
		}

		anythingElseConnected = true;
		PAD_STATE[ i ].IsConnected |= true;

		// Mapping is inverse of XBox.
		PAD_STATE[ i ].Buttons.A = __max( PAD_STATE[ i ].Buttons.A, ( status[ i ].button & PAD_BUTTON_A ) ? ButtonState_Pressed : ButtonState_Released );
		PAD_STATE[ i ].Buttons.B = __max( PAD_STATE[ i ].Buttons.B, ( status[ i ].button & PAD_BUTTON_B ) ? ButtonState_Pressed : ButtonState_Released );
		PAD_STATE[ i ].Buttons.Y = __max( PAD_STATE[ i ].Buttons.Y, ( status[ i ].button & PAD_BUTTON_X ) ? ButtonState_Pressed : ButtonState_Released );
		PAD_STATE[ i ].Buttons.X = __max( PAD_STATE[ i ].Buttons.X, ( status[ i ].button & PAD_BUTTON_Y ) ? ButtonState_Pressed : ButtonState_Released );

		PAD_STATE[ i ].Buttons.LeftShoulder = __max( PAD_STATE[ i ].Buttons.LeftShoulder, ( status[ i ].button & PAD_BUTTON_L ) ? ButtonState_Pressed : ButtonState_Released );
		PAD_STATE[ i ].Buttons.RightShoulder = __max( PAD_STATE[ i ].Buttons.RightShoulder, ( status[ i ].button & PAD_BUTTON_R ) ? ButtonState_Pressed : ButtonState_Released );
		PAD_STATE[ i ].Buttons.Start = __max( PAD_STATE[ i ].Buttons.Start, ( status[ i ].button & PAD_BUTTON_START ) ? ButtonState_Pressed : ButtonState_Released );
		//PAD_STATE[ i ].Buttons.Back = __max( PAD_STATE[ i ].Buttons.Back, ( status[ i ].button & PAD_BUTTON_MINUS ) ? ButtonState_Pressed : ButtonState_Released );

		PAD_STATE[ i ].DPad.Down = __max( PAD_STATE[ i ].DPad.Down, ( status[ i ].button & PAD_BUTTON_DOWN ) ? ButtonState_Pressed : ButtonState_Released );
		PAD_STATE[ i ].DPad.Left = __max( PAD_STATE[ i ].DPad.Left, ( status[ i ].button & PAD_BUTTON_LEFT ) ? ButtonState_Pressed : ButtonState_Released );
		PAD_STATE[ i ].DPad.Right = __max( PAD_STATE[ i ].DPad.Right, ( status[ i ].button & PAD_BUTTON_RIGHT ) ? ButtonState_Pressed : ButtonState_Released );
		PAD_STATE[ i ].DPad.Up = __max( PAD_STATE[ i ].DPad.Up, ( status[ i ].button & PAD_BUTTON_UP ) ? ButtonState_Pressed : ButtonState_Released );

		if( i == 0 && !channel0ThumbsticksWritten )
		{
			PAD_STATE[ i ].Triggers.Left = status[ i ].triggerLeft / 255.f;
			PAD_STATE[ i ].Triggers.Right = status[ i ].triggerRight / 255.f;

			PAD_STATE[ i ].ThumbSticks.Left = Vector2( status[ i ].stickX / 128.f, status[ i ].stickY / 128.f );
			PAD_STATE[ i ].ThumbSticks.Right = Vector2( status[ i ].substickX / 128.f, status[ i ].substickY / 128.f );
		}
	}

	// Update DRC.
	s32 error;
	for( int i = 0; i < 1/*VPAD_MAX_CONTROLLERS*/; ++i )
	{
		readLength = VPADRead( VPADBASE_CHAN0 + i, &vpadStatus, 1, &error );

		bool wasConnected = PAD_STATE[ i ].IsConnected;

		bool isVpadConnectedNow = error != VPAD_READ_ERR_NO_CONTROLLER;

		PAD_STATE[ i ].IsConnected = isVpadConnectedNow;
		if( !PAD_STATE[ i ].IsConnected )
			PAD_STATE[ i ].IsConnected = wasConnected;
		
		GLOBAL_CONNECTION_STATUS[ 0 ] = isVpadConnectedNow;

		// If the vpad was connected but is no longer.
		/*if( vpadConnected && !isVpadConnectedNow )
		{
			DisconnectController( 0 );
		}
		else if( !vpadConnected && isVpadConnectedNow )
		{
			ReconnectController( 0 );
		}*/
		vpadConnected = isVpadConnectedNow;

		if( !isVpadConnectedNow )
			continue;

		if( error == VPAD_READ_ERR_NONE )
		{
			if( vpadStatus.hold != 0 )
			{
				vpadActive = true;
				PAD_STATE[ i ].Type = GamePadState::ControllerType_Standard;
			}

			// Mapping is inverse of XBox.
			PAD_STATE[ i ].Buttons.A = __max( PAD_STATE[ i ].Buttons.A, vpadStatus.hold & VPAD_BUTTON_A ? ButtonState_Pressed : ButtonState_Released );
			PAD_STATE[ i ].Buttons.B = __max( PAD_STATE[ i ].Buttons.B, vpadStatus.hold & VPAD_BUTTON_B ? ButtonState_Pressed : ButtonState_Released );
			PAD_STATE[ i ].Buttons.Y = __max( PAD_STATE[ i ].Buttons.Y, vpadStatus.hold & VPAD_BUTTON_X ? ButtonState_Pressed : ButtonState_Released );
			PAD_STATE[ i ].Buttons.X = __max( PAD_STATE[ i ].Buttons.X, vpadStatus.hold & VPAD_BUTTON_Y ? ButtonState_Pressed : ButtonState_Released );

			PAD_STATE[ i ].Buttons.LeftShoulder = __max( PAD_STATE[ i ].Buttons.LeftShoulder, vpadStatus.hold & VPAD_BUTTON_L ? ButtonState_Pressed : ButtonState_Released );
			PAD_STATE[ i ].Buttons.RightShoulder = __max( PAD_STATE[ i ].Buttons.RightShoulder, vpadStatus.hold & VPAD_BUTTON_R ? ButtonState_Pressed : ButtonState_Released );
			PAD_STATE[ i ].Buttons.Start = __max( PAD_STATE[ i ].Buttons.Start, vpadStatus.hold & VPAD_BUTTON_PLUS ? ButtonState_Pressed : ButtonState_Released );
			PAD_STATE[ i ].Buttons.Back = __max( PAD_STATE[ i ].Buttons.Back, ( vpadStatus.hold & VPAD_BUTTON_MINUS ) ? ButtonState_Pressed : ButtonState_Released );


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
	
			const float threshold = 0.1f * 0.1f;

			float x = vpadStatus.lStick.x;
			float y = vpadStatus.lStick.y;
			float magnitude = x * x + y * y;
			if( magnitude > threshold )
				PAD_STATE[ i ].ThumbSticks.Left = Vector2( vpadStatus.lStick.x, vpadStatus.lStick.y );
			
			x = vpadStatus.rStick.x;
			y = vpadStatus.rStick.y;
			magnitude = x * x + y * y;
			if( magnitude > threshold )
				PAD_STATE[ i ].ThumbSticks.Right = Vector2( vpadStatus.rStick.x, vpadStatus.rStick.y );

			if( i == 0 && !channel0ThumbsticksWritten )
			{
				PAD_STATE[ i ].Triggers.Left =  ( vpadStatus.hold & VPAD_TRIGGER_ZL ) / VPAD_TRIGGER_ZL ? ButtonState_Pressed : ButtonState_Released;
				PAD_STATE[ i ].Triggers.Right = ( vpadStatus.hold & VPAD_TRIGGER_ZR ) / VPAD_TRIGGER_ZR ? ButtonState_Pressed : ButtonState_Released;

				PAD_STATE[ i ].ThumbSticks.Left = Vector2( vpadStatus.lStick.x, vpadStatus.lStick.y );
				PAD_STATE[ i ].ThumbSticks.Right = Vector2( vpadStatus.lStick.x, vpadStatus.lStick.y );
			}

			
			versionComboDown |= ( vpadStatus.hold & ( VPAD_BUTTON_A | VPAD_BUTTON_B | VPAD_BUTTON_PLUS ) ) == ( VPAD_BUTTON_A | VPAD_BUTTON_B | VPAD_BUTTON_PLUS );
		}
	}

	/*static int versionCounter = 0;

	if( versionComboDown )
		versionCounter++;
	else
		versionCounter = 0;*/

	GLOBAL_SHOW_VERSION = versionComboDown;
	GLOBAL_PLAYER0_DOWN = PAD_STATE[ 0 ].DPad.Down == ButtonState_Pressed;

	/*if( versionCounter >= 60 )
		GLOBAL_SHOW_VERSION = true;*/
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
