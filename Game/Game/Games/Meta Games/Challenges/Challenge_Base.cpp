#include <global_header.h>

#include <Hacks\List.h>

namespace CloudberryKingdom
{

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
		if ( NonCampaign )
			PlayerManager::setCoinsSpent( 0 );

		DifficultySelected = Difficulty;
	}

	void Challenge::Aftermath()
	{
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
