// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no3.h"

// pushes alucard to the right
void EntityPushAlucard(Entity* self) {
    Entity* player = &PLAYER;
    Tilemap* tilemap = &g_Tilemap;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitSpawner);
        #ifdef VERSION_PSP
        g_CastleFlags[PROLOGUE_COMPLETE] = 0;
        #endif
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
    0x0286, 0x18D0, 0x0286, 0x19A0, 0x0286, 0xFFFF, 0x0290};
static u16 D_80181468[] = {
    0x0040, 0x0290, 0x00C0, 0x0498, 0x0140, 0x0480, 0x01C0, 0x028A, 0x0240,
    0x0298, 0x02C8, 0x0290, 0x0348, 0x0480, 0x03C0, 0x0288, 0x0440, 0x0498,
    0x04C8, 0x0494, 0x0548, 0x0284, 0x05C0, 0x0290, 0x0640, 0x0498, 0x06C0,
    0x028E, 0x0740, 0x0298, 0x07C0, 0x0482, 0x0848, 0x0288, 0x08C8, 0x0280,
    0x0940, 0x0498, 0x09C0, 0x0286, 0x0A48, 0x0286, 0x0AD0, 0x0290, 0x0B58,
    0x0482, 0x0BE0, 0x0298, 0x0C70, 0x0288, 0x0D00, 0x0286, 0x0D90, 0x0480,
    0x0E30, 0x0292, 0x0EE0, 0x0296, 0x0FC0, 0x0488, 0x10C0, 0x0294, 0x1200,
    0x0482, 0xFFFF, 0x0290};
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
        // This is a weird way to make a while-loop.
        while(true){
            if (*ptrParams > 352) {
                break;
            }
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

static u16 D_801814EC[] = {0x0020,0x0006,0x003E,0x0007,0x005E,0x0008,0x007E,0x0007,0x009C,0x0009,0x00E0,0x0006,0x00FE,0x0008,0x011C,0x0009,0x0170,0x0006,0x018E,0x0008,0x01AE,0x0007,0x01CE,0x0007,0x01EE,0x0008,0x020E,0x0007,0x022C,0x0009,0x02A0,0x0006,0x02BE,0x0007,0x02DE,0x0008,0x02FC,0x0009,0x0360,0x0006,0x037E,0x0007,0x039E,0x0008,0x03BE,0x0007,0x03DE,0x0007,0x03FC,0x0009,0x0460,0x0006,0x047E,0x0007,0x049E,0x0007,0x04BE,0x0008,0x04DE,0x0007,0x04FE,0x0007,0x051E,0x0008,0x053C,0x0009,0x0620,0x0006,0x063E,0x0007,0x065E,0x0008,0x067E,0x0007,0x069C,0x0009,0x06E0,0x0006,0x06FE,0x0008,0x071C,0x0009,0x0770,0x0006,0x078E,0x0008,0x07AE,0x0007,0x07CE,0x0007,0x07EE,0x0008,0x080E,0x0007,0x082C,0x0009,0x08A0,0x0006,0x08BE,0x0007,0x08DE,0x0008,0x08FC,0x0009,0x0960,0x0006,0x097E,0x0007,0x099E,0x0008,0x09BE,0x0007,0x09DE,0x0007,0x09FC,0x0009,0x0A60,0x0006,0x0A7E,0x0007,0x0A9E,0x0007,0x0ABE,0x0008,0x0ADE,0x0007,0x0AFE,0x0007,0x0B1E,0x0008,0x0B3C,0x0009,0x0BB0,0x0006,0x0BCE,0x0007,0x0BEE,0x0007,0x0C0E,0x0008,0x0C2C,0x0009,0xFFFF,0x0002};

void EntityUnkId50(Entity* self) {
    Tilemap* tilemap = &g_Tilemap;
    Entity* newEntity;
    u16 temp_s3;
    u16* ptr;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitSpawner);
        self->flags |= FLAG_POS_CAMERA_LOCKED;
        self->unk68 = 0xC0;
        self->ext.et_801BCC4C.unk7C = 0;
        ptr = D_801814EC;
        while(true){
            if (*ptr > 288) {
                break;
            }
            newEntity = AllocEntity(&g_Entities[192], &g_Entities[256]);
            if (newEntity != NULL) {
                CreateEntityFromCurrentEntity(E_BACKGROUND_BLOCK, newEntity);
                newEntity->posX.i.hi = *ptr++;
                newEntity->params = *ptr++;
                newEntity->unk68 = 0xC0;
            } else {
                ptr += 2;
            }
            self->ext.et_801BCC4C.unk7C++;
        }
        break;

    case 1:
        self->posX.i.hi = 128;
        ptr = &D_801814EC[self->ext.et_801BCC4C.unk7C * 2];
        temp_s3 = tilemap->scrollX.i.hi * 0xC0 / 0x100 + 288;
        if (temp_s3 >= ptr[0]) {
            newEntity = AllocEntity(&g_Entities[192], &g_Entities[256]);
            if (newEntity != NULL) {
                CreateEntityFromCurrentEntity(E_BACKGROUND_BLOCK, newEntity);
                newEntity->posX.i.hi = temp_s3 - *ptr++ + 288;
                newEntity->posX.i.lo = self->posX.i.lo;
                newEntity->params = *ptr++;
                newEntity->unk68 = 0xC0;
            }
            self->ext.et_801BCC4C.unk7C++;
        }
        break;
    }
}

