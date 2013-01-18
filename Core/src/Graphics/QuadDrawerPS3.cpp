#include <Graphics/QuadDrawerPS3.h>

#include <cassert>
#include <Content/ResourcePtr.h>
#include <Content/Texture.h>
#include <Content/Wad.h>
#include <Core.h>
#include <cstring>
#include <fstream>
#include <Graphics/Types.h>
#include <Graphics/Effect.h>
#include <sstream>
#include <string>
#include <vector>

/// Maximum number of displayable quads.
#define MAX_QUADS 1024

struct QuadVert
{
	Vector2 Position;
	Vector2 TexCoord;
	Vector4 Color;
};

struct RenderBatch
{
	unsigned int Offset;
	unsigned int NumElements;
	ResourcePtr< Texture > Map;
};

typedef std::vector< RenderBatch > BatchList;

struct QuadDrawerInternal
{
	unsigned int QuadBuffer[2];
	unsigned int CurrentBuffer;
	unsigned int NumElements;
	QuadVert *Vertices;

	//unsigned int Program;
	unsigned int VertexAttrib;
	unsigned int TexCoordAttrib;
	unsigned int ColorAttrib;
	//unsigned int TexUniform;

	boost::shared_ptr<Effect> CurrentEffect;
	boost::shared_ptr<EffectParameter> TextureParameter;
	boost::shared_ptr<EffectParameter> ExtraTextureParameter1;
	boost::shared_ptr<EffectParameter> ExtraTextureParameter2;

	ResourcePtr< Texture > MiddleFrame;
	ResourcePtr< Texture > LeftFrame;
	ResourcePtr< Texture > RightFrame;

	ResourcePtr< Texture > MiddleFrameMask;
	ResourcePtr< Texture > LeftFrameMask;
	ResourcePtr< Texture > RightFrameMask;

	ResourcePtr< Texture > CastleBackground;
	
	BatchList Batches;

	QuadDrawerInternal() :
		CurrentBuffer( 0 ),
		NumElements( 0 ),
		Vertices( 0 ),
		//Program( 0 ),
		VertexAttrib( 0 ),
		TexCoordAttrib( 0 ),
		ColorAttrib( 0 )//,
		//TexUniform( 0 )
	{

	}
};


QuadDrawerPS3::QuadDrawerPS3() :
	internal_( new QuadDrawerInternal )
{
	internal_->MiddleFrame = CONTENT->Load< Texture >( "Art/Environments/Castle/Background/v2/Castle_Window_Center_Frame.png" );
	internal_->LeftFrame = CONTENT->Load< Texture >( "Art/Environments/Castle/Background/v2/Castle_Window_Left_Frame.png" );
	internal_->RightFrame = CONTENT->Load< Texture >( "Art/Environments/Castle/Background/v2/Castle_Window_Right_Frame.png" );

	internal_->MiddleFrameMask = CONTENT->Load< Texture >( "Art/Environments/Castle/Background/v2/Castle_Window_Center_Mask.png" );
	internal_->LeftFrameMask = CONTENT->Load< Texture >( "Art/Environments/Castle/Background/v2/Castle_Window_Left_Mask.png" );
	internal_->RightFrameMask = CONTENT->Load< Texture >( "Art/Environments/Castle/Background/v2/Castle_Window_Right_Mask.png" );

	internal_->CastleBackground = CONTENT->Load< Texture >( "Art/Environments/Castle/Background/v2/Castle_Backdrop_2.png" );
}

QuadDrawerPS3::~QuadDrawerPS3()
{
	delete internal_;
}

void QuadDrawerPS3::SetEffect( const boost::shared_ptr<Effect> &effect )
{
	internal_->CurrentEffect = effect;

	internal_->VertexAttrib = effect->Attributes( "a_position" );
	internal_->TexCoordAttrib = effect->Attributes( "a_texcoord" );
	internal_->ColorAttrib = effect->Attributes( "a_color" );
	internal_->TextureParameter = effect->Parameters( "u_texture" );
	internal_->ExtraTextureParameter1 = effect->Parameters( "u_backTexture" );
	internal_->ExtraTextureParameter2 = effect->Parameters( "u_maskTexture" );
}

boost::shared_ptr<Effect> QuadDrawerPS3::GetEffect()
{
	return internal_->CurrentEffect;
}

void QuadDrawerPS3::Draw( const SimpleQuad &quad )
{
	/*if( internal_->NumElements >= MAX_QUADS * 4 )
		return;

	RenderBatch rb;
	rb.Map = quad.Diffuse;
	rb.Offset = 0;
	rb.NumElements = 4;

	for( int i = 0; i < 4; ++i )
	{
		internal_->Vertices->Position = quad.V[ i ];
		internal_->Vertices->TexCoord = quad.T[ i ];
		internal_->Vertices->Color = quad.Color;
		++internal_->Vertices;
	}

	BatchList &batches = internal_->Batches;
	if( batches.empty() )
		batches.push_back( rb );
	else
	{
		RenderBatch &lastBatch = batches.back();

		// If the previous batch has the same texture, expand it. Otherwise
		// start a new batch.
		if( lastBatch.Map == rb.Map )
			lastBatch.NumElements += 4;
		else
		{
			rb.Offset = lastBatch.Offset + lastBatch.NumElements;
			batches.push_back( rb );
		}
	}
	internal_->NumElements += 4;*/
}

void QuadDrawerPS3::Flush()
{
	if( internal_->NumElements == 0 )
		return;

	internal_->TextureParameter->SetValue( 0 );
	internal_->ExtraTextureParameter1->SetValue( 1 );
	internal_->ExtraTextureParameter2->SetValue( 2 );

	internal_->CurrentEffect->CurrentTechnique->Passes[ 0 ]->Apply();

	//glUseProgram( internal_->Program );
	//glUniform1i( internal_->TexUniform, 0 );

	internal_->CastleBackground->Activate( 1 );


	internal_->Batches.clear();
	internal_->NumElements = 0;
	internal_->CurrentBuffer = 1 - internal_->CurrentBuffer;
}
