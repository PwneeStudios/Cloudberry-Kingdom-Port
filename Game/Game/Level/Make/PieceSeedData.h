#ifndef PIECESEEDDATA
#define PIECESEEDDATA

#include <global_header.h>

namespace CloudberryKingdom
{
	struct PieceSeedData
	{
		/// <summary>
		/// Uses the upgrade data inMyUpgrades1 to calculate the level gen data.
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
