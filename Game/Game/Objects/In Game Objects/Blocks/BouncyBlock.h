#ifndef BOUNCYBLOCK
#define BOUNCYBLOCK

#include <small_header.h>

//#include "Core/Graphics/Draw/Quads/PieceQuad.h"
//#include "Core/Sound/EzSound.h"
//#include "Game/Collision Detection/AABox.h"
//#include "Game/Objects/ObjectBase.h"
#include "Game/Tilesets/TileSet.h"
#include "Game/Objects/In Game Objects/Blocks/Block.h"
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

	struct BouncyBlock : public BlockBase
	{

		virtual ~BouncyBlock()
		{
#ifdef BOOST_BIN
			OnDestructor( "BouncyBlock" );
#endif
		}

	
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
