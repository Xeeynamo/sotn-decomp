// SPDX-License-Identifier: AGPL-3.0-or-later
#include "demon.h"
#include "../servant_private.h"

static s32 s_ServantId;
static FamiliarStats s_DemonStats;
static s16 D_us_801786A0[3][8];
static s32 D_us_801786D0;
static s32 D_us_801786D4;
static Entity* s_CurrentSwitch;
static bool D_us_801786DC;
static s32 s_LastTargetedEntityIndex;

#include "demon_data.h"

#ifdef VERSION_PSP
extern s16 D_092F2810[];
#define buggyPtr D_092F2810
#else
extern ServantEvent g_Events[];
#define buggyPtr ((s16*)g_Events)
#endif

static void SetAnimationFrame(Entity* self, s32 animationIndex) {
    if (self->anim != g_DemonAnimationFrames[animationIndex]) {
        self->anim = g_DemonAnimationFrames[animationIndex];
        self->pose = 0;
        self->poseTimer = 0;
    }
}

static Entity* FindValidTarget(Entity* self) {
    static bool s_TargetMatch[0x80];

    const int EntitySearchCount = 0x80;
    s32 foundIndex;
    s32 i;
    u32 found;
    Entity* entity;
    s32 distance;

    found = 0;
    entity = &g_Entities[STAGE_ENTITY_START];
    for (i = 0; i < EntitySearchCount; i++, entity++) {
        s_TargetMatch[i] = false;
        if (!entity->entityId) {
            continue;
        }
        if (entity->hitboxState == 0) {
            continue;
        }
        if (entity->flags & FLAG_UNK_00200000) {
            continue;
        }
        if (entity->posX.i.hi < -16) {
            continue;
        }
        if (entity->posX.i.hi > 272) {
            continue;
        }
        if (entity->posY.i.hi > 240) {
            continue;
        }
        if (entity->posY.i.hi < 0) {
            continue;
        }
        if (!g_DemonAbilityStats[s_DemonStats.level / 10].makeBadAttacks &&
            entity->hitboxState & 8) {
            continue;
        }

        if (abs(self->posX.i.hi - entity->posX.i.hi) >
                g_DemonAbilityStats[s_DemonStats.level / 10]
                    .maxEnemyAxisDelta ||
            abs(self->posY.i.hi - entity->posY.i.hi) >
                g_DemonAbilityStats[s_DemonStats.level / 10]
                    .maxEnemyAxisDelta) {
            continue;
        }
        if (self->facingLeft && self->posX.i.hi < entity->posX.i.hi) {
            continue;
        }
        if (!self->facingLeft && self->posX.i.hi > entity->posX.i.hi) {
            continue;
        }
        if (entity->hitPoints >= 0x7000) {
            continue;
        }

        if (entity->flags & FLAG_UNK_80000) {
            if (entity->hitPoints >=
                g_DemonAbilityStats[s_DemonStats.level / 10].minimumEnemyHp) {
                found++;
                s_TargetMatch[i] = true;
            }
        } else {
            entity->flags |= FLAG_UNK_80000;
            return entity;
        }
    }

    if (found > 0) {
        foundIndex = s_LastTargetedEntityIndex % EntitySearchCount;
        for (i = 0; i < EntitySearchCount; i++) {
            if (s_TargetMatch[foundIndex]) {
                entity = &g_Entities[STAGE_ENTITY_START + foundIndex];
                s_LastTargetedEntityIndex =
                    (foundIndex + 1) % EntitySearchCount;
                return entity;
            }
            foundIndex = (foundIndex + 1) % EntitySearchCount;
        }
    }

    return NULL;
}

#include "../check_entity_valid.h"

void unused_2DBC(Entity* self) {}

void ExecuteAbilityInitialize(Entity* self) {
    if (!self->ext.demon.abilityId) {
        switch (self->entityId) {
        case DEMON_MODE_DEFAULT_UPDATE:
        case DEMON_MODE_ADDITIONAL_INIT:
            self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA |
                          FLAG_UNK_20000;
            SetAnimationFrame(self, 0);

            self->ext.demon.randomMovementAngle = rand() % 0x1000;
            self->ext.demon.targetAngle = 0;
            self->ext.demon.defaultDistToTargetLoc = 8;
            self->ext.demon.angleStep = 0x20;
            self->step++;
            break;
        }
    } else {
        switch (self->entityId) {
        case DEMON_MODE_DEFAULT_UPDATE:
        case DEMON_MODE_BASIC_ATTACK:
        case DEMON_MODE_SPECIAL_ATTACK:
        case DEMON_MODE_PRESS_SWITCH:
        case DEMON_MODE_ADDITIONAL_INIT:
            self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA |
                          FLAG_UNK_20000;
            SetAnimationFrame(self, 0);
            self->step++;
            break;
        }
    }
    self->ext.demon.abilityId = self->entityId;
    D_us_801786D0 = 0;
}

void DestroyEntityPassthrough(Entity* self) { DestroyEntity(self); }

void func_us_80172EF8(Entity* self) {
    Primitive* prim;
    s32 posX, posY;

    self->posX.val = self->ext.factory.parent->posX.val;
    self->posY.val = self->ext.factory.parent->posY.val;
    switch (self->step) {
    case 0:
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 2);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags = FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_HAS_PRIMS;
        prim = &g_PrimBuf[self->primIndex];
        prim->tpage = 0x1A;
        prim->clut = 0x143;
        prim->priority = self->zPriority + 1;
        prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
        PCOL(prim) = 0xC0;

        prim = prim->next;
        prim->tpage = 0x1A;
        prim->clut = 0x143;
        prim->priority = self->zPriority + 1;
        prim->drawMode =
            DRAW_UNK_400 | DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
        prim->u0 = prim->u2 = 0;
        prim->u1 = prim->u3 = 0x3F;
        prim->v0 = prim->v1 = 0xC0;
        prim->v2 = prim->v3 = 0xFF;

        self->ext.factory.unk7C = 0;
        self->ext.factory.unk7E = 0;
        self->step++;
        break;

    case 1:
        self->ext.factory.unk7C++;
        self->ext.factory.unk7C &= 7;
        self->ext.factory.unk7E += 8;
        if (self->ext.factory.unk7E >= 0x100) {
            self->step++;
        }
        self->ext.factory.unk80++;
        break;

    case 2:
        self->ext.factory.unk7C++;
        self->ext.factory.unk7C &= 7;
        self->ext.factory.unk80++;
        if (self->ext.factory.unk80 > 50) {
            CreateEventEntity(self, DEMON_MODE_UNK_DB, 0);
            DestroyEntity(self);
            return;
        }
        break;
    }
    posX = self->posX.i.hi + (self->facingLeft ? 6 : -6);
    posY = self->posY.i.hi - 0xC;
    prim = &g_PrimBuf[self->primIndex];

    prim->u0 = prim->u1 = D_us_80171B74[self->ext.factory.unk7C][0];
    prim->u2 = prim->u3 = D_us_80171B74[self->ext.factory.unk7C][1];
    prim->v0 = prim->v2 = D_us_80171B74[self->ext.factory.unk7C][2];
    prim->v1 = prim->v3 = D_us_80171B74[self->ext.factory.unk7C][3];
    prim->x0 = prim->x2 = posX - self->ext.factory.unk7E * 8 / 256;
    prim->x1 = prim->x3 = posX + self->ext.factory.unk7E * 8 / 256;
    prim->y0 = prim->y1 = posY - self->ext.factory.unk7E * 32 / 256;
    prim->y2 = prim->y3 = posY;
    prim = prim->next;
    PCOL(prim) = self->ext.factory.unk7E / 2;
    prim->x0 = prim->x2 = posX - (0x100 - self->ext.factory.unk7E) * 32 / 256;
    prim->x1 = prim->x3 = posX + (0x100 - self->ext.factory.unk7E) * 32 / 256;
    prim->y0 = prim->y1 = posY - (0x100 - self->ext.factory.unk7E) * 32 / 256;
    prim->y2 = prim->y3 = posY + (0x100 - self->ext.factory.unk7E) * 32 / 256;
}

