#ifndef LAVA_CASTLE
#define LAVA_CASTLE

#include <global_header.h>

namespace CloudberryKingdom
{
	class ObjectBase;
}


//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;



namespace CloudberryKingdom
{
	class LavaBlock_Castle : public LavaBlock
	{
	public:
		LavaBlock_Castle( bool BoxesOnly );

		virtual void MakeNew();

	protected:
		virtual void SetQuad( Vector2 center, Vector2 size );

	public:
		virtual void PhsxStep();

		virtual void Draw();

		virtual void Clone( const std::shared_ptr<ObjectBase> &A );
	};
}


#endif	//#ifndef LAVA_CASTLE
