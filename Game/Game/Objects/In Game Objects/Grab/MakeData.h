#ifndef MAKE_DATA
#define MAKE_DATA

#include <global_header.h>

namespace CloudberryKingdom
{

	struct MakeData : public std::enable_shared_from_this<MakeData>
	{

	
		Vector2 TRBobMoveZone, BLBobMoveZone;

		std::shared_ptr<RichLevelGenData> GenData;

		/// <summary>
		/// The PieceSeedData from which the current MakeData's level is being made
		/// </summary>
		std::shared_ptr<PieceSeedData> PieceSeed;

		/// <summary>
		/// The LevelSeed which spawned the creation of this level.
		/// </summary>
		std::shared_ptr<LevelSeedData> LevelSeed;

		bool ComputerWaitAtStart;
		std::vector<int> ComputerWaitAtStartLength;
		float SparsityMultiplier;

		int NumInitialBobs;

		/// <summary>
		/// Minimum number of start positions to make, regardless of the number of computer AIs
		/// </summary>
		int MinStartPositionsToMake;

		Vector2 CamStartPos;
		std::vector<PhsxData> Start;
		std::vector<Vector2> CheckpointShift;
		std::vector<Bob::BobMove> MoveData;

		bool InitialPlats, InitialCamZone, FinalPlats;
		bool SkinnyStart;

		bool SetTRCamBound;

		/// <summary>
		/// If true the top has extra safety blocks and extra stage 1 fill, to mimick the bottom.
		/// Used, in particular, for Spaceship hero.
		/// </summary>
		bool TopLikeBottom;

		/// <summary>
		/// If true the top has extra safety blocks and extra stage 1 fill, to mimick the bottom.
		/// Blocks are thinner than normal.
		/// Used, in particular, for Invert bob.
		/// </summary>
		bool TopLikeBottom_Thin;

		/// <summary>
		/// If true then blocks will not be modified (no shifting of bottom, no top only).
		/// </summary>
		bool BlocksAsIs;

		/// <summary>
		/// When making a multi-piece level, this index specifies which piece the MakeData refers to.
		/// </summary>
		int Index;

		/// <summary>
		/// When making a multi-piece level, this index specifies how many pieces are being made.
		/// </summary>
		int OutOf;

		void Release();

		void Init( const std::shared_ptr<PieceSeedData> &data );

		BobVec MakeBobs( const std::shared_ptr<Level> &level );

		std::shared_ptr<LevelPiece> MakeLevelPiece( const std::shared_ptr<Level> &level, BobVec bobs, int Length, int StartPhsxStep );

	
		void InitializeInstanceFields();

	
		MakeData()
		{
			InitializeInstanceFields();
		}
	};
}

#endif
