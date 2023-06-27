/*
 * Overlay: ST0
 * Enemy: Dracula Boss
 */

#include "st0.h"

void EntityDracula(Entity* self) {
    s16 firstPrimIndex;
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
        self->unk3C = 0;
        self[1].unk3C = 0;
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
        self->unk3C = 0;
        self->facing = 1;
        CreateEntityFromCurrentEntity(0x1D, &self[1]);
        self[1].zPriority = self->zPriority + 1;

        firstPrimIndex = g_api.func_800EDB58(PRIM_GT4, 128);
        if (firstPrimIndex == -1) {
            self->step = 0;
            break;
        }

        prim = &g_PrimBuf[firstPrimIndex];
        self->firstPolygonIndex = firstPrimIndex;
        self->ext.dracula.prim = prim;
        self->flags |= FLAG_FREE_POLYGONS;
        while (prim != NULL) {
            prim->blendMode = 8;
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
            if (LOW(self->animFrameIdx) == 2) {
                newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (newEntity != NULL) {
                    CreateEntityFromEntity(0x1F, self, newEntity);
                    newEntity->facing = self->facing;
                    newEntity->posX.i.hi -= 8;
                    newEntity->posY.i.hi -= 24;
                }
            }
            break;

        case 3:
            if (AnimateEntity(D_80180A2C, self) == 0) {
                g_api.func_800FD4C0(0, 2);
                SetStep(4);
            }
        }
        break;

    case 4:
        switch (self->step_s) {
        case 0:
            self->unk3C = 0;
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
                self->facing = (func_801B4C78() & 1) ^ 1;
                self->ext.dracula.unkA0 = 0;
            }
            if (self->ext.dracula.unk9C != 0xFF) {
                break;
            }
            self->step_s++;
            break;

        case 3:
            self->facing = (func_801B4C78() & 1) ^ 1;
            self->ext.dracula.unkA2 = (self->ext.dracula.unkA2 + 1) & 3;
            self->unk3C = 3;
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
                    newEntity->facing = self->facing;
                    newEntity->zPriority = self->zPriority + 1;
                    newEntity->subId = i;
                    if (self->facing != 0) {
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
                    newEntity->facing = self->facing;
                    if (self->facing != 0) {
                        newEntity->posX.i.hi += D_80180A58[index].x;
                    } else {
                        newEntity->posX.i.hi -= D_80180A58[index].x;
                    }
                    newEntity->posY.i.hi += D_80180A58[index].y;
                    newEntity->zPriority = self->zPriority + 1;
                    newEntity->subId = index;
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
            self->unk3C = 0;
            g_isDraculaFirstFormDefeated = 1;
            while (prim != NULL) {
                prim->blendMode = 8;
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
            if (LOW(self->animFrameIdx) == 5) {
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
            self->unk19 |= 8;
            prim->type = PRIM_G4;
            prim->x0 = prim->x2 = self->posX.i.hi;
            prim->x1 = prim->x3 = self->posX.i.hi;
            prim->y0 = prim->y1 = 0;
            prim->y2 = prim->y3 = 0x100;
            prim->r0 = prim->g0 = prim->b0 = self->ext.dracula.unk94;
            prim->priority = 0xC0;
            prim->blendMode = 0x31;
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
            prim->blendMode = 0x31;
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
            prim->blendMode = 0x31;
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
                prim->blendMode = 8;
                prim = prim->next;
            }
            CreateEntityFromCurrentEntity(0x2B, &self[2]);
            self[2].facing = self->facing;
            CreateEntityFromCurrentEntity(0x20, &self[5]);
            self[5].facing = self->facing;
            self[5].posY.i.hi += 2;
            self->step_s++;
            break;

        case 7:
            if (func_801BD88C(self->ext.dracula.prim, 7) == 0) {
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
            if (self->subId == 0) {
                self->animCurFrame++;
                self->subId |= 1;
            } else {
                break;
            }
        } else {
            self->subId = 0;
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
        self->unk3C = 1;
        self->hitPoints = 0x7FFF;
        self->unk10 = 3;
        self->hitboxOffY = 0x27;
        self->hitboxWidth = 12;
        self->animCurFrame = 0;
        self->hitboxHeight = 34;
        break;
    case 1:
        self->facing = self[-1].facing;
        self->posX.i.hi = self[-1].posX.i.hi;
        self->posY.i.hi = self[-1].posY.i.hi;
        self->unk3C = self[-1].unk3C & 0xFFFD;
        break;
    case 2:
        self->unk3C = 0;
        break;
    }

    if (g_isDraculaFirstFormDefeated) {
        self->unk3C = 0;
    }
}

void EntityDraculaFireball(Entity* self) {
    if (g_isDraculaFirstFormDefeated) {
        self->flags |= 0x100;
    }

    if (self->flags & 0x100) {
        self->pfnUpdate = EntityExplosion;
        self->step = 0;
        self->subId = 2;
        return;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(D_801805EC);

        if (self->facing == 0) {
            self->accelerationX = -0x20000;
        } else {
            self->accelerationX = 0x20000;
        }

        if (self->subId == 1) {
            self->accelerationY = -0x8000;
        }

        if (self->subId == 2) {
            self->accelerationY = 0x8000;
        }
        self->ext.generic.unk8C.modeU16.unk0 = 0x28;

    case 1:
        AnimateEntity(D_8018097C, self);
        MoveEntity();

        if (--self->ext.generic.unk8C.modeS16.unk0 == 0) {
            self->accelerationY = 0;
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
        entity->objectId = E_EXPLOSION;
        entity->pfnUpdate = EntityExplosion;
        entity->step = 0;
        entity->step_s = 0;
        entity->subId = 1;
        return;
    }

    switch (entity->step) {
    case 0:
        InitializeEntity(D_801805F8);
        entity->unk3C = 0;
        entity->unk19 |= 4;
        break;
    case 1:
        if (AnimateEntity(D_801809B0, entity) == 0) {
            entity->unk3C = 1;
            SetStep(2);
        }
        break;
    case 2:
        AnimateEntity(D_80180990, entity);
        MoveEntity();
        entity->unk1E += 4;
        speedX = 0x1000;
        if (entity->subId != 0) {
            speedX = 0xE00;
        }

        if (entity->facing != 0) {
            entity->accelerationX += speedX;
        } else {
            entity->accelerationX -= speedX;
        }

        if (!(g_blinkTimer & 3)) {
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
        entity->unk3C = 0;
        entity->accelerationY = -0x10000;
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
        entity->unk19 = 4;
        entity->unk3C = 0;
        entity->accelerationX = -0x10000;
        entity->accelerationY = 0;
        if (entity->subId) {
            s16 radians;
            s32 speed;
            entity->animCurFrame = 0x5C;
            speed = (Random() & 0x1F) + 0x10;
            radians = (Random() * 6) + 0x900;
            entity->accelerationX = speed * rcos(radians);
            entity->accelerationY = speed * rsin(radians);
            SetStep(3);
        }
    case 1:
        MoveEntity();
        entity->unk1E += 0x20;
        entity->accelerationY += 0x2000;
        if (entity->posY.i.hi >= 205) {
            g_api.PlaySfx(NA_SE_BREAK_GLASS);
            entity->posY.i.hi = 204;
            SetStep(2);
        }
        break;
    case 2:
        entity->unk19 = 0;
        if (AnimateEntity(D_80180A40, entity) == 0) {
            s32 i;
            for (i = 0; i < 8; i++) {
                Entity* glassShardEntity =
                    AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (glassShardEntity != 0) {
                    CreateEntityFromEntity(31, entity, glassShardEntity);
                    glassShardEntity->subId = 1;
                }
            }
            DestroyEntity(entity);
        }
        break;
    case 3:
        MoveEntity();
        entity->accelerationY += 0x2000;
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

INCLUDE_ASM("asm/us/st/st0/nonmatchings/2C564", func_801ADB10);

INCLUDE_ASM("asm/us/st/st0/nonmatchings/2C564", EntityDraculaFinalForm);

void EntityDraculaMegaFireball(Entity* self) {
    s16 angle;

    if (self->step == 0) {
        InitializeEntity(D_80180610);
        self->flags |= FLAG_DESTROY_IF_OUT_OF_CAMERA |
                       FLAG_DESTROY_IF_BARELY_OUT_OF_CAMERA;
        if (self->subId == 0) {
            angle = self->unk1E;
            self->unk1C = 0x80;
            self->unk1A = 0x80;
            self->unk19 |= 7;
            self->unk1E = 0x1C0 - angle;
            if (self->facing != 0) {
                self->accelerationX = rcos(angle) * 0x60;
            } else {
                self->accelerationX = -(rcos(angle) * 0x60);
            }
            self->accelerationY = rsin(angle) * 0x60;
        }
    }
    if (self->subId != 0) {
        if (AnimateEntity(D_80180BA0, self) == 0) {
            DestroyEntity(self);
        }
        if (g_blinkTimer & 1) {
            self->animCurFrame = 0;
        }
    } else {
        if (self->unk1A < 0x100) {
            self->unk1A = self->unk1C = self->unk1C + 0x10;
        }
        AnimateEntity(D_80180BB8, self);
        MoveEntity();
    }
}

void EntityDraculaRainAttack(Entity* self) {
    Entity* newEntity;
    s32 accelY;
    s32 accelX;
    s16 angle;
    s32 i;

    if (self->flags & 0x100) {
        newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (newEntity != NULL) {
            CreateEntityFromEntity(E_EXPLOSION, self, newEntity);
            newEntity->subId = 2;
        }
        DestroyEntity(self);
        return;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(D_8018061C);
        if (self->subId != 0) {
            self->unk3C = 0;
            self->animCurFrame = 0x59;
            accelX = (Random() & 0x1F) + 0x10;
            angle = (Random() * 6) + 0x900;
            self->accelerationX = accelX * rcos(angle);
            accelY = accelX * rsin(angle);
            self->step = 3;
            self->accelerationY = accelY;
            break;
        }
        self->accelerationY = 0x40000;

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
                    newEntity->subId = 1;
                    newEntity->posY.i.hi += 12;
                }
            }
            DestroyEntity(self);
        }
        break;

    case 3:
        MoveEntity();
        self->accelerationY += 0x2000;
        if (self->posY.i.hi >= 0xF1) {
            DestroyEntity(self);
        }
        break;
    }
}

INCLUDE_ASM("asm/us/st/st0/nonmatchings/2C564", func_801AF380);

INCLUDE_ASM("asm/us/st/st0/nonmatchings/2C564", func_801AF6D0);

INCLUDE_ASM("asm/us/st/st0/nonmatchings/2C564", func_801AF774);