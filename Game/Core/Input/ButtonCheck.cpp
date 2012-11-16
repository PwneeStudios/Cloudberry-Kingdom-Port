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

	bool KeyboardExtension::IsKeyDownCustom( KeyboardState keyboard, Keys key )
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
		_DownCount = std::vector<int>( Tools->Length<ControllerButtons>() );
	}

std::vector<ButtonStatistics*> ButtonStats::Controller = 0;
std::shared_ptr<ButtonStatistics> ButtonStats::All = 0;

	void ButtonStats::Init()
	{
		if ( Controller.empty() )
		{
			Controller = std::vector<ButtonStatistics*>( 4 );
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
			if ( Tools::GamepadState[ i ].Buttons->A == ButtonState::Pressed )
			{
				Controller[ i ]->IncrCount( ControllerButtons_A );
				Incr = true;
			}
			else
				Controller[ i ]->SetCount( ControllerButtons_A, 0 );

			Vector2 dir = ButtonCheck::GetDir( i );
			Controller[ i ]->IncrCount( ControllerButtons_RIGHT, dir.X > ::7 );
			Controller[ i ]->IncrCount( ControllerButtons_LEFT, dir.X < -.7f );
			Controller[ i ]->IncrCount( ControllerButtons_UP, dir.Y > ::7 );
			Controller[ i ]->IncrCount( ControllerButtons_DOWN, dir.Y < -.7f );
		}

		if ( Incr )
			All->IncrCount( ControllerButtons_A );
		else
			All->SetCount( ControllerButtons_A, 0 );

		const ControllerButtons tempVector[] = { ControllerButtons_LEFT, ControllerButtons_RIGHT, ControllerButtons_UP, ControllerButtons_DOWN };
		std::vector<ControllerButtons> buttons = std::vector<ControllerButtons>( tempVector, tempVector + sizeof( tempVector ) / sizeof( tempVector[ 0 ] ) );
		for ( std::vector<CloudberryKingdom::ControllerButtons>::const_iterator button = buttons.begin(); button != buttons.end(); ++button )
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
		KeyboardKey = Keys::None;
		IsKeyboard = true;
	}

bool ButtonCheck::MouseInUse = false;
bool ButtonCheck::PrevMouseInUse = false;

	void ButtonCheck::UpdateControllerAndKeyboard_StartOfStep()
	{
		// Update controller/keyboard states
	#if defined(WINDOWS)
		Tools::Keyboard = Keyboard::GetState();
		if ( Tools::PrevKeyboard == 0 )
			Tools::PrevKeyboard = Tools::Keyboard;

		Tools::Mouse = Mouse::GetState();
	#endif
		Tools::GamepadState[ 0 ] = GamePad::GetState( PlayerIndex::One );
		Tools::GamepadState[ 1 ] = GamePad::GetState( PlayerIndex::Two );
		Tools::GamepadState[ 2 ] = GamePad::GetState( PlayerIndex::Three );
		Tools::GamepadState[ 3 ] = GamePad::GetState( PlayerIndex::Four );

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
			Tools::DeltaMouse = Tools::ToWorldCoordinates( Vector2( Tools::Mouse.X, Tools::Mouse.Y ), Tools::CurLevel->getMainCamera() ) - Tools::ToWorldCoordinates(Vector2(Tools::PrevMouse.X, Tools::PrevMouse.Y), Tools::CurLevel->getMainCamera());
		}
		Tools::RawDeltaMouse = Vector2( Tools::Mouse.X, Tools::Mouse.Y ) - Vector2( Tools::PrevMouse.X, Tools::PrevMouse.Y );

		Tools::PrevKeyboard = Tools::Keyboard;
		Tools::PrevMouse = Tools::Mouse;

		// Store the previous states of the Xbox controllers.
		for ( int i = 0; i < 4; i++ )
			if ( Tools::PrevGamepadState[ i ] != 0 )
				Tools::PrevGamepadState[ i ] = Tools::GamepadState[ i ];
	}

