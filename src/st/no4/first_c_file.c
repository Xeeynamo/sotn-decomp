// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no4.h"

INCLUDE_ASM("st/no4/nonmatchings/first_c_file", func_us_801C12B0);

INCLUDE_ASM("st/no4/nonmatchings/first_c_file", func_us_801C15F8);

INCLUDE_ASM("st/no4/nonmatchings/first_c_file", func_us_801C1844);

INCLUDE_ASM("st/no4/nonmatchings/first_c_file", func_us_801C1C94);

INCLUDE_ASM("st/no4/nonmatchings/first_c_file", func_us_801C1EE4);

INCLUDE_ASM("st/no4/nonmatchings/first_c_file", func_us_801C21AC);

INCLUDE_ASM("st/no4/nonmatchings/first_c_file", func_us_801C2474);

INCLUDE_ASM("st/no4/nonmatchings/first_c_file", func_us_801C2850);

INCLUDE_ASM("st/no4/nonmatchings/first_c_file", func_us_801C2B78);

INCLUDE_ASM("st/no4/nonmatchings/first_c_file", func_us_801C2E60);

INCLUDE_ASM("st/no4/nonmatchings/first_c_file", func_us_801C3160);

INCLUDE_ASM("st/no4/nonmatchings/first_c_file", func_us_801C34EC);

INCLUDE_ASM("st/no4/nonmatchings/first_c_file", func_us_801C37C8);

INCLUDE_ASM("st/no4/nonmatchings/first_c_file", func_us_801C3A04);

INCLUDE_ASM("st/no4/nonmatchings/first_c_file", func_us_801C3CC4);

INCLUDE_ASM("st/no4/nonmatchings/first_c_file", func_us_801C3FB0);

INCLUDE_ASM("st/no4/nonmatchings/first_c_file", func_us_801C4228);

INCLUDE_ASM("st/no4/nonmatchings/first_c_file", func_us_801C4520);

extern s16 D_us_801811D6;  // water surface sprite height
extern s16 D_us_801812B8;  // water background sprite height
extern u8 D_us_80181588[]; // Water flow animation that needs to be blocked by
                           // the crate

// Does something with the water level that kills the 4 spear guards in the
// alcove
void func_us_801C4738(Entity* self) {
    Entity* newEnt;

    if (self->step == 0) {
        InitializeEntity(g_EInitInteractable);
        self->animSet = ANIMSET_OVL(1);
        self->palette = 68;
        self->drawFlags = FLAG_DRAW_UNK10;
        self->posX.i.hi = 0x711 - g_Tilemap.scrollX.i.hi;
        if (g_CastleFlags[NO4_WATER_BLOCKED] != 0) {
            self->ext.et_waterAlcove.waterHeight = 64;
        } else {
            newEnt = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (newEnt != NULL) {
                CreateEntityFromCurrentEntity(E_ID_27, newEnt);
                newEnt->params = 1;
            }
            self->ext.et_waterAlcove.entity7E = newEnt;

            newEnt = AllocEntity(newEnt, &g_Entities[256]);
            if (newEnt != NULL) {
                CreateEntityFromCurrentEntity(E_ID_26, newEnt);
                newEnt->params = 1;
            }
            self->ext.et_waterAlcove.entity82 = newEnt;
            self->ext.et_waterAlcove.waterHeight = 0;
        }
    }

    // Animates the small flow of water that needs to be blocked by the crate
    AnimateEntity(D_us_80181588, self);

    if (g_CastleFlags[NO4_WATER_BLOCKED] != 0) {
        if (self->ext.et_waterAlcove.waterHeight < 64) {
            if (!(self->ext.et_waterAlcove.unk90 & 0x7)) {
                if (self->ext.et_waterAlcove.waterHeight == 0) {
                    g_api_PlaySfx(SFX_WATER_BUBBLE);
                }
                self->ext.et_waterAlcove.waterHeight++;
                if (self->ext.et_waterAlcove.waterHeight == 20) {
                    g_CastleFlags[NO4_WATER_BLOCKED]++;
                }
                if (self->ext.et_waterAlcove.waterHeight == 52) {
                    g_CastleFlags[NO4_WATER_BLOCKED]++;
                }
            }
            self->ext.et_waterAlcove.unk90++;
        }

        if (self->ext.et_waterAlcove.entity7E != 0) {
            DestroyEntity(self->ext.et_waterAlcove.entity7E);
            self->ext.et_waterAlcove.entity7E = NULL;
        }

        if (self->ext.et_waterAlcove.entity82 != 0) {
            DestroyEntity(self->ext.et_waterAlcove.entity82);
            self->ext.et_waterAlcove.entity82 = NULL;
        }
        self->animCurFrame = 0;
    }

    D_us_801812B8 = 177 - self->ext.et_waterAlcove.waterHeight;
    D_us_801811D6 = 176 - self->ext.et_waterAlcove.waterHeight;

    if (self->ext.et_waterAlcove.waterHeight >= 64) {
        DestroyEntity(self);
    }
}

