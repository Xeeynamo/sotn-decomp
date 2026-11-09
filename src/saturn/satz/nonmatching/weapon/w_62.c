// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"
#include <saturn_sprite.h>
#include <saturn_weapon.h>
#include "weapon/weapon.h"

extern PlayerState g_Player;
extern Primitive g_PrimBuf[];
s32 AllocPrimitives(s32 type, s32 count);
void GetEquipProperties(s32 handId, Equipment* res, s32 equipId);
u16 LocalLookupTblNoToVram(u16 tableNo);
u16 SPR_2LookupTblNoToVram(u16 tableNo);
u32 MTH_GetRand(void);
void PlaySfx(s32 sfxId);
s32 rcos(s32 angle);
s32 rsin(s32 angle);
void func_060AB44C(s32 kind, s16 invincibilityFrames);
s32 func_060ADACC(s8* frameProps, u16** frames);
Entity* func_060B93C4(void);
s16 func_060B94F8(Entity* self, Entity* target, s16 targetOffscreenLeft);
void func_060B9340(Entity* entity);
Entity* func_060BAF44(Entity* source, u32 factoryParams, s32 arg2);

extern WeaponAnimation DAT_060D6A80[2];
extern AnimationFrame DAT_060D6AA0[];
extern SaturnSpriteImage DAT_060D6AE0[];
extern SaturnSpriteFrameHeader* DAT_060D7088[];
extern SaturnSpriteResource DAT_060D719C;
s32 DAT_060D71B0;

typedef struct {
    union {
        struct {
            /* 0x78 */ Entity* target;
            /* 0x7C */ s16 pad7C;
            /* 0x7E */ s16 facing;
        } s;
        u8 pad78[0x10];
    } u;
    /* 0x88 */ Entity* parent;
    /* 0x8C */ u8 pad8C[0x1E];
    /* 0xAA */ s16 equipId;
} HomingExt;

void func_060D6060(Entity* self, s32 kind);

static void dagger_linger(Entity* self);
void func_060D6128(Entity* self);
void func_060D63A0(Entity* self);
void func_060D63B8(Entity* self);
void func_060D63D0(Entity* self);
void func_060D6768(Entity* self);
void func_060D6780(Entity* self);
s32 func_060D6798(void);
void func_060D67A4(Entity* self);
void func_060D67BC(Entity* self);
void func_060D6890(Entity* self);
void func_060D68A8(Entity* self);
void func_060D68C0(Entity* self);
void func_060D68D8(Entity* self);
void func_060D68F0(Entity* self);
void func_060D6908(Entity* self);
void func_060D6920(void);

void func_060D6060(Entity* self, s32 kind) {
    Equipment equip;

    GetEquipProperties(WEAPON_HAND, &equip, self->ext.weapon.equipId);
    switch (kind) {
    case 0:
    case 1:
        self->attack = equip.attack;
        self->attackElement = equip.element;
        self->hitboxState = equip.hitType;
        self->nFramesInvincibility = equip.enemyInvincibilityFrames;
        self->stunFrames = equip.stunFrames;
        self->hitEffect = equip.hitEffect;
        self->entityRoomIndex = equip.criticalRate;
        func_060B9340(self);
        break;
    case 2:
        self->attack = equip.attack;
        break;
    }
    if (self->hitboxState == 4) {
        self->attack = 0xFF;
    }
}

static void dagger_linger(Entity* self) {
    self->step = 2;
    *(s16*)&self->ext = 4;
    self->animCurFrame = 0;
    self->hitboxState = 0;
}

void func_060D6128(Entity* self) {
    WeaponAnimation* anim;
    SpriteObject* sprite;

    self->posX.val = g_Entities[0].posX.val;
    self->posY.val = g_Entities[0].posY.val;
    self->facingLeft = g_Entities[0].facingLeft;
    anim = &DAT_060D6A80[(self->params >> 8) & 0x7F];
    if (g_Player.anim < anim->frameStart ||
        g_Player.anim >= anim->frameStart + 7 || !g_Player.unk46) {
        if (self->step != 2) {
            dagger_linger(self);
        }
    }
    DAT_060D71B0 = (self->params & 0x7F00) ? 3 : 8;
    if (self->step == 0) {
        sprite = CreateSpriteObject(
            DAT_060D719C.allocationIndex, DAT_060D719C.flags, DAT_060D6AE0, 6);
        self->unk0 = sprite;
        if (!sprite) {
            DestroyEntity(self);
            return;
        }
        self->ext.weapon.frames = DAT_060D7088;
        self->animSet = 0x8010 + WEAPON_HAND_ANIMSET;
        self->palette = 0x110 + WEAPON_HAND_PALETTE + anim->palette;
        self->unk56 = 0x64 + WEAPON_HAND_UNK56;
        self->flags = 0x60000;
        sprite->zPriority =
            (self->params & 0x7F00) ? g_Entities[0].zPriority - 2
                                    : g_Entities[0].zPriority + 2;
        func_060D6060(self, 0);
        self->step++;
    }
    if (self->step == 2) {
        if (--*(s16*)&self->ext == 0) {
            DestroyEntity(self);
        }
        return;
    }
    self->ext.weapon.anim = (u8)g_Player.anim - anim->frameStart;
    if (g_Player.pose == 1 && g_Player.poseTimer == anim->soundFrame) {
        PlaySfx(anim->soundId);
        if (anim->soundId == 0x60B) {
            PlaySfx(0x709);
        }
    }
    if (func_060ADACC(anim->frameProps, anim->frames) < 0) {
        dagger_linger(self);
    }
    if (self->ext.weapon.anim <= 3 && g_Player.poseTimer == 6) {
        self->hitboxState = 4;
    }
    self->drawFlags = g_Entities[0].drawFlags;
    self->scaleY = g_Entities[0].scaleY;
    self->unk26 = g_Entities[0].unk26;
}

