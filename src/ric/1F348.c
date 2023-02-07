#include "common.h"
#include "game.h"
#include "objects.h"
#include "sfx.h"

void func_8015C908(s32 step);
void func_8015C920(s32* unk0);
void func_8015D020(void);
bool func_8015DBB0(s32);
void func_8015C93C(s32 speed);
s32 func_8015C9CC(void);
void func_8015CA84(s32 speed);
void func_8015CD98(s32 accelerationX);
void func_8015CDE0(s32);
void func_8015CE7C(void);
s32 func_8015CF08(void);
s32 func_8015E380(s32);
void func_8015F9F0(Entity* entity);
void func_8015FAB8(Entity*);
Entity* func_801606BC(Entity* entity, u32 arg1, s32 arg2);

extern s16 D_801545EA[];
extern s16 D_80154604;
extern s16 D_801545A8;
extern s16 D_801545AA;
extern s16 D_801545AC;
extern s16 D_80154606;
extern s8 D_80154688;
extern s32 D_80155368[];
extern s32 D_801553BC;
extern s32 D_80155488;
extern s32 D_801554B0;
extern s32 D_801554C0;
extern s32 D_801554C8;
extern s32 D_801554D0;
extern s32 D_80155748;
extern s32 D_801558B4;
extern s32 D_801558D4;
extern s32 D_801558DC;
extern s32 D_80155528;
extern s32 D_80155670;
extern s32 D_80155750;
extern /*?*/ s32 D_8015591C;
extern /*?*/ s32 D_80155950;
extern s32 D_80174F74;
extern s32 D_80174F78;
extern u8 D_80174FAC;
extern u8 D_80174FB0;
extern u8 D_80174FB4;
extern u8 D_80174FB8;
extern u16 D_80175950;
extern u16 D_80175952;
extern u16 D_80175954;
extern s16 D_80175956;
extern s16 D_80175956;

void func_8015B348(void) {
    switch (PLAYER.unk2E) {
    case 0:
        g_CurrentEntity->unk34 |= 0x10000;
        D_80097420[0] = 4;
        func_8015C93C(0x2000);

        if (PLAYER.accelerationX == 0) {
            func_8015C920(&D_80155748);
            *D_80072F1A = 4;
            func_801606BC(g_CurrentEntity, 0x1D, 0);
            func_801606BC(g_CurrentEntity, 0x90021, 0);
            D_801545AC = 0;
            PLAYER.unk2E++;
        }
        break;

    case 1:
        PLAYER.unk19 = 2;
        D_801545AA += 64;
        PLAYER.unk1C = (rsin(D_801545AA) >> 0xA) + 256;

        if (D_801545AC != 0) {
            D_801545AC--;
            if ((D_801545AC) == 0) {
                PLAYER.unk19 = 0;
                PLAYER.unk1C = 0x100;
                func_801606BC(g_CurrentEntity, 0x17, 0);
                D_801545A8 = 0x90;
                PLAYER.unk2E++;
            }
        }
        break;

    case 2:
        D_801545A8--;
        if ((D_801545A8) == 0) {
            func_8015C920(&D_801558B4);
            PLAYER.palette = 0x814E;
            g_CurrentEntity->accelerationY = -0x10000;
            func_801606BC(g_CurrentEntity, 0x16, 0);
            D_801545A8 = 0x30;
            g_api.PlaySfx(0x6E2);
            D_80174F78 = 0xA0;
            PLAYER.unk2E++;
        }
        break;

    case 3:
        D_801545A8--;
        if ((D_801545A8) == 0) {
            PLAYER.accelerationY = 0;
            D_801545A8 = 0xC0;
            func_801606BC(g_CurrentEntity, 0x24, 0);
            func_801606BC(g_CurrentEntity, 0x20025, 0);
            func_801606BC(g_CurrentEntity, 0x30026, 0);
            func_801606BC(g_CurrentEntity, 0x40027, 0);
            PLAYER.palette = 0x813D;
            *D_80072F1A = 0;
            PLAYER.unk2E++;
        }

        if (D_80097B9C.hp < D_80097B9C.hpMax) {
            D_80097B9C.hp++;
        }

        D_80174F78--;
        if ((D_80174F78 >= 0) && (D_80174F78 == (((D_80174F78) / 20) * 0x14))) {
            g_api.PlaySfx(NA_SE_PL_RIC_UNK_6E2);
        }
        break;

    case 4:
        D_801545A8--;
        if ((D_801545A8 << 0x10) == 0) {
            D_801545A8 = 0x10;
            PLAYER.unk2E++;
        }

        if (D_80097B9C.hp < D_80097B9C.hpMax) {
            D_80097B9C.hp++;
        }

        D_80174F78--;
        if ((D_80174F78 >= 0) && (D_80174F78 == (((D_80174F78) / 20) * 0x14))) {
            g_api.PlaySfx(NA_SE_PL_RIC_UNK_6E2);
        }
        break;

    case 5:
        if (D_801545A8 == 5) {
            PLAYER.animationFrameIndex = 6;
            PLAYER.palette = 0x8120;
            func_801606BC(g_CurrentEntity, 0x1C, 0);
        }
        D_801545A8--;
        if (D_801545A8 == 0) {
            func_8015C920(&D_801558D4);
            g_api.PlaySfx(NA_SE_UNK_62F);
            func_801606BC(g_CurrentEntity, 0x1B, 0);
            PLAYER.unk2E++;
            break;
        }

        if (D_80097B9C.hp < D_80097B9C.hpMax) {
            D_80097B9C.hp++;
        }
        break;

    case 6:
        if (PLAYER.animationFrameDuration < 0) {
            func_8015C920(&D_801558DC);
            PLAYER.unk2E++;
        }
        break;

    case 7:
        if (PLAYER.animationFrameDuration < 0) {
            g_CurrentEntity->unk34 &= 0xFFFEFFFF;
            D_80097420[0] = 0;
            func_8015CF08();
            func_8015C920(&D_801558DC);
            *D_80072F1A = 4;
            func_801606BC(g_CurrentEntity, 0x90021, 0);
        }
        break;
    }
}

