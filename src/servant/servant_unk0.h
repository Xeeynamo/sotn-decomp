// SPDX-License-Identifier: AGPL-3.0-or-later
s32 ServantUnk0(void) {
    if (g_StageId >= STAGE_RNO0 && g_StageId < STAGE_RNZ1_DEMO) {
        if (D_8003C708.flags == 0x22) {
            return 1;
        }
        if (D_8003C708.flags == FLAG_UNK_20) {
            return 0;
        }
        return 2;
    } else {
        if (D_8003C708.flags == 0x22) {
            return 0;
        }

        if (D_8003C708.flags == FLAG_UNK_20) {
            return 1;
        }
        return 2;
    }
}
