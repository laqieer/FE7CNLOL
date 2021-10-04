#define SoundMainRAM_Buffer 0x3005DA0
void SoundMainRAM();

__attribute__((section(".soundMainRAMSrc")))
const int soundMainRAMSrc = &SoundMainRAM;

__attribute__((section(".soundMainRAMBuffer")))
const int soundMainRAMBuffer = SoundMainRAM_Buffer;

__attribute__((section(".soundMainRAMFunc")))
const int soundMainRAMFunc = SoundMainRAM_Buffer | 1;

__attribute__((section(".soundMainRAMWordCnt")))
const short soundMainRAMWordCnt = 0x2A0;