void func_us_80173348(Entity* self) {
    Primitive* prim;
    s32 posX, posY;

    self->posX.val = self->ext.factory.parent->posX.val;
    self->posY.val = self->ext.factory.parent->posY.val;

    switch (self->step) {
    case 0:
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 2);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }

        self->flags = FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_HAS_PRIMS;
        prim = &g_PrimBuf[self->primIndex];
        prim->tpage = 0x1A;
        prim->clut = 0x146;
        prim->priority = self->zPriority + 1;
        prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
        PCOL(prim) = 0x80;

        prim = prim->next;
        prim->tpage = 0x1A;
        prim->clut = 0x145;
        prim->priority = self->zPriority + 1;
        prim->drawMode =
            DRAW_UNK_400 | DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
        prim->u0 = prim->u2 = 0;
        prim->u1 = prim->u3 = 0x3F;
        prim->v0 = prim->v1 = 0xC0;
        prim->v2 = prim->v3 = 0xFF;

        self->ext.factory.unk7C = 0;
        self->ext.factory.unk7E = 0;
        self->step++;
        break;

    case 1:
        self->ext.factory.unk80++;
        if ((self->ext.factory.unk80 % 10) == 0 &&
            self->ext.factory.unk7C < 2) {
            self->ext.factory.unk7C++;
        }

        self->ext.factory.unk7E += 8;
        if (self->ext.factory.unk7E >= 0x100) {
            self->step++;
        }
        break;

    case 2:
        self->ext.factory.unk80++;
        if (self->ext.factory.unk80 > 0x32) {
            CreateEventEntity(self, DEMON_MODE_UNK_DC, 0);
            DestroyEntity(self);
            return;
        }
        break;
    }

    posX = self->posX.i.hi + (self->facingLeft ? 6 : -6);
    posY = self->posY.i.hi - 0xC;

    prim = &g_PrimBuf[self->primIndex];
    prim->u0 = prim->u2 = D_us_80171BF4[self->ext.factory.unk7C][0];
    prim->u1 = prim->u3 = D_us_80171BF4[self->ext.factory.unk7C][1];
    prim->v0 = prim->v1 = D_us_80171BF4[self->ext.factory.unk7C][2];
    prim->v2 = prim->v3 = D_us_80171BF4[self->ext.factory.unk7C][3];
    prim->x0 = prim->x2 = posX - self->ext.factory.unk7E * 16 / 256;
    prim->x1 = prim->x3 = posX + self->ext.factory.unk7E * 16 / 256;
    prim->y0 = prim->y1 = posY - self->ext.factory.unk7E * 16 / 256;
    prim->y2 = prim->y3 = posY + self->ext.factory.unk7E * 16 / 256;

    prim = prim->next;
    PCOL(prim) = self->ext.factory.unk7E / 2;
    prim->x0 = prim->x2 = posX - (256 - self->ext.factory.unk7E) * 32 / 256;
    prim->x1 = prim->x3 = posX + (256 - self->ext.factory.unk7E) * 32 / 256;
    prim->y0 = prim->y1 = posY - (256 - self->ext.factory.unk7E) * 32 / 256;
    prim->y2 = prim->y3 = posY + (256 - self->ext.factory.unk7E) * 32 / 256;
}

void func_us_801737F0(Entity* self) {
    Primitive* prim;
    s32 s, c;
    s32 dx, dy;
    s32 t;

    self->posX.val = self->ext.factory.parent->posX.val;
    self->posY.val = self->ext.factory.parent->posY.val;

    switch (self->step) {
    case 0:
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 2);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }

        self->flags = FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_HAS_PRIMS;

        prim = &g_PrimBuf[self->primIndex];
        prim->tpage = 0x1A;
        prim->clut = 0x147;
        prim->priority = self->zPriority + 1;
        prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
        prim->u0 = prim->u2 = 0xE0;
        prim->u1 = prim->u3 = 0xFF;
        prim->v0 = prim->v1 = 0x80;
        prim->v2 = prim->v3 = 0x9F;
        PCOL(prim) = 0x80;

        prim = prim->next;
        prim->tpage = 0x1A;
        prim->clut = 0x147;
        prim->priority = self->zPriority + 1;
        prim->drawMode =
            DRAW_UNK_400 | DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
        prim->u0 = prim->u2 = 0;
        prim->u1 = prim->u3 = 0x3F;
        prim->v0 = prim->v1 = 0xC0;
        prim->v2 = prim->v3 = 0xFF;

        self->ext.factory.unk7C = 0;
        self->ext.factory.unk7E = 0;
        self->ext.factory.unk82 = 0;

        self->step++;
        break;

    case 1:
        self->ext.factory.unk80++;
        if ((self->ext.factory.unk80 % 10) == 0 &&
            self->ext.factory.unk7C < 2) {
            self->ext.factory.unk7C++;
        }

        self->ext.factory.unk7E += 8;

        if (self->ext.factory.unk7E >= 0x100) {
            self->step++;
        }
        break;

    case 2:
        self->ext.factory.unk80++;

        if (self->ext.factory.unk80 > 50) {
            CreateEventEntity(self, DEMON_MODE_UNK_DD, 0);
            DestroyEntity(self);
            return;
        }
        break;
    }

    self->ext.factory.unk82 += 0x400;
    self->ext.factory.unk82 &= 0xFFF;

    s = rsin(self->ext.factory.unk82);
    c = rcos(self->ext.factory.unk82);

    dx = self->posX.i.hi + (self->facingLeft ? 6 : -6);
    dy = self->posY.i.hi - 0xC;
    prim = &g_PrimBuf[self->primIndex];

    t = (self->ext.factory.unk7E * 16) / 256;

    prim->x0 = dx + ((c * -t - s * -t) >> 12);
    prim->y0 = dy + ((s * -t + c * -t) >> 12);

    prim->x1 = dx + ((c * t - s * -t) >> 12);
    prim->y1 = dy + ((s * t + c * -t) >> 12);

    prim->x2 = dx + ((c * -t - s * t) >> 12);
    prim->y2 = dy + ((s * -t + c * t) >> 12);

    prim->x3 = dx + ((c * t - s * t) >> 12);
    prim->y3 = dy + ((s * t + c * t) >> 12);
    PCOL(prim) = (self->ext.factory.unk80 & 1) * 128;

    prim = prim->next;

    PCOL(prim) = self->ext.factory.unk7E / 2;

    prim->x0 = prim->x2 = dx - (256 - self->ext.factory.unk7E) * 32 / 256;
    prim->x1 = prim->x3 = dx + (256 - self->ext.factory.unk7E) * 32 / 256;
    prim->y0 = prim->y1 = dy - (256 - self->ext.factory.unk7E) * 32 / 256;
    prim->y2 = prim->y3 = dy + (256 - self->ext.factory.unk7E) * 32 / 256;
}

