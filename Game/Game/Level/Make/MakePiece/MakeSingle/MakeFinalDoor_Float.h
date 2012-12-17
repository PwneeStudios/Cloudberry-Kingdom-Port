#ifndef MAKEFINALDOOR_FLOAT
#define MAKEFINALDOOR_FLOAT

#include <global_header.h>

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
