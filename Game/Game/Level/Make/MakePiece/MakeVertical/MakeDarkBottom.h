#ifndef MAKEDARKBOTTOM
#define MAKEDARKBOTTOM

#include "MakeFinalDoor.h"

namespace CloudberryKingdom
{
	class Level;
}


//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
using namespace Microsoft::Xna::Framework;

namespace CloudberryKingdom
{
	class MakeDarkBottom : public MakeFinalDoorVertical
	{
	public:
		MakeDarkBottom( const std::shared_ptr<Level> &level );

		virtual void Phase3();
	};
}


#endif	//#ifndef MAKEDARKBOTTOM
