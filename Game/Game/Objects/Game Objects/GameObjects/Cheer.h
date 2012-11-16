#ifndef CHEER
#define CHEER

#include <global_header.h>

namespace CloudberryKingdom
{
	class DrawPile;
}

namespace CloudberryKingdom
{
	class QuadClass;
}




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
