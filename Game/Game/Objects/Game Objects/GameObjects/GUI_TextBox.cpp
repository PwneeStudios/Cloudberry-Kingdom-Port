#include <small_header.h>
#include "Game/Objects/Game Objects/GameObjects/GUI_TextBox.h"

#include "Core/Graphics/Draw/Quads/QuadClass.h"
#include "Game/Localization.h"
#include "Core/Input/ButtonCheck.h"
#include "Core/Text/EzFont.h"
#include "Core/Text/EzText.h"
#include "Game/Player/PlayerManager.h"
#include "Game/Objects/Game Objects/GameObjects/GUI_Text.h"
#include "Game/Tools/Resources.h"
#include "Game/Tools/Tools.h"

#include "Game/Player/PlayerData.h"

#include <Hacks/Queue.h>
#include <Hacks\List.h>
#include <Hacks/Clipboard.h>

#include <Game/CloudberryKingdom/CloudberryKingdom.CloudberryKingdomGame.h>

namespace CloudberryKingdom
{

#if defined(PC_VERSION)
	GUI_EnterName::GUI_EnterName() : GUI_TextBox(PlayerManager::getDefaultName(), Vector2()) { }
	boost::shared_ptr<GUI_EnterName> GUI_EnterName::GUI_EnterName_Construct()
	{
		GUI_TextBox::GUI_TextBox_Construct(PlayerManager::getDefaultName(), Vector2());

		boost::shared_ptr<EzText> Text = boost::make_shared<EzText>( Localization::Words_NewHighScore, Resources::Font_Grobold42 );

		Text->setPos( Vector2( -579.365f, 253.9681f ) );
		Text->setScale( Text->getScale() * .7f );
		MyPile->Add( Text );

		return boost::static_pointer_cast<GUI_EnterName>( shared_from_this() );
	}
#endif

#if defined(PC_VERSION)
	void GUI_EnterName::Enter()
	{
		if ( getLength() > 0 )
			PlayerManager::setDefaultName( getText() );
		else
			setText( PlayerManager::getDefaultName() );

		GUI_TextBox::Enter();
	}
#endif

	void GUI_TextBox::OnAdd()
	{
		GUI_Text::OnAdd();

		GetFocus();
	}

	void GUI_TextBox::ReleaseBody()
	{
		GUI_Text::ReleaseBody();

		OnEnter.reset();
		OnEscape.reset();
		ReleaseFocus();
	}

	void GUI_TextBox::GetFocus()
	{
		HasFocus = true;

	#if defined(WINDOWS)
		KeyboardExtension::FreezeInput();

		// FIXME: Reimplement this using something similar.
		//EventInput::CharEntered += boost::make_shared<CharEnteredHandler>( shared_from_this(), &GUI_TextBox::CharEntered );
		//EventInput::KeyDown += boost::make_shared<KeyEventHandler>( shared_from_this(), &GUI_TextBox::KeyDown );
	#endif
	}

	void GUI_TextBox::ReleaseFocus()
	{
		if ( !HasFocus )
			return;
		HasFocus = false;

	#if defined(WINDOWS)
		KeyboardExtension::UnfreezeInput();

		// FIXME: As above.
		//EventInput::CharEntered -= CharEntered;
		//EventInput::KeyDown -= KeyDown;
	#endif
	}

		void GUI_TextBox::PosCaret()
		{
			// Position the caret at the end of the text
			std::wstring hold = getText();
			std::wstring _s = getText().substr(0, __max( 0, getText().size() - 1) );
			//string _s = Text;
			MyText->SubstituteText( _s );
			float width = MyText->GetWorldWidth();
			MyText->SubstituteText( hold );

			Caret->setScale( MyText->getScale() * 1.105f );
			if ( _s.size() == 0 )
				Caret->setX( MyText->getPos().X + 15.5f );
			else
				Caret->setX( MyText->getPos().X + width - 130 * Caret->getScale() );
			Caret->setY( MyText->getPos().Y + 7 * Caret->getScale() );

			// If we're selecting move the caret one character to the left
			//if (SelectIndex_End - SelectIndex_Start > 0)
			//    Caret.X -= MyText.GetWorldWidth(" ");
		}

