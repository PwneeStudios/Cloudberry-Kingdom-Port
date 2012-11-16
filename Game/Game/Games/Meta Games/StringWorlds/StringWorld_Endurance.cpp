#include "StringWorld_Endurance.h"
#include "Game/Level/Make/CloudberryKingdom.LevelSeedData.h"
#include "Game/Objects/Game Objects/GameObjects/PerfectScoreObject.h"
#include "Game/Objects/Game Objects/GameObjects/GUI_Score.h"
#include "Game/Objects/Game Objects/GameObjects/GUI_Level.h"
#include "Game/Objects/Game Objects/GameObjects/GUI_LivesLeft.h"
#include "Game/Objects/Game Objects/GameObjects/GUI_Lives.h"
#include "Game/Objects/Game Objects/GameObjects/GUI_NextLife.h"
#include "Game/Objects/Game Objects/GameObjects/CoinScoreMultiplierObject.h"
#include "Game/Games/GameType.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;

namespace CloudberryKingdom
{

	StringWorldEndurance::OnSwapLambda::OnSwapLambda( const std::shared_ptr<StringWorldEndurance> &ch )
	{
		this->ch = ch;
	}

	void StringWorldEndurance::OnSwapLambda::Apply( const std::shared_ptr<LevelSeedData> &data )
	{
		data->MyGame->AddGameObject( ch->Gui_LivesLeft, ch->Gui_NextLife, ch->Gui_Lives, ch->MyCoinScoreMultiplier, std::make_shared<PerfectScoreObject>( false, true ), ch->MyGUI_Score );
			//, MyGUI_Level
	}

	StringWorldEndurance::StringWorldEndurance( Func<int, LevelSeedData*> GetSeed, const std::shared_ptr<GUI_LivesLeft> &Gui_LivesLeft, int NextLife ) : StringWorldGameData( std::make_shared<Func>( this, &StringWorldEndurance::GetSeed ) )
	{
		// Lives
		this->Gui_LivesLeft = Gui_LivesLeft;
		Gui_Lives = std::make_shared<GUI_Lives>( Gui_LivesLeft );
		Gui_NextLife = std::make_shared<GUI_NextLife>( NextLife, Gui_LivesLeft );

		// Coin score multiplier
		MyCoinScoreMultiplier = std::make_shared<CoinScoreMultiplierObject>();

		// Level and Score
		MyGUI_Score = std::make_shared<GUI_Score>();
		MyGUI_Level = std::make_shared<GUI_Level>();

		// Add game objects, including 'Perfect' watcher
		OnSwapToFirstLevel->Add( std::make_shared<OnSwapLambda>( this ) );
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
