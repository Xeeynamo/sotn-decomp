// SPDX-License-Identifier: AGPL-3.0-or-later
#include <stdint.h>
#include "../../warp.h"

extern void* volatile SpGourTbl;
extern SaturnSpriteFrameHeader* g_WarpSpriteBank16Frames[];
extern s32 g_WarpBackgroundPhase;
extern s32 g_WarpActive;
extern Point16 g_WarpRoomCoords[6];
extern s32 g_WarpBackgroundAngles[16];
extern s32 DAT_060E2490;
extern s32 DAT_060E2494;
extern s32 DAT_060E2498;

s32 AllocPrimitives(s32 type, s32 count);
void CreateEntityFromCurrentEntity(u16 entityId, Entity* entity);
void PlaySfxPositional(s32 sfxId);
void StartColorOffsetFade(s32, s32);
s32 rcos(s32 angle);
s32 rsin(s32 angle);
u16 SPR_2LookupTblNoToVram(u16 tableNo);
void func_060DC4D4(Entity* self);
void func_060DC7D8(Entity* self);

typedef struct {
    Primitive* primBg;
    s32 unk7C;
    Primitive* primFade;
    s32 unk84;
    u16 fade;
    u16 fadeOut;
    Primitive* primClip;
} ET_WarpRoom;

typedef struct {
    s32 unk78[3];
    s32 timer;
} ET_WarpSmallRock;

#define PLAYER_STATUS_READY_MASK 0xC5CF3EF7
#define WRP_UNLOCKS 0xD0

extern u16 g_WarpEInitExplosion[5];

extern SaturnSpriteFrameHeader* g_SaturnSharedSpriteBank3Frames[];
extern void (*func_8010E168)(s32, s32);
extern void (*DAT_06064588)(s32 resetAnims, s32 arg1);
extern void* volatile SpGourTbl;

s32 PlaySfxVolPan(s32 sfxId, s32 sfxVol, s16 sfxPan);
s32 GetSideToPlayer2(Entity* self);
s32 func_060DF528(Entity* entity);
s32 func_060DF580(Entity* self);

typedef struct {
    s32 unk78;
    s32 unk7C;
    s16 angle;
    s16 offsetX;
    Primitive* prims;
    Primitive* prim88;
} ET_WarpDoor;

_Static_assert(__builtin_offsetof(ET_WarpDoor, prims) ==
                   __builtin_offsetof(ET_PrimHolder, prim),
               "door");
_Static_assert(sizeof(ET_WarpDoor) <= sizeof(Ext), "ext size");

#define DOOR(e) ((ET_WarpDoor*)&(e)->ext)

extern s16 g_WarpPrizeDropOffsets[4];
extern struct {
    s8 values[2];
    u8 padding[2];
} g_WarpHeartPrizes;
extern void* volatile SpGourTbl;

typedef struct {
    s32 unk78;
    u8 aliveTimer;
    u8 pad7D[3];
    s32 fallSpeed;
    s16 gravity;
    s16 sparkleTimer;
    s32 unk88;
    s32 unk8C;
    s32 castleFlag;
} ET_WarpPrizeDrop;

_Static_assert(__builtin_offsetof(ET_WarpPrizeDrop, fallSpeed) ==
                   __builtin_offsetof(ET_EquipItemDrop, fallSpeed),
               "fallSpeed");
_Static_assert(__builtin_offsetof(ET_WarpPrizeDrop, castleFlag) ==
                   __builtin_offsetof(ET_EquipItemDrop, castleFlag),
               "castleFlag");

extern u16 g_WarpEInitExplosion[5];
#include <string.h>
#include "../../game.h"

extern s16 g_WarpPrizeDropOffsets[];

extern void* volatile SpGourTbl;

typedef struct {
    u16 blinkTimer;
    u8 pad7A[2];
    u8 aliveTimer;
    u8 pad7D[0xB];
    s16 iconSlot;
    u8 pad8A[6];
    s32 castleFlag;
} ET_WarpEquipDrop;

