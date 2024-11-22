// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sword.h"
#include <items.h>

static void ServantInit(InitializeMode mode);
static void UpdateServantDefault(Entity* self);
static void func_us_801746BC(Entity* self);
static void func_us_80174B6C(Entity* self);
static void func_us_801758C8(Entity* self);
static void func_us_80176270(Entity* self);
static void func_us_80176664(Entity* self);
static void func_us_8017666C(Entity* self);
static void func_us_80176674(Entity* self);
static void func_us_80176BF0(Entity* self);
static void func_us_80176BF8(Entity* self);
static void func_us_80176F28(Entity* self);
static void func_us_801773CC(Entity* self);
static void UpdateServantSfxPassthrough(Entity* self);
static void func_us_80177480(Entity* self);
static void func_us_80177590(Entity* self);

ServantDesc sword_ServantDesc = {
    ServantInit,      UpdateServantDefault,
    func_us_801746BC, func_us_80174B6C,
    func_us_801758C8, func_us_80176270,
    func_us_80176664, func_us_8017666C,
    func_us_80176674, func_us_80176BF0,
    func_us_80176BF8, func_us_80176F28,
    func_us_801773CC, UpdateServantSfxPassthrough,
    func_us_80177480, func_us_80177590,
};

static s32 D_us_801782B0;
static s32 D_us_801782B4;
static s32 D_us_801782B8;
static s32 D_us_801782BC;
static s32 D_us_801782C0;
static s32 D_us_801782C4;

extern Entity D_800736C8;
extern Entity D_80073784[];

void func_us_80172420(Entity* self, s32 entityId) {
    Entity* entity;
    s32 i;

    if (self == NULL) {
        self = &D_800736C8;
    }

    for (i = 0; i < 3; i++) {
        entity = D_80073784 + i;
        if (entity->entityId == entityId + SWORD_UNK_DA) {
            return;
        }

        if (!entity->entityId) {
            break;
        }
    }

    if (!entity->entityId) {
        DestroyEntity(entity);
        entity->entityId = entityId + SWORD_UNK_DA;
        entity->zPriority = self->zPriority;
        entity->facingLeft = self->facingLeft;
        entity->flags = FLAG_KEEP_ALIVE_OFFCAMERA;
        entity->posX.val = self->posX.val;
        entity->posY.val = self->posY.val;
        entity->ext.factory.parent = self;
    }
}

void func_us_801724E8(Entity* self, s32 arg1, u32 params) {
    Entity* entity;

    if (entity = g_api.GetFreeEntity(UNK_ENTITY_11, 0x2F)) {

        DestroyEntity(entity);

        if (arg1 == 0) {
            entity->entityId = SWORD_UNK_DE;
        } else {
            entity->entityId = SWORD_UNK_DF;
        }

        entity->zPriority = self->zPriority;
        entity->facingLeft = self->facingLeft;
        entity->flags = FLAG_KEEP_ALIVE_OFFCAMERA;
        entity->posX.val = self->posX.val;
        entity->posY.val = self->posY.val;
        entity->ext.factory.parent = self;
        entity->params = params;
    }
}

#define UNK_SWORD_PRIM_COUNT 96

extern s16 D_us_80170594[72];
extern s16 D_us_801708F4[72];
extern s16 D_us_801710E4[UNK_SWORD_PRIM_COUNT];
extern s16 D_us_80171564[UNK_SWORD_PRIM_COUNT];
extern s32 D_us_801786D4[UNK_SWORD_PRIM_COUNT * 4];
extern s32 D_us_80178854[UNK_SWORD_PRIM_COUNT * 4];
extern s32 D_us_801789D4[UNK_SWORD_PRIM_COUNT * 4];

typedef struct {
    s16 a, b, c, d;
} UnkQuad;

extern UnkQuad D_us_80170354[];
extern UnkQuad D_us_80170DE4[];

