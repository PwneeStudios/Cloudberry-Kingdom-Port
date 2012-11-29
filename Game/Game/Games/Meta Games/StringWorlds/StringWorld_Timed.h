#ifndef STRINGWORLD_TIMED
#define STRINGWORLD_TIMED

#include <global_header.h>

namespace CloudberryKingdom
{
	class StringWorldTimed : public StringWorldGameData
	{
	private:
		class StringWorldOnTimerExpiredLambda : public Lambda_1<std::shared_ptr<GUI_Timer_Base> >
		{
		private:
			std::shared_ptr<GUI_Score> MyGUI_Score;
			std::shared_ptr<GUI_Level> MyGUI_Level;

		public:
			StringWorldOnTimerExpiredLambda( const std::shared_ptr<GUI_Score> &MyGUI_Score, const std::shared_ptr<GUI_Level> &MyGUI_Level );

			void Apply( const std::shared_ptr<GUI_Timer_Base> &timer );
		};

	private:
		class OnSwapLambda : public Lambda_1<std::shared_ptr<LevelSeedData> >
		{
		private:
			std::shared_ptr<StringWorldTimed> ch;
		public:
			OnSwapLambda( const std::shared_ptr<StringWorldTimed> &ch );

			void Apply( const std::shared_ptr<LevelSeedData> &data );
		};

	private:
		std::shared_ptr<GUI_Timer> MyGUI_Timer;
		std::shared_ptr<TimerWarning> Warning;
	public:
		std::shared_ptr<GUI_Score> MyGUI_Score;
		std::shared_ptr<GUI_Level> MyGUI_Level;
	private:
		std::shared_ptr<CoinScoreMultiplierObject> MyCoinScoreMultiplier;

	public:
		StringWorldTimed( const std::shared_ptr<LambdaFunc_1<int, std::shared_ptr<LevelSeedData> > > &GetSeed, const std::shared_ptr<GUI_Timer> &Timer );

		virtual void Release();

		virtual void AdditionalSwapToLevelProcessing( const std::shared_ptr<GameData> &game );
	};
}


#endif	//#ifndef STRINGWORLD_TIMED
