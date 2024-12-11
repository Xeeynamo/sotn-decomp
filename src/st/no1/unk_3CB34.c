// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no1.h"

// Mask for all of the statuses where the UP button will
// be ignored when in elevator position or on the elevator platform
//
// Value: 0xC5CFFEDF
// clang-format off
#define PLAYER_STATUS_ELEVATOR_MASK                                              \
    (                                                                            \
        /* 0xC0000000 */ PLAYER_STATUS_UNK80000000 | PLAYER_STATUS_UNK40000000 | \
        /* 0x05000000 */ PLAYER_STATUS_UNK4000000 | PLAYER_STATUS_AXEARMOR |     \
        /* 0x00C00000 */ PLAYER_STATUS_UNK800000 | PLAYER_STATUS_UNK400000 |     \
        /* 0x000F0000 */ PLAYER_STATUS_UNK80000 | PLAYER_STATUS_DEAD | PLAYER_STATUS_UNK20000 | PLAYER_STATUS_UNK10000 | \
        /* 0x0000F000 */ PLAYER_STATUS_CURSE | PLAYER_STATUS_POISON | PLAYER_STATUS_UNK2000 | PLAYER_STATUS_UNK1000 | \
        /* 0x00000E00 */ PLAYER_STATUS_UNK800 | PLAYER_STATUS_UNK400 | PLAYER_STATUS_UNK200 | \
        /* 0x000000D0 */ PLAYER_STATUS_STONE | PLAYER_STATUS_UNK40 |  PLAYER_STATUS_UNK10 | \
        /* 0x0000000F */ PLAYER_STATUS_UNK8 | PLAYER_STATUS_WOLF_FORM | PLAYER_STATUS_MIST_FORM | PLAYER_STATUS_BAT_FORM \
    )
// clang-format on

extern u16 D_us_801809F8[];
extern u8 D_us_80181550[];
extern u8 D_us_8018155C[];
extern s16 D_us_80181568[];
extern s32 D_psp_0929A720;

void func_us_801BCB34(Entity* self) {
    Collider collider;
    Primitive* prim;
    s16 posX, posY;
    s32 primIndex;
    char dPad;
    Entity* player;
    Entity* tempEntity;
    s32 i;

    s16 unusedA = g_Tilemap.scrollX.i.hi + self->posX.i.hi;
    s16 unusedB = g_Tilemap.scrollY.i.hi + self->posY.i.hi;

    player = &PLAYER;

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_801809F8);
        self->ext.et_801BCB34.unk84 = self->params;
        self->ext.et_801BCB34.unk85 = self->ext.et_801BCB34.unk84;
        self->ext.et_801BCB34.unk86 = 0;
        self->ext.et_801BCB34.unk87 = 0;
        self->zPriority = g_unkGraphicsStruct.g_zEntityCenter + 0x10;
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 0x28);
        if (primIndex != -1) {
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            self->ext.et_801BCB34.unk90 = prim;
            UnkPolyFunc2(prim);
            prim->next->u2 = 0;
            prim = prim->next;
            prim = prim->next;
            self->ext.et_801BCB34.unk7C = prim;
        } else {
            self->ext.et_801BCB34.unk90 = NULL;
            self->ext.et_801BCB34.unk7C = NULL;
        }
        tempEntity = self + 1;
#ifdef VERSION_PSP
        CreateEntityFromEntity(D_psp_0929A720, self, tempEntity);
#else
        CreateEntityFromEntity(E_ID_2A, self, tempEntity);
