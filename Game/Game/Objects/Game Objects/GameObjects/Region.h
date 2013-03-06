#ifndef REGION
#define REGION

#include <global_header.h>

namespace CloudberryKingdom
{

	struct Region : public GUI_Panel
	{
	
		virtual ~Region()
		{
#ifdef BOOST_BIN
			OnDestructor( "Region" );
#endif
		}


		Region( const Vector2 &pos, const Vector2 &size );
		boost::shared_ptr<Region> Region_Construct( const Vector2 &pos, const Vector2 &size );
	
		boost::shared_ptr<AABox> Box;
	
		void Init( const Vector2 &pos, const Vector2 &size );

		boost::shared_ptr<Door> AttachedDoor;
	
		virtual void MyPhsxStep();
	
		virtual bool OnScreen();
	
		virtual void MyDraw();

	};
}


#endif	//#ifndef REGION