INCLUDE_ASM("asm/ric/nonmatchings/1F348", func_8015B898);

INCLUDE_ASM("asm/ric/nonmatchings/1F348", func_8015BB80);

INCLUDE_ASM("asm/ric/nonmatchings/1F348", func_8015BCD0);

INCLUDE_ASM("asm/ric/nonmatchings/1F348", func_8015BE84);

INCLUDE_ASM("asm/ric/nonmatchings/1F348", func_8015C178);

INCLUDE_ASM("asm/ric/nonmatchings/1F348", func_8015C2A8);

INCLUDE_ASM("asm/ric/nonmatchings/1F348", func_8015C4AC);

INCLUDE_ASM("asm/ric/nonmatchings/1F348", func_8015C6D4);

void func_8015C908(s32 step) {
    PLAYER.step = step;
    PLAYER.unk2E = 0;
}

void func_8015C920(s32* unk0) {
    g_CurrentEntity->unk4C = unk0;
    g_CurrentEntity->animationFrameDuration = 0;
    g_CurrentEntity->animationFrameIndex = 0;
}

void func_8015C93C(s32 speed) {
    if (g_CurrentEntity->accelerationX < 0) {
        g_CurrentEntity->accelerationX += speed;
        if (g_CurrentEntity->accelerationX > 0) {
            g_CurrentEntity->accelerationX = 0;
        }
    } else {
        g_CurrentEntity->accelerationX -= speed;
        if (g_CurrentEntity->accelerationX < 0)
            g_CurrentEntity->accelerationX = 0;
    }
}

void func_8015C984(s32 speed) {
    if (g_CurrentEntity->accelerationY < 0) {
        g_CurrentEntity->accelerationY += speed;
        if (g_CurrentEntity->accelerationY > 0) {
            g_CurrentEntity->accelerationY = 0;
        }
    } else {
        g_CurrentEntity->accelerationY -= speed;
        if (g_CurrentEntity->accelerationY < 0) {
            g_CurrentEntity->accelerationY = 0;
        }
    }
}

