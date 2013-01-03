/*---------------------------------------------------------------------------*
  Project:  CAFE AX Streaming Server
  File:     AXStreamServer.c

  Copyright (C)1998-2011 Nintendo  All Rights Reserved.

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
#include "AXStream.h"



/*---------------------------------------------------------------------------*
    Local Types
 *---------------------------------------------------------------------------*/
typedef enum _AXS_SVR_STATE { 
    AXS_UNCONFIGURED,
    AXS_BUFFER_WAITING,     // rest of AXSTREAM is invalid, AXProcessVoiceStream will ignore it
    AXS_BUFFER_READY,       // App has set up a new buffer
                            // AXStream will see this and change state to AXS_BUFFER_ACTIVE
    AXS_BUFFER_ACTIVE,      // AXStream has the new buffer, but Renderer has not yet caught up to it.
    AXS_BUFFER_LOOPING,     // sample loop is mid buffer - waiting for currentOffset to pass it
    AXS_STOPPING,           // In a AXS_LAST buffer but not yet reached its end
    AXS_STOPPED             // Voice has stopped at end of stream. last buffer can be released now.
} AXS_SVR_STATE;

typedef enum {
	AXS_VOICE_STOPPED=0,
    AXS_VOICE_STOP_REQD,
	AXS_VOICE_STARTED,
	AXS_VOICE_RUNNING
}AXS_VOICE_STATE;
typedef struct _AXSTREAM {
    AXVPB          *p;
    AXS_SVR_STATE   state;
    AXS_BUFFER_MODE mode;
    u32             loopCount;
    const void     *old_buffer;
    AXPBOFFSET      offsets;
    AXPBADPCMLOOP   loop;
    AXS_VOICE_STATE voiceState;

} AXSTREAM;

/*---------------------------------------------------------------------------*
    Local Data
 *---------------------------------------------------------------------------*/
static AXSTREAM __axs_streams[AX_MAX_VOICES] = { 0 };

#define REPORTING_STATE_CHANGES 0x00000001
#define REPORTING_STATE         0x00000002
#define REPORTING_STATE_READY   0x00000004
#define REPORTING_STATE_LOOPED  0x00000008
#define REPORTING_OFFSETS       0x00000010
#define REPORTING_ADDBUFFER     0x00000020

#define reporting_state_changes (reporting&REPORTING_STATE_CHANGES)
#define reporting_state         (reporting&REPORTING_STATE)
#define reporting_state_ready   (reporting&(REPORTING_STATE_READY|REPORTING_STATE))
#define reporting_state_looped  (reporting&(REPORTING_STATE_LOOPED|REPORTING_STATE))
#define reporting_offsets       (reporting&REPORTING_OFFSETS)
#define reporting_addbuffer     (reporting&REPORTING_ADDBUFFER)

static char * state_names[] = {
        "AXS_UNCONFIGURED",
        "AXS_BUFFER_WAITING",     // rest of AXSTREAM is invalid, AXProcessVoiceStream will ignore it
        "AXS_BUFFER_READY",       // App has set up a new buffer
                                  // AXStream will see this and change state to AXS_BUFFER_ACTIVE
        "AXS_BUFFER_ACTIVE",      // AXStream has the new buffer, but Renderer has not yet caught up to it.
        "AXS_BUFFER_LOOPING",     // sample loop is mid buffer - waiting for currentOffset to pass it
        "AXS_STOPPING",           // In a AXS_LAST buffer but not yet reached its end
        "AXS_STOPPED"             // Voice has stopped at end of stream. last buffer can be released now.
};

static char * state_abbrevs[] = {
        "u",
        "w",
        "r",
        "a",
        "l",
        "g",
        "d"
};

static char * mode_names[] = {
        "AXS_NORMAL",           // to be followed by another buffer
                                // transition will be from this endOffset
                                // to next buffer's currentOffset
        "AXS_LAST",             // set if voice stops at endOffset
        "AXS_SAMPLE_LOOPED",    // set if sample has a loop point at loopOffset
                                // if loopOffset == endOffset, loop resumes in next buffer
                                // if not, loopOffset should mark the last sample
                                // of the voice, and the following samples
                                // should be continuing from the voice's actual
                                // loop sample relative to its file information.
                                // For an ADPCM voice note that both the ending
                                // and the restart of the samples need to be aligned
                                // to the ADPCM 8 byte (16 nibbles) block structure.
                                // indicate the restart sample in the restart block header
        "AXS_SAMPLE_LOOPS"      // set if sample has a loop point at loopOffset
                                // and buffer contains entire loop.
};

