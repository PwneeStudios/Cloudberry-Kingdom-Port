#ifndef _LINEDEATH
#define _LINEDEATH

#include <global_header.h>

namespace CloudberryKingdom
{
	class Bob;
}




namespace CloudberryKingdom
{
	class _LineDeath : public _Death
	{
	protected:
		MovingLine MyLine;
	public:
		Vector2 p1, p2;

		_LineDeath();
		_LineDeath( bool BoxesOnly );

		virtual void Construct( bool BoxesOnly );

		virtual void Interact( const std::shared_ptr<Bob> &bob );

	protected:
		virtual void DrawBoxes();

	public:
		virtual void Move( Vector2 shift );

		virtual void PhsxStep2();
	};
}


#endif	//#ifndef _LINEDEATH