s32 func_8015C9CC(void) {
    u16* facing;

    if (D_80072F64 & 2) {
        return 0;
    }

    facing = &PLAYER.facing;
    if (*facing == 1) {
        if (D_80072EE8 & 0x2000) {
            *facing = 0;
            D_80072F6C = 1;
            return -1;
        } else if (D_80072EE8 & 0x8000) {
            return 1;
        }
    } else {
        if (!(D_80072EE8 & 0x2000)) {
            if (D_80072EE8 & 0x8000) {
                *facing = 1;
                D_80072F6C = 1;
                return -1;
            }
            return 0;
        }
        return 1;
    }
    return 0;
}

void func_8015CA84(s32 speed) {
    if (g_CurrentEntity->facing == 1)
        speed = -speed;
    g_CurrentEntity->accelerationX = speed;
}

void func_8015CAAC(s32 speed) {
    if (PLAYER.objectRoomIndex == 1)
        speed = -speed;
    PLAYER.accelerationX = speed;
}

void func_8015CAD4(s32 arg0, s16 arg1) {
    if (arg0 == 0) {
        func_801606BC(g_CurrentEntity, 0x15002C, 0);
        if (arg1 >= D_80072F1A[0]) {
            D_80072F1A[0] = arg1;
        }
    } else if (D_80072F1C[0] <= arg1) {
        D_80072F1C[0] = arg1;
    }
}

INCLUDE_ASM("asm/ric/nonmatchings/1F348", func_8015CB58);

void func_8015CC28(void) {
    Entity* entity = &g_EntityArray[UNK_ENTITY_1];

    entity->unk7E.modeU8.unk1 = 0;
    entity->unk7E.modeU8.unk0 = 0;
    entity->unk7C.U8.unk1 = 0;
    entity->unk7C.U8.unk0 = 0;
}

void func_8015CC50() { func_8015C908(0xF0); }

void func_8015CC70(s16 arg0) {
    PLAYER.unk2E = arg0;
    PLAYER.step = 0x0020;
    PLAYER.animationFrameDuration = 0;
    PLAYER.animationFrameIndex = 0;
    if (arg0 & 1) {
        PLAYER.unk4C = &D_80155950;
    } else {
        PLAYER.unk4C = &D_8015591C;
    }
}

void func_8015CCC8(s32 arg0, s32 arg1) {
    func_8015C908(2);
    func_8015C920(&D_801554C0);
    PLAYER.accelerationX = arg1;
    PLAYER.accelerationY = 0;
    if (arg0 == 1) {
        PLAYER.unk4C = &D_801554B0;
        PLAYER.unk2E = 4;
    }
    if (arg0 == 2) {
        PLAYER.unk4C = &D_801554D0;
        PLAYER.unk2E = 1;
    }
    if (arg0 == 3) {
        PLAYER.unk4C = &D_801554C8;
        PLAYER.unk2E = 4;
    }
}

void func_8015CD98(s32 accelerationX) {
    PLAYER.accelerationX = accelerationX;
    PLAYER.accelerationY = 0;
    D_80072F64 = 0;
    func_8015C908(0);
    func_8015C920(&D_801553BC);
}

void func_8015CDE0(s32 arg0) {
    if ((D_80072F10 != 0) && (D_80072F9A == 0)) {
        func_8015CE7C();
        return;
    } else {
        D_80072F02[0] = 8;
    }
    D_80072F10 = 0xC;
    D_80072F02[0] = 0xC;
    D_80072F64 = 0;
    func_8015C908(1);
    func_8015C920(&D_80155488);
    func_8015CA84(0x14000);
    PLAYER.accelerationY = 0;
}

void func_8015CE7C(void) {
    if (D_80072F9A != 0) {
        func_8015CDE0(0);
    } else {
        D_80072F64 = 0;
        func_8015C908(0x19);
        func_8015C920(&D_80155670);
        func_8015CA84(0x24000);
        D_80072F16[0] = 0x28;
        PLAYER.accelerationY = 0;
        func_801606BC(g_CurrentEntity, 0x50001, 0);
    }
}

INCLUDE_ASM("asm/ric/nonmatchings/1F348", func_8015CF08);

INCLUDE_ASM("asm/ric/nonmatchings/1F348", func_8015D020);

INCLUDE_ASM("asm/ric/nonmatchings/1F348", func_8015D120);

INCLUDE_ASM("asm/ric/nonmatchings/1F348", func_8015D1D0);

