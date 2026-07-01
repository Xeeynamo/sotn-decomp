// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rno3.h"

// NOTE: Compare this to e_orobourous. Lots of similarities.

extern EInit g_EInitDragonRider1;
extern EInit g_EInitDragonRider2;
extern EInit D_us_801809F8;

typedef struct {
    u32 velX;
    u32 velY;
    s16 rotate;
} adhoc_vels_rot;

typedef enum{
    DRAGON_INIT,
    DRAGON_WAIT,
    DRAGON_2, // unused
    DRAGON_BOUNCING,
    DRAGON_DEAD
} DragonRiderSteps;

// Note: This data has to come after the "rest_time" string above for psp to
// match
// This is precisely identical to the other bone twisting animation
static u8 anim_bone_twisting2[] = {32, 4, 6, 5, 6, 6, 14, 7, 6, 6, 6, 5, 0};
static u8 anim_head_flip_withrider[] = {8, 3, 8, 2, 255, 0};
static s16 sensors2[] = {0, 12, 0, 4, 8, -4, -16, 0};
static adhoc_vels_rot D_pspeu_0925A758[] = {
    {FIX(0.0625), FIX(0.0), -8},
    {FIX(0.25), FIX(-1.5), 40},
    {FIX(0.5), FIX(-0.5), 16},
    {FIX(0.125), FIX(-0.375), 8}};
static s16 D_pspeu_0925A788[] = {-7, 2, 13, 10, 4, 0, 7, 13, -5, 0, 7, 13};
static s16 D_pspeu_0925A7A0[] = {4, -12, 5, 10, 0, -18, 6, 5, 0, -18, 6, 5};

void EntityDragonRider(Entity* self) {
    Collider sp2C;
    Entity* other;
    s32 temp_s6;
    s32 i;
    s32 var_s4;
    s32 xVar;
    s32 yVar;
    s16* temp_s2;

    if (self->flags & FLAG_DEAD) {
        SetStep(DRAGON_DEAD);
    }
    switch (self->step) {
    case DRAGON_INIT:
        InitializeEntity(g_EInitDragonRider1);
        self->animCurFrame = 1;
        self->drawFlags |= ENTITY_ROTATE;
        self->ext.orob.unk9 = 2;
        break;
    case DRAGON_WAIT:
        if (UnkCollisionFunc3(sensors2) & 1) {
            other = self + 1;
            for (i = 0; i < 24; i++, other++) {
                CreateEntityFromEntity(E_DRAGON_SEGMENT, self, other);
                other->posY.i.hi += 8;
                other->params = (i + 1);
                other->nextPart = other - 1;
            }
            CreateEntityFromEntity(E_UNK_33, self, other);
            other->nextPart = other - 1;
            other->parent = self;
            self->parent = NULL;
            self->nextPart = other;
            SetStep(DRAGON_BOUNCING);
        }
        break;
    case DRAGON_BOUNCING:
        MoveEntity();
        self->velocityY += self->ext.orob.gravity;
        self->ext.orob.gravity += 0x100;
        if (self->ext.orob.movingLeft != self->facingLeft &&
            (AnimateEntity(anim_head_flip_withrider, self) == 0)) {
            self->animCurFrame = 1;
            self->facingLeft = self->ext.orob.movingLeft;
        }
        if (self->rotate) {
            self->rotate -= 0x10;
        }
        xVar = self->posX.i.hi;
        yVar = self->posY.i.hi + 12;
        g_api.CheckCollision(xVar, yVar, &sp2C, 0);
        if (sp2C.effects & EFFECT_SOLID) {
            PlaySfxPositional(SFX_EXPLODE_F);
            self->posY.i.hi += sp2C.unk18;
            self->velocityY = FIX(-2.75);
            self->ext.orob.gravity = 0;
            temp_s6 = self->ext.orob.movingLeft;
            if (temp_s6 == (GetSideToPlayer() & 1)) {
                self->ext.orob.unk9--;
            } else {
                self->ext.orob.unk9 = 2;
            }
            xVar = g_Tilemap.scrollX.i.hi + self->posX.i.hi;
            if (self->ext.orob.movingLeft) {
                if ((u32)((g_Tilemap.hSize << 8) - 0x80) < xVar) {
                    self->ext.orob.unk9 = 0;
                }
            } else if (xVar < 0x80) {
                self->ext.orob.unk9 = 0;
            }
            if (!self->ext.orob.unk9) {
                self->ext.orob.unk9 = 2;
                self->ext.orob.movingLeft ^= 1;
                self->poseTimer = 0;
                self->pose = 0;
            } else {
                self->rotate = 0x200;
            }
            if (self->ext.orob.movingLeft) {
                self->velocityX = FIX(1.5);
                EntityGreyPuffSpawner(self, 5, 3, 4, 12, 0, -4);
            } else {
                self->velocityX = FIX(-1.5);
                EntityGreyPuffSpawner(self, 5, 3, -4, 12, 0, 4);
            }
        }
        break;
    case DRAGON_DEAD:
        PlaySfxPositional(SFX_SKELETON_DEATH_A);
        other = self + 1;
        for (i = 0; i < 24; i++, other++) {
            other->flags |= FLAG_DEAD;
        }
        other = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (other != NULL) {
            CreateEntityFromEntity(E_EXPLOSION, self, other);
            other->params = 3;
        }
        for (i = 0; i < 4; i++) {
            other = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (other != NULL) {
                // NOTE: There is a dedicated entity for dragon head parts,
                // but we actually use the orob head parts when dragon dies.
                CreateEntityFromEntity(E_OROB_HEAD_PARTS, self, other);
                other->facingLeft = self->facingLeft;
                other->velocityX = self->velocityX;
                other->velocityY = FIX(-1.5);
                other->params = i;
            }
        }
        DestroyEntity(self);
        return;
    }
    temp_s2 = &D_pspeu_0925A788[0];
    var_s4 = self->animCurFrame - 1;
    if (var_s4 < 0) {
        var_s4 = 0;
    }
    temp_s2 += var_s4 * 4;
    self->hitboxOffX = *temp_s2++;
    self->hitboxOffY = *temp_s2++;
    self->hitboxWidth = *temp_s2++;
    self->hitboxHeight = *temp_s2++;
}

