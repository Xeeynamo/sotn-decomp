// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sword.h"
#include <items.h>
#include <sfx.h>

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
    .Init = ServantInit,
    .Update = UpdateServantDefault,
    func_us_801746BC, // active target below level 70
    func_us_80174B6C, // active target above level 70
    func_us_801758C8,
    func_us_80176270,
    func_us_80176664,
    func_us_8017666C,
    func_us_80176674,
    func_us_80176BF0,
    func_us_80176BF8,
    func_us_80176F28,
    func_us_801773CC,
    UpdateServantSfxPassthrough,
    func_us_80177480,
    func_us_80177590,
};

static s32 D_us_801782B0;
static s32 D_us_801782B4;
static s32 D_us_801782B8;
static s32 D_us_801782BC;
static s32 D_us_801782C0;
static s32 D_us_801782C4;
static s32 D_us_801782C8;
static s32 D_us_801782CC;
static s32 D_us_801782D0;
// static VECTOR D_us_801782D4;
static s32 D_us_801782D4;
static s32 D_us_801782D8;
static s32 D_us_801782DC;
STATIC_PAD_BSS(4);
// end static VECTOR D_us_801782D4;
static MATRIX D_us_801782E4;
static MATRIX D_us_80178304;
static MATRIX D_us_80178324;
static s32 D_us_80178344[128];
STATIC_PAD_BSS(4);
static s32 D_us_80178548; // x
static s32 D_us_8017854C; // y
static s32 D_us_80178550; // x (ps)
static s32 D_us_80178554; // y (ps)
static s32 D_us_80178558; // z (ps)
static s32 D_us_8017855C;
static s32 D_us_80178560; // distance
static s32 D_us_80178564;
static s32 D_us_80178568; // x (ps)
static s32 D_us_8017856C;
static s32 D_us_80178570;
static s32 D_us_80178574;
static s32 D_us_80178578;
static s32 D_us_8017857C;
static s32 D_us_80178580; // x (ps)
static s32 D_us_80178584; // y (ps)
static s32 D_us_80178588; // z (ps)
static s32 D_us_8017858C; // x (ps)
static s32 D_us_80178590; // y (ps)
static s32 D_us_80178594; // z (ps)
static s32 D_us_80178598;
static s32 D_us_8017859C; // x (ps)
static s32 D_us_801785A0; // y (ps)
static s32 D_us_801785A4; // z (ps)
static s32 D_us_801785A8; // x (ps)
static s32 D_us_801785AC; // y (ps)
static s32 D_us_801785B0; // distance (ps)
static s32 D_us_801785B4;
static s32 D_us_801785B8; // x (ps)
static s32 D_us_801785BC; // y (ps)
static s32 D_us_801785C0; // z (ps)
static s32 D_us_801785C4; // x (ps)
static s32 D_us_801785C8; // y (ps)
static s32 D_us_801785CC; // x (ps)
static s32 D_us_801785D0;
static s32 D_us_801785D4;
static s32 D_us_801785D8;
static s32 D_us_801785DC;
static s32 D_us_801785E0; // distance
static s32 D_us_801785E4;
static s32 D_us_801785E8;
static s32 D_us_801785EC; // x (ps)
static s32 D_us_801785F0; // y (ps)
static s32 D_us_801785F4; // z (ps)
static s32 D_us_801785F8;
static s32 D_us_801785FC;
static s32 D_us_80178600;
static s32 D_us_80178604;
static s32 D_us_80178608;
static s32 D_us_8017860C;
static s32 D_us_80178610;
static s32 D_us_80178614; // distance (ps)
STATIC_PAD_BSS(4);
static s32 D_us_8017861C; // x
static s32 D_us_80178620; // y
static s32 D_us_80178624; // x
static s32 D_us_80178628; // y
static s32 D_us_8017862C; // z
static s32 D_us_80178630;
static s32 D_us_80178634;
static s32 D_us_80178638; // (ps)
static Primitive* D_us_8017863C;
STATIC_PAD_BSS(4);
static s32 D_us_80178644;
static s32 D_us_80178648;
static FamiliarStats s_SwordStats;
static s32 s_SwordCurrentLevel;
static s32 D_us_8017865C[1];
static s32 D_us_80178660[3]; // should be part of the preceeding array
static u32 D_us_8017866C;
extern s32 D_us_80178670[4][5];
extern Point16 D_us_801786C0[5];
extern s32 D_us_801786D4[96];
extern s32 D_us_80178854[96];
extern s32 D_us_801789D4[96];
extern MATRIX D_us_80178B54;
extern s32 D_us_80178B74;
extern s32 D_us_80178B78;
extern s32 D_us_80178B7C;
extern s32 D_us_80178B80;
extern s32 D_us_80178B84;
extern s32 D_us_80178B88;

