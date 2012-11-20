#ifndef BOUNCYBLOCK
#define BOUNCYBLOCK

#include <global_header.h>

namespace CloudberryKingdom
{
	class BlockGroup;
}

namespace CloudberryKingdom
{
	class EzSound;
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
	class BouncyBlock : public BlockBase
	{
	public:
		class BouncyBlockTileInfo : public TileInfoBase
		{
		public:
			std::shared_ptr<BlockGroup> Group;
			std::shared_ptr<EzSound> BounceSound;

		private:
			void InitializeInstanceFields();

public:
			BouncyBlockTileInfo()
			{
				InitializeInstanceFields();
			}
		};

	private:
		BouncyBlockState State;
	public:
		Vector2 Offset, SizeOffset;
		float speed;

	private:
		int TouchedCountdown;

	public:
		virtual void MakeNew();

		void SetState( BouncyBlockState NewState );
		void SetState( BouncyBlockState NewState, bool ForceSet );

		BouncyBlock( bool BoxesOnly );

		void Init( Vector2 center, Vector2 size, float speed, const std::shared_ptr<Level> &level );

		float SideDampening;
	private:
		void Snap( const std::shared_ptr<Bob> &bob );

	public:
		virtual void SideHit( const std::shared_ptr<Bob> &bob );

		virtual void LandedOn( const std::shared_ptr<Bob> &bob );

		virtual void HitHeadOn( const std::shared_ptr<Bob> &bob );

		virtual void Reset( bool BoxesOnly );

		virtual void PhsxStep();

		virtual void PhsxStep2();

		void Update();

		virtual void Extend( Side side, float pos );

		virtual void Move( Vector2 shift );

		virtual void Draw();

		virtual void Clone( const std::shared_ptr<ObjectBase> &A );

	private:
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef BOUNCYBLOCK
