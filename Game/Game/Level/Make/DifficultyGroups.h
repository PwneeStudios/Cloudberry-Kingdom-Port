#ifndef DIFFICULTYGROUPS
#define DIFFICULTYGROUPS

#include <global_header.h>

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

			UpgradeSequenceSingle( Upgrade MyUpgrade, double v0, double v1, double v2, double v3, double v4 );
		};

	public:
		class UpgradeSequence
		{
		public:
			void Apply( const std::shared_ptr<PieceSeedData> &Piece, float Difficulty );

		private:
			std::vector<UpgradeSequenceSingle> UpgradeList;
		public:

			DifficultyGroups::UpgradeSequence::UpgradeSequence(
				DifficultyGroups::UpgradeSequenceSingle s1,
				DifficultyGroups::UpgradeSequenceSingle s2,
				DifficultyGroups::UpgradeSequenceSingle s3,
				DifficultyGroups::UpgradeSequenceSingle s4,
				DifficultyGroups::UpgradeSequenceSingle s5,
				DifficultyGroups::UpgradeSequenceSingle s6,
				DifficultyGroups::UpgradeSequenceSingle s7,
				DifficultyGroups::UpgradeSequenceSingle s8,
				DifficultyGroups::UpgradeSequenceSingle s9,
				DifficultyGroups::UpgradeSequenceSingle s10 );
			DifficultyGroups::UpgradeSequence::UpgradeSequence(
				DifficultyGroups::UpgradeSequenceSingle s1,
				DifficultyGroups::UpgradeSequenceSingle s2,
				DifficultyGroups::UpgradeSequenceSingle s3,
				DifficultyGroups::UpgradeSequenceSingle s4,
				DifficultyGroups::UpgradeSequenceSingle s5,
				DifficultyGroups::UpgradeSequenceSingle s6,
				DifficultyGroups::UpgradeSequenceSingle s7,
				DifficultyGroups::UpgradeSequenceSingle s8,
				DifficultyGroups::UpgradeSequenceSingle s9 );
			DifficultyGroups::UpgradeSequence::UpgradeSequence(
				DifficultyGroups::UpgradeSequenceSingle s1,
				DifficultyGroups::UpgradeSequenceSingle s2,
				DifficultyGroups::UpgradeSequenceSingle s3,
				DifficultyGroups::UpgradeSequenceSingle s4,
				DifficultyGroups::UpgradeSequenceSingle s5,
				DifficultyGroups::UpgradeSequenceSingle s6,
				DifficultyGroups::UpgradeSequenceSingle s7,
				DifficultyGroups::UpgradeSequenceSingle s8 );
			DifficultyGroups::UpgradeSequence::UpgradeSequence(
				DifficultyGroups::UpgradeSequenceSingle s1,
				DifficultyGroups::UpgradeSequenceSingle s2,
				DifficultyGroups::UpgradeSequenceSingle s3,
				DifficultyGroups::UpgradeSequenceSingle s4,
				DifficultyGroups::UpgradeSequenceSingle s5,
				DifficultyGroups::UpgradeSequenceSingle s6,
				DifficultyGroups::UpgradeSequenceSingle s7 );
			DifficultyGroups::UpgradeSequence::UpgradeSequence(
				DifficultyGroups::UpgradeSequenceSingle s1,
				DifficultyGroups::UpgradeSequenceSingle s2,
				DifficultyGroups::UpgradeSequenceSingle s3,
				DifficultyGroups::UpgradeSequenceSingle s4,
				DifficultyGroups::UpgradeSequenceSingle s5,
				DifficultyGroups::UpgradeSequenceSingle s6 );
			DifficultyGroups::UpgradeSequence::UpgradeSequence(
				DifficultyGroups::UpgradeSequenceSingle s1,
				DifficultyGroups::UpgradeSequenceSingle s2,
				DifficultyGroups::UpgradeSequenceSingle s3,
				DifficultyGroups::UpgradeSequenceSingle s4,
				DifficultyGroups::UpgradeSequenceSingle s5 );
			DifficultyGroups::UpgradeSequence::UpgradeSequence(
				DifficultyGroups::UpgradeSequenceSingle s1,
				DifficultyGroups::UpgradeSequenceSingle s2,
				DifficultyGroups::UpgradeSequenceSingle s3,
				DifficultyGroups::UpgradeSequenceSingle s4 );
			DifficultyGroups::UpgradeSequence::UpgradeSequence(
				DifficultyGroups::UpgradeSequenceSingle s1,
				DifficultyGroups::UpgradeSequenceSingle s2,
				DifficultyGroups::UpgradeSequenceSingle s3 );
			DifficultyGroups::UpgradeSequence::UpgradeSequence(
				DifficultyGroups::UpgradeSequenceSingle s1,
				DifficultyGroups::UpgradeSequenceSingle s2 );
			DifficultyGroups::UpgradeSequence::UpgradeSequence(
				DifficultyGroups::UpgradeSequenceSingle s1 );
		};

	private:
		class FixedPieceModHelper : public Lambda_1<std::shared_ptr<PieceSeedData> >
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
		static std::shared_ptr<Lambda_1<std::shared_ptr<PieceSeedData> > > FixedPieceMod( float Difficulty, const std::shared_ptr<LevelSeedData> &LevelSeed );

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
