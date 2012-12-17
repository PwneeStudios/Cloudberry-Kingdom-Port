#include <global_header.h>

namespace CloudberryKingdom
{

	float FancyColor::getA()
	{
		return clr2->getPos().Y;
	}

	Color FancyColor::getColor()
	{
		return ToColor( clr1->AbsVal, clr2->AbsVal );
	}

	void FancyColor::setColor( const Color &value )
	{
		clr1->Playing = false;
		clr2->Playing = false;
		clr1->RelVal = Pair1( value.ToVector4() );
		clr2->RelVal = Pair2( value.ToVector4() );
	}

	void FancyColor::Release()
	{
		clr1->Release();
		clr2->Release();
	}

	FancyColor::FancyColor()
	{
		InitializeInstanceFields();
		Init( Color::White );
	}

	FancyColor::FancyColor( Color color )
	{
		InitializeInstanceFields();
		Init( color );
	}

	void FancyColor::Init( Color color )
	{
		CreateVectors();
		setColor( color );
	}

	void FancyColor::CreateVectors()
	{
		clr1 = boost::make_shared<FancyVector2>();
		clr2 = boost::make_shared<FancyVector2>();
	}

	Color FancyColor::ToColor( Vector2 v1, Vector2 v2 )
	{
		return Color( Vector4( v1.X, v1.Y, v2.X, v2.Y ) );
	}

	Vector2 FancyColor::Pair1( Vector4 v )
	{
		return Vector2( v.X, v.Y );
	}

	Vector2 FancyColor::Pair2( Vector4 v )
	{
		return Vector2( v.Z, v.W );
	}

	Color FancyColor::GetDest()
	{
		return ToColor( clr1->GetDest(), clr2->GetDest() );
	}

	void FancyColor::ToAndBack( Vector4 End, int Frames )
	{
		clr1->ToAndBack( Pair1( End ), Frames );
		clr2->ToAndBack( Pair2( End ), Frames );
	}

	void FancyColor::ToAndBack( Vector4 Start, Vector4 End, int Frames )
	{
		clr1->ToAndBack( Pair1( Start ), Pair1( End ), Frames );
		clr2->ToAndBack( Pair2( Start ), Pair2( End ), Frames );
	}

	void FancyColor::LerpTo( Vector4 End, int Frames )
	{
		LerpTo( End, Frames, DefaultLerpStyle );
	}

	void FancyColor::LerpTo( Vector4 End, int Frames, LerpStyle Style )
	{
		clr1->LerpTo( Pair1( End ), Frames, Style );
		clr2->LerpTo( Pair2( End ), Frames, Style );
	}

	void FancyColor::LerpTo( Vector4 Start, Vector4 End, int Frames )
	{
		LerpTo( Start, End, Frames, DefaultLerpStyle );
	}

	void FancyColor::LerpTo( Vector4 Start, Vector4 End, int Frames, LerpStyle Style )
	{
		clr1->LerpTo( Pair1( Start ), Pair1( End ), Frames, Style );
		clr2->LerpTo( Pair2( Start ), Pair2( End ), Frames, Style );
	}

	Color FancyColor::Update()
	{
		return ToColor( clr1->Update(), clr2->Update() );
	}

	void FancyColor::InitializeInstanceFields()
	{
		DefaultLerpStyle = LerpStyle_LINEAR;
	}
}
