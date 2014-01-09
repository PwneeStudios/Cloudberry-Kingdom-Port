#ifndef SWARMBUNDLE
#define SWARMBUNDLE

#include <small_header.h>

//#include "Core/Animation/SpriteAnim.h"
//#include "Core/Tools/CoreMath.h"
//#include "Game/Level/Replays/SwarmRecord.h"
//#include "Game/Objects/Bob/Bob.h"
//#include "Game/Objects/Bob/BobLink.h"
//#include "Game/Objects/In Game Objects/Grab/MakeData.h"
//#include "Game/Level/Level.h"


namespace CloudberryKingdom
{

	struct SwarmBundle
	{

	
		struct BobToSpritesLambda : public Lambda_2<std::map<int, boost::shared_ptr<SpriteAnim> >, Vector2>
		{
		
			boost::shared_ptr<Bob> bob;
		
			BobToSpritesLambda( const boost::shared_ptr<Bob> &bob );

			void Apply( const std::map<int, boost::shared_ptr<SpriteAnim> > &dict, const Vector2 &pos );
		};

	
		std::vector<boost::shared_ptr<SwarmRecord> > Swarms;
	
		boost::shared_ptr<SwarmRecord> CurrentSwarm;

		bool Initialized;
	
		std::vector<boost::shared_ptr<SpriteAnimGroup> > AnimGroup;

		std::vector<boost::shared_ptr<BobLink> > BobLinks;

	
		void Release();

		SwarmBundle();

		void Init( const boost::shared_ptr<Level> &level );

		void SetSwarm( const boost::shared_ptr<Level> &level, int i );

		const int getSwarmIndex() const;

		const int getNumSwarms() const;

		bool GetNextSwarm( const boost::shared_ptr<Level> &level );

		bool EndCheck( const boost::shared_ptr<Level> &level );

		void StartNewSwarm();

		void Draw( int Step, const boost::shared_ptr<Level> &level );
	};
}


#endif	//#ifndef SWARMBUNDLE
