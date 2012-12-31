#include <global_header.h>

#include <Core.h>
#include <Content/Wad.h>
#include <Graphics/Types.h>
#include <Graphics/QuadDrawer.h>
#include <Utility/Log.h>

#include "Hacks/XNA/SamplerState.h"

namespace CloudberryKingdom
{

	void QuadDrawer::InitializeStatics()
	{
		QuadDrawer::CurLightSourceFade = 0;
	}

	// Statics
	float QuadDrawer::CurLightSourceFade;


	const Matrix &QuadDrawer::getCurrentMatrix() const
	{
		return _CurrentMatrix;
	}

	void QuadDrawer::setCurrentMatrix( const Matrix &value )
	{
		_CurrentMatrix = value;
		CurrentMatrixSignature = ColorHelper::MatrixSignature( _CurrentMatrix );
	}

	const float &QuadDrawer::getGlobalIllumination() const
	{
		return _GlobalIllumination;
	}

	void QuadDrawer::setGlobalIllumination( const float &value )
	{
		_GlobalIllumination = value;
	}

	QuadDrawer::QuadDrawer( const boost::shared_ptr<GraphicsDevice> &device, int n )
	{
		InitializeInstanceFields();
		Device = device;
		N = n;

		TrianglesInBuffer = 0;
		i = 0;
		Vertices = std::vector<MyOwnVertexFormat>( N );

		LineQuad = SimpleQuad();
		LineQuad.Init();

		WrapWrap = boost::make_shared<SamplerState>();
		WrapWrap->AddressU = GfxTextureAddressMode_Wrap;
		WrapWrap->AddressV = GfxTextureAddressMode_Wrap;

		ClampClamp = boost::make_shared<SamplerState>();
		ClampClamp->AddressU = GfxTextureAddressMode_Clamp;
		ClampClamp->AddressV = GfxTextureAddressMode_Clamp;

		ClampWrap = boost::make_shared<SamplerState>();
		ClampWrap->AddressU = GfxTextureAddressMode_Clamp;
		ClampWrap->AddressV = GfxTextureAddressMode_Wrap;

		WrapClamp = boost::make_shared<SamplerState>();
		WrapClamp->AddressU = GfxTextureAddressMode_Wrap;
		WrapClamp->AddressV = GfxTextureAddressMode_Clamp;
	}

	void QuadDrawer::SetColorMatrix( Matrix m, float signature )
	{
		if ( CurrentMatrixSignature != signature )
		{
			Flush();

			CurrentMatrixSignature = signature;
			setCurrentMatrix( m );

			Tools::HslEffect->Hsl->SetValue( getCurrentMatrix() );
		}
	}

	void QuadDrawer::DrawQuad( const boost::shared_ptr<Quad> &quad )
	{
		if ( i + 6 > N || i != 0 && ( CurrentEffect->effect != quad->MyEffect->effect || CurrentTexture->getTex() != quad->MyTexture->getTex() || CurrentMatrixSignature != quad->MyMatrixSignature ) )
			Flush();

		if ( i == 0 )
		{
			CurrentEffect = quad->MyEffect;
			QUAD_DRAWER->SetEffect( quad->MyEffect->effect );
			CurrentTexture = quad->MyTexture;
			setCurrentMatrix( quad->getMyMatrix() );
		}
		CurrentEffect->CurrentIllumination = 1;
		CurrentEffect->Illumination->SetValue( 1.f );


		/*Vertices[ i ] = quad->Vertices[ 0 ];
		Vertices[ i + 1 ] = quad->Vertices[ 1 ];
		Vertices[ i + 2 ] = quad->Vertices[ 2 ];

		Vertices[ i + 3 ] = quad->Vertices[ 3 ];
		Vertices[ i + 4 ] = quad->Vertices[ 2 ];
		Vertices[ i + 5 ] = quad->Vertices[ 1 ];

		i += 6;
		TrianglesInBuffer += 2;*/

		::SimpleQuad sq;
		sq.V[0] = Vector2( quad->Vertices[ 0 ].xy.X, quad->Vertices[ 0 ].xy.Y );
		sq.V[1] = Vector2( quad->Vertices[ 1 ].xy.X, quad->Vertices[ 1 ].xy.Y );
		sq.V[3] = Vector2( quad->Vertices[ 2 ].xy.X, quad->Vertices[ 2 ].xy.Y );
		sq.V[2] = Vector2( quad->Vertices[ 3 ].xy.X, quad->Vertices[ 3 ].xy.Y );

		sq.T[0] = Vector2( quad->Vertices[ 0 ].uv.X, quad->Vertices[ 0 ].uv.Y );
		sq.T[1] = Vector2( quad->Vertices[ 1 ].uv.X, quad->Vertices[ 1 ].uv.Y );
		sq.T[3] = Vector2( quad->Vertices[ 2 ].uv.X, quad->Vertices[ 2 ].uv.Y );
		sq.T[2] = Vector2( quad->Vertices[ 3 ].uv.X, quad->Vertices[ 3 ].uv.Y );

		sq.Color = quad->Vertices[ 0 ].TheColor.ToVector4();

		sq.Diffuse = quad->MyTexture->getTex()->texture_;
		QUAD_DRAWER->Draw( sq );
	}

