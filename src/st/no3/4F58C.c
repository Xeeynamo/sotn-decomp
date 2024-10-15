// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no3.h"
#include "sfx.h"

static void func_801CF58C(Entity* self) {
    self->velocityX = 0;
    self->ext.warg.unk86 = 0x100;
    SetStep(6);
    g_api.PlaySfx(SE_WARG_GROWL);
    self->ext.warg.unk80 = 0x20;
}

void func_801CF5E0(Entity* self) {
    s16 temp_v0;

    if (self->facingLeft == GetSideToPlayer()) {
        SetStep(5);
        return;
    }

    if (self->ext.warg.unk86 == 0) {
        func_801CF58C(self);
        return;
    }

    temp_v0 = self->ext.warg.unk84 - self->posX.i.hi - g_Tilemap.scrollX.i.hi;

    if (temp_v0 > 16) {
        SetStep(3);
        if (self->facingLeft != 0) {
            self->ext.warg.unk7C = 0;
        } else {
            self->ext.warg.unk7C = 1;
        }
    } else if (temp_v0 < -16) {
        SetStep(3);
        if (self->facingLeft != 0) {
            self->ext.warg.unk7C = 1;
        } else {
            self->ext.warg.unk7C = 0;
        }
    } else {
        SetStep(7);
    }

    self->ext.warg.unk80 = 0;
    self->ext.warg.unk82 = 32;
}

// duplicate of func_801CC90C in this file
void func_801CF6D8(Entity* arg0) {
    s16 temp_v0_2;
    s16 temp_v1;
    s16 temp_v0;

    temp_v0 = GetDistanceToPlayerX();
    temp_v1 = arg0->ext.warg.unk86;
    if (temp_v1 != 0) {

        if ((u32)(temp_v0) < 0x60) {
            temp_v0_2 = temp_v1 - 2;
            arg0->ext.warg.unk86 = temp_v0_2;
            if (temp_v0_2 < 0) {
                arg0->ext.warg.unk86 = 0;
            }
        } else {
            arg0->ext.warg.unk86 = (temp_v1 - 1);
        }
    }
}

extern u16 D_80180B9C;
extern u8 D_801830BC;
extern u8 D_801830DC;
extern u8 D_801830FC;
extern u8 D_80183130;
extern u8 D_80183148;
extern u8 D_80183178;
extern u8 D_80183180;
extern u8 D_801831A0;
extern u8 D_801831FC;
extern u8 D_80183204;
extern s16 D_80183274[];
extern u16 D_8018327C[];
extern u32 D_8018328C[];
extern u32 D_801832A4[];
extern u16 D_801832EC[];

