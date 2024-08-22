// SPDX-License-Identifier: AGPL-3.0-only
/*
 * Overlay: ST0
 * Enemy: Dracula Boss
 */

#include "st0.h"
#include "sfx.h"

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

    if ((self->flags & FLAG_DEAD) && (self->step < 8)) {
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
                g_api.PlaySfx(SFX_FIREBALL_SHOT_A);
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
        self->flags |= FLAG_DEAD;
    }

    if (self->flags & FLAG_DEAD) {
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
        self->ext.dracula.unk8C = 0x28;

    case 1:
        AnimateEntity(D_8018097C, self);
        MoveEntity();

        if (--self->ext.dracula.unk8C == 0) {
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
