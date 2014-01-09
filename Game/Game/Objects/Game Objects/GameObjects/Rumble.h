#ifndef RUMBLE
#define RUMBLE

#include <small_header.h>

#include "Game/Objects/Game Objects/GameObjects/GUI_Panel.h"
//#include "Game/Tools/Tools.h"


namespace CloudberryKingdom
{

	struct Rumble : public GUI_Panel
	{
	
		virtual ~Rumble()
		{
#ifdef BOOST_BIN
			OnDestructor( "Rumble" );
#endif
		}


		Rumble();
		boost::shared_ptr<Rumble> Rumble_Construct();
	
		virtual void ReleaseBody();

		virtual void MyPhsxStep();

	};

}


#endif	//#ifndef RUMBLE
