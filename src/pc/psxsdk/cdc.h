#ifndef CDC_H
#define CDC_H
#include <inttypes.h>

struct CD_Audio_Buffer {
    int16_t Samples[2][0x1000]; // [0][...] = l, [1][...] = r
    uint32_t Size;
    uint32_t Freq;
    uint32_t ReadPos;
};

extern struct CD_Audio_Buffer AudioBuffer;

void GetCDAudio(int32_t samples[2]);
void XA_ProcessSector(const uint8_t* sdata, struct CD_Audio_Buffer* ab);
#endif
