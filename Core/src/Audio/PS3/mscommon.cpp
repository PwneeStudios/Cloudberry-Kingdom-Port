/* SCE CONFIDENTIAL
PlayStation(R)3 Programmer Tool Runtime Library 430.001
* Copyright (C) 2008 Sony Computer Entertainment Inc.
* All Rights Reserved.
*/

/*
    mscommon.cpp

    A common set of function calls required by most samples

	If using these common headers in your own projects be sure to specify
	the preprocessor flag "MS_THREADED_SAMPLE" if linking against the 
	MultiStream Threaded library (libmstreamThreadAT3.a or libmstreamThreadMP3.a).

    Written by: A. Bowler
*/


// Commenting this will remove all Sulpha setup/shutdown.
// Leave this uncommented to be able to connect the Sulpha PC tool audio debugger to the application
#define USE_SULPHA

//Amount of memory to supply to Sulpha as a buffer
#define SULPHA_MEMORYBUFFER_SIZE (1024 * 1024)

// Number of items (PCM data, streams, busses and DPS's) to name
#define SULPHA_NUM_NAMED_OBJECTS (70)




#include <Audio/PS3/mscommon.h>

bool InitSulpha(unsigned int _memoryBufferSize, unsigned int _numNames);

static bool graphicsInitCell();
static int audioInitCell(bool _skipGraphicsInit);
static void systemCallback(const uint64_t status, const uint64_t param, void *userdata);

volatile bool s_receivedExitGameRequest;

#ifndef MS_THREADED_SAMPLE
/**********************************************************************************/
// SPURS information
/**********************************************************************************/
#define				SPURS_SPU_NUM	3
#define				SPU_THREAD_GROUP_PRIORITY		100
CellSpurs			spurs __attribute__((aligned (128)));
#endif

sys_ppu_thread_t     s_MultiStreamPuThread   = 0;
void *               s_pMultiStreamMemory    = NULL;

void *               s_pSulphaMemory		 = NULL;


#define   CHANNEL   CELL_AUDIO_PORT_8CH
#define   BLOCK     CELL_AUDIO_BLOCK_8

CellAudioPortParam   audioParam;
CellAudioPortConfig  portConfig;


/**********************************************************************************/
// MultiStream thread defines
/**********************************************************************************/
#define STACK_SIZE              (0x4000) // 16 kb
#define EXIT_CODE               (0xbee)
#define SERVER_PRIO             (0)



/**********************************************************************************

graphicsInitCell
	Initialises graphics
	This is not MultiStream specific.

	Returns: False on failure, true otherwise

**********************************************************************************/
static bool graphicsInitCell(void)
{
	uint32_t color_depth=4; // ARGB8
//	uint32_t z_depth=4;     // COMPONENT24
	int32_t ret;
	CellVideoOutResolution resolution;

	uint32_t display_width;
//	uint32_t display_height; 

//	float    display_aspect_ratio;
	uint32_t color_pitch;
//	uint32_t depth_pitch;

	// read the current video status
	// INITIAL DISPLAY MODE HAS TO BE SET BY RUNNING SETMONITOR.SELF
	CellVideoOutState videoState;
	ret = cellVideoOutGetState(CELL_VIDEO_OUT_PRIMARY, 0, &videoState);
	if (ret != CELL_OK){
		printf("cellVideoOutGetState() failed. (0x%x)\n", ret);
		return false;
	}

	cellVideoOutGetResolution(videoState.displayMode.resolutionId, &resolution);

	display_width = resolution.width;
//	display_height = resolution.height;
	color_pitch = display_width*color_depth;
//	depth_pitch = display_width*z_depth;

//	uint32_t color_size =   color_pitch*display_height;
//	uint32_t depth_size =  depth_pitch*display_height;

	CellVideoOutConfiguration videocfg;
	memset(&videocfg, 0, sizeof(CellVideoOutConfiguration));
	videocfg.resolutionId = videoState.displayMode.resolutionId;
	videocfg.format = CELL_VIDEO_OUT_BUFFER_COLOR_FORMAT_X8R8G8B8;
	videocfg.pitch = color_pitch;

	// set video out configuration with waitForEvent set to 0 (4th parameter)
	ret = cellVideoOutConfigure(CELL_VIDEO_OUT_PRIMARY, &videocfg, NULL, 0);
	if (ret != CELL_OK){
		printf("cellVideoOutConfigure() failed. (0x%x)\n", ret);
		return false;
	}

	ret = cellVideoOutGetState(CELL_VIDEO_OUT_PRIMARY, 0, &videoState);
	if (ret != CELL_OK){
		printf("cellVideoOutGetState() failed. (0x%x)\n", ret);
		return false;
	}

/*
	switch (videoState.displayMode.aspect){
	  case CELL_VIDEO_OUT_ASPECT_4_3:
		  display_aspect_ratio=4.0f/3.0f;
		  break;
	  case CELL_VIDEO_OUT_ASPECT_16_9:
		  display_aspect_ratio=16.0f/9.0f;
		  break;
	  default:
		  printf("unknown aspect ratio %x\n", videoState.displayMode.aspect);
		  display_aspect_ratio=16.0f/9.0f;
	}
*/

	return true;
}


