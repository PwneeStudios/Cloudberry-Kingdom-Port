#include <global_header.h>

#include <MasterHack.h>

namespace CloudberryKingdom
{

	void TitleGameData_MW::InitializeStatics()
	{
		TitleGameData_MW::Factory = boost::make_shared<TitleGameData_MW_Factory>();
	}

	boost::shared_ptr<GameData> TitleGameData_MW_Factory::Make()
	{
		boost::shared_ptr<TitleGameData_MW> temp = boost::make_shared<TitleGameData_MW>();
		TitleGameData_MW_Construct( temp );
		return boost::static_pointer_cast<GameData>( temp );
	}

	TitleGameData_MW::_InitProxy::_InitProxy( const boost::shared_ptr<TitleGameData_MW> &tgdmw )
	{
		this->tgdmw = tgdmw;
	}

	void TitleGameData_MW::_InitProxy::Apply()
	{
		tgdmw->_Init();
	}

	boost::shared_ptr<SimpleGameFactory> TitleGameData_MW::Factory;

	void TitleGameData_MW::Release()
	{
		TitleGameData::Release();
	}

	TitleGameData_MW::TitleGameData_MW() : TitleGameData()
	{
		// See TitleGameData_MW_Construct.
	}

	void TitleGameData_MW::SetToReturnTo( int code )
	{
		TitleGameData::SetToReturnTo( code );
	}

	void TitleGameData_MW::ReturnTo( int code )
	{
        if (SetToRepaly)
        {
			Tools::SongWad->SetPlayList( Tools::Song_Heavens );
			Tools::SongWad->Restart( true, false );
		}

		TitleGameData::ReturnTo( code );
	}

	boost::shared_ptr<Level> TitleGameData_MW::MakeLevel()
	{
		boost::shared_ptr<Level> level = boost::make_shared<Level>();
		level->setMainCamera( boost::make_shared<Camera>() );

		level->TimeLimit = -1;

		level->CurPiece = level->StartNewPiece( 0, BobVec(), 4 );

		Vector2 Center = Vector2( 0, 0 );

		level->getMainCamera()->MakeFancyPos();
		level->getMainCamera()->FancyPos->RelVal = Center;

		level->CurPiece->CamStartPos = Center;

		// Camera Zone
		CamZone = boost::static_pointer_cast<CameraZone>( Recycle->GetObject( ObjectType_CAMERA_ZONE, false ) );
		CamZone->Init( Vector2(), Vector2( 100000, 100000 ) );
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

		Tools::TitleGame = shared_from_this();

		// Backdrop
		BackPanel = MakeMagic( StartMenu_MW_Backpanel, () );
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
		WaitThenDo( 18, boost::make_shared<_InitProxy>( boost::static_pointer_cast<TitleGameData_MW>( shared_from_this() ) ) );
	}

	void TitleGameData_MW::_Init()
	{
		// Press Start
		PressStart = MakeMagic( StartMenu_MW_PressStart, ( boost::static_pointer_cast<TitleGameData_MW>( shared_from_this() ) ) );
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