INCLUDE_ASM("st/no4/nonmatchings/first_c_file", func_us_801C4980);

void func_us_801C4BD8(Entity* self) {
    Tilemap* tmap;
    s16* dataPtr;
    s32 volume;

    if (self->step == 0) {
        InitializeEntity(g_EInitInteractable);
        self->animSet = 0;
    }

    tmap = &g_Tilemap;
    dataPtr = &D_us_8018159C[self->params * 4];

    volume = PLAYER.posX.i.hi + tmap->scrollX.i.hi - *dataPtr++;
    volume = (volume * *dataPtr++) / 4096;
    volume += *dataPtr++;

    if (volume < 0) {
        volume = 0;
    } else if (volume >= 128) {
        volume = 127;
    }

    if (volume == 0) {
        if (D_us_80181108 != 0) {
            D_us_80181108 = 0;
            g_api.PlaySfx(SET_UNK_A6);
            return;
        }
    }
    if (D_us_80181108 != 0) {
        g_api.SetVolumeCommand22_23(volume, *dataPtr++);
        return;
    }

    g_api.PlaySfxVolPan(SFX_UNK_797, volume, *dataPtr++);
    D_us_80181108 = 1;
}

INCLUDE_ASM("st/no4/nonmatchings/first_c_file", func_us_801C4D2C);

INCLUDE_ASM("st/no4/nonmatchings/first_c_file", func_us_801C5020);

void func_us_801C50FC(void) {
    u16* tile;
    s16 i;

    tile = &g_Tilemap.fg[691];

    for (i = 0; i < 10; i++, tile++) {
        *tile = 0;
    }
}

INCLUDE_ASM("st/no4/nonmatchings/first_c_file", func_us_801C5134);

INCLUDE_ASM("st/no4/nonmatchings/first_c_file", func_us_801C5268);

extern s16 D_us_801815DC[]; // animCurFrame
extern u16 D_us_801815EC[]; // facingLeft
extern s16 D_us_801815FC[]; // rotZ
extern s32 D_us_8018160C[]; // velocityY

void func_us_801C542C(Entity* self) {
    u16 params = self->params;
    if (self->step == 0) {
        InitializeEntity(g_EInitCommon);
        self->animSet = ANIMSET_OVL(1);
        self->animCurFrame = D_us_801815DC[params];
        self->facingLeft = D_us_801815EC[params];
        self->velocityY = D_us_8018160C[params];
        self->drawFlags = FLAG_DRAW_ROTZ;
        self->rotZ = false;
    }
    if (F(self->velocityY).i.hi < 8) {
        F(self->velocityY).val += FIX(0.25);
    }
    MoveEntity();
    self->rotZ += D_us_801815FC[params];
}

extern s16 D_us_8018162C[];

