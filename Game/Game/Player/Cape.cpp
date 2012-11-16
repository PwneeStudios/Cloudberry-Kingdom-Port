#include "Cape.h"
#include "Game/Objects/Bob/Bob.h"
#include "Core/Graphics/VertexFormat.h"
#include "Core/Graphics/Draw/Quads/QuadClass.h"
#include "Core/Tools/ColorHelper.h"
#include "Game/Player/Hero Physics/Base.h"
#include "Game/Tools/Tools.h"
#include "Core/Effects/EzEffect.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
using namespace Microsoft::Xna::Framework::Graphics;
using namespace Microsoft::Xna::Framework;

namespace CloudberryKingdom
{

	void CapeLink::Init()
	{
		Show = true;
	}

	Microsoft::Xna::Framework::Vector2 Cape::SineWind( Vector2 Dir, float NormalIntensity, float Period, float t )
	{
		Vector2 Normal = Vector2( -Dir.Y, Dir.X );
		return Dir + NormalIntensity * Normal * static_cast<float>( sin( t / Period ) );
	}

	void Cape::Copy( const std::shared_ptr<Cape> &cape )
	{
		for ( int i = 0; i < Nodes.size(); i++ )
			Nodes[ i ] = cape->Nodes[ i ];

		for ( int i = 0; i < Links.size(); i++ )
			Links[ i ] = cape->Links[ i ];
	}

	void Cape::setMyColor( const Color &value )
	{
		SetColor( value );
	}

	const Microsoft::Xna::Framework::Color &Cape::getMyColor() const
	{
		return _MyColor;
	}

	void Cape::setMyOutlineColor( const Color &value )
	{
		SetOutlineColor( value );
	}

	const Microsoft::Xna::Framework::Color &Cape::getMyOutlineColor() const
	{
		return _MyOutlineColor;
	}

	void Cape::Release()
	{
		MyBob.reset();

		Vertices.clear();
		Nodes.clear();
		Links.clear();

		if ( MyQuad != 0 )
			MyQuad->Release();
			MyQuad.reset();
	}

	void Cape::SetOutlineColor( Color clr )
	{
		if ( clr == _MyOutlineColor )
			return;

		_MyOutlineColor = clr;
	}

	void Cape::SetColor( Color clr )
	{
		if ( clr == getMyColor() )
			return;

		_MyColor = clr;
		Color PremultipliedColor = ColorHelper::PremultiplyAlpha( clr );
		Color PremultipliedColor_Darker = ColorHelper::PremultiplyAlpha( Color( clr.ToVector3() *.5f ) );

		int count = 0;
		// Triangles
		float h2 = 1 / Sections;
		float h1 = 1 / HorizontalSections;
		for ( int i = Sections - 1; i >= 0; i-- )
		{
			for ( int j = 0; j < HorizontalSections; j++ )
			{
				Vertices[ count ].Color = PremultipliedColor_Darker;
				Vertices[ count ].uv = Vector2( j * h1, i * h2 );

				Vertices[ count + 1 ].Color = PremultipliedColor;
				Vertices[ count + 1 ].uv = Vector2( ( j + 1 ) * h1, i * h2 );

				Vertices[ count + 2 ].Color = PremultipliedColor_Darker;
				Vertices[ count + 2 ].uv = Vector2( j * h1, ( i + 1 ) * h2 );

				Vertices[ count + 3 ].Color = PremultipliedColor;
				Vertices[ count + 3 ].uv = Vector2( ( j + 1 ) * h1, ( i + 1 ) * h2 );

				Vertices[ count + 5 ].Color = PremultipliedColor;
				Vertices[ count + 5 ].uv = Vector2( ( j + 1 ) * h1, i * h2 );

				Vertices[ count + 4 ].Color = PremultipliedColor_Darker;
				Vertices[ count + 4 ].uv = Vector2( j * h1, ( i + 1 ) * h2 );

				count += 6;
			}
		}
	}

	void Cape::Move( Vector2 Shift )
	{
		for ( int i = 0; i < Nodes.size(); i++ )
		{
			Nodes[ i ].Data.Position += Shift;
		}

		UpdateTriangles();
	}

