#ifndef CHEER
#define CHEER

#include <global_header.h>

namespace CloudberryKingdom
{

	struct Cheer : public GameObject
	{
	
		std::shared_ptr<DrawPile> MyPile;

	
		std::shared_ptr<QuadClass> Berry;
		Cheer();

		virtual void OnAdd();

	
		virtual void MyDraw();

		virtual void MyPhsxStep();

	
		void InitializeInstanceFields();
	};

}


#endif	//#ifndef CHEER
