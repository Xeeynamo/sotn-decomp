// SPDX-License-Identifier: AGPL-3.0-or-later
#include "bo4.h"

INCLUDE_ASM("boss/bo4/nonmatchings/unk_45354", func_us_801C5354);

void func_8010E0A8(void) {
    g_Entities[STAGE_ENTITY_START + UNK_ENTITY_1].ext.entSlot1.unk2 = 0;
}

void func_8010E0B8(void) {
    g_Entities[STAGE_ENTITY_START + UNK_ENTITY_1].ext.entSlot1.unk1 = 0;
    g_Entities[STAGE_ENTITY_START + UNK_ENTITY_1].ext.entSlot1.unk0 = 0;
}


INCLUDE_ASM("boss/bo4/nonmatchings/unk_45354", func_us_801C5430);

// begin: split to common decelerate
void DecelerateX(s32 amount) {
    if (g_CurrentEntity->velocityX < 0) {
        g_CurrentEntity->velocityX += amount;
        if (g_CurrentEntity->velocityX > 0) {
            g_CurrentEntity->velocityX = 0;
        }
    } else {
        g_CurrentEntity->velocityX -= amount;
        if (g_CurrentEntity->velocityX < 0) {
            g_CurrentEntity->velocityX = 0;
        }
    }
}

void DecelerateY(s32 amount) {
    if (g_CurrentEntity->velocityY < 0) {
        g_CurrentEntity->velocityY += amount;
        if (g_CurrentEntity->velocityY > 0) {
            g_CurrentEntity->velocityY = 0;
        }
    } else {
        g_CurrentEntity->velocityY -= amount;
        if (g_CurrentEntity->velocityY < 0) {
            g_CurrentEntity->velocityY = 0;
        }
    }
}
// end: split to common decelerate

extern PlayerState g_Dop;

s32 CheckMoveDirection(void) {
    if (g_Dop.unk44 & 2) {
        return 0;
    }
    if (DOPPELGANGER.facingLeft == 1) {
        if (g_Dop.padPressed & PAD_RIGHT) {
            DOPPELGANGER.facingLeft = 0;
            g_Dop.unk4C = 1;
            return -1;
        } else if (g_Dop.padPressed & PAD_LEFT) {
            return 1;
        }
    } else {
        if (g_Dop.padPressed & PAD_RIGHT) {
            return 1;
        }
        if (g_Dop.padPressed & PAD_LEFT) {
            DOPPELGANGER.facingLeft = 1;
            g_Dop.unk4C = 1;
            return -1;
        }
    }
    return 0;
}

INCLUDE_ASM("boss/bo4/nonmatchings/unk_45354", func_us_801C55A8);

void SetSpeedX(s32 speed) {
    if (g_CurrentEntity->facingLeft == 1) {
        speed = -speed;
    }
    g_CurrentEntity->velocityX = speed;
}

void func_8010E3B8(s32 velocityX) {
    if (DOPPELGANGER.entityRoomIndex == 1) {
        velocityX = -velocityX;
    }
    DOPPELGANGER.velocityX = velocityX;
}

INCLUDE_ASM("boss/bo4/nonmatchings/unk_45354", func_us_801C5648);

INCLUDE_ASM("boss/bo4/nonmatchings/unk_45354", func_us_801C56A8);

INCLUDE_ASM("boss/bo4/nonmatchings/unk_45354", func_us_801C57E4);

INCLUDE_ASM("boss/bo4/nonmatchings/unk_45354", func_us_801C58E4);

INCLUDE_ASM("boss/bo4/nonmatchings/unk_45354", func_us_801C5990);

INCLUDE_ASM("boss/bo4/nonmatchings/unk_45354", func_us_801C59DC);

INCLUDE_ASM("boss/bo4/nonmatchings/unk_45354", func_us_801C5A4C);

INCLUDE_ASM("boss/bo4/nonmatchings/unk_45354", func_us_801C5AD8);

INCLUDE_ASM("boss/bo4/nonmatchings/unk_45354", func_us_801C5B68);

INCLUDE_ASM("boss/bo4/nonmatchings/unk_45354", func_us_801C5C94);

INCLUDE_ASM("boss/bo4/nonmatchings/unk_45354", func_us_801C5CF8);

INCLUDE_ASM("boss/bo4/nonmatchings/unk_45354", func_us_801C5FAC);

INCLUDE_ASM("boss/bo4/nonmatchings/unk_45354", func_us_801C5FDC);

INCLUDE_ASM("boss/bo4/nonmatchings/unk_45354", func_us_801C6040);

INCLUDE_ASM("boss/bo4/nonmatchings/unk_45354", func_us_801C65F0);

INCLUDE_ASM("boss/bo4/nonmatchings/unk_45354", func_us_801C6654);

INCLUDE_ASM("boss/bo4/nonmatchings/unk_45354", func_us_801C6884);

INCLUDE_ASM("boss/bo4/nonmatchings/unk_45354", func_us_801C68D0);

INCLUDE_ASM("boss/bo4/nonmatchings/unk_45354", func_us_801C6BA0);

INCLUDE_ASM("boss/bo4/nonmatchings/unk_45354", func_us_801C6BE8);

INCLUDE_ASM("boss/bo4/nonmatchings/unk_45354", func_us_801C6E7C);

INCLUDE_ASM("boss/bo4/nonmatchings/unk_45354", func_us_801C6F74);

INCLUDE_ASM("boss/bo4/nonmatchings/unk_45354", func_us_801C7244);

INCLUDE_ASM("boss/bo4/nonmatchings/unk_45354", func_us_801C72BC);

