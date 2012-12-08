#include <global_header.h>

namespace CloudberryKingdom
{

bool KeyboardExtension::Freeze = false;

	void KeyboardExtension::FreezeInput()
	{
		Freeze = true;
	}

	void KeyboardExtension::UnfreezeInput()
	{
		Freeze = false;
	}

	bool KeyboardExtension::IsKeyDownCustom( KeyboardState &keyboard, Keys key )
	{
		if ( Freeze )
			return false;

		return keyboard.IsKeyDown( key );
	}

	int ButtonStatistics::DownCount( ControllerButtons button )
	{
		return _DownCount[ static_cast<int>( button ) ];
	}

	void ButtonStatistics::IncrCount( ControllerButtons button, bool Incr )
	{
		if ( Incr )
			IncrCount( button );
		else
			SetCount( button, 0 );
	}

	void ButtonStatistics::IncrCount( ControllerButtons button )
	{
		_DownCount[ static_cast<int>( button ) ]++;
	}

	void ButtonStatistics::SetCount( ControllerButtons button, int count )
	{
		_DownCount[ static_cast<int>( button ) ] = count;
	}

	void ButtonStatistics::InitializeInstanceFields()
	{
		_DownCount = std::vector<int>( ControllerButtons_LENGTH );
	}

std::vector<std::shared_ptr<ButtonStatistics> > ButtonStats::Controller;
std::shared_ptr<ButtonStatistics> ButtonStats::All = 0;

	void ButtonStats::Init()
	{
		if ( Controller.empty() )
		{
			Controller = std::vector<std::shared_ptr<ButtonStatistics> >( 4 );
			All = std::make_shared<ButtonStatistics>();

			for ( int i = 0; i < 4; i++ )
				Controller[ i ] = std::make_shared<ButtonStatistics>();
		}
	}

	void ButtonStats::Update()
	{
		Init();

		bool Incr = false;
		for ( int i = 0; i < 4; i++ )
		{
			if ( Tools::GamepadState[ i ].Buttons.A == ButtonState_Pressed )
			{
				Controller[ i ]->IncrCount( ControllerButtons_A );
				Incr = true;
			}
			else
				Controller[ i ]->SetCount( ControllerButtons_A, 0 );

			Vector2 dir = ButtonCheck::GetDir( i );
			Controller[ i ]->IncrCount( ControllerButtons_RIGHT, dir.X > 0.7f );
			Controller[ i ]->IncrCount( ControllerButtons_LEFT, dir.X < -0.7f );
			Controller[ i ]->IncrCount( ControllerButtons_UP, dir.Y > 0.7f );
			Controller[ i ]->IncrCount( ControllerButtons_DOWN, dir.Y < -0.7f );
		}

		if ( Incr )
			All->IncrCount( ControllerButtons_A );
		else
			All->SetCount( ControllerButtons_A, 0 );

		const ControllerButtons tempVector[] = { ControllerButtons_LEFT, ControllerButtons_RIGHT, ControllerButtons_UP, ControllerButtons_DOWN };
		std::vector<ControllerButtons> buttons = std::vector<ControllerButtons>( tempVector, tempVector + sizeof( tempVector ) / sizeof( tempVector[ 0 ] ) );
		for ( std::vector<ControllerButtons>::const_iterator button = buttons.begin(); button != buttons.end(); ++button )
		{
			Incr = false;
			for ( int i = 0; i < 4; i++ )
				if ( Controller[ i ]->DownCount( *button ) > 0 )
					Incr = true;

			All->IncrCount( *button, Incr );
		}
	}

	void ButtonClass::Set( Keys key )
	{
		KeyboardKey = key;
		IsKeyboard = true;
	}

	void ButtonClass::Set( ControllerButtons key )
	{
		ControllerButton = key;
		IsKeyboard = false;
	}

	void ButtonClass::InitializeInstanceFields()
	{
		ControllerButton = ControllerButtons_NONE;
		KeyboardKey = Keys_None;
		IsKeyboard = true;
	}

bool ButtonCheck::MouseInUse = false;
bool ButtonCheck::PrevMouseInUse = false;

