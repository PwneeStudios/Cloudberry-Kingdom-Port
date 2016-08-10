/* ========================================================================================== */
/* FMOD WiiU Specific header file. Copyright (c), Firelight Technologies Pty, Ltd. 2011-2012. */
/* ========================================================================================== */

#ifndef _FMODWIIU_H
#define _FMODWIIU_H

#include "fmod.h"
#include <cafe/fs.h>

typedef unsigned int FMOD_WIIU_CONTROLLER;

/*
[DEFINE]
[
    [DESCRIPTION]   
    Pass this to FMOD_WiiU_SetControllerSpeaker to specify which controllers the sound
    should be played out of.

    [REMARKS]
    By default audio will be played out of the TV speakers only.

    [SEE_ALSO]
    FMOD_WiiU_SetControllerSpeaker
    FMOD_WiiU_GetControllerSpeaker
]
*/
#define FMOD_WIIU_CONTROLLER_DEFAULT 0x00000000
#define FMOD_WIIU_CONTROLLER_TV      0x00000001
#define FMOD_WIIU_CONTROLLER_DRC     0x00000002


/*
[ENUM]
[
    [DESCRIPTION]   
    These definitions can be used for creating WiiU FMOD_HARDWARE DSP effects.

    [REMARKS]

    [SEE_ALSO]
    System::createDSPByType
]
*/
typedef enum FMOD_DSP_TYPE_WIIU
{
    FMOD_DSP_TYPE_WIIU_REVERB = FMOD_DSP_TYPE_HARDWARE, /* Reverb DSP effect. */
    FMOD_DSP_TYPE_WIIU_CHORUS,                          /* Chorus DSP effect. */
    FMOD_DSP_TYPE_WIIU_DELAY,                           /* Chorus DSP effect. */
    FMOD_DSP_TYPE_WIIU_FORCEINT = 65536                 /* Makes sure this enum is signed 32bit. */
} FMOD_DSP_TYPE_WIIU;


/*
[ENUM]
[  
    [DESCRIPTION]   
    Hardware reverb effect properties.

    [REMARKS]

    [SEE_ALSO]      
    DSP::setParameter
    DSP::getParameter
    FMOD_DSP_TYPE_WIIU
]
*/
typedef enum FMOD_DSP_WIIU_REVERB
{
    FMOD_DSP_WIIU_REVERB_EARLYREFLECTION,   /* 5.0 to 40.0        - Initial reflection delay (in milliseconds), in 5ms increments i.e. 5ms, 10ms, 15ms... */
    FMOD_DSP_WIIU_REVERB_PREDELAYMAX,       /* 0.0 to 0.1         - Maximum value of pre-delay (in seconds) for the end of reverberation (maximum delay time until reflection begins). The memory to be used for pre-delay is allocated according to this value. */
    FMOD_DSP_WIIU_REVERB_PREDELAY,          /* 0.0 to PreDelayMax - Pre-delay (in seconds) for the end of reverberation (delay time until reverberation begins). */
    FMOD_DSP_WIIU_REVERB_FUSEDMODE,         /* 0.0 to 4.0         - Mode for the end of reverberation. 0 = metal tank, 1 = small room, 2 = large room, 3 = hall, 4 = cavernous. */
    FMOD_DSP_WIIU_REVERB_FUSEDTIME,         /* 0.0 to 10.0        - Reverberation time (in seconds) for the end of reverberation. */
    FMOD_DSP_WIIU_REVERB_COLORATION,        /* 0.0 to 1.0         - Tunes the coefficients of the all-pass filter. This number is used to simulate the acoustic properties of sound-reflective walls. In general, the smaller this value becomes, the coarser the reverberation density. In the opposite way, as this value increases the reverberation becomes more dense, but waveform interference may cause the high frequencies to stand out. */
    FMOD_DSP_WIIU_REVERB_DAMPING,           /* 0.0 to 1.0         - Tunes the filter coefficient of the low-pass filter. As this value approaches 0.0, the signal's low-frequency portion becomes its main content and reverb begins to stand out. In the opposite way, as this value approaches 1.0, the high-frequency portion of the signal is passed with less attenuation, and reverb becomes less noticeable. */
    FMOD_DSP_WIIU_REVERB_CROSSTALK,         /* 0.0 to 1.0         - Sets the amount of interaction between channels. If crosstalk is set to 0.0, the reverberation does not seep into other channels at all, and any interaction among the channels is eliminated. If set to a value larger than 0.0, the reverberation will seep into other channels. */
    FMOD_DSP_WIIU_REVERB_EARLYGAIN,         /* 0.0 to 1.0         - Mix gain of the initial reflected sound. */
    FMOD_DSP_WIIU_REVERB_FUSEDGAIN,         /* 0.0 to 1.0         - Mix gain for the end of reverberation. */
    FMOD_DSP_WIIU_REVERB_OUTGAIN,           /* 0.0 to 1.0         - Output gain. */
} FMOD_DSP_WIIU_REVERB;