void func_us_801C5518(Entity* self) {
    Tilemap* tmap;
    u16 diff;
    s16* dataPtr;

    if (self->step == 0) {
        InitializeEntity(g_EInitInteractable);
        self->animSet = 0;
    }

    tmap = &g_Tilemap;
    dataPtr = &D_us_8018162C[self->params << 2];
    diff = PLAYER.posX.i.hi + tmap->scrollX.i.hi - *dataPtr++;

    if (*dataPtr++ >= diff) {
        diff = PLAYER.posY.i.hi + tmap->scrollY.i.hi - *dataPtr++;
        if (*dataPtr >= diff) {
            if (PLAYER.velocityY < 0) {
                PLAYER.velocityY *= 7;
                PLAYER.velocityY /= 8;
            } else if (PLAYER.velocityY > 0) {
                PLAYER.nFramesInvincibility = 1;
            }
        }
    }
}

extern Primitive D_us_80181644;

// Function that runs when the player is in the switch room to activate the
// skeleton ape that can destroy the bridge in underground caverns.
// Location (X: 21, Y: 33)
// https://guides.gamercorner.net/sotn/areas/underground-caverns

void func_us_801C5628(Entity* self) {
    Entity* newEnt;

    if (self->step == 0) {
        InitializeEntity(g_EInitInteractable);
        self->animSet = ANIMSET_OVL(1);
        self->animCurFrame = 40;
        if (g_CastleFlags[NO4_SKELETON_APE_AND_BRIDGE] == 0) {
            self->posX.i.hi = 52;
        } else {
            self->posX.i.hi = 44;
        }
    }

    // Idk why it wants to store the entity before but it works so ¯\_(ツ)_/¯
    newEnt = g_Entities;

    if ((((GetPlayerCollisionWith(self, 0x8, 16, 5) & 0x1) &&
          (g_Player.vram_flag & 0x1)) &&
         (g_pads->pressed & PAD_LEFT)) &&
        (PLAYER.step == 1)) {
        if (self->ext.timer.t != 0) { // ext.xxx.unk7C
            self->ext.timer.t--;
        } else {
            if (self->posX.i.hi >= 45) {
                self->posX.i.hi--;
                PLAYER.posX.i.hi--;
                if (self->posX.i.hi == 44) {
                    g_CastleFlags[NO4_SKELETON_APE_AND_BRIDGE] = 1;
                    PlaySfxPositional(SFX_SWITCH_CLICK);
                    self->step++;
                }
            }
            self->ext.timer.t = 2;
        }
    }

    if ((self->step == 2) && (newEnt->posX.i.hi >= 129)) {
        g_api.PlaySfxVolPan(SFX_WALL_DEBRIS_A, 127, 8);
        newEnt = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (newEnt != NULL) {
            CreateEntityFromCurrentEntity(E_MESSAGE_BOX, newEnt);
            newEnt->posX.i.hi = 128;
            newEnt->posY.i.hi = 176;
            newEnt->ext.prim = &D_us_80181644;
            newEnt->params = 0x100;
        }
        self->step++;
    }
}

INCLUDE_ASM("st/no4/nonmatchings/first_c_file", func_us_801C582C);

INCLUDE_ASM("st/no4/nonmatchings/first_c_file", func_us_801C5868);

void func_us_801C58A0(Entity* self) {
    Entity* newEnt;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitCommon);
        if (g_CastleFlags[NO4_SKELETON_APE_AND_BRIDGE] != 0) {
            func_us_801C5868();
            DestroyEntity(self);
        }
        break;
    case 1:
        if (g_CastleFlags[NO4_SKELETON_APE_AND_BRIDGE] != 0) {
            newEnt = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (newEnt != NULL) {
                CreateEntityFromCurrentEntity(E_SKELETON_APE, newEnt);
                newEnt->params = 2;
                newEnt->posY.i.hi = newEnt->posY.i.hi - 96;
                newEnt->posX.i.hi = newEnt->posX.i.hi + 96;
                self->ext.prim = (Primitive*)(newEnt + 2); // I dont like this
            }
            self->step += 1;
        }
        break;
    case 2:
        if (self->ext.prim->x3 == 4U) {
            func_us_801C5868();
            func_us_801C5134();
            DestroyEntity(self);
        }
        break;
    }
}

INCLUDE_ASM("st/no4/nonmatchings/first_c_file", func_us_801C59E0);

INCLUDE_ASM("st/no4/nonmatchings/first_c_file", func_us_801C5AD4);