		void GUI_TextBox::ScaleTextToFit()
		{
			MyText->setScale( .8f );
			float w = MyText->GetWorldWidth();
			float MaxWidth = 2400.0f;
			if (w > MaxWidth)
			{
				MyText->setScale( MyText->getScale() * MaxWidth / w );
			}
		}

	void GUI_TextBox::MyPhsxStep()
	{
		int static DownCount = 0;
		int const RepeatKeyOnceDelay = 65, RepeatKeyMultipleDelay = 38;
		static std::vector<Keys> LastPress;

		GUI_Text::MyPhsxStep();

        if (!Active) return;

		//if ( !Active )
		//{
		//	DownCount = 0;
		//	LastPress.clear();
		//	return;
		//}

		ScaleTextToFit();

		PosCaret();

		// Decide if we should draw the caret
		if ( HasFocus )
		{
			// Don't draw the caret if there isn't room for another character
			if ( LimitLength && getLength() == MaxLength )
				Caret->Show = false;
			else
			{
				// Draw the caret every other half second
				//Caret->Show = Tools::TheGame->DrawCount / 30 % 2 == 0;
				Caret->Show = Tools::TheGame->DrawCount % 65 > 23;
			}

#if defined(WINDOWS)
			std::vector<Keys> keys = Tools::Keyboard.GetPressedKeys();
			
			if ( keys.size() > 0 )
			{
				if (DownCount == 0 || DownCount == RepeatKeyOnceDelay ||
					DownCount > RepeatKeyOnceDelay && (DownCount - RepeatKeyOnceDelay) % RepeatKeyMultipleDelay == 0 ||
					LastPress.size() > 0 && keys.size() > 0 && LastPress[0] != keys[0] )
				{				
					//DeleteSelected();

					for ( std::vector<Keys>::const_iterator itr = keys.begin(); itr != keys.end(); ++itr )
					{
						LastPress.push_back( *itr );

						wchar_t wchar = static_cast<wchar_t>( *itr );
						if ( IsAcceptableChar( wchar ) && ( !LimitLength || static_cast<int>( MyText->FirstString().length() ) < MaxLength) )
						{
							MyText->AppendText( wchar );
							Recenter();
						}

						if ( *itr == Keys_Back )
							Backspace();
						if ( *itr == Keys_Enter && !Tools::PrevKeyboard.IsKeyDown(Keys_Enter) )
							Enter();
					}
				}

				DownCount++;
			}
			else
			{
				DownCount = 0;
				LastPress.clear();
			}


			KeyboardExtension::Freeze = false;
			if ( ButtonCheck::State( Keys_Escape ).Down )
			{
				Cancel();
				return;
			}
			if ( ButtonCheck::State( Keys_V ).Pressed && Tools::CntrlDown() )
			{
				Paste();
				return;
			}
			//if (ButtonCheck.State(Keys.V).Pressed && Tools::CntrlDown()) { Paste(); return; }
			if ( ButtonCheck::State( Keys_C ).Down && Tools::CntrlDown() )
			{
				Copy();
				return;
			}
			if ( ButtonCheck::State( Keys_X ).Down && Tools::CntrlDown() )
			{
				Copy();
				Clear();
				return;
			}
			if ( HasFocus )
				KeyboardExtension::Freeze = true;
	#endif

			GamepadInteract();
		}
		else
		{
			// Don't draw the caret when we don't have focus
			Caret->Show = false;
			
			DownCount = 0;
			LastPress.clear();
		}
	}

	void GUI_TextBox::Cancel()
	{
		if ( Canceled )
			return;
		if ( OnEscape != 0 )
			OnEscape->Apply();
	}

