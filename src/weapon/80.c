#include "weapon_private.h"

#include "../destroy_entity.h"

INCLUDE_ASM("weapon/w0_000/nonmatchings/80", LoadWeaponPalette);

extern s32 g_HandId;

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


INCLUDE_ASM("weapon/w0_000/nonmatchings/80", EntityWeaponAttack);

void func_pspeu_092F3420(void) {
}

void func_pspeu_092F3428(void) {
}

void func_pspeu_092F3430(void) {
}

void func_pspeu_092F3438(void) {
}

void func_pspeu_092F3440(void) {
}

INCLUDE_ASM("weapon/w0_000/nonmatchings/80", GetWeaponId);

void func_pspeu_092F3458(void) {
}

void func_pspeu_092F3460(void) {
}

void func_pspeu_092F3468(void) {
}

void func_pspeu_092F3470(void) {
}

void func_pspeu_092F3478(void) {
}

void func_pspeu_092F3480(void) {
}

void func_pspeu_092F3488(void) {
}

void func_pspeu_092F3490(void) {
}

// TODO: this should be WEAPON0_PTR
extern void D_8017A000[];
extern Weapon w0_000_Overlay;

void w0_000_Load(void) {
    memcpy(&D_8017A000, &w0_000_Overlay, sizeof(Weapon));
}


// INCLUDE_RODATA("weapon/w0_000/nonmatchings/80", D_pspeu_092F4708);