// sets up familiar entity id "state" during initialization
// and level change
void func_us_80172420(Entity* self, s32 entityId) {
    Entity* entity;
    s32 i;

    if (self == NULL) {
        self = &g_Entities[UNK_ENTITY_4];
    }

    for (i = 0; i < 3; i++) {
        entity = &g_Entities[UNK_ENTITY_5 + i];
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

extern s16 D_us_80170594[];
extern s16 D_us_801708F4[];
extern s16 D_us_801710E4[UNK_SWORD_PRIM_COUNT];
extern s16 D_us_80171564[UNK_SWORD_PRIM_COUNT];

extern SVECTOR D_us_80170354[];
extern SVECTOR D_us_80170DE4[];

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

        for (i = 0; i < 72; i++) {
            prim->u0 = *uvCoords++;
            prim->v0 = *uvCoords++;

            prim->u1 = *uvCoords++;
            prim->v1 = *uvCoords++;

            prim->u2 = prim->u3 = *uvCoords++;
            prim->v2 = prim->v3 = *uvCoords++;

            prim->clut = 0x140;
            prim->drawMode = DRAW_UNK_100 | DRAW_HIDE | DRAW_UNK02;
            prim = prim->next;

            D_us_801786D4[i] = SP(0x20 + D_us_80170354[i].vx * 8);
            D_us_80178854[i] = SP(0x20 + D_us_80170354[i].vy * 8);
            D_us_801789D4[i] = SP(0x20 + D_us_80170354[i].vz * 8);
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

            D_us_801786D4[i] = SP(32 + D_us_80170DE4[i].vx * 8);
            D_us_80178854[i] = SP(32 + D_us_80170DE4[i].vy * 8);
            D_us_801789D4[i] = SP(32 + D_us_80170DE4[i].vz * 8);
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

extern SwordUnk_A0 D_us_801700A0[];

void func_us_80172940(Entity* self) {
    Primitive* prim;
    s32 i;

    if (self->ext.swordFamiliar.unk7c == 0) {
        if ((self->entityId == SWORD_DEFAULT) ||
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
                D_us_801700A0[(s_SwordStats.level / 10)].unk4;
            self->ext.swordFamiliar.unk82 = 1;
            func_us_8017259C(self, self->ext.swordFamiliar.unk80, 1);
            self->ext.swordFamiliar.unk86 = self->ext.swordFamiliar.unk88 =
                FLT(1.0 / 4.0);
            self->ext.swordFamiliar.unk8c = self->ext.swordFamiliar.targetX = 0;
            s_SwordCurrentLevel = 0;
            D_us_80178B74 = 1;
            self->step++;
        }
    } else {
        switch (self->entityId) {
        case SWORD_DEFAULT:
            self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA |
                          FLAG_HAS_PRIMS | FLAG_UNK_20000;
            self->step++;
            break;

        case SWORD_CIRCLE_ATTACK:
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
// see: Max3
static s32 Min3(s32 arg0, s32 arg1, s32 arg2) UNUSED {
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

void func_us_80172C8C(MATRIX* arg0, MATRIX* arg1) {
    D_us_801782B0 = rsin(arg0->m[0][0]);
    D_us_801782B4 = rsin(arg0->m[0][1]);
    D_us_801782B8 = rsin(arg0->m[0][2]);
    D_us_801782BC = rcos(arg0->m[0][0]);
    D_us_801782C0 = rcos(arg0->m[0][1]);
    D_us_801782C4 = rcos(arg0->m[0][2]);

    arg1->m[0][0] = FLT_TO_I(D_us_801782C4 * D_us_801782C0);
    arg1->m[0][1] =
        FLT_TO_I(-D_us_801782B8 * D_us_801782BC) +
        FLT_TO_I(D_us_801782B0 * FLT_TO_I(D_us_801782C4 * D_us_801782B4));
    arg1->m[0][2] =
        FLT_TO_I(D_us_801782B8 * D_us_801782B0) +
        FLT_TO_I(D_us_801782BC * FLT_TO_I(D_us_801782C4 * D_us_801782B4));
    arg1->m[1][0] = FLT_TO_I(D_us_801782B8 * D_us_801782C0);
    arg1->m[1][1] =
        FLT_TO_I(D_us_801782C4 * D_us_801782BC) +
        FLT_TO_I(D_us_801782B0 * FLT_TO_I(D_us_801782B8 * D_us_801782B4));
    arg1->m[1][2] =
        FLT_TO_I(-D_us_801782C4 * D_us_801782B0) +
        FLT_TO_I(D_us_801782BC * FLT_TO_I(D_us_801782B8 * D_us_801782B4));
    arg1->m[2][0] = FLT_TO_I(-D_us_801782B4);
    arg1->m[2][1] = FLT_TO_I(D_us_801782C0 * D_us_801782B0);
    arg1->m[2][2] = FLT_TO_I(D_us_801782C0 * D_us_801782BC);
}

void func_us_80172E84(Entity*, s32);
INCLUDE_ASM("servant/tt_004/nonmatchings/sword", func_us_80172E84);

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

void CheckSwordLevel(Entity* self) {
    if (self->step) {
        g_api.GetServantStats(self, 0, 0, &s_SwordStats);
        if (s_SwordCurrentLevel != s_SwordStats.level) {
            s_SwordCurrentLevel = s_SwordStats.level;
            if (D_us_801700A0[(s_SwordStats.level / 10)].unk8 & 1) {
                if (SearchForEntityInRange(0, SWORD_UNK_DA) == NULL) {
                    func_us_80172420(self, 0);
                }
            }
            // reserved for level 90
            if ((D_us_801700A0[(s_SwordStats.level / 10)].unk8 & 2) &&
                SearchForEntityInRange(0, SWORD_UNK_DB) == NULL) {
                func_us_80172420(self, 1);
            }

            if (s_SwordStats.level == 50 && !g_CastleFlags[SWORD_FAMILIAR]) {
                g_api.AddToInventory(ITEM_SWORD_FAMILIAR, EQUIP_HAND);
                g_CastleFlags[SWORD_FAMILIAR] = 1;
            }
        }
    }
}

#define CLUT_INDEX_SERVANT_2 0x410
extern u16 g_ServantClut[16];
extern u16 g_SwordClut[32];
extern VECTOR g_TransferVector;
extern SVECTOR g_RotationAngle;

extern VECTOR D_us_80170080;

#ifdef VERSION_PSP
extern u16 D_91F8618[];
extern u16 D_psp_092F1138[];
#endif

void ServantInit(InitializeMode mode) {
    Entity* self;
    s32 i;
    s32 j;
    u16* dst;
    u16* src;
    s32 posX;
    RECT rect;

    if (mode == MENU_SWITCH_SERVANT || mode == MENU_SAME_SERVANT) {
        ProcessEvent(NULL, true);
        if (mode == MENU_SAME_SERVANT) {
            return;
        }
    }

    self = &g_Entities[UNK_ENTITY_4];

    dst = &g_Clut[1][CLUT_INDEX_SERVANT];
    src = g_ServantClut;

#ifdef VERSION_PSP
    for (j = 1; i < LEN(g_SwordClut); j++) {
        g_SwordClut[j] |= 0x8000;
    }
#endif

    for (i = 0; i < LEN(g_ServantClut); i++) {
        *dst++ = *src++;
    }

    dst = &g_Clut[1][CLUT_INDEX_SERVANT_2];
    src = g_SwordClut;

    for (i = 0; i < LEN(g_SwordClut); i++) {
        *dst++ = *src++;
    }

    rect.x = 0;
    rect.y = 0xF4;
    rect.w = 0x30;
    rect.h = 1;

    dst = &g_Clut[1][CLUT_INDEX_SERVANT];
    LoadImage(&rect, (u_long*)dst);
    DestroyEntity(self);

    self->zPriority = PLAYER.zPriority - 2;
    self->facingLeft = (PLAYER.facingLeft + 1) & 1;

    if (mode == MENU_SWITCH_SERVANT) {
#ifdef VERSION_PSP
        if ((D_8003C708.flags & FLAG_UNK_20) ||
            (D_8003C708.flags & FLAG_UNK_40)) {
#else
        if ((LOW(D_8003C708.flags) & (FLAG_UNK_40 | FLAG_UNK_20)) != 0) {
#endif
            self->entityId = SWORD_DEFAULT;
            if (g_CastleFlags[SWORD_FAMILIAR] == 1 ||
                g_CastleFlags[SWORD_FAMILIAR] == 2) {
                g_CastleFlags[SWORD_FAMILIAR] = 4;
            }
        } else {
            self->entityId = SWORD_UNK_D8;
        }
        self->posX.val = FIX(128);
        self->posY.val = -FIX(32);
    } else {
        self->entityId = SWORD_DEFAULT;
        if (D_8003C708.flags & FLAG_UNK_20) {
            if (ServantUnk0()) {
                self->posX.val = FIX(192);
            } else {
                self->posX.val = FIX(64);
            }
            self->posY.val = FIX(144);
        } else {
#ifdef VERSION_PSP
            if (PLAYER.facingLeft) {
                posX = FIX(28);
            } else {
                posX = -FIX(28);
            }
            self->posX.val = PLAYER.posX.val + posX;
            self->posY.val = PLAYER.posY.val - FIX(28);
#else
            posX = PLAYER.posX.val;
            if (PLAYER.facingLeft) {
                self->posX.val = posX + FIX(28);
            } else {
                self->posX.val = posX - FIX(28);
            }
            self->posY.val = PLAYER.posY.val - FIX(28);
#endif
        }
    }

    D_us_80170080.vx = (self->posX.i.hi - 128) << 5;
    D_us_80170080.vy = (self->posY.i.hi - 128) << 5;
    D_us_80170080.vz = 0;

    g_api.GetServantStats(self, 0, 0, &s_SwordStats);
    if (D_us_801700A0[(s_SwordStats.level / 10)].unk8 & 1) {
        func_us_80172420(self, 0);
    }
    if (D_us_801700A0[(s_SwordStats.level / 10)].unk8 & 2) {
        func_us_80172420(self, 1);
    }

    RotMatrix(&g_RotationAngle, &D_us_80178B54);
    TransMatrix(&D_us_80178B54, &g_TransferVector);

    D_us_80178B80 = 0;
    D_us_80178B84 = 0;
    D_us_80178B7C = 0;
    D_us_80178B78 = 0;
}

extern s16 D_us_80170078[];
extern Point16 D_us_8017007C;

void UpdateServantDefault(Entity* self) {
    Entity* follow;
    s32 currentX;

    CheckSwordLevel(self);

    // first time we've reached level 90
    if (g_CastleFlags[SWORD_FAMILIAR] == 1) {
        self->entityId = SWORD_UNK_D5;
        self->step = 0;
        g_CastleFlags[SWORD_FAMILIAR] = 2;
        return;
    }

    if (g_Player.unk70) {
        self->entityId = SWORD_UNK_D4;
        self->step = 0;
        return;
    }

    D_us_80178564 += 16;
    D_us_80178564 &= 0xFFF;

    if (D_8003C708.flags & FLAG_UNK_20) {
        switch (ServantUnk0()) {
        case 0:
            D_us_80178548 = FIX(0x40);
            break;
        case 1:
            D_us_80178548 = FIX(0xC0);
            break;
        case 2:
            D_us_80178548 = self->posX.i.hi > 128 ? FIX(0xC0) : FIX(0x40);
            break;
        }
        D_us_8017854C = (FLT_TO_FIX(rcos(D_us_80178564)) * 16) + FIX(0x90);
    } else {
        D_us_80178550 = PLAYER.facingLeft ? FIX(0x1C) : -FIX(0x1C);
        D_us_80178554 = FIX(0x1C);
        D_us_80178548 = PLAYER.posX.val + D_us_80178550;
        D_us_8017854C =
            PLAYER.posY.val -
            ((FLT_TO_FIX(rcos(D_us_80178564)) * 16) + D_us_80178554);
    }

    switch (self->step) {
    case 0:
        func_us_80172940(self);
        D_us_80178564 = 0;
        break;

    case 1:

        D_us_80178550 = FIX_TO_I(D_us_80178548 - self->posX.val);
        D_us_80178554 = FIX_TO_I(D_us_8017854C - self->posY.val);

        D_us_80178560 = FLT_TO_I(
            SquareRoot12(I_TO_FLT(SQ(D_us_80178550) + SQ(D_us_80178554))));

        if (D_us_80178560 < 16) {
            self->velocityX = (D_us_80178548 - self->posX.val) >> 6;
            self->velocityY = (D_us_8017854C - self->posY.val) >> 6;
        } else if (D_us_80178560 < 64) {
            self->velocityX = (D_us_80178548 - self->posX.val) >> 5;
            self->velocityY = (D_us_8017854C - self->posY.val) >> 5;
        } else if (D_us_80178560 < 256) {
            self->velocityX = (D_us_80178548 - self->posX.val) >> 4;
            self->velocityY = (D_us_8017854C - self->posY.val) >> 4;
        } else {
            self->velocityX = (D_us_80178548 - self->posX.val) >> 2;
            self->velocityY = (D_us_8017854C - self->posY.val) >> 2;
        }

        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;

        if (D_us_80178560 > 16) {
            self->ext.swordFamiliar.unk84 =
                ratan2(D_us_80178554, D_us_80178550) & 0xFFF;
            self->ext.swordFamiliar.unk86 = GetTargetPositionWithDistanceBuffer(
                self->ext.swordFamiliar.unk84, self->ext.swordFamiliar.unk88,
                8);
        } else {
            self->ext.swordFamiliar.unk86 = GetTargetPositionWithDistanceBuffer(
                FLT(1.0 / 4.0), self->ext.swordFamiliar.unk88, 8);
        }

        self->ext.swordFamiliar.unk88 = self->ext.swordFamiliar.unk86;
        D_us_8017007C.x = self->ext.swordFamiliar.unk86 - FLT(1.0 / 4.0);

        D_us_80178558 = -D_us_80170080.vz;
        D_us_80178550 = abs(D_us_80178550) << 5;
        D_us_80178554 = abs(D_us_80178554) << 5;

        D_us_8017855C = MAX(D_us_80178550, D_us_80178554);
        self->ext.swordFamiliar.currentX =
            ratan2(D_us_80178558, D_us_8017855C) & 0xFFF;

        self->ext.swordFamiliar.unk8c = GetTargetPositionWithDistanceBuffer(
            self->ext.swordFamiliar.currentX, self->ext.swordFamiliar.targetX,
            32);
        self->ext.swordFamiliar.targetX = self->ext.swordFamiliar.unk8c;

        D_us_80170080.vz +=
            FLT_TO_I(rsin(self->ext.swordFamiliar.unk8c) * 0x60);
        D_us_80170078[0] = self->ext.swordFamiliar.unk8c;

        if (!g_CutsceneHasControl) {
            if ((self->ext.swordFamiliar.follow = func_us_80173AA0(self)) !=
                NULL) {
                // level 70 and higher
                if (!D_us_801700A0[(s_SwordStats.level / 10)].unk0) {
                    self->entityId = SWORD_CIRCLE_ATTACK;
                } else {
                    self->entityId = SWORD_UNK_D3;
                }
                self->step = 0;
            }
        }
        break;
    }

    ProcessEvent(self, false);
    D_us_80170080.vx = (self->posX.i.hi - 128) << 5;
    D_us_80170080.vy = (self->posY.i.hi - 128) << 5;
    func_us_80172E84(self, self->ext.swordFamiliar.unk80);
}

extern s16 D_us_80170090[];
extern s32 D_us_80170218;

// only called when the sword has a target
void func_us_801746BC(Entity* self) {
    s32 roll;
    s16* sfxId;

    CheckSwordLevel(self);

    if (g_Player.unk70) {
        self->entityId = SWORD_UNK_D4;
        self->step = 0;
        return;
    }

    D_us_80170080.vx = (self->posX.i.hi - 128) << 5;
    D_us_80170080.vy = (self->posY.i.hi - 128) << 5;
    self->ext.swordFamiliar.posX =
        (g_Tilemap.left << 8) + g_Tilemap.scrollX.i.hi;
    self->ext.swordFamiliar.posY =
        (g_Tilemap.top << 8) + g_Tilemap.scrollY.i.hi;

    switch (self->step) {
    case 0:
        func_us_80172940(self);
        break;

    case 1:
        self->ext.swordFamiliar.unk98 = 1;

        D_us_80178578 = (rand() % 128) + 64 + self->ext.swordFamiliar.posX;
        D_us_8017857C = (rand() % 128) + 64 + self->ext.swordFamiliar.posY;

        self->step++;
        break;

    case 2:
        D_us_80178570 =
            (D_us_80178578 - self->ext.swordFamiliar.posX) - self->posX.i.hi;
        D_us_80178574 =
            (D_us_8017857C - self->ext.swordFamiliar.posY) - self->posY.i.hi;
        self->ext.swordFamiliar.unk84 =
            ratan2(D_us_80178574, D_us_80178570) & 0xFFF;
        self->ext.swordFamiliar.unk86 = GetTargetPositionWithDistanceBuffer(
            self->ext.swordFamiliar.unk84, self->ext.swordFamiliar.unk88, 32);
        self->ext.swordFamiliar.unk88 = self->ext.swordFamiliar.unk86;

        if (self->ext.swordFamiliar.unk84 == self->ext.swordFamiliar.unk86) {
            self->step++;
        }

        D_us_8017007C.x = self->ext.swordFamiliar.unk86 - FLT(1.0 / 4.0);
        break;

    case 3:
        self->velocityX =
            (I_TO_FIX(D_us_80178578 - self->ext.swordFamiliar.posX) -
             self->posX.val) >>
            4;
        self->velocityY =
            (I_TO_FIX(D_us_8017857C - self->ext.swordFamiliar.posY) -
             self->posY.val) >>
            4;
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;

        if (CalculateDistance(
                self, D_us_80178578 - self->ext.swordFamiliar.posX,
                D_us_8017857C - self->ext.swordFamiliar.posY) < 2) {
            D_us_8017856C = 0;
            D_us_80178568 = D_us_8017007C.x & 0xFFF;
            self->step++;
        }
        break;

    case 4:
        D_us_8017856C++;
        if (D_us_80170218 < D_us_8017856C) {
            g_api.PlaySfx(SFX_NOISE_SWEEP_DOWN_A);
            self->step++;
        }
        break;

    case 5:
    case 6:
        D_us_8017007C.x += 128;
        D_us_8017007C.x &= 0xFFF;

        if (D_us_8017007C.x == D_us_80178568) {
            D_us_8017856C = 0;
            self->step++;
        }
        break;

    case 7:
        D_us_8017856C++;
        if (D_us_80170218 < D_us_8017856C) {
            self->step++;
        }
        break;

    case 8:
        if (CheckEntityValid(self->ext.swordFamiliar.follow) == 0 &&
            (self->ext.swordFamiliar.follow = func_us_80173AA0(self)) == 0) {
            self->entityId = SWORD_DEFAULT;
            self->step = 0;
            break;
        } else if (g_CutsceneHasControl) {
            self->entityId = SWORD_DEFAULT;
            self->step = 0;
            break;
        }

        self->step = 1;

        break;
    }

    ProcessEvent(self, false);
    D_us_80170080.vx = (self->posX.i.hi - 128) << 5;
    D_us_80170080.vy = (self->posY.i.hi - 128) << 5;
    func_us_80172E84(self, self->ext.swordFamiliar.unk80);

    if (self->step > 4 && self->step < 7) {
        if (self->ext.swordFamiliar.unk98) {
            if ((roll = rand() % 16) < 2) {
                g_api.PlaySfx(D_us_80170090[roll ? 0 : 1]);
            }
            self->ext.swordFamiliar.unk98 = 0;
        }
        func_us_801724E8(self, 0, false);
        func_us_801724E8(self, 0, true);
    }
}

extern s32 D_us_8017021C;
extern s32 D_us_80170220;

#ifdef VERSION_PSP
extern s32 D_psp_092F2000;
#else
#define D_psp_092F2000 FLT(-1.0 / 4.0);
#endif

void func_us_80174B6C(Entity* self) {
    s32 roll;
    s32 currentX;

    CheckSwordLevel(self);
    if (g_Player.unk70) {
        self->entityId = SWORD_UNK_D4;
        self->step = 0;
        return;
    }

    D_us_80170080.vx = (self->posX.i.hi - 0x80) << 5;
    D_us_80170080.vy = (self->posY.i.hi - 0x80) << 5;
    // This is weird… why swap operands between game versions?
#ifdef VERSION_PSP
    self->ext.swordFamiliar.posX =
        g_Tilemap.scrollX.i.hi + (g_Tilemap.left << 8);
    self->ext.swordFamiliar.posY =
        g_Tilemap.scrollY.i.hi + (g_Tilemap.top << 8);
#else
    self->ext.swordFamiliar.posX =
        (g_Tilemap.left << 8) + g_Tilemap.scrollX.i.hi;
    self->ext.swordFamiliar.posY =
        (g_Tilemap.top << 8) + g_Tilemap.scrollY.i.hi;
#endif
    D_us_801785A8 = (self->ext.swordFamiliar.posX - 0x80) << 5;
    D_us_801785AC = (self->ext.swordFamiliar.posY - 0x80) << 5;

    switch (self->step) {
    case 0:
        func_us_80172940(self);
        D_us_8017859C = (rand() & PSP_RANDMASK) - FLT(4);
        D_us_801785A4 = (rand() & PSP_RANDMASK) - FLT(4);
        break;

    case 1:
        D_us_80178580 = PLAYER.facingLeft ? FLT(1.0 / 2.0) : FLT(-1.0 / 2.0);
        D_us_80178584 = FLT(-1.0 / 4.0);
        D_us_80178588 = FLT(-1.0 / 4.0);
        D_us_80178580 += D_us_801785A8;
        D_us_80178584 = D_us_801785AC + D_psp_092F2000;
        self->step++;

        // fallthrough
    case 2:

        D_us_8017858C = D_us_80178580 - D_us_801785A8 - D_us_80170080.vx;
        D_us_80178590 = D_us_80178584 - D_us_801785AC - D_us_80170080.vy;
        D_us_80178594 = D_us_80178588 - D_us_80170080.vz;

        self->ext.swordFamiliar.unk84 =
            ratan2(D_us_80178590, D_us_8017858C) & 0xFFF;
        self->ext.swordFamiliar.unk86 = GetTargetPositionWithDistanceBuffer(
            self->ext.swordFamiliar.unk84, self->ext.swordFamiliar.unk88, 0x80);
        self->ext.swordFamiliar.unk88 = self->ext.swordFamiliar.unk86;

        D_us_8017859C =
            FLT_TO_I(rcos(self->ext.swordFamiliar.unk86) * FLT(5.0 / 128.0));
        D_us_801785A0 =
            FLT_TO_I(rsin(self->ext.swordFamiliar.unk86) * FLT(5.0 / 128.0));

        D_us_80170078[2] = self->ext.swordFamiliar.unk86 - FLT(1.0 / 4.0);
        D_us_8017858C = abs(D_us_8017858C);
        D_us_80178590 = abs(D_us_80178590);

        D_us_80178598 = MAX(D_us_8017858C, D_us_80178590);

        self->ext.swordFamiliar.currentX =
            ratan2(D_us_80178594, D_us_80178598) & 0xFFF;
        self->ext.swordFamiliar.unk8c = GetTargetPositionWithDistanceBuffer(
            self->ext.swordFamiliar.currentX, self->ext.swordFamiliar.targetX,
            0x40);

        self->ext.swordFamiliar.targetX = self->ext.swordFamiliar.unk8c;
        D_us_801785A4 = FLT_TO_I(rsin(self->ext.swordFamiliar.unk8c) * 0xA0);
        D_us_80170078[0] = self->ext.swordFamiliar.unk8c;

        D_us_80170080.vx += D_us_8017859C;
        D_us_80170080.vy += D_us_801785A0;
        D_us_80170080.vz += D_us_801785A4;
        D_us_8017858C = D_us_80178580 - D_us_801785A8 - D_us_80170080.vx;
        D_us_80178590 = D_us_80178584 - D_us_801785AC - D_us_80170080.vy;
        D_us_80178594 = D_us_80178588 - D_us_80170080.vz;

        D_us_801785B0 = SquareRoot0(
            SQ(D_us_8017858C) + SQ(D_us_80178590) + SQ(D_us_80178594));

        if (D_us_801785B0 < FLT(1.0 / 8.0)) {
            self->step++;
        }
        break;

    case 3:
        D_us_8017859C = (D_us_80178580 - D_us_801785A8 - D_us_80170080.vx) >> 4;
        D_us_801785A0 = (D_us_80178584 - D_us_801785AC - D_us_80170080.vy) >> 4;
        D_us_801785A4 = (D_us_80178588 - D_us_80170080.vz) >> 4;

        D_us_80170080.vx += D_us_8017859C;
        D_us_80170080.vy += D_us_801785A0;
        D_us_80170080.vz += D_us_801785A4;

        self->ext.swordFamiliar.unk86 = GetTargetPositionWithDistanceBuffer(
            FLT(1.0 / 4.0), self->ext.swordFamiliar.unk88, 32);
        self->ext.swordFamiliar.unk88 = self->ext.swordFamiliar.unk86;
        D_us_80170078[2] = self->ext.swordFamiliar.unk86 - FLT(1.0 / 4.0);

        self->ext.swordFamiliar.unk8c = GetTargetPositionWithDistanceBuffer(
            FLT(0), self->ext.swordFamiliar.targetX, 32);

        self->ext.swordFamiliar.targetX = self->ext.swordFamiliar.unk8c;
        D_us_80170078[0] = self->ext.swordFamiliar.unk8c;

        if ((self->ext.swordFamiliar.unk86 == FLT(1.0 / 4.0)) &&
            (self->ext.swordFamiliar.unk8c == 0)) {
            D_us_801785B4 = 0;
            self->step++;
        }
        break;

    case 4:
        D_us_801785B4++;
        if (D_us_801785B4 > D_us_8017021C) {
            self->step++;
        }
        break;
    case 5:
        if (!CheckEntityValid(self->ext.swordFamiliar.follow)) {
            if ((self->ext.swordFamiliar.follow = func_us_80173AA0(self)) ==
                NULL) {
                self->entityId = SWORD_DEFAULT;
                self->step = 0;
                break;
            }
        }
        if (g_CutsceneHasControl) {
            self->entityId = SWORD_DEFAULT;
            self->step = 0;
            break;
        }

        D_us_80178580 = D_us_8017859C >= 0 ? FLT(1.0 / 2.0) : FLT(-1.0 / 2.0);
        D_us_80178584 = FLT(-1.0 / 2.0);
        D_us_80178588 = D_us_801785A4 >= 0 ? FLT(1.0 / 2.0) : FLT(-1.0 / 2.0);
        D_us_80178580 += D_us_801785A8;
#ifdef VERSION_PSP
        D_us_80178584 = D_us_801785AC + D_psp_092F2000;
#else
        D_us_80178584 = D_us_801785AC - FLT(1.0 / 2.0);
#endif
        g_api.PlaySfx(SFX_BOSS_WING_FLAP);
        self->step++;
        // fallthrough

    case 6:
        D_us_8017858C = D_us_80178580 - D_us_801785A8 - D_us_80170080.vx;
        D_us_80178590 = D_us_80178584 - D_us_801785AC - D_us_80170080.vy;
        D_us_80178594 = D_us_80178588 - D_us_80170080.vz;

        self->ext.swordFamiliar.unk84 =
            ratan2(D_us_80178590, D_us_8017858C) & 0xFFF;
        self->ext.swordFamiliar.unk86 = GetTargetPositionWithDistanceBuffer(
            self->ext.swordFamiliar.unk84, self->ext.swordFamiliar.unk88, 0x80);
        self->ext.swordFamiliar.unk88 = self->ext.swordFamiliar.unk86;

        D_us_8017859C =
            FLT_TO_I(rcos(self->ext.swordFamiliar.unk86) * FLT(3.0 / 64.0));
        D_us_801785A0 =
            FLT_TO_I(rsin(self->ext.swordFamiliar.unk86) * FLT(3.0 / 64.0));

        D_us_80170078[2] = self->ext.swordFamiliar.unk86 - FLT(1.0 / 4.0);

        D_us_8017858C = abs(D_us_8017858C);
        D_us_80178590 = abs(D_us_80178590);

        D_us_80178598 = MAX(D_us_8017858C, D_us_80178590);

        self->ext.swordFamiliar.currentX =
            ratan2(D_us_80178594, D_us_80178598) & 0xFFF;
        self->ext.swordFamiliar.unk8c = GetTargetPositionWithDistanceBuffer(
            (s16)self->ext.swordFamiliar.currentX,
            self->ext.swordFamiliar.targetX, 0x80);

        self->ext.swordFamiliar.targetX = self->ext.swordFamiliar.unk8c;
        D_us_801785A4 =
            FLT_TO_I(rsin(self->ext.swordFamiliar.unk8c) * FLT(3.0 / 64.0));

        D_us_80170078[0] = self->ext.swordFamiliar.unk8c;
        D_us_80170080.vx += D_us_8017859C;
        D_us_80170080.vy += D_us_801785A0;
        D_us_80170080.vz += D_us_801785A4;

        D_us_8017858C = D_us_80178580 - D_us_801785A8 - D_us_80170080.vx;
        D_us_80178590 = D_us_80178584 - D_us_801785AC - D_us_80170080.vy;
        D_us_80178594 = D_us_80178588 - D_us_80170080.vz;

        D_us_801785B0 = SquareRoot0(
            SQ(D_us_8017858C) + SQ(D_us_80178590) + SQ(D_us_80178594));

        if (D_us_801785B0 < FLT(1.0 / 8.0)) {
            D_us_801785B4 = 0;
            self->step++;
        }

        break;
    case 7:
    case 10:

        D_us_80170080.vx += D_us_8017859C;
        D_us_80170080.vy += D_us_801785A0;
        D_us_80170080.vz += D_us_801785A4;

        self->ext.swordFamiliar.unk84 =
            ratan2(D_us_801785A0, D_us_8017859C) & 0xFFF;

        self->ext.swordFamiliar.unk86 = GetTargetPositionWithDistanceBuffer(
            self->ext.swordFamiliar.unk84, self->ext.swordFamiliar.unk88, 0x80);
        self->ext.swordFamiliar.unk88 = self->ext.swordFamiliar.unk86;

        D_us_80170078[2] = self->ext.swordFamiliar.unk86 - FLT(1.0 / 4.0);
        D_us_80178594 = D_us_801785A4;
        D_us_8017858C = abs(D_us_8017859C);
        D_us_80178590 = abs(D_us_801785A0);

        D_us_80178598 =
            (D_us_8017858C > D_us_80178590) ? D_us_8017858C : D_us_80178590;

        self->ext.swordFamiliar.currentX =
            ratan2(D_us_801785A4, D_us_80178598) & 0xFFF;
        self->ext.swordFamiliar.unk8c = GetTargetPositionWithDistanceBuffer(
            self->ext.swordFamiliar.currentX, self->ext.swordFamiliar.targetX,
            0x80);
        self->ext.swordFamiliar.targetX = self->ext.swordFamiliar.unk8c;
        D_us_80170078[0] = self->ext.swordFamiliar.unk8c;
        D_us_801785B4++;

        if (D_us_801785B4 > D_us_80170220) {
            if (self->step == 10) {
                self->step = 1;
            } else {
                self->step++;
            }
        }
        break;

    case 8:
        if (!CheckEntityValid(self->ext.swordFamiliar.follow)) {
            if ((self->ext.swordFamiliar.follow = func_us_80173AA0(self)) ==
                NULL) {
                self->entityId = SWORD_DEFAULT;
                self->step = 0;
                break;
            }
        }
        if (g_CutsceneHasControl) {
            self->entityId = SWORD_DEFAULT;
            self->step = 0;
            break;
        }
        self->ext.swordFamiliar.unk98 = 1;
        self->step++;
        // fallthrough
    case 9:
        D_us_80178580 = (self->ext.swordFamiliar.follow->posX.i.hi - 0x80) << 5;
        D_us_80178584 = (self->ext.swordFamiliar.follow->posY.i.hi - 0x80) << 5;
        D_us_80178588 = 0;
        D_us_80178584 += D_us_801785AC;
        D_us_80178580 += D_us_801785A8;

        D_us_8017858C = D_us_80178580 - D_us_801785A8 - D_us_80170080.vx;
        D_us_80178590 = D_us_80178584 - D_us_801785AC - D_us_80170080.vy;
        D_us_80178594 = D_us_80178588 - D_us_80170080.vz;

        self->ext.swordFamiliar.unk84 =
            ratan2(D_us_80178590, D_us_8017858C) & 0xFFF;
        self->ext.swordFamiliar.unk86 = GetTargetPositionWithDistanceBuffer(
            self->ext.swordFamiliar.unk84, self->ext.swordFamiliar.unk88, 0x80);
        self->ext.swordFamiliar.unk88 = self->ext.swordFamiliar.unk86;

        D_us_8017859C =
            FLT_TO_I(rcos(self->ext.swordFamiliar.unk86) * FLT(3.0 / 64.0));
        D_us_801785A0 =
            FLT_TO_I(rsin(self->ext.swordFamiliar.unk86) * FLT(3.0 / 64.0));

        D_us_80170078[2] = self->ext.swordFamiliar.unk86 - FLT(1.0 / 4.0);
        D_us_8017858C = abs(D_us_8017858C);
        D_us_80178590 = abs(D_us_80178590);
        D_us_80178598 =
            (D_us_8017858C > D_us_80178590) ? D_us_8017858C : D_us_80178590;

        self->ext.swordFamiliar.currentX =
            ratan2(D_us_80178594, D_us_80178598) & 0xFFF;

        self->ext.swordFamiliar.unk8c = GetTargetPositionWithDistanceBuffer(
            self->ext.swordFamiliar.currentX, self->ext.swordFamiliar.targetX,
            128);
        self->ext.swordFamiliar.targetX = self->ext.swordFamiliar.unk8c;
        D_us_801785A4 =
            FLT_TO_I(rsin(self->ext.swordFamiliar.unk8c) * FLT(3.0 / 64.0));
        D_us_80170078[0] = self->ext.swordFamiliar.unk8c;

        D_us_80170080.vx += D_us_8017859C;
        D_us_80170080.vy += D_us_801785A0;
        D_us_80170080.vz += D_us_801785A4;
        D_us_8017858C = D_us_80178580 - D_us_801785A8 - D_us_80170080.vx;
        D_us_80178590 = D_us_80178584 - D_us_801785AC - D_us_80170080.vy;
        D_us_80178594 = D_us_80178588 - D_us_80170080.vz;

        D_us_801785B0 = SquareRoot0(
            SQ(D_us_8017858C) + SQ(D_us_80178590) + SQ(D_us_80178594));

        if (D_us_801785B0 < FLT(1.0 / 8.0)) {
            self->step++;
        }
        break;
    }

    ProcessEvent(self, false);
    self->posX.i.hi = D_us_80170080.vx / 32 + 128;
    self->posY.i.hi = D_us_80170080.vy / 32 + 128;
    func_us_80172E84(self, self->ext.swordFamiliar.unk80);

    if (self->step < 5) {
        return;
    }

    if (D_us_80170080.vz >= FLT(-1.0 / 8.0) &&
        D_us_80170080.vz <= FLT(1.0 / 8.0)) {
        if (self->ext.swordFamiliar.unk98) {
            if ((roll = rand() % 16) < 2) {
                g_api.PlaySfx(D_us_80170090[roll ? 0 : 1]);
            }
            self->ext.swordFamiliar.unk98 = 0;
        }
        func_us_801724E8(self, 0, false);
        func_us_801724E8(self, 0, true);
    }
}

extern s16 D_us_80170098[]; // sfx ids

void func_us_801758C8(Entity* self) {
    Primitive* next;
    s32 i;
    Primitive* prim;
    Primitive* last;
    s32 x;
    s32 y;
    s32 z;
    s32 var_s7;

    s16 x0, x1, x2, x3;
    s16 y0, y1, y2, y3;

    CheckSwordLevel(self);
    D_us_80170080.vx = (self->posX.i.hi - 0x80) << 5;
    D_us_80170080.vy = (self->posY.i.hi - 0x80) << 5;

    switch (self->step) {
    case 0:
        func_us_80172940(self);
        break;

    case 1:
        D_us_801785B8 = FLT(0);
        D_us_801785BC = FLT(-1.0);
        D_us_801785C0 = FLT(-3.0 / 4.0);
        g_api.PlaySfx(SFX_ANIME_SWORD_A);
        self->step++;
        // fallthrough

    case 2:

        D_us_801785C4 = D_us_801785B8 - D_us_80170080.vx;
        D_us_801785C8 = D_us_801785BC - D_us_80170080.vy;
        D_us_801785CC = D_us_801785C0 - D_us_80170080.vz;
        self->ext.swordFamiliar.unk84 =
            ratan2(D_us_801785C8, D_us_801785C4) & 0xFFF;

        self->ext.swordFamiliar.unk86 = GetTargetPositionWithDistanceBuffer(
            self->ext.swordFamiliar.unk84, self->ext.swordFamiliar.unk88,
            0x180);
        self->ext.swordFamiliar.unk88 = self->ext.swordFamiliar.unk86;
        D_us_801785D4 = FLT_TO_I(rcos(self->ext.swordFamiliar.unk86) << 7);
        D_us_801785D8 = FLT_TO_I(rsin(self->ext.swordFamiliar.unk86) << 7);

        D_us_8017007C.x = self->ext.swordFamiliar.unk86 - FLT(1.0 / 4.0);
        D_us_801785C4 = abs(D_us_801785C4);
        D_us_801785C8 = abs(D_us_801785C8);

#ifdef VERSION_PSP
        D_us_801785D0 = CLAMP_MAX(D_us_801785C4, D_us_801785C8);
#else
        D_us_801785D0 = CLAMP_MIN(D_us_801785C4, D_us_801785C8);
#endif

        self->ext.swordFamiliar.currentX =
            ratan2(D_us_801785CC, D_us_801785D0) & 0xFFF;
        self->ext.swordFamiliar.unk8c = GetTargetPositionWithDistanceBuffer(
            self->ext.swordFamiliar.currentX, self->ext.swordFamiliar.targetX,
            0x40);

        self->ext.swordFamiliar.targetX = self->ext.swordFamiliar.unk8c;

        D_us_801785DC = FLT_TO_I(rsin(self->ext.swordFamiliar.unk8c) << 7);

        D_us_80170078[0] = self->ext.swordFamiliar.unk8c;
        D_us_80170080.vx += D_us_801785D4;
        D_us_80170080.vy += D_us_801785D8;
        D_us_80170080.vz += D_us_801785DC;

        D_us_801785C4 = D_us_801785B8 - D_us_80170080.vx;
        D_us_801785C8 = D_us_801785BC - D_us_80170080.vy;
        D_us_801785CC = D_us_801785C0 - D_us_80170080.vz;

        D_us_801785E0 = SquareRoot0(
            SQ(D_us_801785C4) + SQ(D_us_801785C8) + SQ(D_us_801785CC));
        if (D_us_801785E0 < FIX(1.0 / 256.0)) {
            D_us_80170080.vx = 0;
            D_us_80170080.vy = FIX(-1.0 / 16.0);
            D_us_80170080.vz = FIX(-3.0 / 64.0);
            self->step++;
        }
        break;

    case 3:
        func_us_8017280C(self, self->ext.swordFamiliar.unk80, 1);
        D_us_80178B74 = 0;
        D_us_80170078[0] = self->ext.swordFamiliar.targetX = 0;
        D_us_8017007C.x = FLT(0);
        self->ext.swordFamiliar.unk88 = FIX(1.0 / 64.0);
        g_api.PlaySfx(SFX_ANIME_SWORD_A);
        self->step++;
        // fallthrough

    case 4:
        D_us_80170080.vy += FIX(1.0 / 256.0);
        if (D_us_80170080.vy >= 0) {
            D_us_80170080.vy = 0;
            D_us_801785E4 = 0;
            g_api.PlaySfx(D_us_80170098[0]);
            g_PauseAllowed = false;
            self->step++;
        }
        break;
    case 5:
        D_us_801785E4++;
        if (D_us_801785E4 > 70) {
            self->step++;
        }
        break;

    case 6:
        self->ext.swordFamiliar.unk88 += 0x40;
        self->ext.swordFamiliar.unk88 &= 0xFFF;
        D_us_8017007C.x = self->ext.swordFamiliar.unk88 - FLT(1.0 / 4.0);
        D_us_80170080.vz += 0x60;

        if (D_us_80170080.vz >= 0) {
            D_us_80170080.vz = 0;
            D_us_801785E8 = 0;
            self->step++;
        }

        break;

    case 7:
        self->ext.swordFamiliar.unk88 += 0x40;
        self->ext.swordFamiliar.unk88 &= 0xFFF;
        D_us_8017007C.x = self->ext.swordFamiliar.unk88 - FLT(1.0 / 4.0);
        if (self->ext.swordFamiliar.unk88 == FLT(3.0 / 4.0)) {
            D_us_801785E4 = 0;
            self->step++;
        }

        prim = &g_PrimBuf[self->primIndex];
        next = prim->next;
        for (i = 0; i < D_us_801785E8; i++) {
            next = next->next;
        }

        last = next->next;
        *next = *prim;
        next->next = last;
        next->clut = 0x142;
        next->drawMode = DRAW_UNK_100 | DRAW_UNK_40 | DRAW_TPAGE2 | DRAW_TPAGE |
                         DRAW_COLORS | DRAW_TRANSP;
        next->r0 = next->r1 = next->r2 = next->r3 = next->g0 = next->g1 =
            next->g2 = next->g3 = next->b0 = next->b1 = next->b2 = next->b3 =
                128;
        D_us_801785E8++;
        break;

    case 8:
        D_us_801785E4++;
        if (D_us_801785E4 > 15) {
            D_us_801785E4 = 0;
            g_PauseAllowed = true;
            func_us_801724E8(self, 1, false);
            g_api.PlaySfx(SFX_MAGIC_SWITCH);
            self->step++;
        }
        break;

    case 9:
        prim = &g_PrimBuf[self->primIndex];
        next = prim->next;
        var_s7 = D_us_801785E4 * 32;
        x0 = prim->x0 - 128;
        x1 = prim->x1 - 128;
        x2 = prim->x2 - 128;
        x3 = prim->x3 - 128;
        y0 = prim->y0 - 128;
        y1 = prim->y1 - 128;
        y2 = prim->y2 - 128;
        y3 = prim->y3 - 128;

        for (i = 0; i < 64; i++) {
            s32 temp_s1 = rsin(var_s7);
            s32 temp_s2 = rcos(var_s7);
            D_us_801785C4 =
                FLT_TO_I(rcos(var_s7 + ROT(270)) * (D_us_801785E4 * 16)) + 128;
            D_us_801785C8 =
                FLT_TO_I(rsin(var_s7 + ROT(270)) * (D_us_801785E4 * 16)) + 128;
            next->x0 =
                D_us_801785C4 + FLT_TO_I((temp_s2 * x0) - (temp_s1 * y0));
            next->y0 =
                D_us_801785C8 + FLT_TO_I((temp_s1 * x0) + (temp_s2 * y0));
            next->x1 =
                D_us_801785C4 + FLT_TO_I((temp_s2 * x1) - (temp_s1 * y1));
            next->y1 =
                D_us_801785C8 + FLT_TO_I((temp_s1 * x1) + (temp_s2 * y1));
            next->x2 =
                D_us_801785C4 + FLT_TO_I((temp_s2 * x2) - (temp_s1 * y2));
            next->y2 =
                D_us_801785C8 + FLT_TO_I((temp_s1 * x2) + (temp_s2 * y2));
            next->x3 =
                D_us_801785C4 + FLT_TO_I((temp_s2 * x3) - (temp_s1 * y3));
            next->y3 =
                D_us_801785C8 + FLT_TO_I((temp_s1 * x3) + (temp_s2 * y3));
            next = next->next;
            var_s7 += FLT(1.0 / 64.0);
            var_s7 &= 0xFFF;
        }

        D_us_801785E4++;
        if (D_us_801785E4 > 15) {
            D_us_801785E4 = 0;
            self->step++;
        }
        break;

    case 10:
        D_us_801785E4++;

        if (D_us_801785E4 > 30) {
            func_us_8017259C(self, self->ext.swordFamiliar.unk80,
                             self->ext.swordFamiliar.unk82);
            D_us_80178B74 = 1;
            self->entityId = SWORD_DEFAULT;
            self->step = 0;
        }
        break;
    }

    ProcessEvent(self, false);

    self->posX.i.hi = D_us_80170080.vx / 32 + 128;
    self->posY.i.hi = D_us_80170080.vy / 32 + 128;

    func_us_80172E84(self, self->ext.swordFamiliar.unk80);
}

void func_us_80176270(Entity* self) {
    s32 i;

    D_us_80170080.vx = (self->posX.i.hi - 128) << 5;
    D_us_80170080.vy = (self->posY.i.hi - 128) << 5;

    switch (self->step) {
    case 0:
        func_us_80172940(self);
        break;

    case 1:
        D_us_801785EC = FLT(1);
        D_us_801785F0 = FLT(1);
        D_us_801785F4 = FLT(-1);
        g_api.PlaySfx(SFX_ANIME_SWORD_A);
        self->step++;

        // fallthrough

    case 2:
    case 3:
        D_us_801785F8 = D_us_801785EC - D_us_80170080.vx;
        D_us_801785FC = D_us_801785F0 - D_us_80170080.vy;
        D_us_80178600 = D_us_801785F4 - D_us_80170080.vz;
        self->ext.swordFamiliar.unk84 =
            ratan2(D_us_801785FC, D_us_801785F8) & 0xFFF;

        self->ext.swordFamiliar.unk86 = GetTargetPositionWithDistanceBuffer(
            self->ext.swordFamiliar.unk84, self->ext.swordFamiliar.unk88,
            0x180);
        self->ext.swordFamiliar.unk88 = self->ext.swordFamiliar.unk86;
        D_us_80178608 = FLT_TO_I(rcos(self->ext.swordFamiliar.unk86) << 8);
        D_us_8017860C = FLT_TO_I(rsin(self->ext.swordFamiliar.unk86) << 8);
        D_us_8017007C.x = self->ext.swordFamiliar.unk86 - FLT(1.0 / 4.0);

        D_us_801785F8 = abs(D_us_801785F8);
        D_us_801785FC = abs(D_us_801785FC);

        D_us_80178604 = MAX(D_us_801785F8, D_us_801785FC);

        self->ext.swordFamiliar.currentX =
            ratan2(D_us_80178600, D_us_80178604) & 0xFFF;

        self->ext.swordFamiliar.unk8c = GetTargetPositionWithDistanceBuffer(
            self->ext.swordFamiliar.currentX, self->ext.swordFamiliar.targetX,
            0x40);
        self->ext.swordFamiliar.targetX = self->ext.swordFamiliar.unk8c;

        D_us_80178610 = FLT_TO_I(rsin(self->ext.swordFamiliar.unk8c) << 8);

        D_us_80170078[0] = self->ext.swordFamiliar.unk8c;

        D_us_80170080.vx += D_us_80178608;
        D_us_80170080.vy += D_us_8017860C;
        D_us_80170080.vz += D_us_80178610;

        D_us_801785F8 = D_us_801785EC - D_us_80170080.vx;
        D_us_801785FC = D_us_801785F0 - D_us_80170080.vy;
        D_us_80178600 = D_us_801785F4 - D_us_80170080.vz;

        D_us_80178614 = SquareRoot0(
            SQ(D_us_801785F8) + SQ(D_us_801785FC) + SQ(D_us_80178600));

        if (D_us_80178614 < FLT(1.0 / 16.0)) {
            if (self->step == 2) {
                D_us_80170080.vx = FLT(1);
                D_us_80170080.vy = FLT(1);
                D_us_80170080.vz = FLT(-1);
                D_us_801785EC = FLT(-1);
                D_us_801785F0 = FLT(-1);
                D_us_801785F4 = FLT(-1);
                self->ext.swordFamiliar.unk88 = FLT(5.0 / 8.0);
                self->ext.swordFamiliar.targetX = 0;
                g_api.PlaySfx(SFX_ANIME_SWORD_A);
            }
            self->step++;
        }
        break;

    case 4:
        if ((g_Status.relics[RELIC_SWORD_CARD] & 1) &&
            (g_Status.relics[RELIC_SWORD_CARD] & 2)) {
            g_Status.relics[RELIC_SWORD_CARD] = 1;
            g_Servant = 0;
        }

        for (i = 0; i < 4; i++) {
            DestroyEntity(&g_Entities[UNK_ENTITY_4 + i]);
        }
        return;
    }

    ProcessEvent(self, false);

    self->posX.i.hi = D_us_80170080.vx / 32 + 128;
    self->posY.i.hi = D_us_80170080.vy / 32 + 128;
    func_us_80172E84(self, self->ext.swordFamiliar.unk80);
}

void func_us_80176664(Entity* self) {}

void func_us_8017666C(Entity* self) {}

void func_us_80176674(Entity* self) {
    s32 params;
    s32 x, y;

    CheckSwordLevel(self);

    D_us_80178638 += FLT(1.0 / 256.0);
    D_us_80178638 &= 0xFFF;

    D_us_80178624 = PLAYER.facingLeft ? -FIX(24) : FIX(24);
    D_us_80178628 = FIX(28);
    D_us_8017861C = PLAYER.posX.val + D_us_80178624;

    D_us_80178620 = PLAYER.posY.val -
                    ((FLT_TO_FIX(rcos(D_us_80178638)) << 4) + D_us_80178628);
    D_us_80178624 = FIX_TO_I(D_us_8017861C - self->posX.val);
    D_us_80178628 = FIX_TO_I(D_us_80178620 - self->posY.val);

    D_us_80178634 =
        FLT_TO_I(SquareRoot12(I_TO_FLT(SQ(D_us_80178624) + SQ(D_us_80178628))));

    if (D_us_80178634 < 60) {
        self->velocityX = (D_us_8017861C - self->posX.val) >> 6;
        self->velocityY = (D_us_80178620 - self->posY.val) >> 6;
    } else if (D_us_80178634 < 100) {
        self->velocityX = (D_us_8017861C - self->posX.val) >> 5;
        self->velocityY = (D_us_80178620 - self->posY.val) >> 5;
    } else {
        self->velocityX = (D_us_8017861C - self->posX.val) >> 4;
        self->velocityY = (D_us_80178620 - self->posY.val) >> 4;
    }

    self->posX.val += self->velocityX;
    self->posY.val += self->velocityY;

    if (D_us_80178634 > 16) {
        self->ext.swordFamiliar.unk84 =
            ratan2(D_us_80178628, D_us_80178624) & 0xFFF;
        self->ext.swordFamiliar.unk86 = GetTargetPositionWithDistanceBuffer(
            self->ext.swordFamiliar.unk84, self->ext.swordFamiliar.unk88, 8);
    } else {
        self->ext.swordFamiliar.unk86 = GetTargetPositionWithDistanceBuffer(
            FLT(1.0 / 4.0), self->ext.swordFamiliar.unk88, 8);
    }

    self->ext.swordFamiliar.unk88 = self->ext.swordFamiliar.unk86;
    D_us_8017007C.x = self->ext.swordFamiliar.unk86 - FLT(1.0 / 4.0);

    D_us_8017862C = -D_us_80170080.vz;
    D_us_80178624 = FLT_TO_FIX(abs(D_us_80178624)) << 1;
    D_us_80178628 = FLT_TO_FIX(abs(D_us_80178628)) << 1;
    D_us_80178630 = MAX(D_us_80178624, D_us_80178628);

    self->ext.swordFamiliar.currentX =
        ratan2(D_us_8017862C, D_us_80178630) & 0xFFF;
    self->ext.swordFamiliar.unk8c = GetTargetPositionWithDistanceBuffer(
        self->ext.swordFamiliar.currentX, self->ext.swordFamiliar.targetX,
        0x20);

    self->ext.swordFamiliar.targetX = self->ext.swordFamiliar.unk8c;
    D_us_80170080.vz += FLT_TO_I(rsin(self->ext.swordFamiliar.unk8c) * 96);
    D_us_80170078[0] = self->ext.swordFamiliar.unk8c;

    switch (self->step) {
    case 0:
        func_us_80172940(self);
        if (g_CastleFlags[SWORD_FAMILIAR] == 1 ||
            g_CastleFlags[SWORD_FAMILIAR] == 2) {
            g_CastleFlags[SWORD_FAMILIAR] = 3;
        }
        break;
    case 1:
        if ((IsMovementAllowed(1)) || (CheckAllEntitiesValid()) ||
            (D_us_80178B80 == 1) || (g_CutsceneHasControl) ||
            (g_unkGraphicsStruct.D_800973FC != 0)) {
            self->entityId = SWORD_DEFAULT;
            self->step = 0;
            if (g_CastleFlags[SWORD_FAMILIAR] == 3) {
                g_CastleFlags[SWORD_FAMILIAR] = 4;
            }
            return;
        }

        D_us_80178624 = FIX_TO_I(D_us_8017861C - self->posX.val);
        D_us_80178628 = FIX_TO_I(D_us_80178620 - self->posY.val);
        D_us_80178634 = FLT_TO_I(
            SquareRoot12(I_TO_FLT(SQ(D_us_80178624) + SQ(D_us_80178628))));

        if (D_us_80178634 < 32) {
            self->step++;
        }
        break;

    case 2:
        g_PauseAllowed = false;
        if (s_SwordStats.unk8 == 1) {
            CreateEventEntity(self, SWORD_UNK_DD, 0x4FB);
        } else if (g_CastleFlags[SWORD_FAMILIAR] == 3) {
            CreateEventEntity(self, SWORD_UNK_DD, 0x4FE);
            g_CastleFlags[SWORD_FAMILIAR] = 4;
        } else {
            // at level 50, change
            if (s_SwordStats.level < 50) {
                CreateEventEntity(self, SWORD_UNK_DD, 0x4FC);
            } else {
                CreateEventEntity(self, SWORD_UNK_DD, 0x4FF);
            }
        }
        self->step++;
        break;

    case 3:
        if (g_PlaySfxStep == 0x63) {
            self->step++;
        }
        break;

    case 4:
        g_PauseAllowed = true;
        self->entityId = SWORD_DEFAULT;
        self->step = 0;
        break;
    }

    ProcessEvent(self, false);
    D_us_80170080.vx = (self->posX.i.hi - 128) << 5;
    D_us_80170080.vy = (self->posY.i.hi - 128) << 5;
    func_us_80172E84(self, self->ext.swordFamiliar.unk80);
}

void func_us_80176BF0(Entity* self) {}

void func_us_80176BF8(Entity* self) {
    const int PRIM_COUNT = 16;
    Primitive* prim;
    Primitive* next;
    s32 i;

    switch (self->step) {
    case 0:
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, PRIM_COUNT);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }

        self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA |
                      FLAG_HAS_PRIMS | FLAG_UNK_20000;
        prim = &g_PrimBuf[self->primIndex];
        for (i = 0; i < PRIM_COUNT; i++) {
            prim->tpage = 0x1B;
            prim->clut = 0x141;
            prim->u0 = prim->u2 = 0;
            prim->v0 = prim->v1 = 0;
            prim->u1 = prim->u3 = 16;
            prim->v2 = prim->v3 = 16;
            prim->r0 = prim->r1 = ((i + 1) * 4) + 8;
            prim->g0 = prim->g1 = ((i + 1) * 14) + 8;
            prim->b0 = prim->b1 = ((i + 1) * 8) + 8;
            prim->r2 = prim->r3 = (i * 4) + 8;
            prim->g2 = prim->g3 = (i * 14) + 8;
            prim->b2 = prim->b3 = (i * 8) + 8;
            prim->drawMode =
                DRAW_UNK_400 | DRAW_UNK_100 | DRAW_UNK_40 | DRAW_TPAGE2 |
                DRAW_TPAGE | DRAW_HIDE | DRAW_COLORS | DRAW_UNK02 | DRAW_TRANSP;
            prim = prim->next;
        }
        self->step++;
        break;

    case 1:
        prim = &g_PrimBuf[self->primIndex];
        for (i = 0; i < (PRIM_COUNT - 1); i++) {
            prim = prim->next;
        }
        LOW(prim->x0) = D_us_8017865C[0];
        LOW(prim->x1) = D_us_8017865C[1];
        self->step++;
        break;

    case 2:
        prim = &g_PrimBuf[self->primIndex];
        if (D_us_80178B78) {
            for (i = 0; i < (PRIM_COUNT - 1); i++) {
                next = prim->next;
                prim->priority = next->priority;
                prim->drawMode = next->drawMode;
                LOW(prim->x0) = LOW(next->x0);
                LOW(prim->x1) = LOW(next->x1);
                LOW(prim->x2) = LOW(next->x2);
                LOW(prim->x3) = LOW(next->x3);
                prim = next;
            }
            prim->priority = D_us_8017866C;
            prim->drawMode &= ~DRAW_HIDE;

            LOW(prim->x2) = LOW(prim->x0);
            LOW(prim->x3) = LOW(prim->x1);
            do {
            } while (0);
            LOW(prim->x0) = D_us_8017865C[0];
            LOW(prim->x1) = D_us_8017865C[1];
        } else {
            for (i = 0; i < PRIM_COUNT; i++) {
                prim->drawMode |= DRAW_HIDE;
                LOW(prim->x0) = LOW(prim->x1) = D_us_8017865C[0];
                LOW(prim->x2) = LOW(prim->x3) = D_us_8017865C[1];
                prim = prim->next;
            }
            self->step--;
        }
        break;
    }

    D_us_80178B78 = 0;
}

void func_us_80176F28(Entity* self) {
    s32 i;

    switch (self->step) {
    case 0:
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 4);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }

        self->flags =
            FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_HAS_PRIMS | FLAG_UNK_20000;
        D_us_8017863C = &g_PrimBuf[self->primIndex];
        for (i = 0; i < 4; i++) {
            D_us_8017863C->tpage = 0x1B;
            D_us_8017863C->clut = 0x141;
            D_us_8017863C->u0 = D_us_8017863C->u2 = 0;
            D_us_8017863C->v0 = D_us_8017863C->v1 = 0;
            D_us_8017863C->u1 = D_us_8017863C->u3 = 16;
            D_us_8017863C->v2 = D_us_8017863C->v3 = 16;
            D_us_8017863C->drawMode =
                DRAW_UNK_100 | DRAW_TPAGE2 | DRAW_TPAGE | DRAW_HIDE |
                DRAW_COLORS | DRAW_UNK02 | DRAW_TRANSP;

            D_us_8017863C = D_us_8017863C->next;
        }
        self->step++;
        break;

    case 1:
        D_us_8017863C = &g_PrimBuf[self->primIndex];
        if (D_us_80178B7C != 0) {
            for (i = 0; i < 4; i++) {
                D_us_8017863C->priority = D_us_80178670[i][4];
                D_us_8017863C->drawMode &= ~DRAW_HIDE;
                LOW(D_us_8017863C->x0) = D_us_80178670[i][0];
                LOW(D_us_8017863C->x1) = D_us_80178670[i][1];
                LOW(D_us_8017863C->x2) = D_us_80178670[i][2];
                LOW(D_us_8017863C->x3) = D_us_80178670[i][3];

                if (i < 2) {
                    D_us_8017863C->r0 = D_us_8017863C->g0 =
                        FLT_TO_I(FLT_TO_FIX(rsin(D_us_80178644)) << 1) + 32;
                    D_us_8017863C->b0 =
                        FLT_TO_I(FLT_TO_FIX(rsin(D_us_80178648)) << 1) + 64;

                    D_us_8017863C->r1 = D_us_8017863C->g1 =
                        FLT_TO_I(FLT_TO_FIX(rsin(D_us_80178644)) << 1) + 96;
                    D_us_8017863C->b1 =
                        FLT_TO_I(FLT_TO_FIX(rsin(D_us_80178648)) << 1) + 192;

                    D_us_8017863C->r2 = D_us_8017863C->g2 =
                        FLT_TO_I(FLT_TO_FIX(rcos(D_us_80178644)) << 1) + 32;
                    D_us_8017863C->b2 =
                        FLT_TO_I(FLT_TO_FIX(rcos(D_us_80178648)) << 1) + 64;

                    D_us_8017863C->r3 = D_us_8017863C->g3 =
                        FLT_TO_I(FLT_TO_FIX(rcos(D_us_80178644)) << 1) + 32;
                    D_us_8017863C->b3 =
                        FLT_TO_I(FLT_TO_FIX(rcos(D_us_80178648)) << 1) + 64;
                } else {
                    D_us_8017863C->r0 = D_us_8017863C->g0 =
                        FLT_TO_I(FLT_TO_FIX(rsin(D_us_80178644)) << 1) + 96;
                    D_us_8017863C->b0 =
                        FLT_TO_I(FLT_TO_FIX(rsin(D_us_80178648)) << 1) + 0xc0;

                    D_us_8017863C->r1 = D_us_8017863C->g1 =
                        FLT_TO_I(FLT_TO_FIX(rsin(D_us_80178644)) << 1) + 96;
                    D_us_8017863C->b1 =
                        FLT_TO_I(FLT_TO_FIX(rsin(D_us_80178648)) << 1) + 192;

                    D_us_8017863C->r2 = D_us_8017863C->g2 =
                        FLT_TO_I(FLT_TO_FIX(rcos(D_us_80178644)) << 1) + 32;
                    D_us_8017863C->b2 =
                        FLT_TO_I(FLT_TO_FIX(rcos(D_us_80178648)) << 1) + 64;

                    D_us_8017863C->r3 = D_us_8017863C->g3 =
                        FLT_TO_I(FLT_TO_FIX(rcos(D_us_80178644)) << 1) + 32;
                    D_us_8017863C->b3 =
                        FLT_TO_I(FLT_TO_FIX(rcos(D_us_80178648)) << 1) + 64;
                }

                D_us_8017863C = D_us_8017863C->next;
            }
        } else {
            for (i = 0; i < 4; i++) {
                D_us_8017863C->drawMode |= DRAW_HIDE;

                LOW(D_us_8017863C->x0) = D_us_80178670[i][0];
                LOW(D_us_8017863C->x1) = D_us_80178670[i][1];
                LOW(D_us_8017863C->x2) = D_us_80178670[i][2];
                LOW(D_us_8017863C->x3) = D_us_80178670[i][3];

                D_us_8017863C = D_us_8017863C->next;
            }
        }
        D_us_80178644 += 0x20;
        D_us_80178644 &= 0xFFF;
        D_us_80178644 += 0x40;
        D_us_80178644 &= 0xFFF;
        break;
    }

    D_us_80178B7C = 0;
}

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

void func_us_80177480(Entity* self) {
    s32 flag;
    s32 spellId;

    switch (self->step) {
    case 0:
        self->flags =
            FLAG_POS_CAMERA_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_UNK_20000;
        flag = D_us_801700A0[(s_SwordStats.level / 10)].unk0;
        if (flag) {
            spellId = FAM_ABILITY_SWORD_UNK20;
        } else {
            spellId = FAM_ABILITY_SWORD_UNK19;
        }

        g_api.GetServantStats(self, spellId, 1, &s_SwordStats);

        self->hitboxWidth = 4;
        self->hitboxHeight = 4;

        if (!self->params) {
            self->posX.i.hi = LOW(D_us_801786C0[0]) & 0xFFFF;
            self->posY.i.hi = (LOW(D_us_801786C0[0]) >> 16) & 0xFFFF;
        } else {
            self->posX.i.hi = LOW(D_us_801786C0[1]) & 0xFFFF;
            self->posY.i.hi = (LOW(D_us_801786C0[1]) >> 16) & 0xFFFF;
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
