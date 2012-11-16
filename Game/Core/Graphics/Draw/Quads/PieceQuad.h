#ifndef PIECEQUAD
#define PIECEQUAD

#include <global_header.h>

namespace CloudberryKingdom
{
	class PieceQuad;
}

namespace CloudberryKingdom
{
	class BlockGroup;
}

namespace CloudberryKingdom
{
	class EzEffect;
}

namespace CloudberryKingdom
{
	class EzTexture;
}


namespace CloudberryKingdom
{
	class PieceQuadData
	{
	public:
		Vector2 Center_BL_Shift;
		Vector2 Center_TR_Shift;

		float LeftWidth, RightWidth, TopWidth, BottomWidth;
		float RepeatWidth, RepeatHeight;

		Vector2 UV_Multiples;

		/// <summary>
		/// Make quad flush against bottom, instead of top.
		/// </summary>
		bool BottomFlush;

		/// <summary>
		/// Make center quad's texture upside down.
		/// </summary>
		bool UpsideDown;

		/// <summary>
		/// Make center quad's texture mirrored horizontally.
		/// </summary>
		bool Mirror;
	};

	class PieceQuadGroup : public std::vector<PieceQuad*>
	{
	public:
		PieceQuadGroup();

	private:
		static std::vector<std::wstring> suffixes;
	public:
		void InitPillars( const std::wstring &root );
		void InitPillars( const std::wstring &root, std::vector<std::wstring&> suffixes );

//ORIGINAL LINE: public void SetCutoffs(params float[] cutoffs)
//C# TO C++ CONVERTER TODO TASK: Use 'va_start', 'va_arg', and 'va_end' to access the parameter array within this method:
		void SetCutoffs( ... );

		std::shared_ptr<PieceQuad> Get( float width );
	};

	class PieceQuad
	{
	public:
		enum Orientation
		{
			Orientation_NORMAL,
			Orientation_UPSIDE_DOWN,
			Orientation_ROTATE_RIGHT,
			Orientation_ROTATE_LEFT
		};
		// Some pillar info
	public:
		float BoxHeight;

		void CalcTexture( int anim, float t );

		float Group_CutoffWidth;

		/// <summary>
		/// Layer of the quad, used in DrawPiles
		/// </summary>
		int Layer;

		static std::unordered_map<std::wstring, PieceQuad*> Dict;

		static std::shared_ptr<PieceQuad> Get( const std::wstring &name );

//C# TO C++ CONVERTER NOTE: The variable MovingBlock was renamed since it is named the same as a user-defined type:
//C# TO C++ CONVERTER NOTE: The variable FallingBlock was renamed since it is named the same as a user-defined type:
//C# TO C++ CONVERTER NOTE: The variable BouncyBlock was renamed since it is named the same as a user-defined type:
		static std::shared_ptr<PieceQuad> MovingBlock_Renamed, FallingBlock_Renamed, BouncyBlock_Renamed, Elevator;
		static std::shared_ptr<BlockGroup> FallGroup, BouncyGroup, MovingGroup, ElevatorGroup;

		SimpleQuad Center;

		float t;
		bool Playing;

		Orientation MyOrientation;

		PieceQuadData Data;

		Color MyColor;

		BasePoint Base;

		/// <summary>
		/// Clone the properties of another PieceQuad to this PieceQuad.
		/// </summary>
		void Clone( const std::shared_ptr<PieceQuad> &PieceQuadA );

		/// <summary>
		/// The width of the pillar this piecequad is associated with, if any.
		/// </summary>
		int Pillar_Width;

		PieceQuad( int width, const std::wstring &texture, float left, float right, float top );
		PieceQuad( int width, const std::wstring &texture, float left, float right, float top, bool upside_down );
	private:
		void _Constructor( int width, const std::wstring &texture, float left, float right, float top, bool upside_down );

	public:
		PieceQuad();

	private:
		void InitAll();

	public:
		void SetAlpha( float Alpha );

		void SetColor( Color color );

		void SetEffect( const std::shared_ptr<EzEffect> &effect );

		void Init( const std::shared_ptr<EzTexture> &tex, const std::shared_ptr<EzEffect> &fx );

		Vector2 FromBounds( Vector2 TR, Vector2 BL );

		/// <summary>
		/// Whether to turn upside down this PieceQuad.
		/// </summary>
		bool Invert;

		void CalcQuads( Vector2 Size );

		float FixedHeight;
		void Update();

		void Draw();

	private:
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef PIECEQUAD
