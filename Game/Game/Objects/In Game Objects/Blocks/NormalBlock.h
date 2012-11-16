#ifndef NORMALBLOCK
#define NORMALBLOCK

#include <global_header.h>

namespace CloudberryKingdom
{
	class BlockBase;
}

namespace CloudberryKingdom
{
	class PieceQuad;
}

namespace CloudberryKingdom
{
	class TileSet;
}

namespace CloudberryKingdom
{
	class ObjectBase;
}

namespace CloudberryKingdom
{
	class Bob;
}








namespace CloudberryKingdom
{
	class NormalBlock : public BlockBase
	{
	public:
		bool Invert;

		std::shared_ptr<BlockBase> HoldBlock;

		bool Moved;

		void BasicConstruction( bool BoxesOnly );

		virtual void Release();

		virtual void MakeNew();

		NormalBlock( bool BoxesOnly );

	private:
		std::shared_ptr<PieceQuad> GetPieceTemplate();

		std::shared_ptr<PieceQuad> GetPieceTemplate( float width );

	public:
		virtual void ResetPieces();

		void Init( Vector2 center, Vector2 size, const std::shared_ptr<TileSet> &tile );

	private:
		static float TopOnlyHeight;

	public:
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

	private:
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef NORMALBLOCK