void func_us_8017259C(Entity* arg0, s32 arg1, s32 arg2) {
    Primitive* prim;
    s32 i;
    s16* uvCoords;

    prim = &g_PrimBuf[arg0->primIndex];

    if (!arg1) {
        if (arg2) {
            uvCoords = D_us_801708F4;
        } else {
            uvCoords = D_us_80170594;
        }

        for (i = 0; i < LEN(D_us_80170594); i++) {
            prim->u0 = *uvCoords++;
            prim->v0 = *uvCoords++;

            prim->u1 = *uvCoords++;
            prim->v1 = *uvCoords++;

            prim->u2 = prim->u3 = *uvCoords++;
            prim->v2 = prim->v3 = *uvCoords++;

            prim->clut = 0x140;
            prim->drawMode = DRAW_UNK_100 | DRAW_HIDE | DRAW_UNK02;
            prim = prim->next;

            D_us_801786D4[i] = SP(0x20 + D_us_80170354[i].a * 8);
            D_us_80178854[i] = SP(0x20 + D_us_80170354[i].b * 8);
            D_us_801789D4[i] = SP(0x20 + D_us_80170354[i].c * 8);
        }

        for (; i < UNK_SWORD_PRIM_COUNT; i++) {
            prim->drawMode |= DRAW_HIDE;
            prim = prim->next;
        }
    } else {
        if (arg2) {
            uvCoords = D_us_80171564;
        } else {
            uvCoords = D_us_801710E4;
        }

        for (i = 0; i < LEN(D_us_801710E4); i++) {
            prim->u0 = *uvCoords++;
            prim->v0 = *uvCoords++;

            prim->u1 = *uvCoords++;
            prim->v1 = *uvCoords++;

            prim->u2 = prim->u3 = *uvCoords++;
            prim->v2 = prim->v3 = *uvCoords++;

            prim->clut = 0x140;
            prim->drawMode = DRAW_UNK_100 | DRAW_HIDE | DRAW_UNK02;
            prim = prim->next;

            D_us_801786D4[i] = SP(0x20 + D_us_80170DE4[i].a * 8);
            D_us_80178854[i] = SP(0x20 + D_us_80170DE4[i].b * 8);
            D_us_801789D4[i] = SP(0x20 + D_us_80170DE4[i].c * 8);
        }
    }
}

void func_us_8017280C(Entity* self, s32 arg1, s32 arg2) {
    Primitive* prim;
    s32 i;

    prim = &g_PrimBuf[self->primIndex];
    if (!arg1) {
        for (i = 0; i < arg2; i++) {
            prim->tpage = 0x1B;
            prim->clut = 0x140;
            prim->u0 = prim->u2 = 0x30;
            prim->u1 = prim->u3 = 0x5F;
            prim->v0 = prim->v1 = 0;
            prim->v2 = prim->v3 = 0x70;
            prim->drawMode = DRAW_UNK_100 | DRAW_HIDE;
            prim = prim->next;
        }
    } else {
        for (i = 0; i < arg2; i++) {
            prim->tpage = 0x1B;
            prim->clut = 0x140;
            prim->u0 = prim->u2 = 0x60;
            prim->u1 = prim->u3 = 0x8F;
            prim->v0 = prim->v1 = 0;
            prim->v2 = prim->v3 = 0x70;
            prim->drawMode = DRAW_UNK_100 | DRAW_HIDE;
            prim = prim->next;
        }
    }
    for (; i < UNK_SWORD_PRIM_COUNT; i++) {
        prim->drawMode |= DRAW_HIDE;
        prim = prim->next;
    }
}

extern s16 D_us_801700A4[];
extern s32 s_SwordCurrentLevel;
extern s32 D_us_80178B74;
extern s32 D_us_80178B80;
extern FamiliarStats s_SwordStats;

void func_us_80172940(Entity* self) {
    Primitive* prim;
    s32 i;

    if (self->ext.swordFamiliar.unk7c == 0) {
        if ((self->entityId == SWORD_UNK_D1) ||
            (self->entityId == SWORD_UNK_D8)) {
            self->primIndex =
                g_api.AllocPrimitives(PRIM_GT4, UNK_SWORD_PRIM_COUNT);
            if (self->primIndex == -1) {
                DestroyEntity(self);
                return;
            }
            self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA |
                          FLAG_HAS_PRIMS | FLAG_UNK_20000;
            prim = &g_PrimBuf[self->primIndex];
            for (i = 0; i < UNK_SWORD_PRIM_COUNT; i++) {
                prim->tpage = 0x1B;
                prim->clut = 0x140;
                prim->drawMode = DRAW_UNK_100 | DRAW_HIDE;
                prim = prim->next;
            }
            g_api.GetServantStats(self, 0, 0, &s_SwordStats);
            self->ext.swordFamiliar.unk80 =
                D_us_801700A4[(s_SwordStats.level / 10) * 6];
            self->ext.swordFamiliar.unk82 = 1;
            func_us_8017259C(self, self->ext.swordFamiliar.unk80, 1);
            self->ext.swordFamiliar.unk86 = self->ext.swordFamiliar.unk88 =
                0x400;
            self->ext.swordFamiliar.unk8c = self->ext.swordFamiliar.unk8e = 0;
            s_SwordCurrentLevel = 0;
            D_us_80178B74 = 1;
            self->step++;
        }
    } else {
        switch (self->entityId) {
        case SWORD_UNK_D1:
            self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA |
                          FLAG_HAS_PRIMS | FLAG_UNK_20000;
            self->step++;
            break;

        case SWORD_UNK_D2:
        case SWORD_UNK_D3:
            self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA |
                          FLAG_HAS_PRIMS | FLAG_UNK_20000;
            self->ext.swordFamiliar.posX =
                (g_Tilemap.left << 8) + g_Tilemap.scrollX.i.hi;
            self->ext.swordFamiliar.posY =
                (g_Tilemap.top << 8) + g_Tilemap.scrollY.i.hi;
            self->step++;
            break;

        case SWORD_UNK_D4:
        case SWORD_UNK_D5:
            self->flags =
                FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_HAS_PRIMS | FLAG_UNK_20000;
            self->step++;
            break;
        }
    }

    D_us_80178B80 = 0;
    self->ext.swordFamiliar.unk7c = self->entityId;
}

