#include <global_header.h>



namespace CloudberryKingdom
{

	std::wstring GUI_Multiplier::ToString()
	{
		return _T( "x" ) + StringConverterHelper::toString( GetMultiplier() );
	}

	void GUI_Multiplier::OnAdd()
	{
		GUI_Panel::OnAdd();

		if ( !AddedOnce )
		{
			if ( DoSlideIn )
			{
				SlideOut( PresetPos_RIGHT, 0 );
				SlideIn();
				Show();
			}
			else
			{
				SlideIn( 0 );
				Show();
			}
		}

		AddedOnce = true;
	}

	void GUI_Multiplier::ReleaseBody()
	{
		GUI_Panel::ReleaseBody();
	}

	int GUI_Multiplier::GetMultiplier()
	{
		return Multiplier;
	}

	void GUI_Multiplier::SetMultiplier( int Multiplier )
	{
		if ( this->Multiplier != Multiplier )
		{
			this->Multiplier = Multiplier;
			UpdateMultiplierText();
		}
	}

	void GUI_Multiplier::UpdateMultiplierText()
	{
		MultiplierText->SubstituteText( ToString() );
	}

	GUI_Multiplier::GUI_Multiplier( int Style )
	{
		InitializeInstanceFields();
		DoInit( Style, false );
	}

	GUI_Multiplier::GUI_Multiplier( int Style, bool SlideIn )
	{
		InitializeInstanceFields();
		DoInit( Style, SlideIn );
	}

	void GUI_Multiplier::DoInit( int Style, bool SlideIn )
	{
		DoSlideIn = SlideIn;

		MyPile = std::make_shared<DrawPile>();
		EnsureFancy();

		MyPile->setPos( Vector2( 1235, 820 ) );

		// Object is carried over through multiple levels, so prevent it from being released.
		PreventRelease = true;

		PauseOnPause = true;

		MyPile->FancyPos->UpdateWithGame = true;

		std::shared_ptr<EzFont> font;
		float scale;
		Color c, o;

		if ( false )
		{
			font = Resources::Font_Grobold42;
			scale = .5f;
			c = Color::White;
			o = Color::Black;
		}
		else
		{
			font = Resources::Font_Grobold42;
			scale = .5f;
			c = Color( 228, 0, 69 );
			o = Color::White;
		}

		if ( Style == 0 )
		{
			MultiplierText = std::make_shared<EzText>( ToString(), Resources::Font_Grobold42, 950, false, true );
			MultiplierText->setScale( .95f );
			MultiplierText->setPos( Vector2( 187, 130 ) );
			MultiplierText->MyFloatColor = ( Color( 255, 255, 255 ) ).ToVector4();
		}
		else if ( Style == 1 )
		{
			MultiplierText = std::make_shared<EzText>( ToString(), font, 950, false, true );
			MultiplierText->setScale( scale );
			MultiplierText->setPos( Vector2( 381.4434f, 85.55492f ) );
			MultiplierText->MyFloatColor = c.ToVector4();
			MultiplierText->OutlineColor = o.ToVector4();
		}

		MultiplierText->RightJustify = true;

		MyPile->Add( MultiplierText );
	}

	void GUI_Multiplier::MyDraw()
	{
		if ( !getCore()->Show || getCore()->MyLevel->SuppressCheckpoints )
			return;

		GUI_Panel::MyDraw();
	}

	void GUI_Multiplier::MyPhsxStep()
	{
		GUI_Panel::MyPhsxStep();

		//this.MultiplierText.MyFloatColor = new Color(100, 100, 200).ToVector4();

		if ( Hid || !Active )
			return;

		if ( getCore()->MyLevel->Watching || getCore()->MyLevel->Finished )
			return;

		SetMultiplier( static_cast<int>( MyGame->ScoreMultiplier + .1f ) );
	}

	void GUI_Multiplier::InitializeInstanceFields()
	{
		AddedOnce = false;
		DoSlideIn = true;
	}
}
