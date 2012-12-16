#ifndef _CIRCLEDEATH
#define _CIRCLEDEATH

#include <global_header.h>

namespace CloudberryKingdom
{
	struct _CircleDeath : public _Death
	{
	
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
