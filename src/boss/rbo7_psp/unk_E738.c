// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../rbo7/rbo7.h"

#ifdef VERSION_PSP
extern s32 E_ID(LIFE_UP_SPAWN);
extern s32 E_ID(UNK_19);
#endif

extern EInit g_EInitInteractable;
extern s32 D_us_80180564;
extern s32 D_us_801805C8;

void func_us_80192B38_from_rbo3(Entity* self) {
    Entity* entity;
    s32 x;
    s32 y;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        /* fall through */
    case 1:
        entity = &PLAYER;
        x = entity->posX.i.hi + g_Tilemap.scrollX.i.hi;
        if (x > 0x80 && x < 0x180) {
            D_us_80180564 = 1;
            D_us_801805C8 = 1;
            g_api.TimeAttackController(
                TIMEATTACK_EVENT_AKMODAN_II_DEFEAT, TIMEATTACK_SET_VISITED);
            stopMusicFlag = true;
            currentMusicId = MU_FESTIVAL_OF_SERVANTS;
            self->step++;
        }
        break;

    case 2:
        if (g_api.func_80131F68() == false) {
            stopMusicFlag = false;
            g_api.PlaySfx(currentMusicId);
            self->step++;
        }
        break;

    case 3:
        if (D_us_801805C8 & 2) {
            g_api.TimeAttackController(
                TIMEATTACK_EVENT_AKMODAN_II_DEFEAT, TIMEATTACK_SET_RECORD);
            g_api.PlaySfx(SET_UNK_90);
            currentMusicId = MU_FINAL_TOCATTA;
            self->step++;
        }
        break;

    case 4:
        if (D_us_801805C8 & 4) {
            self->step++;
        }
        break;

    case 5:
        x = 0x100 - g_Tilemap.scrollX.i.hi;
        y = 0x180 - g_Tilemap.scrollY.i.hi;
        entity = AllocEntity(&g_Entities[0xA0], &g_Entities[0xC0]);
        if (entity == NULL) {
            break;
        }
        CreateEntityFromEntity(E_ID(LIFE_UP_SPAWN), self, entity);
        entity->posX.i.hi = x;
        entity->posY.i.hi = y;
        entity->params = 0x13;
        D_us_80180564 = 0;
        stopMusicFlag = true;
        currentMusicId = MU_FINAL_TOCATTA;
        self->step++;
        break;

    case 6:
        if (g_api.func_80131F68() == false) {
            stopMusicFlag = false;
            g_api.PlaySfx(currentMusicId);
            self->step++;
        }
        break;
    }
}

#include "../../st/e_breakable.h"

INCLUDE_ASM("boss/rbo7_psp/nonmatchings/rbo7_psp/unk_E738", func_us_801940B4);

extern EInit D_us_80180444;

void func_us_801957C0(Entity* self) {
    Entity* harpy;

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_80180444);
        self->hitboxState = 0;
        if (self->params == 2) {
            self->step = 2;
        }
        if (self->params == 3) {
            self->step = 3;
        }
        break;
    case 2:
        switch (self->step_s) {
        case 0:
            self->animCurFrame = 0;
            harpy = self - self->params;
            if (harpy->ext.harpy.unk84) {
                self->animCurFrame = 4;
                self->ext.harpy.unk80 = 0x40;
                self->step_s++;
            }
            break;
        case 1:
            if (self->facingLeft) {
                self->velocityX = FIX(0.75);
            } else {
                self->velocityX = -FIX(0.75);
            }
            self->step_s++;
            /* fall through */
        case 2:
            MoveEntity();
            if (!--self->ext.harpy.unk80) {
                self->zPriority -= 2;
                self->step_s++;
            }
            break;
        }
        break;
    case 3:
        switch (self->step_s) {
        case 0:
            self->animCurFrame = 0;
            harpy = self - self->params;
            if (harpy->ext.harpy.unk84) {
                self->animCurFrame = 2;
                self->step_s++;
            }
            break;
        case 1:
            break;
        }
        break;
    }
}

extern s8 D_us_8018074C[];
extern u8 D_us_80180764[];

