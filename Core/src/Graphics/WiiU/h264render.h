#ifndef _H264_RENDER_H_
#define _H264_RENDER_H_

#ifdef __cplusplus
extern "C" {
#endif

// Struct for attribute buffers
typedef struct _AttribBuffer
{
    f32 *pVertexBuffer;
    u32 vertexSize;
    u32 vertexStride;
    u32 vertexCount;
} AttribBuffer;

#define SAMPLE_MODE (0)                 //1:TV 2: DRC 0: TV & DRC
#define NUM_DECODE ((SAMPLE_MODE==1)? 1:2) // 1 -> TV, 2-> TV + DRC
#define NUM_H264_BUFFER (2) // 2 -> double buffer

extern  GX2Texture      g_LTexture[NUM_DECODE][NUM_H264_BUFFER];
extern  GX2Texture      g_UVTexture[NUM_DECODE][NUM_H264_BUFFER];

extern  u32             g_H264WriteBufIdx[NUM_DECODE];

void InitShader(void);
void FreeShader(void);

void InitVideoBuffer(u8 decIdx, u8 bufIdx, u16 width, u16 height);

void InitAttribData(void);
void FreeAttribData(void);

void drawTVFrame(void);
void drawDRCFrame(void);

#ifdef __cplusplus
}
#endif

#endif

