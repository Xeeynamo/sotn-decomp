// SPDX-License-Identifier: AGPL-3.0-or-later

// check if "sit" has been triggered
static s32 func_us_801BEDD8(Entity* self) {
    s16 offsetX;
    s16 offsetY;

    if (g_pads[0].pressed != PAD_UP) {
        return 0;
    }

    offsetX = self->posX.i.hi - PLAYER.posX.i.hi;
    offsetY = self->posY.i.hi - PLAYER.posY.i.hi;

    if (offsetY > 4 || offsetY < -4) {
        return 0;
    }

    if (offsetX > 4 || offsetX < -4) {
        return 0;
    }

    return 1;
}

void EntityChair(Entity* self) {
    s16 offsetX;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitCommon);
        break;

    case 1:
        if (func_us_801BEDD8(self) != 0) {
            g_Player.demo_timer = 10;
            g_Player.padSim = PAD_UP;
            g_Player.unk14 = self->params;

            self->step++;
        }
        break;

    case 2:
        g_Player.unk14 = self->params;
        offsetX = self->posX.i.hi - PLAYER.posX.i.hi;
        if (offsetX > 0) {
            PLAYER.posX.i.hi++;
        }
        if (offsetX < 0) {
            PLAYER.posX.i.hi--;
        }
        if (offsetX == 0) {
            self->step++;
        }
        break;

    case 3:
        g_Player.unk14 = self->params;
        if (PLAYER.poseTimer < 0) {
            self->ext.chair.unk0 = 0xA00;
            self->step++;
        }

        if (PLAYER.step != 0 || PLAYER.step_s != 4) {
            self->step = 1;
        }
        break;

    case 4:
        g_Player.unk14 = self->params;
        if (PLAYER.step != 0 || PLAYER.step_s != 4) {
            self->step = 1;
        }
        break;
    }
    g_api.UpdateAnim(NULL, NULL);

#ifdef CHAIR_DEBUG
    FntPrint("obj_step:%02x\n", self->step);
    FntPrint("pl_step:%02x,pl_step_s:%02x\n", PLAYER.step, PLAYER.step_s);
#endif
}

static AnimationFrame D_us_80180F8C[] = {
    {8, 8}, {8, 9}, {8, 10}, {8, 11}, {-1, 0}};

void func_us_801B81E8(Entity* self) {
    if (self->ext.chair.unkEntity->step != 4) {
        DestroyEntity(self);
        return;
    }
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitCommon);
        self->animSet = ANIMSET_OVL(2);
        self->velocityY = FIX(-3.0 / 8.0);
        self->velocityX = FIX(0.25);
        if (self->facingLeft) {
            self->velocityX = -self->velocityX;
        }
        self->unk5A = 0x20;
        self->palette = PAL_FLAG(0x19F);
        self->anim = D_us_80180F8C;
        self->pose = 0;
        self->poseTimer = 0;
        self->facingLeft = false;
        self->posY.i.hi -= 16;
        self->posX.val += self->velocityX << 5;
        break;

    case 1:
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        if (self->poseTimer < 0) {
            DestroyEntity(self);
            return;
        }
        break;
    }
    g_api.UpdateAnim(NULL, NULL);
}
