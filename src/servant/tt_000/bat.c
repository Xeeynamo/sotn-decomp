// SPDX-License-Identifier: AGPL-3.0-or-later
#include <servant.h>
#include <sfx.h>
#include <psxsdk/libc.h>
#include "../servant_private.h"

#define ABILITY_STATS_DELAY_FRAMES 0
#define ABILITY_STATS_ATTACK_ANGLE 1
#define ABILITY_STATS_ADD_BAT_COUNT 2
#define ABILITY_STATS_MIN_ENEMY_HP 3
#define ABILITY_STATS_BAD_ATTACKS 4

#define ENTITY_ID_ATTACK_MODE 0xD2
#define ENTITY_ID_BLUE_TRAIL 0xDA

#ifndef VERSION_PSP
static s32 s_TargetMatch[0x80];
static Collider D_80174AD8;
static s16 s_TargetLocationX;
STATIC_PAD_BSS(2);
static s16 s_TargetLocationY;
STATIC_PAD_BSS(2);
static s16 s_TargetLocationX_calc;
STATIC_PAD_BSS(2);
static s16 s_TargetLocationY_calc;
STATIC_PAD_BSS(2);
static s16 D_80174B0C;
STATIC_PAD_BSS(2);
static s16 D_80174B10;
STATIC_PAD_BSS(2);
static s16 D_80174B14;
STATIC_PAD_BSS(2);
static s16 D_80174B18;
STATIC_PAD_BSS(2);
static s32 D_80174B1C;
static s32 D_80174B20;
static s32 D_80174B24;
static s32 D_80174B28;
static s32 D_80174B2C;
static s32 D_80174B2C;
static s32 D_80174B30;
static s32 D_80174B34;
static s16 D_80174B38;
STATIC_PAD_BSS(2);
static s16 D_80174B3C;
STATIC_PAD_BSS(2);
static s16 D_80174B40;
STATIC_PAD_BSS(2);
static s16 D_80174B44;
STATIC_PAD_BSS(2);
static Primitive* s_CurrentPrim;
static s32 D_80174B4C[16];
static Point16 D_80174B8C[16];
static s16 D_80174BCC[16];
static s16 D_80174BEC[16];
static s16 D_80174C0C[16];
static s32 D_80174C2C;
static FamiliarStats s_BatStats;
static Point16 D_80174C3C[4][16];
static s32 s_IsServantDestroyed;
static s32 s_LastTargetedEntityIndex;
static s32 _unused[26];

static void func_80172C30(Entity* self);
static void unused_339C(void);
static void unused_33A4(void);
static void unused_33AC(void);
static void unused_33B4(void);
static void unused_33BC(void);
static void unused_33C4(void);
static void unused_33CC(void);
static void UpdateBatBlueTrailEntities(Entity* self);
static void unused_3C0C(Entity* self);
static void unused_3C14(void);
static void unused_3C1C(void);
static void unused_3C24(void);

ServantDesc bat_ServantDesc = {
    ServantInit,          UpdateServantDefault, func_80172C30,
    unused_339C,        unused_33A4,        unused_33AC,
    unused_33B4,        unused_33BC,        unused_33C4,
    unused_33CC,        UpdateBatBlueTrailEntities, unused_3C0C,
    unused_3C14,        unused_3C1C,        unused_3C24,
    DestroyServantEntity,
};
#endif


#ifdef VERSION_PSP
extern FamiliarStats s_BatStats;
extern s32 s_TargetMatch[0x80];

extern Collider D_80174AD8;
extern s16 s_TargetLocationX;
extern s16 s_TargetLocationY;
extern s16 s_TargetLocationX_calc;
extern s16 s_TargetLocationY_calc;
extern s16 D_80174B0C;
extern s16 D_80174B10;
extern s16 D_80174B14;
extern s16 D_80174B18;
extern s32 D_80174B1C;
extern s32 D_80174B20;
extern s32 D_80174B24;
extern s32 D_80174B28;
extern s32 D_80174B2C;
extern s32 D_80174B2C;
extern s32 D_80174B30;
extern s32 D_80174B34;
extern s16 D_80174B38;
extern s16 D_80174B3C;
extern s16 D_80174B40;
extern s16 D_80174B44;
extern Primitive* s_CurrentPrim;
extern s32 D_80174B4C[16];
extern Point16 D_80174B8C[16];
extern s16 D_80174BCC[16];
extern s16 D_80174BEC[16];
extern s16 D_80174C0C[16];
extern s32 D_80174C2C;
extern FamiliarStats s_BatStats;
extern Point16 D_80174C3C[4][16];
extern s32 s_IsServantDestroyed;
extern s32 s_LastTargetedEntityIndex;
#endif


extern AnimationFrame g_DefaultBatAnimationFrame[];
extern s32 g_BatAbilityStats[][5];
extern u16 g_BatClut[];

#include "../set_entity_animation.h"

