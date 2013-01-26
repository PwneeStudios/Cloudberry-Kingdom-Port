#ifndef TEMPLATE_GAMEOBJECT
#define TEMPLATE_GAMEOBJECT

#include <global_header.h>

namespace CloudberryKingdom
{

	struct Template_GameObject : public GameObject
	{
	
		virtual ~Template_GameObject() { }

		Template_GameObject();

		virtual void Init();

	
		virtual void MyDraw();

		virtual void MyPhsxStep();

	};

}


#endif	//#ifndef TEMPLATE_GAMEOBJECT
