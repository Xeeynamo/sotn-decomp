// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no1.h"

// Likely copied out of DRA, unused in NO1
static void DebugShowWaitInfo(const char* msg) {
    static s32 g_DebugWaitInfoTimer;

    g_CurrentBuffer = g_CurrentBuffer->next;
    FntPrint(msg);
    if (g_DebugWaitInfoTimer++ & 4) {
        FntPrint("\no\n");
    }
    DrawSync(0);
    VSync(0);
    PutDrawEnv(&g_CurrentBuffer->draw);
    PutDispEnv(&g_CurrentBuffer->disp);
    FntFlush(-1);
}

static void DebugInputWait(const char* msg) {
    while (PadRead(0))
        DebugShowWaitInfo(msg);
    while (!PadRead(0))
        DebugShowWaitInfo(msg);
}

static AnimationFrame anim0[] = {
    POSE(128, 7, 0),
    POSE_LOOP(0),
};

static AnimationFrame anim1[] = {
    POSE(128, 8, 0),
    POSE_LOOP(0),
};

static AnimationFrame anim2[] = {
    POSE(128, 33, 0),
    POSE(32, 34, 0),
    POSE(32, 35, 0),
    POSE_LOOP(0),
};

static AnimationFrame anim3[] = {
    POSE(16, 36, 0),
    POSE(16, 37, 0),
    POSE(16, 38, 0),
    POSE_LOOP(0),
};

static AnimationFrame anim4[] = {
    POSE(128, 39, 0),
    POSE(16, 40, 0),
    POSE(32, 41, 0),
    POSE_LOOP(0),
};

static AnimationFrame anim5[] = {
    POSE(16, 40, 0), POSE(16, 41, 0), POSE(16, 42, 0), POSE(16, 43, 0),
    POSE(16, 42, 0), POSE(16, 43, 0), POSE(16, 41, 0), POSE_LOOP(0),
};

static AnimationFrame* anims0[] = {
    anim0, anim0, anim1, anim1, anim2, anim2, anim3, anim4,
};

static AnimationFrame* anims1[] = {
    anim0, anim1, anim1, anim2, anim2, anim2, anim3, anim4, anim0,
};

static AnimationFrame anim6[] = {
    POSE(7, 2, 0), POSE(7, 3, 0), POSE(7, 4, 0), POSE(7, 5, 0),
    POSE(7, 6, 0), POSE(4, 4, 0), POSE_LOOP(0),
};

static AnimationFrame anim7[] = {
    POSE(6, 48, 0), POSE(6, 49, 0), POSE(6, 50, 0), POSE(6, 51, 0),
    POSE(6, 52, 0), POSE(4, 50, 0), POSE_LOOP(0),
};

static AnimationFrame anim8[] = {
    POSE(136, 9, 0),  POSE(40, 10, 0), POSE(22, 9, 0),  POSE(24, 10, 0),
    POSE(8, 11, 0),   POSE(32, 12, 0), POSE(8, 11, 0),  POSE(24, 10, 0),
    POSE(16, 11, 0),  POSE(16, 12, 0), POSE(16, 13, 0), POSE(16, 14, 0),
    POSE(8, 15, 0),   POSE(8, 16, 0),  POSE(8, 15, 0),  POSE(8, 16, 0),
    POSE(8, 15, 0),   POSE(8, 16, 0),  POSE(8, 15, 0),  POSE(8, 16, 0),
    POSE(8, 15, 0),   POSE(8, 16, 0),  POSE(8, 15, 0),  POSE(8, 16, 0),
    POSE(136, 17, 0), POSE_END,
};

static AnimationFrame anim9[] = {
    POSE(129, 17, 0), POSE(16, 16, 0), POSE(16, 14, 0),
    POSE(16, 13, 0),  POSE(16, 12, 0), POSE(16, 11, 0),
    POSE(16, 10, 0),  POSE(129, 9, 0), POSE_END,
};

static AnimationFrame anim10[] = {
    POSE(6, 48, 0), POSE(6, 49, 0), POSE(6, 50, 0), POSE(6, 51, 0),
    POSE(6, 52, 0), POSE(4, 50, 0), POSE_END,
};