static u16 pineSet1[] = {0x0010,0x000B,0x0031,0x0003,0x0040,0x0102,0x0068,0x0104,0x0088,0x0005,0x00AC,0x0103,0x00D1,0x0107,0x00F3,0x0105,0x011C,0x000A,0x0132,0x0107,0x0151,0x010B,0x0178,0x010B,0x0190,0x0002,0x01A6,0x010A,0x01D0,0x0100,0x01F2,0x0102,0x0220,0x0005,0x0231,0x0108,0x0250,0x0106,0x0270,0x0007,0x0288,0x0105,0x02C0,0x0009,0x02E4,0x010A,0x0308,0x010B,0x0324,0x0104,0x0354,0x0102,0x036B,0x0004,0x038C,0x010B,0x03A8,0x0107,0x03D1,0x0108,0x03F4,0x0005,0x0418,0x0102,0x0440,0x0101,0x046C,0x0102,0x0484,0x0005,0x04B0,0x0001,0x04CC,0x0102,0x04EF,0x0107,0x0514,0x0107,0x0538,0x0006,0x055B,0x0002,0x0587,0x0103,0x05A1,0x010B,0x05C0,0x0000,0x05E6,0x0105,0x0602,0x0003,0x062A,0x010A,0x064E,0x0100,0x0678,0x0002,0x069A,0x0107,0x06C0,0x0104,0x06EC,0x0002,0x0714,0x0104,0x073C,0x0106,0x0764,0x000B,0x0790,0x0107,0x07A0,0x0002,0x07D0,0x0105,0x0810,0x0001,0xFFFF};
static u16 pineSet2[] = {0x000C,0x0100,0x002A,0x010A,0x0048,0x0004,0x0066,0x0100,0x0084,0x000A,0x00A2,0x0101,0x00C0,0x000B,0x00DE,0x0104,0x00FD,0x0103,0x011A,0x000B,0x0138,0x0104,0x0155,0x0006,0x0173,0x0101,0x0191,0x0102,0x01B0,0x0104,0x01CE,0x010B,0x01EC,0x0007,0x0209,0x0100,0x0228,0x0104,0x0246,0x0101,0x0264,0x0105,0x0282,0x0009,0x02A0,0x010B,0x02BE,0x0103,0x02DC,0x0009,0x02FB,0x0001,0x031A,0x0108,0x0339,0x000B,0x035A,0x0105,0x037A,0x0006,0x039C,0x0104,0x03BE,0x0101,0x03E0,0x0104,0x0402,0x0101,0xFFFF};
static u16 pineSet3[] = {0x000A,0x0105,0x0026,0x0100,0x0041,0x0007,0x005D,0x0101,0x0078,0x0008,0x0094,0x0101,0x00B1,0x0004,0x00CD,0x0102,0x00E9,0x0107,0x0105,0x010B,0x0122,0x0005,0x013E,0x0103,0x015C,0x0000,0x0179,0x0107,0x019A,0x010A,0x01BA,0x0002,0x01DA,0x0106,0x01FE,0x0000,0xFFFF};
static u16 D_801817D4[] = {0x80, 0x40, 0x20};
static u16 D_801817DC[] = {0x100, 0xD8, 0xB0};
static u8 D_801817E4[] = {0x80, 0x60, 0x40};
static u16 D_801817E8[] = {0x17, 0x49};
static u16* D_801817EC[] = {pineSet1, pineSet2, pineSet3};

