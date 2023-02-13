#include "ric.h"

void func_8015C920(AnimationFrame* unk0) {
    g_CurrentEntity->unk4C = unk0;
    g_CurrentEntity->animFrameDuration = 0;
    g_CurrentEntity->animFrameIdx = 0;
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

void func_8015CB58(s32 arg0, s32 arg1) {
    POLY_GT4* poly;

    FntPrint("op disable\n");
    if (arg0 != 0) {
        g_EntityArray[UNK_ENTITY_1].unk7C.S8.unk1 = 1;
        g_EntityArray[UNK_ENTITY_3].animCurFrame = 0;
        g_EntityArray[UNK_ENTITY_2].animCurFrame = 0;
        g_EntityArray[UNK_ENTITY_1].animCurFrame = 0;

        poly = &D_80086FEC[g_EntityArray[UNK_ENTITY_1].firstPolygonIndex];
        while (poly != NULL) {
            poly->x1 = 0;
            poly = (POLY_GT4*)poly->tag;
        }
    }
    g_EntityArray[UNK_ENTITY_1].unk7C.S8.unk0 = 1;
    g_EntityArray[UNK_ENTITY_1].unk7E.modeU8.unk0 = 0xA;
    if (arg1 != 0) {
        D_80072F1E = 4;
    }
}

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
    PLAYER.animFrameDuration = 0;
    PLAYER.animFrameIdx = 0;
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

INCLUDE_ASM("asm/ric/nonmatchings/20920", func_8015CF08);

INCLUDE_ASM("asm/ric/nonmatchings/20920", func_8015D020);

void func_8015D120(void) {
    func_8015C908(8);
    PLAYER.accelerationX = 0;
    func_8015CA84(0x14000);
    PLAYER.accelerationY = -0x78000;
    D_80072F20.pl_high_jump_timer = 0;
    func_8015C920(&D_8015579C);
    func_8015CC28();
    func_801606BC(g_CurrentEntity, 0x2DU, 0);
    g_api.PlaySfx(0x6FB);
    D_80072F18 = 4;
    if (D_80072F92 != 0) {
        PLAYER.accelerationY = 0;
    }
}

INCLUDE_ASM("asm/ric/nonmatchings/20920", func_8015D1D0);

INCLUDE_ASM("asm/ric/nonmatchings/20920", func_8015D250);

INCLUDE_ASM("asm/ric/nonmatchings/20920", func_8015D3CC);

INCLUDE_ASM("asm/ric/nonmatchings/20920", func_8015D678);

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

INCLUDE_ASM("asm/ric/nonmatchings/20920", func_8015DA60);

INCLUDE_ASM("asm/ric/nonmatchings/20920", func_8015DB04);

INCLUDE_ASM("asm/ric/nonmatchings/20920", func_8015DBB0);

// same as func_800E2398
INCLUDE_ASM("asm/ric/nonmatchings/20920", func_8015E380);

void func_8015E420(s32 arg0) {
    while (PadRead(0))
        func_8015E380(arg0);
    while (PadRead(0) == 0)
        func_8015E380(arg0);
}

INCLUDE_ASM("asm/ric/nonmatchings/20920", func_8015E484);

void func_8015E7B4(Unkstruct_8010BF64* arg0) { // !FAKE:
    s32 temp = D_80154604;

    arg0->unk14 = temp;
    arg0->unk1C = temp = D_80154606;
    arg0->unk18 = D_801545EA[8] - 1;
    arg0->unk20 = D_801545EA[0] + 1;
}

INCLUDE_ASM("asm/ric/nonmatchings/20920", func_8015E800);

INCLUDE_ASM("asm/ric/nonmatchings/20920", func_8015EE28);

INCLUDE_ASM("asm/ric/nonmatchings/20920", func_8015F414);

INCLUDE_ASM("asm/ric/nonmatchings/20920", func_8015F680);

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

INCLUDE_ASM("asm/ric/nonmatchings/20920", func_8015F96C);

INCLUDE_ASM("asm/ric/nonmatchings/20920", func_8015F9F0);

// This function matches with GCC 2.7.2 using -01 Compilation flags
// Matches with GCC 2.6.0 + aspsx 2.3.4
// https://decomp.me/scratch/VaPMV
#ifndef NON_MATCHING
INCLUDE_ASM("asm/ric/nonmatchings/20920", func_8015FA5C);
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
INCLUDE_ASM("asm/ric/nonmatchings/20920", func_8015FAB8);
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

INCLUDE_ASM("asm/ric/nonmatchings/20920", func_8015FB84);

INCLUDE_ASM("asm/ric/nonmatchings/20920", func_8015FDB0);

INCLUDE_ASM("asm/ric/nonmatchings/20920", func_8015FEA8);

// same as DRA/func_8011F074
void func_801601DC(Entity* entity) {
    s16 posX;
    s16 posY;

    switch (entity->step) {
    case 0:
        entity->unk34 = 0x08120000;
        entity->unk5A = 0x79;
        entity->animSet = 0xE;
        entity->zPriority = PLAYER.zPriority + 2;
        entity->palette = 0x819F;

        if (D_80174FFC & 1) {
            entity->blendMode = 0x70;
        } else {
            entity->blendMode = 0x10;
        }
        entity->unk1C = 0x40;
        entity->unk1A = 0x40;
        entity->unk4C = &D_80154924;
        D_80174FFC++;
        entity->unk6C = 0xFF;
        entity->unk19 = 0x33;
        posX = 10;
        posY = 15;
        entity->posY.i.hi = entity->posY.i.hi - posY + (rand() % 35);
        entity->posX.i.hi = entity->posX.i.hi - posX + (rand() % 20);
        entity->accelerationY = -0x6000 - (rand() & 0x3FFF);
        entity->step++;
        break;

    case 1:
        if (entity->unk6C >= 17) {
            entity->unk6C += 248;
        }
        entity->posY.val += entity->accelerationY;
        entity->unk1A += 8;
        entity->unk1C += 8;
        if (entity->animFrameDuration < 0) {
            func_80156C60(entity);
        }
        break;
    }
}

void func_801603B4(void) {}

void func_801603BC(void) {}

INCLUDE_ASM("asm/ric/nonmatchings/20920", func_801603C4);

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

INCLUDE_ASM("asm/ric/nonmatchings/20920", func_80160788);

// move a0,s0
#ifndef NON_MATCHING
INCLUDE_ASM("asm/ric/nonmatchings/20920", func_80160C38);
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
        if (PLAYER.animFrameIdx < 2) {
            entity->unk3C = 0;
        }
        if (PLAYER.animFrameIdx >= 8) {
            func_80156C60(entity);
        }
    } else {
        func_80156C60(entity);
    }
}
#endif