#if defined(PC_VERSION)
	void ButtonCheck::UpdateMouseUse()
	{
	#if defined(PC_VERSION)
		if ( ButtonCheck::AnyKeyboardKey() || (PlayerManager::Players.size() > 0 && PlayerManager::getPlayer() != 0 && ButtonCheck::GetMaxDir(false).Length() > ::3) )
	#else
		if ( ButtonCheck::AnyKeyboardKey() || (PlayerManager::Players.size() > 0 && ButtonCheck::GetMaxDir(true).Length() > ::3) )
	#endif
			MouseInUse = false;

		if ( Tools::DeltaMouse != Vector2::Zero || Tools::Mouse.LeftButton == ButtonState::Pressed || Tools::Mouse.RightButton == ButtonState::Pressed )
			MouseInUse = true;

		PrevMouseInUse = MouseInUse;
	}
#endif

	void ButtonCheck::KillSecondary()
	{
		Help_KeyboardKey->Set( Keys::None );
		Quickspawn_KeyboardKey->Set( Keys::None );
		Start_Secondary = Go_Secondary = Back_Secondary = ReplayPrev_Secondary = ReplayNext_Secondary = SlowMoToggle_Secondary = Left_Secondary = Right_Secondary = Up_Secondary = Down_Secondary = Keys::None;
	}

