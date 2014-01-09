#ifndef MAKEDARKBOTTOM
#define MAKEDARKBOTTOM

#include <small_header.h>

#include "Game/Level/Make/MakePiece/MakeVertical/MakeFinalDoor_Vertical.h"
//#include "Game/Objects/Game Objects/GameObjects/Region.h"
//#include "Game/Objects/In Game Objects/Grab/MakeData.h"
//#include "Game/Level/Level.h"


namespace CloudberryKingdom
{
	struct Level;
}

namespace CloudberryKingdom
{
	struct MakeDarkBottom : public MakeFinalDoorVertical
	{
	
		virtual ~MakeDarkBottom()
		{
#ifdef BOOST_BIN
			OnDestructor( "MakeDarkBottom" );
#endif
		}


		MakeDarkBottom( const boost::shared_ptr<Level> &level );

		virtual void Phase3();

	};
}


#endif	//#ifndef MAKEDARKBOTTOM
