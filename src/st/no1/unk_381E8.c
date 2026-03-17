// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no1.h"

// Likely copied out of DRA. This code
// appears to go unused.
static s32 g_DebugWaitInfoTimer;

static void DebugShowWaitInfo(const char* msg) {
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

// Baby birds in the nest
extern AnimationFrame* D_us_80181000[];

void func_us_801B8430(Entity* self) {

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitCommon);
        self->flags &= ~(FLAG_DESTROY_IF_OUT_OF_CAMERA |
                         FLAG_DESTROY_IF_BARELY_OUT_OF_CAMERA);
        self->animSet = ANIMSET_OVL(1);
        self->zPriority = PLAYER.zPriority + 4;
        self->poseTimer = self->pose = 0;
        self->anim = D_us_80181000[g_CastleFlags[NO1_BIRD_CYCLE]];
        break;

    case 1:
        break;
    }
    g_api.UpdateAnim(NULL, NULL);
}

extern AnimationFrame D_us_80180FE0[];
extern AnimationFrame* D_us_80181020[];
extern AnimationFrame D_us_80181044[];
extern AnimationFrame D_us_80181060[];
extern AnimationFrame D_us_80181108[];
extern AnimationFrame* D_us_80181348[];
extern AnimationFrame* D_us_80181368[];
extern s32 D_us_80181388;

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
            self->anim = D_us_80181044;
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
            self->anim = D_us_80181060;
            self->ext.et_801B84E4.unk80 = 0x90;
            if (g_CastleFlags[NO1_BIRD_CYCLE] == 7) {
                (self - 1)->anim = D_us_80180FE0;
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
                self->anim = D_us_80181044;
                self->zPriority = PLAYER.zPriority + 8;
                (self - 1)->anim = D_us_80181020[g_CastleFlags[NO1_BIRD_CYCLE]];
            }
        }
        break;

    case 4:
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        posX = self->posX.i.hi + g_Tilemap.scrollX.i.hi;
        if (posX <= self->ext.et_801B84E4.unk7C) {
            self->poseTimer = self->pose = 0;
            self->anim = D_us_80181348[g_CastleFlags[NO1_BIRD_CYCLE]];
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
        if (D_us_80181368[g_CastleFlags[NO1_BIRD_CYCLE]] != NULL) {
            self->poseTimer = self->pose = 0;
            self->anim = D_us_80181368[g_CastleFlags[NO1_BIRD_CYCLE]];
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
            self->anim = D_us_80181108;
            self->posY.i.hi -= 20;
            if (g_CastleFlags[NO1_BIRD_CYCLE] >= 5) {
                self->posY.i.hi += 16;
            }
            self->zPriority = PLAYER.zPriority + 8;
            (self - 1)->anim = D_us_80181020[g_CastleFlags[NO1_BIRD_CYCLE]];
        }
        break;

    case 7:
        D_us_80181388++;
        if (D_us_80181388 < 0x31 && D_us_80181388 % 16 == 0) {
            g_api.PlaySfx(SFX_WING_FLAP_A);
        }
        if (self->poseTimer < 0) {
            self->velocityX = FIX(-1.375);
            self->poseTimer = self->pose = 0;
            self->anim = D_us_80181044;
            self->step++;
        }
        break;

    case 8:
        D_us_80181388++;
        if (D_us_80181388 < 0x31 && D_us_80181388 % 16 == 0) {
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

extern AnimationFrame D_us_80181044[];
extern AnimationFrame D_us_80181108[];
extern AnimationFrame D_us_8018132C[];

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
            self->anim = D_us_8018132C;

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
            self->anim = D_us_80181108;
            self->posY.i.hi -= 4;
            g_api.PlaySfx(SFX_WING_FLAP_A);
            self->step++;
        }
        break;

    case 3:
        if (self->poseTimer < 0) {
            self->velocityX = FIX(-1.375);
            self->poseTimer = self->pose = 0;
            self->anim = D_us_80181044;
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

extern SVECTOR D_us_8018138C;
extern SVECTOR D_us_80181394;
extern SVECTOR D_us_8018139C;
extern SVECTOR D_us_801813A4;

void func_us_801B8D30(Entity* self) {
    s32 primIndex;
    Primitive* prim;
    Entity* player;
    s32 p;
    s32 flag;
    s16 posX, posY;
    SVECTOR vector;
    VECTOR vector2;
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
        posX = self->posX.i.hi - player->posX.i.hi;
        posY = self->posY.i.hi - player->posY.i.hi;
        posX -= 80;
        prim = self->ext.et_801B8D30.prim;
        prim->drawMode = DRAW_HIDE;

        if (abs(posX) < 16) {
            prim->drawMode = DRAW_UNK_40 | DRAW_TPAGE2 | DRAW_TPAGE |
                             DRAW_UNK02 | DRAW_TRANSP;
            self->ext.et_801B8D30.unk80 = posX * 64;
        }
        break;
    }

    prim = self->ext.et_801B8D30.prim;
    SetGeomScreen(0x200);
    vector.vx = 0;
    vector.vy = self->ext.et_801B8D30.unk80;
    vector.vz = 0x180;
    RotMatrixYXZ(&vector, &matrix);

    vector2.vx = 0;
    vector2.vy = 0;
    vector2.vz = 0x200;
    TransMatrix(&matrix, &vector2);
    SetRotMatrix(&matrix);
    SetTransMatrix(&matrix);
    SetGeomOffset(self->posX.i.hi, self->posY.i.hi);
    RotAverage4(
        &D_us_8018138C, &D_us_80181394, &D_us_8018139C, &D_us_801813A4,
        (long*)&LOW(prim->x0), (long*)&LOW(prim->x1), (long*)&LOW(prim->x2),
        (long*)&LOW(prim->x3), (long*)&p, (long*)&flag);
}
