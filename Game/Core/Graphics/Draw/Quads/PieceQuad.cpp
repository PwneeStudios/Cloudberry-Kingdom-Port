#include <global_header.h>

namespace CloudberryKingdom
{

	PieceQuadData::PieceQuadData() :
		LeftWidth( 0 ), RightWidth( 0 ), TopWidth( 0 ), BottomWidth( 0 ),
		RepeatWidth( 0 ), RepeatHeight( 0 ),
		BottomFlush( false ),
		UpsideDown( false ),
		Mirror( false )
	{
	}

	void PieceQuad::InitializeStatics()
	{
	}

	// Statics
	std::map<std::wstring, boost::shared_ptr<PieceQuad> > PieceQuad::Dict;
	boost::shared_ptr<PieceQuad> PieceQuad::MovingBlock_Renamed, PieceQuad::FallingBlock_Renamed, PieceQuad::BouncyBlock_Renamed, PieceQuad::Elevator;
	boost::shared_ptr<BlockGroup> PieceQuad::FallGroup, PieceQuad::BouncyGroup, PieceQuad::MovingGroup, PieceQuad::ElevatorGroup;


	void PieceQuad::CalcTexture( int anim, float t )
	{
		Center.CalcTexture( anim, t );
	}

	boost::shared_ptr<PieceQuad> PieceQuad::Get( const std::wstring &name )
	{
		return Dict[ name ];
	}

	void PieceQuad::Clone( const boost::shared_ptr<PieceQuad> &PieceQuadA )
	{
		FixedHeight = PieceQuadA->FixedHeight;

		Data = PieceQuadA->Data;

		MyOrientation = PieceQuadA->MyOrientation;

		Center = PieceQuadA->Center;

		Base = PieceQuadA->Base;

		SetColor( PieceQuadA->MyColor );
	}

	PieceQuad::PieceQuad( int width, const std::wstring &texture, float left, float right, float top )
	{
		InitializeInstanceFields();
		_Constructor( width, texture, left, right, top, false );
	}

	PieceQuad::PieceQuad( int width, const std::wstring &texture, float left, float right, float top, bool upside_down )
	{
		InitializeInstanceFields();
		_Constructor( width, texture, left, right, top, upside_down );
	}

	void PieceQuad::_Constructor( int width, const std::wstring &texture, float left, float right, float top, bool upside_down )
	{
		InitAll();
		Init( 0, Tools::BasicEffect );
		Pillar_Width = width;

		Data.RepeatWidth = 2000;
		Data.RepeatHeight = 2000;
		Data.UV_Multiples = Vector2( 1, 0 );
		Center.U_Wrap = Center.V_Wrap = false;

		FixedHeight = 0; // Flag to tell ParseExtra to set the height properly

		Center.SetTextureOrAnim( texture );

		int tex_width = Center.getTexWidth();
		int tex_height = Center.getTexHeight();

		if ( upside_down )
		{
			Data.UpsideDown = true;
			Data.BottomFlush = true;
		}
		Data.Center_BL_Shift.X = left;
		Data.Center_TR_Shift.X = right;
		Data.Center_TR_Shift.Y = Data.Center_BL_Shift.Y = top;

		// Extend the quad down to properly scale quad
		if ( FixedHeight == 0 )
		{
			float sprite_width = 2 * width + Data.Center_TR_Shift.X - Data.Center_BL_Shift.X;
			FixedHeight = sprite_width * static_cast<float>( tex_height ) / static_cast<float>( tex_width );
		}
	}

	PieceQuad::PieceQuad()
	{
		InitializeInstanceFields();
		InitAll();
	}

	void PieceQuad::InitAll()
	{
		Center = SimpleQuad();
		Center.Init();

		Base.Init();
	}

	void PieceQuad::SetAlpha( float Alpha )
	{
		Vector4 clr = MyColor.ToVector4();
		clr.W = Alpha;
		SetColor( Color( clr ) );
	}

	void PieceQuad::SetColor( Color color )
	{
		if ( MyColor == color )
			return;

		MyColor = color;

		Center.SetColor( color );
	}

	void PieceQuad::SetEffect( const boost::shared_ptr<EzEffect> &effect )
	{
		Center.MyEffect = effect;
	}

