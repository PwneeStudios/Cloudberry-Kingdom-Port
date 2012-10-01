#include <Graphics/QuadDrawerWiiU.h>

#include <cassert>
#include <cafe/demo.h>
#include <cafe/gx2.h>
#include <cafe/demo/demoGfxTypes.h>
#include <Graphics/Types.h>

/// Maximum number of displayable quads.
#define MAX_QUADS 1024

static const char *const GSH_SIMPLE_SHADER_FILE = "Shaders/screen.gsh";

struct QuadVert
{
	Vector2 Position;
	Vector2 TexCoord;
	Vector4 Color;
};

// static void InitShader( DEMOGfxShader *shader, AttribBuffer *attribData )
static void InitShader( DEMOGfxShader *shader, GX2RBuffer *positionBuffer )
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

	// Set up color vertex attribute.
	DEMOGfxInitShaderAttribute( shader, "a_color", attribBuffer,
		0, GX2_ATTRIB_FORMAT_32_32_32_32_FLOAT );
	GX2UTSetAttributeBuffer( positionBuffer, attribBuffer, offsetof( QuadVert, Color ) );

	DEMOGfxInitFetchShader( shader );

	GX2SetShaders( &shader->fetchShader, shader->pVertexShader, shader->pPixelShader );
}


struct QuadDrawerInternal
{
	DEMOGfxShader SimpleShader;
	GX2RBuffer QuadBuffer;

	QuadVert *Vertices;
	u32 NumElements;
};

QuadDrawerWiiU::QuadDrawerWiiU() :
	internal_( new QuadDrawerInternal )
{
	GX2UTCreateBuffer( &internal_->QuadBuffer, GX2R_BIND_VERTEX_BUFFER
		| GX2R_USAGE_CPU_WRITE | GX2R_USAGE_GPU_READ, sizeof( QuadVert ),
		MAX_QUADS * 4 );
	GX2RSetBufferName( &internal_->QuadBuffer, "QuadBuffer" );

	InitShader( &internal_->SimpleShader, &internal_->QuadBuffer );

	internal_->Vertices = reinterpret_cast< QuadVert * >(
		GX2RLockBuffer( &internal_->QuadBuffer )
	);
}

QuadDrawerWiiU::~QuadDrawerWiiU()
{
	DEMOGfxFreeShaders( &internal_->SimpleShader );

	GX2RUnlockBuffer( &internal_->QuadBuffer );

	GX2RDestroyBuffer( &internal_->QuadBuffer );

	delete internal_;
}

void QuadDrawerWiiU::Draw( const SimpleQuad &quad )
{
	if( internal_->NumElements >= MAX_QUADS * 4 )
		return;

	for( int i = 0; i < 4; ++i )
	{
		internal_->Vertices->Position = quad.V[ i ];
		internal_->Vertices->Color = quad.Color;
		++internal_->Vertices;
	}

	internal_->NumElements += 4;	
}

void QuadDrawerWiiU::Flush()
{
	if( internal_->NumElements == 0 )
		return;

	GX2RUnlockBuffer( &internal_->QuadBuffer );

	GX2Draw( GX2_PRIMITIVE_QUADS, internal_->NumElements );

	internal_->NumElements = 0;
	internal_->Vertices = reinterpret_cast< QuadVert * >(
		GX2RLockBuffer( &internal_->QuadBuffer )
	);
}
