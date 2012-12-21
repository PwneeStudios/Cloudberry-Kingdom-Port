#ifndef LINE
#define LINE

namespace CloudberryKingdom
{

	struct Line
	{

		Vector2 p1, p2;

		Line();

	};

	struct MovingLine
	{
	
		Line Current, Target;
		Vector2 TR, BL;

		bool Invalidated;
		bool SkipOverlap, SkipEdge;

		MovingLine();

		void SetCurrent( Vector2 _p1, Vector2 _p2 );

		void SetTarget( Vector2 _p1, Vector2 _p2 );

		void SwapToCurrent();

		void CalcBounds();

		void Validate();

	};

}


#endif	//#ifndef LINE