static Entity* FindValidTarget(Entity* self) {
    const int EntitySearchCount = 128;
    s32 foundIndex;
    s32 i;
    u32 found;
    Entity* entity;
    s32 distance;

    found = 0;
    entity = &g_Entities[STAGE_ENTITY_START];
    for (i = 0; i < EntitySearchCount; i++, entity++) {
        s_TargetMatch[i] = 0;
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
        if (entity->hitboxState & 8 && !g_BatAbilityStats[s_BatStats.level / 10][ABILITY_STATS_BAD_ATTACKS]) {
            continue;
        }
        if (abs(self->posX.i.hi - entity->posX.i.hi) < 64 &&
            abs(self->posY.i.hi - entity->posY.i.hi) < 64) {
            continue;
        }
        if (!self->facingLeft && self->posX.i.hi < entity->posX.i.hi) {
            continue;
        }
        if (self->facingLeft && self->posX.i.hi > entity->posX.i.hi) {
            continue;
        }
        if (entity->hitPoints >= 0x7000) {
            continue;
        }

        if (entity->flags & FLAG_UNK_80000) {
            if (entity->hitPoints >= g_BatAbilityStats[s_BatStats.level / 10][ABILITY_STATS_MIN_ENEMY_HP]) {
                found++;
                s_TargetMatch[i] = 1;
            }
        } else {
            entity->flags |= FLAG_UNK_80000;
            return entity;
        }
    }

    if (found > 0) {
        foundIndex = s_LastTargetedEntityIndex % EntitySearchCount;
        for (i = 0; i < 0x80; i++) {
            if (s_TargetMatch[foundIndex]) {
                entity = &g_Entities[STAGE_ENTITY_START + foundIndex];
                s_LastTargetedEntityIndex = (foundIndex + 1) % EntitySearchCount;
                return entity;
            }
            foundIndex = (foundIndex + 1) % EntitySearchCount;
        }
    }

    return NULL;
}

#include "../check_entity_valid.h"

#ifndef VERSION_PSP
// This may be dead code.  Doesn't look like it is called anywhere.
bool Unused_CheckCollision(s16 x, s16 y, s16* outX, s16* outY) {
    s32 curY;

    g_api.CheckCollision(x, y, &D_80174AD8, 0);
    if (D_80174AD8.effects & 1) {
        return 0;
    }

    for (curY = y - 16; curY > 0; curY -= 16) {
        g_api.CheckCollision(x, curY, &D_80174AD8, 0);
        switch (D_80174AD8.effects & 0x801) {
        case 0:
            break;
        case 1:
            *outX = x;
            *outY = curY + D_80174AD8.unk10;
            return 1;
        default:
            return 0;
        }
    }
    return 0;
}
#endif

static void unused_1560(Entity* self) {}

// Only ever called by UpdateServantDefault so that is the parent
void CreateBlueTrailEntity(Entity* parent) {
    Entity* entity;
    s32 i;

    // Look for empty ent slot 5, 6, or 7
    for (i = 0; i < 3; i++) {
        entity = &g_Entities[5 + i];
        // if ID is zero, it's vacant and we'll use it.
        if (!entity->entityId) {
            break;
        }
    }
    // If we found a vacant entity in that loop, we use it.
    if (!entity->entityId) {
        // Make sure it's empty
        DestroyEntity(entity);
        // The entity we're making is the Servant function 0xA,
        // UpdateBatBlueTrailEntities
        entity->entityId = ENTITY_ID_BLUE_TRAIL;
        entity->zPriority = parent->zPriority;
        entity->facingLeft = parent->facingLeft;
        entity->flags = FLAG_KEEP_ALIVE_OFFCAMERA;
        entity->posX.val = parent->posX.val;
        entity->posY.val = parent->posY.val;
        entity->ext.batFamBlueTrail.parent = parent;
    }
}

void CreateAdditionalBats(s32 amount, s32 entityId) {
    s32 i;
    Entity* entity;
    u16 facing;

    amount = MIN(amount, 3);
    for (i = 0; i < amount; i++) {
        entity = &g_Entities[5 + i];
        if (entity->entityId == entityId) {
            entity->step = 0;
        } else {
            DestroyEntity(entity);
            entity->entityId = entityId;
            entity->unk5A = 0x6C;
            entity->palette = 0x140;
            entity->animSet = ANIMSET_OVL(20);
            entity->zPriority = g_Entities[0].zPriority - 2;
            entity->facingLeft = (g_Entities[0].facingLeft + 1) & 1;
            entity->params = i + 1;
        }
        entity->ext.bat.cameraX = g_Tilemap.scrollX.i.hi;
        entity->ext.bat.cameraY = g_Tilemap.scrollY.i.hi;
    }
}

void func_8017170C(Entity* entity, s32 frameIndex) {
    Primitive* prim;
    s32 tpage;
    s32 x;
    s32 y;
    s32 index;

    prim = &g_PrimBuf[entity->primIndex];
    if (frameIndex == 0) {
        prim->drawMode = DRAW_HIDE;
        return;
    }
    index = frameIndex - 1;
    if (entity->facingLeft) {
        x = entity->posX.i.hi + 2;
    } else {
        x = entity->posX.i.hi - 16;
    }
    y = entity->posY.i.hi - 16;

    prim->x0 = prim->x2 = x - D_80170608[index].x;
    prim->y0 = prim->y1 = y - D_80170608[index].y;
    prim->x1 = prim->x3 = prim->x0 + D_80170608[index].width;
    prim->y2 = prim->y3 = prim->y0 + D_80170608[index].height;
    prim->clut = D_80170608[index].clut;
    prim->tpage = D_80170608[index].tpage / 4;
    prim->u0 = prim->u2 = D_80170608[index].texLeft;
    prim->v0 = prim->v1 = D_80170608[index].texTop;
    prim->u1 = prim->u3 = D_80170608[index].texRight;
    prim->v2 = prim->v3 = D_80170608[index].texBottom;
    prim->priority = entity->zPriority + 1;
    prim->drawMode = DRAW_UNK_100 | DRAW_UNK02;
}

