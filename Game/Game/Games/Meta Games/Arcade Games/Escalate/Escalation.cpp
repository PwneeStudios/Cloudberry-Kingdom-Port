#include <global_header.h>

#include <Hacks/List.h>
#include <Hacks/String.h>

#include <MasterHack.h>

namespace CloudberryKingdom
{

	void Challenge_Escalation::InitializeStatics()
	{
		int tempVector[] = { 15, 15, 15, 15, 15 };
		Challenge_Escalation::NumLives = VecFromArray( tempVector );
		
		Challenge_Escalation::instance = boost::make_shared<Challenge_Escalation>();

		std::wstring tempVector2[] = { std::wstring( L"hills" ), std::wstring( L"forest" ), std::wstring( L"cloud" ), std::wstring( L"cave" ), std::wstring( L"castle" ), std::wstring( L"sea" ) };
		Challenge_Escalation::tilesets = VecFromArray( tempVector2 );
	}

	// Statics
	std::vector<int> Challenge_Escalation::NumLives;

	boost::shared_ptr<Challenge_Escalation> Challenge_Escalation::instance;

	std::vector<std::wstring> Challenge_Escalation::tilesets;



	Challenge_Escalation::OnOutOfLivesLambda::OnOutOfLivesLambda( const boost::shared_ptr<Challenge> &challenge )
	{
		this->challenge = challenge;
	}

	void Challenge_Escalation::OnOutOfLivesLambda::Apply( const boost::shared_ptr<GUI_LivesLeft> &Lives )
	{
		boost::shared_ptr<GameData> game = Lives->MyGame;
		boost::shared_ptr<Level> level = game->MyLevel;

		level->setPreventReset( true );
		level->setSetToReset( false );

		// End the level
		level->EndLevel();

		// Special explode
		for ( std::vector<boost::shared_ptr<Bob> >::const_iterator bob = level->Bobs.begin(); bob != level->Bobs.end(); ++bob )
			ParticleEffects::PiecePopFart( level, ( *bob )->getCore()->Data.Position );

		// Add the Game Over panel, check for Awardments
		game->WaitThenDo( 50, boost::make_shared<ShowEndScreenProxy>( challenge ) );
	}

	Challenge_Escalation::OnBeginLambda::OnBeginLambda()
	{
	}

	bool Challenge_Escalation::OnBeginLambda::Apply( const boost::shared_ptr<Level> &level )
	{
		level->MyGame->AddGameObject( HelpMenu::MakeListener() );
		level->MyGame->AddGameObject( InGameStartMenu::MakeListener() );
		return false;
	}

	Challenge_Escalation::OnSwapLambda::OnSwapLambda( const boost::shared_ptr<Challenge_Escalation> &ch )
	{
		this->ch = ch;
	}

	void Challenge_Escalation::OnSwapLambda::Apply( const boost::shared_ptr<LevelSeedData> &data )
	{
		data->MyGame->AddGameObject( boost::make_shared<Escalation_Tutorial>( ch ) );
	}

	Challenge_Escalation::ScoreMultiplierHelper::ScoreMultiplierHelper( float multiplier )
	{
		this->multiplier = multiplier;
	}

	void Challenge_Escalation::ScoreMultiplierHelper::Apply( const boost::shared_ptr<GameData> &game )
	{
		game->ScoreMultiplier *= multiplier;
	}

	Challenge_Escalation::AdditionalPreStartOnSwapToLevelHelper::AdditionalPreStartOnSwapToLevelHelper( const boost::shared_ptr<Challenge_Escalation> &ce )
	{
		this->ce = ce;
	}