INCLUDE_ASM("asm/ric/nonmatchings/1F348", func_8015D250);

INCLUDE_ASM("asm/ric/nonmatchings/1F348", func_8015D3CC);

INCLUDE_ASM("asm/ric/nonmatchings/1F348", func_8015D678);

void func_8015D9B4() { func_8015C908(0x16); }

void func_8015D9D4(void) {
    func_8015C9CC();
    func_8015C908(0x17);
    func_8015C920(&D_80155750);
    g_CurrentEntity->accelerationY = 0;
    func_8015CA84(0x58000);
    func_8015CC28();
    func_801606BC(g_CurrentEntity, 0x19, 0);
    g_api.PlaySfx(0x707);
    D_80072F18 = 4;
}

INCLUDE_ASM("asm/ric/nonmatchings/1F348", func_8015DA60);

INCLUDE_ASM("asm/ric/nonmatchings/1F348", func_8015DB04);

INCLUDE_ASM("asm/ric/nonmatchings/1F348", func_8015DBB0);

// same as func_800E2398
INCLUDE_ASM("asm/ric/nonmatchings/1F348", func_8015E380);

void func_8015E420(s32 arg0) {
    while (PadRead(0))
        func_8015E380(arg0);
    while (PadRead(0) == 0)
        func_8015E380(arg0);
}

INCLUDE_ASM("asm/ric/nonmatchings/1F348", func_8015E484);

void func_8015E7B4(Unkstruct_8010BF64* arg0) { // !FAKE:
    s32 temp = D_80154604;

    arg0->unk14 = temp;
    arg0->unk1C = temp = D_80154606;
    arg0->unk18 = D_801545EA[8] - 1;
    arg0->unk20 = D_801545EA[0] + 1;
}

INCLUDE_ASM("asm/ric/nonmatchings/1F348", func_8015E800);

INCLUDE_ASM("asm/ric/nonmatchings/1F348", func_8015EE28);

INCLUDE_ASM("asm/ric/nonmatchings/1F348", func_8015F414);

INCLUDE_ASM("asm/ric/nonmatchings/1F348", func_8015F680);

Entity* func_8015F8F8(s16 entityIndex, s16 arg1) {
    Entity* entity = &g_EntityArray[entityIndex];
    s16 var_a0 = entityIndex;

    if (entityIndex < arg1) {
        while (var_a0 < arg1) {
            if (entity->objectId == ENTITY_UNALLOCATED) {
                return entity;
            }
            var_a0++;
            entity++;
        }
    }
    return NULL;
}

INCLUDE_ASM("asm/ric/nonmatchings/1F348", func_8015F96C);

INCLUDE_ASM("asm/ric/nonmatchings/1F348", func_8015F9F0);

// This function matches with GCC 2.7.2 using -01 Compilation flags
// https://decomp.me/scratch/VaPMV
#ifndef NON_MATCHING
INCLUDE_ASM("asm/ric/nonmatchings/1F348", func_8015FA5C);
#else
extern s32 D_80154674[];
extern s32 D_80154675[];
extern s32 D_80154676[];
extern s32 D_80154677[];

extern u8 D_80174FAC;
extern u8 D_80174FB0;
extern u8 D_80174FB4;
extern u8 D_80174FB8;

void func_8015FA5C(s32 arg0) {

    D_80174FAC = D_80154674[arg0];
    D_80174FB0 = D_80154675[arg0];
    D_80174FB4 = D_80154676[arg0];
    D_80174FB8 = D_80154677[arg0];
}
#endif

// aspsx
// https://decomp.me/scratch/bRvg6
#ifndef NON_MATCHING
INCLUDE_ASM("asm/ric/nonmatchings/1F348", func_8015FAB8);
#else
void func_8015FAB8(Entity* entity) {
    u16 var_v0;
    s32 temp;
    Unkstruct_8011A290* temp_v1 = (entity->unkB0 * 0x14) + (&D_80154688);

    if ((*D_80072F1A) != NULL) {
        var_v0 = temp_v1->sp10 * 2;
    } else {
        var_v0 = temp_v1->sp10;
    }

    entity->unk40 = var_v0;
    entity->unk42 = temp_v1->sp14;
    entity->unk3C = temp_v1->sp1C;
    temp = entity->unk40;
    entity->unk49 = temp_v1->sp17;
    entity->unk58 = temp_v1->sp18;
    entity->unk6A = temp_v1->sp1E;
    entity->objectRoomIndex = temp_v1->sp22;
    entity->unk40 = g_api.func_800FD664(temp);
    func_8015F9F0(entity);
}
#endif

