#ifndef _LINEDEATH
#define _LINEDEATH

#include "_Death.h"
#include "../Game/Collision Detection/Line.h"

namespace CloudberryKingdom
{
	class Bob;
}


//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;
using namespace Microsoft::Xna::Framework;

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;

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
