#include <Graphics/Effect.h>

#include <cassert>
#include <fstream>
#include <gxm.h>
#include <libdbg.h>
#include <map>
#include <sstream>
#include <Utility/Log.h>
#include <vector>

#include "EffectInternalVita.h"

extern const SceGxmProgram _binary_clear_v_gxp_start;
extern const SceGxmProgram _binary_clear_f_gxp_start;
extern const SceGxmProgram _binary_basic_v_gxp_start;
extern const SceGxmProgram _binary_basic_f_gxp_start;

extern const SceGxmProgram _binary_BasicEffect_v_gxp_start;
extern const SceGxmProgram _binary_BasicEffect_f_gxp_start;

extern const SceGxmProgram _binary_BwEffect_v_gxp_start;
extern const SceGxmProgram _binary_BwEffect_f_gxp_start;

extern const SceGxmProgram _binary_Circle_v_gxp_start;
extern const SceGxmProgram _binary_Circle_f_gxp_start;

extern const SceGxmProgram _binary_FireballEffect_v_gxp_start;
extern const SceGxmProgram _binary_FireballEffect_f_gxp_start;

extern const SceGxmProgram _binary_Hsl_v_gxp_start;
extern const SceGxmProgram _binary_Hsl_f_gxp_start;

extern const SceGxmProgram _binary_Hsl_Green_v_gxp_start;
extern const SceGxmProgram _binary_Hsl_Green_f_gxp_start;

extern const SceGxmProgram _binary_Lava_v_gxp_start;
extern const SceGxmProgram _binary_Lava_f_gxp_start;

extern const SceGxmProgram _binary_LightMap_v_gxp_start;
extern const SceGxmProgram _binary_LightMap_f_gxp_start;

extern const SceGxmProgram _binary_LightSource_v_gxp_start;
extern const SceGxmProgram _binary_LightSource_f_gxp_start;

extern const SceGxmProgram _binary_NoTexture_v_gxp_start;
extern const SceGxmProgram _binary_NoTexture_f_gxp_start;

extern const SceGxmProgram _binary_Paint_v_gxp_start;
extern const SceGxmProgram _binary_Paint_f_gxp_start;

extern const SceGxmProgram _binary_Paint_SpriteBatch_v_gxp_start;
extern const SceGxmProgram _binary_Paint_SpriteBatch_f_gxp_start;

extern const SceGxmProgram _binary_screen_v_gxp_start;
extern const SceGxmProgram _binary_screen_f_gxp_start;

extern const SceGxmProgram _binary_Shell_v_gxp_start;
extern const SceGxmProgram _binary_Shell_f_gxp_start;

extern const SceGxmProgram _binary_Text_NoOutline_v_gxp_start;
extern const SceGxmProgram _binary_Text_NoOutline_f_gxp_start;

extern const SceGxmProgram _binary_Text_ThickOutline_v_gxp_start;
extern const SceGxmProgram _binary_Text_ThickOutline_f_gxp_start;

extern const SceGxmProgram _binary_Text_ThinOutline_v_gxp_start;
extern const SceGxmProgram _binary_Text_ThinOutline_f_gxp_start;

extern const SceGxmProgram _binary_Window_v_gxp_start;
extern const SceGxmProgram _binary_Window_f_gxp_start;

static SceGxmShaderPatcher *shaderPatcher = NULL;

#define UNUSED( x )		( void )( x )

static void *patcherHostAlloc(void *userData, uint32_t size)
{
	UNUSED(userData);
	return malloc(size);
}

static void patcherHostFree(void *userData, void *mem)
{
	UNUSED(userData);
	free(mem);
}

// Memory allocation stuff defined in CoreVita.cpp.
extern void *graphicsAlloc(SceKernelMemBlockType type, uint32_t size, uint32_t alignment, uint32_t attribs, SceUID *uid);
extern void graphicsFree(SceUID uid);
extern void *vertexUsseAlloc(uint32_t size, SceUID *uid, uint32_t *usseOffset);
extern void vertexUsseFree(SceUID uid);
extern void *fragmentUsseAlloc(uint32_t size, SceUID *uid, uint32_t *usseOffset);
extern void fragmentUsseFree(SceUID uid);