/**********************************************************************************

audioInitCell
	Initialises low level video and audio.
	This is not MultiStream specific.

	Returns: audio port number returned from cellAudioPortOpen(..)

**********************************************************************************/
static int audioInitCell(bool _skipGraphicsInit)
{
	s_receivedExitGameRequest = false;
	int ret = cellSysutilRegisterCallback(0, systemCallback, NULL);
	if (ret != CELL_OK) {
		printf( "error: cellSysutilRegisterCallback() = 0x%x\n", ret);
		exit(1);
	}

	unsigned int returnPortNum = 0;


	if(!_skipGraphicsInit)
	{
		if(!graphicsInitCell())
			return -1;
	}


	//	cellMSSystemConfigureSysUtilEx returns the following data:
	//	Bits 0-3:	Number of available output channels
	//	Bit    4:	Dolby On status
	//	Bit    5:	DTS On status
	int retSysUtil = cellMSSystemConfigureSysUtilEx(CELL_MS_AUDIOMODESELECT_SUPPORTSLPCM | CELL_MS_AUDIOMODESELECT_SUPPORTSDOLBY | CELL_MS_AUDIOMODESELECT_SUPPORTSDTS | CELL_MS_AUDIOMODESELECT_PREFERDOLBY);
	if( retSysUtil < 0 )
	{
		printf("error cellMSSystemConfigureSysUtilEx\n");
		return -1;
	}
	unsigned int numChans = (retSysUtil & 0x0000000F);
	unsigned int dolbyOn = (retSysUtil & 0x00000010) >> 4;
	unsigned int dtsOn = (retSysUtil & 0x00000020) >> 5;
	printf("Number Of Channels: %u\n", numChans);
	printf("Dolby enabled: %u\n", dolbyOn);
	printf("DTS enabled: %u\n", dtsOn);

	ret = cellAudioInit();
	if (ret !=CELL_OK)
	{
		printf("error cellAudioInit\n");
		return -1;
	}

	// audio port open.
	memset(&audioParam, 0, sizeof(CellAudioPortParam));
	audioParam.nChannel = CHANNEL;
	audioParam.nBlock   = BLOCK;

	ret = cellAudioPortOpen(&audioParam, &returnPortNum);
	printf("cellAudioPortOpen() : %d  port %d\n", ret, returnPortNum);
	if (ret != CELL_OK)
	{
		cellAudioQuit();
		printf("Error cellAudioPortOpen()\n");
		return -1;
	}
	 
	// get port config.
	ret = cellAudioGetPortConfig(returnPortNum, &portConfig);
	printf("cellAudioGetPortConfig() : %d\n", ret);
	if (ret != CELL_OK)
	{
		cellAudioQuit();
		printf("Error cellAudioGetPortConfig\n");
		return -1;
	}

	cellMSSystemConfigureLibAudio(&audioParam, &portConfig);


	return returnPortNum;


}