typedef enum{
    DRAGSEG_INIT,
    DRAGSEG_DELAY,
    DRAGSEG_FOLLOW,
    DRAGSEG_DEAD = 8
} DragonSegmentSteps;

void EntityDragonSegment(Entity* self) {
    Collider sp2C;
    Entity* other;
    s32 temp_s0;
    s32 xVar;
    s32 yVar;

    if ((self->flags & FLAG_DEAD) && (self->step < 8)) {
        self->hitboxState = 0;
        self->flags |= FLAG_DESTROY_IF_OUT_OF_CAMERA |
                       FLAG_DESTROY_IF_BARELY_OUT_OF_CAMERA;
        SetStep(DRAGSEG_DEAD);
    }
    switch (self->step) { /* irregular */
    case DRAGSEG_INIT:
        InitializeEntity(g_EInitDragonRider2);
        self->pose = self->params % 6;
        self->drawFlags |= ENTITY_OPACITY;
        temp_s0 = self->params;
        self->opacity = 0x80 - temp_s0;
        temp_s0 -= 10;
        if (temp_s0 > 0) {
            self->drawFlags = ENTITY_SCALEY | ENTITY_SCALEX;
            self->scaleX = self->scaleY = 0x100 - (temp_s0 * 6);
        }
        self->ext.orob.stepTimer = self->params * 5;
        /* fallthrough */
    case DRAGSEG_DELAY:
        if (self->ext.orob.stepTimer) {
            self->ext.orob.stepTimer--;
        } else {
            self->step = 2;
        }
        break;
    case DRAGSEG_FOLLOW:
        MoveEntity();
        self->velocityY += self->ext.orob.gravity;
        self->ext.orob.gravity += 0x100;
        xVar = self->posX.i.hi;
        yVar = self->posY.i.hi + 6;
        g_api.CheckCollision(xVar, yVar, &sp2C, 0);
        if (sp2C.effects & EFFECT_SOLID) {
            self->posY.i.hi += sp2C.unk18;
            self->velocityY = FIX(-2.75);
            self->ext.orob.gravity = 0;
            other = self - 1;
            if (other->ext.orob.movingLeft != self->ext.orob.movingLeft) {
                self->ext.orob.movingLeft = other->ext.orob.movingLeft;
            }
            if (self->ext.orob.movingLeft) {
                self->velocityX = FIX(1.5);
            } else {
                self->velocityX = FIX(-1.5);
            }
        }
        break;
    case DRAGSEG_DEAD:
        MoveEntity();
        self->velocityY += 0x1400;
        return;
    }
    AnimateEntity(&anim_bone_twisting2, self);
    temp_s0 = self->params & 3;
    if ((g_Timer & 3) == temp_s0) {
        self->hitboxState = 3;
        return;
    }
    self->hitboxState = 0;
}

// Unused!
void EntityDragonHeadParts(Entity* self) {
    adhoc_vels_rot* temp_s0;

    if (!self->step) {
        InitializeEntity(D_us_801809F8);
        self->drawFlags = ENTITY_ROTATE;
        self->hitboxState = 0;
        self->animCurFrame = self->params + 8;
        self->zPriority += self->params;
        temp_s0 = &D_pspeu_0925A758[self->params];
        if (self->facingLeft) {
            self->velocityX += temp_s0->velX;
        } else {
            self->velocityX += -temp_s0->velX;
        }
        self->velocityY += temp_s0->velY;
    }
    MoveEntity();
    self->velocityY += FIX(0.09375);
    temp_s0 = &D_pspeu_0925A758[self->params];
    self->rotate += temp_s0->rotate;
}

void func_us_801C4C50(Entity* self) {
    s32 animIdx;
    s16* xywh_ptr;
    Entity* other;

    if (!self->step) {
        InitializeEntity(g_EInitDragonRider1);
        self->animCurFrame = 0;
    }
    other = self - 25;
    self->posX.i.hi = other->posX.i.hi;
    self->posY.i.hi = other->posY.i.hi;
    self->facingLeft = other->facingLeft;
    xywh_ptr = &D_pspeu_0925A7A0[0];
    animIdx = other->animCurFrame - 1;
    if (animIdx < 0) {
        animIdx = 0;
    }
    xywh_ptr += animIdx * 4;
    self->hitboxOffX = *xywh_ptr++;
    self->hitboxOffY = *xywh_ptr++;
    self->hitboxWidth = *xywh_ptr++;
    self->hitboxHeight = *xywh_ptr++;
    if (other->entityId != E_DRAGON_RIDER) {
        DestroyEntity(self);
    }
}