	void ButtonCheck::UpdateControllerAndKeyboard_StartOfStep()
	{
		// Update controller/keyboard states
	#if defined(WINDOWS)
		Tools::Keyboard = Keyboard::GetState();

		// FIXME: These are all value types.
		//if ( Tools::PrevKeyboard == 0 )
			Tools::PrevKeyboard = Tools::Keyboard;

		Tools::Mouse = Mouse::GetState();
	#endif
		Tools::GamepadState[ 0 ] = GamePad::GetState( PlayerIndex_One );
		Tools::GamepadState[ 1 ] = GamePad::GetState( PlayerIndex_Two );
		Tools::GamepadState[ 2 ] = GamePad::GetState( PlayerIndex_Three );
		Tools::GamepadState[ 3 ] = GamePad::GetState( PlayerIndex_Four );

		ButtonStats::Update();

		Tools::UpdateVibrations();

	#if defined(PC_VERSION)
		UpdateMouseUse();
	#endif
	}

	void ButtonCheck::UpdateControllerAndKeyboard_EndOfStep( ResolutionGroup Resolution )
	{
		// Determine if the mouse is in the window or not.
		Tools::MouseInWindow = Tools::Mouse.X > 0 && Tools::Mouse.X < Resolution.Backbuffer.X && Tools::Mouse.Y > 0 && Tools::Mouse.Y < Resolution.Backbuffer.Y;

		// Calculate how much user has scrolled the mouse wheel and moved the mouse.
		Tools::DeltaScroll = Tools::Mouse.ScrollWheelValue - Tools::PrevMouse.ScrollWheelValue;
		if ( Tools::CurLevel != 0 )
		{
			Tools::DeltaMouse = Tools::ToWorldCoordinates( Vector2( static_cast<float>( Tools::Mouse.X ), static_cast<float>( Tools::Mouse.Y ) ), Tools::CurLevel->getMainCamera() )
				- Tools::ToWorldCoordinates( Vector2( static_cast<float>( Tools::PrevMouse.X ), static_cast<float>( Tools::PrevMouse.Y ) ), Tools::CurLevel->getMainCamera());
		}
		Tools::RawDeltaMouse = Vector2( static_cast<float>( Tools::Mouse.X ), static_cast<float>( Tools::Mouse.Y ) )
			- Vector2( static_cast<float>( Tools::PrevMouse.X ), static_cast<float>( Tools::PrevMouse.Y ) );

		Tools::PrevKeyboard = Tools::Keyboard;
		Tools::PrevMouse = Tools::Mouse;

		// Store the previous states of the Xbox controllers.
		for ( int i = 0; i < 4; i++ )
		{
			// FIXME: All of these are value types.
			//if ( Tools::PrevGamepadState[ i ] != 0 )
				Tools::PrevGamepadState[ i ] = Tools::GamepadState[ i ];
		}
	}

#if defined(PC_VERSION)
	void ButtonCheck::UpdateMouseUse()
	{
	#if defined(PC_VERSION)
		if ( ButtonCheck::AnyKeyboardKey() || (PlayerManager::Players.size() > 0 && PlayerManager::getPlayer() != 0 && ButtonCheck::GetMaxDir(false).Length() > 0.3f) )
	#else
		if ( ButtonCheck::AnyKeyboardKey() || (PlayerManager::Players.size() > 0 && ButtonCheck::GetMaxDir(true).Length() > ::3) )
	#endif
			MouseInUse = false;

		if ( Tools::DeltaMouse != Vector2() || Tools::Mouse.LeftButton == ButtonState_Pressed || Tools::Mouse.RightButton == ButtonState_Pressed )
			MouseInUse = true;

		PrevMouseInUse = MouseInUse;
	}
#endif

