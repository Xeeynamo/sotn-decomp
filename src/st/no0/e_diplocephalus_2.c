// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no0.h"

// Fireball
INCLUDE_ASM("st/no0/nonmatchings/e_diplocephalus_2", func_us_801D0990);

extern EInit g_EInitDiplocephalusTail;
extern u8 D_us_80181DBC[];
extern u8 D_us_80181DDC[];
extern u8 D_us_80181DEC[];
extern u8 D_us_80181E0C[];
extern u8 D_us_80181E30[];

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

    if (self->ext.diplocephalus.unk8C == NULL) {
        FntPrint("stail_step %x\n", self->step);
    }
    if (self->ext.diplocephalus.unk90 == NULL) {
        FntPrint("tail_step %x\n", self->step);
    }
    if (self->ext.diplocephalus.unk90 == NULL) {
        self->ext.diplocephalus.parent->ext.diplocephalus.unkAC =
            self->hitParams;
    } else if (self->hitboxState) {
        self->hitboxState = 0;
        if (self->ext.diplocephalus.unk8C != NULL) {
            (self - 1)->hitboxState = 1;
        } else {
            (self + 5)->hitboxState = 1;
        }
    }
    if ((self->ext.diplocephalus.parent->entityId != E_ID_21) &&
        (self->ext.diplocephalus.unk8C == NULL) && (self->step < 8)) {
        self->step = 8;
    }
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitDiplocephalusTail);
        self->hitboxState = 1;
        self->drawFlags = FLAG_DRAW_ROTZ;
        self->ext.diplocephalus.unk84 = 0;
        self->ext.diplocephalus.unk9C = 0;
        self->ext.diplocephalus.unk9D = 0;
        self->ext.diplocephalus.unk8C = NULL;
        tempEntity2 = self;
        tempEntity = self;
        for (i = 0; i < 6; i++) {
            tempEntity++;
            CreateEntityFromCurrentEntity(E_ID_24, tempEntity);
            tempEntity->ext.diplocephalus.unk8C = tempEntity - 1;
            (tempEntity - 1)->ext.diplocephalus.unk90 = tempEntity;
            tempEntity->step = 3;
            tempEntity->animSet = self->animSet;
            tempEntity->animCurFrame = 0x13;
            tempEntity->facingLeft =
                self->ext.diplocephalus.parent->facingLeft ^ 1;
            tempEntity->zPriority =
                self->ext.diplocephalus.parent->zPriority - i - 1;
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
            tempEntity->ext.diplocephalus.parent =
                self->ext.diplocephalus.parent;
            tempEntity->drawFlags = FLAG_DRAW_ROTZ;
            tempEntity2 = tempEntity;
            tempEntity->unk60 = tempEntity + 1;
        }
        tempEntity->unk60 = NULL;
        (tempEntity - 1)->ext.diplocephalus.unk9F = 1;
        tempEntity->hitboxState = 3;
        tempEntity->hitboxWidth = 8;
        tempEntity->hitboxHeight = 0xD;
        tempEntity->hitboxOffY = -8;
        tempEntity->ext.diplocephalus.unk90 = NULL;
        tempEntity->flags |= FLAG_UNK_20000000;
        self->ext.diplocephalus.entity = tempEntity;
        self->ext.diplocephalus.entity->animCurFrame = 0x17;
        self->ext.diplocephalus.entity->zPriority = self->zPriority;
        self->ext.diplocephalus.entity->step = 5;
        self->ext.diplocephalus.entity->drawFlags = FLAG_DRAW_DEFAULT;
        self->ext.diplocephalus.entity->ext.diplocephalus.unk84 = 0x500U;
        self->ext.diplocephalus.entity->ext.diplocephalus.unk8C->animCurFrame =
            0x16;
        /* fallthrough */
    case 1:
        if (self->facingLeft) {
            self->posX.val = self->ext.diplocephalus.parent->posX.val - FIX(29);
        } else {
            self->posX.val = self->ext.diplocephalus.parent->posX.val + FIX(29);
        }
        self->posY.val = self->ext.diplocephalus.parent->posY.val;
        dVelocity = self->velocityY - self->ext.diplocephalus.velocityY;

        if (dVelocity > 0) {
            self->ext.diplocephalus.unk84 += 0x10;
        }
        if (dVelocity < 0) {
            self->ext.diplocephalus.unk84 -= 0x10;
        }
        if (self->ext.diplocephalus.unk84 > 0) {
            self->ext.diplocephalus.unk84 -= 8;
        }
        if (self->ext.diplocephalus.unk84 < 0) {
            self->ext.diplocephalus.unk84 += 8;
        }
        if (self->ext.diplocephalus.unk84 > 0x100) {
            self->ext.diplocephalus.unk84 = 0x100;
        }
        if (self->ext.diplocephalus.unk84 < -0x100) {
            self->ext.diplocephalus.unk84 = -0x100;
        }
        dVelocity = self->velocityX - self->ext.diplocephalus.velocityX;
        if (self->facingLeft ^ 1) {
            dVelocity = -dVelocity;
        }
        if (dVelocity > 0) {
            self->ext.diplocephalus.entity->ext.diplocephalus.unk84 += 0x10;
        }
        if (dVelocity < 0) {
            self->ext.diplocephalus.entity->ext.diplocephalus.unk84 -= 0x10;
        }
        if (self->ext.diplocephalus.entity->ext.diplocephalus.unk84 > 0x500) {
            self->ext.diplocephalus.entity->ext.diplocephalus.unk84 -= 8;
        }
        if (self->ext.diplocephalus.entity->ext.diplocephalus.unk84 < 0x500) {
            self->ext.diplocephalus.entity->ext.diplocephalus.unk84 += 8;
        }
        if (self->ext.diplocephalus.entity->ext.diplocephalus.unk84 > 0x700) {
            self->ext.diplocephalus.entity->ext.diplocephalus.unk84 = 0x700;
        }
        if (self->ext.diplocephalus.entity->ext.diplocephalus.unk84 < 0x300) {
            self->ext.diplocephalus.entity->ext.diplocephalus.unk84 = 0x300;
        }
        three = 3;
        temp_a2 = self->ext.diplocephalus.entity->ext.diplocephalus.unk84 -
                  self->ext.diplocephalus.unk84;
        temp_s5 = (temp_a2 - self->ext.diplocephalus.unk84) / three;
        temp_s6 = (self->ext.diplocephalus.entity->ext.diplocephalus.unk84 -
                   temp_a2) /
                  (6 - three);
        unused = (self->ext.diplocephalus.entity->ext.diplocephalus.unk84 -
                  self->ext.diplocephalus.unk84) /
                 6;

        tempEntity = self;
        i = 0;
        while (!(three < i)) {
            tempEntity->ext.diplocephalus.unk84 =
                self->ext.diplocephalus.unk84 + temp_s5 * i;
            xOffset = (rcos(tempEntity->ext.diplocephalus.unk84) << 3) << 4;
            yOffset = (rsin(tempEntity->ext.diplocephalus.unk84) << 3) << 4;
            if (self->facingLeft) {
                tempEntity->ext.diplocephalus.unk90->posX.val =
                    tempEntity->posX.val - xOffset;
            } else {
                tempEntity->ext.diplocephalus.unk90->posX.val =
                    tempEntity->posX.val + xOffset;
            }
            tempEntity->ext.diplocephalus.unk90->posY.val =
                tempEntity->posY.val - yOffset;
            i++;
            tempEntity->rotZ = -tempEntity->ext.diplocephalus.unk84;
            tempEntity = tempEntity->ext.diplocephalus.unk90;
        }
        i = 0;
        while (tempEntity->ext.diplocephalus.unk90 != NULL) {
            tempEntity->ext.diplocephalus.unk84 = temp_a2 + temp_s6 * i;
            xOffset = (rcos(tempEntity->ext.diplocephalus.unk84) << 3) << 4;
            yOffset = (rsin(tempEntity->ext.diplocephalus.unk84) << 3) << 4;
            if (self->facingLeft) {
                tempEntity->ext.diplocephalus.unk90->posX.val =
                    tempEntity->posX.val - xOffset;
            } else {
                tempEntity->ext.diplocephalus.unk90->posX.val =
                    tempEntity->posX.val + xOffset;
            }
            tempEntity->ext.diplocephalus.unk90->posY.val =
                tempEntity->posY.val - yOffset;
            i++;
            tempEntity->rotZ = -tempEntity->ext.diplocephalus.unk84;
            tempEntity = tempEntity->ext.diplocephalus.unk90;
        }
        self->ext.diplocephalus.entity->posX.i.hi += 1;
        self->ext.diplocephalus.entity->posY.i.hi -= 2;
        self->ext.diplocephalus.velocityY =
            self->ext.diplocephalus.parent->velocityY;
        self->ext.diplocephalus.velocityX =
            self->ext.diplocephalus.parent->velocityX;
        self->ext.diplocephalus.unk9C++;
        if (self->ext.diplocephalus.unk9C > 0x20) {
            tempEntity = self->ext.diplocephalus.unk90;
            for (i = 0; i < self->ext.diplocephalus.unk9D; i++) {
                tempEntity = tempEntity->ext.diplocephalus.unk90;
            }
            tempEntity->animFrameDuration = 0;
            tempEntity->animFrameIdx = 0;
            tempEntity->step = 4;
            self->ext.diplocephalus.unk9C = 0;
            self->ext.diplocephalus.unk9D++;
        }
        if (self->ext.diplocephalus.unk9D > 3) {
            self->ext.diplocephalus.unk9D = 0;
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
        if (self->ext.diplocephalus.parent->ext.diplocephalus.unkAD != 0) {
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
        self->ext.diplocephalus.unk9D = 1;
        self->ext.diplocephalus.unk9C = 0;
        self->ext.diplocephalus.entity->step = 7;
        self->ext.diplocephalus.entity->flags &= ~FLAG_UNK_20000000;
        PlaySfxPositional(0x778);
        tempEntity = self;
        while (tempEntity->ext.diplocephalus.unk90 != NULL) {
            tempEntity->hitboxState = 0;
            tempEntity++;
        }
        self->ext.diplocephalus.entity->hitboxState = 0;
        PlaySfxPositional(SFX_STUTTER_EXPLODE_B);
        self->step++;
        return;
    case 9:
        if ((self->ext.diplocephalus.entity->ext.diplocephalus.unk90 != 0) ||
            (self->ext.diplocephalus.entity->entityId != E_ID_24)) {
            if (self->ext.diplocephalus.unk9C++ > 6) {
                self->ext.diplocephalus.unk9D++;
                self->ext.diplocephalus.unk9C = 0;
                self->ext.diplocephalus.entity--;
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
                CreateEntityFromCurrentEntity(E_ID_25, tempEntity);
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
