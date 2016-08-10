#ifndef _GFX_COMMON_H_
#define _GFX_COMMON_H_


// These parameters describe the different video modes.
typedef struct VideoParameters {
	int iWidth;
	int iHeight;
	GLenum TVStandard;
} VideoParameters;

// Supported video modes by this sample
enum gfxVideoMode
{
	GFX_DISPLAY_MODE_VGA=0,
	GFX_DISPLAY_MODE_480i,
	GFX_DISPLAY_MODE_480p,
	GFX_DISPLAY_MODE_576i,
	GFX_DISPLAY_MODE_576p,
	GFX_DISPLAY_MODE_720p,
	GFX_DISPLAY_MODE_1080i,
	GFX_DISPLAY_MODE_1080p,
};

void 		gfxInitGraphics();
void		gfxExitGraphics();

void		gfxRegisterSysutilCallback();
void		gfxCheckSysutilCallback();

CGprogram 	gfxLoadProgramFromFile(CGprofile target, const char* filename);
CGprogram 	gfxLoadProgramFromSource(CGprofile target, const char* filename);

void 		gfxCheckCgError(int line);
GLuint 		gfxCreateCheckerTexture (
				unsigned int resolution,	//wSidth and height of texture to make
				unsigned int col1,			//check color 1
				unsigned int col2 );		//check color 2


void 		gfxSwapEnds(void *val);
		

void		dbgFontInit(void);
void		dbgFontExit(void);
void		dbgFontPut(void);
void		dbgFontDraw(void);
void 		dbgFontPrintf(float x,float y, float scale,char* fmt,...);


extern GLuint 	gfxWidth;
extern GLuint 	gfxHeight;
extern GLfloat	gfxAspectRatio;

inline 	GLuint	gfxGetWidth(){ return gfxWidth; };
inline 	GLuint 	gfxGetHeight(){ return gfxHeight; } ;
inline  GLfloat	gfxGetAspectRatio(){ return gfxAspectRatio; } ;

void		gfxCaptureScreen(const char *pFilename);

#endif
