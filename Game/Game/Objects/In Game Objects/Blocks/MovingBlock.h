#ifndef MOVINGBLOCK
#define MOVINGBLOCK

#define _USE_MATH_DEFINES
#include <small_header.h>

//#include "Core/Graphics/Draw/Quads/PieceQuad.h"
//#include "Core/Tools/CoreMath.h"
//#include "Game/Collision Detection/AABox.h"
//#include "Game/Objects/ObjectBase.h"
#include "Game/Tilesets/TileSet.h"
#include "Game/Objects/In Game Objects/Blocks/Block.h"
#include "Game/Objects/IBounded.h"
//#include "Game/Objects/In Game Objects/Blocks/NormalBlockDraw.h"
//#include "Game/Objects/In Game Objects/Grab/MakeData.h"
//#include "Game/Level/Level.h"
//#include "Game/Tilesets/BlockGroup.h"
//#include "Game/Tools/Recycler.h"
//#include "Game/Tools/Tools.h"
//#include "Game/Tilesets/TileSetInfo.h"


namespace CloudberryKingdom
{
	struct BlockGroup;
}

namespace CloudberryKingdom
{
	struct Level;
}

namespace CloudberryKingdom
{
	struct ObjectBase;
}




namespace CloudberryKingdom
{
	
	struct MovingBlock : public BlockBase, public IBound
	{

		virtual ~MovingBlock()
		{
#ifdef BOOST_BIN
			OnDestructor( "MovingBlock" );
#endif
		}

	
		struct MovingBlockTileInfo : public TileInfoBase
		{
		
			boost::shared_ptr<BlockGroup> Group;

			MovingBlockTileInfo();

		
			void InitializeInstanceFields();
		};

	
		MovingBlockMoveType MoveType;
		int Period, Offset;
		Vector2 Displacement;

		virtual void MakeNew();

		MovingBlock( bool BoxesOnly );

		Vector2 TR_Bound();

		Vector2 BL_Bound();

		virtual void ResetPieces();

		void Init( Vector2 center, Vector2 size, const boost::shared_ptr<Level> &level );

		void MoveToBounded( Vector2 shift );

		virtual void Move( Vector2 shift );

		virtual void Reset( bool BoxesOnly );

	
		Vector2 CalcPosition( float t );

	
		virtual void PhsxStep();

		virtual void Draw();

		virtual void Extend( Side side, float pos );

		virtual void Clone( const boost::shared_ptr<ObjectBase> &A );
	};
}


#endif	//#ifndef MOVINGBLOCK