	void QuadDrawer::SetInitialState()
	{
		Device->SamplerStates[ 0 ] = ClampClamp;
		Device->SamplerStates[ 1 ] = ClampClamp;
		Device->SamplerStates[ 2 ] = ClampClamp;
	}

	void QuadDrawer::SetSamplerState()
	{
		//Device.SamplerStates[1] = ClampClamp;
		//return;

		if ( Current_U_Wrap )
		{
			if ( Current_V_Wrap )
				Device->SamplerStates[ 1 ] = WrapWrap;
			else
				Device->SamplerStates[ 1 ] = WrapClamp;
		}
		else
		{
			if ( Current_V_Wrap )
				Device->SamplerStates[ 1 ] = ClampWrap;
			else
				Device->SamplerStates[ 1 ] = ClampClamp;
		}
	}

	void QuadDrawer::SetAddressMode( bool U_Wrap, bool V_Wrap )
	{
		Current_U_Wrap = U_Wrap;
		Current_V_Wrap = V_Wrap;
		SetSamplerState();
	}

	void QuadDrawer::DrawQuad_Particle( SimpleQuad &quad )
	{
		// Update anim
		if ( quad.Playing )
			quad.UpdateTextureAnim();

		// Calculate illumination
		if ( quad.UseGlobalIllumination )
			Illumination = getGlobalIllumination() * quad.Illumination;
		else
			Illumination = quad.Illumination;

		if ( i + 6 >= N || CurrentEffect->effect != quad.MyEffect->effect
			|| CurrentTexture->getTex() != quad.getMyTexture()->getTex()
			&& !quad.getMyTexture()->FromPacked
			|| CurrentTexture != quad.getMyTexture()->Packed
			&& quad.getMyTexture()->FromPacked
			|| CurrentEffect->CurrentIllumination != Illumination )
			Flush();

		if ( i == 0 )
		{
			if ( Current_U_Wrap != quad.U_Wrap || Current_V_Wrap != quad.V_Wrap )
				SetAddressMode( false, false );

			CurrentEffect = quad.MyEffect;
			QUAD_DRAWER->SetEffect( quad.MyEffect->effect );
			CurrentTexture = quad.getMyTexture();

			if ( CurrentTexture->FromPacked )
				CurrentTexture = CurrentTexture->Packed;

			if ( CurrentEffect->CurrentIllumination != Illumination )
			{
				CurrentEffect->CurrentIllumination = Illumination;
				CurrentEffect->Illumination->SetValue( Illumination );
			}
		}

		/*Vertices[ i ] = quad.v0.Vertex;
		Vertices[ i + 1 ] = quad.v1.Vertex;
		Vertices[ i + 5 ] = Vertices[ i + 1 ];
		Vertices[ i + 2 ] = quad.v2.Vertex;
		Vertices[ i + 4 ] = Vertices[ i + 2 ];
		Vertices[ i + 3 ] = quad.v3.Vertex;

		i += 6;
		TrianglesInBuffer += 2;*/

		::SimpleQuad sq;
		sq.V[0] = Vector2( quad.v0.Vertex.xy.X, quad.v0.Vertex.xy.Y );
		sq.V[1] = Vector2( quad.v1.Vertex.xy.X, quad.v1.Vertex.xy.Y );
		sq.V[3] = Vector2( quad.v2.Vertex.xy.X, quad.v2.Vertex.xy.Y );
		sq.V[2] = Vector2( quad.v3.Vertex.xy.X, quad.v3.Vertex.xy.Y );

		sq.T[0] = Vector2( quad.v0.Vertex.uv.X, quad.v0.Vertex.uv.Y );
		sq.T[1] = Vector2( quad.v1.Vertex.uv.X, quad.v1.Vertex.uv.Y );
		sq.T[3] = Vector2( quad.v2.Vertex.uv.X, quad.v2.Vertex.uv.Y );
		sq.T[2] = Vector2( quad.v3.Vertex.uv.X, quad.v3.Vertex.uv.Y );

		sq.Color = quad.v0.Vertex.TheColor.ToVector4();

		sq.Diffuse = quad.getMyTexture()->getTex()->texture_;
		QUAD_DRAWER->Draw( sq );
	}

