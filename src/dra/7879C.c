// SPDX-License-Identifier: AGPL-3.0-or-later
#include "dra.h"
#include "dra_bss.h"
#include "objects.h"
#include "sfx.h"

// Given a range of start and end values, finds an unused entity
// slot in g_Entities to fill in. Starts at start, and goes to
// end-1. If none in the range are available, returns NULL.
Entity* GetFreeEntity(s16 start, s16 end) {
    Entity* entity = &g_Entities[start];
    s16 i;

    for (i = start; i < end; i++, entity++) {
        if (entity->entityId == E_NONE) {
            return entity;
        }
    }
    return NULL;
}
// Like GetFreeEntity, but searches for an open spot
// starting from the end and working backward
Entity* GetFreeEntityReverse(s16 start, s16 end) {
    Entity* entity = &g_Entities[end - 1];
    s16 i;

    for (i = end - 1; i >= start; i--, entity--) {
        if (entity->entityId == E_NONE) {
            return entity;
        }
    }
    return NULL;
}

void func_80118894(Entity* self) {
    s32 i;
    s32 search_value;

    if (self == &g_Entities[E_WEAPON]) {
        if (!(self->params & 0x8000)) {
            self->enemyId = 1;
            return;
        }
        self->enemyId = 2;
        return;
    }
    // It appears we're looping over elements of the 8013800C array.
    // If the pointer to arg0 comes before the 32nd (0x20th) g_Entities,
    // we iterate through the 8013800C array, starting from element 3 and going
    // as high as 7, searching for our enemy ID. Otherwise we do the same, but
    // starting from element 7 and going up to 11. 8013800C therefore must have
    // 11 elements. It may be possible to refactor this code to remove the
    // duplication.
    // D_8013800C looks to be keeping track of how many abilities/attacks are
    // targeting a specific enemy selecting the lowest targeted entity from 3-6
    // or 7-11
    search_value = 0;
    if (self < &g_Entities[UNK_ENTITY_20]) {
        while (1) {
            for (i = 3; i < 7; i++) {
                if (D_8013800C[i] == search_value) {
                    D_8013800C[i]++;
                    self->enemyId = i;
                    return;
                }
            }
            search_value++;
        }
    } else {
        while (1) {
            for (i = 7; i < 11; i++) {
                if (D_8013800C[i] == search_value) {
                    D_8013800C[i]++;
                    self->enemyId = i;
                    return;
                }
            }
            search_value++;
        }
    }
}

extern s32 D_80138038; // BSS
Entity* func_80118970(void) {
    s32 big_arr[128];
    Entity* ent;
    s32 i;
    s32 successes;
    s32 var_v1;
    s32 temp_a0;

    successes = 0;
    // Hunt through these entities looking for ones that match all criteria.
    // Call them a success and increment successes.
    ent = &g_Entities[STAGE_ENTITY_START];
    for (i = 0; i < 128; i++, ent++) {
        big_arr[i] = 0;
        if ((ent->entityId != 0) && (ent->hitboxState != 0) &&
            !(ent->flags & FLAG_UNK_00200000) &&
            ((LOH(ent->posX.i.hi) >= -16) && (ent->posX.i.hi < 273)) &&
            ((LOH(ent->posY.i.hi) < 241) && (ent->posY.i.hi >= 0)) &&
            (ent->hitPoints < 0x7000)) {
            successes++;
            if (!(ent->flags & FLAG_UNK_80000)) {
                ent->flags |= FLAG_UNK_80000;
                return ent;
            }
            big_arr[i] = 1;
        }
    }

    if (successes != 0) {
        temp_a0 = D_80138038;
        var_v1 = temp_a0 / 128;
        var_v1 = temp_a0 - var_v1 * 128;
        for (i = 0; i < 128; i++) {
            temp_a0 = var_v1 + 1;
            if (big_arr[var_v1] != 0) {
                ent = &g_Entities[STAGE_ENTITY_START + var_v1];
                D_80138038 = temp_a0 - temp_a0 / 128 * 128;
                return ent;
            }
            var_v1 = temp_a0 / 128;
            var_v1 = temp_a0 - var_v1 * 128;
        }
    }
    return NULL;
}

s16 func_80118B18(Entity* ent1, Entity* ent2, s16 facingLeft) {
    s16 var_a1;
    s16 posY;
    s16 posX;
    s16 temp;
    s16 diffY;
    s16 diffX;

    if (ent2 != NULL) {
        posX = ent2->posX.i.hi;
        posY = ent2->posY.i.hi;
    } else {
        posY = 112;
        if (facingLeft) {
            posX = -32;
        } else {
            posX = 288;
        }
    }

    diffX = posX - ent1->posX.i.hi;
    diffY = posY - ent1->posY.i.hi;
    temp = ratan2(-diffY, diffX) & 0xFFF;

    var_a1 = 0;
    if (ent2 != NULL) {
        if (ent2->entityId == E_NONE) {
            var_a1 = 0x1000;
        }
        if (ent2->hitboxState == 0) {
            var_a1 = 0x2000;
        }
        if (ent2->flags & FLAG_UNK_00200000) {
            var_a1 = 0x3000;
        }
    }
    if (ent1->posX.i.hi > 288) {
        var_a1 = 0x4000;
    }

    if (ent1->posX.i.hi < -32) {
        var_a1 = 0x5000;
    }
    if (ent1->posY.i.hi > 240) {
        var_a1 = 0x6000;
    }

    if (ent1->posY.i.hi < 0) {
        var_a1 = 0x7000;
    }
    return temp - var_a1;
}

void func_80118C28(s32 arg0) {
    D_8013803C = D_800ACFB4[arg0][0];
    D_80138040 = D_800ACFB4[arg0][1];
    D_80138044 = D_800ACFB4[arg0][2];
    D_80138048 = D_800ACFB4[arg0][3];
}

s32 CreateHPNumMove(s32 arg0, s32 arg1) {
    Entity* entity = GetFreeEntity(0x38, 0x40);

    if (entity != NULL) {
        DestroyEntity(entity);
        entity->entityId = ENTITY_13;
        entity->posX.val = PLAYER.posX.val;
        entity->posY.val = PLAYER.posY.val;
        entity->ext.hpNumMove.number = arg0;
        entity->ext.hpNumMove.type = arg1;
        return 0;
    }
    return -1;
}
