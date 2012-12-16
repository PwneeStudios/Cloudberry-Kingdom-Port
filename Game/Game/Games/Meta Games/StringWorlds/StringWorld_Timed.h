#ifndef STRINGWORLD_TIMED
#define STRINGWORLD_TIMED

#include <global_header.h>

namespace CloudberryKingdom
{
	struct StringWorldTimed : public StringWorldGameData
	{
	
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

		virtual void Release();

		virtual void AdditionalSwapToLevelProcessing( const boost::shared_ptr<GameData> &game );
	};
}


#endif	//#ifndef STRINGWORLD_TIMED