void func_060D63A0(Entity* self) { DestroyEntity(self); }

void func_060D63B8(Entity* self) { DestroyEntity(self); }

void func_060D63D0(Entity* self) {
    HomingExt* ext = (HomingExt*)&self->ext;
    SaturnSpriteImage* img;
    Primitive* p;
    Entity* t;
    s16 a, x, y;
    s32 dx, dy;

    switch (self->step) {
    case 0:
        self->primIndex = AllocPrimitives(2, 1);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        p = &g_PrimBuf[self->primIndex];
        img = &DAT_060D719C.images[3];
        p->unk8 = DAT_0605AEC0[DAT_060D719C.allocationIndex][0] +
                  img->characterOffsetUnits;
        p->unkA = ((img->storedWidth >> 2) << 8) | (img->storedHeight * 2);
        p->unk6 = ((DAT_060D719C.flags >> 14) & 1)
                      ? LocalLookupTblNoToVram(DAT_060D719C.flags & 0xFFF)
                      : SPR_2LookupTblNoToVram(DAT_060D719C.flags & 0xFFF);
        p->priority = g_Entities[0].zPriority + 2;
        self->posY.i.hi = g_Entities[0].posY.i.hi - 0x2D;
        ext->u.s.facing = self->facingLeft;
        self->facingLeft = 0;
        ext->equipId = 0xE3;
        func_060D6060(self, 0);
        self->hitboxHeight = 6;
        self->hitboxWidth = 6;
        self->flags = 0x08800000;
        ext->u.s.target = func_060B93C4();
        PlaySfx(0x60B);
        self->step++;
    case 1:
        if (self->hitFlags) {
            self->step++;
            self->hitFlags = 0;
            break;
        }
        t = ext->u.s.target;
        if (t) {
            dx = t->posX.i.hi - self->posX.i.hi;
            if (dx >= 0 ? dx <= 0xE : -dx <= 0xE) {
                dy = t->posY.i.hi - self->posY.i.hi;
                if (dy >= 0 ? dy <= 0xB : -dy <= 0xB) {
                    self->step++;
                    break;
                }
            }
        }
        a = func_060B94F8(self, ext->u.s.target, ext->u.s.facing);
        if (a >= 0) {
            self->rotate = a;
        }
        break;
    case 2:
        break;
    default:
        DestroyEntity(self);
        return;
    }
    self->velocityX = (((rcos(self->rotate) * 0x70000) >> 12) * 5) >> 2;
    self->posX.val += self->velocityX;
    self->velocityY = -((rsin(self->rotate) * 0x70000) >> 12);
    self->posY.val += self->velocityY;
    self->hitboxOffX = (s16)(self->velocityX >> 16) * 2;
    self->hitboxOffY = (s16)(self->velocityY >> 16) * 2;
    p = &g_PrimBuf[self->primIndex];
    a = self->rotate;
    x = self->posX.i.hi;
    y = self->posY.i.hi;
    p->x0 = x + ((rcos(a + 0x6EF) * 50) >> 14);
    p->y0 = y - ((rsin(a + 0x6EF) * 50) >> 14);
    p->x1 = x + ((rcos(a + 0x70) * 115) >> 14);
    p->y1 = y - ((rsin(a + 0x70) * 115) >> 14);
    p->x2 = x + ((rcos(a - 0x55) * 115) >> 14);
    p->y2 = y - ((rsin(a - 0x55) * 115) >> 14);
    p->x3 = x + ((rcos(a + 0x8D2) * 45) >> 14);
    p->y3 = y - ((rsin(a + 0x8D2) * 45) >> 14);
}

void func_060D6768(Entity* self) { DestroyEntity(self); }

void func_060D6780(Entity* self) { DestroyEntity(self); }

s32 func_060D6798(void) { return 0x20; }

void func_060D67A4(Entity* self) { DestroyEntity(self); }

void func_060D67BC(Entity* self) {
    SpriteObject* sprite;

    switch (self->step) {
    case 0:
        sprite = CreateSpriteObject(
            DAT_060D719C.allocationIndex, DAT_060D719C.flags, DAT_060D6AE0, 6);
        self->unk0 = sprite;
        if (!sprite) {
            DestroyEntity(self);
            return;
        }
        self->ext.weapon.frames = DAT_060D7088;
        sprite->zPriority = g_Entities[0].zPriority + 2;
        self->flags = 0x100000;
        self->anim = DAT_060D6AA0;
        PlaySfx(0x668);
        self->step++;
        break;
    case 1:
        if (self->poseTimer < 0) {
            func_060BAF44(self, WEAPON_HAND_FACTORY2 | 0x44, 0);
            self->step++;
        }
        break;
    default:
        DestroyEntity(self);
        return;
    }
    func_060AB44C(1, 0x2D);
}

void func_060D6890(Entity* self) { DestroyEntity(self); }

void func_060D68A8(Entity* self) { DestroyEntity(self); }

void func_060D68C0(Entity* self) { DestroyEntity(self); }

void func_060D68D8(Entity* self) { DestroyEntity(self); }

void func_060D68F0(Entity* self) { DestroyEntity(self); }

void func_060D6908(Entity* self) { DestroyEntity(self); }

void func_060D6920(void) {}
