#include "common.h"
#include "registers.h"

extern u32 D_8006BAF4;
extern u32 D_800987B8;
extern u32 D_800987C0;

void StSetMask(u32 mask, u32 start, u32 end) {
    D_800987C0 = mask;
    D_8006BAF4 = start;
    D_800987B8 = end;
}
