// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rno0.h"

static s16 bird_cage_pos_x[] = {0x7C, 0x72};
static s16 bird_cage_pos_y[] = {0x9C, 0x72};
static s16 statue_pos_x[] = {-0x51, 0x50, -0x81, 0x80};
static s16 gear_pos_x[] = {-0x7C, 0x7C};
static s16 stone_door_pos_x[] = {0x20, -0x20, 0x50, -0x50};
static s16 unused[] = {-0x51, 0x50};
static u32 statue_pos_x_3[] = {FIX(-0.5), FIX(0.5)};
static u16 anim_bird_cage[] = {21, 22};
static s16 unused2[] = {-14, 14, -8, 8, -23, -14, -8, 8, 14, 23, -8, 8};
static u8 anim_gear_1[] = {6, 17, 6, 18, 6, 19, 6, 20, 0, 0};
static u8 anim_gear_2[] = {6, 20, 6, 19, 6, 18, 6, 17, 0, 0};
static u16 g_StoneDoorTiles[] = {
    0x597, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x597,
};

void func_us_801CCAAC(Entity* self) {
    Entity* tempEntity;
    s16 angle;

    if ((self->ext.clockRoom.unk88 & 0x1F) == 0) {
        g_api.PlaySfxVolPan(SFX_STONE_MOVE_A, 0x40, 0);
    }
    self->ext.clockRoom.unk88++;

    // Minute hand
    tempEntity = self + 5;
    angle =
        tempEntity->ext.clockRoom.unk80 +
        (LOW(tempEntity->ext.clockRoom.bellTimer) * self->ext.clockRoom.unk88) /
            512;
    angle %= (60 * 60);
    tempEntity->ext.clockRoom.hand = angle;

    // Hour hand
    tempEntity++;
    angle =
        tempEntity->ext.clockRoom.unk80 -
        (LOW(tempEntity->ext.clockRoom.bellTimer) * self->ext.clockRoom.unk88) /
            512;
    angle %= (60 * 60);
    tempEntity->ext.clockRoom.hand = angle;
}

void UpdateBirdcages(Entity* self, u32 timerMinutes) {
    // self + 7 is birdcage door 1
    self += 7;
    if (timerMinutes >= 10 && timerMinutes < 30) {
        self->ext.birdcage.state = true;
    } else {
        self->ext.birdcage.state = false;
    }

    // self + 8 is birdcage door 2
    self += 1;
    if (timerMinutes >= 30 && timerMinutes < 50) {
        self->ext.birdcage.state = true;
    } else {
        self->ext.birdcage.state = false;
    }
}

