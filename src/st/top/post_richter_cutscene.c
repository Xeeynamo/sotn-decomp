// SPDX-License-Identifier: AGPL-3.0-or-later
#include "top.h"

extern EInit g_EInitInteractable;
extern u32 g_CutsceneFlags;

static AnimateEntityFrame D_us_80180DF0[] = {
    {0x02, 0x20}, {0x04, 0x21}, {0x04, 0x22}, {0x04, 0x23}, {0x04, 0x24},
    {0x04, 0x25}, {0x04, 0x26}, {0x04, 0x27}, {0x02, 0x20}, POSE_LOOP(0),
};
static AnimateEntityFrame D_us_80180E04[] = {
    {0x01, 0x2A},
    {0x08, 0x2B},
    POSE_END,
};
static AnimateEntityFrame D_us_80180E0C[] = {
    {0x02, 0x2C}, {0x04, 0x2D}, {0x05, 0x2E}, {0x04, 0x2F}, {0x04, 0x30},
    {0x04, 0x31}, {0x04, 0x32}, {0x04, 0x33}, {0x05, 0x34}, {0x04, 0x35},
    {0x04, 0x36}, {0x04, 0x37}, {0x02, 0x2C}, POSE_LOOP(0),
};

// Alucard walks to the Warp platform
void func_us_801AD11C(Entity* self) {
    Tilemap* tilemap;
    Entity* player;
    s16 offsetX;
    s16 offsetY;

    tilemap = &g_Tilemap;
    player = &PLAYER;
    offsetX = player->posX.i.hi + g_Tilemap.scrollX.i.hi;
    offsetY = self->posY.i.hi + g_Tilemap.scrollY.i.hi;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        g_PauseAllowed = false;
        g_unkGraphicsStruct.pauseEnemies = true;
        g_Player.padSim = PAD_NONE;
        g_Player.demo_timer = 1;
        break;

    case 1:
        if (g_CutsceneFlags & 0x40) {
            g_Player.padSim = PAD_RIGHT;
            self->step++;
        }
        g_Player.demo_timer = 1;
        break;

    case 2:
        g_Player.padSim = PAD_NONE;
        g_Player.demo_timer = 1;
        player->posX.i.hi = 0x380 - tilemap->scrollX.i.hi;
        if (g_CutsceneFlags & 0x20) {
            self->step++;
        }
        break;

    case 3:
        g_Player.padSim = PAD_LEFT;
        g_Player.demo_timer = 1;
        if (offsetX < 0x270) {
            g_Player.padSim |= PAD_CROSS;
            if (offsetX < 0x141) {
                g_Player.padSim = PAD_NONE;
                self->step++;
            }
            if ((g_Status.wornEquipment[1] == 0x19) &&
                (g_Player.vram_flag & TOUCHING_GROUND)) {
                self->step += 2;
            }
        }
        break;

    case 4:
        g_Player.padSim = PAD_UP;
        g_Player.demo_timer = 1;
        break;

    case 5:
        g_PauseAllowed = true;
        if (g_unkGraphicsStruct.pauseEnemies) {
            g_unkGraphicsStruct.pauseEnemies = false;
        }
        DestroyEntity(self);
        break;
    }
}

void func_us_801AD320(Entity* self) {
    Tilemap* tilemap;
    Entity* player;
    s16 offsetX;
    s16 offsetY;

    tilemap = &g_Tilemap;
    player = &PLAYER;
    offsetX = player->posX.i.hi + g_Tilemap.scrollX.i.hi;
    offsetY = self->posY.i.hi + g_Tilemap.scrollY.i.hi;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        self->animSet = ANIMSET_OVL(2);
        self->animCurFrame = 0x11;
        self->unk5A = 0xF;
        self->palette = PAL_FLAG(0x230);
        break;
    case 1:
        if (g_CutsceneFlags & 4) {
            self->animCurFrame = 0x12;
            self->step++;
        }
        break;
    case 2:
        if (g_CutsceneFlags & 8) {
            self->animCurFrame = 0x11;
            self->step++;
        }
        break;
    case 3:
        break;
    }
}

