#ifndef TEMPLATE_GAMEOBJECT
#define TEMPLATE_GAMEOBJECT

#include <small_header.h>

#include "Game/Objects/Game Objects/GameObject.h"
//#include "Game/Objects/In Game Objects/Grab/MakeData.h"
//#include "Game/Level/Level.h"


namespace CloudberryKingdom
{

	struct Template_GameObject : public GameObject
	{
	
		virtual ~Template_GameObject()
		{
#ifdef BOOST_BIN
			OnDestructor( "Template_GameObject" );
#endif
		}


		Template_GameObject();

		virtual void Init();

	
		virtual void MyDraw();

		virtual void MyPhsxStep();

	};

}


#endif	//#ifndef TEMPLATE_GAMEOBJECT