static int reporting = 0;
//static int reporting = REPORTING_ADDBUFFER|REPORTING_STATE_CHANGES;
//static int reporting = REPORTING_OFFSETS|REPORTING_STATE_READY|REPORTING_STATE_LOOPED;
/*---------------------------------------------------------------------------*
    AXStreamInit
    
    Initialize the Streamer Library
 *---------------------------------------------------------------------------*/
void AXStreamInit(void)
{
    memset(__axs_streams, 0, sizeof(__axs_streams));
}

/*---------------------------------------------------------------------------*
    AXStreamVoiceInit
    
    Initialize a Voice for streaming
    p must be configured and ready to play,
    but not yet started
    call from Thread only
 *---------------------------------------------------------------------------*/
AXS_ERR AXStreamVoiceInit(AXVPB *p)
{
    AXS_ERR err = AXS_ERROR;
    AXSTREAM *stream;
    AXS_SVR_STATE entry_state;
    
    if (p && p->index < AX_MAX_VOICES)
    {
        stream = &__axs_streams[p->index];
        entry_state = stream->state;
        if (AXS_UNCONFIGURED == stream->state && NULL == stream->p)
        {
            memset(stream, 0, sizeof(AXSTREAM));
            
            stream->p     = p;
            stream->mode  = AXS_NORMAL;
            stream->state = AXS_BUFFER_WAITING;
        
            err = AXS_ERR_OK;
        }
    }
    
    if(reporting_state_changes)
        OSReport(   "[%d:%s->%s]\n",
                      p->index,
                      state_abbrevs[entry_state],
                      state_abbrevs[stream->state]);

    return err;
}

/*---------------------------------------------------------------------------*
    AXStreamSetAdpcmLoop
    
    Set inital ADPCM predictors+histories from ADPCM header
    Use the same initialization struct as originally
    passed to AXSetVoiceAdpcmLoop(p, &adpcmloop)
    after AXStreamInit() but before starting the voice playing.
    This is required only if the sample is ADPCM format and is looped.
 *---------------------------------------------------------------------------*/
AXS_ERR AXStreamSetAdpcmLoop(AXVPB *p, const AXPBADPCMLOOP *adpcmloop)
{
    AXS_ERR err = AXS_ERROR;
    AXSTREAM *stream;
    
    if (p && p->index < AX_MAX_VOICES)
    {
        stream = &__axs_streams[p->index];
        if (AXS_UNCONFIGURED != stream->state && p == stream->p)
        {
            stream->loop.loop_pred_scale = adpcmloop->loop_pred_scale;
            stream->loop.loop_yn1        = adpcmloop->loop_yn1;
            stream->loop.loop_yn2        = adpcmloop->loop_yn2;

            err = AXS_ERR_OK;
        }
    }
    return err;
}

/*---------------------------------------------------------------------------*
    AXStreamAddBuffer
    
    Give Streamer the next buffer
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
    
 *---------------------------------------------------------------------------*/