// chooses the largest magnitude of arg0, arg1, arg2
//
// see: Min3
static s32 Max3(s32 arg0, s32 arg1, s32 arg2) {
    arg0 = abs(arg0);
    arg1 = abs(arg1);
    arg2 = abs(arg2);

    if (arg0 >= arg1 && arg0 >= arg2) {
        return arg0;
    }

    if (arg1 >= arg0 && arg1 >= arg2) {
        return arg1;
    }

    if (arg2 >= arg0 && arg2 >= arg1) {
        return arg2;
    }
}

// chooses the smallest magnitude of arg0, arg1, arg2
//
// this function is unused.
//
// see: Max3
static s32 Min3(s32 arg0, s32 arg1, s32 arg2) {
    arg0 = abs(arg0);
    arg1 = abs(arg1);
    arg2 = abs(arg2);

    if (arg0 <= arg1 && arg0 <= arg2) {
        return arg0;
    }

    if (arg1 <= arg0 && arg1 <= arg2) {
        return arg1;
    }

    if (arg2 <= arg0 && arg2 <= arg1) {
        return arg2;
    }
}

typedef struct {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
    s16 unk8;
    s16 unkA;
    s16 unkC;
    s16 unkE;
    s16 unk10;
} UnkC8C;

void func_us_80172C8C(UnkC8C* arg0, UnkC8C* arg1) {
    D_us_801782B0 = rsin(arg0->unk0);
    D_us_801782B4 = rsin(arg0->unk2);
    D_us_801782B8 = rsin(arg0->unk4);
    D_us_801782BC = rcos(arg0->unk0);
    D_us_801782C0 = rcos(arg0->unk2);
    D_us_801782C4 = rcos(arg0->unk4);

    arg1->unk0 = (D_us_801782C4 * D_us_801782C0) >> 0xC;
    arg1->unk2 =
        ((-D_us_801782B8 * D_us_801782BC) >> 0xC) +
        ((D_us_801782B0 * ((D_us_801782C4 * D_us_801782B4) >> 0xC)) >> 0xC);
    arg1->unk4 =
        ((D_us_801782B8 * D_us_801782B0) >> 0xC) +
        ((D_us_801782BC * ((D_us_801782C4 * D_us_801782B4) >> 0xC)) >> 0xC);
    arg1->unk6 = (D_us_801782B8 * D_us_801782C0) >> 0xC;
    arg1->unk8 =
        ((D_us_801782C4 * D_us_801782BC) >> 0xC) +
        ((D_us_801782B0 * ((D_us_801782B8 * D_us_801782B4) >> 0xC)) >> 0xC);
    arg1->unkA =
        ((-D_us_801782C4 * D_us_801782B0) >> 0xC) +
        ((D_us_801782BC * ((D_us_801782B8 * D_us_801782B4) >> 0xC)) >> 0xC);
    arg1->unkC = -D_us_801782B4 >> 0xC;
    arg1->unkE = (D_us_801782C0 * D_us_801782B0) >> 0xC;
    arg1->unk10 = (D_us_801782C0 * D_us_801782BC) >> 0xC;
}

INCLUDE_ASM("servant/tt_004/nonmatchings/sword", func_us_80172E84);

extern s32 D_us_80178344[128];
extern s32 D_us_80178B88;

Entity* func_us_80173AA0(Entity* self) {
    Entity* entity;
    s32 i;
    s32 entityIndex;
    s32 hitFlag;

    hitFlag = 0;
    entity = &g_Entities[STAGE_ENTITY_START];

    for (i = 0; i < LEN(D_us_80178344); i++, entity++) {
        D_us_80178344[i] = 0;
        if (entity->entityId && entity->hitboxState != 0 &&
            !(entity->flags & FLAG_UNK_00200000) &&
            LOH(entity->posX.i.hi) >= -16 && entity->posX.i.hi <= 272 &&
            LOH(entity->posY.i.hi) <= 240 && entity->posY.i.hi >= 0 &&
            entity->hitPoints < 0x7000) {
            if (entity->flags & FLAG_UNK_80000) {
                hitFlag++;
                D_us_80178344[i] = 1;
            } else {
                entity->flags |= FLAG_UNK_80000;
                return entity;
            }
        }
    }

    if (hitFlag != 0) {
        entityIndex = D_us_80178B88 % 128;

        for (i = 0; i < LEN(D_us_80178344); i++) {
            if (D_us_80178344[entityIndex] != 0) {
                entity = &g_Entities[STAGE_ENTITY_START + entityIndex];
                D_us_80178B88 = (entityIndex + 1) % 128;
                return entity;
            }

            entityIndex = (entityIndex + 1) % 128;
        }
    }

    return NULL;
}

