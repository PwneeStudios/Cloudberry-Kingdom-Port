#ifndef MOVINGBLOCK
#define MOVINGBLOCK

#define _USE_MATH_DEFINES
#include <global_header.h>

namespace CloudberryKingdom
{
	class BlockGroup;
}

namespace CloudberryKingdom
{
	class Level;
}

namespace CloudberryKingdom
{
	class ObjectBase;
}




namespace CloudberryKingdom
{
	enum MovingBlockMoveType
	{
		MovingBlockMoveType_LINE,
		MovingBlockMoveType_CIRCLE,
		MovingBlockMoveType_FIGURE_EIGHT
	};
	class MovingBlock : public BlockBase, public IBound
	{
	public:
		class MovingBlockTileInfo : public TileInfoBase
		{
		public:
			std::shared_ptr<BlockGroup> Group;

			MovingBlockTileInfo();

		private:
			void InitializeInstanceFields();
		};

	public:
		MovingBlockMoveType MoveType;
		int Period, Offset;
		Vector2 Displacement;

		virtual void MakeNew();

		MovingBlock( bool BoxesOnly );

		Vector2 TR_Bound();

		Vector2 BL_Bound();

		virtual void ResetPieces();

		void Init( Vector2 center, Vector2 size, const std::shared_ptr<Level> &level );

		void MoveToBounded( Vector2 shift );

		virtual void Move( Vector2 shift );

		virtual void Reset( bool BoxesOnly );

	private:
		Vector2 CalcPosition( float t );

	public:
		virtual void PhsxStep();

		virtual void Draw();

		virtual void Extend( Side side, float pos );

		virtual void Clone( const std::shared_ptr<ObjectBase> &A );
	};
}


#endif	//#ifndef MOVINGBLOCK
