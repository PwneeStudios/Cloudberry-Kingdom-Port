#ifndef BOUNCYBLOCK
#define BOUNCYBLOCK

#include <global_header.h>

namespace CloudberryKingdom
{

	struct BouncyBlock : public BlockBase
	{

		virtual ~BouncyBlock() { }
	
		struct BouncyBlockTileInfo : public TileInfoBase
		{
		
			boost::shared_ptr<BlockGroup> Group;
			boost::shared_ptr<EzSound> BounceSound;

		
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

		void Init( Vector2 center, Vector2 size, float speed, const boost::shared_ptr<Level> &level );

		float SideDampening;
	
		void Snap( const boost::shared_ptr<Bob> &bob );

	
		virtual void SideHit( const boost::shared_ptr<Bob> &bob );

		virtual void LandedOn( const boost::shared_ptr<Bob> &bob );

		virtual void HitHeadOn( const boost::shared_ptr<Bob> &bob );

		virtual void Reset( bool BoxesOnly );

		virtual void PhsxStep();

		virtual void PhsxStep2();

		void Update();

		virtual void Extend( Side side, float pos );

		virtual void Move( Vector2 shift );

		virtual void Draw();

		virtual void Clone( const boost::shared_ptr<ObjectBase> &A );

	
		void InitializeInstanceFields();
	};

}


#endif	//#ifndef BOUNCYBLOCK
