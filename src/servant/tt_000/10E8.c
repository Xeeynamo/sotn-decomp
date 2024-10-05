// SPDX-License-Identifier: AGPL-3.0-or-later
#include <servant.h>
#include <sfx.h>
#include <psxsdk/libc.h>

#ifndef VERSION_PSP
s32 D_801748D8[0x80];
Collider D_80174AD8;
s16 D_80174AFC, D_80174AFC_;
s16 D_80174B00, D_80174B00_;
s16 D_80174B04, D_80174B04_;
s16 D_80174B08, D_80174B08_;
s16 D_80174B0C, D_80174B0C_;
s16 D_80174B10, D_80174B10_;
s16 D_80174B14, D_80174B14_;
s16 D_80174B18, D_80174B18_;
s32 D_80174B1C;
s32 D_80174B20;
s32 D_80174B24;
s32 D_80174B28;
s32 D_80174B2C;
s32 D_80174B2C;
s32 D_80174B30;
s32 D_80174B34;
s16 D_80174B38, D_80174B38_;
s16 D_80174B3C, D_80174B3C_;
s16 D_80174B40, D_80174B40_;
s16 D_80174B44, D_80174B44_;
Primitive* D_80174B48;
s32 D_80174B4C[16];
Point16 D_80174B8C[16];
s16 D_80174BCC[16];
s16 D_80174BEC[16];
s16 D_80174C0C[16];
s32 D_80174C2C;
FamiliarStats D_80174C30;
Point16 D_80174C3C[4][16];
s32 g_IsServantDestroyed;
s32 D_80174D40;
s32 _unused[26];

void func_80171ED4(s32 arg0);
void func_80172120(Entity* self);
void func_80172C30(Entity* self);
void func_8017339C(void);
void func_801733A4(void);
void func_801733AC(void);
void func_801733B4(void);
void func_801733BC(void);
void func_801733C4(void);
void func_801733CC(void);
void BatFamiliarBlueTrail(Entity* self);
void func_80173C0C(Entity* self);
void func_80173C14(void);
void func_80173C1C(void);
void func_80173C24(void);
void DestroyServantEntity(Entity* self);

ServantDesc g_ServantDesc = {
    ServantInit,   func_80172120, func_80172C30,        func_8017339C,
    func_801733A4, func_801733AC, func_801733B4,        func_801733BC,
    func_801733C4, func_801733CC, BatFamiliarBlueTrail, func_80173C0C,
    func_80173C14, func_80173C1C, func_80173C24,        DestroyServantEntity,
};
#endif

#ifdef VERSION_PSP
extern FamiliarStats D_80174C30;
extern s32 D_801748D8[0x80];

extern Collider D_80174AD8;
extern s16 D_80174AFC;
extern s16 D_80174B00;
extern s16 D_80174B04;
extern s16 D_80174B08;
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
extern Primitive* D_80174B48;
extern s32 D_80174B4C[16];
extern Point16 D_80174B8C[16];
extern s16 D_80174BCC[16];
extern s16 D_80174BEC[16];
extern s16 D_80174C0C[16];
extern s32 D_80174C2C;
extern FamiliarStats D_80174C30;
extern Point16 D_80174C3C[4][16];
extern s32 g_IsServantDestroyed;
extern s32 D_80174D40;
#endif

#include "../set_entity_animation.h"