INCLUDE_ASM("asm/ric/nonmatchings/1F348", func_8015FB84);

INCLUDE_ASM("asm/ric/nonmatchings/1F348", func_8015FDB0);

INCLUDE_ASM("asm/ric/nonmatchings/1F348", func_8015FEA8);

INCLUDE_ASM("asm/ric/nonmatchings/1F348", func_801601DC);

void func_801603B4(void) {}

void func_801603BC(void) {}

INCLUDE_ASM("asm/ric/nonmatchings/1F348", func_801603C4);

Entity* func_801606BC(Entity* srcEntity, u32 arg1, s32 arg2) {
    /**
     * arg2 is unused, but needed to match other functions that call
     * this function, probably part of the code for a debug build
     */
    Entity* entity = func_8015F8F8(8, 0x10);

    if (entity != NULL) {
        func_80156C60(entity);
        entity->objectId = ENTITY_BREAKABLE;
        entity->unk8C.entityPtr = srcEntity;
        entity->posX.val = srcEntity->posX.val;
        entity->posY.val = srcEntity->posY.val;
        entity->facing = srcEntity->facing;
        entity->zPriority = srcEntity->zPriority;
        entity->subId = arg1 & 0xFFF;
        entity->unkA0 = (arg1 >> 8) & 0xFF00;

        if (srcEntity->unk34 & 0x10000) {
            entity->unk34 |= 0x10000;
        }
    } else {
        return NULL;
    }
    return entity;
}

INCLUDE_ASM("asm/ric/nonmatchings/1F348", func_80160788);

// move a0,s0
#ifndef NON_MATCHING
INCLUDE_ASM("asm/ric/nonmatchings/1F348", func_80160C38);
#else
void func_80160C38(Entity* entity) {
    if (PLAYER.step == 17) {
        entity->posX.i.hi = PLAYER.posX.i.hi;
        entity->posY.i.hi = PLAYER.posY.i.hi;
        entity->facing = PLAYER.facing;
        if (entity->step == 0) {
            entity->unk34 = 0x04060000;
            entity->unk10 = 0x14;
            entity->unk12 = 0xC;
            entity->hitboxHeight = 9;
            entity->hitboxWidth = 9;
            entity->unkB0 = 0x12;
            func_8015FAB8(entity);
            entity->unk7C.s = entity->unk3C;
            entity->step++;
        }
        entity->unk3C = entity->unk7C.s;
        if (PLAYER.animationFrameIndex < 2) {
            entity->unk3C = 0;
        }
        if (PLAYER.animationFrameIndex >= 8) {
            func_80156C60(entity);
        }
    } else {
        func_80156C60(entity);
    }
}
#endif

INCLUDE_ASM("asm/ric/nonmatchings/1F348", func_80160D2C);

INCLUDE_ASM("asm/ric/nonmatchings/1F348", func_80160E4C);

INCLUDE_ASM("asm/ric/nonmatchings/1F348", func_80160F0C);

INCLUDE_ASM("asm/ric/nonmatchings/1F348", func_80160FC4);

INCLUDE_ASM("asm/ric/nonmatchings/1F348", func_8016147C);

INCLUDE_ASM("asm/ric/nonmatchings/1F348", func_80161C2C);

INCLUDE_ASM("asm/ric/nonmatchings/1F348", func_80161EF8);

INCLUDE_ASM("asm/ric/nonmatchings/1F348", func_80161FF0);

INCLUDE_ASM("asm/ric/nonmatchings/1F348", func_801623E0);

INCLUDE_ASM("asm/ric/nonmatchings/1F348", func_80162604);

INCLUDE_ASM("asm/ric/nonmatchings/1F348", func_80162870);

void func_80162C7C(void) {}

INCLUDE_ASM("asm/ric/nonmatchings/1F348", func_80162C84);

