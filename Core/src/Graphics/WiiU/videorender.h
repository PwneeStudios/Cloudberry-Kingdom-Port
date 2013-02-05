/*---------------------------------------------------------------------------*

  Copyright 2011 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

 *---------------------------------------------------------------------------*/

#ifndef _RENDER_H_
#define _RENDER_H_

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

extern  GX2Texture      g_LTexture[2];
extern  GX2Texture      g_UVTexture[2];

void InitShader(void);
void FreeShader(void);

void InitVideoBuffer(s32 dest, u16 width, u16 height);

void InitAttribData(void);
void FreeAttribData(void);

void drawTVFrame(void);
void drawDRCFrame(void);

#ifdef __cplusplus
}
#endif

#endif

