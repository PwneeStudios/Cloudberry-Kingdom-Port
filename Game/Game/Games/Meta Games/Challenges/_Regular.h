#ifndef _REGULAR
#define _REGULAR

#include <small_header.h>

//#include "Game/Games/NormalGame.h"
//#include "Game/Level/Make/LockableBool.h"
//#include "Game/Level/Make/DifficultyGroups.h"
//#include "Game/Level/Make/LevelSeedData.h"
//#include "Game/Level/Make/PieceSeedData.h"
//#include "Game/Level/Make/Parameters/Upgrades.h"
//#include "Game/Menus/Concrete Menus/Title Screen/Arcade/ArcadeMenu.h"
//#include "Game/Player/Hero Physics/Base.h"
//#include "Game/Objects/AutoGen.h"
//#include "Game/Player/Hero Physics/Normal.h"
//#include "Game/Tools/Tools.h"


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
