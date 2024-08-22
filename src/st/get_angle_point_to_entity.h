// SPDX-License-Identifier: AGPL-3.0-or-later
u16 GetAnglePointToEntity(s32 x, s32 y) {
    s16 diffX = x - (u16)g_CurrentEntity->posX.i.hi;
    s16 diffY = y - (u16)g_CurrentEntity->posY.i.hi;
    return ratan2(diffY, diffX);
}
