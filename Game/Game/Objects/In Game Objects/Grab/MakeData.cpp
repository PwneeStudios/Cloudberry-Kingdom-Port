#include "small_header.h"

#include "Game/Objects/In Game Objects/Grab/MakeData.h"
#include "Game/Level/Make/PieceSeedData.h"
#include "Game/Level/Make/Parameters/StyleData/StyleData.h"
#include "Core/Tools/Random.h"
#include "Game/Level/Level.h"
#include "Game/Level/LevelPiece.h"

#include <MasterHack.h>

namespace CloudberryKingdom
{

	void MakeData::Release()
	{
		LevelSeed.reset();
		PieceSeed.reset();
		GenData.reset();
	}

	void MakeData::Init( const boost::shared_ptr<PieceSeedData> &data )
	{
		int N = data->Paths;

		ComputerWaitAtStart = true;
		ComputerWaitAtStartLength = std::vector<int>( 4 );
		Vector2 WaitRange = data->Style->ComputerWaitLengthRange;
		for ( int i = 0; i < 4; i++ )
			ComputerWaitAtStartLength[ i ] = static_cast<int>( data->getRnd()->RndFloat(WaitRange) );
		SparsityMultiplier = 1;

		NumInitialBobs = N;

		Start = std::vector<PhsxData>( N );
		CheckpointShift = std::vector<Vector2>( N );
		MoveData = std::vector<Bob::BobMove>( N );
		for ( int i = 0; i < N; i++ )
		{
			Start[ i ] = PhsxData();
			CheckpointShift[ i ] = Vector2();
			MoveData[ i ].Init();
		}
		CamStartPos = Vector2();

		InitialPlats = FinalPlats = InitialCamZone = true;
		SkinnyStart = false;

		SetTRCamBound = true;
	}

	BobVec MakeData::MakeBobs( const boost::shared_ptr<Level> &level )
	{
		/*
		if (level.MySourceGame.MyGameFlags.IsDoppleganger)
		{
		    for (int i = 0; i < NumInitialBobs; i += 2)
		    {
		        MoveData[i + 1].Copy = i;
	
		        if (level.MySourceGame.MyGameFlags.IsDopplegangerInvert)
		            MoveData[i + 1].InvertDirX = true;
		    }
		}
		*/


		BobVec Computers = BobVec( NumInitialBobs );

		level->Bobs.clear();
		for ( int i = 0; i < NumInitialBobs; i++ )
		{
			//Computers[i] = new Bob(Prototypes.bob[level.DefaultHeroType], true);
			Computers[ i ] = boost::make_shared<Bob>( level->DefaultHeroType, true );
			Bob_PostConstruct( Computers[i], level->DefaultHeroType, true );

			level->AddBob( Computers[ i ] );
			/*Sleep()*/;
		}

		for ( int i = 0; i < NumInitialBobs; i++ )
		{
			Computers[ i ]->Immortal = true;

			Computers[ i ]->ComputerWaitAtStart = ComputerWaitAtStart;
			Computers[ i ]->ComputerWaitAtStartLength = ComputerWaitAtStartLength[ i ];
			Computers[ i ]->MoveData = MoveData[ i ];

			//Sleep();
		}

		return Computers;
	}

	boost::shared_ptr<LevelPiece> MakeData::MakeLevelPiece( const boost::shared_ptr<Level> &level, BobVec bobs, int Length, int StartPhsxStep )
	{
		boost::shared_ptr<LevelPiece> Piece = level->StartNewPiece( Length, bobs );
		Piece->MyData = PieceSeed;
		Piece->MyMakeData = shared_from_this();
		for ( int i = 0; i < NumInitialBobs; i++ )
		{
			bobs[ i ]->MyPiece = Piece;
			Piece->StartData[ i ] = Start[ i ];
			Piece->CheckpointShift[ i ] = CheckpointShift[ i ];
			bobs[ i ]->IndexOffset = StartPhsxStep;
			//Sleep();
		}

		Piece->StartPhsxStep = StartPhsxStep;

		return Piece;
	}

	void MakeData::InitializeInstanceFields()
	{
		MinStartPositionsToMake = 4;
		TopLikeBottom = false;
		TopLikeBottom_Thin = false;
		BlocksAsIs = false;
	}

	MakeData::MakeData() :
		ComputerWaitAtStart( false ),
		SparsityMultiplier( 0 ),
		NumInitialBobs( 0 ),
		MinStartPositionsToMake( 0 ),
		InitialPlats( false ),
		InitialCamZone( false ),
		FinalPlats( false ),
		SkinnyStart( false ),
		SetTRCamBound( false ),
		TopLikeBottom( false ),
		TopLikeBottom_Thin( false ),
		BlocksAsIs( false ),
		Index( 0 ),
		OutOf( 0 )
	{
		InitializeInstanceFields();
	}
}