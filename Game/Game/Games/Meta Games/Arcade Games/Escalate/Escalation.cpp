#include <global_header.h>


namespace CloudberryKingdom
{

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
		for ( std::vector<Bob*>::const_iterator bob = level->Bobs.begin(); bob != level->Bobs.end(); ++bob )
			ParticleEffects::PiecePopFart( level, ( *bob )->getCore()->Data->Position );

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

	void Challenge_Escalation::AdditionalPreStartOnSwapToLevelHelper::Apply( int levelindex )
	{
		Awardments::CheckForAward_Escalation_Level( levelindex - ce->StartIndex );

		// Score multiplier, x1, x1.5, x2, ... for levels 0, 20, 40, ...
		float multiplier = 1 + ( ( levelindex + 1 ) / ce->LevelsPerDifficulty ) *.5f;
		Tools::CurGameData->OnCalculateScoreMultiplier->Add( std::make_shared<ScoreMultiplierHelper>( multiplier ) );

		ce->OnSwapTo_GUI( levelindex );
	}

	void Challenge_Escalation::MakeMyModParamsHelper::Apply( const std::shared_ptr<Level> &level, const std::shared_ptr<PieceSeedData> &p )
	{
		std::shared_ptr<Coin_Parameters> Params = static_cast<Coin_Parameters*>( p->Style->FindParams( Coin_AutoGen::getInstance() ) );
		Params->StartFrame = 90;
		Params->FillType = Coin_Parameters::FillTypes_REGULAR;
	}

const int tempVector[] = { 15, 15, 15, 15, 15 };
std::vector<int> Challenge_Escalation::NumLives = std::vector<int>( tempVector, tempVector + sizeof( tempVector ) / sizeof( tempVector[ 0 ] ) );
const std::shared_ptr<Challenge_Escalation> Challenge_Escalation::instance = std::make_shared<Challenge_Escalation>();

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
		Gui_LivesLeft = std::make_shared<GUI_LivesLeft>( GetLives() );

		// Set the time expired function
		Gui_LivesLeft->OnOutOfLives->Add( std::make_shared<OnOutOfLivesLambda>( this ) );

		// Create the string world, and add the relevant game objects
		MyStringWorld = std::make_shared<StringWorldEndurance>( std::make_shared<Func>( this, &Challenge_Escalation::GetSeed ), Gui_LivesLeft, 25 );

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
		MyStringWorld->OnSwapToFirstLevel->Add( std::make_shared<OnSwapLambda>( this ) );
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
		MyStringWorld->OnSwapToLevel->Add( std::make_shared<AdditionalPreStartOnSwapToLevelHelper>( this ) );
	}

	void Challenge_Escalation::OnSwapTo_GUI( int levelindex )
	{
		// Multiplier increase text
		if ( ( levelindex + 1 ) % LevelsPerDifficulty == 0 )
			Tools::CurGameData->AddGameObject( std::make_shared<MultiplierUp>() );

		// Mod number of coins

		// Reset time after death
		Tools::CurGameData->SetDeathTime( GameData::DeathTime_NORMAL );

		if ( levelindex > StartIndex )
		{
			Tools::Warning();
			std::shared_ptr<LevelTitle> title = std::make_shared<LevelTitle>( std::wstring::Format( _T( "{1} {0}" ), levelindex + 1, Localization::WordString( Localization::Words_LEVEL ) ) );
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
		float difficulty = CoreMath::MultiLerpRestrict( Index / static_cast<float>( LevelsPerDifficulty ), -.5f, 0, 1, 2, 2.5f, 3, 3.5f, 4, 4.5f );
		std::shared_ptr<CloudberryKingdom::LevelSeedData> seed = Make( Index, difficulty );

		return seed;
	}

const std::wstring tempVector2[] = { _T( "hills" ), _T( "forest" ), _T( "cloud" ), _T( "cave" ), _T( "castle" ), _T( "sea" ) };
std::vector<std::wstring> Challenge_Escalation::tilesets = std::vector<std::wstring>( tempVector2, tempVector2 + sizeof( tempVector2 ) / sizeof( tempVector2[ 0 ] ) );

	std::shared_ptr<TileSet> Challenge_Escalation::GetTileSet( int i )
	{
		return tilesets[ ( i / LevelsPerTileset ) % tilesets.size() ];
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

		if ( dynamic_cast<BobPhsxSpaceship*>( hero ) != 0 )
			Length += 2000;

		// Create the LevelSeedData
		std::shared_ptr<LevelSeedData> data = RegularLevel::HeroLevel( Difficulty, hero, Length );
		data->SetTileSet( GetTileSet( Index - StartIndex ) );

		// Adjust the piece seed data
		for ( std::vector<PieceSeedData*>::const_iterator piece = data->PieceSeeds.begin(); piece != data->PieceSeeds.end(); ++piece )
		{
			// Shorten the initial computer delay
			( *piece )->Style_COMPUTER_WAIT_LENGTH_RANGE = Vector2( 8, 35 ); //38);

			( *piece )->Style_MY_MOD_PARAMS->Add( std::make_shared<MakeMyModParamsHelper>() );
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
