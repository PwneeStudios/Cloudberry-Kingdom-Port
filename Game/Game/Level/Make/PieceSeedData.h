#ifndef PIECESEEDDATA
#define PIECESEEDDATA

#include <global_header.h>

namespace CloudberryKingdom
{
	class Lambda_1;
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
	class StyleData;
}

namespace CloudberryKingdom
{
	class RichLevelGenData;
}

namespace CloudberryKingdom
{
	class Upgrades;
}

namespace CloudberryKingdom
{
	class LevelSeedData;
}

namespace CloudberryKingdom
{
	class Rand;
}


//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
using namespace Microsoft::Xna::Framework;

namespace CloudberryKingdom
{
	enum LevelGeometry
	{
		LevelGeometry_RIGHT,
		LevelGeometry_UP,
		LevelGeometry_ONE_SCREEN,
		LevelGeometry_DOWN,
		LevelGeometry_BIG
	};
	enum LevelZoom
	{
		LevelZoom_NORMAL,
		LevelZoom_BIG
	};

	class PieceSeedData
	{
		/// <summary>
		/// Uses the upgrade data inMyUpgrades1 to calculate the level gen data.
		/// </summary>
	public:
		void CalculateSimple();

		std::shared_ptr<Lambda_1<Level*> > PreStage1, PreStage2;

		std::shared_ptr < AutoGen_Parameters *operator []( const std::shared_ptr<AutoGen> &gen );

		/// <summary>
		/// Type of level to be made, relating to shape and direction. Different from the GameType.
		/// </summary>
		LevelGeometry GeometryType;

		/// <summary>
		/// Type of level to be made, relating to the camera zoom.
		/// </summary>
		LevelZoom ZoomType;

		float ExtraBlockLength;

		std::shared_ptr<StyleData> Style;

		std::shared_ptr<RichLevelGenData> MyGenData;
		std::shared_ptr<Upgrades> MyUpgrades1, MyUpgrades2;

		const std::shared_ptr<Upgrades> &getu() const;

		Vector2 Start, End;
		Vector2 CamZoneStartAdd, CamZoneEndAdd;

		int Paths;
		bool LockNumOfPaths;

		Level::LadderType Ladder;
		BlockEmitter_Parameters::BoxStyle ElevatorBoxStyle;

		std::shared_ptr<PieceSeedData> PieceSeed; // Used if this is a platform used for making new platforms

		bool CheckpointsAtStart, InitialCheckpointsHere;

		int MyPieceIndex;

		void Release();

		void CopyFrom( const std::shared_ptr<PieceSeedData> &piece );

		void CopyUpgrades( const std::shared_ptr<PieceSeedData> &piece );

		void CalcBounds();

		void StandardClose();

	private:
		std::shared_ptr<LevelSeedData> MyLevelSeed;
	public:
		const std::shared_ptr<Rand> &getRnd() const;

		PieceSeedData( const std::shared_ptr<LevelSeedData> &LevelSeed );

		PieceSeedData( int Index, LevelGeometry Type, const std::shared_ptr<LevelSeedData> &LevelSeed );

	private:
		void Init( LevelGeometry Type );


	public:
		void NoBlobs();

	private:
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef PIECESEEDDATA