void func_801718A0(Entity* entity) {
    Primitive* prim;
    s32 frame;
    s32 y;
    s32 x;

    frame = 2;
    if (entity->facingLeft) {
        x = entity->posX.i.hi + 2;
    } else {
        x = entity->posX.i.hi - 16;
    }
    y = entity->posY.i.hi - 16;

    x += (rsin(entity->ext.bat.frameCounter << 7) * 8) >> 12;
    y -= entity->ext.bat.frameCounter / 2;

    prim = &g_PrimBuf[entity->primIndex];
    prim->x0 = prim->x2 = x - D_80170608[frame].x;
    prim->y0 = prim->y1 = y - D_80170608[frame].y;
    prim->x1 = prim->x3 = prim->x0 + D_80170608[frame].width;
    prim->y2 = prim->y3 = prim->y0 + D_80170608[frame].height;
}

void func_801719E0(Entity* self) {
    s32 i;

    if (!self->ext.bat.unk80) {
        self->ext.bat.unk82 = self->params;
        self->ext.bat.unk8E = 0;
        switch (self->entityId) {
        case ENTITY_ID_SERVANT:
            self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
            if (self->primIndex == -1) {
                DestroyEntity(self);
                return;
            }
            func_8017170C(self, 0);
            self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA |
                          FLAG_HAS_PRIMS | FLAG_UNK_20000;
            SetEntityAnimation(self, g_DefaultBatAnimationFrame);
            self->ext.bat.unk84 = rand() % 4096;
            self->ext.bat.unk86 = 0;
            self->ext.bat.unk88 = 0xC;
            self->ext.bat.frameCounter = rand() % 4096;
            self->ext.bat.unk8A = 0x20;
            self->step++;
            break;
        case ENTITY_ID_ATTACK_MODE:
            self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
            if (self->primIndex == -1) {
                DestroyEntity(self);
                return;
            }
            func_8017170C(self, 0);
            self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA |
                          FLAG_UNK_02000000 | FLAG_HAS_PRIMS | FLAG_UNK_20000;
            SetEntityAnimation(self, g_DefaultBatAnimationFrame);
            if (!self->ext.bat.unk82) {
                self->ext.bat.follow = &PLAYER;
            } else {
                self->ext.bat.follow = &g_Entities[3 + self->ext.bat.unk82];
            }
            self->ext.bat.cameraX = g_Tilemap.scrollX.i.hi;
            self->ext.bat.cameraY = g_Tilemap.scrollY.i.hi;

            if (!self->ext.bat.unk82) {
                for (i = 0; i < 16; i++) {
                    D_80174C3C[self->ext.bat.unk82][i].x =
                        self->ext.bat.follow->posX.i.hi + self->ext.bat.cameraX;
                    D_80174C3C[self->ext.bat.unk82][i].y =
                        self->ext.bat.follow->posY.i.hi + self->ext.bat.cameraY;
                }
            } else {
                for (i = 0; i < 16; i++) {
                    if (PLAYER.facingLeft) {
                        D_80174C3C[self->ext.bat.unk82][i].x =
                            PLAYER.posX.i.hi +
                            ((self->ext.bat.unk82 + 1) * 0x10) +
                            self->ext.bat.cameraX;

                    } else {
                        D_80174C3C[self->ext.bat.unk82][i].x =
                            PLAYER.posX.i.hi -
                            ((self->ext.bat.unk82 + 1) * 0x10) +
                            self->ext.bat.cameraX;
                    }
                    D_80174C3C[self->ext.bat.unk82][i].y =
                        PLAYER.posY.i.hi + self->ext.bat.cameraY;
                }
                self->posX.i.hi = PLAYER.facingLeft ? 0x180 : -0x80;
                self->posY.i.hi = rand() % 256;
            }
            self->ext.bat.unkA8 = 0;
            self->step++;
            break;
        }
    } else {
        self->ext.bat.unk8E = 0;
        switch (self->entityId) {
        case ENTITY_ID_SERVANT:
            self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA |
                          FLAG_HAS_PRIMS | FLAG_UNK_20000;
            SetEntityAnimation(self, g_DefaultBatAnimationFrame);
            self->ext.bat.frameCounter = rand() % 4096;
            self->step++;
            break;
        case ENTITY_ID_ATTACK_MODE:
            self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA |
                          FLAG_UNK_02000000 | FLAG_HAS_PRIMS | FLAG_UNK_20000;
            SetEntityAnimation(self, g_DefaultBatAnimationFrame);
            if (!self->ext.bat.unk82) {
                self->ext.bat.follow = &PLAYER;
            } else {
                self->ext.bat.follow = &g_Entities[3 + self->ext.bat.unk82];
            }
            self->ext.bat.cameraX = g_Tilemap.scrollX.i.hi;
            self->ext.bat.cameraY = g_Tilemap.scrollY.i.hi;

            for (i = 0; i < 16; i++) {
                if (PLAYER.facingLeft) {
                    D_80174C3C[self->ext.bat.unk82][i].x =
                        PLAYER.posX.i.hi + ((self->ext.bat.unk82 + 1) * 0x10) +
                        self->ext.bat.cameraX;
                } else {
                    D_80174C3C[self->ext.bat.unk82][i].x =
                        PLAYER.posX.i.hi - ((self->ext.bat.unk82 + 1) * 0x10) +
                        self->ext.bat.cameraX;
                }
                D_80174C3C[self->ext.bat.unk82][i].y =
                    PLAYER.posY.i.hi + self->ext.bat.cameraY;
            }
            self->ext.bat.unkA8 = 0;
            self->step++;
            break;
        }
    }
    self->ext.bat.unk80 = self->entityId;
    g_api.func_8011A3AC(self, 0, 0, &s_BatStats);
}