// part of parallax background with pine trees
void EntityBackgroundPineTrees(Entity* self) {
    Tilemap* gTilemap = &g_Tilemap;
    u16 selfUnk68;
    s32 primIndex;
    u16* var_s5;
    u16 var_s4;
    u16 width;
    u16 xpos;
    Primitive* prim_s1;
    Primitive* prim_s0;

    xpos = self->params; // Temporary reuse of xpos var for params
    selfUnk68 = D_801817D4[xpos];
    var_s5 = D_801817EC[xpos];
    var_s5 += self->ext.ILLEGAL.u16[0] * 2;
    var_s4 = D_801817DC[xpos];
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitSpawner);
        self->flags |= FLAG_POS_CAMERA_LOCKED;
        self->unk68 = selfUnk68;
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 32);
        if (primIndex == 0) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;

        for (prim_s0 = &g_PrimBuf[primIndex]; prim_s0 != NULL;
             prim_s0 = prim_s0->next) {
            prim_s0->drawMode = DRAW_HIDE;
        }

        for (prim_s0 = &g_PrimBuf[primIndex]; true; prim_s0 = prim_s1->next) {
            if (*var_s5 >= 0x121) {
                return;
            }
            self->ext.ILLEGAL.u16[0]++;
            for (; prim_s0 != NULL; prim_s0 = prim_s0->next) {
                if (prim_s0->drawMode == DRAW_HIDE) {
                    break;
                }
            }
            if (prim_s0 == NULL) {
                return;
            }

            for (prim_s1 = prim_s0->next; prim_s1 != NULL;
                 prim_s1 = prim_s1->next) {
                if (prim_s1->drawMode == DRAW_HIDE) {
                    break;
                }
            }
            if (prim_s1 == NULL) {
                return;
            }
            prim_s0->tpage = 0xE;
            prim_s0->u0 = prim_s0->u2 = 0x80;
            prim_s0->u1 = prim_s0->u3 = 0x80 + 0x28;
            prim_s0->v0 = prim_s0->v1 = 0x80;
            prim_s0->v2 = prim_s0->v3 = 0x80 + 0x50;

            prim_s1->tpage = 0xF;
            prim_s1->u0 = prim_s1->u2 = 0xB0;
            prim_s1->u1 = prim_s1->u3 = 0xB0 + 0x08;
            prim_s1->v0 = prim_s1->v1 = 0xC8;
            prim_s1->v2 = prim_s1->v3 = 0xC8 + 0x30;

            xpos = *var_s5++;
            width = var_s4 * 20 / 256;

            prim_s0->x0 = prim_s0->x2 = xpos - width;
            prim_s0->x1 = prim_s0->x3 = xpos + width;

            width = var_s4 * 4 / 256;

            prim_s1->x0 = prim_s1->x2 = xpos - width + 1;
            prim_s1->x1 = prim_s1->x3 = xpos + width + 1;

            xpos = *var_s5++;

            prim_s0->clut = prim_s1->clut = D_801817E8[(xpos >> 8) & 0xFF];

            prim_s0->y2 = prim_s0->y3 =
                0x9C - ((0x2C - (xpos & 0xFF)) * var_s4 / 256);

            prim_s0->y0 = prim_s0->y1 = prim_s0->y2 - (var_s4 * 80 / 256);

            prim_s1->y2 = prim_s1->y3 = 0x9C;
            prim_s1->y0 = prim_s1->y1 = 0x9C - 0x30;
            // Set all colors for both prims.
            PCOL(prim_s0) = PCOL(prim_s1) = D_801817E4[self->params];
            prim_s0->priority = 0x3F - (self->params * 2);
            prim_s1->priority = prim_s0->priority - 1;
            prim_s0->drawMode = prim_s1->drawMode = DRAW_COLORS;
        }
    case 1:
        xpos = 0x80 - self->posX.i.hi;
        self->posX.i.hi = 0x80;

        for (prim_s0 = &g_PrimBuf[self->primIndex]; prim_s0 != NULL;
             prim_s0 = prim_s0->next) {
            if (prim_s0->drawMode != DRAW_HIDE) {
                prim_s0->x0 = prim_s0->x2 -= xpos;
                prim_s0->x1 = prim_s0->x3 -= xpos;
                if (prim_s0->x1 <= 0) {
                    prim_s0->drawMode = DRAW_HIDE;
                }
            }
        }
        xpos = gTilemap->scrollX.i.hi * selfUnk68 / 256 + 0x120;

        if (xpos < *var_s5) {
            return;
        }
        self->ext.ILLEGAL.u16[0]++;
        for (prim_s0 = &g_PrimBuf[self->primIndex]; prim_s0 != NULL;
             prim_s0 = prim_s0->next) {
            if (prim_s0->drawMode == DRAW_HIDE) {
                for (prim_s1 = prim_s0->next; prim_s1 != NULL;
                     prim_s1 = prim_s1->next) {
                    if (prim_s1->drawMode == DRAW_HIDE) {
                        prim_s0->tpage = 0xE;
                        prim_s0->u0 = prim_s0->u2 = 0x80;
                        prim_s0->u1 = prim_s0->u3 = 0x80 + 0x28;
                        prim_s0->v0 = prim_s0->v1 = 0x80;
                        prim_s0->v2 = prim_s0->v3 = 0x80 + 0x50;

                        prim_s1->tpage = 0xF;
                        prim_s1->u0 = prim_s1->u2 = 0xB0;
                        prim_s1->u1 = prim_s1->u3 = 0xB0 + 0x08;
                        prim_s1->v0 = prim_s1->v1 = 0xC8;
                        prim_s1->v2 = prim_s1->v3 = 0xC8 + 0x30;

                        xpos = 0x120 - (xpos - *var_s5++);
                        width = var_s4 * 20 / 256;

                        prim_s0->x0 = prim_s0->x2 = xpos - width;
                        prim_s0->x1 = prim_s0->x3 = xpos + width;

                        width = var_s4 * 4 / 256;

                        prim_s1->x0 = prim_s1->x2 = xpos - width + 1;
                        prim_s1->x1 = prim_s1->x3 = xpos + width + 1;

                        xpos = *var_s5;
                        prim_s0->clut = prim_s1->clut =
                            D_801817E8[(xpos >> 8) & 0xFF];
                        prim_s0->y2 = prim_s0->y3 =
                            0x9C - ((0x2C - (xpos & 0xFF)) * var_s4 / 256);
                        prim_s0->y0 = prim_s0->y1 =
                            prim_s0->y2 - (var_s4 * 80 / 256);
                        prim_s1->y2 = prim_s1->y3 = 0x9C;
                        prim_s1->y0 = prim_s1->y1 = 0x9C - 0x30;
                        // Set all colors for both prims.
                        PCOL(prim_s0) = PCOL(prim_s1) =
                            D_801817E4[self->params];
                        prim_s0->priority = 0x3F - (self->params * 2);
                        prim_s1->priority = prim_s0->priority - 1;
                        prim_s0->drawMode = prim_s1->drawMode = DRAW_COLORS;
                        break;
                    }
                }
                break;
            }
        }
        break;
    }
}

