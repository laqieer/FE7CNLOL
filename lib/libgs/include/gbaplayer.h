/****************************************************************
/ GBA Module Player    Copyright (c) 2001-2002 Sergej Kravcenko /
/ Version 1.1          sergej@codewaves.com                     /
****************************************************************/

#ifndef GBAPLAYER
#define GBAPLAYER

//////////////////////////// Structures ////////////////////////////
typedef struct
{
   const unsigned char  *lpbSample;    // Sample data in 8-bit mono RAW  format
   unsigned char        bLeft;         // 0 - left channel, non-0 - right channel
   unsigned long        lStart;        // Start position
   unsigned long        lSize;         // Sample size
   unsigned long        lRepStart;     // Loop start
   unsigned long        lRepEnd;       // Loop end
   unsigned char        bVolume;       // Sound effect volume
   unsigned char        bRep;          // 0 - disable looping, non-0 - enable looping
   unsigned long        lFrq;          // Sample frequency (max 21600 Hz)
} SFXINFO;

/////////////////////////////// Mixing frequencies ///////////////////
#define MIXFREQ_5664    0
#define MIXFREQ_7552    1
#define MIXFREQ_9440    2
#define MIXFREQ_11328   3
#define MIXFREQ_13216   4
#define MIXFREQ_15104   5
#define MIXFREQ_16992   6
#define MIXFREQ_18880   7
#define MIXFREQ_20768   8
#define MIXFREQ_22656   9

/////////////////////////// Prototypes ///////////////////////////////

// Function:      MP_IntHandler
// Description:   DMA1 interrupt handler
// Parameters:    None
// 
// Comments:      You must enable interupts and add this handle to interrupt table (DMA1 slot). 
void MP_IntHandler(void);


// Function:      MP_InitArm
// Description:   Inits gba music player and sound engine
// Parameters:    Mixing frequency. Player supports 5664 Hz - 22656 Hz mixing frequency
//                with following steps:
//                Parameter  | Frequency
//                ----------------------
//                0          |  5664 Hz
//                1          |  7552 Hz
//                2          |  9440 Hz
//                3          | 11328 Hz
//                4          | 13216 Hz
//                5          | 15104 Hz 
//                6          | 16992 Hz
//                7          | 18880 Hz
//                8          | 20768 Hz 
//                9          | 22656 Hz 
// Comments:      Make sure that dma interrupt handler is set before using this function
void MP_InitArm(unsigned char bFreq);
void MP_InitThumb(unsigned char bFreq);

// Function:      MP_UpdateArm
// Description:   Updates current player status
// Parameters:    None
// 
// Comments:      You must call this function every GBA screen frame. It doesn't 
//                matter when you call this function - at frame start or frame end.
// WARNING!!!     This call will enable interrupts and disable all interrupts
//                except DMA1 interrupt. Call this function first and then enable all
//                your interrupts.
void MP_UpdateArm(void);
void MP_UpdateThumb(void);

// Function:      MP_PlayModuleArm
// Description:   Sets current module for playback.
// Parameters:    lpbModule -> pointer to module data
//                bLoop     -> loop module
// 
// Comments:      You can call this function when you want to play new module or change
//                current module
void MP_PlayModuleArm(const unsigned char *lpbModule, unsigned char bLoop);
void MP_PlayModuleThumb(const unsigned char *lpbModule, unsigned char bLoop);

// Function:      MP_StopModuleArm
// Description:   Stops module playback
// Parameters:    None
void MP_StopModuleArm(void);
void MP_StopModuleThumb(void);

// Function:      MP_ResumeModuleArm
// Description:   Resumes module playback
// Parameters:    None
void MP_ResumeModuleArm(void);
void MP_ResumeModuleThumb(void);

// Function:      MP_SetVolumeArm
// Description:   Sets module volume
// Parameters:    bVol - module volume (0-100)
void MP_SetVolumeArm(unsigned char bVol);
void MP_SetVolumeThumb(unsigned char bVol);

// Function:      MP_PlaySfxArm
// Description:   Plays sound effect
// Parameters:    lpsfxInfo -> sound effect information (see struct description for more info)
void MP_PlaySfxArm(SFXINFO *lpsfxInfo);
void MP_PlaySfxThumb(SFXINFO *lpsfxInfo);

// Function:      MP_StopSfxArm
// Description:   Stops sound effect playback
// Parameters:    bLeft -> 0 - left channel, non-0 - right channel
// 
// Comments:      This function is usefull when you want to stop sound effect with
//                looping
void MP_StopSfxArm(unsigned char bLeft);
void MP_StopSfxThumb(unsigned char bLeft);

// Function:      MP_GetModulePos
// Description:   Returns current playing module position
// Parameters:    lpbPattern -> pointer to variable where module pattern number will be stored
//                lpbPatternPos -> pointer to variable where module pattern position will be stored
void MP_GetModulePosArm(unsigned char *lpbPattern, unsigned char *lpbPatternPos);
void MP_GetModulePosThumb(unsigned char *lpbPattern, unsigned char *lpbPatternPos);

// Function:      MP_SetModulePos
// Description:   Sets current playing module position
// Parameters:    bPattern -> module pattern number 
//                bPatternPos -> module pattern position
void MP_SetModulePosArm(unsigned char bPattern, unsigned char bPatternPos);
void MP_SetModulePosThumb(unsigned char bPattern, unsigned char bPatternPos);

#endif
