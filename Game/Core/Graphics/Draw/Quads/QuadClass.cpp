#include <small_header.h>
#include "Core/Graphics/Draw/Quads/QuadClass.h"

#include "Core/FancyVector2.h"
#include "Core/WriteReadTools.h"
#include "Core/Graphics/Draw/Quads/Quad.h"
#include "Core/Graphics/Draw/Simple/BasePoint.h"
#include "Core/Graphics/Draw/Simple/SimpleQuad.h"
#include "Core/Input/ButtonCheck.h"
#include "Core/Texture/EzTexture.h"
#include "Core/Texture/TextureOrAnim.h"
#include "Core/Tools/ColorHelper.h"
#include "Core/Tools/CoreMath.h"
#include "Game/Tilesets/SpriteInfo.h"
#include "Game/Tools/Camera.h"
#include "Game/Tools/Tools.h"

#include "Core/Texture/EzTextureWad.h"
#include "Hacks/String.h"

namespace CloudberryKingdom
{

	const Matrix &HsvQuad::getMyMatrix() const
	{
		return _MyMatrix;
	}

	void HsvQuad::setMyMatrix( const Matrix &value )
	{
		_MyMatrix = value;
		_MyMatrixSignature = ColorHelper::MatrixSignature( _MyMatrix );
	}

	HsvQuad::HsvQuad() : QuadClass()
	{
		_MyMatrixSignature = 0;
	}

	void HsvQuad::Set( const boost::shared_ptr<SpriteInfo> &info, Vector2 Size )
	{
		QuadClass::Set( info, Size );

		if ( info != 0 )
		{
			setMyMatrix( info->ColorMatrix );
		}
	}

	void HsvQuad::Draw( bool Update, bool DrawQuad, bool DrawShadow )
	{
		Tools::QDrawer->SetColorMatrix( getMyMatrix(), _MyMatrixSignature );
		QuadClass::Draw( Update, DrawQuad, DrawShadow );
	}

	boost::shared_ptr<QuadClass> QuadClass::FindQuad( std::vector<boost::shared_ptr<QuadClass> > &list, const std::wstring &Name )
	{
//C# TO C++ CONVERTER TODO TASK: There is no equivalent to implicit typing in C++ unless the C++11 inferred typing option is selected:
		for ( std::vector<boost::shared_ptr<QuadClass> >::const_iterator quad = list.begin(); quad != list.end(); ++quad )
//C# TO C++ CONVERTER TODO TASK: The following .NET 'String.Compare' reference is not converted:
			if ( CompareIgnoreCase( ( *quad )->Name, Name) == 0 )
				return *quad;

		return 0;
	}

	bool QuadClass::HitTest( Vector2 pos )
	{
		return HitTest( pos, Vector2() );
	}

	bool QuadClass::HitTest( Vector2 pos, Vector2 padding )
	{
		if ( !Show )
			return false;

		Update();

		if ( pos.X > getTR().X + padding.X )
			return false;
		if ( pos.X < getBL().X - padding.X )
			return false;
		if ( pos.Y > getTR().Y + padding.Y )
			return false;
		if ( pos.Y < getBL().Y - padding.Y )
			return false;

		return true;
	}

	bool QuadClass::HitTest_WithParallax( Vector2 pos, Vector2 padding, float Parallax )
	{
		if ( !Show )
			return false;

		Update();

		Vector2 c = Tools::getCurCamera()->getPos();

		if ( Base.e1.X > 0 )
		{
			if ( pos.X > Parallax * ( getTR().X - c.X ) + c.X + padding.X )
				return false;
			if ( pos.X < Parallax * ( getBL().X - c.X ) + c.X - padding.X )
				return false;
			if ( pos.Y > Parallax * ( getTR().Y - c.Y ) + c.Y + padding.Y )
				return false;
			if ( pos.Y < Parallax * ( getBL().Y - c.Y ) + c.Y - padding.Y )
				return false;
		}
		else
		{
			if ( pos.X > Parallax * ( getBL().X - c.X ) + c.X + padding.X )
				return false;
			if ( pos.X < Parallax * ( getTR().X - c.X ) + c.X - padding.X )
				return false;
			if ( pos.Y > Parallax * ( getTR().Y - c.Y ) + c.Y + padding.Y )
				return false;
			if ( pos.Y < Parallax * ( getBL().Y - c.Y ) + c.Y - padding.Y )
				return false;
		}

		return true;
	}

