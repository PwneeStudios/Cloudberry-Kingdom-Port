#include <CoreVita.h>

#include <Architecture/Scheduler.h>
#include <Audio/MediaPlayer.h>
#include <Content/Wad.h>
#include <Core.h>
#include <cstdarg>
#include <cstdlib>
#include <GameLoop.h>
#include <Graphics/QuadDrawer.h>
#include <Graphics/TextDrawer.h>
#include <Input/GamePad.h>
#include <Input/Keyboard.h>
#include <list>
#include <Utility/Error.h>
#include <Utility/Limits.h>
#include <Utility/Log.h>

#include <np.h>
#include <sceconst.h>
#include <libdbg.h>
#include <kernel.h>
#include <display.h>
#include <ctrl.h>
#include <gxm.h>

#include <Utility/ConsoleInformation.h>

// Passphrase and signature from PSN Server Management Tools.
static const SceNpCommunicationId s_npCommunicationId = {
    {'N', 'P', 'W', 'R', '0', '4', '4', '1', '3'},
    '\0',
    0,
    0
};

/***
SceNpCommunicationPassphrase

416ea7dc6715f7fb874be27c584df3efc5757062bc2b3992c74b7d42ee450914995edf73efa5e5e7f6bc4b1687be6a0cf40fab915d7657bd0afe59b8decf07cc7ec6b7d6be22489a874eb7efda3b65d46577a7ce2a423176f8ad38a0ead670ded8c70edb8d4543c0b30e295a769efad5b76e4d00e40e2d93dbca69688ea1f097
***/

static const SceNpCommunicationPassphrase s_npCommunicationPassphrase = {
    {
        0x41,0x6e,0xa7,0xdc,0x67,0x15,0xf7,0xfb,
        0x87,0x4b,0xe2,0x7c,0x58,0x4d,0xf3,0xef,
        0xc5,0x75,0x70,0x62,0xbc,0x2b,0x39,0x92,
        0xc7,0x4b,0x7d,0x42,0xee,0x45,0x09,0x14,
        0x99,0x5e,0xdf,0x73,0xef,0xa5,0xe5,0xe7,
        0xf6,0xbc,0x4b,0x16,0x87,0xbe,0x6a,0x0c,
        0xf4,0x0f,0xab,0x91,0x5d,0x76,0x57,0xbd,
        0x0a,0xfe,0x59,0xb8,0xde,0xcf,0x07,0xcc,
        0x7e,0xc6,0xb7,0xd6,0xbe,0x22,0x48,0x9a,
        0x87,0x4e,0xb7,0xef,0xda,0x3b,0x65,0xd4,
        0x65,0x77,0xa7,0xce,0x2a,0x42,0x31,0x76,
        0xf8,0xad,0x38,0xa0,0xea,0xd6,0x70,0xde,
        0xd8,0xc7,0x0e,0xdb,0x8d,0x45,0x43,0xc0,
        0xb3,0x0e,0x29,0x5a,0x76,0x9e,0xfa,0xd5,
        0xb7,0x6e,0x4d,0x00,0xe4,0x0e,0x2d,0x93,
        0xdb,0xca,0x69,0x68,0x8e,0xa1,0xf0,0x97
    }
};

/***
SceNpCommunicationSignature

b9dde13b0100000000000000a2f2d66966b3f8d64f9c7dc9fa81e8fdd335cfa7b4b0b1dca063cf38f7dc3a46bad2dbf90dbd293f146165764419818cf74d9612680ec39bd3dbc02c3f87dc36a5721baea8ead5085ba7c89e77d29577ad157cd610c1f5b380783070b51dbeb37eec58387f707d89879fac90358847dbe9a912929ad92a92c01f8bfc1d788e5aeea145a44892f8cb5d198d2bbf54ec783952deee
***/

static const SceNpCommunicationSignature s_npCommunicationSignature = {
    {
        0xb9,0xdd,0xe1,0x3b,0x01,0x00,0x00,0x00,
        0x00,0x00,0x00,0x00,0xa2,0xf2,0xd6,0x69,
        0x66,0xb3,0xf8,0xd6,0x4f,0x9c,0x7d,0xc9,
        0xfa,0x81,0xe8,0xfd,0xd3,0x35,0xcf,0xa7,
        0xb4,0xb0,0xb1,0xdc,0xa0,0x63,0xcf,0x38,
        0xf7,0xdc,0x3a,0x46,0xba,0xd2,0xdb,0xf9,
        0x0d,0xbd,0x29,0x3f,0x14,0x61,0x65,0x76,
        0x44,0x19,0x81,0x8c,0xf7,0x4d,0x96,0x12,
        0x68,0x0e,0xc3,0x9b,0xd3,0xdb,0xc0,0x2c,
        0x3f,0x87,0xdc,0x36,0xa5,0x72,0x1b,0xae,
        0xa8,0xea,0xd5,0x08,0x5b,0xa7,0xc8,0x9e,
        0x77,0xd2,0x95,0x77,0xad,0x15,0x7c,0xd6,
        0x10,0xc1,0xf5,0xb3,0x80,0x78,0x30,0x70,
        0xb5,0x1d,0xbe,0xb3,0x7e,0xec,0x58,0x38,
        0x7f,0x70,0x7d,0x89,0x87,0x9f,0xac,0x90,
        0x35,0x88,0x47,0xdb,0xe9,0xa9,0x12,0x92,
        0x9a,0xd9,0x2a,0x92,0xc0,0x1f,0x8b,0xfc,
        0x1d,0x78,0x8e,0x5a,0xee,0xa1,0x45,0xa4,
        0x48,0x92,0xf8,0xcb,0x5d,0x19,0x8d,0x2b,
        0xbf,0x54,0xec,0x78,0x39,0x52,0xde,0xee
    }
};

// Drm key for checking file access.
//static const SceNpDrmKey s_npDrmKey = {
//	{ 0xb1, 0x28, 0xb8, 0x67, 0x56, 0xd4, 0x68, 0x2b, 0x16, 0x18, 0x33, 0x8b, 0x49, 0x66, 0x44, 0xd9 }
//};

// Private.
CoreVita::CoreVita( const CoreVita &other ) :
	game_( other.game_ ),
	qd_( other.qd_ ),
	content_( other.content_ )
{

}

