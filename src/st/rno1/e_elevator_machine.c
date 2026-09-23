// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rno1.h"

static AnimateEntityFrame anim0[] = {{4, 1}, {4, 2}, {4, 3}, POSE_LOOP(0)};
static AnimateEntityFrame anim1[] = {
    {6, 4}, {6, 5}, {6, 6}, {6, 7}, POSE_LOOP(0)};
static AnimateEntityFrame anim2[] = {{4, 8}, {4, 9}, {4, 10}, POSE_LOOP(0)};
static AnimateEntityFrame anim3[] = {{8, 11}, {8, 12}, POSE_LOOP(0)};
static AnimateEntityFrame anim4[] = {{4, 13}, {4, 14}, {4, 15}, POSE_LOOP(0)};
static AnimateEntityFrame anim5[] = {{4, 16}, {4, 17}, {4, 18}, POSE_LOOP(0)};
static AnimateEntityFrame anim6[] = {
    {8, 19}, {8, 20}, {8, 21}, {8, 22}, POSE_LOOP(0)};
static AnimateEntityFrame anim7[] = {{4, 23}, {4, 24}, {4, 25}, POSE_LOOP(0)};
static AnimateEntityFrame anim8[] = {{1, 26}, {1, 27}, POSE_LOOP(0)};

static u8 initFrames[] = {1, 4, 8, 11, 13, 16, 19, 23, 26};

static AnimateEntityFrame* anims[] = {
    anim0, anim1, anim2, anim3, anim4, anim5, anim6, anim7, anim8,
};

extern EInit g_EInitElevatorMachine;

// The whirring machinery which controls the elevator. In RNO1, it does not
// have an activation lever, but will be running or not running based on
// whether it was activated in NO1.
// There are 9 copies of this entity, with params 0 through 9. They each
// have different animations, but don't fundamentally do different things.
// Their animations have different numbers of frames so they need separate
// entities to run them all independently.
void EntityElevatorMachine(Entity* self) {
    AnimateEntityFrame* anim;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitElevatorMachine);
        self->animCurFrame = initFrames[self->params];
        self->zPriority = 0x6A;
        break;

    case 1:
        if (g_CastleFlags[NO1_ELEVATOR_ACTIVATED]) {
            self->step += 1;
        }
        break;

    case 2:
        anim = anims[self->params];
        AnimateEntity(anim, self);
        break;
    }
}
