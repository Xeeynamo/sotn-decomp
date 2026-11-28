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

extern WeaponAnimation DAT_060D6A50[3];
extern AnimationFrame DAT_060D6A80[];
extern SaturnSpriteImage DAT_060D6A94[];
extern SaturnSpriteFrameHeader* DAT_060D7360[];
extern SaturnSpriteResource DAT_060D74A0;

void func_060D6060(Entity* self, s32 kind);
void func_060D6128(Entity* self);
void func_060D62C8(Entity* self);
void func_060D6464(Entity* self);
void func_060D6630(Entity* self);
void func_060D6740(Entity* self);
void func_060D6758(Entity* self);
s32 func_060D6770(void);
void func_060D677C(Entity* self);
void func_060D6794(Entity* self);
void func_060D67AC(Entity* self);
void func_060D67C4(Entity* self);
void func_060D67DC(Entity* self);
void func_060D67F4(Entity* self);
void func_060D680C(Entity* self);
void func_060D6824(Entity* self);
void func_060D683C(void);

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
    WeaponAnimation* anim;
    SpriteObject* sprite;

    self->posX.val = g_Entities[0].posX.val;
    self->posY.val = g_Entities[0].posY.val;
    self->facingLeft = g_Entities[0].facingLeft;
    anim = &DAT_060D6A50[(self->params >> 8) & 0x7F];
    if (g_Player.anim < anim->frameStart ||
        g_Player.anim >= anim->frameStart + 7 || !g_Player.unk46) {
        DestroyEntity(self);
        return;
    }
    if (self->step == 0) {
        sprite = CreateSpriteObject(DAT_060D74A0.allocationIndex,
                                    DAT_060D74A0.flags, DAT_060D6A94, 0x12);
        self->unk0 = sprite;
        if (!sprite) {
            DestroyEntity(self);
            return;
        }
        self->ext.weapon.frames = DAT_060D7360;
        sprite->zPriority = g_Entities[0].zPriority - 2;
        self->animSet = 0x8010 + WEAPON_HAND_ANIMSET;
        self->palette = 0x110 + WEAPON_HAND_PALETTE + anim->palette;
        self->unk56 = 0x64 + WEAPON_HAND_UNK56;
        self->flags = 0x60000;
        self->unk1C = 0x30;
        func_060D6060(self, 0);
        self->step++;
    }
    self->ext.weapon.anim = (u8)g_Player.anim - anim->frameStart;
    if (g_Player.pose == 1 && g_Player.poseTimer == anim->soundFrame) {
        PlaySfx(anim->soundId);
    }
    if (func_060ADACC(anim->frameProps, anim->frames) < 0) {
        DestroyEntity(self);
        return;
    }
    self->drawFlags = g_Entities[0].drawFlags;
    self->scaleY = g_Entities[0].scaleY;
    self->unk26 = g_Entities[0].unk26;
}

void func_060D62C8(Entity* self) {
    WeaponAnimation* anim;
    SpriteObject* sprite;

    self->posX.val = g_Entities[0].posX.val;
    self->posY.val = g_Entities[0].posY.val;
    self->facingLeft = g_Entities[0].facingLeft;
    anim = &DAT_060D6A50[(self->params >> 8) & 0x7F];
    if (g_Player.anim != anim->frameStart &&
        g_Player.anim != anim->frameStart + 1) {
        DestroyEntity(self);
        return;
    }
    if (self->step == 0) {
        sprite = CreateSpriteObject(DAT_060D74A0.allocationIndex,
                                    DAT_060D74A0.flags, DAT_060D6A94, 0x12);
        self->unk0 = sprite;
        if (!sprite) {
            DestroyEntity(self);
            return;
        }
        self->ext.weapon.frames = DAT_060D7360;
        sprite->zPriority = g_Entities[0].zPriority - 2;
        self->animSet = 0x8010 + WEAPON_HAND_ANIMSET;
        self->palette = 0x110 + WEAPON_HAND_PALETTE + anim->palette;
        self->unk56 = 0x64 + WEAPON_HAND_UNK56;
        self->flags = 0x60000;
        self->unk1C = 0x30;
        func_060D6060(self, 0);
        self->step++;
    }
    self->ext.weapon.anim = (u8)g_Player.anim - anim->frameStart;
    if (g_Player.pose == 1 && g_Player.poseTimer == anim->soundFrame) {
        PlaySfx(anim->soundId);
    }
    if (func_060ADACC(anim->frameProps, anim->frames) < 0) {
        DestroyEntity(self);
        return;
    }
    self->drawFlags = g_Entities[0].drawFlags;
    self->scaleY = g_Entities[0].scaleY;
    self->unk26 = g_Entities[0].unk26;
}

