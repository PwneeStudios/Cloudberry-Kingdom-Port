#include <global_header.h>









namespace CloudberryKingdom
{

	const std::vector<std::wstring> &SimpleQuad::get_bits_to_save() const
	{
		return IsDefault() ? _bits_to_save_simple : _bits_to_save_full;
	}

const std::wstring* tempVector[] = { _T( "v0" ), _T( "v1" ), _T( "v2" ), _T( "v3" ), _T( "MySetColor" ), _T( "PremultipliedColor" ), _T( "BlendAddRatio" ), _T( "_MyTexture" ), _T( "ExtraTexture1" ), _T( "ExtraTexture2" ), _T( "MyEffect" ) };
std::vector<std::wstring> SimpleQuad::_bits_to_save_full = std::vector<std::wstring*>( tempVector, tempVector + sizeof( tempVector ) / sizeof( tempVector[ 0 ] ) );
const std::wstring* tempVector2[] = { _T( "MySetColor" ), _T( "PremultipliedColor" ), _T( "BlendAddRatio" ), _T( "_MyTexture" ), _T( "ExtraTexture1" ), _T( "ExtraTexture2" ), _T( "MyEffect" ) };
std::vector<std::wstring> SimpleQuad::_bits_to_save_simple = std::vector<std::wstring*>( tempVector2, tempVector2 + sizeof( tempVector2 ) / sizeof( tempVector2[ 0 ] ) );

	void SimpleQuad::WriteCode( const std::wstring &prefix, const std::shared_ptr<StreamWriter> &writer )
	{
		Tools::WriteFieldsToCode( *this, prefix, writer, get_bits_to_save() );
	}

	void SimpleQuad::Write( const std::shared_ptr<StreamWriter> &writer )
	{
		Tools::WriteFields( *this, writer, get_bits_to_save() );
	}

	void SimpleQuad::Read( const std::shared_ptr<StreamReader> &reader )
	{
		*this = static_cast<SimpleQuad>( Tools::ReadFields( *this, reader ) );
		SetColor( MySetColor, true );
	}

	void SimpleQuad::NextKeyFrame()
	{
		std::shared_ptr<CloudberryKingdom::EzTexture> data = TextureAnim->NextKeyFrame();
		setMyTexture( data );
	}

	void SimpleQuad::SetTextureAnim( const std::shared_ptr<AnimationData_Texture> &TextureAnim )
	{
		this->TextureAnim = TextureAnim;
		t = 0;
		anim = 0;
		Playing = true;
		speed = 1;
	}

	void SimpleQuad::Set( const std::shared_ptr<TextureOrAnim> &t_or_a )
	{
		SetTextureOrAnim( t_or_a );
	}

	void SimpleQuad::Set( const std::wstring &name )
	{
		SetTextureOrAnim( name );
	}

	void SimpleQuad::UpdateTextureAnim()
	{
		float dt = Tools::CurLevel->IndependentDeltaT;
		t += dt * TextureAnim->Anims[ anim ].Speed * speed;

		CalcTexture( anim, t );
	}

	const std::shared_ptr<EzTexture> &SimpleQuad::getMyTexture() const
	{
		return _MyTexture;
	}

	void SimpleQuad::setMyTexture( const std::shared_ptr<EzTexture> &value )
	{
		_MyTexture = value;
		if ( _MyTexture != 0 && _MyTexture->FromPacked )
		{
			map( uv0, v0.Vertex.uv, _MyTexture->BL, _MyTexture->TR );
			map( uv1, v1.Vertex.uv, _MyTexture->BL, _MyTexture->TR );
			map( uv2, v2.Vertex.uv, _MyTexture->BL, _MyTexture->TR );
			map( uv3, v3.Vertex.uv, _MyTexture->BL, _MyTexture->TR );
			//UVFromBounds(_MyTexture.BL, _MyTexture.TR);
			//MyTexture = MyTexture.Packed;
		}
	}

	void SimpleQuad::CalcTexture( int anim, float frame )
	{
		this->anim = anim;
		this->t = frame;

		if ( t >= TextureAnim->Anims[ anim ].Data.size() )
			t = 0;
		else if ( t < 0 )
		{
			t += TextureAnim->Anims[ anim ].Data.size();
			if ( t < 0 )
				t = TextureAnim->Anims[ anim ].Data.size() - 1;
		}

		std::shared_ptr<CloudberryKingdom::EzTexture> data = TextureAnim->Calc( anim, t );
		setMyTexture( data );
	}

