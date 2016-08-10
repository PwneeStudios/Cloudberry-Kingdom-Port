/*---------------------------------------------------------------------------*
  Project:  CAFE AX stream demo 3
  File:     streamPool.c

  Copyright (C)1998-2012 Nintendo  All Rights Reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

 *---------------------------------------------------------------------------*/
#include <cafe/os.h>
#include <cafe/fs.h>
#include <cafe/demo.h>
#include <cafe/ax.h>
#include <cafe/mix.h>
#include "streamPool.h"
#include "AXStream.h"


void* PrivateAlloc(u32 size)
{
    return MEMAllocFromDefaultHeap(size);
}

/*---------------------------------------------------------------------------*
 *---------------------------------------------------------------------------*/
void PrivateFree(void* addr)
{
    MEMFreeToDefaultHeap(addr);
}

/*---------------------------------------------------------------------------*
 *---------------------------------------------------------------------------*/
typedef struct _stream_fifo_t {
	OSMessageQueue msgQ;
	OSMessage *msgs;
} stream_fifo_t;

typedef struct _stream_pool_t {
	u8 *base;
	u8 *pool;
	u32 buffer_size;
	u32 buffer_size_rounded;
	u32 buffer_count;
	u32 fifo_count;
	stream_fifo_t available_buffers_queue;
	stream_fifo_t inuse_buffers_queue;
} stream_pool_t;
/*---------------------------------------------------------------------------*
 *---------------------------------------------------------------------------*/
static s32 streamFifoInit(h_stream_pool pool, h_stream_fifo fifo)
{
	s32 err = POOL_ERR_BAD_PARAM;
	stream_pool_t *s_pool = (stream_pool_t *)pool;
	stream_fifo_t *s_fifo = (stream_fifo_t *)fifo;
	s32 fifo_size_bytes;

	if (NULL != pool && NULL != fifo)
	{
	    fifo_size_bytes = s_pool->buffer_count*sizeof(OSMessage);
		s_fifo->msgs = (OSMessage *)PrivateAlloc(fifo_size_bytes);
		if (NULL == s_fifo->msgs)
		{
			err = POOL_ERR_NORAM;
		}
		else
		{
			OSInitMessageQueue(&s_fifo->msgQ, s_fifo->msgs, s_pool->buffer_count);
            err = POOL_ERR_OK;
		}
	}
	return err;
}
/*---------------------------------------------------------------------------*
 * Function:    streamPoolCreate
 * Arguments:   buffer_size: size of the buffer to be allocated in bytes
 *              buffer_count: number of buffers to be allocated
 *              pool:        pointer to the stream pool structure
 * Description: 
 *      Allocates a buffer or size buffer_size*buffer_count with proper alignment
 *      and with a buffer control structure 
 *
 *      Internally each buffer is structured as below:
 *          BUFFER_CTL                  |   |<-- these two put togetheris buf_offset
 *          Padding for alignment       |   |
 *          BUFFER_SIZE                 |<- these put together is buffer_size_rounded
 *          padding for alignment       |
 *      
 *      Apart from allocating buffers, this function creates message queues for buffer
 *      and fifo; and sends messages on the queue to start fetching the data
 *---------------------------------------------------------------------------*/
s32 streamPoolCreate(u32 buffer_size, u32 buffer_count, h_stream_pool *pool)
{
	stream_pool_t *s_pool;
	s32 err = POOL_ERR_BAD_PARAM;
	u32 count;
	u32 buf_offset;
	
	if (NULL != pool)
	{
        // allocate a stream pool structure and initialize it to zero
		s_pool = PrivateAlloc(sizeof(stream_pool_t));
		if (NULL == s_pool)
		{
			return POOL_ERR_NORAM;
		}
		memset(s_pool, 0, sizeof(stream_pool_t));

        // the next three lines are just to allocate buffers such that they are aligned 
        // with cache lines
		
		buf_offset                  = RoundedUp64(sizeof(stream_buffer_ctl));
		s_pool->buffer_size_rounded = RoundedUp64(buffer_size+buf_offset);
		s_pool->base                = PrivateAlloc(s_pool->buffer_size_rounded * (buffer_count+1));
		if (NULL == s_pool->base)
		{
			PrivateFree(s_pool);
			return POOL_ERR_NORAM;
		}
		
		// align the base properly
		s_pool->pool         = (u8*)RoundedUp64(s_pool->base);

		s_pool->buffer_size  = buffer_size;
		s_pool->buffer_count = buffer_count;
		
        // rename the queues to make it more meaningful
		if (POOL_ERR_OK != (err = streamFifoInit((h_stream_pool)s_pool, &s_pool->available_buffers_queue)))
		{
			streamPoolRelease(s_pool);
			return err;
		}
		if (POOL_ERR_OK != (err = streamFifoInit((h_stream_pool)s_pool, &s_pool->inuse_buffers_queue)))
		{
			streamPoolRelease(s_pool);
			return err;
		}

		// load up the free pool
		for (count = 0; count < buffer_count; count++)
		{
			stream_buffer_ctl *buf_ctl;

			buf_ctl            = (stream_buffer_ctl*)&s_pool->pool[count*s_pool->buffer_size_rounded];
			buf_ctl->mode      = 0;
			buf_ctl->size      = 0;
			buf_ctl->buffer    = &((u8*)buf_ctl)[buf_offset];
			buf_ctl->offsets.samples = buf_ctl->buffer;

			if (POOL_ERR_OK != (err = streamPoolFree( (h_stream_pool)s_pool, buf_ctl)))
			{
				streamPoolRelease(s_pool);
				return err;
			}
		}
		*pool = (h_stream_pool)s_pool;
	}
    else
    {
        OSReport("problem with POOL input\n");
    }
	return err;
}
/*---------------------------------------------------------------------------*
 *---------------------------------------------------------------------------*/