/*
[ENUM]
[  
    [DESCRIPTION]   
    Hardware chorus effect properties.

    [REMARKS]

    [SEE_ALSO]      
    DSP::setParameter
    DSP::getParameter
    FMOD_DSP_TYPE_WIIU
]
*/
typedef enum FMOD_DSP_WIIU_CHORUS
{
    FMOD_DSP_WIIU_CHORUS_DELAYTIME, /* 0.1 to 50.0  - Length (in milliseconds) of delay line (standard delay time of input audio). */
    FMOD_DSP_WIIU_CHORUS_DEPTH,     /* 0.0 to 1.0   - Range over which the output position from the delay line (delay time) is varied in time by the LFO. Specified as a proportion of delayTime. */
    FMOD_DSP_WIIU_CHORUS_RATE,      /* 0.1 to 2.0   - Frequency (in hertz) of LFO. */
    FMOD_DSP_WIIU_CHORUS_FEEDBACK,  /* 0.0 to 0.99  - Feedback gain. This is mainly used to heighten the flanging effect when chorus is used as a flanger. It is also possible to use this as a characteristic delay effect by setting a somewhat longer delay time. */
    FMOD_DSP_WIIU_CHORUS_OUTGAIN,   /* 0.0 to 1.0   - Output gain. */
} FMOD_DSP_WIIU_CHORUS;


/*
[ENUM]
[  
    [DESCRIPTION]   
    Hardware delay effect properties.

    [REMARKS]

    [SEE_ALSO]      
    DSP::setParameter
    DSP::getParameter
    FMOD_DSP_TYPE_WIIU
]
*/
typedef enum FMOD_DSP_WIIU_DELAY
{
    FMOD_DSP_WIIU_DELAY_MAXDELAY,   /* 0.01 to 1000.0   - Length (in milliseconds) of the delay line (maximum delay time of input audio). The memory to be used for the delay line is allocated according to this value. */
    FMOD_DSP_WIIU_DELAY_DELAY,      /* 0.01 to maxDelay - Delay time (in milliseconds). */
    FMOD_DSP_WIIU_DELAY_FEEDBACK,   /* 0.0  to 0.99     - Feedback gain. */
    FMOD_DSP_WIIU_DELAY_LPF,        /* 0.0  to 1.0      - Tunes the cut-off frequency of the low-pass filter. The smaller the value, the lower the cut-off frequency. */
    FMOD_DSP_WIIU_DELAY_OUTGAIN,    /* 0.0  to 1.0      - Output gain. */
} FMOD_DSP_WIIU_DELAY;


/*
[ENUM] 
[
    [DESCRIPTION]
    Values for the thread members of the FMOD_WIIU_EXTRADRIVERDATA structure.

    [REMARKS]

    [SEE_ALSO]
    FMOD_WIIU_EXTRADRIVERDATA
]
*/
typedef enum FMOD_THREAD
{
    FMOD_THREAD_DEFAULT,    /* Use FMOD recommended default thread assignment. */
    FMOD_THREAD_CORE0,      /* Thread will be created on Core 0. */
    FMOD_THREAD_CORE1,      /* Thread will be created on Core 1. */
    FMOD_THREAD_CORE2,      /* Thread will be created on Core 2. Default for all threads. */
    FMOD_THREAD_MAX         /* Maximum number of thread options supported. */
} FMOD_THREAD;