static AnimationFrame anim11[] = {
    POSE(129, 17, 0), POSE(16, 16, 0),  POSE(16, 23, 0),
    POSE(16, 22, 0),  POSE(16, 21, 0),  POSE(16, 20, 0),
    POSE(16, 19, 0),  POSE(129, 18, 0), POSE_END,
};

static AnimationFrame anim12[] = {
    POSE(136, 18, 0), POSE(40, 19, 0), POSE(22, 18, 0), POSE(24, 19, 0),
    POSE(8, 20, 0),   POSE(32, 21, 0), POSE(8, 20, 0),  POSE(24, 19, 0),
    POSE(16, 20, 0),  POSE(16, 21, 0), POSE(16, 22, 0), POSE(16, 23, 0),
    POSE(8, 15, 0),   POSE(8, 16, 0),  POSE(8, 15, 0),  POSE(8, 16, 0),
    POSE(8, 15, 0),   POSE(8, 16, 0),  POSE(8, 15, 0),  POSE(8, 16, 0),
    POSE(8, 15, 0),   POSE(8, 16, 0),  POSE(8, 15, 0),  POSE(8, 16, 0),
    POSE(136, 17, 0), POSE_END,
};

static AnimationFrame anim13[] = {
    POSE(129, 32, 0), POSE(16, 30, 0),  POSE(16, 29, 0),
    POSE(16, 28, 0),  POSE(16, 27, 0),  POSE(16, 26, 0),
    POSE(16, 25, 0),  POSE(129, 24, 0), POSE_END,
};

static AnimationFrame anim14[] = {
    POSE(136, 24, 0), POSE(40, 25, 0), POSE(22, 24, 0), POSE(24, 25, 0),
    POSE(8, 26, 0),   POSE(32, 27, 0), POSE(8, 26, 0),  POSE(24, 25, 0),
    POSE(16, 26, 0),  POSE(16, 27, 0), POSE(16, 28, 0), POSE(16, 29, 0),
    POSE(8, 30, 0),   POSE(8, 31, 0),  POSE(8, 30, 0),  POSE(8, 31, 0),
    POSE(8, 30, 0),   POSE(8, 31, 0),  POSE(8, 30, 0),  POSE(8, 31, 0),
    POSE(8, 30, 0),   POSE(8, 31, 0),  POSE(8, 30, 0),  POSE(8, 31, 0),
    POSE(136, 32, 0), POSE_END,
};

static AnimationFrame anim15[] = {
    POSE(128, 44, 0), POSE(32, 45, 0), POSE(16, 44, 0), POSE(32, 45, 0),
    POSE(16, 46, 0),  POSE(32, 47, 0), POSE(8, 46, 0),  POSE(64, 44, 0),
    POSE(32, 45, 0),  POSE(16, 44, 0), POSE(32, 45, 0), POSE(16, 46, 0),
    POSE(32, 47, 0),  POSE(8, 46, 0),  POSE(64, 44, 0), POSE(32, 45, 0),
    POSE(16, 44, 0),  POSE(32, 45, 0), POSE(16, 46, 0), POSE(32, 47, 0),
    POSE(8, 46, 0),   POSE(64, 44, 0), POSE(32, 45, 0), POSE(16, 44, 0),
    POSE(32, 45, 0),  POSE(16, 46, 0), POSE(32, 47, 0), POSE(8, 46, 0),
    POSE(64, 44, 0),  POSE(32, 45, 0), POSE(16, 44, 0), POSE_END,
};

static AnimationFrame anim16[] = {
    POSE(128, 44, 0), POSE(32, 45, 0), POSE(16, 44, 0),  POSE(32, 45, 0),
    POSE(16, 46, 0),  POSE(32, 45, 0), POSE(128, 44, 0), POSE(32, 45, 0),
    POSE(16, 44, 0),  POSE(32, 45, 0), POSE(16, 46, 0),  POSE(32, 45, 0),
    POSE(128, 44, 0), POSE(32, 45, 0), POSE(16, 44, 0),  POSE(32, 45, 0),
    POSE(16, 46, 0),  POSE(32, 45, 0), POSE(128, 44, 0), POSE(32, 45, 0),
    POSE(16, 44, 0),  POSE(32, 45, 0), POSE(16, 46, 0),  POSE(32, 45, 0),
    POSE(64, 44, 0),  POSE(32, 45, 0), POSE(16, 44, 0),  POSE_END,
};