	void Challenge_Escalation::AdditionalPreStartOnSwapToLevelHelper::Apply( const int &levelindex )
	{
		Awardments::CheckForAward_Escalation_Level( levelindex - ce->StartIndex );

		// Score multiplier, x1, x1.5, x2, ... for levels 0, 20, 40, ...
		float multiplier = 1 + ( ( levelindex + 1 ) / ce->LevelsPerDifficulty ) *.5f;
		Tools::CurGameData->OnCalculateScoreMultiplier->Add( boost::make_shared<ScoreMultiplierHelper>( multiplier ) );

		ce->OnSwapTo_GUI( levelindex );
	}

	void Challenge_Escalation::MakeMyModParamsHelper::Apply( const boost::shared_ptr<Level> &level, const boost::shared_ptr<PieceSeedData> &p )
	{
		boost::shared_ptr<Coin_Parameters> Params = boost::dynamic_pointer_cast<Coin_Parameters>( p->Style->FindParams( Coin_AutoGen::getInstance() ) );
		Params->StartFrame = 90;
		Params->FillType = Coin_Parameters::FillTypes_REGULAR;
	}

	const boost::shared_ptr<Challenge_Escalation> &Challenge_Escalation::getInstance()
	{
		return instance;
	}

	Challenge_Escalation::Challenge_Escalation()
	{
		InitializeInstanceFields();
		GameTypeId = 0;
		MenuName = Name = Localization::Words_ESCALATION;
	}

	void Challenge_Escalation::Start( int StartLevel )
	{
		Challenge::Start( StartLevel );

		PlayerManager::setCoinsSpent( -100 );

		i = StartIndex = StartLevel;

		// Create the lives counter
		Gui_LivesLeft = MakeMagic( GUI_LivesLeft, ( GetLives() ) );

		// Set the time expired function
		Gui_LivesLeft->OnOutOfLives->Add( boost::make_shared<OnOutOfLivesLambda>( boost::static_pointer_cast<Challenge>( shared_from_this() ) ) );

		// Create the string world, and add the relevant game objects
		boost::shared_ptr<PassGetSeedAsLambda> _GetSeed = boost::make_shared<PassGetSeedAsLambda>( boost::static_pointer_cast<Challenge>( shared_from_this() ) );
		
		boost::shared_ptr<LambdaFunc_1<int, boost::shared_ptr<LevelSeedData> > > __GetSeed =
			boost::static_pointer_cast<LambdaFunc_1<int, boost::shared_ptr<LevelSeedData> > >( _GetSeed );

		MyStringWorld = boost::make_shared<StringWorldEndurance>( __GetSeed, Gui_LivesLeft, 25 );
		StringWorldEndurance_Construct( MyStringWorld, __GetSeed, Gui_LivesLeft, 25 );

		Escalation_Tutorial::setWatchedOnce( true );
		if ( !Escalation_Tutorial::getWatchedOnce() )
			MyStringWorld->FirstDoorAction = false;

		MyStringWorld->StartLevelMusic.reset();

		// Start menu
		MyStringWorld->OnLevelBegin = boost::make_shared<OnBeginLambda>();

		// Additional preprocessing
		SetGameParent( MyStringWorld );
		AdditionalPreStart();

		// Start
		MyStringWorld->Init( StartLevel );
	}

	void Challenge_Escalation::PreStart_Tutorial()
	{
		MyStringWorld->OnSwapToFirstLevel->Add( boost::make_shared<OnSwapLambda>( boost::static_pointer_cast<Challenge_Escalation>( shared_from_this() ) ) );
	}

	int Challenge_Escalation::GetLives()
	{
		int Difficulty = ( StartIndex + 1 ) / 50;
		return NumLives[ Difficulty ];
	}

	void Challenge_Escalation::AdditionalPreStart()
	{
		// Tutorial
		PreStart_Tutorial();

		// When a new level is swapped to...
		MyStringWorld->OnSwapToLevel->Add( boost::make_shared<AdditionalPreStartOnSwapToLevelHelper>( boost::static_pointer_cast<Challenge_Escalation>( shared_from_this() ) ) );
	}

