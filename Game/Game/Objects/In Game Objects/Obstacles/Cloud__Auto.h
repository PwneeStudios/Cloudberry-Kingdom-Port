#ifndef CLOUD__AUTO
#define CLOUD__AUTO

#include <small_header.h>

//#include "Game/Objects/ObjectBase.h"
//#include "Game/Level/Make/PieceSeedData.h"
#include "Game/Level/Make/Parameters/Param.h"
#include "Game/Objects/AutoGen.h"
//#include "Game/Objects/In Game Objects/Grab/MakeData.h"
//#include "Game/Level/Level.h"
//#include "Game/Objects/In Game Objects/Obstacles/Cloud.h"
//#include "Game/Tools/Recycler.h"


namespace CloudberryKingdom
{
	struct Cloud_Parameters : public AutoGen_Parameters
	{
	
		virtual ~Cloud_Parameters()
		{
#ifdef BOOST_BIN
			OnDestructor( "Cloud_Parameters" );
#endif
		}


		Param Size, Shiftiness;

		virtual void SetParameters( const boost::shared_ptr<PieceSeedData> &PieceSeed, const boost::shared_ptr<Level> &level );

	};

	struct Cloud_AutoGen : public AutoGen
	{
	
		static boost::shared_ptr<Cloud_AutoGen> instance;
	
		const static boost::shared_ptr<Cloud_AutoGen> &getInstance();

	
		Cloud_AutoGen();

	
		boost::shared_ptr<AutoGen_Parameters> SetParameters( const boost::shared_ptr<PieceSeedData> &data, const boost::shared_ptr<Level> &level );

		void PreFill_2( const boost::shared_ptr<Level> &level, Vector2 BL, Vector2 TR );

		void Cleanup_2( const boost::shared_ptr<Level> &level, Vector2 BL, Vector2 TR );

		boost::shared_ptr<ObjectBase> CreateAt( const boost::shared_ptr<Level> &level, Vector2 pos, Vector2 BL, Vector2 TR );
	};
}


#endif	//#ifndef CLOUD__AUTO
