#ifndef PENDULUM
#define PENDULUM

#define _USE_MATH_DEFINES
#include <global_header.h>

namespace CloudberryKingdom
{
	class BlockGroup;
}

namespace CloudberryKingdom
{
	class Bob;
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
	class Pendulum : public BlockBase, public IBound
	{
	public:
		class PendulumTileInfo : public TileInfoBase
		{
		public:
			std::shared_ptr<BlockGroup> Group;

		private:
			void InitializeInstanceFields();

public:
			PendulumTileInfo()
			{
				InitializeInstanceFields();
			}
		};

	public:
		PendulumMoveType MoveType;

		float Angle, MaxAngle, Length;
		int Period, Offset;
		Vector2 PivotPoint;

		virtual void LandedOn( const std::shared_ptr<Bob> &bob );

		virtual void MakeNew();

		Pendulum( bool BoxesOnly );

		Vector2 TR_Bound();

		Vector2 BL_Bound();

		void Init( Vector2 center, Vector2 size, const std::shared_ptr<Level> &level );

		void MoveToBounded( Vector2 shift );

		void CalculateLength();

		virtual void Move( Vector2 shift );

		virtual void Reset( bool BoxesOnly );

		float AddAngle;
	private:
		float CorrespondingAngle;
		Vector2 CalcPosition( float t );

	public:
		float MyTime;
		virtual void PhsxStep();

		virtual void PhsxStep2();

		virtual void Draw();

		virtual void ResetPieces();

		virtual void Extend( Side side, float pos );

		virtual void Clone( const std::shared_ptr<ObjectBase> &A );

	private:
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef PENDULUM