	void GUI_TextBox::GamepadInteract()
	{
        int control = getControl();
        if (control < 0 || control > 3)
        {
            control = -1;
        }
        else
        {
            if ( !PlayerManager::Players[ control ] || !PlayerManager::Players[ control ]->Exists )
            {
                control = -1;
            }
        }

		if ( getLength() == 0 )
		{
			if ( ButtonCheck::State( ControllerButtons_A, control ).Pressed )
				if ( getLength() < MaxLength )
					setText( getText() + L'A' );
			return;
		}

		wchar_t c = getText()[ getLength() - 1 ];
		if ( ButtonCheck::State( ControllerButtons_A, control ).Pressed )
			if ( getLength() < MaxLength )
			{
				setText( getText() + c );
				Recenter();
			}
		if ( ButtonCheck::State( ControllerButtons_X, control ).Pressed )
		{
			Backspace();
			return;
		}
		if ( ButtonCheck::State( ControllerButtons_Y, control ).Pressed )
		{
			Cancel();
			return;
		}
		if ( ButtonCheck::State( ControllerButtons_START, control ).Pressed )
		{
			Enter();
			return;
		}
		if ( ButtonCheck::State( ControllerButtons_B, control ).Pressed) { Cancel(); return; }

		Vector2 dir = ButtonCheck::GetDir( control );

		if ( Tools::TheGame->DrawCount % 7 == 0 && fabs( dir.Y ) > .5f )
		{
			if ( dir.Y > 0 )
				setText( getText().substr(0, getLength() - 1) + IncrChar(c) );
			if ( dir.Y < 0 )
				setText( getText().substr(0, getLength() - 1) + DecrChar(c) );

			Recenter();
		}
	}

#if defined(WINDOWS)
	void GUI_TextBox::Paste()
	{
		Clear();

		std::wstring clipboard = Clipboard::GetText();

		clipboard = Tools::SantitizeOneLineString( clipboard, Resources::LilFont );

		setText( getText() + Tools::SantitizeOneLineString(clipboard, MyText->MyFont) );
	}
#endif

#if defined(WINDOWS)
	void GUI_TextBox::Copy()
	{
		if ( getText() != std::wstring( L"" ) && getText().length() > 0 )
			Clipboard::SetText( getText() );
	}
#endif

	wchar_t GUI_TextBox::IncrChar( wchar_t c )
	{
		int _c = static_cast<int>( c ) + 1;
		if ( _c > ( int )L'z' )
			return L'A';
		return static_cast<wchar_t>( _c );
	}

	wchar_t GUI_TextBox::DecrChar( wchar_t c )
	{
		int _c = static_cast<int>( c ) - 1;
		if ( _c < static_cast<int>( L'A' ) )
			return L'z';
		return static_cast<wchar_t>( _c );
	}

	GUI_TextBox::GUI_TextBox() :
		SelectIndex_Start( 0 ), SelectIndex_End( 0 ),
		HasFocus( false ),
		Canceled( false ),
		MaxLength( 0 ),
		LimitLength( false ),
		DoRecenter( false )
	{
	}
	boost::shared_ptr<GUI_TextBox> GUI_TextBox::GUI_TextBox_Construct()
	{
		GUI_Text::GUI_Text_Construct();
		return boost::static_pointer_cast<GUI_TextBox>( shared_from_this() );
	}

	//GUI_TextBox::GUI_TextBox( const std::wstring &InitialText, Vector2 pos ) : GUI_Text( Tools::SantitizeOneLineString( InitialText, Resources::Font_Grobold42 ), pos, false )
	GUI_TextBox::GUI_TextBox( const std::wstring &InitialText, Vector2 pos ) :
		SelectIndex_Start( 0 ), SelectIndex_End( 0 ),
		HasFocus( false ),
		Canceled( false ),
		MaxLength( 0 ),
		LimitLength( false ),
		DoRecenter( false )
	{
	}
	boost::shared_ptr<GUI_TextBox> GUI_TextBox::GUI_TextBox_Construct( const std::wstring &InitialText, Vector2 pos )
	{
		InitializeInstanceFields();
		GUI_Text::GUI_Text_Construct( Tools::SantitizeOneLineString( InitialText, Resources::Font_Grobold42 ), pos, false );

		Init( InitialText, pos, Vector2(1), 1 );

		return boost::static_pointer_cast<GUI_TextBox>( shared_from_this() );
	}

