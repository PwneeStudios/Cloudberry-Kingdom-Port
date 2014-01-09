#include <small_header.h>
#include "Game/Games/Meta Games/StringWorlds/StringWorld_Timed.h"

#include "Game/Objects/Game Objects/GameObjects/GUI_Panel.h"
#include "Game/Games/GameType.h"
#include "Game/Games/Meta Games/StringWorlds/StringWorld.h"
#include "Game/Level/Make/LockableBool.h"
#include "Game/Level/Make/LevelSeedData.h"
#include "Game/Objects/Game Objects/GameObjects/CoinScoreMultiplierObject.h"
#include "Game/Objects/Game Objects/GameObjects/GUI_Level.h"
#include "Game/Objects/Game Objects/GameObjects/GUI_Score.h"
#include "Game/Objects/Game Objects/GameObjects/GUI_Timer.h"
#include "Game/Objects/Game Objects/GameObjects/PerfectScoreObject.h"
#include "Game/Objects/Game Objects/GameObjects/TimerWarning.h"

#include "Game/Level/Level.h"

namespace CloudberryKingdom
{

	StringWorldTimed::StringWorldOnTimerExpiredLambda::StringWorldOnTimerExpiredLambda( const boost::shared_ptr<GUI_Score> &MyGUI_Score, const boost::shared_ptr<GUI_Level> &MyGUI_Level )
	{
		this->MyGUI_Score = MyGUI_Score;
		this->MyGUI_Level = MyGUI_Level;
	}

	void StringWorldTimed::StringWorldOnTimerExpiredLambda::Apply( const boost::shared_ptr<GUI_Timer_Base> &timer )
	{
		MyGUI_Score->SlideOut( GUI_Panel::PresetPos_TOP );
		MyGUI_Level->SlideOut( GUI_Panel::PresetPos_TOP );
	}

	StringWorldTimed::OnSwapLambda::OnSwapLambda( const boost::shared_ptr<StringWorldTimed> &ch )
	{
		this->ch = ch;
	}

	void StringWorldTimed::OnSwapLambda::Apply( const boost::shared_ptr<LevelSeedData> &data )
	{
		data->MyGame->AddGameObject( ch->MyGUI_Timer );
		data->MyGame->AddGameObject( ch->Warning );
		data->MyGame->AddGameObject( ch->MyGUI_Score );
		data->MyGame->AddGameObject( ch->MyGUI_Level );
		data->MyGame->AddGameObject( ch->MyCoinScoreMultiplier );
		data->MyGame->AddGameObject( MakeMagic( PerfectScoreObject, ( false, true, false ) ) );
	}

	StringWorldTimed::StringWorldTimed( const boost::shared_ptr<LambdaFunc_1<int, boost::shared_ptr<LevelSeedData> > > &GetSeed, const boost::shared_ptr<GUI_Timer> &Timer ) :
		StringWorldGameData( GetSeed )
	{
		// See StringWorldTimed_Construct.

		/*MyGUI_Timer = Timer;

		Warning = boost::make_shared<TimerWarning>();
		Warning->MyTimer = Timer;

		MyGUI_Score = boost::make_shared<GUI_Score>();
		MyGUI_Level = boost::make_shared<GUI_Level>();

		Timer->OnTimeExpired->Add( boost::make_shared<StringWorldOnTimerExpiredLambda>( MyGUI_Score, MyGUI_Level ) );

		// Coin score multiplier
		MyCoinScoreMultiplier = boost::make_shared<CoinScoreMultiplierObject>();

		// Add 'Perfect' watcher
		OnSwapToFirstLevel->Add( boost::make_shared<OnSwapLambda>( boost::static_pointer_cast<StringWorldTimed>( shared_from_this() ) ) );*/
	}

	void StringWorldTimed::AdditionalSetLevel()
	{
		StringWorldGameData::AdditionalSetLevel();

		NextLevelSeed->MyGame->MyLevel->SetBack( 3 );
	}

	void StringWorldTimed::Release()
	{
		StringWorldGameData::Release();

		MyGUI_Timer->ForceRelease();
	}

	void StringWorldTimed::AdditionalSwapToLevelProcessing( const boost::shared_ptr<GameData> &game )
	{
		StringWorldGameData::AdditionalSwapToLevelProcessing( game );

		MyGUI_Level->SetLevel( CurLevelIndex + 1 );

		game->TakeOnce = true;
	}
}