static u16 D_801817F8[] = {0x20, 0x60, 0xA0, 0xE0, 0x120, 0x15F, 0xFFFF};

void EntityUnkId52(Entity* self) {
    Tilemap* tilemap = &g_Tilemap;
    Entity* newEntity;
    u16 temp_s3;
    u16* ptr;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitSpawner);
        self->flags |= FLAG_POS_CAMERA_LOCKED;
        self->ext.et_801BCC4C.unk7C = 0;
        ptr = D_801817F8;
        while(true){
            if (*ptr > 288) {
                break;
            }
            newEntity = AllocEntity(&g_Entities[192], &g_Entities[256]);
            if (newEntity != NULL) {
                CreateEntityFromCurrentEntity(E_BACKGROUND_BLOCK, newEntity);
                newEntity->posX.i.hi = *ptr;
                newEntity->params = 0x10;
                newEntity->unk68 = 0x18;
            }
            ptr++;
            self->ext.et_801BCC4C.unk7C++;
        }
        break;

    case 1:
        self->posX.i.hi = 0x80;
        ptr = &D_801817F8[self->ext.et_801BCC4C.unk7C];
        temp_s3 = tilemap->scrollX.i.hi * 0x18 / 0x100 + 288;
        if (temp_s3 >= *ptr) {
            newEntity = AllocEntity(&g_Entities[192], &g_Entities[256]);
            if (newEntity != NULL) {
                CreateEntityFromCurrentEntity(E_BACKGROUND_BLOCK, newEntity);
                newEntity->posX.i.hi = temp_s3 - *ptr + 288;
                newEntity->posX.i.lo = self->posX.i.lo;
                newEntity->params = 0x10;
                if (self->ext.et_801BCC4C.unk7C == 5) {
                    newEntity->params++;
                }
                newEntity->unk68 = 0x18;
            }
            self->ext.et_801BCC4C.unk7C++;
        }
        break;
    }
}