	void QuadDrawer::DrawQuad( SimpleQuad &quad )
	{
		if ( quad.Hide )
			return;

		if ( quad.MyEffect == 0 || quad.getMyTexture() == 0 )
		{
			Tools::Break();
			return;
		}

		if ( Tools::Render->UsingSpriteBatch )
			Tools::Render->EndSpriteBatch();

		// Update anim
		if ( quad.Playing )
			quad.UpdateTextureAnim();

		// Calculate illumination
		if ( quad.UseGlobalIllumination )
			Illumination = getGlobalIllumination() * quad.Illumination;
		else
			Illumination = quad.Illumination;

		if (
			//i + 6 >= N || i != 0
			//&&
			( CurrentTexture != 0 && CurrentEffect != 0 ) &&
			( CurrentEffect->effect != quad.MyEffect->effect
				|| CurrentTexture->getTex() != quad.getMyTexture()->getTex()
				&& !quad.getMyTexture()->FromPacked
				|| CurrentTexture != quad.getMyTexture()->Packed
				&& quad.getMyTexture()->FromPacked
				|| Current_U_Wrap != quad.U_Wrap
				|| Current_V_Wrap != quad.V_Wrap
				|| CurrentEffect->CurrentIllumination != Illumination ) )
			Flush();

		if ( i == 0 )
		{
			if ( Current_U_Wrap != quad.U_Wrap || Current_V_Wrap != quad.V_Wrap )
				SetAddressMode( quad.U_Wrap, quad.V_Wrap );

			CurrentEffect = quad.MyEffect;
			
			// FIXME: HEHEHE.
			QUAD_DRAWER->SetEffect( quad.MyEffect->effect );
			//CurrentEffect->SetCameraParameters();

			CurrentTexture = quad.getMyTexture();

			// Set extra textures
			if ( quad.ExtraTexture1 != 0 )
				CurrentEffect->SetExtraTexture1( quad.ExtraTexture1 );
			if ( quad.ExtraTexture2 != 0 )
				CurrentEffect->SetExtraTexture2( quad.ExtraTexture2 );

			if ( CurrentTexture->FromPacked )
				CurrentTexture = CurrentTexture->Packed;

			if ( CurrentEffect->CurrentIllumination != Illumination )
			{
				CurrentEffect->CurrentIllumination = Illumination;
				CurrentEffect->Illumination->SetValue( Illumination );
			}
		}

		::SimpleQuad sq;
		sq.V[0] = Vector2( quad.v0.Vertex.xy.X, quad.v0.Vertex.xy.Y );
		sq.V[1] = Vector2( quad.v1.Vertex.xy.X, quad.v1.Vertex.xy.Y );
		sq.V[3] = Vector2( quad.v2.Vertex.xy.X, quad.v2.Vertex.xy.Y );
		sq.V[2] = Vector2( quad.v3.Vertex.xy.X, quad.v3.Vertex.xy.Y );

		/*for( int j = 0; j < 4; ++j )
		{
			sq.V[ j ] /= 1822.45f;
			sq.V[ j ] += Vector2( 1 );
			sq.V[ j ] /= 2.f;
			sq.V[ j ] *= Vector2( 1280.f, 720.f );
			sq.V[ j ].Y = 720.f - sq.V[ j ].Y;
		}*/

		sq.T[0] = Vector2( quad.v0.Vertex.uv.X, quad.v0.Vertex.uv.Y );
		sq.T[1] = Vector2( quad.v1.Vertex.uv.X, quad.v1.Vertex.uv.Y );
		sq.T[3] = Vector2( quad.v2.Vertex.uv.X, quad.v2.Vertex.uv.Y );
		sq.T[2] = Vector2( quad.v3.Vertex.uv.X, quad.v3.Vertex.uv.Y );

		sq.Color = quad.v0.Vertex.TheColor.ToVector4();

		sq.Diffuse = quad.getMyTexture()->getTex()->texture_;
		QUAD_DRAWER->Draw( sq );

		/*Vertices[ i ] = quad.v0.Vertex;
		Vertices[ i + 1 ] = quad.v1.Vertex;
		Vertices[ i + 5 ] = Vertices[ i + 1 ];
		Vertices[ i + 2 ] = quad.v2.Vertex;
		Vertices[ i + 4 ] = Vertices[ i + 2 ];
		Vertices[ i + 3 ] = quad.v3.Vertex;

		i += 6;
		TrianglesInBuffer += 2;*/
	}

