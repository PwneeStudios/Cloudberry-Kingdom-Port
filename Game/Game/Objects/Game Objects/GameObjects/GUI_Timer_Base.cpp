#include <global_header.h>


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

	const int &GUI_Timer_Base::getMinutes() const
	{
		return static_cast<int>( getTime() / (60 * 62) );
	}

	const int &GUI_Timer_Base::getSeconds() const
	{
		return static_cast<int>( ( getTime() - 60 * 62 * getMinutes() ) / 62 );
	}

	const int &GUI_Timer_Base::getMilliseconds() const
	{
		float Remainder = getTime() - 60 * 62 * getMinutes() - 62 * getSeconds();

		return static_cast<int>( 100 * Remainder / 62 );
	}

	std::shared_ptr<StringBuilder> GUI_Timer_Base::BuildString()
	{
		MyString->Length = 0;

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

	const Microsoft::Xna::Framework::Vector2 &GUI_Timer_Base::getApparentPos() const
	{
		return TimerText->FancyPos->AbsVal + TimerText->GetWorldSize() / 2;
	}

	void GUI_Timer_Base::UpdateTimerText()
	{
		TimerText->SubstituteText( BuildString() );
	}

	GUI_Timer_Base::GUI_Timer_Base()
	{
		InitializeInstanceFields();
		MyPile = std::make_shared<DrawPile>();
		EnsureFancy();

		MyPile->setPos( Vector2( -90, 865 ) );
		SlideInLength = 0;

		// Object is carried over through multiple levels, so prevent it from being released.
		PreventRelease = true;

		PauseOnPause = true;

		MyPile->FancyPos->UpdateWithGame = true;

		std::shared_ptr<EzFont> font;
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
			c = Color( 228, 0, 69 );
			o = Color::White;
		}

//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
		TimerText = std::make_shared<EzText>( BuildString()->ToString(), font, 450, true, true );
		TimerText->setScale( scale );
		TimerText->MyFloatColor = c.ToVector4();
		TimerText->OutlineColor = o.ToVector4();

		MyPile->Add( TimerText );
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
				OnTimeExpired->Apply( this );

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
		MyString = std::make_shared<StringBuilder>( 50, 50 );
		AddedOnce = false;
		Intensity = 1;
		OnTimeExpired = std::make_shared<Multicaster_1<GUI_Timer_Base*> >();
		CountDownWhileDead = false;
	}
}
