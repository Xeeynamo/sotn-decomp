/*
 * File: st_update.c
 * Overlay: CHI
 * Description: STAGE - Update functions
 */

#include "chi.h"

// func_8019DE74: Random
#include "../random.h"

// D_80180A20
u16 UNK_Invincibility0[] = {
    0x8163, 0x8164, 0x8166, 0x8164, 0x8160, 0x8166, 0x8162, 0x8164,
    0x8167, 0x8164, 0x8167, 0x8168, 0x8168, 0x8164, 0x8161, 0x8164,
    0x8165, 0x8165, 0x8163, 0x8163, 0x8165, 0x8165,
};

// func_8019DEA4: Update
#include "../update.h"

// func_8019E1A0: UpdateStageEntities
#include "../update_stage_entities.h"