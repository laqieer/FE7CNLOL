//#define SoundMainRAM_Buffer 0x3002378
#define SoundMainRAM_Buffer 0x3005E00
void SoundMainRAM();

__attribute__((section(".soundMainRAMSrc")))
const int soundMainRAMSrc = &SoundMainRAM;

__attribute__((section(".soundMainRAMBuffer")))
const int soundMainRAMBuffer = SoundMainRAM_Buffer;

__attribute__((section(".soundMainRAMFunc")))
const int soundMainRAMFunc = SoundMainRAM_Buffer | 1;

__attribute__((section(".soundMainRAMWordCnt")))
const short soundMainRAMWordCnt = 0x200;

// This is a table of deltas between sample values in compressed PCM data.
const signed char gDeltaEncodingTable[] =
{
      0,
      1,
      4,
      9,
     16,
     25,
     36,
     49,
    -64,
    -49,
    -36,
    -25,
    -16,
     -9,
     -4,
     -1,
};
