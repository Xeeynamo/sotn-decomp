// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../destroy_entity.h"

void LoadWeaponPalette(s32 clutIndex) {
    RECT dstRect;
    u16* dst;
    u16* src;
    s32 i;

    dst = (u16*) &((u16*) g_Clut)[ (((g_HandId * 0x18) + 0x110) * 0x10)];
    src = g_WeaponCluts[clutIndex];

    if (src == NULL) {
        return;
    }

    for (i = 0; i < LEN(*D_8006EDCC); i++) {
        *dst++ = *src++;
    }

    dstRect.x = 0;
    dstRect.w = 0x100;
    dstRect.h = 3;
    dstRect.y = 0xF1;

    dst = (u16*) &((u16*) g_Clut)[0x1100];
    LoadImage(&dstRect, (u_long*) dst);
}

static void SetSpriteBank1(SpriteParts* animset) {
    SpriteParts** spriteBankDst = (SpriteParts**) g_api.o.spriteBanks;

    spriteBankDst += 0x10;
    if (g_HandId != 0) {
        spriteBankDst += 2;
    }
    *spriteBankDst = animset;
}

static void SetWeaponProperties(Entity* self, s32 kind) {
    Equipment equip;
    s32 equipId;

    equipId = self->ext.weapon.equipId;
    g_api.GetEquipProperties(g_HandId, &equip, equipId);
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