// Private.
CoreVita &CoreVita::operator = ( const CoreVita &rhs )
{
	return *this;
}

// Override music volume when BGM is playing. Defined in MediaPlayerVita.cpp.
extern void SetBGMOverride( bool override );

// Is the system menu open? Defined in ConsoleInformationVita.cpp.
extern bool GLOBAL_SYSTEM_MENU_OPEN;

// Pause and resume the background job system.  Defined in SchedulerVita.cpp.
extern void PauseScheduler();
extern void ResumeScheduler();

// Kick off saves on exit to make sure we save everything. Defined in EzStorage.cpp.
extern void SaveAllOnExit();


// FIXME: EXTERNALS FOR SHARING INFORMATION GLOBALLY!

std::string VITA_PATH_PREFIX;

const int DISPLAY_WIDTH = 960;
const int DISPLAY_HEIGHT = 544;

int GLOBAL_WIDTH = DISPLAY_WIDTH;
int GLOBAL_HEIGHT = DISPLAY_HEIGHT;

int DISPLAY_STRIDE_IN_PIXELS = 1024;
const int DISPLAY_BUFFER_COUNT = 2;
const SceGxmMultisampleMode MSAA_MODE = SCE_GXM_MULTISAMPLE_NONE;
const SceGxmColorFormat DISPLAY_COLOR_FORMAT = SCE_GXM_COLOR_FORMAT_A8B8G8R8;
const uint32_t DISPLAY_PIXEL_FORMAT = SCE_DISPLAY_PIXELFORMAT_A8B8G8R8;

#define UNUSED( x )		( void )( x )
#define ALIGN( x, a )	( ( ( x ) + ( ( a ) - 1 ) ) & ~( ( a ) - 1 ) )

// Preallocate all memory used by video player.  Defined in VideoPlayerVita.cpp.
extern void ReserveVideoPlayerMemory();

extern void KillVideoPlayer();

// Wait for save and load operations to finish.  Defined in EzStorage.cpp.
extern void WaitForSaveLoad();

struct DisplayData
{
	void *address;
};

extern const SceGxmProgram _binary_clear_v_gxp_start;
extern const SceGxmProgram _binary_clear_f_gxp_start;
extern const SceGxmProgram _binary_basic_v_gxp_start;
extern const SceGxmProgram _binary_basic_f_gxp_start;

// Data structure for clear geometry
struct ClearVertex {
	float x;
	float y;
};

// Data structure for basic geometry
struct BasicVertex {
	float x;
	float y;
	float z;
	uint32_t color;
};

// Callback function for displaying a buffer
static void displayCallback(const void *callbackData);

// Helper function to allocate memory and map it for the GPU
void *graphicsAlloc(SceKernelMemBlockType type, uint32_t size, uint32_t alignment, uint32_t attribs, SceUID *uid);

// Helper function to free memory mapped to the GPU
void graphicsFree(SceUID uid);

// Helper function to allocate memory and map it as vertex USSE code for the GPU
void *vertexUsseAlloc(uint32_t size, SceUID *uid, uint32_t *usseOffset);

// Helper function to free memory mapped as vertex USSE code for the GPU
void vertexUsseFree(SceUID uid);

// Helper function to allocate memory and map it as fragment USSE code for the GPU
void *fragmentUsseAlloc(uint32_t size, SceUID *uid, uint32_t *usseOffset);

// Helper function to free memory mapped as fragment USSE code for the GPU
void fragmentUsseFree(SceUID uid);

// Helper function to allocate memory and map it for the GPU
void *graphicsAlloc(SceKernelMemBlockType type, uint32_t size, uint32_t alignment, uint32_t attribs, SceUID *uid);

// Helper function to free memory mapped to the GPU
void graphicsFree(SceUID uid);

SceUID vdmRingBufferUid, vertexRingBufferUid, fragmentRingBufferUid, fragmentUsseRingBufferUid;
void *vdmRingBuffer, *vertexRingBuffer, *fragmentRingBuffer, *fragmentUsseRingBuffer;
uint32_t fragmentUsseRingBufferOffset;
SceGxmContext *GraphicsContext = NULL;
	
SceGxmRenderTarget *renderTarget;
void *displayBufferData[ DISPLAY_BUFFER_COUNT ];
SceUID displayBufferUid[ DISPLAY_BUFFER_COUNT ];
SceGxmColorSurface displaySurface[ DISPLAY_BUFFER_COUNT ];
SceGxmSyncObject *displayBufferSync[ DISPLAY_BUFFER_COUNT ];
	
SceGxmDepthStencilSurface depthSurface;

SceGxmVertexProgram *clearVertexProgram = NULL;
SceGxmFragmentProgram *clearFragmentProgram = NULL;
SceGxmVertexProgram *basicVertexProgram = NULL;
SceGxmFragmentProgram *basicFragmentProgram = NULL;
	
ClearVertex *clearVertices;
uint16_t *clearIndices;
BasicVertex *basicVertices;
uint16_t *basicIndices;

SceGxmProgramParameter *wvpParam;

// Patcher stuff. Defined in EffectVita.cpp.
extern void InitializePatcher();
extern void RegisterProgramWithPatcher( const SceGxmProgram *program, SceGxmShaderPatcherId *id );
extern void CreateVertexProgram( SceGxmShaderPatcherId programId, const SceGxmVertexAttribute *attributes, uint32_t attributeCount, const SceGxmVertexStream *streams, uint32_t streamCount, SceGxmVertexProgram **vertexProgram );
extern void CreateFragmentProgram( SceGxmShaderPatcherId programId, SceGxmOutputRegisterFormat outputFormat, SceGxmMultisampleMode multisampleMode, const SceGxmBlendInfo *blendInfo, const SceGxmProgram *vertexProgram, SceGxmFragmentProgram **fragmentProgram );
extern void CleanUpPatcher();

