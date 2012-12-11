#ifndef _REGULAR
#define _REGULAR

#include <global_header.h>

namespace CloudberryKingdom
{
	struct LevelSeedData;
}

namespace CloudberryKingdom
{
	struct BobPhsx;
}


namespace CloudberryKingdom
{
	struct RegularLevel
	{
	
		RegularLevel();

		static void StandardInit( const std::shared_ptr<LevelSeedData> &data );

		// -------------------------
		// Fixed upgrade lists
		// -------------------------
	
		static std::shared_ptr<LevelSeedData> HeroLevel( float Difficulty, const std::shared_ptr<BobPhsx> &Hero, int Length );
	};
}


#endif	//#ifndef _REGULAR