	void SimpleQuad::map( Vector2 &base_uv, Vector2 &new_uv, Vector2 &bl, Vector2 &tr )
	{
		if ( base_uv.X == 0 )
			new_uv.X = bl.X;
		else
			new_uv.X = tr.X;
		if ( base_uv.Y == 1 )
			new_uv.Y = bl.Y;
		else
			new_uv.Y = tr.Y;
	}

	void SimpleQuad::Release()
	{
		v0.Release();
		v1.Release();
		v2.Release();
		v3.Release();

		MyEffect.reset();
		getMyTexture().reset();
	}

	SimpleQuad::SimpleQuad( SimpleQuad &quad )
	{
		Name = quad.Name;

		Animated = quad.Animated;
		TextureAnim = quad.TextureAnim;
		t = quad.t;
		anim = quad.anim;
		Playing = quad.Playing;
		speed = quad.speed;

		Hide = false;

		MySetColor = quad.MySetColor;
		PremultipliedColor = quad.PremultipliedColor;
		BlendAddRatio = quad.BlendAddRatio;

		uv0 = quad.uv0;
		uv1 = quad.uv1;
		uv2 = quad.uv2;
		uv3 = quad.uv3;

		v0 = quad.v0;
		v1 = quad.v1;
		v2 = quad.v2;
		v3 = quad.v3;

		PreCalc0 = quad.PreCalc0;
		PreCalc1 = quad.PreCalc1;
		PreCalc2 = quad.PreCalc2;
		PreCalc3 = quad.PreCalc3;

		MyEffect = quad.MyEffect;
		_MyTexture = quad._MyTexture;

		ExtraTexture1 = quad.ExtraTexture1;
		ExtraTexture2 = quad.ExtraTexture2;

		U_Wrap = quad.U_Wrap;
		V_Wrap = quad.V_Wrap;

		Illumination = quad.Illumination;
		UseGlobalIllumination = quad.UseGlobalIllumination;
	}

	SimpleQuad::SimpleQuad( const std::shared_ptr<Quad> &quad )
	{
		Name = quad.Name;

		Animated = true;
		TextureAnim = quad.TextureAnim;

		Hide = false;

		MySetColor = quad->MyColor;
		PremultipliedColor = quad.PremultipliedColor;
		BlendAddRatio = 0;

		uv0 = quad->Vertices[ 0 ].uv;
		uv1 = quad->Vertices[ 1 ].uv;
		uv2 = quad->Vertices[ 2 ].uv;
		uv3 = quad->Vertices[ 3 ].uv;

		v0.Vertex = quad->Vertices[ 0 ];
		v1.Vertex = quad->Vertices[ 1 ];
		v2.Vertex = quad->Vertices[ 2 ];
		v3.Vertex = quad->Vertices[ 3 ];

		v0.Pos = quad->Vertices[ 0 ].xy;
		v1.Pos = quad->Vertices[ 1 ].xy;
		v2.Pos = quad->Vertices[ 2 ].xy;
		v3.Pos = quad->Vertices[ 3 ].xy;

		v0.AnimData = quad->Corner[ 0 ]->AnimData;
		v1.AnimData = quad->Corner[ 1 ]->AnimData;
		v2.AnimData = quad->Corner[ 2 ]->AnimData;
		v3.AnimData = quad->Corner[ 3 ]->AnimData;

		PreCalc0 = PreCalc1 = PreCalc2 = PreCalc3 = Vector2::Zero;

		MyEffect = quad.MyEffect;
		_MyTexture.reset();
		ExtraTexture1 = ExtraTexture2 = 0;

		U_Wrap = V_Wrap = false;

		UseGlobalIllumination = true;
		Illumination = 1;

		t = anim = 0;
		Playing = false;
		speed = 1;

		setMyTexture( quad->MyTexture );
	}

	void SimpleQuad::SetTextureOrAnim( const std::shared_ptr<TextureOrAnim> &t_or_a )
	{
		if ( t_or_a->IsAnim )
		{
			SetTextureAnim( t_or_a->MyAnim );
			CalcTexture( 0, 0 );
		}
		else
			setMyTexture( t_or_a->MyTexture );
	}

	void SimpleQuad::SetTextureOrAnim( const std::wstring &name )
	{
		if ( Tools::TextureWad->AnimationDict.find( name ) != Tools::TextureWad->AnimationDict.end() )
			SetTextureAnim( Tools::TextureWad->AnimationDict[ name ] );
		else
			setTextureName( name );
	}

