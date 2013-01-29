#include <global_header.h>

namespace CloudberryKingdom
{

	//GUI_CampaignLevel::GUI_CampaignLevel() : GUI_Level(false)
	GUI_CampaignLevel::GUI_CampaignLevel()
	{
	}

	boost::shared_ptr<GUI_CampaignLevel> GUI_CampaignLevel::GUI_CampaignLevel_Construct()
	{
		GUI_Level::GUI_Level_Construct( false );

		return boost::static_pointer_cast<GUI_CampaignLevel>( shared_from_this() );
	}

	void GUI_CampaignLevel::OnAdd()
	{
		GUI_Level::OnAdd();

		UpdateLevelText();
	}

	std::wstring GUI_CampaignLevel::ToString()
	{
		if ( MyGame == 0 )
			return std::wstring( L"   " );

		return MyGame->MyLevel->Name;
	}

	std::wstring GUI_Level::ToString()
	{
		Tools::Warning();
		return Localization::WordString( Prefix ) + std::wstring( L" " ) + StringConverterHelper::toString( Level_Renamed );
	}

	void GUI_Level::OnAdd()
	{
		GUI_Panel::OnAdd();

		if ( !AddedOnce )
		{
			if ( DoSlideIn )
			{
				SlideOut( PresetPos_TOP, 0 );
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

	void GUI_Level::ReleaseBody()
	{
		GUI_Panel::ReleaseBody();
	}

	void GUI_Level::SetLevel( int Level_Renamed )
	{
		if ( this->Level_Renamed != Level_Renamed )
		{
			this->Level_Renamed = Level_Renamed;
			UpdateLevelText();
		}
	}

	void GUI_Level::UpdateLevelText()
	{
		LevelText->SubstituteText( ToString() );
	}

	GUI_Level::GUI_Level() :
		Prefix( static_cast<Localization::Words>( 0 ) ),
		DoSlideIn( false ),
		AddedOnce( false ),
		Level_Renamed( 0 )	
	{
	}
	boost::shared_ptr<GUI_Level> GUI_Level::GUI_Level_Construct()
	{
		InitializeInstanceFields();
		GUI_Panel::GUI_Panel_Construct();

		DoInit( false );

		return boost::static_pointer_cast<GUI_Level>( shared_from_this() );
	}

	GUI_Level::GUI_Level( bool SlideIn ) :
		Prefix( static_cast<Localization::Words>( 0 ) ),
		DoSlideIn( false ),
		AddedOnce( false ),
		Level_Renamed( 0 )	
	{
	}

	boost::shared_ptr<GUI_Level> GUI_Level::GUI_Level_Construct( bool SlideIn )
	{
		InitializeInstanceFields();
		GUI_Panel::GUI_Panel_Construct();

		DoInit( SlideIn );

		return boost::static_pointer_cast<GUI_Level>( shared_from_this() );
	}

	GUI_Level::GUI_Level( int LevelNum ) :
		Prefix( static_cast<Localization::Words>( 0 ) ),
		DoSlideIn( false ),
		AddedOnce( false ),
		Level_Renamed( 0 )	
	{
	}

	boost::shared_ptr<GUI_Level> GUI_Level::GUI_Level_Construct( int LevelNum )
	{
		InitializeInstanceFields();
		GUI_Panel::GUI_Panel_Construct();

		DoInit( false );
		PreventRelease = false;

		SetLevel( LevelNum );

		return boost::static_pointer_cast<GUI_Level>( shared_from_this() );
	}

	void GUI_Level::DoInit( bool SlideIn )
	{
		DoSlideIn = SlideIn;

		MyPile = boost::make_shared<DrawPile>();
		EnsureFancy();

		MyPile->setPos( Vector2( 1590.556f, 803.2224f ) );

		// Object is carried over through multiple levels, so prevent it from being released.
		PreventRelease = true;

		PauseOnPause = true;

		MyPile->FancyPos->UpdateWithGame = true;


		boost::shared_ptr<EzFont> font;
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
			scale = .55f;
			c = bColor( 228, 0, 69 );
			o = Color::White;
		}

		LevelText = boost::make_shared<EzText>( ToString(), font, 950.f, false, true );
		LevelText->setScale( scale );
		LevelText->MyFloatColor = c.ToVector4();
		LevelText->OutlineColor = o.ToVector4();


		LevelText->RightJustify = true;

		MyPile->Add( LevelText );
	}

	void GUI_Level::MyDraw()
	{
		if ( !getCore()->Show || getCore()->MyLevel->SuppressCheckpoints )
			return;

		GUI_Panel::MyDraw();
	}

	void GUI_Level::MyPhsxStep()
	{
		GUI_Panel::MyPhsxStep();

		if ( Hid || !Active )
			return;

		if ( getCore()->MyLevel->Watching || getCore()->MyLevel->Finished )
			return;
	}

	void GUI_Level::InitializeInstanceFields()
	{
		Prefix = Localization::Words_Level;
		DoSlideIn = true;
		AddedOnce = false;
	}
}
