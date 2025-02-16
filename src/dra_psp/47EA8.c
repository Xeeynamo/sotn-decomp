// SPDX-License-Identifier: AGPL-3.0-or-later
#define FAKE_CreateEntFactoryFromEntity_DECL
#include "../dra/dra.h"
#include "../dra/dra_bss.h"

INCLUDE_ASM("dra_psp/psp/dra_psp/47EA8", GetFreeEntity);

INCLUDE_ASM("dra_psp/psp/dra_psp/47EA8", func_psp_091248D0);

INCLUDE_ASM("dra_psp/psp/dra_psp/47EA8", func_80118894);

INCLUDE_ASM("dra_psp/psp/dra_psp/47EA8", func_80118970);

INCLUDE_ASM("dra_psp/psp/dra_psp/47EA8", func_80118B18);

INCLUDE_ASM("dra_psp/psp/dra_psp/47EA8", func_80118C28);

INCLUDE_ASM("dra_psp/psp/dra_psp/47EA8", func_psp_09124FB8);

INCLUDE_ASM("dra_psp/psp/dra_psp/47EA8", EntityNumberMovesToHpMeter);

INCLUDE_ASM("dra_psp/psp/dra_psp/47EA8", func_psp_09125DB8);

INCLUDE_ASM("dra_psp/psp/dra_psp/47EA8", EntityGuardText);

INCLUDE_ASM("dra_psp/psp/dra_psp/47EA8", EntitySmallRisingHeart);

INCLUDE_ASM("dra_psp/psp/dra_psp/47EA8", func_80119E78);

INCLUDE_ASM("dra_psp/psp/dra_psp/47EA8", func_80119F70);

INCLUDE_ASM("dra_psp/psp/dra_psp/47EA8", func_8011A290);

INCLUDE_ASM("dra_psp/psp/dra_psp/47EA8", func_8011A328);

INCLUDE_ASM("dra_psp/psp/dra_psp/47EA8", func_psp_09127348);

INCLUDE_ASM("dra_psp/psp/dra_psp/47EA8", func_8011A4C8);

INCLUDE_ASM("dra_psp/psp/dra_psp/47EA8", func_8011A4D0);

INCLUDE_ASM("dra_psp/psp/dra_psp/47EA8", func_psp_091279A0);

INCLUDE_ASM("dra_psp/psp/dra_psp/47EA8", func_psp_09127B50);

// Problem: Function clearly treats arg2 as s16 (see here:
// https://decomp.me/scratch/lK7y4) If the function is written here as anything
// but s16, it fails. But that's in conflict with the forward declaration in
// dra.h. So we can try to change that declaration to use s16, but then the
// callers of this function no longer match, because then they're doing `seh` on
// their variables before passing them to this function. So okay, we can delete
// the forward declaration, so that the other functions don't know about arg2
// being s16 and will assume it's an int. But then any function that does
// entity = CreateEntFactoryFromEntity(blah, blah, blah) will fail, because
// without the forward declaration, we also assume the return type is int. And
// we can't implicitly cast int to Entity*.

// We need 3 things to all be true:
// 1. Other functions must know this function returns an Entity*
// 2. Other functions must believe arg2 is an s32
// 3. This function must believe arg2 is an s16.
// I do not know any way to make these all work at the same time.

Entity* CreateEntFactoryFromEntity(
    Entity* source, u32 factoryParams, s16 arg2) {
    Entity* newFactory;

    newFactory = GetFreeEntity(8, 16);
    if (newFactory == NULL) {
        return NULL;
    }

    DestroyEntity(newFactory);
    newFactory->entityId = E_ENTITYFACTORY;
    newFactory->ext.factory.parent = source;
    newFactory->posX.val = source->posX.val;
    newFactory->posY.val = source->posY.val;
    newFactory->facingLeft = source->facingLeft;
    newFactory->zPriority = source->zPriority;
    newFactory->params = factoryParams & 0xFFF;
    if (factoryParams & 0x5000) {
        newFactory->ext.factory.unkA8 = 0xE0;
    }
    if (factoryParams & 0xA000) {
        newFactory->ext.factory.unkA8 = 0xF0;
    }
    newFactory->ext.factory.unkA0 = (factoryParams & 0xFF0000) >> 8;
    newFactory->ext.factory.unk92 = arg2;
    if (source->flags & FLAG_UNK_10000) {
        newFactory->flags |= FLAG_UNK_10000;
    }
    if (factoryParams & 0x1000) {
        newFactory->entityId = 0xEF;
    }
    if (factoryParams & 0x2000) {
        newFactory->entityId = 0xFF;
    }
    if (factoryParams & 0x4000) {
        newFactory->entityId = 0xED;
    }
    if (factoryParams & 0x8000) {
        newFactory->entityId = 0xFD;
    }

    return newFactory;
}

INCLUDE_ASM("dra_psp/psp/dra_psp/47EA8", EntityEntFactory);

INCLUDE_ASM("dra_psp/psp/dra_psp/47EA8", EntityUnarmedAttack);

INCLUDE_ASM("dra_psp/psp/dra_psp/47EA8", EntityDiveKickAttack);

INCLUDE_ASM("dra_psp/psp/dra_psp/47EA8", func_8011B480);

INCLUDE_ASM("dra_psp/psp/dra_psp/47EA8", func_8011B530);

INCLUDE_ASM("dra_psp/psp/dra_psp/47EA8", func_8011B5A4);

INCLUDE_ASM("dra_psp/psp/dra_psp/47EA8", EntityUnkId24);

INCLUDE_ASM("dra_psp/psp/dra_psp/47EA8", func_psp_091295F0);

INCLUDE_ASM("dra_psp/psp/dra_psp/47EA8", EntityPlayerBlinkWhite);

INCLUDE_ASM("dra_psp/psp/dra_psp/47EA8", EntityPlayerOutline);

INCLUDE_ASM("dra_psp/psp/dra_psp/47EA8", func_8011E0E4);

INCLUDE_ASM("dra_psp/psp/dra_psp/47EA8", EntityGravityBootBeam);

INCLUDE_ASM("dra_psp/psp/dra_psp/47EA8", EntityWingSmashTrail);