CoreVita::CoreVita( GameLoop &game ) :
	running_( false ),
	game_( game ),
	qd_( 0 ),
	content_( 0 ),
	scheduler_( 0 )
{
	int err = SCE_OK;

	SceGxmInitializeParams initializeParams;
	memset( &initializeParams, 0, sizeof( SceGxmInitializeParams ) );
	initializeParams.flags							= 0;
	initializeParams.displayQueueMaxPendingCount	= 2;
	initializeParams.displayQueueCallback			= displayCallback;
	initializeParams.displayQueueCallbackDataSize	= sizeof( DisplayData );
	initializeParams.parameterBufferSize			= SCE_GXM_DEFAULT_PARAMETER_BUFFER_SIZE;

	err = sceGxmInitialize( &initializeParams );
	SCE_DBG_ASSERT( err == SCE_OK );
	
	vdmRingBuffer = graphicsAlloc(
		SCE_KERNEL_MEMBLOCK_TYPE_USER_RWDATA_UNCACHE,
		SCE_GXM_DEFAULT_VDM_RING_BUFFER_SIZE,
		4,
		SCE_GXM_MEMORY_ATTRIB_READ,
		&vdmRingBufferUid
	);

	vertexRingBuffer = graphicsAlloc(
		SCE_KERNEL_MEMBLOCK_TYPE_USER_RWDATA_UNCACHE,
		SCE_GXM_DEFAULT_VERTEX_RING_BUFFER_SIZE,
		4,
		SCE_GXM_MEMORY_ATTRIB_READ,
		&vertexRingBufferUid);
	
	fragmentRingBuffer = graphicsAlloc(
		SCE_KERNEL_MEMBLOCK_TYPE_USER_RWDATA_UNCACHE,
		SCE_GXM_DEFAULT_FRAGMENT_RING_BUFFER_SIZE,
		4,
		SCE_GXM_MEMORY_ATTRIB_READ,
		&fragmentRingBufferUid
	);
	
	fragmentUsseRingBuffer = fragmentUsseAlloc(
		SCE_GXM_DEFAULT_FRAGMENT_USSE_RING_BUFFER_SIZE,
		&fragmentUsseRingBufferUid,
		&fragmentUsseRingBufferOffset
	);

	SceGxmContextParams contextParams;
	memset( &contextParams, 0, sizeof( SceGxmContextParams ) );
	contextParams.hostMem						= malloc( SCE_GXM_MINIMUM_CONTEXT_HOST_MEM_SIZE );
	contextParams.hostMemSize					= SCE_GXM_MINIMUM_CONTEXT_HOST_MEM_SIZE;
	contextParams.vdmRingBufferMem				= vdmRingBuffer;
	contextParams.vdmRingBufferMemSize			= SCE_GXM_DEFAULT_VDM_RING_BUFFER_SIZE;
	contextParams.vertexRingBufferMem			= vertexRingBuffer;
	contextParams.vertexRingBufferMemSize		= SCE_GXM_DEFAULT_VERTEX_RING_BUFFER_SIZE;
	contextParams.fragmentRingBufferMem			= fragmentRingBuffer;
	contextParams.fragmentRingBufferMemSize		= SCE_GXM_DEFAULT_FRAGMENT_RING_BUFFER_SIZE;
	contextParams.fragmentUsseRingBufferMem		= fragmentUsseRingBuffer;
	contextParams.fragmentUsseRingBufferMemSize	= SCE_GXM_DEFAULT_FRAGMENT_USSE_RING_BUFFER_SIZE;
	contextParams.fragmentUsseRingBufferOffset	= fragmentUsseRingBufferOffset;

	err = sceGxmCreateContext( &contextParams, &GraphicsContext );
	SCE_DBG_ASSERT( err == SCE_OK );

	SceGxmRenderTargetParams renderTargetParams;
	memset( &renderTargetParams, 0, sizeof( SceGxmRenderTargetParams ) );
	renderTargetParams.flags				= 0;
	renderTargetParams.width				= DISPLAY_WIDTH;
	renderTargetParams.height				= DISPLAY_HEIGHT;
	renderTargetParams.scenesPerFrame		= 1;
	renderTargetParams.multisampleMode		= MSAA_MODE;
	renderTargetParams.multisampleLocations	= 0;
	renderTargetParams.driverMemBlock		= SCE_UID_INVALID_UID;

	err = sceGxmCreateRenderTarget( &renderTargetParams, &renderTarget );
	SCE_DBG_ASSERT( err == SCE_OK );

	for( uint32_t i = 0; i < DISPLAY_BUFFER_COUNT; ++i )
	{
		// allocate memory for display
		displayBufferData[ i ] = graphicsAlloc(
			SCE_KERNEL_MEMBLOCK_TYPE_USER_CDRAM_RWDATA,
			4 * DISPLAY_STRIDE_IN_PIXELS * DISPLAY_HEIGHT,
			SCE_GXM_COLOR_SURFACE_ALIGNMENT,
			SCE_GXM_MEMORY_ATTRIB_READ | SCE_GXM_MEMORY_ATTRIB_WRITE,
			&displayBufferUid[ i ]
		);

		// memset the buffer to black
		for( uint32_t y = 0; y < DISPLAY_HEIGHT; ++y )
		{
			uint32_t *row = ( uint32_t * )displayBufferData[ i ] + y * DISPLAY_STRIDE_IN_PIXELS;
			for( uint32_t x = 0; x < DISPLAY_WIDTH; ++x )
			{
				row[ x ] = 0xff000000;
			}
		}

		// initialize a color surface for this display buffer
		err = sceGxmColorSurfaceInit(
			&displaySurface[ i ],
			DISPLAY_COLOR_FORMAT,
			SCE_GXM_COLOR_SURFACE_LINEAR,
			( MSAA_MODE == SCE_GXM_MULTISAMPLE_NONE ) ? SCE_GXM_COLOR_SURFACE_SCALE_NONE : SCE_GXM_COLOR_SURFACE_SCALE_MSAA_DOWNSCALE,
			SCE_GXM_OUTPUT_REGISTER_SIZE_32BIT,
			DISPLAY_WIDTH,
			DISPLAY_HEIGHT,
			DISPLAY_STRIDE_IN_PIXELS,
			displayBufferData[ i ]
		);
		SCE_DBG_ASSERT( err == SCE_OK );

		// create a sync object that we will associate with this buffer
		err = sceGxmSyncObjectCreate( &displayBufferSync[i] );
		SCE_DBG_ASSERT( err == SCE_OK );
	}

	// compute the memory footprint of the depth buffer
	const uint32_t alignedWidth = ALIGN( DISPLAY_WIDTH, SCE_GXM_TILE_SIZEX );
	const uint32_t alignedHeight = ALIGN( DISPLAY_HEIGHT, SCE_GXM_TILE_SIZEY );
	uint32_t sampleCount = alignedWidth * alignedHeight;
	uint32_t depthStrideInSamples = alignedWidth;
	if( MSAA_MODE == SCE_GXM_MULTISAMPLE_4X )
	{
		// samples increase in X and Y
		sampleCount *= 4;
		depthStrideInSamples *= 2;
	}
	else if (MSAA_MODE == SCE_GXM_MULTISAMPLE_2X)
	{
		// samples increase in Y only
		sampleCount *= 2;
	}

	// allocate it
	SceUID depthBufferUid;
	void *depthBufferData = graphicsAlloc(
		SCE_KERNEL_MEMBLOCK_TYPE_USER_RWDATA_UNCACHE,
		4 * sampleCount,
		SCE_GXM_DEPTHSTENCIL_SURFACE_ALIGNMENT,
		SCE_GXM_MEMORY_ATTRIB_READ | SCE_GXM_MEMORY_ATTRIB_WRITE,
		&depthBufferUid
	);

	// create the SceGxmDepthStencilSurface structure
	err = sceGxmDepthStencilSurfaceInit(
		&depthSurface,
		SCE_GXM_DEPTH_STENCIL_FORMAT_S8D24,
		SCE_GXM_DEPTH_STENCIL_SURFACE_TILED,
		depthStrideInSamples,
		depthBufferData,
		NULL
	);
	SCE_DBG_ASSERT( err == SCE_OK );

	InitializePatcher();

	// use embedded GXP files
	const SceGxmProgram *const clearVertexProgramGxp	= &_binary_clear_v_gxp_start;
	const SceGxmProgram *const clearFragmentProgramGxp	= &_binary_clear_f_gxp_start;
	const SceGxmProgram *const basicVertexProgramGxp	= &_binary_basic_v_gxp_start;
	const SceGxmProgram *const basicFragmentProgramGxp	= &_binary_basic_f_gxp_start;

	// register programs with the patcher
	SceGxmShaderPatcherId clearVertexProgramId;
	SceGxmShaderPatcherId clearFragmentProgramId;
	SceGxmShaderPatcherId basicVertexProgramId;
	SceGxmShaderPatcherId basicFragmentProgramId;
	RegisterProgramWithPatcher( clearVertexProgramGxp, &clearVertexProgramId );
	RegisterProgramWithPatcher( clearFragmentProgramGxp, &clearFragmentProgramId );
	RegisterProgramWithPatcher( basicVertexProgramGxp, &basicVertexProgramId );
	RegisterProgramWithPatcher( basicFragmentProgramGxp, &basicFragmentProgramId );

	// get attributes by name to create vertex format bindings
	const SceGxmProgramParameter *paramClearPositionAttribute = sceGxmProgramFindParameterByName(clearVertexProgramGxp, "aPosition");
	SCE_DBG_ASSERT(paramClearPositionAttribute && (sceGxmProgramParameterGetCategory(paramClearPositionAttribute) == SCE_GXM_PARAMETER_CATEGORY_ATTRIBUTE));

	// create clear vertex format
	SceGxmVertexAttribute clearVertexAttributes[1];
	SceGxmVertexStream clearVertexStreams[1];
	clearVertexAttributes[0].streamIndex = 0;
	clearVertexAttributes[0].offset = 0;
	clearVertexAttributes[0].format = SCE_GXM_ATTRIBUTE_FORMAT_F32;
	clearVertexAttributes[0].componentCount = 2;
	clearVertexAttributes[0].regIndex = sceGxmProgramParameterGetResourceIndex(paramClearPositionAttribute);
	clearVertexStreams[0].stride = sizeof(ClearVertex);
	clearVertexStreams[0].indexSource = SCE_GXM_INDEX_SOURCE_INDEX_16BIT;

	// create sclear programs
	CreateVertexProgram( clearVertexProgramId, clearVertexAttributes, 1, clearVertexStreams, 1, &clearVertexProgram );
	CreateFragmentProgram( clearFragmentProgramId, SCE_GXM_OUTPUT_REGISTER_FORMAT_UCHAR4, MSAA_MODE, NULL, clearVertexProgramGxp, &clearFragmentProgram );

	// create the clear triangle vertex/index data
	SceUID clearVerticesUid;
	SceUID clearIndicesUid;
	clearVertices = (ClearVertex *)graphicsAlloc(
		SCE_KERNEL_MEMBLOCK_TYPE_USER_RWDATA_UNCACHE,
		3*sizeof(ClearVertex),
		4,
		SCE_GXM_MEMORY_ATTRIB_READ,
		&clearVerticesUid);
	clearIndices = (uint16_t *)graphicsAlloc(
		SCE_KERNEL_MEMBLOCK_TYPE_USER_RWDATA_UNCACHE,
		3*sizeof(uint16_t),
		2,
		SCE_GXM_MEMORY_ATTRIB_READ,
		&clearIndicesUid);

	clearVertices[0].x = -1.0f;
	clearVertices[0].y = -1.0f;
	clearVertices[1].x =  3.0f;
	clearVertices[1].y = -1.0f;
	clearVertices[2].x = -1.0f;
	clearVertices[2].y =  3.0f;

	clearIndices[0] = 0;
	clearIndices[1] = 1;
	clearIndices[2] = 2;

	// get attributes by name to create vertex format bindings
	// first retrieve the underlying program to extract binding information
	const SceGxmProgramParameter *paramBasicPositionAttribute = sceGxmProgramFindParameterByName(basicVertexProgramGxp, "aPosition");
	SCE_DBG_ASSERT(paramBasicPositionAttribute && (sceGxmProgramParameterGetCategory(paramBasicPositionAttribute) == SCE_GXM_PARAMETER_CATEGORY_ATTRIBUTE));
	const SceGxmProgramParameter *paramBasicColorAttribute = sceGxmProgramFindParameterByName(basicVertexProgramGxp, "aColor");
	SCE_DBG_ASSERT(paramBasicColorAttribute && (sceGxmProgramParameterGetCategory(paramBasicColorAttribute) == SCE_GXM_PARAMETER_CATEGORY_ATTRIBUTE));

	// create shaded triangle vertex format
	SceGxmVertexAttribute basicVertexAttributes[2];
	SceGxmVertexStream basicVertexStreams[1];
	basicVertexAttributes[0].streamIndex = 0;
	basicVertexAttributes[0].offset = 0;
	basicVertexAttributes[0].format = SCE_GXM_ATTRIBUTE_FORMAT_F32;
	basicVertexAttributes[0].componentCount = 3;
	basicVertexAttributes[0].regIndex = sceGxmProgramParameterGetResourceIndex(paramBasicPositionAttribute);
	basicVertexAttributes[1].streamIndex = 0;
	basicVertexAttributes[1].offset = 12;
	basicVertexAttributes[1].format = SCE_GXM_ATTRIBUTE_FORMAT_U8N;
	basicVertexAttributes[1].componentCount = 4;
	basicVertexAttributes[1].regIndex = sceGxmProgramParameterGetResourceIndex(paramBasicColorAttribute);
	basicVertexStreams[0].stride = sizeof(BasicVertex);
	basicVertexStreams[0].indexSource = SCE_GXM_INDEX_SOURCE_INDEX_16BIT;

	// create shaded triangle shaders
	CreateVertexProgram( basicVertexProgramId, basicVertexAttributes, 2, basicVertexStreams, 1, &basicVertexProgram );
	CreateFragmentProgram( basicFragmentProgramId, SCE_GXM_OUTPUT_REGISTER_FORMAT_UCHAR4, MSAA_MODE, NULL, basicVertexProgramGxp, &basicFragmentProgram );
	
	// find vertex uniforms by name and cache parameter information
	wvpParam = const_cast< SceGxmProgramParameter * >( sceGxmProgramFindParameterByName(basicVertexProgramGxp, "wvp") );
	SCE_DBG_ASSERT(wvpParam && (sceGxmProgramParameterGetCategory(wvpParam) == SCE_GXM_PARAMETER_CATEGORY_UNIFORM));

	// create shaded triangle vertex/index data
	SceUID basicVerticesUid;
	SceUID basicIndiceUid;
	basicVertices = (BasicVertex *)graphicsAlloc(
		SCE_KERNEL_MEMBLOCK_TYPE_USER_RWDATA_UNCACHE,
		3*sizeof(BasicVertex),
		4,
		SCE_GXM_MEMORY_ATTRIB_READ,
		&basicVerticesUid);
	basicIndices = (uint16_t *)graphicsAlloc(
		SCE_KERNEL_MEMBLOCK_TYPE_USER_RWDATA_UNCACHE,
		3*sizeof(uint16_t),
		2,
		SCE_GXM_MEMORY_ATTRIB_READ,
		&basicIndiceUid);

	basicVertices[0].x = -0.5f;
	basicVertices[0].y = -0.5f;
	basicVertices[0].z = 0.0f;
	basicVertices[0].color = 0xff0000ff;
	basicVertices[1].x = 0.5f;
	basicVertices[1].y = -0.5f;
	basicVertices[1].z = 0.0f;
	basicVertices[1].color = 0xff00ff00;
	basicVertices[2].x = -0.5f;
	basicVertices[2].y = 0.5f;
	basicVertices[2].z = 0.0f;
	basicVertices[2].color = 0xffff0000;

	basicIndices[0] = 0;
	basicIndices[1] = 1;
	basicIndices[2] = 2;

	scheduler_ = new Scheduler;

	content_ = new Wad( VITA_PATH_PREFIX + "ContentVita/" );

	qd_ = new QuadDrawer;

	td_ = new TextDrawer;

	GamePad::Initialize();
	MediaPlayer::Initialize();
}

