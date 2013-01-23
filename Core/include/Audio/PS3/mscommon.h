/* SCE CONFIDENTIAL
PlayStation(R)3 Programmer Tool Runtime Library 430.001
* Copyright (C) 2008 Sony Computer Entertainment Inc.
* All Rights Reserved.
*/

/*
    mscommon.h

    A common set of function calls required by most samples

    Written by: A. Bowler
*/

#ifndef MS_COMMON_H
#define MS_COMMON_H

#include <sysutil/sysutil_sysparam.h>

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>							
#include <sys/ppu_thread.h>
#include <sys/sys_time.h>
#include <sys/timer.h>
#include <sys/process.h>
#include <sys/spu_initialize.h>


#include <fcntl.h>
#include <cell/fs/cell_fs_errno.h>
#include <cell/fs/cell_fs_file_api.h>

#include <cell/mstream.h>

#include <assert.h>

#include <sys/paths.h>
#include <cell/audio.h>
#include <cell/gcm.h>

#include <sys/system_types.h>

#include <cell/spurs/control.h>
#include <cell/spurs/task.h>
#include <cell/spurs/event_flag.h>
#include <cell/sysmodule.h>



#ifndef MS_THREADED_SAMPLE
void InitSPURS(void);
#endif

long InitialiseAudio( const long nStreams, const long nmaxSubs, int &_nPortNumber, CellAudioPortParam &_audioParam, CellAudioPortConfig &_portConfig, const int _nFlags = CELL_MS_NOFLAGS, bool _bSkipGraphicsInit = false);

void LoadATRAC(const char *_filename, long &_sampleData, long &_sampleDataSize, int &_nSampleFormat, int &_nSampleChannels);
int InitFile(const char *filename,long *addr, long *size);

//long LoadFile( const int fd, long ppData, long nReadSize );
long LoadFile( const int fd, long ppData, long nReadSize = 256*1024, int nStartOffset = 0, int nEndOffset = 0);
int OpenFile( const char* pszFilename, long* pnSize, int nStartOffset = 0 );

long StartMultiStreamUpdateThread( void _thread (uint64_t param));
void ShutdownMultiStream();

bool LoadModules();
bool UnloadModules();

#define SUPPRESS_COMPILER_WARNING(x) (void)x

#endif