INCLUDE_ASM("asm/ric/nonmatchings/20920", func_80160D2C);

INCLUDE_ASM("asm/ric/nonmatchings/20920", func_80160E4C);

INCLUDE_ASM("asm/ric/nonmatchings/20920", func_80160F0C);

INCLUDE_ASM("asm/ric/nonmatchings/20920", func_80160FC4);

INCLUDE_ASM("asm/ric/nonmatchings/20920", func_8016147C);

INCLUDE_ASM("asm/ric/nonmatchings/20920", func_80161C2C);

INCLUDE_ASM("asm/ric/nonmatchings/20920", func_80161EF8);

INCLUDE_ASM("asm/ric/nonmatchings/20920", func_80161FF0);

void func_801623E0(Entity* entity) {
    POLY_GT4* poly;
    s16 firstPolygonIndex;

    entity->posX.val = g_EntityArray->posX.val;
    entity->posY.val = PLAYER.posY.val;
    switch (entity->step) {
    case 0:
        firstPolygonIndex = g_api.AllocPolygons(4, 1);
        entity->firstPolygonIndex = firstPolygonIndex;
        if (firstPolygonIndex == -1) {
            func_80156C60(entity);
            return;
        }
        entity->unk7E.modeU16 = 32;
        entity->unk7C.s = 32;
        poly = &D_80086FEC[entity->firstPolygonIndex];
        poly->u2 = 64;
        poly->u0 = 64;
        poly->v1 = 192;
        poly->v0 = 192;
        poly->u3 = 127;
        poly->u1 = 127;
        poly->v3 = 255;
        poly->v2 = 255;
        poly->tpage = 0x1A;
        poly->clut = 0x13E;
        poly->pad2 = PLAYER.zPriority + 8;
        poly->pad3 = 0;
        entity->unk34 = 0x04850000;
        entity->step++;
        break;

    case 1:
        entity->unk7C.s++;
        entity->unk7E.modeU16++;
        if (entity->unk7C.s >= 45) {
            func_80156C60(entity);
            return;
        }
        break;
    }

    poly = &D_80086FEC[entity->firstPolygonIndex];
    poly->x0 = entity->posX.i.hi - entity->unk7C.s;
    poly->y0 = entity->posY.i.hi - entity->unk7E.modeU16;
    poly->x1 = entity->posX.i.hi + entity->unk7C.s;
    poly->y1 = entity->posY.i.hi - entity->unk7E.modeU16;
    poly->x2 = entity->posX.i.hi - entity->unk7C.s;
    poly->y2 = entity->posY.i.hi + entity->unk7E.modeU16;
    poly->x3 = entity->posX.i.hi + entity->unk7C.s;
    poly->y3 = entity->posY.i.hi + entity->unk7E.modeU16;
    poly->clut = (*(s16*)&g_blinkTimer & 1) + 0x13E;
}