Entity* func_8017110C(Entity* self) {
    const int EntitySearchCount = 128;
    s32 foundIndex;
    s32 i;
    u32 found;
    Entity* e;
    s32 distance;

    found = 0;
    e = &g_Entities[STAGE_ENTITY_START];
    for (i = 0; i < EntitySearchCount; i++, e++) {
        D_801748D8[i] = 0;
        if (!e->entityId) {
            continue;
        }
        if (e->hitboxState == 0) {
            continue;
        }
        if (e->flags & FLAG_UNK_00200000) {
            continue;
        }
        if (e->posX.i.hi < -0x10) {
            continue;
        }
        if (e->posX.i.hi > 0x110) {
            continue;
        }
        if (e->posY.i.hi > 0xF0) {
            continue;
        }
        if (e->posY.i.hi < 0) {
            continue;
        }
        if (e->hitboxState & 8 && !D_80170658[D_80174C30.level / 10][4]) {
            continue;
        }
        if (abs(self->posX.i.hi - e->posX.i.hi) < 64 &&
            abs(self->posY.i.hi - e->posY.i.hi) < 64) {
            continue;
        }
        if (!self->facingLeft && self->posX.i.hi < e->posX.i.hi) {
            continue;
        }
        if (self->facingLeft && self->posX.i.hi > e->posX.i.hi) {
            continue;
        }
        if (e->hitPoints >= 0x7000) {
            continue;
        }

        if (e->flags & FLAG_UNK_80000) {
            if (e->hitPoints >= D_80170658[D_80174C30.level / 10][3]) {
                found++;
                D_801748D8[i] = 1;
            }
        } else {
            e->flags |= FLAG_UNK_80000;
            return e;
        }
    }

    if (found > 0) {
        foundIndex = D_80174D40 % EntitySearchCount;
        for (i = 0; i < 0x80; i++) {
            if (D_801748D8[foundIndex]) {
                e = &g_Entities[STAGE_ENTITY_START + foundIndex];
                D_80174D40 = (foundIndex + 1) % EntitySearchCount;
                return e;
            }
            foundIndex = (foundIndex + 1) % EntitySearchCount;
        }
    }

    return NULL;
}

#include "../check_entity_valid.h"

#ifndef VERSION_PSP
bool func_80171434(s16 x, s16 y, s16* outX, s16* outY) {
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

void func_80171560(Entity* self) {}

// Only ever called by func_80172120 so that is the parent
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
        // BatFamiliarBlueTrail
        entity->entityId = 0xDA;
        entity->zPriority = parent->zPriority;
        entity->facingLeft = parent->facingLeft;
        entity->flags = FLAG_KEEP_ALIVE_OFFCAMERA;
        entity->posX.val = parent->posX.val;
        entity->posY.val = parent->posY.val;
        entity->ext.batFamBlueTrail.parent = parent;
    }
}