	void Cape::ModVel_Add( Vector2 Mod )
	{
		for ( int i = 0; i < Nodes.size(); i++ )
			Nodes[ i ].Data.Velocity += Mod;
	}

	void Cape::ModVel_Mult( Vector2 Mod )
	{
		for ( int i = 0; i < Nodes.size(); i++ )
			Nodes[ i ].Data.Velocity *= Mod;
	}

	void Cape::Reset()
	{
		for ( int i = 0; i < Nodes.size(); i++ )
		{
			Nodes[ i ].Data = Nodes[ i ].StartData;
			Nodes[ i ].Data.Position += AnchorPoint[ 0 ];
		}
	}

	Cape::Cape( const std::shared_ptr<Bob> &bob, CapeType Type, const std::shared_ptr<BobPhsx> &Phsx_Renamed )
	{
		InitializeInstanceFields();
		MyBob = bob;
		MyType = Type;

		MaxForce = .9f;
		Sections = 5;
		HorizontalSections = 1;
		PhsxSteps = 1;
		strength_in = .16f / 1.6f;
		strength_out = 0;
		float cross_strength_out = .005f; // 1.8f;
		float cross_strength_in = 0.11f;
		float horizontal_strength_out = .005f; // 1.8f;
		float horizontal_strength_in = 0.11f;
		Retard = .935f;
		Gravity = Vector2( 0, -1.45f ) / 1.45f;
		float Weight = 1.6f / Sections;

		DrawLines = true;
		DrawNodes = true;

		CapeThickness = Phsx_Renamed->MyBob->PlayerObject->CapeThickness;
		p1_Left = Phsx_Renamed->MyBob->PlayerObject->p1_Left;
		p2_Left = Phsx_Renamed->MyBob->PlayerObject->p2_Left;
		p1_Right = Phsx_Renamed->MyBob->PlayerObject->p1_Right;
		p2_Right = Phsx_Renamed->MyBob->PlayerObject->p2_Right;

		switch ( Type )
		{
			case CapeType_SMALL:
				strength_in *= 1.5f;
				p2_Left = Vector2( -17, -2 );
				p1_Left = Vector2( -34, -25 );
				p2_Right = Vector2( 17, -2 );
				p1_Right = Vector2( 34, -25 );
				break;
		}

		p2_Left *= Phsx_Renamed->ModCapeSize;
		p1_Left *= Phsx_Renamed->ModCapeSize;
		p2_Right *= Phsx_Renamed->ModCapeSize;
		p1_Right *= Phsx_Renamed->ModCapeSize;
		strength_in *= 1 / ( .5f * ( Phsx_Renamed->ModCapeSize.X - 1 ) + 1 );


		MyQuad = std::make_shared<QuadClass>();
		MyQuad->SetToDefault();
		//MyQuad.Quad.MyTexture = Tools.TextureWad.FindByName("FallingBlock13");//"White");
		//MyQuad.Quad.MyEffect = Tools.BasicEffect;


		//NumTriangles = 4 * Sections * HorizontalSections;
		NumTriangles = 2 * Sections * HorizontalSections;
		NumVertices = 3 * NumTriangles;
		Vertices = std::vector<MyOwnVertexFormat>( NumVertices );


		Nodes = std::vector<CapeNode>( ( 1 + 1 * Sections ) * ( HorizontalSections + 1 ) );
		Links = std::vector<CapeLink>( Sections * ( HorizontalSections + 1 ) + ( Sections + 1 ) * HorizontalSections + Sections + 1 + 2 * Sections * HorizontalSections );

		for ( int i = 0; i < Sections + 1; i++ )
		{
			float t = i / static_cast<float>( Sections );
			Vector2 pos1 = t * p1_Left + ( 1 - t ) * p2_Left;
			//Vector2 pos2 = pos1;
			//pos2.X *= -1;
			Vector2 pos2 = t * p1_Right + ( 1 - t ) * p2_Right;

			for ( int j = 0; j <= HorizontalSections; j++ )
			{
				float s = j / static_cast<float>( HorizontalSections );

				Nodes[ i * ( HorizontalSections + 1 ) + j ].Data.Position = s * pos2 + ( 1 - s ) * pos1;
				Nodes[ i * ( HorizontalSections + 1 ) + j ].Data.Position.Y -= 30 * ( 1 - 2 * abs( s - .5f ) ) * t;
				Nodes[ i * ( HorizontalSections + 1 ) + j ].Show = j == 0 || j == HorizontalSections || i == Sections;
				Nodes[ i * ( HorizontalSections + 1 ) + j ].AnchorIndex = -1;

				if ( i == 0 )
				{
					Nodes[ i * ( HorizontalSections + 1 ) + j ].AnchorOffset = Nodes[ i * HorizontalSections + j ].Data.Position;
					Nodes[ i * ( HorizontalSections + 1 ) + j ].AnchorIndex = 0;
				}
			}
		}

		for ( int i = 0; i < Nodes.size(); i++ )
		{
			Nodes[ i ].StartData = Nodes[ i ].Data;
			Nodes[ i ].Weight = Weight;
		}

		int count = 0;
		// Triangles
		float h2 = 1 / Sections;
		float h1 = 1 / HorizontalSections;
		for ( int i = 0; i < Sections; i++ )
		{
			for ( int j = 0; j < HorizontalSections; j++ )
			{
				Vertices[ count ].uv = Vector2( j * h1, i * h2 );
				Vertices[ count ].xy = Nodes[ i * ( HorizontalSections + 1 ) + j ].Data.Position;

				Vertices[ count + 1 ].uv = Vector2( ( j + 1 ) * h1, i * h2 );
				Vertices[ count + 1 ].xy = Nodes[ i * ( HorizontalSections + 1 ) + j + 1 ].Data.Position;

				Vertices[ count + 2 ].uv = Vector2( j * h1, ( i + 1 ) * h2 );
				Vertices[ count + 2 ].xy = Nodes[ ( i + 1 ) * ( HorizontalSections + 1 ) + j ].Data.Position;


				Vertices[ count + 3 ].uv = Vector2( ( j + 1 ) * h1, ( i + 1 ) * h2 );
				Vertices[ count + 3 ].xy = Nodes[ ( i + 1 ) * ( HorizontalSections + 1 ) + ( j + 1 ) ].Data.Position;

				Vertices[ count + 4 ].uv = Vector2( ( j + 1 ) * h1, i * h2 );
				Vertices[ count + 4 ].xy = Nodes[ i * ( HorizontalSections + 1 ) + j + 1 ].Data.Position;

				Vertices[ count + 5 ].xy = Nodes[ ( i + 1 ) * ( HorizontalSections + 1 ) + j ].Data.Position;

				count += 6;
			}
		}

		count = 0;
		// Links
		for ( int i = 0; i < Links.size(); i++ )
			Links[ i ].Init();

		// Vertical
		for ( int i = 0; i < Sections; i++ )
		{
			for ( int j = 0; j <= HorizontalSections; j++ )
			{
				Links[ count ].j = i * ( HorizontalSections + 1 ) + j;
				Links[ count ].k = ( i + 1 ) * ( HorizontalSections + 1 ) + j;
				Links[ count ].a_in = strength_in;
				Links[ count ].a_out = strength_out;
				Links[ count ].Show = j == 0 || j == HorizontalSections;

				count++;
			}
		}

		// Horizontal
		for ( int i = 0; i <= Sections; i++ )
		{
			for ( int j = 0; j < HorizontalSections; j++ )
			{
				Links[ count ].j = i * ( HorizontalSections + 1 ) + j;
				Links[ count ].k = i * ( HorizontalSections + 1 ) + j + 1;
				Links[ count ].a_in = horizontal_strength_in;
				Links[ count ].a_out = horizontal_strength_out;
				Links[ count ].Show = i == Sections;

				count++;
			}
		}


		// Horizontal props
		for ( int i = 0; i <= Sections; i++ )
		{
			int j = 0;
			//for (int j = 0; j < HorizontalSections; j++)
			{
				Links[ count ].j = i * ( HorizontalSections + 1 ) + j;
				Links[ count ].k = i * ( HorizontalSections + 1 ) + HorizontalSections;
				Links[ count ].a_in = horizontal_strength_in;
				Links[ count ].a_out = horizontal_strength_out;
				Links[ count ].Show = false;

				count++;
			}
		}

		// Cross 1
		for ( int i = 0; i < Sections; i++ )
		{
			for ( int j = 0; j < HorizontalSections; j++ )
			{
				Links[ count ].j = i * ( HorizontalSections + 1 ) + j;
				Links[ count ].k = ( i + 1 ) * ( HorizontalSections + 1 ) + j + 1;
				Links[ count ].a_in = cross_strength_in;
				Links[ count ].a_out = cross_strength_out;
				//Links[count].Show = i == j;
				Links[ count ].Show = false;

				count++;
			}
		}

		// Cross 2
		for ( int i = 1; i <= Sections; i++ )
		{
			for ( int j = 0; j < HorizontalSections; j++ )
			{
				Links[ count ].j = i * ( HorizontalSections + 1 ) + j;
				Links[ count ].k = ( i - 1 ) * ( HorizontalSections + 1 ) + j + 1;
				Links[ count ].a_in = cross_strength_in;
				Links[ count ].a_out = cross_strength_out;
				//Links[count].Show = i + j == HorizontalSections;
				Links[ count ].Show = false;

				count++;
			}
		}

		for ( int i = 0; i < Links.size(); i++ )
		{
			int j = Links[ i ].j;
			int k = Links[ i ].k;
			Links[ i ].L = Vector2::Distance( Nodes[ j ].Data.Position, Nodes[ k ].Data.Position );
		}
	}

