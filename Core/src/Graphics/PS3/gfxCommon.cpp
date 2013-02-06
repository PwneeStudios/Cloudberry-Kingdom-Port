/* SCE CONFIDENTIAL
 * PlayStation(R)3 Programmer Tool Runtime Library 430.001
 *                Copyright (C) 2010 Sony Computer Entertainment Inc.
 *                                               All Rights Reserved.
 */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include <sys/process.h>
#include <sys/spu_initialize.h>
#include <sys/paths.h>
#include <sysutil/sysutil_sysparam.h>

#include <PSGL/psgl.h>
#include <PSGL/psglu.h>

#include <cell/dbgfont.h>

#include <stdarg.h>
#include <cell/dbgfont.h>
#include <cell/sysmodule.h>

#include "gfxCommon.h"


GLuint 		gfxWidth = 1280;
GLuint 		gfxHeight = 720;
GLfloat     gfxAspectRatio = 16.0f/9.0f;

// Prototypes
void gfxExitCallback(uint64_t status, uint64_t param, void* userdata);

//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
void gfxInitGraphics() 
{
	// Load required prx modules.
	int ret = cellSysmoduleLoadModule(CELL_SYSMODULE_GCM_SYS);
	switch( ret )
	{
	    case CELL_OK:
	      // The module is successfully loaded,
		break;

	    case CELL_SYSMODULE_ERROR_DUPLICATED:
	      // The module was already loaded,
		break;

	    case CELL_SYSMODULE_ERROR_UNKNOWN:
	    case CELL_SYSMODULE_ERROR_FATAL:
		printf("!! Failed to load CELL_SYSMODULE_GCM_SYS\n" ); 
		printf("!! Exiting Program \n" ); 
		exit(1);
	}

	
	ret = cellSysmoduleLoadModule(CELL_SYSMODULE_FS);
	switch( ret )
	{
	    case CELL_OK:
	      // The module is successfully loaded,
		break;

	    case CELL_SYSMODULE_ERROR_DUPLICATED:
	      // The module was already loaded,
		break;

	    case CELL_SYSMODULE_ERROR_UNKNOWN:
	    case CELL_SYSMODULE_ERROR_FATAL:
		printf("!! Failed to load CELL_SYSMODULE_FS\n" ); 
		printf("!! Exiting Program \n" ); 
		exit(1);
	}

	ret = cellSysmoduleLoadModule(CELL_SYSMODULE_USBD);
	switch( ret )
	{
	    case CELL_OK:
	      // The module is successfully loaded,
		break;

	    case CELL_SYSMODULE_ERROR_DUPLICATED:
	      // The module was already loaded,
		break;

	    case CELL_SYSMODULE_ERROR_UNKNOWN:
	    case CELL_SYSMODULE_ERROR_FATAL:
		printf("!! Failed to load CELL_SYSMODULE_USBD\n" ); 
		printf("!! Exiting Program \n" ); 
		exit(1);
	}

	ret = cellSysmoduleLoadModule(CELL_SYSMODULE_IO);
	switch( ret )
	{
	    case CELL_OK:
	      // The module is successfully loaded,
		break;

	    case CELL_SYSMODULE_ERROR_DUPLICATED:
	      // The module was already loaded,
		break;

	    case CELL_SYSMODULE_ERROR_UNKNOWN:
	    case CELL_SYSMODULE_ERROR_FATAL:
		printf("!! Failed to load CELL_SYSMODULE_IO\n" ); 
		printf("!! Exiting Program \n" ); 
		exit(1);
	}

	gfxRegisterSysutilCallback();
	
	// First, initialize PSGL
	// Note that since we initialized the SPUs ourselves earlier we should
	// make sure that PSGL doesn't try to do so as well.
	PSGLinitOptions initOpts={
        enable: PSGL_INIT_MAX_SPUS | PSGL_INIT_INITIALIZE_SPUS | PSGL_INIT_HOST_MEMORY_SIZE,
		maxSPUs: 1,
		initializeSPUs: false,
		// We're not specifying values for these options, the code is only here
		// to alleviate compiler warnings.
		persistentMemorySize: 0,
		transientMemorySize: 0,
		errorConsole: 0,
		fifoSize: 0,	
		hostMemorySize: 128* 1024*1024,  // 128 mbs for host memory 
	};

	psglInit(&initOpts);

	static PSGLdevice* device=NULL;
	//device=psglCreateDeviceAuto(GL_ARGB_SCE,GL_DEPTH_COMPONENT24,GL_MULTISAMPLING_NONE_SCE);
	//device=psglCreateDeviceAuto(GL_ARGB_SCE,GL_DEPTH_COMPONENT24,GL_MULTISAMPLING_2X_DIAGONAL_CENTERED_SCE);
	device=psglCreateDeviceAuto(GL_ARGB_SCE,GL_DEPTH_COMPONENT24,GL_MULTISAMPLING_4X_SQUARE_ROTATED_SCE);
	
	if ( !device )
	{
		printf("!! Failed to init the device \n" ); 
		printf("!! Exiting Program \n" ); 
		exit(1); 
	}
	psglGetDeviceDimensions(device,&gfxWidth,&gfxHeight);

	printf("gfxInitGraphics::PSGL Device Initialized Width %d Height %d \n",gfxWidth, gfxHeight ); 	

    gfxAspectRatio = psglGetDeviceAspectRatio(device);

	// Now create a PSGL context
	PSGLcontext *pContext=psglCreateContext();

	if (pContext==NULL) {
		fprintf(stderr, "Error creating PSGL context\n");
		exit(-1);
	}

	// Make this context current for the device we initialized
	psglMakeCurrent(pContext, device);

	// Since we're using fixed function stuff (i.e. not using our own shader
	// yet), we need to load shaders.bin that contains the fixed function 
	// shaders.
	psglLoadShaderLibrary( REMOTE_PATH"/shaders.bin");

	// Reset the context
	psglResetCurrentContext();
  
	glViewport(0, 0, gfxWidth, gfxHeight);
	glScissor(0, 0, gfxWidth, gfxHeight);
	glClearColor(0.f, 0.f, 0.f, 1.f);
	glEnable(GL_DEPTH_TEST);

	// PSGL doesn't clear the screen on startup, so let's do that here.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	psglSwap();
}
//----------------------------------------------------------------------------------------------------


