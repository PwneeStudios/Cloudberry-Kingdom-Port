#ifndef SLOWMO
#define SLOWMO

#include <small_header.h>

//#include "Game/Objects/Game Objects/GameObject.h"
#include "Game/Objects/Game Objects/GameObjects/GUI_Panel.h"
//#include "Game/Objects/In Game Objects/Grab/MakeData.h"
//#include "Game/Level/Level.h"
//#include "Game/Tools/Tools.h"


namespace CloudberryKingdom
{

	struct SlowMo : public GUI_Panel
	{

	
		virtual ~SlowMo()
		{
#ifdef BOOST_BIN
			OnDestructor( "SlowMo" );
#endif
		}

		
		SlowMo();
		boost::shared_ptr<SlowMo> SlowMo_Construct();
	
		virtual void ReleaseBody();

	
		int Speed;

	
		virtual void MyPhsxStep();

	
		void InitializeInstanceFields();

	};

}

#endif	//#ifndef SLOWMO