	void Cape::PhsxStep()
	{
		int CurStep;

		if ( MyBob == 0 )
			return;
		if ( MyBob->getCore()->MyLevel == 0 )
			return;
		if ( MyBob->getCore()->MyLevel != Tools::CurLevel )
			return;
		CurStep = MyBob->getCore()->MyLevel->GetPhsxStep();
		if ( !MyBob->CharacterSelect2 && LastPhsxUpdate == CurStep )
			return;

		LastPhsxUpdate = CurStep;

		setMyColor( MyBob->MyColorScheme.CapeColor.Clr );

		for ( int J = 0; J < PhsxSteps; J++ )
		{
			for ( int i = 0; i < Nodes.size(); i++ )
			{
				if ( Nodes[ i ].AnchorIndex >= 0 )
				{
					Nodes[ i ].Data.Position = AnchorPoint[ Nodes[ i ].AnchorIndex ] + Nodes[ i ].AnchorOffset;
				}
				else
				{
					// Integrate
					Nodes[ i ].Data.Position += ( Nodes[ i ].Data.Velocity + 0*Wind ) / PhsxSteps;
					Nodes[ i ].Data.Velocity += GravityScale * Gravity / PhsxSteps + Wind;
					Nodes[ i ].Data.Velocity *= static_cast<float>( pow( Retard / ( 1 + Nodes[ i ].Data.Velocity.LengthSquared() / 1500 ), 1 / PhsxSteps ) );

					// Check if we are below the ground
					if ( GroundCollision )
					{
						if ( Nodes[ i ].Data.Position.Y < AnchorPoint[ 0 ].Y - GroundHeight )
							Nodes[ i ].Data.Position.Y = AnchorPoint[ 0 ].Y - GroundHeight;
					}
				}
			}

			for ( int i = 0; i < Links.size(); i++ )
			{
				int j = Links[ i ].j;
				int k = Links[ i ].k;
				float L = Links[ i ].L;
				float l = Vector2::Distance( Nodes[ j ].Data.Position, Nodes[ k ].Data.Position );

				// Shorten link if too long
				float ext = 1.8f;
				if ( l > ext * L )
				{
					Vector2 Center = ( Nodes[ j ].Data.Position + Nodes[ k ].Data.Position ) / 2;
					Vector2 dif;
					dif = ( Nodes[ j ].Data.Position - Center );
					dif.Normalize();
					Nodes[ j ].Data.Position = Center + ext * L / 2 * dif;
					dif = ( Nodes[ k ].Data.Position - Center );
					dif.Normalize();
					Nodes[ k ].Data.Position = Center + ext * L / 2 * dif;
				}

				Vector2 F = Nodes[ j ].Data.Position - Nodes[ k ].Data.Position;
				float Force = F.Length();
				if ( Force > MaxForce )
					F = MaxForce * F / Force;
				if ( l < L )
					F *= -Links[ i ].a_out * ( l - L );
				if ( l > L )
					F *= -Links[ i ].a_in * ( l - L );
				F /= PhsxSteps;
				Nodes[ j ].Data.Velocity += F / Nodes[ j ].Weight;
				Nodes[ k ].Data.Velocity -= F / Nodes[ j ].Weight;
			}
		}

		UpdateTriangles();
	}

