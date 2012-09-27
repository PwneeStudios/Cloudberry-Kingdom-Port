#include <Graphics/QuadDrawerWiiU.h>

#include <cassert>
#include <cafe/demo.h>
#include <cafe/gx2.h>
#include <cafe/demo/demoGfxTypes.h>
#include <Graphics/Types.h>

static const char *const GSH_SIMPLE_SHADER_FILE = "Shaders/simple.gsh";

struct AttribBuffer
{
	GX2RBuffer PositionBuffer;
	GX2RBuffer ColorBuffer;
};

static void InitShader( DEMOGfxShader *shader, AttribBuffer *attribData )
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
		0, GX2_ATTRIB_FORMAT_32_32_32_FLOAT );
	GX2UTSetAttributeBuffer( &attribData->PositionBuffer, attribBuffer, 0 );

	attribBuffer++;

	// Set up color vertex attribute.
	DEMOGfxInitShaderAttribute( shader, "a_color", attribBuffer,
		0, GX2_ATTRIB_FORMAT_32_32_32_FLOAT );
	GX2UTSetAttributeBuffer( &attribData->ColorBuffer, attribBuffer, 0 );

	DEMOGfxInitFetchShader( shader );

	GX2SetShaders( &shader->fetchShader, shader->pVertexShader, shader->pPixelShader );
}

#pragma alignvar( GX2_VERTEX_BUFFER_ALIGNMENT )
static DEMO_F32x3 TRIANGLE_POSITION_DATA[] = {
	{ -0.75f,  0.75f, -0.5f },
	{  0.75f,  0.75f, -0.5f },
	{  0.00f, -0.75f, -0.5f },
	{ -0.75f, -0.75f, -0.5f }
};

#pragma alignvar( GX2_VERTEX_BUFFER_ALIGNMENT )
static DEMO_F32x3 TRIANGLE_COLOR_DATA[] = {
	{ 1.0f, 0.0f, 0.0f },
	{ 0.0f, 1.0f, 0.0f },
	{ 0.0f, 0.0f, 1.0f },
	{ 0.0f, 1.0f, 1.0f }
};

static const u32 TRIANGLE_VERTEX_NUM = 4;

static void InitAttribData( AttribBuffer *attribData )
{
	GX2RCreateBufferUserMemory( &attribData->PositionBuffer,
		reinterpret_cast< void * >( TRIANGLE_POSITION_DATA ),
		sizeof( TRIANGLE_POSITION_DATA ) );
	
	GX2RCreateBufferUserMemory( &attribData->ColorBuffer,
		reinterpret_cast< void * >( TRIANGLE_COLOR_DATA ),
		sizeof( TRIANGLE_COLOR_DATA ) );

	GX2UTInvalidateBuffer( &attribData->PositionBuffer );
	GX2UTInvalidateBuffer( &attribData->ColorBuffer );
}

static void FreeAttribData( AttribBuffer *attribData )
{
	GX2RDestroyBuffer( &attribData->PositionBuffer );
	GX2RDestroyBuffer( &attribData->ColorBuffer );
}

struct QuadDrawerInternal
{
	DEMOGfxShader SimpleShader;
	AttribBuffer TriangleBuffer;
};

QuadDrawerWiiU::QuadDrawerWiiU() :
	internal_( new QuadDrawerInternal )
{
	GX2UTInitBufferStruct( &internal_->TriangleBuffer.PositionBuffer, GX2R_BIND_VERTEX_BUFFER
		| GX2R_USAGE_CPU_WRITE | GX2R_USAGE_GPU_READ, sizeof( TRIANGLE_POSITION_DATA )
		/ TRIANGLE_VERTEX_NUM, TRIANGLE_VERTEX_NUM );
	GX2RSetBufferName( &internal_->TriangleBuffer.PositionBuffer, "TRIANGLE_POSITION_DATA" );

	GX2UTInitBufferStruct( &internal_->TriangleBuffer.ColorBuffer, GX2R_BIND_VERTEX_BUFFER
		| GX2R_USAGE_CPU_WRITE | GX2R_USAGE_GPU_READ, sizeof( TRIANGLE_COLOR_DATA )
		/ TRIANGLE_VERTEX_NUM, TRIANGLE_VERTEX_NUM );
	GX2RSetBufferName( &internal_->TriangleBuffer.ColorBuffer, "TRIANGLE_COLOR_DATA" );

	InitAttribData( &internal_->TriangleBuffer );
	InitShader( &internal_->SimpleShader, &internal_->TriangleBuffer );
}

QuadDrawerWiiU::~QuadDrawerWiiU()
{
	DEMOGfxFreeShaders( &internal_->SimpleShader );
	FreeAttribData( &internal_->TriangleBuffer );

	delete internal_;
}

void QuadDrawerWiiU::Draw( const SimpleQuad &quad )
{
	DEMO_F32x3 *data = reinterpret_cast< DEMO_F32x3 * >(
		GX2RLockBuffer( &internal_->TriangleBuffer.PositionBuffer )
	);
	for( int i = 0; i < 4; ++i )
	{
		data[ i ].u.v.x = quad.V[ i ].x();
		data[ i ].u.v.y = quad.V[ i ].y();
	}
	GX2RUnlockBuffer( &internal_->TriangleBuffer.PositionBuffer );

	GX2Draw( GX2_PRIMITIVE_QUADS, TRIANGLE_VERTEX_NUM );
}
