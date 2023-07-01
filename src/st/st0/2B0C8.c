#include "st0.h"

INCLUDE_ASM("asm/us/st/st0/nonmatchings/2B0C8", EntityStageTitleFadeout);

INCLUDE_ASM("asm/us/st/st0/nonmatchings/2B0C8", EntityStageTitleCard);

INCLUDE_ASM("asm/us/st/st0/nonmatchings/2B0C8", func_801ABBBC);

s32 func_801AC458(s16 arg0) {
    // !FAKE:
    s32 ret = arg0;
    Entity* e;
    Entity* new_var;

    switch (ret) {
    case 0:
        e = g_CurrentEntity;
        ret = 1;
        e[1].unk19 = 2;
        e[1].unk1C = 0x600;
        e[1].animFrameIdx = 0;
        e[1].animFrameDuration = 0;
        e[1].step = 2;
        e[1].posX.i.hi = e->posX.i.hi;
        e[1].posY.i.hi = e->posY.i.hi + 16;

    case 1:
        new_var = &g_CurrentEntity[1];
        if (AnimateEntity(D_80180964, new_var) == 0) {
            ret++;
        }
        if (LOW(new_var->animFrameIdx) == 6) {
            g_CurrentEntity->ext.stub[0x24] = 1;
        }
        break;

    case 2:
        e = &g_CurrentEntity[1];
        e->animCurFrame = 0;
        e->unk19 = 0;
        e->step = 1;
        ret = 0xFF;
        break;
    }
    return ret;
}