/*
[ENUM] 
[
    [DESCRIPTION]
    Preconfigured reverb settings that name environment types.

    [REMARKS]
    You can use these environments instead of filling the members of the property struct for FMOD_WIIU_SetReverbProperties.
    Use FMOD_WIIU_REVERB_ENV_NONE if you want to define the individual properties yourself in the struct.
    Use FMOD_WIIU_REVERB_ENV_OFF if you want to disable the reverb entirely.

    [SEE_ALSO]
    FMOD_WIIU_SetReverbProperties
]
*/
typedef enum FMOD_WIIU_REVERB_ENV
{
    FMOD_WIIU_REVERB_ENV_NONE,
    FMOD_WIIU_REVERB_ENV_OFF,
    FMOD_WIIU_REVERB_ENV_SMALL_ROOM,
    FMOD_WIIU_REVERB_ENV_LARGE_ROOM,
    FMOD_WIIU_REVERB_ENV_HALL,
    FMOD_WIIU_REVERB_ENV_CAVERNOUS_CATHEDRAL,
    FMOD_WIIU_REVERB_ENV_METAL_CORRIDOR
} FMOD_WIIU_REVERB_ENV;


/*
[STRUCTURE] 
[
    [DESCRIPTION]   
    Use this structure with System::init to set platform specific initialization settings.
    Pass this structure in as the "extradriverdata" parameter in System::init.

    [REMARKS]
    Set any member to zero for default behavior.

    [SEE_ALSO]      
    System::init
    FMOD_THREAD
]
*/
typedef struct FMOD_WIIU_EXTRADRIVERDATA
{
    FMOD_THREAD threadMixer;       /* [in] FMOD software mixer thread. */
    FMOD_THREAD threadStream;      /* [in] FMOD stream thread. */
    FMOD_THREAD threadNonBlocking; /* [in] FMOD thread for FMOD_NONBLOCKING. */
    FMOD_THREAD threadFile;        /* [in] FMOD file thread. */
    FMOD_THREAD threadGeometry;    /* [in] FMOD geometry processing thread. */
    FSClient *fileSystemClient;    /* [in/out] Provide an FSClient for FMOD to use, if NULL an FSClient will be created and returned. */
    bool allowHardwareOnCPU;       /* [in] Allow FMOD_HARDWARE channels to be processed by the CPU if the DSP is overloaded. */
} FMOD_WIIU_EXTRADRIVERDATA;


/*
[STRUCTURE] 
[
    [DESCRIPTION]   
    Parameters to control the hardware reverb effect.

    [REMARKS]
    Some parameters are undocumented, these will be updated as more details become available.

    [SEE_ALSO]
    FMOD_WIIU_REVERB_ENV
    FMOD_WIIU_SetReverbProperties
    FMOD_WIIU_GetReverbProperties
]
*/
typedef struct FMOD_WIIU_REVERB_PROPERTIES
{
    unsigned int         instance;     /* 0 to 2       - [w]   Control independent reverb effects. */
    FMOD_WIIU_REVERB_ENV environment;  /* See enum     - [r/w] Preconfigured reverb settings, overrides below properties if not set to 'none'. */
    unsigned int         earlyMode;    /* 0 to 4       - [r/w] Early reflection mode (undocumented). */
    unsigned int         lateMode;     /* 0 to 4       - [r/w] Late reverb mode (undocumented and unused). */
    float                preDelayTime; /* 0.0 to 100.0 - [r/w] Delay (in milliseconds) between the dry sound and the first early reflection. */
    float                decayTime;    /* 0.1 to 20.0  - [r/w] Decay time (in seconds) for the late reverb. */
    float                hfDecayRatio; /* 0.1 to 1.0   - [r/w] Ratio of decay time at high frequencies to that at low frequencies. Low value means high frequencies decay more quickly. */
    float                coloration;   /* 0.0 to 1.0   - [r/w] Increasing this makes the reverb more colored and less neutral. High values should sound more natural, lower values sounding unusual. */
    float                earlyGain;    /* 0.0 to 1.0   - [r/w] Gain of the early reflections. */
    float                lateGain;     /* 0.0 to 1.0   - [r/w] Gain of the late reverb. */
    float                reverbGain;   /* 0.0 to 1.0   - [r/w] Overall gain of the reverb. */
} FMOD_WIIU_REVERB_PROPERTIES;