CoreVita::~CoreVita()
{
	GamePad::Shutdown();

	delete td_;

	delete qd_;

	delete content_;

	delete scheduler_;

	CleanUpPatcher();

	// Need to shut down media player last as scheduler could still play a song.
	MediaPlayer::Shutdown();

	sceGxmFinish( GraphicsContext );
}

static SceNpTrophyContext TrophyContext;
static SceNpTrophyHandle TrophyHandle;
static bool ContextRegistered;
extern std::list< ErrorType > GLOBAL_ERROR_QUEUE;

bool GetTrophyContext( SceNpTrophyContext &GraphicsContext, SceNpTrophyHandle &handle )
{
	if( !ContextRegistered )
		return false;

	GraphicsContext = TrophyContext;
	handle = TrophyHandle;

	return true;
}

void ForceGetTrophyContext( SceNpTrophyContext &GraphicsContext, SceNpTrophyHandle &handle )
{
	GraphicsContext = TrophyContext;
	handle = TrophyHandle;
}

//int TrophyStatusCallback( SceNpTrophyContext GraphicsContext, SceNpTrophyStatus status, int completed, int total, void *arg )
//{
//	int ret = 0;
//
//	switch( status )
//	{
//	case SCE_NP_TROPHY_STATUS_NOT_INSTALLED:
//		LOG_WRITE( "Trophy configuration not installed.\n" );
//		break;
//	case SCE_NP_TROPHY_STATUS_DATA_CORRUPT:
//		LOG_WRITE( "Trophy data is corrupt.\n" );
//		break;
//	case SCE_NP_TROPHY_STATUS_INSTALLED:
//		LOG_WRITE( "Trophy configuration has been installed.\n" );
//		break;
//	case SCE_NP_TROPHY_STATUS_REQUIRES_UPDATE:
//		LOG_WRITE( "Trophy configuration requires update.\n" );
//		break;
//	case SCE_NP_TROPHY_STATUS_CHANGES_DETECTED:
//		LOG_WRITE( "Trophy changes detected.\n" );
//		break;
//	case SCE_NP_TROPHY_STATUS_UNKNOWN:
//		LOG_WRITE( "Trophy status unknown.\n" );
//		break;
//	default:
//		LOG_WRITE( "Trophy status: %d\n", status );
//		break;
//	}
//
//	return ret;
//}

