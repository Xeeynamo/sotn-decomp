/*
 * Overlay: ST0
 * Enemy: Dracula Boss
 */

#include "st0.h"

void EntityDracula(Entity* self) {
    s16 primIndex;
    Entity* newEntity;
    Primitive* prim;
    s16 temp_v1_8;
    u16 temp_v1_6;
    s32 var_a0_2;
    s16 temp_19;
    s16 temp_20;
    s32 var_a1;
    s32 index;
    u16 posX;
    s32 i;

    if ((self->flags & 0x100) && (self->step < 8)) {
        self->hitboxState = 0;
        self[1].hitboxState = 0;
        SetStep(8);
    }

    index = 1; // !FAKE

    if (self->hitFlags == 1) {
        g_api.PlaySfx(NA_SE_VO_DR_HURT_2);
    }

    if (self->hitFlags == 2) {
        g_api.PlaySfx(NA_SE_VO_DR_HURT_3);
    }

    if (self->hitFlags == 3) {
        g_api.PlaySfx(NA_SE_VO_DR_HURT_4);
    }

    switch (self->step) {
    case 0:
        InitializeEntity(D_801805E0);
        self->animCurFrame = 0x4F;
        self->ext.dracula.unkA1 = 1;
        self->hitboxState = 0;
        self->facingLeft = 1;
        CreateEntityFromCurrentEntity(0x1D, &self[1]);
        self[1].zPriority = self->zPriority + 1;

        primIndex = g_api.func_800EDB58(PRIM_GT4, 128);
        if (primIndex == -1) {
            self->step = 0;
            break;
        }

        prim = &g_PrimBuf[primIndex];
        self->primIndex = primIndex;
        self->ext.dracula.prim = prim;
        self->flags |= FLAG_HAS_PRIMS;
        while (prim != NULL) {
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
        SetStep(2);
        break;

    case 2:
        SetStep(3);
        break;

    case 3:
        switch (self->step_s) {
        case 0:
            if (D_801C257C & 0x10) {
                SetSubStep(1);
            }
            break;

        case 1:
            if ((AnimateEntity(D_80180A0C, self) == 0) && (D_801C257C & 0x20)) {
                SetSubStep(2);
            }
            break;

        case 2:
            if (AnimateEntity(D_80180A20, self) == 0) {
                D_801C257C |= 0x100;
            }
            if (D_801C257C & 0x40) {
                D_8003C744 = 1;
                SetSubStep(3);
            }
            if (self->animFrameIdx == 2 && self->animFrameDuration == 0) {
                newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (newEntity != NULL) {
                    CreateEntityFromEntity(0x1F, self, newEntity);
                    newEntity->facingLeft = self->facingLeft;
                    newEntity->posX.i.hi -= 8;
                    newEntity->posY.i.hi -= 24;
                }
            }
            break;

        case 3:
            if (AnimateEntity(D_80180A2C, self) == 0) {
                g_api.TimeAttackController(
                    TIMEATTACK_EVENT_DRACULA_DEFEAT, TIMEATTACK_SET_VISITED);
                SetStep(4);
            }
        }
        break;

    case 4:
        switch (self->step_s) {
        case 0:
            self->hitboxState = 0;
            self->ext.dracula.unk9C = 0;
            self->step_s++;

        case 1:
            self->ext.dracula.unk9C =
                func_801ABBBC(self->ext.dracula.unk9C, self);
            if (self->ext.dracula.unkA0 != 0) {
                g_api.PlaySfx(NA_SE_VO_DR_TAUNT_2);
                self->animCurFrame = 0;
                self->ext.dracula.unkA0 = 0;
            }
            if (self->ext.dracula.unk9C != 0xFF) {
                break;
            }
            self->step_s++;
            break;

        case 2:
            SetStep(5);
        }
        break;

    case 5:
        switch (self->step_s) {
        case 0:
            self->ext.dracula.unk8C = 0x80;
            self->step_s++;

        case 1:
            if (--self->ext.dracula.unk8C == 0) {
                posX = D_80180A48[Random() & 7];
                self->posY.i.hi = 0x82;
                self->ext.dracula.unk9C = 0;
                self->posX.i.hi = posX;
                self->step_s++;
            }
            break;

        case 2:
            self->ext.dracula.unk9C =
                func_801ABBBC(self->ext.dracula.unk9C, self);
            if (self->ext.dracula.unkA0 != 0) {
                g_api.PlaySfx(NA_SE_VO_DR_TAUNT_1);
                self->animCurFrame = 1;
                self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
                self->ext.dracula.unkA0 = 0;
            }
            if (self->ext.dracula.unk9C != 0xFF) {
                break;
            }
            self->step_s++;
            break;

        case 3:
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            self->ext.dracula.unkA2 = (self->ext.dracula.unkA2 + 1) & 3;
            self->hitboxState = 3;
            if (self->ext.dracula.unkA2 == 0) {
                SetStep(6);
                break;
            }
            SetStep(7);
        }
        break;

    case 7:
        switch (self->step_s) {
        case 0:
            if (AnimateEntity(D_80180914, self) == 0) {
                self[1].animFrameDuration = 0;
                self[1].animFrameIdx = 0;
                SetSubStep(1);
                g_api.PlaySfx(NA_SE_VO_DR_HURT_1);
            }
            break;

        case 1:
            if (AnimateEntity(D_801809A4, &self[1]) == 0) {
                self[1].animCurFrame = 0;
                SetSubStep(2);
            }
            break;

        case 2:
            for (i = 0; i < 3; i++) {
                newEntity = AllocEntity(&g_Entities[160], &g_Entities[192]);
                if (newEntity != NULL) {
                    CreateEntityFromEntity(0x1B, self, newEntity);
                    newEntity->facingLeft = self->facingLeft;
                    newEntity->zPriority = self->zPriority + 1;
                    newEntity->params = i;
                    if (self->facingLeft != 0) {
                        newEntity->posX.i.hi -= 24;
                    } else {
                        newEntity->posX.i.hi += 24;
                    }
                    newEntity->posY.i.hi += 44;
                }
            }
            self->step_s++;

        case 3:
            if (AnimateEntity(D_80180924, self) == 0) {
                SetStep(4);
            }
        }
        break;

    case 6:
        switch (self->step_s) {
        case 0:
            if (AnimateEntity(D_80180934, self) == 0) {
                SetSubStep(1);
                self->ext.dracula.unk8C = 2;
                g_api.PlaySfx(NA_SE_EN_DR_FIREBALL);
                g_api.PlaySfx(NA_SE_VO_DR_HERE_IS_TRUE_POWER);
            }
            break;

        case 1:
        case 2:
            if (--self->ext.dracula.unk8C == 0) {
                newEntity = AllocEntity(&g_Entities[160], &g_Entities[192]);
                if (newEntity != NULL) {
                    CreateEntityFromEntity(0x1C, self, newEntity);
                    index = self->step_s - 1;
                    newEntity->facingLeft = self->facingLeft;
                    if (self->facingLeft != 0) {
                        newEntity->posX.i.hi += D_80180A58[index].x;
                    } else {
                        newEntity->posX.i.hi -= D_80180A58[index].x;
                    }
                    newEntity->posY.i.hi += D_80180A58[index].y;
                    newEntity->zPriority = self->zPriority + 1;
                    newEntity->params = index;
                }
                self->ext.dracula.unk8C = 0x20;
                self->step_s++;
            }
            break;

        case 3:
            if (--self->ext.dracula.unk8C == 0) {
                self->step_s++;
            }
            break;

        case 4:
            if (AnimateEntity(D_80180944, self) == 0) {
                SetStep(4);
            }
        }
        break;

    case 8:
        switch (self->step_s) {
        case 0:
            prim = self->ext.dracula.prim;
            self->hitboxState = 0;
            g_isDraculaFirstFormDefeated = 1;
            while (prim != NULL) {
                prim->drawMode = DRAW_HIDE;
                prim = prim->next;
            }
            g_api.PlaySfx(NA_SE_VO_DR_PLAYTIME_IS_OVER);
            self->step_s++;

        case 1:
            if (AnimateEntity(D_80180954, self) == 0) {
                self->ext.dracula.unk8C = 0x28;
                self->unk5A = 0x59;
                self->step_s++;
            }
            if (self->animFrameIdx == 5 && self->animFrameDuration == 0) {
                g_api.func_80102CD8(2);
            }
            break;

        case 2:
            if (--self->ext.dracula.unk8C == 0) {
                g_api.PlaySfx(NA_SE_VO_DR_GRANT_ME_POWER);
                self->step_s++;
            }
            break;

        case 3:
            prim = self->ext.dracula.prim;
            self->ext.dracula.unk94 = 0x40;
            self->ext.dracula.unk98 = 0;
            self->unk6C = 0x80;
            self->drawFlags |= 8;
            prim->type = PRIM_G4;
            prim->x0 = prim->x2 = self->posX.i.hi;
            prim->x1 = prim->x3 = self->posX.i.hi;
            prim->y0 = prim->y1 = 0;
            prim->y2 = prim->y3 = 0x100;
            prim->r0 = prim->g0 = prim->b0 = self->ext.dracula.unk94;
            prim->priority = 0xC0;
            prim->drawMode = 0x31;
            LOW(prim->r1) = LOW(prim->r0);
            LOW(prim->r2) = LOW(prim->r0);
            LOW(prim->r3) = LOW(prim->r0);
            prim = prim->next;
            prim->type = PRIM_G4;
            prim->x0 = prim->x2 = self->posX.i.hi;
            prim->x1 = prim->x3 = self->posX.i.hi;
            prim->y0 = prim->y1 = prim->r0 = prim->g0 = prim->b0 = 0;
            prim->y2 = prim->y3 = 0x100;
            LOW(prim->r2) = LOW(prim->r0);
            prim->r1 = prim->g1 = prim->b1 = self->ext.dracula.unk94;
            prim->priority = 0xC0;
            prim->drawMode = 0x31;
            LOW(prim->r3) = LOW(prim->r1);
            prim = prim->next;
            prim->type = PRIM_G4;
            prim->x0 = prim->x2 = self->posX.i.hi;
            prim->x1 = prim->x3 = self->posX.i.hi;
            prim->y0 = prim->y1 = 0;
            prim->y2 = prim->y3 = 0x100;
            prim->r0 = prim->g0 = prim->b0 = self->ext.dracula.unk94;
            prim->r1 = prim->g1 = prim->b1 = 0;
            prim->priority = 0xC0;
            prim->drawMode = 0x31;
            LOW(prim->r2) = LOW(prim->r0);
            LOW(prim->r3) = LOW(prim->r1);
            self->ext.dracula.unk8C = 0x20;
            self->step_s++;

        case 4:
            prim = self->ext.dracula.prim;
            prim = prim->next;

            prim->x0 = prim->x2 = prim->x2 - 2;
            prim = prim->next;

            temp_19 = prim->x3 + 2;
            prim->x1 = prim->x3 = temp_19;
            if (self->posX.i.hi != (temp_19 - 0x30)) {
                break;
            }
            self->step_s++;
            break;

        case 5:
            var_a1 = 0;
            temp_20 = self->ext.dracula.unk98 + 4;
            var_a0_2 = self->posX.i.hi - temp_20;
            self->ext.dracula.unk98 = temp_20;
            if (var_a0_2 < 0) {
                var_a1 = 1;
                var_a0_2 = 0;
            }

            prim = self->ext.dracula.prim;
            temp_v1_6 = var_a0_2;
            prim->x0 = prim->x2 = temp_v1_6;
            prim = prim->next;
            prim->x0 = prim->x2 = temp_v1_6 - 0x30;
            prim->x1 = prim->x3 = temp_v1_6;

            var_a0_2 = self->posX.i.hi + self->ext.dracula.unk98;
            if (var_a0_2 > 0x100) {
                var_a1 += 1;
                var_a0_2 = 0x100;
            }
            temp_v1_8 = var_a0_2 + 0x30;

            prim = self->ext.dracula.prim;
            prim->x1 = prim->x3 = var_a0_2;
            prim = prim->next;

            prim = prim->next;
            prim->x0 = prim->x2 = var_a0_2;
            prim->x1 = prim->x3 = temp_v1_8;

            if (self->unk6C != 0) {
                self->unk6C += 0xF8;
            }

            if (self->ext.dracula.unk94 < 0xF0) {
                self->ext.dracula.unk94 += 8;
            }

            prim = self->ext.dracula.prim;
            prim->r0 = prim->g0 = prim->b0 = self->ext.dracula.unk94;
            LOW(prim->r1) = LOW(prim->r0);
            LOW(prim->r2) = LOW(prim->r0);
            LOW(prim->r3) = LOW(prim->r0);

            prim = prim->next;
            prim->r0 = prim->g0 = prim->b0 = 0;
            LOW(prim->r2) = LOW(prim->r0);
            prim->r1 = prim->g1 = prim->b1 = self->ext.dracula.unk94;
            LOW(prim->r3) = LOW(prim->r1);

            prim = prim->next;
            prim->r0 = prim->g0 = prim->b0 = self->ext.dracula.unk94;
            prim->r1 = prim->g1 = prim->b1 = 0;
            LOW(prim->r2) = LOW(prim->r0);
            LOW(prim->r3) = LOW(prim->r1);

            if (var_a1 == 2) {
                self->step_s++;
            }
            break;

        case 6:
            prim = self->ext.dracula.prim;
            prim = prim->next;
            while (prim != NULL) {
                prim->drawMode = DRAW_HIDE;
                prim = prim->next;
            }
            CreateEntityFromCurrentEntity(0x2B, &self[2]);
            self[2].facingLeft = self->facingLeft;
            CreateEntityFromCurrentEntity(0x20, &self[5]);
            self[5].facingLeft = self->facingLeft;
            self[5].posY.i.hi += 2;
            self->step_s++;
            break;

        case 7:
            if (PrimDecreaseBrightness(self->ext.dracula.prim, 7) == 0) {
                self->step_s++;
            }
            break;

        case 8:
            if (D_801C2578 == 0) {
                DestroyEntity(self);
            }
        }
        break;

    case 255:
        /**
         * Debug: Press SQUARE / CIRCLE on the second controller
         * to advance/rewind current animation frame
         */
        if (g_pads[1].pressed & PAD_SQUARE) {
            if (self->params == 0) {
                self->animCurFrame++;
                self->params |= 1;
            } else {
                break;
            }
        } else {
            self->params = 0;
        }
        if (g_pads[1].pressed & PAD_CIRCLE) {
            if (self->step_s == 0) {
                self->animCurFrame--;
                self->step_s |= 1;
                break;
            }
        } else {
            self->step_s = 0;
        }
        break;
    }
}

void EntityDraculaBody(Entity* self) {
    if (g_isDraculaFirstFormDefeated) {
        DestroyEntity(self);
    }

    switch (self->step) {
    case 0:
        InitializeEntity(D_801805E0);
        self->hitboxState = 1;
        self->hitPoints = 0x7FFF;
        self->hitboxOffX = 3;
        self->hitboxOffY = 0x27;
        self->hitboxWidth = 12;
        self->animCurFrame = 0;
        self->hitboxHeight = 34;
        break;
    case 1:
        self->facingLeft = self[-1].facingLeft;
        self->posX.i.hi = self[-1].posX.i.hi;
        self->posY.i.hi = self[-1].posY.i.hi;
        self->hitboxState = self[-1].hitboxState & 0xFFFD;
        break;
    case 2:
        self->hitboxState = 0;
        break;
    }

    if (g_isDraculaFirstFormDefeated) {
        self->hitboxState = 0;
    }
}

void EntityDraculaFireball(Entity* self) {
    if (g_isDraculaFirstFormDefeated) {
        self->flags |= 0x100;
    }

    if (self->flags & 0x100) {
        self->pfnUpdate = EntityExplosion;
        self->step = 0;
        self->params = 2;
        return;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(D_801805EC);

        if (self->facingLeft == 0) {
            self->velocityX = FIX(-2);
        } else {
            self->velocityX = FIX(2);
        }

        if (self->params == 1) {
            self->velocityY = FIX(-0.5);
        }

        if (self->params == 2) {
            self->velocityY = FIX(0.5);
        }
        self->ext.generic.unk8C.modeU16.unk0 = 0x28;

    case 1:
        AnimateEntity(D_8018097C, self);
        MoveEntity();

        if (--self->ext.generic.unk8C.modeS16.unk0 == 0) {
            self->velocityY = 0;
        }
        return;
    }
}

extern u16 D_801805F8[];
extern u8 D_80180990[];
extern u8 D_801809B0[];
extern s16 D_80180A60[];
extern s16 D_80180A62[];
void EntityDraculaMeteorball(Entity* entity) {
    s32 speedX;

    if (g_isDraculaFirstFormDefeated) {
        entity->entityId = E_EXPLOSION;
        entity->pfnUpdate = EntityExplosion;
        entity->step = 0;
        entity->step_s = 0;
        entity->params = 1;
        return;
    }

    switch (entity->step) {
    case 0:
        InitializeEntity(D_801805F8);
        entity->hitboxState = 0;
        entity->drawFlags |= 4;
        break;
    case 1:
        if (AnimateEntity(D_801809B0, entity) == 0) {
            entity->hitboxState = 1;
            SetStep(2);
        }
        break;
    case 2:
        AnimateEntity(D_80180990, entity);
        MoveEntity();
        entity->rotZ += 4;
        speedX = 0x1000;
        if (entity->params != 0) {
            speedX = 0xE00;
        }

        if (entity->facingLeft != 0) {
            entity->velocityX += speedX;
        } else {
            entity->velocityX -= speedX;
        }

        if (!(g_Timer & 3)) {
            Entity* newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (newEntity != 0) {
                s32 randomPosXYIndex;
                CreateEntityFromEntity(0x1E, entity, newEntity);
                newEntity->zPriority = entity->zPriority + 1;
                randomPosXYIndex = (Random() & 3) * 2;
                newEntity->posX.i.hi =
                    newEntity->posX.i.hi + D_80180A60[randomPosXYIndex];
                newEntity->posY.i.hi =
                    newEntity->posY.i.hi + D_80180A62[randomPosXYIndex];
            }
        }
        break;
    }
}

extern u16 D_801805EC[];
extern u8 D_801809E0[];
void func_801AD838(Entity* entity) {
    if (g_isDraculaFirstFormDefeated) {
        DestroyEntity(entity);
        return;
    }

    if (entity->step == 0) {
        InitializeEntity(D_801805EC);
        entity->animCurFrame = 0;
        entity->hitboxState = 0;
        entity->velocityY = FIX(-1);
    }
    MoveEntity();

    if (AnimateEntity(D_801809E0, entity) == 0) {
        DestroyEntity(entity);
    }
}

extern u16 D_801805EC[];
extern u8 D_80180A40[];
void EntityDraculaGlass(Entity* entity) {
    switch (entity->step) {
    case 0:
        InitializeEntity(D_801805EC);
        entity->animCurFrame = 0x59;
        entity->drawFlags = FLAG_DRAW_ROTZ;
        entity->hitboxState = 0;
        entity->velocityX = FIX(-1);
        entity->velocityY = 0;
        if (entity->params) {
            s16 radians;
            s32 speed;
            entity->animCurFrame = 0x5C;
            speed = (Random() & 0x1F) + 0x10;
            radians = (Random() * 6) + 0x900;
            entity->velocityX = speed * rcos(radians);
            entity->velocityY = speed * rsin(radians);
            SetStep(3);
        }
    case 1:
        MoveEntity();
        entity->rotZ += 0x20;
        entity->velocityY += FIX(0.125);
        if (entity->posY.i.hi >= 205) {
            g_api.PlaySfx(NA_SE_BREAK_GLASS);
            entity->posY.i.hi = 204;
            SetStep(2);
        }
        break;
    case 2:
        entity->drawFlags = 0;
        if (AnimateEntity(D_80180A40, entity) == 0) {
            s32 i;
            for (i = 0; i < 8; i++) {
                Entity* glassShardEntity =
                    AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (glassShardEntity != 0) {
                    CreateEntityFromEntity(31, entity, glassShardEntity);
                    glassShardEntity->params = 1;
                }
            }
            DestroyEntity(entity);
        }
        break;
    case 3:
        MoveEntity();
        entity->velocityY += FIX(0.125);
        if (entity->posY.i.hi >= 205) {
            DestroyEntity(entity);
        }
        break;
    }
}

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

Entity* AllocEntity(Entity* start, Entity* end);                /* extern */
s32 AnimateEntity(const u8 frames[], Entity* entity);
void CreateEntityFromCurrentEntity(u16, Entity*);
void CreateEntityFromEntity(u16 entityId, Entity* ent1, Entity* ent2);
s16 GetSideToPlayer(void);                              /* extern */
void InitializeEntity(u16 self[]);
void MoveEntity();
s32 Random();                                     /* extern */
void SetStep(u8);
void SetSubStep(u8 step_s);                                    /* extern */
bool func_801ADAC8(s32 self);                               /* extern */
extern Entity D_8007D858;
extern u16 D_80180604[];
extern s32 D_80180910;
//Animations
extern u8 D_80180AA4[];
extern u8 D_80180AB0[];
extern u8 D_80180AC8[];
extern u8 D_80180AD4[];
extern u8 D_80180AEC[];
extern u8 D_80180AFC[];
extern u8 D_80180B20[];
extern u8 D_80180B48[];
extern u8 D_80180B58[];
extern u8 D_80180B60[];
extern u8 D_80180B80[];
// End animations
extern u16 D_80180BE4[];
extern s16 D_801810F4[];
extern Point16 D_80181108[];
extern s32 D_80181148;
extern u32 D_8018114C;
extern s8 D_801A7B7C;
extern s32 D_801C2578;

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
    s32 mainStep;

    if (self->flags & 0x100) {
        self->hitboxState = 0;
        if (self->step < 6U) {
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
    mainStep = self->step;
    switch (mainStep) {
    case 0x0:                                       /* switch 4 */
        InitializeEntity(D_80180604);
        self->hitboxHeight = 0x10;
        self->hitboxWidth = 0x10;
        self->hitboxOffX = -0x18;
        self->hitboxOffY = -0x10;
        self->hitboxState = 0;
        if (self->params == 0) {
            temp_s2 = self + 1;
            D_8003C744 = 2;
            var_s1 = self + 1;
            self->animCurFrame = 0;
            for(i = 1; i < 4; i++, temp_s2++, var_s1++) {
                CreateEntityFromCurrentEntity(0x20, temp_s2);
                selfzPriority = self->zPriority;
                var_s1->params = i;
                var_s1->unk60 = temp_s2 - 1;
                var_s1->unk5C = self;
                
                var_s1->zPriority = selfzPriority + 2;
                var_s1->hitPoints = 0x7FFE;
            }
            self->unk5C = 0;
            self->unk60 = self + 3;
            return;
        }
        self->animCurFrame = 0;
        SetStep(0x10);
        return;
    case 0x1:                                       /* switch 4 */
        if (D_801C2578 == 0) {
            self->animCurFrame = 1;
        }
        if (D_80180910 != 0) {
            self->animCurFrame = 1;
            self->hitboxState = 3U;
            self->unk6C = 0x80;
            self->drawFlags = 0;
            SetStep(2);
        }
        break;
    case 0x2:                                       /* switch 4 */
        if (self->step_s == 0) {
            self->ext.factory.unk80 = 0x50;
            self->step_s = (self->step_s + 1);
        }
        if ((AnimateEntity(D_80180AA4, self) == 0) && (((GetSideToPlayer() & 1) ^ 1) != self->facingLeft)) {
            SetStep(3);
        }
        if (--self->ext.factory.unk80 == 0) {
            SetStep(5);
            if ((self->posX.i.hi < 0x98) && (self->facingLeft == 1)) {
                if (Random() & 1) {
                    SetStep(7);
                } else {
                    SetStep(4);
                }
            } else if ((self->posX.i.hi >= 0x69) && (self->facingLeft == 0)) {
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
    case 0x7:                                       /* switch 4 */
        switch (self->step_s) {                        /* switch 5; irregular */
        case 0:                                     /* switch 5 */
            self->velocityX = 0;
            self->velocityY = 0;
            self->step_s++;
            /* fallthrough */
        case 1:                                     /* switch 5 */
            if (AnimateEntity(D_80180AB0, self) == 0) {
                SetSubStep(2);
            }
            if (self->animFrameIdx == 5 && self->animFrameDuration == 0) {
                if (self->facingLeft){
                    self->velocityX = 0x8000;
                } else {
                    self->velocityX = -0x8000;
                }
                self->velocityY = -0x40000;
            }
            MoveEntity();
            if (self->velocityY != 0) {
                self->velocityY += 0x1400;
                return;
            }
            break;
        case 2:                                     /* switch 5 */
            MoveEntity();
            self->velocityY += 0x1400;
            if (self->velocityY >= 0) {
                AnimateEntity(D_80180AC8, self);
            }
            if (func_801ADAC8(0x4C) != 0) {
                g_api.PlaySfx(0x63D);
                g_api.func_80102CD8(1);
                self->step_s++;
                return;
            }
            break;
        case 3:                                     /* switch 5 */
            if (AnimateEntity(D_80180AD4, self) == 0) {
                SetStep(2);
                return;
            }
            break;
        }
        break;
    case 0x3:                                       /* switch 4 */
        if (AnimateEntity(D_80180B60, self) == 0) {
            if ((self->posX.i.hi < 0xA0) && (self->facingLeft == 1)) {
                if (Random() & 1) {
                    SetStep(4);
                } else {
                    SetStep(7);
                }
            } else if ((self->posX.i.hi >= 0x61) && (self->facingLeft == 0)) {
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
            return;
        }
        break;
    case 0x4:                                       /* switch 4 */
        switch (self->step_s) {                        /* switch 6; irregular */
        case 0:                                     /* switch 6 */
            if (AnimateEntity(D_80180B48, self) == 0) {
                g_api.PlaySfx(0x866);
                self->step_s++;
                return;
            }
            break;
        case 1:                                     /* switch 6 */
            temp_s2 = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (temp_s2 != NULL) {
                CreateEntityFromEntity(0x21, self, temp_s2);
                temp_s2->posX.i.hi = temp_s2->posX.i.hi;
                temp_s2->posY.i.hi = temp_s2->posY.i.hi;
                temp_s2->facingLeft = self->facingLeft;
                temp_s2->params = 1;
            }
            self->ext.factory.unk80 = 0x20;
            self->step_s++;
            return;
        case 2:                                     /* switch 6 */
            //FAKE assignment to i
            if (i = --self->ext.factory.unk80 == 0) {
                self->ext.factory.unk84 = 0;
                self->step_s++;
                return;
            }
            break;
        case 3:                                     /* switch 6 */
            if (self->ext.factory.unk80 != 0) {
                self->ext.factory.unk80--;
                return;
            }
            self->ext.factory.unk80 = 0x30;
            temp_s1 = &D_801810F4;
            temp_s1 += self->ext.factory.unk84;
            if (*temp_s1 == -1) {
                SetStep(2);
                return;
            }
            if (self->facingLeft != 0) {
                xShift = 0x20;
            } else {
                xShift = -0x20;
            }
            temp_s2 = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (temp_s2 != NULL) {
                g_api.PlaySfx(0x660);
                CreateEntityFromEntity(0x21, self, temp_s2);
                temp_s2->posX.i.hi = (xShift + temp_s2->posX.i.hi);
                temp_s2->posY.i.hi = (temp_s2->posY.i.hi - 4);
                temp_s2->rotZ = *temp_s1;
                if (self->facingLeft != 0) {
                    temp_s2->rotZ = (0x800 - temp_s2->rotZ);
                }
            }
            self->ext.factory.unk84++;
        }
        break;
    case 0x8:                                       /* switch 4 */
        switch (self->step_s) {                        /* switch 7; irregular */
        case 0:                                     /* switch 7 */
            self->velocityX = 0;
            self->velocityY = 0;
            self->ext.factory.unk80 = 4;
            self->ext.factory.unk84 = 0;
            self->step_s = (self->step_s + 1);
            /* fallthrough */
        case 1:                                     /* switch 7 */
            if (AnimateEntity(D_80180B80, self) == 0) {
                SetSubStep(2);
            }
            if (self->animFrameIdx == 3 && self->animFrameDuration == 0) {
                g_api.PlaySfx(0x866);
                self->velocityY = -0x70000;
            }
            MoveEntity();
            if (self->velocityY != 0) {
                self->velocityY += 0x1800;
            }
            if (--self->ext.factory.unk80 == 0) {
                temp_s1 = &D_801810F4[4];
                temp_s1 += self->ext.factory.unk84;
                if (*temp_s1 == -1) {
                    self->ext.factory.unk80 = 0x7FFF;
                    return;
                }
                self->ext.factory.unk80 = 6;
                temp_s2 = AllocEntity(&g_Entities[160], &g_Entities[192]);
                if (temp_s2 != NULL) {
                    g_api.PlaySfx(0x661);
                    CreateEntityFromEntity(0x22, self, temp_s2);
                    temp_s2->posX.i.hi = (temp_s2->posX.i.hi + *temp_s1);
                    temp_s2->zPriority = (self->zPriority + 1);
                }
                self->ext.factory.unk84++;
                return;
            }
            break;
        case 2:                                     /* switch 7 */
            MoveEntity();
            self->velocityY += 0x2000;
            if (self->velocityY >= 0) {
                AnimateEntity(D_80180AC8, self);
            }
            if (func_801ADAC8(0x4C) != 0) {
                g_api.PlaySfx(0x63D);
                g_api.func_80102CD8(1);
                self->step_s++;
                return;
            }
            break;
        case 3:                                     /* switch 7 */
            if (AnimateEntity(D_80180AD4, self) == 0) {
                SetStep(2);
                return;
            }
        }
        break;
    case 0x5:                                       /* switch 4 */
        switch (self->step_s) {                        /* switch 1 */
        case 0:                                     /* switch 1 */
            if (AnimateEntity(D_80180AEC, self) == 0) {
                SetSubStep(1);
                return;
            }
            break;
        case 1:                                     /* switch 1 */
            if (AnimateEntity(D_80180AFC, self) == 0) {
                g_api.PlaySfx(0x856);
                temp_s2 = AllocEntity(&g_Entities[160], &g_Entities[192]);
                if (temp_s2 != NULL) {
                    CreateEntityFromEntity(0x2E, self, temp_s2);
                    if (self->facingLeft != 0) {
                        temp_s2->posX.i.hi += 0x28;
                    } else {
                        temp_s2->posX.i.hi -= 0x28;
                    }
                    temp_s2->posY.i.hi += 0x10;
                    temp_s2->facingLeft = self->facingLeft;
                }
                SetSubStep(2);
                return;
            }
            break;
        case 2:                                     /* switch 1 */
            if (AnimateEntity(D_80180B20, self) == 0) {
                SetSubStep(3);
                return;
            }
            break;
        case 3:                                     /* switch 1 */
            self->ext.factory.unk80 = 0x100;
            self->step_s++;
            return;
        case 4:                                     /* switch 1 */
            if (--self->ext.factory.unk80 == 0) {
                SetStep(2);
                return;
            }
        }
        break;
    case 0x10:                                      /* switch 4 */
        temp_s2 = self - self->params ;
        self->facingLeft = temp_s2->facingLeft;
        self->hitboxState = temp_s2->hitboxState;
        temp_s1 = &D_80180BE4;
        self->posX.i.hi = temp_s2->posX.i.hi;
        self->posY.i.hi = temp_s2->posY.i.hi;
        //Fake reuse of the i variable
        i = temp_s2->animCurFrame - 1;
        temp_s1 += i*12;
        temp_s1 += (self->params - 1) * 4;
        self->hitboxOffX = *temp_s1++;
        self->hitboxOffY = *temp_s1++;

        self->hitboxWidth = *temp_s1++;
        self->hitboxHeight = *temp_s1++;
        if (self->params == 1) {
            switch (self->step_s) {                    /* switch 2 */
            case 0:                                 /* switch 2 */
                self->ext.factory.unk80 = 0x64;
                self->step_s++;
                return;
            case 1:                                 /* switch 2 */
                if (--self->ext.factory.unk80 == 0) {
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
                    return;
                }
                break;
            case 2:                                 /* switch 2 */
                self->rotX = self->rotY = self->rotY - 0x18;
                if (self->rotY < 0x100) {
                    self->animCurFrame = 0;
                    self->drawMode = 0;
                    self->drawFlags = 0;
                    self->step_s++;
                    return;
                }
                break;
            case 3:                                 /* switch 2 */
                if (D_801C2578 == 0) {
                    self->animCurFrame = 1;
                    self->unk5A = 0x50;
                    self->palette = 0x815F;
                    self->drawFlags = 8;
                    self->unk6C = 0;
                    self->drawMode = 0x30;
                    self->step_s++;
                    return;
                }
                break;
            case 4:                                 /* switch 2 */
                self->unk6C += 4;
                self->animCurFrame = temp_s2->animCurFrame;
                if (self->unk6C > 0x60) {
                    self->step_s++;
                    return;
                }
                break;
            case 5:                                 /* switch 2 */
                self->unk6C -= 4;
                self->animCurFrame = temp_s2->animCurFrame;
                if (self->unk6C == 0) {
                    self->animCurFrame = 0;
                    self->drawMode = 0;
                    self->drawFlags = 0;
                    self->step_s++;
                    return;
                }
                break;
            }
        }
        break;
    case 0x6:                                       /* switch 4 */
        switch (self->step_s) {                        /* switch 3 */
        case 0:                                     /* switch 3 */
            g_api.PlaySfx(0x866);
            temp_s2 = self + 1;
            self->hitboxState = 0;
            for(i = 0; i < 3; i++) {
                DestroyEntity(temp_s2);
                temp_s2++;
            }
            g_api.PlaySfx(0x80);
            self->ext.factory.unk80 = 4;
            self->ext.factory.unk84 = 0;
            g_api.TimeAttackController(TIMEATTACK_EVENT_DRACULA_DEFEAT, TIMEATTACK_SET_RECORD);
            D_8003C8B8 = 0;
            D_80181148 = 0x800;
            self->step_s = (self->step_s + 1);
            /* fallthrough */
        case 1:                                     /* switch 3 */
            if (AnimateEntity(D_80180B58, self) == 0) {
                self->step_s++;
            }
            break;
        case 2:                                     /* switch 3 */
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
        case 3:                                     /* switch 3 */
            if (g_api.func_80131F68() == false) {
                // Fake reuse of the i variable
                i = g_Timer - D_8018114C;
                if (i >= 0x301) {
                    g_api.PlaySfx(0x654);
                    self->ext.factory.unk82 = 0x80;
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
                g_api.PlaySfx(0x654);
                self->ext.factory.unk82 = 0x80;
                self->step_s++;
            }
            break;
        case 4:                                     /* switch 3 */
            if (--self->ext.factory.unk82 == 0) {
                self->step_s++;
            }
            break;
        case 5:                                     /* switch 3 */
            CreateEntityFromCurrentEntity(0x2C, self + 1);
            self->step_s++;
            primIndex = g_api.AllocPrimitives(PRIM_G4, 1);
            if (primIndex == -1) {
                D_8003C9A4 = 0xA;
                g_MenuStep = 0;
                return;
            }
            prim = &g_PrimBuf[primIndex];
            self->primIndex = primIndex;
            self->ext.prim = prim;
            self->flags |= 0x800000;
            prim->r0 = prim->g0 = prim->b0 = 0;
            LOW(prim->r1) = LOW(prim->r0);
            LOW(prim->r2) = LOW(prim->r0);
            LOW(prim->r3) = LOW(prim->r0);
            prim->x0 = prim->x2 = 0;
            prim->x1 = prim->x3 = 0x100;
            prim->y0 = prim->y1 = 0;
            prim->y2 = prim->y3 = 0x100;
            prim->priority = self->zPriority + 0x10;
            prim->drawMode = 0x31;
            self->step_s++;
        case 6:                                     /* switch 3 */
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
        if (--self->ext.factory.unk80 == 0) {
            g_api.PlaySfx(0x655);
            self->ext.factory.unk80 = 8;
            temp_s2 = AllocEntity(&g_Entities[224], &g_Entities[256]);
            temp_s1 = &D_80181108[self->ext.factory.unk84].x;
            if (temp_s2 != NULL) {
                CreateEntityFromEntity(2, self, temp_s2);
                temp_s2->params = 3;
                temp_s2->zPriority = (self->zPriority + 1);
                temp_s2->posX.i.hi = (temp_s2->posX.i.hi + *temp_s1++);
                temp_s2->posY.i.hi = (temp_s2->posY.i.hi + *temp_s1++);
            }
            self->ext.factory.unk84 = ((self->ext.factory.unk84 + 1) & 0xF);
            return;
        }
        break;
    case 0xFF:                                      /* switch 4 */
        FntPrint("charal %x\n", self->animCurFrame);
        if (g_pads[1].pressed & 0x80) {
            //uncomment to add eight 00 bytes
            //const char* pad_data = "";
            if (self->params != 0) {
                return;
            }
            self->animCurFrame++;
            self->params |= 1;
        } else {
            self->params = 0;
        }
        if (g_pads[1].pressed & 0x20) {
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

    if (self->flags & 0x100) {
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
        prim->drawMode = 0x35;
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
        prim->drawMode = 0x35;
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
        self->ext.aguneaCrash.unk8B[5] = 1;
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
        if ((self->ext.aguneaCrash.unk8B[5] != 0) &&
            (self->ext.et_801AF774.unk8E < 0x10)) {
            self->ext.aguneaCrash.unk8B[5] = 0;
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
