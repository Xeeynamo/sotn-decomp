// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sword.h"
#include "../servant_private.h"
#include <items.h>
#include <sfx.h>

#define UNK_SWORD_PRIM_COUNT 96
#define CLUT_INDEX_SERVANT_2 0x410

typedef struct {
    s16 x;
    s16 y;
    s32 z;
} SwordUnkStruct;

#ifdef VERSION_PSP
#define sp2 ((SwordUnkStruct*)SP(0x24))
#else
#define sp2 ((SwordUnkStruct*)SP(0x20))
#endif

static FamiliarStats s_SwordStats;
static s32 s_SwordCurrentLevel;
static s32 D_us_8017865C[5];
static s32 D_us_80178670[4][5];
static s32 D_us_801786C0[5];
static SwordUnkStruct* D_us_801786D4[UNK_SWORD_PRIM_COUNT];
static SwordUnkStruct* D_us_80178854[UNK_SWORD_PRIM_COUNT];
static SwordUnkStruct* D_us_801789D4[UNK_SWORD_PRIM_COUNT];
static MATRIX D_us_80178B54;
static bool D_us_80178B74;
static bool D_us_80178B78;
static bool D_us_80178B7C;
static bool D_us_80178B80;
static bool D_us_80178B84;
static s32 D_us_80178B88;

// DATA
#ifdef VERSION_PSP
#include "sword_data.h"
#endif
static VECTOR g_TransferVector = {0, 0, 6500};
static SVECTOR g_RotationAngle = {0};
static SVECTOR D_us_80170078 = {0};
static VECTOR D_us_80170080 = {0};
// sound effect IDs
static s16 D_us_80170090[] = {
    SFX_SWORD_SERVANT_SLASH,      SFX_SWORD_SERVANT_SLICE,
    SFX_SWORD_SERVANT_TEAR,       SFX_SWORD_SERVANT_DARK_EDGE,
    SFX_SWORD_SERVANT_BROS_SPELL, SFX_SWORD_SERVANT_GRUNT_A,
    SFX_SWORD_SERVANT_GRUNT_B,
};
static SwordUnk_A0 D_us_801700A0[10] = {
    {0, 0, 1}, {0, 0, 1}, {0, 0, 1}, {0, 0, 1}, {0, 0, 1},
    {0, 1, 1}, {0, 1, 1}, {1, 1, 1}, {1, 1, 1}, {1, 1, 3},
};
static SVECTOR D_us_80170118 = {-60, -85, 0};
static SVECTOR D_us_80170120 = {61, -85, 0};
static SVECTOR D_us_80170128 = {-60, 274, 0};
static SVECTOR D_us_80170130 = {61, 274, 0};
static SVECTOR D_us_80170138[] = {{0, 90, 0}, {0, 274, 0}};
static SVECTOR D_us_80170148[] = {
    {-22, 80, 0},  {-22, 240, 0}, {0, 90, 0},  {0, 240, 0},
    {22, 80, 0},   {22, 240, 0},  {0, 90, 0},  {0, 240, 0},
    {-22, 240, 0}, {0, 290, 0},   {0, 240, 0}, {0, 240, 0},
    {22, 240, 0},  {0, 290, 0},   {0, 240, 0}, {0, 240, 0},
};
static SVECTOR D_us_801701C8[] = {{0, 125, 0}, {0, 195, 0}};
static u16 g_SwordClut[] = {
    0x0000, 0xD252, 0xD252, 0xD252, 0xD252, 0xD252, 0xD252, 0xD252,
    0xD252, 0xD252, 0xD252, 0xD252, 0xD252, 0xD252, 0xD252, 0xD252,
    0x0000, 0x8841, 0x8C80, 0xAD60, 0xD6A0, 0xDFE0, 0xD607, 0xEED2,
    0xFFFC, 0x80EE, 0x81F4, 0x8F5F, 0xBFFF, 0x800A, 0x8010, 0x8016,
};
static s32 D_us_80170218 = 30;
static s32 D_us_8017021C = 60;
static s32 D_us_80170220 = 15;
#ifndef VERSION_PSP
#include "sword_data.h"
#endif

// sets up familiar entity id "state" during initialization
// and level change
void func_us_80172420(Entity* parent, s32 entityId) {
    Entity* entity;
    s32 i;

    if (parent == NULL) {
        parent = &g_Entities[UNK_ENTITY_4];
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
        entity->zPriority = parent->zPriority;
        entity->facingLeft = parent->facingLeft;
        entity->flags = FLAG_KEEP_ALIVE_OFFCAMERA;
        entity->posX.val = parent->posX.val;
        entity->posY.val = parent->posY.val;
        entity->ext.factory.parent = parent;
    }
}

void func_us_801724E8(Entity* parent, s32 arg1, u32 params) {
    Entity* entity;

    if (entity = g_api.GetFreeEntity(UNK_ENTITY_11, 0x2F)) {
        DestroyEntity(entity);
        entity->entityId = arg1 ? SWORD_UNK_DF : SWORD_UNK_DE;
        entity->zPriority = parent->zPriority;
        entity->facingLeft = parent->facingLeft;
        entity->flags = FLAG_KEEP_ALIVE_OFFCAMERA;
        entity->posX.val = parent->posX.val;
        entity->posY.val = parent->posY.val;
        entity->ext.factory.parent = parent;
        entity->params = params;
    }
}

