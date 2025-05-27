// SPDX-License-Identifier: AGPL-3.0-or-later

#include "../no3/no3.h"

static void func_801CC5A4(Entity* entity, u8 count, u8 params, s16 xDist,
                          s16 yDist, u8 arg5, s16 xOfst) {
    s32 i;
    s16 x = entity->posX.i.hi + xDist;
    s16 y = entity->posY.i.hi + yDist;

    for (i = 0; i < count; ++i) {
        Entity* newEnt = AllocEntity(&g_Entities[160], &g_Entities[192]);
        if (newEnt != NULL) {
            newEnt->entityId = E_EXPLOSION_VARIANTS;
            newEnt->pfnUpdate = EntityExplosionVariants;
            newEnt->params = params;
            newEnt->posX.i.hi = x + i * xOfst;
            newEnt->posY.i.hi = y;
            newEnt->ext.destructAnim.index = D_80182A48[i];
            newEnt->rotX = D_80182A38[D_80182A48[i] + arg5];
            newEnt->rotY = newEnt->rotX;
            newEnt->drawFlags = FLAG_DRAW_ROTY | FLAG_DRAW_ROTX;
            newEnt->zPriority = entity->zPriority + 1;
        }
    }
}

INCLUDE_ASM("st/no3_psp/psp/no3_psp/e_fire_warg", func_pspeu_09249590);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/e_fire_warg", func_pspeu_09249738);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/e_fire_warg", func_pspeu_09249878);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/e_fire_warg", EntityFireWarg);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/e_fire_warg", EntityUnkId30);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/e_fire_warg", EntityUnkId31);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/e_fire_warg", EntityExplosion3);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/e_fire_warg", func_pspeu_0924C7A8);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/e_fire_warg", EntityFireWargWaveAttack);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/e_fire_warg", EntityUnkId2F);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/e_fire_warg", EntityFireWargDeathBeams);
