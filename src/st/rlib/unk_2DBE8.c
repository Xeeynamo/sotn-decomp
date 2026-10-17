// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rlib.h"

extern EInit g_EInitLion;

static s16 D_pspeu_0924C430[] = {0, 30, 0, 4, 24, -4, -48, 0};
static s16 D_pspeu_0924C440[] = {0, 30, 24, 0};
static AnimateEntityFrame D_pspeu_0924C448[] = {{10, 1}, {7, 2}, {6, 3}, {9, 4}, {6, 3}, {7, 2}, POSE_LOOP(0)};
static AnimateEntityFrame D_pspeu_0924C458[] = {{28, 1}, {8, 5}, {8, 6}, {8, 7}, {8, 8}, {31, 7}, {3, 9}, {3, 10}, {2, 11}, {2, 12}, {2, 13}, {1, 14}, {2, 15}, {1, 16}, {2, 17}, {8, 18}, {8, 19}, {8, 10}, {8, 9}, {8, 6}, {8, 5}, {8, 1}, POSE_LOOP(0)};
static AnimateEntityFrame D_pspeu_0924C488[] = {{40, 1}, {5, 5}, {5, 6}, {5, 7}, {5, 20}, {7, 23}, {7, 24}, {7, 25}, {7, 26}, {49, 27}, POSE_END};
static AnimateEntityFrame D_pspeu_0924C4A0[] = {{16, 1}, {5, 21}, {13, 22}, {7, 21}, {7, 1}, POSE_LOOP(0)};