	void ButtonCheck::KillSecondary()
	{
		Help_KeyboardKey->Set( Keys_None );
		Quickspawn_KeyboardKey->Set( Keys_None );
		Start_Secondary = Go_Secondary = Back_Secondary = ReplayPrev_Secondary = ReplayNext_Secondary = SlowMoToggle_Secondary = Left_Secondary = Right_Secondary = Up_Secondary = Down_Secondary = Keys_None;
	}

std::shared_ptr<ButtonClass> ButtonCheck::Quickspawn_KeyboardKey = std::make_shared<ButtonClass>(), ButtonCheck::Help_KeyboardKey = std::make_shared<ButtonClass>(), ButtonCheck::QuickReset_KeyboardKey = std::make_shared<ButtonClass>();
Keys ButtonCheck::Start_Secondary = Keys_None, ButtonCheck::Go_Secondary = Keys_None, ButtonCheck::Back_Secondary = Keys_None, ButtonCheck::ReplayPrev_Secondary = Keys_None, ButtonCheck::ReplayNext_Secondary = Keys_None, ButtonCheck::ReplayToggle_Secondary = Keys_None, ButtonCheck::SlowMoToggle_Secondary = Keys_None, ButtonCheck::Left_Secondary = Keys_None, ButtonCheck::Right_Secondary = Keys_None, ButtonCheck::Up_Secondary = Keys_None, ButtonCheck::Down_Secondary = Keys_None;

	void ButtonCheck::Reset()
	{
		QuickReset_KeyboardKey->Set( Keys_F );
		Quickspawn_KeyboardKey->Set( Keys_Space );
		Help_KeyboardKey->Set( Keys_Enter );

		Start_Secondary = Keys_None;
		Go_Secondary = Keys_None;
		Back_Secondary = Keys_None;

		ReplayPrev_Secondary = Keys_N;
		ReplayNext_Secondary = Keys_M;
		ReplayToggle_Secondary = Keys_L;

		SlowMoToggle_Secondary = Keys_C;

		Left_Secondary = Keys_A;
		Right_Secondary = Keys_D;
		Up_Secondary = Keys_W;
		Down_Secondary = Keys_S;
	}

float ButtonCheck::ThresholdSensitivity = .715f;

	int ButtonCheck::Direction( Vector2 Dir )
	{
		if ( Dir.Length() < .25f )
			return -1;
		if ( Dir.Y < Dir.X && Dir.Y > -Dir.X )
			return 0;
		if ( Dir.Y > Dir.X && Dir.Y > -Dir.X )
			return 1;
		if ( Dir.Y < -Dir.X && Dir.Y > Dir.X )
			return 2;
		if ( Dir.Y < Dir.X && Dir.Y < -Dir.X )
			return 3;
		return -1;
	}

	Vector2 ButtonCheck::GetDir( int Control )
	{
		return GetDir( Control, true );
	}

	Vector2 ButtonCheck::GetDir( int Control, bool Threshold )
	{
		// Get joystick direction
		Vector2 Dir = ButtonCheck::State( ControllerButtons_DPAD, Control ).Dir;

		// Get d-pad direction
		Vector2 HoldDir = ButtonCheck::State( ControllerButtons_LJ, Control ).Dir;

		// Take bigger magnitude of the two
		if ( abs( HoldDir.X ) > abs( Dir.X ) )
			Dir.X = HoldDir.X;
		if ( abs( HoldDir.Y ) > abs( Dir.Y ) )
			Dir.Y = HoldDir.Y;

		// Make sure we exceed the threshold
		// This prevents overly sensitive joysticks from misbehaving.
		if ( Threshold )
		{
			float Sensitivty = ButtonCheck::ThresholdSensitivity;
			if ( abs( Dir.X ) < Sensitivty )
				Dir.X = 0;
			if ( abs( Dir.Y ) < Sensitivty )
				Dir.Y = 0;
		}

		return Dir;
	}

	Vector2 ButtonCheck::GetMaxDir()
	{
		return GetMaxDir( false );
	}

	Vector2 ButtonCheck::GetMaxDir( int Control )
	{
		return GetMaxDir( Control == -1 );
	}

