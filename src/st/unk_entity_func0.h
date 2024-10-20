// SPDX-License-Identifier: AGPL-3.0-or-later
void UnkEntityFunc0(u16 slope, s16 speed) {
    g_CurrentEntity->velocityX = rcos(slope) * speed / 16;
    g_CurrentEntity->velocityY = rsin(slope) * speed / 16;
}