static s16 D_80181808[] = {-338, -20, -338, 12, -304, -20, -304, 12, -306, -15, -306, 13, -274, -15, -274, 13, -242, -15, -242, 13, -210, -15, -210, 13, -178, -15, -178, 13, -146, -15, -146, 13, -114, -15, -114, 13, -82, -15, -82, 13, -50, -15, -50, 13, -18, -15, -18, 13, 10, -15, 10, 13};
static s16 D_80181870[] = {-4, -8, 24, -8, -4, 8, 24, 8, 12, -3, 40, -3, 12, 4, 40, 4, 28, -8, 56, -8, 28, 8, 56, 8, 44, -3, 72, -3, 44, 4, 72, 4, 60, -8, 88, -8, 60, 8, 88, 8, 76, -3, 104, -3, 76, 4, 104, 4, 92, -8, 120, -8, 92, 8, 120, 8, 108, -3, 136, -3, 108, 4, 136, 4, 124, -8, 152, -8, 124, 8, 152, 8, 140, -3, 168, -3, 140, 4, 168, 4, 156, -8, 184, -8, 156, 8, 184, 8, 172, -3, 200, -3, 172, 4, 200, 4, 188, -8, 216, -8, 188, 8, 216, 8};
static u8 g_EntityCastleBridgeUVs[] = {16, 50, 224, 255, 58, 90, 226, 254, 130, 162, 98, 126, 170, 198, 192, 208, 74, 102, 129, 136, 170, 198, 208, 192};
static s16 g_EntityCastleBridgeUVOffsets[] = {0, 8, 4, 8, 4, 8, 4, 8, 4, 8, 4, 12, 16, 12, 16, 20, 16, 12, 16, 12, 16, 12, 16, 12};
static u8 g_EntityCastleBridgePages[] = {14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 15, 14, 15, 14, 15, 14, 15, 14, 15, 14, 15, 14};
static u16 g_EntityCastleBridgePriorities[] = {192, 192, 192, 192, 192, 192, 192, 192, 192, 192, 192, 191, 192, 191, 192, 191, 192, 191, 192, 191, 192, 191, 192, 191};

