#ifndef REGION
#define REGION

#include <global_header.h>

namespace CloudberryKingdom
{
	struct Region : public GUI_Panel
	{
	
		Region( const Vector2 &pos, const Vector2 &size );
		void Region_Construct( const Vector2 &pos, const Vector2 &size );
	
		std::shared_ptr<AABox> Box;
	
		void Init( const Vector2 &pos, const Vector2 &size );

		std::shared_ptr<Door> AttachedDoor;
	
		virtual void MyPhsxStep();

	
		virtual bool OnScreen();

	
		virtual void MyDraw();
	};
}


#endif	//#ifndef REGION