//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
void gfxExitGraphics()
{
	glFinish();
	exit(0);
}
//----------------------------------------------------------------------------------------------------



//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
static void gfxSysutilCallback(uint64_t status, uint64_t param, void* userdata)
{
	(void) param;
	(void) userdata;

	switch(status) {
	case CELL_SYSUTIL_REQUEST_EXITGAME:
		gfxExitGraphics();
		break;
	case CELL_SYSUTIL_DRAWING_BEGIN:
	case CELL_SYSUTIL_DRAWING_END:
		break;
	default:
		printf( "Graphics common: Unknown status received: 0x%llx\n", status );
	}
}
//----------------------------------------------------------------------------------------------------


//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
void gfxRegisterSysutilCallback()
{
	// Register sysutil exit callback
	int ret = cellSysutilRegisterCallback(0, gfxSysutilCallback, NULL);
	if( ret != CELL_OK ) {
		printf( "Registering sysutil callback failed...: error=0x%x\n", ret );
		exit(1);
	}
}
//----------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
void gfxCheckSysutilCallback()
{
	// check system event
	int ret = cellSysutilCheckCallback();
	if( ret != CELL_OK ) {
		printf( "cellSysutilCheckCallback() failed...: error=0x%x\n", ret );
	}
}
//----------------------------------------------------------------------------------------------------



//-----------------------------------------------------------------------------
// Description: Swap the bytes in a 32 bit value
// Parameters:	
// Returns:
// Notes:
// PCs, PS2 and PSP are little endian.  PS3 is big endian so need to swap 
// endian for some of the data
//-----------------------------------------------------------------------------
void gfxSwapEnds(void *val)
{
	unsigned int *ival = (unsigned int *)val;
    *ival = ((*ival >> 24) & 0x000000ff) |
            ((*ival >>  8) & 0x0000ff00) |
            ((*ival <<  8) & 0x00ff0000) |
            ((*ival << 24) & 0xff000000);
}
//-----------------------------------------------------------------------------