#include "../check_entity_valid.h"

extern s32 D_us_801700A8[];

void func_us_80173CB8(Entity* self) {
    if (self->step) {
        g_api.GetServantStats(self, 0, 0, &s_SwordStats);
        if (s_SwordCurrentLevel != s_SwordStats.level) {
            s_SwordCurrentLevel = s_SwordStats.level;
            if (D_us_801700A8[(s_SwordStats.level / 10) * 3] & 1) {
                if (SearchForEntityInRange(0, SWORD_UNK_DA) == NULL) {
                    func_us_80172420(self, 0);
                }
            }
            if ((D_us_801700A8[(s_SwordStats.level / 10) * 3] & 2) &&
                SearchForEntityInRange(0, SWORD_UNK_DB) == NULL) {
                func_us_80172420(self, 1);
            }

            if (s_SwordStats.level == 50 && !g_CastleFlags[CASTLE_FLAG_464]) {
                g_api.AddToInventory(ITEM_SWORD_FAMILIAR, EQUIP_HAND);
                g_CastleFlags[CASTLE_FLAG_464] = true;
            }
        }
    }
}

INCLUDE_ASM("servant/tt_004/nonmatchings/sword", ServantInit);

INCLUDE_ASM("servant/tt_004/nonmatchings/sword", UpdateServantDefault);

INCLUDE_ASM("servant/tt_004/nonmatchings/sword", func_us_801746BC);

INCLUDE_ASM("servant/tt_004/nonmatchings/sword", func_us_80174B6C);

INCLUDE_ASM("servant/tt_004/nonmatchings/sword", func_us_801758C8);

INCLUDE_ASM("servant/tt_004/nonmatchings/sword", func_us_80176270);

void func_us_80176664(Entity* self) {}

void func_us_8017666C(Entity* self) {}

INCLUDE_ASM("servant/tt_004/nonmatchings/sword", func_us_80176674);

void func_us_80176BF0(Entity* self) {}

INCLUDE_ASM("servant/tt_004/nonmatchings/sword", func_us_80176BF8);

INCLUDE_ASM("servant/tt_004/nonmatchings/sword", func_us_80176F28);

extern s32 D_us_80178B80;
extern s32 D_us_80178B84;

void func_us_801773CC(Entity* self) {
    Entity* entity;

    switch (self->params) {
    case 0:
        D_us_80178B80 = 1;
        entity = SearchForEntityInRange(0, SWORD_UNK_DD);
        if (entity > 0 && entity->step < 5) {
            entity->step = 8;
        }
        break;

    case 15:
        D_us_80178B84 = 1;
        break;
    }

    DestroyEntity(self);
}

void UpdateServantSfxPassthrough(Entity* self) { ProcessSfxState(self); }

extern s32 D_us_801700A0[];
extern s32 D_us_801786C0[];
extern s32 D_us_801786C4[];

void func_us_80177480(Entity* self) {
    s32 flag;
    s32 spellId;

    switch (self->step) {
    case 0:
        self->flags =
            FLAG_POS_CAMERA_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_UNK_20000;
        flag = D_us_801700A0[(s_SwordStats.level / 10) * 3];
        if (flag) {
            spellId = FAM_ABILITY_SWORD_UNK20;
        } else {
            spellId = FAM_ABILITY_SWORD_UNK19;
        }

        g_api.GetServantStats(self, spellId, 1, &s_SwordStats);

        self->hitboxWidth = 4;
        self->hitboxHeight = 4;

        if (!self->params) {
            self->posX.i.hi = D_us_801786C0[0] & 0xFFFF;
            self->posY.i.hi = (D_us_801786C0[0] >> 16) & 0xFFFF;
        } else {
            self->posX.i.hi = D_us_801786C4[0] & 0xFFFF;
            self->posY.i.hi = (D_us_801786C4[0] >> 16) & 0xFFFF;
        }

        self->step++;
        break;

    case 1:
        DestroyEntity(self);
        break;
    }
}

void func_us_80177590(Entity* self) {
    switch (self->step) {
    case 0:
        self->flags = FLAG_KEEP_ALIVE_OFFCAMERA;
        g_api.GetServantStats(self, 7, 1, &s_SwordStats);
        self->step++;
        break;

    case 1:
        if (++self->ext.swordFamiliar.unk7c > 8) {
            DestroyEntity(self);
        }
        break;
    }
}
