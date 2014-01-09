#ifndef STRINGWORLD_TIMED
#define STRINGWORLD_TIMED

#include <small_header.h>

//#include "Game/Objects/Game Objects/GameObjects/GUI_Panel.h"
//#include "Game/Games/GameType.h"
#include "Game/Games/Meta Games/StringWorlds/StringWorld.h"
//#include "Game/Level/Make/LockableBool.h"
//#include "Game/Level/Make/LevelSeedData.h"
//#include "Game/Objects/Game Objects/GameObjects/CoinScoreMultiplierObject.h"
//#include "Game/Objects/Game Objects/GameObjects/GUI_Level.h"
//#include "Game/Objects/Game Objects/GameObjects/GUI_Score.h"
//#include "Game/Objects/Game Objects/GameObjects/GUI_Timer.h"
//#include "Game/Objects/Game Objects/GameObjects/PerfectScoreObject.h"
//#include "Game/Objects/Game Objects/GameObjects/TimerWarning.h"


namespace CloudberryKingdom
{

	struct StringWorldTimed : public StringWorldGameData
	{

		virtual ~StringWorldTimed()
		{
#ifdef BOOST_BIN
			OnDestructor( "StringWorldTimed" );
#endif
		}

	
		struct StringWorldOnTimerExpiredLambda : public Lambda_1<boost::shared_ptr<GUI_Timer_Base> >
		{
		
			boost::shared_ptr<GUI_Score> MyGUI_Score;
			boost::shared_ptr<GUI_Level> MyGUI_Level;

		
			StringWorldOnTimerExpiredLambda( const boost::shared_ptr<GUI_Score> &MyGUI_Score, const boost::shared_ptr<GUI_Level> &MyGUI_Level );

			void Apply( const boost::shared_ptr<GUI_Timer_Base> &timer );
		};

	
		struct OnSwapLambda : public Lambda_1<boost::shared_ptr<LevelSeedData> >
		{
		
			boost::shared_ptr<StringWorldTimed> ch;
		
			OnSwapLambda( const boost::shared_ptr<StringWorldTimed> &ch );

			void Apply( const boost::shared_ptr<LevelSeedData> &data );
		};

	
		boost::shared_ptr<GUI_Timer> MyGUI_Timer;
		boost::shared_ptr<TimerWarning> Warning;
	
		boost::shared_ptr<GUI_Score> MyGUI_Score;
		boost::shared_ptr<GUI_Level> MyGUI_Level;
	
		boost::shared_ptr<CoinScoreMultiplierObject> MyCoinScoreMultiplier;

	
		StringWorldTimed( const boost::shared_ptr<LambdaFunc_1<int, boost::shared_ptr<LevelSeedData> > > &GetSeed, const boost::shared_ptr<GUI_Timer> &Timer );

		virtual void AdditionalSetLevel();

		virtual void Release();

		virtual void AdditionalSwapToLevelProcessing( const boost::shared_ptr<GameData> &game );
	};
}


#endif	//#ifndef STRINGWORLD_TIMED
