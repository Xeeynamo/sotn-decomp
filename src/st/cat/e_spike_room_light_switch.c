// SPDX-License-Identifier: AGPL-3.0-or-later
#include "cat.h"

extern EInit g_EInitSpikeRoomLightSwitch;

void EntitySpikeRoomLightSwitch(Entity* self) {
    Primitive* prim;
    s32 i;
    u8 var_s2;
    s32 primIndex;
    Entity* player;

    enum Step {
        INIT = 0,
        WAIT_FOR_PRESS = 1,
        LIGHT_EXPAND_OUT = 2,
        LIGHT_EXPAND_IN = 3,
        PLAY_SFX = 4,
        LIGHT_ROOM = 5,
        CLEAR_SCREEN_WHITE = 6,
        ROOM_LIT = 7
    };

    var_s2 = GetPlayerCollisionWith(
        self, 0x28, self->ext.spikeRoomSwitch.collisionHeight, 4);
    switch (self->step) {
    case INIT:
        InitializeEntity(g_EInitSpikeRoomLightSwitch);
        self->hitboxState = 1;
        self->hitboxWidth = 0x28;
        self->hitboxHeight = 8;
        self->hitboxOffX = 0x28;
        self->hitboxOffY = 0xC;
        // nb. Switch starts out green but is almost immediately changed to
        // yellow.
        self->palette = PAL_FLAG(0x99);
        self->ext.spikeRoomSwitch.timer.i.lo = 0;
        // nb. The switch starts with slightly raised collision, there is a
        // subtle drop as the player presses it (10 -> 8).
        self->ext.spikeRoomSwitch.collisionHeight = 10;
        self->zPriority = 0xC0;

        // If the player has already pressed the switch, it remains pressed and
        // we skip all the logic
        if (g_CastleFlags[CAT_SPIKE_ROOM_LIT]) {
            self->animCurFrame = 2;
            self->ext.spikeRoomSwitch.collisionHeight = 8;
            // "pressed" palette
            self->palette = PAL_FLAG(0x9B);
            self->step = ROOM_LIT;
        }

        if (!g_CastleFlags[CAT_SPIKE_ROOM_LIT]) {
            // If the player hasn't pressed the switch yet, setup a glow effect
            primIndex = g_api.func_800EDB58(PRIM_G4_ALT, 2);
            if (primIndex != -1) {
                self->flags |= FLAG_HAS_PRIMS;
                self->primIndex = primIndex;
                prim = &g_PrimBuf[primIndex];

                for (self->ext.spikeRoomSwitch.prim = prim, i = 0; prim != NULL;
                     prim = prim->next, i++) {
                    prim->x0 = self->posX.i.hi + 1;
                    prim->x2 = prim->x0;
                    prim->x1 = prim->x0 + 0x4C;
                    prim->x3 = prim->x1;
                    prim->y0 = prim->y1 = self->posY.i.hi;
                    if (i != 0) {
                        prim->y2 = prim->y3 = prim->y0 + 8;
                    } else {
                        prim->y2 = prim->y3 = prim->y0 - 0x10;
                    }

                    PGREY(prim, 0) = 0x80;
                    LOW(prim->r1) = LOW(prim->r0);
                    PGREY(prim, 2) = 0;
                    LOW(prim->r3) = LOW(prim->r2);
                    prim->priority = 0xD1;
                    prim->drawMode = DRAW_UNK_400 | DRAW_TPAGE2 | DRAW_TPAGE |
                                     DRAW_UNK02 | DRAW_TRANSP;
                }
            } else {
                DestroyEntity(self);
                return;
            }
        }
        break;
    case WAIT_FOR_PRESS:
        if (!(g_Timer % 2)) {
            self->ext.spikeRoomSwitch.timer.i.lo ^= 1;
        }

        // BUG: This else clause is never hit and the button remains
        // yellow. This looks to be because timer.val is set in the else
        // statement to 0x20 meaning the above XOR alternates between 0x20 and
        // 0x21.
        //
        // Possible this bug was introduced when this 0x20 value was added
        // because timer.val is first initialised to 0 which would make this
        // button flash yellow and green
        if (self->ext.spikeRoomSwitch.timer.i.lo) {
            // Switch is yellow
            self->palette = PAL_FLAG(0x9A);
        } else {
            // Switch is green
            self->palette = PAL_FLAG(0x99);
        }

        if (var_s2) {
            // Player has stepped on the switch!
            if (!--self->ext.spikeRoomSwitch.timer.val) {
                g_api.PlaySfx(SFX_LEVER_METAL_BANG);
                // Switch is hidden palette
                self->palette = PAL_FLAG(0x94);
                self->animCurFrame = 2;
                self->ext.spikeRoomSwitch.collisionHeight = 8;
                self->ext.spikeRoomSwitch.timer.val = 0x20;
                self->step++;
            }
        } else {
            // Set a short pause upon stepping on the button before kicking off
            // the light phase
            self->ext.spikeRoomSwitch.timer.val = 0x20;
        }
        break;
    case LIGHT_EXPAND_OUT:
        prim = self->ext.spikeRoomSwitch.prim;
        prim->y2 -= 3;
        prim->y3 = prim->y2;
#ifdef VERSION_US
        prim->r0 = prim->r0;
#endif
        prim->b0 = prim->g0 = prim->r0;
        LOW(prim->r1) = LOW(prim->r0);
        prim->r2 += 1;
        prim->b2 = prim->g2 = prim->r2;
        LOW(prim->r3) = LOW(prim->r2);
        prim = prim->next;

        prim->y2 += 2;
        prim->y3 = prim->y2;
#ifdef VERSION_US
        prim->r0 = prim->r0;
#endif
        prim->b0 = prim->g0 = prim->r0;
        LOW(prim->r1) = LOW(prim->r0);
        prim->r2 += 1;
        prim->b2 = prim->g2 = prim->r2;
        LOW(prim->r3) = LOW(prim->r2);

        if (!--self->ext.spikeRoomSwitch.timer.val) {
            // nb. This assignment appears unnecessary?
            // The next case already does this
            prim = self->ext.spikeRoomSwitch.prim;
            self->step++;
        }
        break;
    case LIGHT_EXPAND_IN:
        prim = self->ext.spikeRoomSwitch.prim;
        prim->x0 += 2;
        prim->x2 = prim->x0;
        prim->x1 -= 2;
        prim->x3 = prim->x1;
        if (prim->x1 - prim->x0 < 2) {
            prim->x0 = prim->x2 = prim->x0;
            prim->x1 = prim->x3 = prim->x0 - 2;
            prim->y0 = prim->y1 = self->posY.i.hi;
            prim->y2 = prim->y3 = prim->y0;
            PGREY(prim, 0) = 0xFF;
            LOW(prim->r2) = LOW(prim->r0);
            PGREY(prim, 1) = 0;
            LOW(prim->r3) = (s32)LOW(prim->r1);
        }
        prim = prim->next;

        prim->x0 += 2;
        prim->x2 = prim->x0;
        prim->x1 -= 2;
        prim->x3 = prim->x1;
        if (prim->x1 - prim->x0 < 2) {
            prim->x0 = prim->x2 = prim->x0;
            prim->x1 = prim->x3 = prim->x0 + 2;
            prim->y0 = prim->y1 = self->posY.i.hi;
            prim->y2 = prim->y3 = prim->y0;
            PGREY(prim, 0) = 0xFF;
            LOW(prim->r2) = LOW(prim->r0);
            PGREY(prim, 1) = 0;
            LOW(prim->r3) = (s32)LOW(prim->r1);
            self->step++;
            self->ext.spikeRoomSwitch.timer.val = 0x20;
        }
        break;
    case PLAY_SFX:
        // Room appears completely dark for a time,
        // then we move into the light phase
        if (!--self->ext.spikeRoomSwitch.timer.val) {
            g_api.PlaySfx(SFX_WEAPON_APPEAR);
            self->step++;
        }
        break;
    case LIGHT_ROOM:
        prim = self->ext.spikeRoomSwitch.prim;
        while (prim != NULL) {
            if (!(prim->y0 & 0xFF00)) {
                prim->y0 -= 0x10;
                prim->y1 = prim->y0;
            }

            if (!(prim->y2 & 0xFF00)) {
                prim->y2 += 8;
                prim->y3 = prim->y2;
            }

            if (prim->r1 < 0xF7) {
                prim->r1 += 4;
                prim->g1 = prim->b1 = prim->r1;
                LOW(prim->r3) = LOW(prim->r1);
            }
            prim = prim->next;
        }

        var_s2 = 0;
        prim = self->ext.spikeRoomSwitch.prim;
        if (!(prim->x1 & 0xFF00)) {
            prim->x1 = prim->x0 - (self->ext.spikeRoomSwitch.unk84 >> 4);
            prim->x3 = prim->x1;
        } else {
            var_s2++;
        }
        prim = prim->next;

        if (!(prim->x1 & 0xFF00)) {
            prim->x1 = prim->x0 + (self->ext.spikeRoomSwitch.unk84 >> 4);
            prim->x3 = prim->x1;
        } else {
            var_s2++;
        }

        self->ext.spikeRoomSwitch.unk84 += self->ext.spikeRoomSwitch.unk86;
        self->ext.spikeRoomSwitch.unk86 += self->ext.spikeRoomSwitch.unk88;
        self->ext.spikeRoomSwitch.unk88 += 8;
        if (var_s2 > 1) {
            prim = self->ext.spikeRoomSwitch.prim;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;

            prim->x0 = prim->x2 = 0;
            prim->x1 = prim->x3 = 0x100;
            prim->y0 = prim->y1 = 0;
            prim->y2 = prim->y3 = 0x100;
            prim->r0 = prim->b0 = prim->g0 = 0xC0;
            LOW(prim->r1) = LOW(prim->r0);
            LOW(prim->r2) = LOW(prim->r0);
            LOW(prim->r3) = LOW(prim->r0);
            prim->drawMode &= ~DRAW_UNK02;
            g_BgLayers[0].flags |= 1;
            g_CastleFlags[CAT_SPIKE_ROOM_LIT] = true;
            // "pressed" palette
            self->palette = PAL_FLAG(0x9B);
            self->step++;
        }
        break;
    case CLEAR_SCREEN_WHITE:
        // Decrease the "flashbang" effect to return the room to normal
        // brightness
        prim = self->ext.spikeRoomSwitch.prim;
        prim = prim->next;
        var_s2 = PrimDecreaseBrightness(prim, 7);
        if (!var_s2) {
            g_api.FreePrimitives(self->primIndex);
            self->flags &= ~FLAG_HAS_PRIMS;
            player = &PLAYER;
            player->zPriority = 0x94;
            g_unkGraphicsStruct.g_zEntityCenter = 0x94;
            self->step = ROOM_LIT;
        }
        break;
    case ROOM_LIT:
        self->animCurFrame = 2;
        // "pressed" palette
        self->palette = PAL_FLAG(0x9B);
        break;
    }
}