// Stuff to localize the register trophy message.
static std::string WstringToUtf8( const std::wstring& str )
{
	char utf8[ 512 ];
	size_t inSize = str.size();
	size_t outSize = sizeof( utf8 );
	// FIXME: This was only compiling for PS3
	//if( l10n_convert_str( l10n_get_converter( L10N_UTF16, L10N_UTF8 ), str.c_str(), &inSize, utf8, &outSize ) != ConversionOK )
	//	return "";

	return std::string( utf8, utf8 + outSize );
}

static std::wstring Format( const wchar_t *format, ... )
{
	wchar_t buffer[512];

	va_list args;
	va_start( args, format );
	vswprintf( buffer, sizeof( buffer ) / sizeof( wchar_t ), format, args );
	va_end( args );

	return std::wstring( buffer );
}

bool gTrophyContextRegistered = true;

// Space needed for trophy, 
//extern uint64_t RequiredTrophySpace;

void RegisterTrophyContextThread( uint64_t GraphicsContext )
{
	ContextRegistered = false;

	// Register trophy.
	// ...

	gTrophyContextRegistered = true;
	LOG_WRITE( "Trophy configuration done.\n" );

	//sys_ppu_thread_exit( 0 );
}

static SceNpId NPId;
static int ScoreTitleContext = 0;
static bool NPIdObtained = false;

