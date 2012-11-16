#include <global_header.h>

namespace CloudberryKingdom
{

	LevelSequence::OnLevelBeginLambda::OnLevelBeginLambda( const std::shared_ptr<LevelSequence> &ls )
	{
		this->ls = ls;
	}

	bool LevelSequence::OnLevelBeginLambda::Apply( const std::shared_ptr<Level> &level )
	{
		return ls->OnLevelBegin( level );
	}

	LevelSequence::LevelSequence()
	{
		InitializeInstanceFields();
		MakeSeedList();
	}

	void LevelSequence::MakeSeedList()
	{
		for ( int i = 0; i < 500; i++ )
			Seeds.push_back( StringConverterHelper::toString( i ) );
	}

	void LevelSequence::Start( int StartLevel )
	{
	#if defined(DEBUG)
		// For debug purposes we reload the list of seeds each time, so that hot modifications can be made.
		Seeds.clear();
		MakeSeedList();
	#endif

		StartIndex = StartLevel;

		// Create the string world, and add the relevant game objects
		MyStringWorld = std::make_shared<StringWorldGameData>( std::make_shared<Func>( this, &LevelSequence::GetSeed ) );
		MyStringWorld->StartLevelMusic.reset();

		// OnLevelBegin preprocessing for each level.
		//MyStringWorld.OnLevelBegin += OnLevelBegin;
		MyStringWorld->OnLevelBegin = std::make_shared<OnLevelBeginLambda>( this );

		// Additional preprocessing
		SetGameParent( MyStringWorld );
		AdditionalPreStart();

		// Start
		MyStringWorld->Init( StartLevel );
	}

	bool LevelSequence::OnLevelBegin( const std::shared_ptr<Level> &level )
	{
		if ( dynamic_cast<ActionGameData*>( level->MyGame ) != 0 )
			return true;

		level->MyGame->AddGameObject( InGameStartMenu::MakeListener() );
		return false;
	}

	void LevelSequence::SetGameParent( const std::shared_ptr<GameData> &game )
	{
		game->ParentGame = Tools::CurGameData;
		Tools::WorldMap = Tools::CurGameData = game;
		Tools::CurLevel = game->MyLevel;
	}

	void LevelSequence::AdditionalPreStart()
	{
	}

	std::shared_ptr<LevelSeedData> LevelSequence::GetSeed( int Index )
	{
		std::shared_ptr<LevelSeedData> seed = std::make_shared<LevelSeedData>();
		seed->ReadString( Seeds[ Index ] );

		//seed.PostMake = null;

		return seed;
	}

	void LevelSequence::InitializeInstanceFields()
	{
		Seeds = std::vector<std::wstring>( 600 );
	}
}