	void QuadDrawer::DrawFilledBox( Vector2 BL, Vector2 TR, Color color )
	{
		LineQuad.MyEffect = DefaultEffect;
		LineQuad.MyEffect = Tools::BasicEffect;
		LineQuad.setMyTexture( DefaultTexture );

		color = ColorHelper::PremultiplyAlpha( color );

		LineQuad.v0.Vertex.xy = Vector2( BL.X, TR.Y );
		LineQuad.v0.Vertex.TheColor = color;
		LineQuad.v1.Vertex.xy = TR;
		LineQuad.v1.Vertex.TheColor = color;
		LineQuad.v2.Vertex.xy = BL;
		LineQuad.v2.Vertex.TheColor = color;
		LineQuad.v3.Vertex.xy = Vector2( TR.X, BL.Y );
		LineQuad.v3.Vertex.TheColor = color;

		LineQuad.v0.Vertex.uv = Vector2( 0, 0 );
		LineQuad.v1.Vertex.uv = Vector2( 1, 0 );
		LineQuad.v2.Vertex.uv = Vector2( 0, 1 );
		LineQuad.v3.Vertex.uv = Vector2( 1, 1 );

		DrawQuad( LineQuad );
	}

	void QuadDrawer::DrawLine( Vector2 x1, Vector2 x2, const boost::shared_ptr<LineSpriteInfo> &info )
	{
		if ( info->DrawEndPoints )
			DrawLineAndEndPoints( x1, x2, Color( info->Tint ), info->Width, info->End1->MyTexture, info->Sprite->MyTexture, info->End2->MyTexture, Tools::BasicEffect, info->RepeatWidth, info->Dir, 0, 0 );
		else
			DrawLine( x1, x2, Color( info->Tint ), info->Width, info->Sprite->MyTexture, Tools::BasicEffect, info->RepeatWidth, info->Dir, 0, 0, info->Wrap );
	}

