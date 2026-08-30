// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rno4.h"

extern s16 g_WaterEffectRoomData[];
extern s16 g_WaterEffectHeightTable[];

static u16 func_pspeu_0924B480(s16 arg0, s16 arg1, s16 arg2, s16* arg3) {
    s16 temp_s2;
    s16 temp;
    s16* ptr;

    ptr = &g_WaterEffectRoomData[arg0 * 8];
    arg1 -= (g_Tilemap.width - *ptr++);
    temp_s2 = *ptr++;
    arg1 += temp_s2;
    if (arg1 < 0) {
        return 0;
    }
    *arg3++ = arg1;

    temp = temp_s2 - arg1;
    if (temp <= 0) {
        return 0;
    }
    temp_s2 = temp;
    *arg3 = temp;

    temp = g_WaterEffectHeightTable[*ptr++];
    if (temp) {
        temp = temp_s2 / temp;
    } else {
        temp = 0;
    }

    temp = temp + (g_Tilemap.height - *ptr++);
    if (temp < arg2) {
        return 0;
    }
    if (arg2 <= (g_Tilemap.height - *ptr++)) {
        return 0;
    }
    return ((temp + 0x7FFF) + 1) - arg2;
}

INCLUDE_ASM("st/rno4/nonmatchings/unk_52ED0", EntityAlucardWaterEffect);

INCLUDE_ASM("st/rno4/nonmatchings/unk_52ED0", EntitySplashWater);

INCLUDE_ASM("st/rno4/nonmatchings/unk_52ED0", EntitySurfacingWater);

INCLUDE_ASM("st/rno4/nonmatchings/unk_52ED0", EntitySideWaterSplash);

INCLUDE_ASM("st/rno4/nonmatchings/unk_52ED0", EntitySmallWaterDrop);

INCLUDE_ASM("st/rno4/nonmatchings/unk_52ED0", EntityWaterDrop);

INCLUDE_ASM("st/rno4/nonmatchings/unk_52ED0", func_us_801D511C);

#ifdef VERSION_PSP
extern s16 g_DarkOctopusYOffsets[];
#else
extern u16 g_DarkOctopusYOffsets[];
#endif

void func_us_801D58FC(Entity* self) {
    Entity* entity;
#ifndef VERSION_PSP
    Entity* previous = self - 1;
#endif

    if ((self->flags & FLAG_DEAD) && self->step < 2) {
#ifdef VERSION_PSP
        self->hitboxState = 0;
        self->drawFlags |= ENTITY_OPACITY;
        self->opacity = 0x80;
        self->ext.darkOctopus.initialOpacity = 0x80;
#else
        self->opacity = 0x80;
        self->hitboxState = 0;
        self->ext.darkOctopus.initialOpacity = 0x80;
        self->drawFlags |= ENTITY_OPACITY;
#endif
        SetStep(2);
    }

#ifdef VERSION_PSP
    entity = self - 1;
    self->posX.i.hi = entity->posX.i.hi;
    self->posY.i.hi = entity->posY.i.hi;
    self->posY.i.hi += g_DarkOctopusYOffsets[entity->animCurFrame];
#else
    {
        u16 posX;
        s32 frame;
        u16 posY;

        posX = self[-1].posX.i.hi;
        frame = self[-1].animCurFrame;
        posY = self[-1].posY.i.hi;
        self->posX.i.hi = posX;
        self->posY.i.hi = posY;
        self->posY.i.hi = posY + g_DarkOctopusYOffsets[frame];
    }
#endif

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitDarkOctopus);
        self->hitboxWidth = 6;
        self->hitboxHeight = 0xB;
        self->hitboxOffX = 1;
        self->hitboxOffY = -5;
#ifdef VERSION_PSP
        self->nextPart = self - 1;
        break;
#else
        self->nextPart = previous;
#endif

    case 1:
        AnimateEntity(g_DarkOctopusAnim, self);
        break;

    case 2: {
#ifdef VERSION_PSP
        if (g_Timer % 8 == 0) {
#else
        if (!(g_Timer & 7)) {
#endif
            entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (entity != 0) {
                CreateEntityFromEntity(E_EXPLOSION, self, entity);
                entity->params = 0x11;
            }
        }

        switch (self->step_s) {
        case 0:
            entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (entity != 0) {
                CreateEntityFromEntity(E_SUBWPN_IN_CONT, self, entity);
                entity->params = 2;
                self->ext.darkOctopus.linkedEntity = entity;
                entity->ext.darkOctopus.linkedEntity = self;
            } else {
                self->ext.darkOctopus.linkedEntity = NULL;
            }
            self->step_s++;
            break;

        case 1:
            self->opacity -= 4;
            if (self->opacity) {
                break;
            }
#ifdef VERSION_PSP
            self->blendMode = BLEND_NO;
            self->opacity = 0x80;
            self->poseTimer = 0;
            self->pose = 0;
            self->palette = 0x8224;
            self->drawFlags |= ENTITY_SCALEY;
            self->scaleY = 0x100;
            if (self->ext.darkOctopus.linkedEntity != NULL) {
                entity = self->ext.darkOctopus.linkedEntity;
                DestroyEntity(entity);
            }
#else
            self->opacity = 0x80;
            self->palette = 0x8224;
            self->scaleY = 0x100;
            self->blendMode = BLEND_NO;
            self->poseTimer = 0;
            self->pose = 0;
            self->drawFlags |= ENTITY_SCALEY;
            if (self->ext.darkOctopus.linkedEntity != NULL) {
                DestroyEntity(self->ext.darkOctopus.linkedEntity);
            }
#endif
            self->step_s++;
            break;

        case 2:
            self->scaleY -= 4;
            self->posY.val += FIX(0.1875);
            if (self->scaleY < 0x20) {
                self->step_s++;
            }
            break;

        case 3:
            DestroyEntity(self);
            break;
        }
        break;
    }
    }
}

INCLUDE_ASM("st/rno4/nonmatchings/unk_52ED0", func_us_801D5BA4);

#define STEP_TOWARDS_EXTERNAL
#include "../step_towards.h"
#undef STEP_TOWARDS_EXTERNAL

INCLUDE_ASM("st/rno4/nonmatchings/unk_52ED0", func_us_801D5DC8);

INCLUDE_ASM("st/rno4/nonmatchings/unk_52ED0", func_us_801D5E90);

INCLUDE_ASM("st/rno4/nonmatchings/unk_52ED0", func_us_801D68E0);

INCLUDE_ASM("st/rno4/nonmatchings/unk_52ED0", func_us_801D6B8C);
