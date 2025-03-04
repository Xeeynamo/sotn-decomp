// SPDX-License-Identifier: AGPL-3.0-or-later

// Sets velocity based on an input speed, and the existing facing value
void SetSpeedX(s32 speed) {
    if (g_CurrentEntity->facingLeft == 1) {
        speed = -speed;
    }
    g_CurrentEntity->velocityX = speed;
}