bool GetNPScoreContext( int &id )
{
	if( !NPIdObtained )
		return false;

	id = ScoreTitleContext;

	return true;
}

bool IsNPAvailable()
{
	return NPIdObtained;
}

void ConnectToNPThread( uint64_t GraphicsContext )
{
	LOG_WRITE( "stub: fix me! ConnectToNPThread" );

	//int ret = sceNpManagerGetNpId( &NPId );
	//switch( ret )
	//{
	//case SCE_NP_ERROR_NOT_INITIALIZED:
	//case SCE_NP_ERROR_INVALID_ARGUMENT:
	//case SCE_NP_ERROR_INVALID_STATE:
	//case SCE_NP_ERROR_OFFLINE:
	//	sys_ppu_thread_exit( 0 );
	//	return;
	//	break;

	//case 0:
	//	break;
	//}

	//ret = sceNpScoreCreateTitleCtx( &s_npCommunicationId, &s_npCommunicationPassphrase, &NPId );
	//if( ret > 0 )
	//{
	//	ScoreTitleContext = ret;
	//	NPIdObtained = true;
	//}
	//else
	//	LOG_WRITE( "Coldn't get score title GraphicsContext: 0x%x\n", ret );

	//sys_ppu_thread_exit( 0 );
}

void ConnectToNP()
{
	LOG_WRITE( "stub: fix me! ConnectToNP" );

	if( NPIdObtained )
	{
		LOG_WRITE( "Tried to connect to NP multiple times!\n" );
		return;
	}

	LOG_WRITE( "Connecting to NP!\n" );

	// Kick off NP connection.
	//sys_ppu_thread_t tid;
	//int ret = sys_ppu_thread_create( &tid, ConnectToNPThread, 0,
	//	1001, 16 * 1024, 0, "ConnectToNP" );
	//if( ret != 0 )
	//	LOG_WRITE( "Failed to start ConnectToNP: 0x%x\n", ret );
}

ErrorType GLOBAL_NP_DISCONNECT_MESSAGE;

void DisconnectFromNP()
{
	LOG_WRITE( "stub: fix me! DisconnectFromNP" );

	//DisplayError( GLOBAL_NP_DISCONNECT_MESSAGE );
	//LOG_WRITE( "Disconnecting from NP\n" );

	//if( NPIdObtained )
	//{
	//	sceNpScoreDestroyTitleCtx( ScoreTitleContext );
	//}

	NPIdObtained = false;
}

void NPManagerCallback( int event, int result, void *arg )
{
	LOG_WRITE( "stub: fix me! NPManagerCallback" );

	LOG_WRITE( "NP EVENT: %d\tRESULT: %d\n", event, result );
	//switch( event )
	//{
	//case SCE_NP_MANAGER_STATUS_OFFLINE:
	//	DisconnectFromNP();
	//	break;
	//case SCE_NP_MANAGER_STATUS_GETTING_TICKET:
	//	break;
	//case SCE_NP_MANAGER_STATUS_GETTING_PROFILE:
	//	break;
	//case SCE_NP_MANAGER_STATUS_LOGGING_IN:
	//	break;
	//case SCE_NP_MANAGER_STATUS_ONLINE:
	//	{
	//		int id;
	//		if( !GetNPScoreContext( id ) )
	//			ConnectToNP();
	//	}
	//	break;
	//}
}

static bool ErrorDialogOpen = false;
static ErrorType CurrentError( 0 );

void ErrorDialogCallback( int buttonType, void *userData )
{
	LOG_WRITE( "stub: fix me! ErrorDialogCallback" );

	//ErrorType::CompleteCallback complete = CurrentError.GetComplete();

	//switch( buttonType )
	//{
	//case CELL_MSGDIALOG_BUTTON_YES:
	//	if( complete )
	//		complete( true );
	//	break;
	//case CELL_MSGDIALOG_BUTTON_NO:
	//	if( complete )
	//		complete( false );
	//	break;

	//default:
	//	if( complete )
	//		complete( false );
	//	break;
	//}

	ErrorDialogOpen = false;
}

#define NP_POOL_SIZE (128 * 1024)
static uint8_t NPPool[ NP_POOL_SIZE ];

void DebugFrame(float r, float g, float b)
{
	static int count = 0;

	/*LOG_WRITE( "stub: fix me! DebugFrame" );

	glEnable(GL_SCISSOR_TEST);
	glViewport(0, 0, GLOBAL_WIDTH, GLOBAL_HEIGHT);

	for( int i = 0; i < 2; ++i )
	{
		glScissor(0, 0, GLOBAL_WIDTH, GLOBAL_HEIGHT);
		glClearColor( r, g, b, 1 );
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

		int j = 0;
		for( int i = 31; i >= 0; --i)
		{
			glScissor(j, 0, 32, 128);

			if( count & (1 << i) )
				glClearColor( 1, 1, 1, 1 );
			else
				glClearColor( 0, 0, 0, 1 );

			glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

			j += 33;
		}

		psglSwap();
	}*/
	
	++count;
	//glDisable(GL_SCISSOR_TEST);
}

void NPDRMInvalidCompleteCallback( bool yes )
{
	LOG_WRITE( "stub: fix me! NPDRMInvalidCompleteCallback" );

	//glFinish();
	CORE.Exit();
}

