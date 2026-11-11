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
void func_060ADB80(s8* frameProps, AnimationFrame** frames);
Entity* func_060B93C4(void);
s16 func_060B94F8(Entity* self, Entity* target, s16 targetOffscreenLeft);
void func_060B9340(Entity* entity);
Entity* func_060BAF44(Entity* source, u32 factoryParams, s32 arg2);
void func_060C1618(Entity* self);
void func_060A5614(s32 amount);
extern SaturnSpriteResource AlucardSpriteResources[];
extern s32 DAT_060C8508;
extern unkGraphicsStruct g_unkGraphicsStruct;
extern s32 g_Timer;
extern Entity* g_CurrentEntity;

extern s8 DAT_060D7244[][4];
extern AnimationFrame* DAT_060D728C[];
extern SaturnSpriteImage DAT_060D72C4[];
extern SaturnSpriteFrameHeader* DAT_060D76BC[];
extern SaturnSpriteResource DAT_060D77C4;

typedef struct {
    union {
        /* 0x78 */ s16 timer;
        ET_Weapon w;
    } u;
} ShieldExt;
#define SHIELD(e) ((ShieldExt*)&(e)->ext)

typedef struct {
    /* 0x78 */ u8 uv[2];
    /* 0x7A */ u8 pad7A[2];
    /* 0x7C */ s16 timer;
    /* 0x7E */ s16 glow;
} SpellExt;

typedef struct {
    union {
        struct {
            /* 0x78 */ Entity* target;
            /* 0x7C */ Primitive* tip;
        } s;
        u8 pad78[0x10];
    } u;
} VineExt;

void func_060D6060(Entity* self, s32 kind);
void func_060D6128(Entity* self);
void func_060D6498(Entity* self);
void func_060D64B0(Entity* self);
void func_060D64C8(Entity* self);

static u16 shield_clut(u16 f);

static void shield_image(Primitive* p, s32 image);
void func_060D64E0(Entity* self);
void func_060D6740(Entity* self);
s32 func_060D6758(void);
void func_060D6764(Entity* self);
static void vine_hit(Entity* self);
void func_060D6B74(Entity* self);
void func_060D6FEC(Entity* self);
void func_060D7004(Entity* self);
void func_060D701C(Entity* self);
void func_060D7034(Entity* self);
void func_060D704C(Entity* self);
void func_060D7064(Entity* self);
void func_060D707C(void);

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

void func_060D6128(Entity* self) {
    ShieldExt* ext = SHIELD(self);
    s32 pose = 0, crouch = 0;
    SpriteObject* sprite;

    if (!(g_Player.padPressed & WEAPON_HAND_BUTTON) && self->step <= 2) {
        self->poseTimer = 0;
        self->pose = 0;
        self->step = 3;
    }
    if (self->step != 4) {
        self->posX.val = g_Entities[0].posX.val;
        self->posY.val = g_Entities[0].posY.val;
        self->facingLeft = g_Entities[0].facingLeft;
    }
    if ((g_Player.status & 0x10000) && self->step != 4) {
        ((SpriteObject*)self->unk0)->zPriority = g_Entities[0].zPriority + 2;
        self->step = 4;
        if (g_Player.vram_flag & 1) {
            self->velocityX = g_Entities[0].velocityX;
        } else {
            self->velocityX = g_Entities[0].velocityX * 2;
        }
        self->velocityY = 0xFFFC8000;
        ext->u.timer = 0x80;
        self->flags = 0x08000000;
        self->animCurFrame = 0x3E;
    }
    if (g_Entities[0].step == 2 && g_Entities[0].step_s != 2) {
        crouch = 1;
    }
    switch (self->step) {
    case 0:
        sprite = CreateSpriteObject(
            DAT_060D77C4.allocationIndex, DAT_060D77C4.flags, DAT_060D72C4, 6);
        self->unk0 = sprite;
        if (!sprite) {
            DestroyEntity(self);
            return;
        }
        self->ext.weapon.frames = DAT_060D76BC;
        sprite->zPriority = g_Entities[0].zPriority - 2;
        self->animSet = 0x8010 + WEAPON_HAND_ANIMSET;
        self->palette = 0x110 + WEAPON_HAND_PALETTE;
        self->unk56 = 0x64 + WEAPON_HAND_UNK56;
        self->flags = 0x60000;
        g_Player.unk48 = 1;
        func_060D6060(self, 0);
        self->step++;
    case 1:
        if (!(g_Player.anim == 7 || g_Player.anim == 9 ||
              g_Player.anim == 10)) {
            self->ext.weapon.anim = crouch + 0xA;
            if (self->poseTimer < 0) {
                self->step++;
            }
            break;
        }
        self->step++;
    case 2:
        switch (g_Player.anim) {
        case 7:
        case 9:
        case 10:
            pose = 1;
        case 5:
            pose++;
        case 6:
            pose++;
        case 8:
            pose++;
        case 11:
            pose++;
        case 19:
        case 20:
            pose++;
        case 12:
        case 13:
            pose++;
        case 21:
            pose += 2;
            self->pose = g_Player.poseTimer;
            break;
        default:
            self->pose = 0;
            pose = crouch;
            break;
        }
        self->ext.weapon.anim = pose;
        self->poseTimer = 2;
        break;
    case 3:
        g_Player.unk48 = 0;
        self->ext.weapon.anim = crouch + 0xC;
        if (self->poseTimer < 0) {
            DestroyEntity(self);
            return;
        }
        break;
    case 4:
        self->hitboxState = 0;
        g_Player.unk48 = 0;
        self->drawFlags |= 4;
        self->posY.val += self->velocityY;
        self->posX.val += self->velocityX;
        self->velocityY += 0x2800;
        self->rotate += 0x80;
        if (--ext->u.timer <= 0xF) {
            self->drawFlags |= 0x80;
        }
        if (--ext->u.timer == 0) {
            DestroyEntity(self);
            return;
        }
        break;
    }
    if (self->step != 4) {
        func_060ADB80(&DAT_060D7244[0][0], DAT_060D728C);
    } else {
        func_060C1618(self);
    }
    self->drawFlags = g_Entities[0].drawFlags;
    self->scaleY = g_Entities[0].scaleY;
    self->unk26 = g_Entities[0].unk26;
}

