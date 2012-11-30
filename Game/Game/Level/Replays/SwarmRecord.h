#ifndef SWARMRECORD
#define SWARMRECORD

#include <global_header.h>

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

		void Draw( int Step, const std::shared_ptr<Level> &level, std::vector<std::shared_ptr<SpriteAnimGroup> > AnimGroup, std::vector<std::shared_ptr<BobLink> > &BobLinks );

		void AddRecord( const std::shared_ptr<Recording> &Record, int Step );

	private:
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef SWARMRECORD
