// SPDX-License-Identifier: AGPL-3.0-or-later
extern Dialogue OVL_EXPORT(Dialogue);
extern s32 OVL_EXPORT(SkipCutscene);

void CutsceneSkip(Entity* self) {
    if (g_pads[0].tapped == PAD_START) {
        OVL_EXPORT(SkipCutscene) = true;
        g_api.FreePrimitives(self->primIndex);
        self->flags ^= FLAG_HAS_PRIMS;
        if (OVL_EXPORT(Dialogue).primIndex[1] != -1) {
            g_api.FreePrimitives(OVL_EXPORT(Dialogue).primIndex[1]);
        }
        if (OVL_EXPORT(Dialogue).primIndex[0] != -1) {
            g_api.FreePrimitives(OVL_EXPORT(Dialogue).primIndex[0]);
        }
        g_api.PlaySfx(SET_STOP_MUSIC);
        self->step = 1;
        self->step_s = 0;
    }
}
