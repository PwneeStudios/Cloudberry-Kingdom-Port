/*---------------------------------------------------------------------------*
  Project:  CAFE AX Streaming Server
  File:     AXStream.h

  Copyright (C)1998-2011 Nintendo  All Rights Reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

 *---------------------------------------------------------------------------*/
#ifndef __AXSTREAM_H_
#define __AXSTREAM_H_

/*---------------------------------------------------------------------------*
    return value from AXStreamProcess
 *---------------------------------------------------------------------------*/
typedef enum _AXS_STATE {
    AXS_STATE_ERROR = -1,
    AXS_STATE_STOPPED,      // thaaats all fffolks!
                            // you might have a *buffer to reclaim
                            // afterwards call AXStreamRelease()
    AXS_STATE_BUF_REQ,      // I need more data - voice will stop if I don't get any in time
                            // call AXStreamAddBuffer when you have it ready
                            // you might have a *buffer to reclaim
                            // but I only tell you once!
    AXS_STATE_RUNNING       // I'm OK, all chugging along nicely
} AXS_STATE;

/*---------------------------------------------------------------------------*
    return value from all other APIs
 *---------------------------------------------------------------------------*/
typedef enum _AXS_ERR {
    AXS_ERR_OK,
    AXS_ERROR,
} AXS_ERR;

/*---------------------------------------------------------------------------*
    Buffer Descriptor for AXStreamAddBuffer
 *---------------------------------------------------------------------------*/
typedef enum _AXS_BUFFER_MODE { 
    AXS_NORMAL,             // to be followed by another buffer
                            // transition will be from this endOffset
                            // to next buffer's currentOffset
    AXS_LAST,               // set if voice stops at endOffset
    AXS_SAMPLE_LOOPED,      // set if sample has a loop point at loopOffset
                            // if loopOffset == endOffset, loop resumes in next buffer
                            // if not, loopOffset should mark the last sample
                            // of the voice, and the following samples
                            // should be continuing from the voice's actual
                            // loop sample relative to its file information.
                            // For an ADPCM voice note that both the ending
                            // and the restart of the samples need to be aligned
                            // to the ADPCM 8 byte (16 nibbles) block structure.
                            // indicate the restart sample in the restart block header
    AXS_SAMPLE_LOOPS        // set if sample has a loop point at loopOffset
                            // and buffer contains entire loop.
} AXS_BUFFER_MODE;

/*---------------------------------------------------------------------------*
 *---------------------------------------------------------------------------*/