void func_060D6498(Entity* self) { DestroyEntity(self); }

void func_060D64B0(Entity* self) { DestroyEntity(self); }

void func_060D64C8(Entity* self) { DestroyEntity(self); }

static u16 shield_clut(u16 f) {
    return ((f >> 14) & 1) ? LocalLookupTblNoToVram(f & 0xFFF)
                           : SPR_2LookupTblNoToVram(f & 0xFFF);
}

static void shield_image(Primitive* p, s32 image) {
    SaturnSpriteImage* img = &DAT_060D77C4.images[image];

    p->unk8 = DAT_0605AEC0[DAT_060D77C4.allocationIndex][0] +
              img->characterOffsetUnits;
    p->unkA = ((img->storedWidth >> 2) << 8) | (img->storedHeight * 2);
    p->unk6 = shield_clut(DAT_060D77C4.flags + 1);
}

void func_060D64E0(Entity* self) {
    s16* size = (s16*)&self->ext;
    s16* grips = size + 1;
    Primitive* p;
    u32 t;

    switch (self->step) {
    case 0:
        self->primIndex = AllocPrimitives(1, 1);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        p = &g_PrimBuf[self->primIndex];
        p->priority = 0xC1;
        shield_image(p, 3);
        p->drawMode = 2;
        self->flags = 0x08800000;
        self->ext.weapon.equipId = 0xE2;
        func_060D6060(self, 0);
        self->attack >>= 1;
        self->hitboxHeight = 6;
        self->hitboxWidth = 6;
        *grips = 0;
        self->step++;
    case 1:
        if (*grips) {
            self->posX.val = self->unkB4->posX.val;
            self->posY.val = self->unkB4->posY.val;
        }
        if (self->hitFlags) {
            self->hitboxHeight = 2;
            self->hitboxWidth = 2;
            if ((u16)*grips <= 2 && self->unkB4->hitPoints != 0x7FFF &&
                !(self->unkB4->flags & 0x100)) {
                ++*grips;
            } else {
                self->step++;
            }
            self->hitFlags = 0;
        } else {
            t = (u32)g_Timer >> 3;
            *size = (t & 4) ? 0x17 - (t & 7) : (t & 7) + 0x13;
            if (++self->step_s > 0xA0) {
                self->step++;
                self->step_s = 0;
            }
        }
        break;
    default:
        if (--*size <= 0) {
            DestroyEntity(self);
            return;
        }
        break;
    }
    p = &g_PrimBuf[self->primIndex];
    p->x0 = self->posX.i.hi - *size;
    p->x2 = self->posX.i.hi + *size;
    p->y0 = self->posY.i.hi - *size;
    p->y2 = self->posY.i.hi + *size;
}

