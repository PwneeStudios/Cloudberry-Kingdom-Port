#ifndef RANDOMDIFFICULTY
#define RANDOMDIFFICULTY

#include <global_header.h>

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
	
		static int ChoosePaths( const std::shared_ptr<PieceSeedData> &data );

		static LadderType ChooseLadder( int Difficulty );

		static void ZeroUpgrades( const std::shared_ptr<Upgrades> &upgrades );

		//static public int[] ChooseUpgrades(int Num)
		//{
		//    bool[] Valid = new bool[Tools.UpgradeTypes];
		//    for (int i = 0; i < Tools.UpgradeTypes; i++)
		//        Valid[i] = true;
		//    Valid[(int)Upgrade.Speed] = false;
		//    Valid[(int)Upgrade.General] = false;
		//    return MyLevel.Rnd.RndIndex(Tools.UpgradeTypes, Num, Valid);
		//}


		static void EnforceLevelCap( const std::shared_ptr<Upgrades> &upgrades, int Cap, int LowerCap );

		static void UseUpgrades( const std::shared_ptr<PieceSeedData> &Seed, const std::shared_ptr<Upgrades> &u );

		/// <summary>
		/// Randomizes the obstacles upgrades of a seed, using the seed's integer valued difficulty.
		/// </summary>
		/// <param name="Seed"></param>
		static void IntToDifficulty( const std::shared_ptr<PieceSeedData> &Seed, const std::shared_ptr<TileSet> &TileType );
	};
}


#endif	//#ifndef RANDOMDIFFICULTY
