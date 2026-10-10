// SPDX-License-Identifier: AGPL-3.0-or-later
#include "bo4.h"

#include "../dop_anim.h"

extern PlayerState g_Dop;

// n.b.! the code below is the same as rbo5/unk_44954.c

// may be equivalent func_8010DFF0 in DRA
void func_us_801C5354(s32 resetAnims, s32 arg1) {
    Primitive* prim;

    if (resetAnims) {
        g_Entities[E_ID_41].ext.disableAfterImage.resetFlag = 1;
        g_Entities[E_ID_41].animCurFrame = g_Entities[E_ID_42].animCurFrame =
            g_Entities[E_ID_43].animCurFrame = 0;
        prim = &g_PrimBuf[g_Entities[E_AFTERIMAGE_1].primIndex];
        while (prim != NULL) {
            prim->x1 = 0;
            prim = prim->next;
        }
    }
    g_Entities[E_ID_41].ext.disableAfterImage.disableFlag = 1;
    g_Entities[E_ID_41].ext.disableAfterImage.index = MaxAfterImageIndex;
    if (arg1 != 0) {
        if (arg1 < 4) {
            g_Dop.timers[ALU_T_15] = 4;
        } else {
            g_Dop.timers[ALU_T_15] = arg1;
        }
    }
}

#ifndef VERSION_PC
static void ForceAfterImageOn(void) UNUSED {
    g_Entities[STAGE_ENTITY_START + E_AFTERIMAGE_1].ext.afterImage.index = 0;
}
#endif

void EnableAfterImage(void) {
    g_Entities[STAGE_ENTITY_START + E_AFTERIMAGE_1].ext.afterImage.resetFlag =
        0;
    g_Entities[STAGE_ENTITY_START + E_AFTERIMAGE_1].ext.afterImage.disableFlag =
        0;
}

// similar to DRA's func_8010E168. share's the function signature but
// not the entity creation logic, a0 is ignored
void func_us_801C5430(s16 a0, s16 minTime) {
    if (g_Dop.timers[ALU_T_INVINCIBLE_CONSUMABLES] <= minTime) {
        g_Dop.timers[ALU_T_INVINCIBLE_CONSUMABLES] = minTime;
    }
}

#ifndef VERSION_PC
#include "../../decelerate.h"
#endif

s32 CheckMoveDirection(void) {
    if (g_Dop.unk44 & 2) {
        return 0;
    }
    if (DOPPLEGANGER.facingLeft == true) {
        if (g_Dop.padPressed & PAD_RIGHT) {
            DOPPLEGANGER.facingLeft = 0;
            g_Dop.unk4C = 1;
            return -1;
        }
        if (g_Dop.padPressed & PAD_LEFT) {
            return 1;
        }
    } else {
        if (g_Dop.padPressed & PAD_RIGHT) {
            return 1;
        }
        if (g_Dop.padPressed & PAD_LEFT) {
            DOPPLEGANGER.facingLeft = 1;
            g_Dop.unk4C = 1;
            return -1;
        }
    }
    return 0;
}

s32 func_us_801C55A8(s32 minX, s32 maxX) {
    if (DOPPLEGANGER.step == Dop_Stand &&
        DOPPLEGANGER.step == DOPPLEGANGER.step_s) {
        if (DOPPLEGANGER.posX.i.hi >= minX) {
            if (maxX >= DOPPLEGANGER.posX.i.hi) {
                return true;
            }
        }
    }
    return false;
}

#ifndef VERSION_PC
#include "../../set_speed_x.h"
#endif

void DopSetVelocity(s32 velocityX) {
    if (DOPPLEGANGER.entityRoomIndex == 1) {
        velocityX = -velocityX;
    }
    DOPPLEGANGER.velocityX = velocityX;
}
