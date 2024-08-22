// SPDX-License-Identifier: AGPL-3.0-only
#include "st0.h"
#include "sfx.h"

bool func_801ADAC8(s32 arg0) {
    s32 unk = 0xD0;
    Entity* entity = g_CurrentEntity;
    s16 temp_v1 = entity->posY.i.hi + arg0;

    if (temp_v1 >= unk) {
        entity->posY.i.hi = unk - temp_v1 + entity->posY.i.hi;
        return true;
    } else {
        return false;
    }
}

// Function unique to ST0. Has many similarities to ClutLerp.
// Unclear what it actually does; no known calls.
void func_801ADB10(u16* arg0, u16 arg1, u16 arg2, s32 steps, u8* arg4) {
    u16 buf[COLORS_PER_PAL];
    RECT bufRect;
    s32 temp_a2;
    s32 factor;
    s32 temp_v0;
    s32 i;
    s32 j;
    s32 var_v0;
    u16* palA;

    u32 t;
    u32 r, g, b;
    u32 tempR;
    u32 tempG;
    u32 tempB;

    bufRect.x = *arg0;
    bufRect.w = COLORS_PER_PAL;
    bufRect.h = 1;

    arg4[0] >>= 3;
    arg4[1] >>= 3;
    arg4[2] >>= 3;
    palA = g_Clut + arg1 * COLORS_PER_PAL;

    for (i = 0; i < steps; arg2++, i++) {
        factor = i * 4096 / steps;
        for (j = 0; j < 16; j++) {
            if (j == 0) {
                buf[0] = *palA;
            } else {
                t = palA[j] & 0x8000;
                tempR = (palA[j] & 0x1F);
                r = (tempR * (4096 - factor)) + (arg4[0] * factor);
                tempG = (palA[j] >> 5) & 0x1F;
                tempR = r >> 12;
                g = (tempG * (4096 - factor)) + (arg4[1] * factor);
                tempB = (palA[j] >> 10) & 0x1F;
                tempG = g >> 12;
                b = (tempB * (4096 - factor)) + (arg4[2] * factor);
                tempB = b >> 12;
                buf[j] = ((t | (tempR)) | (tempG << 5)) | (tempB << 10);
                (g_Clut + (arg2 * COLORS_PER_PAL))[j] = buf[j];
            }
        }
        temp_a2 = arg2 - 0x200;
        var_v0 = temp_a2;
        if (var_v0 < 0) {
            var_v0 = arg2 - 0x1F1;
        }
        temp_v0 = var_v0 >> 4;
        bufRect.y = temp_v0 + 0xF0;
        bufRect.x = ((temp_a2 - (temp_v0 * 0x10)) * 0x10) + 0x100;
        LoadImage(&bufRect, buf);
        g_ClutIds[arg2] = GetClut(bufRect.x, bufRect.y);
    }
}

