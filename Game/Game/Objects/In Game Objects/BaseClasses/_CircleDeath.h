#ifndef _CIRCLEDEATH
#define _CIRCLEDEATH

#include <global_header.h>

namespace CloudberryKingdom
{
	struct CircleBox;
}

namespace CloudberryKingdom
{
	struct Bob;
}

namespace CloudberryKingdom
{
	struct ObjectBase;
}




namespace CloudberryKingdom
{
	struct _CircleDeath : public _Death
	{
	
		std::shared_ptr<CircleBox> Circle;
		float Radius;

	
		virtual void MakeNew();

		_CircleDeath();
		_CircleDeath( bool BoxesOnly );

		virtual void Construct( bool BoxesOnly );

		virtual void Scale( float scale );

	
		virtual void ActivePhsxStep();

		virtual void DrawBoxes();

	
		virtual void Move( Vector2 shift );

		virtual void Interact( const std::shared_ptr<Bob> &bob );

		virtual void Clone( const std::shared_ptr<ObjectBase> &A );
	};
}


#endif	//#ifndef _CIRCLEDEATH