void func_8017160C(s32 amount, s32 entityId) {
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

    x += (rsin(entity->ext.bat.unk8C << 7) * 8) >> 12;
    y -= entity->ext.bat.unk8C / 2;

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
        case 0xD1:
            self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
            if (self->primIndex == -1) {
                DestroyEntity(self);
                return;
            }
            func_8017170C(self, 0);
            self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA |
                          FLAG_HAS_PRIMS | FLAG_UNK_20000;
            SetEntityAnimation(self, D_801704A8);
            self->ext.bat.unk84 = rand() % 4096;
            self->ext.bat.unk86 = 0;
            self->ext.bat.unk88 = 0xC;
            self->ext.bat.unk8C = rand() % 4096;
            self->ext.bat.unk8A = 0x20;
            self->step++;
            break;
        case 0xD2:
            self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
            if (self->primIndex == -1) {
                DestroyEntity(self);
                return;
            }
            func_8017170C(self, 0);
            self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA |
                          FLAG_UNK_02000000 | FLAG_HAS_PRIMS | FLAG_UNK_20000;
            SetEntityAnimation(self, D_801704A8);
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
        case 0xD1:
            self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA |
                          FLAG_HAS_PRIMS | FLAG_UNK_20000;
            SetEntityAnimation(self, D_801704A8);
            self->ext.bat.unk8C = rand() % 4096;
            self->step++;
            break;
        case 0xD2:
            self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA |
                          FLAG_UNK_02000000 | FLAG_HAS_PRIMS | FLAG_UNK_20000;
            SetEntityAnimation(self, D_801704A8);
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
    g_api.func_8011A3AC(self, 0, 0, &D_80174C30);
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
    src = D_80170720;

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
    *spriteBanks = (SpriteParts*)D_80170040;

    e = &g_Entities[4];

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
        if (D_8003C708.flags & STAGE_INVERTEDCASTLE_FLAG) {
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
    g_IsServantDestroyed = 0;
}

s16 GetTargetPositionWithDistanceBuffer(
    s16 currentX, s16 targetX, s16 distanceBuffer);

#ifdef VERSION_PSP
INCLUDE_ASM("servant/tt_000/nonmatchings/10E8", func_80172120);
#else
void func_80172120(Entity* self) {
    g_api.func_8011A3AC(self, 0, 0, &D_80174C30);
    if (g_IsServantDestroyed != 0) {
        self->zPriority = PLAYER.zPriority - 2;
    }
    if (D_8003C708.flags & 0x20) {
        switch (ServantUnk0()) {
        case 0:
            D_80174B04 = 0x40;
            break;
        case 1:
            D_80174B04 = 0xC0;
            break;
        case 2:
            D_80174B04 = (self->posX.i.hi > 0x80) ? 0xC0 : 0x40;
            break;
        }
        D_80174B08 = 0xA0;
    } else {
        D_80174B18 = -0x12;
        if (PLAYER.facingLeft) {
            D_80174B18 = -D_80174B18;
        }
        D_80174B04 = PLAYER.posX.i.hi + D_80174B18;
        D_80174B08 = PLAYER.posY.i.hi - 0x22;
    }
    D_80174B0C = self->ext.bat.unk84;
    self->ext.bat.unk84 += 0x10;
    D_80174B14 = self->ext.bat.unk88;
    D_80174AFC = D_80174B04 + ((rcos(D_80174B0C) >> 4) * D_80174B14 >> 8);
    D_80174B00 = D_80174B08 - ((rsin(D_80174B0C / 2) >> 4) * D_80174B14 >> 8);
    switch (self->step) {
    case 0:
        func_801719E0(self);
        break;
    case 1:
        if (g_Player.unk0C & PLAYER_STATUS_BAT_FORM) {
            self->ext.bat.unk8C = 0;
            self->step = 5;
            break;
        }
        if (D_8003C708.flags & 0x20) {
            if (PLAYER.posX.i.hi >= self->posX.i.hi) {
                self->facingLeft = true;
            } else {
                self->facingLeft = false;
            }
        } else {
            if (PLAYER.facingLeft == self->facingLeft) {
                if (abs(D_80174AFC - self->posX.i.hi) <= 0) {
                    self->facingLeft = PLAYER.facingLeft ? false : true;
                } else {
                    if (self->facingLeft && D_80174AFC < self->posX.i.hi) {
                        self->facingLeft = PLAYER.facingLeft ? false : true;
                    } else if (
                        !self->facingLeft && D_80174AFC > self->posX.i.hi) {
                        self->facingLeft = PLAYER.facingLeft ? false : true;
                    }
                }
            } else if (
                self->facingLeft && (self->posX.i.hi - D_80174AFC) > 0x1F) {
                self->facingLeft = PLAYER.facingLeft;
            } else if (
                !self->facingLeft && (D_80174AFC - self->posX.i.hi) > 0x1F) {
                self->facingLeft = PLAYER.facingLeft;
            }
        }
        D_80174B0C = CalculateAngleToEntity(self, D_80174AFC, D_80174B00);
        D_80174B10 = GetTargetPositionWithDistanceBuffer(
            D_80174B0C, self->ext.bat.unk86, self->ext.bat.unk8A);
        self->ext.bat.unk86 = D_80174B10;
        D_80174B04 = D_80174AFC - self->posX.i.hi;
        D_80174B08 = D_80174B00 - self->posY.i.hi;
        D_80174B14 =
            SquareRoot12(
                (D_80174B04 * D_80174B04 + D_80174B08 * D_80174B08) << 12) >>
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
            self->velocityX = (D_80174AFC - self->posX.i.hi) << 0xE;
            self->velocityY = (D_80174B00 - self->posY.i.hi) << 0xE;
            self->ext.bat.unk8A = 0x80;
        }
        if (self->velocityY > FIX(1.0)) {
            SetEntityAnimation(self, D_801705EC);
        } else if (D_80174B14 < 60) {
            SetEntityAnimation(self, D_801704A8);
        } else if (D_80174B14 > 100) {
            SetEntityAnimation(self, D_80170514);
        }
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        if (D_8003C704) {
            break;
        }
        D_80174B24 = D_80174AFC - self->posX.i.hi;
        D_80174B28 = D_80174B00 - self->posY.i.hi;
        D_80174B2C =
            SquareRoot12(
                (D_80174B24 * D_80174B24 + D_80174B28 * D_80174B28) << 12) >>
            12;
        if (D_80174B2C < 0x18) {
            if (self->ext.bat.unk8E) {
                self->ext.bat.unk8E = 0;
                SetEntityAnimation(self, D_8017054C);
            }
            self->ext.bat.unk8C++;
            if (self->ext.bat.unk8C > D_80170658[D_80174C30.level / 10][0]) {
                self->ext.bat.unk8C = 0;
                // Pay attention - this is not a ==
                if (self->ext.bat.target = func_8017110C(self)) {
                    self->step++;
                }
            }
        } else {
            self->ext.bat.unk8E = 1;
        }
        break;
    case 2:
        self->ext.bat.unk8C++;
        if (self->ext.bat.unk8C == 1) {
            g_api.PlaySfx(SFX_UI_ALERT_TINK);
            func_8017170C(self, 1);
        } else if (self->ext.bat.unk8C > 30) {
            self->ext.bat.unk8C = 0;
            func_8017170C(self, 0);
            D_80174B1C = self->ext.bat.target->posX.i.hi;
            D_80174B20 = self->ext.bat.target->posY.i.hi;
            self->hitboxWidth = 5;
            self->hitboxHeight = 5;
            g_api.func_8011A3AC(self, 15, 1, &D_80174C30);
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
            D_80170658[D_80174C30.level / 10][1]);
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
            self->ext.bat.unk8C = 0;
            self->step++;
            SetEntityAnimation(self, D_8017054C);
        }
        break;
    case 4:
        D_80174B0C = CalculateAngleToEntity(self, D_80174AFC, D_80174B00);
        D_80174B10 = GetTargetPositionWithDistanceBuffer(
            D_80174B0C, self->ext.bat.unk86, 0x10);
        self->ext.bat.unk86 = D_80174B10;
        self->velocityX = rcos(D_80174B10) << 2 << 4;
        self->velocityY = -(rsin(D_80174B10) << 2 << 4);
        self->facingLeft = (self->velocityX >= 0) ? true : false;
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        self->ext.bat.unk8C++;
        if (self->ext.bat.unk8C > 30) {
            self->hitboxWidth = 0;
            self->hitboxHeight = 0;
            self->step = 1;
        }
        break;
    case 5:
        self->ext.bat.unk8C++;
        if (self->ext.bat.unk8C == 1) {
            g_api.PlaySfx(SFX_BAT_SCREECH);
            func_8017170C(self, 3);
        } else if (self->ext.bat.unk8C > 30) {
            func_8017170C(self, 0);
            self->entityId = 0xD2;
            self->step = 0;
        }
        func_801718A0(self);
        break;
    }
    ProcessEvent(self, false);
    func_80171560(self);
    g_api.UpdateAnim(NULL, D_801705F4);
}
#endif

