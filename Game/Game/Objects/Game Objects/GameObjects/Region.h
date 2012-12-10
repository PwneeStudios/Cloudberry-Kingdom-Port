#ifndef REGION
#define REGION

#include <global_header.h>

namespace CloudberryKingdom
{
	struct Region : public GUI_Panel
	{
	
		Region( Vector2 pos, Vector2 size );

	
		std::shared_ptr<AABox> Box;
	
		void Init( Vector2 pos, Vector2 size );

		std::shared_ptr<Door> AttachedDoor;
	
		virtual void MyPhsxStep();

	
		virtual bool OnScreen();

	
		virtual void MyDraw();
	};
}


#endif	//#ifndef REGION
