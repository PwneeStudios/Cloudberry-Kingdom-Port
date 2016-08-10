#ifndef CONVEYOR
#define CONVEYOR

#include <small_header.h>

//#include "Core/Graphics/Draw/Quads/QuadClass.h"
//#include "Game/Collision Detection/AABox.h"
//#include "Game/Objects/ObjectBase.h"
#include "Game/Objects/In Game Objects/Blocks/Block.h"
//#include "Game/Tools/Recycler.h"
//#include "Game/Tools/Tools.h"


namespace CloudberryKingdom
{
	struct QuadClass;
}

namespace CloudberryKingdom
{
	struct ObjectBase;
}


namespace CloudberryKingdom
{
	
	struct ConveyorBlock : public BlockBase
	{
	
		virtual ~ConveyorBlock()
		{
#ifdef BOOST_BIN
			OnDestructor( "ConveyorBlock" );
#endif
		}


		boost::shared_ptr<QuadClass> MyQuad, LeftEnd, RightEnd;

		virtual void MakeNew();

		virtual void Release();

		ConveyorBlock( bool BoxesOnly );

		float Speed;
	
		float u_offset;
		Vector2 texture_size;
		void SetUV();

		Vector2 Size;
	
		void Init( Vector2 center, Vector2 size );

		virtual void Reset( bool BoxesOnly );

		virtual void PhsxStep();

		virtual void PhsxStep2();

		void Update();

		virtual void Extend( Side side, float pos );

		virtual void Move( Vector2 shift );

		virtual void Draw();

		virtual void Clone( const boost::shared_ptr<ObjectBase> &A );

	
		void InitializeInstanceFields();
	};

}


#endif	//#ifndef CONVEYOR
