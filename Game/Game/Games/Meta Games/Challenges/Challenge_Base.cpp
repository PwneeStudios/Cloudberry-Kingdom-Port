#include <global_header.h>

#include <Hacks\List.h>

#include <Game/CloudberryKingdom/CloudberryKingdom.CloudberryKingdomGame.h>

namespace CloudberryKingdom
{

	int Challenge::Coins = 0;
	int Challenge::CurrentScore = 0;
	int Challenge::CurrentId = 0;
	int Challenge::LeaderboardIndex = 0;

	void Challenge::OnCoinGrabProxy::Apply( const boost::shared_ptr<ObjectBase> &obj )
	{
		Challenge::Coins++;
	}

	void AftermathData::InitializeInstanceFields()
	{
		Success = false;
		EarlyExit = false;
		Retry = false;
	}

	Challenge::PassGetSeedAsLambda::PassGetSeedAsLambda( const boost::shared_ptr<Challenge> &challenge )
	{
		this->challenge = challenge;
	}

	boost::shared_ptr<LevelSeedData> Challenge::PassGetSeedAsLambda::Apply( const int &index )
	{
		return challenge->GetSeed( index );
	}

	Challenge::ShowEndScreenProxy::ShowEndScreenProxy( const boost::shared_ptr<Challenge> &challenge )
	{
		this->challenge = challenge;
	}

	void Challenge::ShowEndScreenProxy::Apply()
	{
		challenge->ShowEndScreen();
	}

	boost::shared_ptr<BobPhsx> Challenge::ChosenHero = 0;

    int Challenge::CalcTopGameLevel(boost::shared_ptr<BobPhsx> hero)
    {
        int id = CalcGameId_Level(hero);
        return PlayerManager::MaxPlayerHighScore(id);
    }

    int Challenge::CalcGameId_Score( boost::shared_ptr<BobPhsx> hero )
    {
        int HeroId = hero == 0 ? 0 : hero->Id;

		//GameId_Level = 100 * HeroId + GameTypeId;
		//return GameId_Level;
		return 100 * HeroId + GameTypeId;
    }

    int Challenge::CalcGameId_Level(boost::shared_ptr<BobPhsx> hero)
    {
        int HeroId = hero == 0 ? 0 : hero->Id;

		//GameId_Level = 100 * HeroId + GameTypeId + LevelMask;
		//return GameId_Level;
		return 100 * HeroId + GameTypeId + LevelMask;
	}

	int Challenge::SetGameId()
	{
		int HeroId = Challenge::ChosenHero == 0 ? 0 : Challenge::ChosenHero->Id;

		GameId_Score = 100 * HeroId + GameTypeId;
		GameId_Level = 100 * HeroId + GameTypeId + LevelMask;
		return GameId_Score;
	}

	const boost::shared_ptr<StringWorldGameData> Challenge::getStringWorld() const
	{
		return boost::static_pointer_cast<StringWorldGameData>( Tools::WorldMap );
	}

	int Challenge::TopScore()
	{
		SetGameId();
		return ScoreDatabase::Max( GameId_Score )->Score;
	}

	int Challenge::TopLevel()
	{
		SetGameId();
		return ScoreDatabase::Max( GameId_Level )->Level_Renamed;
	}

	int Challenge::TopPlayerScore()
	{
		SetGameId();
		return PlayerManager::MaxPlayerHighScore( GameId_Score );
	}

    int Challenge::TopPlayerScore(boost::shared_ptr<BobPhsx> hero)
    {
        SetGameId();
        return PlayerManager::MaxPlayerHighScore(GameId_Score);
    }

	int Challenge::TopPlayerLevel()
	{
		SetGameId();
		return PlayerManager::MaxPlayerHighScore( GameId_Level );
	}

	void Challenge::ShowEndScreen()
	{
		boost::shared_ptr<GameOverPanel> MyGameOverPanel = MakeMagic( GameOverPanel, ( GameId_Score, GameId_Level ) );
		MyGameOverPanel->Levels = getStringWorld()->CurLevelIndex + 1;

		Tools::CurGameData->AddGameObject( MyGameOverPanel );
	}

	void Challenge::Start( int Difficulty )
	{
        CloudberryKingdomGame::PromptForDeviceIfNoneSelected();

		HelpMenu::CostMultiplier = 1;

        CurrentId = GameId_Level;
        CurrentScore = 0;

        PlayerManager::PartiallyInvisible = true;
        PlayerManager::TotallyInvisible = true;

        Coins = 0;

		if ( NonCampaign )
			PlayerManager::setCoinsSpent( 0 );

		DifficultySelected = Difficulty;
	}

	void Challenge::Aftermath()
	{
        CurrentId = -1;
        CurrentScore = -1;
		boost::shared_ptr<AftermathData> data = Tools::CurrentAftermath;
	}

	void Challenge::SetGameParent( const boost::shared_ptr<GameData> &game )
	{
		game->ParentGame = Tools::CurGameData;
		Tools::WorldMap = Tools::CurGameData = game;
		Tools::CurLevel = game->MyLevel;
	}

	void Challenge::InitializeInstanceFields()
	{
		int tempVector[] = { 1, 50, 100, 150 };
		StartLevels = VecFromArray( tempVector );

		NonCampaign = true;
	}
}
