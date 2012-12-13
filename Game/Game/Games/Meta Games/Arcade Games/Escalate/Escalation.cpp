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
		
		Challenge_Escalation::instance = std::make_shared<Challenge_Escalation>();

		std::wstring tempVector2[] = { _T( "hills" ), _T( "forest" ), _T( "cloud" ), _T( "cave" ), _T( "castle" ), _T( "sea" ) };
		Challenge_Escalation::tilesets = VecFromArray( tempVector2 );
	}

	// Statics
	std::vector<int> Challenge_Escalation::NumLives;

	std::shared_ptr<Challenge_Escalation> Challenge_Escalation::instance;

	std::vector<std::wstring> Challenge_Escalation::tilesets;



	Challenge_Escalation::OnOutOfLivesLambda::OnOutOfLivesLambda( const std::shared_ptr<Challenge> &challenge )
	{
		this->challenge = challenge;
	}

	void Challenge_Escalation::OnOutOfLivesLambda::Apply( const std::shared_ptr<GUI_LivesLeft> &Lives )
	{
		std::shared_ptr<GameData> game = Lives->MyGame;
		std::shared_ptr<Level> level = game->MyLevel;

		level->setPreventReset( true );
		level->setSetToReset( false );

		// End the level
		level->EndLevel();

		// Special explode
		for ( std::vector<std::shared_ptr<Bob> >::const_iterator bob = level->Bobs.begin(); bob != level->Bobs.end(); ++bob )
			ParticleEffects::PiecePopFart( level, ( *bob )->getCore()->Data.Position );

		// Add the Game Over panel, check for Awardments
		game->WaitThenDo( 50, std::make_shared<ShowEndScreenProxy>( challenge ) );
	}

	Challenge_Escalation::OnBeginLambda::OnBeginLambda()
	{
	}

	bool Challenge_Escalation::OnBeginLambda::Apply( const std::shared_ptr<Level> &level )
	{
		level->MyGame->AddGameObject( HelpMenu::MakeListener() );
		level->MyGame->AddGameObject( InGameStartMenu::MakeListener() );
		return false;
	}

	Challenge_Escalation::OnSwapLambda::OnSwapLambda( const std::shared_ptr<Challenge_Escalation> &ch )
	{
		this->ch = ch;
	}

	void Challenge_Escalation::OnSwapLambda::Apply( const std::shared_ptr<LevelSeedData> &data )
	{
		data->MyGame->AddGameObject( std::make_shared<Escalation_Tutorial>( ch ) );
	}

	Challenge_Escalation::ScoreMultiplierHelper::ScoreMultiplierHelper( float multiplier )
	{
		this->multiplier = multiplier;
	}

	void Challenge_Escalation::ScoreMultiplierHelper::Apply( const std::shared_ptr<GameData> &game )
	{
		game->ScoreMultiplier *= multiplier;
	}

	Challenge_Escalation::AdditionalPreStartOnSwapToLevelHelper::AdditionalPreStartOnSwapToLevelHelper( const std::shared_ptr<Challenge_Escalation> &ce )
	{
		this->ce = ce;
	}

	void Challenge_Escalation::AdditionalPreStartOnSwapToLevelHelper::Apply( const int &levelindex )
	{
		Awardments::CheckForAward_Escalation_Level( levelindex - ce->StartIndex );

		// Score multiplier, x1, x1.5, x2, ... for levels 0, 20, 40, ...
		float multiplier = 1 + ( ( levelindex + 1 ) / ce->LevelsPerDifficulty ) *.5f;
		Tools::CurGameData->OnCalculateScoreMultiplier->Add( std::make_shared<ScoreMultiplierHelper>( multiplier ) );

		ce->OnSwapTo_GUI( levelindex );
	}

	void Challenge_Escalation::MakeMyModParamsHelper::Apply( const std::shared_ptr<Level> &level, const std::shared_ptr<PieceSeedData> &p )
	{
		std::shared_ptr<Coin_Parameters> Params = std::dynamic_pointer_cast<Coin_Parameters>( p->Style->FindParams( Coin_AutoGen::getInstance() ) );
		Params->StartFrame = 90;
		Params->FillType = Coin_Parameters::FillTypes_REGULAR;
	}

	const std::shared_ptr<Challenge_Escalation> &Challenge_Escalation::getInstance()
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
		Gui_LivesLeft->OnOutOfLives->Add( std::make_shared<OnOutOfLivesLambda>( std::static_pointer_cast<Challenge>( shared_from_this() ) ) );

		// Create the string world, and add the relevant game objects
		std::shared_ptr<PassGetSeedAsLambda> _GetSeed = std::make_shared<PassGetSeedAsLambda>( std::static_pointer_cast<Challenge>( shared_from_this() ) );
		
		std::shared_ptr<LambdaFunc_1<int, std::shared_ptr<LevelSeedData> > > __GetSeed =
			std::static_pointer_cast<LambdaFunc_1<int, std::shared_ptr<LevelSeedData> > >( _GetSeed );

		MyStringWorld = std::make_shared<StringWorldEndurance>( __GetSeed, Gui_LivesLeft, 25 );
		StringWorldEndurance_Construct( MyStringWorld, __GetSeed, Gui_LivesLeft, 25 );

		Escalation_Tutorial::setWatchedOnce( true );
		if ( !Escalation_Tutorial::getWatchedOnce() )
			MyStringWorld->FirstDoorAction = false;

		MyStringWorld->StartLevelMusic.reset();

		// Start menu
		MyStringWorld->OnLevelBegin = std::make_shared<OnBeginLambda>();

		// Additional preprocessing
		SetGameParent( MyStringWorld );
		AdditionalPreStart();

		// Start
		MyStringWorld->Init( StartLevel );
	}

	void Challenge_Escalation::PreStart_Tutorial()
	{
		MyStringWorld->OnSwapToFirstLevel->Add( std::make_shared<OnSwapLambda>( std::static_pointer_cast<Challenge_Escalation>( shared_from_this() ) ) );
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
		MyStringWorld->OnSwapToLevel->Add( std::make_shared<AdditionalPreStartOnSwapToLevelHelper>( std::static_pointer_cast<Challenge_Escalation>( shared_from_this() ) ) );
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
			std::shared_ptr<LevelTitle> title = MakeMagic( LevelTitle, ( Format( _T( "%ls %d" ), Localization::WordString( Localization::Words_LEVEL ).c_str(), levelindex + 1 ) ) );
			Tools::CurGameData->AddGameObject( title );

			if ( ( levelindex + 1 ) % LevelsPerDifficulty == 0 )
				CkColorHelper::_x_x_Red( title->text );
		}

		// Hero title
		//var g = Tools.CurGameData;
		//g.AddGameObject(new LevelTitle(g.MyLevel.DefaultHeroType.Name, new Vector2(150, -300), .7f, true));
	}

	std::shared_ptr<LevelSeedData> Challenge_Escalation::GetSeed( int Index )
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
		std::shared_ptr<CloudberryKingdom::LevelSeedData> seed = Make( Index, difficulty );

		return seed;
	}

	std::shared_ptr<TileSet> Challenge_Escalation::GetTileSet( int i )
	{
		return TileSet::Get( tilesets[ ( i / LevelsPerTileset ) % tilesets.size() ] );
	}

	std::shared_ptr<BobPhsx> Challenge_Escalation::GetHero( int i )
	{
		return Challenge::ChosenHero;
	}

	std::shared_ptr<LevelSeedData> Challenge_Escalation::Make( int Index, float Difficulty )
	{
		std::shared_ptr<BobPhsx> hero = GetHero( Index );

		// Adjust the length. Longer for higher levels.
		int Length;
		float t = ( ( Index - StartIndex ) % LevelsPerTileset ) / static_cast<float>( LevelsPerTileset - 1 );
		Length = CoreMath::LerpRestrict( LevelLength_Short, LevelLength_Long, t );

		if ( std::dynamic_pointer_cast<BobPhsxSpaceship>( hero ) != 0 )
			Length += 2000;

		// Create the LevelSeedData
		std::shared_ptr<LevelSeedData> data = RegularLevel::HeroLevel( Difficulty, hero, Length );
		data->SetTileSet( GetTileSet( Index - StartIndex ) );

		// Adjust the piece seed data
		for ( std::vector<std::shared_ptr<PieceSeedData> >::const_iterator piece = data->PieceSeeds.begin(); piece != data->PieceSeeds.end(); ++piece )
		{
			// Shorten the initial computer delay
			( *piece )->Style->ComputerWaitLengthRange = Vector2( 8, 35 ); //38);

			( *piece )->Style->MyModParams->Add( std::make_shared<MakeMyModParamsHelper>() );
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
