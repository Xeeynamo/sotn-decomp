// SPDX-License-Identifier: AGPL-3.0-or-later

#ifndef PROXIMITY_SFX_VOLUME
#error "PROXIMITY_SFX_VOLUME must be defined before including this file"
#endif

// Plays a sound with volume and pan based on the distance from the screen
// center. The sound gets quieter the farther the entity is from it.
static void PlayProximitySfx(s16 sfxId) {
    s32 yOffset;
    s16 vol;
    s16 pan;
    s32 xOffset;

    xOffset = g_CurrentEntity->posX.i.hi - 128;
    pan = (abs(xOffset) - 0x20) >> 5;
    if (pan > 8) {
        pan = 8;
    } else if (pan < 0) {
        pan = 0;
    }
    if (xOffset < 0) {
        pan = -pan;
    }

    vol = abs(xOffset) - 0x60;
    yOffset = abs(g_CurrentEntity->posY.i.hi - 128) - 112;
    if (yOffset > 0) {
        vol += yOffset;
    }
    if (vol < 0) {
        vol = 0;
    }
    vol = PROXIMITY_SFX_VOLUME - (vol >> 1);
    if (vol > 0) {
        g_api.PlaySfxVolPan(sfxId, vol, pan);
    }
}