void EntityDraculaFinalForm(Entity* self) {
    byte stackpad[56];
    Entity* temp_s2;
    Entity* var_s1;
    Primitive* prim;
    s16 primIndex;
    s32 i;
    s16* temp_s1;
    s32 xShift;
    s32 timerDiff;
    u16 selfzPriority;
    s32 selfParams;

    if (self->flags & FLAG_DEAD) {
        self->hitboxState = 0;
        if (self->step < 6) {
            D_8003C744 = 3;
            SetStep(6);
        }
    }
    if (self->params == 0) {
        if (!(g_Timer & 1)) {
            self->palette = 0x204;
        } else {
            self->palette = 0x202;
        }
    }
    switch (self->step) {
    case 0:
        InitializeEntity(D_80180604);
        self->hitboxHeight = 16;
        self->hitboxWidth = 16;
        self->hitboxOffX = -24;
        self->hitboxOffY = -16;
        self->hitboxState = 0;
        if (self->params == 0) {
            temp_s2 = self + 1;
            D_8003C744 = 2;
            var_s1 = self + 1;
            self->animCurFrame = 0;
            for (i = 1; i < 4; i++, temp_s2++, var_s1++) {
                CreateEntityFromCurrentEntity(32, temp_s2);
                selfzPriority = self->zPriority;
                var_s1->params = i;
                var_s1->unk60 = temp_s2 - 1;
                var_s1->unk5C = self;

                var_s1->zPriority = selfzPriority + 2;
                // seems hitPoints might be used for something else
                var_s1->hitPoints = 0x7FFE;
            }
            self->unk5C = 0;
            self->unk60 = self + 3;
        } else {
            self->animCurFrame = 0;
            SetStep(16);
        }
        break;
    case 1:
        if (D_801C2578 == 0) {
            self->animCurFrame = 1;
        }
        if (D_80180910 != 0) {
            self->animCurFrame = 1;
            self->hitboxState = 3;
            self->unk6C = 0x80;
            self->drawFlags = 0;
            SetStep(2);
        }
        break;
    case 2:
        if (self->step_s == 0) {
            self->ext.dracFinalForm.timer = 80;
            self->step_s++;
        }
        if ((AnimateEntity(D_80180AA4, self) == 0) &&
            (((GetSideToPlayer() & 1) ^ 1) != self->facingLeft)) {
            SetStep(3);
        }
        if (--self->ext.dracFinalForm.timer == 0) {
            SetStep(5);
            if ((self->posX.i.hi < 152) && (self->facingLeft == 1)) {
                if (Random() & 1) {
                    SetStep(7);
                } else {
                    SetStep(4);
                }
            } else if ((self->posX.i.hi > 104) && (self->facingLeft == 0)) {
                if (Random() & 1) {
                    SetStep(7);
                } else {
                    SetStep(4);
                }
            } else if (Random() & 1) {
                SetStep(8);
            } else {
                SetStep(4);
            }
        }
        break;
    case 7:
        switch (self->step_s) {
        case 0:
            self->velocityX = 0;
            self->velocityY = 0;
            self->step_s++;
            /* fallthrough */
        case 1:
            if (AnimateEntity(D_80180AB0, self) == 0) {
                SetSubStep(2);
            }
            if (self->animFrameIdx == 5 && self->animFrameDuration == 0) {
                if (self->facingLeft) {
                    self->velocityX = FIX(0.5);
                } else {
                    self->velocityX = FIX(-0.5);
                }
                self->velocityY = FIX(-4.0);
            }
            MoveEntity();
            if (self->velocityY != 0) {
                self->velocityY += FIX(10.0 / 128);
            }
            break;
        case 2:
            MoveEntity();
            self->velocityY += FIX(10.0 / 128);
            if (self->velocityY >= 0) {
                AnimateEntity(D_80180AC8, self);
            }
            if (func_801ADAC8(0x4C) != 0) {
                g_api.PlaySfx(SFX_START_SLAM_B);
                g_api.func_80102CD8(1);
                self->step_s++;
            }
            break;
        case 3:
            if (AnimateEntity(D_80180AD4, self) == 0) {
                SetStep(2);
            }
        }
        break;
    case 3:
        if (AnimateEntity(D_80180B60, self) == 0) {
            if ((self->posX.i.hi < 160) && (self->facingLeft == 1)) {
                if (Random() & 1) {
                    SetStep(4);
                } else {
                    SetStep(7);
                }
            } else if ((self->posX.i.hi > 96) && (self->facingLeft == 0)) {
                if (Random() & 1) {
                    SetStep(4);
                } else {
                    SetStep(7);
                }
            } else {
                SetStep(2);
            }
        }
        if (self->animFrameIdx == 2 && self->animFrameDuration == 0) {
            self->facingLeft = (self->facingLeft ^ 1);
        }
        break;
    case 4:
        switch (self->step_s) {
        case 0:
            if (AnimateEntity(D_80180B48, self) == 0) {
                g_api.PlaySfx(0x866);
                self->step_s++;
            }
            break;
        case 1:
            temp_s2 = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (temp_s2 != NULL) {
                CreateEntityFromEntity(33, self, temp_s2);
                temp_s2->posX.i.hi = temp_s2->posX.i.hi;
                temp_s2->posY.i.hi = temp_s2->posY.i.hi;
                temp_s2->facingLeft = self->facingLeft;
                temp_s2->params = 1;
            }
            self->ext.dracFinalForm.timer = 32;
            self->step_s++;
            break;
        case 2:
            // FAKE assignment to i
            if (i = --self->ext.dracFinalForm.timer == 0) {
                self->ext.dracFinalForm.unk84 = 0;
                self->step_s++;
            }
            break;
        case 3:
            if (self->ext.dracFinalForm.timer != 0) {
                self->ext.dracFinalForm.timer--;
                break;
            }
            self->ext.dracFinalForm.timer = 48;
            temp_s1 = &D_801810F4;
            temp_s1 += self->ext.dracFinalForm.unk84;
            if (*temp_s1 == -1) {
                SetStep(2);
                return;
            }
            if (self->facingLeft) {
                xShift = 32;
            } else {
                xShift = -32;
            }
            temp_s2 = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (temp_s2 != NULL) {
                g_api.PlaySfx(SFX_FIREBALL_SHOT_A);
                CreateEntityFromEntity(33, self, temp_s2);
                temp_s2->posX.i.hi = (xShift + temp_s2->posX.i.hi);
                temp_s2->posY.i.hi = (temp_s2->posY.i.hi - 4);
                temp_s2->rotZ = *temp_s1;
                if (self->facingLeft) {
                    temp_s2->rotZ = (0x800 - temp_s2->rotZ);
                }
            }
            self->ext.dracFinalForm.unk84++;
        }
        break;
    case 8:
        switch (self->step_s) {
        case 0:
            self->velocityX = 0;
            self->velocityY = 0;
            self->ext.dracFinalForm.timer = 4;
            self->ext.dracFinalForm.unk84 = 0;
            self->step_s++;
            /* fallthrough */
        case 1:
            if (AnimateEntity(D_80180B80, self) == 0) {
                SetSubStep(2);
            }
            if (self->animFrameIdx == 3 && self->animFrameDuration == 0) {
                g_api.PlaySfx(0x866);
                self->velocityY = FIX(-7.0);
            }
            MoveEntity();
            if (self->velocityY != 0) {
                self->velocityY += FIX(0.09375);
            }
            if (--self->ext.dracFinalForm.timer == 0) {
                temp_s1 = &D_801810F4[4];
                temp_s1 += self->ext.dracFinalForm.unk84;
                if (*temp_s1 == -1) {
                    self->ext.dracFinalForm.timer = 0x7FFF;
                    return;
                }
                self->ext.dracFinalForm.timer = 6;
                temp_s2 = AllocEntity(&g_Entities[160], &g_Entities[192]);
                if (temp_s2 != NULL) {
                    g_api.PlaySfx(SFX_FIREBALL_SHOT_B);
                    CreateEntityFromEntity(34, self, temp_s2);
                    temp_s2->posX.i.hi = (temp_s2->posX.i.hi + *temp_s1);
                    temp_s2->zPriority = (self->zPriority + 1);
                }
                self->ext.dracFinalForm.unk84++;
            }
            break;
        case 2:
            MoveEntity();
            self->velocityY += FIX(0.125);
            if (self->velocityY >= 0) {
                AnimateEntity(D_80180AC8, self);
            }
            if (func_801ADAC8(0x4C) != 0) {
                g_api.PlaySfx(SFX_START_SLAM_B);
                g_api.func_80102CD8(1);
                self->step_s++;
            }
            break;
        case 3:
            if (AnimateEntity(D_80180AD4, self) == 0) {
                SetStep(2);
            }
        }
        break;
    case 5:
        switch (self->step_s) {
        case 0:
            if (AnimateEntity(D_80180AEC, self) == 0) {
                SetSubStep(1);
            }
            break;
        case 1:
            if (AnimateEntity(D_80180AFC, self) == 0) {
                g_api.PlaySfx(0x856);
                temp_s2 = AllocEntity(&g_Entities[160], &g_Entities[192]);
                if (temp_s2 != NULL) {
                    CreateEntityFromEntity(46, self, temp_s2);
                    if (self->facingLeft != 0) {
                        temp_s2->posX.i.hi += 40;
                    } else {
                        temp_s2->posX.i.hi -= 40;
                    }
                    temp_s2->posY.i.hi += 16;
                    temp_s2->facingLeft = self->facingLeft;
                }
                SetSubStep(2);
            }
            break;
        case 2:
            if (AnimateEntity(D_80180B20, self) == 0) {
                SetSubStep(3);
            }
            break;
        case 3:
            self->ext.dracFinalForm.timer = 256;
            self->step_s++;
            break;
        case 4:
            if (--self->ext.dracFinalForm.timer == 0) {
                SetStep(2);
            }
        }
        break;
    case 16:
        temp_s2 = self - self->params;
        self->facingLeft = temp_s2->facingLeft;
        self->hitboxState = temp_s2->hitboxState;
        temp_s1 = &D_80180BE4;
        self->posX.i.hi = temp_s2->posX.i.hi;
        self->posY.i.hi = temp_s2->posY.i.hi;
        // Fake reuse of the i variable
        i = temp_s2->animCurFrame - 1;
        temp_s1 += i * 12;
        temp_s1 += (self->params - 1) * 4;
        self->hitboxOffX = *temp_s1++;
        self->hitboxOffY = *temp_s1++;

        self->hitboxWidth = *temp_s1++;
        self->hitboxHeight = *temp_s1++;
        if (self->params == 1) {
            switch (self->step_s) {
            case 0:
                self->ext.dracFinalForm.timer = 100;
                self->step_s++;
                return;
            case 1:
                if (--self->ext.dracFinalForm.timer == 0) {
                    self->animCurFrame = 0x5A;
                    self->unk5A = 0x5E;
                    self->palette = 0x815F;
                    self->drawMode = 0x30;
                    self->drawFlags = 0xB;
                    self->unk6C = 0x10;
                    self->rotY = 0x400;
                    self->rotX = 0x400;
                    g_api.PlaySfx(0x880);
                    self->step_s++;
                }
                break;
            case 2:
                self->rotX = self->rotY = self->rotY - 0x18;
                if (self->rotY < 0x100) {
                    self->animCurFrame = 0;
                    self->drawMode = 0;
                    self->drawFlags = 0;
                    self->step_s++;
                }
                break;
            case 3:
                if (D_801C2578 == 0) {
                    self->animCurFrame = 1;
                    self->unk5A = 0x50;
                    self->palette = 0x815F;
                    self->drawFlags = 8;
                    self->unk6C = 0;
                    self->drawMode = 0x30;
                    self->step_s++;
                }
                break;
            case 4:
                self->unk6C += 4;
                self->animCurFrame = temp_s2->animCurFrame;
                if (self->unk6C > 0x60) {
                    self->step_s++;
                }
                break;
            case 5:
                self->unk6C -= 4;
                self->animCurFrame = temp_s2->animCurFrame;
                if (self->unk6C == 0) {
                    self->animCurFrame = 0;
                    self->drawMode = 0;
                    self->drawFlags = 0;
                    self->step_s++;
                }
                break;
            }
        }
        break;
    case 6: // Time attack call indicates this state is Dracula's defeat
        switch (self->step_s) {
        case 0:
            g_api.PlaySfx(0x866);
            temp_s2 = self + 1;
            self->hitboxState = 0;
            for (i = 0; i < 3; i++) {
                DestroyEntity(temp_s2);
                temp_s2++;
            }
            g_api.PlaySfx(0x80);
            self->ext.dracFinalForm.timer = 4;
            self->ext.dracFinalForm.unk84 = 0;
            g_api.TimeAttackController(
                TIMEATTACK_EVENT_DRACULA_DEFEAT, TIMEATTACK_SET_RECORD);
            D_8003C8B8 = 0;
            D_80181148 = 0x800;
            self->step_s++;
            /* fallthrough */
        case 1:
            if (AnimateEntity(D_80180B58, self) == 0) {
                self->step_s++;
            }
            break;
        case 2:
            if (g_api.func_80131F68() == true) {
                if (--D_80181148 == 0) {
                    D_80181148 = 0x800;
                    g_api.PlaySfx(0x80);
                }
            } else {
                g_api.PlaySfx(0x35E);
                D_8018114C = g_Timer;
                self->step_s++;
            }
            break;
        case 3:
            if (g_api.func_80131F68() == false) {
                // Fake reuse of the i variable
                i = g_Timer - D_8018114C;
                if (i >= 0x301) {
                    g_api.PlaySfx(SFX_EXPLODE_A);
                    self->ext.dracFinalForm.unk82 = 0x80;
                    self->step_s++;
                    break;
                }
                g_api.func_80102CD8(1);
                D_80181148--;
                if (D_80181148 == 0) {
                    D_80181148 = 0x800;
                    g_api.PlaySfx(0x80);
                    self->step_s--;
                    break;
                }
            } else {
                g_api.PlaySfx(SFX_EXPLODE_A);
                self->ext.dracFinalForm.unk82 = 0x80;
                self->step_s++;
            }
            break;
        case 4:
            if (--self->ext.dracFinalForm.unk82 == 0) {
                self->step_s++;
            }
            break;
        case 5:
            CreateEntityFromCurrentEntity(44, self + 1);
            self->step_s++;
            primIndex = g_api.AllocPrimitives(PRIM_G4, 1);
            if (primIndex == -1) {
                g_GameEngineStep = 0xA;
                g_MenuStep = 0;
                return;
            }
            prim = &g_PrimBuf[primIndex];
            self->primIndex = primIndex;
            self->ext.prim = prim;
            self->flags |= FLAG_HAS_PRIMS;
            prim->r0 = prim->g0 = prim->b0 = 0;
            LOW(prim->r1) = LOW(prim->r0);
            LOW(prim->r2) = LOW(prim->r0);
            LOW(prim->r3) = LOW(prim->r0);
            prim->x0 = prim->x2 = 0;
            prim->x1 = prim->x3 = 0x100;
            prim->y0 = prim->y1 = 0;
            prim->y2 = prim->y3 = 0x100;
            prim->priority = self->zPriority + 0x10;
            prim->drawMode = DRAW_TRANSP | 0x30;
            self->step_s++;
        case 6:
            prim = self->ext.prim;
            prim->g0 = prim->b0 = prim->r0 = prim->r0 + 0x18;
            LOW(prim->r1) = LOW(prim->r0);
            LOW(prim->r2) = LOW(prim->r0);
            LOW(prim->r3) = LOW(prim->r0);
            if (prim->r0 >= 0x81) {
                self->step_s++;
            }
            break;
        case 7:
            break;
        }
        if (--self->ext.dracFinalForm.timer == 0) {
            g_api.PlaySfx(SFX_EXPLODE_B);
            self->ext.dracFinalForm.timer = 8;
            temp_s2 = AllocEntity(&g_Entities[224], &g_Entities[256]);
            temp_s1 = &D_80181108[self->ext.dracFinalForm.unk84].x;
            if (temp_s2 != NULL) {
                CreateEntityFromEntity(2, self, temp_s2);
                temp_s2->params = 3;
                temp_s2->zPriority = (self->zPriority + 1);
                temp_s2->posX.i.hi = (temp_s2->posX.i.hi + *temp_s1++);
                temp_s2->posY.i.hi = (temp_s2->posY.i.hi + *temp_s1++);
            }
            self->ext.dracFinalForm.unk84 =
                ((self->ext.dracFinalForm.unk84 + 1) & 0xF);
        }
        break;
    case 0xFF:
        FntPrint("charal %x\n", self->animCurFrame);
        if (g_pads[1].pressed & PAD_SQUARE) {
            if (self->params != 0) {
                return;
            }
            self->animCurFrame++;
            self->params |= 1;
        } else {
            self->params = 0;
        }
        if (g_pads[1].pressed & PAD_CIRCLE) {
            if (self->step_s != 0) {
                return;
            }
            self->animCurFrame--;
            self->step_s |= 1;
        } else {
            self->step_s = 0;
        }
        break;
    }
}

