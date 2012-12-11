#ifndef LAVA_CASTLE
#define LAVA_CASTLE

#include <global_header.h>

namespace CloudberryKingdom
{
	struct ObjectBase;
}


namespace CloudberryKingdom
{
	struct LavaBlock_Castle : public LavaBlock
	{
	
		LavaBlock_Castle( bool BoxesOnly );

		virtual void MakeNew();

	
		virtual void SetQuad( Vector2 center, Vector2 size );

	
		virtual void PhsxStep();

		virtual void Draw();

		virtual void Clone( const std::shared_ptr<ObjectBase> &A );
	};
}


#endif	//#ifndef LAVA_CASTLE
