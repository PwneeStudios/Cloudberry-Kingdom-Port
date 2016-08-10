#ifndef NORMALBLOCKDRAW
#define NORMALBLOCKDRAW

namespace CloudberryKingdom
{

	struct NormalBlockDraw
	{
	
		bool Shadow;
		Vector2 ShadowOffset;
		Color ShadowColor;

		Color Tint;

		boost::shared_ptr<PieceQuad> MyPieces, MyTemplate;
	
		boost::shared_ptr<BlockBase> MyBlock;

	
		NormalBlockDraw();

		void MakeNew();

		void Clone( const boost::shared_ptr<NormalBlockDraw> &DrawA );

		void SetTint( Vector4 v );

		void SetTint( Color Tint );

		void Release();

		static Vector2 ModCeilingSize;
		void Init( const boost::shared_ptr<BlockBase> &block );
		void Init( const boost::shared_ptr<BlockBase> &block, boost::shared_ptr<PieceQuad> template_Renamed, bool Invert );

		void Update();

		void Draw();

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef NORMALBLOCKDRAW