void EntityCastleBridge(Entity* self) {
    const u32 primCount = 24;

    MATRIX* matrix;
    Primitive* prim;
    SVECTOR* vector;
    VECTOR* rotatedVector;
    s16* positionsPtr;
    s16* size;

    s16 xOffset;
    // self stored at    sp 0x40
    s16 yOffset;      // sp 0x3E
    s16 sinZ;         // sp 0x3C
    s16 cosZ;         // sp 0x3A
    Tilemap* tilemap; // sp 0x34
    Entity* player;   // sp 0x30

    u8* uv;
    s32 primIndex;

    tilemap = &g_Tilemap;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitSpawner);

        primIndex = g_api.AllocPrimitives(PRIM_GT4, primCount);

        if (primIndex == 0) {
            DestroyEntity(self);
            return;
        }

        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];

        for (primIndex = 0; prim != NULL; primIndex++) {
            uv = &g_EntityCastleBridgeUVs
                     [g_EntityCastleBridgeUVOffsets[primIndex]];

            prim->u0 = prim->u2 = *uv++;
            prim->u1 = prim->u3 = *uv++;
            prim->v0 = prim->v1 = *uv++;
            prim->v2 = prim->v3 = *uv;

            prim->tpage = g_EntityCastleBridgePages[primIndex];
            prim->clut = 0x66;
            prim->priority = g_EntityCastleBridgePriorities[primIndex];
            prim->drawMode = DRAW_UNK02;

            prim = prim->next;
        }

        self->rotZ = 0;
        break;
    case 1:
        if (tilemap->scrollX.i.hi > 3904) {
            self->step++;
            g_api.PlaySfx(SE_CASTLE_GATE_RISE);
        }
        break;
    case 2:

        if (self->rotZ < 1024) {
            self->rotZ += 4;
        }

        player = &PLAYER;
        sinZ = rsin(self->rotZ); // the result is a signed(?) fixed point 12 bit
                                 // fractional number where 4096 == 1.0
        cosZ = rcos(self->rotZ);

        // the operation (sinZ * 12) >> 12 gives an integer between -12 and 12
        // based on the y coordinate of the rotated vector i am guessing that
        // 4563 is some tilemap offset?
        xOffset = (((sinZ * 12) >> 12) + 4563) -
                  (player->posX.i.hi + tilemap->scrollX.i.hi);

        // divide by zero check
        if (xOffset >= 0 && cosZ) {

            // sinZ / cosZ is suspiciously like a tangent
            xOffset = 172 - ((cosZ * 12) >> 12) - ((xOffset * sinZ) / cosZ);

            if (xOffset > 0 && xOffset < 160) {
                switch (self->step_s) {
                case 0:
                    if (player->velocityY < 0) {
                        self->step_s++;
                    }
                    break;
                case 1:
                    if (player->velocityY >= 0 &&
                        (xOffset < player->posY.i.hi + 30)) {
                        player->posY.i.hi = xOffset - 30;
                        g_api.PlaySfx(SFX_STOMP_SOFT_A);
                        g_Player.vram_flag |= 0x41;
                        self->step_s++;
                    }
                    break;
                case 2:
                    player->posY.i.hi = xOffset - 30;
                    g_Player.vram_flag |= 0x41;
                    break;
                }
            }
        }
        break;
    }

    vector = (SVECTOR*)SP(0);
    rotatedVector = (VECTOR*)SP(8);
    size = (s16*)SP(0x18);
    // identity matrix
    matrix = (MATRIX*)SP(0x20);
    matrix->m[0][0] = matrix->m[1][1] = matrix->m[2][2] = 0x1000; // pain.
    matrix->m[0][1] = matrix->m[0][2] = matrix->m[1][0] = matrix->m[1][2] =
        matrix->m[2][0] = matrix->m[2][1] = 0;

    matrix = RotMatrixZ(self->rotZ, matrix);
    SetRotMatrix(matrix);
    positionsPtr = D_80181808;
    xOffset = 4563 - tilemap->scrollX.i.hi;

    for (primIndex = 0, vector->vz = 0, prim = &g_PrimBuf[self->primIndex]; primIndex < 11; primIndex++) {
        if (primIndex < 2) {
            vector->vx = *positionsPtr++;
            vector->vy = *positionsPtr++;
            ApplyRotMatrix(vector, rotatedVector);

            prim->x0 = (s16)rotatedVector->vx + xOffset;
            prim->y0 = (s16)rotatedVector->vy + 168;

            vector->vx = *positionsPtr++;
            vector->vy = *positionsPtr++;
            ApplyRotMatrix(vector, rotatedVector);

            prim->x2 = (s16)rotatedVector->vx + xOffset;
            prim->y2 = (s16)rotatedVector->vy + 168;
        } else {
            size = (s16*)SP(0x18);
            prim->x0 = *size++;
            prim->y0 = *size++;
            prim->x2 = *size++;
            prim->y2 = *size++;
        }

        size = (s16*)SP(0x18);
        vector->vx = *positionsPtr++;
        vector->vy = *positionsPtr++;

        ApplyRotMatrix(vector, rotatedVector);
        prim->x1 = *size++ = (s16)rotatedVector->vx + xOffset;
        prim->y1 = *size++ = (s16)rotatedVector->vy + 168;

        vector->vx = *positionsPtr++;
        vector->vy = *positionsPtr++;
        ApplyRotMatrix(vector, rotatedVector);

        prim->x3 = *size++ = (s16)rotatedVector->vx + xOffset;
        prim->y3 = *size++ = (s16)rotatedVector->vy + 168;
        prim = prim->next;
    }

    matrix->m[0][0] = matrix->m[1][1] = matrix->m[2][2] = 0x1000;
    matrix->m[0][1] = matrix->m[0][2] = matrix->m[1][0] = matrix->m[1][2] =
        matrix->m[2][0] = matrix->m[2][1] = 0;

    vector->vx = -328;
    vector->vy = -18;

    ApplyRotMatrix(vector, rotatedVector);

    xOffset = (s16)rotatedVector->vx + xOffset;
    yOffset = (s16)rotatedVector->vy + 168;
    matrix = RotMatrixZ(
        ratan2(-352 - rotatedVector->vy, -(rotatedVector->vx - 128)), matrix);
    SetRotMatrix(matrix);

    positionsPtr = D_80181870;
    while (prim != NULL) {
        vector->vx = *positionsPtr++;
        vector->vy = *positionsPtr++;
        ApplyRotMatrix(vector, rotatedVector);
        prim->x0 = (s16)rotatedVector->vx + xOffset;
        prim->y0 = (s16)rotatedVector->vy + yOffset;

        vector->vx = *positionsPtr++;
        vector->vy = *positionsPtr++;
        ApplyRotMatrix(vector, rotatedVector);
        prim->x1 = (s16)rotatedVector->vx + xOffset;
        prim->y1 = (s16)rotatedVector->vy + yOffset;

        vector->vx = *positionsPtr++;
        vector->vy = *positionsPtr++;
        ApplyRotMatrix(vector, rotatedVector);
        prim->x2 = (s16)rotatedVector->vx + xOffset;
        prim->y2 = (s16)rotatedVector->vy + yOffset;

        vector->vx = *positionsPtr++;
        vector->vy = *positionsPtr++;
        ApplyRotMatrix(vector, rotatedVector);
        prim->x3 = (s16)rotatedVector->vx + xOffset;
        prim->y3 = (s16)rotatedVector->vy + yOffset;

        prim = prim->next;
    }
}