#ifdef VERSION_PC
extern u16 g_ServantClut[48];
#endif

void ServantInit(InitializeMode mode) {
    u16* dst;
    u16* src;
    RECT rect;
    s32 i;
    s32 x;
    SpriteParts** spriteBanks;
    Entity* e;

#ifdef VERSION_PC
    const int len = LEN(g_ServantClut);
#else
    const int len = 256;
#endif

    if ((mode == MENU_SWITCH_SERVANT) || (mode == MENU_SAME_SERVANT)) {
        ProcessEvent(NULL, true);
        if (mode == MENU_SAME_SERVANT) {
            return;
        }
    }

    dst = &g_Clut[CLUT_INDEX_SERVANT];
    src = g_ServantClut;

    for (i = 0; i < len; i++) {
        *dst++ = *src++;
    }

    dst = &g_Clut[CLUT_INDEX_SERVANT_OVERWRITE];
    src = g_BatClut;

    for (i = 0; i < 32; i++) {
        *dst++ = *src++;
    }

    rect.x = 0;
    rect.w = 0x100;
    rect.h = 1;
    rect.y = 0xF4;

    dst = &g_Clut[CLUT_INDEX_SERVANT];
    LoadImage(&rect, (u_long*)dst);

    spriteBanks = g_api.o.spriteBanks;
    spriteBanks += 20;
    *spriteBanks = (SpriteParts*)g_ServantSpriteParts;

    e = &g_Entities[SERVANT_ENTITY_INDEX];

    DestroyEntity(e);

    e->unk5A = 0x6C;
    e->palette = 0x140;
    e->animSet = ANIMSET_OVL(20);
    e->zPriority = PLAYER.zPriority - 2;
    e->facingLeft = (PLAYER.facingLeft + 1) & 1;
    e->posX.val = PLAYER.posX.val;
    e->posY.val = PLAYER.posY.val;
    e->params = 0;

    if (mode == MENU_SWITCH_SERVANT) {
        e->entityId = ENTITY_ID_SERVANT;
        e->posX.val = FIX(128);
        e->posY.val = FIX(-32);
    } else {
        e->entityId = ENTITY_ID_SERVANT;
        if (D_8003C708.flags & LAYOUT_RECT_PARAMS_UNKNOWN_20) {
            e->posX.val = ServantUnk0() ? FIX(192) : FIX(64);
            e->posY.val = FIX(160);
        } else {
            e->posX.val =
                (PLAYER.facingLeft ? FIX(18) : FIX(-18)) + PLAYER.posX.val;
            e->posY.val = PLAYER.posY.val - FIX(34);
        }
    }
    e->ext.bat.cameraX = g_Tilemap.scrollX.i.hi;
    e->ext.bat.cameraY = g_Tilemap.scrollY.i.hi;
    s_IsServantDestroyed = 0;
}