	const Vector2 &QuadClass::getTR() const
	{
		return Quad_Renamed.v1.Vertex.xy;
	}

	const Vector2 &QuadClass::getBL() const
	{
		return Quad_Renamed.v2.Vertex.xy;
	}

	const float &QuadClass::getLeft() const
	{
		return getBL().X;
	}

	void QuadClass::setLeft( const float &value )
	{
		setX( value + getSize().X );
	}

	const float &QuadClass::getX() const
	{
		return getPos().X;
	}

	void QuadClass::setX( const float &value )
	{
		setPos( Vector2( value, getPos().Y ) );
	}

	const float &QuadClass::getY() const
	{
		return getPos().Y;
	}

	void QuadClass::setY( const float &value )
	{
		setPos( Vector2( getPos().X, value ) );
	}

	void QuadClass::MakeLightAlpha()
	{
		if ( FancyLightAlpha != 0 )
			return;

		FancyLightAlpha = boost::make_shared<FancyVector2>();
	}

	void QuadClass::SetDefaultShadow()
	{
		SetDefaultShadow( Vector2( 12, 12 ), Color( .2f,.2f,.2f, 1 ) );
	}

	void QuadClass::SetDefaultShadow( float Offset )
	{
		SetDefaultShadow( Vector2( Offset, Offset ), Color( .2f,.2f,.2f, 1 ) );
	}

	void QuadClass::SetDefaultShadow( Vector2 offset, Color color )
	{
		Shadow = true;
		ShadowColor = color;
		ShadowOffset = offset;
	}

	void QuadClass::MakeFancyPos()
	{
		if ( FancyPos != 0 )
			FancyPos->Release();
		FancyPos = boost::make_shared<FancyVector2>();
		FancyPos->RelVal = Base.Origin;
	}

	void QuadClass::Release()
	{
		if ( FancyPos != 0 )
			FancyPos->Release();
			FancyPos.reset();
		if ( FancyScale != 0 )
			FancyScale->Release();
			FancyScale.reset();
		if ( FancyAngle != 0 )
			FancyAngle->Release();
			FancyAngle.reset();
	}

	const Vector2 &QuadClass::getLightAlpha()
	{
		MakeLightAlpha();
		return FancyLightAlpha->RelVal;
	}

	void QuadClass::setLightAlpha( const Vector2 &value )
	{
		MakeLightAlpha();
		FancyLightAlpha->RelVal = value;
	}

	const Vector2 &QuadClass::getPos() const
	{
		if ( FancyPos == 0 )
			return Base.Origin;
		else
			return FancyPos->RelVal;
	}

	void QuadClass::setPos( const Vector2 &value )
	{
		if ( FancyPos == 0 )
			Base.Origin = value;
		else
			FancyPos->RelVal = value;
	}

	float QuadClass::getPosY() const
	{
		return getPos().Y;
	}

	void QuadClass::setPosY( const float &value )
	{
		setPos( Vector2( getPos().X, value ) );
	}

	float QuadClass::getSizeX() const
	{
		return getSize().X;
	}

	void QuadClass::setSizeX( const float &value )
	{
		setSize( Vector2( value, getSize().Y ) );
	}

	float QuadClass::getSizeY() const
	{
		return getSize().Y;
	}

	void QuadClass::setSizeY( const float &value )
	{
		setSize( Vector2( getSize().X, value ) );
	}

	Vector2 QuadClass::getSize() const
	{
		if ( FancyScale == 0 )
			return Vector2( Base.e1.Length(), Base.e2.Length() );
		else
			return FancyScale->RelVal;
	}

	void QuadClass::setSize( const Vector2 &value )
	{
		if ( FancyScale == 0 )
		{
			Rescale( value );
		}
		else
			FancyScale->RelVal = value;
	}

	float QuadClass::getDegrees() const
	{
		return CoreMath::Degrees( getAngle() );
	}

	void QuadClass::setDegrees( const float &value )
	{
		setAngle( CoreMath::Radians( value ) );
	}

	float QuadClass::getAngle() const
	{
		if ( FancyAngle == 0 )
			return 0;
		else
			return FancyAngle->RelVal.X;
	}

