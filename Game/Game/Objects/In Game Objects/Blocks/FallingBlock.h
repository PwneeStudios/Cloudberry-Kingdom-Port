#ifndef FALLINGBLOCK
#define FALLINGBLOCK

#include <global_header.h>

namespace CloudberryKingdom
{
	struct FallingBlock : public BlockBase
	{
	
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
