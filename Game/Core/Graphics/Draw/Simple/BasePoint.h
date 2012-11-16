#ifndef BASEPOINT
#define BASEPOINT

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;

namespace CloudberryKingdom
{
	class BasePoint
	{
	public:
		Vector2 Origin, e1, e2;

		BasePoint( float e1x, float e1y, float e2x, float e2y, float ox, float oy );

		void Init();

		Vector2 GetScale();

		void SetScale( Vector2 scale );
	};
}


#endif	//#ifndef BASEPOINT
