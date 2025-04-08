// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../ric/ric.h"
#include <player.h>

Entity* RicGetFreeEntity(s16 start, s16 end);
INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/182C8", RicGetFreeEntity);

Entity* RicGetFreeEntityReverse(s16 start, s16 end);
INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/182C8", RicGetFreeEntityReverse);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/182C8", func_pspeu_092BE628);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/182C8", func_8015FA5C);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/182C8", RicSetSubweaponParams);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/182C8", func_8015FB84);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/182C8", func_pspeu_092BEA38);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/182C8", RicEntityHitByHoly);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/182C8", RicEntityHitByDark);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/182C8", RicEntityDummy);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/182C8", RicUpdatePlayerEntities);

// clang-format off
INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/182C8", RicCreateEntFactoryFromEntity);
// clang-format on

extern u8 entity_ranges[][2];
void RicEntityFactory(Entity* self) {
    Entity* newEntity;
    s16 nPerCycle;
    s16 i;
    s16 startIndex;
    s16 endIndex;
    u8* data;

    if (self->step == 0) {
        data = (u8*)&g_RicFactoryBlueprints[self->params];
        self->ext.factory.newEntityId = *data++;
        self->ext.factory.amount = *data++;
        self->ext.factory.nPerCycle = *data & 0x3F;
        self->ext.factory.isNonCritical = (s16)(*data >> 7) & 1;
        self->ext.factory.incParamsKind = (s16)(*data++ >> 6) & 1;
        self->ext.factory.tCycle = *data++;
        self->ext.factory.kind = *data & 0x7;
        self->ext.factory.origin = (s16)(*data++ >> 3) & 0x1F;
        self->ext.factory.delay = *data;
        self->flags |= FLAG_KEEP_ALIVE_OFFCAMERA;
        self->step++;
        switch (self->ext.factory.origin) {
        case 0:
            self->flags |= FLAG_POS_CAMERA_LOCKED;
            break;
        case 4:
            self->flags |= FLAG_UNK_20000;
        case 2:
        case 9:
            self->flags |= FLAG_POS_PLAYER_LOCKED;
        case 3:
        case 7:
            self->posX.val = PLAYER.posX.val;
            self->posY.val = PLAYER.posY.val;
            break;
        case 8:
            self->flags |= FLAG_POS_PLAYER_LOCKED;
            self->posX.val = self->ext.factory.parent->posX.val;
            self->posY.val = self->ext.factory.parent->posY.val;
            break;
        }
    } else {
        switch (self->ext.factory.origin) {
        case 0:
            break;
        case 9:
            if (g_Player.unk4E) {
                DestroyEntity(self);
                return;
            }
        case 2:
            self->posX.val = g_Entities->posX.val;
            self->posY.val = PLAYER.posY.val;
            break;
        case 4:
            self->posX.val = g_Entities->posX.val;
            self->posY.val = PLAYER.posY.val;
            if (PLAYER.step != PL_S_RUN) {
                self->entityId = 0;
                return;
            }
            break;
        case 3:
            self->posX.val = g_Entities->posX.val;
            self->posY.val = PLAYER.posY.val;
            if (PLAYER.step == PL_S_HIT) {
                self->entityId = 0;
                return;
            }
            break;
        case 7:
            self->posX.val = g_Entities->posX.val;
            self->posY.val = PLAYER.posY.val;
            if (PLAYER.step != PL_S_HIT) {
                self->entityId = 0;
                return;
            }
            break;
        case 8:
            self->posX.val = self->ext.factory.parent->posX.val;
            self->posY.val = self->ext.factory.parent->posY.val;
            break;
        }
    }
    if (self->ext.factory.delay) {
        if (--self->ext.factory.delay) {
            return;
        }
        self->ext.factory.delay = self->ext.factory.tCycle;
    }
    nPerCycle = self->ext.factory.nPerCycle;
    for (i = 0; i < nPerCycle; i++) {
        data = entity_ranges[0];
        data += self->ext.factory.kind * 2;
        startIndex = *data++;
        endIndex = *data;
        if (self->ext.factory.kind == 0) {
            newEntity = RicGetFreeEntityReverse(startIndex, endIndex + 1);
        } else if (self->ext.factory.kind == 4) {
            newEntity = &g_Entities[31];
        } else if (self->ext.factory.kind == 5) {
            newEntity = &g_Entities[48];
        } else {
            newEntity = RicGetFreeEntity(startIndex, endIndex + 1);
        }
        if (newEntity == NULL) {
            if (self->ext.factory.isNonCritical == 1) {
                self->entityId = 0;
            } else {
                self->ext.factory.delay = self->ext.factory.tCycle;
            }
            return;
        }
        DestroyEntity(newEntity);
        newEntity->entityId =
            self->ext.factory.newEntityId + self->ext.factory.entityIdMod;
        newEntity->params = self->ext.factory.paramsBase;
        // The child  (newEntity) is not an ent factory, but because the
        // factory creates many entities, we can't pick a particular extension.
        // But we're not allowed to use generic, so i'll just reuse entFactory.
        newEntity->ext.factory.parent = self->ext.factory.parent;
        newEntity->posX.val = self->posX.val;
        newEntity->posY.val = self->posY.val;
        newEntity->facingLeft = self->facingLeft;
        newEntity->zPriority = self->zPriority;
        if (self->flags & FLAG_UNK_10000) {
            newEntity->flags |= FLAG_UNK_10000;
        }
        if (self->ext.factory.incParamsKind) {
            newEntity->params += self->ext.factory.spawnIndex;
        } else {
            newEntity->params += i;
        }
        self->ext.factory.spawnIndex++;
        if (self->ext.factory.spawnIndex == self->ext.factory.amount) {
            self->entityId = 0;
            return;
        }
    }
    self->ext.factory.delay = self->ext.factory.tCycle;
}

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/182C8", RicEntitySlideKick);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/182C8", func_80160D2C);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/182C8", RicEntityBladeDash);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/182C8", func_80160F0C);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/182C8", RicEntitySmokePuff);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/182C8", RicEntityHitByCutBlood);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/182C8", func_80161C2C);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/182C8", func_80161EF8);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/182C8", RicEntityApplyMariaPowerAnim);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/182C8", func_801623E0);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/182C8", func_80162604);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/182C8", RicEntityMariaPowers);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/182C8", RicEntityNotImplemented4);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/182C8", RicEntityMaria);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/182C8", func_80162E9C);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/182C8", RicEntityPlayerBlinkWhite);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/182C8", func_801641A0);

// clang-format off
INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/182C8", RicEntityShrinkingPowerUpRing);
// clang-format on

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/182C8", RicEntityHitByIce);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/182C8", RicEntityHitByLightning);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/182C8", func_80165DD8);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/182C8", func_80166024);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/182C8", RicEntityTeleport);
