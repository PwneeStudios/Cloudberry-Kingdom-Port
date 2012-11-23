#ifndef LEVELPIECE
#define LEVELPIECE

#include <global_header.h>

namespace CloudberryKingdom
{
	class Level;
}

namespace CloudberryKingdom
{
	class Bob;
}

namespace CloudberryKingdom
{
	class ComputerRecording;
}

namespace Microsoft
{
	namespace Xna
	{
		namespace Framework
		{
			class Vector2;
		}
	}
}

namespace CloudberryKingdom
{
	class PieceSeedData;
}

namespace CloudberryKingdom
{
	class LevelPiece
	{
	public:
		int Par;

		int StartPhsxStep, DelayStart;

		std::shared_ptr<Level> MyLevel;
		int NumBobs;
		std::vector<Bob*> Computer;

		int PieceLength;

//C# TO C++ CONVERTER NOTE: The variable Recording was renamed since it is named the same as a user-defined type:
		std::vector<ComputerRecording*> Recording_Renamed;

		void Shift( Vector2 shift );

		std::vector<PhsxData> StartData;
		std::vector<Vector2> CheckpointShift;
		Vector2 CamStartPos;

		Vector2 LastPoint;

		std::shared_ptr<PieceSeedData> MyData;
		std::shared_ptr<MakeData> MyMakeData;

		void Release();

		LevelPiece( int Length, const std::shared_ptr<Level> &level, std::vector<Bob*> computer, int numBobs );

		PhsxData GetLastData();
		PhsxData GetLastData( int Index );
	};
}


#endif	//#ifndef LEVELPIECE