/*
[API]
[
    [DESCRIPTION]
    Sets parameters for the global reverb environment. This function is intended as a platform specific replacement for FMOD_System_SetReverbProperties.

    [PARAMETERS]
    'prop'	    Address of an FMOD_WIIU_REVERB_PROPERTIES structure which defines the attributes for the reverb.

    [REMARKS]
    These reverb properties will only affect FMOD_HARDWARE channels, see System::setReverbProperties for an FMOD_SOFTWARE alternative.
    It is important to specify the 'instance' value in the FMOD_WIIU_REVERB_PROPERTIES structure correctly, otherwise you will get an FMOD_ERR_REVERB_INSTANCE error.

    [SEE_ALSO]
    FMOD_HARDWARE
    FMOD_WIIU_REVERB_PROPERTIES
    FMOD_WiiU_GetReverbProperties
]
*/
FMOD_RESULT F_API FMOD_WiiU_SetReverbProperties(FMOD_SYSTEM *system, const FMOD_WIIU_REVERB_PROPERTIES *prop);


/*
[API]
[
    [DESCRIPTION]
    Retrieves the current reverb environment for the specified reverb instance. This function is intended as a platform specific replacement for FMOD_System_GetReverbProperties.

    [PARAMETERS]
    'prop'	    Address of a variable that receives the current reverb environment description.

    [REMARKS]	
    It is important to specify the 'instance' value in the FMOD_WIIU_REVERB_PROPERTIES structure correctly, otherwise you will get an FMOD_ERR_REVERB_INSTANCE error.

    [SEE_ALSO]
    FMOD_WIIU_REVERB_PROPERTIES
    FMOD_WiiU_SetReverbProperties
]
*/
FMOD_RESULT F_API FMOD_WiiU_GetReverbProperties(FMOD_SYSTEM *system, FMOD_WIIU_REVERB_PROPERTIES *prop);


/*
[API]
[
    [DESCRIPTION]
    Specify which controllers to play this channel on.

    [PARAMETERS]
    'controller'    Controller to output sound to, you can OR multiple FMOD_WIIU_CONTROLLER defines together.

    [REMARKS]	
    Only FMOD_HARDWARE channels can output to alternate locations, FMOD_SOFTWARE will always come out the TV speakers.
    By default audio will be played out of the TV speakers only.
    
    [SEE_ALSO]
    FMOD_WIIU_CONTROLLER
    FMOD_WiiU_GetControllerSpeaker
]
*/
FMOD_RESULT F_API FMOD_WiiU_SetControllerSpeaker(FMOD_CHANNEL *channel, FMOD_WIIU_CONTROLLER controller);


/*
[API]
[
    [DESCRIPTION]
    Get which destination the channel will be played on, the default is the TV speakers.

    [PARAMETERS]
    'controller'    Controller to output sound to, can be multiple FMOD_WIIU_CONTROLLER defines ORed together.

    [REMARKS]	

    [SEE_ALSO]
    FMOD_WIIU_CONTROLLER
    FMOD_WiiU_SetControllerSpeaker
]
*/
FMOD_RESULT F_API FMOD_WiiU_GetControllerSpeaker(FMOD_CHANNEL *channel, FMOD_WIIU_CONTROLLER *controller);


/*
[API]
[
    [DESCRIPTION]
    Control whether audio is silenced before being sent to speakers.

    [PARAMETERS]
    'mute'    Sets the mute state.

    [REMARKS]	
    This can be called from any thread to facilitate silencing all audio if a recoverable disk error condition has occurred.

    [SEE_ALSO]
    FMOD_WiiU_GetMute
]
*/
FMOD_RESULT F_API FMOD_WiiU_SetMute(BOOL mute);


/*
[API]
[
    [DESCRIPTION]
    Fetch whether audio is silenced before being sent to speakers. 

    [PARAMETERS]
    'mute'    Gets the mute state.

    [REMARKS]	

    [SEE_ALSO]
    FMOD_WiiU_GetMute
]
*/
FMOD_RESULT F_API FMOD_WiiU_GetMute(BOOL *mute);

#endif  /* _FMODWIIU_H */