	Vector2 ButtonCheck::GetMaxDir( bool MustExist )
	{
		if ( PlayerManager::Players.empty() || PlayerManager::Players[ 0 ] == 0 || PlayerManager::Players[ 1 ] == 0 || PlayerManager::Players[ 2 ] == 0 || PlayerManager::Players[ 3 ] == 0 )
			return Vector2();

		Vector2 Dir = Vector2();
		for ( int i = 0; i < 4; i++ )
		{
			if ( PlayerManager::Get( i )->Exists || !MustExist )
			{
				Vector2 HoldDir = ButtonCheck::State( ControllerButtons_LJ, i ).Dir;
				if ( abs( HoldDir.X ) > abs( Dir.X ) )
					Dir.X = HoldDir.X;
				if ( abs( HoldDir.Y ) > abs( Dir.Y ) )
					Dir.Y = HoldDir.Y;

				HoldDir = ButtonCheck::State( ControllerButtons_DPAD, i ).Dir;
				if ( abs( HoldDir.X ) > abs( Dir.X ) )
					Dir.X = HoldDir.X;
				if ( abs( HoldDir.Y ) > abs( Dir.Y ) )
					Dir.Y = HoldDir.Y;
			}
		}

		return Dir;
	}

bool ButtonCheck::PreventNextInput = false;
int ButtonCheck::PreventTimeStamp = 0;

	void ButtonCheck::PreventInput()
	{
	#if defined(MIRROR_ALL)
		return;
	#endif

		PreventNextInput = true;
		PreventTimeStamp = Tools::TheGame->DrawCount;
	}

	bool ButtonCheck::Back( int Control )
	{
	#if defined(WINDOWS)
		if ( ButtonCheck::State( ControllerButtons_B, Control, false ).Pressed || ButtonCheck::State( Keys_Escape ).Pressed || ButtonCheck::State( Keys_Back ).Pressed )
			return true;
	#else
		if ( ButtonCheck::State( ControllerButtons_B, Control, false ).Pressed )
			return true;
	#endif
		else
			return false;
	}

	ButtonData ButtonCheck::State( Keys Key )
	{
		ButtonData Data = ButtonData();
		Data.PressingPlayer = 0;
	#if defined(WINDOWS)
		Data.Down = KeyboardExtension::IsKeyDownCustom( Tools::Keyboard, Key );
		Data.Pressed = Data.Down && !KeyboardExtension::IsKeyDownCustom( Tools::PrevKeyboard, Key );
		Data.Released = !Data.Down && KeyboardExtension::IsKeyDownCustom( Tools::PrevKeyboard, Key );
	#endif
		return Data;
	}

#if defined(WINDOWS)
	bool ButtonCheck::AnyMouseKey()
	{
		return Tools::MouseDown() || Tools::CurRightMouseDown();
	}
#endif

#if defined(WINDOWS)
	bool ButtonCheck::AnyKeyboardKey()
	{
		int ValidKeysPressed = 0;

		std::vector<Keys> keys = Tools::Keyboard.GetPressedKeys();
		for ( size_t i = 0; i < keys.size(); i++ )
			if ( keys[ i ] != Keys_Left && keys[ i ] != Keys_Right && keys[ i ] != Keys_Up && keys[ i ] != Keys_Down && keys[ i ] != Keys_LeftShift && keys[ i ] != Keys_RightShift && keys[ i ] != Keys_LeftAlt && keys[ i ] != Keys_RightAlt && keys[ i ] != Keys_LeftControl && keys[ i ] != Keys_RightControl && keys[ i ] != Keys_Tab )
			{
				ValidKeysPressed++;
			}

		return ValidKeysPressed > 0;

		//bool AnyKeyDown = !(keys.Length == 0 || (keys.Length == 1 && keys[0] == Keys.None));
		//return AnyKeyDown;
	}
#endif

	bool ButtonCheck::AnyKey()
	{
	#if defined(WINDOWS)
		return AnyKeyboardKey() || AnyMouseKey() || AllState(-2).Down;
	#else
		return AllState( -2 ).Down;
	#endif
	}

	ButtonData ButtonCheck::AllState( int iPlayerIndex )
	{
		static ControllerButtons tempButtons[] = { ControllerButtons_A, ControllerButtons_B, ControllerButtons_X, ControllerButtons_Y, ControllerButtons_LS, ControllerButtons_RS };
		static std::vector<ControllerButtons> buttons( tempButtons, tempButtons + sizeof( tempButtons ) / sizeof( ControllerButtons ) );

		return State( iPlayerIndex, buttons );
	}

#if defined(WINDOWS)
	bool ButtonCheck::KeyboardGo()
	{
		return KeyboardExtension::IsKeyDownCustom( Tools::Keyboard, Keys_Enter ) || KeyboardExtension::IsKeyDownCustom( Tools::Keyboard, Keys_Space ) || KeyboardExtension::IsKeyDownCustom( Tools::Keyboard, Go_Secondary );
	}
#endif

