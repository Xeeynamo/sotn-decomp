// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no0.h"

extern u16 D_us_80180BD8[];
extern u16 D_us_80180BDE[];
extern u16 D_us_8018234C[];
extern u16 D_us_80182354[];
extern u8 D_us_80182364[];
extern u8 D_us_80182390[];
extern u8 D_us_801823A0[];
extern u8 D_us_801823B0[];
extern u8 D_us_801823B8[];
extern u8 D_us_801823C4[];
extern u8 D_us_801823E4[];
extern u8 D_us_801823F4[];
extern u8 D_us_8018243C[];
extern u16 D_us_80182454[];

// Main Cthulu entity
void func_us_801D9264(Entity* self) {
    RECT clipRect;
    DRAWENV drawEnv;
    DR_ENV* dr_env;
    Entity* newEntity;
    Primitive* prim;
    s16 angle;
    s32 i;
    s32 posX;
    s32 posY;
    s32 colRet;
    s32 primIndex;
    u16 temp_v0_13;
    u16 temp_v0_15;

    if ((g_Player.status & PLAYER_STATUS_UNK40000) && (self->step < 9)) {
        SetStep(9);
    }
    if ((self->flags & FLAG_DEAD) && (self->step < 10)) {
        self->hitboxState = 0;
        PlaySfxPositional(0x757);
        SetStep(10);
    }
    switch (self->step) {
    case 0:
        InitializeEntity(&D_us_80180BD8);
        self->animCurFrame = 1;
        /* fallthrough */
    case 1:
        if (UnkCollisionFunc3(D_us_80182354) & 1) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            SetStep(2);
        }
        break;
    case 2:
        if (self->step_s == 0) {
            self->ext.et_801D9264.timer = 0x40;
            self->step_s++;
        }
        AnimateEntity(D_us_80182390, self);
        if (self->ext.et_801D9264.timer == 0x20) {
            self->facingLeft ^= 1;
        }
        if ((self->facingLeft == ((GetSideToPlayer() & 1) ^ 1)) &&
            (GetDistanceToPlayerX() < 0x48)) {
            SetStep(5);
        }
        if (!--self->ext.et_801D9264.timer) {
            SetStep(3);
        }
        break;
    case 3:
        switch (self->step_s) {
        case 0:
            if (!AnimateEntity(D_us_801823E4, self)) {
                self->ext.et_801D9264.y =
                    self->posY.i.hi + g_Tilemap.scrollY.i.hi - 0x20;
                SetSubStep(1);
            }
            break;
        case 1:
            self->velocityY = FIX(-4);
            self->velocityX = 0;
            self->animCurFrame = 0x15;
            self->step_s++;
            /* fallthrough */
        case 2:
            MoveEntity();
            self->velocityY += FIX(3.0 / 16);
            posY = self->posY.i.hi + g_Tilemap.scrollY.i.hi;
            posY -= self->ext.et_801D9264.y;
            if ((posY <= 0) || (self->velocityY > 0)) {
                self->step_s++;
            }
            break;
        case 3:
            AnimateEntity(D_us_801823B8, self);
            if (self->animFrameIdx == 3 && self->animFrameDuration == 0) {
                PlaySfxPositional(SFX_WING_FLAP_A);
            }
            posY = self->posY.i.hi + g_Tilemap.scrollY.i.hi;
            posY -= self->ext.et_801D9264.y;
            if (posY == 0) {
                self->ext.et_801D9264.timer = 0x80;
                self->velocityY = 0;
                self->step_s++;
            } else if (posY < 0) {
                self->posY.i.hi++;
            } else {
                self->posY.i.hi--;
            }
            break;
        case 4:
            AnimateEntity(D_us_801823B8, self);
            if (self->animFrameIdx == 3 && self->animFrameDuration == 0) {
                PlaySfxPositional(SFX_WING_FLAP_A);
            }
            colRet = UnkCollisionFunc2(D_us_8018234C);
            if (colRet & 0x80) {
                self->facingLeft ^= 1;
            }
            if (self->facingLeft) {
                self->velocityX = FIX(0.75);
            } else {
                self->velocityX = FIX(-0.75);
            }

            if (self->ext.et_801D9264.timer == 0) {
                if (colRet == 1) {
                    SetSubStep(5);
                }
            } else {
                self->ext.et_801D9264.timer--;
            }
            break;
        case 5:
            self->animCurFrame = 6;
            if (UnkCollisionFunc3(D_us_80182354) & 1) {
                PlaySfxPositional(SFX_EXPLODE_B);
                SetSubStep(6);
            }
            break;
        case 6:
            if (!AnimateEntity(D_us_8018243C, self)) {
                SetStep(2);
            }
            break;
        }
        break;
    case 5:
        switch (self->step_s) {
        case 0:
            if (self->facingLeft) {
                self->velocityX = FIX(1.5);
            } else {
                self->velocityX = FIX(-1.5);
            }
            self->velocityY = FIX(-4);
            self->animCurFrame = 0x15;
            self->step_s++;
            /* fallthrough */
        case 1:
            MoveEntity();
            self->velocityY += FIX(3.0 / 16);
            if (self->velocityY > 0) {
                self->step_s++;
                if (self->ext.et_801D9264.unk84 == 0) {
                    self->ext.et_801D9264.unk84 = 2;
                    SetStep(7);
                } else {
                    self->ext.et_801D9264.unk84--;
                }
            }
            break;
        case 2:
            self->animCurFrame = 6;
            if (UnkCollisionFunc3(D_us_80182354) & 1) {
                PlaySfxPositional(SFX_EXPLODE_B);
                SetSubStep(3);
            }
            break;
        case 3:
            if (!AnimateEntity(D_us_8018243C, self)) {
                if (GetDistanceToPlayerX() > 0x40) {
                    self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
                }
                SetSubStep(0);

                if (self->ext.et_801D9264.unk84 == 1) {
                    SetStep(6);
                    posX = self->posX.i.hi + g_Tilemap.scrollX.i.hi;
                    if (posX > 0x400) {
                        self->facingLeft = 1;
                        self->ext.et_801D9264.unk85 = 3;
                    }
                    if (++self->ext.et_801D9264.unk85 > 2) {
                        self->ext.et_801D9264.unk85 = 0;
                        SetStep(8);
                    }
                } else {
                    posX = self->posX.i.hi + g_Tilemap.scrollX.i.hi;
                    if (self->facingLeft && posX > g_Tilemap.width - 0x80) {
                        self->facingLeft = 0;
                    } else if (!self->facingLeft && posX < g_Tilemap.x + 0x80) {
                        self->facingLeft = 1;
                    }
                }
            }
        }
        break;
    case 7:
        if (!AnimateEntity(D_us_801823C4, self)) {
            SetStep(5);
            self->step_s = 2;
        }
        if (self->animFrameIdx == 8 && self->animFrameDuration == 0) {
            newEntity = &PLAYER;
            posX = newEntity->posX.i.hi - self->posX.i.hi;
            posY = newEntity->posY.i.hi - self->posY.i.hi;
            if (!self->facingLeft) {
                posX = -posX;
            }
            angle = ratan2(-posY, posX);
            if (angle > 0x280) {
                angle = 0x280;
            }
            if (angle < -0x280) {
                angle = -0x280;
            }
            if (GetDistanceToPlayerY() < 0x60) {
                PlaySfxPositional(SFX_FM_EXPLODE_SWISHES);
                newEntity = AllocEntity(&g_Entities[160], &g_Entities[192]);
                if (newEntity != NULL) {
                    CreateEntityFromEntity(E_ID_44, self, newEntity);
                    newEntity->facingLeft = self->facingLeft;
                    if (self->facingLeft) {
                        newEntity->posX.i.hi += 0x10;
                    } else {
                        newEntity->posX.i.hi -= 0x10;
                    }
                    newEntity->rotZ = angle;
                    newEntity->posY.i.hi -= 0x16;
                    newEntity->zPriority = self->zPriority + 1;
                }
            }
        }
        break;
    case 6:
        if (!AnimateEntity(D_us_801823F4, self)) {
            SetStep(5);
        }
        if ((GetDistanceToPlayerY() < 0x60) && (self->animCurFrame == 0x24) &&
            (self->animFrameDuration == 0)) {
            PlaySfxPositional(SFX_FM_EXPLODE_SWISHES);
            for (i = 0; i < 3; i++) {
                newEntity = AllocEntity(&g_Entities[160], &g_Entities[192]);
                if (newEntity != NULL) {
                    CreateEntityFromEntity(E_ID_44, self, newEntity);
                    newEntity->facingLeft = self->facingLeft;
                    if (self->facingLeft) {
                        newEntity->posX.i.hi += 0x10;
                    } else {
                        newEntity->posX.i.hi -= 0x10;
                    }
                    newEntity->posY.i.hi -= 0x14;
                    newEntity->rotZ = D_us_80182454[i];
                }
            }
        }
        break;
    case 8:
        if (AnimateEntity(D_us_80182364, self) == 0) {
            SetStep(2);
        }
        if ((GetDistanceToPlayerY() < 0x60) &&
            (self->animFrameIdx == 0x9 && self->animFrameDuration == 0)) {
            PlaySfxPositional(0x758);
            PlaySfxPositional(SFX_FM_THUNDER_EXPLODE);
            newEntity = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(E_ID_45, self, newEntity);
                newEntity->facingLeft = self->facingLeft;
                newEntity->zPriority = self->zPriority + 1;
                if (self->facingLeft) {
                    newEntity->posX.i.hi += 0x20;
                } else {
                    newEntity->posX.i.hi -= 0x20;
                }
                newEntity->posY.i.hi = newEntity->posY.i.hi;
            }
        }
        break;
    case 9:
        switch (self->step_s) {
        case 0:
            if (UnkCollisionFunc3(D_us_80182354) & 1) {
                PlaySfxPositional(0x758);
                self->step_s++;
            }
            break;
        case 1:
            if (!AnimateEntity(D_us_801823A0, self)) {
                SetSubStep(2);
            }
            break;
        case 2:
            if (!(g_Timer & 0xF)) {
                PlaySfxPositional(0x759);
            }
            AnimateEntity(D_us_801823B0, self);
            if ((g_Player.status & PLAYER_STATUS_UNK40000) == 0) {
                SetStep(2);
            }
        }
        break;
    case 10:
        switch (self->step_s) {
        case 0:
            if (self->animCurFrame > 8 && self->animCurFrame < 19) {
                self->animCurFrame = 0x14;
            }
            primIndex = g_api.AllocPrimitives(PRIM_GT4, 8);
            if (primIndex == -1) {
                self->step_s = 0;
                return;
            }
            prim = &g_PrimBuf[primIndex];
            self->primIndex = primIndex;
            self->ext.prim = prim;
            self->flags |= FLAG_HAS_PRIMS;
            dr_env = g_api.func_800EDB08((POLY_GT4*)prim);
            if (dr_env == NULL) {
                DestroyEntity(self);
                return;
            }

            prim->type = PRIM_ENV;
            prim->priority = 0xF;
            if (self->params) {
                prim->priority += 4;
            }
            prim->drawMode = DRAW_DEFAULT;
            drawEnv = g_CurrentBuffer->draw;

            drawEnv.isbg = 1;
            drawEnv.r0 = drawEnv.g0 = drawEnv.b0 = 0;

            posY = self->params ? 0x180 : 0x100;

            clipRect.x = 0;
            clipRect.y = posY;
            clipRect.w = 0x80;
            clipRect.h = 0x80;
            drawEnv.clip = clipRect;
            drawEnv.ofs[0] = 0;
            drawEnv.ofs[1] = 0x100;
            SetDrawEnv(dr_env, &drawEnv);

            prim = prim->next;
            if (g_api.func_800EDB08((POLY_GT4*)prim) == NULL) {
                DestroyEntity(self);
                return;
            }
            prim->type = PRIM_ENV;

            prim->priority = 0x12;
            if (self->params) {
                prim->priority += 4;
            }

            prim->drawMode = DRAW_UNK_800;
            prim = prim->next;
            self->ext.et_801D9264.unkA4 = prim;
            posY = self->params ? 0xFF : 0x7F;
            prim->type = PRIM_GT4;
            prim->tpage = 0x110;
            prim->u1 = prim->u3 = 0x3F;
            prim->u0 = prim->u2 = 0;
            prim->v0 = prim->v1 = posY - 0x70;
            prim->v2 = prim->v3 = posY;
            temp_v0_13 = (u16)self->posX.i.hi;
            prim->x0 = prim->x2 = temp_v0_13 - 0x20;
            prim->x1 = prim->x3 = temp_v0_13 + 0x20;
            temp_v0_15 = (u16)self->posY.i.hi;
            prim->y2 = prim->y3 = temp_v0_15 + 0x28;
            prim->y0 = prim->y1 = temp_v0_15 - 0x48;
            prim->priority = self->zPriority;
            prim->drawMode = DRAW_UNK02;

            prim = prim->next;
            prim->type = PRIM_TILE;
            posY = (self->params != 0) << 7;
            prim->x0 = 0;
            prim->y0 = posY;
            prim->v0 = prim->u0 = 0x80;
            prim->r0 = prim->g0 = prim->b0 = 0;

            prim->priority = 0x11;
            if (self->params) {
                prim->priority += 4;
            }

            prim->drawMode = DRAW_UNK_40 | DRAW_TPAGE | DRAW_TRANSP;

            prim = prim->next;
            while (prim != NULL) {
                prim->drawMode = DRAW_HIDE;
                prim = prim->next;
            }

            self->zPriority = 0x10;

            if (self->params) {
                self->zPriority += 4;
            }

            posY = self->params ? 0x100 : 0x80;

            self->posX.i.hi = 0x20;
            self->posY.i.hi = posY - 0x28;

            self->palette = *D_us_80180BDE;
            self->flags &= ~FLAG_POS_CAMERA_LOCKED;
            self->step_s++;
            break;
        case 1:
            prim = self->ext.prim;
            self->animCurFrame = 0;
            prim->type = PRIM_ENV;

            dr_env = LOW(prim->r1);
            drawEnv = g_CurrentBuffer->draw;
            drawEnv.isbg = 0;
            drawEnv.dtd = 0;

            posY = self->params ? 0x180 : 0x100;

            clipRect.x = 0;
            clipRect.y = posY;
            clipRect.w = 0x80;
            clipRect.h = 0x80;
            drawEnv.clip = clipRect;
            drawEnv.ofs[0] = 0;
            drawEnv.ofs[1] = 0x100;
            SetDrawEnv(dr_env, &drawEnv);

            prim->priority = 0xF;
            if (self->params) {
                prim->priority += 4;
            }

            prim->drawMode = DRAW_DEFAULT;
            self->ext.et_801D9264.y = 0x28;
            self->ext.et_801D9264.timer = 0x10;
            self->step_s++;
            /* fallthrough */
        case 2:
            if (!(g_Timer & 7)) {
                PlaySfxPositional(SFX_FM_EXPLODE_B);
            }
            prim = self->ext.et_801D9264.unkA4;
            posX = Random() & 0x3F;
            posY = self->ext.et_801D9264.y;
            if (!(g_Timer & 0xF)) {
                newEntity = AllocEntity(&g_Entities[STAGE_ENTITY_START],
                                        &g_Entities[TOTAL_ENTITY_COUNT]);
                if (newEntity != NULL) {
                    CreateEntityFromCurrentEntity(E_EXPLOSION, newEntity);
                    newEntity->posX.i.hi = prim->x0 + posX;
                    newEntity->posY.i.hi = prim->y2 + posY - 0x30;
                    newEntity->params = 3;
                }
            }
            newEntity = AllocEntity(&g_Entities[STAGE_ENTITY_START],
                                    &g_Entities[TOTAL_ENTITY_COUNT]);
            if (newEntity != NULL) {
                CreateEntityFromCurrentEntity(E_ID_46, newEntity);
                newEntity->posX.i.hi = (self->posX.i.hi - 0x20) + posX;
                newEntity->posY.i.hi = (self->posY.i.hi + posY) + 4;
                newEntity->params = 1;
                newEntity->facingLeft = colRet;
                newEntity->zPriority = 0x10;
                if (self->params) {
                    newEntity->zPriority += 4;
                }
            }
            if (!--self->ext.et_801D9264.timer) {
                self->ext.et_801D9264.timer = 2;
                self->ext.et_801D9264.y -= 2;
                if (self->ext.et_801D9264.y < -0x28) {
                    self->ext.et_801D9264.timer = 0x40;
                    self->step_s++;
                }
            }
            break;
        case 3:
            if (!--self->ext.et_801D9264.timer) {
                DestroyEntity(self);
                return;
            }
        }
        break;
    case 255:
#include "../pad2_anim_debug.h"
    }
    if (self->animCurFrame > 10 && self->animCurFrame < 15) {
        LOH(self->hitboxOffX) = -0x12;
        LOH(self->hitboxOffY) = 0x11;
        self->hitboxWidth = 0x16;
        self->hitboxHeight = 0x16;
    } else {
        LOH(self->hitboxOffX) = -1;
        LOH(self->hitboxOffY) = 1;
        self->hitboxWidth = 0x13;
        self->hitboxHeight = 0x26;
    }
}

// Shot fireball
INCLUDE_ASM("st/no0/nonmatchings/e_ctulhu", func_us_801DA488);

// Ice shockwave attack
INCLUDE_ASM("st/no0/nonmatchings/e_ctulhu", func_us_801DA6B4);

// Death
INCLUDE_ASM("st/no0/nonmatchings/e_ctulhu", func_us_801DADD0);