void CheckNPDRMFileThread( uint64_t GraphicsContext )
{
	LOG_WRITE( "stub: fix me! CheckNPDRMFileThread" );

	//std::string file_path = VITA_PATH_PREFIX + "UNLOCK.EDAT";
	//int ret = sceNpDrmIsAvailable2( &s_npDrmKey, file_path.c_str() );
	//
	//if( ret == 0 )
	//{
	//	// Good to go.
	//}

	//sys_ppu_thread_exit( 0 );
}

int CoreVita::Run()
{
	running_ = true;

	// initialize controller data
	SceCtrlData ctrlData;
	memset(&ctrlData, 0, sizeof(ctrlData));

	game_.Initialize();

	// message for SDK sample auto test
	printf("## api_libgxm/basic: INIT SUCCEEDED ##\n");

	// loop until exit
	uint32_t backBufferIndex = 0;
	uint32_t frontBufferIndex = 0;
	float rotationAngle = 0.0f;
	bool quit = false;

	while( running_ )
	{
		GamePad::Update();

		scheduler_->MainThread();

		// check control data
		sceCtrlPeekBufferPositive(0, &ctrlData, 1);

		// update triangle angle
		rotationAngle += SCE_MATH_TWOPI/60.0f;
		if (rotationAngle > SCE_MATH_TWOPI)
			rotationAngle -= SCE_MATH_TWOPI;

		// set up a 4x4 matrix for a rotation
		float aspectRatio = (float)DISPLAY_WIDTH/(float)DISPLAY_HEIGHT;

		float s = sin(rotationAngle);
		float c = cos(rotationAngle);

		float wvpData[16];
		wvpData[ 0] = c/aspectRatio;
		wvpData[ 1] = s;
		wvpData[ 2] = 0.0f;
		wvpData[ 3] = 0.0f;

		wvpData[ 4] = -s/aspectRatio;
		wvpData[ 5] = c;
		wvpData[ 6] = 0.0f;
		wvpData[ 7] = 0.0f;

		wvpData[ 8] = 0.0f;
		wvpData[ 9] = 0.0f;
		wvpData[10] = 1.0f;
		wvpData[11] = 0.0f;

		wvpData[12] = 0.0f;
		wvpData[13] = 0.0f;
		wvpData[14] = 0.0f;
		wvpData[15] = 1.0f;

		/* -----------------------------------------------------------------
			12. Rendering step

			This sample renders a single scene containing the two triangles,
			the clear triangle followed by the spinning triangle.  Before
			any drawing can take place, a scene must be started.  We render
			to the back buffer, so it is also important to use a sync object
			to ensure that these rendering operations are synchronized with
			display operations.

			The clear triangle shaders do not declare any uniform variables,
			so this may be rendered immediately after setting the vertex and
			fragment program.

			The spinning triangle vertex program declares a matrix parameter,
			so this forms part of the vertex default uniform buffer and must
			be written before the triangle can be drawn.

			Once both triangles have been drawn the scene can be ended, which
			submits it for rendering on the GPU.
		   ----------------------------------------------------------------- */

		// start rendering to the main render target
		sceGxmBeginScene(
			GraphicsContext,
			0,
			renderTarget,
			NULL,
			NULL,
			displayBufferSync[backBufferIndex],
			&displaySurface[backBufferIndex],
			&depthSurface);

		game_.Update();

		qd_->Flush();

		// set clear shaders
		sceGxmSetVertexProgram(GraphicsContext, clearVertexProgram);
		sceGxmSetFragmentProgram(GraphicsContext, clearFragmentProgram);

		// draw the clear triangle
		sceGxmSetVertexStream(GraphicsContext, 0, clearVertices);
		sceGxmDraw(GraphicsContext, SCE_GXM_PRIMITIVE_TRIANGLES, SCE_GXM_INDEX_FORMAT_U16, clearIndices, 3);

		// render the rotating triangle
		sceGxmSetVertexProgram(GraphicsContext, basicVertexProgram);
		sceGxmSetFragmentProgram(GraphicsContext, basicFragmentProgram);

		// set the vertex program constants
		void *vertexDefaultBuffer;
		sceGxmReserveVertexDefaultUniformBuffer(GraphicsContext, &vertexDefaultBuffer);
		sceGxmSetUniformDataF(vertexDefaultBuffer, wvpParam, 0, 16, wvpData);

		// draw the spinning triangle
		sceGxmSetVertexStream(GraphicsContext, 0, basicVertices);
		sceGxmDraw(GraphicsContext, SCE_GXM_PRIMITIVE_TRIANGLES, SCE_GXM_INDEX_FORMAT_U16, basicIndices, 3);

		// end the scene on the main render target, submitting rendering work to the GPU
		sceGxmEndScene(GraphicsContext, NULL, NULL);

		// PA heartbeat to notify end of frame
		sceGxmPadHeartbeat(&displaySurface[backBufferIndex], displayBufferSync[backBufferIndex]);

		/* -----------------------------------------------------------------
			13. Flip operation

			Now we have finished submitting rendering work for this frame it
			is time to submit a flip operation.  As part of specifying this
			flip operation we must provide the sync objects for both the old
			buffer and the new buffer.  This is to allow synchronization both
			ways: to not flip until rendering is complete, but also to ensure
			that future rendering to these buffers does not start until the
			flip operation is complete.

			The callback function will be called from an internal thread once
			queued GPU operations involving the sync objects is complete.
			Assuming we have not reached our maximum number of queued frames,
			this function returns immediately.

			Once we have queued our flip, we manually cycle through our back
			buffers before starting the next frame.
		   ----------------------------------------------------------------- */

		// queue the display swap for this frame
		DisplayData displayData;
		displayData.address = displayBufferData[backBufferIndex];
		sceGxmDisplayQueueAddEntry(
			displayBufferSync[frontBufferIndex],	// front buffer is OLD buffer
			displayBufferSync[backBufferIndex],		// back buffer is NEW buffer
			&displayData);

		// update buffer indices
		frontBufferIndex = backBufferIndex;
		backBufferIndex = (backBufferIndex + 1) % DISPLAY_BUFFER_COUNT;
	}

	return 0;
}

