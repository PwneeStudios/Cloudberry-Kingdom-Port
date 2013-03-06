#include <global_header.h>

namespace CloudberryKingdom
{

	StringWorldEndurance::OnSwapLambda::OnSwapLambda( const boost::shared_ptr<StringWorldEndurance> &ch )
	{
		this->ch = ch;
	}

	void StringWorldEndurance::OnSwapLambda::Apply( const boost::shared_ptr<LevelSeedData> &data )
	{
		data->MyGame->AddGameObject( ch->Gui_LivesLeft );
		data->MyGame->AddGameObject( ch->Gui_NextLife );
		data->MyGame->AddGameObject( ch->Gui_Lives );
		data->MyGame->AddGameObject( ch->MyCoinScoreMultiplier );
		data->MyGame->AddGameObject( MakeMagic( PerfectScoreObject, ( false, true, false ) ) );
		data->MyGame->AddGameObject( ch->MyGUI_Score );
			//, MyGUI_Level
	}

	StringWorldEndurance::StringWorldEndurance( const boost::shared_ptr<LambdaFunc_1<int, boost::shared_ptr<LevelSeedData> > > &GetSeed, const boost::shared_ptr<GUI_LivesLeft> &Gui_LivesLeft, int NextLife ) :
		StringWorldGameData( GetSeed )
	{
		// StringWorldEndurance_Construct.

		// Lives
		/*this->Gui_LivesLeft = Gui_LivesLeft;
		Gui_Lives = boost::make_shared<GUI_Lives>( Gui_LivesLeft );
		Gui_NextLife = boost::make_shared<GUI_NextLife>( NextLife, Gui_LivesLeft );

		// Coin score multiplier
		MyCoinScoreMultiplier = boost::make_shared<CoinScoreMultiplierObject>();

		// Level and Score
		MyGUI_Score = boost::make_shared<GUI_Score>();
		MyGUI_Level = boost::make_shared<GUI_Level>();

		// Add game objects, including 'Perfect' watcher
		OnSwapToFirstLevel->Add( boost::make_shared<OnSwapLambda>( boost::static_pointer_cast<StringWorldEndurance>( shared_from_this() ) ) );*/
	}

	void StringWorldEndurance::AdditionalSetLevel()
	{
		StringWorldGameData::AdditionalSetLevel();

		NextLevelSeed->MyGame->MyLevel->SetBack( 3 );
	}

	void StringWorldEndurance::Release()
	{
		StringWorldGameData::Release();

		Gui_LivesLeft->ForceRelease();
		Gui_NextLife->ForceRelease();
	}

	void StringWorldEndurance::AdditionalSwapToLevelProcessing( const boost::shared_ptr<GameData> &game )
	{
		StringWorldGameData::AdditionalSwapToLevelProcessing( game );

		//game.TakeOnce = true;

		// Should we give the player points for coins even if they die?
		//game.AlwaysGiveCoinScore = true;
		game->AlwaysGiveCoinScore = false;
	}
}