#endif
        tempEntity->posY.i.hi -= 0x22;
        tempEntity->ext.et_801BCB34.unk8C = 0;
        break;
    case 1:
        self->step++;
        break;
    case 2:
        self->velocityY = 0;
        if ((GetDistanceToPlayerX() < 6) && (GetDistanceToPlayerY() < 0x10)) {
            i = g_Player.status;
            if (i & PLAYER_STATUS_ELEVATOR_MASK) {
                break;
            }
            dPad = 0;
            if (g_pads[0].pressed & PAD_UP) {
                dPad = 1;
            }
            if (g_pads[0].pressed & PAD_DOWN) {
                dPad = -1;
            }
            if (dPad) {
                dPad += self->ext.et_801BCB34.unk84;
                if ((dPad == (char)(-1)) || (dPad > 2)) {
                    break;
                }
#ifndef VERSION_PSP
                g_Player.D_80072EFC = 2;
                g_Player.padSim = 0;
                PLAYER.velocityX = 0;
                PLAYER.velocityY = 0;
#endif
                g_api.func_8010DFF0(0, 1);
                g_api.func_8010E168(1, 0x20);
                self->ext.et_801BCB34.unk85 = dPad;
                self->animFrameIdx = 0;
                self->animFrameDuration = 0;
                self->step_s = 0;
                self->step++;
#ifdef VERSION_PSP
                PLAYER.posX.val = self->posX.val;
                PLAYER.posY.val = 0;
#endif
            }
        }
        if (self->ext.et_801BCB34.unk94) {
            self->animFrameIdx = 0;
            self->animFrameDuration = 0;
            self->step_s = 1;
            self->step = 3;
        }
        break;
    case 3:
        if (!self->ext.et_801BCB34.unk94) {
            g_api.func_8010DFF0(0, 1);
            g_api.func_8010E168(1, 0x20);
            g_Player.padSim = 0;
            g_Player.D_80072EFC = 0x40;
        }
        if (AnimateEntity(D_us_80181550, self) == 0) {
            PlaySfxPositional(0x7B5);
            if (!self->ext.et_801BCB34.unk94) {
                g_unkGraphicsStruct.unk1C |= 1;
            }
            self->ext.et_801BCB34.unk88 = 0x18;
            self->step_s = 0;
            self->animFrameIdx = 0;
            self->animFrameDuration = 0;
            if (self->ext.et_801BCB34.unk85 > self->ext.et_801BCB34.unk84) {
                self->step = 4;
            } else {
                self->step = 5;
                if (!self->ext.et_801BCB34.unk94) {
                    g_api.PlaySfx(SFX_VO_ALU_YELL);
                }
            }
        }
        break;
    case 4:
        if (!self->ext.et_801BCB34.unk94) {
            if (!self->ext.et_801BCB34.unk88) {
                MoveEntity();
                player->posY.i.hi = self->posY.i.hi - 4;
            } else {
                player->posY.i.hi = self->posY.i.hi - 4;
                MoveEntity();
                self->ext.et_801BCB34.unk88 -= 1;
            }
            g_api.func_8010DFF0(0, 1);
            g_api.func_8010E168(1, 0x20);
            g_Player.padSim = 0x4000;
            g_Player.D_80072EFC = 2;
            g_Player.pl_vram_flag |= 0x41;
        } else {
            MoveEntity();
        }
        posY = g_Tilemap.scrollY.i.hi + self->posY.i.hi;
        switch (self->step_s) {
        case 0:
            self->velocityY -= FIX(0.125);
            if (self->ext.et_801BCB34.unk7C != NULL) {
                if (Random() % 10 == 0) {
                    prim = self->ext.et_801BCB34.unk7C;
                    prim = FindFirstUnkPrim2(prim, 2);
                    if (prim != NULL) {
                        UnkPolyFunc2(prim);
                        prim->next->x1 = self->posX.i.hi + 0x10;
                        prim->next->y0 = self->posY.i.hi + 0x2C;
                        prim->next->r3 = self->ext.et_801BCB34.unk86;
                    }
                    self->ext.et_801BCB34.unk86 ^= 1;
                }
            }
            if (posY < D_us_80181568[self->ext.et_801BCB34.unk85]) {
                if (self->ext.et_801BCB34.unk85 == 2) {
                    g_api.PlaySfx(0x7B3);
                    posX = self->posX.i.hi;
                    posY = self->posY.i.hi - 0x18;
                    g_api.CheckCollision(posX, posY, &collider, 0);
                    self->posY.i.hi += collider.unk20;
                    self->velocityY = -self->velocityY;
                    self->step_s = 2;
                    for (i = 0; i < 3; i++) {
                        tempEntity =
                            AllocEntity(&g_Entities[224], &g_Entities[256]);
                        if (tempEntity != NULL) {
                            CreateEntityFromEntity(E_INTENSE_EXPLOSION, self, tempEntity);
                            tempEntity->posX.i.hi += (i * 8) - 8;
                            tempEntity->posY.i.hi -= 0x18;
                            tempEntity->drawFlags |= FLAG_DRAW_ROTZ;
                            tempEntity->rotZ = 0x400 - (i << 0xA);
                            tempEntity->params = 0x10;
                        }
                    }
                } else {
                    g_api.PlaySfx(SFX_LEVER_METAL_BANG);
                    self->ext.et_801BCB34.unk87 = 1;
                    self->velocityY /= 2;
                    self->step_s++;
                }
            }
            break;

        case 1:
            self->velocityY += FIX(1.0);
            if (posY > D_us_80181568[self->ext.et_801BCB34.unk85] + 8) {
                self->velocityY = 0;
                self->step_s = 3;
            }
            break;

        case 2:
            self->velocityY -= FIX(2.0);
            if (self->velocityY < 0) {
                self->velocityY = 0;
                self->step_s = 3;
            }
            break;

        case 3:
            self->ext.et_801BCB34.unk87 = 0;
            if (posY == D_us_80181568[self->ext.et_801BCB34.unk85]) {
                self->step_s = 0;
                self->step = 6;
            } else {
                if (posY > D_us_80181568[self->ext.et_801BCB34.unk85]) {
                    F(self->velocityY).i.hi = -1;
                } else {
                    F(self->velocityY).i.hi = 1;
                }
            }
            break;
        }
        break;

    case 5:
        if (!self->ext.et_801BCB34.unk94) {
            if (!self->ext.et_801BCB34.unk88) {
                MoveEntity();
                player->posY.i.hi = self->posY.i.hi - 4;
            } else {
                player->posY.i.hi = self->posY.i.hi - 4;
                MoveEntity();
                self->ext.et_801BCB34.unk88 -= 1;
            }
            g_api.func_8010DFF0(0, 1);
            g_api.func_8010E168(1, 0x20);
            g_Player.padSim = 0x4000;
            g_Player.D_80072EFC = 2;
        } else {
            MoveEntity();
        }
        posY = g_Tilemap.scrollY.i.hi + self->posY.i.hi;
        switch (self->step_s) {
        case 0:
            self->velocityY += FIX(0.25);
            if (self->ext.et_801BCB34.unk7C != NULL) {
                if (Random() % 10 == 0) {
                    prim = self->ext.et_801BCB34.unk7C;
                    prim = FindFirstUnkPrim2(prim, 2);
                    if (prim != NULL) {
                        UnkPolyFunc2(prim);
                        prim->next->x1 = self->posX.i.hi + 0x10;
                        prim->next->y0 = self->posY.i.hi + 0x2C;
                        prim->next->r3 = self->ext.et_801BCB34.unk86;
                        prim->next->r3 |= 0x10;
                    }
                    self->ext.et_801BCB34.unk86 ^= 1;
                }
            }
            if (posY > D_us_80181568[self->ext.et_801BCB34.unk85]) {
                self->ext.et_801BCB34.unk87 = 1;
                if (!self->ext.et_801BCB34.unk85) {
                    g_api.PlaySfx(0x7B3);
                    self->velocityY = -self->velocityY / 2;
                    posX = self->posX.i.hi;
                    posY = self->posY.i.hi + 0x24;
                    g_api.CheckCollision(posX, posY, &collider, 0);
                    self->posY.i.hi += collider.unk18;
                    self->step_s = 2;
                    for (i = 0; i < 3; i++) {
                        tempEntity =
                            AllocEntity(&g_Entities[224], &g_Entities[256]);
                        if (tempEntity != NULL) {
                            CreateEntityFromEntity(E_INTENSE_EXPLOSION, self, tempEntity);
                            tempEntity->posX.i.hi += (i * 8) - 8;
                            tempEntity->posY.i.hi += 0x24;
                            tempEntity->drawFlags |= FLAG_DRAW_ROTZ;
                            tempEntity->rotZ = 0x400 - (i << 0xA);
                            tempEntity->params = 0x10;
                        }
                    }
                } else {
                    g_api.PlaySfx(SFX_LEVER_METAL_BANG);
                    self->velocityY /= 2;
                    self->step_s = 1;
                }
            }
            break;

        case 1:
            self->velocityY -= FIX(1.5);
            if (posY < D_us_80181568[self->ext.et_801BCB34.unk85]) {
                self->velocityY = 0;
                self->step_s = 3;
            }
            break;

        case 2:
            self->velocityY += FIX(1.0);
            if (self->velocityY > 0) {
                self->velocityY -= FIX(0.75);
                if (posY > D_us_80181568[self->ext.et_801BCB34.unk85]) {
                    posX = self->posX.i.hi;
                    posY = self->posY.i.hi + 0x24;
                    g_api.CheckCollision(posX, posY, &collider, 0);
                    self->posY.i.hi += collider.unk18;
                    self->velocityY = 0;
                    self->step_s = 3;
                    for (i = 0; i < 3; i++) {
                        tempEntity =
                            AllocEntity(&g_Entities[224], &g_Entities[256]);
                        if (tempEntity != NULL) {
                            CreateEntityFromEntity(E_INTENSE_EXPLOSION, self, tempEntity);
                            tempEntity->posX.i.hi += (i * 8) - 8;
                            tempEntity->posY.i.hi += 0x24;
                            tempEntity->drawFlags |= FLAG_DRAW_ROTZ;
                            tempEntity->rotZ = 0x400 - (i << 0xA);
                            tempEntity->params = 0x10;
                        }
                    }
                }
            }
            break;

        case 3:
            self->ext.et_801BCB34.unk87 = 0;
            if (posY == D_us_80181568[self->ext.et_801BCB34.unk85]) {
                self->step_s = 0;
                self->step = 6;
            } else {
                if (posY > D_us_80181568[self->ext.et_801BCB34.unk85]) {
                    F(self->velocityY).i.hi = -1;
                } else {
                    F(self->velocityY).i.hi = 1;
                }
            }
            break;
        }
        break;
    case 6:
        switch (self->step_s) {
        case 0:
            if (!self->ext.et_801BCB34.unk94) {
                player->posY.i.hi = self->posY.i.hi - 8;
            }
            g_unkGraphicsStruct.unk1C &= ~1;
            self->velocityY = 0;
            self->step_s++;
            break;

        case 1:
            if (!self->ext.et_801BCB34.unk94) {
                g_api.func_8010DFF0(0, 1);
                g_api.func_8010E168(1, 0x20);
                g_Player.padSim = 0;
                g_Player.D_80072EFC = 2;
            }
            if (AnimateEntity(D_us_8018155C, self) == 0) {
                self->animFrameIdx = 0;
                self->animFrameDuration = 0;
                self->step_s++;
            }
            break;

        case 2:
            self->ext.et_801BCB34.unk84 = self->ext.et_801BCB34.unk85;
            self->ext.et_801BCB34.unk94 = 0;
            self->step_s = 0;
            self->step = 2;
            break;
        }
        break;
    }
    prim = self->ext.et_801BCB34.unk90;
    if (prim != NULL) {
        func_us_801BC9A8(prim);
    }
    prim = self->ext.et_801BCB34.unk7C;
    while (prim != NULL) {
        if (prim->p3 & 8) {
            func_us_801BC598(prim);
        }
        prim = prim->next;
    }
}

