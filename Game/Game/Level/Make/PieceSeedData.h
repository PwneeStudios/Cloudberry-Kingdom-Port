#ifndef PIECESEEDDATA
#define PIECESEEDDATA

#include <small_header.h>

//#include "Core/Tools/Random.h"
//#include "Game/Level/Make/LockableBool.h"
//#include "Game/Level/Make/LevelSeedData.h"
//#include "Game/Level/Make/Parameters/LevelGenData.h"
//#include "Game/Level/Make/Parameters/RandomDifficulty.h"
//#include "Game/Level/Make/Parameters/Upgrades.h"
//#include "Game/Level/Make/Parameters/StyleData/StyleData.h"
//#include "Game/Level/Make/Parameters/StyleData/BigData.h"
//#include "Game/Level/Make/Parameters/StyleData/UpData.h"
//#include "Game/Level/Make/Parameters/StyleData/DownData.h"
//#include "Game/Level/Make/Parameters/StyleData/OneScreenData.h"
//#include "Game/Level/Make/Parameters/StyleData/SingleData.h"
//#include "Game/Objects/AutoGen.h"
//#include "Game/Objects/In Game Objects/Grab/MakeData.h"
//#include "Game/Level/Level.h"
//#include "Game/Objects/In Game Objects/Grab/Coin__Auto.h"
//#include "Game/Objects/In Game Objects/Obstacles/BlockEmitter__Auto.h"
//#include "Game/Tools/Tools.h"


namespace CloudberryKingdom
{
	struct PieceSeedData
	{
		MetaGameType MyMetaGameType;

		void ApplyMetaGameStyling();

		/// <summary>
		/// Uses the upgrade data in MyUpgrades1 to calculate the level gen data.
		/// </summary>
		void CalculateSimple();

		boost::shared_ptr<Lambda_1<boost::shared_ptr<Level> > > PreStage1, PreStage2;

		boost::shared_ptr<AutoGen_Parameters> operator []( const boost::shared_ptr<AutoGen> &gen );

		/// <summary>
		/// Type of level to be made, relating to shape and direction. Different from the GameType.
		/// </summary>
		LevelGeometry GeometryType;

		/// <summary>
		/// Type of level to be made, relating to the camera zoom.
		/// </summary>
		LevelZoom ZoomType;

		float ExtraBlockLength;

		boost::shared_ptr<StyleData> Style;

		boost::shared_ptr<RichLevelGenData> MyGenData;
		boost::shared_ptr<Upgrades> MyUpgrades1, MyUpgrades2;

		const boost::shared_ptr<Upgrades> &getu() const;

		Vector2 Start, End;
		Vector2 CamZoneStartAdd, CamZoneEndAdd;

		int Paths;
		bool LockNumOfPaths;

		LadderType Ladder;
		BoxStyle ElevatorBoxStyle;

		boost::shared_ptr<PieceSeedData> PieceSeed; // Used if this is a platform used for making new platforms

		bool CheckpointsAtStart, InitialCheckpointsHere;

		int MyPieceIndex;

		void Release();

		void CopyFrom( const boost::shared_ptr<PieceSeedData> &piece );

		void CopyUpgrades( const boost::shared_ptr<PieceSeedData> &piece );

		void CalcBounds();

		void StandardClose();

	
		boost::shared_ptr<LevelSeedData> MyLevelSeed;
	
		const boost::shared_ptr<Rand> &getRnd() const;

		PieceSeedData( const boost::shared_ptr<LevelSeedData> &LevelSeed );

		PieceSeedData( int Index, LevelGeometry Type, const boost::shared_ptr<LevelSeedData> &LevelSeed );

	
		void Init( LevelGeometry Type );


	
		void NoBlobs();

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef PIECESEEDDATA
