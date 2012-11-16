#include <global_header.h>

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;


namespace CloudberryKingdom
{

	void MovingLine::SetCurrent( Vector2 _p1, Vector2 _p2 )
	{
		Current.p1 = _p1;
		Current.p2 = _p2;

		Invalidated = true;
	}

	void MovingLine::SetTarget( Vector2 _p1, Vector2 _p2 )
	{
		Target.p1 = _p1;
		Target.p2 = _p2;

		Invalidated = true;
	}

	void MovingLine::SwapToCurrent()
	{
		Current = Target;

		Invalidated = true;
	}

	void MovingLine::CalcBounds()
	{
		// Expensive
		//TR = Vector2.Max(Vector2.Max(Current.p1, Current.p2), Vector2.Max(Target.p1, Target.p2));
		//BL = Vector2.Min(Vector2.Min(Current.p1, Current.p2), Vector2.Min(Target.p1, Target.p2));

		// Cheaper
		//TR = Vector2.Max(Target.p1, Target.p2);
		//BL = Vector2.Min(Target.p1, Target.p2);

		// Cheapest
		CoreMath::MaxAndMin( Target.p1, Target.p2, TR, BL );
	}

	void MovingLine::Validate()
	{
		if ( Invalidated )
		{
			CalcBounds();

			Invalidated = false;
		}
	}
}