/**
 * This function matches with GCC 2.6.0 + ASPSX 2.3.4
 * Aspatch jumps to the wrong instruction
 */
#ifndef NON_MATCHING
INCLUDE_ASM("asm/ric/nonmatchings/20920", func_80162604);
#else
void func_80162604(Entity* entity) {
    POLY_GT4* poly;
    s16 firstPolygonIndex;

    entity->posX.val = g_EntityArray->posX.val;
    entity->posY.val = PLAYER.posY.val;
    switch (entity->step) {
    case 0:
        firstPolygonIndex = g_api.AllocPolygons(4, 1);
        entity->firstPolygonIndex = firstPolygonIndex;
        if (firstPolygonIndex != (-1)) {
            entity->unk7E.modeU16 = 0;
            entity->unk7C.s = 0;
            poly = &D_80086FEC[entity->firstPolygonIndex];
            poly->v1 = 192;
            poly->v0 = 192;
            poly->u3 = 63;
            poly->u1 = 63;
            poly->v3 = 255;
            poly->v2 = 255;
            poly->tpage = 0x1A;
            poly->u2 = 0;
            poly->u0 = 0;
            poly->clut = 0x162;
            poly->pad2 = PLAYER.zPriority - 4;
            poly->pad3 = 0;
            entity->unk34 = 0x04850000;
            entity->step++;
            goto def;
        } else {
            func_80156C60(entity);
            break;
        }

    case 1:
        entity->unk7C.s += 8;
        entity->unk7E.modeU16 += 8;
        if (entity->unk7C.s < 0x20) {
            goto def;
        }

    case 2:
        entity->step++;
        goto def;

    case 3:
        entity->unk7C.s -= 8;
        entity->unk7E.modeU16 -= 8;
        if (entity->unk7C.s >= 5) {
            goto def;
        } else {

            func_80156C60(entity);
        }
        break;

    def:
    default:
        poly = &D_80086FEC[entity->firstPolygonIndex];
        poly->x0 = entity->posX.i.hi - entity->unk7C.s;
        poly->y0 = entity->posY.i.hi - entity->unk7E.modeU16;
        poly->x1 = entity->posX.i.hi + entity->unk7C.s;
        poly->y1 = entity->posY.i.hi - entity->unk7E.modeU16;
        poly->x2 = entity->posX.i.hi - entity->unk7C.s;
        poly->y2 = entity->posY.i.hi + entity->unk7E.modeU16;
        poly->x3 = entity->posX.i.hi + entity->unk7C.s;
        poly->y3 = entity->posY.i.hi + entity->unk7E.modeU16;
        break;
    }
}
#endif

