// SPDX-License-Identifier: AGPL-3.0-or-later
extern s32 g_SkipCutscene;
extern Dialogue g_Dialogue;

void CutsceneSkip(Entity* self) {
    if (g_pads[0].tapped == PAD_START) {
        g_SkipCutscene = true;
        g_api.FreePrimitives(self->primIndex);
        self->flags ^= FLAG_HAS_PRIMS;
        if (g_Dialogue.primIndex[1] != -1) {
            g_api.FreePrimitives(g_Dialogue.primIndex[1]);
        }
        if (g_Dialogue.primIndex[0] != -1) {
            g_api.FreePrimitives(g_Dialogue.primIndex[0]);
        }
        g_api.PlaySfx(SET_STOP_MUSIC);
        self->step = 1;
        self->step_s = 0;
    }
}
