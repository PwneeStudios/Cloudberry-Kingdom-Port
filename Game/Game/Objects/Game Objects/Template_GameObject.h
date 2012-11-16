#ifndef TEMPLATE_GAMEOBJECT
#define TEMPLATE_GAMEOBJECT

#include "GameObject.h"

namespace CloudberryKingdom
{
	class Template_GameObject : public GameObject
	{
	public:
		Template_GameObject();

		virtual void Init();

	protected:
		virtual void MyDraw();

		virtual void MyPhsxStep();
	};
}


#endif	//#ifndef TEMPLATE_GAMEOBJECT
