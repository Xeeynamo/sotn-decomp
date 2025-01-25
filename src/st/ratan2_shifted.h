// SPDX-License-Identifier: AGPL-3.0-or-later
u8 Ratan2Shifted(s16 x, s16 y) {
    u8 angle = ratan2(y, x) >> 4;
    return angle + 0x40;
}