/**********************************************************************************

LoadATRAC
	Load ATRAC file into RAM and check header
	
	Requires:
	_filename			Filename to load
	_sampleData			Reference to long - Returns sample data buffer created in memory
	_sampleDataSize		Reference to long - Returns size of _sampleData in bytes
	_nSampleFormat		Reference to int  - Returns sample format of ATRAC file
	_nSampleChannels	Reference to int  - Returns sample channels in ATRAC file

	Returns: Nothing

**********************************************************************************/
void LoadATRAC(const char *_filename, long &_sampleData, long &_sampleDataSize, int &_nSampleFormat, int &_nSampleChannels)
{
	/*
	.MSF Header is 64 bytes in size

	First 16 bytes:

	(int) "MSF"n	Where "n" = Header version number

	(int) type (adpcm / atrac / pcm - matches CELL_MS_ADPCM / CELL_MS_ATRAC* DEFINITIONS)
		3   - ADPCM
		4	- ATRAC LOW BITRATE
		5	- ATRAC MED BITRATE
		6	- ATRAC HIGH BITRATE
		7	- MP3
	(int) channels (number of channels encoded)
		1-8
	(int) File size (excluding 64 bytes of header info)

	Next 12 signed int's are loop offsets
		-1 = No Loop offset
		Note: 0 = start of sample data. NOT start of header file
		Loop offsets may not match original loop points stored within a WAV file.
		Loop offsets will be modified so that they are at the start of an ATRAC3 data packet
	*/


	int *ptr = NULL;
	char *cpt = NULL;
	int i = -1;

	InitFile(_filename, &_sampleData, &_sampleDataSize);

	ptr=(int*)_sampleData;
	cpt=(char *)_sampleData;
	ptr++;
	_nSampleFormat = *ptr++;
	_nSampleChannels = *ptr++;

	printf("Header: ");
	for (i=0;i<3;i++)
	{
		printf("%c",*cpt++);
	}
	printf("\n");
	printf("Version: %d\n",*cpt);

	printf("Sample Format = 0x%x\n", _nSampleFormat);
	printf("Sample Channels = 0x%x\n", _nSampleChannels);
	printf("Sample Size: 0x%x\n",*ptr);

	//E Modify start and size to skip the 64 bytes .MSF header
	_sampleData += 64;
	_sampleDataSize -= 64;

}


/**********************************************************************************

InitFile
	Handles the opening / loading of a file

	Requires:	*filename		Pointer to a file path string
				*addr			Pointer to an address to store the loaded data address
				*size			Pointer to an address to store the loaded data size

	Returns:	File handle

**********************************************************************************/
int InitFile(const char *filename,long *addr, long *size)
{
	if(!(filename && addr && size))
		return -1;

	long pData;

    // Open PCM sample data
    int nFileHandle=OpenFile( filename, size);

    if(nFileHandle<0)
    {
        printf(" ERROR opening file - %s, exiting.\n", filename);
        while(1){};
    }

	printf("Attempt to allocate 0x%x bytes\n",(int)*size);
    // Allocate memory for a sample buffer
	pData = (long)memalign(128,*size);
	printf("allocated addres: 0x%x\n",(int)pData);
	// Load file.
	LoadFile(nFileHandle,pData,*size);
	*addr=pData;

	return(nFileHandle);
}




