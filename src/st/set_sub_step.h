// SPDX-License-Identifier: AGPL-3.0-or-later
void SetSubStep(u8 step_s) {
    g_CurrentEntity->step_s = step_s;
    g_CurrentEntity->pose = 0;
    g_CurrentEntity->animFrameDuration = 0;
}