// Mostly just shadows in the far distance.
// Use texture viewer to confirm.
void EntityDistantBackgroundTrees(Entity* self) {
    const s32 X_SPACING = 30;
    Primitive* prim;
    s32 primIndex;
    s16 xPos;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitSpawner);
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 9);
        if (primIndex == 0) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_POS_CAMERA_LOCKED | FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        self->posX.i.hi = 128;
        self->unk68 = 0x10;
        for(prim = &g_PrimBuf[primIndex], xPos = 0; prim != NULL; prim = prim->next) {
            prim->tpage = 0xE;
            prim->clut = 0x67;
            prim->u0 = prim->u2 = 0x61;
            prim->u1 = prim->u3 = 0x7F;
            prim->v0 = prim->v1 = 0xE1;
            prim->v2 = prim->v3 = 0xFF;
            prim->x0 = prim->x2 = xPos;
            xPos += X_SPACING;
            prim->x1 = prim->x3 = xPos;
            prim->y0 = prim->y1 = 0xC0;
            prim->y2 = prim->y3 = 0xE3;
            prim->priority = 0x40;
            prim->drawMode = DRAW_DEFAULT;
        }
        break;

    case 1:
        xPos = 128 - self->posX.i.hi;
        self->posX.i.hi = 0x80;
        for(prim = &g_PrimBuf[self->primIndex]; prim != NULL; prim = prim->next) {
            prim->x0 = prim->x2 -= xPos;
            prim->x1 = prim->x3 = prim->x0 + X_SPACING;
        }
        break;
    }
}

// shows part of the parallax background castle wall
void EntityBackgroundCastleWall(Entity* self) {
    Entity* newEntity;

    newEntity = AllocEntity(&g_Entities[192], &g_Entities[256]);
    if (newEntity != NULL) {
        CreateEntityFromCurrentEntity(E_BACKGROUND_BLOCK, newEntity);
        newEntity->params = 0xC;
        newEntity->unk68 = 0x80;
        newEntity = AllocEntity(newEntity, &g_Entities[256]);
        if (newEntity != NULL) {
            CreateEntityFromCurrentEntity(E_BACKGROUND_BLOCK, newEntity);
            newEntity->posX.i.hi += 0x40;
            newEntity->posY.i.hi = 0x80;
            newEntity->params = 0xB;
            newEntity->unk68 = 0xC0;
        }
    }
    DestroyEntity(self);
}

