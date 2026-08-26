// SPDX-License-Identifier: AGPL-3.0-or-later
void func_us_8019B5A4(Entity* self) {
    Entity* prev;

    if (g_RcenShaftFlags & 4) {
        if (self->step != 2) {
            SetStep(2);
        }
    }

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_80180570);
        self->blendMode = BLEND_ADD | BLEND_TRANSP;
        /* fall through */
    case 1:
        AnimateEntity(D_us_801807D0, self);
        prev = self - 1;
        self->posX.i.hi = prev->posX.i.hi;
        self->posY.i.hi = prev->posY.i.hi;
        if (!(g_Timer & 0x7F)) {
            func_us_8019AA04(0x6E6);
        }
        break;

    case 2:
        AnimateEntity(D_us_80180800, self);
        if (!self->poseTimer && self->pose == 0xA) {
            PlaySfxPositional(SFX_SHAFT_ORB_BREAK);
        }
        prev = self - 1;
        self->posX.i.hi = prev->posX.i.hi;
        self->posY.i.hi = prev->posY.i.hi;
        if (g_RcenShaftFlags & 8) {
            DestroyEntity(self);
        }
        break;
    }
}
