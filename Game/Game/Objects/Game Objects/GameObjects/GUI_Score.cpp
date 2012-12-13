#include <global_header.h>

namespace CloudberryKingdom
{

	int GUI_CampaignScore::RunningCampaignScoreLambda::Apply( const std::shared_ptr<PlayerData> &p )
	{
		return p->RunningCampaignScore();
	}

	//GUI_CampaignScore::GUI_CampaignScore() : GUI_Score(false)
	GUI_CampaignScore::GUI_CampaignScore() { }
	std::shared_ptr<GUI_CampaignScore> GUI_CampaignScore::GUI_CampaignScore_Construct()
	{
		GUI_Score::GUI_Score_Construct( false );

		PreventRelease = false;
		UpdateAfterLevelFinish = true;

		return std::static_pointer_cast<GUI_CampaignScore>( shared_from_this() );
	}

	int GUI_CampaignScore::GetScore()
	{
		int Score = PlayerManager::PlayerSum( std::make_shared<RunningCampaignScoreLambda>() );
		return Score;
	}

	std::wstring GUI_Score::ToString()
	{
		Tools::Warning();
		return Localization::WordString( Localization::Words_SCORE ) + _T( " " ) + StringConverterHelper::toString( GetScore() );
	}

	void GUI_Score::OnAdd()
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

	void GUI_Score::ReleaseBody()
	{
		GUI_Panel::ReleaseBody();
	}

	int GUI_Score::GetScore()
	{
		return Score;
	}

	void GUI_Score::SetScore( int Score )
	{
		if ( this->Score != Score )
		{
			this->Score = Score;
			UpdateScoreText();
		}
	}

	void GUI_Score::UpdateScoreText()
	{
		ScoreText->SubstituteText( ToString() );
	}

	GUI_Score::GUI_Score() { }
	std::shared_ptr<GUI_Score> GUI_Score::GUI_Score_Construct()
	{
		GUI_Panel::GUI_Panel_Construct();

		InitializeInstanceFields();
		DoInit( false );

		return std::static_pointer_cast<GUI_Score>( shared_from_this() );
	}

	GUI_Score::GUI_Score( bool SlideIn ) { }
	std::shared_ptr<GUI_Score> GUI_Score::GUI_Score_Construct( bool SlideIn )
	{
		GUI_Panel::GUI_Panel_Construct();

		InitializeInstanceFields();
		DoInit( SlideIn );

		return std::static_pointer_cast<GUI_Score>( shared_from_this() );
	}

	void GUI_Score::DoInit( bool SlideIn )
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

			font = Resources::Font_Grobold42;
			scale = .5f;
			c = bColor( 228, 0, 69 );
			o = Color::White;

			ScoreText = std::make_shared<EzText>( ToString(), font, 950.f, false, true );
			ScoreText->setScale( scale );
			ScoreText->setPos( Vector2( 381.4434f, 85.55492f ) );
			ScoreText->MyFloatColor = c.ToVector4();
			ScoreText->OutlineColor = o.ToVector4();

		ScoreText->RightJustify = true;

		MyPile->Add( ScoreText );
	}

	void GUI_Score::MyDraw()
	{
		if ( !getCore()->Show || getCore()->MyLevel->SuppressCheckpoints )
			return;

		GUI_Panel::MyDraw();
	}

	void GUI_Score::MyPhsxStep()
	{
		GUI_Panel::MyPhsxStep();

		if ( Hid || !Active )
			return;

		if ( getCore()->MyLevel->Watching || (getCore()->MyLevel->Finished && !UpdateAfterLevelFinish) )
			return;

		if ( MyGame->AlwaysGiveCoinScore )
			SetScore( PlayerManager::GetGameScore() );
		else
			SetScore( PlayerManager::GetGameScore_WithTemporary() );
	}

	void GUI_Score::InitializeInstanceFields()
	{
		AddedOnce = false;
		DoSlideIn = true;
		UpdateAfterLevelFinish = false;
	}
}