	const int &SimpleQuad::getTexWidth() const
	{
		if ( TextureAnim != 0 )
			return TextureAnim->Width;
		else
			return getMyTexture()->Width;
	}

	const int &SimpleQuad::getTexHeight() const
	{
		if ( TextureAnim != 0 )
			return TextureAnim->Height;
		else
			return getMyTexture()->Height;
	}

	const std::wstring &SimpleQuad::getTextureName() const
	{
		return getMyTexture()->Path;
	}

	void SimpleQuad::setTextureName( const std::wstring &value )
	{
		setMyTexture( Tools::TextureWad->FindByName( value ) );
	}

	void SimpleQuad::EnforceTextureRatio()
	{
		float Ratio = static_cast<float>( getMyTexture()->Height ) / static_cast<float>(getMyTexture()->Width);
		v0.Pos = Vector2( -1, Ratio );
		v1.Pos = Vector2( 1, Ratio );
		v2.Pos = Vector2( -1, -Ratio );
		v3.Pos = Vector2( 1, -Ratio );
	}

	const Microsoft::Xna::Framework::Vector2 &SimpleQuad::getTR() const
	{
		return v1.Vertex.xy;
	}

	const Microsoft::Xna::Framework::Vector2 &SimpleQuad::getBL() const
	{
		return v2.Vertex.xy;
	}

	const float &SimpleQuad::getRight() const
	{
		return v1.Vertex.xy.X;
	}

	const float &SimpleQuad::getLeft() const
	{
		return v2.Vertex.xy.X;
	}

	const float &SimpleQuad::getTop() const
	{
		return v1.Vertex.xy.Y;
	}

	const float &SimpleQuad::getBottom() const
	{
		return v2.Vertex.xy.Y;
	}

	const float &SimpleQuad::getWidth() const
	{
		return getRight() - getLeft();
	}

	const float &SimpleQuad::getHeight() const
	{
		return getTop() - getBottom();
	}

	void SimpleQuad::Shift( Vector2 shift )
	{
		v0.Pos += shift;
		v1.Pos += shift;
		v2.Pos += shift;
		v3.Pos += shift;
	}

	void SimpleQuad::FromBounds( Vector2 BL, Vector2 TR )
	{
		v0.Pos = Vector2( BL.X, TR.Y );
		v1.Pos = TR;
		v2.Pos = BL;
		v3.Pos = Vector2( TR.X, BL.Y );
	}

	void SimpleQuad::RotateRight()
	{
		v0.RotateRight();
		v1.RotateRight();
		v2.RotateRight();
		v3.RotateRight();
	}

	void SimpleQuad::RotateLeft()
	{
		v0.RotateLeft();
		v1.RotateLeft();
		v2.RotateLeft();
		v3.RotateLeft();
	}

	void SimpleQuad::RotateUV()
	{
		Vector2 hold = v0.Vertex.uv;

		v0.Vertex.uv = v1.Vertex.uv;
		v1.Vertex.uv = v3.Vertex.uv;
		v3.Vertex.uv = v2.Vertex.uv;
		v2.Vertex.uv = hold;
	}

	void SimpleQuad::MirrorUV_Vertical()
	{
		Vector2 hold;

		hold = v0.Vertex.uv;
		v0.Vertex.uv = v2.Vertex.uv;
		v2.Vertex.uv = hold;

		hold = v1.Vertex.uv;
		v1.Vertex.uv = v3.Vertex.uv;
		v3.Vertex.uv = hold;
	}

	void SimpleQuad::MirrorUV_Horizontal()
	{
		Vector2 hold;

		hold = v0.Vertex.uv;
		v0.Vertex.uv = v1.Vertex.uv;
		v1.Vertex.uv = hold;

		hold = v2.Vertex.uv;
		v2.Vertex.uv = v3.Vertex.uv;
		v3.Vertex.uv = hold;
	}

	const Microsoft::Xna::Framework::Vector2 &SimpleQuad::getUV_Offset() const
	{
		if ( _MyTexture->FromPacked )
			return v0.Vertex.uv / Vector2( _MyTexture->TR.X - _MyTexture->BL.X, _MyTexture->BL.Y - _MyTexture->TR.Y );
		else
			return v0.Vertex.uv;
	}

	void SimpleQuad::setUV_Offset( const Vector2 &value )
	{
		UVFromBounds_2( value, value + getUV_Repeat() );
	}