	void QuadDrawer::DrawLine( Vector2 x1, Vector2 x2, const boost::shared_ptr<LineSpriteInfo> &info, Vector4 Tint, float Width )
	{
		DrawLine( x1, x2, Color( info->Tint * Tint ), Width, info->Sprite->MyTexture, Tools::BasicEffect, info->RepeatWidth, info->Dir, 0, 0, info->Wrap );
	}

	void QuadDrawer::DrawLine( Vector2 x1, Vector2 x2, const boost::shared_ptr<LineSpriteInfo> &info, Vector4 Tint, float Width, float v_shift )
	{
		DrawLine( x1, x2, Color( info->Tint * Tint ), Width, info->Sprite->MyTexture, Tools::BasicEffect, info->RepeatWidth, info->Dir, 0, v_shift, info->Wrap );
	}

	void QuadDrawer::DrawLine( Vector2 x1, Vector2 x2, Color color, float width )
	{
		DrawLine( x1, x2, color, width, 0, 0, 1, 0, 0, 0, false );
	}

	void QuadDrawer::DrawLine( Vector2 x1, Vector2 x2, Color color, float width, const boost::shared_ptr<EzTexture> &Tex, const boost::shared_ptr<EzEffect> &fx, float RepeatWidth, int Dir, bool Illumination )
	{
		bool Hold = LineQuad.UseGlobalIllumination;
		LineQuad.UseGlobalIllumination = Illumination;
		DrawLine( x1, x2, color, width, Tex, fx, RepeatWidth, Dir, 0, 0, false );
		LineQuad.UseGlobalIllumination = Hold;
	}

	void QuadDrawer::DrawLine( Vector2 x1, Vector2 x2, Color color, float width, const boost::shared_ptr<EzTexture> &Tex, const boost::shared_ptr<EzEffect> &fx, float RepeatWidth, int Dir, float BlendAddRatio )
	{
		DrawLine( x1, x2, color, width, Tex, fx, RepeatWidth, Dir, BlendAddRatio, 0, false );
	}

	void QuadDrawer::DrawLine( Vector2 x1, Vector2 x2, Color color, float width, const boost::shared_ptr<EzTexture> &Tex, const boost::shared_ptr<EzEffect> &fx, float RepeatWidth, int Dir, float BlendAddRatio, float v_shift, bool Wrap )
	{
		color = ColorHelper::PremultiplyAlpha( color );

		Vector2 Tangent = x2 - x1;
		Vector2 Normal = Vector2( Tangent.Y, -Tangent.X );
		Normal.FastNormalize();

		LineQuad.MyEffect = DefaultEffect;
		if ( fx == 0 )
			LineQuad.MyEffect = Tools::EffectWad->EffectList[ 1 ];
		else
			LineQuad.MyEffect = fx;

		if ( Tex == 0 )
		{
			LineQuad.setMyTexture( DefaultTexture );
		}
		else
		{
			LineQuad.setMyTexture( Tex );

			float r = ( x2 - x1 ).Length() / RepeatWidth;
			if ( Dir == 0 )
			{
				LineQuad.v0.Vertex.uv = Vector2( 0, v_shift );
				LineQuad.v1.Vertex.uv = Vector2( 1, v_shift );
				LineQuad.v2.Vertex.uv = Vector2( 0, r + v_shift );
				LineQuad.v3.Vertex.uv = Vector2( 1, r + v_shift );
			}
			if ( Dir == 1 )
			{
				LineQuad.v0.Vertex.uv = Vector2( v_shift, 0 );
				LineQuad.v1.Vertex.uv = Vector2( v_shift, 1 );
				LineQuad.v2.Vertex.uv = Vector2( r + v_shift, 0 );
				LineQuad.v3.Vertex.uv = Vector2( r + v_shift, 1 );
			}
			LineQuad.U_Wrap = LineQuad.V_Wrap = true;
		}

		LineQuad.U_Wrap = LineQuad.V_Wrap = Wrap;

		LineQuad.v0.Vertex.xy = x1 + Normal * width / 2;
		LineQuad.v0.Vertex.TheColor = color;
		LineQuad.v1.Vertex.xy = x1 - Normal * width / 2;
		LineQuad.v1.Vertex.TheColor = color;
		LineQuad.v2.Vertex.xy = x2 + Normal * width / 2;
		LineQuad.v2.Vertex.TheColor = color;
		LineQuad.v3.Vertex.xy = x2 - Normal * width / 2;
		LineQuad.v3.Vertex.TheColor = color;

		LineQuad.BlendAddRatio = BlendAddRatio;

		DrawQuad( LineQuad );

		LineQuad.BlendAddRatio = 0;
	}

