#ifndef BOUNCYBLOCK
#define BOUNCYBLOCK

#include <global_header.h>

namespace CloudberryKingdom
{
	struct BouncyBlock : public BlockBase
	{
	
		struct BouncyBlockTileInfo : public TileInfoBase
		{
		
			std::shared_ptr<BlockGroup> Group;
			std::shared_ptr<EzSound> BounceSound;

		
			void InitializeInstanceFields();


			BouncyBlockTileInfo()
			{
				InitializeInstanceFields();
			}
		};

	
		BouncyBlockState State;
	
		Vector2 Offset, SizeOffset;
		float speed;

	
		int TouchedCountdown;

	
		virtual void MakeNew();

		void SetState( BouncyBlockState NewState );
		void SetState( BouncyBlockState NewState, bool ForceSet );

		BouncyBlock( bool BoxesOnly );

		void Init( Vector2 center, Vector2 size, float speed, const std::shared_ptr<Level> &level );

		float SideDampening;
	
		void Snap( const std::shared_ptr<Bob> &bob );

	
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

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef BOUNCYBLOCK
