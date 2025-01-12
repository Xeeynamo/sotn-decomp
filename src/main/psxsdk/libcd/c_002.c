#include "common.h"
#include "registers.h"

void init_ring_status(s32, s32);
extern s32 D_8003C0FC;
extern s16 D_8003C75C;
extern s32 D_8003C908;
extern s32 D_800730D4;
extern s32 D_80097954;
extern s32 D_80097958;
extern s32 D_80097960;
extern s32 D_80098894;

void StClearRing(void) {
    D_80097960 = 0;
    D_80097958 = 0;
    D_80097954 = 0;
    D_800730D4 = 0;
    init_ring_status(0, D_80098894);
    D_8003C908 = 0;
    D_8003C75C = 0;
    D_8003C0FC = 0;
}
