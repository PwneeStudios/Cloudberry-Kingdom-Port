/* SCE CONFIDENTIAL
 * PlayStation(R)3 Programmer Tool Runtime Library 430.001
 * Copyright (C) 2010 Sony Computer Entertainment Inc.
 * All Rights Reserved.
 */

#ifndef	__HLPLAYERRAPI_H__
#define	__HLPLAYERRAPI_H__

#ifdef __cplusplus
extern "C" {
#endif
typedef void* hlPlayerHandle_t;

typedef struct hlMemAllocator {
    void* pArg;
	void* (*allocate)(void *pArg, uint32_t size, uint32_t alignment);
	void (*deallocate)(void *pArg, void* pMemory);
	void* (*allocateTexture)(void *pArg, uint32_t size, uint32_t alignment);
	void (*deallocateTexture)(void *pArg, void* pMemory);
} hlMemAllocator;


/**
 * Sets up the video player
 * 
 * @return new player handle
 * @param [I/-] VideoPlayerInit structure contains spurs instance,
 *              and required output format
 * @param [I/-] memory allocator
 *              memalign and free are used if NULL is specified
 */
hlPlayerHandle_t hlPlayerInit(VideoPlayerInit*, hlMemAllocator*);

/**
 * Finalizes the video player. 
 *
 * @return true if succeeded.
 * @param [I/-] player handle
 */
bool hlPlayerClose(hlPlayerHandle_t);

/**
 * Starts Playback
 * 
 * @return true if succeeded.
 * @param [I/-] player handle
 * @param [I/-] Filename including path
 * @param [I/-] Specify if the video is to loop or not
 */
bool hlPlayerPlay(hlPlayerHandle_t, char*, bool); 

/**
 * Stop Playback
 * 
 * @return true if succeeded.
 * @param [I/-] player handle
 */
bool hlPlayerStop(hlPlayerHandle_t); 

/**
 * Pause Playback
 * 
 * @return true if succeeded.
 * @param [I/-] player handle
 */
bool hlPlayerPause(hlPlayerHandle_t); 
	
/**
 * Resume Playback
 * 
 * @return true if succeeded.
 * @param [I/-] player handle
 */	
bool hlPlayerResume(hlPlayerHandle_t);

/**
 * Adjust the volume of stream
 * 
 * @return true if succeeded.
 * @param [I/-] player handle
 * @param [I/-] valid from -16.0f to 16.0f, the default value is 1.0f
 */
bool hlPlayerVolume(hlPlayerHandle_t, float);

/**
 * check if player is playing
 *
 * @return true if currently playing.
 * @param [I/-] player handle
 */
bool hlPlayerisPlaying(hlPlayerHandle_t);

/**
 * Retrieve pointer a valid video frame
 * 
 * @return true if succeeded.
 * @param [I/-] player handle
 * @param [I/-] structure contains a pointer to the frame texture
 *              as well as information about the texture
 */
bool hlPlayerGetFrame(hlPlayerHandle_t, VideoFrameInfo*);

/**
 * Retrieve the current playback time. 
 * Useful for jumping to a fixed offset from the current point & progress bars
 * 
 * @return Current time value in Msecs
 * @param [I/-] player handle
 */	
uint64_t hlPlayerCurrentTime(hlPlayerHandle_t); 

/**
 * Retrieve the video start time. Useful for progress bars
 * 
 * @return Start time value in Msecs
 * @param [I/-] player handle
 */
uint64_t hlPlayerStartTime(hlPlayerHandle_t);

/**
 * Retrieve the video end time. Useful for progress bars
 * 
 * @return End time value in Msecs
 * @param [I/-] player handle
 */
uint64_t hlPlayerEndTime(hlPlayerHandle_t);

/**
 * Jump to a Msec offset between the start and end time
 * 
 * @return true if succeeded.
 * @param [I/-] player handle
 * @param [I/-] jump point from the beginning of the movie in Msec
 */
bool hlPlayerJumpTimeOffset(hlPlayerHandle_t, uint64_t offsetMsec);

/**
 * Enable Fast Playback
 * 
 * @return true if succeeded.
 * @param [I/-] player handle
 * @param [I/-] values of 2,3,4x are supported with this mode
 */
bool hlPlayerTrickFastPlay(hlPlayerHandle_t,int playspeed); 

/**
 * Enable Fast Forward
 * 
 * @return true if succeeded.
 * @param [I/-] player handle
 * @param [I/-] values of 1 to 5 are supported (1=10x,2=20x,3=30x...)
 */
bool hlPlayerTrickFastForward(hlPlayerHandle_t,int trickspeed); 

/**
 * Enable Fast Rewind
 * 
 * @return true if succeeded.
 * @param [I/-] player handle
 * @param [I/-] values of 1 to 5 are supported (1=10x,2=20x,3=30x...)
 */
bool hlPlayerTrickFastRewind(hlPlayerHandle_t,int trickspeed); 

/**
 * Disable any outstanding trick calls
 * 
 * @return true if succeeded.
 * @param [I/-] player handle
 */
bool hlPlayerTrickResumePlay(hlPlayerHandle_t);

/**
 * Retrieve memory usage stats
 * 
 * @return true if succeeded.
 * @param [I/-] player handle
 * @param [-/O] decoder memory
 * @param [-/O] output texture memory
 */
bool hlPlayerMemstats(hlPlayerHandle_t, int*, int*);

#ifdef __cplusplus
}
#endif

#endif