	void Challenge_Escalation::OnSwapTo_GUI( int levelindex )
	{
		// Multiplier increase text
		if ( ( levelindex + 1 ) % LevelsPerDifficulty == 0 )
			Tools::CurGameData->AddGameObject( MakeMagic( MultiplierUp, () ) );

		// Mod number of coins

		// Reset time after death
		Tools::CurGameData->SetDeathTime( GameData::DeathTime_NORMAL );

		if ( levelindex > StartIndex )
		{
			Tools::Warning();
			boost::shared_ptr<LevelTitle> title = MakeMagic( LevelTitle, ( Format( _T( "%ls %d" ), Localization::WordString( Localization::Words_LEVEL ).c_str(), levelindex + 1 ) ) );
			Tools::CurGameData->AddGameObject( title );

			if ( ( levelindex + 1 ) % LevelsPerDifficulty == 0 )
				CkColorHelper::_x_x_Red( title->text );
		}

		// Hero title
		//var g = Tools.CurGameData;
		//g.AddGameObject(new LevelTitle(g.MyLevel.DefaultHeroType.Name, new Vector2(150, -300), .7f, true));
	}

	boost::shared_ptr<LevelSeedData> Challenge_Escalation::GetSeed( int Index )
	{
		std::vector<float> lerp_vec;

		lerp_vec.push_back(-.5f);
		lerp_vec.push_back(0);
		lerp_vec.push_back(1);
		lerp_vec.push_back(2);
		lerp_vec.push_back(2.5f);
		lerp_vec.push_back(3);
		lerp_vec.push_back(3.5f);
		lerp_vec.push_back(4);
		lerp_vec.push_back(4.5f);

		float difficulty = CoreMath::MultiLerpRestrict( Index / static_cast<float>( LevelsPerDifficulty ), lerp_vec );
		boost::shared_ptr<CloudberryKingdom::LevelSeedData> seed = Make( Index, difficulty );

		return seed;
	}

	boost::shared_ptr<TileSet> Challenge_Escalation::GetTileSet( int i )
	{
		return TileSet::Get( tilesets[ ( i / LevelsPerTileset ) % tilesets.size() ] );
	}

	boost::shared_ptr<BobPhsx> Challenge_Escalation::GetHero( int i )
	{
		return Challenge::ChosenHero;
	}

	boost::shared_ptr<LevelSeedData> Challenge_Escalation::Make( int Index, float Difficulty )
	{
		boost::shared_ptr<BobPhsx> hero = GetHero( Index );

		// Adjust the length. Longer for higher levels.
		int Length;
		float t = ( ( Index - StartIndex ) % LevelsPerTileset ) / static_cast<float>( LevelsPerTileset - 1 );
		Length = CoreMath::LerpRestrict( LevelLength_Short, LevelLength_Long, t );

		if ( boost::dynamic_pointer_cast<BobPhsxSpaceship>( hero ) != 0 )
			Length += 2000;

		// Create the LevelSeedData
		boost::shared_ptr<LevelSeedData> data = RegularLevel::HeroLevel( Difficulty, hero, Length );
		data->SetTileSet( GetTileSet( Index - StartIndex ) );

		// Adjust the piece seed data
		for ( std::vector<boost::shared_ptr<PieceSeedData> >::const_iterator piece = data->PieceSeeds.begin(); piece != data->PieceSeeds.end(); ++piece )
		{
			// Shorten the initial computer delay
			( *piece )->Style->ComputerWaitLengthRange = Vector2( 8, 35 ); //38);

			( *piece )->Style->MyModParams->Add( boost::make_shared<MakeMyModParamsHelper>() );
		}

		return data;
	}

	void Challenge_Escalation::InitializeInstanceFields()
	{
		i = 0;
		StartIndex = 0;
		LevelsPerDifficulty = 20;
		LevelsPerTileset = 5;
		LevelLength_Short = 5500;
		LevelLength_Long = 7500;
	}
}
