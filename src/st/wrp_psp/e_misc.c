// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../wrp/wrp.h"

extern u16 D_80180608[];

INCLUDE_ASM("st/wrp_psp/psp/wrp_psp/e_misc", EntityRelicOrb);

void EntityHeartDrop(Entity* self) {
    u16 index;
    u8 value;
    PfnEntityUpdate update;

    if (!self->step) {
        index = self->ext.heartDrop.unkB4 = self->params + 0x118;
        value = g_CastleFlags[(index >> 3) + HEART_FLAGS_START] >> (index & 7);
        if (value & 1) {
            DestroyEntity(self);
            return;
        }

        index -= 0x118;
        index = D_80180608[index];
        if (index < 128) {
            self->ext.heartDrop.update = EntityPrizeDrop;
        } else {
            self->ext.heartDrop.update = EntityEquipItemDrop;
            index -= 128;
        }
        self->params = index + 0x8000;
    } else {
        index = self->ext.heartDrop.unkB4;
        if (self->step < 5) {
            if (self->hitFlags) {
                g_CastleFlags[(index >> 3) + HEART_FLAGS_START] |=
                    1 << (index & 7);
                self->step = 5;
            }
        }
    }
    update = self->ext.heartDrop.update;
    update(self);
}

u16 g_InitializeData0[];
void BlitChar(char*, s32, s32, s32);
#include "../entity_message_box.h"

#include "../entity_unkId13.h"

#include "../entity_unkId14.h"

#include "../entity_unkId15.h"

extern u16 g_InitializeEntityData0[];

#include "../entity_intense_explosion.h"

#include "../play_sfx_positional.h"
