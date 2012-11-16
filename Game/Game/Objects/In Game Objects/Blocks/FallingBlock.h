#ifndef FALLINGBLOCK
#define FALLINGBLOCK

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
	class Bob;
}

namespace CloudberryKingdom
{
	class ObjectBase;
}


namespace CloudberryKingdom
{
	enum FallingBlockState
	{
		FallingBlockState_REGULAR,
		FallingBlockState_TOUCHED,
		FallingBlockState_FALLING,
		FallingBlockState_ANGRY
	};
	class FallingBlock : public BlockBase
	{
	public:
		class FallingBlockTileInfo : public TileInfoBase
		{
		public:
			std::shared_ptr<BlockGroup> Group;

			FallingBlockTileInfo();

		private:
			void InitializeInstanceFields();
		};

	public:
		bool TouchedOnce, HitGround;

		bool Thwomp;
		Vector2 AngryAccel;
		float AngryMaxSpeed;

		int StartLife, Life;
		//public int StartLife { get { return _StartLife; } set { _StartLife = value; if (value > 20) Console.WriteLine("!");  } }

	private:
		FallingBlockState State;
		bool EmittedExplosion;
	public:
		Vector2 Offset;
	private:
		int ResetTimer;
	public:
		static int ResetTimerLength;

		virtual void MakeNew();

		void SetState( FallingBlockState NewState );
		void SetState( FallingBlockState NewState, bool ForceSet );

		FallingBlock( bool BoxesOnly );

		void Init( Vector2 center, Vector2 size, int life, const std::shared_ptr<Level> &level );

		virtual void HitHeadOn( const std::shared_ptr<Bob> &bob );

		virtual void LandedOn( const std::shared_ptr<Bob> &bob );

		virtual void Reset( bool BoxesOnly );

		virtual void PhsxStep();

		virtual void Extend( Side side, float pos );

		virtual void Move( Vector2 shift );
		virtual void Draw();

		virtual void Clone( const std::shared_ptr<ObjectBase> &A );
	};
}


#endif	//#ifndef FALLINGBLOCK