	void Cape::UpdateTriangles()
	{
		int count = 0;
		// Triangles
		float h2 = 1 / Sections;
		float h1 = 1 / HorizontalSections;
		for ( int i = Sections - 1; i >= 0; i-- )
		{
			for ( int j = 0; j < HorizontalSections; j++ )
			{
				Vertices[ count ].xy = Nodes[ i * ( HorizontalSections + 1 ) + j ].Data.Position;

				Vertices[ count + 1 ].xy = Nodes[ i * ( HorizontalSections + 1 ) + j + 1 ].Data.Position;

				Vertices[ count + 2 ].xy = Nodes[ ( i + 1 ) * ( HorizontalSections + 1 ) + j ].Data.Position;

				Vertices[ count + 3 ].xy = Nodes[ ( i + 1 ) * ( HorizontalSections + 1 ) + ( j + 1 ) ].Data.Position;

				Vertices[ count + 5 ].xy = Nodes[ i * ( HorizontalSections + 1 ) + j + 1 ].Data.Position;

				Vertices[ count + 4 ].xy = Nodes[ ( i + 1 ) * ( HorizontalSections + 1 ) + j ].Data.Position;

				count += 6;
			}
		}

		if ( DoScaling )
			for ( int i = 0; i < Vertices.size(); i++ )
				ApplyScaling( Vertices[ i ].xy );
	}

