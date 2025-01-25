// SPDX-License-Identifier: AGPL-3.0-or-later
s32 GetSineScaled(u8 arg0, s16 arg1) {
    s32 sine = g_SineTable[arg0];
    return sine * arg1;
}
