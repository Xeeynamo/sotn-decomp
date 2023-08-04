#include "common.h"
#include "libsnd_internal.h"

void SsVoKeyOff(s32 vab_pro, s32 pitch) {
    SpuVmSeKeyOff((vab_pro << 8) >> 0x10, vab_pro, (pitch >> 8), pitch);
}
