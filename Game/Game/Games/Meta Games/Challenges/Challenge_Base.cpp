#include <global_header.h>






namespace CloudberryKingdom
{

	void AftermathData::InitializeInstanceFields()
	{
		Retry = false;
	}

	Challenge::ShowEndScreenProxy::ShowEndScreenProxy( const std::shared_ptr<Challenge> &challenge )
	{
		this->challenge = challenge;
	}

	void Challenge::ShowEndScreenProxy::Apply()
	{
		challenge->ShowEndScreen();
	}

std::shared_ptr<BobPhsx> Challenge::ChosenHero = 0;

	int Challenge::SetGameId()
	{
		int HeroId = Challenge::ChosenHero == 0 ? 0 : Challenge::ChosenHero->Id;

		GameId_Score = 100 * HeroId + GameTypeId;
		GameId_Level = 100 * HeroId + GameTypeId + LevelMask;
		return GameId_Score;
	}

	const std::shared_ptr<StringWorldGameData> &Challenge::getStringWorld() const
	{
		return static_cast<StringWorldGameData*>( Tools::WorldMap );
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
		std::shared_ptr<GameOverPanel> MyGameOverPanel = std::make_shared<GameOverPanel>( GameId_Score, GameId_Level );
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
		std::shared_ptr<AftermathData> data = Tools::CurrentAftermath;
	}

	void Challenge::SetGameParent( const std::shared_ptr<GameData> &game )
	{
		game->ParentGame = Tools::CurGameData;
		Tools::WorldMap = Tools::CurGameData = game;
		Tools::CurLevel = game->MyLevel;
	}

	void Challenge::InitializeInstanceFields()
	{
		const int tempVector[] = { 1, 50, 100, 150 };
		std::vector<int> temp_StartLevels = std::vector<int>( tempVector, tempVector + sizeof( tempVector ) / sizeof( tempVector[ 0 ] ) );
		for ( int element = 0; element < sizeof( temp_StartLevels ) / sizeof( temp_StartLevels[ 0 ] ); element++ )
			StartLevels[ element ] = temp_StartLevels[ element ];
		NonCampaign = true;
	}
}
