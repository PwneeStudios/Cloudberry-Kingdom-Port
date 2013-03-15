#include <Input/GamePad.h>

#include <cafe/pad.h>
#include <cafe/vpad.h>
#include <cafe/wenc.h>
//#include <cafe/pads/wpad/wpad.h>
#include <cafe/pads/kpad/kpad.h>

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

enum MyControllerTypes
{
	Who_NOONE,
	Who_VPAD,
	Who_KPAD
};

int WhoIsDisconnected = Who_NOONE;

static void ConnectCallback( s32 chan, s32 reason )
{
	if( reason >= 0 )
	{
		u32 dataFormat = WPADGetDataFormat( chan );
		/*if( dataFormat != WPAD_FMT_URCC )
		{
			dataFormat = WPAD_FMT_CORE;
			kpadIsURCC[ chan ] = false;
		}
		else
			kpadIsURCC[ chan ] = true;
		*/
		//WPADSetDataFormat( chan, dataFormat );
		WPADControlSpeaker( chan, WPAD_SPEAKER_OFF, NULL );
		WPADControlDpd( chan, WPAD_DPD_OFF, NULL );
		kpadIsConnected[ chan ] = true;
		LOG.Write( "Gamepad connected, format = %d\n", dataFormat );
	}
	else if( reason == WPAD_ERR_NO_CONTROLLER )
	{
		WhoIsDisconnected = Who_KPAD;

		kpadIsConnected[ chan ] = false;
		LOG.Write( "Gamepad disconnected\n" );
	}
}

/*int kpadConnectHistory[ WPAD_MAX_CONTROLLERS ];
int vpadConnectHistory;
const int disconnectThreshold = 30;*/

void GamePad::Initialize()
{
	PADInit();
	KPADInit();
	WPADEnableURCC( TRUE );

	for( int i = 0; i < WPAD_MAX_CONTROLLERS; ++i )
		KPADSetConnectCallback( i, ConnectCallback );
	/*WPADInit();

	for( int i = 0; i < WPAD_MAX_CONTROLLERS; i++ )
		WPADSetConnectCallback( i, ConnectCallback );*/

	memset( &vpadStatus, 0, sizeof( VPADStatus ) );
	vpadConnected = true;
	readLength = 0;

	// FIXME: Should not always be active.
	vpadActive = true;

	memset( kpadStatus, 0, sizeof( kpadStatus ) );
	memset( kpadReadLength, 0, sizeof( kpadReadLength ) );
	memset( kpadIsConnected, 0, sizeof( kpadIsConnected ) );
	memset( kpadIsURCC, 0, sizeof( kpadIsURCC ) );
	/*for( int i = 0; i < WPAD_MAX_CONTROLLERS; ++i )
		kpadConnectHistory[ i ] = disconnectThreshold;
	vpadConnectHistory = disconnectThreshold;*/
}

