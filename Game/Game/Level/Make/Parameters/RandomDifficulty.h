#ifndef RANDOMDIFFICULTY
#define RANDOMDIFFICULTY

#include <small_header.h>

//#include "Game/Tilesets/TileSet.h"
//#include "Game/Level/Make/PieceSeedData.h"
//#include "Game/Level/Make/Parameters/Upgrades.h"
//#include "Game/Objects/AutoGen.h"
//#include "Game/Objects/In Game Objects/Grab/MakeData.h"
//#include "Game/Level/Level.h"
#include "Game/Tools/Tools.h"
//#include "Game/Tilesets/TileSetInfo.h"


namespace CloudberryKingdom
{
	struct PieceSeedData;
}

namespace CloudberryKingdom
{
	struct Upgrades;
}

namespace CloudberryKingdom
{
	struct TileSet;
}
namespace CloudberryKingdom
{
	struct RndDifficulty
	{
	
		static int ChoosePaths( const boost::shared_ptr<PieceSeedData> &data );

		static LadderType ChooseLadder( int Difficulty );

		static void ZeroUpgrades( const boost::shared_ptr<Upgrades> &upgrades );

		//static public int[] ChooseUpgrades(int Num)
		//{
		//    bool[] Valid = new bool[Tools::UpgradeTypes];
		//    for (int i = 0; i < Tools::UpgradeTypes; i++)
		//        Valid[i] = true;
		//    Valid[(int)Upgrade.Speed] = false;
		//    Valid[(int)Upgrade.General] = false;
		//    return MyLevel.Rnd.RndIndex(Tools::UpgradeTypes, Num, Valid);
		//}


		static void EnforceLevelCap( const boost::shared_ptr<Upgrades> &upgrades, int Cap, int LowerCap );

		static void UseUpgrades( const boost::shared_ptr<PieceSeedData> &Seed, const boost::shared_ptr<Upgrades> &u );

		/// <summary>
		/// Randomizes the obstacles upgrades of a seed, using the seed's integer valued difficulty.
		/// </summary>
		/// <param name="Seed"></param>
		static void IntToDifficulty( const boost::shared_ptr<PieceSeedData> &Seed, const boost::shared_ptr<TileSet> &TileType );
	};
}


#endif	//#ifndef RANDOMDIFFICULTY
