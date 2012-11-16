#include <global_header.h>

using namespace Microsoft::Xna::Framework;

namespace CloudberryKingdom
{

	const float &FancyColor::getA() const
	{
		return clr2->getPos().Y;
	}

	const Microsoft::Xna::Framework::Color &FancyColor::getColor() const
	{
		return ToColor( clr1->AbsVal, clr2->AbsVal );
	}

	void FancyColor::setColor( const Microsoft::Xna::Framework::Color &value )
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
		Init( getColor().White );
	}

	FancyColor::FancyColor( Microsoft::Xna::Framework::Color color )
	{
		InitializeInstanceFields();
		Init( color );
	}

	void FancyColor::Init( Microsoft::Xna::Framework::Color color )
	{
		CreateVectors();
		setColor( color );
	}

	void FancyColor::CreateVectors()
	{
		clr1 = std::make_shared<FancyVector2>();
		clr2 = std::make_shared<FancyVector2>();
	}

	Microsoft::Xna::Framework::Color FancyColor::ToColor( Vector2 v1, Vector2 v2 )
	{
		return Color( Vector4( v1.X, v1.Y, v2.X, v2.Y ) );
	}

	Microsoft::Xna::Framework::Vector2 FancyColor::Pair1( Vector4 v )
	{
		return Vector2( v.X, v.Y );
	}

	Microsoft::Xna::Framework::Vector2 FancyColor::Pair2( Vector4 v )
	{
		return Vector2( v.Z, v.W );
	}

	Microsoft::Xna::Framework::Color FancyColor::GetDest()
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

	Microsoft::Xna::Framework::Color FancyColor::Update()
	{
		return ToColor( clr1->Update(), clr2->Update() );
	}

	void FancyColor::InitializeInstanceFields()
	{
		DefaultLerpStyle = LerpStyle_LINEAR;
	}
}
