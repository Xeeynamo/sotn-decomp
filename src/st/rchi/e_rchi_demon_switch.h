// SPDX-License-Identifier: AGPL-3.0-or-later
void EntityDemonSwitch(Entity* self) {
    switch (self->step) {
    case 0:
        InitializeEntity(D_us_80180648);

        self->animCurFrame = 3;
        self->hitPoints = 32767;
        self->hitboxState = 3;
        self->hitboxWidth = 6;
        self->hitboxHeight = 8;

        if (g_CastleFlags[RCHI_DEMON_SWITCH]) {
            self->animCurFrame = 4;
        }
        /* fall through */
    case 1:
        if (self->hitParams == 7) {
            g_api.PlaySfx(SFX_ANIME_SWORD_B);
            g_CastleFlags[RCHI_DEMON_SWITCH] = 1;
            g_api_RevealSecretPassageAtPlayerPositionOnMap(RCHI_DEMON_SWITCH);
            self->animCurFrame = 4;
            self->step++;
        }
        break;
    }
}
