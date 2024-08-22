// SPDX-License-Identifier: AGPL-3.0-or-later
u8 GetAnglePointToEntityShifted(s32 x, s32 y) {
    s32 diffX = x - (u16)g_CurrentEntity->posX.i.hi;
    s32 diffY = y - (u16)g_CurrentEntity->posY.i.hi;
    return Ratan2Shifted(diffX, diffY);
}