void EntityHarpyKick(Entity* self) {
    s32 animFrame;
    s8* hitbox;
    Entity* harpy;

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_80180444);
        /* fall through */
    case 1:
        harpy = self - 1;
        self->facingLeft = harpy->facingLeft;
        self->posX.val = harpy->posX.val;
        self->posY.val = harpy->posY.val;

        animFrame = harpy->animCurFrame;
        animFrame -= 0x23;
        if (animFrame < 0) {
            animFrame = 0;
        }

        hitbox = D_us_8018074C;
        animFrame = D_us_80180764[animFrame];
        hitbox += animFrame * 4;
        self->hitboxOffX = *hitbox++;
        self->hitboxOffY = *hitbox++;
        self->hitboxWidth = *hitbox++;
        self->hitboxHeight = *hitbox++;

        if (harpy->entityId != E_ID(UNK_19)) {
            DestroyEntity(self);
        }
        break;
    }
}

extern EInit D_us_80180450;
extern u8 D_pspeu_09255350[];
extern u8 D_pspeu_09255360[];
extern u8 D_pspeu_09255378[];

void func_us_80195A8C(Entity* self) {
    s16 angle;

    if (D_us_801805C8 & 2) {
        DestroyEntity(self);
        return;
    }
    switch (self->step) {
    case 0:
        InitializeEntity(D_us_80180450);
        self->blendMode = BLEND_TRANSP;
        self->drawFlags = ENTITY_SCALEX | ENTITY_SCALEY | ENTITY_ROTATE;
        self->hitboxWidth = self->hitboxHeight = 6;
        self->rotate += 0x180 - Random() * 3;
        angle = self->rotate;
        self->posX.i.hi += (rsin(angle) * 8) >> 12;
        self->posY.i.hi += (rcos(angle) * -28) >> 12;
        self->velocityX = rsin(angle) * 24;
        self->velocityY = rcos(angle) * -24;
        self->scaleX = 0x60;
        self->scaleY = 0x60;
        self->ext.et_80195A8C.unk86 = 0;
        /* fall through */
    case 1:
        if (!AnimateEntity(D_pspeu_09255350, self)) {
            SetStep(2);
        }
        MoveEntity();
        self->scaleX += 12;
        self->scaleY += 12;
        break;
    case 2:
        if (!self->step_s) {
            self->velocityX >>= 2;
            self->velocityY >>= 2;
            self->step_s++;
        }
        MoveEntity();
        if (!AnimateEntity(D_pspeu_09255360, self)) {
            self->ext.et_80195A8C.unk86++;
        }
        if (self->ext.et_80195A8C.unk86 > 0x10) {
            self->drawFlags |= ENTITY_OPACITY;
            self->opacity = 0x80;
            self->hitboxState = 0;
            SetStep(3);
        }
        break;
    case 3:
        self->opacity -= 2;
        self->scaleX += 24;
        self->scaleY += 24;
        if (!AnimateEntity(D_pspeu_09255378, self)) {
            DestroyEntity(self);
        }
        break;
    }
}

extern u8 D_pspeu_09255380[];

void func_us_80195D04(Entity* self) {
    if (D_us_801805C8 & 2) {
        DestroyEntity(self);
        return;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_80180450);
        self->animSet = 5;
        self->palette += PAL_UNK_FLAG;
        self->unk5A = 0;
        self->blendMode = BLEND_TRANSP;
        self->velocityY = -FIX(0.375);
        self->hitboxWidth = self->hitboxHeight = 3;
        /* fall through */
    case 1:
        MoveEntity();
        if (self->pose > 0x19) {
            self->hitboxState = 0;
        }
        if (!AnimateEntity(D_pspeu_09255380, self)) {
            DestroyEntity(self);
        }
        break;
    }
}

extern u8 D_us_8018076C[];

void EntityCtulhuDeath(Entity* self) {
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        self->animSet = 14;
        self->unk5A = 121;
        self->drawFlags = ENTITY_OPACITY;
        if (self->params) {
            self->palette = 0x2EE;
            self->opacity = 8;
            self->blendMode = BLEND_TRANSP | BLEND_SUB;
            self->flags &= ~FLAG_POS_CAMERA_LOCKED;
        } else {
            self->palette = 0x2E4;
            self->zPriority += 2;
            self->opacity = 0x14;
            self->blendMode = BLEND_TRANSP | BLEND_ADD;
        }
        /* fall through */
    case 1:
        self->posY.val -= FIX(1);
        if (!AnimateEntity(D_us_8018076C, self)) {
            DestroyEntity(self);
        }
        break;
    }
}

#include "../../st/e_room_bg.h"