#ifdef VERSION_PSP
INCLUDE_ASM("servant/tt_000/nonmatchings/bat", UpdateServantDefault);
#else
void UpdateServantDefault(Entity* self) {
    g_api.func_8011A3AC(self, 0, 0, &s_BatStats);
    if (s_IsServantDestroyed != 0) {
        self->zPriority = PLAYER.zPriority - 2;
    }
    if (D_8003C708.flags & LAYOUT_RECT_PARAMS_UNKNOWN_20) {
        switch (ServantUnk0()) {
        case 0:
            s_TargetLocationX_calc = 0x40;
            break;
        case 1:
            s_TargetLocationX_calc = 0xC0;
            break;
        case 2:
            s_TargetLocationX_calc = (self->posX.i.hi > 0x80) ? 0xC0 : 0x40;
            break;
        }
        s_TargetLocationY_calc = 0xA0;
    } else {
        D_80174B18 = -0x12;
        if (PLAYER.facingLeft) {
            D_80174B18 = -D_80174B18;
        }
        s_TargetLocationX_calc = PLAYER.posX.i.hi + D_80174B18;
        s_TargetLocationY_calc = PLAYER.posY.i.hi - 0x22;
    }
    D_80174B0C = self->ext.bat.unk84;
    self->ext.bat.unk84 += 0x10;
    D_80174B14 = self->ext.bat.unk88;
    s_TargetLocationX = s_TargetLocationX_calc + ((rcos(D_80174B0C) >> 4) * D_80174B14 >> 8);
    s_TargetLocationY = s_TargetLocationY_calc - ((rsin(D_80174B0C / 2) >> 4) * D_80174B14 >> 8);
    switch (self->step) {
    case 0:
        func_801719E0(self);
        break;
    case 1:
        if (g_Player.status & PLAYER_STATUS_BAT_FORM) {
            self->ext.bat.frameCounter = 0;
            self->step = 5;
            break;
        }
        if (D_8003C708.flags & LAYOUT_RECT_PARAMS_UNKNOWN_20) {
            if (PLAYER.posX.i.hi >= self->posX.i.hi) {
                self->facingLeft = true;
            } else {
                self->facingLeft = false;
            }
        } else {
            if (PLAYER.facingLeft == self->facingLeft) {
                if (abs(s_TargetLocationX - self->posX.i.hi) <= 0) {
                    self->facingLeft = PLAYER.facingLeft ? false : true;
                } else {
                    if (self->facingLeft && s_TargetLocationX < self->posX.i.hi) {
                        self->facingLeft = PLAYER.facingLeft ? false : true;
                    } else if (
                        !self->facingLeft && s_TargetLocationX > self->posX.i.hi) {
                        self->facingLeft = PLAYER.facingLeft ? false : true;
                    }
                }
            } else if (
                self->facingLeft && (self->posX.i.hi - s_TargetLocationX) > 0x1F) {
                self->facingLeft = PLAYER.facingLeft;
            } else if (
                !self->facingLeft && (s_TargetLocationX - self->posX.i.hi) > 0x1F) {
                self->facingLeft = PLAYER.facingLeft;
            }
        }
        D_80174B0C = CalculateAngleToEntity(self, s_TargetLocationX, s_TargetLocationY);
        D_80174B10 = GetTargetPositionWithDistanceBuffer(
            D_80174B0C, self->ext.bat.unk86, self->ext.bat.unk8A);
        self->ext.bat.unk86 = D_80174B10;
        s_TargetLocationX_calc = s_TargetLocationX - self->posX.i.hi;
        s_TargetLocationY_calc = s_TargetLocationY - self->posY.i.hi;
        D_80174B14 =
            SquareRoot12(
                (s_TargetLocationX_calc * s_TargetLocationX_calc + s_TargetLocationY_calc * s_TargetLocationY_calc) << 12) >>
            12;
        if (D_80174B14 < 30) {
            self->velocityY = -(rsin(D_80174B10) << 3);
            self->velocityX = rcos(D_80174B10) << 3;
            self->ext.bat.unk8A = 0x20;
        } else if (D_80174B14 < 60) {
            self->velocityY = -(rsin(D_80174B10) << 4);
            self->velocityX = rcos(D_80174B10) << 4;
            self->ext.bat.unk8A = 0x40;
        } else if (D_80174B14 < 100) {
            self->velocityY = -(rsin(D_80174B10) << 5);
            self->velocityX = rcos(D_80174B10) << 5;
            self->ext.bat.unk8A = 0x60;
        } else if (D_80174B14 < 0x100) {
            self->velocityY = -(rsin(D_80174B10) << 6);
            self->velocityX = rcos(D_80174B10) << 6;
            self->ext.bat.unk8A = 0x80;
        } else {
            self->velocityX = (s_TargetLocationX - self->posX.i.hi) << 0xE;
            self->velocityY = (s_TargetLocationY - self->posY.i.hi) << 0xE;
            self->ext.bat.unk8A = 0x80;
        }
        if (self->velocityY > FIX(1.0)) {
            SetEntityAnimation(self, D_801705EC);
        } else if (D_80174B14 < 60) {
            SetEntityAnimation(self, g_DefaultBatAnimationFrame);
        } else if (D_80174B14 > 100) {
            SetEntityAnimation(self, D_80170514);
        }
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        if (g_CutsceneHasControl) {
            break;
        }
        D_80174B24 = s_TargetLocationX - self->posX.i.hi;
        D_80174B28 = s_TargetLocationY - self->posY.i.hi;
        D_80174B2C =
            SquareRoot12(
                (D_80174B24 * D_80174B24 + D_80174B28 * D_80174B28) << 12) >>
            12;
        if (D_80174B2C < 0x18) {
            if (self->ext.bat.unk8E) {
                self->ext.bat.unk8E = 0;
                SetEntityAnimation(self, D_8017054C);
            }
            self->ext.bat.frameCounter++;
            if (self->ext.bat.frameCounter > g_BatAbilityStats[s_BatStats.level / 10][ABILITY_STATS_DELAY_FRAMES]) {
                self->ext.bat.frameCounter = 0;
                // Pay attention - this is not a ==
                if (self->ext.bat.target = FindValidTarget(self)) {
                    self->step++;
                }
            }
        } else {
            self->ext.bat.unk8E = 1;
        }
        break;
    case 2:
        self->ext.bat.frameCounter++;
        if (self->ext.bat.frameCounter == 1) {
            g_api.PlaySfx(SFX_UI_ALERT_TINK);
            func_8017170C(self, 1);
        } else if (self->ext.bat.frameCounter > 30) {
            self->ext.bat.frameCounter = 0;
            func_8017170C(self, 0);
            D_80174B1C = self->ext.bat.target->posX.i.hi;
            D_80174B20 = self->ext.bat.target->posY.i.hi;
            self->hitboxWidth = 5;
            self->hitboxHeight = 5;
            g_api.func_8011A3AC(self, 15, 1, &s_BatStats);
            self->ext.bat.unk86 = 0xC00;
            SetEntityAnimation(self, D_801705EC);
            CreateBlueTrailEntity(self);
            self->step++;
        }
        break;
    case 3:
        D_80174B1C = self->ext.bat.target->posX.i.hi;
        D_80174B20 = self->ext.bat.target->posY.i.hi;
        D_80174B0C = CalculateAngleToEntity(self, D_80174B1C, D_80174B20);
        D_80174B10 = GetTargetPositionWithDistanceBuffer(
            D_80174B0C, self->ext.bat.unk86,
            g_BatAbilityStats[s_BatStats.level / 10][ABILITY_STATS_ATTACK_ANGLE]);
        self->ext.bat.unk86 = D_80174B10;
        self->velocityX = rcos(D_80174B10) << 2 << 4;
        self->velocityY = -(rsin(D_80174B10) << 2 << 4);
        if (self->velocityX > 0) {
            self->facingLeft = 1;
        }
        if (self->velocityX < 0) {
            self->facingLeft = 0;
        }
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        D_80174B24 = D_80174B1C - self->posX.i.hi;
        D_80174B28 = D_80174B20 - self->posY.i.hi;
        D_80174B2C =
            SquareRoot12(
                (D_80174B24 * D_80174B24 + D_80174B28 * D_80174B28) << 12) >>
            12;
        if (!CheckEntityValid(self->ext.bat.target) || D_80174B2C < 8) {
            self->ext.bat.frameCounter = 0;
            self->step++;
            SetEntityAnimation(self, D_8017054C);
        }
        break;
    case 4:
        D_80174B0C = CalculateAngleToEntity(self, s_TargetLocationX, s_TargetLocationY);
        D_80174B10 = GetTargetPositionWithDistanceBuffer(
            D_80174B0C, self->ext.bat.unk86, 0x10);
        self->ext.bat.unk86 = D_80174B10;
        self->velocityX = rcos(D_80174B10) << 2 << 4;
        self->velocityY = -(rsin(D_80174B10) << 2 << 4);
        self->facingLeft = (self->velocityX >= 0) ? true : false;
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        self->ext.bat.frameCounter++;
        if (self->ext.bat.frameCounter > 30) {
            self->hitboxWidth = 0;
            self->hitboxHeight = 0;
            self->step = 1;
        }
        break;
    case 5:
        self->ext.bat.frameCounter++;
        if (self->ext.bat.frameCounter == 1) {
            g_api.PlaySfx(SFX_BAT_SCREECH);
            func_8017170C(self, 3);
        } else if (self->ext.bat.frameCounter > 30) {
            func_8017170C(self, 0);
            self->entityId = ENTITY_ID_ATTACK_MODE;
            self->step = 0;
        }
        func_801718A0(self);
        break;
    }
    ProcessEvent(self, false);
    unused_1560(self);
    g_api.UpdateAnim(NULL, D_801705F4);
}
#endif

