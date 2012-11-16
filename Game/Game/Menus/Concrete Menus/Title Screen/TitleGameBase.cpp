#include <global_header.h>


//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;

namespace CloudberryKingdom
{

	std::shared_ptr<GameData> TitleFactory::Make( const std::shared_ptr<LevelSeedData> &data, bool MakeInBackground )
	{
		return 0;
	}

std::shared_ptr<GameFactory> TitleGameData::Factory = std::make_shared<TitleFactory>();

	void TitleGameData::Release()
	{
		GameData::Release();

		if ( Released )
			return;

		if ( Tools::WorldMap == this )
			Tools::WorldMap.reset();
	}

	TitleGameData::TitleGameData()
	{
		InitializeInstanceFields();
		LockLevelStart = false;
		SuppressQuickSpawn = true;

		Init();

		Tools::CurGameData->SuppressQuickSpawn = true;
		Tools::CurGameData->SuppressSongInfo = true;
	}

	void TitleGameData::SetToReturnTo( int code )
	{
		GameData::SetToReturnTo( code );

		Tools::WorldMap = this;
	}

	void TitleGameData::ReturnTo( int code )
	{
		CleanLastLevel();

		// Fire event
		ReturnToEvent();
	}

	std::shared_ptr<Level> TitleGameData::MakeLevel()
	{
		std::shared_ptr<Level> level = std::make_shared<Level>();
		level->setMainCamera( std::make_shared<Camera>() );

		level->TimeLimit = -1;

		level->CurPiece = level->StartNewPiece( 0, 0, 4 );

		Vector2 Center = Vector2( 1000, 0 );

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

		// Initialize the background
		level->MyTileSet = _T( "forest" );
		//level.MyBackground = Background.Get("KobblerPie");
		level->MyBackground = Background::Get( _T( "forest" ) );
		//level.MyBackground = Background.Get("forest_snow");

		level->MyBackground->Init( level );

		return level;
	}

	void TitleGameData::Init()
	{
		GameData::Init();

		Tools::CurLevel = MyLevel = MakeLevel();
		Tools::WorldMap = Tools::CurGameData = MyLevel->MyGame = this;
		Tools::CurGameType = TitleGameData::Factory;

		Tools::TitleGame = this;

		MyLevel->PlayMode = 0;
		MyLevel->ResetAll( false );
	}

	void TitleGameData::AdditionalReset()
	{
		GameData::AdditionalReset();

		MyLevel->getMainCamera()->MyZone = CamZone;
	}

	void TitleGameData::PhsxStep()
	{
	#if defined(PC_VERSION)
		Tools::TheGame->ShowMouse = true;
	#endif
		std::shared_ptr<Camera> cam = MyLevel->getMainCamera();
		cam->MyPhsxType = Camera::PhsxType_FIXED;

		cam->FancyPos->RelVal = Vector2::Zero;

		/*
		// Pan the camera
		cam.FancyPos.RelVal += cam.Data.Velocity;
		if (PanCamera)
		{
		    if (cam.Pos.X > PanMaxDist)
		        cam.Data.Acceleration.X = -PanAcc;
		    if (cam.Pos.X < PanMinDist)
		        cam.Data.Acceleration.X = PanAcc;
		    if (cam.Data.Acceleration == Vector2.Zero)
		        cam.Data.Acceleration = new Vector2(1, 0);
	
		    if (cam.Data.Velocity.X < PanMaxSpeed && cam.Data.Acceleration.X > 0 ||
		        cam.Data.Velocity.X > -PanMaxSpeed && cam.Data.Acceleration.X < 0)
		        cam.Data.Velocity += cam.Data.Acceleration;
	
		    cam.Data.UpdatePosition();
		}
		else
		    Cam.Data.Velocity *= .98f;
		*/

		GameData::PhsxStep();
	}

	void TitleGameData::PostDraw()
	{
		GameData::PostDraw();
	}

	void TitleGameData::InitializeInstanceFields()
	{
		PanCamera = true;
		PanAcc = .02f;
		PanMaxSpeed = 3.8f;
		PanMaxDist = 29000;
		PanMinDist = 3000;
	}
}