static AnimationFrame anim17[] = {
    POSE(32, 44, 0), POSE(32, 45, 0), POSE(16, 44, 0), POSE(32, 45, 0),
    POSE(16, 46, 0), POSE(32, 45, 0), POSE_LOOP(0),
};

static AnimationFrame* anims2[] = {
    anim8, anim8, anim12, anim12, anim14, anim15, anim16, anim16,
};

static AnimationFrame* anims3[] = {
    anim9, anim11, anim11, anim13, anim13, NULL, NULL, NULL,
};

// Baby birds in the nest
void func_us_801B8430(Entity* self) {

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitCommon);
        self->flags &= ~(FLAG_DESTROY_IF_OUT_OF_CAMERA |
                         FLAG_DESTROY_IF_BARELY_OUT_OF_CAMERA);
        self->animSet = ANIMSET_OVL(1);
        self->zPriority = PLAYER.zPriority + 4;
        self->poseTimer = self->pose = 0;
        self->anim = anims0[g_CastleFlags[NO1_BIRD_CYCLE]];
        break;

    case 1:
        break;
    }
    g_api.UpdateAnim(NULL, NULL);
}

static s32 D_us_80181388 = 0;

// The bird life cycle at the bottom of NO1
void func_us_801B84E4(Entity* self) {
    s16 posX;

    FntPrint("tori_w:%02x\n", g_CastleFlags[NO1_BIRD_CYCLE]);
    FntPrint("obj_step:%02x\n", self->step);

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitCommon);
        self->flags |= FLAG_UNK_10000000;
        self->flags &= ~(FLAG_DESTROY_IF_OUT_OF_CAMERA |
                         FLAG_DESTROY_IF_BARELY_OUT_OF_CAMERA |
                         FLAG_UNK_20000000 | FLAG_UNK_02000000);
        if (g_CastleFlags[NO1_BIRD_CYCLE] == 8) {
            self->step = 0xFF;
        } else {
            self->ext.et_801B84E4.unk7C =
                self->posX.i.hi + g_Tilemap.scrollX.i.hi;
            if (g_CastleFlags[NO1_BIRD_CYCLE] >= 5) {
                self->ext.et_801B84E4.unk7C += 9;
            }
            self->ext.et_801B84E4.unk7E = self->ext.et_801B84E4.unk7C + 0x20;
            self->velocityX = FIX(-1.375);
            self->posY.i.hi -= 0x16;
            self->animSet = ANIMSET_OVL(1);
            self->zPriority = PLAYER.zPriority;
            self->poseTimer = self->pose = 0;
            self->anim = anim6;
        }
        break;

    case 1:
        self->posX.i.hi = 0x130;
        if (g_Tilemap.scrollY.i.hi >= 0x48) {
            self->step++;
        }
        break;

    case 2:
        self->posX.val += self->velocityX;
        posX = self->posX.i.hi + g_Tilemap.scrollX.i.hi;
        if ((posX - self->ext.et_801B84E4.unk7E) < 0x28) {
            self->velocityX += 0x600;
        }
        if (posX <= self->ext.et_801B84E4.unk7E) {
            self->poseTimer = self->pose = 0;
            self->anim = anim7;
            self->ext.et_801B84E4.unk80 = 0x90;
            if (g_CastleFlags[NO1_BIRD_CYCLE] == 7) {
                (self - 1)->anim = anim5;
                (self - 1)->poseTimer = (self - 1)->pose = 0;
                self->ext.et_801B84E4.unk80 = 0x100;
                g_api.PlaySfx(SFX_NO1_BIRD_CYCLE);
            }
            self->step++;
        }
        break;

    case 3:
        if (--self->ext.et_801B84E4.unk80 == 0) {
            self->velocityY = FIX(0.15625);
            self->velocityX = FIX(-0.5);
            self->step++;
            if (g_CastleFlags[NO1_BIRD_CYCLE] == 7) {
                self->velocityX = FIX(-1.375);
                self->step = 8;
                self->poseTimer = self->pose = 0;
                self->anim = anim6;
                self->zPriority = PLAYER.zPriority + 8;
                (self - 1)->anim = anims1[g_CastleFlags[NO1_BIRD_CYCLE]];
            }
        }
        break;

    case 4:
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        posX = self->posX.i.hi + g_Tilemap.scrollX.i.hi;
        if (posX <= self->ext.et_801B84E4.unk7C) {
            self->poseTimer = self->pose = 0;
            self->anim = anims2[g_CastleFlags[NO1_BIRD_CYCLE]];
            self->posY.i.hi = (self - 1)->posY.i.hi;
            if (g_CastleFlags[NO1_BIRD_CYCLE] == 2 ||
                g_CastleFlags[NO1_BIRD_CYCLE] == 3 ||
                g_CastleFlags[NO1_BIRD_CYCLE] == 4) {
                self->zPriority = PLAYER.zPriority + 8;
            }
            if (g_CastleFlags[NO1_BIRD_CYCLE] >= 5) {
                self->posY.i.hi -= 0x10;
            }
            self->step++;
        }
        break;

    case 5:
        if (self->poseTimer >= 0) {
            break;
        }
        self->step++;
        if (anims3[g_CastleFlags[NO1_BIRD_CYCLE]] != NULL) {
            self->poseTimer = self->pose = 0;
            self->anim = anims3[g_CastleFlags[NO1_BIRD_CYCLE]];
            if (g_CastleFlags[NO1_BIRD_CYCLE]) {
                self->zPriority = PLAYER.zPriority + 8;
            }
            break;
        }
    case 6:
        if (self->poseTimer < 0) {
            g_api.PlaySfx(SFX_WING_FLAP_A);
            D_us_80181388 = 0;
            self->step++;
            self->poseTimer = self->pose = 0;
            self->anim = anim10;
            self->posY.i.hi -= 20;
            if (g_CastleFlags[NO1_BIRD_CYCLE] >= 5) {
                self->posY.i.hi += 16;
            }
            self->zPriority = PLAYER.zPriority + 8;
            (self - 1)->anim = anims1[g_CastleFlags[NO1_BIRD_CYCLE]];
        }
        break;

    case 7:
        D_us_80181388++;
        if (D_us_80181388 < 49 && (D_us_80181388 % 16) == 0) {
            g_api.PlaySfx(SFX_WING_FLAP_A);
        }
        if (self->poseTimer < 0) {
            self->velocityX = FIX(-1.375);
            self->poseTimer = self->pose = 0;
            self->anim = anim6;
            self->step++;
        }
        break;

    case 8:
        D_us_80181388++;
        if (D_us_80181388 < 49 && (D_us_80181388 % 16) == 0) {
            g_api.PlaySfx(SFX_WING_FLAP_A);
        }
        self->posX.val += self->velocityX;
        if (self->posX.i.hi < -0x28) {
            g_CastleFlags[NO1_BIRD_CYCLE]++;
            if (g_CastleFlags[NO1_BIRD_CYCLE] == 9) {
                g_CastleFlags[NO1_BIRD_CYCLE] = 0;
            }
            self->step++;
        }
        break;

    default:
        self->animSet = 0;
        break;
    }
    g_api.UpdateAnim(NULL, NULL);
}