void func_us_80173D14(Entity* self) {
    Primitive* prim;
    s32 x0, x1, x2, x3;
    s32 y0, y1, y2, y3;
    s32 posX, posY;
    s32 s, c;
    s32 i;

    self->posX.val = self->ext.factory.parent->posX.val;
    self->posY.val = self->ext.factory.parent->posY.val;
    switch (self->step) {
    case 0:
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 4);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags = FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_HAS_PRIMS;
        if (self->facingLeft) {
            s = rsin(0xE00);
            c = rcos(0xE00);
        } else {
            s = rsin(0xA00);
            c = rcos(0xA00);
        }
        prim = &g_PrimBuf[self->primIndex];
        for (i = 0; i < 3; i++) {
            prim->tpage = 0x1A;
            prim->clut = 0x147;
            prim->priority = self->zPriority + 1;
            prim->drawMode =
                DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
            prim->u0 = prim->u2 = 0xB;
            prim->u1 = prim->u3 = 0x35;
            prim->v0 = prim->v1 = 0xCB;
            prim->v2 = prim->v3 = 0xF5;
            PCOL(prim) = 0x80;
            x0 = D_us_80171B44[i][0];
            y0 = D_us_80171B44[i][1];
            x1 = D_us_80171B44[i][2];
            y1 = D_us_80171B44[i][3];
            x2 = D_us_80171B44[i][4];
            y2 = D_us_80171B44[i][5];
            x3 = D_us_80171B44[i][6];
            y3 = D_us_80171B44[i][7];
            D_us_801786A0[i][0] = ((c * x0) - (s * y0)) >> 0xC;
            D_us_801786A0[i][1] = ((s * x0) + (c * y0)) >> 0xC;
            D_us_801786A0[i][2] = ((c * x1) - (s * y1)) >> 0xC;
            D_us_801786A0[i][3] = ((s * x1) + (c * y1)) >> 0xC;
            D_us_801786A0[i][4] = ((c * x2) - (s * y2)) >> 0xC;
            D_us_801786A0[i][5] = ((s * x2) + (c * y2)) >> 0xC;
            D_us_801786A0[i][6] = ((c * x3) - (s * y3)) >> 0xC;
            D_us_801786A0[i][7] = ((s * x3) + (c * y3)) >> 0xC;
            prim = prim->next;
        }
        prim->tpage = 0x1A;
        prim->clut = 0x147;
        prim->priority = self->zPriority + 1;
        prim->drawMode =
            DRAW_UNK_400 | DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
        prim->u0 = prim->u2 = 0;
        prim->u1 = prim->u3 = 0x3F;
        prim->v0 = prim->v1 = 0xC0;
        prim->v2 = prim->v3 = 0xFF;
        self->step++;
        break;

    case 1:
        self->ext.factory.unk7C++;
        self->ext.factory.unk7E += 8;
        if (self->ext.factory.unk7E >= 0x100) {
            self->step++;
        }
        break;

    case 2:
        self->ext.factory.unk7C++;
        if (self->ext.factory.unk7C > 50) {
            CreateEventEntity(self, DEMON_MODE_UNK_DE, 0);
            DestroyEntity(self);
            return;
        }
        break;
    }

    posX = self->posX.i.hi + (self->facingLeft ? 2 : -2);
    posY = self->posY.i.hi - 0xC;
    prim = &g_PrimBuf[self->primIndex];
    for (i = 0; i < 3; i++) {
        prim->x0 = posX + D_us_801786A0[i][0] * self->ext.factory.unk7E / 256;
        prim->y0 = posY + D_us_801786A0[i][1] * self->ext.factory.unk7E / 256;
        prim->x1 = posX + D_us_801786A0[i][2] * self->ext.factory.unk7E / 256;
        prim->y1 = posY + D_us_801786A0[i][3] * self->ext.factory.unk7E / 256;
        prim->x2 = posX + D_us_801786A0[i][4] * self->ext.factory.unk7E / 256;
        prim->y2 = posY + D_us_801786A0[i][5] * self->ext.factory.unk7E / 256;
        prim->x3 = posX + D_us_801786A0[i][6] * self->ext.factory.unk7E / 256;
        prim->y3 = posY + D_us_801786A0[i][7] * self->ext.factory.unk7E / 256;
        PCOL(prim) = ((self->ext.factory.unk7C & 1) * 64) + 0x40;
        prim = prim->next;
    }

    posX = self->posX.i.hi + (self->facingLeft ? 4 : -4);
    PCOL(prim) = self->ext.factory.unk7E / 2;
    prim->x0 = prim->x2 = posX - (0x100 - self->ext.factory.unk7E) * 32 / 256;
    prim->x1 = prim->x3 = posX + (0x100 - self->ext.factory.unk7E) * 32 / 256;
    prim->y0 = prim->y1 = posY - (0x100 - self->ext.factory.unk7E) * 32 / 256;
    prim->y2 = prim->y3 = posY + (0x100 - self->ext.factory.unk7E) * 32 / 256;
}

