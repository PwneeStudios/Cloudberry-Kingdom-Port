#include <global_header.h>

#include <MasterHack.h>

namespace CloudberryKingdom
{

	PassGetSeedAsLambda_LevelSequence::PassGetSeedAsLambda_LevelSequence( const boost::shared_ptr<LevelSequence> &ls )
	{
		this->ls = ls;
	}

	boost::shared_ptr<LevelSeedData> PassGetSeedAsLambda_LevelSequence::Apply( const int &index )
	{
		return ls->GetSeed( index );
	}

	LevelSequence::OnLevelBeginLambda::OnLevelBeginLambda( const boost::shared_ptr<LevelSequence> &ls )
	{
		this->ls = ls;
	}

	bool LevelSequence::OnLevelBeginLambda::Apply( const boost::shared_ptr<Level> &level )
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
		boost::shared_ptr<PassGetSeedAsLambda_LevelSequence> _GetSeed = boost::make_shared<PassGetSeedAsLambda_LevelSequence>( shared_from_this() );

		boost::shared_ptr<LambdaFunc_1<int, boost::shared_ptr<LevelSeedData> > > __GetSeed =
			boost::static_pointer_cast<LambdaFunc_1<int, boost::shared_ptr<LevelSeedData> > >( _GetSeed );

		MyStringWorld = boost::make_shared<StringWorldGameData>( __GetSeed );
		StringWorldGameData_Construct( MyStringWorld, __GetSeed );

		MyStringWorld->StartLevelMusic.reset();

		// OnLevelBegin preprocessing for each level.
		//MyStringWorld.OnLevelBegin += OnLevelBegin;
		MyStringWorld->OnLevelBegin = boost::make_shared<OnLevelBeginLambda>( shared_from_this() );

		// Additional preprocessing
		SetGameParent( MyStringWorld );
		AdditionalPreStart();

		// Start
		MyStringWorld->Init( StartLevel );
	}

	bool LevelSequence::OnLevelBegin( const boost::shared_ptr<Level> &level )
	{
		if ( boost::dynamic_pointer_cast<ActionGameData>( level->MyGame ) != 0 )
			return true;

		level->MyGame->AddGameObject( InGameStartMenu::MakeListener() );
		return false;
	}

	void LevelSequence::SetGameParent( const boost::shared_ptr<GameData> &game )
	{
		game->ParentGame = Tools::CurGameData;
		Tools::WorldMap = Tools::CurGameData = game;
		Tools::CurLevel = game->MyLevel;
	}

	void LevelSequence::AdditionalPreStart()
	{
	}

	boost::shared_ptr<LevelSeedData> LevelSequence::GetSeed( int Index )
	{
		boost::shared_ptr<LevelSeedData> seed = boost::make_shared<LevelSeedData>();
		seed->ReadString( Seeds[ Index ] );

		//seed.PostMake = null;

		return seed;
	}

	void LevelSequence::InitializeInstanceFields()
	{
		Seeds = std::vector<std::wstring>( );
		Seeds.reserve( 600 );
	}
}