INCLUDE_ASM("st/no4/nonmatchings/first_c_file", func_us_801C5C7C);

void func_us_801C6CEC(Entity* self) {

    Entity* prev = self - 1;

    if (self->step == 0) {
        InitializeEntity(g_EInitInteractable);
        self->animSet = ANIMSET_OVL(1);
        self->animCurFrame = 0x1C;
        self->drawFlags = FLAG_DRAW_ROTZ;
        self->zPriority = 0x9A;
        self->flags |= FLAG_POS_CAMERA_LOCKED;
    }
    self->posX.i.hi = prev->posX.i.hi;
    self->rotZ = prev->rotZ;
    if (self->facingLeft != 0) {
        self->posX.i.hi += 4;
    } else {
        self->posX.i.hi -= 4;
    }
    self->posY.i.hi = prev->posY.i.hi;
}

INCLUDE_ASM("st/no4/nonmatchings/first_c_file", func_us_801C6DA8);

INCLUDE_ASM("st/no4/nonmatchings/first_c_file", func_us_801C7204);

INCLUDE_ASM("st/no4/nonmatchings/first_c_file", func_us_801C726C);

INCLUDE_ASM("st/no4/nonmatchings/first_c_file", func_us_801C789C);

void func_us_801C7FA4(void) {}

extern u16 D_us_801817E8;

void func_us_801C7FAC(void) {
    s32 i;
    Tilemap* tileMap = &g_Tilemap;
    s16 offset = 0x595;
    u16* var_a2 = &D_us_801817E8;

    for (i = 0; i < 7; i++) {
        *(tileMap->fg + offset) = *var_a2++;
        offset++;
        *(tileMap->fg + offset) = *var_a2++;
        offset = offset + 0xCF;
    }
}

void func_us_801C801C(Entity* self) {
    Entity* newEnt;
    s16 offsetY;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitCommon);
        self->animSet = ANIMSET_OVL(1);
        if (g_CastleFlags[BOATMAN_GATE_OPEN] != 0) {
            func_us_801C7FAC();
            DestroyEntity(self);
            return;
        }
        self->animCurFrame = 24;
        return;
    case 1:
        if (g_CastleFlags[BOATMAN_GATE_OPEN] != 0) {
            GetPlayerCollisionWith(self, 16, 56, 3);
            func_us_801C7FAC();
            self->ext.et_801C801C.unk80 = 0;
            self->step++;
            return;
        }
        break;
    case 2:
        if (!(self->ext.et_801C801C.unk80++ & 0xF)) {
            PlaySfxPositional(SFX_STONE_MOVE_C);
        }

        self->posY.i.hi--;
        offsetY = self->posY.i.hi + g_Tilemap.scrollY.i.hi;

        if (offsetY >= 125) {
            if (self->ext.et_801C801C.unk7C != 0) {
                self->ext.et_801C801C.unk7C--;
            } else {
                newEnt = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (newEnt != NULL) {
                    CreateEntityFromCurrentEntity(E_SURFACING_WATER, newEnt);
                    newEnt->posY.i.hi = 176 - g_Tilemap.scrollY.i.hi;
                    newEnt->posX.i.hi = (s16)(newEnt->posX.i.hi - 16) +
                                        (self->ext.et_801C801C.unk7E * 8);
                    newEnt->params = 0x8000;
                    newEnt->ext.et_801C801C.unk88 = 23;
                    newEnt->zPriority = 155;
                }

                self->ext.et_801C801C.unk7E++;
                if (self->ext.et_801C801C.unk7E >= 5) {
                    self->ext.et_801C801C.unk7E = 0;
                }
                self->ext.et_801C801C.unk7C = 1;
            }
        }

        GetPlayerCollisionWith(self, 16, 60, 3);

        if (offsetY < 36) {
            DestroyEntity(self);
        }
    }
}

INCLUDE_ASM("st/no4/nonmatchings/first_c_file", func_us_801C8248);

INCLUDE_ASM("st/no4/nonmatchings/first_c_file", func_us_801C82B8);