INCLUDE_ASM("asm/ric/nonmatchings/20920", func_80162870);

void func_80162C7C(void) {}

/**
 * TODO:
 * Aspatch jumps to the wrong instruction
 * This function matches with GCC 2.6.0 + ASPSX 2.3.4,
 * It also has a jumptable which makes it impossible for it
 * to be included in a NON_MATCHING state.
 * CAUTION: rodata yet to be confirmed matching
 */
#ifndef NON_MATCHING
INCLUDE_ASM("asm/ric/nonmatchings/20920", func_80162C84);
#else
extern s32 D_80154ED4;
extern s32 D_80154EF8;

void func_80162C84(Entity* entity) {
    switch (entity->step) {
    case 0:
        entity->unk34 = 0x0C110000;
        entity->facing = 1;
        entity->unk5A = 0x66;
        entity->zPriority = PLAYER.zPriority - 8;
        entity->palette = 0x8149;
        entity->animSet = -0x7FED;
        func_8015C920(&D_80154ED4);
        entity->accelerationX = -0x1C000;
        entity->posY.i.hi = 0xBB;
        entity->posX.i.hi = 0x148;
        entity->unk7E.modeU16 = 0;
        entity->step++;
        break;

    case 1:
        if (*(s32*)&entity->animFrameIdx == 0x10000) {
            g_api.PlaySfx(0x882);
        }
        if (*(s32*)&entity->animFrameIdx == 0x10004) {
            g_api.PlaySfx(0x883);
        }

        entity->posX.val += entity->accelerationX;
        if (((s16)entity->unk7E.modeU16 == 0) && (entity->posX.i.hi < 256)) {
            g_api.PlaySfx(0x87D);
            entity->unk7E.modeU16++;
        }
        if (entity->posX.i.hi < 0xE0) {
            func_8015C920(&D_80154EF8);
            entity->accelerationX = 0;
            entity->step++;
            func_801606BC(entity, 0x40000, 0);
            return;
        }
    case 2:
        if (entity->animFrameIdx == 16) {
            g_api.PlaySfx(0x87E);
            entity->unk7C.s = 0x80;
            entity->step++;
        }
        break;

    case 3:
        entity->unk7C.s--;
        if ((entity->unk7C.s) == 0) {
            func_801606BC(entity, 0x1E, 0);
            entity->step++;
        }
        break;

    case 4:

    default:
        return;
    }
}
#endif

// same as DRA/func_8011BD48
bool func_80162E9C(Entity* entity) {
    s32 i = 0x10;
    s16 objId = entity->objectId;
    s16 subId = entity->subId;
    Entity* e = &g_EntityArray[i];
    for (; i < 0x40; i++, e++) {
        if (objId == (s32)e->objectId && subId == (s32)e->subId &&
            e != entity) {
            return true;
        }
    }

    return false;
}

INCLUDE_ASM("asm/ric/nonmatchings/20920", func_80162EF8);

