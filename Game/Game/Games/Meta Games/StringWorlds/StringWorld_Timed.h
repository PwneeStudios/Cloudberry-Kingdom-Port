#ifndef STRINGWORLD_TIMED
#define STRINGWORLD_TIMED

#include <global_header.h>

namespace CloudberryKingdom
{
	struct StringWorldTimed : public StringWorldGameData
	{
	
		struct StringWorldOnTimerExpiredLambda : public Lambda_1<std::shared_ptr<GUI_Timer_Base> >
		{
		
			std::shared_ptr<GUI_Score> MyGUI_Score;
			std::shared_ptr<GUI_Level> MyGUI_Level;

		
			StringWorldOnTimerExpiredLambda( const std::shared_ptr<GUI_Score> &MyGUI_Score, const std::shared_ptr<GUI_Level> &MyGUI_Level );

			void Apply( const std::shared_ptr<GUI_Timer_Base> &timer );
		};

	
		struct OnSwapLambda : public Lambda_1<std::shared_ptr<LevelSeedData> >
		{
		
			std::shared_ptr<StringWorldTimed> ch;
		
			OnSwapLambda( const std::shared_ptr<StringWorldTimed> &ch );

			void Apply( const std::shared_ptr<LevelSeedData> &data );
		};

	
		std::shared_ptr<GUI_Timer> MyGUI_Timer;
		std::shared_ptr<TimerWarning> Warning;
	
		std::shared_ptr<GUI_Score> MyGUI_Score;
		std::shared_ptr<GUI_Level> MyGUI_Level;
	
		std::shared_ptr<CoinScoreMultiplierObject> MyCoinScoreMultiplier;

	
		StringWorldTimed( const std::shared_ptr<LambdaFunc_1<int, std::shared_ptr<LevelSeedData> > > &GetSeed, const std::shared_ptr<GUI_Timer> &Timer );

		virtual void Release();

		virtual void AdditionalSwapToLevelProcessing( const std::shared_ptr<GameData> &game );
	};
}


#endif	//#ifndef STRINGWORLD_TIMED
