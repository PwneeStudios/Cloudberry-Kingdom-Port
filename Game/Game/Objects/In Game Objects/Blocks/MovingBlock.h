#ifndef MOVINGBLOCK
#define MOVINGBLOCK

#define _USE_MATH_DEFINES
#include <global_header.h>

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

		virtual ~MovingBlock() { }
	
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
