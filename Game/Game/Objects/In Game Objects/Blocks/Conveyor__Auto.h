#ifndef CONVEYOR__AUTO
#define CONVEYOR__AUTO

#include <small_header.h>

//#include "Game/Objects/ObjectBase.h"
//#include "Game/Level/Make/DifficultyHelper.h"
//#include "Game/Level/Make/PieceSeedData.h"
//#include "Game/Level/Make/Parameters/LevelGenData.h"
#include "Game/Level/Make/Parameters/Param.h"
//#include "Game/Level/Make/Parameters/StyleData/StyleData.h"
#include "Game/Objects/AutoGen.h"
//#include "Game/Objects/In Game Objects/Blocks/Conveyor.h"
//#include "Game/Objects/In Game Objects/Grab/MakeData.h"
//#include "Game/Level/Level.h"
//#include "Game/Player/Hero Physics/Spaceship.h"
//#include "Game/Tools/Recycler.h"


namespace CloudberryKingdom
{
	struct PieceSeedData;
}

namespace CloudberryKingdom
{
	struct Level;
}

namespace CloudberryKingdom
{
	struct AutoGen_Parameters;
}

namespace CloudberryKingdom
{
	struct ObjectBase;
}

namespace CloudberryKingdom
{
	struct ConveyorBlock_Parameters : public AutoGen_Parameters
	{
	
		virtual ~ConveyorBlock_Parameters()
		{
#ifdef BOOST_BIN
			OnDestructor( "ConveyorBlock_Parameters" );
#endif
		}


		Param Width, KeepUnused, Speed;

		virtual void SetParameters( const boost::shared_ptr<PieceSeedData> &PieceSeed, const boost::shared_ptr<Level> &level );

	};

	struct ConveyorBlock_AutoGen : public AutoGen
	{
	
		static boost::shared_ptr<ConveyorBlock_AutoGen> instance;
	
		const static boost::shared_ptr<ConveyorBlock_AutoGen> &getInstance();

	
		ConveyorBlock_AutoGen();

	
		boost::shared_ptr<AutoGen_Parameters> SetParameters( const boost::shared_ptr<PieceSeedData> &data, const boost::shared_ptr<Level> &level );

		void PreFill_2( const boost::shared_ptr<Level> &level, Vector2 BL, Vector2 TR );

		void Cleanup_2( const boost::shared_ptr<Level> &level, Vector2 BL, Vector2 TR );

		boost::shared_ptr<ConveyorBlock_Parameters> GetParams( const boost::shared_ptr<Level> &level );

		boost::shared_ptr<ObjectBase> CreateAt( const boost::shared_ptr<Level> &level, Vector2 pos, Vector2 BL, Vector2 TR );
	};
}


#endif	//#ifndef CONVEYOR__AUTO
