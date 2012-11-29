#include "MakeData.h"

namespace CloudberryKingdom
{
	void MakeData::Release()
	{
		LevelSeed.reset();
		PieceSeed.reset();
		GenData.reset();
	}

	void MakeData::Init( const std::shared_ptr<PieceSeedData> &data )
	{
		int N = data->Paths;

		ComputerWaitAtStart = true;
		ComputerWaitAtStartLength = std::vector<int>( 4 );
		Vector2 WaitRange = data->Style_COMPUTER_WAIT_LENGTH_RANGE;
		for ( int i = 0; i < 4; i++ )
			ComputerWaitAtStartLength[ i ] = static_cast<int>( data->getRnd()->RndFloat(WaitRange) );
		SparsityMultiplier = 1;

		NumInitialBobs = N;

		Start = std::vector<PhsxData>( N );
		CheckpointShift = std::vector<Vector2>( N );
		MoveData = std::vector<Bob::BobMove*>( N );
		for ( int i = 0; i < N; i++ )
		{
			Start[ i ] = PhsxData();
			CheckpointShift[ i ] = Vector2();
			MoveData[ i ] = Bob::BobMove();
			MoveData[ i ].Init();
		}
		CamStartPos = Vector2();

		InitialPlats = FinalPlats = InitialCamZone = true;
		SkinnyStart = false;

		SetTRCamBound = true;
	}

	BobVec MakeData::MakeBobs( const std::shared_ptr<Level> &level )
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
			Computers[ i ] = std::make_shared<Bob>( level->DefaultHeroType, true );

			level->AddBob( Computers[ i ] );
			Sleep();
		}

		for ( int i = 0; i < NumInitialBobs; i++ )
		{
			Computers[ i ]->Immortal = true;

			Computers[ i ]->ComputerWaitAtStart = ComputerWaitAtStart;
			Computers[ i ]->ComputerWaitAtStartLength = ComputerWaitAtStartLength[ i ];
			Computers[ i ]->MoveData = MoveData[ i ];

			Sleep();
		}

		return Computers;
	}

	std::shared_ptr<LevelPiece> MakeData::MakeLevelPiece( const std::shared_ptr<Level> &level, BobVec bobs, int Length, int StartPhsxStep )
	{
		std::shared_ptr<LevelPiece> Piece = level->StartNewPiece( Length, bobs );
		Piece->MyData = PieceSeed;
		Piece->MyMakeData = this;
		for ( int i = 0; i < NumInitialBobs; i++ )
		{
			bobs[ i ]->MyPiece = Piece;
			Piece->StartData[ i ] = Start[ i ];
			Piece->CheckpointShift[ i ] = CheckpointShift[ i ];
			bobs[ i ]->IndexOffset = StartPhsxStep;
			Sleep();
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
}