static u8 D_801819D0[] = {5, 56, 5, 57, 5, 58, 3, 59, 0};
static u8 D_801819DC[] = {6, 56, 6, 57, 6, 58, 4, 59, 0};

// intro owl and leaves
void EntityFlyingOwlAndLeaves(Entity* self) {
    Tilemap* tilemap;
    Entity* newEntity;
    u16 animFlag = true;
    u16 i;

    tilemap = &g_Tilemap;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitCommon);
        self->animSet = ANIMSET_OVL(1);
        self->animCurFrame = 56;
        if (self->params) {
            self->drawFlags =
                FLAG_DRAW_ROTX | FLAG_DRAW_ROTY | FLAG_DRAW_UNK8;
            self->rotX = 0x180;
            self->rotY = 0x180;
            self->unk6C = 0x60;
            self->posY.i.hi = -16;
            self->zPriority = 0xC1;
        } else {
            self->drawFlags = FLAG_DRAW_UNK8;
            self->unk6C = 0x20;
            self->zPriority = 0xBF;
        }
        self->unk68 = 0x1C0;
        break;

    case 1:
        if (self->posX.i.hi < 224) {
            self->ext.ILLEGAL.u16[0] = 0;
            self->step++;
        }
        break;

    case 2:
        if (!(self->ext.ILLEGAL.u16[0]++ & 7)) {
            g_api.PlaySfx(SE_TREE_BRANCH);
        }
        if (self->posX.i.hi < 192) {
            SetStep(3);
            if (self->params) {
                self->velocityX = FIX(8);
                self->velocityY = FIX(3);
                break;
            }
            self->velocityX = FIX(10);
            self->velocityY = FIX(1.625);
            for (i = 0; i < 8; i++) {
                newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (newEntity != NULL) {
                    CreateEntityFromCurrentEntity(E_FALLING_LEAF, newEntity);
                    newEntity->params = i;
                }
            }
        }
        break;

    case 3:
        if (self->params) {
            animFlag = AnimateEntity(D_801819DC, self);
            self->velocityY -= 0xA00;
        } else {
            animFlag = AnimateEntity(D_801819D0, self);
            if (self->velocityY > FIX(-2)) {
                self->velocityY -= FIX(0.03125);
            }
        }
        MoveEntity();
        if (!self->params && (tilemap->scrollX.i.hi > 0xD80)) {
            self->step++;
        }
        if (self->posX.i.hi > 288 || self->posY.i.hi < -16) {
            DestroyEntity(self);
        }
        break;

    case 4:
        if (self->velocityY > FIX(-2)) {
            self->velocityY -= FIX(0.03125);
        }
        animFlag = AnimateEntity(D_801819D0, self);
        MoveEntity();
        if (self->unk6C < 0x78) {
            self->unk6C += 2;
        }
        if (self->posX.i.hi > 288 || self->posY.i.hi < -16) {
            DestroyEntity(self);
        }
    }

    if (!animFlag) {
        PlaySfxPositional(SFX_WING_FLAP_A);
    }
}

// a single leaf from when the owl comes out in the intro
void EntityFallingLeaf(Entity* self) {
    volatile int pad;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitCommon);
        self->animSet = ANIMSET_OVL(1);
        self->animCurFrame = (self->params & 1) + 63;
        self->zPriority = 0xC1;
        self->velocityX = D_801819E8[self->params * 2];
        self->velocityY = D_801819EC[self->params * 2];
        self->unk68 = 0x1C0;
        break;

    case 1:
        if (self->velocityX > 0) {
            self->velocityX -= FIX(0.0625);
        }
        if (self->velocityY < FIX(1.0)) {
            self->velocityY += 0x400;
        }
        if (self->velocityY > FIX(1.0)) {
            self->velocityY -= 0x400;
        }
        MoveEntity();
        break;
    }
}
