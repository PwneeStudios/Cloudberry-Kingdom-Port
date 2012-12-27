#ifndef PENDULUM
#define PENDULUM

#define _USE_MATH_DEFINES
#include <global_header.h>

namespace CloudberryKingdom
{
	struct Pendulum : public BlockBase, public IBound
	{
	
		struct PendulumTileInfo : public TileInfoBase
		{
		
			boost::shared_ptr<BlockGroup> Group;

		
			void InitializeInstanceFields();


			PendulumTileInfo()
			{
				InitializeInstanceFields();
			}
		};

	
		PendulumMoveType MoveType;

		float Angle, MaxAngle, Length;
		int Period, Offset;
		Vector2 PivotPoint;

		virtual void LandedOn( const boost::shared_ptr<Bob> &bob );

		virtual void MakeNew();

		Pendulum( bool BoxesOnly );

		Vector2 TR_Bound();

		Vector2 BL_Bound();

		BoxStyle MyBoxStyle;

		void Init( Vector2 center, Vector2 size, const boost::shared_ptr<Level> &level, BoxStyle _MyBoxStyle );

		void MoveToBounded( Vector2 shift );

		void CalculateLength();

		virtual void Move( Vector2 shift );

		virtual void Reset( bool BoxesOnly );

		float AddAngle;
	
		float CorrespondingAngle;
		Vector2 CalcPosition( float t );

	
		float MyTime;
		virtual void PhsxStep();

		virtual void PhsxStep2();

		virtual void Draw();

		virtual void ResetPieces();

		virtual void Extend( Side side, float pos );

		virtual void Clone( const boost::shared_ptr<ObjectBase> &A );

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef PENDULUM