static SVECTOR v0 = {-10, -48, -20};
static SVECTOR v1 = {10, -48, -20};
static SVECTOR v2 = {-10, 48, -20};
static SVECTOR v3 = {10, 48, -20};

// Triggers in the bottom room of NO1
void func_us_801B8B00(Entity* self) {
    s16 offsetX;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitCommon);
        self->flags |= FLAG_UNK_10000000;
        self->flags &= ~(FLAG_DESTROY_IF_OUT_OF_CAMERA |
                         FLAG_DESTROY_IF_BARELY_OUT_OF_CAMERA |
                         FLAG_UNK_20000000 | FLAG_UNK_02000000);

        if (g_CastleFlags[NO1_BIRD_CYCLE] != 8) {
            self->step = 0xFF;
        } else {
            self->posY.i.hi -= 16;

            offsetX = -6;
            if (self->params) {
                offsetX = 6;
            }
            self->posX.i.hi += offsetX;

            self->animSet = ANIMSET_OVL(1);
            self->zPriority = PLAYER.zPriority;
            self->poseTimer = self->pose = 0;
            self->anim = anim17;

            if (self->params) {
                self->pose = 3;
            }
        }
        break;

    case 1:
        if (g_Tilemap.scrollY.i.hi >= 72) {
            if (self->params) {
                self->ext.bird.timer = 0x300;
            } else {
                self->ext.bird.timer = 0x200;
            }
            self->step++;
        }
        break;

    case 2:
        if (--self->ext.bird.timer == 0) {
            self->poseTimer = self->pose = 0;
            self->anim = anim10;
            self->posY.i.hi -= 4;
            g_api.PlaySfx(SFX_WING_FLAP_A);
            self->step++;
        }
        break;

    case 3:
        if (self->poseTimer < 0) {
            self->velocityX = FIX(-1.375);
            self->poseTimer = self->pose = 0;
            self->anim = anim6;
            self->step++;
        }
        break;

    case 4:
        self->posX.val += self->velocityX;
        if (self->posX.i.hi < -0x28) {
            if (self->params) {
                g_CastleFlags[NO1_BIRD_CYCLE] = 0;
            }
            self->step++;
        }
        break;

    default:
        self->animSet = 0;
        break;
    }

    g_api.UpdateAnim(NULL, NULL);
}