	void QuadDrawer::DrawLineAndEndPoints( Vector2 x1, Vector2 x2, Color color, float width, const boost::shared_ptr<EzTexture> &Tex1, const boost::shared_ptr<EzTexture> &Tex2, const boost::shared_ptr<EzTexture> &Tex3, const boost::shared_ptr<EzEffect> &fx, float RepeatWidth, int Dir, float BlendAddRatio, float v_shift )
	{
		color = ColorHelper::PremultiplyAlpha( color );

		Vector2 Tangent = x2 - x1;
		Tangent.FastNormalize();

		Vector2 Mid1 = x1 + Tangent * width / Tex1->getAspectRatio();
		Vector2 Mid2 = x2 - Tangent * width / Tex3->getAspectRatio();

		Vector2 Normal = Vector2( Tangent.Y, -Tangent.X );

		LineQuad.MyEffect = fx;
		LineQuad.v0.Vertex.TheColor = color;
		LineQuad.v1.Vertex.TheColor = color;
		LineQuad.v2.Vertex.TheColor = color;
		LineQuad.v3.Vertex.TheColor = color;
		LineQuad.BlendAddRatio = BlendAddRatio;

		LineQuad.v0.Vertex.uv = Vector2( 0, 1 );
		LineQuad.v1.Vertex.uv = Vector2( 1, 1 );
		LineQuad.v2.Vertex.uv = Vector2( 0, 0 );
		LineQuad.v3.Vertex.uv = Vector2( 1, 0 );

		// Draw end point
		LineQuad.U_Wrap = LineQuad.V_Wrap = false;
		LineQuad.setMyTexture( Tex1 );
		LineQuad.v0.Vertex.xy = x1 + Normal * width / 2;
		LineQuad.v1.Vertex.xy = x1 - Normal * width / 2;
		LineQuad.v2.Vertex.xy = Mid1 + Normal * width / 2;
		LineQuad.v3.Vertex.xy = Mid1 - Normal * width / 2;
		DrawQuad( LineQuad );


		// Draw Body
		float r = ( Mid2 - Mid1 ).Length() / RepeatWidth;
		if ( Dir == 0 )
		{
			LineQuad.v0.Vertex.uv = Vector2( 0, v_shift );
			LineQuad.v1.Vertex.uv = Vector2( 1, v_shift );
			LineQuad.v2.Vertex.uv = Vector2( 0, r + v_shift );
			LineQuad.v3.Vertex.uv = Vector2( 1, r + v_shift );
		}
		if ( Dir == 1 )
		{
			LineQuad.v0.Vertex.uv = Vector2( v_shift, 0 );
			LineQuad.v1.Vertex.uv = Vector2( v_shift, 1 );
			LineQuad.v2.Vertex.uv = Vector2( r + v_shift, 0 );
			LineQuad.v3.Vertex.uv = Vector2( r + v_shift, 1 );
		}
		LineQuad.U_Wrap = LineQuad.V_Wrap = true;

		LineQuad.setMyTexture( Tex2 );
		LineQuad.v0.Vertex.xy = Mid1 + Normal * width / 2;
		LineQuad.v1.Vertex.xy = Mid1 - Normal * width / 2;
		LineQuad.v2.Vertex.xy = Mid2 + Normal * width / 2;
		LineQuad.v3.Vertex.xy = Mid2 - Normal * width / 2;
		DrawQuad( LineQuad );


		// Draw end point
		LineQuad.U_Wrap = LineQuad.V_Wrap = false;
		LineQuad.v0.Vertex.uv = Vector2( 0, 1 );
		LineQuad.v1.Vertex.uv = Vector2( 1, 1 );
		LineQuad.v2.Vertex.uv = Vector2( 0, 0 );
		LineQuad.v3.Vertex.uv = Vector2( 1, 0 );

		LineQuad.setMyTexture( Tex3 );
		LineQuad.v0.Vertex.xy = Mid2 + Normal * width / 2;
		LineQuad.v1.Vertex.xy = Mid2 - Normal * width / 2;
		LineQuad.v2.Vertex.xy = x2 + Normal * width / 2;
		LineQuad.v3.Vertex.xy = x2 - Normal * width / 2;
		DrawQuad( LineQuad );

		LineQuad.BlendAddRatio = 0;
	}