void EntityDraculaMegaFireball(Entity* self) {
    s16 angle;

    if (self->step == 0) {
        InitializeEntity(D_80180610);
        self->flags |= FLAG_DESTROY_IF_OUT_OF_CAMERA |
                       FLAG_DESTROY_IF_BARELY_OUT_OF_CAMERA;
        if (self->params == 0) {
            angle = self->rotZ;
            self->rotY = 0x80;
            self->rotX = 0x80;
            self->drawFlags |= 7;
            self->rotZ = 0x1C0 - angle;
            if (self->facingLeft != 0) {
                self->velocityX = rcos(angle) * 0x60;
            } else {
                self->velocityX = -(rcos(angle) * 0x60);
            }
            self->velocityY = rsin(angle) * 0x60;
        }
    }
    if (self->params != 0) {
        if (AnimateEntity(D_80180BA0, self) == 0) {
            DestroyEntity(self);
        }
        if (g_Timer & 1) {
            self->animCurFrame = 0;
        }
    } else {
        if (self->rotX < 0x100) {
            self->rotX = self->rotY = self->rotY + 0x10;
        }
        AnimateEntity(D_80180BB8, self);
        MoveEntity();
    }
}

void EntityDraculaRainAttack(Entity* self) {
    Entity* newEntity;
    s32 velY;
    s32 velX;
    s16 angle;
    s32 i;

    if (self->flags & FLAG_DEAD) {
        newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (newEntity != NULL) {
            CreateEntityFromEntity(E_EXPLOSION, self, newEntity);
            newEntity->params = 2;
        }
        DestroyEntity(self);
        return;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(D_8018061C);
        if (self->params != 0) {
            self->hitboxState = 0;
            self->animCurFrame = 0x59;
            velX = (Random() & 0x1F) + 0x10;
            angle = (Random() * 6) + 0x900;
            self->velocityX = velX * rcos(angle);
            velY = velX * rsin(angle);
            self->step = 3;
            self->velocityY = velY;
            break;
        }
        self->velocityY = FIX(4);

    case 1:
        MoveEntity();
        AnimateEntity(D_80180BCC, self);
        if (func_801ADAC8(0x14) != 0) {
            SetStep(2);
        }
        break;

    case 2:
        if (AnimateEntity(D_80180BDC, self) == 0) {

            for (i = 0; i < 4; i++) {
                newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (newEntity != NULL) {
                    CreateEntityFromEntity(0x22, self, newEntity);
                    newEntity->params = 1;
                    newEntity->posY.i.hi += 12;
                }
            }
            DestroyEntity(self);
        }
        break;

    case 3:
        MoveEntity();
        self->velocityY += FIX(0.125);
        if (self->posY.i.hi >= 0xF1) {
            DestroyEntity(self);
        }
        break;
    }
}

