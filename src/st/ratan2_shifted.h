// SPDX-License-Identifier: AGPL-3.0-or-later
u8 Ratan2Shifted(s16 x, s16 y) { return (ratan2(y, x) >> 4) + 0x40; }