	void QuadClass::setAngle( const float &value )
	{
		if ( FancyAngle == 0 )
			return;
		else
			FancyAngle->setRelValX( value );
	}

	QuadClass::QuadClass( const boost::shared_ptr<Quad> &quad )
	{
		InitializeInstanceFields();
		Initialize( 0, false, false );
		Quad_Renamed = SimpleQuad( quad );
	}

	QuadClass::QuadClass( const boost::shared_ptr<QuadClass> &quad )
	{
		InitializeInstanceFields();
		Initialize( 0, false, false );
		quad->Clone( this->shared_from_this() );
	}

	QuadClass::QuadClass()
	{
		InitializeInstanceFields();
		Initialize( 0, false, false );
	}

	QuadClass::QuadClass( const boost::shared_ptr<FancyVector2> &Center )
	{
		InitializeInstanceFields();
		Initialize( Center, false, false );
	}

	QuadClass::QuadClass( const boost::shared_ptr<FancyVector2> &Center, bool UseFancySize )
	{
		InitializeInstanceFields();
		Initialize( Center, UseFancySize, false );
	}

	QuadClass::QuadClass( const boost::shared_ptr<FancyVector2> &Center, bool UseFancySize, bool UseFancyAngle )
	{
		InitializeInstanceFields();
		Initialize( Center, UseFancySize, UseFancyAngle );
	}

	QuadClass::~QuadClass()
	{
	}

	void QuadClass::Initialize( const boost::shared_ptr<FancyVector2> &Center, bool UseFancySize, bool UseFancyAngle )
	{
		Quad_Renamed.Init();
		Base.Init();

		SetToDefault();

		if ( Center != 0 )
		{
			FancyPos = boost::make_shared<FancyVector2>();
			FancyPos->Center = Center;
		}

		if ( UseFancySize )
		{
			FancyScale = boost::make_shared<FancyVector2>();
		}

		if ( UseFancyAngle )
		{
			FancyAngle = boost::make_shared<FancyVector2>();
		}
	}

	const std::wstring &QuadClass::getTextureName() const
	{
		return Quad_Renamed.getMyTexture()->Path;
	}

	void QuadClass::setTextureName( const std::wstring &value )
	{
		Quad_Renamed.setMyTexture( Tools::TextureWad->FindByName( value ) );
	}

	const std::wstring &QuadClass::getEffectName() const
	{
		return Quad_Renamed.MyEffect->Name;
	}

	void QuadClass::setEffectName( const std::wstring &value )
	{
		Quad_Renamed.MyEffect = Tools::EffectWad->FindByName( value );
	}

	boost::shared_ptr<QuadClass> QuadClass::Clone()
	{
		boost::shared_ptr<QuadClass> cloned = boost::make_shared<QuadClass>();
		Clone( cloned );
		return cloned;
	}

	void QuadClass::Clone( const boost::shared_ptr<QuadClass> &quad )
	{
		quad->Base = Base;

		quad->Quad_Renamed.setMyTexture( Quad_Renamed.getMyTexture() );
		quad->Quad_Renamed.ExtraTexture1 = Quad_Renamed.ExtraTexture1;
		quad->Quad_Renamed.ExtraTexture2 = Quad_Renamed.ExtraTexture2;
		quad->Quad_Renamed.MyEffect = Quad_Renamed.MyEffect;

		quad->Quad_Renamed.SetColor( Quad_Renamed.MySetColor );
	}

	void QuadClass::SetTexture( const std::wstring &Name )
	{
		Quad_Renamed.setMyTexture( Tools::TextureWad->FindByName( Name ) );
	}

	float QuadClass::WidthToScreenWidthRatio( const boost::shared_ptr<Camera> &cam )
	{
		return.5f * getSize().X / cam->GetWidth();
	}

	void QuadClass::SetSize( Vector2 size )
	{
		if ( size.X < 0 )
			ScaleXToMatchRatio( size.Y );
		else if ( size.Y < 0 )
			ScaleYToMatchRatio( size.X );
		else
			setSize( size );
	}

	void QuadClass::ScaleToTextureSize()
	{
		if ( Quad_Renamed.getMyTexture() != 0 )
		{
			setSize( Vector2( static_cast<float>( Quad_Renamed.getTexWidth() ),
				static_cast<float>( Quad_Renamed.getTexHeight() ) ) );
		}
	}

