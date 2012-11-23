#ifndef STYLEDATA
#define STYLEDATA

#include <global_header.h>

namespace CloudberryKingdom
{
	class Multicaster_2;
}

namespace CloudberryKingdom
{
	class PieceSeedData;
}

namespace CloudberryKingdom
{
	class AutoGen_Parameters;
}

namespace CloudberryKingdom
{
	class AutoGen;
}

namespace CloudberryKingdom
{
	class Rand;
}

namespace CloudberryKingdom
{
	class Upgrades;
}

namespace CloudberryKingdom
{
	class Level;
}


namespace CloudberryKingdom
{
	class StyleData
	{
	public:
		enum FinalPlatsType
		{
			FinalPlatsType_DOOR,
			FinalPlatsType_DARK_BOTTOM
		};
	public:
		enum FinalDoorStyle
		{
			FinalDoorStyle_NORMAL
		};
	public:
		enum InitialPlatsType
		{
			InitialPlatsType_NORMAL,
			InitialPlatsType_LANDING_ZONE,
			InitialPlatsType_DOOR,
			InitialPlatsType_SPACESHIP,
			InitialPlatsType_UP_TILED_FLOOR
		};
	public:
		enum GroundType
		{
			GroundType_NONE,
			GroundType_SAFETY_NET,
			GroundType_INVISIBLE_USED,
			GroundType_USED,
			GroundType_INVERTED_USED,
			GroundType_VIRGIN_USED,
			GroundType_INVERT_SAFETY_NET
		};
	public:
		enum _BlockFillType
		{
			_BlockFillType_REGULAR,
			_BlockFillType_TOP_ONLY,
			_BlockFillType_INVERTABLE,
			_BlockFillType_SIDEWAYS
		};
	public:
		enum _OverlapCleanupType
		{
			_OverlapCleanupType_REGULAR,
			_OverlapCleanupType_SOPHISTICATED
		};
	public:
		enum _SparsityType
		{
			_SparsityType_REGULAR,
			_SparsityType_LIL_SPARSE,
			_SparsityType_VERY_SPARSE
		};
	public:
		enum _MoveTypePeriod
		{
			_MoveTypePeriod_INF,
			_MoveTypePeriod_SHORT,
			_MoveTypePeriod_NORMAL1,
			_MoveTypePeriod_NORMAL2
		};
	public:
		enum _MoveTypeInnerPeriod
		{
			_MoveTypeInnerPeriod_LONG,
			_MoveTypeInnerPeriod_SHORT,
			_MoveTypeInnerPeriod_NORMAL
		};
	public:
		enum _PauseType
		{
			_PauseType_NONE,
			_PauseType_LIMITED,
			_PauseType_NORMAL,
			_PauseType_NORMAL2
		};
	public:
		enum _ReverseType
		{
			_ReverseType_NONE,
			_ReverseType_NORMAL,
			_ReverseType_NORMAL2,
			_ReverseType_NORMAL3
		};
	public:
		enum _JumpType
		{
			_JumpType_ALWAYS,
			_JumpType_ALOT,
			_JumpType_NORMAL,
			_JumpType_NORMAL2
		};
	public:
		enum _ElevatorSwitchType
		{
			_ElevatorSwitchType_RANDOM,
			_ElevatorSwitchType_ALTERNATE,
			_ElevatorSwitchType_ALL_UP,
			_ElevatorSwitchType_ALL_DOWN
		};
	public:
		enum _OffsetType
		{
			_OffsetType_RANDOM,
			_OffsetType_ALL_SAME,
			_OffsetType_SPATIALLY_PERIODIC
		};
	public:
		enum _FillType
		{
			_FillType_RND,
			_FillType_HALFN_HALF,
			_FillType_PURE
		};
	public:
		enum _SinglePathType
		{
			_SinglePathType_NORMAL,
			_SinglePathType_LOW,
			_SinglePathType_MID,
			_SinglePathType_HIGH
		};
	public:
		enum _DoublePathType
		{
			_DoublePathType_SEPARATED,
			_DoublePathType_GAP,
			_DoublePathType_INDEPENDENT
		};
	public:
		enum _TriplePathType
		{
			_TriplePathType_SEPARATED,
			_TriplePathType_INDEPENDENT
		};
	public:
		enum _StartType
		{
			_StartType_TOP,
			_StartType_MIDDLE,
			_StartType_BOTTOM
		};
		/// <summary>
		/// A callback to modify AutoGen parameters after they have been set
		/// </summary>
	public:
		std::shared_ptr<Multicaster_2<Level*, PieceSeedData*> > MyModParams;

		void Release();