INCLUDE_ASM("boss/bo4/nonmatchings/unk_45354", func_us_801C7340);

INCLUDE_ASM("boss/bo4/nonmatchings/unk_45354", func_us_801C7380);

INCLUDE_ASM("boss/bo4/nonmatchings/unk_45354", func_us_801C78DC);

INCLUDE_ASM("boss/bo4/nonmatchings/unk_45354", func_us_801C80D8);

INCLUDE_ASM("boss/bo4/nonmatchings/unk_45354", func_us_801C8184);

INCLUDE_ASM("boss/bo4/nonmatchings/unk_45354", func_us_801C820C);

INCLUDE_ASM("boss/bo4/nonmatchings/unk_45354", func_us_801C8224);

INCLUDE_ASM("boss/bo4/nonmatchings/unk_45354", func_us_801C8CE0);

INCLUDE_ASM("boss/bo4/nonmatchings/unk_45354", func_us_801C8EE4);

INCLUDE_ASM("boss/bo4/nonmatchings/unk_45354", func_us_801C8F3C);

INCLUDE_ASM("boss/bo4/nonmatchings/unk_45354", func_us_801C93C4);

INCLUDE_ASM("boss/bo4/nonmatchings/unk_45354", func_us_801C95E4);

INCLUDE_ASM("boss/bo4/nonmatchings/unk_45354", func_us_801C9694);

Entity* GetFreeEntity(s16 start, s16 end) {
    Entity* entity = &g_Entities[start];
    s16 i;

    for (i = start; i < end; i++, entity++) {
        if (entity->entityId == E_NONE) {
            return entity;
        }
    }
    return NULL;
}

Entity* GetFreeEntityReverse(s16 start, s16 end) {
    Entity* entity = &g_Entities[end - 1];
    s16 i;

    for (i = end - 1; i >= start; i--, entity--) {
        if (entity->entityId == E_NONE) {
            return entity;
        }
    }
    return NULL;
}

// TODO: this is the same as unionD_800ACFB4 in src/dra
typedef union {
    u8 rawBytes[4];
    AnimationFrame af;
} unionD_us_8018136C;
extern unionD_us_8018136C D_us_8018136C[];

extern u8 D_us_801D3D4C;
extern u8 D_us_801D3D50;
extern u8 D_us_801D3D54;
extern u8 D_us_801D3D58;

void func_80118C28(s32 arg0) {
    // Break up the 4-byte struct D_us_8018136C[arg0] into individual bytes.
    D_us_801D3D4C = D_us_8018136C[arg0].rawBytes[0];
    D_us_801D3D50 = D_us_8018136C[arg0].rawBytes[1];
    D_us_801D3D54 = D_us_8018136C[arg0].rawBytes[2];
    D_us_801D3D58 = D_us_8018136C[arg0].rawBytes[3];
}

INCLUDE_ASM("boss/bo4/nonmatchings/unk_45354", func_us_801C9BC0);

INCLUDE_ASM("boss/bo4/nonmatchings/unk_45354", DopEntityHitByHoly);

INCLUDE_ASM("boss/bo4/nonmatchings/unk_45354", func_us_801C9FEC);

INCLUDE_ASM("boss/bo4/nonmatchings/unk_45354", func_us_801CA014);

INCLUDE_ASM("boss/bo4/nonmatchings/unk_45354", func_us_801CA208);

INCLUDE_ASM("boss/bo4/nonmatchings/unk_45354", func_us_801CA2AC);

INCLUDE_ASM("boss/bo4/nonmatchings/unk_45354", func_us_801CA748);

INCLUDE_ASM("boss/bo4/nonmatchings/unk_45354", func_us_801CA834);

INCLUDE_ASM("boss/bo4/nonmatchings/unk_45354", DopEntityHitByDark);

INCLUDE_ASM("boss/bo4/nonmatchings/unk_45354", func_us_801CB020);

INCLUDE_ASM("boss/bo4/nonmatchings/unk_45354", func_us_801CB07C);

INCLUDE_ASM("boss/bo4/nonmatchings/unk_45354", EntityPlayerOutline);

INCLUDE_ASM("boss/bo4/nonmatchings/unk_45354", EntityGravityBootBeam);

INCLUDE_ASM("boss/bo4/nonmatchings/unk_45354", EntityWingSmashTrail);

INCLUDE_ASM("boss/bo4/nonmatchings/unk_45354", func_us_801CD178);

INCLUDE_ASM("boss/bo4/nonmatchings/unk_45354", func_us_801CD89C);

INCLUDE_ASM("boss/bo4/nonmatchings/unk_45354", DopEntityHitByLightning);

INCLUDE_ASM("boss/bo4/nonmatchings/unk_45354", EntityHitByIce);

INCLUDE_ASM("boss/bo4/nonmatchings/unk_45354", func_us_801CE9EC);

INCLUDE_ASM("boss/bo4/nonmatchings/unk_45354", func_us_801CEA30);

INCLUDE_ASM("boss/bo4/nonmatchings/unk_45354", EntityMist);

INCLUDE_ASM("boss/bo4/nonmatchings/unk_45354", func_us_801D0318);

INCLUDE_ASM("boss/bo4/nonmatchings/unk_45354", ReboundStoneBounce1);

INCLUDE_ASM("boss/bo4/nonmatchings/unk_45354", ReboundStoneBounce2);

INCLUDE_ASM("boss/bo4/nonmatchings/unk_45354", func_us_801D0DE0);

INCLUDE_ASM("boss/bo4/nonmatchings/unk_45354", func_us_801D162C);

INCLUDE_ASM("boss/bo4/nonmatchings/unk_45354", func_us_801D17EC);
