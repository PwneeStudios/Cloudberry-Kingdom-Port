#include <global_header.h>

namespace CloudberryKingdom
{

	StringWorldEndurance::OnSwapLambda::OnSwapLambda( const std::shared_ptr<StringWorldEndurance> &ch )
	{
		this->ch = ch;
	}

	void StringWorldEndurance::OnSwapLambda::Apply( const std::shared_ptr<LevelSeedData> &data )
	{
		data->MyGame->AddGameObject( ch->Gui_LivesLeft );
		data->MyGame->AddGameObject( ch->Gui_NextLife );
		data->MyGame->AddGameObject( ch->Gui_Lives );
		data->MyGame->AddGameObject( ch->MyCoinScoreMultiplier );
		data->MyGame->AddGameObject( std::make_shared<PerfectScoreObject>( false, true ) );
		data->MyGame->AddGameObject( ch->MyGUI_Score );
			//, MyGUI_Level
	}

	StringWorldEndurance::StringWorldEndurance( const std::shared_ptr<LambdaFunc_1<int, std::shared_ptr<LevelSeedData> > > &GetSeed, const std::shared_ptr<GUI_LivesLeft> &Gui_LivesLeft, int NextLife ) :
		StringWorldGameData( GetSeed )
	{
		// StringWorldEndurance_Construct.

		// Lives
		/*this->Gui_LivesLeft = Gui_LivesLeft;
		Gui_Lives = std::make_shared<GUI_Lives>( Gui_LivesLeft );
		Gui_NextLife = std::make_shared<GUI_NextLife>( NextLife, Gui_LivesLeft );

		// Coin score multiplier
		MyCoinScoreMultiplier = std::make_shared<CoinScoreMultiplierObject>();

		// Level and Score
		MyGUI_Score = std::make_shared<GUI_Score>();
		MyGUI_Level = std::make_shared<GUI_Level>();

		// Add game objects, including 'Perfect' watcher
		OnSwapToFirstLevel->Add( std::make_shared<OnSwapLambda>( std::static_pointer_cast<StringWorldEndurance>( shared_from_this() ) ) );*/
	}

	void StringWorldEndurance::Release()
	{
		StringWorldGameData::Release();

		Gui_LivesLeft->ForceRelease();
		Gui_NextLife->ForceRelease();
	}

	void StringWorldEndurance::AdditionalSwapToLevelProcessing( const std::shared_ptr<GameData> &game )
	{
		StringWorldGameData::AdditionalSwapToLevelProcessing( game );

		//game.TakeOnce = true;

		// Should we give the player points for coins even if they die?
		//game.AlwaysGiveCoinScore = true;
		game->AlwaysGiveCoinScore = false;
	}
}
