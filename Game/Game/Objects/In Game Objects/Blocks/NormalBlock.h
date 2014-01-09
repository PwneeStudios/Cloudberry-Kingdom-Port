#ifndef NORMALBLOCK
#define NORMALBLOCK

#include <small_header.h>

//#include "Core/Graphics/Draw/Quads/PieceQuad.h"
//#include "Game/Collision Detection/AABox.h"
//#include "Game/Collision Detection/Phsx.h"
//#include "Game/Objects/ObjectBase.h"
//#include "Game/Tilesets/TileSet.h"
#include "Game/Objects/In Game Objects/Blocks/Block.h"
//#include "Game/Objects/Bob/Bob.h"
//#include "Game/Objects/In Game Objects/Blocks/NormalBlockDraw.h"
//#include "Game/Tools/Recycler.h"
//#include "Game/Tools/Tools.h"
//#include "Game/Tilesets/TileSetInfo.h"


namespace CloudberryKingdom
{
	
	struct NormalBlock : public BlockBase
	{

		virtual ~NormalBlock()
		{
#ifdef BOOST_BIN
			OnDestructor( "NormalBlock" );
#endif
		}


		// Members
		
		bool Invert;
		boost::shared_ptr<BlockBase> HoldBlock;
		bool Moved;
		static float TopOnlyHeight;


		// Methods

		void BasicConstruction( bool BoxesOnly );

		virtual void Release();

		virtual void MakeNew();

		NormalBlock( bool BoxesOnly );

	
		boost::shared_ptr<PieceQuad> GetPieceTemplate();

		boost::shared_ptr<PieceQuad> GetPieceTemplate( float width );

	
		virtual void ResetPieces();

		void Init( Vector2 center, Vector2 size, const boost::shared_ptr<TileSet> &tile );

		void CheckHeight();

		void MakeTopOnly();

		virtual void Move( Vector2 shift );

		virtual void Reset( bool BoxesOnly );

		virtual void PhsxStep();

		virtual void PhsxStep2();


		void Update();

		void MoveTo( Vector2 Pos );

		virtual void Extend( Side side, float pos );

		virtual void Draw();

		virtual void Clone( const boost::shared_ptr<ObjectBase> &A );

		virtual void Write( const boost::shared_ptr<BinaryWriter> &writer );
		virtual void Read( const boost::shared_ptr<BinaryReader> &reader );

		virtual bool PreDecision( const boost::shared_ptr<Bob> &bob );

		virtual bool PostCollidePreDecision( const boost::shared_ptr<Bob> &bob );

		virtual void PostCollideDecision( const boost::shared_ptr<Bob> &bob, ColType &Col, bool &Overlap, bool &Delete );

		static void Block_PostCollideDecision( const boost::shared_ptr<BlockBase> &block, const boost::shared_ptr<Bob> &bob, ColType &Col, bool &Overlap, bool &Delete );

		virtual void PostInteractWith( const boost::shared_ptr<Bob> &bob, ColType &Col, bool &Overlap );

		virtual void PostKeep( const boost::shared_ptr<Bob> &bob, ColType &Col, bool &Overlap );

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef NORMALBLOCK
