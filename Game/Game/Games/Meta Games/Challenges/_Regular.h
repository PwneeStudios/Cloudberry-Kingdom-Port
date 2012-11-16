#ifndef _REGULAR
#define _REGULAR

#include <global_header.h>

namespace CloudberryKingdom
{
	class LevelSeedData;
}

namespace CloudberryKingdom
{
	class BobPhsx;
}







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
