#include <Graphics/QuadDrawerVita.h>

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

#include <gxm.h>

extern void *graphicsAlloc(SceKernelMemBlockType type, uint32_t size, uint32_t alignment, uint32_t attribs, SceUID *uid);
extern void graphicsFree(SceUID uid);

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
	unsigned int	QuadBuffer;
	unsigned int	NumElements;
	QuadVert *		Vertices;
	SceUID			AllocationIDVertices;
	unsigned short *Indices;
	SceUID			AllocationIDIndices;

	boost::shared_ptr<Effect>			CurrentEffect;
	boost::shared_ptr<EffectParameter>	TextureParameter;
	boost::shared_ptr<EffectParameter>	ExtraTextureParameter1;
	boost::shared_ptr<EffectParameter>	ExtraTextureParameter2;

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


QuadDrawerVita::QuadDrawerVita() :
	internal_( new QuadDrawerInternal )
{
	internal_->Vertices = reinterpret_cast< QuadVert * >(
		graphicsAlloc(
			SCE_KERNEL_MEMBLOCK_TYPE_USER_RWDATA_UNCACHE,
			MAX_QUADS * 4 * sizeof( QuadVert ),
			4,
			SCE_GXM_MEMORY_ATTRIB_READ,
			&internal_->AllocationIDVertices
		)
	);

	internal_->Indices = reinterpret_cast< unsigned short * >(
		graphicsAlloc(
			SCE_KERNEL_MEMBLOCK_TYPE_USER_RWDATA_UNCACHE,
			MAX_QUADS * 6 * sizeof( unsigned short ),
			4,
			SCE_GXM_MEMORY_ATTRIB_READ,
			&internal_->AllocationIDIndices
		)
	);
	//glGenBuffers( 1, &internal_->QuadBuffer );
	//glBindBuffer( GL_ARRAY_BUFFER, internal_->QuadBuffer );
	//glBufferData( GL_ARRAY_BUFFER, MAX_QUADS * 4 * sizeof( QuadVert ), 0, GL_DYNAMIC_DRAW );
	//internal_->Vertices = reinterpret_cast< QuadVert * >( glMapBuffer( GL_ARRAY_BUFFER, GL_WRITE_ONLY ) );
	//glBindBuffer( GL_ARRAY_BUFFER, 0 );

	internal_->MiddleFrame = CONTENT->Load< Texture >( "Art/Environments/Castle/Background/v2/Castle_Window_Center_Frame.png" );
	internal_->LeftFrame = CONTENT->Load< Texture >( "Art/Environments/Castle/Background/v2/Castle_Window_Left_Frame.png" );
	internal_->RightFrame = CONTENT->Load< Texture >( "Art/Environments/Castle/Background/v2/Castle_Window_Right_Frame.png" );

	internal_->MiddleFrameMask = CONTENT->Load< Texture >( "Art/Environments/Castle/Background/v2/Castle_Window_Center_Mask.png" );
	internal_->LeftFrameMask = CONTENT->Load< Texture >( "Art/Environments/Castle/Background/v2/Castle_Window_Left_Mask.png" );
	internal_->RightFrameMask = CONTENT->Load< Texture >( "Art/Environments/Castle/Background/v2/Castle_Window_Right_Mask.png" );

	internal_->CastleBackground = CONTENT->Load< Texture >( "Art/Environments/Castle/Background/v2/Castle_Backdrop_2.png" );
}

QuadDrawerVita::~QuadDrawerVita()
{
	graphicsFree( internal_->AllocationIDVertices );
	graphicsFree( internal_->AllocationIDIndices );

	delete internal_;
}

void QuadDrawerVita::SetEffect( const boost::shared_ptr<Effect> &effect )
{
	const static std::string TextureSampler = "TextureSampler";
	const static std::string BackTextureSampler = "BackTextureSampler";
	const static std::string MaskTextureSampler = "MaskTextureSampler";

	internal_->CurrentEffect = effect;

	internal_->TextureParameter = effect->Parameters( TextureSampler );
	internal_->ExtraTextureParameter1 = effect->Parameters( BackTextureSampler );
	internal_->ExtraTextureParameter2 = effect->Parameters( MaskTextureSampler );
}

boost::shared_ptr<Effect> QuadDrawerVita::GetEffect()
{
	return internal_->CurrentEffect;
}