	const Microsoft::Xna::Framework::Vector2 &SimpleQuad::getUV_Repeat() const
	{
		if ( _MyTexture->FromPacked )
			return ( v3.Vertex.uv - v0.Vertex.uv ) / Vector2( _MyTexture->TR.X - _MyTexture->BL.X, _MyTexture->BL.Y - _MyTexture->TR.Y );
		else
			return v3.Vertex.uv - v0.Vertex.uv;
	}

	void SimpleQuad::setUV_Repeat( const Vector2 &value )
	{
		UVFromBounds_2( getUV_Offset(), getUV_Offset() + value );
	}

	void SimpleQuad::UV_Phsx( Vector2 speed )
	{
		v0.Vertex.uv += speed;
		v1.Vertex.uv += speed;
		v2.Vertex.uv += speed;
		v3.Vertex.uv += speed;
	}

	void SimpleQuad::UVFromBounds( Vector2 BL, Vector2 TR )
	{
		v0.Vertex.uv = Vector2( BL.X, TR.Y );
		v1.Vertex.uv = TR;
		v2.Vertex.uv = BL;
		v3.Vertex.uv = Vector2( TR.X, BL.Y );
	}

	void SimpleQuad::UVFromBounds_2( Vector2 BL, Vector2 TR )
	{
		v0.Vertex.uv = BL;
		v1.Vertex.uv = Vector2( TR.X, BL.Y );
		v2.Vertex.uv = Vector2( BL.X, TR.Y );
		v3.Vertex.uv = TR;
	}

	void SimpleQuad::Init()
	{
		UseGlobalIllumination = true;
		Illumination = 1;

		BlendAddRatio = 0;
		SetColor( Color::White );

		DefaultCorners();

		uv0 = v0.Vertex.uv = Vector2( 0, 0 );
		uv1 = v1.Vertex.uv = Vector2( 1, 0 );
		uv2 = v2.Vertex.uv = Vector2( 0, 1 );
		uv3 = v3.Vertex.uv = Vector2( 1, 1 );
	}

	void SimpleQuad::DefaultCorners()
	{
		v0.Pos = Vector2( -1, 1 );
		v1.Pos = Vector2( 1, 1 );
		v2.Pos = Vector2( -1, -1 );
		v3.Pos = Vector2( 1, -1 );

		v0.Vertex.xy = Vector2( -1, 1 );
		v1.Vertex.xy = Vector2( 1, 1 );
		v2.Vertex.xy = Vector2( -1, -1 );
		v3.Vertex.xy = Vector2( 1, -1 );
	}

	bool SimpleQuad::IsDefault()
	{
		if ( v0.Pos != Vector2( -1, 1 ) )
			return false;
		if ( v1.Pos != Vector2( 1, 1 ) )
			return false;
		if ( v2.Pos != Vector2( -1, -1 ) )
			return false;
		if ( v3.Pos != Vector2( 1, -1 ) )
			return false;

		if ( uv0 != Vector2( 0, 0 ) )
			return false;
		if ( uv1 != Vector2( 1, 0 ) )
			return false;
		if ( uv2 != Vector2( 0, 1 ) )
			return false;
		if ( uv3 != Vector2( 1, 1 ) )
			return false;

		if ( v0.Vertex.uv != Vector2( 0, 0 ) )
			return false;
		if ( v1.Vertex.uv != Vector2( 1, 0 ) )
			return false;
		if ( v2.Vertex.uv != Vector2( 0, 1 ) )
			return false;
		if ( v3.Vertex.uv != Vector2( 1, 1 ) )
			return false;

		return true;
	}

	void SimpleQuad::UpdatedShift( Vector2 shift )
	{
		v0.Vertex.xy += shift;
		v1.Vertex.xy += shift;
		v2.Vertex.xy += shift;
		v3.Vertex.xy += shift;
	}

	void SimpleQuad::CopyUpdate( SimpleQuad &SourceQuad, Vector2 &shift )
	{
		v0.Vertex.xy = SourceQuad.v0.Vertex.xy + shift;
		v1.Vertex.xy = SourceQuad.v1.Vertex.xy + shift;
		v2.Vertex.xy = SourceQuad.v2.Vertex.xy + shift;
		v3.Vertex.xy = SourceQuad.v3.Vertex.xy + shift;
	}

	void SimpleQuad::UpdateShift( BasePoint &Base )
	{
		v0.Vertex.xy = Base.Origin + PreCalc0;
		v1.Vertex.xy = Base.Origin + PreCalc1;
		v2.Vertex.xy = Base.Origin + PreCalc2;
		v3.Vertex.xy = Base.Origin + PreCalc3;
	}

