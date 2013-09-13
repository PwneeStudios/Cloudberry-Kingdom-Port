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
#include <libdbg.h>

extern void *graphicsAlloc(SceKernelMemBlockType type, uint32_t size, uint32_t alignment, uint32_t attribs, SceUID *uid);
extern void graphicsFree(SceUID uid);

/// Maximum number of displayable quads.
#define MAX_QUADS 1024

#define MAX_RING_QUADS 2048

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

class DrawBuffer
{
	unsigned int		NumElements;
	unsigned int		NumVertices;

	QuadVert *			Vertices;
	SceUID				AllocationIDVertices;

	unsigned short *	Indices;
	SceUID				AllocationIDIndices;

	unsigned int		allocatedElements_;
	unsigned int		allocatedVertices_;
	QuadVert *			currentQuadVert_;
	unsigned short *	currentIndex_;

public:
	DrawBuffer()
		: NumElements( 0 )
		, NumVertices( 0 )
		, Vertices( NULL )
		, AllocationIDVertices( 0 )
		, Indices( NULL )
		, AllocationIDIndices( 0 )
		, allocatedElements_( 0 )
		, allocatedVertices_( 0 )
		, currentQuadVert_( 0 )
		, currentIndex_( 0 )
	{
		Vertices = reinterpret_cast< QuadVert * >(
			graphicsAlloc(
				SCE_KERNEL_MEMBLOCK_TYPE_USER_RWDATA_UNCACHE,
				MAX_QUADS * 4 * sizeof( QuadVert ),
				4,
				SCE_GXM_MEMORY_ATTRIB_READ,
				&AllocationIDVertices
			)
		);

		Indices = reinterpret_cast< unsigned short * >(
			graphicsAlloc(
				SCE_KERNEL_MEMBLOCK_TYPE_USER_RWDATA_UNCACHE,
				MAX_QUADS * 6 * sizeof( unsigned short ),
				4,
				SCE_GXM_MEMORY_ATTRIB_READ,
				&AllocationIDIndices
			)
		);

		currentQuadVert_	= Vertices;
		currentIndex_		= Indices;
	}

	~DrawBuffer()
	{
		graphicsFree( AllocationIDVertices );
		graphicsFree( AllocationIDIndices );
	}

	bool Allocate( unsigned int numVertices, unsigned int numIndices,
		QuadVert * &vertices, unsigned short * &indices )
	{
		if( allocatedElements_ + numIndices > NumElements
			|| allocatedVertices_ + numVertices > NumVertices )
		{
			vertices	= NULL;
			indices		= NULL;

			return false;
		}

		vertices		= currentQuadVert_;
		currentIndex_	= currentIndex_;

		allocatedElements_	+= numIndices;
		allocatedVertices_	+= numVertices;
		currentIndex_		+= numIndices;
		currentQuadVert_	+= numVertices;

		return true;
	}

	void Reset()
	{
		allocatedElements_ = 0;
		allocatedVertices_ = 0;
		
		currentQuadVert_	= Vertices;
		currentIndex_		= Indices;
	}
};

template< typename T >
class RingBuffer
{
	unsigned int	numElements_;
	unsigned int	numUsed_;
	T *				data_;

public:
	RingBuffer( unsigned int numElements )
		: numElements_( numElements )
		, numUsed_( 0 )
		, data_( NULL )
	{
		data_ = new T[ numElements_ ];
	}

	~RingBuffer()
	{
		delete[] data_;
	}

	bool CanAllocate( unsigned int n )
	{
		return numUsed_ + n <= numElements_;
	}

	T *Allocate( unsigned int n )
	{
		T *data = data_ + numUsed_;
		numUsed_ += n;
		return data;
	}

	void Reset()
	{
		numUsed_ = 0;
	}
};

RingBuffer< QuadVert > *		QuadDrawerVertexRingBuffer;
RingBuffer< unsigned short > *	QuadDrawerIndexRingBuffer;

struct QuadDrawerInternal
{
	unsigned int	QuadBuffer;
	unsigned int	NumElements;
	unsigned int	NumVertices;
	QuadVert *		Vertices;
	SceUID			AllocationIDVertices;
	unsigned short *Indices;
	SceUID			AllocationIDIndices;

	DrawBuffer		DrawBuffers[ 2 ];
	DrawBuffer		CurrentDrawBuffer;
	unsigned int	CurrentBuffer;

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

