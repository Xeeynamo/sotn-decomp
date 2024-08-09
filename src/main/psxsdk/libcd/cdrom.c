#include "common.h"

extern void StClearRing(void);
extern s32 D_800987C8;
extern s32 D_80098894;

void StSetRing(s32 arg0, s32 arg1) {
    D_800987C8 = arg0;
    D_80098894 = arg1;
    StClearRing();
}