	GUI_TextBox::GUI_TextBox( const std::wstring &InitialText, Vector2 pos, Vector2 scale, float fontscale ) : GUI_Text( InitialText, pos, false, Resources::LilFont ),
		SelectIndex_Start( 0 ), SelectIndex_End( 0 ),
		HasFocus( false ),
		Canceled( false ),
		MaxLength( 0 ),
		LimitLength( false ),
		DoRecenter( false )
	{
	}
	boost::shared_ptr<GUI_TextBox> GUI_TextBox::GUI_TextBox_Construct( const std::wstring &InitialText, Vector2 pos, Vector2 scale, float fontscale )
	{
		InitializeInstanceFields();
		GUI_Text::GUI_Text_Construct( InitialText, pos, false, Resources::LilFont );

		Init( InitialText, pos, scale, fontscale );

		return boost::static_pointer_cast<GUI_TextBox>( shared_from_this() );
	}

	void GUI_TextBox::Init( std::wstring InitialText, Vector2 pos, Vector2 scale, float fontscale )
	{
		InitialText = Tools::SantitizeOneLineString( InitialText, Resources::LilFont );

		if ( InitialText.size() == 0 )
			InitialText = std::wstring( L"_" );

		FixedToCamera = true;
		NoPosMod = true;

		MyText->setScale( MyText->getScale() * fontscale );

		// Backdrop
		Backdrop = boost::make_shared<QuadClass>( boost::shared_ptr<FancyVector2>(), true, false );
		Backdrop->setTextureName( std::wstring( L"score_screen" ) );
		Backdrop->setSize( Vector2( 640.4763f, 138.0953f ) * scale );

		MyText->setPos( Vector2( -522.2222f + 40, 23.80954f ) * scale );
		//MyPile.Insert(0, Backdrop);

		// Caret
		//var font = Resources::Font_Grobold42;
		boost::shared_ptr<CloudberryKingdom::EzFont> font = Resources::Font_Grobold42;
		Caret = boost::make_shared<EzText>( std::wstring( L"_" ), font, 1000.f, false, true,.575f );
		Caret->MyFloatColor = Color::Black.ToVector4();
		Caret->setPos( MyText->getPos() );
		Caret->setScale( Caret->getScale() * fontscale );

		MyPile->Add( Caret );

		// Select quad
		SelectQuad = boost::make_shared<QuadClass>( boost::shared_ptr<FancyVector2>(), true, false );
		SelectQuad->setTextureName( std::wstring( L"White" ) );
		SelectQuad->Quad_Renamed.SetColor( bColor( 255, 255, 255, 125 ) );
		SelectQuad->setSize( Vector2( 100, 100 * scale.Y ) );
		SelectQuad->Layer = 0;

		MyPile->Add( SelectQuad );

		SelectAll();
		Recenter();
	}

	void GUI_TextBox::SelectAll()
	{
		SelectIndex_Start = 0;
		SelectIndex_End = getLength();

		UpdateSelectQuad();
	}

	void GUI_TextBox::Unselect()
	{
		SelectIndex_Start = SelectIndex_End = 0;
		UpdateSelectQuad();
	}

	void GUI_TextBox::Clear()
	{
		SelectAll();
		DeleteSelected();
	}