#ifdef VERSION_PSP
INCLUDE_ASM("servant/tt_000/nonmatchings/10E8", func_80172C30);
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

    g_api.func_8011A3AC(self, 0, 0, &D_80174C30);
    if (g_IsServantDestroyed != 0) {
        self->zPriority = PLAYER.zPriority - 2;
    }
    switch (self->step) {
    case 0:
        func_801719E0(self);
        if (!self->ext.bat.unk82) {
            func_8017160C(D_80170658[D_80174C30.level / 10][2], 0xD2);
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
                SetEntityAnimation(self, D_801704A8);
            }
            self->ext.bat.unk8E = true;
        }
        self->facingLeft = PLAYER.facingLeft ? false : true;
        if (!self->ext.bat.unkA8) {
            if (g_Player.unk0C & PLAYER_STATUS_UNK800) {
                // This causes the bat familiar to shoot a fireball when the
                // player does so in bat form.
                g_api.CreateEntFactoryFromEntity(self, FACTORY(81, 1), 0);
                self->ext.bat.unkA8 = 1;
            }
        } else if (self->ext.bat.unkA8) {
            if (!(g_Player.unk0C & PLAYER_STATUS_UNK800)) {
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
        if (!(g_Player.unk0C & PLAYER_STATUS_BAT_FORM)) {
            self->ext.bat.unk8C = 0;
            self->step++;
        }
        break;
    case 2:
        self->ext.bat.unk8C++;
        if (self->ext.bat.unk8C == 1) {
            if (!self->ext.bat.unk82) {
                g_api.PlaySfx(SFX_BAT_SCREECH);
            }
            func_8017170C(self, 2);
        } else if (self->ext.bat.unk8C >= 0x1F) {
            func_8017170C(self, 0);
            if (!self->ext.bat.unk82) {
                self->entityId = 0xD1;
                self->step = 0;
                break;
            }
            self->step++;
            D_80174C3C[self->ext.bat.unk82][0].x =
                PLAYER.facingLeft ? -0x80 : 0x180;
            D_80174C3C[self->ext.bat.unk82][0].y = rand() % 256;
            SetEntityAnimation(self, D_801704A8);
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
    func_80171560(self);
    g_api.UpdateAnim(NULL, D_801705F4);
}
#endif

void func_8017339C(void) {}

void func_801733A4(void) {}

void func_801733AC(void) {}

void func_801733B4(void) {}

void func_801733BC(void) {}

void func_801733C4(void) {}

void func_801733CC(void) {}

// When bat familiar swoops toward enemy to attack, it leaves a trail of blue
// bat outlines behind it, not unlike Alucard's wing smash bat outlines.
void BatFamiliarBlueTrail(Entity* self) {
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
            D_80174B48 = &g_PrimBuf[self->primIndex];
            for (i = 0; i < nPrim; i++) {
                D_80174B48->tpage = 0x1B;
                D_80174B48->clut = 0x143;
                D_80174B48->u0 = D_80174B48->u2 = 64;
                D_80174B48->v0 = D_80174B48->v1 = 0;
                D_80174B48->u1 = D_80174B48->u3 = 88;
                D_80174B48->v2 = D_80174B48->v3 = 32;
                D_80174B48->priority = self->zPriority;
                D_80174B48->drawMode = 0x15 | DRAW_HIDE;
                D_80174B48 = D_80174B48->next;
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
        D_80174B48 = &g_PrimBuf[self->primIndex];
        for (i = 0; i < nPrim; i++) {
            if (D_80174B4C[i]) {
                if (D_80174BCC[i]) {
                    D_80174B48->x0 = D_80174B48->x2 =
                        D_80174B8C[i].x + D_80174BEC[i] * XS / 256;
                    D_80174B48->x1 = D_80174B48->x3 =
                        D_80174B8C[i].x - D_80174BEC[i] * XE / 256;
                } else {
                    D_80174B48->x0 = D_80174B48->x2 =
                        D_80174B8C[i].x - D_80174BEC[i] * XS / 256;
                    D_80174B48->x1 = D_80174B48->x3 =
                        D_80174B8C[i].x + D_80174BEC[i] * XE / 256;
                }
                D_80174B48->y0 = D_80174B48->y1 =
                    D_80174B8C[i].y - D_80174BEC[i] * YS / 256;
                D_80174B48->y2 = D_80174B48->y3 =
                    D_80174B8C[i].y + D_80174BEC[i] * YE / 256;
                D_80174B48->r0 = D_80174B48->r1 = D_80174B48->r2 =
                    D_80174B48->r3 = D_80174B48->g0 = D_80174B48->g1 =
                        D_80174B48->g2 = D_80174B48->g3 = D_80174B48->b0 =
                            D_80174B48->b1 = D_80174B48->b2 = D_80174B48->b3 =
                                D_80174C0C[i];
                D_80174BEC[i] -= 8;
                D_80174C0C[i] -= 8;
                if (D_80174C0C[i] < 81) {
                    D_80174B48->drawMode |= DRAW_HIDE;
                    D_80174B4C[i] = 0;
                } else {
                    D_80174B48->drawMode ^= DRAW_HIDE;
                }
            }
            D_80174B48 = D_80174B48->next;
        }
        break;
    case 2:
        isEntityAlive = false;
        D_80174B48 = &g_PrimBuf[self->primIndex];
        for (i = 0; i < nPrim; i++) {
            if (D_80174B4C[i]) {
                if (D_80174BCC[i]) {
                    D_80174B48->x0 = D_80174B48->x2 =
                        D_80174B8C[i].x + D_80174BEC[i] * XS / 256;
                    D_80174B48->x1 = D_80174B48->x3 =
                        D_80174B8C[i].x - D_80174BEC[i] * XE / 256;
                } else {
                    D_80174B48->x0 = D_80174B48->x2 =
                        D_80174B8C[i].x - D_80174BEC[i] * XS / 256;
                    D_80174B48->x1 = D_80174B48->x3 =
                        D_80174B8C[i].x + D_80174BEC[i] * XE / 256;
                }
                D_80174B48->y0 = D_80174B48->y1 =
                    D_80174B8C[i].y - D_80174BEC[i] * YS / 256;
                D_80174B48->y2 = D_80174B48->y3 =
                    D_80174B8C[i].y + D_80174BEC[i] * YE / 256;
                D_80174B48->r0 = D_80174B48->r1 = D_80174B48->r2 =
                    D_80174B48->r3 = D_80174B48->g0 = D_80174B48->g1 =
                        D_80174B48->g2 = D_80174B48->g3 = D_80174B48->b0 =
                            D_80174B48->b1 = D_80174B48->b2 = D_80174B48->b3 =
                                D_80174C0C[i];
                D_80174B48->r0 = D_80174B48->r1 = D_80174B48->r2 =
                    D_80174B48->r3 = D_80174B48->g0 = D_80174B48->g1 =
                        D_80174B48->g2 = D_80174B48->g3 = D_80174B48->b0 =
                            D_80174B48->b1 = D_80174B48->b2 = D_80174B48->b3 =
                                D_80174C0C[i];
                D_80174BEC[i] -= 8;
                D_80174C0C[i] -= 8;
                if (D_80174C0C[i] < 81) {
                    D_80174B48->drawMode |= DRAW_HIDE;
                    D_80174B4C[i] = 0;
                } else {
                    D_80174B48->drawMode ^= DRAW_HIDE;
                }
            }
            isEntityAlive |= D_80174B4C[i];
            D_80174B48 = D_80174B48->next;
        }

        if (isEntityAlive == false) {
            DestroyEntity(self);
            return;
        }
        break;
    }
}

#ifndef VERSION_PSP
void func_80173C0C(Entity* self) {}
#else
void func_80173C0C(void) {}
#endif

void func_80173C14(void) {}

void func_80173C1C(void) {}

void func_80173C24(void) {}

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
