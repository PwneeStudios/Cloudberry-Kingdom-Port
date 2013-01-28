#include <Graphics/QuadDrawerWiiU.h>

#include <cassert>
#include <cafe/demo.h>
#include <cafe/gx2.h>
#include <cafe/demo/demoGfxTypes.h>
#include <Content/ResourcePtr.h>
#include <Content/Texture.h>
#include <Graphics/Types.h>
#include <Graphics/Effect.h>
#include <Graphics/EffectTechnique.h>
#include <Graphics/EffectPass.h>
#include <Utility/Log.h>
#include <vector>

/// Maximum number of displayable quads.
#define MAX_QUADS 1024

static const char *const GSH_SIMPLE_SHADER_FILE = "Shaders/screen.gsh";

struct QuadVert
{
	Vector2 Position;
	Vector2 TexCoord;
	Vector4 Color;
};

struct RenderBatch
{
	u32 Offset;
	u32 NumElements;
	ResourcePtr< Texture > Map;
};

typedef std::vector< RenderBatch > BatchList;

// static void InitShader( DEMOGfxShader *shader, AttribBuffer *attribData )
/*static void InitShader( DEMOGfxShader *shader, GX2RBuffer *positionBuffer, u32 &sampler )
{
	void *gshBuf;
	u32 gshLen;
	u32 attribBuffer = 0;

	// Load shader from file and then into a shader object.
	gshBuf = DEMOFSSimpleRead( GSH_SIMPLE_SHADER_FILE, &gshLen );
	DEMOGfxLoadShaders( shader, 0, gshBuf );
	DEMOFree( gshBuf );

	// Set up position vertex attribute.
	DEMOGfxInitShaderAttribute( shader, "a_position", attribBuffer,
		0, GX2_ATTRIB_FORMAT_32_32_FLOAT );
	GX2UTSetAttributeBuffer( positionBuffer, attribBuffer, 0 );

	attribBuffer++;

	// Set up texture coordinate attribute.
	DEMOGfxInitShaderAttribute( shader, "a_texcoord", attribBuffer,
		0, GX2_ATTRIB_FORMAT_32_32_FLOAT );
	GX2UTSetAttributeBuffer( positionBuffer, attribBuffer, offsetof( QuadVert, TexCoord ) );

	attribBuffer++;

	// Set up color vertex attribute.
	DEMOGfxInitShaderAttribute( shader, "a_color", attribBuffer,
		0, GX2_ATTRIB_FORMAT_32_32_32_32_FLOAT );
	GX2UTSetAttributeBuffer( positionBuffer, attribBuffer, offsetof( QuadVert, Color ) );

	// Get location of texture sampler.
	sampler = static_cast< u32 >(
		GX2GetPixelSamplerVarLocation( shader->pPixelShader, "u_texture" )
	);

	DEMOGfxInitFetchShader( shader );

	GX2SetShaders( &shader->fetchShader, shader->pVertexShader, shader->pPixelShader );
}
*/

struct QuadDrawerInternal
{
	//DEMOGfxShader SimpleShader;
	GX2RBuffer QuadBuffer;
	std::vector<QuadVert> LocalQuadBuffer;

	QuadVert *Vertices;
	u32 NumElements;

	//u32 SamplerLocation;
	GX2Sampler Sampler;

	BatchList Batches;

	boost::shared_ptr<Effect> Effect;
};

