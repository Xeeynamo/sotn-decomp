// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rno3.h"

#ifdef VERSION_PSP
extern s32 E_ID(CAVERN_DOOR_PLATFORM);
#endif

extern EInit D_us_80180A34;

#include "../door_cascade_physics.h"

// lever and platform to open caverns door
void EntityCavernDoorLever(Entity* self) {
    s32 posX;
    s32 posY;
    Entity* platform;

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_80180A34);
        self->animCurFrame = 18;
        self->drawFlags |= ENTITY_ROTATE;
        self->rotate = -0x200;
        platform = self + 1;
        CreateEntityFromEntity(E_ID(CAVERN_DOOR_PLATFORM), self, platform);
        if (g_CastleFlags[NO4_TO_NP3_SHORTCUT]) {
            self->rotate = 0;
        }

    case 1:
        platform = self + 1;
        if (platform->ext.cavernDoor.collision) {
            self->rotate += 4;
            if (self->rotate > 0) {
                self->rotate = 0;
                if (!g_CastleFlags[NO4_TO_NP3_SHORTCUT]) {
                    g_api.PlaySfx(SFX_LEVER_METAL_BANG);
                }
                g_CastleFlags[NO4_TO_NP3_SHORTCUT] = 1;
            } else if (!(g_Timer & 0xF)) {
                g_api.PlaySfx(SFX_LEVER_METAL_BANG);
            }
        }
        break;
    }
    platform = self + 1;
    posX = self->posX.val;
    posY = self->posY.val;
    posX += rcos(self->rotate) * 0x28 << 4;
    posY += rsin(self->rotate) * 0x28 << 4;
    platform->posX.val = posX;
    platform->posY.val = posY;
}

// platform attached to lever at cavern door
void EntityCavernDoorPlatform(Entity* self) {
    Entity* player;
    s32 collision;
    s32 xDiff;

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_80180A34);
        self->animCurFrame = 17;
        self->ext.cavernDoor.xCoord.val = self->posX.val;
        self->ext.cavernDoor.xCoord.val = self->posX.val; // ? WTF

    case 1:
        collision = GetPlayerCollisionWith(self, 6, 5, 4);
        self->ext.cavernDoor.collision = collision;

        if (collision != 0) {
            xDiff = self->posX.i.hi - FIX_TO_I(self->ext.cavernDoor.xCoord.val);
            player = &PLAYER;
            player->posX.i.hi += xDiff;
            player->posY.i.hi += 1;
// Need to identify this var, and see why it's in NP3 but not NO3
#if !defined(STAGE_IS_NO3)
            g_unkGraphicsStruct.shoveX.i.hi += xDiff;
            g_unkGraphicsStruct.shoveY.i.hi += 1;
#endif
        }
        self->ext.cavernDoor.xCoord.val = self->posX.val;
        self->ext.cavernDoor.yCoord.val = self->posY.val;
    }
}

INCLUDE_ASM("st/rno3/nonmatchings/unk_31A64", func_us_801B1E38);