	void QuadDrawer::DrawCircle( Vector2 x, float r, Color color )
	{
		DrawSquareDot( x, color, 2 * r, DefaultTexture, Tools::CircleEffect );
	}

	void QuadDrawer::DrawLightSource( Vector2 x, float r, float Fade, Color color )
	{
		if ( Fade != CurLightSourceFade )
		{
			Tools::LightSourceEffect->effect->Parameters( "Fade" )->SetValue( Fade );
			CurLightSourceFade = Fade;
		}
		DrawSquareDot( x, color, 2 * r, DefaultTexture, Tools::LightSourceEffect );
	}

	void QuadDrawer::DrawSquareDot( Vector2 x, Color color, float width )
	{
		DrawSquareDot( x, color, width, 0, 0 );
	}

	void QuadDrawer::DrawSquareDot( Vector2 x, Color color, float width, const boost::shared_ptr<EzTexture> &Tex, const boost::shared_ptr<EzEffect> &fx )
	{
		color = ColorHelper::PremultiplyAlpha( color );

		LineQuad.MyEffect = DefaultEffect;
		if ( fx == 0 )
			LineQuad.MyEffect = Tools::EffectWad->EffectList[ 2 ];
		else
			LineQuad.MyEffect = fx;

		if ( Tex == 0 )
		{
			LineQuad.setMyTexture( DefaultTexture );
		}
		else
		{
			LineQuad.setMyTexture( Tex );
		}

		LineQuad.v0.Vertex.xy = x + Vector2( -1, 1 ) * width / 2;
		LineQuad.v0.Vertex.TheColor = color;
		LineQuad.v1.Vertex.xy = x + Vector2( 1, 1 ) * width / 2;
		LineQuad.v1.Vertex.TheColor = color;
		LineQuad.v2.Vertex.xy = x + Vector2( -1, -1 ) * width / 2;
		LineQuad.v2.Vertex.TheColor = color;
		LineQuad.v3.Vertex.xy = x + Vector2( 1, -1 ) * width / 2;
		LineQuad.v3.Vertex.TheColor = color;

		LineQuad.v0.Vertex.uv = Vector2( 0, 0 );
		LineQuad.v1.Vertex.uv = Vector2( 1, 0 );
		LineQuad.v2.Vertex.uv = Vector2( 0, 1 );
		LineQuad.v3.Vertex.uv = Vector2( 1, 1 );

		LineQuad.U_Wrap = LineQuad.V_Wrap = false;

		DrawQuad( LineQuad );
	}

	void QuadDrawer::DrawToScaleQuad( Vector2 x, Color color, float width )
	{
		DrawToScaleQuad( x, color, width, 0, 0 );
	}