/**********************************************************************************

InitialiseAudio

	This function sets up the audio system.

	Requires:	nStreams		Maximum number of streams to be active at any time
				nmaxSubs		Maximum number of sub channels to init in MultiStream
				_nPortNumber	Reference to int - Returns port number from CELL audio init
				_audioParam		Reference to CellAudioPortParam - Returns audio params from CELL audio init
				_portConfig		Reference to CellAudioPortConfig - Returns port configuration from CELL audio init
				_flags			MultiStream flags to pass to cellMSSystemGetNeededMemorySize and cellMSSystemInit* functions
							Default flag setting is no flags: "CELL_MS_NOFLAGS"

	Returns:	0	OK
				-1	Error


**********************************************************************************/
long InitialiseAudio( const long nStreams, const long nmaxSubs, int &_nPortNumber , CellAudioPortParam &_audioParam, CellAudioPortConfig &_portConfig, const int _nFlags, bool _bSkipGraphicsInit)
{
	CellMSSystemConfig cfg;

#ifndef MS_THREADED_SAMPLE
	uint8_t prios[8] = {1, 0, 0, 0, 0, 0, 0, 0};
#endif

	printf("Initialising\n");

// Setup system memory allocation

	cfg.channelCount=nStreams;
	cfg.subCount=nmaxSubs;
	cfg.dspPageCount=5;
	cfg.flags=_nFlags;	//default is CELL_MS_NOFLAGS

    _nPortNumber = audioInitCell(_bSkipGraphicsInit);
	if(_nPortNumber < 0)
	{
		printf("InitialiseAudio: Failed to find valid port number!\n");
		return -1;
	}

	_audioParam = audioParam;
	_portConfig = portConfig;

	// Initialise MultiStream

	int nMemoryNeeded = cellMSSystemGetNeededMemorySize(&cfg);
	s_pMultiStreamMemory = memalign(128, nMemoryNeeded);


	//Init Sulpha
	if(!InitSulpha(SULPHA_MEMORYBUFFER_SIZE , SULPHA_NUM_NAMED_OBJECTS))
		return -1;


#ifndef MS_THREADED_SAMPLE
	InitSPURS();

	// Initialise SPURS MultiStream version
	cellMSSystemInitSPURS(s_pMultiStreamMemory, &cfg, &spurs, &prios[0]);
#else
	// Initialise Threaded MultiStream version (define MS_THREADED_SAMPLE in proprocessor flags)
	cellMSSystemInitSPUThread(s_pMultiStreamMemory, &cfg, 100);
#endif

    return 0;
}


/**********************************************************************************
InitSulpha

	Initialises memory and DECI3 connection for Sulpha audio debugger PC tool
**********************************************************************************/
bool InitSulpha(unsigned int _memoryBufferSize, unsigned int _numNames)
{
#ifdef USE_SULPHA
	s_pSulphaMemory = malloc(_memoryBufferSize);
	if(!s_pSulphaMemory)
		return false;

	int result = cellMSSulphaInit(s_pSulphaMemory, _memoryBufferSize, _numNames);
	printf("cellMSSulphaInit returned %d\n", result);

	// As well as using the Sulpha DECI3 connection, it is also possible to 
	// write directly to a file using cellMSSulphaFileConnect/Disconnect.
	result = cellMSSulphaDECI3Start();
	printf("cellMSSulphaDECI3Start returned %d\n", result);
#endif //USE_SULPHA

	return true;
}



/**********************************************************************************
ShutdownMultiStream

	This function closes the MultiStream system.
	All previously allocated memory is also free'd.
	Note that there is no need to stop any streams here. Just by not calling the
	update functions, no more data will be generated.

**********************************************************************************/
void ShutdownMultiStream()
{

#ifdef USE_SULPHA
	cellMSSulphaShutdown();
	if( s_pSulphaMemory )
	{
		free( s_pSulphaMemory );
		s_pSulphaMemory = NULL;
	}
#endif

	void* pMemory = cellMSSystemClose();
	assert(pMemory == s_pMultiStreamMemory);

	free( s_pMultiStreamMemory);

	s_pMultiStreamMemory = NULL;
	pMemory = NULL;
}


/**********************************************************************************
OpenFile

	This function opens a file.

	Requires:	pszFilename		Name of file to load
				pnSize			Pointer to pass back the size of data loaded
				nStartOffset	Offset in bytes to skip when reading file

	Returns:	>= 0			File handle
				-1				File not found
				-2				Seek fail
**********************************************************************************/
int OpenFile( const char* pszFilename, long* pnSize, int nStartOffset )
{
int ret;
int fd;
uint64_t	pos=0;
    printf("Open file: %s\n", pszFilename);

    ret = cellFsOpen (pszFilename, CELL_FS_O_RDONLY, &fd, NULL, 0);
    if (ret) {
        printf ("cellFsOpen(%s) returned %d\n", pszFilename, ret);
		return(-1);
    }

	ret = cellFsLseek(fd,0,CELL_FS_SEEK_END, &pos);
	if (ret!=0)
	{
		printf("seek to enderror %x\n",ret);
		cellFsClose (fd);
		return(-2);
	}

    *pnSize = (long )pos;

	ret = cellFsLseek(fd, nStartOffset ,CELL_FS_SEEK_SET,&pos);
	if (ret!=0)
	{
		printf("seek to start error %x\n",ret);
		cellFsClose (fd);
		return(-2);
	}

	return(fd);
}