		std::map<AutoGen*, AutoGen_Parameters*> GenParams;
		void CalcGenParams( const std::shared_ptr<PieceSeedData> &SeedData, const std::shared_ptr<Level> &level );
		std::shared_ptr<AutoGen_Parameters> FindParams( const std::shared_ptr<AutoGen> &gen );

		std::shared_ptr<StyleData> Clone();

		float Zoom;
		Level::TimeTypes TimeType;

		bool SuppressCoins, SuppressCheckpoints;

		float TopSpace, BottomSpace;
		float FillxStep, FillyStep;

		float ModNormalBlockWeight;

		/// <summary>
		/// The length of time the computer waits at the beginning of the level.
		/// </summary>
		Vector2 ComputerWaitLengthRange; //50);

		Vector2 DoorHitBoxPadding;

		FinalPlatsType MyFinalPlatsType;

		FinalDoorStyle MyFinalDoorStyle;

		InitialPlatsType MyInitialPlatsType;

		bool MakeInitialPlats;
		float UpperSafetyNetOffset, LowerSafetyNetOffset;

		/// <summary>
		/// The width of an additional region of padding at the beginning of a level where no obstacles can exist.
		/// </summary>
		float SafeStartPadding;

		/// <summary>
		/// The width of an additional region of padding at the end of a level where no obstacles can exist.
		/// </summary>
		float SafeEndPadding;

		/// <summary>
		/// Makes the level longer by this much.
		/// </summary>
		float LengthPadding;

		/// <summary>
		/// When trues players will automatically operate EOL doors.
		/// </summary>
		bool AutoOpenDoor;

		GroundType MyGroundType, MyTopType;

		bool RemovedUnusedOverlappingBlocks;
		bool RemoveBlockOnCol;
		bool RemoveBlockOnOverlap;
		float MinBlockDist;

	private:
		std::vector<float> BlockFillTypeRatio;
	public:
		_BlockFillType BlockFillType;

		_OverlapCleanupType OverlapCleanupType;


	private:
		std::vector<float> Sparsity;
		std::vector<float> SparsityTypeRatio;
	public:
		_SparsityType SparsityType;

		/// <summary>
		/// When true the computer's destination is always super curvy.
		/// </summary>
		bool AlwaysCurvyMove;

		bool AlwaysEdgeJump;

		_MoveTypePeriod MoveTypePeriod;

		_MoveTypeInnerPeriod MoveTypeInnerPeriod;

		_PauseType PauseType;

		_ReverseType ReverseType;

		_JumpType JumpType;

		_ElevatorSwitchType ElevatorSwitchType;
	private:
		std::vector<float> ElevatorSwitchTypeRatio;

	public:
		_OffsetType PendulumOffsetType, FlyingBlobOffsetType;
	private:
		std::vector<float> OffsetTypeRatio;

		std::vector<float> FillTypeRatio;
	public:
		_FillType FillType;

	private:
		static std::vector<float> _SinglePathRatio;
	public:
		_SinglePathType SinglePathType;
		_DoublePathType DoublePathType;
		_TriplePathType TriplePathType;
		_StartType Bob1Start, Bob2Start, Bob3Start;

		float ChanceToKeepUnused;

		/// <summary>
		/// When true the computer stops less, reverses less, etc.
		/// </summary>
		bool FunRun;

		bool Masochistic;

		std::shared_ptr<Rand> Rnd;
		StyleData( const std::shared_ptr<Rand> &Rnd );

		void Calculate( const std::shared_ptr<Upgrades> &u );

	protected:
		virtual void CalculateKeepUnused( float JumpLevel );

	public:
		virtual void Randomize();

		float GetSparsity();

		int GetOffset( int Period, Vector2 pos, _OffsetType Type );
	private:
		void SetStartType( PhsxData &Start, Vector2 &CheckpointShift, _StartType StartType, const std::shared_ptr<PieceSeedData> &Piece );

	public:
		void SetSinglePathType( const std::shared_ptr<Level.MakeData> &makeData, const std::shared_ptr<Level> &level, const std::shared_ptr<PieceSeedData> &Piece );

		void SetDoubePathType( const std::shared_ptr<Level.MakeData> &makeData, const std::shared_ptr<Level> &level, const std::shared_ptr<PieceSeedData> &Piece );

		void SetTriplePathType( const std::shared_ptr<Level.MakeData> &makeData, const std::shared_ptr<Level> &level, const std::shared_ptr<PieceSeedData> &Piece );

		void SuppressGroundCeiling( const std::shared_ptr<PieceSeedData> &piece );

		void SetToMake_BouncyHallway( const std::shared_ptr<PieceSeedData> &piece );

	private:
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef STYLEDATA