void EntityWarg(Entity* self) {
    DR_ENV* dr_env;
    Tilemap* gTilemap;
    Entity* otherEnt;
    Primitive* prim;
    s16* hitboxPtr;
    u16 switchTemp;
    u8 animResult;
    s16 xVar;
    s32 primIndex;
    EnemyDef* enemy;
    DRAWENV drawEnv;
    RECT rect = (RECT){
        .x = 0,
        .y = 0x100,
        .w = 0x80,
        .h = 0x80,
    };

    gTilemap = &g_Tilemap;
    switchTemp = self->step;
    if (self->flags & FLAG_DEAD) {
        if (switchTemp != 11) {
            if (!(self->animCurFrame < 0x2B || self->animCurFrame > 0x30)) {
                self->facingLeft ^= 1;
            }
            self->velocityX = 0;
            self->velocityY = 0;
            self->ext.warg.unk88 = self->posX.i.hi + gTilemap->scrollX.i.hi;
            self->ext.warg.unk8A = self->posY.i.hi + gTilemap->scrollY.i.hi;
            g_api.PlaySfx(SFX_STUTTER_EXPLODE_A);
            SetStep(11);
        }
    } else if (self->hitFlags & 0xF) {
        if (self->ext.warg.unk86 >= 0x10) {
            self->ext.warg.unk86 /= 2;
        }
        if (switchTemp == 2 || switchTemp == 3 || switchTemp == 7) {
            SetStep(10);
        }
    }
    switchTemp = self->step;
    switch (switchTemp) {
    case 0:
        otherEnt = self + 1;
        self->unk60 = otherEnt;
        CreateEntityFromCurrentEntity(E_ID_4B, otherEnt);
        otherEnt->unk5C = self;
        InitializeEntity(&D_80180B9C);
        otherEnt->unk60 = self;
        self->facingLeft = (GetSideToPlayer() ^ 1) & 1;
        if (self->facingLeft) {
            self->posX.i.hi -= 0x20;
        } else {
            self->posX.i.hi += 0x20;
        }
        self->ext.warg.unk86 = 0x40;
        break;
    case 1:
        AnimateEntity(&D_801830FC, self);
        if (UnkCollisionFunc3(D_8018327C) & 1) {
            SetStep(2);
            self->ext.warg.unk84 = self->posX.i.hi + gTilemap->scrollX.i.hi;
        }
        break;
    case 2:
        AnimateEntity(&D_801830FC, self);
        if (GetDistanceToPlayerX() < 0x80 || self->hitFlags) {
            SetStep(7);
        }
        break;
    case 3:
        func_801CF6D8(self);
        xVar = self->ext.warg.unk84 - self->posX.i.hi - gTilemap->scrollX.i.hi;
        if (self->ext.warg.unk80) {
            self->ext.warg.unk80 -= 1;
            self->animFrameDuration = 0;
            break;
        }
        if (!self->ext.warg.unk7C) {
            animResult = AnimateEntity(&D_801830BC, self);
            if (!animResult || (animResult & 0x80)) {
                animResult = self->animFrameIdx - 1;
                if (self->facingLeft) {
                    self->velocityX = D_8018328C[animResult];
                    if (xVar < -0x10) {
                        self->ext.warg.unk7C = 1;
                        self->animFrameIdx = 7 - self->animFrameIdx;
                        self->ext.warg.unk80 = 0x10;
                    }
                } else {
                    self->velocityX = -D_8018328C[animResult];
                    if (xVar > 0x10) {
                        self->ext.warg.unk7C = 1;
                        self->animFrameIdx = 7 - self->animFrameIdx;
                        self->ext.warg.unk80 = 0x10;
                    }
                }
            }
        } else {
            animResult = AnimateEntity(&D_801830DC, self);
            if (animResult != 1) {
                animResult = self->animFrameIdx - 1;
                if (self->facingLeft) {
                    self->velocityX = -D_801832A4[animResult];
                    if (xVar > 0x10) {
                        self->ext.warg.unk7C = 0;
                        self->animFrameIdx = 7 - self->animFrameIdx;
                        self->ext.warg.unk80 = 0x10;
                    }
                } else {
                    self->velocityX = D_801832A4[animResult];
                    if (xVar < -0x10) {
                        self->ext.warg.unk7C = 0;
                        self->animFrameIdx = 7 - self->animFrameIdx;
                        self->ext.warg.unk80 = 0x10;
                    }
                }
            }
        }
        UnkCollisionFunc2(D_80183274);
        if (self->ext.warg.unk82) {
            --self->ext.warg.unk82;
            break;
        }
        if ((self->facingLeft == GetSideToPlayer()) & 1) {
            SetStep(5);
            break;
        }
        if (!self->ext.warg.unk86) {
            func_801CF58C(self);
            break;
        }
        if (xVar < 0x10 && xVar > -0x10) {
            self->velocityX = 0;
            SetStep(7);
            break;
        }
        break;
    case 5:
        func_801CF6D8(self);
        if (!AnimateEntity(&D_80183130, self)) {
            self->facingLeft ^= 1;
            self->animCurFrame = 0xE;
            func_801CF5E0(self);
        }
        break;
    case 6:
        switch (self->step_s) {
        case 0:
            AnimateEntity(&D_80183178, self);
            if (!--self->ext.warg.unk80) {
                SetSubStep(1);
            }
            break;
        case 1:
            otherEnt = self + 1;
            animResult = AnimateEntity(&D_80183148, self);
            if (self->velocityX) {
                if (self->velocityX < 0) {
                    self->velocityX += FIX(0.375);
                } else {
                    self->velocityX -= FIX(0.375);
                }
            } else {
                otherEnt->attackElement = self->attackElement;
                otherEnt->attack = self->attack;
            }

            if (animResult & 0x80 && self->animFrameIdx == 7) {
                if (self->facingLeft) {
                    self->velocityX = FIX(6.0);
                } else {
                    self->velocityX = FIX(-6.0);
                }
                g_api.PlaySfx(SFX_UNK_782);
                enemy = &g_api.enemyDefs[176];
                otherEnt->attackElement = enemy->attackElement;
                otherEnt->attack = enemy->attack;
            }
            UnkCollisionFunc2(D_80183274);
            if (!animResult) {
                func_801CF5E0(self);
            }
        }
        break;
    case 7:
        self->ext.warg.unk80 += 1;
        func_801CF6D8(self);
        AnimateEntity(&D_80183180, self);
        if (self->ext.warg.unk82) {
            self->ext.warg.unk82 -= 1;
            break;
        }
        if (!(self->facingLeft ^ GetSideToPlayer())) {
            SetStep(5);
            break;
        }
        if (!self->ext.warg.unk86) {
            func_801CF58C(self);
        }
        break;
    case 8:
        if (!AnimateEntity(&D_801831A0, self)) {
            func_801CF5E0(self);
        }
        break;
    case 10:
        func_801CF6D8(self);
        switch (self->step_s) {
        case 0:
            SetSubStep(1);
            g_api.PlaySfx(SFX_UNK_781);
            if (self->facingLeft) {
                self->velocityX = FIX(-2.0);
            } else {
                self->velocityX = FIX(2.0);
            }
            break;
        case 1:
            UnkCollisionFunc2(D_80183274);
            if (self->velocityX) {
                if (self->facingLeft) {
                    self->velocityX += FIX(0.125);
                    EntityExplosionVariantsSpawner(
                        self, 1, 1, -0x20, 0x26, (Random() & 3) + 1, -4);
                    EntityExplosionVariantsSpawner(
                        self, 1, 1, 2, 0x26, (Random() & 3) + 1, -4);
                } else {
                    self->velocityX -= FIX(0.125);
                    EntityExplosionVariantsSpawner(
                        self, 1, 1, -2, 0x26, (Random() & 3) + 1, 4);
                    EntityExplosionVariantsSpawner(
                        self, 1, 1, 0x20, 0x26, (Random() & 3) + 1, 4);
                }
            }
            if (!AnimateEntity(&D_801831FC, self)) {
                SetSubStep(2);
            }
            break;
        case 2:
            if (!AnimateEntity(&D_80183204, self)) {
                func_801CF5E0(self);
            }
        }
        break;
    case 11:
        if (++self->ext.warg.unk80 & 1) {
            otherEnt = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (otherEnt != NULL) {
                CreateEntityFromCurrentEntity(E_WARG_EXP_TRANSP, otherEnt);
                // Is this divide?
                otherEnt->params =
                    ((g_unkGraphicsStruct.g_zEntityCenter - (Random() & 7) - 8)
                     << 8) +
                    1;
                otherEnt->posX.i.hi =
                    self->ext.warg.unk88 - gTilemap->scrollX.i.hi;
                otherEnt->posY.i.hi =
                    self->ext.warg.unk8A - gTilemap->scrollY.i.hi;
                if (self->facingLeft) {
                    otherEnt->posX.i.hi += (((Random() & 0xF) - 8) * 8);
                } else {
                    otherEnt->posX.i.hi += (((Random() & 0xF) - 7) * 8);
                }
                otherEnt->posY.i.hi += (((Random() & 7) - 2) * 8);
            }
        }
        switch (self->step_s) {
        case 0:
            if (UnkCollisionFunc3(D_8018327C) & 1) {
                self->drawFlags = FLAG_DRAW_UNK8;
                self->unk6C = 0x80;
                SetSubStep(1);
            }
            break;
        case 1:
            AnimateEntity(&D_801831A0, self);
            self->unk6C -= 2;
            if (self->unk6C == 0x40) {
                g_api.PlaySfx(SFX_UNK_780);
            }
            if (self->unk6C) {
                break;
            }

            self->palette = 0x15F;
            self->unk6C = 0x80;
            primIndex = g_api.AllocPrimitives(4, 3);
            // That's weird, it should do == -1, right?
            if (!primIndex) {
                DestroyEntity(self);
                DestroyEntity(self + 1);
                return;
            }

            self->primIndex = primIndex;
            self->flags |= FLAG_HAS_PRIMS;
            prim = &g_PrimBuf[primIndex];
            dr_env = g_api.func_800EDB08((POLY_GT4*)prim);

            if (dr_env != NULL) {
                prim->type = PRIM_ENV;
                prim->priority = 0x3F;
                prim->drawMode = DRAW_DEFAULT;

                // The bgtz here is due to loading everything from the draw
                drawEnv = g_CurrentBuffer->draw;
                drawEnv.isbg = 1;
                drawEnv.r0 = drawEnv.g0 = drawEnv.b0 = 0;
                drawEnv.clip = rect;
                drawEnv.ofs[0] = 0;
                drawEnv.ofs[1] = 0x100;
#ifdef VERSION_PSP
                drawEnv.dtd = 0;
#endif
                SetDrawEnv(dr_env, &drawEnv);
            } else {
                DestroyEntity(self);
                DestroyEntity(self + 1);
                return;
            }
            prim = prim->next;
            dr_env = g_api.func_800EDB08((POLY_GT4*)prim);
            if (dr_env != NULL) {
                prim->type = PRIM_ENV;
                prim->priority = 0x41;
                prim->drawMode = DRAW_UNK_800;

            } else {
                DestroyEntity(self);
                DestroyEntity(self + 1);
                return;
            }
            prim = prim->next;
#ifdef VERSION_PSP
            prim->tpage = 0x1110;
#endif
#ifdef VERSION_US
            prim->tpage = 0x110;
#endif
            prim->u0 = prim->u2 = 0;
            prim->u1 = prim->u3 = 0x80;
            prim->v0 = prim->v1 = 0x10;
            prim->v2 = prim->v3 = 0x70;
            prim->x0 = prim->x2 = self->posX.i.hi - 0x40;
            prim->x1 = prim->x3 = prim->x0 + 0x80;
            prim->y0 = prim->y1 = self->posY.i.hi - 0x30;
            prim->y2 = prim->y3 = prim->y0 + 0x60;
            prim->priority = self->zPriority;
            prim->drawMode =
                DRAW_UNK_40 | DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;
            self->posX.i.hi = 0x40;
            self->posY.i.hi = 0x40;
            self->zPriority = 0x40;
            self->step_s += 1;
            break;
        case 2:
            AnimateEntity(&D_801831A0, self);
            self->posX.i.hi = 0x40;
            self->posY.i.hi = 0x40;
            self->zPriority = 0x40;
            self->unk6C -= 2;
            if (!self->unk6C) {
                DestroyEntity(self);
                DestroyEntity(self + 1);
                return;
            }
            break;
        }
        break;
    // The switch statement expects a 12th case, but there's nothing there
    case 12:
        break;
    }

    switchTemp = self->animCurFrame;
    if (switchTemp) {
        if (self->params) {
            if (switchTemp >= 0x56) {
                switchTemp -= 0x39;
            } else if (switchTemp >= 0x39) {
                switchTemp -= 0x39;
            } else {
                switchTemp = 0xD;
            }
        } else {
            if (switchTemp >= 0x60) {
                switchTemp -= 0x30;
            } else {
                --switchTemp;
            }
        }

        hitboxPtr = &(D_801832EC)[switchTemp * 8];
        self->hitboxOffX = *hitboxPtr++;
        self->hitboxOffY = *hitboxPtr++;
        self->hitboxWidth = *hitboxPtr++;
        self->hitboxHeight = *hitboxPtr;
    }
}

