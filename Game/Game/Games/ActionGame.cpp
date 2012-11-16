#include <global_header.h>

using namespace Microsoft::Xna::Framework;

namespace CloudberryKingdom
{

	std::shared_ptr<GameData> ActionFactory::Make( const std::shared_ptr<LevelSeedData> &data, bool MakeInBackground )
	{
		return std::make_shared<ActionGameData>( data, MakeInBackground );
	}

std::shared_ptr<GameFactory> ActionGameData::Factory = std::make_shared<ActionFactory>();

	ActionGameData::ActionGameData()
	{
		InitializeInstanceFields();
	}

	ActionGameData::ActionGameData( const std::shared_ptr<LevelSeedData> &LevelSeed, bool MakeInBackground )
	{
		InitializeInstanceFields();
		Init( LevelSeed, MakeInBackground );
	}

	void ActionGameData::Init( const std::shared_ptr<LevelSeedData> &LevelSeed, bool MakeInBackground )
	{
		GameData::Init();

		Seed = LevelSeed;

		AllowQuickJoin = false;

		Loading = false;
		LevelSeed->Loaded->setval( true );
		LevelSeed->MyGame = this;

		MyLevel = MakeEmptyLevel();
	}

	void ActionGameData::PhsxStep()
	{
		GameData::PhsxStep();

		if ( !ActionTaken )
		{
			if ( Seed->PostMake != 0 )
				Seed->PostMake->Apply( MyLevel );

			ActionTaken = true;
		}

		if ( Done )
		{
		}
	}

	void ActionGameData::PostDraw()
	{
		GameData::PostDraw();
	}

	void ActionGameData::Draw()
	{
		Tools::TheGame->MyGraphicsDevice->Clear( Color::Black );

		GameData::Draw();
	}

	void ActionGameData::Release()
	{
		GameData::Release();

		Seed.reset();
	}

	std::shared_ptr<Level> ActionGameData::MakeEmptyLevel()
	{
		std::shared_ptr<Level> level = std::make_shared<Level>();
		level->setMainCamera( std::make_shared<Camera>() );
		level->CurPiece = level->StartNewPiece( 0, 0, 4 );
		level->CurPiece->StartData[ 0 ].Position = Vector2( 0, 0 );
		level->getMainCamera()->BLCamBound = Vector2(-100000, 0);
		level->getMainCamera()->TRCamBound = Vector2(100000, 0);
		level->getMainCamera()->Update();
		level->TimeLimit = -1;

		level->MyBackground = std::make_shared<RegularBackground>();
		level->MyBackground->Init( level );

		level->MyGame = this;

		return level;
	}

	void ActionGameData::MakeBobs( const std::shared_ptr<Level> &level )
	{
	}

	void ActionGameData::UpdateBobs()
	{
	}

	void ActionGameData::Reset()
	{
	}

	void ActionGameData::InitializeInstanceFields()
	{
		Done = false;
		ActionTaken = false;
	}
}
