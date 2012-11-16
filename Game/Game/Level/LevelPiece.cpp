#include <global_header.h>

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;


namespace CloudberryKingdom
{

	void LevelPiece::Shift( Vector2 shift )
	{
		if ( Recording_Renamed.empty() )
			return;

		for ( int i = 0; i < Recording_Renamed.size(); i++ )
			if ( Recording_Renamed[ i ] != 0 )
				Recording_Renamed[ i ]->Shift( shift );
	}

	void LevelPiece::Release()
	{
		MyData.reset();
		MyMakeData.reset();

		MyLevel.reset();

		StartData.clear();

		if ( Recording_Renamed.size() > 0 )
			for ( std::vector<CloudberryKingdom::ComputerRecording*>::const_iterator record = Recording_Renamed.begin(); record != Recording_Renamed.end(); ++record )
				//ComputerRecording.ToPool(record);
				( *record )->Release();
		Recording_Renamed.clear();

		if ( Computer.size() > 0 )
			for ( std::vector<CloudberryKingdom::Bob*>::const_iterator comp = Computer.begin(); comp != Computer.end(); ++comp )
				( *comp )->Release();

		if ( Computer.size() > 0 )
		for ( int i = 0; i < Computer.size(); i++ )
			Computer[ i ]->getCore()->MyLevel.reset();
		Computer.clear();

		/*
		if (Recording != null)
		for (int i = 0; i < Recording.Length; i++)
		    Recording[i].Release();
		Recording = null;*/
		StartData.clear();
	}

	LevelPiece::LevelPiece( int Length, const std::shared_ptr<Level> &level, std::vector<Bob*> computer, int numBobs )
	{
		NumBobs = 0;
		if ( computer.size() > 0 )
			NumBobs = computer.size();
		else
			NumBobs = numBobs;

		MyLevel = level;
		Computer = computer;

		PieceLength = 6000; // Length;
		int Padding = 100;

		int n = __max( 1, NumBobs );
		StartData = std::vector<PhsxData>( n );
		CheckpointShift = std::vector<Vector2>( n );
		if ( computer.size() > 0 )
		{
			Recording_Renamed = std::vector<ComputerRecording*>( NumBobs );
			for ( int i = 0; i < NumBobs; i++ )
			{
				//Recording[i] = new ComputerRecording();
				//Recording[i].Init(PieceLength + Padding);
				Recording_Renamed[ i ] = ComputerRecording::FromPool();
				computer[ i ]->MyPieceIndex = i;
				computer[ i ]->MyRecord = Recording_Renamed[ i ];
			}
		}
	}

	PhsxData LevelPiece::GetLastData()
	{
		return GetLastData( 0 );
	}

	PhsxData LevelPiece::GetLastData( int Index )
	{
		PhsxData LastData = PhsxData();
		LastData.Position = Recording_Renamed[ Index ]->AutoLocs[ PieceLength - 1 ];
		LastData.Velocity = Recording_Renamed[ Index ]->AutoVel[ PieceLength - 1 ];

		return LastData;
	}
}