	ButtonData ButtonCheck::State( int iPlayerIndex, const std::vector<ControllerButtons> &ButtonList )
	{
		ButtonData data = ButtonData();
		data.PressingPlayer = iPlayerIndex;
		for ( std::vector<ControllerButtons>::const_iterator button = ButtonList.begin(); button != ButtonList.end(); ++button )
		{
			ButtonData newdata = State( *button, iPlayerIndex );

			data.Down |= newdata.Down;
			data.Pressed |= newdata.Pressed;
			data.Released |= newdata.Released;
			data.Squeeze = __max( data.Squeeze, newdata.Squeeze );
		}

		return data;
	}

bool ButtonCheck::PreLogIn = true;

	ButtonData ButtonCheck::State( const std::shared_ptr<ButtonClass> &Button, int iPlayerIndex )
	{
		if ( Button == 0 )
			return State( ControllerButtons_NONE, iPlayerIndex );

		if ( Button->IsKeyboard )
			return GetState( Button->KeyboardKey, false );
		else
			return State( Button->ControllerButton, iPlayerIndex );
	}

	ButtonData ButtonCheck::GetState( Keys Key, bool Prev )
	{
		ButtonData Data = ButtonData();
		Data.PressingPlayer = 0;
		if ( Key == Keys_None )
			return Data;

		if ( PreventNextInput )
		{
			Data.Pressed = Data.Down = false;

			if ( Tools::TheGame->DrawCount > PreventTimeStamp + 3 )
				PreventNextInput = false;

			return Data;
		}

	#if defined(WINDOWS)
		KeyboardState keyboard;
		if ( Prev )
			keyboard = Tools::PrevKeyboard;
		else
			keyboard = Tools::Keyboard;

		Data.Down = KeyboardExtension::IsKeyDownCustom( keyboard, Key );
	#endif

		// Get previous data to calculate Pressed and Released
		if ( !Prev )
		{
			ButtonData prevdata = GetState( Key, true );

			// Pressed == true if the previous state was not pressed but the current is
			if ( Data.Down && !prevdata.Down )
				Data.Pressed = true;

			// Released == true if the previous state was not Released but the current is
			if ( !Data.Down && prevdata.Down )
				Data.Released = true;
		}

		return Data;
	}

	ButtonData ButtonCheck::State( ControllerButtons Button, PlayerIndex Index )
	{
		return GetState( Button, static_cast<int>( Index ), false, true );
	}

	ButtonData ButtonCheck::State( ControllerButtons Button, int iPlayerIndex )
	{
		return GetState( Button, iPlayerIndex, false, true );
	}

	ButtonData ButtonCheck::State( ControllerButtons Button, int iPlayerIndex, bool UseKeyboardMapping )
	{
		return GetState( Button, iPlayerIndex, false, UseKeyboardMapping );
	}

