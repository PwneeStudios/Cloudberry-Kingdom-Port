#ifndef LEVELPIECE
#define LEVELPIECE

#include <global_header.h>

namespace CloudberryKingdom
{
	struct LevelPiece
	{
	
		int Par;

		int StartPhsxStep, DelayStart;

		std::shared_ptr<Level> MyLevel;
		int NumBobs;
		BobVec Computer;

		int PieceLength;

		std::vector<std::shared_ptr<ComputerRecording> > Recording_Renamed;

		void Shift( Vector2 shift );

		std::vector<PhsxData> StartData;
		std::vector<Vector2> CheckpointShift;
		Vector2 CamStartPos;

		Vector2 LastPoint;

		std::shared_ptr<PieceSeedData> MyData;
		std::shared_ptr<MakeData> MyMakeData;

		void Release();

		LevelPiece( int Length, const std::shared_ptr<Level> &level, BobVec computer, int numBobs );

		PhsxData GetLastData();
		PhsxData GetLastData( int Index );
	};
}


#endif	//#ifndef LEVELPIECE