#ifdef VERSION_PSP
extern s32 D_91FC3F8;
extern s32 D_91FC400;
extern s32 D_91FC408;
extern s32 D_91FC410;
#define timer_frames D_91FC3F8
#define timer_seconds D_91FC400
#define timer_minutes D_91FC408
#define timer_hours D_91FC410
void UpdateClockHands(Entity* self) {
#else
#define timer_frames status->timerFrames
#define timer_seconds status->timerSeconds
#define timer_minutes status->timerMinutes
#define timer_hours status->timerHours
void UpdateClockHands(Entity* self, PlayerStatus* status) {
#endif
    // self + 5 is the minute hand
    self += 5;
    self->ext.clockRoom.hand = timer_minutes * 60;

    // self + 6 is the hour hand
    self += 1;
    #if defined(VERSION_US) && defined(INVERTED_STAGE)
    #define HOURS (timer_hours)
    #else
    #define HOURS (timer_hours % 12)
    #endif
    self->ext.clockRoom.hand = (HOURS * 300) + (timer_minutes * 5);
}

// Two statues. One responds to the stopwatch subweapon.
// The other leads to colloseum (ARE overlay)
typedef enum Statues {
    /* 0 */ WATCH_STATUE,
    /* 1 */ ARE_STATUE,
} Statues;

static u16 g_Statues[2];
#ifdef VERSION_PSP
static u32 D_pspeu_092A1D08;
static u32 D_pspeu_092A1D00;
#endif

extern EInit g_EInitCommon;

void EntityClockRoomController(Entity* self) {
    #ifndef VERSION_PSP
    PlayerStatus* status = &g_Status;
    #endif
    Primitive* prim;
    Entity* entity;
    s32 primIndex;
    u16 i;
    s16 posX;

    // Plays the clock bell
    if (self->ext.clockRoom.bellTimer) {
        if (!self->ext.clockRoom.bellDuration) {
            g_api.PlaySfx(SFX_CLOCK_ROOM_BELL);
            if (--self->ext.clockRoom.bellTimer) {
                self->ext.clockRoom.bellDuration = 64;
            }
        } else {
            self->ext.clockRoom.bellDuration--;
        }
    }

    // Controls the statues
    entity = &PLAYER;
    if (g_unkGraphicsStruct.D_800973FC == 0) {
        if (entity->posY.i.hi < 0x90) {
            g_Statues[WATCH_STATUE] = false;
        }
    } else if (!self->ext.clockRoom.unk8A) {
        g_Statues[WATCH_STATUE] = true;
    }

    self->ext.clockRoom.unk8A = g_unkGraphicsStruct.D_800973FC;

    // Every other minute the top left statue opens
    if (timer_minutes & 1) {
        if (entity->posY.i.hi < 0x90) {
            g_Statues[ARE_STATUE] = false;
        }
    } else {
        g_Statues[ARE_STATUE] = true;
    }

    switch (self->step) {
    case 0:
        if ((g_Timer % 60) == 0) {
            g_api.PlaySfx(SFX_CLOCK_ROOM_TICK);
        }

        primIndex = g_api.AllocPrimitives(PRIM_G4, 1);
        if (primIndex == -1) {
            return;
        }
#ifndef VERSION_PSP
        InitializeEntity(g_EInitCommon);
#endif
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        prim->x0 = prim->x2 = prim->y0 = prim->y1 = 0;
        prim->x1 = prim->x3 = prim->y2 = prim->y3 = 256;
        prim->r0 = prim->g0 = prim->b0 = 0;
        LOW(prim->r1) = LOW(prim->r0);
        LOW(prim->r2) = LOW(prim->r0);
        LOW(prim->r3) = LOW(prim->r0);
        prim->priority = 0x1F0;
        prim->drawMode = DRAW_HIDE;
#ifdef VERSION_PSP
        InitializeEntity(g_EInitCommon);
#endif

        g_api.PlaySfx(SET_STOP_MUSIC);
        stopMusicFlag = true;
        currentMusicId = 0;
        entity = &PLAYER;
        g_Statues[WATCH_STATUE] = false;

        if (entity->posY.i.hi > 0xC0) {
            posX = entity->posX.i.hi;
            if (posX < 0x40) {
                g_Statues[WATCH_STATUE] = true;
            } else if (posX > 0xC0) {
                g_Statues[ARE_STATUE] = true;
            }
        }

        self->animSet = ANIMSET_OVL(2);
        self->animCurFrame = 23;
        self->zPriority = 0x40;

        // Create clock hands
        entity = self + 5;
        for (i = 0; i < 2; i++, entity++) {
            CreateEntityFromCurrentEntity(E_CLOCK_HANDS, entity);
            entity->params = i;
        }
#ifdef VERSION_PSP
        UpdateClockHands(self);
#else
        UpdateClockHands(self, status);
#endif

        // Create Birdcage doors
        entity = self + 7;
        for (i = 0; i < 2; i++, entity++) {
            CreateEntityFromCurrentEntity(E_BIRDCAGE_DOOR, entity);
            entity->params = i;
        }
        UpdateBirdcages(self, timer_minutes);

        // Shadow for the Bighorn sheep head on the center
        entity = self + 9;
        CreateEntityFromCurrentEntity(E_CLOCK_ROOM_SHADOW, entity);
        entity->animSet = ANIMSET_OVL(2);
        entity->animCurFrame = 23;
        entity->zPriority = 0x40;
        entity->palette = PAL_FLAG(0x4B);
        entity->drawFlags = ENTITY_OPACITY;
        entity->blendMode = BLEND_TRANSP;
        entity->posY.i.hi += 4;

        // Create path blocking statues
        entity = self + 1;
        for (i = 0; i < 2; i++, entity++) {
            CreateEntityFromCurrentEntity(E_STATUE, entity);
            entity->params = i;
        }

        // Create the gears that drive the statues
        entity = self + 12;
        for (i = 0; i < 2; i++, entity++) {
            CreateEntityFromCurrentEntity(E_STATUE_GEAR, entity);
            entity->params = i;
        }

        // Create the stones on the floor
        entity = self + 14;
        for (i = 0; i < 2; i++, entity++) {
            CreateEntityFromCurrentEntity(E_STONE_DOOR, entity);
            entity->params = i;
        }
        break;

    case 1:
        if (!timer_frames) {
            g_api.PlaySfx(SFX_CLOCK_ROOM_TICK);
        }

#ifdef VERSION_PSP
        UpdateClockHands(self);
#else
        UpdateClockHands(self, status);
#endif
        if (timer_seconds == 0 && timer_frames == 0) {
            if (timer_minutes == 0) {
                self->ext.clockRoom.bellTimer = ((timer_hours + 11) % 12) + 1;
                if (!self->ext.clockRoom.bellTimer) {
                    self->ext.clockRoom.bellTimer = 12;
                }
            } else if (((timer_minutes != 0) ^ 1) == 30) {
                self->ext.clockRoom.bellTimer = 1;
            }
        }

        UpdateBirdcages(self, timer_minutes);

        if (!g_CastleFlags[RCEN_OPEN]) {
            entity = &PLAYER;
            #if defined(VERSION_US) && defined(INVERTED_STAGE)
            #define XLIM 0x60
            #else
            #define XLIM 0x50
            #endif
            if (entity->posX.i.hi >= XLIM && entity->posX.i.hi <= 0xA0) {
                for(posX = 0, i = RELIC_HEART_OF_VLAD; i <= RELIC_EYE_OF_VLAD; i++){
                    // If we don't have the relic, set the posX flag.
                    if(!(g_Status.relics[i] & 1)){
                        posX++;
                    }
                }
                // If it's zero (we have all relics) we will open the clock
                if(!posX){
                    SetStep(2);
                }
            }
        }
        break;

    case 2:
        g_Statues[WATCH_STATUE] = false;
        g_Statues[ARE_STATUE] = false;
        g_Player.padSim = 0;
        g_Player.demo_timer = 1;
        entity = &PLAYER;
        posX = entity->posX.i.hi;
        #if defined(VERSION_US) && defined(INVERTED_STAGE)
        entity->posX.i.hi = (posX <= 0x80 ? 0x60 : 0xA0);
        #endif
        switch (self->step_s) {
        case 0:
            self->ext.clockRoom.unk88 = 0;
            self->step_s++;
            break;
        case 1:
            self->step_s++;
            break;

        case 2:
            self->step_s++;
            break;
        case 3:
            self->step_s++;
            break;
        case 4:
            prim = &g_PrimBuf[self->primIndex];
            prim->r0 = prim->g0 = prim->b0 += 16;
            LOW(prim->r1) = LOW(prim->r0);
            LOW(prim->r2) = LOW(prim->r0);
            LOW(prim->r3) = LOW(prim->r0);
            prim->drawMode = DRAW_TRANSP | DRAW_TPAGE | DRAW_TPAGE2;
            if (prim->r0 > 192) {
                self->step_s++;
            }
            break;

        case 5:
            prim = &g_PrimBuf[self->primIndex];
            prim->r0 = prim->g0 = prim->b0 -= 4;
            LOW(prim->r1) = LOW(prim->r0);
            LOW(prim->r2) = LOW(prim->r0);
            LOW(prim->r3) = LOW(prim->r0);
            if (prim->r0 < 8) {
                prim->drawMode = DRAW_HIDE;
                self->step_s++;
            }
            break;

        case 6:
            entity = self + 7;
            LOH(entity->ext.clockRoom.unk80) = 1;

            entity++;
            LOH(entity->ext.clockRoom.unk80) = 1;

            self->ext.clockRoom.unk88 = 0x80;
            self->ext.clockRoom.unk88 = 1;
            self->step_s++;
            break;

        case 7:
            if (!--self->ext.clockRoom.unk88) {
                // Minute hand
                entity = self + 5;
                posX = LOW(entity->ext.clockRoom.unk80) =
                    entity->ext.clockRoom.hand;
                posX %= (60 * 60);
                LOW(entity->ext.clockRoom.bellTimer) = 5400 - posX;

                // Hour hand
                entity++;
                posX = LOW(entity->ext.clockRoom.unk80) =
                    entity->ext.clockRoom.hand;
                posX %= (60 * 60);
                LOW(entity->ext.clockRoom.bellTimer) = posX + 1800;

                self->ext.clockRoom.unk88 = 0;
                self->step_s++;
            }
            break;

        case 8:
            func_us_801CCAAC(self);
            if (self->ext.clockRoom.unk88 >= 0x200) {
                self->step_s++;
                self->ext.clockRoom.bellTimer = 13;
                self->ext.clockRoom.unk88 = 0x380;
            }
            break;

        case 9:
            if (!--self->ext.clockRoom.unk88) {
                g_CastleFlags[RCEN_OPEN] = 1;
                g_api.RevealSecretPassageAtPlayerPositionOnMap(RCEN_OPEN);
                SetStep(3);
                self->ext.clockRoom.unk88 = 0x140;
            }
        }
        break;

    case 3:
        g_Statues[WATCH_STATUE] = false;
        g_Statues[ARE_STATUE] = false;
        switch (self->step_s) {
        case 0:
            if (!--self->ext.clockRoom.unk88) {
                // Minute hand
                entity = self + 5;
                LOW(entity->ext.clockRoom.unk80) = entity->ext.clockRoom.hand;
                posX = timer_minutes * 60;
                LOW(entity->ext.clockRoom.bellTimer) = posX + 1800;

                // Hour hand
                entity++;
                LOW(entity->ext.clockRoom.unk80) = entity->ext.clockRoom.hand;
#ifdef VERSION_PSP
                posX = ((timer_hours % 12) * 300) + (timer_minutes * 5);
#else
                posX = (timer_hours * 300) + (timer_minutes * 5);
#endif
                LOW(entity->ext.clockRoom.bellTimer) = 5400 - posX;

                self->ext.clockRoom.unk88 = 0;
                self->step_s++;
            }
            break;

        case 1:
            func_us_801CCAAC(self);
            if (self->ext.clockRoom.unk88 >= 0x200) {
                SetStep(1);
            }
        }
        break;
    }
}

#include "../clock_room_entities.h"
