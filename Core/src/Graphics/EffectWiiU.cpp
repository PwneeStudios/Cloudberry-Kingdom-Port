#include <Graphics/Effect.h>

#include <cassert>
#include <cafe/demo.h>
#include <cafe/gx2.h>
#include <cafe/demo/demoGfxTypes.h>
#include <Content/ResourcePtr.h>
#include <Content/Texture.h>
#include <Graphics/Types.h>
#include <map>
#include <Utility/Log.h>

static void InitShader( DEMOGfxShader *shader, GX2RBuffer *positionBuffer, u32 &sampler );

struct EffectInternal
{
	std::map<std::string, boost::shared_ptr<EffectParameter> > Parameters;

	DEMOGfxShader Shader;
};

Effect::Effect() :
	internal_( new EffectInternal )
{
}

Effect::~Effect()
{
	delete internal_;
}

void Effect::Load( const std::string &name )
{
	internal_->Parameters[ "SecretDefaultParameter" ] = boost::make_shared<EffectParameter>( 0, 0 );
}

boost::shared_ptr<EffectParameter> Effect::Parameters( const std::string &name )
{
	if( internal_->Parameters.find( name ) == internal_->Parameters.end() )
	{
		return internal_->Parameters[ "SecretDefaultParameter" ];
	}

	return internal_->Parameters[ name ];
}

boost::shared_ptr<EffectTechnique> Effect::Techniques( const std::string &name )
{
	return DefaultTechnique;
}

unsigned int Effect::Attributes( const std::string &name )
{
	return 0;
}

void InitShader( DEMOGfxShader *shader, GX2RBuffer *positionBuffer, u32 &sampler )
{
	/*void *gshBuf;
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

	GX2SetShaders( &shader->fetchShader, shader->pVertexShader, shader->pPixelShader );*/
}
