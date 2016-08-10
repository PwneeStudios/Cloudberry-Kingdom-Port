#ifndef GUIDE
#define GUIDE

#include <small_header.h>

//#include "Game/Objects/Game Objects/GameObject.h"
#include "Game/Objects/Game Objects/GameObjects/GUI_Panel.h"
//#include "Game/Objects/Bob/Bob.h"
//#include "Game/Objects/In Game Objects/Grab/MakeData.h"
//#include "Game/Level/Level.h"


namespace CloudberryKingdom
{

	struct ShowGuide : public GUI_Panel
	{
	
		virtual ~ShowGuide()
		{
#ifdef BOOST_BIN
			OnDestructor( "ShowGuide" );
#endif
		}


		ShowGuide();
		boost::shared_ptr<ShowGuide> ShowGuide_Construct();

		virtual void ReleaseBody();

		virtual void MyPhsxStep();

	};

}


#endif	//#ifndef GUIDE
