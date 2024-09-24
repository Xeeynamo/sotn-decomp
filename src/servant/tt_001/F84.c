// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include <servant.h>



INCLUDE_ASM("servant/tt_001/nonmatchings/F84", func_us_80170F84);

INCLUDE_ASM("servant/tt_001/nonmatchings/F84", func_us_80171284);

s32 func_us_801714F4(Entity* entity) {
    if (entity->hitboxState == 0)
        return 0;
    if (entity->posX.i.hi < -16)
        return 0;
    if (entity->posX.i.hi > 272)
        return 0;
    if (entity->posY.i.hi > 240)
        return 0;
    if (entity->posY.i.hi < 0)
        return 0;
    if (entity->hitPoints >= 0x7000)
        return 0;
    if (entity->hitPoints <= 0)
        return 0;

    return 1;
}

void func_us_80171560(void) {}

INCLUDE_ASM("servant/tt_001/nonmatchings/F84", func_us_80171568);

INCLUDE_ASM("servant/tt_001/nonmatchings/F84", func_us_80171624);

INCLUDE_ASM("servant/tt_001/nonmatchings/F84", func_us_80171864);

void func_us_801720A4(void) {}

void func_us_801720AC(void) {}

void func_us_801720B4(void) {}

void func_us_801720BC(void) {}

void func_us_801720C4(void) {}

void func_us_801720CC(void) {}

void func_us_801720D4(void) {}

void func_us_801720DC(void) {}

INCLUDE_ASM("servant/tt_001/nonmatchings/F84", func_us_801720E4);

INCLUDE_ASM("servant/tt_001/nonmatchings/F84", func_us_8017246C);

void func_us_801728EC(void) {}

void func_us_801728F4(void) {}

void func_us_801728FC(void) {}

extern s32 D_us_8017381C;

void func_us_80172904(Entity* entity)
{
    switch (entity->params) {
    case 15:
        D_us_8017381C = 1;
        break;
    }
    DestroyEntity(entity);
}

#ifndef VERSION_PSP
u32 Tt001UpdateAnim(Entity* self, s8* frameProps, AnimationFrame** frames) {
    AnimationFrame* animFrame;
    s32 ret;

    ret = 0;
    if (self->animFrameDuration == -1) {
        ret = -1;
    } else if (self->animFrameDuration == 0) {
        self->animFrameDuration = self->anim[self->animFrameIdx].duration;
    } else if (--self->animFrameDuration == 0) {
        self->animFrameIdx++;
        animFrame = &self->anim[self->animFrameIdx];
        // Effectively a switch statement, but breaks if I actually use one.
        if (animFrame->duration == 0) {
            self->animFrameIdx = animFrame->unk2;
            self->animFrameDuration = self->anim[self->animFrameIdx].duration;
            ret = 0;
        } else if (animFrame->duration == 0xFFFF) {
            self->animFrameIdx--;
            self->animFrameDuration = -1;
            ret = -1;
        } else if (animFrame->duration == 0xFFFE) {
            self->anim = frames[animFrame->unk2];
            self->animFrameIdx = 0;
            ret = -2;
            self->animFrameDuration = self->anim->duration;
        } else {
            self->animFrameDuration = animFrame->duration;
        }
    }
    if (frameProps != NULL) {
        // This is ugly - theoretically the type for frameProps should be
        // FrameProperty* but anything besides this where we assign this big
        // expression fails.
        frameProps =
            &frameProps[(self->anim[self->animFrameIdx].unk2 >> 9) << 2];
        self->hitboxOffX = *frameProps++;
        self->hitboxOffY = *frameProps++;
        self->hitboxWidth = *frameProps++;
        self->hitboxHeight = *frameProps++;
    }
    self->animCurFrame = self->anim[self->animFrameIdx].unk2 & 0x1FF;
    return ret;
}
#endif

#include "../../destroy_entity.h"

s32 func_us_80172B50(s32 arg0, s32 arg1) {
    if (arg0 < 0) {
        arg0 += arg1;
        if (arg0 > 0) {
            arg0 = 0;
        }
    } else {
        arg0 -= arg1;
        if (arg0 < 0) {
            arg0 = 0;
        }
    }

    return arg0;
}

Entity* func_us_80172B88(s32 rangeIndex, s32 entityId) {
    volatile u32 pad; // fake?
    s16 start = D_80170EE4[rangeIndex].start;
    s16 end = D_80170EE4[rangeIndex].end;
    Entity* entity = &g_Entities[start];
    s32 i;

    for (i = start; end >= i; i++, entity++) {
        if (entity->entityId == entityId) {
            return entity;
        }
    }

    return NULL;
}

INCLUDE_ASM("servant/tt_001/nonmatchings/F84", func_us_80172C08);

INCLUDE_ASM("servant/tt_001/nonmatchings/F84", func_us_80172C4C);

INCLUDE_ASM("servant/tt_001/nonmatchings/F84", func_us_80172CC0);

INCLUDE_ASM("servant/tt_001/nonmatchings/F84", func_us_80172D10);

INCLUDE_ASM("servant/tt_001/nonmatchings/F84", func_us_80172EE8);

INCLUDE_ASM("servant/tt_001/nonmatchings/F84", func_us_801732BC);

INCLUDE_ASM("servant/tt_001/nonmatchings/F84", func_us_80173378);

INCLUDE_ASM("servant/tt_001/nonmatchings/F84", func_us_80173490);

INCLUDE_ASM("servant/tt_001/nonmatchings/F84", func_us_8017353C);

INCLUDE_RODATA("servant/tt_001/nonmatchings/F84", func_us_80170F60);
