#include <global_header.h>





namespace CloudberryKingdom
{

	std::shared_ptr<GameData> TitleGameData_MW_Factory::Make()
	{
		return std::make_shared<TitleGameData_MW>();
	}

	TitleGameData_MW::_InitProxy::_InitProxy( const std::shared_ptr<TitleGameData_MW> &tgdmw )
	{
		this->tgdmw = tgdmw;
	}

	void TitleGameData_MW::_InitProxy::Apply()
	{
		tgdmw->_Init();
	}

std::shared_ptr<SimpleGameFactory> TitleGameData_MW::Factory = std::make_shared<TitleGameData_MW_Factory>();

	void TitleGameData_MW::Release()
	{
		TitleGameData::Release();
	}

	TitleGameData_MW::TitleGameData_MW() : TitleGameData()
	{
	}

	void TitleGameData_MW::SetToReturnTo( int code )
	{
		TitleGameData::SetToReturnTo( code );
	}

	void TitleGameData_MW::ReturnTo( int code )
	{
		Tools::SongWad->SetPlayList( Tools::Song_Heavens );
		Tools::SongWad->Restart( true, false );

		TitleGameData::ReturnTo( code );
	}

	std::shared_ptr<Level> TitleGameData_MW::MakeLevel()
	{
		std::shared_ptr<Level> level = std::make_shared<Level>();
		level->setMainCamera( std::make_shared<Camera>() );

		level->TimeLimit = -1;

		level->CurPiece = level->StartNewPiece( 0, 0, 4 );

		Vector2 Center = Vector2( 0, 0 );

		level->getMainCamera()->MakeFancyPos();
		level->getMainCamera()->FancyPos->RelVal = Center;

		level->CurPiece->CamStartPos = Center;

		// Camera Zone
		CamZone = static_cast<CameraZone*>( Recycle->GetObject( ObjectType_CAMERA_ZONE, false ) );
		CamZone->Init( Vector2::Zero, Vector2( 100000, 100000 ) );
		CamZone->Start = Center;
		CamZone->End = Center;
		CamZone->FreeY = false;
		level->AddObject( CamZone );
		level->getMainCamera()->MyZone = CamZone;

		return level;
	}

	void TitleGameData_MW::Init()
	{
		TitleGameData::Init();

		Tools::CurGameType = TitleGameData::Factory;

		Tools::TitleGame = this;

		// Backdrop
		BackPanel = std::make_shared<StartMenu_MW_Backpanel>();
		AddGameObject( BackPanel );
		BackPanel->SetState( StartMenu_MW_Backpanel::State_SCENE );
		BackPanel->InitialZoomIn();

		// Music
		Tools::Warning();
		//Tools.MusicVolume.Val = 0f;
		Tools::SongWad->SuppressNextInfoDisplay = true;
		//Tools.SongWad.SetPlayList(Tools.Song_WritersBlock);
		Tools::SongWad->SetPlayList( Tools::Song_Heavens );
		Tools::SongWad->Start( true );

		// Fade in
		FadeIn( .0175f );
		WaitThenDo( 18, std::make_shared<_InitProxy>( this ) );
	}

	void TitleGameData_MW::_Init()
	{
		// Press Start
		PressStart = std::make_shared<StartMenu_MW_PressStart>( this );
		AddGameObject( PressStart );

		/*
		// Menu
		GUI_Panel panel;
	
		if (CloudberryKingdomGame.StartAsFreeplay)
		    panel = new CustomLevel_GUI();
		else
		{
		    panel = new StartMenu_MW(this);
	
		    //panel = new StartMenu();
	
		    //panel = new AdvancedCustomGUI();
		    //panel = new SimpleCustomGUI();
	
		    //panel = new StatsMenu();
		    //panel = new AwardmentMenu();
		    //panel = new CategoryMenu();
		    //panel = new CampaignMenu();
		    //panel = new ArcadeMenu();
		}
	
		AddGameObject(panel);
		 */
	}

	void TitleGameData_MW::AdditionalReset()
	{
		TitleGameData::AdditionalReset();

		MyLevel->getMainCamera()->MyZone = CamZone;
	}

	void TitleGameData_MW::PhsxStep()
	{
		TitleGameData::PhsxStep();
	}

	void TitleGameData_MW::PostDraw()
	{
		TitleGameData::PostDraw();
	}
}
