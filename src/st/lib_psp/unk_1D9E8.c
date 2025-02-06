// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../../st/lib/lib.h"

INCLUDE_ASM("st/lib_psp/psp/lib_psp/unk_1D9E8", func_psp_09255068);

INCLUDE_ASM("st/lib_psp/psp/lib_psp/unk_1D9E8", func_us_801BB8DC);

INCLUDE_ASM("st/lib_psp/psp/lib_psp/unk_1D9E8", func_psp_09256018);

INCLUDE_ASM("st/lib_psp/psp/lib_psp/unk_1D9E8", func_psp_092564B8);

INCLUDE_ASM("st/lib_psp/psp/lib_psp/unk_1D9E8", func_psp_09256AC0);

INCLUDE_ASM("st/lib_psp/psp/lib_psp/unk_1D9E8", func_psp_09256E08);

INCLUDE_ASM("st/lib_psp/psp/lib_psp/unk_1D9E8", func_psp_09257100);

INCLUDE_ASM("st/lib_psp/psp/lib_psp/unk_1D9E8", func_psp_092576C8);

INCLUDE_ASM("st/lib_psp/psp/lib_psp/unk_1D9E8", func_psp_09257BF8);

INCLUDE_ASM("st/lib_psp/psp/lib_psp/unk_1D9E8", func_psp_09258100);

INCLUDE_ASM("st/lib_psp/psp/lib_psp/unk_1D9E8", func_psp_09258A38);

// Lesser Demon
INCLUDE_ASM("st/lib_psp/psp/lib_psp/unk_1D9E8", func_psp_09258B50);

INCLUDE_ASM("st/lib_psp/psp/lib_psp/unk_1D9E8", func_psp_0925A798);

INCLUDE_ASM("st/lib_psp/psp/lib_psp/unk_1D9E8", func_psp_0925A830);

INCLUDE_ASM("st/lib_psp/psp/lib_psp/unk_1D9E8", func_psp_0925A8D0);

INCLUDE_ASM("st/lib_psp/psp/lib_psp/unk_1D9E8", func_psp_0925ABE8);

INCLUDE_ASM("st/lib_psp/psp/lib_psp/unk_1D9E8", func_psp_0925AC70);

INCLUDE_ASM("st/lib_psp/psp/lib_psp/unk_1D9E8", func_psp_0925AD40);

INCLUDE_ASM("st/lib_psp/psp/lib_psp/unk_1D9E8", func_psp_0925ADA0);

INCLUDE_ASM("st/lib_psp/psp/lib_psp/unk_1D9E8", func_psp_0925AFB0);

INCLUDE_ASM("st/lib_psp/psp/lib_psp/unk_1D9E8", func_psp_0925AFE8);

INCLUDE_ASM("st/lib_psp/psp/lib_psp/unk_1D9E8", func_psp_0925B380);

INCLUDE_ASM("st/lib_psp/psp/lib_psp/unk_1D9E8", func_psp_0925B470);

INCLUDE_ASM("st/lib_psp/psp/lib_psp/unk_1D9E8", func_psp_0925D350);

INCLUDE_ASM("st/lib_psp/psp/lib_psp/unk_1D9E8", func_psp_0925D430);

INCLUDE_ASM("st/lib_psp/psp/lib_psp/unk_1D9E8", func_psp_0925D4D0);

INCLUDE_ASM("st/lib_psp/psp/lib_psp/unk_1D9E8", func_psp_0925D8D8);

extern s32 g_CutsceneFlags;

extern s32 D_us_801D51D4;
extern s32 D_us_801D5288;

extern u8 D_us_801811FC[];
extern u8 D_us_80181204[];
extern u8 D_us_80181210[];
extern u8 D_us_8018121C[];
extern u8 D_us_80181234[];
extern u8 D_us_80181244[];
extern u8 D_us_801812C0[];
extern u8 D_us_801812C8[];
extern u8 D_us_801812D0[];
extern u8* D_us_801812D8[];

