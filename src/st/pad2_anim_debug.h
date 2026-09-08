// SPDX-License-Identifier: AGPL-3.0-or-later

// Common code dropped into many Entity functions using a special case
// in the self->step field. Allows using the Player 2 controller to move
// the entity's frame one step forward or back. This code is impossible
// to reach when playing the game, but can be triggered by poking the proper
// location in RAM to trigger the entity's state machine.

#ifndef BUTTON_SYMBOL
#define BUTTON_SYMBOL PAD_CIRCLE
#endif

#ifndef PAD2_ANIM_DEBUG_PRINT
#define PAD2_ANIM_DEBUG_PRINT() FntPrint("charal %x\n", self->animCurFrame)
#endif

#ifndef PAD2_ANIM_DEBUG_ABORT
#define PAD2_ANIM_DEBUG_ABORT break
#endif

/**
 * Debug: Press SQUARE / CIRCLE on the second controller
 * to advance/rewind current animation frame
 */
PAD2_ANIM_DEBUG_PRINT();
if (g_pads[1].pressed & PAD_SQUARE) {
    if (self->params) {
        PAD2_ANIM_DEBUG_ABORT;
    }
    self->animCurFrame++;
    self->params |= 1;
} else {
    self->params = 0;
}
if (g_pads[1].pressed & BUTTON_SYMBOL) {
    if (self->step_s) {
        PAD2_ANIM_DEBUG_ABORT;
    }
    self->animCurFrame--;
    self->step_s |= 1;
} else {
    self->step_s = 0;
}
break;

#undef PAD2_ANIM_DEBUG_PRINT
#undef PAD2_ANIM_DEBUG_ABORT
