#ifndef PENDULUM
#define PENDULUM

#define _USE_MATH_DEFINES
#include <small_header.h>

//#include "Core/Graphics/Draw/Quads/PieceQuad.h"
//#include "Core/Tools/CoreMath.h"
//#include "Game/Collision Detection/AABox.h"
//#include "Game/Objects/ObjectBase.h"
#include "Game/Tilesets/TileSet.h"
#include "Game/Objects/In Game Objects/Blocks/Block.h"
#include "Game/Objects/IBounded.h"
//#include "Game/Objects/Bob/Bob.h"
//#include "Game/Objects/In Game Objects/Blocks/NormalBlockDraw.h"
//#include "Game/Objects/In Game Objects/Grab/MakeData.h"
//#include "Game/Level/Level.h"
//#include "Game/Objects/In Game Objects/Obstacles/BlockEmitter__Auto.h"
//#include "Game/Tilesets/BlockGroup.h"
//#include "Game/Tools/Recycler.h"
//#include "Game/Tools/Tools.h"
//#include "Game/Tilesets/TileSetInfo.h"


namespace CloudberryKingdom
{

	struct Pendulum : public BlockBase, public IBound
	{

		virtual ~Pendulum()
		{
#ifdef BOOST_BIN
			OnDestructor( "Pendulum" );
#endif
		}

	
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
