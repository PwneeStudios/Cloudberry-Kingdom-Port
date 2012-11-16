#ifndef CHEER
#define CHEER

#include "../Game/Objects/Game Objects/GameObject.h"
#include <tchar.h>

namespace CloudberryKingdom
{
	class DrawPile;
}

namespace CloudberryKingdom
{
	class QuadClass;
}


using namespace Microsoft::Xna::Framework;

namespace CloudberryKingdom
{
	class Cheer : public GameObject
	{
	private:
		std::shared_ptr<DrawPile> MyPile;

	public:
		std::shared_ptr<QuadClass> Berry;
		Cheer();

		virtual void OnAdd();

	protected:
		virtual void MyDraw();

		virtual void MyPhsxStep();

	private:
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef CHEER
