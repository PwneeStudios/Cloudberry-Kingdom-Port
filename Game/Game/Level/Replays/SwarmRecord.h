#ifndef SWARMRECORD
#define SWARMRECORD

#include <global_header.h>


namespace CloudberryKingdom
{
	struct SwarmRecord
	{
	
		std::shared_ptr<LevelPiece> MyLevelPiece;

		std::list<std::shared_ptr<Recording> > Records;
		std::shared_ptr<Recording> MainRecord;
#if defined(XBOX)
	
		int MaxRecords;
#else
		int MaxRecords;
#endif

		std::shared_ptr<QuadClass> BobQuad;

	
		void Release();

		SwarmRecord();

		void Draw( int Step, const std::shared_ptr<Level> &level, std::vector<std::shared_ptr<SpriteAnimGroup> > AnimGroup, std::vector<std::shared_ptr<BobLink> > &BobLinks );

		void AddRecord( const std::shared_ptr<Recording> &Record, int Step );

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef SWARMRECORD