void func_801AF380(void) {
    Primitive* prim;
    s16* var_t0;
    s32 i;
    u8* var_a3;
    s32 uBase;
    s32 vBase;

    var_t0 = &D_80181150[0];
    var_a3 = &D_801813E8;
    uBase = 0;
    vBase = 0;
    prim = g_CurrentEntity->ext.et_801AF774.prim1;
    for (i = 0; i < 47; i++) {
        prim->tpage = 0x17;
        prim->clut = 0x200;
        // This should REALLY be done using Point16, but no,
        // that would make too much sense for SOTN
        prim->u0 = uBase + var_t0[*var_a3 * 2];
        prim->v0 = vBase + var_t0[*var_a3 * 2 + 1];
        var_a3++;
        prim->u1 = uBase + var_t0[*var_a3 * 2];
        prim->v1 = vBase + var_t0[*var_a3 * 2 + 1];
        var_a3++;
        prim->u2 = uBase + var_t0[*var_a3 * 2];
        prim->v2 = vBase + var_t0[*var_a3 * 2 + 1];
        var_a3++;
        prim->u3 = uBase + var_t0[*var_a3 * 2];
        prim->v3 = vBase + var_t0[*var_a3 * 2 + 1];
        var_a3++;
        prim->r0 = prim->g0 = prim->b0 = 0x80;
        LOW(prim->r1) = LOW(prim->r0);
        LOW(prim->r2) = LOW(prim->r0);
        LOW(prim->r3) = LOW(prim->r0);
        prim->priority = 0xA0;
        prim->drawMode = DRAW_TRANSP | 0x34;
        prim = prim->next;
    }
    var_t0 = &D_8018129C[0];
    var_a3 = &D_801814A8;
    uBase = 0;
    vBase = 0x80;
    g_CurrentEntity->ext.et_801AF774.prim2 = prim;
    for (i = 0; i < 42; i++) {
        prim->tpage = 0x17;
        prim->clut = 0x204;
        prim->u0 = uBase + var_t0[*var_a3 * 2];
        prim->v0 = vBase + var_t0[*var_a3 * 2 + 1];
        var_a3++;
        prim->u1 = uBase + var_t0[*var_a3 * 2];
        prim->v1 = vBase + var_t0[*var_a3 * 2 + 1];
        var_a3++;
        prim->u2 = uBase + var_t0[*var_a3 * 2];
        prim->v2 = vBase + var_t0[*var_a3 * 2 + 1];
        var_a3++;
        prim->u3 = uBase + var_t0[*var_a3 * 2];
        prim->v3 = vBase + var_t0[*var_a3 * 2 + 1];
        var_a3++;
        prim->r0 = prim->g0 = prim->b0 = 0;
        LOW(prim->r1) = LOW(prim->r0);
        LOW(prim->r2) = LOW(prim->r0);
        LOW(prim->r3) = LOW(prim->r0);
        prim->priority = 0xA0;
        prim->drawMode = DRAW_TRANSP | 0x34;
        prim = prim->next;
    }

    var_t0 = &D_80181150;
    for (i = 0; i < 83; i++) {
        D_801BEB64[i].x = (*var_t0++ - 0x1E) << 0x10;
        D_801BEB64[i].y = (*var_t0++ - 0x53) << 0x10;
    }
}