#ifdef __cplusplus
extern "C" {
#endif

/*---------------------------------------------------------------------------*
    AXStreamInit
    
    Initialize the Streamer Library
    
    Arguments:      none
    
    Returns:        none
 *---------------------------------------------------------------------------*/
void AXStreamInit(void);

/*---------------------------------------------------------------------------*
    AXStreamVoiceInit
    
    Initialize a Voice for streaming
     
    Arguments:
    
        p           Voice ready to be streamed
    
    Returns:        AXS_ERR code
    
    Description:
        p must be configured and ready to play,
        but not yet started
        
        call from Thread only
*---------------------------------------------------------------------------*/
AXS_ERR AXStreamVoiceInit(AXVPB *p);

/*---------------------------------------------------------------------------*
    AXStreamSetAdpcmLoop
    
    Set inital ADPCM predictors+histories from ADPCM header
    
    Arguments:
    
        p    Voice prepared for streaming
        
        adpcmloop   ptr to source sound's loop control
                    from DSPADPCM header, or Sound Pipe table info
    
    Returns:        AXS_ERR code
    
    Description:
    
        p must be configured and ready to play,
        but not yet started
        
        Use the same initialization struct as originally
        passed to AXSetVoiceAdpcmLoop(p, &adpcmloop)
        after AXStreamInit() but before starting the voice playing.
        This is required only if the sample is ADPCM format and is looped.
        
        call from Thread only
 *---------------------------------------------------------------------------*/
AXS_ERR AXStreamSetAdpcmLoop(AXVPB *p, const AXPBADPCMLOOP *adpcmloop);

/*---------------------------------------------------------------------------*
    AXStreamAddBuffer
    
    Give Streamer the next buffer
    
    Arguments:
    
        p           Voice prepared for streaming
        
        offsets     an AXPBOFFSETS struct describing the
                    layout of the new buffer
                    
        mode        controls the loop management of the new buffer
        
    Returns:        AXS_ERR code
    
        offsets should be initialized with the samples buffer information
        call with first buffer before starting voice
        Call only from Frame callback
        
        offsets setup:
        format:         ignored
        samples:        base address of the buffer to which the other offsets apply
        currentOffset:  samples offset from samples to the first sample to be played
        loopOffset:     samples offset from samples to the last sample of a loop
                        ignored for buffers not containing a loop (AXS_NORMAL and AXS_LAST)
        endOffset:      samples offset from samples to the last sample to be played from this buffer
        
        call from Thread for the first buffer
        thereafter call only from Frame Callback
    
 *---------------------------------------------------------------------------*/
AXS_ERR AXStreamAddBuffer(AXVPB *p, const AXPBOFFSET *offsets, AXS_BUFFER_MODE mode);

/*---------------------------------------------------------------------------*
    AXStreamProcess
    
    Call in every User Fame Callback for every voice that is streaming.
    
    Arguments:
    
        p           Voice prepared for streaming

        *buffer:    to be filled with a consumed buffer or NULL.
        
    Returns
    
        state:      normally AXS_STATE_STOPPED, AXS_STATE_BUF_REQ, or AXS_STATE_RUNNING
        *buffer:    is filled with a consumed buffer or NULL.
        
    Description:
    
        The buffer is returned to you for you to dispose
        and will only be passed back to you once.
        This should be taken care of before inspecting the returned state.
    
        call from frame Callback only
 *---------------------------------------------------------------------------*/
AXS_STATE AXStreamProcess(AXVPB *p, void **buffer);

/*---------------------------------------------------------------------------*
    AXStreamRelease
    
    Call when done with the streaming. May have zero, one or two
    buffers in hand that need your attention
    
    Arguments:
    
        p           Voice prepared for streaming

        *buffer_0:  to be filled with a consumed buffer or NULL.
        
        *buffer_1:  to be filled with a consumed buffer or NULL.

    Returns
        AXS_ERROR or AXS_ERR_OK
        
    Description:
    
        if AXS_OK, check the two buffer pointers and free the non-NULL ones
    
        OK to call from Thread or frame callback
 *---------------------------------------------------------------------------*/
AXS_ERR AXStreamRelease(AXVPB *p, void **buffer_0, void **buffer_1);


AXS_ERR AXStreamStopVoice(AXVPB *voice);
AXS_ERR AXStreamStartVoice(AXVPB *voice);
/*---------------------------------------------------------------------------*
To use:

1: AXStreamInit(); to prepare the service for use

2: when acquiring a voice to be streamed:

    a: configure it for the streaming sample format
    b: AXStreamVoiceInit(p);
    c: AXStreamSetVoiceAdpcmLoop(p, &adpcmloop);
    d: AXStreamAddBuffer(p, &offsets, mode);
    e: AXSetVoiceState(p, AX_PB_STATE_RUN);
    
3: thereafter, in every User Frame Callback, for every streaming voice:

    void *buffer;
    void *buffer_1;
    AXS_STATE state;
    
    state = AXStreamProcess(p, &buffer);
    if (buffer) my_free(buffer);
    switch (state)
    {
    case AXS_STATE_ERROR:
        // oops - cancel voice and recover
        if (AXS_ERR_OK == AXStreamRelease(p, &buffer, &buffer_1)
        {
            if (buffer)   my_free(buffer);
            if (buffer_1) my_free(buffer_1);
        }
        AXFreeVoice(p);
        break;
        
    case AXS_STATE_STOPPED:
        // voice completed, free it
        if (AXS_ERR_OK == AXStreamRelease(p, &buffer, &buffer_1)
        {
            if (buffer)   my_free(buffer);
            if (buffer_1) my_free(buffer_1);
        }
        AXFreeVoice(p);
        break;
        
    case AXS_STATE_BUF_REQ:
        // need another buffer to stream when the current one finishes
        // when you have it available, call:
        
        AXStreamAddBuffer(p, buffer, mode);
        
        // this state will persist until either you provide a new buffer
        // or time runs out and you get AXS_STATE_ERROR instead
        
        // the trickiest part for you is determining the value for mode.
        // Main constraints here are that the minimum length for a buffer
        // (as set by endOffset - loopOffset) is 3 frames, except where
        // AXS_SAMPLE_LOOPED is appropriate and the restart of the sample
        // is appended into the same buffer, when an additional 3 frames minimum
        // must follow the splice point. Or if it is the last buffer.
        break;
        
    case AXS_STATE_RUNNING:
        // all is good, no action required
        break;
        
    default:
        // bad state, something got corrupted, PANIC!!!
    }
    
 *---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*
 *---------------------------------------------------------------------------*/
#ifdef __cplusplus
}
#endif

#endif // __AXSTREAM_H_
