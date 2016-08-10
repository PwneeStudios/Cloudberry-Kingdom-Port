#include <small_header.h>
#include "Game/Objects/Game Objects/GameObjects/GUI_Timer_Base.h"

#include "Core/Graphics/Draw/DrawPile.h"
#include "Core/Text/EzFont.h"
#include "Core/Text/EzText.h"
#include "Game/Objects/Game Objects/GameObjects/GUI_Panel.h"
#include "Game/Player/PlayerManager.h"
#include "Game/Tools/Resources.h"
#include "Game/Tools/Tools.h"

#include "Game/Level/Level.h"
#include "Game/Games/GameType.h"

namespace CloudberryKingdom
{

	const int &GUI_Timer_Base::getTime() const
	{
		return _Time;
	}

	void GUI_Timer_Base::setTime( const int &value )
	{
		_Time = value;
		UpdateTimerText();
	}

	const int GUI_Timer_Base::getMinutes() const
	{
		return static_cast<int>( getTime() / (60 * 62) );
	}

	const int GUI_Timer_Base::getSeconds() const
	{
		return static_cast<int>( ( getTime() - 60 * 62 * getMinutes() ) / 62 );
	}

	const int GUI_Timer_Base::getMilliseconds() const
	{
		float Remainder = getTime() - 60.f * 62.f * getMinutes() - 62.f * getSeconds();

		return static_cast<int>( 100 * Remainder / 62 );
	}

	boost::shared_ptr<StringBuilder> GUI_Timer_Base::BuildString()
	{
		MyString->setLength( 0 );

		if ( getMinutes() > 0 )
		{
			MyString->Add( getMinutes(), 1 );
			MyString->Append( L':' );
			MyString->Add( getSeconds(), 2 );
		}
		else
		{
			MyString->Add( getSeconds(), 1 );
			MyString->Append( L':' );
			MyString->Add( getMilliseconds(), 2 );
		}

		return MyString;
	}

	void GUI_Timer_Base::OnAdd()
	{
		GUI_Panel::OnAdd();

		if ( !AddedOnce )
		{
			Hide();

			Show();
		}

		AddedOnce = true;
	}

	void GUI_Timer_Base::Hide()
	{
		GUI_Panel::Hide();
		SlideOut( PresetPos_TOP, 0 );
	}

	void GUI_Timer_Base::Show()
	{
		GUI_Panel::Show();
		SlideIn();
		MyPile->BubbleUp( false, 5, Intensity );
	}

	void GUI_Timer_Base::ShowInstant()
	{
		GUI_Panel::Show();
		SlideIn( 0 );
		MyPile->BubbleUp( false, 0, Intensity );
	}

	void GUI_Timer_Base::ReleaseBody()
	{
		GUI_Panel::ReleaseBody();
	}

	const Vector2 GUI_Timer_Base::getApparentPos() const
	{
		return TimerText->FancyPos->AbsVal + TimerText->GetWorldSize() / 2;
	}

	void GUI_Timer_Base::UpdateTimerText()
	{
		TimerText->SubstituteText( BuildString() );
	}

	GUI_Timer_Base::GUI_Timer_Base() :
		_Time( 0 ),
		AddedOnce( false ),
		Intensity( 0 ),
		CountDownWhileDead( false )
	{
	}
	boost::shared_ptr<GUI_Timer_Base> GUI_Timer_Base::GUI_Timer_Base_Construct()
	{
		InitializeInstanceFields();
		GUI_Panel::GUI_Panel_Construct();

		MyPile = boost::make_shared<DrawPile>();
		EnsureFancy();

		MyPile->setPos( Vector2( -115.0f, 803.8889f ) );
		SlideInLength = 0;

		// Object is carried over through multiple levels, so prevent it from being released.
		PreventRelease = true;

		PauseOnPause = true;

		MyPile->FancyPos->UpdateWithGame = true;

		boost::shared_ptr<EzFont> font;
		float scale;
		Color c, o;

		if ( false )
		{
			font = Resources::Font_Grobold42_2;
			scale = .55f;
			c = Color::White;
			o = Color::Black;
		}
		else
		{
			font = Resources::Font_Grobold42;
			scale = .75f;
			c = bColor( 228, 0, 69 );
			o = Color::White;
		}

		TimerText = boost::make_shared<EzText>( BuildString()->ToString(), font, 450.f, true, true );
		TimerText->setScale( scale );
		TimerText->MyFloatColor = c.ToVector4();
		TimerText->OutlineColor = o.ToVector4();

		MyPile->Add( TimerText );

		return boost::static_pointer_cast<GUI_Timer_Base>( shared_from_this() );
	}

	void GUI_Timer_Base::MyDraw()
	{
		if ( !getCore()->Show || getCore()->MyLevel->SuppressCheckpoints )
			return;

		GUI_Panel::MyDraw();
	}

	void GUI_Timer_Base::MyPhsxStep()
	{
		GUI_Panel::MyPhsxStep();
		if ( getCore()->Released || MyGame == 0 )
			return;

		if ( MyGame->HasBeenCompleted )
			return;

		if ( MyGame->SoftPause )
			return;
		if ( Hid || !Active )
			return;

		if ( getTime() == 0 )
		{
			if ( OnTimeExpired != 0 )
				OnTimeExpired->Apply( boost::static_pointer_cast<GUI_Timer_Base>( shared_from_this() ) );

			return;
		}

		if ( getCore()->MyLevel->Watching || getCore()->MyLevel->Finished )
			return;

		if ( CountDownWhileDead || !PlayerManager::AllDead() )
			setTime( getTime() - 1 );
	}

	void GUI_Timer_Base::InitializeInstanceFields()
	{
		_Time = 5000;
		MyString = boost::make_shared<StringBuilder>( 50, 50 );
		AddedOnce = false;
		Intensity = 1;
		OnTimeExpired = boost::make_shared<Multicaster_1<boost::shared_ptr<GUI_Timer_Base> > >();
		CountDownWhileDead = false;
	}
}
