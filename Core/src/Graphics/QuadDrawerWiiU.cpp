#include <Graphics/QuadDrawerWiiU.h>

#include <cassert>
#include <cafe/demo.h>
#include <cafe/gx2.h>

static const char *const GSH_SIMPLE_SHADER_FILE = "assets/shaders/demo_gx2/cafe/simple/simple.gsh";

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

static void InitAttribData( AttribBuffer *attribData )
{

}

static void FreeAttribData( AttribBuffer *attribData )
{
	GX2RDestroyBuffer( &attribData->PositionBuffer );
	GX2RDestroyBuffer( &attribData->ColorBuffer );
}

QuadDrawerWiiU::QuadDrawerWiiU()
{

}

QuadDrawerWiiU::~QuadDrawerWiiU()
{
}

void QuadDrawerWiiU::Draw( const SimpleQuad &quad )
{

}
