// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no0.h"

// Fireball
extern u8 D_us_80181E3C[]; // anim
extern u8 D_us_80181E54[]; // anim
extern u8 D_us_80181E70[]; // anim

// Tail
extern u8 D_us_80181DBC[]; // anim
extern u8 D_us_80181DDC[]; // anim
extern u8 D_us_80181DEC[]; // anim
extern u8 D_us_80181E0C[]; // anim
extern u8 D_us_80181E30[]; // anim

void EntityDiplocephalusFireball(Entity* self) {
    Entity* player;
    Primitive* prim;
    s16 angle;
    s32 primIndex;
    s32 magnitude;

    FntPrint("tama_step %x\n", self->step);
    if ((self->flags & FLAG_DEAD) && self->step < 4) {
        PlaySfxPositional(SFX_EXPLODE_FAST_A);
        self->hitboxState = 0;
        SetStep(4);
    }

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitDiplocephalusFireball);
        self->drawFlags |= FLAG_DRAW_ROTZ | FLAG_DRAW_ROTY | FLAG_DRAW_ROTX;
        self->rotX = self->rotY = 0x60;

        primIndex = g_api.AllocPrimBuffers(PRIM_GT4, 20);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }

        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.diplocephalusFireball.unk90 = prim;

        while (prim != NULL) {
            prim->tpage = 26;
            prim->clut = 368;
            PGREY(prim, 0) = 64;
            LOW(prim->r1) = LOW(prim->r0);
            LOW(prim->r2) = LOW(prim->r0);
            LOW(prim->r3) = LOW(prim->r0);
            prim->p3 = 0;
            prim->priority = self->zPriority + 2;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }

        if (self->facingLeft) {
            self->velocityX = FIX(6);
        } else {
            self->velocityX = FIX(-6);
        }
        self->velocityY = 0;
        self->ext.diplocephalusFireball.unk9C = 2;
        // Fallthrough
    case 1:
        MoveEntity();
        AnimateEntity(D_us_80181E3C, self);
        self->rotZ += 64;
        self->rotX += 16;
        if (self->rotX > 256) {
            self->rotX = 256;
        }
        self->rotY = self->rotX;
        MoveEntity();
        self->velocityX -= self->velocityX / 8;
        if (abs(self->velocityX) < FIX(0.25)) {
            if (self->facingLeft) {
                self->ext.diplocephalusFireball.unk8C = 0;
            } else {
                self->ext.diplocephalusFireball.unk8C = 2048;
            }
            self->ext.diplocephalusFireball.unk88 = 0;
            self->step++;
        }
        break;
    case 2:
        player = &PLAYER;
        angle = GetAngleBetweenEntities(self, player);
        angle = GetNormalizedAngle(
            16, self->ext.diplocephalusFireball.unk8C, angle);
        magnitude = self->ext.diplocephalusFireball.unk88;
        magnitude += 3072;
        if (magnitude > 0x30000) {
            magnitude = 0x30000;
            self->step++;
        }
        self->velocityX = (magnitude * rcos(angle)) >> 12;
        self->velocityY = (magnitude * rsin(angle)) >> 12;
        self->ext.diplocephalusFireball.unk88 = magnitude;
        self->ext.diplocephalusFireball.unk8C = angle;
        AnimateEntity(D_us_80181E3C, self);
        MoveEntity();
        break;
    case 3:
        AnimateEntity(D_us_80181E3C, self);
        MoveEntity();
        break;
    case 4:
        switch (self->step_s) {
        case 0:
            prim = self->ext.diplocephalusFireball.unk90;
            while (prim != NULL) {
                prim->p3 = 0;
                prim->drawMode = DRAW_HIDE;
                prim = prim->next;
            }

            self->velocityX >>= 1;
            self->velocityY >>= 1;
            self->drawFlags = FLAG_DRAW_DEFAULT;
            self->step_s++;
            self->flags = 0xFFFFFFF0;
            self->palette = PAL_DRA(0x2C0);
            // fallthrough
        case 1:
            MoveEntity();
            self->posY.val -= FIX(1.0);
            if (!AnimateEntity(D_us_80181E54, self)) {
                DestroyEntity(self);
                return;
            }
            break;
        }
        break;
    }

    if ((g_Timer & 1) && !(self->flags & FLAG_DEAD)) {
        prim = self->ext.diplocephalusFireball.unk90;
        prim = FindFirstUnkPrim(prim);
        if (prim != NULL) {
            prim->p3 = 3;
            prim->x0 = prim->x2 = self->posX.i.hi - 12;
            prim->x1 = prim->x3 = prim->x0 + 28;
            prim->y0 = prim->y1 = self->posY.i.hi - 12;
            prim->y2 = prim->y3 = prim->y0 + 28;
            prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS |
                             DRAW_UNK02 | DRAW_TRANSP;
            prim->p1 = 0;
            prim->p2 = 0;
        }
    }

    prim = self->ext.diplocephalusFireball.unk90;
    while (prim != NULL) {
        if (prim->p3 && !UpdateAnimation(D_us_80181E70, prim)) {
            prim->p3 = 0;
            prim->drawMode = DRAW_HIDE;
        }
        prim = prim->next;
    }
}