void GamePad::Update()
{
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

	// Update Wiimotes.
	for( int i = 0; i < WPAD_MAX_CONTROLLERS; i++ )
	{
		kpadReadLength[ i ] = KPADRead( i, &kpadStatus[ i ], 1 );

		PAD_STATE[ i ].IsConnected = kpadIsConnected[ i ];// kpadConnectHistory[ i ] < disconnectThreshold;
		
		if( !kpadIsConnected[ i ] )
			continue;
		/*if( kpadReadLength[ i ] == 0 )
		{
			++kpadConnectHistory[ i ];
			continue;
		}*/

		anythingElseConnected = true;

		if( kpadStatus[ i ].wpad_err == WPAD_ERR_CORRUPTED )
			continue;
		
		if( kpadStatus[ i ].data_format == WPAD_FMT_CORE
			|| kpadStatus[ i ].data_format == WPAD_FMT_CORE_ACC
			|| kpadStatus[ i ].data_format == WPAD_FMT_CORE_ACC_DPD )
		{
			if( kpadStatus[ i ].hold != 0 )
				vpadActive = false;

			PAD_STATE[ i ].Buttons.A = ( kpadStatus[ i ].hold & KPAD_BUTTON_2 ) ? ButtonState_Pressed : ButtonState_Released;
			PAD_STATE[ i ].Buttons.B = ( kpadStatus[ i ].hold & KPAD_BUTTON_1 ) ? ButtonState_Pressed : ButtonState_Released;
			PAD_STATE[ i ].Buttons.X = ( kpadStatus[ i ].hold & KPAD_BUTTON_A ) ? ButtonState_Pressed : ButtonState_Released;
			PAD_STATE[ i ].Buttons.Y = ( 
										//kpadStatus[ i ].hold & KPAD_BUTTON_A ||
										kpadStatus[ i ].hold & KPAD_BUTTON_MINUS ) ? ButtonState_Pressed : ButtonState_Released;

			PAD_STATE[ i ].Buttons.Start = ( kpadStatus[ i ].hold & KPAD_BUTTON_PLUS ) ? ButtonState_Pressed : ButtonState_Released;

			PAD_STATE[ i ].DPad.Down =  ( kpadStatus[ i ].hold & KPAD_BUTTON_LEFT  ) ? ButtonState_Pressed : ButtonState_Released;
			PAD_STATE[ i ].DPad.Left =  ( kpadStatus[ i ].hold & KPAD_BUTTON_UP    ) ? ButtonState_Pressed : ButtonState_Released;
			PAD_STATE[ i ].DPad.Right = ( kpadStatus[ i ].hold & KPAD_BUTTON_DOWN  ) ? ButtonState_Pressed : ButtonState_Released;
			PAD_STATE[ i ].DPad.Up =    ( kpadStatus[ i ].hold & KPAD_BUTTON_RIGHT ) ? ButtonState_Pressed : ButtonState_Released;

			if( PAD_STATE[ i ].Buttons.A || PAD_STATE[ i ].Buttons.B || PAD_STATE[ i ].Buttons.X || PAD_STATE[ i ].Buttons.Y )
			{
				PAD_STATE[ i ].Type = GamePadState::ControllerType_Mini;
				if ( i == 1 ) LOG.Write( "Controller %d is mini.\n", i );
			}
		}
		else if( kpadStatus[ i ].data_format == WPAD_FMT_URCC )
		{
			u32 hold = kpadStatus[ i ].ex_status.uc.hold;
			Vec2 lStick = kpadStatus[ i ].ex_status.uc.lstick;
			Vec2 rStick = kpadStatus[ i ].ex_status.uc.rstick;

			if( hold != 0 )
			{
				vpadActive = true;
				PAD_STATE[ i ].Type = GamePadState::ControllerType_Standard;
				if ( i == 1 ) LOG.Write( "Controller %d is standard.\n", i );
			}

			PAD_STATE[ i ].Buttons.A = __max( PAD_STATE[ i ].Buttons.A, ( hold & KPAD_UC_BUTTON_A ) ? ButtonState_Pressed : ButtonState_Released );
			PAD_STATE[ i ].Buttons.B = __max( PAD_STATE[ i ].Buttons.B, ( hold & KPAD_UC_BUTTON_B ) ? ButtonState_Pressed : ButtonState_Released );
			PAD_STATE[ i ].Buttons.Y = __max( PAD_STATE[ i ].Buttons.Y, ( hold & KPAD_UC_BUTTON_X ) ? ButtonState_Pressed : ButtonState_Released );
			PAD_STATE[ i ].Buttons.X = __max( PAD_STATE[ i ].Buttons.X, ( hold & KPAD_UC_BUTTON_Y ) ? ButtonState_Pressed : ButtonState_Released );

			PAD_STATE[ i ].Buttons.LeftShoulder = __max( PAD_STATE[ i ].Buttons.LeftShoulder, ( hold & KPAD_UC_BUTTON_L ) ? ButtonState_Pressed : ButtonState_Released );
			PAD_STATE[ i ].Buttons.RightShoulder = __max( PAD_STATE[ i ].Buttons.RightShoulder, ( hold & KPAD_UC_BUTTON_R ) ? ButtonState_Pressed : ButtonState_Released );
			PAD_STATE[ i ].Buttons.Start = __max( PAD_STATE[ i ].Buttons.Start, ( hold & KPAD_UC_BUTTON_PLUS ) ? ButtonState_Pressed : ButtonState_Released );

			PAD_STATE[ i ].DPad.Down = __max( PAD_STATE[ i ].DPad.Down, ( hold & KPAD_UC_BUTTON_DOWN ) ? ButtonState_Pressed : ButtonState_Released );
			PAD_STATE[ i ].DPad.Left = __max( PAD_STATE[ i ].DPad.Left, ( hold & KPAD_UC_BUTTON_LEFT ) ? ButtonState_Pressed : ButtonState_Released );
			PAD_STATE[ i ].DPad.Right = __max( PAD_STATE[ i ].DPad.Right, ( hold & KPAD_UC_BUTTON_RIGHT ) ? ButtonState_Pressed : ButtonState_Released );
			PAD_STATE[ i ].DPad.Up = __max( PAD_STATE[ i ].DPad.Up, ( hold & KPAD_UC_BUTTON_UP ) ? ButtonState_Pressed : ButtonState_Released );

			PAD_STATE[ i ].Triggers.Left =  ( hold & KPAD_UC_TRIGGER_ZL ) / KPAD_UC_TRIGGER_ZL ? ButtonState_Pressed : ButtonState_Released;
			PAD_STATE[ i ].Triggers.Right = ( hold & KPAD_UC_TRIGGER_ZR ) / KPAD_UC_TRIGGER_ZR ? ButtonState_Pressed : ButtonState_Released;

			PAD_STATE[ i ].ThumbSticks.Left = Vector2( lStick.x, lStick.y );
			PAD_STATE[ i ].ThumbSticks.Right = Vector2( rStick.x, rStick.y );

			if( 0 == i )
				channel0ThumbsticksWritten = true;
		}

		LOG.Write( "Controler types: 0 = %d, 1 = %d, 2 = %d, 3 = %d\n", PAD_STATE[ 0 ].Type, PAD_STATE[ 1 ].Type, PAD_STATE[ 2 ].Type, PAD_STATE[ 3 ].Type );
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

		PAD_STATE[ i ].DPad.Down = __max( PAD_STATE[ i ].DPad.Down, ( status[ i ].button & PAD_BUTTON_DOWN ) ? ButtonState_Pressed : ButtonState_Released );
		PAD_STATE[ i ].DPad.Left = __max( PAD_STATE[ i ].DPad.Left, ( status[ i ].button & PAD_BUTTON_LEFT ) ? ButtonState_Pressed : ButtonState_Released );
		PAD_STATE[ i ].DPad.Right = __max( PAD_STATE[ i ].DPad.Right, ( status[ i ].button & PAD_BUTTON_RIGHT ) ? ButtonState_Pressed : ButtonState_Released );
		PAD_STATE[ i ].DPad.Up = __max( PAD_STATE[ i ].DPad.Up, ( status[ i ].button & PAD_BUTTON_UP ) ? ButtonState_Pressed : ButtonState_Released );
		/*PAD_STATE[ i ].Buttons.LeftStick = ( status[ i ].button & PAD_BUTTON_START ) ? ButtonState_Pressed : ButtonState_Released;
		PAD_STATE[ i ].Buttons.RightStick = ( status[ i ].button & PAD_BUTTON_START ) ? ButtonState_Pressed : ButtonState_Released;
		PAD_STATE[ i ].Buttons.Back = ( status[ i ].button & PAD_BUTTON_START ) ? ButtonState_Pressed : ButtonState_Released;
		PAD_STATE[ i ].Buttons.BigButton = ( status[ i ].button & PAD_BUTTON_MENU ) ? ButtonState_Pressed : ButtonState_Released;*/

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
		PAD_STATE[ i ].IsConnected = true;
		if( error == VPAD_READ_ERR_NO_CONTROLLER )
			PAD_STATE[ i ].IsConnected = wasConnected;

		if( error == VPAD_READ_ERR_NONE )
		{
			vpadConnected = true;

			if( vpadStatus.hold != 0 )
			{
				vpadActive = true;
				PAD_STATE[ i ].Type = GamePadState::ControllerType_Standard;
				if ( i == 1 ) LOG.Write( "Controller %d is standard.\n", i );
			}

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

			if( i == 0 && !channel0ThumbsticksWritten )
			{
				PAD_STATE[ i ].Triggers.Left =  ( vpadStatus.hold & VPAD_TRIGGER_ZL ) / VPAD_TRIGGER_ZL ? ButtonState_Pressed : ButtonState_Released;
				PAD_STATE[ i ].Triggers.Right = ( vpadStatus.hold & VPAD_TRIGGER_ZR ) / VPAD_TRIGGER_ZR ? ButtonState_Pressed : ButtonState_Released;

				PAD_STATE[ i ].ThumbSticks.Left = Vector2( vpadStatus.lStick.x, vpadStatus.lStick.y );
				PAD_STATE[ i ].ThumbSticks.Right = Vector2( vpadStatus.lStick.x, vpadStatus.lStick.y );
			}
		}
		else if( error == VPAD_READ_ERR_NO_CONTROLLER && vpadConnected == true/* && !anythingElseConnected*/ )
		{
			// Only show error if nothing is connected to the WiiU.
			vpadConnected = false;

			WhoIsDisconnected = Who_VPAD;

			// Unable to communicate with the WiiU gamepad.
			//DisplayError( ErrorType( 1650101 ) );
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