AXS_ERR AXStreamAddBuffer(AXVPB *p, const AXPBOFFSET *offsets, AXS_BUFFER_MODE mode)
{
    AXS_ERR err = AXS_ERROR;
    AXSTREAM *stream;
    
    if (offsets && p && p->index < AX_MAX_VOICES && __axs_streams[p->index].p == p)
    {
        stream = &__axs_streams[p->index];
        if (stream->state == AXS_BUFFER_WAITING)
        {
            stream->offsets = *offsets;
            stream->mode    = mode;
            stream->state   = AXS_BUFFER_READY;
    
            err = AXS_ERR_OK;
        }
        if (stream->state == AXS_BUFFER_LOOPING)
        {
            stream->offsets = *offsets;
            stream->mode    = mode;

            stream->old_buffer = p->offsets.samples;
            err = AXS_ERR_OK;
        }
    }
    if (reporting_addbuffer)
    {
        OSReport("%s %s: state = %s, buffer = %8.8x, mode = %s\n", __FILE__, __FUNCTION__,
                    state_names[stream->state], offsets->samples, mode_names[mode]);
    }
    
    return err;
}
/*---------------------------------------------------------------------------*
    AXStreamProcess
    
    Call in every User Fame Callback for every voice that is streaming.
    
    Returns 
        state:      normally AXS_STATE_STOPPED, AXS_STATE_BUF_REQ, or AXS_STATE_RUNNING
        *buffer:    is filled with a consumed buffer or NULL.
                    The buffer is returned to you for you to dispose
                    and will only be passed back to you once.
                    This should be taken care of before inspecting the returned state.
    
    call from frame Callback only
 *---------------------------------------------------------------------------*/
static void report_offsets(AXVPB *p)
{
    AXPBOFFSET offsets;
	AXGetVoiceOffsets(p, &offsets);
	OSReport("S-%8.8x C-%8.8x E-%8.8x L-%8.8x\n", offsets.samples, offsets.currentOffset, offsets.endOffset, offsets.loopOffset);
}

