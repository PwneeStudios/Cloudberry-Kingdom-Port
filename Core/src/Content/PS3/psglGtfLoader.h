/* SCE CONFIDENTIAL
 * PlayStation(R)3 Programmer Tool Runtime Library 430.001
 *                Copyright (C) 2010 Sony Computer Entertainment Inc.
 *                                               All Rights Reserved.
 */

#ifndef PSGLGTFLOADER_HEADER
#define PSGLGTFLOADER_HEADER

#include <PSGL/psgl.h>

typedef struct  
{
    GLuint textureID;
    GLuint bufferID;
} psglTextureReference;

int psglCreateTextureReferenceFromFile(const char *filename, psglTextureReference *textureReference, bool bLoadInPlace, bool bForceSwizzling);

int psglCreateTextureReferenceFromGTFFile(const char *filename, psglTextureReference *textureReference, bool bLoadInPlace, bool bForceSwizzling);

/*
int psglCreateTextureReferenceFromDDSFile(const char *filename, psglTextureReference *textureReference, bool bLoadInPlace, bool bForceSwizzling);

int psglCreateTextureReferenceFromGTF(const char *buffer, size_t size, psglTextureReference *textureReference);
int psglCreateTextureReferenceFromDDS(const char *buffer, size_t size, psglTextureReference *textureReference);
*/

int psglDestroyTextureReference(psglTextureReference *textureReference);

#endif