	ButtonData ButtonCheck::GetState( ControllerButtons Button, int iPlayerIndex, bool Prev, bool UseKeyboardMapping )
	{
		// Debug tool: Use this to set the keyboard for use by player 1/2/3/4
		bool SingleOutPlayer = false;
		int ThisPlayerOnly = 1;

		if ( PreLogIn && iPlayerIndex == -1 )
			iPlayerIndex = -2;

	#if defined(MIRROR_ALL)
		iPlayerIndex = 0;
	#endif
		ButtonData Data = ButtonData();
		Data.PressingPlayer = iPlayerIndex;
		if ( Button == ControllerButtons_NONE )
			return Data;
	#if defined(XBOX)
		if ( Button == ControllerButtons_ENTER )
			return Data;
	#endif

		if ( SingleOutPlayer && iPlayerIndex >= 0 && iPlayerIndex != ThisPlayerOnly )
			return Data;

		if ( PreventNextInput )
		{
			Data.Pressed = Data.Down = false;

			if ( Tools::TheGame->DrawCount > PreventTimeStamp + 3 )
				PreventNextInput = false;

			return Data;
		}

		if ( Tools::AutoLoop )
		{
			if ( Button == ControllerButtons_A )
			{
				Data.Down = Prev;
			}
			return Data;
		}

		if ( iPlayerIndex == -1 || iPlayerIndex == -2 )
		{
			if ( !Prev )
			{
				bool NoneExist = PlayerManager::GetNumPlayers() == 0;

				for ( int i = 0; i < 4; i++ )
					if ( NoneExist || PlayerManager::Get( i )->Exists || iPlayerIndex == -2 )
					{
						ButtonData data = GetState( Button, i, false, UseKeyboardMapping );

						// Track which player is the one pressing the button.
						if ( data.Pressed )
							Data.PressingPlayer = i;

						Data.Down = Data.Down || data.Down;
						Data.Pressed = Data.Pressed || data.Pressed;
						Data.Released = Data.Released || data.Released;

						if ( data.Dir.LengthSquared() > Data.Dir.LengthSquared() )
							Data.Dir = data.Dir;
					}
			}
			else
			{
				for ( int i = 0; i < 4; i++ )
					if ( PlayerManager::Get( i )->Exists || iPlayerIndex == -2 )
					{
						ButtonData data = GetState( Button, i, true, UseKeyboardMapping );
						Data.Down = Data.Down || data.Down;
						Data.Pressed = Data.Pressed || data.Pressed;
						Data.Released = Data.Released || data.Released;
					}
			}
			return Data;
		}
	#if defined(WINDOWS)

		Keys key = Keys_None;
		Keys SecondaryKey = Keys_None;
		Keys TertiaryKey = Keys_None;

		if ( ( SingleOutPlayer && iPlayerIndex == ThisPlayerOnly ) || ( UseKeyboardMapping && ( iPlayerIndex == 0 || PlayerManager::Get( iPlayerIndex )->Exists ) ) )
		{
	//#if PC_VERSION
			if ( Button == ControllerButtons_ENTER )
				key = Keys_Enter;

			if ( Button == ControllerButtons_START )
			{
				key = Keys_Escape;
				TertiaryKey = Start_Secondary;
			}
			if ( Button == ControllerButtons_A )
			{
				TertiaryKey = Go_Secondary;
			}
			if ( Button == ControllerButtons_B )
			{
				key = Keys_Escape;
				TertiaryKey = Back_Secondary;
			}
			if ( Button == ControllerButtons_X )
				TertiaryKey = SlowMoToggle_Secondary;
			//if (Button == ControllerButtons.Y)
			//    TertiaryKey = Help_Secondary;
			if ( Button == ControllerButtons_LS )
				TertiaryKey = ReplayPrev_Secondary;
			if ( Button == ControllerButtons_RS )
				TertiaryKey = ReplayNext_Secondary;


			if ( Button == ControllerButtons_X ) // Keys.C;
				key = Keys_None;
			if ( Button == ControllerButtons_Y ) // Keys.V;
				key = Keys_None;
			if ( Button == ControllerButtons_RT )
				key = Keys_OemPeriod;
			if ( Button == ControllerButtons_LT )
				key = Keys_OemComma;
			if ( Button == ControllerButtons_LS )
				key = Keys_A;
			if ( Button == ControllerButtons_RS )
				key = Keys_D;
	//#else
	//                if (Button == ControllerButtons.Start) key = Keys.S;
	//                if (Button == ControllerButtons.Back) key = Keys.Escape;
	//                if (Button == ControllerButtons.A) key = Keys.Z;
	//                if (Button == ControllerButtons.B) key = Keys.X;
	//                if (Button == ControllerButtons.X) key = Keys.C;
	//                if (Button == ControllerButtons.Y) key = Keys.V;
	//                if (Button == ControllerButtons.RT) key = Keys.OemPeriod;
	//                if (Button == ControllerButtons.LT) key = Keys.OemComma;
	//#endif

			if ( Button == ControllerButtons_START )
				SecondaryKey = Keys_Back;
			//if (Button == ControllerButtons.Back) SecondaryKey = Keys.Back;
			if ( Button == ControllerButtons_B )
				SecondaryKey = Keys_Back;
		}

		KeyboardState keyboard;
		if ( Prev )
			keyboard = Tools::PrevKeyboard;
		else
			keyboard = Tools::Keyboard;

	#endif
		//#else
		GamePadState Pad;
		if ( Prev )
			Pad = Tools::PrevGamepadState[ iPlayerIndex ];
		else
			Pad = Tools::GamepadState[ iPlayerIndex ];

		switch ( Button )
		{
			case ControllerButtons_START:
				Data.Down = ( Pad.Buttons.Start == ButtonState_Pressed );
				break;
			case ControllerButtons_BACK:
				Data.Down = ( Pad.Buttons.Back == ButtonState_Pressed );
				break;
			case ControllerButtons_A:
				Data.Down = ( Pad.Buttons.A == ButtonState_Pressed );
				break;
			case ControllerButtons_B:
				Data.Down = ( Pad.Buttons.B == ButtonState_Pressed );
				break;
			case ControllerButtons_X:
				Data.Down = ( Pad.Buttons.X == ButtonState_Pressed );
				break;
			case ControllerButtons_Y:
				Data.Down = ( Pad.Buttons.Y == ButtonState_Pressed );
				break;
			case ControllerButtons_LJBUTTON:
				Data.Down = ( Pad.Buttons.LeftStick == ButtonState_Pressed );
				break;
			case ControllerButtons_RJBUTTON:
				Data.Down = ( Pad.Buttons.RightStick == ButtonState_Pressed );
				break;
			case ControllerButtons_LS:
				Data.Down = ( Pad.Buttons.LeftShoulder == ButtonState_Pressed );
				break;
			case ControllerButtons_RS:
				Data.Down = ( Pad.Buttons.RightShoulder == ButtonState_Pressed );
				break;
			case ControllerButtons_LT:
			{
					Data.Down = ( Pad.Triggers.Left > 0.5f );
					Data.Squeeze = Pad.Triggers.Left;
					break;
			}
			case ControllerButtons_RT:
			{
					Data.Down = ( Pad.Triggers.Right > 0.5f );
					Data.Squeeze = Pad.Triggers.Right;
					break;
			}
			case ControllerButtons_LJ:
				Data.Dir = Pad.ThumbSticks.Left;
				break;
			case ControllerButtons_RJ:
				Data.Dir = Pad.ThumbSticks.Right;
				break;
			case ControllerButtons_DPAD:
			{
					Data.Dir = Vector2();
					if ( Pad.DPad.Right == ButtonState_Pressed )
						Data.Dir = Vector2( 1, 0 );
					if ( Pad.DPad.Up == ButtonState_Pressed )
						Data.Dir = Vector2( 0, 1 );
					if ( Pad.DPad.Left == ButtonState_Pressed )
						Data.Dir = Vector2( -1, 0 );
					if ( Pad.DPad.Down == ButtonState_Pressed )
						Data.Dir = Vector2( 0, -1 );
			}
				break;
		}
		//#endif

	#if defined(WINDOWS)
	if ( ( SingleOutPlayer && iPlayerIndex == ThisPlayerOnly ) || ( UseKeyboardMapping && iPlayerIndex == 0 ) )
	//if (UseKeyboardMapping && iPlayerIndex == 0)
	{
		if ( Button == ControllerButtons_A )
		{
			if ( Prev )
				Data.Down |= Tools::Mouse.LeftButton == ButtonState_Pressed;
			else
				Data.Down |= Tools::PrevMouse.LeftButton == ButtonState_Pressed;
		}
		else
			Data.Down |= KeyboardExtension::IsKeyDownCustom( keyboard, key );

		if ( SecondaryKey != Keys_None )
			Data.Down |= KeyboardExtension::IsKeyDownCustom( keyboard, SecondaryKey );

		if ( TertiaryKey != Keys_None )
			Data.Down |= KeyboardExtension::IsKeyDownCustom( keyboard, TertiaryKey );

		key = Keys_Escape;

		//if (Button == ControllerButtons.A) key = Keys.Z;
		//if (Button == ControllerButtons.B) key = Keys.X;

		if ( Button == ControllerButtons_A )
			key = Go_Secondary;
		if ( Button == ControllerButtons_B )
			key = Back_Secondary;

		if ( key != Keys_Escape )
			Data.Down |= KeyboardExtension::IsKeyDownCustom( keyboard, key );

		if ( Button == ControllerButtons_A )
			Data.Down |= KeyboardExtension::IsKeyDownCustom( keyboard, Keys_Enter ) || KeyboardExtension::IsKeyDownCustom( keyboard, Keys_Space );
	//#else
	//    Data.Down |= keyboard.IsKeyDownCustom(key);
	//#endif

		if ( Button == ControllerButtons_LJ )
		{
			Vector2 KeyboardDir = Vector2();
			if ( KeyboardExtension::IsKeyDownCustom( keyboard, Keys_Left ) )
				KeyboardDir.X = -1;
			if ( KeyboardExtension::IsKeyDownCustom( keyboard, Keys_Right ) )
				KeyboardDir.X = 1;
			if ( KeyboardExtension::IsKeyDownCustom( keyboard, Keys_Up ) )
				KeyboardDir.Y = 1;
			if ( KeyboardExtension::IsKeyDownCustom( keyboard, Keys_Down ) )
				KeyboardDir.Y = -1;
			if ( KeyboardExtension::IsKeyDownCustom( keyboard, Left_Secondary ) )
				KeyboardDir.X = -1;
			if ( KeyboardExtension::IsKeyDownCustom( keyboard, Right_Secondary ) )
				KeyboardDir.X = 1;
			if ( KeyboardExtension::IsKeyDownCustom( keyboard, Up_Secondary ) )
				KeyboardDir.Y = 1;
			if ( KeyboardExtension::IsKeyDownCustom( keyboard, Down_Secondary ) )
				KeyboardDir.Y = -1;

			if ( KeyboardDir.LengthSquared() > Data.Dir.LengthSquared() )
			{
				// Use the keyboard direction instead of the gamepad direction 
				// and note that the keyboard was used.
				if ( iPlayerIndex >= 0 )
					PlayerManager::Get( iPlayerIndex )->KeyboardUsedLast = true;
				Data.Dir = KeyboardDir;
			}
			else
				if ( iPlayerIndex >= 0 )
					PlayerManager::Get( iPlayerIndex )->KeyboardUsedLast = false;
		}
	}
	#endif

		// Get previous data to calculate Pressed and Released
		if ( !Prev )
		{
			ButtonData prevdata = GetState( Button, iPlayerIndex, true, UseKeyboardMapping );

			// Pressed == true if the previous state was not pressed but the current is
			if ( Data.Down && !prevdata.Down )
				Data.Pressed = true;

			// Released == true if the previous state was not Released but the current is
			if ( !Data.Down && prevdata.Down )
				Data.Released = true;
		}

		return Data;
	}

