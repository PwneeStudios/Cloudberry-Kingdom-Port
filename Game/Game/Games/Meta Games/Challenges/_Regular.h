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

		static void StandardInit( const boost::shared_ptr<LevelSeedData> &data );

		// -------------------------
		// Fixed upgrade lists
		// -------------------------
	
		static boost::shared_ptr<LevelSeedData> HeroLevel( float Difficulty, const boost::shared_ptr<BobPhsx> &Hero, int Length, bool ScreenSaver);
	};
}


#endif	//#ifndef _REGULAR
