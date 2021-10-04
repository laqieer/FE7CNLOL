void SoundMainRAM();

__attribute__((section(".compressedSamplesSupport")))
const int compressedSamplesSupport = &SoundMainRAM;