	void QuadDrawer::DrawToScaleQuad( Vector2 x, Color color, float width, const boost::shared_ptr<EzTexture> &Tex, const boost::shared_ptr<EzEffect> &fx )
	{
		color = ColorHelper::PremultiplyAlpha( color );

		LineQuad.MyEffect = DefaultEffect;
		if ( fx == 0 )
			LineQuad.MyEffect = Tools::EffectWad->EffectList[ 2 ];
		else
			LineQuad.MyEffect = fx;

		if ( Tex == 0 )
		{
			LineQuad.setMyTexture( DefaultTexture );
		}
		else
		{
			LineQuad.setMyTexture( Tex );
		}

		float a = width / LineQuad.getMyTexture()->getAspectRatio();

		LineQuad.v0.Vertex.xy = x + Vector2( -width, a ) / 2;
		LineQuad.v0.Vertex.TheColor = color;
		LineQuad.v1.Vertex.xy = x + Vector2( width, a ) / 2;
		LineQuad.v1.Vertex.TheColor = color;
		LineQuad.v2.Vertex.xy = x + Vector2( -width, -a ) / 2;
		LineQuad.v2.Vertex.TheColor = color;
		LineQuad.v3.Vertex.xy = x + Vector2( width, -a ) / 2;
		LineQuad.v3.Vertex.TheColor = color;

		LineQuad.v0.Vertex.uv = Vector2( 0, 0 );
		LineQuad.v1.Vertex.uv = Vector2( 1, 0 );
		LineQuad.v2.Vertex.uv = Vector2( 0, 1 );
		LineQuad.v3.Vertex.uv = Vector2( 1, 1 );


		DrawQuad( LineQuad );
	}

	void QuadDrawer::DrawBox( Vector2 BL, Vector2 TR, Color color, float width )
	{
		Vector2 BR = Vector2( TR.X, BL.Y );
		Vector2 TL = Vector2( BL.X, TR.Y );
		Vector2 Offset = Vector2( Sign( TR.X - BL.X ) * width / 2, 0 );

		DrawLine( BL - Offset, BR + Offset, color, width );
		DrawLine( BR, TR, color, width );
		DrawLine( TR + Offset, TL - Offset, color, width );
		DrawLine( TL, BL, color, width );
	}

	void QuadDrawer::SetToDefaultTexture()
	{
		Flush();
		CurrentTexture = DefaultTexture;
		CurrentEffect->xTexture->SetValue( CurrentTexture->getTex() );
	}

	void QuadDrawer::WashTexture()
	{
		CurrentTexture = Tools::TextureWad->DefaultTexture;
	}

	void QuadDrawer::Flush()
	{
		if ( CurrentTexture != 0 )
		{
			CurrentEffect->SetCameraParameters();
			CurrentEffect->Hsl->SetValue( getCurrentMatrix() );
		}

		QUAD_DRAWER->Flush();
		return; // FIXME: We shoudl not return.
	//#if DEBUG
	//            if (Device.SamplerStates[1] == null) Tools.Write("!");
	//            if (Device.SamplerStates[1] != ClampClamp) Tools.Write("!");
	//#endif

		//if (CurrentTexture != null)
		if ( CurrentTexture != 0 && i > 0 )
		{
			CurrentEffect->xTexture->SetValue( CurrentTexture->getTex() );
			CurrentEffect->Hsl->SetValue( getCurrentMatrix() );

			// Test HSV transform
			//CurrentEffect.Hsl.SetValue(ColorHelper.HsvTransform(Tools.Num_0_to_2, 1f, Tools.Num_0_to_360));

			if ( !CurrentEffect->IsUpToDate )
				CurrentEffect->SetCameraParameters();

			//if (i > 0)
				{
				CurrentEffect->effect->CurrentTechnique->Passes[ 0 ]->Apply();

				/*Device->DrawUserPrimitives<MyOwnVertexFormat>( GfxPrimitiveType_TriangleList, Vertices, 0, TrianglesInBuffer );*/
				Device->DrawUserPrimitives( GfxPrimitiveType_TriangleList, Vertices, 0, TrianglesInBuffer );
				}
		}

		TrianglesInBuffer = 0;
		i = 0;

		QUAD_DRAWER->Flush();
	}

	void QuadDrawer::InitializeInstanceFields()
	{
		CurrentMatrixSignature = 0;
	
		Current_U_Wrap = false; Current_V_Wrap = false;
	
		N = 0;
		TrianglesInBuffer = 0;
	
		i = 0;

		_GlobalIllumination = 1;
		Illumination = 1;
	}
}
