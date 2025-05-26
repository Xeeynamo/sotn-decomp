// SPDX-License-Identifier: AGPL-3.0-or-later

static u8 thunder_anim[] = {4, 23, 3, 24, 2, 25, 2, 26, 255, 0, 0, 0};

void EntityLightningThunder(Entity* self) {
    s32 sfxPan;

    if (!self->step) {
        InitializeEntity(g_EInitStInteractable);
        self->zPriority = 0x2A;
        self->flags &= ~FLAG_POS_CAMERA_LOCKED;
        self->facingLeft = Random() & 1;
        sfxPan = (self->posX.i.hi >> 0x4) - 8;
        g_api.PlaySfxVolPan(SFX_THUNDER_B, 0x40, sfxPan);
    }
    if (AnimateEntity(thunder_anim, self) == 0) {
        DestroyEntity(self);
    }
}

extern s16 cloudPos[][2] = {{0x88, 0x6C}, {0xC8, 0x30}, {0x30, 0x44}};

// When lightning strikes, we get a bright bolt, but it is against a cloud
// as a background. It's subtle and hard to see, but it's there.
void EntityLightningCloud(Entity* self) {
    if (!self->step) {
        InitializeEntity(g_EInitStInteractable);
        self->zPriority = 0x29;
        self->flags &= ~FLAG_POS_CAMERA_LOCKED;
        // There are 3 shapes of cloud, this picks which one.
        self->animCurFrame = self->params + 0x22;
        self->posX.i.hi = cloudPos[self->params][0];
        self->posY.i.hi = cloudPos[self->params][1];
        self->ext.backgroundLightning.timer = 5;
    }

    if (!--self->ext.backgroundLightning.timer) {
        DestroyEntity(self);
    }
}