AXS_STATE AXStreamProcess(AXVPB *p, void **buffer)
{
    AXS_STATE     client_state      = AXS_STATE_ERROR;
    AXS_SVR_STATE entry_state;
    AXSTREAM     *stream;
    AXPBADPCMLOOP loop;
    u32           loopCount;
    
    if (buffer && p && p->index < AX_MAX_VOICES && __axs_streams[p->index].p == p)
    {
        *buffer = NULL;
        stream = &__axs_streams[p->index];
        
        if (reporting_state)         OSReport("(%d@%s)", p->index, state_abbrevs[stream->state]);
        if (reporting_state_changes) entry_state = stream->state;

        if (reporting_offsets) report_offsets(p);

        // not much to do if the voice is already stopped
        // note the user already gave us a buffer and started the stream
        // before calling this function the first time
        if (AXS_VOICE_STOP_REQD == stream->voiceState)
        {
            stream->voiceState = AXS_VOICE_STOPPED; 
            // Just in case the Client force-stopped us ...
            // figure out how many buffers we have in hand
            if (stream->old_buffer)
            {
                // definitely one old one,
                *buffer                 = (void *)stream->old_buffer;
                // may still have an active one
                stream->old_buffer      = p->offsets.samples;
            }
            else
            if (p->offsets.samples == stream->offsets.samples)
            {
                // only have one or none in hand
                *buffer                 = (void *)stream->offsets.samples;
                stream->old_buffer      = NULL;
                p->offsets.samples      = NULL;
            }
            else
            {
                // again, one active, old already returned,
                // or one active, next one pending
                *buffer                 = (void *)p->offsets.samples;
                stream->old_buffer      = stream->offsets.samples;
            }
            stream->offsets.samples = NULL;
            client_state            = AXS_STATE_STOPPED;
            stream->state           = AXS_STOPPED;
        }
    
        switch (stream->state)
        {
        case AXS_UNCONFIGURED:
            // what it says - not readied yet
            client_state   = AXS_STATE_ERROR;
            break;
            
        case AXS_BUFFER_WAITING:
            // don't have a follow-on buffer ready yet
            // return state to ask for one
            // also the case between init and getting the first one
            client_state   = AXS_STATE_BUF_REQ;
            break;
            
        case AXS_BUFFER_READY:
            // OK, the CLient gave us a buffer
            // decide what to do with it

            if(stream->voiceState == AXS_VOICE_STARTED)
            {
                AXSetVoiceState(p, AX_PB_STATE_RUN);
                stream->voiceState = AXS_VOICE_RUNNING;
                
            }

			stream->state = AXS_BUFFER_ACTIVE;
			client_state  = AXS_STATE_RUNNING;

            if (stream->offsets.samples == p->offsets.samples)
            {
                // user is either setting up first buffer
                // or the entire loop is in the one buffer
                // so set the endOffset here
                AXSetVoiceEndOffset(p, stream->offsets.endOffset);
                
                // mode will tell us if this endOffset is a sample loop or not
                switch (stream->mode)
                {
                case AXS_NORMAL:            // to be followed by another buffer
                                            // transition will be from this endOffset
                                            // to next buffer's startOffset
                                            // this case here would be a first of multiple buffer scenario
                                            // AXPBADPCMLOOP will have been already set up from samples file
                    AXSetVoiceType(p, AX_PB_TYPE_STREAM);
                    AXSetVoiceLoop(p, TRUE);
    				stream->state = AXS_BUFFER_WAITING;
    				client_state  = AXS_STATE_BUF_REQ;
                    break;
                    
                case AXS_LAST:              // set if voice stops at endOffset
                    AXSetVoiceType(p, AX_PB_TYPE_NORMAL);
                    AXSetVoiceLoop(p, FALSE);
                    break;
                    
                case AXS_SAMPLE_LOOPED:     // set if sample has a loop point at loopOffset
                                            // if loopOffset == endOffset, loop resumes in next buffer
                                            // else resumes at next sample until endOffset (at least 2 frames)
                                            // either case the renderer needs to use the loop_yn1/2 histories
                                            // assumes there will be a next buffer
                                            // therefore this must be the first buffer
    				stream->state = AXS_BUFFER_WAITING;
    				client_state  = AXS_STATE_BUF_REQ;
                    AXSetVoiceType(p, AX_PB_TYPE_NORMAL);
                    AXSetVoiceLoop(p, TRUE);
                    //AXSetVoiceAdpcmLoop(p, &stream->loop);
                    if (stream->offsets.loopOffset != stream->offsets.endOffset)
                    {
                        AXSetVoiceEndOffset(p, stream->offsets.loopOffset+1);
                    }
                    break;
                    
                case AXS_SAMPLE_LOOPS:      // set if sample has a loop point at loopOffset
                                            // and buffer contains entire loop.
                
                    AXSetVoiceType(p, AX_PB_TYPE_NORMAL);
                    AXSetVoiceLoop(p, TRUE);
                    AXSetVoiceLoopOffset(p, stream->offsets.loopOffset);
                    AXSetVoiceAdpcmLoop(p, &stream->loop);

                    break;
                    
                default:
                    break;
                }

                break;
            }
            else
            {
                // Not the first buffer
                // the Renderer is still walking up the previous buffer
                // need to tell it where to go to when it gets to the endOffset
                // At this time the mode is not significant
                
                // stash the previous buffer ptr in prep for releasing it later
                stream->old_buffer   = p->offsets.samples;
                // now we can switch the voice info to the new buffer
                AXSetVoiceSamplesAddr(p, stream->offsets.samples);
                
                // Now we know there's another buffer, set up the rest of the voice
                // so the renderer will skip here instead of just stopping
                AXSetVoiceType(p, AX_PB_TYPE_STREAM);
                AXSetVoiceLoopOffset(p, stream->offsets.currentOffset);
                
                // get the ADPCM looping info from the new buffer ready for the skip
                loop.loop_pred_scale = (u16)(*(u8*)stream->offsets.samples);
                AXSetVoiceAdpcmLoop(p, &loop);
                AXSetVoiceLoop(p, TRUE);
            }
            if (reporting_offsets) report_offsets(p);

            // intentional fall through to BUF_ACTIVE stage
            //break;
            
        case AXS_BUFFER_ACTIVE:
            // we have the next one ready in hand
            // and the renderer is configured to skip to this one
            // when it finishes ther previous one
            
           
            // has the renderer skipped yet?
            loopCount = AXGetVoiceLoopCount(p);
            if (loopCount != stream->loopCount)
            {
            	if(reporting&REPORTING_STATE_LOOPED) OSReport(">");
                if (reporting&REPORTING_OFFSETS) report_offsets(p);
                stream->loopCount  = loopCount;
                *buffer            = (void*)stream->old_buffer;   // done with this one
                stream->old_buffer = NULL;
                client_state       = AXS_STATE_BUF_REQ;
                stream->state      = AXS_BUFFER_WAITING;
                AXSetVoiceEndOffset(p, stream->offsets.endOffset);
                switch (stream->mode)
                {
                    case AXS_NORMAL:            // to be followed by another buffer
                        // transition will be from this endOffset
                        // to next buffer's startOffset
                        // but just inb case the client is late giving us that
                        // set the voice to end on this biffer
                        // until we have the next in hand
                        AXSetVoiceType(p, AX_PB_TYPE_NORMAL);
                        AXSetVoiceLoop(p, FALSE);
                        break;

                    case AXS_LAST:              // set if voice stops at this endOffset
                        AXSetVoiceType(p, AX_PB_TYPE_NORMAL);
                        AXSetVoiceLoop(p, FALSE);
                        stream->state      = AXS_STOPPING;
                        break;

                    case AXS_SAMPLE_LOOPED:     // set if sample has a loop point at loopOffset
                        // the renderer needs to use the loop_yn1/2 histories
                        AXSetVoiceType(p, AX_PB_TYPE_NORMAL);
                        AXSetVoiceLoop(p, TRUE);
                        if (stream->offsets.loopOffset != stream->offsets.endOffset)
                        {
                            // loop resumes at loopOffset+n
                            // until endOffset (at least 2 frames)
                            // resume point is +1 for PCM
                            // but is next 16 nibble adjusted for ADPCM
                            // we have been keeping the real loop data for this occasion
                            if (p->offsets.format == AX_PB_FORMAT_ADPCM)
                            {

                                AXSetVoiceAdpcmLoop(p, &stream->loop);
                                AXSetVoiceLoopOffset(p, stream->offsets.loopOffset);
                            }
                            else
                            {
                                AXSetVoiceLoopOffset(p, stream->offsets.loopOffset+1);
                            }
                            AXSetVoiceEndOffset(p, stream->offsets.endOffset);
                            stream->state           = AXS_BUFFER_LOOPING;
                            stream->offsets.samples = NULL;
                        }
                        break;

                    case AXS_SAMPLE_LOOPS:      // set if sample has a loop point at loopOffset
                        // and buffer contains entire loop.
                        // set normal since we are no longer streaming
                        AXSetVoiceType(p, AX_PB_TYPE_NORMAL);
                        AXSetVoiceLoop(p, TRUE);
                        AXSetVoiceLoopOffset(p, stream->offsets.loopOffset);
                        AXSetVoiceAdpcmLoop(p, &stream->loop);
                        client_state = AXS_STATE_RUNNING;
                        stream->state      = AXS_BUFFER_ACTIVE;
                        break;

                    default:
                        // oops, out of state values.
                        break;
                }
            }
            else
            {
                client_state = AXS_STATE_RUNNING;
            }
            break;
            
        case AXS_BUFFER_LOOPING:

            // check if we got a new buffer when we are in this mode..
            if(stream->offsets.samples != NULL && stream->offsets.samples != p->offsets.samples)
            {
                // set the new address
                AXSetVoiceSamplesAddr(p, stream->offsets.samples);
                switch(stream->mode)
                {
                    case AXS_NORMAL:
                        AXSetVoiceLoop(p, TRUE);
                        AXSetVoiceType(p, AX_PB_TYPE_NORMAL);
                        AXSetVoiceLoopOffset(p, stream->offsets.loopOffset);

                        break;
                    case AXS_SAMPLE_LOOPED:
                        ASSERT(FALSE);
                        break;
                    case AXS_SAMPLE_LOOPS:
                        AXSetVoiceLoop(p, TRUE);
                        AXSetVoiceType(p, AX_PB_TYPE_NORMAL);
                        AXSetVoiceLoopOffset(p, stream->offsets.loopOffset);
                        break;
                } // end of switch
            } // end of new buffer arrival
            // has the renderer skipped yet?
            loopCount = AXGetVoiceLoopCount(p);
            if (loopCount != stream->loopCount)
            {
                stream->loopCount  = loopCount;
                *buffer            = (void*)stream->old_buffer;   // done with this one
                stream->old_buffer = p->offsets.samples;
                client_state       = AXS_STATE_BUF_REQ;
                stream->state      = AXS_BUFFER_WAITING;

                // OK, passed the mid-buffer stream loop point
                // reset endOffset to the real endOffset
                AXSetVoiceEndOffset(p, stream->offsets.endOffset);
                AXSetVoiceLoop(p, FALSE);

            }
            else
            {
                client_state = AXS_STATE_RUNNING;
            }
            break;
            
        case AXS_STOPPING:
        	if (AX_PB_STATE_STOP == p->state)
        	{
        		stream->state = AXS_STOPPED;
        		client_state  = AXS_STATE_STOPPED;
        	}
        	else
        	{
        	    client_state  = AXS_STATE_RUNNING;
        	}
            break;
            
        case AXS_STOPPED:
            client_state  = AXS_STATE_STOPPED;
            break;
        
        default:
            client_state = AXS_STATE_ERROR;
            break;
        }
    }
    
    if (client_state == AXS_STATE_ERROR)
    {
        stream->state = AXS_UNCONFIGURED;
    }
    if(reporting_state_changes && entry_state != stream->state)
        OSReport(   "[%d:%s->%s]\n",
                      p->index,
                      state_abbrevs[entry_state],
                      state_abbrevs[stream->state]);
    return client_state;
}
/*---------------------------------------------------------------------------*
    AXStreamRelease
    
    Call when done with the streaming. May have zero, one or two
    buffers in hand that need your attention
    
    Returns
        AXS_ERROR or AXS_ERR_OK
        if AXS_OK, check the two buffer pointers and free the non-NULL ones
    
    OK to call from Thread or frame callback
 *---------------------------------------------------------------------------*/