void func_us_801AD400(Entity* self) {
    Entity* player;
    Tilemap* tilemap;
    s16 offsetX, offsetY;
    s32 panDistance;

    tilemap = &g_Tilemap;
    player = &PLAYER;
    offsetX = self->posX.i.hi + g_Tilemap.scrollX.i.hi;
    offsetY = self->posY.i.hi + g_Tilemap.scrollY.i.hi;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        self->animSet = ANIMSET_OVL(4);
        self->animCurFrame = 0;
        self->unk5A = 0x46;
        self->palette = 0x208;
        self->facingLeft = 1;
        break;

    case 1:
        if (g_CutsceneFlags & 0x10) {
            self->velocityX = FIX(-1.5);
            SetStep(2);
        }

        break;
    case 2:
        panDistance = AnimateEntity(D_us_80180DF0, self);
        if ((panDistance & 0x80) && (self->pose == 3 || self->pose == 7)) {
            panDistance = (self->posX.i.hi - 0x78) / 16;

            if (panDistance < -8) {
                panDistance = -8;
            }
            if (panDistance > 8) {
                panDistance = 8;
            }
            g_api.PlaySfxVolPan(SFX_STOMP_SOFT_B, 0x50, panDistance);
        }
        MoveEntity();
        if (offsetX < 0x3C0) {
            self->animCurFrame = 0xC;
            self->step++;
        }
        break;

    case 3:
        if (g_CutsceneFlags & 0x80) {
            self->animSet = ANIMSET_OVL(5);
            self->unk5A = 0x48;
            self->animCurFrame = 0x2C;
            self->velocityX = FIX(-0.75);
            SetStep(4);
        }
        break;

    case 4:
        AnimateEntity(D_us_80180E0C, self);
        MoveEntity();
        if (offsetX < 0x350) {
            SetStep(5);
        }
        break;

    case 5:
        if (AnimateEntity(D_us_80180E04, self) == 0) {
            self->animSet = ANIMSET_OVL(4);
            self->animCurFrame = 0xC;
            self->unk5A = 0x46;
            self->facingLeft = 0;
            SetStep(6);
        }
        break;

    case 6:
        break;
    }
}

#ifdef VERSION_PSP

void func_pspeu_092496C8(Entity* self) {
    Entity* player = &PLAYER;
    s16 offsetX = player->posX.i.hi - self->posX.i.hi;

    if (offsetX > 0) {
        self->facingLeft = 0;
    } else {
        self->facingLeft = 1;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        self->animSet = ANIMSET_OVL(2);
        self->animCurFrame = 0x11;
        self->unk5A = 0xF;
        self->palette = PAL_FLAG(0x230);
        // fallthrough
    case 1:
        break;
    }
}

void func_pspeu_092497B0(Entity* self) {
    Entity* player = &PLAYER;
    s16 xOffset = player->posX.i.hi - self->posX.i.hi;

    if (xOffset > 0) {
        self->facingLeft = 0;
    } else {
        self->facingLeft = 1;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        self->animSet = ANIMSET_OVL(4);
        self->animCurFrame = 0xC;
        self->unk5A = 0x46;
        self->palette = 0x208;
        // fallthrough
    case 1:
        break;
    }
}

void func_pspeu_09249898(Entity* self) {
    Entity* player;
    s16 offsetX;

    player = &PLAYER;
    offsetX = player->posX.i.hi - self->posX.i.hi;
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        break;
    case 1:
        if (player->step < 2 && g_pads->tapped & PAD_UP && offsetX < 0x28 &&
            offsetX > -0x28) {
            g_CutsceneFlags |= 1;
            g_PauseAllowed = false;
            g_unkGraphicsStruct.pauseEnemies = true;
            g_Player.padSim = PAD_NONE;
            g_Player.demo_timer = 1;
            self->step++;
        }
        break;
    case 2:
        g_Player.padSim = PAD_NONE;
        g_Player.demo_timer = 1;
        if (g_CastleFlags[0xE2]) {
            if (offsetX < 8) {
                if (player->facingLeft) {
                    g_Player.padSim = PAD_RIGHT;
                }
            } else if (!player->facingLeft) {
                g_Player.padSim = PAD_LEFT;
            }
        } else if (offsetX < -8) {
            if (player->facingLeft) {
                g_Player.padSim = PAD_RIGHT;
            }
        } else if (!player->facingLeft) {
            g_Player.padSim = PAD_LEFT;
        }
        self->step++;
        break;
    case 3:
        g_Player.padSim = PAD_NONE;
        g_Player.demo_timer = 1;
        if (g_CutsceneFlags & 4) {
            self->step++;
            break;
        }
        break;
    case 4:
        g_PauseAllowed = true;
        if (g_unkGraphicsStruct.pauseEnemies) {
            g_unkGraphicsStruct.pauseEnemies = false;
        }
        SetStep(1);
        break;
    }
}

#endif
