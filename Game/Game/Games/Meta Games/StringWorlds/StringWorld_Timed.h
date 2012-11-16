#ifndef STRINGWORLD_TIMED
#define STRINGWORLD_TIMED

#include <global_header.h>

namespace CloudberryKingdom
{
	class GUI_Timer_Base;
}

namespace CloudberryKingdom
{
	class GUI_Score;
}

namespace CloudberryKingdom
{
	class GUI_Level;
}

namespace CloudberryKingdom
{
	class LevelSeedData;
}

namespace CloudberryKingdom
{
	class GUI_Timer;
}

namespace CloudberryKingdom
{
	class TimerWarning;
}

namespace CloudberryKingdom
{
	class CoinScoreMultiplierObject;
}

namespace CloudberryKingdom
{
	class GameData;
}





namespace CloudberryKingdom
{
	class StringWorldTimed : public StringWorldGameData
	{
	private:
		class StringWorldOnTimerExpiredLambda : public Lambda_1<GUI_Timer_Base*>
		{
		private:
			std::shared_ptr<GUI_Score> MyGUI_Score;
			std::shared_ptr<GUI_Level> MyGUI_Level;

		public:
			StringWorldOnTimerExpiredLambda( const std::shared_ptr<GUI_Score> &MyGUI_Score, const std::shared_ptr<GUI_Level> &MyGUI_Level );

			void Apply( const std::shared_ptr<GUI_Timer_Base> &timer );
		};

	private:
		class OnSwapLambda : public Lambda_1<LevelSeedData*>
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
		StringWorldTimed( Func<int, LevelSeedData*> GetSeed, const std::shared_ptr<GUI_Timer> &Timer );

		virtual void Release();

		virtual void AdditionalSwapToLevelProcessing( const std::shared_ptr<GameData> &game );
	};
}


#endif	//#ifndef STRINGWORLD_TIMED