INCLUDE_ASM("asm/ric/nonmatchings/1F348", func_80162E9C);

INCLUDE_ASM("asm/ric/nonmatchings/1F348", func_80162EF8);

INCLUDE_ASM("asm/ric/nonmatchings/1F348", func_801641A0);

INCLUDE_ASM("asm/ric/nonmatchings/1F348", func_80164444);

INCLUDE_ASM("asm/ric/nonmatchings/1F348", func_80164DF8);

INCLUDE_ASM("asm/ric/nonmatchings/1F348", func_801656B0);

void func_80165DD8(POLY_GT4* poly, s32 colorIntensity, s32 y, s32 radius,
                   bool arg4) {
    s16 top = y - radius;
    s16 bottom = y + radius;
    s32 colorChannel;

    poly->y1 = top;
    poly->y0 = top;

    poly->y3 = bottom;
    poly->y2 = bottom;

    if (poly->y0 < 0) {
        poly->y1 = 0;
        poly->y0 = 0;
    }

    if (poly->y0 > 240) {
        poly->y3 = 240;
        poly->y2 = 240;
    }

    if (arg4 == 0) {
        colorChannel = colorIntensity * D_80155368[0];
        if (colorChannel < 0) {
            colorChannel += 255;
        }
        poly->r3 = (u32)colorChannel >> 8;
        poly->r1 = (u32)colorChannel >> 8;

        colorChannel = colorIntensity * D_80155368[1];
        if (colorChannel < 0) {
            colorChannel += 255;
        }
        poly->g3 = (u32)colorChannel >> 8;
        poly->g1 = (u32)colorChannel >> 8;

        colorChannel = colorIntensity * D_80155368[2];
        if (colorChannel < 0) {
            colorChannel += 255;
        }
        poly->b3 = (u32)colorChannel >> 8;
        poly->b1 = (u32)colorChannel >> 8;

        colorChannel = colorIntensity * D_80155368[3];
        if (colorChannel < 0) {
            colorChannel += 255;
        }
        poly->r2 = (u32)colorChannel >> 8;
        poly->r0 = (u32)colorChannel >> 8;

        colorChannel = colorIntensity * D_80155368[4];
        if (colorChannel < 0) {
            colorChannel += 255;
        }
        poly->g2 = (u32)colorChannel >> 8;
        poly->g0 = (u32)colorChannel >> 8;

        colorChannel = colorIntensity * D_80155368[5];
    } else {
        colorChannel = colorIntensity * D_80155368[0];
        if (colorChannel < 0) {
            colorChannel += 255;
        }
        poly->r3 = (u32)colorChannel >> 8;
        poly->r1 = (u32)colorChannel >> 8;

        colorChannel = colorIntensity * D_80155368[1];
        if (colorChannel < 0) {
            colorChannel += 255;
        }
        poly->g3 = (u32)colorChannel >> 8;
        poly->g1 = (u32)colorChannel >> 8;

        colorChannel = colorIntensity * D_80155368[2];
        if (colorChannel < 0) {
            colorChannel += 255;
        }
        poly->b3 = (u32)colorChannel >> 8;
        poly->b1 = (u32)colorChannel >> 8;

        colorChannel = colorIntensity * D_80155368[6];
        if (colorChannel < 0) {
            colorChannel += 255;
        }
        poly->r2 = (u32)colorChannel >> 8;
        poly->r0 = (u32)colorChannel >> 8;

        colorChannel = colorIntensity * D_80155368[7];
        if (colorChannel < 0) {
            colorChannel += 255;
        }
        poly->g2 = (u32)colorChannel >> 8;
        poly->g0 = (u32)colorChannel >> 8;
        colorChannel = colorIntensity * D_80155368[8];
    }
    if (colorChannel < 0) {
        colorChannel += 255;
    }
    poly->b2 = (u32)colorChannel >> 8;
    poly->b0 = (u32)colorChannel >> 8;
}

void func_80166024() {
    PLAYER.palette = 0x815E;
    PLAYER.blendMode = 0x70;
}

void func_80166044() {
    PLAYER.palette = 0x8120;
    PLAYER.blendMode = 0;
}

INCLUDE_ASM("asm/ric/nonmatchings/1F348", func_80166060);

