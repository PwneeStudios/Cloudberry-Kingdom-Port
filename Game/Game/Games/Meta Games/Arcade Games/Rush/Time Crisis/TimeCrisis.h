#ifndef TIMECRISIS
#define TIMECRISIS

#include "../Game/Games/Meta Games/Arcade Games/Rush/Hero Rush/HeroRush.h"
#include "../Core/Lambdas/Lambda_1.h"
#include "../Game/Games/Meta Games/Arcade Games/Rush/Hero Rush 2/HeroRush2.h"
#include "../Game/Games/Meta Games/Arcade Games/Escalate/Escalation.h"
#include "../Game/Games/ScreenSaver.h"
#include "../Game/Games/Meta Games/StringWorlds/StringWorld_Timed.h"
#include "../Game/Games/Meta Games/StringWorlds/StringWorld_Endurance.h"

namespace CloudberryKingdom
{
	class LevelSeedData;
}

namespace CloudberryKingdom
{
	class BobPhsx;
}


//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
using namespace Microsoft::Xna::Framework;

namespace CloudberryKingdom
{
	class Challenge_TimeCrisis : public Challenge_HeroRush
	{
	private:
		class OnSwapLambda : public Lambda_1<LevelSeedData*>
		{
		private:
			std::shared_ptr<Challenge_TimeCrisis> ch;
		public:
			OnSwapLambda( const std::shared_ptr<Challenge_TimeCrisis> &ch );

			void Apply( const std::shared_ptr<LevelSeedData> &data );
		};
	private:
		static const std::shared_ptr<Challenge_TimeCrisis> instance;
	public:
		const static std::shared_ptr<Challenge_TimeCrisis> &getInstance() const;

	protected:
		Challenge_TimeCrisis();

		virtual std::shared_ptr<BobPhsx> GetHero( int i );

		virtual void PreStart_Tutorial( bool TemporarySkip );

	};
}


#endif	//#ifndef TIMECRISIS