AXS_ERR AXStreamRelease(AXVPB *p, void **buffer_0, void **buffer_1)
{
    AXSTREAM *stream;
    AXS_SVR_STATE entry_state;
    
    if (NULL == p || NULL == buffer_0 || NULL == buffer_1)
    {
        return AXS_ERROR;
    }
    if (p->index >= AX_MAX_VOICES)
    {
        *buffer_0 = NULL;
        *buffer_1 = NULL;
        return AXS_ERROR;
    }
    
    stream = &__axs_streams[p->index];
    if (stream->p != p)
    {
        *buffer_0 = NULL;
        *buffer_1 = NULL;
        return AXS_ERROR;
    }

    entry_state = stream->state;
    if (AXS_UNCONFIGURED == stream->state)
    {
        *buffer_0 = NULL;
        *buffer_1 = NULL;
        return AXS_ERROR;
    }
    
    // figure out how many buffers we have in hand
    if (NULL != stream->old_buffer)
    {
        // definitely one old one,
        *buffer_0      = (void*)stream->old_buffer;
        // may still have an active one
        *buffer_1      = (void*)p->offsets.samples;
    }
    else
    if (p->offsets.samples == stream->offsets.samples)
    {
        // only have one or none in hand
        *buffer_0     = (void*)stream->offsets.samples;
        *buffer_1      = NULL;
    }
    else
    {
        // again, one active, old already returned,
        // or one active, next one pending
        *buffer_0      = (void*)p->offsets.samples;
        *buffer_1      = (void*)stream->offsets.samples;
    }
    
    stream->state = AXS_UNCONFIGURED;

    if(reporting_state_changes)
        OSReport(   "[%d:%s->%s]\n",
                      p->index,
                      state_abbrevs[entry_state],
                      state_abbrevs[stream->state]);

    stream->p = NULL;

    return AXS_ERR_OK;
}
/*--- set the local state of the voice to be on ----------- */
AXS_ERR AXStreamStartVoice(AXVPB *voice)
{
	AXSTREAM *stream;
	if(voice == NULL)
	{
		return AXS_ERROR;
	}

	stream = &__axs_streams[voice->index];
    ASSERT(stream->state == AXS_BUFFER_READY);


    stream->voiceState = AXS_VOICE_STARTED;

    return AXS_ERR_OK;
}

/*--- set the local state of the voice to be on ----------- */
AXS_ERR AXStreamStopVoice(AXVPB *voice)
{
	AXSTREAM *stream;
	if(voice == NULL)
	{
		return AXS_ERROR;
	}

	stream = &__axs_streams[voice->index];

    stream->voiceState = AXS_VOICE_STOP_REQD;

    return AXS_ERR_OK;
}
