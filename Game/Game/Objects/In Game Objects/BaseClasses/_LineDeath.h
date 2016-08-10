#ifndef _LINEDEATH
#define _LINEDEATH

#include <small_header.h>

//#include "Game/Collision Detection/Line.h"
//#include "Game/Collision Detection/Phsx.h"
//#include "Game/Objects/Bob/Bob.h"
#include "Game/Objects/In Game Objects/BaseClasses/_Death.h"
//#include "Game/Tools/Tools.h"
#include "Game/Collision Detection/Line.h"


namespace CloudberryKingdom
{
	struct Bob;
}




namespace CloudberryKingdom
{

	struct _LineDeath : public _Death
	{
	
		virtual ~_LineDeath()
		{
#ifdef BOOST_BIN
			OnDestructor( "_LineDeath" );
#endif
		}


		MovingLine MyLine;
	
		Vector2 p1, p2;

		_LineDeath();
		_LineDeath( bool BoxesOnly );

		virtual void Construct( bool BoxesOnly );

		virtual void Interact( const boost::shared_ptr<Bob> &bob );

	
		virtual void DrawBoxes();

	
		virtual void Move( Vector2 shift );

		virtual void PhsxStep2();
	};
}


#endif	//#ifndef _LINEDEATH