void EntityDiplocephalusTail(Entity* self) {
    s16 unused;
    s16 temp_s5;
    u8 three;
    s16 temp_a2;
    s16 temp_s6;
    s32 dVelocity;
    s32 yOffset;
    s32 xOffset;
    s32 i;
    Entity* tempEntity2;
    Entity* tempEntity;

    if (self->ext.diplocephalusUnk.entity8C == NULL) {
        FntPrint("stail_step %x\n", self->step);
    }
    if (self->ext.diplocephalusUnk.unk90 == NULL) {
        FntPrint("tail_step %x\n", self->step);
    }
    if (self->ext.diplocephalusUnk.unk90 == NULL) {
        self->ext.diplocephalusUnk.parent->ext.diplocephalus.hitParams =
            self->hitParams;
    } else if (self->hitboxState) {
        self->hitboxState = 0;
        if (self->ext.diplocephalusUnk.entity8C != NULL) {
            (self - 1)->hitboxState = 1;
        } else {
            (self + 5)->hitboxState = 1;
        }
    }
    if ((self->ext.diplocephalusUnk.parent->entityId != E_DIPLOCEPHALUS) &&
        (self->ext.diplocephalusUnk.entity8C == NULL) && (self->step < 8)) {
        self->step = 8;
    }
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitDiplocephalusTail);
        self->hitboxState = 1;
        self->drawFlags = FLAG_DRAW_ROTZ;
        self->ext.diplocephalusUnk.unk84 = 0;
        self->ext.diplocephalusUnk.unk9C = 0;
        self->ext.diplocephalusUnk.unk9D = 0;
        self->ext.diplocephalusUnk.entity8C = NULL;
        tempEntity2 = self;
        tempEntity = self;
        for (i = 0; i < 6; i++) {
            tempEntity++;
            CreateEntityFromCurrentEntity(E_DIPLOCEPHALUS_TAIL, tempEntity);
            tempEntity->ext.diplocephalusUnk.entity8C = tempEntity - 1;
            (tempEntity - 1)->ext.diplocephalusUnk.unk90 = tempEntity;
            tempEntity->step = 3;
            tempEntity->animSet = self->animSet;
            tempEntity->animCurFrame = 0x13;
            tempEntity->facingLeft =
                self->ext.diplocephalusUnk.parent->facingLeft ^ 1;
            tempEntity->zPriority =
                self->ext.diplocephalusUnk.parent->zPriority - i - 1;
            tempEntity->attackElement = self->attackElement;
            tempEntity->attack = self->attack;
            tempEntity->hitPoints = self->hitPoints;
            tempEntity->enemyId = self->enemyId;
            tempEntity->hitboxState = 0;
            tempEntity->hitboxWidth = self->hitboxWidth;
            tempEntity->hitboxHeight = self->hitboxHeight;
            tempEntity->flags = self->flags;
            tempEntity->unk5A = self->unk5A;
            tempEntity->palette = self->palette;
            tempEntity->ext.diplocephalusUnk.parent =
                self->ext.diplocephalusUnk.parent;
            tempEntity->drawFlags = FLAG_DRAW_ROTZ;
            tempEntity2 = tempEntity;
            tempEntity->unk60 = tempEntity + 1;
        }
        tempEntity->unk60 = NULL;
        (tempEntity - 1)->ext.diplocephalusUnk.unk9F = 1;
        tempEntity->hitboxState = 3;
        tempEntity->hitboxWidth = 8;
        tempEntity->hitboxHeight = 0xD;
        tempEntity->hitboxOffY = -8;
        tempEntity->ext.diplocephalusUnk.unk90 = NULL;
        tempEntity->flags |= FLAG_UNK_20000000;
        self->ext.diplocephalusUnk.entity = tempEntity;
        self->ext.diplocephalusUnk.entity->animCurFrame = 0x17;
        self->ext.diplocephalusUnk.entity->zPriority = self->zPriority;
        self->ext.diplocephalusUnk.entity->step = 5;
        self->ext.diplocephalusUnk.entity->drawFlags = FLAG_DRAW_DEFAULT;
        self->ext.diplocephalusUnk.entity->ext.diplocephalusUnk.unk84 = 0x500U;
        self->ext.diplocephalusUnk.entity->ext.diplocephalusUnk.entity8C
            ->animCurFrame = 0x16;
        /* fallthrough */
    case 1:
        if (self->facingLeft) {
            self->posX.val =
                self->ext.diplocephalusUnk.parent->posX.val - FIX(29);
        } else {
            self->posX.val =
                self->ext.diplocephalusUnk.parent->posX.val + FIX(29);
        }
        self->posY.val = self->ext.diplocephalusUnk.parent->posY.val;
        dVelocity = self->velocityY - self->ext.diplocephalusUnk.velocityY;

        if (dVelocity > 0) {
            self->ext.diplocephalusUnk.unk84 += 0x10;
        }
        if (dVelocity < 0) {
            self->ext.diplocephalusUnk.unk84 -= 0x10;
        }
        if (self->ext.diplocephalusUnk.unk84 > 0) {
            self->ext.diplocephalusUnk.unk84 -= 8;
        }
        if (self->ext.diplocephalusUnk.unk84 < 0) {
            self->ext.diplocephalusUnk.unk84 += 8;
        }
        if (self->ext.diplocephalusUnk.unk84 > 0x100) {
            self->ext.diplocephalusUnk.unk84 = 0x100;
        }
        if (self->ext.diplocephalusUnk.unk84 < -0x100) {
            self->ext.diplocephalusUnk.unk84 = -0x100;
        }
        dVelocity = self->velocityX - self->ext.diplocephalusUnk.velocityX;
        if (self->facingLeft ^ 1) {
            dVelocity = -dVelocity;
        }
        if (dVelocity > 0) {
            self->ext.diplocephalusUnk.entity->ext.diplocephalusUnk.unk84 +=
                0x10;
        }
        if (dVelocity < 0) {
            self->ext.diplocephalusUnk.entity->ext.diplocephalusUnk.unk84 -=
                0x10;
        }
        if (self->ext.diplocephalusUnk.entity->ext.diplocephalusUnk.unk84 >
            0x500) {
            self->ext.diplocephalusUnk.entity->ext.diplocephalusUnk.unk84 -= 8;
        }
        if (self->ext.diplocephalusUnk.entity->ext.diplocephalusUnk.unk84 <
            0x500) {
            self->ext.diplocephalusUnk.entity->ext.diplocephalusUnk.unk84 += 8;
        }
        if (self->ext.diplocephalusUnk.entity->ext.diplocephalusUnk.unk84 >
            0x700) {
            self->ext.diplocephalusUnk.entity->ext.diplocephalusUnk.unk84 =
                0x700;
        }
        if (self->ext.diplocephalusUnk.entity->ext.diplocephalusUnk.unk84 <
            0x300) {
            self->ext.diplocephalusUnk.entity->ext.diplocephalusUnk.unk84 =
                0x300;
        }
        three = 3;
        temp_a2 =
            self->ext.diplocephalusUnk.entity->ext.diplocephalusUnk.unk84 -
            self->ext.diplocephalusUnk.unk84;
        temp_s5 = (temp_a2 - self->ext.diplocephalusUnk.unk84) / three;
        temp_s6 =
            (self->ext.diplocephalusUnk.entity->ext.diplocephalusUnk.unk84 -
             temp_a2) /
            (6 - three);
        unused =
            (self->ext.diplocephalusUnk.entity->ext.diplocephalusUnk.unk84 -
             self->ext.diplocephalusUnk.unk84) /
            6;

        tempEntity = self;
        i = 0;
        while (!(three < i)) {
            tempEntity->ext.diplocephalusUnk.unk84 =
                self->ext.diplocephalusUnk.unk84 + temp_s5 * i;
            xOffset = (rcos(tempEntity->ext.diplocephalusUnk.unk84) << 3) << 4;
            yOffset = (rsin(tempEntity->ext.diplocephalusUnk.unk84) << 3) << 4;
            if (self->facingLeft) {
                tempEntity->ext.diplocephalusUnk.unk90->posX.val =
                    tempEntity->posX.val - xOffset;
            } else {
                tempEntity->ext.diplocephalusUnk.unk90->posX.val =
                    tempEntity->posX.val + xOffset;
            }
            tempEntity->ext.diplocephalusUnk.unk90->posY.val =
                tempEntity->posY.val - yOffset;
            i++;
            tempEntity->rotZ = -tempEntity->ext.diplocephalusUnk.unk84;
            tempEntity = tempEntity->ext.diplocephalusUnk.unk90;
        }
        i = 0;
        while (tempEntity->ext.diplocephalusUnk.unk90 != NULL) {
            tempEntity->ext.diplocephalusUnk.unk84 = temp_a2 + temp_s6 * i;
            xOffset = (rcos(tempEntity->ext.diplocephalusUnk.unk84) << 3) << 4;
            yOffset = (rsin(tempEntity->ext.diplocephalusUnk.unk84) << 3) << 4;
            if (self->facingLeft) {
                tempEntity->ext.diplocephalusUnk.unk90->posX.val =
                    tempEntity->posX.val - xOffset;
            } else {
                tempEntity->ext.diplocephalusUnk.unk90->posX.val =
                    tempEntity->posX.val + xOffset;
            }
            tempEntity->ext.diplocephalusUnk.unk90->posY.val =
                tempEntity->posY.val - yOffset;
            i++;
            tempEntity->rotZ = -tempEntity->ext.diplocephalusUnk.unk84;
            tempEntity = tempEntity->ext.diplocephalusUnk.unk90;
        }
        self->ext.diplocephalusUnk.entity->posX.i.hi += 1;
        self->ext.diplocephalusUnk.entity->posY.i.hi -= 2;
        self->ext.diplocephalusUnk.velocityY =
            self->ext.diplocephalusUnk.parent->velocityY;
        self->ext.diplocephalusUnk.velocityX =
            self->ext.diplocephalusUnk.parent->velocityX;
        self->ext.diplocephalusUnk.unk9C++;
        if (self->ext.diplocephalusUnk.unk9C > 0x20) {
            tempEntity = self->ext.diplocephalusUnk.unk90;
            for (i = 0; i < self->ext.diplocephalusUnk.unk9D; i++) {
                tempEntity = tempEntity->ext.diplocephalusUnk.unk90;
            }
            tempEntity->animFrameDuration = 0;
            tempEntity->animFrameIdx = 0;
            tempEntity->step = 4;
            self->ext.diplocephalusUnk.unk9C = 0;
            self->ext.diplocephalusUnk.unk9D++;
        }
        if (self->ext.diplocephalusUnk.unk9D > 3) {
            self->ext.diplocephalusUnk.unk9D = 0;
        }
        break;
    case 4:
        if (AnimateEntity(D_us_80181E30, self) == 0) {
            self->animFrameDuration = 0;
            self->animFrameIdx = 0;
            self->step = 3;
        }
        break;
    case 5:
        AnimateEntity(D_us_80181DBC, self);
        if (self->ext.diplocephalusUnk.parent->ext.diplocephalus.hitParams2 !=
            0) {
            PlaySfxPositional(0x777);
            self->animFrameDuration = 0;
            self->animFrameIdx = 0;
            self->step = 6;
            return;
        }
        if (!(Random() & 0x7F)) {
            self->animFrameDuration = 0;
            self->animFrameIdx = 0;
            self->params = 1;
            self->step = 11;
        }
        break;
    case 6:
        if (AnimateEntity(D_us_80181DDC, self) == 0) {
            self->animFrameDuration = 0;
            self->animFrameIdx = 0;
            self->step--;
        }
        break;
    case 7:
        if (AnimateEntity(D_us_80181DEC, self) == 0) {
            tempEntity = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (tempEntity != NULL) {
                CreateEntityFromEntity(E_EXPLOSION, self, tempEntity);
                tempEntity->params = 3;
                tempEntity->zPriority = self->zPriority + 9;
            }
            g_api.func_80102CD8(1);
            EntityExplosionSpawn(0, 0);
            return;
        }
        break;
    case 8:
        self->ext.diplocephalusUnk.unk9D = 1;
        self->ext.diplocephalusUnk.unk9C = 0;
        self->ext.diplocephalusUnk.entity->step = 7;
        self->ext.diplocephalusUnk.entity->flags &= ~FLAG_UNK_20000000;
        PlaySfxPositional(0x778);
        tempEntity = self;
        while (tempEntity->ext.diplocephalusUnk.unk90 != NULL) {
            tempEntity->hitboxState = 0;
            tempEntity++;
        }
        self->ext.diplocephalusUnk.entity->hitboxState = 0;
        PlaySfxPositional(SFX_STUTTER_EXPLODE_B);
        self->step++;
        return;
    case 9:
        if ((self->ext.diplocephalusUnk.entity->ext.diplocephalusUnk.unk90 !=
             0) ||
            (self->ext.diplocephalusUnk.entity->entityId !=
             E_DIPLOCEPHALUS_TAIL)) {
            if (self->ext.diplocephalusUnk.unk9C++ > 6) {
                self->ext.diplocephalusUnk.unk9D++;
                self->ext.diplocephalusUnk.unk9C = 0;
                self->ext.diplocephalusUnk.entity--;
                tempEntity = self->ext.diplocephalus.entity;
                tempEntity->step = 10;
            }
        }
        break;
    case 10:
        self->posY.val += FIX(0.25);
        PlaySfxPositional(SFX_EXPLODE_FAST_A);
        EntityExplosionSpawn(0, 0);
        break;
    case 11:
        if (AnimateEntity(D_us_80181E0C, self) == 0) {
            self->animFrameDuration = 0;
            self->animFrameIdx = 0;
            self->step = 5;
            return;
        }
        if (self->animFrameIdx == 8 && self->params) {
            PlaySfxPositional(0x776);
            tempEntity = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (tempEntity != NULL) {
                PlaySfxPositional(SFX_FM_EXPLODE_SWISHES);
                CreateEntityFromCurrentEntity(
                    E_DIPLOCEPHALUS_FIREBALL, tempEntity);
                tempEntity->facingLeft = self->facingLeft;
                if (self->facingLeft) {
                    tempEntity->posX.i.hi += 0xC;
                } else {
                    tempEntity->posX.i.hi -= 0xC;
                }
                tempEntity->posY.i.hi -= 0x10;
                self->params = 0;
            }
        }
        break;
    }
}
