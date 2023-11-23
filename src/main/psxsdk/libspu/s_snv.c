#include "common.h"

void SpuSetAnyVoice(s32, s32, u16, u16);

void SpuSetNoiseVoice(s32 a, s32 b) { SpuSetAnyVoice(a, b, 0xCA, 0xCB); }