INCLUDE_ASM("asm/ric/nonmatchings/1F348", func_80166784);

INCLUDE_ASM("asm/ric/nonmatchings/1F348", func_8016779C);

INCLUDE_ASM("asm/ric/nonmatchings/1F348", func_80167964);

void func_80167A58(void) {}

void func_80167A60(void) {}

void func_80167A68(void) {}

INCLUDE_ASM("asm/ric/nonmatchings/1F348", func_80167A70);

INCLUDE_ASM("asm/ric/nonmatchings/1F348", func_80167EC4);

INCLUDE_ASM("asm/ric/nonmatchings/1F348", func_801682B4);

INCLUDE_ASM("asm/ric/nonmatchings/1F348", func_8016840C);

INCLUDE_ASM("asm/ric/nonmatchings/1F348", func_801684D8);

INCLUDE_ASM("asm/ric/nonmatchings/1F348", func_80168A20);

INCLUDE_ASM("asm/ric/nonmatchings/1F348", func_8016902C);

INCLUDE_ASM("asm/ric/nonmatchings/1F348", func_80169470);

INCLUDE_ASM("asm/ric/nonmatchings/1F348", func_80169704);

INCLUDE_ASM("asm/ric/nonmatchings/1F348", func_80169C10);

INCLUDE_ASM("asm/ric/nonmatchings/1F348", func_80169D74);

INCLUDE_ASM("asm/ric/nonmatchings/1F348", func_80169F04);

INCLUDE_ASM("asm/ric/nonmatchings/1F348", func_8016A26C);

INCLUDE_ASM("asm/ric/nonmatchings/1F348", func_8016A974);

INCLUDE_ASM("asm/ric/nonmatchings/1F348", func_8016B0C0);

void func_8016B8E8(s32 arg0) {
    g_CurrentEntity->unk7C.s = (arg0 << 0x10 >> 0xF) - g_CurrentEntity->unk7C.s;
    if (g_CurrentEntity->unk80.modeS16.unk2 == 0) {
        g_CurrentEntity->unk80.modeS16.unk0++;
        g_CurrentEntity->unk80.modeS16.unk2++;
    }
}

void func_8016B92C(s16 arg0) {
    if (g_CurrentEntity->unk80.modeS16.unk2 == 0) {
        g_CurrentEntity->unk7C.s = (arg0 * 2) - g_CurrentEntity->unk7C.s;
        g_CurrentEntity->unk80.modeS16.unk0++;
        g_CurrentEntity->unk80.modeS16.unk2++;
    }
}

INCLUDE_ASM("asm/ric/nonmatchings/1F348", func_8016B97C);

INCLUDE_ASM("asm/ric/nonmatchings/1F348", func_8016C1BC);

s32 func_8016C6C4(Unkstruct_80128BBC* arg0, u8 value) {
    u8 ret = 0;
    s32 i;
    s32 j;
    Unkstruct_80128BBC_Sub* temp = arg0->unk04;

    for (i = 0; i < 4; i++, temp++) {
        for (j = 0; j < 3; j++) {
            temp->unk00[j] -= value;

            if (temp->unk00[j] < 16) {
                temp->unk00[j] = 16;
            } else {
                ret |= 1;
            }
        }
    }
    return ret;
}

INCLUDE_ASM("asm/ric/nonmatchings/1F348", func_8016C734);

INCLUDE_ASM("asm/ric/nonmatchings/1F348", func_8016CC74);

INCLUDE_ASM("asm/ric/nonmatchings/1F348", func_8016D328);

INCLUDE_ASM("asm/ric/nonmatchings/1F348", func_8016D4D8);

void func_8016D920(Entity* entity) {
    switch (entity->step) {
    case 0:
        entity->unk34 = 0x04000000;
        entity->unkB0 = 0x19;
        func_8015FAB8(entity);
        entity->hitboxWidth = 4;
        entity->hitboxHeight = 4;
        entity->step++;
        break;

    case 1:
        if (++entity->unk7C.s >= 4) {
            func_80156C60(entity);
        }
        break;
    }
}

INCLUDE_ASM("asm/ric/nonmatchings/1F348", func_8016D9C4);

INCLUDE_ASM("asm/ric/nonmatchings/1F348", func_8016DF74);