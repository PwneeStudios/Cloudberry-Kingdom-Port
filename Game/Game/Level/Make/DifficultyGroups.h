#ifndef DIFFICULTYGROUPS
#define DIFFICULTYGROUPS

#include <global_header.h>

namespace CloudberryKingdom
{
	struct DifficultyGroups
	{
	
		struct UpgradeSequenceSingle
		{
		
			void Apply( const boost::shared_ptr<PieceSeedData> &Piece, float Difficulty );

		
			Upgrade MyUpgrade;
		
			std::vector<double> Values;

			UpgradeSequenceSingle( Upgrade MyUpgrade, double v0, double v1, double v2, double v3, double v4 );
		};

	
		struct UpgradeSequence
		{
		
			void Apply( const boost::shared_ptr<PieceSeedData> &Piece, float Difficulty );

		
			std::vector<UpgradeSequenceSingle> UpgradeList;
		

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

	
		struct FixedPieceModHelper : public Lambda_1<boost::shared_ptr<PieceSeedData> >
		{
		
			float Difficulty;
			boost::shared_ptr<LevelSeedData> LevelSeed;

		
			FixedPieceModHelper( float Difficulty, const boost::shared_ptr<LevelSeedData> &LevelSeed );

			void Apply( const boost::shared_ptr<PieceSeedData> &piece );
		};

		/// <summary>
		/// Returns a function that modifies a PieceSeed's difficulty
		/// </summary>
	
		static boost::shared_ptr<Lambda_1<boost::shared_ptr<PieceSeedData> > > FixedPieceMod( float Difficulty, const boost::shared_ptr<LevelSeedData> &LevelSeed );

		static float HeroDifficultyMod( float Difficulty, const boost::shared_ptr<BobPhsx> &hero );

		/// <summary>
		/// Modify the upgrades for a PieceSeed.
		/// Difficulty should range from 0 (Easy) to 4 (Masochistic)
		/// </summary>
		static void FixedPieceSeed( const boost::shared_ptr<PieceSeedData> &piece, float Difficulty, const boost::shared_ptr<BobPhsx> &hero );

	
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
