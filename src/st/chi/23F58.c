#include "chi.h"

/*
 * File: 23F58.c
 * Overlay: CHI
 * Description: Abandoned Mine
 */

// [Duplicate]
// func_801A3F58
extern u16 g_InitializeData0[];
#include "../entity_relic_orb.h"

// [Duplicate]
// [Almost duplicate of CEN.EntityHeartDrop -- 0xC0 immediate is 0xB0 here]
// func_801A4A28
extern u16 D_801809E4[];

void func_801A4A28(Entity* self) {
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
// func_801A4B50
#include "../entity_message_box.h"

#include "../check_coll_offsets.h"

// [Duplicate]
// func_801A519C
#include "../entity_unkId13.h"

//D_80181378
u16 g_eUnk14SpawnRots[] = {
    0x0010, 0x0020, 0x0030, 0x0040, 0x0050, 0x0060, 0x0070, 0x0000
};
void EntityUnkId14(Entity*);
// [Duplicate]
// func_801A52AC
#include "../entity_unkId14_spawner.h"

void EntityUnkId15(Entity*);
// [Duplicate]
// func_801A53DC
#include "../entity_unkId15_spawner.h"