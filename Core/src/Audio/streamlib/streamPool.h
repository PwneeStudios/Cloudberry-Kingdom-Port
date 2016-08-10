/*---------------------------------------------------------------------------*
  Project:  CAFE AX stream demo 3
  File:     streamPool.h

  Copyright (C)1998-2012 Nintendo  All Rights Reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

 *---------------------------------------------------------------------------*/
#ifndef STREAMPOOL_H_
#define STREAMPOOL_H_

#define POOL_ERR_OK 0
#define POOL_ERR_NORAM -1
#define POOL_ERR_EMPTY -2
#define POOL_ERR_FULL -3
#define POOL_ERR_BAD_PARAM -4

/*---------------------------------------------------------------------------*
 *---------------------------------------------------------------------------*/
#ifdef __cplusplus
extern "C" {
#endif

typedef void * h_stream_pool;
typedef void * h_stream_fifo;

// buffer management
typedef struct _stream_buffer_ctl {
    u8 *buffer; // points to data array
    u32 mode;   // mode is of type AXS_BUFFER_MODE (AXStream.h)
    u32 size;
    AXPBOFFSET offsets;
} stream_buffer_ctl;


#define RoundedUp64(x) ((((u32)(x))+63)&0xffffffc0)

#define buffer2buffer_ctl(buffer) (stream_buffer_ctl*)(((u32)buffer) - RoundedUp64(sizeof(stream_buffer_ctl)))

void*  PrivateAlloc          (u32 size);
void   PrivateFree           (void* addr);

/*---------------------------------------------------------------------------*
 *---------------------------------------------------------------------------*/
s32 streamPoolCreate(u32 buffer_size, u32 buffer_count, h_stream_pool *pool);
/*---------------------------------------------------------------------------*
 *---------------------------------------------------------------------------*/
s32 streamPoolRelease(h_stream_pool pool);
/*---------------------------------------------------------------------------*
 *---------------------------------------------------------------------------*/
s32 streamPoolAlloc(h_stream_pool pool, stream_buffer_ctl **buffer);
/*---------------------------------------------------------------------------*
 *---------------------------------------------------------------------------*/
s32 streamPoolFree(h_stream_pool pool, stream_buffer_ctl *buffer);
/*---------------------------------------------------------------------------*
 *---------------------------------------------------------------------------*/
s32 streamPoolDequeue(h_stream_pool pool, stream_buffer_ctl **buffer);
/*---------------------------------------------------------------------------*
 *---------------------------------------------------------------------------*/
s32 streamPoolEnqueue(h_stream_pool pool, stream_buffer_ctl *buffer);
/*---------------------------------------------------------------------------*
 *---------------------------------------------------------------------------*/
s32 streamPoolSize(h_stream_pool pool);

/*---------------------------------------------------------------------------*
 *---------------------------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
#endif /*STREAMPOOL_H_*/