std::shared_ptr<ButtonClass> Quickspawn_KeyboardKey, Help_KeyboardKey, ButtonCheck::QuickReset_KeyboardKey = std::make_shared<ButtonClass>();
Keys Start_Secondary, Go_Secondary, Back_Secondary, ReplayPrev_Secondary, ReplayNext_Secondary, ReplayToggle_Secondary, SlowMoToggle_Secondary, Left_Secondary, Right_Secondary, Up_Secondary, ButtonCheck::Down_Secondary = 0;

	void ButtonCheck::Reset()
	{
		QuickReset_KeyboardKey->Set( Keys::F );
		Quickspawn_KeyboardKey->Set( Keys::Space );
		Help_KeyboardKey->Set( Keys::Enter );

		Start_Secondary = Keys::None;
		Go_Secondary = Keys::None;
		Back_Secondary = Keys::None;

		ReplayPrev_Secondary = Keys::N;
		ReplayNext_Secondary = Keys::M;
		ReplayToggle_Secondary = Keys::L;

		SlowMoToggle_Secondary = Keys::C;

		Left_Secondary = Keys::A;
		Right_Secondary = Keys::D;
		Up_Secondary = Keys::W;
		Down_Secondary = Keys::S;
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

	Microsoft::Xna::Framework::Vector2 ButtonCheck::GetDir( int Control )
	{
		return GetDir( Control, true );
	}

	Microsoft::Xna::Framework::Vector2 ButtonCheck::GetDir( int Control, bool Threshold )
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

	Microsoft::Xna::Framework::Vector2 ButtonCheck::GetMaxDir()
	{
		return GetMaxDir( false );
	}

	Microsoft::Xna::Framework::Vector2 ButtonCheck::GetMaxDir( int Control )
	{
		return GetMaxDir( Control == -1 );
	}

	Microsoft::Xna::Framework::Vector2 ButtonCheck::GetMaxDir( bool MustExist )
	{
		if ( PlayerManager::Players.empty() || PlayerManager::Players[ 0 ] == 0 || PlayerManager::Players[ 1 ] == 0 || PlayerManager::Players[ 2 ] == 0 || PlayerManager::Players[ 3 ] == 0 )
			return Vector2::Zero;

		Vector2 Dir = Vector2::Zero;
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
		if ( ButtonCheck::State( ControllerButtons_B, Control, false ).Pressed || ButtonCheck::State( Keys::Escape ).Pressed || ButtonCheck::State( Keys::Back ).Pressed )
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
		Data.Down = Tools::Keyboard.IsKeyDownCustom( Key );
		Data.Pressed = Data.Down && !Tools::PrevKeyboard.IsKeyDownCustom( Key );
		Data.Released = !Data.Down && Tools::PrevKeyboard.IsKeyDownCustom( Key );
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

		std::vector<Microsoft::Xna::Framework::Input::Keys> keys = Tools::Keyboard.GetPressedKeys();
		for ( int i = 0; i < keys.size(); i++ )
			if ( keys[ i ] != Keys::Left && keys[ i ] != Keys::Right && keys[ i ] != Keys::Up && keys[ i ] != Keys::Down && keys[ i ] != Keys::LeftShift && keys[ i ] != Keys::RightShift && keys[ i ] != Keys::LeftAlt && keys[ i ] != Keys::RightAlt && keys[ i ] != Keys::LeftControl && keys[ i ] != Keys::RightControl && keys[ i ] != Keys::Tab )
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
		return State( iPlayerIndex, ControllerButtons_A, ControllerButtons_B, ControllerButtons_X, ControllerButtons_Y, ControllerButtons_LS, ControllerButtons_RS );
	}

#if defined(WINDOWS)
	bool ButtonCheck::KeyboardGo()
	{
		return Tools::Keyboard.IsKeyDownCustom( Keys::Enter ) || Tools::Keyboard.IsKeyDownCustom( Keys::Space ) || Tools::Keyboard.IsKeyDownCustom( Go_Secondary );
	}
#endif

	ButtonData ButtonCheck::State( int iPlayerIndex, ... )
	{
		ButtonData data = ButtonData();
		data.PressingPlayer = iPlayerIndex;
		for ( unknown::const_iterator button = ButtonList.begin(); button != ButtonList.end(); ++button )
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

	ButtonData ButtonCheck::State( const std::shared_ptr<ButtonClass> &Button, PlayerIndex Index )
	{
		return State( Button, -2 );
	}

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
		if ( Key == Keys::None )
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

		Data.Down = keyboard.IsKeyDownCustom( Key );
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

		Keys key = Keys::None;
		Keys SecondaryKey = Keys::None;
		Keys TertiaryKey = Keys::None;

		if ( ( SingleOutPlayer && iPlayerIndex == ThisPlayerOnly ) || ( UseKeyboardMapping && ( iPlayerIndex == 0 || PlayerManager::Get( iPlayerIndex )->Exists ) ) )
		{
	//#if PC_VERSION
			if ( Button == ControllerButtons_ENTER )
				key = Keys::Enter;

			if ( Button == ControllerButtons_START )
			{
				key = Keys::Escape;
				TertiaryKey = Start_Secondary;
			}
			if ( Button == ControllerButtons_A )
			{
				TertiaryKey = Go_Secondary;
			}
			if ( Button == ControllerButtons_B )
			{
				key = Keys::Escape;
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
				key = Keys::None;
			if ( Button == ControllerButtons_Y ) // Keys.V;
				key = Keys::None;
			if ( Button == ControllerButtons_RT )
				key = Keys::OemPeriod;
			if ( Button == ControllerButtons_LT )
				key = Keys::OemComma;
			if ( Button == ControllerButtons_LS )
				key = Keys::A;
			if ( Button == ControllerButtons_RS )
				key = Keys::D;
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
				SecondaryKey = Keys::Back;
			//if (Button == ControllerButtons.Back) SecondaryKey = Keys.Back;
			if ( Button == ControllerButtons_B )
				SecondaryKey = Keys::Back;
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
				Data.Down = ( Pad.Buttons->Start == ButtonState::Pressed );
				break;
			case ControllerButtons_BACK:
				Data.Down = ( Pad.Buttons->Back == ButtonState::Pressed );
				break;
			case ControllerButtons_A:
				Data.Down = ( Pad.Buttons->A == ButtonState::Pressed );
				break;
			case ControllerButtons_B:
				Data.Down = ( Pad.Buttons->B == ButtonState::Pressed );
				break;
			case ControllerButtons_X:
				Data.Down = ( Pad.Buttons->X == ButtonState::Pressed );
				break;
			case ControllerButtons_Y:
				Data.Down = ( Pad.Buttons->Y == ButtonState::Pressed );
				break;
			case ControllerButtons_LJBUTTON:
				Data.Down = ( Pad.Buttons->LeftStick == ButtonState::Pressed );
				break;
			case ControllerButtons_RJBUTTON:
				Data.Down = ( Pad.Buttons->RightStick == ButtonState::Pressed );
				break;
			case ControllerButtons_LS:
				Data.Down = ( Pad.Buttons->LeftShoulder == ButtonState::Pressed );
				break;
			case ControllerButtons_RS:
				Data.Down = ( Pad.Buttons->RightShoulder == ButtonState::Pressed );
				break;
			case ControllerButtons_LT:
			{
					Data.Down = ( Pad.Triggers.Left > ::5 );
					Data.Squeeze = Pad.Triggers.Left;
					break;
			}
			case ControllerButtons_RT:
			{
					Data.Down = ( Pad.Triggers.Right > ::5 );
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
					Data.Dir = Vector2::Zero;
					if ( Pad.DPad.Right == ButtonState::Pressed )
						Data.Dir = Vector2( 1, 0 );
					if ( Pad.DPad.Up == ButtonState::Pressed )
						Data.Dir = Vector2( 0, 1 );
					if ( Pad.DPad.Left == ButtonState::Pressed )
						Data.Dir = Vector2( -1, 0 );
					if ( Pad.DPad.Down == ButtonState::Pressed )
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
				Data.Down |= Tools::Mouse.LeftButton == ButtonState::Pressed;
			else
				Data.Down |= Tools::PrevMouse.LeftButton == ButtonState::Pressed;
		}
		else
			Data.Down |= keyboard.IsKeyDownCustom( key );

		if ( SecondaryKey != Keys::None )
			Data.Down |= keyboard.IsKeyDownCustom( SecondaryKey );

		if ( TertiaryKey != Keys::None )
			Data.Down |= keyboard.IsKeyDownCustom( TertiaryKey );

		key = Keys::Escape;

		//if (Button == ControllerButtons.A) key = Keys.Z;
		//if (Button == ControllerButtons.B) key = Keys.X;

		if ( Button == ControllerButtons_A )
			key = Go_Secondary;
		if ( Button == ControllerButtons_B )
			key = Back_Secondary;

		if ( key != Keys::Escape )
			Data.Down |= keyboard.IsKeyDownCustom( key );

		if ( Button == ControllerButtons_A )
			Data.Down |= keyboard.IsKeyDownCustom( Keys::Enter ) || keyboard.IsKeyDownCustom( Keys::Space );
	//#else
	//    Data.Down |= keyboard.IsKeyDownCustom(key);
	//#endif

		if ( Button == ControllerButtons_LJ )
		{
			Vector2 KeyboardDir = Vector2::Zero;
			if ( keyboard.IsKeyDownCustom( Keys::Left ) )
				KeyboardDir.X = -1;
			if ( keyboard.IsKeyDownCustom( Keys::Right ) )
				KeyboardDir.X = 1;
			if ( keyboard.IsKeyDownCustom( Keys::Up ) )
				KeyboardDir.Y = 1;
			if ( keyboard.IsKeyDownCustom( Keys::Down ) )
				KeyboardDir.Y = -1;
			if ( keyboard.IsKeyDownCustom( Left_Secondary ) )
				KeyboardDir.X = -1;
			if ( keyboard.IsKeyDownCustom( Right_Secondary ) )
				KeyboardDir.X = 1;
			if ( keyboard.IsKeyDownCustom( Up_Secondary ) )
				KeyboardDir.Y = 1;
			if ( keyboard.IsKeyDownCustom( Down_Secondary ) )
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
