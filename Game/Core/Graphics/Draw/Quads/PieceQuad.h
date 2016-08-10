#ifndef PIECEQUAD
#define PIECEQUAD

#include <small_header.h>

//#include "Core/Effects/EzEffect.h"
//#include "Core/Graphics/Draw/Simple/BasePoint.h"
#include "Core/Graphics/Draw/Simple/SimpleQuad.h"
//#include "Core/Texture/EzTexture.h"
//#include "Game/Tilesets/BlockGroup.h"
//#include "Game/Tools/Tools.h"


#include "Core/Graphics/Draw/Simple/BasePoint.h"

namespace CloudberryKingdom
{
	struct PieceQuadData
	{

		PieceQuadData();

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

	struct PieceQuad
	{

	
		static void InitializeStatics();

	
		enum Orientation
		{
			Orientation_NORMAL,
			Orientation_UPSIDE_DOWN,
			Orientation_ROTATE_RIGHT,
			Orientation_ROTATE_LEFT
		};
		// Some pillar info
	
		float BoxHeight;

        /// <summary>
        /// Used when Style.UseLowerBlockBounds == true. Block will have a lower lip than usual.
        /// This is used for InvertHero, so he is standing on the bottom of blocks properly.
        /// (Otherwise you want the lips to be higher, so your head doesn't hit them as easily).
        /// </summary>
        float ModLowerBlockBound;

        /// <summary>
        /// When ModLowerBlockBound is used, this says whether ModLowerBlockBound is an offset from the normal bound, or an absolute bound.
        /// </summary>
        bool RelativeLowerLip;

		void CalcTexture( int anim, float t );

		float Group_CutoffWidth;

		/// <summary>
		/// Layer of the quad, used in DrawPiles
		/// </summary>
		int Layer;

		static std::map<std::wstring, boost::shared_ptr<PieceQuad> > Dict;

		static boost::shared_ptr<PieceQuad> Get( const std::wstring &name );

		static boost::shared_ptr<PieceQuad> MovingBlock_Renamed, FallingBlock_Renamed, BouncyBlock_Renamed, Elevator;
		static boost::shared_ptr<BlockGroup> FallGroup, BouncyGroup, MovingGroup, ElevatorGroup;

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
		void Clone( const boost::shared_ptr<PieceQuad> &PieceQuadA );

		/// <summary>
		/// The width of the pillar this piecequad is associated with, if any.
		/// </summary>
		int Pillar_Width;

		PieceQuad( int width, const std::wstring &texture, float left, float right, float top );
		PieceQuad( int width, const std::wstring &texture, float left, float right, float top, bool upside_down );
	    PieceQuad(int width, const std::wstring &texture, float left, float right, float top, bool upside_down, float lowerlip, bool relativelowerlip);
	    void _Constructor(int width, const std::wstring &texture, float left, float right, float top, bool upside_down, float lowerlip, bool relativelowerlip);

	
		PieceQuad();

	
		void InitAll();

	
		void SetAlpha( float Alpha );

		void SetColor( Color color );

		void SetEffect( const boost::shared_ptr<EzEffect> &effect );

		void Init( const boost::shared_ptr<EzTexture> &tex, const boost::shared_ptr<EzEffect> &fx );

		Vector2 FromBounds( Vector2 TR, Vector2 BL );

		/// <summary>
		/// Whether to turn upside down this PieceQuad.
		/// </summary>
		bool Invert;

		void CalcQuads( Vector2 Size );

		float FixedHeight;
		void Update();

		void Draw();

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef PIECEQUAD