void func_801AF6D0(void) {
    s16* var_a0;
    s16* var_a1;
    s32 i;
    s32* var_a2;
    s32 a, b, c, d;

    var_a1 = (s16*)D_80181150;
    var_a0 = (s16*)D_8018129C;

    d = -0x1E;
    c = -0x53;
    b = -0x38;
    a = -0x75;

    i = 0;
    var_a2 = D_801BEB64;

    for (; i < 0x53; ++i) {
        D_801BEB64[i].x += ((b + *var_a0++) - (d + *var_a1++)) << 9;
        D_801BEB64[i].y += ((a + *var_a0++) - (c + *var_a1++)) << 9;
        var_a2 += 2;
    }
}

void func_801AF774(Entity* self) {
    RECT sp10;
    DRAWENV sp18;
    DRAWENV* var_a2;
    DRAWENV* var_a3;
    Primitive* prim;
    s32 primIndex;
    s32 i;
    u32 var_t0;
    u8 temp_t0;
    u8* var_a2_3;
    s16* temp_a3;
    s32 xBase;
    s32 yBase;
    inline s32 add(a, b) { return a + b; }

    switch (self->step) {
    case 0:
        InitializeEntity(D_801805E0);
        self->hitboxState = 0;
        self->animCurFrame = 0;
        self->drawMode |= (DRAW_TPAGE | 0x20);
        self->flags &= ~FLAG_UNK_08000000;
        D_801C2578 = 1;
        self->ext.et_801AF774.unk90 = 1;
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 0x5C);
        if (primIndex != -1) {
            prim = &g_PrimBuf[primIndex];
            self->primIndex = primIndex;
            self->ext.et_801AF774.prim3 = prim;
            self->flags |= FLAG_HAS_PRIMS;
            prim->tpage = 0x110;
            if (!self->facingLeft) {
                prim->u0 = prim->u2 = 0;
                prim->u1 = prim->u3 = 0x80;
                prim->v0 = prim->v1 = 0;
                prim->v2 = prim->v3 = 0x80;
            } else {
                prim->u1 = prim->u3 = 0;
                do {
                    prim->u0 = prim->u2 = 0x7F;
                    prim->v0 = prim->v1 = 0;
                    prim->v2 = prim->v3 = 0x80;
                } while (0);
            }

            prim->x0 = prim->x2 = self->posX.i.hi - 0x40;
            prim->x1 = prim->x3 = self->posX.i.hi + 0x40;
            prim->y0 = prim->y1 = self->posY.i.hi - 0x25;
            prim->y2 = prim->y3 = self->posY.i.hi + 0x5B;
            prim->r0 = prim->g0 = prim->b0 = 0x80;
            LOW(prim->r1) = LOW(prim->r0);
            LOW(prim->r2) = LOW(prim->r0);
            LOW(prim->r3) = LOW(prim->r0);
            prim->drawMode = DRAW_UNK02 | DRAW_HIDE;
            prim->priority = 0xA8;
            prim = prim->next;
            self->ext.et_801AF774.prim4 = prim;
            if (g_api.func_800EDB08(prim) == NULL) {
                g_api.FreePrimitives(primIndex);
                self->step = 0;
                self->flags &= ~FLAG_HAS_PRIMS;
                return;
            }
            prim->type = PRIM_ENV;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
            g_api.func_800EDB08(prim);
            if (prim == NULL) {
                g_api.FreePrimitives(primIndex);
                self->step = 0;
                self->flags &= ~FLAG_HAS_PRIMS;
                return;
            }
            prim->type = PRIM_ENV;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
            self->ext.prim = prim;
            while (prim != NULL) {
                prim->priority = 0xA0;
                prim->drawMode = DRAW_HIDE;
                prim = prim->next;
                var_a3 = &sp18;
            }
        } else {
            self->step = 0;
            FntPrint("can't get effect works!\n");
            return;
        }
    case 1:
        var_a3 = &sp18;
        prim = self->ext.et_801AF774.prim4;
        var_a2 = &g_CurrentBuffer->draw;
        *var_a3 = *var_a2;
        sp18.isbg = 1;
        sp18.r0 = 0;
        sp18.g0 = 0;
        sp18.b0 = 0;
        sp10.x = 0;
        sp10.y = 0x100;
        sp10.w = 0x7f;
        sp10.h = 0xff;
        sp18.clip = sp10;
        sp18.ofs[0] = 0;
        sp18.ofs[1] = 0x100;
        SetDrawEnv(LOW(prim->r1), &sp18);
        prim->priority = 0x9F;
        prim->drawMode = DRAW_DEFAULT;
        prim = prim->next;
        prim->priority = 0xA1;
        prim->drawMode = DRAW_UNK_800;
    case 6:
        self->step++;
        return;

    case 2:
        func_801AF380();
        var_a3 = &sp18;
        prim = self->ext.et_801AF774.prim4;
        var_a2 = &g_CurrentBuffer->draw;
        var_t0 = LOW(prim->r1);
        *var_a3 = *var_a2;
        sp18.isbg = 0;
        sp18.dtd = 0;
        sp10.x = 0;
        sp10.y = 0x100;
        sp10.w = 0x80;
        sp10.h = 0x80;
        sp18.clip = sp10;
        sp18.ofs[0] = 0;
        sp18.ofs[1] = 0x100;
        SetDrawEnv(var_t0, &sp18);
        prim->priority = 0x9F;
        prim->drawMode = 0;
        prim = prim->next;
        prim->priority = 0xA1;
        prim->drawMode = DRAW_UNK_800;
        self->ext.et_801AF774.unk8E = 0x80;
        self->ext.et_801AF774.unk8C = 0x8000;
        self->step_s = 0;
        self->step++;
        return;
    case 3:
        prim = self->ext.et_801AF774.prim3;
        prim->drawMode =
            DRAW_TPAGE | 0x20 | DRAW_COLORS | DRAW_UNK02 | DRAW_TRANSP;
        if (self->ext.et_801AF774.unk8E > 0) {
            func_801AF6D0();
        }
        var_t0 = (u16)self->ext.et_801AF774.unk8C >> 8;
        if (var_t0 >= 0x81) {
            var_t0 = 0x80;
        }
        var_t0 = (u8)var_t0 >> 3;
        prim = self->ext.prim;
        xBase = 0x40;
        yBase = 0x70;
        temp_a3 = &D_801BEB64;
        var_a2_3 = &D_801813E8;

        for (i = 0; i < 47; i++) {
            prim->x0 = add(xBase, temp_a3[*var_a2_3 * 4 + 1]);
            prim->y0 = add(yBase, temp_a3[*var_a2_3 * 4 + 3]);
            var_a2_3++;
            prim->x1 = add(xBase, temp_a3[*var_a2_3 * 4 + 1]);
            prim->y1 = add(yBase, temp_a3[*var_a2_3 * 4 + 3]);
            var_a2_3++;
            prim->x2 = add(xBase, temp_a3[*var_a2_3 * 4 + 1]);
            prim->y2 = add(yBase, temp_a3[*var_a2_3 * 4 + 3]);
            var_a2_3++;
            prim->x3 = add(xBase, temp_a3[*var_a2_3 * 4 + 1]);
            prim->y3 = add(yBase, temp_a3[*var_a2_3 * 4 + 3]);
            var_a2_3++;
            prim->b0 = var_t0;
            prim->g0 = var_t0;
            prim->r0 = var_t0;

            LOW(prim->r1) = LOW(prim->r0);
            LOW(prim->r2) = LOW(prim->r0);
            LOW(prim->r3) = LOW(prim->r0);
            prim = prim->next;
        }
        var_t0 = (u16)self->ext.et_801AF774.unk8C >> 8;
        if (var_t0 >= 0x81U) {
            var_t0 = 0x80;
        }
        var_t0 = (0x80 - var_t0);
        temp_t0 = var_t0;
        temp_t0 >>= 3;
        prim = self->ext.et_801AF774.prim2;
        temp_a3 = &D_801BEB64;
        var_a2_3 = &D_801814A8;
        xBase = 0x40;
        yBase = 0x70;
        for (i = 0; i < 42; i++) {
            prim->x0 = add(xBase, temp_a3[*var_a2_3 * 4 + 1]);
            prim->y0 = add(yBase, temp_a3[*var_a2_3 * 4 + 3]);
            var_a2_3++;
            prim->x1 = add(xBase, temp_a3[*var_a2_3 * 4 + 1]);
            prim->y1 = add(yBase, temp_a3[*var_a2_3 * 4 + 3]);
            var_a2_3++;
            prim->x2 = add(xBase, temp_a3[*var_a2_3 * 4 + 1]);
            prim->y2 = add(yBase, temp_a3[*var_a2_3 * 4 + 3]);
            var_a2_3++;
            prim->x3 = add(xBase, temp_a3[*var_a2_3 * 4 + 1]);
            prim->y3 = add(yBase, temp_a3[*var_a2_3 * 4 + 3]);
            var_a2_3++;

            prim->r0 = prim->g0 = prim->b0 = temp_t0;
            LOW(prim->r1) = LOW(prim->r0);
            LOW(prim->r2) = LOW(prim->r0);
            LOW(prim->r3) = LOW(prim->r0);
            prim = prim->next;
        }
        self->ext.et_801AF774.unk8C =
            ((--self->ext.et_801AF774.unk8E << 0x10) >> 8);
        if (self->ext.et_801AF774.unk8E < 0) {
            self->step = 4;
        }
        if ((self->ext.et_801AF774.unk90 != 0) &&
            (self->ext.et_801AF774.unk8E < 0x10)) {
            self->ext.et_801AF774.unk90 = 0;
            CreateEntityFromCurrentEntity(0x23, self + 1);
        }
        return;
    case 4:
        prim = self->ext.et_801AF774.prim3;
        prim->drawMode =
            DRAW_TPAGE | 0x20 | DRAW_COLORS | DRAW_UNK02 | DRAW_TRANSP;
        prim = prim->next;
        D_801C2578 = 0;
        if (prim != NULL) {
            do {
                prim->drawMode = DRAW_HIDE;
                prim = prim->next;
            } while (prim != NULL);
        }
        self->ext.et_801AF774.unk8E = 0x10;
        self->step++;
        return;
    case 5:
        if (--self->ext.et_801AF774.unk8E == 0) {
            self->step++;
            return;
        }
        break;
    case 7:
        if (PrimDecreaseBrightness(self->ext.et_801AF774.prim3, 7) == 0) {
            D_80180910 = 1;
            DestroyEntity(self);
        }
        break;
    }
}
