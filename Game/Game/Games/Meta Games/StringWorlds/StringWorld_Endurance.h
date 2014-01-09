#ifndef STRINGWORLD_ENDURANCE
#define STRINGWORLD_ENDURANCE

#include <small_header.h>

//#include "Game/Games/GameType.h"
#include "Game/Games/Meta Games/StringWorlds/StringWorld.h"
//#include "Game/Level/Make/LockableBool.h"
//#include "Game/Level/Make/LevelSeedData.h"
//#include "Game/Objects/Game Objects/GameObjects/CoinScoreMultiplierObject.h"
//#include "Game/Objects/Game Objects/GameObjects/GUI_Level.h"
//#include "Game/Objects/Game Objects/GameObjects/GUI_Lives.h"
//#include "Game/Objects/Game Objects/GameObjects/GUI_LivesLeft.h"
//#include "Game/Objects/Game Objects/GameObjects/GUI_NextLife.h"
//#include "Game/Objects/Game Objects/GameObjects/GUI_Score.h"
//#include "Game/Objects/Game Objects/GameObjects/PerfectScoreObject.h"


namespace CloudberryKingdom
{
	struct StringWorldEndurance : public StringWorldGameData
	{
	
		virtual ~StringWorldEndurance()
		{
#ifdef BOOST_BIN
			OnDestructor( "StringWorldEndurance" );
#endif
		}


		struct OnSwapLambda : public Lambda_1<boost::shared_ptr<LevelSeedData> >
		{
		
			boost::shared_ptr<StringWorldEndurance> ch;
		
			OnSwapLambda( const boost::shared_ptr<StringWorldEndurance> &ch );

			void Apply( const boost::shared_ptr<LevelSeedData> &data );
		};

	
		boost::shared_ptr<GUI_Score> MyGUI_Score;
		boost::shared_ptr<GUI_Level> MyGUI_Level;

		boost::shared_ptr<GUI_LivesLeft> Gui_LivesLeft;
		boost::shared_ptr<GUI_Lives> Gui_Lives;
		boost::shared_ptr<GUI_NextLife> Gui_NextLife;
		boost::shared_ptr<CoinScoreMultiplierObject> MyCoinScoreMultiplier;

	
		StringWorldEndurance( const boost::shared_ptr<LambdaFunc_1<int, boost::shared_ptr<LevelSeedData> > > &GetSeed, const boost::shared_ptr<GUI_LivesLeft> &Gui_LivesLeft, int NextLife );

		virtual void AdditionalSetLevel();

		virtual void Release();

		virtual void AdditionalSwapToLevelProcessing( const boost::shared_ptr<GameData> &game );
	};
}


#endif	//#ifndef STRINGWORLD_ENDURANCE
