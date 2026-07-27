// SPDX-License-Identifier: AGPL-3.0-or-later

extern EInit g_EInitImpSmoke;
extern u8 anim_imp_smoke[];

// Smoke puff shown above and behind Alucard while an imp jams him.
void EntityImpSmoke(Entity* self) {
    Entity* player;

    if (!self->step) {
        InitializeEntity(g_EInitImpSmoke);
        self->zPriority = g_unkGraphicsStruct.g_zEntityCenter + 4;
        player = &PLAYER;
        self->posX.i.hi = player->posX.i.hi;
        self->posY.i.hi = player->posY.i.hi - 0x18;
        if (player->facingLeft) {
            self->posX.i.hi -= 6;
        } else {
            self->posX.i.hi += 6;
        }
        g_api.PlaySfx(SFX_BONE_THROW);
    }
    self->posY.val -= FIX(0.5);
    if (AnimateEntity(anim_imp_smoke, self) == 0) {
        DestroyEntity(self);
    }
}