void OVL_EXPORT(ServantInit)(InitializeMode mode) {
    u16* src;
    u16* dst;
    RECT rect;
    s32 i;
    SpriteParts** spriteBanks;
    Entity* entity;

#ifdef VERSION_PC
    const int lenServant = LEN(g_ServantClut);
    const int lenDemon = LEN(g_DemonClut);
#else
    const int lenServant = 256;
    const int lenDemon = 80;
#endif

    s_ServantId = g_Servant;

    if (mode == MENU_SWITCH_SERVANT || mode == MENU_SAME_SERVANT) {
        ProcessEvent(NULL, true);
        if (mode == MENU_SAME_SERVANT) {
            return;
        }
    }

    dst = &g_Clut[1][CLUT_INDEX_SERVANT];
    src = g_ServantClut;
    for (i = 0; i < lenServant; i++) {
        *dst++ = *src++;
    }

    dst = &g_Clut[1][CLUT_INDEX_SERVANT_OVERWRITE];
    src = g_DemonClut;

    for (i = 0; i < lenDemon; i++) {
        *dst++ = *src++;
    }

    rect.x = 0;
    rect.w = 0x100;
    rect.h = 1;
    rect.y = 0xF4;

    dst = &g_Clut[1][CLUT_INDEX_SERVANT];
    LoadImage(&rect, (u_long*)dst);

    spriteBanks = g_api.o.spriteBanks;
    spriteBanks += 20;
    *spriteBanks = (SpriteParts*)g_DemonSpriteParts;

    entity = &g_Entities[SERVANT_ENTITY_INDEX];

    DestroyEntity(entity);
    entity->unk5A = 0x6C;
    entity->palette = PAL_SERVANT;
    entity->animSet = ANIMSET_OVL(20);
    entity->zPriority = PLAYER.zPriority - 2;
    entity->facingLeft = PLAYER.facingLeft;
    entity->params = 0;

    if (mode == MENU_SWITCH_SERVANT) {
#ifdef VERSION_PSP
        if ((D_8003C708.flags & LAYOUT_RECT_PARAMS_UNKNOWN_20) ||
            (D_8003C708.flags & LAYOUT_RECT_PARAMS_UNKNOWN_40)) {
#else
        if (LOW(D_8003C708.flags) &
            (LAYOUT_RECT_PARAMS_UNKNOWN_20 | LAYOUT_RECT_PARAMS_UNKNOWN_40)) {
#endif
            entity->entityId = DEMON_MODE_DEFAULT_UPDATE;
        } else {
            entity->entityId = DEMON_MODE_ADDITIONAL_INIT;
        }
        entity->posX.val = FIX(128);
        entity->posY.val = FIX(-32);
    } else {
        entity->entityId = DEMON_MODE_DEFAULT_UPDATE;
        if (D_8003C708.flags & LAYOUT_RECT_PARAMS_UNKNOWN_20) {
            if (ServantUnk0()) {
                entity->posX.val = FIX(192);
            } else {
                entity->posX.val = FIX(64);
            }
            entity->posY.val = FIX(160);
        } else {
            entity->posX.val =
                PLAYER.posX.val + (PLAYER.facingLeft ? FIX(24) : FIX(-24));
            entity->posY.val = PLAYER.posY.val + FIX(-32);
        }
    }

    D_us_801786D0 = 0;
    D_us_801786D4 = 0;
    g_api.GetServantStats(entity, 0, 0, &s_DemonStats);
}

void OVL_EXPORT(UpdateServantDefault)(Entity* self) {
    static s32 targetX;
    static s32 targetY;
    static s16 dx0;
    STATIC_PAD_BSS(2);
    static s16 dy0;
    STATIC_PAD_BSS(2);
    static s16 angle;
    STATIC_PAD_BSS(2);
    static s16 dAngle;
    STATIC_PAD_BSS(2);
    static s16 distance0;
    STATIC_PAD_BSS(2);
    static s16 xOffset;
    STATIC_PAD_BSS(2);

    static s32 dx1;
    static s32 dy1;
    static s32 distance1;

    s32 i;
    s32 rnd;

    g_api.GetServantStats(self, 0, 0, &s_DemonStats);
    if (D_us_801786D4) {
        self->zPriority = PLAYER.zPriority - 2;
    }

    if (D_8003C708.flags & FLAG_UNK_20) {
        switch (ServantUnk0()) {
        case 0:
            targetX = 0x40;
            break;

        case 1:
            targetX = 0xC0;
            break;

        case 2:
            targetX = (self->posX.i.hi > 0x80) ? 0xC0 : 0x40;
            break;
        }
        targetY = 0xA0;
    } else {
        xOffset = -0x18;
        if (PLAYER.facingLeft) {
            xOffset = -xOffset;
        }
        dx0 = PLAYER.posX.i.hi + xOffset;
        dy0 = PLAYER.posY.i.hi - 0x20;

        angle = self->ext.demon.randomMovementAngle;
        self->ext.demon.randomMovementAngle += 0x10;
        self->ext.demon.randomMovementAngle &= 0xFFF;
        distance0 = self->ext.demon.defaultDistToTargetLoc;

        targetX = dx0 + ((rcos(angle / 2) * distance0) >> 0xC);
        targetY = dy0 - ((rsin(angle) * (distance0 / 2)) >> 0xC);
    }
    switch (self->step) {
    case 0:
        ExecuteAbilityInitialize(self);
        break;

    case 1:
        if (D_8003C708.flags & FLAG_UNK_20) {
            if (PLAYER.posX.i.hi >= self->posX.i.hi) {
                self->facingLeft = false;
            } else {
                self->facingLeft = true;
            }
        } else {
            if (PLAYER.facingLeft != self->facingLeft) {
                if (abs(targetX - self->posX.i.hi) <= 0) {
                    self->facingLeft = PLAYER.facingLeft;
                } else if (!self->facingLeft && targetX < self->posX.i.hi) {
                    self->facingLeft = PLAYER.facingLeft;
                } else if (self->facingLeft && targetX > self->posX.i.hi) {
                    self->facingLeft = PLAYER.facingLeft;
                }
            } else if (
                !self->facingLeft && (self->posX.i.hi - targetX) > 0x28) {
                self->facingLeft = PLAYER.facingLeft ? false : true;
            } else if (self->facingLeft && (targetX - self->posX.i.hi) > 0x28) {
                self->facingLeft = PLAYER.facingLeft ? false : true;
            }
        }

        angle = CalculateAngleToEntity(self, targetX, targetY);
        dAngle = StepAngleTowards(
            angle, self->ext.demon.targetAngle, self->ext.demon.angleStep);
        self->ext.demon.targetAngle = dAngle;
        dx0 = targetX - self->posX.i.hi;
        dy0 = targetY - self->posY.i.hi;
        distance0 = SquareRoot12((dx0 * dx0 + dy0 * dy0) << 12) >> 12;
        if (distance0 < 40) {
            self->velocityY = -(rsin(dAngle) << 3);
            self->velocityX = rcos(dAngle) << 3;
            self->ext.demon.angleStep = 0x20;
        } else if (distance0 < 60) {
            self->velocityY = -(rsin(dAngle) << 4);
            self->velocityX = rcos(dAngle) << 4;
            self->ext.demon.angleStep = 0x40;
        } else if (distance0 < 100) {
            self->velocityY = -(rsin(dAngle) << 5);
            self->velocityX = rcos(dAngle) << 5;
            self->ext.demon.angleStep = 0x60;
        } else if (distance0 < 256) {
            self->velocityY = -(rsin(dAngle) << 6);
            self->velocityX = rcos(dAngle) << 6;
            self->ext.demon.angleStep = 0x80;
        } else {
            self->velocityX = (targetX - self->posX.i.hi) << 0xE;
            self->velocityY = (targetY - self->posY.i.hi) << 0xE;
            self->ext.demon.angleStep = 0x80;
        }
        if (self->velocityY > FIX(1.0)) {
            SetAnimationFrame(self, 10);
        } else if (distance0 < 60) {
            SetAnimationFrame(self, 0);
        } else if (distance0 > 100) {
            SetAnimationFrame(self, 11);
        }
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        if (!g_CutsceneHasControl) {
            dx1 = targetX - self->posX.i.hi;
            dy1 = targetY - self->posY.i.hi;

            distance1 = SquareRoot12((dx1 * dx1 + dy1 * dy1) << 12) >> 12;

            if (distance1 < 0x20) {
                self->ext.demon.abilityTimer++;
                if (self->ext.demon.abilityTimer >
                    g_DemonAbilityStats[s_DemonStats.level / 10].timer) {
                    self->ext.demon.abilityTimer = 0;

                    if (self->ext.demon.target = FindValidTarget(self)) {
                        if (rand() % 0x100 <=
                            g_DemonAttackSelector[s_DemonStats.level / 10][0]) {
                            self->entityId = DEMON_MODE_BASIC_ATTACK;
                        } else {
                            self->entityId = DEMON_MODE_SPECIAL_ATTACK;
                        }
                        self->step = 0;
                    }
                }
            }
            // This is likely dead code and not actually valid as it's doing
            // some weird stuff with g_Events that doesn't make any sense.  And
            // it only does it with the N Demon, which was stripped out anyway
            if (s_ServantId == FAM_ACTIVE_NOSE_DEMON) {
                if (!g_CutsceneHasControl && !IsMovementAllowed(1) &&
                    !CheckAllEntitiesValid() &&
                    !(D_8003C708.flags & FLAG_UNK_20) && !D_us_801786D0) {
                    if (self->ext.demon.unkCounter <= 18000) {
                        self->ext.demon.unkCounter++;
                    }
                } else {
                    self->ext.demon.unkCounter = 0;
                }
                if (self->ext.demon.unkCounter == 18000) {
                    rnd = rand() % 0x100;
                    for (i = 0; true; i++) {
                        if (rnd <= buggyPtr[i * 2]) {
                            CreateEventEntity(self, DEMON_EVENT_SFX_PASSTHROUGH,
                                              buggyPtr[i * 2 + 1]);
                            break;
                        }
                    }
                }
            }
            if (D_us_801786D0 == 2) {
                s_CurrentSwitch = 0;
                CreateEventEntity(self, DEMON_SUBENTITY_SWITCH, 0);
                self->entityId = DEMON_MODE_PRESS_SWITCH;
                self->step = 0;
            }
        }
        break;
    }
    ProcessEvent(self, false);
    unused_2DBC(self);
    ServantUpdateAnim(self, g_DemonFrameProps, g_DemonAnimationFrames);
}

void UpdateServantBasicAttack(Entity* self) {
    static s32 targetX;
    static s32 targetY;
    static s32 dx;
    static s32 dy;
    static u32 animStatus;
    static s32 targetFacingLeft;
    static s32 rnd;

    if (D_us_801786D4) {
        self->zPriority = PLAYER.zPriority - 2;
    }
    switch (self->step) {
    case 0:
        ExecuteAbilityInitialize(self);
        break;

    case 1:
        targetFacingLeft = self->ext.demon.target->facingLeft;
        self->step++;
        /* fallthrough */
    case 2:
        if (!CheckEntityValid(self->ext.demon.target) &&
            (self->ext.demon.target = FindValidTarget(self)) == NULL) {
            self->entityId = DEMON_MODE_DEFAULT_UPDATE;
            self->step = 0;
        } else {
            targetX = self->ext.demon.target->posX.val;
            targetX += targetFacingLeft ? FIX(32) : FIX(-32);
            targetY = self->ext.demon.target->posY.val;

            self->velocityX = (targetX - self->posX.val) >> 3;
            self->velocityY = (targetY - self->posY.val) >> 3;

            self->facingLeft = self->velocityX > 0 ? false : true;

            self->posX.val += self->velocityX;
            self->posY.val += self->velocityY;
            dx = abs(targetX - self->posX.val);
            dy = abs(targetY - self->posY.val);
            if (dx < FIX(8) && dy < FIX(1)) {
                self->facingLeft = targetFacingLeft;
                self->step++;
            }
        }
        break;

    case 3:
        rnd = rand() % 2;
        SetAnimationFrame(self, rnd ? 1 : 3);

        g_api.GetServantStats(
            self, rnd ? FAM_ABILITY_DEMON_UNK21 : FAM_ABILITY_DEMON_UNK22, 1,
            &s_DemonStats);

        rnd = rand() % 8;
        switch (rnd) {
        case 0:
            g_api.PlaySfx(g_DemonSfxMap[0]);
            break;

        case 1:
            g_api.PlaySfx(g_DemonSfxMap[1]);
            break;

        case 2:
            g_api.PlaySfx(g_DemonSfxMap[2]);
            break;
        }
        self->step++;
        break;

    case 4:
        if (animStatus == -2) {
            self->ext.demon.abilityTimer = 0;
            self->step++;
        }
        break;

    case 5:
        self->velocityX = self->facingLeft ? FIX(0.125) : FIX(-0.125);
        self->velocityY = FIX(-0.25);
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        self->ext.demon.abilityTimer++;
        if (self->ext.demon.abilityTimer > 30) {
            self->step++;
        }
        break;

    case 6:
        if (g_CutsceneHasControl ||
            (self->ext.demon.target = FindValidTarget(self)) == NULL) {
            self->entityId = DEMON_MODE_DEFAULT_UPDATE;
            self->step = 0;
            break;
        }
        if ((rand() % 0x100) <=
            g_DemonAttackSelector[s_DemonStats.level / 10][0]) {
            self->step = 1;
        } else {
            self->entityId = DEMON_MODE_SPECIAL_ATTACK;
            self->step = 0;
        }
        break;
    }
    animStatus =
        ServantUpdateAnim(self, g_DemonFrameProps, g_DemonAnimationFrames);
}

void UpdateServantSpecialAttack(Entity* self) {
    static s32 targetX;
    static s32 targetY;
    static s32 dx;
    static s32 dy;
    static s32 animStatus;
    static s32 targetFacingLeft;
    static s32 attackIdx;

    s32 i;

    if (D_us_801786D4) {
        self->zPriority = PLAYER.zPriority - 2;
    }
    switch (self->step) {
    case 0:
        ExecuteAbilityInitialize(self);
        break;

    case 1:
        targetFacingLeft = self->ext.demon.target->facingLeft;
        self->step++;
        /* fallthrough */
    case 2:
        if (!CheckEntityValid(self->ext.demon.target) &&
            (self->ext.demon.target = FindValidTarget(self)) == NULL) {
            self->entityId = DEMON_MODE_DEFAULT_UPDATE;
            self->step = 0;
        } else {
            targetX = self->ext.demon.target->posX.val;
            targetX += targetFacingLeft ? FIX(32) : FIX(-32);

            targetY = self->ext.demon.target->posY.val;
            self->velocityX = (targetX - self->posX.val) >> 3;
            self->velocityY = (targetY - self->posY.val) >> 3;
            self->facingLeft = self->velocityX > 0 ? 0 : 1;

            self->posX.val += self->velocityX;
            self->posY.val += self->velocityY;

            dx = abs(targetX - self->posX.val);
            dy = abs(targetY - self->posY.val);
            if (dx < FIX(8) && dy < FIX(1)) {
                self->facingLeft = targetFacingLeft;
                self->step++;
            }
        }
        break;

    case 3:
        attackIdx = rand() % 256;
        for (i = 1; i < 6; i++) {
            if (attackIdx <=
                g_DemonAttackSelector[s_DemonStats.level / 10][i]) {
                attackIdx = i - 1;
                break;
            }
        }

        SetAnimationFrame(
            self, g_DemonAttackIdSfxLookup[attackIdx].animationIndex);
        g_api.PlaySfx(
            g_DemonSfxMap[g_DemonAttackIdSfxLookup[attackIdx].sfxIndex]);

        g_api.GetServantStats(
            self, g_DemonAttackIdSfxLookup[attackIdx].abilityId, 1,
            &s_DemonStats);
        // This is for the different Attack types.  Param selects update
        // function from passthrough array
        CreateEventEntity(self, DEMON_SPECIAL_ATTACK_UPDATE, attackIdx);
        self->step++;
        break;

    case 4:
        if (animStatus == -2) {
            self->ext.demon.abilityTimer = 0;
            self->step++;
        }
        break;

    case 5:
        self->velocityX = self->facingLeft ? FIX(0.125) : FIX(-0.125);
        self->velocityY = FIX(-0.25);
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;

        self->ext.demon.abilityTimer++;

        if (self->ext.demon.abilityTimer > 30) {
            self->entityId = DEMON_MODE_DEFAULT_UPDATE;
            self->step = 0;
        }
        break;
    }
    animStatus =
        ServantUpdateAnim(self, g_DemonFrameProps, g_DemonAnimationFrames);
}

void unused_5800(void) {}

void unused_5808(void) {}

void UpdateServantPressSwitch(Entity* self) {
    static s32 targetX;
    static s32 targetY;
    STATIC_PAD_BSS(4);
    static ServantSfxEventDesc* sfxEvent;
    static s16 sfxFlag;
    STATIC_PAD_BSS(2);

    Entity* entity;
    s32 dx, dy;

    if (D_us_801786D4) {
        self->zPriority = PLAYER.zPriority - 2;
    }
    if (s_CurrentSwitch) {
        targetX = s_CurrentSwitch->posX.val;
        targetY = s_CurrentSwitch->posY.val;
        self->ext.demon.switchPressVelocityOffset += 0x40;
        self->ext.demon.switchPressVelocityOffset &= 0xFFF;
        targetY =
            (rsin((s32)self->ext.demon.switchPressVelocityOffset) << 3 << 4) +
            targetY;

        self->velocityX = (targetX - self->posX.val) >> 5;
        self->velocityY = (targetY - self->posY.val) >> 5;
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
    }
    switch (self->step) {
    case 0:
        ExecuteAbilityInitialize(self);
        break;

    case 1:
        self->facingLeft = (self->velocityX > 0) ? false : true;

        dx = (targetX - self->posX.val) >> 0x10;
        dy = (targetY - self->posY.val) >> 0x10;
        if ((SquareRoot12((dx * dx + dy * dy) << 12) >> 12) < 0x10) {
            if (g_StageId < STAGE_RNO0 || g_StageId > STAGE_RNZ1_DEMO - 1) {
                self->facingLeft = false;
                sfxEvent = (ServantSfxEventDesc*)g_SfxDemonSwitchRandomizer[1];
            } else {
                self->facingLeft = true;
                sfxEvent = (ServantSfxEventDesc*)g_SfxDemonSwitchRandomizer[3];
            }
            self->step++;
        }
        break;

    case 2:
        sfxFlag = ((s16*)sfxEvent)[0];
#ifndef VERSION_PSP
        pauseAllowed = false;
#endif
        self->step++;
        // fallthrough
    case 3:
        if (sfxFlag < 0) {
            if (g_PlaySfxStep > 4) {
                SetAnimationFrame(self, sfxEvent->animIndex);
#ifndef VERSION_PSP
                pauseAllowed = true;
#endif
                self->step++;
            }
        } else {
            if (g_PlaySfxStep == 4 || g_PlaySfxStep >= 99) {
                sfxFlag--;
            }
            if (sfxFlag < 0) {
                SetAnimationFrame(self, sfxEvent->animIndex);
                if (sfxEvent->sfxId != 0 &&
                    !SearchForEntityInRange(0, DEMON_EVENT_SFX_PASSTHROUGH)) {
                    CreateEventEntity(
                        self, DEMON_EVENT_SFX_PASSTHROUGH, sfxEvent->sfxId);
                }
                sfxEvent++;
                sfxFlag = ((s16*)sfxEvent)[0];
            }
        }
        break;

    case 4:
        self->ext.demon.attackEndCounter++;
        if (self->ext.demon.attackEndCounter > 120) {
            self->entityId = DEMON_MODE_DEFAULT_UPDATE;
            self->step = 0;
        }
        break;
    }

    if (s_CurrentSwitch && !s_CurrentSwitch->entityId) {
#ifndef VERSION_PSP
        pauseAllowed = true;
#endif
        self->entityId = DEMON_MODE_DEFAULT_UPDATE;
        self->step = 0;

        if ((entity = SearchForEntityInRange(0, DEMON_EVENT_SFX_PASSTHROUGH)) !=
                NULL &&
            entity->step < 5) {
            entity->step = 7;
        }
    }
    if (self->anim == g_DemonAnimationFrames[7] && self->pose == 8) {
        D_us_801786DC = true;
    }
    ServantUpdateAnim(self, NULL, g_DemonAnimationFrames);
}

void UpdateSubentitySwitch(Entity* self) {
    switch (self->step) {
    case 0:
        self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA;
        s_CurrentSwitch = self;
        D_us_801786DC = false;

        if (g_StageId < STAGE_RNO0 || g_StageId > STAGE_RNZ1_DEMO - 1) {
            self->posX.i.hi = 200;
            self->posY.i.hi = 36;
            self->facingLeft = false;
        } else {
            self->posX.i.hi = 56;
            self->posY.i.hi = 196;
            self->facingLeft = true;
        }

        self->step++;
        break;

    case 1:
        if (D_us_801786DC) {
            self->hitboxOffX = 0x18;
            self->hitboxOffY = 4;
            self->hitboxWidth = 2;
            self->hitboxHeight = 2;
            self->attack = 0;
            self->attackElement = ELEMENT_HIT;
            self->hitboxState = 2;
            self->nFramesInvincibility = 0;
            self->stunFrames = 0;
            self->hitEffect = 7;
            self->entityRoomIndex = 0;

            g_api.func_80118894(self);

            self->step++;
        }
        break;

    case 2:
        break;
    }
}

void UpdateServantAdditionalInit(Entity* self) {
    static s32 targetX;
    static s32 targetY;
    static s16 dx0;
    STATIC_PAD_BSS(2);
    static s16 dy0;
    STATIC_PAD_BSS(2);
    static s16 angle;
    STATIC_PAD_BSS(2);
    static s16 dAngle;
    STATIC_PAD_BSS(2);
    static s16 distance0;
    STATIC_PAD_BSS(2);
    static s16 xOffset;
    STATIC_PAD_BSS(2);

    static s32 dx1;
    static s32 dy1;
    static s32 distance1;
    static ServantSfxEventDesc* sfxEvent;
    static s16 sfxFlag;
    STATIC_PAD_BSS(2);

    s16 rnd;
    s32 i;

    g_api.GetServantStats(self, 0, 0, &s_DemonStats);
    if (D_us_801786D4) {
        self->zPriority = PLAYER.zPriority - 2;
    }

    xOffset = -0x18;
    if (!PLAYER.facingLeft) {
        xOffset = -xOffset;
    }

    dx0 = PLAYER.posX.i.hi + xOffset;
    dy0 = PLAYER.posY.i.hi - 0x20;
    angle = self->ext.demon.randomMovementAngle;
    self->ext.demon.randomMovementAngle += 0x10;
    self->ext.demon.randomMovementAngle &= 0xFFF;
    distance0 = self->ext.demon.defaultDistToTargetLoc;

    targetX = dx0 + ((rcos(angle / 2) * distance0) >> 12);
    targetY = dy0 - ((rsin(angle) * (distance0 / 2)) >> 12);

    angle = CalculateAngleToEntity(self, targetX, targetY);
    dAngle = StepAngleTowards(
        angle, self->ext.demon.targetAngle, self->ext.demon.angleStep);
    self->ext.demon.targetAngle = dAngle;
    dx0 = targetX - self->posX.i.hi;
    dy0 = targetY - self->posY.i.hi;
    distance0 = SquareRoot12((dx0 * dx0 + dy0 * dy0) << 12) >> 12;
    if (distance0 < 60) {
        self->velocityY = -(rsin(dAngle) << 3);
        self->velocityX = (rcos(dAngle) << 3);
        self->ext.demon.angleStep = 0x40;
    } else if (distance0 < 100) {
        self->velocityY = -(rsin(dAngle) << 4);
        self->velocityX = (rcos(dAngle) << 4);
        self->ext.demon.angleStep = 0x60;
    } else {
        self->velocityY = -(rsin(dAngle) << 5);
        self->velocityX = (rcos(dAngle) << 5);
        self->ext.demon.angleStep = 0x80;
    }
    self->posX.val += self->velocityX;
    self->posY.val += self->velocityY;
    switch (self->step) {
    case 0:
        ExecuteAbilityInitialize(self);
        break;

    case 1:
        if (PLAYER.facingLeft != self->facingLeft) {
            if (abs(targetX - self->posX.i.hi) <= 0) {
                self->facingLeft = PLAYER.facingLeft;
            } else if (!self->facingLeft && targetX < self->posX.i.hi) {
                self->facingLeft = PLAYER.facingLeft;
            } else if (self->facingLeft && targetX > self->posX.i.hi) {
                self->facingLeft = PLAYER.facingLeft;
            }
        } else if (!self->facingLeft && (self->posX.i.hi - targetX) > 40) {
            self->facingLeft = PLAYER.facingLeft ? false : true;
        } else if (self->facingLeft && (targetX - self->posX.i.hi) > 40) {
            self->facingLeft = PLAYER.facingLeft ? false : true;
        }
        if (self->velocityY > FIX(1.0)) {
            SetAnimationFrame(self, 10);
        } else if (distance0 < 60) {
            SetAnimationFrame(self, 0);
        } else if (distance0 > 100) {
            SetAnimationFrame(self, 11);
        }
        if (IsMovementAllowed(1) || CheckAllEntitiesValid() ||
            D_us_801786D0 == 1 || g_CutsceneHasControl ||
            g_unkGraphicsStruct.D_800973FC) {
            SetAnimationFrame(self, 0);
            self->entityId = DEMON_MODE_DEFAULT_UPDATE;
            self->step = 0;
            return;
        }
        dx1 = targetX - self->posX.i.hi;
        dy1 = targetY - self->posY.i.hi;
        distance1 = SquareRoot12((dx1 * dx1 + dy1 * dy1) << 12) >> 12;
        if (distance1 < 0x20) {
            self->facingLeft = PLAYER.facingLeft ? false : true;
            self->step++;
        }
        break;

    case 2:
        rnd = rand() % 0x100;
        if (s_DemonStats.unk8 == true) {
            for (i = 0; true; i++) {
                if (rnd <= g_SfxDemonIntroPrevSummoned[i * 2]) {
                    sfxEvent = (ServantSfxEventDesc*)
                        g_SfxDemonIntroPrevSummoned[i * 2 + 1];
                    break;
                }
            }
        } else {
            for (i = 0; true; i++) {
                if (rnd <= g_SfxDemonIntroNewSummoned[i * 2]) {
                    sfxEvent = (ServantSfxEventDesc*)
                        g_SfxDemonIntroNewSummoned[i * 2 + 1];
                    break;
                }
            }
        }
        sfxFlag = ((s16*)sfxEvent)[0];
        pauseAllowed = false;
        self->step++;
        break;

    case 3:
        if (PLAYER.posX.i.hi >= self->posX.i.hi) {
            self->facingLeft = false;
        } else {
            self->facingLeft = true;
        }
        if (sfxFlag < 0) {
            if (g_PlaySfxStep > 4) {
                SetAnimationFrame(self, sfxEvent->animIndex);
                self->step++;
            }
            break;
        }
        if (g_PlaySfxStep == 4 || g_PlaySfxStep >= 99) {
            sfxFlag--;
        }
        if (sfxFlag < 0) {
            SetAnimationFrame(self, sfxEvent->animIndex);
            if (sfxEvent->sfxId != 0 &&
                (SearchForEntityInRange(0, DEMON_EVENT_SFX_PASSTHROUGH) ==
                 NULL)) {
                CreateEventEntity(
                    self, DEMON_EVENT_SFX_PASSTHROUGH, sfxEvent->sfxId);
            }
            sfxEvent++;
            sfxFlag = ((s16*)sfxEvent)[0];
        }
        break;

    case 4:
        if (g_PlaySfxStep == 99) {
            self->step++;
        }
        break;

    case 5:
        SetAnimationFrame(self, 0);
        pauseAllowed = true;
        self->entityId = DEMON_MODE_DEFAULT_UPDATE;
        self->step = 0;
        break;
    }
    ProcessEvent(self, false);
    ServantUpdateAnim(self, g_DemonFrameProps, g_DemonAnimationFrames);
}

void UpdateServantSfxPassthrough(Entity* self) { ProcessSfxState(self); }

void UpdateEventAttack(Entity* self) { g_AttackFunctions[self->params](self); }

void func_us_801765A0(Entity* self) {
    static s32 origX;
    static s32 origY;

    switch (self->step) {
    case 0:
        if (!self->params) {
            origX = self->posX.val;
            origY = self->posY.val;
        } else {
            self->posX.val = origX;
            self->posY.val = origY;
        }

        self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA;
        self->palette = PAL_FLAG(PAL_UNK_143);
        self->drawMode = DRAW_TPAGE2 | DRAW_TPAGE;
        self->animSet = 0xE;
        self->unk5A = 0x79;
        self->anim = D_us_80171CD8;
        self->pose = 0;
        self->poseTimer = 0;
        self->drawFlags |= FLAG_DRAW_SCALEY;
        self->scaleY = 0xC0;

        self->velocityX = self->facingLeft ? -0xC000 : 0xC000;

        switch (self->params) {
        case 2:
            self->posY.i.hi += 8;
        case 1:
            self->posY.i.hi += 8;
        case 0:
            self->posX.i.hi += self->facingLeft ? -0x20 : 0x20;
        }

        g_api.GetServantStats(self, FAM_ABILITY_DEMON_UNK24, 1, &s_DemonStats);

        self->hitboxOffX = 0;
        self->hitboxOffY = 0;
        self->hitboxWidth = 12;
        self->hitboxHeight = 10;

        self->step++;
        if (self->params >= 2) {
            self->step++;
        }
        break;

    case 1:
        self->posX.val += self->velocityX;

        self->ext.demon.abilityId++;
        if (self->ext.demon.abilityId > 6) {
            CreateEventEntity(self, DEMON_MODE_UNK_DB, self->params + 1);
            self->step++;
        }
        break;

    case 2:
        self->posX.val += self->velocityX;

        if (self->ext.demon.frameCounter == -1) {
            DestroyEntity(self);
            return;
        }
        break;
    }

    self->ext.demon.frameCounter = ServantUpdateAnim(self, NULL, NULL);
}

void func_us_80176814(Entity* self) {
    static s32 origX;
    static s32 origY;

    Primitive* prim;
    s32 i;
    s32 x, y;

    switch (self->step) {
    case 0:
        if (!self->params) {
            origX = self->posX.val;
            origY = self->posY.val;
        } else {
            self->posX.val = origX;
            self->posY.val = origY;
        }

        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 0xC);

        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags =
            FLAG_POS_CAMERA_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_HAS_PRIMS;
        prim = &g_PrimBuf[self->primIndex];
        for (i = 0; i < 12; i++) {
            prim->tpage = 0x1A;
            prim->clut = 0x146;
            prim->priority = self->zPriority + 1;
            prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS |
                             DRAW_UNK02 | DRAW_TRANSP;

            prim->u0 = prim->u2 = ((i % 4) * 4) + 8;
            prim->u1 = prim->u3 = ((i % 4) * 4) + 12;
            prim->v0 = prim->v1 = 0x60;
            prim->v2 = prim->v3 = 0x80;
            PCOL(prim) = 0x80;
            prim = prim->next;
        }
        self->velocityX = self->facingLeft ? FIX(-4.0) : FIX(4.0);

        g_api.GetServantStats(self, FAM_ABILITY_DEMON_UNK25, 1, &s_DemonStats);

        self->hitboxOffX = 28;
        self->hitboxOffY = 0;
        self->hitboxWidth = 12;
        self->hitboxHeight = 10;

        self->step++;
        if (self->params >= 2) {
            self->step++;
        }
        break;

    case 1:
        self->posX.val += self->velocityX;
        self->ext.demon.frameCounter++;

        if (self->ext.demon.frameCounter > 2) {
            CreateEventEntity(self, 220, self->params + 1);
            self->step++;
        }
        break;

    case 2:
        self->posX.val += self->velocityX;
        self->ext.demon.frameCounter++;
        if (self->ext.demon.frameCounter > 8) {
            DestroyEntity(self);
            return;
        }
    }
    x = self->posX.i.hi;
    y = self->posY.i.hi - 12;
    prim = &g_PrimBuf[self->primIndex];

    for (i = 0; i < 12; i++) {
        if (self->facingLeft) {
            prim->x2 = x - D_us_80171D10[i];
            prim->x3 = x - D_us_80171D10[i + 1];
            if (i == 0) {
                prim->x0 = prim->x2 - 0x10;
            } else {
                prim->x0 = prim->x2 - 0x20;
            }
            if (i == 11) {
                prim->x1 = prim->x3 - 0x10;
            } else {
                prim->x1 = prim->x3 - 0x20;
            }

        } else {
            prim->x2 = x + D_us_80171D10[i];
            prim->x3 = x + D_us_80171D10[i + 1];

            if (i == 0) {
                prim->x0 = prim->x2 + 0x10;
            } else {
                prim->x0 = prim->x2 + 0x20;
            }
            if (i == 11) {
                prim->x1 = prim->x3 + 0x10;
            } else {
                prim->x1 = prim->x3 + 0x20;
            }
        }

        prim->y0 = prim->y2 = y + (i * 2);
        prim->y1 = prim->y3 = y + ((i + 1) * 2);

        prim = prim->next;
    }
}