	void GUI_TextBox::DeleteSelected()
	{
		/*setText( getText().erase( SelectIndex_Start, SelectIndex_End - SelectIndex_Start) );*/
		
		//std::wstring s = getText();
		//s.substr(0, SelectIndex_Start ) + s.substr( SelectIndex_End );
		setText( std::wstring( L"A" ) );

		Unselect();
	}

	void GUI_TextBox::UpdateSelectQuad()
	{
		//float width = MyText->GetWorldWidth( getText().substr(SelectIndex_Start, SelectIndex_End - SelectIndex_Start) );
		float width = 2438;
		float pos = MyText->GetWorldWidth( getText().substr(0, SelectIndex_Start) );

		SelectQuad->setSize( Vector2( width / 2 + 50, SelectQuad->getSize().Y + 30 ) );
		SelectQuad->setLeft( MyText->getPos().X + pos );
		//SelectQuad->setPos( MyText->getPos() + Vector2( MyText->GetWorldWidth() / 2 + 50, -MyText->GetWorldHeight() / 4 ) );
		/*SelectQuad->setPos( Vector2( 377.0f, -MyText->GetWorldHeight() / 4 ) );*/
		SelectQuad->setPos( Vector2( 344.0f, -MyText->GetWorldHeight() / 4 ) );
	}

	boost::shared_ptr<EzText> GUI_TextBox::MakeText( std::wstring text, bool centered, const boost::shared_ptr<EzFont> &font )
	{
		boost::shared_ptr<EzText> eztext = boost::make_shared<EzText>( text, font, 1000.f, centered, true,.575f );
		eztext->MyFloatColor = Color::Black.ToVector4();
		eztext->OutlineColor = Color::Transparent.ToVector4();

		return eztext;
	}

#if defined(WINDOWS)
	bool GUI_TextBox::IsAcceptableChar( wchar_t c )
	{
		int ascii = static_cast<int>( c );

		return ascii >= 32 && ascii <= 122;
	}
#endif

	bool GUI_TextBox::IsLetter( wchar_t c )
	{
		int ascii = static_cast<int>( c );

		if ( ascii >= 65 && ascii <= 90 || ascii >= 97 && ascii <= 122 )
			return true;
		else
			return false;
	}

	void GUI_TextBox::Recenter()
	{
		if ( DoRecenter )
			MyText->setPos( Vector2( -MyText->GetWorldWidth() / 2, 0 ) );

		if ( MyText != 0 && MyText->Bits.size() > 0 && MyText->Bits[ 0 ] != 0 )
			MyText->Bits[ 0 ]->loc.X = 0;

		ScaleTextToFit();
		PosCaret();
	}

	void GUI_TextBox::Backspace()
	{
		// If we're selecting delete the selection
		//if ( SelectIndex_End - SelectIndex_Start > 0 )
		//	DeleteSelected();
		//else
		{
			// Otherwise delete one character
			if ( getLength() == 1 )
				return;

			setText( getText().substr(0, getLength() - 1) );
		}

		Recenter();
	}

	void GUI_TextBox::Enter()
	{
		Unselect();

		ReleaseFocus();
		MyPile->Jiggle( true );

		// Change the backdrop color
		Backdrop->setTextureName( std::wstring( L"Score/Score_Screen_grey" ) );

		if ( OnEnter != 0 )
			OnEnter->Apply();
	}

	const int GUI_TextBox::getLength() const
	{
		return getText().length();
	}

	const std::wstring GUI_TextBox::getText() const
	{
		return MyText->FirstString();
	}

	void GUI_TextBox::setText( const std::wstring &value )
	{
		MyText->SubstituteText( value );
	}

	void GUI_TextBox::InitializeInstanceFields()
	{
		OnEnter = boost::make_shared<Multicaster>();
		OnEscape = boost::make_shared<Multicaster>();
		HasFocus = false;
		Canceled = false;
		SelectIndex_Start = 0;
		SelectIndex_End = 0;
		MaxLength = 18;
		LimitLength = true;
		DoRecenter = false;
	}
}
