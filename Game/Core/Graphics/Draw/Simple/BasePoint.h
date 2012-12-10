#ifndef BASEPOINT
#define BASEPOINT

namespace CloudberryKingdom
{
	struct BasePoint
	{
	
		Vector2 Origin, e1, e2;

		BasePoint();
		BasePoint( float e1x, float e1y, float e2x, float e2y, float ox, float oy );

		void Init();

		Vector2 GetScale();

		void SetScale( Vector2 scale );
	};
}


#endif	//#ifndef BASEPOINT