_Static_assert(__builtin_offsetof(ET_WarpEquipDrop, castleFlag) ==
                   __builtin_offsetof(ET_EquipItemDrop, castleFlag),
               "castleFlag");

extern void* volatile SpGourTbl;

extern void* volatile SpGourTbl;

typedef struct {
    u16 timer;
    u16 size;
    s32 speed;
    s32 accelY[12];
} ET_WarpEnemyBlood;

_Static_assert(sizeof(ET_WarpEnemyBlood) <= sizeof(Ext), "ext size");

static u16 Gray15(u32 c);

static void HoldPlayer(s32 timer, s32 zPriority);
static s32 BgComponent(s32 k);

static u16 FlagsToVram(u16 flags);

static u16* GourEntry(Primitive* prim);

static u16 Gray15_b5(u32 c);

static u16 Gray15(u32 c) { return (c << 10) + (c << 5) + c + 0x8000; }

static void HoldPlayer(s32 timer, s32 zPriority) {
    g_Player.padSim = 0;
    g_Player.demo_timer = timer;
    DAT_0605C668 = 0;
    if (zPriority) {
        ((s32*)&g_unkGraphicsStruct)[4] = zPriority;
        if (PLAYER.unk0 != NULL) {
            PLAYER.unk0->zPriority = zPriority;
        }
    }
}