s32 streamPoolRelease(h_stream_pool pool)
{
	if (NULL != pool)
	{
		stream_pool_t *s_pool = (stream_pool_t *)pool;

		if (s_pool->available_buffers_queue.msgs)
		{
			PrivateFree(s_pool->available_buffers_queue.msgs);
			s_pool->available_buffers_queue.msgs = NULL;
		}
		if (s_pool->inuse_buffers_queue.msgs)
		{
			PrivateFree(s_pool->inuse_buffers_queue.msgs);
			s_pool->inuse_buffers_queue.msgs = NULL;
		}
		if (s_pool->base) 
		{
			PrivateFree(s_pool->base);
			s_pool->base = NULL;
		}
		s_pool->pool = NULL;
		
		PrivateFree(s_pool);
	}

	return POOL_ERR_OK;
}
/*---------------------------------------------------------------------------*
 *---------------------------------------------------------------------------*/
s32 streamPoolAlloc(h_stream_pool pool, stream_buffer_ctl **buffer)
{
	s32 err = POOL_ERR_BAD_PARAM;
	stream_pool_t *s_pool = (stream_pool_t *)pool;
	BOOL qret = FALSE;
	OSMessage msg;

	if (NULL != pool && NULL != buffer)
	{
		qret = OSReceiveMessage(&s_pool->available_buffers_queue.msgQ, &msg, OS_MESSAGE_NOBLOCK);
		err = qret ? POOL_ERR_OK : POOL_ERR_EMPTY;
		if (POOL_ERR_OK == err)
		{
			*buffer = (stream_buffer_ctl *)msg.message;
		}
	}
	return err;
}
/*---------------------------------------------------------------------------*
 *---------------------------------------------------------------------------*/
s32 streamPoolFree(h_stream_pool pool, stream_buffer_ctl *buffer)
{
	s32 err = POOL_ERR_BAD_PARAM;
	BOOL qret = FALSE;
    OSMessage msg;
	stream_pool_t *s_pool = (stream_pool_t *)pool;
	
	if (NULL != pool && NULL != buffer)
	{
        msg.message = (void*)buffer;
		qret = OSSendMessage(&s_pool->available_buffers_queue.msgQ, &msg, OS_MESSAGE_NOBLOCK);
		err = qret ? POOL_ERR_OK : POOL_ERR_FULL;
	}
	return err;
}
/*---------------------------------------------------------------------------*
 *---------------------------------------------------------------------------*/
s32 streamPoolEnqueue(h_stream_pool pool, stream_buffer_ctl *buffer)
{
	s32 err = POOL_ERR_BAD_PARAM;
	BOOL qret = FALSE;
    OSMessage msg;
	stream_pool_t *s_pool = (stream_pool_t *)pool;
	
	if (NULL != pool && NULL != buffer)
	{
	    msg.message = (void*)buffer;
		qret = OSSendMessage(&s_pool->inuse_buffers_queue.msgQ, &msg, OS_MESSAGE_NOBLOCK);
		err = qret ? POOL_ERR_OK : POOL_ERR_FULL;
	}
	return err;
}
/*---------------------------------------------------------------------------*
 *---------------------------------------------------------------------------*/
s32 streamPoolDequeue(h_stream_pool pool, stream_buffer_ctl **buffer)
{
	s32 err = POOL_ERR_BAD_PARAM;
	stream_pool_t *s_pool = (stream_pool_t *)pool;
	BOOL qret = FALSE;
	OSMessage msg;
	
	if (NULL != pool && NULL != buffer)
	{
		qret = OSReceiveMessage(&s_pool->inuse_buffers_queue.msgQ, &msg, OS_MESSAGE_NOBLOCK);
		err = qret ? POOL_ERR_OK : POOL_ERR_EMPTY;
		if (POOL_ERR_OK == err)
		{
			*buffer = (stream_buffer_ctl *)msg.message;
		}
	}
	return err;
}
/*---------------------------------------------------------------------------*
 *---------------------------------------------------------------------------*/
s32 streamPoolSize(h_stream_pool pool)
{
	s32 size = POOL_ERR_BAD_PARAM;
	stream_pool_t *s_pool = (stream_pool_t *)pool;
	
	if (NULL != pool)
	{
		size = s_pool->inuse_buffers_queue.msgQ.usedCount;
	}
	return size;
}
