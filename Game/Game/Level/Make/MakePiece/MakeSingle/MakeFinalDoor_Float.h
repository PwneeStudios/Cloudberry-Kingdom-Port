#ifndef MAKEFINALDOOR_FLOAT
#define MAKEFINALDOOR_FLOAT

#include <small_header.h>

//#include "Game/Objects/In Game Objects/Blocks/Block.h"
//#include "Game/Games/Meta Games/StringWorlds/StringWorld.h"
//#include "Game/Games/Meta Games/StringWorlds/LevelConnector.h"
//#include "Game/Level/Make/PieceSeedData.h"
#include "Game/Level/Make/MakePiece/MakeThing.h"
//#include "Game/Objects/Door/Door.h"
//#include "Game/Objects/In Game Objects/Blocks/NormalBlock.h"
//#include "Game/Objects/In Game Objects/Grab/MakeData.h"
//#include "Game/Level/Level.h"
//#include "Game/Objects/Special/CameraZone.h"
//#include "Game/Tools/Recycler.h"
//#include "Game/Tools/Tools.h"


namespace CloudberryKingdom
{
	struct Level;
}

namespace CloudberryKingdom
{
	struct BlockBase;
}

namespace CloudberryKingdom
{
	struct ILevelConnector;
}

namespace CloudberryKingdom
{
	struct Door;
}



namespace CloudberryKingdom
{
	struct MakeFinalDoor_Float : public MakeThing
	{
	
		virtual ~MakeFinalDoor_Float()
		{
#ifdef BOOST_BIN
			OnDestructor( "MakeFinalDoor_Float" );
#endif
		}


		boost::shared_ptr<Level> MyLevel;

		/// <summary>
		/// The block on which the final door rests on.
		/// </summary>
	
		boost::shared_ptr<BlockBase> FinalBlock;

		/// <summary>
		/// The position of the final door.
		/// </summary>
		Vector2 FinalPos;

		MakeFinalDoor_Float( const boost::shared_ptr<Level> &level );

		virtual void Phase1();

		virtual void Phase2();

		virtual void Phase3();

		static void AttachDoorAction( const boost::shared_ptr<ILevelConnector> &door );

		static void SetFinalDoor( const boost::shared_ptr<Door> &door, const boost::shared_ptr<Level> &level, Vector2 FinalPos );
	};
}


#endif	//#ifndef MAKEFINALDOOR_FLOAT