	ButtonCheck::ButtonCheck()
	{
	}

	std::wstring ButtonCheck::GetString()
	{
		std::wstring s;

		switch ( MyType )
		{
			case MashType_HOLD:
				s = _T( "Hold {p" );
				break;
			case MashType_TAP:
				s = _T( "Tap {p" );
				break;
			case MashType_HOLD_DIR:
				s = _T( "Hold {p" );
				break;
			default:
				s = _T( "" );
				break;
		}

		s += _T( "Big_Button_" ) + Tools::ButtonNames[ static_cast<int>( MyButton1 ) ] + _T( ",75,75}" );

		switch ( MyType )
		{
			case MashType_HOLD_DIR:
				s += _T( " " ) + Tools::DirNames[ Dir ];
				break;
			default:
				break;
		}

		return s;
	}

	void ButtonCheck::Phsx()
	{
		Satisfied = false;

		Previous = Current;
		Current = ButtonCheck::State( MyButton1, MyPlayerIndex );

		switch ( MyType )
		{
			case MashType_HOLD:
				if ( Current.Down )
					Satisfied = true;

				break;

			case MashType_TAP:
				if ( Current.Down != Previous.Down )
					GapCount = 0;
				else
					GapCount++;
				if ( GapCount < GapAllowance )
					Satisfied = true;

				break;

			case MashType_HOLD_DIR:
				if ( Direction( Current.Dir ) == Dir )
					Satisfied = true;
				break;
		}
	}
}