void func_us_80176C1C(Entity* self) {
    static s32 origX;
    static s32 origY;

    Primitive* prim;
    s32 i;

    switch (self->step) {
    case 0:
        if (!self->params) {
            origX = self->posX.val;
            origY = self->posY.val;
        } else {
            self->posX.val = origX;
            self->posY.val = origY;
        }
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 8);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags =
            FLAG_POS_CAMERA_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_HAS_PRIMS;
        switch (self->params) {
        case 0:
            self->posX.i.hi += self->facingLeft ? -0x20 : 0x20;
            break;

        case 1:
            self->posX.i.hi += self->facingLeft ? -0x18 : 0x18;
            self->posY.i.hi += 8;
            break;

        case 2:
            self->posX.i.hi += self->facingLeft ? -0x10 : 0x10;
            self->posY.i.hi += 0x10;
            break;
        }
        prim = &g_PrimBuf[self->primIndex];
        for (i = 0; i < 8; i++) {
            prim->priority = self->zPriority + 1;
            prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_HIDE |
                             DRAW_COLORS | DRAW_UNK02 | DRAW_TRANSP;
            prim->tpage = 0x1A;
            prim->clut = PAL_UNK_194;

            prim->u0 = prim->u2 = (rand() % 5) * 0x10 + 0x90;
            prim->u1 = prim->u3 = prim->u0 + 0x10;
            prim->v0 = prim->v1 = 0xC0;
            prim->v2 = prim->v3 = 0xD0;
            if (self->facingLeft) {
                prim->x0 = prim->x2 = self->posX.i.hi - i * 8;
                prim->x1 = prim->x3 = self->posX.i.hi - (i + 1) * 8;
            } else {
                prim->x0 = prim->x2 = self->posX.i.hi + i * 8;
                prim->x1 = prim->x3 = self->posX.i.hi + (i + 1) * 8;
            }
            if (i < 7) {
                prim->y0 = prim->y1 = self->posY.i.hi - 6;
                prim->y2 = prim->y3 = self->posY.i.hi + 6;
            } else {
                prim->y0 = prim->y1 = self->posY.i.hi - 4;
                prim->y2 = prim->y3 = self->posY.i.hi + 4;
            }
            // this looks like a mistake but it is needed to get a match on PSP
            prim->r0 = prim->r1 = prim->r2 = prim->r3 = prim->g1 = prim->g2 =
                prim->g2 = prim->g3 = prim->b0 = prim->b1 = prim->b2 =
                    prim->b3 = 0;
            prim = prim->next;
        }
        g_api.GetServantStats(self, FAM_ABILITY_DEMON_UNK26, 1, &s_DemonStats);
        self->hitboxOffX = 0;
        self->hitboxOffY = 0;
        self->hitboxWidth = 0;
        self->hitboxHeight = 4;

        self->step++;
        if (self->params >= 2) {
            self->step++;
        }
        break;

    case 1:
        self->ext.factory.unk7C++;
        if (self->ext.factory.unk7C > 2) {
            CreateEventEntity(self, DEMON_MODE_UNK_DD, self->params + 1);
            self->step++;
        }
        break;

    case 2:
        self->ext.factory.unk7C++;
        if (self->ext.factory.unk7C > 16) {
            DestroyEntity(self);
            return;
        }
        break;
    }
    if (self->ext.factory.unk7E < 8) {
        prim = &g_PrimBuf[self->primIndex];
        for (i = 0; i < self->ext.factory.unk7E; i++) {
            prim = prim->next;
        }

        prim->drawMode &= ~DRAW_HIDE;
        prim->r0 = 0x80;
        self->hitboxOffX += 4;
        self->hitboxWidth += 4;
        self->ext.factory.unk7E++;
    }
    prim = &g_PrimBuf[self->primIndex];
    for (i = 0; i < 8; i++) {
        prim->r0 -= 8;
        if (prim->r0 < 0x20) {
            prim->drawMode |= DRAW_HIDE;
        } else {
            // this looks like a mistake but it is needed to get a match on PSP
            prim->r1 = prim->r2 = prim->r3 = prim->g1 = prim->g2 = prim->g2 =
                prim->g3 = prim->b0 = prim->b1 = prim->b2 = prim->b3 = prim->r0;
            prim->u0 = prim->u2 = (rand() % 5) * 0x10 + 0x90;
            prim->u1 = prim->u3 = prim->u0 + 0x10;
        }
        prim = prim->next;
    }
}

