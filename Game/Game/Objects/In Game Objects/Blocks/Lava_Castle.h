#ifndef LAVA_CASTLE
#define LAVA_CASTLE

#include <small_header.h>

//#include "Game/Objects/ObjectBase.h"
#include "Game/Objects/In Game Objects/Blocks/Lava.h"
//#include "Game/Tools/Tools.h"


namespace CloudberryKingdom
{
	struct ObjectBase;
}


namespace CloudberryKingdom
{
	struct LavaBlock_Castle : public LavaBlock
	{
	
		virtual ~LavaBlock_Castle()
		{
#ifdef BOOST_BIN
			OnDestructor( "LavaBlock_Castle" );
#endif
		}


		LavaBlock_Castle( bool BoxesOnly );

		virtual void MakeNew();

	
		virtual void SetQuad( Vector2 center, Vector2 size );

	
		virtual void PhsxStep();

		virtual void Draw();

		virtual void Clone( const boost::shared_ptr<ObjectBase> &A );
	};
}


#endif	//#ifndef LAVA_CASTLE
