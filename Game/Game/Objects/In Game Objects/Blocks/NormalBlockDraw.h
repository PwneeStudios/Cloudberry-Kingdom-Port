#ifndef NORMALBLOCKDRAW
#define NORMALBLOCKDRAW

namespace CloudberryKingdom
{
	class NormalBlockDraw
	{
	public:
		bool Shadow;
		Vector2 ShadowOffset;
		Color ShadowColor;

		Color Tint;

		std::shared_ptr<PieceQuad> MyPieces, MyTemplate;
	private:
		std::shared_ptr<BlockBase> MyBlock;

	public:
		NormalBlockDraw();

		void MakeNew();

		void Clone( const std::shared_ptr<NormalBlockDraw> &DrawA );

		void SetTint( Vector4 v );

		void SetTint( Color Tint );

		void Release();

		static Vector2 ModCeilingSize;
		void Init( const std::shared_ptr<BlockBase> &block );
		void Init( const std::shared_ptr<BlockBase> &block, std::shared_ptr<PieceQuad> template_Renamed, bool Invert );

		void Update();

		void Draw();

	private:
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef NORMALBLOCKDRAW