// func_psp_09254348
void EntityUnkId4B(Entity* self) {
    u16 lastAnimFrame;
    Entity* previous;
    s16* hitboxPtr;

    previous = self - 1;

    if (!self->step) {
        InitializeEntity(&D_80180B9C);
        self->animCurFrame = 0;
        self->hitPoints = 0x7FFF;
    }

    self->posX.i.hi = previous->posX.i.hi;
    self->posY.i.hi = previous->posY.i.hi;
    self->facingLeft = previous->facingLeft;
    lastAnimFrame = previous->animCurFrame;

    if (lastAnimFrame) {

        if (self->params) {

            if (lastAnimFrame >= 109) {
                lastAnimFrame -= 108;
            } else if (lastAnimFrame >= 82) {
                lastAnimFrame -= 62;
            } else if (lastAnimFrame >= 76) {
                lastAnimFrame -= 59;
            } else if (lastAnimFrame >= 63) {
                lastAnimFrame -= 56;
            } else if (lastAnimFrame >= 51) {
                lastAnimFrame -= 50;
            } else {
                lastAnimFrame -= 49;
            }
            hitboxPtr = &D_801836BC[lastAnimFrame * 8];

        } else {
            if (previous->params) {
                if (lastAnimFrame >= 86 || lastAnimFrame >= 57) {
                    lastAnimFrame -= 57;
                } else {
                    lastAnimFrame = 13;
                }
            } else if (lastAnimFrame >= 96) {
                lastAnimFrame -= 48;
            } else {
                lastAnimFrame -= 1;
            }
            hitboxPtr = &D_801832EC[lastAnimFrame * 8];
        }

        hitboxPtr = hitboxPtr + 4;
        self->hitboxOffX = *hitboxPtr++;
        self->hitboxOffY = *hitboxPtr++;
        self->hitboxWidth = *hitboxPtr++;
        self->hitboxHeight = *hitboxPtr;
    }
}

// A single "puff" of the warg explosion animation, transparent
void EntityWargExplosionPuffTransparent(Entity* entity) {
    u32 temp_v0;

    if (entity->step == 0) {
        InitializeEntity(g_EInitParticle);
        entity->animSet = ANIMSET_DRA(14);
        entity->unk5A = 0x79;
        entity->palette = 0xD0;
        entity->drawMode = DRAW_TPAGE2 | DRAW_TPAGE;
        entity->drawFlags = FLAG_DRAW_UNK8;
        entity->animFrameIdx = 0;
        entity->animFrameDuration = 0;
        entity->unk6C = 0x60;
        temp_v0 = entity->params & 0xFF00;
        if (temp_v0 != 0) {
            entity->zPriority = temp_v0 >> 8;
        }
        entity->velocityY += 0xFFFF0000;
        return;
    }
    entity->posY.val += entity->velocityY;
    if (AnimateEntity(D_8018383C, entity) == 0) {
        DestroyEntity(entity);
    }
}

#include "../popup.h"
