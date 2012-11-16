#ifndef DIFFICULTYGROUPS
#define DIFFICULTYGROUPS

#include <global_header.h>

namespace CloudberryKingdom
{
	class PieceSeedData;
}

namespace CloudberryKingdom
{
	class LevelSeedData;
}

namespace CloudberryKingdom
{
	class Lambda_1;
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
	class DifficultyGroups
	{
	public:
		class UpgradeSequenceSingle
		{
		public:
			void Apply( const std::shared_ptr<PieceSeedData> &Piece, float Difficulty );

		private:
			Upgrade MyUpgrade;
		public:
			std::vector<double> Values;

//ORIGINAL LINE: public UpgradeSequenceSingle(Upgrade MyUpgrade, params double[] values)
//C# TO C++ CONVERTER TODO TASK: Use 'va_start', 'va_arg', and 'va_end' to access the parameter array within this method:
			UpgradeSequenceSingle( Upgrade MyUpgrade, ... );
		};

	public:
		class UpgradeSequence
		{
		public:
			void Apply( const std::shared_ptr<PieceSeedData> &Piece, float Difficulty );

		private:
			std::vector<UpgradeSequenceSingle> UpgradeList;
		public:
//ORIGINAL LINE: public UpgradeSequence(params UpgradeSequenceSingle[] Upgrades)
//C# TO C++ CONVERTER TODO TASK: Use 'va_start', 'va_arg', and 'va_end' to access the parameter array within this method:
			UpgradeSequence( ... );
		};

	private:
		class FixedPieceModHelper : public Lambda_1<PieceSeedData*>
		{
		private:
			float Difficulty;
			std::shared_ptr<LevelSeedData> LevelSeed;

		public:
			FixedPieceModHelper( float Difficulty, const std::shared_ptr<LevelSeedData> &LevelSeed );

			void Apply( const std::shared_ptr<PieceSeedData> &piece );
		};

		/// <summary>
		/// Returns a function that modifies a PieceSeed's difficulty
		/// </summary>
	public:
		static std::shared_ptr<Lambda_1<PieceSeedData*> > FixedPieceMod( float Difficulty, const std::shared_ptr<LevelSeedData> &LevelSeed );

		static float HeroDifficultyMod( float Difficulty, const std::shared_ptr<BobPhsx> &hero );

		/// <summary>
		/// Modify the upgrades for a PieceSeed.
		/// Difficulty should range from 0 (Easy) to 4 (Masochistic)
		/// </summary>
		static void FixedPieceSeed( const std::shared_ptr<PieceSeedData> &piece, float Difficulty, const std::shared_ptr<BobPhsx> &hero );

	private:
		static void InitFixedUpgrades();

		static std::vector<UpgradeSequence> UpUpgrades;
		static void MakeUpUpgrades();

		static std::vector<UpgradeSequence> DownUpgrades;
		static void MakeDownUpgrades();

		static std::vector<UpgradeSequence> CartUpgrades;
		static void MakeCartUpgrades();

		static std::vector<UpgradeSequence> EasyUpgrades;
		static void MakeEasyUpgrades();

		static std::vector<UpgradeSequence> NormalUpgrades;
		static void MakeNormalUpgrades();

		static std::vector<UpgradeSequence> AbusiveUpgrades;
		static void MakeAbusiveUpgrades();

		static std::vector<UpgradeSequence> HardcoreUpgrades;
		static void MakeHardcoreUpgrades();
	};
}


#endif	//#ifndef DIFFICULTYGROUPS
