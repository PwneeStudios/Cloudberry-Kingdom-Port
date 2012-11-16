#ifndef _CIRCLEDEATH
#define _CIRCLEDEATH

#include <global_header.h>

namespace CloudberryKingdom
{
	class CircleBox;
}

namespace CloudberryKingdom
{
	class Bob;
}

namespace CloudberryKingdom
{
	class ObjectBase;
}


//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;


//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;

namespace CloudberryKingdom
{
	class _CircleDeath : public _Death
	{
	protected:
		std::shared_ptr<CircleBox> Circle;
		float Radius;

	public:
		virtual void MakeNew();

		_CircleDeath();
		_CircleDeath( bool BoxesOnly );

		virtual void Construct( bool BoxesOnly );

		virtual void Scale( float scale );

	protected:
		virtual void ActivePhsxStep();

		virtual void DrawBoxes();

	public:
		virtual void Move( Vector2 shift );

		virtual void Interact( const std::shared_ptr<Bob> &bob );

		virtual void Clone( const std::shared_ptr<ObjectBase> &A );
	};
}


#endif	//#ifndef _CIRCLEDEATH