INCLUDE_ASM("st/no1/nonmatchings/unk_3CB34", func_us_801BD8AC);

INCLUDE_ASM("st/no1/nonmatchings/unk_3CB34", func_us_801BDA0C);

INCLUDE_ASM("st/no1/nonmatchings/unk_3CB34", func_us_801BDF9C);

INCLUDE_ASM("st/no1/nonmatchings/unk_3CB34", func_us_801BE2C8);

INCLUDE_RODATA("st/no1/nonmatchings/unk_3CB34", D_us_801B4808);

INCLUDE_ASM("st/no1/nonmatchings/unk_3CB34", func_us_801BE880);

INCLUDE_ASM("st/no1/nonmatchings/unk_3CB34", func_us_801BEB54);

INCLUDE_ASM("st/no1/nonmatchings/unk_3CB34", func_us_801BEE00);

INCLUDE_ASM("st/no1/nonmatchings/unk_3CB34", func_us_801BF074);

INCLUDE_ASM("st/no1/nonmatchings/unk_3CB34", func_us_801BF3F4);

INCLUDE_ASM("st/no1/nonmatchings/unk_3CB34", func_us_801BFA34);

INCLUDE_ASM("st/no1/nonmatchings/unk_3CB34", func_us_801BFB40);

INCLUDE_ASM("st/no1/nonmatchings/unk_3CB34", func_us_801C01F0);

INCLUDE_ASM("st/no1/nonmatchings/unk_3CB34", func_us_801C05DC);

INCLUDE_ASM("st/no1/nonmatchings/unk_3CB34", func_us_801C0A40);

INCLUDE_ASM("st/no1/nonmatchings/unk_3CB34", func_us_801C0B9C);

INCLUDE_ASM("st/no1/nonmatchings/unk_3CB34", func_us_801C0E98);

INCLUDE_ASM("st/no1/nonmatchings/unk_3CB34", func_us_801C1090);

INCLUDE_ASM("st/no1/nonmatchings/unk_3CB34", func_us_801C10F4);
