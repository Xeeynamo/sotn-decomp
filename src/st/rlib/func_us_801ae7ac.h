// SPDX-License-Identifier: AGPL-3.0-or-later

extern EInit g_EInitInteractable;
extern u8 D_us_80180824[];
extern u8 D_us_8018082C[];

void func_us_801AE7AC_from_lib(Entity* self) {
    Entity* breakable;

    if (!self->step) {
        InitializeEntity(g_EInitInteractable);
        self->blendMode = BLEND_TRANSP | BLEND_ADD;
        self->animSet = ANIMSET_OVL(2);
    }

    if (!self->params) {
        AnimateEntity(D_us_80180824, self);
    } else {
        AnimateEntity(D_us_8018082C, self);
    }

    breakable = self - 1;
    if (breakable->entityId != E_BREAKABLE) {
        if (!self->params) {
            self->animCurFrame = 0xD;
        } else {
            self->animCurFrame = 0xE;
        }
    }
}