	void Cape::ApplyScaling( Vector2 &v )
	{
		v = ( v - ScaleCenter ) * Scale + ScaleCenter;
	}

	void Cape::Draw()
	{
		Tools::QDrawer->Flush();

		std::shared_ptr<EzEffect> Effect = MyQuad->Quad_Renamed->MyEffect;

		if ( !Effect->IsUpToDate )
			Effect->SetCameraParameters();


		Effect->xTexture->SetValue( MyQuad->Quad_Renamed->MyTexture->Tex );
		Effect->effect->CurrentTechnique->Passes[ 0 ]->Apply();

		//Tools.QDrawer.SetAddressMode(true, true);
		Tools::QDrawer->SetAddressMode( false, false );

		Tools::Device->DrawUserPrimitives( PrimitiveType::TriangleList, Vertices, 0, NumTriangles );

		Tools::QDrawer->Flush();

		float width = CapeThickness;
		//float width = 16;
		//float width = 8;
		if ( DoScaling )
			width *= Scale.X;

		if ( DrawLines )
			for ( int i = 0; i < Links.size(); i++ )
			{
				if ( Links[ i ].Show )
				{
					int j = Links[ i ].j;
					int k = Links[ i ].k;

					Vector2 p1 = Nodes[ j ].Data.Position;
					Vector2 p2 = Nodes[ k ].Data.Position;

					if ( DoScaling )
					{
						ApplyScaling( p1 );
						ApplyScaling( p2 );
					}
					Tools::QDrawer->DrawLine( p1, p2, getMyOutlineColor(), width, Tools::TextureWad->TextureList[ 2 ], Tools::BasicEffect, 100, 0, true );
				}
			}

		if ( DrawNodes )
			for ( int i = 0; i < Nodes.size(); i++ )
			{
				if ( Nodes[ i ].Show )
				{
					Vector2 p = Nodes[ i ].Data.Position;
					if ( DoScaling )
						ApplyScaling( p );
					Tools::QDrawer->DrawSquareDot( p, getMyOutlineColor(), width, Tools::TextureWad->TextureList[ 1 ], Tools::BasicEffect );
				}
			}
	}

	void Cape::InitializeInstanceFields()
	{
		DoScaling = false;
		AnchorPoint = std::vector<Vector2>( 2 );
		PhsxSteps = 5;
		strength_in = 2;
		Retard = .99f;
		Gravity = Vector2( 0, -1.76f );
		GroundCollision = false;
		GroundHeight = 50;
		GravityScale = 1;
		Wind = Vector2::Zero;
		CapeThickness = 16;
	}
}
