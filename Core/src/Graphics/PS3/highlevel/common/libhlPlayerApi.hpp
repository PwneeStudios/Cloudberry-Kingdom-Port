/* SCE CONFIDENTIAL
 * PlayStation(R)3 Programmer Tool Runtime Library 430.001
 * Copyright (C) 2010 Sony Computer Entertainment Inc.
 * All Rights Reserved.
 */

#ifndef	__hlPlayerAPICPP_H__
#define	__hlPlayerAPICPP_H__

#ifdef __cplusplus
// C++ Only interface to hlPlayer

#include "SailAdapter.h"
#include "SailSoundAdapter.h"

namespace cell {
namespace Sail {

class hlPlayer
{
public:
	VideoPlayerInit* pinitParams;

	/**E
     * Constructor that sets up the video player
     * 
     * @param [I/-] VideoPlayerInit structure contains spurs instance, and
     *              required output format
     * @param [I/-] CustomAllocators structure contains replacement memory
     *              and file IO calls 
     *              If not in use pass NULL 
     */
    hlPlayer(VideoPlayerInit*,CustomAllocators*);

	/**E
     * Destructor that finalizes the video player. 
     */
	~hlPlayer(void);

	/**E
     * Starts Playback
     * 
     * @return true if succeeded.
     * @param [I/-] Filename including path
     * @param [I/-] Specify if the video is to loop or not
     */
	bool Play(char* videouri, bool looping=false); 

	/**E
     * Stop Playback
     * 
     * @return true if succeeded.
     */
	bool Stop(void); 

	/**E
     * Pause Playback
     * 
     * @return true if succeeded.
     */
	bool Pause(void); 

	/**E
     * Resume Playback
     * 
     * @return true if succeeded.
     */
	bool Resume(void);

	/**E
     * Adjust the volume of stream
     * 
     * @return true if succeeded.
     * @param [I/-] valid from 0.0f to 16.0f, the default value is 1.0f
     */
	bool Volume(float);

	/**E
     * check if player is playing
     *
     * @return true if currently playing.
     */
	bool isPlaying(void);

	/**E
     * Retrieve pointer a valid video frame
     * 
     * @return true if succeeded.
     * @param [I/-] structure contains a pointer to the frame texture as
     *              well as information about the texture
     */
	bool vsyncGetFrame(VideoFrameInfo*); // Called every flip

	/**E
     * Retrieve the current playback time. 
     * Useful for jumping to a fixed offset from the current point & progress
     * bars
     * 
     * @return Current time value in Msecs
     */
	uint64_t CurrentTime(void); 

	/**E
     * Retrieve the video start time. Useful for progress bars
     * 
     * @return Start time value in Msecs
     */
	uint64_t StartTime(void);
	
	/**E
     * Retrieve the video end time. Useful for progress bars
     * 
     * @return End time value in Msecs
     */
	uint64_t EndTime(void);

	/**E
     * Jump to a Msec offset between the start and end time
     * 
     * @return true if succeeded.
     * @param [I/-] jump point from the beginning of the movie in Msec
     */
    bool JumpTimeOffset(uint64_t offsetMsec);

	/**E
     * Enable Fast Playback
     * 
     * @return true if succeeded.
     * @param [I/-] values of 2,3,4x are supported with this mode
     */
	bool TrickFastPlay(int playspeed);

	/**E
     * Enable Fast Forward
     * 
     * @return true if succeeded.
     * @param [I/-] values of 1 to 5 are supported (1=10x,2=20x,3=30x...)
     */
	bool TrickFastForward(int trickspeed);

	/**E
     * Enable Fast Rewind
     * 
     * @return true if succeeded.
     * @param [I/-] values of 1 to 5 are supported (1=10x,2=20x,3=30x...)
     */
	bool TrickFastRewind(int trickspeed);

	/**E
     * Disable any outstanding trick calls
     * 
     * @return true if succeeded.
     */
	bool TrickResumePlay(void);

	/**E
     * Retrieve memory usage stats
     * 
     * @return true if succeeded.
     * @param [-/O] decoder memory
     * @param [-/O] output texture memory
     */
	bool Memstats(int*, int*);

public:
	cell::Sail::sailAdapter* pPlayerCore;
	cell::Sail::soundAdapter* AudioOut;

	bool mPlayerReady;
	uint64_t mCurrentPlaybackTime;
	bool current_looping;
    volatile uint32_t mAccess;
    volatile int      mEnabled;
    void *mpUserdata;

};
#endif
} // namespace Sail
} // namespace cell

#endif
