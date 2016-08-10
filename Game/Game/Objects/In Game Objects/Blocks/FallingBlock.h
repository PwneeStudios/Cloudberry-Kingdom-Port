#ifndef FALLINGBLOCK
#define FALLINGBLOCK

#include <small_header.h>

//#include "Core/Graphics/Draw/Quads/PieceQuad.h"
//#include "Core/Particle Effects/Specific Effects/CloudberryKingdom.ParticleEffects.h"
//#include "Game/Collision Detection/AABox.h"
//#include "Game/Objects/ObjectBase.h"
#include "Game/Tilesets/TileSet.h"
#include "Game/Objects/In Game Objects/Blocks/Block.h"
//#include "Game/Level/Make/PieceSeedData.h"
//#include "Game/Objects/Bob/Bob.h"
//#include "Game/Objects/In Game Objects/Blocks/NormalBlockDraw.h"
//#include "Game/Objects/In Game Objects/Grab/MakeData.h"
//#include "Game/Level/Level.h"
//#include "Game/Tilesets/BlockGroup.h"
//#include "Game/Tools/Recycler.h"
//#include "Game/Tools/Tools.h"
//#include "Game/Tilesets/TileSetInfo.h"


namespace CloudberryKingdom
{
	
	struct FallingBlock : public BlockBase
	{
	
		virtual ~FallingBlock()
		{
#ifdef BOOST_BIN
			OnDestructor( "FallingBlock" );
#endif
		}


		struct FallingBlockTileInfo : public TileInfoBase
		{
		
			boost::shared_ptr<BlockGroup> Group;

			FallingBlockTileInfo();

		
			void InitializeInstanceFields();
		};

	
		bool TouchedOnce, HitGround;

		bool Thwomp;
		Vector2 AngryAccel;
		float AngryMaxSpeed;

		int StartLife, Life;
		//public int StartLife { get { return _StartLife; } set { _StartLife = value; if (value > 20) Console.WriteLine("!");  } }

	
		FallingBlockState State;
		bool EmittedExplosion;
	
		Vector2 Offset;
	
		int ResetTimer;
	
		static int ResetTimerLength;

		virtual void MakeNew();

		void SetState( FallingBlockState NewState );
		void SetState( FallingBlockState NewState, bool ForceSet );

		FallingBlock( bool BoxesOnly );

		void Init( Vector2 center, Vector2 size, int life, const boost::shared_ptr<Level> &level );

		virtual void HitHeadOn( const boost::shared_ptr<Bob> &bob );

		virtual void LandedOn( const boost::shared_ptr<Bob> &bob );

		virtual void Reset( bool BoxesOnly );

		virtual void PhsxStep();

		virtual void Extend( Side side, float pos );

		virtual void Move( Vector2 shift );
		virtual void Draw();

		virtual void Clone( const boost::shared_ptr<ObjectBase> &A );
	};
}


#endif	//#ifndef FALLINGBLOCK