#ifdef VERSION_PSP
INCLUDE_ASM("servant/tt_000/nonmatchings/bat", func_80172C30);
#else
void func_80172C30(Entity* self) {
    if (self->step == 1 && self->flags & FLAG_UNK_00200000) {
        D_80174B38 = (self->ext.bat.cameraX - g_Tilemap.scrollX.i.hi) +
                     (self->ext.bat.unkB0 - PLAYER.posX.i.hi);
        D_80174B3C = (self->ext.bat.cameraY - g_Tilemap.scrollY.i.hi) +
                     (self->ext.bat.unkB2 - PLAYER.posY.i.hi);

        for (D_80174B30 = 0; D_80174B30 < 0x10; D_80174B30++) {
            D_80174C3C[self->ext.bat.unk82][D_80174B30].x -= D_80174B38;
            D_80174C3C[self->ext.bat.unk82][D_80174B30].y -= D_80174B3C;
        }
        return;
    }

    g_api.func_8011A3AC(self, 0, 0, &s_BatStats);
    if (s_IsServantDestroyed != 0) {
        self->zPriority = PLAYER.zPriority - 2;
    }
    switch (self->step) {
    case 0:
        func_801719E0(self);
        if (!self->ext.bat.unk82) {
            CreateAdditionalBats(g_BatAbilityStats[s_BatStats.level / 10][ABILITY_STATS_ADD_BAT_COUNT], ENTITY_ID_ATTACK_MODE);
        }
        break;
    case 1:
        self->ext.bat.unkB0 = PLAYER.posX.i.hi;
        self->ext.bat.unkB2 = PLAYER.posY.i.hi;
        self->ext.bat.cameraX = g_Tilemap.scrollX.i.hi;
        self->ext.bat.cameraY = g_Tilemap.scrollY.i.hi;
        D_80174B40 =
            D_80174C3C[self->ext.bat.unk82][0].x - self->ext.bat.cameraX;
        D_80174B44 =
            D_80174C3C[self->ext.bat.unk82][0].y - self->ext.bat.cameraY;
        self->velocityX = (D_80174B40 - self->posX.i.hi) << 0xC;
        self->velocityY = (D_80174B44 - self->posY.i.hi) << 0xC;
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        if ((self->velocityX == 0) && (self->velocityY == 0)) {
            if (self->ext.bat.unk8E) {
                SetEntityAnimation(self, D_8017054C);
                self->ext.bat.unk8E = false;
            }
        } else {
            if (self->velocityY > FIX(1)) {
                SetEntityAnimation(self, D_801705EC);
            } else {
                SetEntityAnimation(self, g_DefaultBatAnimationFrame);
            }
            self->ext.bat.unk8E = true;
        }
        self->facingLeft = PLAYER.facingLeft ? false : true;
        if (!self->ext.bat.unkA8) {
            if (g_Player.status & PLAYER_STATUS_UNK800) {
                // This causes the bat familiar to shoot a fireball when the
                // player does so in bat form.
                g_api.CreateEntFactoryFromEntity(self, FACTORY(81, 1), 0);
                self->ext.bat.unkA8 = 1;
            }
        } else if (self->ext.bat.unkA8) {
            if (!(g_Player.status & PLAYER_STATUS_UNK800)) {
                self->ext.bat.unkA8 = 0;
            }
        }
        D_80174B38 = self->ext.bat.follow->posX.i.hi - self->posX.i.hi;
        D_80174B3C = self->ext.bat.follow->posY.i.hi - self->posY.i.hi;
        D_80174B34 =
            SquareRoot12(((D_80174B38 * D_80174B38) + (D_80174B3C * D_80174B3C))
                         << 0xC) >>
            0xC;
        if (IsMovementAllowed(0) || D_80174B34 >= 0x19) {
            for (D_80174B30 = 0; D_80174B30 < 0xF; D_80174B30++) {
                D_80174C3C[self->ext.bat.unk82][D_80174B30].x =
                    D_80174C3C[self->ext.bat.unk82][D_80174B30 + 1].x;
                D_80174C3C[self->ext.bat.unk82][D_80174B30].y =
                    D_80174C3C[self->ext.bat.unk82][D_80174B30 + 1].y;
            }
            D_80174C3C[self->ext.bat.unk82][D_80174B30].x =
                self->ext.bat.follow->posX.i.hi + self->ext.bat.cameraX;
            D_80174C3C[self->ext.bat.unk82][D_80174B30].y =
                self->ext.bat.follow->posY.i.hi + self->ext.bat.cameraY;
        }
        if (!(g_Player.status & PLAYER_STATUS_BAT_FORM)) {
            self->ext.bat.frameCounter = 0;
            self->step++;
        }
        break;
    case 2:
        self->ext.bat.frameCounter++;
        if (self->ext.bat.frameCounter == 1) {
            if (!self->ext.bat.unk82) {
                g_api.PlaySfx(SFX_BAT_SCREECH);
            }
            func_8017170C(self, 2);
        } else if (self->ext.bat.frameCounter >= 0x1F) {
            func_8017170C(self, 0);
            if (!self->ext.bat.unk82) {
                self->entityId = ENTITY_ID_SERVANT;
                self->step = 0;
                break;
            }
            self->step++;
            D_80174C3C[self->ext.bat.unk82][0].x =
                PLAYER.facingLeft ? -0x80 : 0x180;
            D_80174C3C[self->ext.bat.unk82][0].y = rand() % 256;
            SetEntityAnimation(self, g_DefaultBatAnimationFrame);
        }
        break;
    case 3:
        D_80174B40 = D_80174C3C[self->ext.bat.unk82][0].x;
        D_80174B44 = D_80174C3C[self->ext.bat.unk82][0].y;
        self->velocityX = (D_80174B40 - self->posX.i.hi) << 0xA;
        self->velocityY = (D_80174B44 - self->posY.i.hi) << 0xA;
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        if (self->posX.i.hi < -0x20 || 0x120 < self->posX.i.hi) {
            DestroyEntity(self);
            return;
        }
        break;
    }
    ProcessEvent(self, false);
    unused_1560(self);
    g_api.UpdateAnim(NULL, D_801705F4);
}
#endif