/**********************************************************************************
LoadFile

	This function loads a file into memory.

	Requires:	fd				Handle of file to use
				ppData			Pointer to pass back where file will be loaded
				nReadSize	 	Size of data to load
				nStartOffset	Offset to the read start point from the file beginning
				nEndOffset		Offset from end of the file to stop reading

	Returns:	0				OK
				-1				File load failed
**********************************************************************************/
long LoadFile( const int fd, long ppData, long nReadSize, int nStartOffset, int nEndOffset)
{
	uint64_t nRead = 0;
	uint64_t pos=0;
	int ret;
	int loadSize;

	loadSize=nReadSize;			// Change this to allow file to be loaded in smaller chunks

	while(nReadSize!=0)
	{
		if (loadSize>nReadSize)
			loadSize=nReadSize;

		ret=cellFsRead(fd, (void*)ppData, loadSize, &nRead);
		if (ret!=0)
		{
			printf("read error %x\n",ret);
			cellFsClose (fd);
			return(-1);
		}

	    if( (long)nRead != loadSize )		// Reached end of file and more data still required
	    {
			printf("Looping..\n");
			nRead-=nEndOffset;
			ret = cellFsLseek(fd,nStartOffset,CELL_FS_SEEK_SET,&pos);	// Seek back to start
			if (ret!=0)
			{
				printf("seek error %x\n",ret);
				cellFsClose (fd);
				return(-1);
			}
		}
		ppData+=nRead;
		nReadSize-=nRead;
    }
	return(0);	// All file loaded
}

/**********************************************************************************
StartMultiStreamUpdateThread
	This function creates the thread to update multistream.

	Requires:
		_thread		Thread function to call to handle MS/libaudio buffer updates

**********************************************************************************/
long StartMultiStreamUpdateThread(void _thread (uint64_t param))
{
   
	// create the MultiStream / libaudio update thread
	int nRet = sys_ppu_thread_create(&s_MultiStreamPuThread, _thread, NULL, SERVER_PRIO, STACK_SIZE, SYS_PPU_THREAD_CREATE_JOINABLE, "MultiStream PU Thread");
	if(nRet)
	{
		printf("ERROR creating Multistream update thread!!!\n");
		return -1;
	}
	printf("Multistream thread (%d) created OK.\n", (int)s_MultiStreamPuThread);
    return 0;
}


/**********************************************************************************
InitSPURS
	Initialises SPURS so that SPURS version of MultiStream can then load
**********************************************************************************/
#ifndef MS_THREADED_SAMPLE

void InitSPURS(void)
{
	int ret = -1;
	sys_ppu_thread_t	thread_id;
	int					ppu_thr_prio __attribute__((aligned (128)));  // information for the reverb

	sys_ppu_thread_get_id(&thread_id);
	ret = sys_ppu_thread_get_priority(thread_id, &ppu_thr_prio);
	if(ret != CELL_OK)
	{
		printf( " ERROR sys_ppu_thread_get_priority = 0x%x\n", ret ); while(1){};
	}
	printf(" thread_id = %d, ppu_thr_prio = %d\n", (int)thread_id, ppu_thr_prio );

	// Keep the SPURS_SPU_NUM value as low as possible (MultiStream uses a maximum of 1 SPU) to reduce 
	// priority conflicts when SPURS SPU thread groups are context switched in and out by the PS3 operating system.
	ret = cellSpursInitialize(&spurs, SPURS_SPU_NUM, SPU_THREAD_GROUP_PRIORITY, ppu_thr_prio-1, false);
	if(ret != CELL_OK)
	{
		printf( "******** ERROR cellSpursInitialize = 0x%x\n", ret );
		while(1){};
	}
}

#endif