	void QuadClass::Rescale( Vector2 size )
	{
		Base.e1.Normalize();
		Base.e1 *= size.X;
		Base.e2.Normalize();
		Base.e2 *= size.Y;
	}

	void QuadClass::Scale( float scale )
	{
		setSize( getSize() * scale );
	}

	Vector2 QuadClass::GetTextureScaling()
	{
		return Vector2( getSize().X / Quad_Renamed.getTexWidth(), getSize().Y / Quad_Renamed.getTexHeight() );
	}

	void QuadClass::ScaleXToMatchRatio()
	{
		ScaleXToMatchRatio( getSize().Y );
	}

	void QuadClass::ScaleXToMatchRatio( float height )
	{
		if ( Quad_Renamed.getMyTexture()->Load() )
			setSize( Vector2( height * Quad_Renamed.getTexWidth() / Quad_Renamed.getTexHeight() * Quad_Renamed.getUV_Repeat().X / Quad_Renamed.getUV_Repeat().Y, height ) );
	}

	void QuadClass::ScaleYToMatchRatio()
	{
		ScaleYToMatchRatio( getSize().X );
	}

	void QuadClass::ScaleYToMatchRatio( float width )
	{
		if ( Quad_Renamed.getMyTexture()->Load() )
			setSize( Vector2( width, width * Quad_Renamed.getTexHeight() / Quad_Renamed.getTexWidth() * Quad_Renamed.getUV_Repeat().Y / Quad_Renamed.getUV_Repeat().X ) );
	}

	void QuadClass::RepeatY()
	{
		float V = ( getSize().Y / Quad_Renamed.getTexHeight() ) / (getSize().X / Quad_Renamed.getTexWidth());
		Quad_Renamed.UVFromBounds( Vector2(), Vector2( 1, V ) );
		Quad_Renamed.V_Wrap = true;
	}

	void QuadClass::PointxAxisTo( float Radians )
	{
		Vector2 Dir = Vector2( static_cast<float>( cos( Radians ) ), static_cast<float>( sin( Radians ) ) );
		PointxAxisTo( Dir );
	}

	void QuadClass::PointxAxisTo( Vector2 Dir )
	{
		CoreMath::PointxAxisTo( Base.e1, Base.e2, Dir );
	}

	void QuadClass::TextureParralax( float Parralax, Vector2 repeat, Vector2 shift, const boost::shared_ptr<Camera> &Cam )
	{
		Vector2 offset = Parralax * repeat * ( Cam->EffectivePos + shift ) / ( 2 * Vector2( Cam->AspectRatio / .001f, 1 / .001f ) );

		offset.Y *= -1;
		repeat *= .001f / Cam->EffectiveZoom.X;
		Quad_Renamed.v0.Vertex.uv = Vector2( -repeat.X / 2, -repeat.Y / 2 ) + offset;
		Quad_Renamed.v1.Vertex.uv = Vector2( repeat.X / 2, -repeat.Y / 2 ) + offset;
		Quad_Renamed.v2.Vertex.uv = Vector2( -repeat.X / 2, repeat.Y / 2 ) + offset;
		Quad_Renamed.v3.Vertex.uv = Vector2( repeat.X / 2, repeat.Y / 2 ) + offset;
	}

	void QuadClass::FullScreen( const boost::shared_ptr<Camera> &cam )
	{
		setSize( Vector2( ( cam->EffectiveTR.X - cam->EffectiveBL.X ) / 2, ( cam->EffectiveTR.Y - cam->EffectiveBL.Y ) / 2 ) );
		setPos( ( cam->EffectiveTR + cam->EffectiveBL ) / 2 );
	}

	void QuadClass::FromBounds( Vector2 BL, Vector2 TR )
	{
		setSize( Vector2( ( TR.X - BL.X ) / 2, ( TR.Y - BL.Y ) / 2 ) );
		setPos( ( TR + BL ) / 2 );
	}

	void QuadClass::SetToDefault()
	{
		Quad_Renamed.MyEffect = Tools::BasicEffect;
		Quad_Renamed.setMyTexture( Tools::TextureWad->FindByName( std::wstring( L"White" ) ) );
	}

