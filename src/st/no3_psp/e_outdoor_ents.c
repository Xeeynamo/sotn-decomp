// SPDX-License-Identifier: AGPL-3.0-or-later

#include "../no3/no3.h"

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
        if ((player->velocityY > 0) && !self->ext.alucardController.unk7C) {
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

// Pushes Alucard through the castle door at the entrance
void EntityCastleDoorTransition(Entity* self) {
    Entity* player = &PLAYER;
    Tilemap* tilemap = &g_Tilemap;
    switch (self->step) {
    case 0:
        if (g_CastleFlags[PROLOGUE_COMPLETE]) {
            DestroyEntity(self);
            return;
        }
        InitializeEntity(g_EInitSpawner);
        g_Entities[UNK_ENTITY_1].ext.alucardController.unk7C = true;
        g_Player.padSim = PAD_RIGHT;
        g_Player.demo_timer = 255;
        player->posX.i.hi = 8;
        self->ext.castleDoorTransition.playerVelocity = FIX(2.5);
        break;

    case 1:
        player->posX.val += self->ext.castleDoorTransition.playerVelocity;
        g_Player.demo_timer = 1;
        if ((player->posX.i.hi + tilemap->scrollX.i.hi) > 120) {
            g_Player.padSim = 0;
            self->step++;
        }
        break;

    case 2:
        if (self->ext.castleDoorTransition.playerVelocity != 0) {
            self->ext.castleDoorTransition.playerVelocity -= FIX(5.0 / 32);
            EntityExplosionVariantsSpawner(
                player, 1, 1, 4, 0x18, (Random() & 3) + 1, -4);
        } else {
            self->step++;
            g_PauseAllowed = true;
        }
        player->posX.val += self->ext.castleDoorTransition.playerVelocity;
        g_Player.demo_timer = 1;
        break;
    case 3:
        break;
    }
}

static u16 D_801813DC[] = {
    0x0080, 0x0290, 0x0130, 0x0498, 0x01E0, 0x0480, 0x0290, 0x028A, 0x0340,
    0x0298, 0x03F8, 0x0290, 0x04A0, 0x0480, 0x0554, 0x0288, 0x0608, 0x0498,
    0x06B6, 0x0494, 0x0760, 0x0284, 0x0810, 0x0290, 0x08C0, 0x0498, 0x0970,
    0x028E, 0x0A20, 0x0298, 0x0AD0, 0x0482, 0x0B88, 0x0288, 0x0C38, 0x0280,
    0x0CE0, 0x0498, 0x0D90, 0x0286, 0x0E50, 0x0286, 0x0F10, 0x0286, 0x0FD8,
    0x0286, 0x10A0, 0x0286, 0x1160, 0x0286, 0x1240, 0x0286, 0x1320, 0x0286,
    0x1400, 0x0286, 0x14E8, 0x0286, 0x15D0, 0x0286, 0x16C0, 0x0286, 0x17C0,
    0x0286, 0x18D0, 0x0286, 0x19A0, 0x0286, 0xFFFF, 0x0290, 0x0000, 0x0000};
static u16 D_80181468[] = {
    0x0040, 0x0290, 0x00C0, 0x0498, 0x0140, 0x0480, 0x01C0, 0x028A, 0x0240,
    0x0298, 0x02C8, 0x0290, 0x0348, 0x0480, 0x03C0, 0x0288, 0x0440, 0x0498,
    0x04C8, 0x0494, 0x0548, 0x0284, 0x05C0, 0x0290, 0x0640, 0x0498, 0x06C0,
    0x028E, 0x0740, 0x0298, 0x07C0, 0x0482, 0x0848, 0x0288, 0x08C8, 0x0280,
    0x0940, 0x0498, 0x09C0, 0x0286, 0x0A48, 0x0286, 0x0AD0, 0x0290, 0x0B58,
    0x0482, 0x0BE0, 0x0298, 0x0C70, 0x0288, 0x0D00, 0x0286, 0x0D90, 0x0480,
    0x0E30, 0x0292, 0x0EE0, 0x0296, 0x0FC0, 0x0488, 0x10C0, 0x0294, 0x1200,
    0x0482, 0xFFFF, 0x0290, 0x0000, 0x0000};
// large foreground tree during intro
void EntityForegroundTree(Entity* self) {
    Tilemap* tilemap = &g_Tilemap;
    u16* ptrParams;
    u16 var_s4;
    u16 var_s3;
    Entity *ent, *ent2;

    if (self->params) {
        var_s4 = 320;
        ptrParams = &D_80181468[self->ext.foregroundTree.unk7C * 2];
    } else {
        var_s4 = 448;
        ptrParams = &D_801813DC[self->ext.foregroundTree.unk7C * 2];
    }

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitSpawner);
        self->flags |= FLAG_POS_CAMERA_LOCKED;
        self->unk68 = var_s4;
    label:
        if (*ptrParams <= 352) {
            ent = AllocEntity(&g_Entities[192], &g_Entities[256]);
            if (ent != NULL) {
                CreateEntityFromCurrentEntity(E_BACKGROUND_BLOCK, ent);
                ent->posX.i.hi = *ptrParams++;
                var_s3 = *ptrParams++;
                ent->params = ((var_s3 >> 8) & 0xFF) + self->params;
                ent->posY.i.hi = var_s3 & 255;
                ent->unk68 = var_s4;
                if (self->params) {
                    ent->unk6C = 0x60;
                }
            } else {
                ptrParams += 2;
            }
            self->ext.foregroundTree.unk7C++;
            goto label;
        }
        break;

    case 1:
        self->posX.i.hi = 128;
        var_s3 = tilemap->scrollX.i.hi * var_s4 / 256 + 352;
        if (var_s3 >= *ptrParams) {
            ent = AllocEntity(&g_Entities[192], &g_Entities[256]);
            if (ent != NULL) {
                CreateEntityFromCurrentEntity(E_BACKGROUND_BLOCK, ent);
                ent->posX.i.hi = var_s3 - *ptrParams++ + 368;
                var_s3 = *ptrParams;
                ent->params = ((var_s3 >> 8) & 0xFF) + self->params;
                ent->posY.i.hi = var_s3 & 255;
                ent->unk68 = var_s4;
                if (self->params) {
                    ent->unk6C = 0x60;
                } else if (self->ext.foregroundTree.unk7C == 7) {
                    ent2 = AllocEntity(&g_Entities[192], &g_Entities[256]);
                    CreateEntityFromEntity(E_BACKGROUND_BLOCK, ent, ent2);
                    ent2->params = 0x12;
                    ent2->posY.i.hi -= 16;
                    ent2->unk68 = var_s4;
                    ent2->unk6C = 0x40;
                } else if (self->ext.foregroundTree.unk7C == 10) {
                    ent2 = AllocEntity(&g_Entities[192], &g_Entities[256]);
                    CreateEntityFromEntity(E_BACKGROUND_BLOCK, ent, ent2);
                    ent2->params = 0x13;
                    ent2->posY.i.hi += 48;
                    ent2->unk68 = var_s4;
                    ent2->unk6C = 0x40;
                } else if (self->ext.foregroundTree.unk7C == 15) {
                    ent2 = AllocEntity(&g_Entities[192], &g_Entities[256]);
                    CreateEntityFromEntity(E_BACKGROUND_BLOCK, ent, ent2);
                    ent2->params = 0x14;
                    ent2->posY.i.hi += 4;
                    ent2->unk68 = var_s4;
                    ent2->unk6C = 0x40;
                }
            }
            self->ext.foregroundTree.unk7C++;
        }
    }
}

// long imports get split wrongly
// clang-format off
INCLUDE_ASM("st/no3_psp/psp/no3_psp/e_outdoor_ents", EntityUnkId50);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/e_outdoor_ents", EntityBackgroundPineTrees);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/e_outdoor_ents", EntityUnkId52);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/e_outdoor_ents", EntityCastleBridge);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/e_outdoor_ents", EntityDistantBackgroundTrees);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/e_outdoor_ents", EntityBackgroundCastleWall);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/e_outdoor_ents", EntityFlyingOwlAndLeaves);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/e_outdoor_ents", EntityFallingLeaf);

// clang-format on
