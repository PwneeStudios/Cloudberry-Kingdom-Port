#ifndef _REGULAR
#define _REGULAR

#include "../Game/Menus/Concrete Menus/CharacterSelect/HeroLevel.h"

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

namespace CloudberryKingdom
{
	class RegularLevel
	{
	private:
		RegularLevel();

		static void StandardInit( const std::shared_ptr<LevelSeedData> &data );

		// -------------------------
		// Fixed upgrade lists
		// -------------------------
	public:
		static std::shared_ptr<LevelSeedData> HeroLevel( float Difficulty, const std::shared_ptr<BobPhsx> &Hero, int Length );
	};
}


#endif	//#ifndef _REGULAR
