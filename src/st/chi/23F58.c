/*
 * File: 23F58.c
 * Overlay: CHI
 * Description: Abandoned Mine
 */

#include "chi.h"

extern u16 g_InitializeData0[];

// D_80181314: g_RelicOrbTexts
// D_80181318: g_RelicOrbTextBg1EY
// D_80181328: g_RelicOrbTextBg1SY
// D_80181338: g_RelicOrbTextBg2SY
// D_80181348: g_RelicOrbTextBg2EY
// D_80181358: g_RelicOrbSparkleX
// D_80181368: g_RelicOrbSparkleY
// [Duplicate]
// func_801A3F58: [E_RELIC_ORB] EntityRelicOrb
#include "../entity_relic_orb.h"

extern u16 D_801809E4[];

// [Duplicate]
// [Almost duplicate of CEN.EntityHeartDrop -- 0xC0 immediate is 0xB0 here]
// E_HEART_DROP
// func_801A4A28
void EntityHeartDrop(Entity* self) {
    u16 temp_a0;
    u16 temp_a0_2;
    u16 var_a0;

    if (self->step == 0) {
        temp_a0 = self->params + 0xB0;
        self->ext.generic.unkB4 = temp_a0;
        if ((D_8003BEEC[temp_a0 >> 3] >> (temp_a0 & 7)) & 1) {
            DestroyEntity(self);
            return;
        }
        temp_a0_2 = temp_a0 - 0xB0;
        var_a0 = D_801809E4[temp_a0_2];
        if (var_a0 < 128) {
            self->ext.generic.unkB8.unkFuncB8 = EntityPrizeDrop;
        } else {
            self->ext.generic.unkB8.unkFuncB8 = EntityEquipItemDrop;
            var_a0 -= 128;
        }
        self->params = var_a0 + 0x8000;
    } else {
        temp_a0_2 = self->ext.generic.unkB4;
        if (self->step < 5) {
            if (self->hitFlags != 0) {
                var_a0 = self->ext.generic.unkB4;
                D_8003BEEC[temp_a0_2 >> 3] |= 1 << (var_a0 & 7);
                self->step = 5;
            }
        }
    }
    self->ext.generic.unkB8.unkFuncB8(self);
}

// [Duplicate]
// func_801A4B50: [E_SAVE_GAME_POPUP] EntityMessageBox
#include "../entity_message_box.h"

// func_801A50AC: CheckColliderOffsets
#include "../check_coll_offsets.h"

// [Duplicate]
// func_801A519C: [E_ID_13] EntityUnkId13
#include "../entity_unkId13.h"

//D_80181378
u16 g_eUnk14SpawnRots[] = {
    0x0010, 0x0020, 0x0030, 0x0040, 0x0050, 0x0060, 0x0070, 0x0000
};
void EntityUnkId14(Entity*);

// [Duplicate]
// func_801A52AC: EntityUnkId14Spawner
#include "../entity_unkId14_spawner.h"

void EntityUnkId15(Entity*);

// [Duplicate]
// func_801A53DC: EntityUnkId15Spawner
#include "../entity_unkId15_spawner.h"