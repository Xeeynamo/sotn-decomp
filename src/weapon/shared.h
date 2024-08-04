#include "weapon_private.h"

#include "../destroy_entity.h"

static void LoadWeaponPalette(s32 clutIndex) {
    RECT dstRect;
    u16* src;
    u16* dst;
    s32 i;

#if !defined(W_029)
    dst = src = g_WeaponCluts[clutIndex];
    dst = D_8006EDCC[g_HandId];
#else
    dst = D_8006EDCC[g_HandId];
    src = g_WeaponCluts[clutIndex];
#endif
    if (src == NULL) {
        return;
    }

    // I think dst is longer than src so this reads out of bounds
#ifndef VERSION_PC
    for (i = 0; i < LEN(*D_8006EDCC); i++) {
#else
    for (i = 0; i < 112; i++) {
#endif
        *dst++ = *src++;
    }

#if !defined(W_029)
    dstRect.w = 0x100;
    dstRect.h = 3;
    dstRect.x = 0;
    dstRect.y = 0xF1;
#else
    dstRect.x = 0;
    dstRect.w = 0x100;
    dstRect.h = 3;
    dstRect.y = 0xF1;
#endif
    LoadImage(&dstRect, &D_8006EDCC);
}

static void SetSpriteBank1(SpriteParts* animset) {
    SpritePart** spriteBankDst = g_api.o.spriteBanks;

    spriteBankDst += 0x10;
    if (g_HandId != 0) {
        spriteBankDst += 2;
    }
    *spriteBankDst = animset;
}

static void SetSpriteBank2(SpriteParts* animset) {
    SpritePart** spriteBankDst = g_api.o.spriteBanks;

    spriteBankDst += 0x11;
    if (g_HandId != 0) {
        spriteBankDst += 2;
    }
    *spriteBankDst = animset;
}

#if !defined(W_029) && !defined(W_030) && !defined(W_044) && !defined(W_051)
static void SetWeaponAnimation(u8 anim) {
    g_CurrentEntity->ext.weapon.anim = anim;
    g_CurrentEntity->animFrameDuration = 0;
    g_CurrentEntity->animFrameIdx = 0;
}
#endif

#if !defined(W_044)
static void DecelerateX(s32 amount) {
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

static void DecelerateY(s32 amount) {
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

static void SetSpeedX(s32 speed) {
    if (g_CurrentEntity->facingLeft == 1) {
        speed = -speed;
    }
    g_CurrentEntity->velocityX = speed;
}
#endif

#if !defined(W_030) && !defined(W_051)
static void DestroyEntityWeapon(bool arg0) {
    if (arg0 == false) {
        DestroyEntity(&g_Entities[E_WEAPON]);
    }
    if (arg0 == true && g_Player.unk48 != 0) {
        DestroyEntity(&g_Entities[E_WEAPON]);
        g_Player.unk48 = 0;
    }
}
#endif

static void SetWeaponProperties(Entity* self, s32 kind) {
    Equipment equip;

    g_api.GetEquipProperties(g_HandId, &equip, self->ext.weapon.equipId);
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