	QuadClass::QuadClass( const boost::shared_ptr<EzTexture> &texture )
	{
		InitializeInstanceFields();
		Initialize( 0, false, false );
		Set( texture, 1 );
		ScaleToTextureSize();
	}

	QuadClass::QuadClass( const std::wstring &name )
	{
		InitializeInstanceFields();
		Initialize( 0, false, false );
		Set( Tools::Texture( name ), 1 );
		ScaleToTextureSize();
	}

	QuadClass::QuadClass( const std::wstring &TextureName, float Width )
	{
		InitializeInstanceFields();
		Initialize( 0, false, false );
		Set( TextureName, Width );
	}

	QuadClass::QuadClass( const std::wstring &TextureName, const std::wstring &Name )
	{
		InitializeInstanceFields();
		Initialize( 0, false, false );
		Set( TextureName, 100 );
		this->Name = Name;
	}

	QuadClass::QuadClass( const boost::shared_ptr<EzTexture> &Texture, float Width, const std::wstring &Name )
	{
		InitializeInstanceFields();
		Initialize( 0, false, false );
		Set( Texture, Width );
		this->Name = Name;
	}

	QuadClass::QuadClass( const boost::shared_ptr<EzTexture> &Texture, float Width, bool Fancy )
	{
		InitializeInstanceFields();
		Initialize( 0, Fancy, Fancy );
		Set( Texture, Width );
	}

	QuadClass::QuadClass( const std::wstring &TextureName, float Width, bool Fancy )
	{
		InitializeInstanceFields();
		Initialize( 0, Fancy, Fancy );
		Set( TextureName, Width );
	}

	void QuadClass::Set( const std::wstring &TextureName, float Width )
	{
		Quad_Renamed.MyEffect = Tools::BasicEffect;
		this->setTextureName( TextureName );

		ScaleYToMatchRatio( Width );
	}

	void QuadClass::Set( const boost::shared_ptr<EzTexture> &Texture, float Width )
	{
		Quad_Renamed.MyEffect = Tools::BasicEffect;
		Quad_Renamed.setMyTexture( Texture );

		ScaleYToMatchRatio( Width );
	}

	void QuadClass::Set( const boost::shared_ptr<TextureOrAnim> &t_or_a )
	{
		Quad_Renamed.SetTextureOrAnim( t_or_a );
	}

	void QuadClass::Set( const std::wstring &name )
	{
		Quad_Renamed.SetTextureOrAnim( name );
	}

	void QuadClass::Set( const boost::shared_ptr<SpriteInfo> &info )
	{
		Set( info, info->Size );
	}

	void QuadClass::Set( const boost::shared_ptr<SpriteInfo> &info, Vector2 Size )
	{
		if ( info->Sprite == 0 )
			Show = false;
		else
		{
			Quad_Renamed.DefaultCorners();

			Set( info->Sprite );
			SetSize( info->Size );

			if ( info->RelativeOffset )
				Quad_Renamed.Shift( info->Offset );
			else
				Quad_Renamed.Shift( info->Offset / this->getSize() );

			if ( info->Degrees != 0 )
				setDegrees( info->Degrees );
		}
	}

	void QuadClass::Draw()
	{
		Draw( true, true, Shadow );
	}

	void QuadClass::DrawShadow()
	{
		Draw( true, false, true );
	}

	void QuadClass::MultiplyAlpha( float alpha )
	{
		Quad_Renamed.MultiplyAlpha( alpha );
	}

	float QuadClass::getAlpha() const
	{
		return Quad_Renamed.MySetColor.A / 255.f;
	}

	void QuadClass::setAlpha( const float &value )
	{
		//if (value == 1) Tools::Write("");
		Quad_Renamed.SetAlpha( value );
	}

	void QuadClass::Fade( float speed )
	{
		Fading = true;
		FadeSpeed = speed;
	}

	void QuadClass::ResetFade()
	{
		Fading = false;
		setAlpha( 1 );
	}

