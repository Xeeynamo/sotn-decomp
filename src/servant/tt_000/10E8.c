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
s32 D_80174D3C;
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
void func_80173C0C(void);
void func_80173C14(void);
void func_80173C1C(void);
void func_80173C24(void);
void func_80173C2C(Entity* self);

ServantDesc g_ServantDesc = {
    func_80171ED4, func_80172120, func_80172C30,        func_8017339C,
    func_801733A4, func_801733AC, func_801733B4,        func_801733BC,
    func_801733C4, func_801733CC, BatFamiliarBlueTrail, func_80173C0C,
    func_80173C14, func_80173C1C, func_80173C24,        func_80173C2C,
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
extern s32 D_80174D3C;
extern s32 D_80174D40;

void DestroyEntity(Entity* entity);
void ProcessEvent(Entity* self, bool resetEvent);
void CreateEventEntity(Entity* entityParent, s32 entityId, s32 params);
#endif

void func_801710E8(Entity* entity, AnimationFrame* anim) {
    if (entity->anim != anim) {
        entity->anim = anim;
        entity->animFrameIdx = 0;
        entity->animFrameDuration = 0;
    }
}

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
            func_801710E8(self, D_801704A8);
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
            func_801710E8(self, D_801704A8);
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
            func_801710E8(self, D_801704A8);
            self->ext.bat.unk8C = rand() % 4096;
            self->step++;
            break;
        case 0xD2:
            self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA |
                          FLAG_UNK_02000000 | FLAG_HAS_PRIMS | FLAG_UNK_20000;
            func_801710E8(self, D_801704A8);
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

void ProcessEvent(Entity* self, bool resetEvent);
extern u16 D_80170448[48];

void func_80171ED4(s32 arg0) {
    u16* dst;
    u16* src;
    RECT rect;
    s32 i;
    s32 x;
    SpriteParts** spriteBanks;
    Entity* e;

#ifdef VERSION_PC
    // i exceeds the size of D_80170448
    const int len = LEN(D_80170448);
#else
    const int len = 256;
#endif

    if ((arg0 == 1) || (arg0 == 3)) {
        ProcessEvent(NULL, true);
        if (arg0 == 3) {
            return;
        }
    }

    dst = &g_Clut[0x1400];
    src = D_80170448;

    for (i = 0; i < len; i++) {
        *dst++ = *src++;
    }

    dst = &g_Clut[0x1430];
    src = D_80170720;

    for (i = 0; i < 32; i++) {
        *dst++ = *src++;
    }

    rect.x = 0;
    rect.w = 0x100;
    rect.h = 1;
    rect.y = 0xF4;

    dst = &g_Clut[0x1400];
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

    if (arg0 == 1) {
        e->entityId = 0xD1;
        e->posX.val = 0x800000;
        e->posY.val = 0xFFE00000;
    } else {
        e->entityId = 0xD1;
        if (D_8003C708.flags & 0x20) {
            e->posX.val = func_80174864() ? 0xC00000 : 0x400000;
            e->posY.val = 0xA00000;
        } else {
            e->posX.val =
                (PLAYER.facingLeft ? +0x120000 : -0x120000) + PLAYER.posX.val;
            e->posY.val = PLAYER.posY.val - 0x220000;
        }
    }
    e->ext.bat.cameraX = g_Tilemap.scrollX.i.hi;
    e->ext.bat.cameraY = g_Tilemap.scrollY.i.hi;
    D_80174D3C = 0;
}

s16 func_80173F74(s16 x1, s16 x2, s16 minDistance);
s16 func_80173F30(Entity* entity, s16 x, s16 y);

#ifdef VERSION_PSP
INCLUDE_ASM("servant/tt_000/nonmatchings/10E8", func_80172120);
#else
void func_80172120(Entity* self) {
    g_api.func_8011A3AC(self, 0, 0, &D_80174C30);
    if (D_80174D3C != 0) {
        self->zPriority = PLAYER.zPriority - 2;
    }
    if (D_8003C708.flags & 0x20) {
        switch (func_80174864()) {
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
        if (g_Player.unk0C & 1) {
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
        D_80174B0C = func_80173F30(self, D_80174AFC, D_80174B00);
        D_80174B10 =
            func_80173F74(D_80174B0C, self->ext.bat.unk86, self->ext.bat.unk8A);
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
            func_801710E8(self, D_801705EC);
        } else if (D_80174B14 < 60) {
            func_801710E8(self, D_801704A8);
        } else if (D_80174B14 > 100) {
            func_801710E8(self, D_80170514);
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
                func_801710E8(self, D_8017054C);
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
            func_801710E8(self, D_801705EC);
            CreateBlueTrailEntity(self);
            self->step++;
        }
        break;
    case 3:
        D_80174B1C = self->ext.bat.target->posX.i.hi;
        D_80174B20 = self->ext.bat.target->posY.i.hi;
        D_80174B0C = func_80173F30(self, D_80174B1C, D_80174B20);
        D_80174B10 = func_80173F74(D_80174B0C, self->ext.bat.unk86,
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
            func_801710E8(self, D_8017054C);
        }
        break;
    case 4:
        D_80174B0C = func_80173F30(self, D_80174AFC, D_80174B00);
        D_80174B10 = func_80173F74(D_80174B0C, self->ext.bat.unk86, 0x10);
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
    if (D_80174D3C != 0) {
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
                func_801710E8(self, D_8017054C);
                self->ext.bat.unk8E = false;
            }
        } else {
            if (self->velocityY > FIX(1)) {
                func_801710E8(self, D_801705EC);
            } else {
                func_801710E8(self, D_801704A8);
            }
            self->ext.bat.unk8E = true;
        }
        self->facingLeft = PLAYER.facingLeft ? false : true;
        if (!self->ext.bat.unkA8) {
            if (g_Player.unk0C & 0x800) {
                // This causes the bat familiar to shoot a fireball when the
                // player does so in bat form.
                g_api.CreateEntFactoryFromEntity(self, FACTORY(81, 1), 0);
                self->ext.bat.unkA8 = 1;
            }
        } else if (self->ext.bat.unkA8) {
            if (!(g_Player.unk0C & 0x800)) {
                self->ext.bat.unkA8 = 0;
            }
        }
        D_80174B38 = self->ext.bat.follow->posX.i.hi - self->posX.i.hi;
        D_80174B3C = self->ext.bat.follow->posY.i.hi - self->posY.i.hi;
        D_80174B34 =
            SquareRoot12(((D_80174B38 * D_80174B38) + (D_80174B3C * D_80174B3C))
                         << 0xC) >>
            0xC;
        if (func_801746A0(0) || D_80174B34 >= 0x19) {
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
        if (!(g_Player.unk0C & 1)) {
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
            func_801710E8(self, D_801704A8);
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

void func_80173C0C(void) {}

void func_80173C14(void) {}

void func_80173C1C(void) {}

void func_80173C24(void) {}

void func_80173C2C(Entity* entity) {
    switch (entity->params) {
    case 15:
        D_80174D3C = 1;
        break;
    }
    DestroyEntity(entity);
}

#ifndef VERSION_PSP
u32 Tt000UpdateAnim(Entity* self, s8* frameProps, AnimationFrame** frames) {
    AnimationFrame* animFrame;
    s32 ret;

    ret = 0;
    if (self->animFrameDuration == -1) {
        ret = -1;
    } else if (self->animFrameDuration == 0) {
        self->animFrameDuration = self->anim[self->animFrameIdx].duration;
    } else if (--self->animFrameDuration == 0) {
        self->animFrameIdx++;
        animFrame = &self->anim[self->animFrameIdx];
        // Effectively a switch statement, but breaks if I actually use one.
        if (animFrame->duration == 0) {
            self->animFrameIdx = animFrame->unk2;
            self->animFrameDuration = self->anim[self->animFrameIdx].duration;
            ret = 0;
        } else if (animFrame->duration == 0xFFFF) {
            self->animFrameIdx--;
            self->animFrameDuration = -1;
            ret = -1;
        } else if (animFrame->duration == 0xFFFE) {
            self->anim = frames[animFrame->unk2];
            self->animFrameIdx = 0;
            ret = -2;
            self->animFrameDuration = self->anim->duration;
        } else {
            self->animFrameDuration = animFrame->duration;
        }
    }
    if (frameProps != NULL) {
        // This is ugly - theoretically the type for frameProps should be
        // FrameProperty* but anything besides this where we assign this big
        // expression fails.
        frameProps =
            &frameProps[(self->anim[self->animFrameIdx].unk2 >> 9) << 2];
        self->hitboxOffX = *frameProps++;
        self->hitboxOffY = *frameProps++;
        self->hitboxWidth = *frameProps++;
        self->hitboxHeight = *frameProps++;
    }
    self->animCurFrame = self->anim[self->animFrameIdx].unk2 & 0x1FF;
    return ret;
}
#endif

#include "../../destroy_entity.h"

#ifndef VERSION_PSP
s32 func_80173E78(s32 arg0, s32 arg1) {
    if (arg0 < 0) {
        arg0 += arg1;
        if (arg0 > 0) {
            arg0 = 0;
        }
    } else {
        arg0 -= arg1;
        if (arg0 < 0) {
            arg0 = 0;
        }
    }

    return arg0;
}

Entity* func_80173EB0(s32 rangeIndex, s32 entityId) {
    volatile u32 pad; // fake?
    s16 start = D_80171094[rangeIndex].start;
    s16 end = D_80171094[rangeIndex].end;
    Entity* entity = &g_Entities[start];
    s32 i;

    for (i = start; end >= i; i++, entity++) {
        if (entity->entityId == entityId) {
            return entity;
        }
    }

    return NULL;
}
#endif

s16 func_80173F30(Entity* entity, s16 x, s16 y) {
    s16 angle;
    s16 diffy;
    s16 diffx;

    diffx = x - entity->posX.i.hi;
    diffy = y - entity->posY.i.hi;
    angle = ratan2(-diffy, diffx) & 0xFFF;

    return angle;
}

s16 func_80173F74(s16 x1, s16 x2, s16 minDistance) {
    s16 diff = abs(x2 - x1);
    if (minDistance > diff) {
        minDistance = diff;
    }

    if (x2 < x1) {
        if (diff < 0x800) {
            x2 += minDistance;
        } else {
            x2 -= minDistance;
        }
    } else {
        if (diff < 0x800) {
            x2 -= minDistance;
        } else {
            x2 += minDistance;
        }
    }
    return x2 & 0xFFF;
}

#ifndef VERSION_PSP
s32 func_80173FE8(Entity* entity, s32 x, s32 y) {
    s32 diffX = x - entity->posX.i.hi;
    s32 diffY = y - entity->posY.i.hi;

    return SquareRoot12((SQ(diffX) + SQ(diffY)) << 12) >> 12;
}

void func_80174038(Entity* entity) {
    switch (entity->step) {
    case 0:
        entity->flags = FLAG_UNK_20000 | FLAG_KEEP_ALIVE_OFFCAMERA;
        if (D_8003C704 != 0) {
            D_80171090 = 99;
            DestroyEntity(entity);
            return;
        }
        if (g_api.CdSoundCommandQueueEmpty() != 0) {
            g_api.PlaySfx(SET_UNK_10);
            entity->step++;
        }
        break;

    case 1:
        if (g_api.func_80133950() != 0) {
            entity->step++;
        }
        break;
    case 2:
        g_api.PlaySfx(entity->params);
        entity->step++;
        break;

    case 3:
        if (g_api.func_80131F68() != 0) {
            entity->step++;
        }
        break;

    case 4:
        if (g_api.func_80131F68() == 0) {
            entity->step++;
        }
        break;

    case 5:
        if ((*(s32*)&D_8003C708.flags & 0x60) != 0) {
            D_80171090 = 99;
            DestroyEntity(entity);
            return;
        }
        if (g_api.CdSoundCommandQueueEmpty() != 0) {
            g_api.PlaySfx(SET_UNK_11);
            entity->step++;
        }
        break;

    case 6:
        if (g_api.func_80133950() != 0) {
            D_80171090 = 99;
            DestroyEntity(entity);
            return;
        }
        break;

    case 7:
        g_api.PlaySfx(SET_STOP_MUSIC);
        entity->step = 4;
        break;

    case 8:
        D_80171090 = 99;
        DestroyEntity(entity);
        return;
    }

    D_80171090 = entity->step;
}
#endif

extern ServantEvent g_Events[];
extern ServantEvent* g_EventQueue;
extern u32 g_CurrentServant;
extern s32 g_CurrentRoomX;
extern s32 g_CurrentRoomY;

// Trigger an event under certain specific set of conditions
void ProcessEvent(Entity* self, bool resetEvent) {
    ServantEvent* evt;
    ServantEvent* queue;
    s32 cameraX;
    s32 cameraY;
    s32 i;

    if (resetEvent) {
        g_CurrentRoomY = 0;
        g_CurrentRoomX = 0;
        g_CurrentServant = 0;
        return;
    }

    cameraX = g_Tilemap.scrollX.i.hi;
    cameraY = g_Tilemap.scrollY.i.hi;
    // Ensures the following block is only evaluated once per room
    if (g_CurrentServant != g_Servant || g_CurrentRoomX != g_Tilemap.left ||
        g_CurrentRoomY != g_Tilemap.top) {
        g_CurrentServant = g_Servant;
        g_CurrentRoomX = g_Tilemap.left;
        g_CurrentRoomY = g_Tilemap.top;
        queue = g_EventQueue;
        for (i = 1; g_Events[i].roomX != -1; i++) {
            evt = &g_Events[i];
            // Filter by familiar
            if (evt->servantId != -1 && evt->servantId != g_CurrentServant) {
                continue;
            }

#if defined(VERSION_US)
            if (evt->roomX < 0) {
                if (!(g_StageId & STAGE_INVERTEDCASTLE_FLAG)) {
                    continue;
                }
                goto block_13;
            }
            if (!(g_StageId & STAGE_INVERTEDCASTLE_FLAG)) {
            block_13:
#elif defined(VERSION_HD) || defined(VERSION_PSP)
            if (evt->roomX >= 0 ||
                (g_StageId >= STAGE_RNO0 && g_StageId < STAGE_RNZ1_DEMO)) {
#endif
                if (abs(evt->roomX) != g_CurrentRoomX ||
                    evt->roomY != g_CurrentRoomY) {
                    continue;
                }

                if (evt->cameraX == cameraX && evt->cameraY == cameraY &&
                    (evt->condition == -1 ||
                     (!(evt->condition & 0x80000000) ||
                      !g_CastleFlags[evt->condition & 0xFFFF]) &&
                         (!(evt->condition & CHECK_RELIC_FLAG) ||
                          !(g_Status.relics[evt->condition & 0xFFFF] &
                            RELIC_FLAG_FOUND)))) {
                    evt->timer = 0;
                    if (evt->delay == 0) {
                        CreateEventEntity(self, evt->entityId, evt->params);
                        if (evt->unk2C) {
                            continue;
                        }
                    }
                }
                if (evt->delay > 0) {
                    evt->timer = evt->delay - 1;
                }
                queue->next = evt;
                queue = evt;
            }
        }
        queue->next = NULL;
    } else {
        queue = g_EventQueue;
        while (queue->next != NULL) {
            if (!evt->delay) {
            }
            if (queue->next->cameraX == cameraX &&
                queue->next->cameraY == cameraY &&
                (queue->next->condition == -1 ||
                 (!(queue->next->condition & 0x80000000) ||
                  !g_CastleFlags[queue->next->condition & 0xFFFF]) &&
                     (!(queue->next->condition & CHECK_RELIC_FLAG) ||
                      !(g_Status.relics[queue->next->condition & 0xFFFF] &
                        1)))) {
                if (queue->next->timer > 0) {
                    queue->next->timer--;
                } else {
                    CreateEventEntity(
                        self, queue->next->entityId, queue->next->params);
                    if (queue->next->unk2C) {
                        queue->next = queue->next->next;
                        continue;
                    } else {
                        queue->next->timer = queue->next->delay;
                    }
                }
            }
            queue = queue->next;
        }
    }
}