void func_us_801771B0(Entity* self) {
    static s32 origX;
    static s32 origY;

    Primitive* prim;
    s32 i;
    s32 x, y;

    switch (self->step) {
    case 0:
        if (!self->params) {
            origX = self->posX.val;
            origY = self->posY.val;
        } else {
            self->posX.val = origX;
            self->posY.val = origY;
        }

        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 3);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }

        self->flags =
            FLAG_POS_CAMERA_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_HAS_PRIMS;
        HIH(self->velocityX) = self->facingLeft ? -0x10 : 0x10;

        switch (self->params) {
        case 2:
            self->posY.i.hi += 8;
        case 1:
            self->posY.i.hi += 8;
        case 0:
            self->posX.i.hi += self->facingLeft ? -0x20 : 0x20;
        }

        prim = &g_PrimBuf[self->primIndex];
        for (i = 0; i < 3; i++) {
            prim->tpage = 0x1A;
            prim->clut = 0x147;
            prim->priority = self->zPriority + 1;
            prim->drawMode =
                DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
            prim->u0 = prim->u2 = 0xB;
            prim->u1 = prim->u3 = 0x35;
            prim->v0 = prim->v1 = 0xCB;
            prim->v2 = prim->v3 = 0xF5;
            PCOL(prim) = 0x80;

            prim = prim->next;
        }

        g_api.GetServantStats(self, 0x1B, 1, &s_DemonStats);

        self->hitboxOffX = -4;
        self->hitboxOffY = 0;
        self->hitboxWidth = 28;
        self->hitboxHeight = 4;

        self->step++;
        if (self->params >= 2) {
            self->step++;
        }
        break;

    case 1:
        self->ext.factory.unk7C++;
        self->posX.val += self->velocityX;

        if (self->ext.factory.unk7C > 2) {
            CreateEventEntity(self, DEMON_MODE_UNK_DE, self->params + 1);
            self->step++;
        }
        break;

    case 2:
        self->ext.factory.unk7C++;
        self->posX.val += self->velocityX;

        if (self->posX.i.hi < -0x20 || self->posX.i.hi > 0x120) {
            DestroyEntity(self);
            return;
        }
        break;
    }

    x = self->posX.i.hi;
    y = self->posY.i.hi;

    prim = &g_PrimBuf[self->primIndex];
    for (i = 0; i < 3; i++) {

        if (self->facingLeft) {
            prim->x0 = x - D_us_80171B44[i][0];
            prim->y0 = y - D_us_80171B44[i][1];
            prim->x1 = x - D_us_80171B44[i][2];
            prim->y1 = y - D_us_80171B44[i][3];
            prim->x2 = x - D_us_80171B44[i][4];
            prim->y2 = y - D_us_80171B44[i][5];
            prim->x3 = x - D_us_80171B44[i][6];
            prim->y3 = y - D_us_80171B44[i][7];
        } else {
            prim->x0 = x + D_us_80171B44[i][0];
            prim->y0 = y + D_us_80171B44[i][1];
            prim->x1 = x + D_us_80171B44[i][2];
            prim->y1 = y + D_us_80171B44[i][3];
            prim->x2 = x + D_us_80171B44[i][4];
            prim->y2 = y + D_us_80171B44[i][5];
            prim->x3 = x + D_us_80171B44[i][6];
            prim->y3 = y + D_us_80171B44[i][7];
        }

        PCOL(prim) = ((self->ext.factory.unk7C & 1) * 64) + 0x40;
        prim = prim->next;
    }
}

void func_us_80177690(Entity* self) {
    Entity* entity;

    switch (self->params) {
    case 0:
        D_us_801786D0 = 1;
        if ((entity = SearchForEntityInRange(0, DEMON_EVENT_SFX_PASSTHROUGH)) !=
                NULL &&
            entity->step < 5) {
            entity->step = 8;
        }
        break;

    case 1:
        D_us_801786D0 = 2;
        break;

    case 15:
        D_us_801786D4 = 1;
        break;
    }
    DestroyEntity(self);
}

#ifdef VERSION_PSP
s16 D_092F2810[4] = {0};
#endif

#include "../shared_events.h"
#include "../shared_globals.h"
#include "../servant_update_anim.h"
#include "../../destroy_entity.h"
#include "../accumulate_toward_zero.h"
#include "../search_for_entity_in_range.h"
#include "../calculate_angle_to_entity.h"
#include "../step_angle_towards.h"
#include "../calculate_distance.h"
#include "../play_sfx.h"
#include "../process_event.h"
#include "../create_event_entity.h"
#include "../is_movement_allowed.h"
#include "../check_all_entities_valid.h"
#include "../servant_unk0.h"
