#ifndef LINE
#define LINE
namespace CloudberryKingdom
{
	class Line
	{
	public:
		Vector2 p1, p2;
	};
	class MovingLine
	{
	public:
		Line Current, Target;
		Vector2 TR, BL;
		bool Invalidated;

		bool SkipOverlap, SkipEdge;

		void SetCurrent( Vector2 _p1, Vector2 _p2 );

		void SetTarget( Vector2 _p1, Vector2 _p2 );

		void SwapToCurrent();

		void CalcBounds();

		void Validate();
	};
}


#endif	//#ifndef LINE