void func_801641A0(Entity* entity) {
    POLY_GT4* poly;
    s16 firstPolygonIndex;

    entity->posX.i.hi = PLAYER.posX.i.hi;
    entity->posY.i.hi = PLAYER.posY.i.hi - 8;
    switch (entity->step) {
    case 0:
        firstPolygonIndex = g_api.AllocPolygons(4, 1);
        entity->firstPolygonIndex = firstPolygonIndex;
        if (firstPolygonIndex != -1) {
            entity->unk7C.s = 16;
            entity->unk7E.modeU16 = 12;
            poly = &D_80086FEC[entity->firstPolygonIndex];
            poly->u2 = 64;
            poly->u0 = 64;
            poly->v1 = 192;
            poly->v0 = 192;
            poly->u3 = 127;
            poly->u1 = 127;
            poly->v3 = 255;
            poly->v2 = 255;
            poly->b3 = 128;
            poly->g3 = 128;
            poly->r3 = 128;
            poly->b2 = 128;
            poly->g2 = 128;
            poly->r2 = 128;
            poly->b1 = 128;
            poly->g1 = 128;
            poly->r1 = 128;
            poly->b0 = 128;
            poly->g0 = 128;
            poly->r0 = 128;
            poly->tpage = 0x1A;
            poly->clut = 0x160;
            poly->pad2 = PLAYER.zPriority + 8;
            poly->pad3 = 0x35;
            entity->unk34 = 0x04840000;
            entity->step++;
            goto def;
        } else {
            func_80156C60(entity);
            break;
        }

    case 1:
        entity->unk7C.s += 2;
        entity->unk7E.modeU16 += 2;
        if (entity->unk7C.s >= 57) {
            func_80156C60(entity);
            break;
        }

    default:
    def:
        poly = &D_80086FEC[entity->firstPolygonIndex];
        poly->x0 = entity->posX.i.hi - entity->unk7C.s;
        poly->y0 = entity->posY.i.hi - entity->unk7E.modeU16;
        poly->x1 = entity->posX.i.hi + entity->unk7C.s;
        poly->y1 = entity->posY.i.hi - entity->unk7E.modeU16;
        poly->x2 = entity->posX.i.hi - entity->unk7C.s;
        poly->y2 = entity->posY.i.hi + entity->unk7E.modeU16;
        poly->x3 = entity->posX.i.hi + entity->unk7C.s;
        poly->y3 = entity->posY.i.hi + entity->unk7E.modeU16;
        if (poly->b3 >= 12) {
            poly->b3 += 244;
        }
        poly->r0 = poly->g0 = poly->b0 = poly->r1 = poly->g1 = poly->b1 =
            poly->r2 = poly->g2 = poly->b2 = poly->r3 = poly->g3 = poly->b3;
    }
}

INCLUDE_ASM("asm/ric/nonmatchings/20920", func_80164444);

INCLUDE_ASM("asm/ric/nonmatchings/20920", func_80164DF8);

INCLUDE_ASM("asm/ric/nonmatchings/20920", func_801656B0);

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

INCLUDE_ASM("asm/ric/nonmatchings/20920", func_80166060);

INCLUDE_ASM("asm/ric/nonmatchings/20920", func_80166784);

void func_8016779C(Entity* entity) {
    if (D_80072F66 == 0) {
        func_80156C60(entity);
        return;
    }

    entity->facing = PLAYER.facing;
    if (entity->step == 0) {
        entity->unk34 = 0x04070000;
        entity->animSet = -0x7FEE;
        entity->unk5A = 0x46;
        entity->palette = 0x8120;
        entity->zPriority = PLAYER.zPriority + 2;
    }

    if (PLAYER.step == 2) {
        if (PLAYER.facing != 0) {
            entity->animCurFrame = D_80155CCC[D_80175080];
        } else {
            entity->animCurFrame = D_80155CB8[D_80175080];
        }
    } else if (PLAYER.step == 0) {
        if (PLAYER.facing != 0) {
            entity->animCurFrame = D_80155CF4[D_80175080];
        } else {
            entity->animCurFrame = D_80155CE0[D_80175080];
        }
    } else if (PLAYER.facing != 0) {
        entity->animCurFrame = D_80155D1C[D_80175080];
    } else {
        entity->animCurFrame = D_80155D08[D_80175080];
    }

    entity->posX.val = g_EntityArray->posX.val;
    entity->posY.val = PLAYER.posY.val;
}

/**
 * TODO: !FAKE
 * Needs to be refactored
 */