void InitializePatcher()
{
	// set buffer sizes for this sample
	const uint32_t patcherBufferSize		= 64*1024;
	const uint32_t patcherVertexUsseSize	= 64*1024;
	const uint32_t patcherFragmentUsseSize	= 64*1024;

	// allocate memory for buffers and USSE code
	SceUID patcherBufferUid;
	void *patcherBuffer = graphicsAlloc(
		SCE_KERNEL_MEMBLOCK_TYPE_USER_RWDATA_UNCACHE,
		patcherBufferSize,
		4,
		SCE_GXM_MEMORY_ATTRIB_READ | SCE_GXM_MEMORY_ATTRIB_WRITE,
		&patcherBufferUid);
	SceUID patcherVertexUsseUid;
	uint32_t patcherVertexUsseOffset;
	void *patcherVertexUsse = vertexUsseAlloc(
		patcherVertexUsseSize,
		&patcherVertexUsseUid,
		&patcherVertexUsseOffset);
	SceUID patcherFragmentUsseUid;
	uint32_t patcherFragmentUsseOffset;
	void *patcherFragmentUsse = fragmentUsseAlloc(
		patcherFragmentUsseSize,
		&patcherFragmentUsseUid,
		&patcherFragmentUsseOffset);

	// create a shader patcher
	SceGxmShaderPatcherParams patcherParams;
	memset(&patcherParams, 0, sizeof(SceGxmShaderPatcherParams));
	patcherParams.userData					= NULL;
	patcherParams.hostAllocCallback			= &patcherHostAlloc;
	patcherParams.hostFreeCallback			= &patcherHostFree;
	patcherParams.bufferAllocCallback		= NULL;
	patcherParams.bufferFreeCallback		= NULL;
	patcherParams.bufferMem					= patcherBuffer;
	patcherParams.bufferMemSize				= patcherBufferSize;
	patcherParams.vertexUsseAllocCallback	= NULL;
	patcherParams.vertexUsseFreeCallback	= NULL;
	patcherParams.vertexUsseMem				= patcherVertexUsse;
	patcherParams.vertexUsseMemSize			= patcherVertexUsseSize;
	patcherParams.vertexUsseOffset			= patcherVertexUsseOffset;
	patcherParams.fragmentUsseAllocCallback	= NULL;
	patcherParams.fragmentUsseFreeCallback	= NULL;
	patcherParams.fragmentUsseMem			= patcherFragmentUsse;
	patcherParams.fragmentUsseMemSize		= patcherFragmentUsseSize;
	patcherParams.fragmentUsseOffset		= patcherFragmentUsseOffset;

	int err = sceGxmShaderPatcherCreate(&patcherParams, &shaderPatcher);
	SCE_DBG_ASSERT(err == SCE_OK);
}

void RegisterProgramWithPatcher( const SceGxmProgram *program, SceGxmShaderPatcherId *id )
{
	int err = sceGxmShaderPatcherRegisterProgram( shaderPatcher, program, id );
	SCE_DBG_ASSERT( err == SCE_OK );
}

void CreateVertexProgram( SceGxmShaderPatcherId programId, const SceGxmVertexAttribute *attributes, uint32_t attributeCount, const SceGxmVertexStream *streams, uint32_t streamCount, SceGxmVertexProgram **vertexProgram )
{
	int err = sceGxmShaderPatcherCreateVertexProgram( shaderPatcher, programId, attributes, attributeCount, streams, streamCount, vertexProgram );
	SCE_DBG_ASSERT( err == SCE_OK );
}

void CreateFragmentProgram( SceGxmShaderPatcherId programId, SceGxmOutputRegisterFormat outputFormat, SceGxmMultisampleMode multisampleMode, const SceGxmBlendInfo *blendInfo, const SceGxmProgram *vertexProgram, SceGxmFragmentProgram **fragmentProgram )
{
	int err = sceGxmShaderPatcherCreateFragmentProgram( shaderPatcher, programId, outputFormat, multisampleMode, blendInfo, vertexProgram, fragmentProgram );
	SCE_DBG_ASSERT( err == SCE_OK );
}

void CleanUpPatcher()
{
	sceGxmShaderPatcherDestroy( shaderPatcher );
}

// Pointer to global graphics context. Declared in CoreVita.cpp.
extern SceGxmContext *GraphicsContext;

void Effect::Apply()
{
	sceGxmSetVertexProgram( GraphicsContext, internal_->VertexProgram );
	sceGxmSetFragmentProgram( GraphicsContext, internal_->FragmentProgram );

	void *vertexDefaultBuffer;
	sceGxmReserveVertexDefaultUniformBuffer( GraphicsContext, &vertexDefaultBuffer );
	
	std::map<std::string, boost::shared_ptr<EffectParameter> >::iterator i;
	for( i = internal_->Parameters.begin(); i != internal_->Parameters.end(); ++i )
	{
		i->second->Apply();

		if( !i->second->internal_->Parameter )
			continue;

		sceGxmSetUniformDataF(
			vertexDefaultBuffer,
			i->second->internal_->Parameter,
			0,
			i->second->internal_->NumComponents,
			i->second->internal_->Data
		);
	}
}