	void SimpleQuad::UpdateShift_Precalc( BasePoint &Base )
	{
		PreCalc0 = v0.Pos.X * Base.e1 + v0.Pos.Y * Base.e2;
		PreCalc1 = v1.Pos.X * Base.e1 + v1.Pos.Y * Base.e2;
		PreCalc2 = v2.Pos.X * Base.e1 + v2.Pos.Y * Base.e2;
		PreCalc3 = v3.Pos.X * Base.e1 + v3.Pos.Y * Base.e2;
	}

	void SimpleQuad::Update( BasePoint &Base )
	{
		v0.Vertex.xy = Base.Origin + v0.Pos.X * Base.e1 + v0.Pos.Y * Base.e2;
		v1.Vertex.xy = Base.Origin + v1.Pos.X * Base.e1 + v1.Pos.Y * Base.e2;
		v2.Vertex.xy = Base.Origin + v2.Pos.X * Base.e1 + v2.Pos.Y * Base.e2;
		v3.Vertex.xy = Base.Origin + v3.Pos.X * Base.e1 + v3.Pos.Y * Base.e2;
	}

	void SimpleQuad::SymmetricUpdate( BasePoint &Base )
	{
		Vector2 x = v0.Pos.X * Base.e1;
		Vector2 y = v0.Pos.Y * Base.e2;
		v0.Vertex.xy = Base.Origin + x + y;
		v1.Vertex.xy = Base.Origin - x + y;
		v2.Vertex.xy = Base.Origin + x - y;
		v3.Vertex.xy = Base.Origin - x - y;
	}

	void SimpleQuad::SetHold()
	{
		v0.AnimData.Hold = v0.Pos;
		v1.AnimData.Hold = v1.Pos;
		v2.AnimData.Hold = v2.Pos;
		v3.AnimData.Hold = v3.Pos;
	}

	void SimpleQuad::ReadAnim( int anim, int frame )
	{
		v0.Pos = v0.AnimData.Get( anim, frame );
		v1.Pos = v1.AnimData.Get( anim, frame );
		v2.Pos = v2.AnimData.Get( anim, frame );
		v3.Pos = v3.AnimData.Get( anim, frame );
	}

	void SimpleQuad::Transfer( int anim, float DestT, int AnimLength, bool Loop, bool Linear, float t )
	{
		v0.Pos = v0.AnimData.Transfer( anim, DestT, AnimLength, Loop, Linear, t );
		v1.Pos = v1.AnimData.Transfer( anim, DestT, AnimLength, Loop, Linear, t );
		v2.Pos = v2.AnimData.Transfer( anim, DestT, AnimLength, Loop, Linear, t );
		v3.Pos = v3.AnimData.Transfer( anim, DestT, AnimLength, Loop, Linear, t );
	}

	void SimpleQuad::Calc( int anim, float t, int AnimLength, bool Loop, bool Linear )
	{
		v0.Pos = v0.AnimData.Calc( anim, t, AnimLength, Loop, Linear );
		v1.Pos = v1.AnimData.Calc( anim, t, AnimLength, Loop, Linear );
		v2.Pos = v2.AnimData.Calc( anim, t, AnimLength, Loop, Linear );
		v3.Pos = v3.AnimData.Calc( anim, t, AnimLength, Loop, Linear );
	}

	void SimpleQuad::SetColor( Color color )
	{
		SetColor( color, false );
	}

	void SimpleQuad::SetColor( Color color, bool ForceUpdate )
	{
		if ( !ForceUpdate && color == MySetColor )
			return;

		MySetColor = color;

		PremultipliedColor = ColorHelper::PremultiplyAlpha( color, BlendAddRatio );

		v0.Vertex.Color = PremultipliedColor;
		v1.Vertex.Color = PremultipliedColor;
		v2.Vertex.Color = PremultipliedColor;
		v3.Vertex.Color = PremultipliedColor;
	}

	void SimpleQuad::SetColor( Vector4 color )
	{
		SetColor( Color( color ) );
	}

	void SimpleQuad::SetAlpha( float alpha )
	{
		if ( alpha < 0 )
			alpha = 0;
		if ( alpha > 1 )
			alpha = 1;

		Color color = MySetColor;
		color.A = static_cast<unsigned char>( alpha * 255 );
		SetColor( color );
	}

	void SimpleQuad::MultiplyAlpha( float alpha )
	{
		Color color = MySetColor;
		color.A = static_cast<unsigned char>( alpha * color.A );
		SetColor( color );
	}
}