void unused_339C(void) {}

void unused_33A4(void) {}

void unused_33AC(void) {}

void unused_33B4(void) {}

void unused_33BC(void) {}

void unused_33C4(void) {}

void unused_33CC(void) {}

// When bat familiar swoops toward enemy to attack, it leaves a trail of blue
// bat outlines behind it, not unlike Alucard's wing smash bat outlines.
void UpdateBatBlueTrailEntities(Entity* self) {
    const s32 nPrim = 16;
    const s32 XS = 11; // X start, left
    const s32 XE = 13; // X end, right
    const s32 YS = 24; // Y start, top
    const s32 YE = 8;  // Y end, bottom
    s32 i;
    s32 isEntityAlive;

    switch (self->step) {
    case 0:
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, nPrim);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        } else {
            self->flags = FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_HAS_PRIMS;
            s_CurrentPrim = &g_PrimBuf[self->primIndex];
            for (i = 0; i < nPrim; i++) {
                s_CurrentPrim->tpage = 0x1B;
                s_CurrentPrim->clut = 0x143;
                s_CurrentPrim->u0 = s_CurrentPrim->u2 = 64;
                s_CurrentPrim->v0 = s_CurrentPrim->v1 = 0;
                s_CurrentPrim->u1 = s_CurrentPrim->u3 = 88;
                s_CurrentPrim->v2 = s_CurrentPrim->v3 = 32;
                s_CurrentPrim->priority = self->zPriority;
                s_CurrentPrim->drawMode = 0x15 | DRAW_HIDE;
                s_CurrentPrim = s_CurrentPrim->next;
                D_80174B4C[i] = 0;
            }
            D_80174C2C = 0;
            self->step++;
        }
        break;
    case 1:
        if (self->ext.batFamBlueTrail.parent->step != 3) {
            self->step++;
        }
        D_80174B8C[D_80174C2C].x = self->ext.batFamBlueTrail.parent->posX.i.hi;
        D_80174B8C[D_80174C2C].y = self->ext.batFamBlueTrail.parent->posY.i.hi;
        D_80174BCC[D_80174C2C] = self->ext.batFamBlueTrail.parent->facingLeft;
        D_80174BEC[D_80174C2C] = 256;
        D_80174C0C[D_80174C2C] = 192;
        D_80174B4C[D_80174C2C] = 1;
        D_80174C2C = ++D_80174C2C >= nPrim ? 0 : D_80174C2C;
        s_CurrentPrim = &g_PrimBuf[self->primIndex];
        for (i = 0; i < nPrim; i++) {
            if (D_80174B4C[i]) {
                if (D_80174BCC[i]) {
                    s_CurrentPrim->x0 = s_CurrentPrim->x2 =
                        D_80174B8C[i].x + D_80174BEC[i] * XS / 256;
                    s_CurrentPrim->x1 = s_CurrentPrim->x3 =
                        D_80174B8C[i].x - D_80174BEC[i] * XE / 256;
                } else {
                    s_CurrentPrim->x0 = s_CurrentPrim->x2 =
                        D_80174B8C[i].x - D_80174BEC[i] * XS / 256;
                    s_CurrentPrim->x1 = s_CurrentPrim->x3 =
                        D_80174B8C[i].x + D_80174BEC[i] * XE / 256;
                }
                s_CurrentPrim->y0 = s_CurrentPrim->y1 =
                    D_80174B8C[i].y - D_80174BEC[i] * YS / 256;
                s_CurrentPrim->y2 = s_CurrentPrim->y3 =
                    D_80174B8C[i].y + D_80174BEC[i] * YE / 256;
                s_CurrentPrim->r0 = s_CurrentPrim->r1 = s_CurrentPrim->r2 =
                    s_CurrentPrim->r3 = s_CurrentPrim->g0 = s_CurrentPrim->g1 =
                        s_CurrentPrim->g2 = s_CurrentPrim->g3 = s_CurrentPrim->b0 =
                            s_CurrentPrim->b1 = s_CurrentPrim->b2 = s_CurrentPrim->b3 =
                                D_80174C0C[i];
                D_80174BEC[i] -= 8;
                D_80174C0C[i] -= 8;
                if (D_80174C0C[i] < 81) {
                    s_CurrentPrim->drawMode |= DRAW_HIDE;
                    D_80174B4C[i] = 0;
                } else {
                    s_CurrentPrim->drawMode ^= DRAW_HIDE;
                }
            }
            s_CurrentPrim = s_CurrentPrim->next;
        }
        break;
    case 2:
        isEntityAlive = false;
        s_CurrentPrim = &g_PrimBuf[self->primIndex];
        for (i = 0; i < nPrim; i++) {
            if (D_80174B4C[i]) {
                if (D_80174BCC[i]) {
                    s_CurrentPrim->x0 = s_CurrentPrim->x2 =
                        D_80174B8C[i].x + D_80174BEC[i] * XS / 256;
                    s_CurrentPrim->x1 = s_CurrentPrim->x3 =
                        D_80174B8C[i].x - D_80174BEC[i] * XE / 256;
                } else {
                    s_CurrentPrim->x0 = s_CurrentPrim->x2 =
                        D_80174B8C[i].x - D_80174BEC[i] * XS / 256;
                    s_CurrentPrim->x1 = s_CurrentPrim->x3 =
                        D_80174B8C[i].x + D_80174BEC[i] * XE / 256;
                }
                s_CurrentPrim->y0 = s_CurrentPrim->y1 =
                    D_80174B8C[i].y - D_80174BEC[i] * YS / 256;
                s_CurrentPrim->y2 = s_CurrentPrim->y3 =
                    D_80174B8C[i].y + D_80174BEC[i] * YE / 256;
                s_CurrentPrim->r0 = s_CurrentPrim->r1 = s_CurrentPrim->r2 =
                    s_CurrentPrim->r3 = s_CurrentPrim->g0 = s_CurrentPrim->g1 =
                        s_CurrentPrim->g2 = s_CurrentPrim->g3 = s_CurrentPrim->b0 =
                            s_CurrentPrim->b1 = s_CurrentPrim->b2 = s_CurrentPrim->b3 =
                                D_80174C0C[i];
                s_CurrentPrim->r0 = s_CurrentPrim->r1 = s_CurrentPrim->r2 =
                    s_CurrentPrim->r3 = s_CurrentPrim->g0 = s_CurrentPrim->g1 =
                        s_CurrentPrim->g2 = s_CurrentPrim->g3 = s_CurrentPrim->b0 =
                            s_CurrentPrim->b1 = s_CurrentPrim->b2 = s_CurrentPrim->b3 =
                                D_80174C0C[i];
                D_80174BEC[i] -= 8;
                D_80174C0C[i] -= 8;
                if (D_80174C0C[i] < 81) {
                    s_CurrentPrim->drawMode |= DRAW_HIDE;
                    D_80174B4C[i] = 0;
                } else {
                    s_CurrentPrim->drawMode ^= DRAW_HIDE;
                }
            }
            isEntityAlive |= D_80174B4C[i];
            s_CurrentPrim = s_CurrentPrim->next;
        }

        if (isEntityAlive == false) {
            DestroyEntity(self);
            return;
        }
        break;
    }
}

#ifndef VERSION_PSP
void unused_3C0C(Entity* self) {}
#else
void unused_3C0C(void) {}
#endif

void unused_3C14(void) {}

void unused_3C1C(void) {}

void unused_3C24(void) {}

#include "../destroy_servant_entity.h"

#ifndef VERSION_PSP
#include "../servant_update_anim.h"
#endif

#include "../../destroy_entity.h"

#ifndef VERSION_PSP
#include "../accumulate_toward_zero.h"
#include "../search_for_entity_in_range.h"
#endif

#include "../calculate_angle_to_entity.h"

#include "../get_target_position_with_distance_buffer.h"

#ifndef VERSION_PSP
#include "../calculate_distance.h"
#include "../play_sfx.h"
#endif

#include "../process_event.h"

#include "../create_event_entity.h"

#include "../is_movement_allowed.h"

#ifndef VERSION_PSP
#include "../check_all_entities_valid.h"
#endif

#include "../servant_unk0.h"

#ifdef VERSION_PSP
extern ServantDesc bat_ServantDesc;
void func_092EC220(void) {
    memcpy((u8*)&D_8D1DC40, (u8*)&bat_ServantDesc, sizeof(ServantDesc));
}
#endif