void EntityLion(Entity* self) {
    Entity* other;
    s32 coll;
    s32 i;

    if (self->flags & FLAG_DEAD) {
        if (self->step != 6) {
            PlaySfxPositional(SFX_UNK_RLIB_732);
            self->hitboxState = 0;
            PlaySfxPositional(SFX_FM_STUTTER_EXPLODE);
            SetStep(6);
        }
    }
    switch (self->step) { /* switch 1; irregular */
    case 0x0:             /* switch 1 */
        InitializeEntity(g_EInitLion);
        other = self + 1;
        CreateEntityFromCurrentEntity(E_HARPY_KICK, other);
        /* fallthrough */
    case 0x1: /* switch 1 */
        if (UnkCollisionFunc3(D_pspeu_0924C430) & 1) {
            SetStep(2);
        }
        break;
    case 0x2: /* switch 1 */
        AnimateEntity(&D_pspeu_0924C4A0, self);
        self->facingLeft = GetSideToPlayer() & 1;
        if (GetDistanceToPlayerX() < 0x60) {
            SetStep(3);
        }
        break;
    case 0x3: /* switch 1 */
        AnimateEntity(&D_pspeu_0924C448, self);
        coll = UnkCollisionFunc2(D_pspeu_0924C440);
        if (coll & 0x60) {
            self->posX.val -= self->velocityX;
        }
        if (self->facingLeft ^ self->ext.ILLEGAL.u8[8]) {
            self->velocityX = FIX(-0.75);
        } else {
            self->velocityX = FIX(0.75);
        }
        if (self->ext.ILLEGAL.u8[8]) {
            self->velocityX -= self->velocityX / 4;
        }
        switch (self->step_s) { /* switch 2; irregular */
        case 0:                 /* switch 2 */
            self->facingLeft = GetSideToPlayer() & 1;
            self->ext.ILLEGAL.u8[8] = 1;
            self->ext.ILLEGAL.s16[3] = 0x60;
            self->step_s++;
            /* fallthrough */
        case 1: /* switch 2 */
            self->facingLeft = GetSideToPlayer() & 1;
            other = &PLAYER;
            if (other->facingLeft != self->facingLeft) {
                self->ext.ILLEGAL.s16[3]--;
            }
            if ((GetDistanceToPlayerX() > 0x60) &&
                other->facingLeft == self->facingLeft) {
                SetStep(4);
            } else {
                if (!self->ext.ILLEGAL.s16[3]) {
                    self->step_s++;
                }
                if (GetDistanceToPlayerX() < 0x28) {
                    SetStep(5);
                }
            }
            break;
        case 2: /* switch 2 */
            self->facingLeft = ((GetSideToPlayer() & 1) ^ 1);
            self->ext.ILLEGAL.u8[8] = 0;
            if (GetDistanceToPlayerX() > 0xA0) {
                SetStep(2);
            }
            break;
        }
        if (self->hitFlags & 3) {
            self->facingLeft = GetSideToPlayer() & 1;
            SetStep(5);
        }
        break;
    case 0x4: /* switch 1 */
        AnimateEntity(&D_pspeu_0924C448, self);
        coll = UnkCollisionFunc2(&D_pspeu_0924C440);
        if (coll & 0x60) {
            self->posX.val -= self->velocityX;
        }
        self->facingLeft = GetSideToPlayer() & 1;
        other = &PLAYER;
        if (other->facingLeft != self->facingLeft) {
            self->ext.ILLEGAL.s16[3]--;
            self->ext.ILLEGAL.u8[8] = 1;
            if (!self->ext.ILLEGAL.s16[3]) {
                SetStep(3);
                return;
            }
        } else {
            self->ext.ILLEGAL.s16[3] = 0x20;
            self->ext.ILLEGAL.u8[8] = 0;
        }
        if (self->facingLeft ^ self->ext.ILLEGAL.u8[8]) {
            self->velocityX = FIX(-0.75);
        } else {
            self->velocityX = FIX(0.75);
        }
        if (self->ext.ILLEGAL.u8[8]) {
            self->velocityX -= self->velocityX / 4;
        }
        switch (self->step_s) { /* switch 3; irregular */
        case 0:                 /* switch 3 */
            self->facingLeft = GetSideToPlayer() & 1;
            self->ext.ILLEGAL.u8[8]; // Need a line here to touch self.
            self->ext.ILLEGAL.s16[2] = 0x30;
            self->step_s++;
            /* fallthrough */
        case 1: /* switch 3 */
            self->velocityX -= self->velocityX / 2;
            if (g_Timer & 1) {
                self->poseTimer++;
            }
            if (!--self->ext.ILLEGAL.s16[2]) {
                self->step_s++;
            }
            /* fallthrough */
        case 2: /* switch 3 */
            if (GetDistanceToPlayerX() < 0x40) {
                SetStep(5);
            }
            break;
        }
        if (self->hitFlags & 3) {
            self->facingLeft = GetSideToPlayer() & 1;
            SetStep(5);
        }
        break;
    case 0x5: /* switch 1 */
        if (!self->poseTimer && (self->pose == 6)) {
            PlaySfxPositional(SFX_BOSS_WING_FLAP);
        }
        if (AnimateEntity(&D_pspeu_0924C458, self) == 0) {
            SetStep(3);
        }
        break;
    case 0x6:                   /* switch 1 */
        switch (self->step_s) { /* switch 4; irregular */
        case 0:                 /* switch 4 */
            if (!(g_Timer & 3)) {
                other = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (other != 0) {
                    CreateEntityFromEntity(E_INTENSE_EXPLOSION, self, other);
                    other->posX.i.hi += (0x20 - (Random() & 0x2F));
                    other->posY.i.hi += (0x20 - (Random() & 0x3F));
                }
            }
            if (!(g_Timer & 7)) {
                PlaySfxPositional(SFX_SMALL_FLAME_IGNITE);
            }
            if (AnimateEntity(&D_pspeu_0924C488, self) == 0) {
                self->step_s++;
            }
            break;
        case 1: /* switch 4 */
            PlaySfxPositional(SFX_FLEA_ARMOR_EXPLODE);
            for (i = 0; i < 6; i++) {
                other = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (other != NULL) {
                    CreateEntityFromEntity(E_UNK_1E, self, other);
                    other->params = i;
                    other->facingLeft = self->facingLeft;
                }
            }
            DestroyEntity(self);
            return;
        }
        break;
    case 0xFF: /* switch 1 */
#include "../pad2_anim_debug.h"
    }
}

extern EInit D_us_8018064C;
extern s8 g_HarpyKickHitboxes[];
extern u8 g_HarpyKickHitboxIdx[];

void EntityHarpyKick(Entity* self) {
    s32 animFrame;
    s8* hitbox;
    Entity* harpy;

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_8018064C);
        /* fall through */
    case 1:
        harpy = self - 1;
        self->facingLeft = harpy->facingLeft;
        self->posX.val = harpy->posX.val;
        self->posY.val = harpy->posY.val;
        animFrame = harpy->animCurFrame;
        hitbox = g_HarpyKickHitboxes;
        animFrame = g_HarpyKickHitboxIdx[animFrame];
        hitbox += animFrame * 4;
        self->hitboxOffX = *hitbox++;
        self->hitboxOffY = *hitbox++;
        self->hitboxWidth = *hitbox++;
        self->hitboxHeight = *hitbox++;
        if (harpy->entityId != E_LION) {
            DestroyEntity(self);
        }
        break;
    }
}

extern EInit D_us_80180658;
extern s32 D_us_801817CC[];

void func_us_801AE414(Entity* self) {
    switch (self->step_s) {
    case 0:
        InitializeEntity(D_us_80180658);
        self->animCurFrame = self->params + 0x1C;
        /* fall through */
    case 1:
        MoveEntity();
        self->velocityY += (u32)self->ext.et_801AE414.accelY;
        self->ext.et_801AE414.accelY += D_us_801817CC[self->params];
    }
}