void func_060D6740(Entity* self) { DestroyEntity(self); }

s32 func_060D6758(void) { return 8; }

void func_060D6764(Entity* self) {
    SpellExt* ext = (SpellExt*)&self->ext;
    SaturnSpriteResource* fx = &AlucardSpriteResources[7];
    SpriteObject* sprite;
    Primitive* p;
    s32 w;

    DAT_060C8508 = 8;
    switch (self->step) {
    case 0:
        self->primIndex = AllocPrimitives(1, 1);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        sprite = CreateSpriteObject(
            DAT_060D77C4.allocationIndex, DAT_060D77C4.flags, DAT_060D72C4, 6);
        self->unk0 = sprite;
        if (!sprite) {
            DestroyEntity(self);
            return;
        }
        self->ext.weapon.frames = DAT_060D76BC;
        sprite->zPriority = g_Entities[0].zPriority - 2;
        self->animSet = 0x8010 + WEAPON_HAND_ANIMSET;
        self->palette = 0x110 + WEAPON_HAND_PALETTE;
        self->unk56 = 0x64 + WEAPON_HAND_UNK56;
        ext->uv[0] = WEAPON_HAND ? 0 : 0x80;
        ext->uv[1] = WEAPON_HAND ? 0x80 : 0;
        self->posY.i.hi -= 8;
        self->flags = 0x0C810000;
        self->facingLeft = g_Entities[0].facingLeft;
        self->animCurFrame = 0x3E;
        self->drawFlags = 3;
        self->scaleY = 0;
        self->scaleX = 0;
        p = &g_PrimBuf[self->primIndex];
        p->unk8 = DAT_0605AEC0[fx->allocationIndex + 1][0];
        p->unkA = DAT_0605AEC0[fx->allocationIndex + 1][1];
        p->unk6 = shield_clut(fx->flags);
        p->x3 = 0x80;
        ext->glow = 0;
        p->priority = g_Entities[0].zPriority - 6;
        p->drawMode = 0x75;
        self->velocityX = self->facingLeft == 1 ? 0x20000 : -0x20000;
        self->velocityY = 0;
        if (g_Player.unk48) {
            DestroyEntity(&g_Entities[16]);
            g_Player.unk48 = 0;
        }
        PlaySfx(0x641);
        g_unkGraphicsStruct.unk28 = 1;
        self->step++;
        break;
    case 1:
        func_060A5614(0x1000);
        self->velocityY -= 0x2800;
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        self->scaleX += 0xC;
        self->scaleY = self->scaleX;
        ext->glow = self->scaleX * 0x28 / 256;
        if (self->scaleX > 0xFF) {
            ext->glow = 0x28;
            self->scaleX = 0x100;
            self->scaleY = 0x100;
            ext->timer = 8;
            func_060BAF44(self, WEAPON_HAND_FACTORY2 | 0x58, 0);
            g_unkGraphicsStruct.unk28 = 0;
            self->step++;
        }
        break;
    case 2:
        if (--ext->timer == 0) {
            ext->timer = 0x10;
            self->step++;
        }
        break;
    case 3:
        p = &g_PrimBuf[self->primIndex];
        p->priority = (ext->timer & 1) ? g_Entities[0].zPriority - 4 : 0x1BC;
        self->scaleX -= 0x10;
        if (self->scaleX <= 0) {
            self->scaleX = 0;
        }
        self->scaleY = self->scaleX;
        if (--ext->timer == 0) {
            self->animCurFrame = 0;
            ext->timer = 0x20;
            PlaySfx(0x6B1);
            self->step++;
        }
        break;
    case 4:
        ext->glow += 8;
        if (--ext->timer == 0) {
            self->step++;
        }
        break;
    default:
        DestroyEntity(self);
        return;
    }
    p = &g_PrimBuf[self->primIndex];
    if (p->x3 > 8) {
        if (g_Timer & 1) {
            p->drawMode |= 8;
        } else {
            p->drawMode &= ~8;
        }
    }
    w = (ext->glow * 5) >> 2;
    p->x0 = self->posX.i.hi - w;
    p->x2 = self->posX.i.hi + w - 1;
    p->y0 = self->posY.i.hi - ext->glow;
    p->y2 = self->posY.i.hi + ext->glow - 1;
    func_060C1618(self);
}