void func_us_801B8D30(Entity* self) {
    long p, flag;
    s32 primIndex;
    Primitive* prim;
    Entity* player;
    s16 dx, dy;
    SVECTOR rot;
    VECTOR trans;
    MATRIX matrix;

    player = &PLAYER;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        self->animSet = 0;
        self->animCurFrame = 0;

        primIndex = g_api.AllocPrimitives(PRIM_G4, 1);
        if (primIndex != -1) {
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            self->ext.et_801B8D30.prim = prim;
            PGREY(prim, 0) = 0x80;
            LOW(prim->r1) = LOW(prim->r0);
            LOW(prim->r2) = LOW(prim->r0);
            LOW(prim->r3) = LOW(prim->r0);
            prim->priority = 0x60;
            prim->drawMode = DRAW_UNK_40 | DRAW_TPAGE2 | DRAW_TPAGE |
                             DRAW_UNK02 | DRAW_TRANSP;
        } else {
            DestroyEntity(self);
            return;
        }
        break;

    case 1:
        dx = self->posX.i.hi - player->posX.i.hi;
        dy = self->posY.i.hi - player->posY.i.hi;
        dx -= 80;
        prim = self->ext.et_801B8D30.prim;
        prim->drawMode = DRAW_HIDE;

        if (abs(dx) < 16) {
            prim->drawMode = DRAW_UNK_40 | DRAW_TPAGE2 | DRAW_TPAGE |
                             DRAW_UNK02 | DRAW_TRANSP;
            self->ext.et_801B8D30.unk80 = dx * 64;
        }
        break;
    }

    prim = self->ext.et_801B8D30.prim;
    SetGeomScreen(0x200);

    rot.vx = 0;
    rot.vy = self->ext.et_801B8D30.unk80;
    rot.vz = ROT(33.75);
    RotMatrixYXZ(&rot, &matrix);

    trans.vx = 0;
    trans.vy = 0;
    trans.vz = 0x200;
    TransMatrix(&matrix, &trans);

    SetRotMatrix(&matrix);
    SetTransMatrix(&matrix);
    SetGeomOffset(self->posX.i.hi, self->posY.i.hi);
    RotAverage4(&v0, &v1, &v2, &v3, (long*)&prim->x0, (long*)&prim->x1,
                (long*)&prim->x2, (long*)&prim->x3, &p, &flag);
}