//Load up a generic bunch of modules that are useful for MultiStream samples
bool LoadModules()
{
    printf( "\nLoading libfs\n" );
	int ret = cellSysmoduleLoadModule( CELL_SYSMODULE_FS );
	if ( ret < 0 )
	{
		printf( "\nError loading module FS!!!\n" );
		return false;
	}
    
    printf( "\nLoading libusbd\n" );
	ret = cellSysmoduleLoadModule( CELL_SYSMODULE_USBD );
	if ( ret < 0 )
	{
		printf( "\nError loading module USBD!!!\n" );
		return false;
	}
    
    printf( "\nLoading libnet\n" );
	ret = cellSysmoduleLoadModule( CELL_SYSMODULE_NET );
	if ( ret < 0 )
	{
		printf( "\nError loading module NET!!!\n" );
		return false;
	}

    printf( "\nLoading libio\n" );
	ret = cellSysmoduleLoadModule( CELL_SYSMODULE_IO );
	if ( ret < 0 )
	{
		printf( "\nError loading module IO!!!\n" );
		while(1){};
	}

    printf( "\nLoading libaudio\n" );
	ret = cellSysmoduleLoadModule( CELL_SYSMODULE_AUDIO );
	if ( ret < 0 )
	{
		printf( "\nError loading module AUDIO!!!\n" );
		return false;
	}

    printf( "\nLoading libresc\n" );
	ret = cellSysmoduleLoadModule( CELL_SYSMODULE_RESC );
	if ( ret < 0 )
	{
		printf( "\nError loading module RESC!!!\n" );
		return false;
	}

#ifndef MS_THREADED_SAMPLE
    printf( "\nLoading libspurs\n" );
	ret = cellSysmoduleLoadModule( CELL_SYSMODULE_SPURS );
	if ( ret < 0 )
	{
		printf( "\nError loading module SPURS!!!\n" );
		return false;
	}
#endif

    return true;
}

//Unload modules
bool UnloadModules()
{
    printf( "\n Unloading libfs\n" );
    int ret = cellSysmoduleUnloadModule( CELL_SYSMODULE_FS );
	if ( ret < 0 )
	{
		printf( "\nError unloading module FS!!!\n" );
		return false;
	}
    
    printf( "\n Unloading libusbd\n" );
	ret = cellSysmoduleUnloadModule( CELL_SYSMODULE_USBD );
	if ( ret < 0 )
	{
		printf( "\nError unloading module USBD!!!\n" );
		return false;
	}
    
    printf( "\n Unloading libnet\n" );
	ret = cellSysmoduleUnloadModule( CELL_SYSMODULE_NET );
	if ( ret < 0 )
	{
		printf( "\nError unloading module NET!!!\n" );
		return false;
	}

    printf( "\n Unloading libio\n" );
	ret = cellSysmoduleUnloadModule( CELL_SYSMODULE_IO );
	if ( ret < 0 )
	{
		printf( "\nError unloading module IO!!!\n" );
		while(1){};
	}

    printf( "\n Unloading libaudio\n" );
	ret = cellSysmoduleUnloadModule( CELL_SYSMODULE_AUDIO );
	if ( ret < 0 )
	{
		printf( "\nError unloading module AUDIO!!!\n" );
		return false;
	}

    printf( "\n Unloading libresc\n" );
    ret = cellSysmoduleUnloadModule( CELL_SYSMODULE_RESC );
	if ( ret < 0 )
	{
		printf( "\nError unloading module RESC!!!\n" );
		return false;
	}

#ifndef MS_THREADED_SAMPLE
    printf( "\n Unloading libspurs\n" );
	ret = cellSysmoduleUnloadModule( CELL_SYSMODULE_SPURS );
	if ( ret < 0 )
	{
		printf( "\nError unloading module SPURS!!!\n" );
		return false;
	}
#endif

    return true;
}


/**********************************************************************************
	systemCallback
	sysutil callback to catch the exit request
**********************************************************************************/
static void systemCallback(const uint64_t status, const uint64_t param, void *userdata)
{
	//Remove compiler warnings
	(void)param;
	(void)userdata;

	switch (status) 
	{
		case CELL_SYSUTIL_REQUEST_EXITGAME:
			printf("system notification: CELL_SYSUTIL_REQUEST_EXITGAME\n");
			s_receivedExitGameRequest = true;
			break;

		default:
			//printf("system notification: unknown status\n");
			break;
	}
}
