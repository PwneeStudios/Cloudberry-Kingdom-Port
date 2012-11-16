#ifndef SWARMRECORD
#define SWARMRECORD

#include <vector>
#include <queue>
#include <tchar.h>

namespace CloudberryKingdom
{
	class LevelPiece;
}

namespace CloudberryKingdom
{
	class Recording;
}

namespace CloudberryKingdom
{
	class QuadClass;
}

namespace CloudberryKingdom
{
	class BobLink;
}

namespace CloudberryKingdom
{
	class SpriteAnimGroup;
}

namespace CloudberryKingdom
{
	class Level;
}


//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;

namespace CloudberryKingdom
{
	class SwarmRecord
	{
	public:
		std::shared_ptr<LevelPiece> MyLevelPiece;

		std::queue<Recording*> Records;
		std::shared_ptr<Recording> MainRecord;
#if defined(XBOX)
	private:
		int MaxRecords;
#else
		int MaxRecords;
#endif

		std::shared_ptr<QuadClass> BobQuad;

	public:
		void Release();

		SwarmRecord();

		void Draw( int Step, const std::shared_ptr<Level> &level, std::vector<SpriteAnimGroup*> AnimGroup, std::vector<BobLink*> &BobLinks );

		void AddRecord( const std::shared_ptr<Recording> &Record, int Step );

	private:
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef SWARMRECORD
