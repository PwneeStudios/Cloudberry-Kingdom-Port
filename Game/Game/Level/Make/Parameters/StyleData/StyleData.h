#ifndef STYLEDATA
#define STYLEDATA

#include <small_header.h>

#include "Core/PhsxData.h"
//#include "Core/Tools/Random.h"
//#include "Game/Level/Make/Generators.h"
//#include "Game/Level/Make/PieceSeedData.h"
//#include "Game/Level/Make/Parameters/Upgrades.h"
//#include "Game/Objects/AutoGen.h"
//#include "Game/Objects/In Game Objects/Blocks/BouncyBlock__Auto.h"
//#include "Game/Objects/In Game Objects/Blocks/Ceiling__Auto.h"
//#include "Game/Objects/In Game Objects/Blocks/NormalBlock__Auto.h"
//#include "Game/Objects/In Game Objects/Grab/MakeData.h"
//#include "Game/Level/Level.h"
//#include "Game/Tools/Tools.h"


namespace CloudberryKingdom
{

	struct StyleData : public boost::enable_shared_from_this<StyleData>
	{

		virtual ~StyleData()
		{
#ifdef BOOST_BIN
			OnDestructor( "StyleData" );
#endif
		}

	
		enum FinalPlatsType
		{
			FinalPlatsType_DOOR,
			FinalPlatsType_DARK_BOTTOM
		};
	
		enum FinalDoorStyle
		{
			FinalDoorStyle_NORMAL
		};
	
		enum InitialPlatsType
		{
			InitialPlatsType_NORMAL,
			InitialPlatsType_LANDING_ZONE,
			InitialPlatsType_DOOR,
			InitialPlatsType_SPACESHIP,
			InitialPlatsType_UP_TILED_FLOOR
		};
	
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
	
		enum _BlockFillType
		{
			_BlockFillType_REGULAR,
			_BlockFillType_TOP_ONLY,
			_BlockFillType_INVERTABLE,
			_BlockFillType_SIDEWAYS
		};
	
		enum _OverlapCleanupType
		{
			_OverlapCleanupType_REGULAR,
			_OverlapCleanupType_SOPHISTICATED
		};
	
		enum _SparsityType
		{
			_SparsityType_REGULAR,
			_SparsityType_LIL_SPARSE,
			_SparsityType_VERY_SPARSE
		};
	
		enum _MoveTypePeriod
		{
			_MoveTypePeriod_INF,
			_MoveTypePeriod_SHORT,
			_MoveTypePeriod_NORMAL1,
			_MoveTypePeriod_NORMAL2,
			_MoveTypePeriod_LENGTH
		};
	
		enum _MoveTypeInnerPeriod
		{
			_MoveTypeInnerPeriod_LONG,
			_MoveTypeInnerPeriod_SHORT,
			_MoveTypeInnerPeriod_NORMAL,
			_MoveTypeInnerPeriod_LENGTH
		};
	
		enum _PauseType
		{
			_PauseType_NONE,
			_PauseType_LIMITED,
			_PauseType_NORMAL,
			_PauseType_NORMAL2,
			_PauseType_LENGTH
		};
	
		enum _ReverseType
		{
			_ReverseType_NONE,
			_ReverseType_NORMAL,
			_ReverseType_NORMAL2,
			_ReverseType_NORMAL3,
			_ReverseType_LENGTH
		};
	
		enum _JumpType
		{
			_JumpType_ALWAYS,
			_JumpType_ALOT,
			_JumpType_NORMAL,
			_JumpType_NORMAL2,
			_JumpType_LENGTH
		};
	
		enum _ElevatorSwitchType
		{
			_ElevatorSwitchType_RANDOM,
			_ElevatorSwitchType_ALTERNATE,
			_ElevatorSwitchType_ALL_UP,
			_ElevatorSwitchType_ALL_DOWN
		};
	
		enum _OffsetType
		{
			_OffsetType_RANDOM,
			_OffsetType_ALL_SAME,
			_OffsetType_SPATIALLY_PERIODIC
		};
	