static void vine_hit(Entity* self) {
    s32 x, y;

    if (!self->hitFlags) {
        return;
    }
    if (self->unkB4->hitPoints != 0x7FFF && !(self->unkB4->flags & 0x100)) {
        x = self->posX.val;
        y = self->posY.val;
        self->posX.i.hi = (rand() & 0xF) - 7 + self->unkB4->posX.i.hi;
        self->posY.i.hi = (rand() & 0xF) - 7 + self->unkB4->posY.i.hi;
        func_060BAF44(self, WEAPON_HAND_FACTORY2 | 0x4E, 0);
        self->posX.val = x;
        self->posY.val = y;
    }
    self->hitFlags = 0;
}

void func_060D6B74(Entity* self) {
    VineExt* ext = (VineExt*)&self->ext;
    Primitive *p, *next;
    s32 i, t;
    s16 a;

    switch (self->step) {
    case 0:
        self->primIndex = AllocPrimitives(2, 0x28);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags = 0x0C800000;
        p = &g_PrimBuf[self->primIndex];
        p->x3 = p->x2 = p->x1 = p->x0 = self->posX.i.hi;
        p->y3 = p->y2 = p->y1 = p->y0 = self->posY.i.hi;
        ext->u.s.tip = p;
        for (i = 0; p; p = p->next) {
            p->unk4 &= ~0x1000;
            p->priority = g_Entities[0].zPriority + 4;
            shield_image(p, 10 + i);
            p->drawMode = 0xA;
            if (++i > 5) {
                i = 0;
            }
        }
        self->ext.weapon.equipId = 0xE2;
        func_060D6060(self, 0);
        self->hitboxHeight = 6;
        self->hitboxWidth = 6;
        ext->u.s.target = func_060B93C4();
        t = func_060B94F8(self, ext->u.s.target, self->facingLeft);
        if (t >= 0) {
            self->rotate = (u16)t - 0x200 + (MTH_GetRand() & 0x3FF);
        }
        self->step++;
        break;
    case 1:
        t = func_060B94F8(self, ext->u.s.target, self->facingLeft);
        if (t >= 0) {
            self->rotate =
                self->rotate < t ? self->rotate + 0x70 : self->rotate - 0x70;
        }
        p = ext->u.s.tip;
        next = p->next;
        ext->u.s.tip = next;
        if ((u16)(self->posX.i.hi + 0x20) > 0x180 ||
            (u16)(self->posY.i.hi + 0x20) > 0x130 || !next) {
            self->step++;
            break;
        }
        next->drawMode &= ~8;
        next->x0 = p->x3;
        next->y0 = p->y3;
        next->x1 = p->x2;
        next->y1 = p->y2;
        a = self->rotate;
        self->posX.i.hi += (rcos(a) * 16) >> 12;
        self->posY.i.hi -= (rsin(a) * 16) >> 12;
        next->x3 = self->posX.i.hi + ((rcos(a - 0x400) * 8) >> 12);
        next->y3 = self->posY.i.hi - ((rsin(a - 0x400) * 8) >> 12);
        next->x2 = self->posX.i.hi + ((rcos(a + 0x400) * 8) >> 12);
        next->y2 = self->posY.i.hi - ((rsin(a + 0x400) * 8) >> 12);
        break;
    case 2:
        p = &g_PrimBuf[self->primIndex];
        p->drawMode |= 8;
        ext->u.s.tip = p->next;
        self->step++;
        break;
    case 3:
        p = ext->u.s.tip;
        if (!p || (p->drawMode & 8)) {
            DestroyEntity(self);
            return;
        }
        p->drawMode |= 8;
        ext->u.s.tip = p->next;
        break;
    default:
        DestroyEntity(self);
        return;
    }
    vine_hit(self);
}

void func_060D6FEC(Entity* self) { DestroyEntity(self); }

void func_060D7004(Entity* self) { DestroyEntity(self); }

void func_060D701C(Entity* self) { DestroyEntity(self); }

void func_060D7034(Entity* self) { DestroyEntity(self); }

void func_060D704C(Entity* self) { DestroyEntity(self); }

void func_060D7064(Entity* self) { DestroyEntity(self); }

void func_060D707C(void) {}
