#ifndef MAKEFINALDOOR_FLOAT
#define MAKEFINALDOOR_FLOAT

#include <global_header.h>

namespace CloudberryKingdom
{
	class Level;
}

namespace CloudberryKingdom
{
	class BlockBase;
}

namespace CloudberryKingdom
{
	class ILevelConnector;
}

namespace CloudberryKingdom
{
	class Door;
}


//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;


namespace CloudberryKingdom
{
	class MakeFinalDoor_Float : public MakeThing
	{
	private:
		std::shared_ptr<Level> MyLevel;

		/// <summary>
		/// The block on which the final door rests on.
		/// </summary>
	public:
		std::shared_ptr<BlockBase> FinalBlock;

		/// <summary>
		/// The position of the final door.
		/// </summary>
		Vector2 FinalPos;

		MakeFinalDoor_Float( const std::shared_ptr<Level> &level );

		virtual void Phase1();

		virtual void Phase2();

		virtual void Phase3();

		static void AttachDoorAction( const std::shared_ptr<ILevelConnector> &door );

		static void SetFinalDoor( const std::shared_ptr<Door> &door, const std::shared_ptr<Level> &level, Vector2 FinalPos );
	};
}


#endif	//#ifndef MAKEFINALDOOR_FLOAT
