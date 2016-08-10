#ifndef _CIRCLEDEATH
#define _CIRCLEDEATH

#include <small_header.h>

//#include "Game/Collision Detection/Circle.h"
//#include "Game/Objects/ObjectBase.h"
//#include "Game/Objects/Bob/Bob.h"
#include "Game/Objects/In Game Objects/BaseClasses/_Death.h"


namespace CloudberryKingdom
{

	struct _CircleDeath : public _Death
	{

		virtual ~_CircleDeath()
		{
#ifdef BOOST_BIN
			OnDestructor( "_CircleDeath" );
#endif
		}


		boost::shared_ptr<CircleBox> Circle;
		float Radius;

	
		virtual void MakeNew();

		_CircleDeath();
		_CircleDeath( bool BoxesOnly );

		virtual void Construct( bool BoxesOnly );

		virtual void Scale( float scale );

	
		virtual void ActivePhsxStep();

		virtual void DrawBoxes();

	
		virtual void Move( Vector2 shift );

		virtual void Interact( const boost::shared_ptr<Bob> &bob );

		virtual void Clone( const boost::shared_ptr<ObjectBase> &A );
	};

}


#endif	//#ifndef _CIRCLEDEATH