		enum _FillType
		{
			_FillType_RND,
			_FillType_HALFN_HALF,
			_FillType_PURE
		};
	
		enum _SinglePathType
		{
			_SinglePathType_NORMAL,
			_SinglePathType_LOW,
			_SinglePathType_MID,
			_SinglePathType_HIGH
		};
	
		enum _DoublePathType
		{
			_DoublePathType_SEPARATED,
			_DoublePathType_GAP,
			_DoublePathType_INDEPENDENT,
			_DoublePathType_LENGTH
		};
	
		enum _TriplePathType
		{
			_TriplePathType_SEPARATED,
			_TriplePathType_INDEPENDENT,
			_TriplePathType_LENGTH
		};
	
		enum _StartType
		{
			_StartType_TOP,
			_StartType_MIDDLE,
			_StartType_BOTTOM,
			_StartType_LENGTH
		};

        /// <summary>
        /// When true, blocks have a lower lip than usual. This is used for InvertHero, so he is standing on the bottom of blocks properly.
        /// (Otherwise you want the lips to be higher, so your head doesn't hit them as easily).
        /// </summary>
        bool UseLowerBlockBounds;

		/// <summary>
		/// A callback to modify AutoGen parameters after they have been set
		/// </summary>
		boost::shared_ptr<Multicaster_2<boost::shared_ptr<Level>, boost::shared_ptr<PieceSeedData> > > MyModParams;

		void Release();

		std::map<boost::shared_ptr<AutoGen>, boost::shared_ptr<AutoGen_Parameters> > GenParams;
		void CalcGenParams( const boost::shared_ptr<PieceSeedData> &SeedData, const boost::shared_ptr<Level> &level );
		boost::shared_ptr<AutoGen_Parameters> FindParams( const boost::shared_ptr<AutoGen> &gen );

		boost::shared_ptr<StyleData> Clone();

		float Zoom;
		TimeTypes TimeType;

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

	
		std::vector<float> BlockFillTypeRatio;
	
		_BlockFillType BlockFillType;

		_OverlapCleanupType OverlapCleanupType;


	
		std::vector<float> Sparsity;
		std::vector<float> SparsityTypeRatio;
	
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
	
		std::vector<float> ElevatorSwitchTypeRatio;

	
		_OffsetType PendulumOffsetType, FlyingBlobOffsetType;
	
		std::vector<float> OffsetTypeRatio;

		std::vector<float> FillTypeRatio;
	
		_FillType FillType;

	
		static std::vector<float> _SinglePathRatio;
	
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

		boost::shared_ptr<Rand> Rnd;
		StyleData( const boost::shared_ptr<Rand> &Rnd );

		void Calculate( const boost::shared_ptr<Upgrades> &u );

	
		virtual void CalculateKeepUnused( float JumpLevel );

	
		virtual void Randomize();

		float GetSparsity();

		int GetOffset( int Period, Vector2 pos, _OffsetType Type );
	
		void SetStartType( PhsxData &Start, Vector2 &CheckpointShift, _StartType StartType, const boost::shared_ptr<PieceSeedData> &Piece );

	
		void SetSinglePathType( const boost::shared_ptr<MakeData> &makeData, const boost::shared_ptr<Level> &level, const boost::shared_ptr<PieceSeedData> &Piece );

		void SetDoubePathType( const boost::shared_ptr<MakeData> &makeData, const boost::shared_ptr<Level> &level, const boost::shared_ptr<PieceSeedData> &Piece );

		void SetTriplePathType( const boost::shared_ptr<MakeData> &makeData, const boost::shared_ptr<Level> &level, const boost::shared_ptr<PieceSeedData> &Piece );

		void SuppressGroundCeiling( const boost::shared_ptr<PieceSeedData> &piece );

		void SetToMake_BouncyHallway( const boost::shared_ptr<PieceSeedData> &piece );

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef STYLEDATA