void func_060DC040(Entity* self) {
    ET_WarpRoom* ext = (ET_WarpRoom*)&self->ext;
    Entity* entity;
    s32 primIndex, i, moveX, moveY, room;
    u16 c;

    switch (self->step) {
    case 0:
        TekiInit(self, 5);
        self->step++;
        primIndex = AllocPrimitives(3, 26);
        if (primIndex == -1) {
            self->step = 0;
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        func_060DC4D4(self);
        DAT_060E2490 = 0x100;
        for (i = 0; i < 32; i++) {
            entity = AllocEntity(&g_Entities[160], &g_Entities[256]);
            if (entity != NULL) {
                CreateEntityFromCurrentEntity(23, entity);
                entity->posY.i.hi = 0xCC - g_Tilemap.scrollY.i.hi;
                entity->posX.i.hi = (Random() & 0x7F) + 0x60;
            }
        }
        self->hitboxState = 1;
        self->hitboxOffY += 16;
        self->hitboxWidth = 2;
        self->hitboxHeight = 16;
        g_CastleFlags[WRP_UNLOCKS] |= 1;
        g_CastleFlags[WRP_UNLOCKS] |= 1 << self->params;
        g_WarpActive = 0;
        if ((u32)(PLAYER.posX.i.hi + g_Tilemap.scrollX.i.hi - 121) <= 78) {
            g_Player.padSim = 0;
            g_Player.demo_timer = 16;
            DAT_0605C668 = 0;
            self->step = 5;
            g_WarpActive = 1;
            break;
        }
    case 1:
        if (!self->hitFlags || !(g_pads[0].pressed & 0x1000) || D_80097C98 ||
            (g_Player.status & PLAYER_STATUS_READY_MASK)) {
            break;
        }
        g_Player.padSim = 0;
        g_Player.demo_timer = 0x80;
        DAT_0605C668 = 0;
        PLAYER.velocityX = 0;
        PLAYER.velocityY = 0;
        self->step++;
        break;
    case 2:
        HoldPlayer(0x80, 9);
        ext->fade += 2;
        c = (ext->fade >> 4) + 0x10;
        ext->primFade->unk6 = Gray15(c);
        if (ext->fade > 96) {
            g_WarpActive = 1;
            PlaySfx(0x636);
            StartColorOffsetFade(2, 127);
            self->step++;
        }
        break;
    case 3:
        HoldPlayer(0x80, 9);
        ext->primFade->drawMode = 49;
        if (ext->fade <= 0xEF) {
            ext->fade += 2;
            c = (ext->fade >> 4) + 0x10;
            ext->primFade->unk6 = Gray15(c);
        }
        if (DAT_0605BECC == 0) {
            self->step++;
        }
        break;
    case 4:
        room = self->params + 1;
        for (i = 0;;) {
            if (room > 5) {
                room = 0;
            }
            if ((g_CastleFlags[WRP_UNLOCKS] >> room) & 1) {
                break;
            }
            i++;
            room++;
            if (i > 5) {
                break;
            }
        }
        DAT_060E2498 = room;
        moveX = g_WarpRoomCoords[room].x - g_Tilemap.left;
        moveY = g_WarpRoomCoords[room].y - g_Tilemap.top;
        PLAYER.posX.i.hi += moveX * 0x140;
        PLAYER.posY.i.hi += moveY << 8;
        self->step = 0x80;
        D_80097C98 = 2;
        break;
    case 5:
        HoldPlayer(16, 0x90);
        ext->fade = 0;
        ext->primFade->unk6 = (s16)0xC210;
        ext->fadeOut = 0xF8;
        self->step++;
    case 6:
        g_Player.padSim = 0;
        g_Player.demo_timer = 16;
        DAT_0605C668 = 0;
        ext->fadeOut -= 4;
        if (DAT_0605BECC == 0) {
            ext->fadeOut = 0;
            DAT_0605C668 = 1;
            self->step = 1;
        }
        if (ext->fadeOut <= 39) {
            g_WarpActive = 0;
        }
        break;
    }
    func_060DC7D8(self);
}

void func_060DC4D4(Entity* self) {
    ET_WarpRoom* ext = (ET_WarpRoom*)&self->ext;
    Primitive* prim = &g_PrimBuf[self->primIndex];
    u16* gour;
    s32 x = self->posX.i.hi;
    s32 y = self->posY.i.hi;
    s32 sin, cos, i, k;

    ext->primClip = prim;
    prim->type = 0x1008;
    prim->x0 = 0x78;
    prim->y0 = 0x70;
    prim->x2 = 0xC7;
    prim->y2 = 0xBB;
    prim->priority = 1;
    prim->drawMode = 0;
    prim = prim->next;
    prim->type = 0x1008;
    prim->x0 = DAT_0605AEA0[0].x;
    prim->y0 = DAT_0605AEA0[0].y;
    prim->x2 = DAT_0605AEA0[1].x;
    prim->y2 = DAT_0605AEA0[1].y;
    prim->priority = 32;
    prim->drawMode = 0;
    prim = prim->next;
    ext->primBg = prim;
    for (i = 0; i < 16; i++, prim = prim->next) {
        prim->type = 0x1004;
        prim->unk4 = 0x4C0 | 4;
        prim->unk6 = (s16)0xFFFF;
        gour = (u16*)SpGourTbl + prim->unk1C * 4;
        for (k = 0; k < 4; k++) {
            gour[k] = 0xC210;
        }
        rsincos(i << 8, &sin, &cos);
        prim->x0 = x + (((cos >> 4) * 64) >> 8);
        prim->y0 = y - (((sin >> 4) * 64) >> 8);
        rsincos((i + 1) << 8, &sin, &cos);
        prim->x1 = x + (((cos >> 4) * 64) >> 8);
        prim->y1 = y - (((sin >> 4) * 64) >> 8);
        prim->x2 = prim->x3 = x;
        prim->y2 = prim->y3 = y;
        prim->priority = 5;
        prim->drawMode = 0x406;
    }
    ext->fade = 0;
    ext->primFade = prim;
    prim->type = 0x1004;
    prim->unk4 = 0x4C0 | 3;
    prim->x0 = prim->x3 = 120;
    prim->x1 = prim->x2 = 0xC8;
    prim->y0 = prim->y1 = 112;
    prim->y2 = prim->y3 = 0xC0;
    prim->unk6 = (s16)0xC210;
    prim->priority = 17;
    prim->drawMode = 51;
    prim = prim->next;
    prim->type = 0x1000;
    prim->unk4 = 0x488;
    prim->unk8 = DAT_0605AEC0[g_WarpSpriteBank16.allocationIndex + 5][0];
    prim->unkA = DAT_0605AEC0[g_WarpSpriteBank16.allocationIndex + 5][1];
    prim->unk6 = SPR_2LookupTblNoToVram(1);
    prim->unk4 &= 0xFFC7;
    prim->unk6 = (prim->unk6 & 0x8FFF) | 0x7000;
    prim->x0 = 0x78;
    prim->y0 = 0x6C;
    prim->priority = 31;
    prim->drawMode = 0;
}

static s32 BgComponent(s32 k) {
    s32 v =
        ((rsin(g_WarpBackgroundAngles[k % 16]) + 0x1000) >> 6) * DAT_060E2490;

    if (v < 0) {
        v += 0x7FF;
    }
    return v >> 11;
}

void func_060DC7D8(Entity* self) {
    Primitive* prim;
    u16* gour;
    s32 i, b;

    g_WarpBackgroundPhase += 0x10;
    DAT_060E2494 = (rsin(g_WarpBackgroundPhase) >> 8) + 0xD0;
    if (DAT_060E2494 < 0) {
        DAT_060E2494 = 0;
    } else if (DAT_060E2494 > 0xFF) {
        DAT_060E2494 = 0xFF;
    }
    DAT_060E2490 = (rcos(g_WarpBackgroundPhase) >> 8) + 0xD0;
    prim = ((ET_WarpRoom*)&self->ext)->primBg;
    for (i = 0; i < 16; i++, prim = prim->next) {
        gour = (u16*)SpGourTbl + prim->unk1C * 4;
        gour[0] = (BgComponent(i + 10) << 10) + (BgComponent(i + 5) << 5) +
                  BgComponent(i) + 0x8000;
        gour[1] = (BgComponent(i + 11) << 10) + (BgComponent(i + 6) << 5) +
                  BgComponent(i + 1) + 0x8000;
        b = DAT_060E2494 / 8;
        gour[2] = gour[3] = Gray15(b);
        g_WarpBackgroundAngles[i] += 0x20;
    }
}

void func_060DCAFC(Entity* self) {
    ET_WarpSmallRock* ext = (ET_WarpSmallRock*)&self->ext;
    SaturnSpriteResource* res = &g_WarpSpriteBank16;
    SpriteObject* sprite;
    s32 dx, dy, r, y;
    s16 angle;

    switch (self->step) {
    case 0:
        TekiInit(self, 5);
        self->step++;
        sprite = CreateSpriteObject(
            res->allocationIndex, res->flags, res->images, 1);
        self->unk0 = sprite;
        self->drawFlags = 4;
        self->rotate = (u8)Random() << 4;
        self->animCurFrame = (u8)Random() % 5 + 1;
        sprite->flags |= 0x40;
        func_0600AFA8(sprite, g_WarpSpriteBank16Frames[self->animCurFrame]);
        if (g_WarpActive) {
            self->posY.i.hi = (Random() & 0x1F) + 0x90;
            self->step = 4;
            break;
        }
    case 1:
        if (!g_WarpActive) {
            break;
        }
        ext->timer = Random() & 0x3F;
        self->velocityY = FIX(-4);
        self->step++;
        break;
    case 2:
        if (ext->timer) {
            ext->timer--;
            break;
        }
        MoveEntity(self);
        self->velocityY += FIX(0.25);
        if (self->velocityY > FIX(-1)) {
            self->drawFlags = 3;
            self->scaleX = self->scaleY = 0x100;
            self->step++;
        }
        break;
    case 3:
        dx = 0xA0 - self->posX.i.hi;
        dy = 0xA0 - self->posY.i.hi;
        angle = ratan2(dy, dx);
        self->velocityX = rcos(angle) * 32;
        self->velocityY = rsin(angle) * 32;
        MoveEntity(self);
        r = SquareRoot0(dx * dx + dy * dy) * 2;
        if (r > 0x100) {
            r = 0x100;
        }
        self->scaleX = self->scaleY = r;
        if (r <= 7) {
            DestroyEntity(self);
            return;
        }
        break;
    case 4:
        self->rotate += 0x20;
        self->velocityY = rsin(self->rotate) << 2;
        if (!g_WarpActive) {
            ext->timer = 16;
            self->step++;
        }
        break;
    case 5:
        if (--ext->timer == 0) {
            PlaySfxPositional(0x644);
        }
        MoveEntity(self);
        self->velocityY += FIX(0.1875);
        y = self->posY.i.hi + g_Tilemap.scrollY.i.hi + 5;
        if (y > 0xD0) {
            self->posY.i.hi = 0xCB - g_Tilemap.scrollY.i.hi;
            self->step = 1;
        }
        break;
    }
    sprite = self->unk0;
    if (sprite != NULL) {
        sprite->posX = self->posX.val;
        sprite->posY = self->posY.val;
        if (self->drawFlags & 3) {
            sprite->scaleX = sprite->scaleY = self->scaleX / 4;
        } else {
            sprite->scaleX = sprite->scaleY = 64;
        }
        sprite->rotate = (self->drawFlags & 4) ? self->rotate : 0;
    }
}

static u16 FlagsToVram(u16 flags) {
    if (flags & 0x4000) {
        return LocalLookupTblNoToVram(flags & 0xFFF);
    }
    return SPR_2LookupTblNoToVram(flags & 0xFFF);
}

static u16* GourEntry(Primitive* prim) {
    return (u16*)SpGourTbl + prim->unk1C * 4;
}

static u16 Gray15_b5(u32 c) { return c + (c << 5) + (c << 10) + 0x8000; }

void EntityWarpRedDoor(Entity* self) {
    ET_WarpDoor* ext = DOOR(self);
    Primitive* prim;
    u16* gour;
    u16 step;
    u16 col;
    s32 dx;
    s32 angle;
    s32 frac;
    s32 fracHi;
    s32 x0;
    s32 i;

    switch (self->step) {
    case 0:
        TekiInit(self, 3);
        self->unk0 = CreateSpriteObject(
            g_SaturnSharedSpriteBank3Resource.allocationIndex,
            g_SaturnSharedSpriteBank3Resource.flags,
            g_SaturnSharedSpriteBank3Resource.images, 3);
        self->animCurFrame = 1;
        self->step++;
        if (func_060DF580(self) == 0) {
            return;
        }
        break;
    case 1:
        if (PLAYER.facingLeft != ((GetSideToPlayer2(self) & 1) ^ 1)) {
            break;
        }
        step = PLAYER.step;
        if (!((step == 0x19 && g_PlayableCharacter != 0) ||
              (step == 0x13 && g_PlayableCharacter == 0) || step == 1)) {
            break;
        }
        if (func_060DF528(self) == 0) {
            break;
        }
        if (self->params & 0x100) {
            PlaySfxVolPan(0x642, 0x60, 6);
        } else {
            PlaySfxVolPan(0x642, 0x60, -6);
        }
        for (prim = ext->prims, i = 0; prim != NULL; prim = prim->next, i++) {
            if (i == 0) {
                prim->drawMode &= ~8;
            }
            if (i == 1 && !(self->params & 0x100)) {
                prim->drawMode &= ~8;
            }
            if (i == 2 && (self->params & 0x100)) {
                prim->drawMode &= ~8;
            }
        }
        self->animCurFrame = 0;
        self->unk0->flags |= 8;
        ext->prim88->drawMode |= 8;
        g_Player.padSim = 0;
        g_Player.demo_timer = 2;
        self->step++;
        break;
    case 2:
        g_Player.padSim = 0;
        g_Player.demo_timer = 24;
        if (!(self->params & 0x100)) {
            ext->angle += 0x20;
            if (ext->angle > 0xFFF) {
                ext->angle = 0x1000;
            }
            if (ext->angle == 0x1000) {
                self->step++;
            }
        } else {
            ext->angle -= 0x20;
            if (ext->angle <= 0x800) {
                ext->angle = 0x800;
            }
            if (ext->angle == 0x800) {
                self->step++;
            }
        }
        break;
    case 3:
        if (g_Player.demo_timer > 3) {
            return;
        }
        g_Player.padSim = (self->params & 0x100) ? 0x8000 : 0x4000;
        g_Player.demo_timer = 3;
        break;
    case 4:
        g_Player.padSim = (self->params & 0x100) ? 0x4000 : 0x8000;
        g_Player.demo_timer = 4;
        if (func_060DF528(self) == 0) {
            self->step++;
        }
        break;
    case 5:
        g_Player.padSim = 0;
        g_Player.demo_timer = 4;
        if (!(self->params & 0x100)) {
            ext->angle -= 0x20;
            if (ext->angle <= 0xC00) {
                ext->angle = 0xC00;
            }
        } else {
            ext->angle += 0x20;
            if (ext->angle > 0xBFF) {
                ext->angle = 0xC00;
            }
        }
        if (ext->angle != 0xC00) {
            break;
        }
        for (prim = ext->prims; prim != NULL; prim = prim->next) {
            prim->drawMode |= 8;
        }
        if (self->params & 0x100) {
            PlaySfxVolPan(0x64F, 0x60, 6);
        } else {
            PlaySfxVolPan(0x64F, 0x60, -6);
        }
        self->animCurFrame = 1;
        self->unk0->flags &= ~8;
        ext->prim88->drawMode &= ~8;
        self->step = 1;
        break;
    }

    if (self->step != 1) {
        DAT_06064588(1, 1);
        func_8010E168(1, 32);
    }

    dx = (s16)(self->posX.i.hi - ext->offsetX);
    if (self->params & 0x100) {
        dx = (s16)(dx - 1);
    } else {
        dx = (s16)(dx + 1);
    }
    angle = ext->angle;
    x0 = 0;
    prim = ext->prims;
    if (prim != NULL) {
        frac = angle & 0x3FF;
        fracHi = frac >> 4;
        for (i = 0; prim != NULL; prim = prim->next, i++) {
            gour = GourEntry(prim);
            if (prim->drawMode & 8) {
                continue;
            }
            if (!(self->params & 0x100)) {
                if (i == 0) {
                    prim->x0 = dx + ((rcos(angle) * 40) >> 12);
                    x0 = prim->x0;
                    prim->x2 = prim->x0 - (((rsin(angle) >> 4) * 8) >> 8);
                    if (angle > 0xF80) {
                        prim->x2 = prim->x0;
                    }
                    if (angle == 0x1000) {
                        gour[3] = 0xA108;
                        gour[1] = 0xA108;
                    } else {
                        col = Gray15_b5((u16)(0x7F - fracHi) >> 3);
                        gour[3] = col;
                        gour[1] = col;
                    }
                } else {
                    prim->x0 = dx;
                    prim->x2 = x0;
                    if (angle == 0x1000) {
                        gour[2] = 0xA108;
                        gour[0] = 0xA108;
                    } else {
                        col = Gray15_b5(frac >> 7);
                        gour[2] = col;
                        gour[0] = col;
                    }
                }
            } else {
                if (i == 0) {
                    prim->x2 = dx + ((rcos(angle) * 40) >> 12);
                    x0 = prim->x2;
                    prim->x0 = prim->x2 + (((rsin(angle) >> 4) * 8) >> 8);
                    if (angle <= 0x87F) {
                        prim->x0 = prim->x2;
                    }
                    if (angle == 0x800) {
                        col = 0xC210;
                    } else {
                        col = Gray15_b5((fracHi + 0x3F) >> 3);
                    }
                    gour[2] = col;
                    gour[0] = col;
                } else {
                    prim->x0 = x0 - 1;
                    prim->x2 = dx;
                    if (angle == 0x800) {
                        gour[3] = 0xA108;
                        gour[1] = 0xA108;
                    } else {
                        col = Gray15_b5((u16)(0x3F - fracHi) >> 3);
                        gour[3] = col;
                        gour[1] = col;
                    }
                }
            }
        }
    }

    func_060DF938(self);
    if (self->unk0 != NULL) {
        self->unk0->posX = self->posX.val;
        self->unk0->posY = self->posY.val;
    }
}

s32 func_060DF528(Entity* entity) {
    Entity* player = &g_Entities[0];
    s16 distance;

    distance = (s16)(player->posX.i.hi - entity->posX.i.hi);
    distance = ABS(distance);
    if (distance > 22) {
        return 0;
    }
    distance = (s16)(player->posY.i.hi - entity->posY.i.hi);
    distance = ABS(distance);
    if (distance > 32) {
        return 0;
    }
    return 1;
}

s32 func_060DF580(Entity* self) {
    ET_WarpDoor* ext = DOOR(self);
    SpriteObject* sprite;
    Primitive* prim;
    u16* gour;
    u16 idx;
    s32 offsetX;
    s32 primIndex;
    s32 y;
    s32 i;

    sprite = self->unk0;
    func_0600AFA8(sprite, g_SaturnSharedSpriteBank3Frames[1]);
    sprite->zPriority = 0x70;
    sprite->clutBase = 0x8009;
    self->facingLeft = 0;
    self->posY.i.hi += 0x1F;
    offsetX = (self->params & 0x100) ? -5 : 5;
    ext->offsetX = offsetX;
    self->posX.i.hi += offsetX;
    primIndex = AllocPrimitives(0x8001, 4);
    self->primIndex = primIndex;
    if (self->primIndex == -1) {
        DestroyEntity(self);
        return 0;
    }
    self->flags |= FLAG_HAS_PRIMS;
    prim = &g_PrimBuf[self->primIndex];
    ext->prim88 = prim;
    prim->type = 0x1000;
    prim->unk4 = 0x488;
    prim->unk8 =
        DAT_0605AEC0[g_SaturnSharedSpriteBank3Resource.allocationIndex][0];
    prim->unkA =
        DAT_0605AEC0[g_SaturnSharedSpriteBank3Resource.allocationIndex][1];
    prim->unk6 = FlagsToVram(g_SaturnSharedSpriteBank3Resource.flags);
    prim->x0 = self->posX.i.hi - 4;
    prim->y0 = self->posY.i.hi - 0x1F;
    prim->priority = 0x71;
    prim->drawMode = 6;
    prim = prim->next;
    ext->prims = prim;
    y = (s16)(self->posY.i.hi - 0x1F);
    for (i = 0; prim != NULL; prim = prim->next, i++) {
        gour = GourEntry(prim);
        idx = g_SaturnSharedSpriteBank3Resource.allocationIndex;
        if (i > 0) {
            idx += 2;
        }
        prim->unk8 = DAT_0605AEC0[idx][0];
        prim->unkA = DAT_0605AEC0[idx][1];
        prim->unk6 = FlagsToVram(g_SaturnSharedSpriteBank3Resource.flags);
        prim->priority = 0x70;
        prim->drawMode = 6;
        if (i == 2) {
            prim->type = (prim->type & 0xFFCF) | 0x10;
            if (!(self->params & 0x100)) {
                prim->drawMode |= 8;
            }
        }
        if (i == 1 && (self->params & 0x100)) {
            prim->drawMode |= 8;
        }
        prim->y0 = prim->y1 = y;
        prim->y2 = prim->y3 = y + 0x3E;
        gour[3] = gour[2] = gour[1] = gour[0] = 0xC210;
    }

    if (func_060DF528(self)) {
        if (!(self->params & 0x100)) {
            PlaySfxVolPan(0x642, 0x60, -6);
            ext->angle = 0x1000;
        } else {
            PlaySfxVolPan(0x642, 0x60, 6);
            ext->angle = 0x800;
        }
        self->animCurFrame = 0;
        sprite->flags |= 8;
        ext->prim88->drawMode |= 8;
        self->step = 4;
        PLAYER.velocityY = 0;
        g_Player.padSim = 0;
        g_Player.demo_timer = 24;
    } else {
        ext->angle = 0xC00;
        prim = ext->prims;
        i = 0;
        while (prim != NULL) {
            prim->drawMode |= 8;
            if (++i == 3) {
                break;
            }
            prim = prim->next;
        }
    }
    return 1;
}