QuadDrawerWiiU::QuadDrawerWiiU() :
	internal_( new QuadDrawerInternal )
{
	internal_->Vertices = 0;
	internal_->NumElements = 0;
	//internal_->SamplerLocation = 0;

	internal_->LocalQuadBuffer.reserve( MAX_QUADS * 4 );

	GX2UTCreateBuffer( &internal_->QuadBuffer, GX2R_BIND_VERTEX_BUFFER
		| GX2R_USAGE_CPU_WRITE | GX2R_USAGE_GPU_READ, sizeof( QuadVert ),
		MAX_QUADS * 4 );
	GX2RSetBufferName( &internal_->QuadBuffer, "QuadBuffer" );

	//InitShader( &internal_->SimpleShader, &internal_->QuadBuffer, internal_->SamplerLocation );

	GX2InitSampler( &internal_->Sampler, GX2_TEX_CLAMP_MIRROR, GX2_TEX_XY_FILTER_BILINEAR );

	/*internal_->Vertices = reinterpret_cast< QuadVert * >(
		GX2RLockBuffer( &internal_->QuadBuffer )
	);*/
}

QuadDrawerWiiU::~QuadDrawerWiiU()
{
	//DEMOGfxFreeShaders( &internal_->SimpleShader );

	//GX2RUnlockBuffer( &internal_->QuadBuffer );

	GX2RDestroyBuffer( &internal_->QuadBuffer );

	delete internal_;
}

void QuadDrawerWiiU::SetEffect( const boost::shared_ptr<Effect> &effect )
{
	internal_->Effect = effect;
}

boost::shared_ptr<Effect> QuadDrawerWiiU::GetEffect()
{
	return internal_->Effect;
}

void QuadDrawerWiiU::Draw( const SimpleQuad &quad )
{
	if( internal_->NumElements >= MAX_QUADS * 4 )
		return;

	RenderBatch rb;
	rb.Map = quad.Diffuse;
	rb.Offset = 0;
	rb.NumElements = 4;

	for( int i = 0; i < 4; ++i )
	{
		internal_->LocalQuadBuffer.push_back( QuadVert() );
		internal_->LocalQuadBuffer.back().Position = quad.V[ i ];
		internal_->LocalQuadBuffer.back().TexCoord = quad.T[ i ];
		internal_->LocalQuadBuffer.back().Color = quad.Color;
		/*internal_->Vertices->Position = quad.V[ i ];
		internal_->Vertices->TexCoord = quad.T[ i ];
		internal_->Vertices->Color = quad.Color;
		++internal_->Vertices;*/
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

void QuadDrawerWiiU::Flush()
{
	if( internal_->NumElements == 0 )
		return;

	
	internal_->Vertices = reinterpret_cast< QuadVert * >(
		GX2RLockBuffer( &internal_->QuadBuffer )
	);
	memcpy( internal_->Vertices, &internal_->LocalQuadBuffer[ 0 ], internal_->NumElements * sizeof( QuadVert ) );
	GX2RUnlockBuffer( &internal_->QuadBuffer );

	internal_->Effect->CurrentTechnique->Passes[ 0 ]->Apply();

	GX2UTSetAttributeBuffer( &internal_->QuadBuffer, 0, 0 );
	GX2UTSetAttributeBuffer( &internal_->QuadBuffer, 1, offsetof( QuadVert, TexCoord ) );
	GX2UTSetAttributeBuffer( &internal_->QuadBuffer, 2, offsetof( QuadVert, Color ) );

	GX2SetPixelSampler( &internal_->Sampler, 0 );

	BatchList::iterator i;
	for( i = internal_->Batches.begin(); i != internal_->Batches.end(); ++i )
	{
		RenderBatch &batch = *i;
		batch.Map->Activate( 0 );
		GX2DrawEx( GX2_PRIMITIVE_QUADS, batch.NumElements, batch.Offset, 1 );	
	}
	
	internal_->Batches.clear();
	internal_->NumElements = 0;
	internal_->LocalQuadBuffer.clear();
	/*internal_->Vertices = reinterpret_cast< QuadVert * >(
		GX2RLockBuffer( &internal_->QuadBuffer )
	);*/

	// FIXME: Maybe a GX2Flush() is sufficient?
	GX2DrawDone();
}

void QuadDrawerWiiU::Unlock()
{
	//GX2RUnlockBuffer( &internal_->QuadBuffer );
}
