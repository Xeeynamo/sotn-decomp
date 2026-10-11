// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../rno2/rno2.h"

extern s16 D_pspeu_09258BD0[];
extern s16 D_pspeu_09258BE0[];
extern AnimateEntityFrame D_pspeu_09258BE8[];
extern AnimateEntityFrame D_pspeu_09258BF8[];
extern AnimateEntityFrame D_pspeu_09258C08[];
extern s16 D_pspeu_09258C10[][4];
extern EInit g_EInitGhostDancer;

void EntityGhostDancer(Entity* self) {
    Entity* other;
    s16* temp_s1;
    s32 var_s3;
    s32 i;

    if (self->flags & 0x100) {
        for(i = 0; i < 6; i++) {
            other = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (other != NULL) {
                temp_s1 = D_pspeu_09258C10[i];
                CreateEntityFromEntity(0x3C, self, other);
                other->facingLeft = self->facingLeft;
                other->params = (i + 0x100);
                if (self->facingLeft) {
                    other->posX.i.hi -= *temp_s1++;
                } else {
                    other->posX.i.hi += *temp_s1++;
                }
                other->posY.i.hi += *temp_s1++;
                other->ext.ILLEGAL.s16[4] = *temp_s1++;
                other->ext.ILLEGAL.s16[2] = *temp_s1++;
                other->velocityY = (Random() & 0x1F) * -0x1000;
                other->velocityX = (Random() & 0x3F) * 0xC00;
                if (((GetSideToPlayer() & 1) ^ 1) != 0) {
                    other->velocityX = -other->velocityX;
                }
            }
        }
        other = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (other != NULL) {
            CreateEntityFromEntity(2, self, other);
            other->params = 2;
        }
        PlaySfxPositional(0x62A);
        DestroyEntity(self);
        return;
    }
    switch (self->step) {                              /* switch 1 */
    case 0:                                         /* switch 1 */
        InitializeEntity(g_EInitGhostDancer);
        self->hitboxOffY = 2;
        if (Random() & 1) {
            self->palette += 1;
        }
        if (self->params & 0x100) {
            self->drawFlags |= 4;
            self->animCurFrame = (self->params & 0xF) + 0x10;
            self->hitboxState = 0;
            self->flags |= 0x80202000;
            self->step = 6;
            return;
        }
        self->animCurFrame = 1;
        self->ext.ILLEGAL.s16[2] = 0;
        return;
    case 1:                                         /* switch 1 */
        if (UnkCollisionFunc3(D_pspeu_09258BD0) & 1) {
            self->step += 1;
        }
        break;
    case 2:                                         /* switch 1 */
        if (self->facingLeft) {
            self->velocityX = 0x18000;
        } else {
            self->velocityX = -0x18000;
        }
        var_s3 = UnkCollisionFunc2(D_pspeu_09258BE0);
        if (var_s3 == 0x80) {
            SetStep(4);
        }
        if (var_s3 == 0xFF) {
            SetStep(3);
        }
        if (AnimateEntity(D_pspeu_09258BE8, self) == 0) {
            if (self->facingLeft == (GetSideToPlayer() & 1)) {
                SetStep(3);
            }
        }
        if (!self->ext.ILLEGAL.s16[2]) {
            if ((self->facingLeft ^ (GetSideToPlayer() & 1)) && 
                (GetDistanceToPlayerX() < 0x40)) {
                SetStep(4);
            }
        } else {
            self->ext.ILLEGAL.s16[2]--;
        }
        break;
    case 3:                                         /* switch 1 */
        if (AnimateEntity(D_pspeu_09258BF8, self) == 0) {
            self->facingLeft ^= 1;
            self->animCurFrame = 1;
            SetStep(2);
        }
        break;
    case 4:                                         /* switch 1 */
        switch (self->step_s) {                        /* switch 2; irregular */
        case 0:                                     /* switch 2 */
            self->hitboxWidth = 8;
            self->hitboxHeight = 0xF;
            self->hitboxOffX = -2;
            self->hitboxOffY = 0xD;
            if (AnimateEntity(D_pspeu_09258C08, self) == 0) {
                self->step_s += 1;
            }
            break;
        case 1:                                     /* switch 2 */
            if (self->facingLeft) {
                self->velocityX = 0x20000;
            } else {
                self->velocityX = -0x20000;
            }
            self->velocityY = -0x68000;
            self->drawFlags |= 4;
            self->animCurFrame = 0xF;
            self->rotate = 0x200;
            self->hitboxOffY = -8;
            self->step_s += 1;
            /* fallthrough */
        case 2:                                     /* switch 2 */
            self->rotate -= 0x10;
            if (UnkCollisionFunc3(D_pspeu_09258BD0) & 1) {
                PlaySfxPositional(0x648);
                self->hitboxOffY = 0xD;
                self->drawFlags = 0;
                self->animCurFrame = 0xE;
                self->ext.ILLEGAL.s16[2] = 0x10;
                self->step_s += 1;
            }
            break;
        case 3:                                     /* switch 2 */
            if (!--self->ext.ILLEGAL.s16[2]) {
                self->hitboxWidth = 5;
                self->hitboxHeight = 0x19;
                self->hitboxOffX = 0;
                self->hitboxOffY = 2;
                self->ext.ILLEGAL.s16[2] = 0x20;
                SetStep(2);
            }
        }
        break;
    case 6:                                         /* switch 1 */
        MoveEntity();
        self->velocityY += 0x2000;
        self->rotate += self->ext.ILLEGAL.s16[4];
        if (!--self->ext.ILLEGAL.s16[2]) {
            other = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (other != NULL) {
                CreateEntityFromEntity(2, self, other);
                other->params = 0;
            }
            DestroyEntity(self);
        }
        break;
    }
}