void CoreVita::Exit()
{
	running_ = false;
}

void displayCallback(const void *callbackData)
{
	SceDisplayFrameBuf framebuf;
	int err = SCE_OK;
	UNUSED(err);

	// Cast the parameters back
	const DisplayData *displayData = (const DisplayData *)callbackData;

	// Swap to the new buffer on the next VSYNC
	memset(&framebuf, 0x00, sizeof(SceDisplayFrameBuf));
	framebuf.size        = sizeof(SceDisplayFrameBuf);
	framebuf.base        = displayData->address;
	framebuf.pitch       = DISPLAY_STRIDE_IN_PIXELS;
	framebuf.pixelformat = DISPLAY_PIXEL_FORMAT;
	framebuf.width       = DISPLAY_WIDTH;
	framebuf.height      = DISPLAY_HEIGHT;
	err = sceDisplaySetFrameBuf(&framebuf, SCE_DISPLAY_UPDATETIMING_NEXTVSYNC);
	SCE_DBG_ASSERT(err == SCE_OK);

	// Block this callback until the swap has occurred and the old buffer
	// is no longer displayed
	err = sceDisplayWaitVblankStart();
	SCE_DBG_ASSERT(err == SCE_OK);
}

void *graphicsAlloc(SceKernelMemBlockType type, uint32_t size, uint32_t alignment, uint32_t attribs, SceUID *uid)
{
	int err = SCE_OK;
	UNUSED(err);

	/*	Since we are using sceKernelAllocMemBlock directly, we cannot directly
		use the alignment parameter.  Instead, we must allocate the size to the
		minimum for this memblock type, and just assert that this will cover
		our desired alignment.

		Developers using their own heaps should be able to use the alignment
		parameter directly for more minimal padding.
	*/
	if (type == SCE_KERNEL_MEMBLOCK_TYPE_USER_CDRAM_RWDATA) {
		// CDRAM memblocks must be 256KiB aligned
		SCE_DBG_ASSERT(alignment <= 256*1024);
		size = ALIGN(size, 256*1024);
	} else {
		// LPDDR memblocks must be 4KiB aligned
		SCE_DBG_ASSERT(alignment <= 4*1024);
		size = ALIGN(size, 4*1024);
	}
	UNUSED(alignment);

	// allocate some memory
	*uid = sceKernelAllocMemBlock("basic", type, size, NULL);
	SCE_DBG_ASSERT(*uid >= SCE_OK);

	// grab the base address
	void *mem = NULL;
	err = sceKernelGetMemBlockBase(*uid, &mem);
	SCE_DBG_ASSERT(err == SCE_OK);

	// map for the GPU
	err = sceGxmMapMemory(mem, size, attribs);
	SCE_DBG_ASSERT(err == SCE_OK);

	// done
	return mem;
}

void graphicsFree(SceUID uid)
{
	int err = SCE_OK;
	UNUSED(err);

	// grab the base address
	void *mem = NULL;
	err = sceKernelGetMemBlockBase(uid, &mem);
	SCE_DBG_ASSERT(err == SCE_OK);

	// unmap memory
	err = sceGxmUnmapMemory(mem);
	SCE_DBG_ASSERT(err == SCE_OK);

	// free the memory block
	err = sceKernelFreeMemBlock(uid);
	SCE_DBG_ASSERT(err == SCE_OK);
}

void *vertexUsseAlloc(uint32_t size, SceUID *uid, uint32_t *usseOffset)
{
	int err = SCE_OK;
	UNUSED(err);

	// align to memblock alignment for LPDDR
	size = ALIGN(size, 4096);

	// allocate some memory
	*uid = sceKernelAllocMemBlock("basic", SCE_KERNEL_MEMBLOCK_TYPE_USER_RWDATA_UNCACHE, size, NULL);
	SCE_DBG_ASSERT(*uid >= SCE_OK);

	// grab the base address
	void *mem = NULL;
	err = sceKernelGetMemBlockBase(*uid, &mem);
	SCE_DBG_ASSERT(err == SCE_OK);

	// map as vertex USSE code for the GPU
	err = sceGxmMapVertexUsseMemory(mem, size, usseOffset);
	SCE_DBG_ASSERT(err == SCE_OK);

	// done
	return mem;
}

void vertexUsseFree(SceUID uid)
{
	int err = SCE_OK;
	UNUSED(err);

	// grab the base address
	void *mem = NULL;
	err = sceKernelGetMemBlockBase(uid, &mem);
	SCE_DBG_ASSERT(err == SCE_OK);

	// unmap memory
	err = sceGxmUnmapVertexUsseMemory(mem);
	SCE_DBG_ASSERT(err == SCE_OK);

	// free the memory block
	err = sceKernelFreeMemBlock(uid);
	SCE_DBG_ASSERT(err == SCE_OK);
}

void *fragmentUsseAlloc(uint32_t size, SceUID *uid, uint32_t *usseOffset)
{
	int err = SCE_OK;
	UNUSED(err);

	// align to memblock alignment for LPDDR
	size = ALIGN(size, 4096);

	// allocate some memory
	*uid = sceKernelAllocMemBlock("basic", SCE_KERNEL_MEMBLOCK_TYPE_USER_RWDATA_UNCACHE, size, NULL);
	SCE_DBG_ASSERT(*uid >= SCE_OK);

	// grab the base address
	void *mem = NULL;
	err = sceKernelGetMemBlockBase(*uid, &mem);
	SCE_DBG_ASSERT(err == SCE_OK);

	// map as fragment USSE code for the GPU
	err = sceGxmMapFragmentUsseMemory(mem, size, usseOffset);
	SCE_DBG_ASSERT(err == SCE_OK);

	// done
	return mem;
}

void fragmentUsseFree(SceUID uid)
{
	int err = SCE_OK;
	UNUSED(err);

	// grab the base address
	void *mem = NULL;
	err = sceKernelGetMemBlockBase(uid, &mem);
	SCE_DBG_ASSERT(err == SCE_OK);

	// unmap memory
	err = sceGxmUnmapFragmentUsseMemory(mem);
	SCE_DBG_ASSERT(err == SCE_OK);

	// free the memory block
	err = sceKernelFreeMemBlock(uid);
	SCE_DBG_ASSERT(err == SCE_OK);
}