void func_060D6464(Entity* self) {
    WeaponAnimation* anim;
    SpriteObject* sprite;

    self->posX.val = g_Entities[0].posX.val;
    self->posY.val = g_Entities[0].posY.val;
    self->facingLeft = g_Entities[0].facingLeft;
    anim = &DAT_060D6A50[(self->params >> 8) & 0x7F];
    if (g_Player.anim < anim->frameStart ||
        g_Player.anim >= anim->frameStart + 7 || !g_Player.unk46) {
        DestroyEntity(self);
        return;
    }
    if (self->step == 0) {
        sprite = CreateSpriteObject(DAT_060D74A0.allocationIndex,
                                    DAT_060D74A0.flags, DAT_060D6A94, 0x12);
        self->unk0 = sprite;
        if (!sprite) {
            DestroyEntity(self);
            return;
        }
        self->ext.weapon.frames = DAT_060D7360;
        sprite->zPriority = g_Entities[0].zPriority - 2;
        self->animSet = 0x8010 + WEAPON_HAND_ANIMSET;
        self->palette = 0x110 + WEAPON_HAND_PALETTE + anim->palette;
        self->unk56 = 0x64 + WEAPON_HAND_UNK56;
        self->flags = 0x60000;
        self->unk1C = 0x30;
        func_060D6060(self, 0);
        self->step++;
    }
    self->ext.weapon.anim = (u8)g_Player.anim - anim->frameStart;
    if (g_Player.pose == 1 && g_Player.poseTimer == anim->soundFrame) {
        PlaySfx(anim->soundId);
    }
    if (self->step_s == 0 && g_Player.poseTimer == 3) {
        func_060BAF44(self, WEAPON_HAND_FACTORY | 0x7F, 0);
        self->step_s++;
    }
    if (func_060ADACC(anim->frameProps, anim->frames) < 0) {
        DestroyEntity(self);
        return;
    }
    self->drawFlags = g_Entities[0].drawFlags;
    self->scaleY = g_Entities[0].scaleY;
    self->unk26 = g_Entities[0].unk26;
}

void func_060D6630(Entity* self) {
    SpriteObject* sprite;

    if ((u32)(g_Player.anim - 0x60) > 1 || g_Player.poseTimer != 4) {
        DestroyEntity(self);
        return;
    }
    if (self->step == 0) {
        sprite = CreateSpriteObject(DAT_060D74A0.allocationIndex,
                                    DAT_060D74A0.flags, DAT_060D6A94, 0x12);
        self->unk0 = sprite;
        if (!sprite) {
            DestroyEntity(self);
            return;
        }
        self->ext.weapon.frames = DAT_060D7360;
        sprite->zPriority = g_Entities[0].zPriority + 1;
        self->anim = DAT_060D6A80;
        self->flags = 0x160000;
        self->step++;
    }
    if (self->poseTimer == 1) {
        self->posX.i.hi =
            g_Entities[0].posX.i.hi - 8 + ((MTH_GetRand() >> 3) & 0xF);
        self->posY.i.hi =
            g_Entities[0].posY.i.hi - 8 + ((MTH_GetRand() >> 10) & 0xF);
        PlaySfx(0x689);
    }
}

void func_060D6740(Entity* self) { DestroyEntity(self); }

void func_060D6758(Entity* self) { DestroyEntity(self); }

s32 func_060D6770(void) { return 36; }

void func_060D677C(Entity* self) { DestroyEntity(self); }

void func_060D6794(Entity* self) { DestroyEntity(self); }

void func_060D67AC(Entity* self) { DestroyEntity(self); }

void func_060D67C4(Entity* self) { DestroyEntity(self); }

void func_060D67DC(Entity* self) { DestroyEntity(self); }

void func_060D67F4(Entity* self) { DestroyEntity(self); }

void func_060D680C(Entity* self) { DestroyEntity(self); }

void func_060D6824(Entity* self) { DestroyEntity(self); }

void func_060D683C(void) {}
