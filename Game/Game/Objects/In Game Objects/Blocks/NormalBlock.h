#ifndef NORMALBLOCK
#define NORMALBLOCK

#include <global_header.h>

namespace CloudberryKingdom
{
	struct NormalBlock : public BlockBase
	{

	
		bool Invert;

		std::shared_ptr<BlockBase> HoldBlock;

		bool Moved;

		void BasicConstruction( bool BoxesOnly );

		virtual void Release();

		virtual void MakeNew();

		NormalBlock( bool BoxesOnly );

	
		std::shared_ptr<PieceQuad> GetPieceTemplate();

		std::shared_ptr<PieceQuad> GetPieceTemplate( float width );

	
		virtual void ResetPieces();

		void Init( Vector2 center, Vector2 size, const std::shared_ptr<TileSet> &tile );

	
		static float TopOnlyHeight;

	
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

		virtual void Clone( const std::shared_ptr<ObjectBase> &A );

		virtual void Write( const std::shared_ptr<BinaryWriter> &writer );
		virtual void Read( const std::shared_ptr<BinaryReader> &reader );

		virtual bool PreDecision( const std::shared_ptr<Bob> &bob );

		virtual bool PostCollidePreDecision( const std::shared_ptr<Bob> &bob );

		virtual void PostCollideDecision( const std::shared_ptr<Bob> &bob, ColType &Col, bool &Overlap, bool &Delete );

		static void Block_PostCollideDecision( const std::shared_ptr<BlockBase> &block, const std::shared_ptr<Bob> &bob, ColType &Col, bool &Overlap, bool &Delete );

		virtual void PostInteractWith( const std::shared_ptr<Bob> &bob, ColType &Col, bool &Overlap );

		virtual void PostKeep( const std::shared_ptr<Bob> &bob, ColType &Col, bool &Overlap );

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef NORMALBLOCK
