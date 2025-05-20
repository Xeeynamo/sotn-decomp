// SPDX-License-Identifier: AGPL-3.0-or-later

#include "../no3/no3.h"

// long imports get split wrongly
// clang-format off

// pushes alucard to the right
void EntityPushAlucard(Entity* self) {
    Entity* player = &PLAYER;
    Tilemap* tilemap = &g_Tilemap;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitSpawner);
        g_CastleFlags[PROLOGUE_COMPLETE] = 0;
        g_Entities[UNK_ENTITY_1].ext.alucardController.unk7C = true;
        g_Player.padSim = 0;
        g_Player.demo_timer = 255;
        player->posX.i.hi = 0;
        g_unkGraphicsStruct.unkC = 0;
        player->animCurFrame = 0;
        g_PauseAllowed = false;
        break;

    case 1:
        player->posX.val += FIX(6);
        if (tilemap->scrollX.i.hi > 0x800) {
            g_Entities[UNK_ENTITY_1].ext.alucardController.unk7C = false;
            g_Player.padSim = PAD_RIGHT;
            self->step++;
        }
        player->animCurFrame = 0;
        g_Player.demo_timer = 1;
        g_api.func_8010E0A8();
        break;

    case 2:
        player->posX.val += FIX(8.5);
        g_unkGraphicsStruct.unkC += 4;
        if (g_unkGraphicsStruct.unkC == 192) {
            self->step++;
            self->ext.alucardController.unk80 = FIX(4.5);
        }
        g_Player.demo_timer = 1;
        g_api.func_8010E0A8();
        break;

    case 3:
        if (g_unkGraphicsStruct.unkC > 128) {
            g_unkGraphicsStruct.unkC -= 1;
            self->ext.alucardController.unk80 = FIX(3.5);
        } else {
            self->ext.alucardController.unk80 = FIX(4.5);
        }
        player->posX.val += self->ext.alucardController.unk80;
        if (self->ext.alucardController.unk80 == FIX(4.5)) {
            self->step++;
        }
        g_Player.demo_timer = 1;
        g_api.func_8010E0A8();
        break;

    case 4:
        player->posX.val += FIX(4.5);
        if (tilemap->scrollX.i.hi > 0xF80) {
            g_api.PlaySfx(SFX_VO_ALU_ATTACK_B);
            g_Player.padSim = PAD_RIGHT | PAD_CROSS;
            self->ext.alucardController.unk7C = false;
            self->step++;
        }
        g_Player.demo_timer = 1;
        g_api.func_8010E0A8();
        break;

    case 5:
        if ((player->velocityY > 0) &&
            !self->ext.alucardController.unk7C) {
            g_Player.padSim = PAD_CROSS;
            self->ext.alucardController.unk7C = true;
        } else {
            g_Player.padSim = PAD_RIGHT | PAD_CROSS;
        }
        g_api.func_8010E0A8();
        player->posX.val += FIX(4.5);
        g_Player.demo_timer = 1;
    }
}

INCLUDE_ASM("st/no3_psp/psp/no3_psp/e_outdoor_ents", EntityCastleDoorTransition);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/e_outdoor_ents", EntityForegroundTree);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/e_outdoor_ents", EntityUnkId50);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/e_outdoor_ents", EntityBackgroundPineTrees);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/e_outdoor_ents", EntityUnkId52);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/e_outdoor_ents", EntityCastleBridge);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/e_outdoor_ents", EntityDistantBackgroundTrees);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/e_outdoor_ents", EntityBackgroundCastleWall);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/e_outdoor_ents", EntityFlyingOwlAndLeaves);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/e_outdoor_ents", EntityFallingLeaf);

// clang-format on