CellDbgFontConsoleId DbgFontID;

//-----------------------------------------------------------------------------
// Description: Debug font initialization function
//-----------------------------------------------------------------------------
void dbgFontInit(void)
{
	// initialize debug font library, then open 2 consoles
	CellDbgFontConfig cfg;
	cfg.bufSize      = 512;
	cfg.screenWidth  = gfxGetWidth();
	cfg.screenHeight = gfxGetHeight();
	cellDbgFontInit(&cfg);

	CellDbgFontConsoleConfig ccfg0;
	ccfg0.posLeft     = 0.1f;
	ccfg0.posTop      = 0.8f;
	ccfg0.cnsWidth    = 16;
	ccfg0.cnsHeight   = 4;
	ccfg0.scale       = 0.25f;
	ccfg0.color       = 0xff0080ff;  // ABGR -> orange
	DbgFontID = cellDbgFontConsoleOpen(&ccfg0);


}

char buffer[2048];

//-----------------------------------------------------------------------------
// Description: Debug font put function
//-----------------------------------------------------------------------------
void dbgFontPut(void)
{
static int bollox=0;
bollox++;

	sprintf(buffer,"its bollox %d",bollox);
	cellDbgFontPuts(0.1f, 0.7f, 6.0f, 0xffffffff, "Now printing out to left console..");
	cellDbgFontPuts(0.1f, 0.7f, 1.0f, 0xffffffff, buffer);

}


char tempstr[512];
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void dbgFontPrintf(float x,float y, float scale,char* fmt,...)
{

	//build the output string
	char tempstr[512];

	va_list arglist;
	va_start(arglist, fmt);
	vsprintf(tempstr, fmt, arglist);
	va_end(arglist);

	cellDbgFontPuts((x/gfxGetWidth()),(y/gfxGetHeight()),scale, 0xffffffff, tempstr);



}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Description: Debug font draw function
//-----------------------------------------------------------------------------
void dbgFontDraw(void)
{
	cellDbgFontDraw();
}

//-----------------------------------------------------------------------------
// Description: Debug font exit function
//-----------------------------------------------------------------------------
void dbgFontExit(void)
{
	cellDbgFontExit();
}

//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// GLuint createCheckerTexture(unsigned int resolution,	unsigned int col1,	unsigned int col2)
// Description: 
// Generates an openGL texture with a check pattern
// Returns: 
// A named texture
// Notes
// GLunint createCheckerTexture(16,0xffffffff,0x00000000);
// would generate a 16 * 16 pixel texture with black and white checks
//-----------------------------------------------------------------------------
GLuint 
gfxCreateCheckerTexture
(
unsigned int resolution,	//wSidth and height of texture to make
unsigned int col1,			//check color 1
unsigned int col2			//check color 2
)
{
	GLuint texture;
	glGenTextures(1, &texture);

	unsigned int *texData = (unsigned int*)malloc(sizeof(unsigned int)*resolution*resolution);
	unsigned int *tP = texData;
	bool flip = true;	//flip is used to generate the checker board pattern

	for (unsigned int i=0; i< resolution; i++)
	{
		for (unsigned int j=0; j< resolution; j++)
		{
			if (flip)
			{
				*tP=col1;
			} else
			{
				*tP=col2;
			}

			//printf("0x%x ",*tP);
			tP++;
			flip = !flip;
		}
		//printf("\n");
		flip = !flip;
	}


// Basic OpenGL texture state setup
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);  
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,resolution,resolution,0,GL_RGBA,GL_UNSIGNED_INT_8_8_8_8,texData);

	free(texData);

	return texture;
}
//----------------------------------------------------------------------------




//-----------------------------------------------------------------------------
// CGprogram gfxLoadProgramFromFile(CGprofile target, const char* filename)
// Description: 
// Loads a shader program
// Returns: NA
// Notes:
// Causes program termination on failure
// Use __LINE__ as a parameter to have the cpp replace with the line number
// in the source
//-----------------------------------------------------------------------------
CGprogram gfxLoadProgramFromFile(CGprofile target, const char* filename)
{
  CGprogram id = cgCreateProgramFromFile(cgCreateContext(), CG_BINARY, filename, target, NULL, NULL);
  if(!id)
	{
	printf("Failed to load shader program >>%s<<\nExiting\n", filename);
	exit(0);
	}
  else
	return id;
}

