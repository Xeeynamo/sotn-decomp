// SPDX-License-Identifier: AGPL-3.0-or-later

// Common code dropped into many Entity functions using a special case
// in the self->step field. Allows using the Player 2 controller to move
// the entity's frame one step forward or back. This code is impossible
// to reach when playing the game, but can be triggered by poking the proper
// location in RAM to trigger the entity's state machine.

/**
 * Debug: Press SQUARE / CIRCLE on the second controller
 * to advance/rewind current animation frame
 */
FntPrint("charal %x\n", self->animCurFrame);
if (g_pads[1].pressed & PAD_SQUARE) {
    if (self->params) {
        break;
    }
    self->animCurFrame++;
    self->params |= 1;
} else {
    self->params = 0;
}
if (g_pads[1].pressed & PAD_CIRCLE) {
    if (!self->step_s) {
        self->animCurFrame--;
        self->step_s |= 1;
    }
} else {
    self->step_s = 0;
}
break;