Effect::Effect() :
	internal_( new EffectInternal )
{
	internal_->FragmentProgram = 0;
	internal_->VertexProgram = 0;
}

Effect::~Effect()
{
	delete internal_;
}

extern std::string PS3_PATH_PREFIX;

char *LoadShaderFromSDATA( const std::string &path )
{
	char *buffer = 0;
	return buffer;
}

void Effect::Load( const std::string &name )
{
	const SceGxmProgram *vertexProgramGxp	= NULL;
	const SceGxmProgram *fragmentProgramGxp	= NULL;

	if( name == "Shaders/BasicEffect" )
	{
		vertexProgramGxp	= &_binary_BasicEffect_v_gxp_start;
		fragmentProgramGxp	= &_binary_BasicEffect_f_gxp_start;
	}
	else if( name == "Shaders/NoTexture" )
	{
		vertexProgramGxp	= &_binary_NoTexture_v_gxp_start;
		fragmentProgramGxp	= &_binary_NoTexture_f_gxp_start;
	}
	else if( name == "Shaders/Circle" )
	{
		vertexProgramGxp	= &_binary_Circle_v_gxp_start;
		fragmentProgramGxp	= &_binary_Circle_f_gxp_start;
	}
	else if( name == "Shaders/Shell" )
	{
		vertexProgramGxp	= &_binary_Shell_v_gxp_start;
		fragmentProgramGxp	= &_binary_Shell_f_gxp_start;
	}
	else if( name == "Shaders/FireballEffect" )
	{
		vertexProgramGxp	= &_binary_FireballEffect_v_gxp_start;
		fragmentProgramGxp	= &_binary_FireballEffect_f_gxp_start;
	}
	else if( name == "Shaders/LightMap" )
	{
		vertexProgramGxp	= &_binary_LightMap_v_gxp_start;
		fragmentProgramGxp	= &_binary_LightMap_f_gxp_start;
	}
	else if( name == "Shaders/LightSource" )
	{
		vertexProgramGxp	= &_binary_LightSource_v_gxp_start;
		fragmentProgramGxp	= &_binary_LightSource_f_gxp_start;
	}
	else if( name == "Shaders/Hsl_Green" )
	{
		vertexProgramGxp	= &_binary_Hsl_Green_v_gxp_start;
		fragmentProgramGxp	= &_binary_Hsl_Green_f_gxp_start;
	}
	else if( name == "Shaders/Hsl" )
	{
		vertexProgramGxp	= &_binary_Hsl_v_gxp_start;
		fragmentProgramGxp	= &_binary_Hsl_f_gxp_start;
	}
	else if( name == "Shaders/Window" )
	{
		vertexProgramGxp	= &_binary_Window_v_gxp_start;
		fragmentProgramGxp	= &_binary_Window_f_gxp_start;
	}
	else if( name == "Shaders/Text_NoOutline" )
	{
		vertexProgramGxp	= &_binary_Text_NoOutline_v_gxp_start;
		fragmentProgramGxp	= &_binary_Text_NoOutline_f_gxp_start;
	}
	else if( name == "Shaders/Text_ThickOutline" )
	{
		vertexProgramGxp	= &_binary_Text_ThickOutline_v_gxp_start;
		fragmentProgramGxp	= &_binary_Text_ThickOutline_f_gxp_start;
	}
	else if( name == "Shaders/Text_ThinOutline" )
	{
		vertexProgramGxp	= &_binary_Text_ThinOutline_v_gxp_start;
		fragmentProgramGxp	= &_binary_Text_ThinOutline_f_gxp_start;
	}

	assert( vertexProgramGxp && fragmentProgramGxp );

	SceGxmShaderPatcherId vertexProgramId, fragmentProgramId;
	RegisterProgramWithPatcher( vertexProgramGxp, &vertexProgramId );
	RegisterProgramWithPatcher( fragmentProgramGxp, &fragmentProgramId );

	const SceGxmProgramParameter *positionParameter = sceGxmProgramFindParameterByName( vertexProgramGxp, "a_position" );
	const SceGxmProgramParameter *texcoordParameter = sceGxmProgramFindParameterByName( vertexProgramGxp, "a_texcoord" );
	const SceGxmProgramParameter *colorParameter = sceGxmProgramFindParameterByName( vertexProgramGxp, "a_color" );

	struct QuadVert
	{
		Vector2 Position;
		Vector2 TexCoord;
		Vector4 Color;
	};

	SceGxmVertexAttribute vertexAttributes[3];
	vertexAttributes[ 0 ].streamIndex = 0;
	vertexAttributes[ 0 ].offset = offsetof( QuadVert, Position );
	vertexAttributes[ 0 ].format = SCE_GXM_ATTRIBUTE_FORMAT_F32;
	vertexAttributes[ 0 ].componentCount = 2;
	vertexAttributes[ 0 ].regIndex = sceGxmProgramParameterGetResourceIndex( positionParameter );

	vertexAttributes[ 1 ].streamIndex = 0;
	vertexAttributes[ 1 ].offset = offsetof( QuadVert, TexCoord );
	vertexAttributes[ 1 ].format = SCE_GXM_ATTRIBUTE_FORMAT_F32;
	vertexAttributes[ 1 ].componentCount = 2;
	vertexAttributes[ 1 ].regIndex = sceGxmProgramParameterGetResourceIndex( texcoordParameter );

	vertexAttributes[ 2 ].streamIndex = 0;
	vertexAttributes[ 2 ].offset = offsetof( QuadVert, Color );
	vertexAttributes[ 2 ].format = SCE_GXM_ATTRIBUTE_FORMAT_F32;
	vertexAttributes[ 2 ].componentCount = 4;
	vertexAttributes[ 2 ].regIndex = sceGxmProgramParameterGetResourceIndex( colorParameter );

	SceGxmVertexStream vertexStreams[1];
	vertexStreams[ 0 ].stride = sizeof( QuadVert );
	vertexStreams[ 0 ].indexSource = SCE_GXM_INDEX_FORMAT_U16;

	SceGxmVertexProgram *vertexProgram;
	SceGxmFragmentProgram *fragmentProgram;

	CreateVertexProgram( vertexProgramId, vertexAttributes, 3, vertexStreams, 1, &vertexProgram );
	CreateFragmentProgram( fragmentProgramId, SCE_GXM_OUTPUT_REGISTER_FORMAT_UCHAR4, SCE_GXM_MULTISAMPLE_NONE, NULL, vertexProgramGxp, &fragmentProgram );

	uint32_t numParameters = sceGxmProgramGetParameterCount( vertexProgramGxp );

	for( uint32_t i = 0; i < numParameters; ++i )
	{
		const SceGxmProgramParameter *param = sceGxmProgramGetParameter( vertexProgramGxp, i );
		const char *paramName = sceGxmProgramParameterGetName( param );
		SceGxmParameterType paramType = sceGxmProgramParameterGetType( param );
		uint32_t componentCount = sceGxmProgramParameterGetComponentCount( param );
		SceGxmParameterCategory paramCategory = sceGxmProgramParameterGetCategory( param );

		if( paramCategory == SCE_GXM_PARAMETER_CATEGORY_ATTRIBUTE )
			continue;

		internal_->Parameters[ paramName ] = boost::make_shared< EffectParameter >( *this,
			reinterpret_cast< int >( param )
		);
	}

	numParameters = sceGxmProgramGetParameterCount( fragmentProgramGxp );

	for( uint32_t i = 0; i < numParameters; ++i )
	{
		const SceGxmProgramParameter *param = sceGxmProgramGetParameter( fragmentProgramGxp, i );
		const char *paramName = sceGxmProgramParameterGetName( param );
		SceGxmParameterType paramType = sceGxmProgramParameterGetType( param );
		uint32_t componentCount = sceGxmProgramParameterGetComponentCount( param );
		SceGxmParameterCategory paramCategory = sceGxmProgramParameterGetCategory( param );

		if( paramCategory == SCE_GXM_PARAMETER_CATEGORY_ATTRIBUTE
			|| paramCategory == SCE_GXM_PARAMETER_CATEGORY_SAMPLER )
			continue;

		internal_->Parameters[ paramName ] = boost::make_shared< EffectParameter >( *this,
			reinterpret_cast< int >( param )
		);
	}

	internal_->Parameters[ "SecretDefaultParameter" ] = boost::make_shared< EffectParameter >( *this, 0 );

	internal_->VertexProgram = vertexProgram;
	internal_->FragmentProgram = fragmentProgram;

	DefaultTechnique = boost::make_shared<EffectTechnique>(
		boost::shared_ptr<EffectPass>( new EffectPass( *this, 0 ) )
	);

	CurrentTechnique = DefaultTechnique;
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
