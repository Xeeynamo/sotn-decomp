#include "common.h"

void SpuVmSeKeyOff(s32, u8, u16, u8);

void SsVoKeyOff(s32 vab_pro, s32 pitch) {
    SpuVmSeKeyOff((vab_pro << 8) >> 0x10, vab_pro, (pitch >> 8), pitch);
}