void EntityLibrarianChair(Entity* self) {
    Entity* newEnt;
    Entity* player = &PLAYER;
    Tilemap* tilemap = &g_Tilemap;

    if (self->step && (self->step < 11) && (D_us_801D51D4 != 0) &&
        (D_us_801D5288 != 0)) {
        self->step = 11;
        self->animCurFrame = 2;
    }
    if (player->posX.i.hi < 0x38) {
        self->zPriority = 0xC0;
        if (g_Player.status & PLAYER_STATUS_TRANSFORM) {
            GetPlayerCollisionWith(self, 16, 12, 2);
            // If the chair is not in step 16, and the player is high enough,
            // and moving upward, trigger a hit.
        } else if (self->step < 16 &&
                   ((player->posY.i.hi + tilemap->scrollY.i.hi) < 201) &&
                   ((*((f32*)&player->velocityY)).i.hi < 0)) {
            SetStep(16);
            if (PLAYER.step == Player_HighJump) {
                g_Player.unk4A = 0x1C;
                if (PLAYER.step_s == 0) {
                    PLAYER.step_s = 1;
                    PLAYER.velocityY = FIX(-8);
                }
            }
            // Play chair jumping sound
            g_api.PlaySfx(SFX_QUICK_STUTTER_EXPLODE_B);
            self->ext.libraryChair.totalHits++;
            self->ext.libraryChair.consecutiveHits++;

            // At first hit, give Life Max Up.
            if (!(g_CastleFlags[LIBRARIAN_DROPS] & 1)) {
                newEnt = AllocEntity(&g_Entities[160], &g_Entities[192]);
                if (newEnt != NULL) {
                    CreateEntityFromCurrentEntity(E_PRIZE_DROP, newEnt);
                    newEnt->params = 23;
                    g_CastleFlags[LIBRARIAN_DROPS] |= 1;
                }
            }
            // Getting Axe Lord Armor requires hitting librarian 64 times.
            if (!(g_CastleFlags[LIBRARIAN_DROPS] & 2) &&
                (self->ext.libraryChair.totalHits >= 64)) {
                newEnt = AllocEntity(&g_Entities[160], &g_Entities[192]);
                if (newEnt != NULL) {
                    CreateEntityFromCurrentEntity(E_EQUIP_ITEM_DROP, newEnt);
                    newEnt->params = NUM_HAND_ITEMS + ITEM_AXE_LORD_ARMOR;
                    g_CastleFlags[LIBRARIAN_DROPS] |= 2;
                }
            }
            // Ring of Arcana requires 16 hits, without touching ground
            if (!(g_CastleFlags[LIBRARIAN_DROPS] & 4) &&
                (self->ext.libraryChair.consecutiveHits >= 16)) {
                newEnt = AllocEntity(&g_Entities[160], &g_Entities[192]);
                if (newEnt != NULL) {
                    CreateEntityFromCurrentEntity(E_EQUIP_ITEM_DROP, newEnt);
                    newEnt->params = NUM_HAND_ITEMS + ITEM_RING_OF_ARCANA;
                    g_CastleFlags[LIBRARIAN_DROPS] |= 4;
                }
            }
            // Dracula Tunic requires 24 hits, and inverted castle must be
            // unlocked.
            if (!(g_CastleFlags[LIBRARIAN_DROPS] & 8) &&
                (self->ext.libraryChair.consecutiveHits >= 24) &&
                (g_CastleFlags[INVERTED_CASTLE_UNLOCKED])) {
                newEnt = AllocEntity(&g_Entities[160], &g_Entities[192]);
                if (newEnt != NULL) {
                    CreateEntityFromCurrentEntity(E_EQUIP_ITEM_DROP, newEnt);
                    newEnt->params = NUM_HAND_ITEMS + ITEM_DRACULA_TUNIC;
                    g_CastleFlags[LIBRARIAN_DROPS] |= 8;
                }
            }
        }
    } else {
        self->zPriority = 0x80;
    }
    // If the player touches the ground, reset the frames airborne.
    if (g_Player.pl_vram_flag & 1) {
        self->ext.libraryChair.consecutiveHits = 0;
    }
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitCommon);
        self->zPriority = 0x80;
        self->animSet = ANIMSET_OVL(11);
        self->animCurFrame = 2;
        self->palette = 0x210;
        self->unk5A = 0x48;
        self->ext.libraryChair.debugAnimID = 0;
        self->ext.libraryChair.timer = 0x20;
        self->flags &= ~FLAG_DESTROY_IF_OUT_OF_CAMERA;
        if (g_PlayableCharacter != PLAYER_ALUCARD) {
            self->facingLeft = 1;
            self->posX.i.hi -= 8;
        }
        g_CutsceneFlags = 0;
        D_us_801D5288 = 0;
        D_us_801D51D4 = 0;
        break;
    case 1:
        if (g_CutsceneFlags & 2) {
            if (--self->ext.libraryChair.timer) {
                SetStep(2);
            }
        } else {
            if (g_CutsceneFlags & 0x80) {
                SetStep(9);
            }
        }
        break;
    case 2:
        if (AnimateEntity(&D_us_801811FC, self) == 0) {
            SetStep(3);
        }
        break;
    case 3:
        AnimateEntity(&D_us_80181204, self);
        if (g_CutsceneFlags & 4) {
            SetStep(4);
        }
        break;
    case 4:
        AnimateEntity(&D_us_80181210, self);
        if (g_CutsceneFlags & 8) {
            SetStep(5);
        }
        break;
    case 5:
        AnimateEntity(&D_us_8018121C, self);
        if (g_CutsceneFlags & 0x10) {
            SetStep(6);
        }
        break;
    case 6:
        AnimateEntity(&D_us_80181234, self);
        if (g_CutsceneFlags & 0x20) {
            SetStep(7);
        }
        break;
    case 7:
        if (AnimateEntity(&D_us_80181244, self) == 0) {
            SetStep(11);
        }
        break;
    case 9:
        if (AnimateEntity(&D_us_801811FC, self) == 0) {
            SetStep(10);
        }
        break;
    case 10:
        if (AnimateEntity(&D_us_801812C0, self) == 0) {
            SetStep(11);
        }
        break;
    case 11:
        if (g_CutsceneFlags & 0x800) {
            SetStep(12);
            self->ext.libraryChair.timer = 0x30;
        }
        if (g_CutsceneFlags & 0x1000) {
            SetStep(13);
        }
        break;
    case 12:
        AnimateEntity(&D_us_801812C8, self);
        if (!--self->ext.libraryChair.timer) {
            g_CutsceneFlags &= ~0x800;
            self->animCurFrame = 2;
            SetStep(11);
        }
        if (g_CutsceneFlags & 0x1000) {
            self->animCurFrame = 2;
            SetStep(13);
        }
        break;
    case 13:
        break;
    case 16:
        AnimateEntity(&D_us_801812D0, self);
        if (g_Player.status & PLAYER_STATUS_TRANSFORM) {
            self->velocityY += FIX(3.0 / 8);
            if (self->velocityY > FIX(7)) {
                self->velocityY = FIX(7);
            }
            MoveEntity();
            GetPlayerCollisionWith(self, 16, 12, 0x12);
        } else {
            if (PLAYER.step == Player_HighJump && PLAYER.step_s == 0) {
                PLAYER.step_s = 1;
                PLAYER.velocityY = FIX(-8);
            }
            self->posY.i.hi = player->posY.i.hi - 0x1C;
            self->velocityY = player->velocityY;
        }
        if ((self->posY.i.hi + tilemap->scrollY.i.hi) >= 172) {
            self->posY.i.hi = 172 - tilemap->scrollY.i.hi;
            self->animCurFrame = 2;
            SetStep(1);
        }
        break;
    case 255:
        if (g_pads[0].tapped & PAD_UP) {
            if (self->ext.libraryChair.debugAnimID) {
                self->ext.libraryChair.debugAnimID--;
                self->animFrameIdx = 0;
                self->animFrameDuration = 0;
            }
        } else if (g_pads[0].tapped & PAD_DOWN) {
            if (self->ext.libraryChair.debugAnimID != 0x10) {
                self->ext.libraryChair.debugAnimID++;
                self->animFrameIdx = 0;
                self->animFrameDuration = 0;
            }
        }
        AnimateEntity(D_us_801812D8[self->ext.libraryChair.debugAnimID], self);
        break;
    }
}

INCLUDE_ASM("st/lib_psp/psp/lib_psp/unk_1D9E8", func_psp_0925EAF0);

INCLUDE_ASM("st/lib_psp/psp/lib_psp/unk_1D9E8", func_psp_0925EBA0);

INCLUDE_ASM("st/lib_psp/psp/lib_psp/unk_1D9E8", func_psp_0925ED00);

INCLUDE_ASM("st/lib_psp/psp/lib_psp/unk_1D9E8", func_psp_0925F068);
