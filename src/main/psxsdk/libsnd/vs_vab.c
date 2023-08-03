#include "common.h"

INCLUDE_ASM("asm/us/main/nonmatchings/psxsdk/libsnd/vs_vab", SsVabClose);

typedef struct VabHdr {
    s32 form;
    s32 ver;
    s32 id;
    u32 fsize;
    u16 reserved0;
    u16 ps;
    u16 ts;
    u16 vs;
    u8 mvol;
    u8 pan;
    u8 attr1;
    u8 attr2;
    u32 reserved1;
} VabHdr;

s16 SsVabOpenHead(u8*, s16);
s16 SsVabTransBody(u8*, s16);
extern s32 D_80098854[];

s16 SsVabOpen(u8* addr, VabHdr* vab_header) {
    s16 vab_id;

    vab_id = SsVabOpenHead(addr, -1);
    if (vab_id != -1) {
        vab_id = SsVabTransBody(D_80098854[vab_id], vab_id);
    }
    return vab_id;
}