void func_80167964(Entity* entity) {
    /**
     * 0x5E was originally 0xBC in mips2c output
     * suggesting the size of the Entity struct
     */
    if (D_80072F66 != 0) {
        if (entity->step == 0) {
            entity->unk34 = 0x04070000;
        }
        if (!(entity->subId & 0xFF00)) {
            *(&PLAYER.palette +
              (*(&D_80155D30 + (entity->animFrameDuration)) * 0x5E)) = 0x8140;
        }
        *(&PLAYER.unkA4 +
          (*(&D_80155D30 + (entity->animFrameDuration)) * 0x5E)) = 4;
        entity->animFrameDuration++;
        if (entity->animFrameDuration == 0xF) {
            func_80156C60(entity);
        }
    } else {
        func_80156C60(entity);
    }
}

void func_80167A58(void) {}

void func_80167A60(void) {}

void func_80167A68(void) {}

INCLUDE_ASM("asm/ric/nonmatchings/20920", func_80167A70);

INCLUDE_ASM("asm/ric/nonmatchings/20920", func_80167EC4);

INCLUDE_ASM("asm/ric/nonmatchings/20920", func_801682B4);

s32 func_8016840C(s16 x, s16 y) {
    CollisionResult sp10;
    u16 temp;

    if (g_CurrentEntity->accelerationX != 0) {
        g_api.CheckCollision(g_CurrentEntity->posX.i.hi + y,
                             g_CurrentEntity->posY.i.hi + x, &sp10, 0);
        if (g_CurrentEntity->accelerationX > 0) {
            temp = sp10.unk14;
        } else {
            temp = sp10.unk1C;
        }
        if (!(sp10.unk0 & 2)) {
            return 0;
        }
    } else {
        return 0;
    }
    g_CurrentEntity->posX.i.lo = 0;
    g_CurrentEntity->posX.i.hi += temp;
    return 2;
}

INCLUDE_ASM("asm/ric/nonmatchings/20920", func_801684D8);

INCLUDE_ASM("asm/ric/nonmatchings/20920", func_80168A20);

INCLUDE_ASM("asm/ric/nonmatchings/20920", func_8016902C);

INCLUDE_ASM("asm/ric/nonmatchings/20920", func_80169470);

INCLUDE_ASM("asm/ric/nonmatchings/20920", func_80169704);

void func_80169C10(Entity* entity) {
    POLY_GT4* poly;
    s16 firstPolygonIndex;
    s32 PosX = 8;
    s32 PosY = 4;

    switch (entity->step) {
    case 0:
        firstPolygonIndex = g_api.AllocPolygons(4, 1);
        entity->firstPolygonIndex = firstPolygonIndex;
        if (firstPolygonIndex != -1) {
            entity->unk34 = 0x08800000;
            entity->accelerationY = 0x8000;
            entity->posX.i.hi =
                ((u16)entity->posX.i.hi - PosX) + (rand() & 0xF);
            entity->posY.i.hi =
                ((u16)entity->posY.i.hi - PosY) + (rand() & 0xF);
            poly = &D_80086FEC[entity->firstPolygonIndex];
            poly->clut = 0x1B0;
            poly->tpage = 0x1A;
            poly->b0 = 0;
            poly->b1 = 0;
            poly->pad2 = entity->zPriority;
            poly->pad2 = poly->pad2 + 4;
            poly->pad3 = 0x31;
            func_8015FDB0(poly, entity->posX.i.hi, entity->posY.i.hi);
            entity->step++;
        } else {
            func_80156C60(entity);
        }
        break;

    default:
        entity->posY.val += entity->accelerationY;
        poly = &D_80086FEC[entity->firstPolygonIndex];
        if (func_8015FDB0(poly, entity->posX.i.hi, entity->posY.i.hi) != 0) {
            func_80156C60(entity);
        }
        break;
    }
}