//-----------------------------------------------------------------------------
// CGprogram gfxLoadProgramFromSource(CGprofile target, const char* filename)
// Description: 
// Loads a shader program
// Returns: NA
// Notes:
// Causes program termination on failure
// Use __LINE__ as a parameter to have the cpp replace with the line number
// in the source
//-----------------------------------------------------------------------------
CGprogram gfxLoadProgramFromSource(CGprofile target, const char* filename)
{
  CGprogram id = cgCreateProgramFromFile(cgCreateContext(), CG_SOURCE, filename, target, NULL, NULL);
  if(!id)
	{
	printf("Failed to load shader program >>%s<< \nExiting\n", filename);
	exit(0);
	}
  else
	return id;
}


//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// void CheckCgError(int line)
// Description: If there is a CG error reported this function will print it to
// the console and then cause the program to exit
// Returns: NA
// Notes:
// Causes program to exit
// Use __LINE__ as a parameter to have the cpp replace with the line number
// in the source
//-----------------------------------------------------------------------------
void gfxCheckCgError(int line)
{
	CGerror err = cgGetError ();

	if (err != CG_NO_ERROR)
	{
		printf ("CG error:%d at line %d %s\n", err, line, cgGetErrorString (err));
		exit (0);
	}
}
//-----------------------------------------------------------------------------




#define LITTLE_SHORT(x) (((x & 0xff) << 8) | ((x & 0xff00) >> 8))
#define LITTLE_INT(x)	(((x & 0xff) << 24) | ((x & 0xff00) << 8) | ((x & 0xff0000) >> 8) | ((x & 0xff000000) >> 24))
#define BIG_SHORT(x)	(x)
#define BIG_INT(x)		(x)

//-----------------------------------------------------------------------------
// Description: Capture the screen
// Parameters:	pFilename - Filename to save capture as (Targa format)
// Returns:
// Notes: Uses a default numbered name if <i><c>pFilename</c></i> is <c>NULL</c>
//-----------------------------------------------------------------------------
void gfxCaptureScreen(const char *pFilename)
{
	unsigned char	header[12] = { 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	unsigned char	bpp = 32;
	unsigned char	id = 8;
	unsigned short	width;
	unsigned short	height;
	unsigned char	*pPixels;
	FILE			*fp = NULL;

	if(pFilename)
	{
		fp = fopen(pFilename, "wb");
		if(!fp)
			return;
	}
	else
	{
		char	filename[256];
		int		i = 0;

		do
		{
			if(fp)
				fclose(fp);

#ifdef __CELLOS_LV2__
			sprintf(filename, SYS_APP_HOME"/screen%04d.tga", i);
#else
			sprintf(filename, "screen%04d.tga", i);
#endif
			fp = fopen(filename, "rb");
			i ++;
		} while(fp);
		
		fp = fopen(filename, "wb");
	}

	pPixels = new unsigned char[gfxWidth * gfxHeight * 4];
	glReadPixels(0, 0, gfxWidth, gfxHeight, GL_BGRA, GL_UNSIGNED_INT_8_8_8_8_REV, pPixels);
	unsigned int	*pIntPix = (unsigned int *)pPixels;
	for(GLuint i = 0; i < gfxWidth * gfxHeight; i ++)
	{
		*pIntPix = LITTLE_INT(*pIntPix);
		pIntPix ++;
	}

	fwrite(header, 1, sizeof(header), fp);

	width = LITTLE_SHORT(gfxWidth);
	height = LITTLE_SHORT(gfxHeight);

	fwrite(&width, 1, sizeof(unsigned short), fp);
	fwrite(&height, 1, sizeof(unsigned short), fp);
	fwrite(&bpp, 1, sizeof(unsigned char), fp);
	fwrite(&id, 1, sizeof(unsigned char), fp);

	fwrite(pPixels, 4, gfxWidth * gfxHeight, fp);
	fclose(fp);

	delete []pPixels;
}
//-----------------------------------------------------------------------------

