#ifndef SWARMRECORD
#define SWARMRECORD

#include <small_header.h>

//#include "Core/Animation/SpriteAnim.h"
//#include "Core/Graphics/Draw/Quads/QuadClass.h"
//#include "Core/Texture/EzTexture.h"
//#include "Game/Level/LevelPiece.h"
//#include "Game/Level/Replays/Recording.h"
//#include "Game/Player/PlayerManager.h"
//#include "Game/Objects/Bob/BobLink.h"
//#include "Game/Objects/In Game Objects/Grab/MakeData.h"
//#include "Game/Level/Level.h"
//#include "Game/Tools/Tools.h"



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