	void PieceQuad::Init( const boost::shared_ptr<EzTexture> &tex, const boost::shared_ptr<EzEffect> &fx )
	{
		Data.Center_BL_Shift = Vector2();
		Data.Center_TR_Shift = Vector2();

		Data.LeftWidth = Data.RightWidth = Data.TopWidth = Data.BottomWidth = 0;
		Data.RepeatWidth = Data.RepeatHeight = 0;

		Center.U_Wrap = false;
		Center.V_Wrap = false;

		Center.setMyTexture( tex );

		Center.MyEffect = fx;

		Center.U_Wrap = Center.V_Wrap = true;

		Data.UV_Multiples = Vector2( 1, 1 );

		SetColor( Color::White );
	}

	Vector2 PieceQuad::FromBounds( Vector2 TR, Vector2 BL )
	{
		CalcQuads( ( TR - BL ) / 2 );
		return ( TR + BL ) / 2;
	}

	void PieceQuad::CalcQuads( Vector2 Size )
	{
		// Prevent the center from being a sliver
		if ( Data.LeftWidth + Data.RightWidth + 3 > 2 * Size.X )
			Size.X = .5f * ( Data.LeftWidth + Data.RightWidth );

		float x1, x2, x3, x4, y1, y2, y3, y4;
		x1 = -Size.X;
		x2 = x1 + Data.LeftWidth;
		x4 = Size.X;
		x3 = x4 - Data.RightWidth;
		y1 = -Size.Y;
		y2 = y1 + Data.BottomWidth;
		y4 = Size.Y;
		y3 = y4 - Data.TopWidth;

		if ( FixedHeight >= 0 )
			y2 = y3 - FixedHeight;

		Vector2 SmallShift = Vector2( 1, 1 );

		if ( Data.BottomFlush || Invert )
			Center.FromBounds( Vector2( x2, y1 ) + Data.Center_BL_Shift, Vector2( x3 - 1, y1 + y3 - y2 - 1 ) + Data.Center_TR_Shift + SmallShift );
		else
			Center.FromBounds( Vector2( x2, y2 ) + Data.Center_BL_Shift, Vector2( x3 - 1, y3 - 1 ) + Data.Center_TR_Shift + SmallShift );

		float U, V;

		if ( Data.UV_Multiples.X == 0 )
			U = ( x3 - x2 ) / Data.RepeatWidth;
		else
		{
			U = ( x3 - x2 ) / Data.RepeatWidth;
			U = __max( 1, static_cast<int>( U / Data.UV_Multiples.X ) ) * Data.UV_Multiples.X;
		}

		if ( Data.UV_Multiples.Y == 0 )
			V = ( y3 - y2 ) / Data.RepeatHeight;
		else
		{
			V = ( y3 - y2 ) / Data.RepeatHeight;
			V = __max( 1, static_cast<int>( V / Data.UV_Multiples.Y ) ) * Data.UV_Multiples.Y;
		}


		if ( FixedHeight >= 0 )
			V = .995f;

		Orientation HoldOrientation;
		switch ( MyOrientation )
		{
			case Orientation_NORMAL:
				Center.UVFromBounds( Vector2( 0, V ), Vector2( U, 0 ) );
				break;

			case Orientation_UPSIDE_DOWN:
				Center.UVFromBounds( Vector2( 0, 0 ), Vector2( U, V ) );
				break;

			case Orientation_ROTATE_RIGHT:
				HoldOrientation = MyOrientation;
				MyOrientation = Orientation_NORMAL;
				std::swap( Size.X, Size.Y );
				CalcQuads( Size );
				MyOrientation = HoldOrientation;

				Center.RotateRight();

				break;

			case Orientation_ROTATE_LEFT:
				HoldOrientation = MyOrientation;
				MyOrientation = Orientation_NORMAL;
				std::swap( Size.X, Size.Y );
				CalcQuads( Size );
				MyOrientation = HoldOrientation;

				Center.RotateLeft();

				break;
		}

		if ( Data.UpsideDown || Invert )
			Center.MirrorUV_Vertical();

		if ( Data.Mirror )
			Center.MirrorUV_Horizontal();
	}

	void PieceQuad::Update()
	{
		Center.Update( Base );
	}

	void PieceQuad::Draw()
	{
		Update();

		Tools::QDrawer->DrawQuad( Center );
	}

	void PieceQuad::InitializeInstanceFields()
	{
		Invert = false;

		BoxHeight = -1;
		Group_CutoffWidth = 0;
		Layer = 0;
		Playing = false;
		MyOrientation = Orientation_NORMAL;
		Pillar_Width = 0;
		FixedHeight = -1;
	}
}