	void QuadClass::Draw( bool Update, bool DrawQuad, bool DrawShadow )
	{
		if ( !Show )
			return;

		if ( Fading )
		{
			setAlpha( CoreMath::RestrictVal( MinAlpha, MaxAlpha, getAlpha() + FadeSpeed ) );
		}

		if ( FancyLightAlpha != 0 )
		{
			FancyLightAlpha->RelVal = CoreMath::Restrict( 0, 1000, FancyLightAlpha->RelVal );
			FancyLightAlpha->Update();

			Vector4 color = Vector4( FancyLightAlpha->getPos().X / 1000 );
			color.W = FancyLightAlpha->getPos().Y / 1000;

			Quad_Renamed.SetColor( color );
		}

		if ( FancyPos != 0 )
			Base.Origin = FancyPos->Update( ParentScaling );

		Vector2 HoldScale = Vector2(1);
		Color HoldColor = Quad_Renamed.MySetColor;
		if ( FancyScale != 0 )
		{
			Vector2 scale = FancyScale->Update() * ParentScaling;
			Base.e1 = Vector2( scale.X, 0 );
			Base.e2 = Vector2( 0, scale.Y );
		}
		else
		{
			if ( ParentScaling != Vector2(1) )
			{
				HoldScale = getSize();
				setSize( getSize() * ParentScaling );
			}
		}
		if ( ParentAlpha != 1 )
			MultiplyAlpha( ParentAlpha );

		if ( FancyAngle != 0 )
		{
			float Angle = FancyAngle->Update().X;
			PointxAxisTo( Angle );
		}

		if ( DrawShadow )
		{
			Quad_Renamed.MyEffect = Tools::EffectWad->EffectList[ 1 ];
			Vector2 HoldSize = getSize();
			Scale( ShadowScale );
			Base.Origin -= ShadowOffset;
			Color _HoldColor = Quad_Renamed.MySetColor;
			Quad_Renamed.SetColor( ShadowColor );
			Quad_Renamed.Update( Base );
			Tools::QDrawer->DrawQuad( Quad_Renamed );
			//Tools::QDrawer.Flush();
			Quad_Renamed.MyEffect = Tools::BasicEffect;
			Base.Origin += ShadowOffset;
			Quad_Renamed.SetColor( _HoldColor );
			setSize( HoldSize );
		}

		if ( Update )
			Quad_Renamed.Update( Base );

		if ( DrawQuad )
			Tools::QDrawer->DrawQuad( Quad_Renamed );

		// Reset scaling if modified
		if ( FancyScale == 0 && ParentScaling != Vector2(1) )
			setSize( HoldScale );
		// Reset alpha if modified
		if ( ParentAlpha != 1 )
			Quad_Renamed.SetColor( HoldColor );
	}

	void QuadClass::UpdateShift()
	{
		Quad_Renamed.UpdateShift( Base );
	}

	void QuadClass::UpdateShift_Precalc()
	{
		Quad_Renamed.UpdateShift_Precalc( Base );
	}

	void QuadClass::Update()
	{
		Quad_Renamed.Update( Base );
	}

	void QuadClass::Write( const boost::shared_ptr<BinaryWriter> &writer )
	{
		writer->Write( Quad_Renamed.getMyTexture()->Path );
		writer->Write( Quad_Renamed.MyEffect->Name );

		WriteReadTools::WriteVector2( writer, Base.e1 );
		WriteReadTools::WriteVector2( writer, Base.e2 );
		WriteReadTools::WriteVector2( writer, Base.Origin );
	}

	void QuadClass::Read( const boost::shared_ptr<BinaryReader> &reader )
	{
		Quad_Renamed.setMyTexture( Tools::TextureWad->FindByName( reader->ReadString() ) );
		Quad_Renamed.MyEffect = Tools::EffectWad->FindByName( reader->ReadString() );

		WriteReadTools::ReadVector2( reader, Base.e1 );
		WriteReadTools::ReadVector2( reader, Base.e2 );
		WriteReadTools::ReadVector2( reader, Base.Origin );
	}

	void QuadClass::InitializeInstanceFields()
	{
		Shadow = false;
		ShadowOffset = Vector2();
		ShadowColor = Color::Black;
		ShadowScale = 1;
		Quad_Renamed = SimpleQuad();
		Name = std::wstring( L"" );
		Layer = 0;
		ParentScaling = Vector2(1);
		ParentAlpha = 1;
		Fading = false;
		FadeSpeed = 0;
		MinAlpha = 0;
		MaxAlpha = 1;
		Show = true;
	}
}