void func_80169D74(Entity* entity) {
    Multi temp;
    s16* ptr;

    switch (entity->step) {
    case 0:
        entity->unk34 = 0x0C000000;
        entity->unk84.unk = entity->unk8C.entityPtr->unk84.unk;
        entity->animSet = -0x7FEF;
        entity->animCurFrame = D_80155E68[entity->subId];
        entity->unk5A = 0x66;
        entity->palette = 0x81B0;
        entity->blendMode = 0x10;
        entity->facing = PLAYER.facing;
        entity->zPriority = PLAYER.zPriority;
        entity->unk19 = 4;
        entity->unk1E = 0xC00;
        entity->step++;
        break;

    case 1:
        entity->unk1E -= 0x80;
        if (entity->unk8C.entityPtr->step == 7) {
            entity->step++;
            entity->unk7C.s = (entity->subId + 1) * 4;
        }
        break;

    case 2:
        entity->unk1E -= 0x80;
        entity->unk7C.s--;
        if (entity->unk7C.s == 0) {
            func_80156C60(entity);
            return;
        }
        break;
    }
    temp = entity->unk84;
    ptr = temp.unk + ((u16)entity->unk80.modeS16.unk0 * 4);
    entity->posX.i.hi = ptr[0] - D_8007308E;
    entity->posY.i.hi = ptr[1] - D_80073092;
    entity->unk80.modeS16.unk0 = (entity->unk80.modeS16.unk0 + 1) & 0x3F;
}

INCLUDE_ASM("asm/ric/nonmatchings/20920", func_80169F04);

INCLUDE_ASM("asm/ric/nonmatchings/20920", func_8016A26C);

INCLUDE_ASM("asm/ric/nonmatchings/20920", func_8016A974);

INCLUDE_ASM("asm/ric/nonmatchings/20920", func_8016B0C0);

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

INCLUDE_ASM("asm/ric/nonmatchings/20920", func_8016B97C);

INCLUDE_ASM("asm/ric/nonmatchings/20920", func_8016C1BC);

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

INCLUDE_ASM("asm/ric/nonmatchings/20920", func_8016C734);

INCLUDE_ASM("asm/ric/nonmatchings/20920", func_8016CC74);

void func_8016D328(Entity* entity) {
    s16 firstPolygonIndex;
    s32 acceleration;

    switch (entity->step) {
    case 0:
        firstPolygonIndex = g_api.AllocPolygons(4, 1);
        entity->firstPolygonIndex = firstPolygonIndex;
        if (firstPolygonIndex != -1) {
            entity->unk34 = 0x08800000;
            entity->posX.val = entity->unk8C.entityPtr->unk84.unk;
            entity->posY.val = entity->unk8C.entityPtr->unk88.unk;
            entity->facing = entity->unk8C.entityPtr->unk8C.modeU16.unk0;
            entity->unkB0 = 0x18;
            func_8015FAB8(entity);
            entity->unk5A = 0x79;
            entity->animSet = 0xE;
            entity->palette = 0x819E;
            entity->unk4C = &D_80155EA8;
            entity->blendMode = 0x30;
            entity->unk19 = 8;
            entity->unk6C = 0x60;
            entity->hitboxWidth = 8;
            entity->hitboxHeight = 8;
            entity->unk34 |= 0x100000;
            acceleration = (rand() % 512) + 0x300;
            entity->accelerationX = rcos(acceleration) * 32;
            entity->accelerationY = -(rsin(acceleration) * 32);
            entity->step++;
            break;
        } else {
            func_80156C60(entity);
            break;
        }

    case 1:
        if (++entity->unk7C.s >= 0x27) {
            func_80156C60(entity);
            break;
        } else {
            entity->posX.val += entity->accelerationX;
            entity->posY.val += entity->accelerationY;
        }
    }
}

INCLUDE_ASM("asm/ric/nonmatchings/20920", func_8016D4D8);

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

INCLUDE_ASM("asm/ric/nonmatchings/20920", func_8016D9C4);

INCLUDE_ASM("asm/ric/nonmatchings/20920", func_8016DF74);