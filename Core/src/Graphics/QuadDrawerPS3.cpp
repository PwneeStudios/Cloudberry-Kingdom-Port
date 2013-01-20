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

#include <PSGL/psgl.h>
#include <PSGL/psglu.h>

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
	unsigned int QuadBuffer;
	unsigned int NumElements;
	QuadVert *Vertices;

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
		NumElements( 0 ),
		Vertices( 0 )
	{

	}
};


QuadDrawerPS3::QuadDrawerPS3() :
	internal_( new QuadDrawerInternal )
{
	glGenBuffers( 1, &internal_->QuadBuffer );
	glBindBuffer( GL_ARRAY_BUFFER, internal_->QuadBuffer );
	glBufferData( GL_ARRAY_BUFFER, MAX_QUADS * 4 * sizeof( QuadVert ), 0, GL_DYNAMIC_DRAW );
	internal_->Vertices = reinterpret_cast< QuadVert * >( glMapBuffer( GL_ARRAY_BUFFER, GL_WRITE_ONLY ) );
	glBindBuffer( GL_ARRAY_BUFFER, 0 );

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
	glBindBuffer( GL_ARRAY_BUFFER, internal_->QuadBuffer );
	glUnmapBuffer( GL_ARRAY_BUFFER );
	glBindBuffer( GL_ARRAY_BUFFER, 0 );

	glDeleteBuffers( 1, &internal_->QuadBuffer );

	delete internal_;
}

void QuadDrawerPS3::SetEffect( const boost::shared_ptr<Effect> &effect )
{
	internal_->CurrentEffect = effect;

	internal_->TextureParameter = effect->Parameters( "TextureSampler" );
	internal_->ExtraTextureParameter1 = effect->Parameters( "BackTextureSampler" );
	internal_->ExtraTextureParameter2 = effect->Parameters( "MaskTextureSampler" );
}

boost::shared_ptr<Effect> QuadDrawerPS3::GetEffect()
{
	return internal_->CurrentEffect;
}

void QuadDrawerPS3::Draw( const SimpleQuad &quad )
{
	if( internal_->NumElements >= MAX_QUADS * 4 )
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
	internal_->NumElements += 4;
}

void QuadDrawerPS3::Flush()
{
	if( internal_->NumElements == 0 )
		return;

	internal_->TextureParameter->SetValue( 0 );
	internal_->ExtraTextureParameter1->SetValue( 1 );
	internal_->ExtraTextureParameter2->SetValue( 2 );

	glBindBuffer( GL_ARRAY_BUFFER, internal_->QuadBuffer );
	glUnmapBuffer( GL_ARRAY_BUFFER );

	glEnableClientState( GL_VERTEX_ARRAY );
	glBindBuffer( GL_ARRAY_BUFFER, internal_->QuadBuffer );
	glVertexPointer( 2, GL_FLOAT, sizeof( QuadVert ), reinterpret_cast< const GLvoid * >( offsetof( QuadVert, Position ) ) );

	glEnableClientState( GL_TEXTURE_COORD_ARRAY );
	glBindBuffer( GL_ARRAY_BUFFER, internal_->QuadBuffer );
	glTexCoordPointer( 2, GL_FLOAT, sizeof( QuadVert ), reinterpret_cast< const GLvoid * >( offsetof( QuadVert, TexCoord ) ) );

	glEnableClientState( GL_COLOR_ARRAY );
	glBindBuffer( GL_ARRAY_BUFFER, internal_->QuadBuffer );
	glColorPointer( 4, GL_FLOAT, sizeof( QuadVert), reinterpret_cast< const GLvoid * >( offsetof( QuadVert, Color ) ) );

	internal_->CastleBackground->Activate( 1 );

	BatchList::iterator i;
	for( i = internal_->Batches.begin(); i != internal_->Batches.end(); ++i )
	{
		RenderBatch &batch = *i;

		batch.Map->Activate( *internal_->TextureParameter.get() );
		internal_->CurrentEffect->CurrentTechnique->Passes[ 0 ]->Apply();

		glDrawArrays( GL_QUADS, batch.Offset, batch.NumElements );
	}

	glDisableClientState( GL_COLOR_ARRAY );
	glDisableClientState( GL_TEXTURE_COORD_ARRAY );
	glDisableClientState( GL_VERTEX_ARRAY );

	internal_->Vertices = reinterpret_cast< QuadVert * >(
		glMapBuffer( GL_ARRAY_BUFFER, GL_WRITE_ONLY )
	);
	glBindBuffer( GL_ARRAY_BUFFER, 0 );


	internal_->Batches.clear();
	internal_->NumElements = 0;
}
