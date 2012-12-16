#ifndef _LINEDEATH
#define _LINEDEATH

#include <global_header.h>

namespace CloudberryKingdom
{
	struct Bob;
}




namespace CloudberryKingdom
{
	struct _LineDeath : public _Death
	{
	
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
