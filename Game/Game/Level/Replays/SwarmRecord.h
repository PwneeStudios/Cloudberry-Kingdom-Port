#ifndef SWARMRECORD
#define SWARMRECORD

#include <global_header.h>


namespace CloudberryKingdom
{
	struct SwarmRecord
	{
	
		boost::shared_ptr<LevelPiece> MyLevelPiece;

		std::list<boost::shared_ptr<Recording> > Records;
		boost::shared_ptr<Recording> MainRecord;
#if defined(XBOX)
	
		int MaxRecords;
#else
		int MaxRecords;
#endif

		boost::shared_ptr<QuadClass> BobQuad;

	
		void Release();

		SwarmRecord();

		void Draw( int Step, const boost::shared_ptr<Level> &level, std::vector<boost::shared_ptr<SpriteAnimGroup> > AnimGroup, std::vector<boost::shared_ptr<BobLink> > &BobLinks );

		void AddRecord( const boost::shared_ptr<Recording> &Record, int Step );

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef SWARMRECORD
