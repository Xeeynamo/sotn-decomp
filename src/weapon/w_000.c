#include "weapon_private.h"

extern s16 D_4000_8017A040[];
extern AnimSoundEvent D_4000_8017B06C[];
extern s16* D_4000_8017B0BC[5];
extern s32 D_4000_8017B0D0; // dstClutIndex

void DestroyEntity(Entity* entity) {
    s32 i;
    s32 length;
    u32* ptr;

    if (entity->flags & FLAG_HAS_PRIMS) {
        g_api.FreePrimitives(entity->primIndex);
    }

    ptr = (u32*)entity;
    length = sizeof(Entity) / sizeof(u32);
    for (i = 0; i < length; i++)
        *ptr++ = NULL;
}

void LoadWeaponPalette(s32 clutIndex) {
    RECT dstRect;
    u16* src;
    u16* dst;
    s32 i;

    dst = src = D_4000_8017B0BC[clutIndex];
    dst = D_8006EDCC[D_4000_8017B0D0];
    if (src == NULL) {
        return;
    }

    for (i = 0; i < LEN(*D_8006EDCC); i++) {
        *dst++ = *src++;
    }

    dstRect.w = 0x100;
    dstRect.h = 3;
    dstRect.x = 0;
    dstRect.y = 0xF1;
    LoadImage(&dstRect, &D_8006EDCC);
}

void SetSpriteBank1(s16* spriteBankPtr) {
    s16** spriteBankDst = g_api.o.spriteBanks;

    spriteBankDst += 0x10;
    if (D_4000_8017B0D0 != 0) {
        spriteBankDst += 2;
    }
    *spriteBankDst = spriteBankPtr;
}

void SetSpriteBank2(s16* spriteBankPtr) {
    s16** spriteBankDst = g_api.o.spriteBanks;

    spriteBankDst += 0x11;
    if (D_4000_8017B0D0 != 0) {
        spriteBankDst += 2;
    }
    *spriteBankDst = spriteBankPtr;
}

void ResetAnimation(u8 arg0) {
    g_CurrentEntity->ext.weapon.unkAC = arg0;
    g_CurrentEntity->animFrameDuration = 0;
    g_CurrentEntity->animFrameIdx = 0;
}

void DecelerateX(s32 amount) {
    if (g_CurrentEntity->velocityX < 0) {
        g_CurrentEntity->velocityX += amount;
        if (g_CurrentEntity->velocityX > 0) {
            g_CurrentEntity->velocityX = 0;
        }
    } else {
        g_CurrentEntity->velocityX -= amount;
        if (g_CurrentEntity->velocityX < 0) {
            g_CurrentEntity->velocityX = 0;
        }
    }
}

void DecelerateY(s32 amount) {
    if (g_CurrentEntity->velocityY < 0) {
        g_CurrentEntity->velocityY += amount;
        if (g_CurrentEntity->velocityY > 0) {
            g_CurrentEntity->velocityY = 0;
        }
    } else {
        g_CurrentEntity->velocityY -= amount;
        if (g_CurrentEntity->velocityY < 0) {
            g_CurrentEntity->velocityY = 0;
        }
    }
}

void SetSpeedX(s32 speed) {
    if (g_CurrentEntity->facing == 1) {
        speed = -speed;
    }
    g_CurrentEntity->velocityX = speed;
}

void DestroyEntityWeapon(bool arg0) {
    if (arg0 == false) {
        DestroyEntity(&g_Entities[E_WEAPON]);
    }
    if (arg0 == true && g_Player.unk48 != 0) {
        DestroyEntity(&g_Entities[E_WEAPON]);
        g_Player.unk48 = 0;
    }
}

void SetWeaponProperties(Entity* self, s32 kind) {
    Equipment equip;

    g_api.GetEquipProperties(D_4000_8017B0D0, &equip, self->ext.weapon.equipId);
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
        g_api.func_80118894(self);
        break;
    case 2:
        self->attack = equip.attack;
        break;
    }
    if (self->hitboxState == 4) {
        self->attack = 0xFF;
    }
}

void EntityWeaponAttack(Entity* self) {
    u8 temp_v1;
    AnimSoundEvent* sndEvnet;
    s32 mask;

    self->posX.val = g_Entities->posX.val;
    self->posY.val = PLAYER.posY.val;
    self->facing = PLAYER.facing;
    mask = 0x17F;
    sndEvnet = &D_4000_8017B06C[(self->params >> 8) & mask];
    temp_v1 = sndEvnet->ACshift;

    if (!(PLAYER.ext.weapon.unkAC >= temp_v1 &&
          PLAYER.ext.weapon.unkAC < temp_v1 + 7 && g_Player.unk46 != 0)) {
        DestroyEntity(self);
        return;
    }

    if (self->step == 0) {
        SetSpriteBank1(D_4000_8017A040);
        self->animSet = ANIMSET_OVL(0x10);
        self->palette = 0x110;
        self->unk5A = 0x64;
        if (D_4000_8017B0D0 != 0) {
            self->animSet += 2;
            self->palette += 0x18;
            self->unk5A += 2;
        }
        self->palette += sndEvnet->unk8;
        self->flags = FLAG_UNK_20000 | FLAG_UNK_40000;
        self->zPriority = PLAYER.zPriority - 2;
        self->blendMode = 0x30;
        SetWeaponProperties(self, 0);
        self->step++;
    }
    self->ext.generic.unkAC = PLAYER.ext.weapon.unkAC - sndEvnet->ACshift;
    if (PLAYER.animFrameDuration == 1 &&
        PLAYER.animFrameIdx == sndEvnet->soundFrame) {
        g_api.PlaySfx(sndEvnet->soundId);
    }

    if (g_api.UpdateUnarmedAnim(sndEvnet->frameProps, sndEvnet->frames) < 0) {
        DestroyEntity(self);
        return;
    }

    self->unk19 = PLAYER.unk19;
    self->unk1C = PLAYER.unk1C;
    self->rotPivotY = PLAYER.rotPivotY;
}

void func_ptr_80170004(Entity* self) {}

void func_ptr_80170008(Entity* self) {}

void func_ptr_8017000C(Entity* self) {}

void func_ptr_80170010(Entity* self) {}

void func_ptr_80170014(Entity* self) {}

int GetWeaponId(void) { return 0; }

void func_ptr_80170020(Entity* self) {}

void func_ptr_80170024(Entity* self) {}

void func_ptr_80170028(Entity* self) {}

void WeaponUnused2C(void) {}

void WeaponUnused30(void) {}

void WeaponUnused34(void) {}

void WeaponUnused38(void) {}

void WeaponUnused3C(void) {}