void func_us_8017259C(Entity* self, s32 arg1, s32 arg2) {
    Primitive* prim;
    s32 i;
    s16* uvCoords;

    prim = &g_PrimBuf[self->primIndex];

    if (!arg1) {
        uvCoords = arg2 ? D_us_801708F4 : D_us_80170594;
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

            D_us_801786D4[i] = &sp2[D_us_80170354[i].vx];
            D_us_80178854[i] = &sp2[D_us_80170354[i].vy];
            D_us_801789D4[i] = &sp2[D_us_80170354[i].vz];
        }

        for (; i < UNK_SWORD_PRIM_COUNT; i++) {
            prim->drawMode |= DRAW_HIDE;
            prim = prim->next;
        }
    } else {
        uvCoords = arg2 ? D_us_80171564 : D_us_801710E4;
        for (i = 0; i < UNK_SWORD_PRIM_COUNT; i++) {
            prim->u0 = *uvCoords++;
            prim->v0 = *uvCoords++;

            prim->u1 = *uvCoords++;
            prim->v1 = *uvCoords++;

            prim->u2 = prim->u3 = *uvCoords++;
            prim->v2 = prim->v3 = *uvCoords++;

            prim->clut = 0x140;
            prim->drawMode = DRAW_UNK_100 | DRAW_HIDE | DRAW_UNK02;
            prim = prim->next;

            D_us_801786D4[i] = &sp2[D_us_80170DE4[i].vx];
            D_us_80178854[i] = &sp2[D_us_80170DE4[i].vy];
            D_us_801789D4[i] = &sp2[D_us_80170DE4[i].vz];
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

void func_us_80172940(Entity* self) {
    Primitive* prim;
    s32 i;

    if (!self->ext.swordFamiliar.unk7c) {
        switch (self->entityId) {
        case SWORD_DEFAULT:
        case SWORD_UNK_D8:
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
                D_us_801700A0[s_SwordStats.level / 10].unk4;
            self->ext.swordFamiliar.unk82 = 1;
            func_us_8017259C(self, self->ext.swordFamiliar.unk80,
                             self->ext.swordFamiliar.unk82);
            self->ext.swordFamiliar.unk86 = self->ext.swordFamiliar.unk88 =
                FLT(0.25);
            self->ext.swordFamiliar.unk8c = self->ext.swordFamiliar.targetX = 0;
            s_SwordCurrentLevel = 0;
            D_us_80178B74 = true;
            self->step++;
            break;
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
                g_Tilemap.left * 0x100 + g_Tilemap.scrollX.i.hi;
            self->ext.swordFamiliar.posY =
                g_Tilemap.top * 0x100 + g_Tilemap.scrollY.i.hi;
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

    self->ext.swordFamiliar.unk7c = self->entityId;
    D_us_80178B80 = false;
}

static s32 Max3(s32 arg0, s32 arg1, s32 arg2) {
#ifdef VERSION_PSP
#define abs labs
#endif
    s32 var_s2 = abs(arg0);
    s32 var_s1 = abs(arg1);
    s32 var_s0 = abs(arg2);

    if (var_s2 >= var_s1 && var_s2 >= var_s0) {
        return var_s2;
    } else if (var_s1 >= var_s2 && var_s1 >= var_s0) {
        return var_s1;
    } else if (var_s0 >= var_s2 && var_s0 >= var_s1) {
        return var_s0;
#ifdef VERSION_PSP
    } else {
        return 0;
#endif
    }
#ifdef VERSION_PSP
#undef abs
#endif
}

static s32 Min3(s32 arg0, s32 arg1, s32 arg2) {
#ifdef VERSION_PSP
#define abs labs
#endif
    s32 var_s2 = abs(arg0);
    s32 var_s1 = abs(arg1);
    s32 var_s0 = abs(arg2);

    if (var_s2 <= var_s1 && var_s2 <= var_s0) {
        return var_s2;
    } else if (var_s1 <= var_s2 && var_s1 <= var_s0) {
        return var_s1;
    } else if (var_s0 <= var_s2 && var_s0 <= var_s1) {
        return var_s0;
#ifdef VERSION_PSP
    } else {
        return 0;
#endif
    }
#ifdef VERSION_PSP
#undef abs
#endif
}

void func_us_80172C8C(SVECTOR* arg0, MATRIX* arg1) {
    static s32 D_us_801782B0;
    static s32 D_us_801782B4;
    static s32 D_us_801782B8;
    static s32 D_us_801782BC;
    static s32 D_us_801782C0;
    static s32 D_us_801782C4;

    D_us_801782B0 = rsin(arg0->vx);
    D_us_801782B4 = rsin(arg0->vy);
    D_us_801782B8 = rsin(arg0->vz);
    D_us_801782BC = rcos(arg0->vx);
    D_us_801782C0 = rcos(arg0->vy);
    D_us_801782C4 = rcos(arg0->vz);

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

typedef struct SwordScratchPad {
    /* 0x0 */ s32 i;
    /* 0x4 */ s32 gteDP;
    /* 0x8 */ s32 gteFLG;
    /* 0xC */ s32 gteOTZ;
    /* 0x10 */ Primitive* prim;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ s32 zPriority;
} SwordScratchPad;

#define sp(field)                                                              \
    (*((typeof(((SwordScratchPad*)0)->field)*)SP(                              \
        (size_t) & (((SwordScratchPad*)0)->field))))

void func_us_80172E84(Entity* self, s32 arg1) {
    static s32 D_us_801782C8;
    static s32 D_us_801782CC;
    static SVECTOR* D_us_801782D0;
    static VECTOR D_us_801782D4;
    static MATRIX D_us_801782E4;
    static MATRIX D_us_80178304;
    static MATRIX D_us_80178324;

    SetGeomOffset(0x80, 0x80);
    gte_SetGeomScreen(1000);
    D_us_801782D4.vx = D_us_80170080.vx / 5;
    D_us_801782D4.vy = D_us_80170080.vy / 5;
    D_us_801782D4.vz = D_us_80170080.vz;
    func_us_80172C8C(&D_us_80170078, &D_us_801782E4);
    TransMatrix(&D_us_801782E4, &D_us_801782D4);
    CompMatrix(&D_us_80178B54, &D_us_801782E4, &D_us_80178304);
    gte_SetRotMatrix(&D_us_80178304);
    gte_SetTransMatrix(&D_us_80178304);

    if (D_us_80178B84) {
        if (D_us_80170080.vz < 0) {
            sp(zPriority) = PLAYER.zPriority + 11;
        } else if (D_us_80170080.vz > 0) {
            sp(zPriority) = PLAYER.zPriority - 9;
        } else {
            sp(zPriority) = PLAYER.zPriority - 1;
        }
    } else {
        if (D_us_80170080.vz < 0) {
            sp(zPriority) = 0x9F;
        } else if (D_us_80170080.vz > 0) {
            sp(zPriority) = 0x8B;
        } else {
            sp(zPriority) = 0x93;
        }
    }

    if (!D_us_80178B74) {
        sp(prim) = &g_PrimBuf[self->primIndex];
        if (D_us_80170080.vz < 0) {
            sp(prim)->priority = PLAYER.zPriority + 1;
        } else {
            sp(prim)->priority = PLAYER.zPriority - 1;
        }

        sp(prim)->drawMode &= ~DRAW_HIDE;

        gte_ldv0(&D_us_80170118);
        gte_rtps();
        gte_stsxy((long*)&sp(prim)->x0);
        gte_stdp(&sp(gteDP));
        gte_stflg(&sp(gteFLG));
        gte_stszotz((long*)&sp(gteOTZ));

        gte_ldv0(&D_us_80170120);
        gte_rtps();
        gte_stsxy((long*)&sp(prim)->x1);
        gte_stdp(&sp(gteDP));
        gte_stflg(&sp(gteFLG));
        gte_stszotz((long*)&sp(gteOTZ));

        gte_ldv0(&D_us_80170128);
        gte_rtps();
        gte_stsxy((long*)&sp(prim)->x2);
        gte_stdp(&sp(gteDP));
        gte_stflg(&sp(gteFLG));
        gte_stszotz((long*)&sp(gteOTZ));

        gte_ldv0(&D_us_80170130);
        gte_rtps();
        gte_stsxy((long*)&sp(prim)->x3);
        gte_stdp(&sp(gteDP));
        gte_stflg(&sp(gteFLG));
        gte_stszotz((long*)&sp(gteOTZ));
    } else {
        D_us_801782C8 = arg1 ? 0x32 : 0x26;
        D_us_801782CC = arg1 ? 0x60 : 0x48;
        D_us_801782D0 = arg1 ? D_us_80170C54 : D_us_80170224;

        sp(unk14) = S32_MAX;
        for (sp(i) = 0; sp(i) < D_us_801782C8; sp(i)++) {
            gte_ldv0(&D_us_801782D0[sp(i)]);
            gte_rtps();

            gte_stsxy((long*)&sp2[sp(i)]);
            gte_stdp(&sp(gteDP));
            gte_stflg(&sp(gteFLG));
            gte_stszotz((long*)&sp(gteOTZ));

            if (sp(unk14) > sp(gteOTZ)) {
                sp(unk14) = sp(gteOTZ);
            }

            sp2[sp(i)].z = sp(gteOTZ);
        }

        sp(prim) = &g_PrimBuf[self->primIndex];
        for (sp(i) = 0; sp(i) < D_us_801782CC; sp(i) = sp(i) + 1) {
            if (NormalClip(*((long*)&(*D_us_801786D4[sp(i)])),
                           *((long*)&(*D_us_80178854[sp(i)])),
                           *((long*)&(*D_us_801789D4[sp(i)]))) >= 0) {

                sp(prim)->x0 = D_us_801786D4[sp(i)]->x;
                sp(prim)->y0 = D_us_801786D4[sp(i)]->y;
                sp(prim)->x1 = D_us_80178854[sp(i)]->x;
                sp(prim)->y1 = D_us_80178854[sp(i)]->y;
                sp(prim)->x2 = D_us_801789D4[sp(i)]->x;
                sp(prim)->y2 = D_us_801789D4[sp(i)]->y;
                sp(prim)->x3 = D_us_801789D4[sp(i)]->x;
                sp(prim)->y3 = D_us_801789D4[sp(i)]->y;

                sp(unk18) =
                    Max3(D_us_801786D4[sp(i)]->z, D_us_80178854[sp(i)]->z,
                         D_us_801789D4[sp(i)]->z);

                sp(prim)->priority =
                    sp(zPriority) - (sp(unk18) - sp(unk14)) / 9;
                sp(prim)->drawMode &= ~DRAW_HIDE;
            } else {
                sp(prim)->drawMode |= DRAW_HIDE;
            }

            sp(prim) = sp(prim)->next;
        }
    }

    gte_ldv0(&D_us_80170138[0]);
    gte_rtps();
    gte_stsxy((long*)&D_us_8017865C[0]);
    gte_stdp(&sp(gteDP));
    gte_stflg(&sp(gteFLG));
    gte_stszotz((long*)&sp(gteOTZ));

    gte_ldv0(&D_us_80170138[1]);
    gte_rtps();
    gte_stsxy((long*)&D_us_8017865C[1]);
    gte_stdp(&sp(gteDP));
    gte_stflg(&sp(gteFLG));
    gte_stszotz((long*)&sp(gteOTZ));

    D_us_8017865C[4] = sp(zPriority) - 10;
    for (sp(i) = 0; sp(i) < 16; sp(i) += 4) {
        gte_ldv0(&D_us_80170148[sp(i)]);
        gte_rtps();
        gte_stsxy((long*)&D_us_80178670[sp(i) / 4][0]);
        gte_stdp(&sp(gteDP));
        gte_stflg(&sp(gteFLG));
        gte_stszotz((long*)&sp(gteOTZ));

        sp(unk18) = sp(gteOTZ);

        gte_ldv0(&D_us_80170148[sp(i) + 1]);
        gte_rtps();
        gte_stsxy((long*)&D_us_80178670[sp(i) / 4][1]);
        gte_stdp(&sp(gteDP));
        gte_stflg(&sp(gteFLG));
        gte_stszotz((long*)&sp(gteOTZ));

        if (sp(unk18) < sp(gteOTZ)) {
            sp(unk18) = sp(gteOTZ);
        }

        gte_ldv0(&D_us_80170148[sp(i) + 2]);
        gte_rtps();
        gte_stsxy((long*)&D_us_80178670[sp(i) / 4][2]);
        gte_stdp(&sp(gteDP));
        gte_stflg(&sp(gteFLG));
        gte_stszotz((long*)&sp(gteOTZ));

        if (sp(unk18) < sp(gteOTZ)) {
            sp(unk18) = sp(gteOTZ);
        }

        gte_ldv0(&D_us_80170148[sp(i) + 3]);
        gte_rtps();
        gte_stsxy((long*)&D_us_80178670[sp(i) / 4][3]);
        gte_stdp(&sp(gteDP));
        gte_stflg(&sp(gteFLG));
        gte_stszotz((long*)&sp(gteOTZ));

        if (sp(unk18) < sp(gteOTZ)) {
            sp(unk18) = sp(gteOTZ);
        }

        D_us_80178670[sp(i) / 4][4] =
            sp(zPriority) - (sp(unk18) - sp(unk14)) / 9 + 1;
    }

    D_us_80178B78 = D_us_80178B7C = true;

    gte_ldv0(&D_us_801701C8[0]);
    gte_rtps();
    gte_stsxy((long*)&D_us_801786C0[0]);
    gte_stdp(&sp(gteDP));
    gte_stflg(&sp(gteFLG));
    gte_stszotz((long*)&sp(gteOTZ));

    gte_ldv0(&D_us_801701C8[1]);
    gte_rtps();
    gte_stsxy((long*)&D_us_801786C0[1]);
    gte_stdp(&sp(gteDP));
    gte_stflg(&sp(gteFLG));
    gte_stszotz((long*)&sp(gteOTZ));
}

Entity* func_us_80173AA0(Entity* self) {
    static s32 D_us_80178344[128];

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
            if (D_us_801700A0[s_SwordStats.level / 10].unk8 & 1) {
                if (SearchForEntityInRange(0, SWORD_UNK_DA) == NULL) {
                    func_us_80172420(self, 0);
                }
            }
            // reserved for level 90
            if ((D_us_801700A0[s_SwordStats.level / 10].unk8 & 2) &&
                SearchForEntityInRange(0, SWORD_UNK_DB) == NULL) {
                func_us_80172420(self, 1);
            }

            if (s_SwordStats.level == 50 &&
                g_CastleFlags[SWORD_FAMILIAR] == 0) {
                g_api.AddToInventory(ITEM_SWORD_FAMILIAR, EQUIP_HAND);
                g_CastleFlags[SWORD_FAMILIAR] = 1;
            }
        }
    }
}

void OVL_EXPORT(ServantInit)(InitializeMode mode) {
    Entity* self;
    s32 i, j;
    u16* dst;
    u16* src;
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
    for (j = 1; j < LEN(g_ServantClut); j++) {
        g_ServantClut[j] |= 0x8000;
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
        self->posY.val = FIX(-32);
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
            self->posX.val =
                PLAYER.posX.val + (PLAYER.facingLeft ? FIX(28) : FIX(-28));
            self->posY.val = PLAYER.posY.val - FIX(28);
        }
    }

    D_us_80170080.vx = (self->posX.i.hi - 128) << 5;
    D_us_80170080.vy = (self->posY.i.hi - 128) << 5;
    D_us_80170080.vz = 0;

    g_api.GetServantStats(self, 0, 0, &s_SwordStats);
    if (D_us_801700A0[s_SwordStats.level / 10].unk8 & 1) {
        func_us_80172420(self, 0);
    }
    if (D_us_801700A0[s_SwordStats.level / 10].unk8 & 2) {
        func_us_80172420(self, 1);
    }

    RotMatrix(&g_RotationAngle, &D_us_80178B54);
    TransMatrix(&D_us_80178B54, &g_TransferVector);

    D_us_80178B80 = false;
    D_us_80178B84 = false;
    D_us_80178B7C = false;
    D_us_80178B78 = false;
}

void OVL_EXPORT(UpdateServantDefault)(Entity* self) {
    static s32 D_us_80178544;
    static s32 D_us_80178548; // x
    static s32 D_us_8017854C; // y
    static s32 D_us_80178550; // x (ps)
    static s32 D_us_80178554; // y (ps)
    static s32 D_us_80178558; // z (ps)
    static s32 D_us_8017855C;
    static s32 D_us_80178560; // distance
    static s32 D_us_80178564;

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
        D_us_80178550 = PLAYER.facingLeft ? FIX(0x1C) : FIX(-0x1C);
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
            self->ext.swordFamiliar.unk86 =
                StepAngleTowards(self->ext.swordFamiliar.unk84,
                                 self->ext.swordFamiliar.unk88, 8);
        } else {
            self->ext.swordFamiliar.unk86 =
                StepAngleTowards(FLT(0.25), self->ext.swordFamiliar.unk88, 8);
        }

        self->ext.swordFamiliar.unk88 = self->ext.swordFamiliar.unk86;
        D_us_80170078.vz = self->ext.swordFamiliar.unk86 - FLT(0.25);

        D_us_80178558 = -D_us_80170080.vz;
        D_us_80178550 = abs(D_us_80178550) << 5;
        D_us_80178554 = abs(D_us_80178554) << 5;

        D_us_8017855C = MAX(D_us_80178550, D_us_80178554);
        self->ext.swordFamiliar.currentX =
            ratan2(D_us_80178558, D_us_8017855C) & 0xFFF;

        self->ext.swordFamiliar.unk8c =
            StepAngleTowards(self->ext.swordFamiliar.currentX,
                             self->ext.swordFamiliar.targetX, 32);
        self->ext.swordFamiliar.targetX = self->ext.swordFamiliar.unk8c;

        D_us_80170080.vz +=
            FLT_TO_I(rsin(self->ext.swordFamiliar.unk8c) * 0x60);
        D_us_80170078.vx = self->ext.swordFamiliar.unk8c;

        if (!g_CutsceneHasControl) {
            if ((self->ext.swordFamiliar.follow = func_us_80173AA0(self)) !=
                NULL) {
                // level 70 and higher
                if (!D_us_801700A0[s_SwordStats.level / 10].unk0) {
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

// only called when the sword has a target
void func_us_801746BC(Entity* self) {
    static s32 D_us_80178568; // x (ps)
    static s32 D_us_8017856C;
    static s32 D_us_80178570;
    static s32 D_us_80178574;
    static s32 D_us_80178578;
    static s32 D_us_8017857C;

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
        g_Tilemap.left * 0x100 + g_Tilemap.scrollX.i.hi;
    self->ext.swordFamiliar.posY =
        g_Tilemap.top * 0x100 + g_Tilemap.scrollY.i.hi;

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
        self->ext.swordFamiliar.unk86 = StepAngleTowards(
            self->ext.swordFamiliar.unk84, self->ext.swordFamiliar.unk88, 32);
        self->ext.swordFamiliar.unk88 = self->ext.swordFamiliar.unk86;

        if (self->ext.swordFamiliar.unk84 == self->ext.swordFamiliar.unk86) {
            self->step++;
        }

        D_us_80170078.vz = self->ext.swordFamiliar.unk86 - FLT(0.25);
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
            D_us_80178568 = D_us_80170078.vz & 0xFFF;
            self->step++;
        }
        break;

    case 4:
        D_us_8017856C++;
        if (D_us_8017856C > D_us_80170218) {
            g_api.PlaySfx(SFX_NOISE_SWEEP_DOWN_A);
            self->step++;
        }
        break;

    case 5:
    case 6:
        D_us_80170078.vz += 128;
        D_us_80170078.vz &= 0xFFF;

        if (D_us_80170078.vz == D_us_80178568) {
            D_us_8017856C = 0;
            self->step++;
        }
        break;

    case 7:
        D_us_8017856C++;
        if (D_us_8017856C > D_us_80170218) {
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

    if (self->step >= 5 && self->step < 7) {
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

void func_us_80174B6C(Entity* self) {
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
    self->ext.swordFamiliar.posX =
        g_Tilemap.left * 0x100 + g_Tilemap.scrollX.i.hi;
    self->ext.swordFamiliar.posY =
        g_Tilemap.top * 0x100 + g_Tilemap.scrollY.i.hi;
    D_us_801785A8 = (self->ext.swordFamiliar.posX - 0x80) << 5;
    D_us_801785AC = (self->ext.swordFamiliar.posY - 0x80) << 5;

    switch (self->step) {
    case 0:
        func_us_80172940(self);
        D_us_8017859C = (rand() & PSP_RANDMASK) - FLT(4);
        D_us_801785A4 = (rand() & PSP_RANDMASK) - FLT(4);
        break;

    case 1:
        D_us_80178580 = PLAYER.facingLeft ? FLT(0.5) : FLT(-0.5);
        D_us_80178584 = FLT(-0.25);
        D_us_80178588 = FLT(-0.25);
        D_us_80178580 += D_us_801785A8;
        D_us_80178584 += D_us_801785AC;
        self->step++;
        // fallthrough

    case 2:

        D_us_8017858C = D_us_80178580 - D_us_801785A8 - D_us_80170080.vx;
        D_us_80178590 = D_us_80178584 - D_us_801785AC - D_us_80170080.vy;
        D_us_80178594 = D_us_80178588 - D_us_80170080.vz;

        self->ext.swordFamiliar.unk84 =
            ratan2(D_us_80178590, D_us_8017858C) & 0xFFF;
        self->ext.swordFamiliar.unk86 = StepAngleTowards(
            self->ext.swordFamiliar.unk84, self->ext.swordFamiliar.unk88, 0x80);
        self->ext.swordFamiliar.unk88 = self->ext.swordFamiliar.unk86;

        D_us_8017859C =
            FLT_TO_I(rcos(self->ext.swordFamiliar.unk86) * FLT(5.0 / 128.0));
        D_us_801785A0 =
            FLT_TO_I(rsin(self->ext.swordFamiliar.unk86) * FLT(5.0 / 128.0));

        D_us_80170078.vz = self->ext.swordFamiliar.unk86 - FLT(0.25);
        D_us_8017858C = abs(D_us_8017858C);
        D_us_80178590 = abs(D_us_80178590);

        D_us_80178598 = MAX(D_us_8017858C, D_us_80178590);

        self->ext.swordFamiliar.currentX =
            ratan2(D_us_80178594, D_us_80178598) & 0xFFF;
        self->ext.swordFamiliar.unk8c =
            StepAngleTowards(self->ext.swordFamiliar.currentX,
                             self->ext.swordFamiliar.targetX, 0x40);

        self->ext.swordFamiliar.targetX = self->ext.swordFamiliar.unk8c;
        D_us_801785A4 = FLT_TO_I(rsin(self->ext.swordFamiliar.unk8c) * 0xA0);
        D_us_80170078.vx = self->ext.swordFamiliar.unk8c;

        D_us_80170080.vx += D_us_8017859C;
        D_us_80170080.vy += D_us_801785A0;
        D_us_80170080.vz += D_us_801785A4;
        D_us_8017858C = D_us_80178580 - D_us_801785A8 - D_us_80170080.vx;
        D_us_80178590 = D_us_80178584 - D_us_801785AC - D_us_80170080.vy;
        D_us_80178594 = D_us_80178588 - D_us_80170080.vz;

        D_us_801785B0 = SquareRoot0(
            SQ(D_us_8017858C) + SQ(D_us_80178590) + SQ(D_us_80178594));

        if (D_us_801785B0 < FLT(0.125)) {
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

        self->ext.swordFamiliar.unk86 =
            StepAngleTowards(FLT(0.25), self->ext.swordFamiliar.unk88, 32);
        self->ext.swordFamiliar.unk88 = self->ext.swordFamiliar.unk86;
        D_us_80170078.vz = self->ext.swordFamiliar.unk86 - FLT(0.25);

        self->ext.swordFamiliar.unk8c =
            StepAngleTowards(FLT(0), self->ext.swordFamiliar.targetX, 32);

        self->ext.swordFamiliar.targetX = self->ext.swordFamiliar.unk8c;
        D_us_80170078.vx = self->ext.swordFamiliar.unk8c;

        if ((self->ext.swordFamiliar.unk86 == FLT(0.25)) &&
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

        D_us_80178580 = D_us_8017859C >= 0 ? FLT(0.5) : FLT(-0.5);
        D_us_80178584 = FLT(-0.5);
        D_us_80178588 = D_us_801785A4 >= 0 ? FLT(0.5) : FLT(-0.5);
        D_us_80178580 += D_us_801785A8;
        D_us_80178584 += D_us_801785AC;
        g_api.PlaySfx(SFX_BOSS_WING_FLAP);
        self->step++;
        // fallthrough

    case 6:
        D_us_8017858C = D_us_80178580 - D_us_801785A8 - D_us_80170080.vx;
        D_us_80178590 = D_us_80178584 - D_us_801785AC - D_us_80170080.vy;
        D_us_80178594 = D_us_80178588 - D_us_80170080.vz;

        self->ext.swordFamiliar.unk84 =
            ratan2(D_us_80178590, D_us_8017858C) & 0xFFF;
        self->ext.swordFamiliar.unk86 = StepAngleTowards(
            self->ext.swordFamiliar.unk84, self->ext.swordFamiliar.unk88, 0x80);
        self->ext.swordFamiliar.unk88 = self->ext.swordFamiliar.unk86;

        D_us_8017859C =
            FLT_TO_I(rcos(self->ext.swordFamiliar.unk86) * FLT(3.0 / 64.0));
        D_us_801785A0 =
            FLT_TO_I(rsin(self->ext.swordFamiliar.unk86) * FLT(3.0 / 64.0));

        D_us_80170078.vz = self->ext.swordFamiliar.unk86 - FLT(0.25);

        D_us_8017858C = abs(D_us_8017858C);
        D_us_80178590 = abs(D_us_80178590);

        D_us_80178598 = MAX(D_us_8017858C, D_us_80178590);

        self->ext.swordFamiliar.currentX =
            ratan2(D_us_80178594, D_us_80178598) & 0xFFF;
        self->ext.swordFamiliar.unk8c =
            StepAngleTowards((s16)self->ext.swordFamiliar.currentX,
                             self->ext.swordFamiliar.targetX, 0x80);

        self->ext.swordFamiliar.targetX = self->ext.swordFamiliar.unk8c;
        D_us_801785A4 =
            FLT_TO_I(rsin(self->ext.swordFamiliar.unk8c) * FLT(3.0 / 64.0));

        D_us_80170078.vx = self->ext.swordFamiliar.unk8c;
        D_us_80170080.vx += D_us_8017859C;
        D_us_80170080.vy += D_us_801785A0;
        D_us_80170080.vz += D_us_801785A4;

        D_us_8017858C = D_us_80178580 - D_us_801785A8 - D_us_80170080.vx;
        D_us_80178590 = D_us_80178584 - D_us_801785AC - D_us_80170080.vy;
        D_us_80178594 = D_us_80178588 - D_us_80170080.vz;

        D_us_801785B0 = SquareRoot0(
            SQ(D_us_8017858C) + SQ(D_us_80178590) + SQ(D_us_80178594));

        if (D_us_801785B0 < FLT(0.125)) {
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

        self->ext.swordFamiliar.unk86 = StepAngleTowards(
            self->ext.swordFamiliar.unk84, self->ext.swordFamiliar.unk88, 0x80);
        self->ext.swordFamiliar.unk88 = self->ext.swordFamiliar.unk86;

        D_us_80170078.vz = self->ext.swordFamiliar.unk86 - FLT(0.25);
        D_us_80178594 = D_us_801785A4;
        D_us_8017858C = abs(D_us_8017859C);
        D_us_80178590 = abs(D_us_801785A0);

        D_us_80178598 =
            (D_us_8017858C > D_us_80178590) ? D_us_8017858C : D_us_80178590;

        self->ext.swordFamiliar.currentX =
            ratan2(D_us_80178594, D_us_80178598) & 0xFFF;
        self->ext.swordFamiliar.unk8c =
            StepAngleTowards(self->ext.swordFamiliar.currentX,
                             self->ext.swordFamiliar.targetX, 0x80);
        self->ext.swordFamiliar.targetX = self->ext.swordFamiliar.unk8c;
        D_us_80170078.vx = self->ext.swordFamiliar.unk8c;
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
        D_us_80178580 += D_us_801785A8;
        D_us_80178584 += D_us_801785AC;

        D_us_8017858C = D_us_80178580 - D_us_801785A8 - D_us_80170080.vx;
        D_us_80178590 = D_us_80178584 - D_us_801785AC - D_us_80170080.vy;
        D_us_80178594 = D_us_80178588 - D_us_80170080.vz;

        self->ext.swordFamiliar.unk84 =
            ratan2(D_us_80178590, D_us_8017858C) & 0xFFF;
        self->ext.swordFamiliar.unk86 = StepAngleTowards(
            self->ext.swordFamiliar.unk84, self->ext.swordFamiliar.unk88, 0x80);
        self->ext.swordFamiliar.unk88 = self->ext.swordFamiliar.unk86;

        D_us_8017859C =
            FLT_TO_I(rcos(self->ext.swordFamiliar.unk86) * FLT(3.0 / 64.0));
        D_us_801785A0 =
            FLT_TO_I(rsin(self->ext.swordFamiliar.unk86) * FLT(3.0 / 64.0));

        D_us_80170078.vz = self->ext.swordFamiliar.unk86 - FLT(0.25);
        D_us_8017858C = abs(D_us_8017858C);
        D_us_80178590 = abs(D_us_80178590);
        D_us_80178598 =
            (D_us_8017858C > D_us_80178590) ? D_us_8017858C : D_us_80178590;

        self->ext.swordFamiliar.currentX =
            ratan2(D_us_80178594, D_us_80178598) & 0xFFF;

        self->ext.swordFamiliar.unk8c =
            StepAngleTowards(self->ext.swordFamiliar.currentX,
                             self->ext.swordFamiliar.targetX, 128);
        self->ext.swordFamiliar.targetX = self->ext.swordFamiliar.unk8c;
        D_us_801785A4 =
            FLT_TO_I(rsin(self->ext.swordFamiliar.unk8c) * FLT(3.0 / 64.0));
        D_us_80170078.vx = self->ext.swordFamiliar.unk8c;

        D_us_80170080.vx += D_us_8017859C;
        D_us_80170080.vy += D_us_801785A0;
        D_us_80170080.vz += D_us_801785A4;
        D_us_8017858C = D_us_80178580 - D_us_801785A8 - D_us_80170080.vx;
        D_us_80178590 = D_us_80178584 - D_us_801785AC - D_us_80170080.vy;
        D_us_80178594 = D_us_80178588 - D_us_80170080.vz;

        D_us_801785B0 = SquareRoot0(
            SQ(D_us_8017858C) + SQ(D_us_80178590) + SQ(D_us_80178594));

        if (D_us_801785B0 < FLT(0.125)) {
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

    if (D_us_80170080.vz >= FLT(-0.125) && D_us_80170080.vz <= FLT(0.125)) {
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

void func_us_801758C8(Entity* self) {
    static s32 D_us_801785B8; // x (ps)
    static s32 D_us_801785BC; // y (ps)
    static s32 D_us_801785C0; // z (ps)
    static s32 D_us_801785C4; // x (ps)
    static s32 D_us_801785C8; // y (ps)
    static s32 D_us_801785CC; // z (ps)
    static s32 D_us_801785D0;
    static s32 D_us_801785D4;
    static s32 D_us_801785D8;
    static s32 D_us_801785DC;
    static s32 D_us_801785E0; // distance
    static s32 D_us_801785E4;
    static s32 D_us_801785E8;

    Primitive* next;
    s32 i;
    Primitive* prim;
    Primitive* last;
    s32 x, y, z;
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
        D_us_801785C0 = FLT(-0.75);
        g_api.PlaySfx(SFX_ANIME_SWORD_A);
        self->step++;
        // fallthrough

    case 2:
        D_us_801785C4 = D_us_801785B8 - D_us_80170080.vx;
        D_us_801785C8 = D_us_801785BC - D_us_80170080.vy;
        D_us_801785CC = D_us_801785C0 - D_us_80170080.vz;
        self->ext.swordFamiliar.unk84 =
            ratan2(D_us_801785C8, D_us_801785C4) & 0xFFF;

        self->ext.swordFamiliar.unk86 =
            StepAngleTowards(self->ext.swordFamiliar.unk84,
                             self->ext.swordFamiliar.unk88, 0x180);
        self->ext.swordFamiliar.unk88 = self->ext.swordFamiliar.unk86;
        D_us_801785D4 = FLT_TO_I(rcos(self->ext.swordFamiliar.unk86) << 7);
        D_us_801785D8 = FLT_TO_I(rsin(self->ext.swordFamiliar.unk86) << 7);

        D_us_80170078.vz = self->ext.swordFamiliar.unk86 - FLT(0.25);
        D_us_801785C4 = abs(D_us_801785C4);
        D_us_801785C8 = abs(D_us_801785C8);

        D_us_801785D0 = MAX(D_us_801785C4, D_us_801785C8);

        self->ext.swordFamiliar.currentX =
            ratan2(D_us_801785CC, D_us_801785D0) & 0xFFF;
        self->ext.swordFamiliar.unk8c =
            StepAngleTowards(self->ext.swordFamiliar.currentX,
                             self->ext.swordFamiliar.targetX, 0x40);

        self->ext.swordFamiliar.targetX = self->ext.swordFamiliar.unk8c;

        D_us_801785DC = FLT_TO_I(rsin(self->ext.swordFamiliar.unk8c) << 7);

        D_us_80170078.vx = self->ext.swordFamiliar.unk8c;
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
        D_us_80178B74 = false;
        D_us_80170078.vx = self->ext.swordFamiliar.targetX = 0;
        D_us_80170078.vz = FLT(0);
        self->ext.swordFamiliar.unk88 = FIX(1.0 / 64.0);
        g_api.PlaySfx(SFX_ANIME_SWORD_A);
        self->step++;
        // fallthrough

    case 4:
        D_us_80170080.vy += FIX(1.0 / 256.0);
        if (D_us_80170080.vy >= 0) {
            D_us_80170080.vy = 0;
            D_us_801785E4 = 0;
            g_api.PlaySfx(D_us_80170090[4]);
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
        D_us_80170078.vz = self->ext.swordFamiliar.unk88 - FLT(0.25);
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
        D_us_80170078.vz = self->ext.swordFamiliar.unk88 - FLT(0.25);
        if (self->ext.swordFamiliar.unk88 == FLT(0.75)) {
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
        PCOL(next) = 0x80;
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
            D_us_80178B74 = true;
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
    static s32 D_us_80178618;

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

        self->ext.swordFamiliar.unk86 =
            StepAngleTowards(self->ext.swordFamiliar.unk84,
                             self->ext.swordFamiliar.unk88, 0x180);
        self->ext.swordFamiliar.unk88 = self->ext.swordFamiliar.unk86;
        D_us_80178608 = FLT_TO_I(rcos(self->ext.swordFamiliar.unk86) << 8);
        D_us_8017860C = FLT_TO_I(rsin(self->ext.swordFamiliar.unk86) << 8);
        D_us_80170078.vz = self->ext.swordFamiliar.unk86 - FLT(0.25);

        D_us_801785F8 = abs(D_us_801785F8);
        D_us_801785FC = abs(D_us_801785FC);

        D_us_80178604 = MAX(D_us_801785F8, D_us_801785FC);

        self->ext.swordFamiliar.currentX =
            ratan2(D_us_80178600, D_us_80178604) & 0xFFF;

        self->ext.swordFamiliar.unk8c =
            StepAngleTowards(self->ext.swordFamiliar.currentX,
                             self->ext.swordFamiliar.targetX, 0x40);
        self->ext.swordFamiliar.targetX = self->ext.swordFamiliar.unk8c;

        D_us_80178610 = FLT_TO_I(rsin(self->ext.swordFamiliar.unk8c) << 8);

        D_us_80170078.vx = self->ext.swordFamiliar.unk8c;

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
                self->ext.swordFamiliar.unk88 = FLT(0.625);
                self->ext.swordFamiliar.targetX = 0;
                g_api.PlaySfx(SFX_ANIME_SWORD_A);
            }
            self->step++;
        }
        break;

    case 4:
        if ((g_Status.relics[RELIC_SWORD_CARD] & RELIC_FLAG_FOUND) &&
            (g_Status.relics[RELIC_SWORD_CARD] & RELIC_FLAG_ACTIVE)) {
            g_Status.relics[RELIC_SWORD_CARD] = RELIC_FLAG_FOUND;
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

void func_us_80176664(void) {}

void func_us_8017666C(void) {}

void func_us_80176674(Entity* self) {
    static s32 D_us_8017861C; // x
    static s32 D_us_80178620; // y
    static s32 D_us_80178624; // x
    static s32 D_us_80178628; // y
    static s32 D_us_8017862C; // z
    static s32 D_us_80178630;
    static s32 D_us_80178634;
    static s32 D_us_80178638; // (ps)

    s32 params;
    s32 x, y;

    CheckSwordLevel(self);

    D_us_80178638 += FLT(1.0 / 256.0);
    D_us_80178638 &= 0xFFF;

    D_us_80178624 = PLAYER.facingLeft ? FIX(-24) : FIX(24);
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
        self->ext.swordFamiliar.unk86 = StepAngleTowards(
            self->ext.swordFamiliar.unk84, self->ext.swordFamiliar.unk88, 8);
    } else {
        self->ext.swordFamiliar.unk86 =
            StepAngleTowards(FLT(0.25), self->ext.swordFamiliar.unk88, 8);
    }

    self->ext.swordFamiliar.unk88 = self->ext.swordFamiliar.unk86;
    D_us_80170078.vz = self->ext.swordFamiliar.unk86 - FLT(0.25);

    D_us_8017862C = -D_us_80170080.vz;
    D_us_80178624 = abs(D_us_80178624) << 5;
    D_us_80178628 = abs(D_us_80178628) << 5;
    D_us_80178630 = MAX(D_us_80178624, D_us_80178628);

    self->ext.swordFamiliar.currentX =
        ratan2(D_us_8017862C, D_us_80178630) & 0xFFF;
    self->ext.swordFamiliar.unk8c =
        StepAngleTowards(self->ext.swordFamiliar.currentX,
                         self->ext.swordFamiliar.targetX, 0x20);

    self->ext.swordFamiliar.targetX = self->ext.swordFamiliar.unk8c;
    D_us_80170080.vz += FLT_TO_I(rsin(self->ext.swordFamiliar.unk8c) * 96);
    D_us_80170078.vx = self->ext.swordFamiliar.unk8c;

    switch (self->step) {
    case 0:
        func_us_80172940(self);
        if (g_CastleFlags[SWORD_FAMILIAR] == 1 ||
            g_CastleFlags[SWORD_FAMILIAR] == 2) {
            g_CastleFlags[SWORD_FAMILIAR] = 3;
        }
        break;

    case 1:
        if (IsMovementAllowed(1) || CheckAllEntitiesValid() ||
            D_us_80178B80 == true || g_CutsceneHasControl ||
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
#ifdef VERSION_PSP
#define params 0x4F9
#else
#define params 0x4FB
#endif
        if (s_SwordStats.unk8 == 1) {
            CreateEventEntity(self, SWORD_UNK_DD, params);
        } else if (g_CastleFlags[SWORD_FAMILIAR] == 3) {
            CreateEventEntity(self, SWORD_UNK_DD, params + 3);
            g_CastleFlags[SWORD_FAMILIAR] = 4;
        } else if (s_SwordStats.level < 50) {
            CreateEventEntity(self, SWORD_UNK_DD, params + 1);
        } else {
            CreateEventEntity(self, SWORD_UNK_DD, params + 4);
        }
#undef params
        self->step++;
        break;

    case 3:
        if (g_PlaySfxStep == 99) {
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

void func_us_80176BF0(void) {}

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
            prim->priority = D_us_8017865C[4];
            prim->drawMode &= ~DRAW_HIDE;

            LOW(prim->x2) = LOW(prim->x0);
            LOW(prim->x3) = LOW(prim->x1);
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

    D_us_80178B78 = false;
}

void func_us_80176F28(Entity* self) {
    static Primitive* D_us_8017863C;
    STATIC_PAD_BSS(4);
    static s32 D_us_80178644;
    static s32 D_us_80178648;

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
        if (D_us_80178B7C) {
            for (i = 0; i < 4; i++) {
                D_us_8017863C->priority = D_us_80178670[i][4];
                D_us_8017863C->drawMode &= ~DRAW_HIDE;
                LOW(D_us_8017863C->x0) = D_us_80178670[i][0];
                LOW(D_us_8017863C->x1) = D_us_80178670[i][1];
                LOW(D_us_8017863C->x2) = D_us_80178670[i][2];
                LOW(D_us_8017863C->x3) = D_us_80178670[i][3];

                if (i < 2) {
                    D_us_8017863C->r0 = D_us_8017863C->g0 =
                        FLT_TO_I(rsin(D_us_80178644) << 5) + 32;
                    D_us_8017863C->b0 = FLT_TO_I(rsin(D_us_80178648) << 5) + 64;

                    D_us_8017863C->r1 = D_us_8017863C->g1 =
                        FLT_TO_I(rsin(D_us_80178644) << 5) + 96;
                    D_us_8017863C->b1 =
                        FLT_TO_I(rsin(D_us_80178648) << 5) + 192;

                    D_us_8017863C->r2 = D_us_8017863C->g2 =
                        FLT_TO_I(rcos(D_us_80178644) << 5) + 32;
                    D_us_8017863C->b2 = FLT_TO_I(rcos(D_us_80178648) << 5) + 64;

                    D_us_8017863C->r3 = D_us_8017863C->g3 =
                        FLT_TO_I(rcos(D_us_80178644) << 5) + 32;
                    D_us_8017863C->b3 = FLT_TO_I(rcos(D_us_80178648) << 5) + 64;
                } else {
                    D_us_8017863C->r0 = D_us_8017863C->g0 =
                        FLT_TO_I(rsin(D_us_80178644) << 5) + 96;
                    D_us_8017863C->b0 =
                        FLT_TO_I(rsin(D_us_80178648) << 5) + 192;

                    D_us_8017863C->r1 = D_us_8017863C->g1 =
                        FLT_TO_I(rsin(D_us_80178644) << 5) + 96;
                    D_us_8017863C->b1 =
                        FLT_TO_I(rsin(D_us_80178648) << 5) + 192;

                    D_us_8017863C->r2 = D_us_8017863C->g2 =
                        FLT_TO_I(rcos(D_us_80178644) << 5) + 32;
                    D_us_8017863C->b2 = FLT_TO_I(rcos(D_us_80178648) << 5) + 64;

                    D_us_8017863C->r3 = D_us_8017863C->g3 =
                        FLT_TO_I(rcos(D_us_80178644) << 5) + 32;
                    D_us_8017863C->b3 = FLT_TO_I(rcos(D_us_80178648) << 5) + 64;
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

    D_us_80178B7C = false;
}

void func_us_801773CC(Entity* self) {
    Entity* entity;

    switch (self->params) {
    case 0:
        D_us_80178B80 = true;
        if ((entity = SearchForEntityInRange(0, SWORD_UNK_DD)) != NULL &&
            entity->step < 5) {
            entity->step = 8;
        }
        break;

    case 15:
        D_us_80178B84 = true;
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
        flag = D_us_801700A0[s_SwordStats.level / 10].unk0;
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
            self->posX.i.hi = D_us_801786C0[1] & 0xFFFF;
            self->posY.i.hi = (D_us_801786C0[1] >> 16) & 0xFFFF;
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
        self->ext.swordFamiliar.unk7c++;
        if (self->ext.swordFamiliar.unk7c > 8) {
            DestroyEntity(self);
        }
        break;
    }
}

//#include "../shared_events.h"
//#include "../shared_globals.h"

#define E_UNK_DC 220
#define E_UNK_DF 223
// clang-format off
#define MAKE_EVENT(servant, roomX, roomY, camX, camY, check, delay, entity, params) \
    { 0, 0, servant, roomX, roomY, camX, camY, check, delay, entity, params, 1 }
#define NULL_EVENT \
    { 0, 0, -1, -1, -1, -1, -1, -1, -1, -1, 0, 0 }
ServantEvent g_Events[] = {
    NULL_EVENT,
    MAKE_EVENT(FAM_ACTIVE_BAT, 41, 50, 0, 4, FOR_CASTLE_FLAG(CAT_SPIKE_ROOM_LIT), 1, E_UNK_DF, 15),
    MAKE_EVENT(FAM_ACTIVE_GHOST, 41, 50, 0, 4, FOR_CASTLE_FLAG(CAT_SPIKE_ROOM_LIT), 1, E_UNK_DF, 15),
    MAKE_EVENT(FAM_ACTIVE_DEMON, 49, 20, 0, 4, CHECK_NONE, 0, E_UNK_DF, 0),
    MAKE_EVENT(FAM_ACTIVE_DEMON, 32, 40, 0, 4, FOR_CASTLE_FLAG(CHI_DEMON_SWITCH), 8, E_UNK_DF, 1),
    MAKE_EVENT(FAM_ACTIVE_DEMON, 16, 21, 0, 4, CHECK_NONE, 0, E_UNK_DF, 0),
    MAKE_EVENT(FAM_ACTIVE_DEMON, -31, 20, 0, 772, FOR_CASTLE_FLAG(RCHI_DEMON_SWITCH), 8, E_UNK_DF, 1),
    MAKE_EVENT(FAM_ACTIVE_DEMON, 41, 50, 0, 4, FOR_CASTLE_FLAG(CAT_SPIKE_ROOM_LIT), 1, E_UNK_DF, 15),
    MAKE_EVENT(FAM_ACTIVE_NOSE_DEMON, 49, 20, 0, 4, CHECK_NONE, 0, E_UNK_DF, 0),
    MAKE_EVENT(FAM_ACTIVE_NOSE_DEMON, 32, 40, 0, 4, FOR_CASTLE_FLAG(CHI_DEMON_SWITCH), 8, E_UNK_DF, 1),
    MAKE_EVENT(FAM_ACTIVE_NOSE_DEMON, 16, 21, 0, 4, CHECK_NONE, 0, E_UNK_DF, 0),
    MAKE_EVENT(FAM_ACTIVE_NOSE_DEMON, -31, 20, 0, 772, FOR_CASTLE_FLAG(RCHI_DEMON_SWITCH), 8, E_UNK_DF, 1),
    MAKE_EVENT(FAM_ACTIVE_NOSE_DEMON, 41, 50, 0, 4, FOR_CASTLE_FLAG(CAT_SPIKE_ROOM_LIT), 1, E_UNK_DF, 15),
    MAKE_EVENT(FAM_ACTIVE_FAERIE, 49, 20, 0, 4, CHECK_NONE, 0, E_UNK_DC, 0),
    MAKE_EVENT(FAM_ACTIVE_FAERIE, 16, 21, 0, 4, CHECK_NONE, 0, E_UNK_DC, 0),
    MAKE_EVENT(FAM_ACTIVE_FAERIE, 41, 50, 0, 4, FOR_CASTLE_FLAG(CAT_SPIKE_ROOM_LIT), 48, E_UNK_DC, 1),
    MAKE_EVENT(FAM_ACTIVE_FAERIE, 21, 22, 150, 4, FOR_RELIC(RELIC_FORM_OF_MIST), 96, E_UNK_DC, 2),
    MAKE_EVENT(FAM_ACTIVE_FAERIE, 60, 26, 0, 255, FOR_RELIC(RELIC_FORM_OF_MIST), 96, E_UNK_DC, 2),
    MAKE_EVENT(FAM_ACTIVE_FAERIE, 44, 18, 633, 772, FOR_RELIC(RELIC_FORM_OF_MIST), 96, E_UNK_DC, 2),
    MAKE_EVENT(FAM_ACTIVE_FAERIE, 10, 15, 790, 4, FOR_RELIC(RELIC_FORM_OF_MIST), 96, E_UNK_DC, 2),
    MAKE_EVENT(FAM_ACTIVE_FAERIE, 39, 37, 0, 516, FOR_CASTLE_FLAG(NO4_SECRET_FLOOR_OPEN), 96, E_UNK_DC, 3),
    MAKE_EVENT(FAM_ACTIVE_FAERIE, 36, 27, 0, 4, FOR_CASTLE_FLAG(NO4_SECRET_WALL_OPEN), 256, E_UNK_DC, 4),
    MAKE_EVENT(FAM_ACTIVE_FAERIE, 12, 32, 0, 516, FOR_CASTLE_FLAG(NZ0_SECRET_WALL_OPEN), 160, E_UNK_DC, 5),
    MAKE_EVENT(FAM_ACTIVE_FAERIE, 12, 32, 0, 511, FOR_CASTLE_FLAG(NZ0_SECRET_FLOOR_OPEN), 32, E_UNK_DC, 6),
    MAKE_EVENT(FAM_ACTIVE_FAERIE, 27, 21, 512, 260, FOR_CASTLE_FLAG(NO2_SECRET_WALL_OPEN), 64, E_UNK_DC, 7),
    MAKE_EVENT(FAM_ACTIVE_FAERIE, 49, 18, 0, 4, FOR_CASTLE_FLAG(LIB_BOOKSHELF_SECRET), 512, E_UNK_DC, 8),
    MAKE_EVENT(FAM_ACTIVE_FAERIE, 50, 11, 0, 4, FOR_CASTLE_FLAG(NZ1_UPPER_WALL_OPEN), 32, E_UNK_DC, 9),
    MAKE_EVENT(FAM_ACTIVE_FAERIE, 43, 10, 0, 255, FOR_CASTLE_FLAG(NZ1_LOWER_WALL_OPEN), 0x80, E_UNK_DC, 10),
    MAKE_EVENT(FAM_ACTIVE_FAERIE, 41, 50, 0, 4, FOR_CASTLE_FLAG(CAT_SPIKE_ROOM_LIT), 1, E_UNK_DC, 15),
    MAKE_EVENT(FAM_ACTIVE_YOUSEI, 49, 20, 0, 4, CHECK_NONE, 0, E_UNK_DC, 0),
    MAKE_EVENT(FAM_ACTIVE_YOUSEI, 16, 21, 0, 4, CHECK_NONE, 0, E_UNK_DC, 0),
    MAKE_EVENT(FAM_ACTIVE_YOUSEI, 41, 50, 0, 4, FOR_CASTLE_FLAG(CAT_SPIKE_ROOM_LIT), 48, E_UNK_DC, 1),
    MAKE_EVENT(FAM_ACTIVE_YOUSEI, 21, 22, 150, 4, FOR_RELIC(RELIC_FORM_OF_MIST), 96, E_UNK_DC, 2),
    MAKE_EVENT(FAM_ACTIVE_YOUSEI, 60, 26, 0, 255, FOR_RELIC(RELIC_FORM_OF_MIST), 96, E_UNK_DC, 2),
    MAKE_EVENT(FAM_ACTIVE_YOUSEI, 44, 18, 633, 772, FOR_RELIC(RELIC_FORM_OF_MIST), 96, E_UNK_DC, 2),
    MAKE_EVENT(FAM_ACTIVE_YOUSEI, 10, 15, 790, 4, FOR_RELIC(RELIC_FORM_OF_MIST), 96, E_UNK_DC, 2),
    MAKE_EVENT(FAM_ACTIVE_YOUSEI, 39, 37, 0, 516, FOR_CASTLE_FLAG(NO4_SECRET_FLOOR_OPEN), 96, E_UNK_DC, 3),
    MAKE_EVENT(FAM_ACTIVE_YOUSEI, 36, 27, 0, 4, FOR_CASTLE_FLAG(NO4_SECRET_WALL_OPEN), 256, E_UNK_DC, 4),
    MAKE_EVENT(FAM_ACTIVE_YOUSEI, 12, 32, 0, 516, FOR_CASTLE_FLAG(NZ0_SECRET_WALL_OPEN), 160, E_UNK_DC, 5),
    MAKE_EVENT(FAM_ACTIVE_YOUSEI, 12, 32, 0, 511, FOR_CASTLE_FLAG(NZ0_SECRET_FLOOR_OPEN), 32, E_UNK_DC, 6),
    MAKE_EVENT(FAM_ACTIVE_YOUSEI, 27, 21, 512, 260, FOR_CASTLE_FLAG(NO2_SECRET_WALL_OPEN), 64, E_UNK_DC, 7),
    MAKE_EVENT(FAM_ACTIVE_YOUSEI, 49, 18, 0, 4, FOR_CASTLE_FLAG(LIB_BOOKSHELF_SECRET), 512, E_UNK_DC, 8),
    MAKE_EVENT(FAM_ACTIVE_YOUSEI, 50, 11, 0, 4, FOR_CASTLE_FLAG(NZ1_UPPER_WALL_OPEN), 32, E_UNK_DC, 9),
    MAKE_EVENT(FAM_ACTIVE_YOUSEI, 43, 10, 0, 255, FOR_CASTLE_FLAG(NZ1_LOWER_WALL_OPEN), 128, E_UNK_DC, 10),
    MAKE_EVENT(FAM_ACTIVE_YOUSEI, 41, 50, 0, 4, FOR_CASTLE_FLAG(CAT_SPIKE_ROOM_LIT), 1, E_UNK_DC, 15),
    MAKE_EVENT(FAM_ACTIVE_SWORD, 49, 20, 0, 4, CHECK_NONE, 0, E_UNK_DC, 0),
    MAKE_EVENT(FAM_ACTIVE_SWORD, 16, 21, 0, 4, CHECK_NONE, 0, E_UNK_DC, 0),
    MAKE_EVENT(FAM_ACTIVE_SWORD, 41, 50, 0, 4, FOR_CASTLE_FLAG(CAT_SPIKE_ROOM_LIT), 1, E_UNK_DC, 15),
#if defined(VERSION_HD)
    { 0, 0, -1, 1, -1, -1, -1, -1, -1, -1, 0, 0, 0 }
#else
    NULL_EVENT
#endif
};

s32 g_PlaySfxStep = 99;
s16 g_EntityRanges[] = {5, 7, 32, 63};
ServantEvent* g_EventQueue = g_Events;
u32 g_CurrentServant = 0;
s32 g_CurrentRoomX = 0;
s32 g_CurrentRoomY = 0;