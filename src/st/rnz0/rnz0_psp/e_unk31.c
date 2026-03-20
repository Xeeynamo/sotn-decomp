// SPDX-License-Identifier: AGPL-3.0-or-later

// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../rnz0.h"

extern u8 D_pspeu_092589E8[];
extern u8 D_pspeu_092589F8[];
extern u8 D_pspeu_09258A10[];
extern u8 D_pspeu_09258A30[];
extern EInit D_pspeu_092607C0;

void EntityUnk31(Entity* self) {
    Entity* other;
    s32 xVar;
    s32 yVar;
    s16 angle;
    s32 tempVar; // Used as a temp in 2 different places

    if ((self->flags & FLAG_DEAD) && (self->step < 8)) {
        SetStep(8);
    }
    if ((self->hitFlags & 3) && (self->step != 4)) {
        SetStep(4);
    }
    switch (self->step) {
    case 0:
        InitializeEntity(D_pspeu_092607C0);
        self->drawFlags = ENTITY_OPACITY;
        self->opacity = 0;
        self->blendMode = BLEND_ADD | BLEND_TRANSP;
        self->hitboxOffY = 1;
        SetStep(2);
        break;
    case 2:
        AnimateEntity(D_pspeu_092589F8, self);
        MoveEntity();
        switch (self->step_s) {
        case 0:
            other = &PLAYER;
            xVar = other->posX.i.hi - self->posX.i.hi;
            yVar = (other->posY.i.hi - 0x40) - self->posY.i.hi;
            angle = ratan2(yVar, xVar);
            self->ext.ILLEGAL.s16[3] =
                GetNormalizedAngle(8, self->ext.ILLEGAL.s16[3], angle);
            self->velocityX = (rcos(self->ext.ILLEGAL.s16[3]) << 0xF) >> 0xC;
            self->velocityY = (rsin(self->ext.ILLEGAL.s16[3]) << 0xF) >> 0xC;
            if (self->velocityX > 0) {
                self->facingLeft = 1;
            } else {
                self->facingLeft = 0;
            }

            tempVar = ((GetSideToPlayer() & 1) ^ 1);
            if (self->facingLeft == tempVar && GetDistanceToPlayerX() < 0x20) {
                self->step_s = 1;
            }
            break;
        case 1:
            if ((GetDistanceToPlayerY() > 0x50) ||
                (GetDistanceToPlayerX() > 0x50)) {
                self->step_s = 0;
            }
            break;
        }
        break;
    case 4:
        if (AnimateEntity(&D_pspeu_09258A10, self) == 0) {
            SetStep(2U);
        }
        break;
    case 8:
        switch (self->step_s) {
        case 0:
            self->drawFlags = ENTITY_DEFAULT;
            self->blendMode = BLEND_NO;
            self->velocityX = 0;
            self->velocityY = 0;
            self->step_s += 1;
            /* fallthrough */
        case 1:
            if (AnimateEntity(&D_pspeu_09258A30, self) == 0) {
                self->ext.ILLEGAL.s16[2] = 0;
                self->step_s += 1;
            }
            break;
        case 2:
            if (UnkCollisionFunc3(&D_pspeu_092589E8) & 1) {
                PlaySfxPositional(SFX_SKULL_KNOCK_B);
                self->ext.ILLEGAL.s16[2] = 0x18;
                self->step_s += 1;
            }
            break;
        case 3:
            if (!--self->ext.ILLEGAL.s16[2]) {
                other = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (other != NULL) {
                    CreateEntityFromEntity(E_EXPLOSION, self, other);
                    other->params = 2;
                }
                PlaySfxPositional(SFX_RAPID_SCRAPE_3X);
                DestroyEntity(self);
                return;
            }
            break;
        }
        break;
    }
    if (!(self->flags & FLAG_DEAD)) {
        other = &PLAYER;
        tempVar = self->opacity;
        if ((other->velocityX != 0) || (other->velocityY != 0)) {
            tempVar -= 0x10;
            if (tempVar < 0) {
                tempVar = 0;
            }
        } else {
            tempVar += 0x10;
            if (tempVar > 0xA0) {
                tempVar = 0xA0;
            }
        }
        self->opacity = tempVar;
    }
}