	QuadDrawerInternal()
		: NumElements( 0 )
		, NumVertices( 0 )
		, Vertices( 0 )
		, Indices( 0 )
		, CurrentBuffer( 0 )
	{

	}
};


QuadDrawerVita::QuadDrawerVita() :
	internal_( new QuadDrawerInternal )
{
	/*internal_->Vertices = internal_->DrawBuffers[ internal_->CurrentBuffer ].Vertices;
	internal_->Indices = internal_->DrawBuffers[ internal_->CurrentBuffer ].Indices;*/

	QuadDrawerVertexRingBuffer	= new RingBuffer< QuadVert >( MAX_RING_QUADS * 4 );
	QuadDrawerIndexRingBuffer	= new RingBuffer< unsigned short >( MAX_RING_QUADS * 2 * 3 );

	/*internal_->Vertices = reinterpret_cast< QuadVert * >(
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
	);*/

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
	/*graphicsFree( internal_->AllocationIDVertices );
	graphicsFree( internal_->AllocationIDIndices );*/

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

	QuadVert *		vertexBase;
	unsigned short *indexBase;

	if( !internal_->CurrentDrawBuffer.Allocate( 4, 6, vertexBase, indexBase ) )
	{
		int err = sceGxmMidSceneFlush( GraphicsContext, SCE_GXM_MIDSCENE_PRESERVE_DEFAULT_UNIFORM_BUFFERS, NULL, NULL );
		SCE_DBG_ASSERT( err == SCE_OK );

		sceGxmWaitEvent();
		internal_->CurrentDrawBuffer.Reset();
	}

	RenderBatch rb;
	rb.Map = quad.Diffuse;
	rb.Offset = 0;
	rb.NumElements = 6;

	QuadVert *vertexBase = internal_->Vertices + internal_->NumVertices;
	for( int i = 0; i < 4; ++i )
	{
		vertexBase->Position	= quad.V[ i ];
		vertexBase->TexCoord	= quad.T[ i ];
		vertexBase->Color		= quad.Color;
		++vertexBase;
	}

	unsigned short baseIndex = internal_->NumVertices;
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
	internal_->NumVertices += 4;
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
		}*/
		
		batch.Map->Activate( 0 );

		internal_->CurrentEffect->CurrentTechnique->Passes[ 0 ]->Apply();

		sceGxmSetFrontDepthWriteEnable( GraphicsContext, SCE_GXM_DEPTH_WRITE_DISABLED );
		sceGxmSetFrontDepthFunc( GraphicsContext, SCE_GXM_DEPTH_FUNC_ALWAYS );
		sceGxmSetBackDepthWriteEnable( GraphicsContext, SCE_GXM_DEPTH_WRITE_DISABLED );
		sceGxmSetBackDepthFunc( GraphicsContext, SCE_GXM_DEPTH_FUNC_ALWAYS );

		//sceGxmSetFrontPolygonMode( GraphicsContext, SCE_GXM_POLYGON_MODE_TRIANGLE_LINE );
		//sceGxmSetBackPolygonMode( GraphicsContext, SCE_GXM_POLYGON_MODE_TRIANGLE_LINE );

		sceGxmSetVertexStream( GraphicsContext, 0, internal_->Vertices );

		//if( batch.NumElements == 1740 )
		//{
			int err = sceGxmDraw(
				GraphicsContext,
				SCE_GXM_PRIMITIVE_TRIANGLES,
				SCE_GXM_INDEX_FORMAT_U16,
				internal_->Indices + batch.Offset,
				batch.NumElements
			);
			SCE_DBG_ASSERT( err == SCE_OK );

			/*int k = 0;
			for( int i = 0; i < 100000; ++i )
			{
				int j = 0;
				j++;
				k += j;
			}*/
		//}

			err = sceGxmMidSceneFlush( GraphicsContext, SCE_GXM_MIDSCENE_PRESERVE_DEFAULT_UNIFORM_BUFFERS, NULL, NULL );
			SCE_DBG_ASSERT( err == SCE_OK );

			sceGxmWaitEvent();
		//}
	}

	internal_->Batches.clear();
	internal_->NumElements = 0;
	internal_->NumVertices = 0;

	internal_->CurrentBuffer = ( internal_->CurrentBuffer + 1 ) % 2;
	internal_->Vertices = internal_->DrawBuffers[ internal_->CurrentBuffer ].Vertices;
	internal_->Indices = internal_->DrawBuffers[ internal_->CurrentBuffer ].Indices;
}
