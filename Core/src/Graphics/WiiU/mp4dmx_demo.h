/***********************************************************
 *
 *  Copyright (C) 2012  PUX Corporation
 *  All Rights Reserved.
 *
 ***********************************************************/
 
#ifndef __MP4DEMUX_DEMO_H__
#define __MP4DEMUX_DEMO_H__

#include <cafe.h>

#define MEDIA_HEADER        (0)
#define MEDIA_CHUNK         (1)
#define MEDIA_SAMPLE        (2)

#define TRACK_TYPE_ANY      (0)
#define TRACK_TYPE_VIDEO    (1)
#define TRACK_TYPE_AUDIO    (2)

#define MP4DMXFW_RET_SUCCESS                    (0)
#define MP4DMXFW_RET_ERROR_NOT_ENOUGH_MEMORY    (1)
#define MP4DMXFW_RET_ERROR_BADPARAM             (2)
#define MP4DMXFW_RET_ERROR_INVALID_POINTER      (3)
#define MP4DMXFW_RET_ERROR_FATAL                (4)
#define MP4DMXFW_RET_ERROR_BAD_TIMESTAMP        (5)
#define MP4DMXFW_RET_ERROR_BAD_STREAM           (6)
#define MP4DMXFW_RET_WARNING_NOP                (7)
#define MP4DMXFW_RET_ERROR_SAMPLE_STOP          (8)
#define MP4DMXFW_RET_ERROR_SAMPLE_ABORT         (9)
#define MP4DMXFW_RET_ERROR                      (10)


/* MP4DMXFW_SAMPLE Structure */
typedef struct __MP4DMXFW_SAMPLE__ {
    void    *data_ptr;
    s32     size;
    s32     pts;
    s32     video_width;
    s32     video_height;
    s32     video_framerate;
    s32     video_maxbitrate;
    s32     video_profile;
    s32     video_level;
    s32     audio_channel;
    s32     audio_subsample;
    s32     audio_maxbitrate;
} MP4DMXFW_SAMPLE;


/* MP4DMXFW_UNIT Structure */
typedef struct __MP4DMXFW_UNIT__ {
    s32     type;
    s32     track_type;
    s32     status;
    s64     offset;
    s32     bufsize;
    s32     chunk_offset;
    s32     chunk_size;
    s32     num_of_sample;
    MP4DMXFW_SAMPLE *sample;
    s32     threadnum;
} MP4DMXFW_UNIT;


/* Memory Allocation Structure */
typedef struct __MP4DMXFW_CtrlParam__ {
    void *MP4DMXFW_CallbackSetData;     // 
    void *MP4DMXFW_CallbackGetData;     // 
} MP4DMXFW_CtrlParam;


#ifdef __cplusplus
extern "C" {
#endif

/*=================================================
  MP4Demux Framework API Functions
-------------------------------------------------*/
s32 MP4DMXFW_Open(MEMHeapHandle ExpHeap, void **handle, s32 *UseWorkMemSize, s32 threadnum);
s32 MP4DMXFW_Begin(void *pMlibHandle, MP4DMXFW_CtrlParam *ctrl_param, s32 threadnum);
s32 MP4DMXFW_Execute(void *pMlibHandle, MP4DMXFW_CtrlParam *ctrl_param, s32 control_flag, u64 start_time_stamp, u64 end_time_stamp, s32 threadnum);
s32 MP4DMXFW_End(void *handle, s32 threadnum);
s32 MP4DMXFW_Close(MEMHeapHandle ExpHeap, void *handle, s32 threadnum);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif // __MP4DEMUX_DEMO_H__