void QuadDrawerVita::Draw( const SimpleQuad &quad )
{
	if( internal_->NumElements >= MAX_QUADS * 6 )
		return;

	RenderBatch rb;
	rb.Map = quad.Diffuse;
	rb.Offset = 0;
	rb.NumElements = 6;

	QuadVert *vertexBase = internal_->Vertices + 4 * internal_->NumElements / 6;
	for( int i = 0; i < 4; ++i )
	{
		vertexBase->Position	= quad.V[ i ];
		vertexBase->TexCoord	= quad.T[ i ];
		vertexBase->Color		= quad.Color;
		++vertexBase;
	}

	unsigned short baseIndex = internal_->NumElements;
	unsigned short *indexBase = internal_->Indices + internal_->NumElements;
	*( indexBase++ ) = baseIndex + 0;
	*( indexBase++ ) = baseIndex + 1;
	*( indexBase++ ) = baseIndex + 2;

	*( indexBase++ ) = baseIndex + 0;
	*( indexBase++ ) = baseIndex + 2;
	*( indexBase++ ) = baseIndex + 3;

	BatchList &batches = internal_->Batches;
	if( batches.empty() )
		batches.push_back( rb );
	else
	{
		RenderBatch &lastBatch = batches.back();

		// If the previous batch has the same texture, expand it. Otherwise
		// start a new batch.
		if( lastBatch.Map == rb.Map )
			lastBatch.NumElements += 6;
		else
		{
			rb.Offset = lastBatch.Offset + lastBatch.NumElements;
			batches.push_back( rb );
		}
	}
	internal_->NumElements += 6;
}

// Pointer to global graphics context. Declared in CoreVita.cpp.
extern SceGxmContext *GraphicsContext;

void QuadDrawerVita::Flush()
{
	if( internal_->NumElements == 0 )
		return;

	internal_->TextureParameter->SetValue( 0 );
	internal_->ExtraTextureParameter1->SetValue( 1 );
	internal_->ExtraTextureParameter2->SetValue( 2 );

	//glBindBuffer( GL_ARRAY_BUFFER, internal_->QuadBuffer );
	//glUnmapBuffer( GL_ARRAY_BUFFER );

	//glEnableClientState( GL_VERTEX_ARRAY );
	//glBindBuffer( GL_ARRAY_BUFFER, internal_->QuadBuffer );
	//glVertexPointer( 2, GL_FLOAT, sizeof( QuadVert ), reinterpret_cast< const GLvoid * >( offsetof( QuadVert, Position ) ) );

	//glEnableClientState( GL_TEXTURE_COORD_ARRAY );
	//glBindBuffer( GL_ARRAY_BUFFER, internal_->QuadBuffer );
	//glTexCoordPointer( 2, GL_FLOAT, sizeof( QuadVert ), reinterpret_cast< const GLvoid * >( offsetof( QuadVert, TexCoord ) ) );

	//glEnableClientState( GL_COLOR_ARRAY );
	//glBindBuffer( GL_ARRAY_BUFFER, internal_->QuadBuffer );
	//glColorPointer( 4, GL_FLOAT, sizeof( QuadVert), reinterpret_cast< const GLvoid * >( offsetof( QuadVert, Color ) ) );

	//internal_->CastleBackground->Activate( *internal_->ExtraTextureParameter1.get() )

	BatchList::iterator i;
	for( i = internal_->Batches.begin(); i != internal_->Batches.end(); ++i )
	{
		RenderBatch &batch = *i;

		/*if( batch.Map == internal_->LeftFrame )
		{
			internal_->LeftFrameMask->Activate( *internal_->ExtraTextureParameter2.get() );
		}
		else if( batch.Map == internal_->MiddleFrame )
		{
			internal_->MiddleFrameMask->Activate( *internal_->ExtraTextureParameter2.get() );
		}
		else if( batch.Map == internal_->RightFrame )
		{
			internal_->RightFrameMask->Activate( *internal_->ExtraTextureParameter2.get() );
		}
		
		batch.Map->Activate( *internal_->TextureParameter.get() );*/

		internal_->CurrentEffect->CurrentTechnique->Passes[ 0 ]->Apply();

		sceGxmSetVertexStream( GraphicsContext, 0, internal_->Vertices );
		
		/*sceGxmDraw(
			GraphicsContext,
			SCE_GXM_PRIMITIVE_TRIANGLES,
			SCE_GXM_INDEX_FORMAT_U16,
			internal_->Indices + batch.Offset,
			batch.NumElements
		);*/
		//glDrawArrays( GL_QUADS, batch.Offset, batch.NumElements );
	}

	//glDisableClientState( GL_COLOR_ARRAY );
	//glDisableClientState( GL_TEXTURE_COORD_ARRAY );
	//glDisableClientState( GL_VERTEX_ARRAY );

	//internal_->Vertices = reinterpret_cast< QuadVert * >(
	//	glMapBuffer( GL_ARRAY_BUFFER, GL_WRITE_ONLY )
	//);
	//glBindBuffer( GL_ARRAY_BUFFER, 0 );

	internal_->Batches.clear();
	internal_->NumElements = 0;
}
