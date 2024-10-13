#include "chi.h"

/*
 * File: 2B7CC.c
 * Overlay: CHI
 * Description: Abandoned Mine
 */

// D_801817F4
u8 PhysicsSensors_VenusWeed[] = {
    0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x04, 0x00, 0x02, 0x00, 0xFC, 0xFF, 0xFC, 0xFF, 0x00, 0x00
};

u8 D_80181804[] = {
    0x00, 0x00, 0x01, 0x00, 0x04, 0x00, 0x00, 0x00
};

u8 D_8018180C[] = {
    0x01, 0x01, 0x0A, 0x03, 0x06, 0x04, 0x06, 0x05, 0x05, 0x06, 0x05, 0x07, 0x05, 0x08, 0x05, 0x09,
    0x05, 0x0A, 0x08, 0x0C, 0xFF, 0x00, 0x00, 0x00
};

u8 D_80181824[] = {
    0x04, 0x0C, 0x08, 0x0E, 0x04, 0x0F, 0x01, 0x10, 0xFF, 0x00, 0x00, 0x00
};

u8 D_80181830[] = {
    0x03, 0x10, 0x08, 0x11, 0xFF, 0x00, 0x00, 0x00,
};

u8 D_80181838[] = {
    0x12, 0x11, 0x02, 0x12, 0x02, 0x13, 0x04, 0x14, 0x04, 0x15, 0x6F, 0x16, 0x08, 0x13, 0x08, 0x12,
    0x08, 0x11, 0x08, 0x10, 0x20, 0x0F, 0x08, 0x0E, 0x04, 0x0C, 0xFF, 0x00,
};

u8 D_80181854[] = {
    0x0A, 0x0B, 0x0A, 0x0C, 0x0A, 0x0D, 0x0A, 0x0C, 0x00, 0x00, 0x00, 0x00
};

u8 D_80181860[] = {
    0x10, 0x17, 0x08, 0x18, 0x06, 0x19, 0x05, 0x1A, 0x04, 0x1B, 0x01, 0x1C, 0xFF, 0x00, 0x00, 0x00
};

u8 D_80181870[] = {
    0x14, 0x1C, 0x03, 0x1D, 0x02, 0x1E, 0x02, 0x1F, 0x02, 0x20, 0x02, 0x21, 0x2A, 0x1F, 0x05, 0x0F,
    0x05, 0x0E, 0x10, 0x0C, 0xFF, 0x00, 0x00, 0x00
};

u8 D_80181888[] = {
    0x01, 0x26, 0x04, 0x27, 0x04, 0x28, 0x04, 0x29, 0x02, 0x2A, 0x02, 0x2B, 0x02, 0x2C, 0x02, 0x2D,
    0x02, 0x2E, 0x02, 0x2F, 0x02, 0x30, 0x02, 0x31, 0x02, 0x32, 0x02, 0x33, 0x02, 0x34, 0x02, 0x35,
    0x02, 0x36, 0x03, 0x33, 0x03, 0x34, 0x03, 0x35, 0x03, 0x36, 0x04, 0x33, 0x04, 0x34, 0x04, 0x35,
    0x04, 0x36, 0x05, 0x33, 0x05, 0x34, 0x05, 0x35, 0x05, 0x36, 0x04, 0x33, 0x04, 0x34, 0x04, 0x35,
    0xFF, 0x00, 0x00, 0x00
};

u8 D_801818CC[] = {
    0x03, 0x36, 0x03, 0x33, 0x02, 0x34, 0x01, 0x35, 0x04, 0x30, 0x04, 0x2F, 0x04, 0x2E, 0x05, 0x2D,
    0x05, 0x2C, 0x05, 0x2B, 0x05, 0x2A, 0x04, 0x29, 0x04, 0x28, 0x04, 0x27, 0x01, 0x26, 0xFF, 0x00
};

u8 D_801818EC[] = {
    0x03, 0x22, 0x03, 0x23, 0x03, 0x24, 0x03, 0x25, 0x00, 0x00, 0x00, 0x00
};

// D_801818F8
u8 AnimFrames_ThornweedDisguise[] = {
    0x05, 0x2A, 0x05, 0x2B, 0x05, 0x2C, 0x05, 0x2D, 0x00, 0x00, 0x00, 0x00
};

// D_80181904
u8 AnimFrames_ThornweedQuickWiggle[] = {
    0x02, 0x2A, 0x02, 0x2B, 0x02, 0x2C, 0x02, 0x2D, 0x00, 0x00
};

// D_8018190E
u8 D_8018190E[] = {
    0x10, 0x0C, 0x0E, 0x0E, 0x0C, 0x12, 0x0E, 0x13, 0x02, 0x14, 0x04, 0x15, 0x20, 0x16, 0xFF,
    0x00
};

extern EntityInit EntityInit_80180700;

// [Why can't PhysicsSensors_VenusWeed be named PhysicsSensors AND PhysicsSensors_Thornweed be named PhysicsSensors? Names collide why?]
// E_VENUS_WEED
// func_801AB7CC
// https://decomp.me/scratch/QrYmQ
// PSP:func_psp_0923AE68:Match
// PSP:https://decomp.me/scratch/MjOOd
void EntityVenusWeed(Entity* self)
{
    const int ActivateDistanceX = 0x70;
    const int LeavesWidthMax = 0x38;
    const int LeavesHeightMax = 0x22;
    const int StemWidthMax = 0xC;
    const int StemHeightMax = 0x22;
    const int FlowerOffsetY = 0x1B;
    const int WiggleLeavesSpeed = 0x180;
    const int AttackDuration = 0x30;
    const int DeathFinalClut = PAL_DRA(0x210);

    enum Step {
        INIT = 0,
        DROP_TO_GROUND = 1,
        THORNWEED_DISGUISE = 2,
        GROW = 3,
        IDLE = 4,
        ATTACK = 5,
        DEATH = 8,
    };

    enum Grow_Substep {
        GROW_LEAVES = 0,
        GROW_STEM = 1,
        GROW_FLOWER = 2,
        GROW_TENDRILS = 3,
        GROW_DONE = 4,
    };

    enum Death_Substep {
        DEATH_INIT = 0,
        DEATH_COLOR_CYCLE = 1,
        DEATH_SHRINK = 2,
        DEATH_DONE = 3,
    };

    Entity* entity;
    s32 x;
    s32 primIdx;
    s32 y;
    Primitive* prim;
    s32 checkCount;
    s32 i;
    s16 rot;

    // Death check
    if ((self->flags & FLAG_DEAD) && (self->step < DEATH)) {
        SetStep(DEATH);
    }

    switch (self->step) {
        case INIT:
            InitializeEntity(&EntityInit_80180700);
            self->hitboxOffX = 1;
            self->hitboxOffY = -7;

            primIdx = g_api.AllocPrimitives(PRIM_GT4, 3);
            if (primIdx == -1) {
                DestroyEntity(self);
                return;
            }
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIdx;
            prim = &g_PrimBuf[primIdx];
            self->ext.prim = prim;

            for (i = 0; i < 2; i++) {
                prim->tpage = 0x14;
                prim->clut = PAL_DRA(0x21A);
                prim->u0 = prim->u2 = 0x48;
                prim->u1 = prim->u3 = 0x80;
                prim->v0 = prim->v1 = 0;
                prim->v2 = prim->v3 = 0x22;
                prim->priority = self->zPriority - 1;
                prim->drawMode = DRAW_HIDE;

                prim = prim->next;
            }

            self->ext.venusWeed.prim = prim;
            prim->tpage = 0x14;
            prim->clut = 0x21A;
            prim->u0 = prim->u2 = 0;
            prim->u1 = prim->u3 = 0x18;
            prim->v0 = prim->v1 = 0x30;
            prim->v2 = prim->v3 = 0x52;
            prim->priority = self->zPriority - 2;
            prim->drawMode = 8;

            prim = prim->next;
            break;

        case DROP_TO_GROUND:
            if (UpdatePhysicsState(&PhysicsSensors_VenusWeed) & 1) {
                SetStep(THORNWEED_DISGUISE);
            }
            break;

        case THORNWEED_DISGUISE:
            AnimateEntity(&AnimFrames_ThornweedDisguise, self);
            if (GetDistanceToPlayerX() < ActivateDistanceX) {
                self->hitboxState = 0;
                SetStep(3);
            }

            // Death check
            if (self->flags & FLAG_DEAD) {
                entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (entity != NULL) {
                    CreateEntityFromEntity(E_EXPLOSION, self, entity);
                    entity->posY.i.hi -= 4;
                    entity->params = 0;
                }

                PlaySfxWithPosArgs(NA_SE_EN_EXPLOSIVE_DEATH);
                DestroyEntity(self);
                return;
            }
            break;

        case GROW:
            AnimateEntity(&AnimFrames_ThornweedQuickWiggle, self);

            checkCount = 0;
            switch (self->step_s) {
                case GROW_LEAVES:
                    // Update leaves width
                    self->ext.venusWeed.leavesWidth++;
                    if (self->ext.venusWeed.leavesWidth > LeavesWidthMax) {
                        self->ext.venusWeed.leavesWidth = LeavesWidthMax;
                        checkCount += 1;
                    }

                    // Update leaves height
                    self->ext.venusWeed.leavesHeight++;
                    if (self->ext.venusWeed.leavesHeight > LeavesHeightMax) {
                        self->ext.venusWeed.leavesHeight = LeavesHeightMax;
                        checkCount += 1;
                    }

                    prim = self->ext.prim;
                    x = self->posX.i.hi;
                    y = self->posY.i.hi;
                    y -=self->ext.venusWeed.leavesHeight;
                    // 2 primitives: One for left and one for right
                    for (i = -1; i < 2; i += 2) {
                        prim->x0 = prim->x2 = x;
                        prim->x1 = prim->x3 = x + self->ext.venusWeed.leavesWidth * i;
                        prim->y0 = prim->y1 = y;
                        prim->y2 = prim->y3 = self->posY.i.hi;
                        prim->drawMode = DRAW_UNK02;

                        prim = prim->next;
                    }

                    // Check for completion
                    if (checkCount == 2) {
                        self->step_s++;
                    }
                    break;

                case GROW_STEM:
                    // Update stem width
                    self->ext.venusWeed.stemWidth++;
                    if (self->ext.venusWeed.stemWidth > StemWidthMax) {
                        self->ext.venusWeed.stemWidth = StemWidthMax;
                        checkCount += 1;
                    }

                    // Update stem height
                    self->ext.venusWeed.stemHeight++;
                    if (self->ext.venusWeed.stemHeight > StemHeightMax) {
                        self->ext.venusWeed.stemHeight = StemHeightMax;
                        checkCount += 1;
                    }

                    prim = self->ext.venusWeed.prim;
                    x = self->posX.i.hi;
                    y = self->posY.i.hi - self->ext.venusWeed.stemHeight;
                    prim->x0 = prim->x2 = x - self->ext.venusWeed.stemWidth;
                    prim->x1 = prim->x3 = x + self->ext.venusWeed.stemWidth;
                    prim->y0 = prim->y1 = y;
                    prim->y2 = prim->y3 = self->posY.i.hi;
                    prim->drawMode = DRAW_UNK02;

                    // Check for completion
                    if (checkCount == 2) {
                        self->step_s++;
                    }
                    break;

                case GROW_FLOWER:
                    entity = self + 1;

                    // Spawn entity
                    CreateEntityFromCurrentEntity(E_ID_2A, entity);
                    entity->posX.i.hi = self->posX.i.hi;
                    entity->posY.i.hi = self->posY.i.hi - FlowerOffsetY;

                    // Face the player
                    entity->facingLeft = GetSideToPlayer() & 1;
                    entity->zPriority = (s32)self->zPriority;

                    self->step_s++;
                    break;

                case GROW_TENDRILS:
                    entity = (self + 2);
                    for (i = 0; i < 0xA; i++, entity++) {
                        CreateEntityFromCurrentEntity(E_ID_2B, entity);
                        entity->params = i;
                        entity->zPriority = self->zPriority + 1;
                    }

                    self->step_s++;
                    break;

                case GROW_DONE:
                    //TODO: Wait for signal?
                    break;
            }
            break;

        case IDLE:
            //TODO: Wait for signal?
            AnimateEntity(&AnimFrames_ThornweedDisguise, self);
            break;

        case ATTACK:
            //TODO: Wait for signal?
            if (self->ext.venusWeed.triggerAttack) {
                self->ext.venusWeed.triggerAttack = false;
                self->ext.venusWeed.timer = AttackDuration;
            }
            if (self->ext.venusWeed.timer) {
                AnimateEntity(&AnimFrames_ThornweedQuickWiggle, self);
                self->ext.venusWeed.timer--;
            }
            break;

        case DEATH:
            switch (self->step_s) {
                case DEATH_INIT:
                    self->ext.venusWeed.wiggleT = 0;
                    self->step_s++;
                    // fallthrough
                case DEATH_COLOR_CYCLE:
                    // Cycle thru cluts
                    if (!(g_Timer & 7)) {
                        // Switch to next clut
                        self->palette += 1;
                        // For primitives too
                        prim = self->ext.prim;
                        while (prim != NULL) {
                            prim->clut += 1;
                            prim = prim->next;
                        }
                        if (self->palette == DeathFinalClut) {
                            self->step_s++;
                        }
                    }
                    break;

                case DEATH_SHRINK:
                    checkCount = 0;
                    self->ext.venusWeed.timer++;
                    // Every other frame
                    if (self->ext.venusWeed.timer & 1) {
                        prim = self->ext.prim;
                        x = self->posX.i.hi;

                        // Shrink leaves
                        if (self->ext.venusWeed.leavesWidth) {
                            self->ext.venusWeed.leavesWidth--;
                            if (self->ext.venusWeed.leavesWidth < 0) {
                                self->ext.venusWeed.leavesWidth = 0;
                            }
                        }
                        // Update leaves sprites
                        for (i = -1; i < 2; i += 2) {
                            prim->x1 = x + (self->ext.venusWeed.leavesWidth + LeavesWidthMax) / 2 * i;
                            prim->x3 = x + (self->ext.venusWeed.leavesWidth * i);
                            prim->y0++;
                            prim->y1++;
                            if (prim->y1 > prim->y2) {
                                prim->drawMode = 8;
                                checkCount += 1;
                            }
                            prim = prim->next;
                        }
                    }

                    // Collapse stem
                    prim = self->ext.venusWeed.prim;
                    prim->y0 = ++prim->y1;
                    if (prim->y0 > prim->y2) {
                        prim->drawMode = DRAW_HIDE;
                        checkCount += 1;
                    }

                    // Check for completion
                    if (checkCount == 3) {
                        self->step_s += 1;
                    }
                    break;

                case DEATH_DONE:
                    // Spawn explosion
                    entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                    if (entity != NULL) {
                        CreateEntityFromEntity(E_EXPLOSION, self, entity);
                        entity->params = 2;
                        entity->posY.i.hi -= 0xC;
                    }

                    PlaySfxWithPosArgs(NA_SE_EN_VENUS_WEED_DEATH);

                    // Destroy
                    PreventEntityFromRespawning(self);
                    DestroyEntity(self);
                    return;
            }
    }

    // Update wiggle
    if (self->ext.venusWeed.wiggleT) {
        rot = self->rotZ;
        self->rotZ += WiggleLeavesSpeed;
        x = rcos(rot) * 3 >> 0xC;
        y = rsin(rot) * 3 >> 0xC;
        prim = self->ext.prim;

        // Update leaves
        for (i = -1; i < 2; i += 2) {
            prim->x1 = self->posX.i.hi + (x + LeavesWidthMax) * i;
            prim->y1 = self->posY.i.hi - LeavesHeightMax + y * i;

            prim = prim->next;
        }

        // Update stem
        x /= 2;
        entity = self + 1;
        prim = self->ext.venusWeed.prim;
        self->ext.venusWeed.wiggleT--;
        if (!self->ext.venusWeed.wiggleT) {
            entity->posX.i.hi = self->posX.i.hi;
            prim->x0 = self->posX.i.hi - StemWidthMax;
            prim->x1 = self->posX.i.hi + StemWidthMax;
        } else {
            prim->x0 = self->posX.i.hi - StemWidthMax + x;
            prim->x1 = self->posX.i.hi + StemWidthMax + x;
            entity->posX.i.hi = self->posX.i.hi + x;
        }
    }
}

extern u8 D_8018180C[];
extern u8 D_80181854[];
extern u8 D_80181824[];
extern u8 D_80181830[];
extern u8 D_80181838[];
extern u8 D_80181860[];
extern u8 D_80181870[];
extern EntityInit EntityInit_8018070C;

// E_ID_2A
// func_801AC074
// https://decomp.me/scratch/0O3ex
// PSP:func_psp_0923BB48:Match
// PSP:https://decomp.me/scratch/yUOcn
void func_801AC074(Entity* self)
{
    Entity* entity;   // s0
    s32 x;            // s5
    s16 temp_v0_6;    // s2
    s32 var_s1;       // s1
    s32 var_s4;       // s4
    s32 var_v0;       // s3
    s32 y;            // s6

    if (self->hitFlags & 3) {
        PlaySfxWithPosArgs(0x70F);
        entity = self - 1;
        entity->ext.venusWeed.wiggleT = 0x40;
    }
    if ((self->flags & FLAG_DEAD) && (self->step < 8)) {
        PlaySfxWithPosArgs(0x710);
        SetStep(8);
    }

    switch (self->step) {
        case 0:
            InitializeEntity(&EntityInit_8018070C);
            self->hitboxOffX = 6;
            self->hitboxOffY = -0x10;
            self->hitboxWidth = 0xE;
            self->hitboxHeight = 0xE;
            self->animCurFrame = 1;
            self->drawFlags |= FLAG_DRAW_ROTX | FLAG_DRAW_ROTY;
            self->rotX = self->rotY = 0;
            self->hitboxState = 0;
            break;

        case 1:
            self->rotX = self->rotY += 6;
            if (self->rotX >= 0x100) {
                self->drawFlags = 0;
                self->hitboxState = 3;

                PlaySfxWithPosArgs(0x669);
                SetStep(2);
            }
            break;

        case 2:
            if (AnimateEntity(D_8018180C, self) == 0) {
                entity = self - 1;
                entity->step = 4;
                entity->step_s = 0;
                SetStep(3);
            }
            break;

        case 3:
            if (!self->step_s) {
                self->ext.venusWeedFlower.unk8C = 1;
                self->step_s++;
            }
            if (AnimateEntity(D_80181854, self) == 0) {
                self->facingLeft = GetSideToPlayer() & 1;
            }
            if (!--self->ext.venusWeedFlower.unk8C) {
                self->facingLeft = GetSideToPlayer() & 1;
                if (self->ext.venusWeedFlower.unk92) {
                    SetStep(5);
                } else {
                    SetStep(4);
                }
                self->ext.venusWeedFlower.unk92 ^= 1;
                return;
            }
            break;

        case 4:
            switch (self->step_s) {
                case 0:
                    entity = self - 1;
                    entity->step = 5;
                    entity->step_s = 0;
                    entity = self + 1;
                    for (var_s1 = 0; var_s1 < 0xA; var_s1++, entity++) {
                        entity->step = 3;
                        entity->step_s = 0;
                    }
                    self->step_s++;
                    // fallthrough
                case 1:
                    if (AnimateEntity(D_80181824, self) == 0) {
                        SetSubStep(2);
                    }
                    break;

                case 2:
                    PlaySfxWithPosArgs(0x6B0);
                    entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                    if (entity != NULL) {
                        CreateEntityFromEntity(0x2DU, self, entity);
                        entity->facingLeft = self->facingLeft;
                        entity->ext.venusWeedFlower.entity = self;
                    }
                    self->step_s++;
                    // fallthrough
                case 3:
                    if (AnimateEntity(D_80181830, self) == 0) {
                        entity = self + 1;
                        if (g_Timer & 1) {
                            var_v0 = 0;
                        } else {
                            var_v0 = 4;
                        }
                        for (var_s1 = 0; var_s1 < 10; var_s1++, entity++) {
                            entity->ext.venusWeedFlower.unk90 = var_v0 + 1;
                            var_v0++;
                            var_v0 &= 0x7;
                        }
                        SetSubStep(4);
                    }
                    break;

                case 4:
                    if (AnimateEntity(D_80181838, self) == 0) {
                        SetSubStep(5);
                    }
                    break;

                case 5:
                    entity = self - 1;
                    entity->step = 4;
                    SetStep(3);
                    break;
            }
            if (self->ext.venusWeedFlower.unk91) {
                entity = self - 1;
                entity->ext.venusWeed.triggerAttack = true;
                if (!(self->palette & 0x8000)) {
                    self->palette += self->ext.venusWeedFlower.unk91;
                    if (self->palette > 0x219) {
                        self->palette = 0x219;
                    }
                    self->ext.venusWeedFlower.unk91 = false;
                    return;
                }
            }
            break;

        case 5:
            switch (self->step_s) {
                case 0:
                    entity = self - 1;
                    entity->step = 6;
                    entity->step_s = 0;
                    self->step_s += 1;
                    // fallthrough
                case 1:
                    if (AnimateEntity(D_80181860, self) == 0) {
                        SetSubStep(2);
                        return;
                    }
                    break;

                case 2:
                    PlaySfxWithPosArgs(0x6B0);
                    entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                    if (entity != NULL) {
                        CreateEntityFromEntity(E_ID_2D, self, entity);
                        entity->facingLeft = self->facingLeft;
                        entity->ext.venusWeedFlower.entity = self;
                    }
                    self->step_s++;
                    // fallthrough
                case 3:
                    if (AnimateEntity(D_80181870, self) == 0) {
                        self->step_s++;
                    }
                    if (!self->animFrameDuration && self->animFrameIdx == 3) {
                        PlaySfxWithPosArgs(0x626);
                        if (self->facingLeft) {
                            x = self->posX.i.hi - 0x18;
                        } else {
                            x = self->posX.i.hi + 0x18;
                        }
                        y = self->posY.i.hi - 0x18;
                        entity = &PLAYER;
                        temp_v0_6 = ratan2(entity->posY.i.hi - y, entity->posX.i.hi - x);
                        if (self->facingLeft) {
                            if (temp_v0_6 < 0) {
                                if (temp_v0_6 > -0x480) {
                                    temp_v0_6 = -0x480;
                                }
                                var_s4 = -0x60;
                            } else {
                                if (temp_v0_6 < 0x500) {
                                    temp_v0_6 = 0x500;
                                }
                                var_s4 = 0x60;
                            }
                        } else if (temp_v0_6 < 0) {
                            if (temp_v0_6 < -0x380) {
                                temp_v0_6 = -0x380;
                            }
                            var_s4 = 0x60;
                        } else {
                            if (temp_v0_6 > 0x300) {
                                temp_v0_6 = 0x300;
                            }
                            var_s4 = -0x60;
                        }
                        for (var_s1 = 0; var_s1 < 5; var_s1++) {
                            entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
                            if (entity != NULL) {
                                CreateEntityFromEntity(E_ID_2C, self, entity);
                                entity->rotZ = temp_v0_6;
                                entity->params = var_s1;
                                entity->posX.i.hi = x;
                                entity->posY.i.hi -= 0x18;
                            }
                            temp_v0_6 += var_s4;
                        }
                        return;
                    }
                    break;

                case 4:
                    entity = self - 1;
                    entity->step = 4;
                    SetStep(3);
                    return;
            }
            break;

        case 8:
            entity = self + 1;
            for (var_s1 = 0; var_s1 < 0xA; var_s1++, entity++) {
                entity->flags |= FLAG_DEAD;
            }
            PlaySfxWithPosArgs(0x65B);
            self->hitboxState = 0;
            entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_EXPLOSION, self, entity);
                entity->params = 3;
            }
            entity = self - 1;
            entity->flags |= FLAG_DEAD;
            DestroyEntity(self);
            break;
    }
}

extern s8 D_80181920[];
extern s16 D_80181946[];
extern EntityInit EntityInit_80180718;

// E_ID_2B
// func_801AC730
// https://decomp.me/scratch/dVIWY
// PSP:func_psp_0923C4E8:No match
// PSP:https://decomp.me/scratch/tbskC
void func_801AC730(Entity* self)
{
    s32 var_s0;        // s0
    s8* temp_v1_2;     // s2
    Entity* entity;    // s1
    u32 temp;          // s3

    if ((self->flags & FLAG_DEAD) && (self->step < 8)) {
        SetStep(8);
    }

    switch (self->step) {
        case 0:
            InitializeEntity(&EntityInit_80180718);
            self->animCurFrame = 0;
            break;

        case 1:
            if (UpdatePhysicsState(PhysicsSensors_VenusWeed) & 1) {
                SetStep(2);
            }
            break;

        case 2:
            if (!self->step_s) {
                var_s0 = (self->params * 2) - 9;
                var_s0 = var_s0 * var_s0;
                if (self->params < 5) {
                    var_s0 = -var_s0;
                }
                if (var_s0 > 0) {
                    var_s0 += 0x18;
                } else {
                    var_s0 -= 0x18;
                }
                var_s0 += (Random() & 0x1F) - 0xF;
                self->ext.venusWeedTendril.unk94 = var_s0;
                self->step_s++;
            }
            AnimateEntity(D_801818EC, self);
            func_801A1914(D_80181804);
            entity = self - 1 - self->params;
            var_s0 = entity->posX.i.hi + self->ext.venusWeedTendril.unk94;
            var_s0 -= self->posX.i.hi;
            if (abs(var_s0) < 2) {
                self->step_s--;
            } else if (var_s0 > 0) {
                self->velocityX = (abs(var_s0) << 0xC) / 4;
            } else {
                self->velocityX = (-(abs(var_s0) << 0xC)) / 4;
            }
            break;

        case 3:
            switch (self->step_s) {
                case 0:
                    AnimateEntity(D_801818EC, self);
                    if (self->ext.venusWeedTendril.unk90) {
#if VERSION_PSP
                        self->ext.venusWeedTendril.unk8C = D_80181946[self->ext.venusWeedTendril.unk90 - 1];
#else
                        self->ext.venusWeedTendril.unk8C = D_80181946[self->ext.venusWeedTendril.unk90];
#endif
                        self->ext.venusWeedTendril.unk90 = 0;
                        SetSubStep(1);
                    }
                    break;

                case 1:
                    if (self->ext.venusWeedTendril.unk8C) {
                        self->ext.venusWeedTendril.unk8C--;
                        break;
                    }
                    self->step_s++;
                    // Fallthrough
                case 2:
                    if (AnimateEntity(D_80181888, self) == 0) {
                        SetSubStep(3);
                    }
                    if (!self->animFrameDuration && self->animFrameIdx == 0xA) {
                        PlaySfxWithPosArgs(0x6D2);
                    }
                    break;

                case 3:
                    if (AnimateEntity(D_801818CC, self) == 0) {
                        SetStep(2);
                    }
                    break;
            }
            if (self->hitFlags & 0x80) {
                entity = self - 1 - self->params;
                entity->ext.venusWeedTendril.unk91++;
            }
            break;

        case 8:
            if (!self->step_s) {
                self->ext.venusWeedTendril.unk8C = (self->params * 8) + 8;
                self->step_s++;
            }
            if (!--self->ext.venusWeedTendril.unk8C) {
                entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (entity != NULL) {
                    CreateEntityFromEntity(2U, self, entity);
                    entity->params = 2;
                    entity->posY.i.hi -= 0xC;
                }
                PlaySfxWithPosArgs(0x655);
                DestroyEntity(self);
                return;
            }
            break;
    }

    temp_v1_2 = D_80181920;
#if VERSION_PSP
    temp = D_8018190E[self->animCurFrame - 0x22];
#else
    temp = D_8018190E[self->animCurFrame];
#endif
    temp_v1_2 += temp * 4;
    self->hitboxOffX = *temp_v1_2++;
    self->hitboxOffY = *temp_v1_2++;
    self->hitboxWidth = *temp_v1_2++;
    self->hitboxHeight = *temp_v1_2++;
}

extern EntityInit EntityInit_80180724;

// E_ID_2C
// func_801ACB6C
// https://decomp.me/scratch/AyVyt
// PSP:func_psp_0923CAC8:Match
// PSP:https://decomp.me/scratch/qBeC0
void func_801ACB6C(Entity* self)
{
    Collider collider;
    Entity* entity;     // s0
    s16 temp_s0;        // s1
    s32 temp_lo;        // s4
    s32 temp_s1;        // s2
    s32 temp_v1_2;      // s3

    switch (self->step) {
        case 0:
            InitializeEntity(&EntityInit_80180724);
            self->animCurFrame = 0x37;
            self->drawFlags = 4;
            temp_s0 = self->rotZ;
            self->hitboxOffX = (rcos(temp_s0) * 6) >> 0xC;
            self->hitboxOffY = (rsin(temp_s0) * 6) >> 0xC;
            self->ext.venusWeedDart.unk94 = rcos(temp_s0) << 3 >> 0xC;
            self->ext.venusWeedDart.unk96 = rsin(temp_s0) << 3 >> 0xC;
            self->ext.venusWeedDart.unk98 = 0x8000;
            // fallthrough
        case 1:
            MoveEntity();
            temp_s0 = self->rotZ;
            temp_s1 = self->ext.venusWeedDart.unk98;
            self->velocityX = (temp_s1 * rcos(temp_s0)) >> 0xC;
            self->velocityY = (temp_s1 * rsin(temp_s0)) >> 0xC;
            self->ext.venusWeedDart.unk98 += self->ext.venusWeedDart.unk9C;
            self->ext.venusWeedDart.unk9C += ((self->params + 1) << 0xB);
            if (self->ext.venusWeedDart.unk9C > 0x10000) {
                self->ext.venusWeedDart.unk9C = 0x10000;
            }
            if (self->ext.venusWeedDart.unk98 > 0x60000) {
                self->ext.venusWeedDart.unk98 = 0x60000;
            }
            temp_lo = self->posX.i.hi + self->ext.venusWeedDart.unk94;
            temp_v1_2 = self->posY.i.hi + self->ext.venusWeedDart.unk96;
            g_api_CheckCollision(temp_lo, temp_v1_2, &collider, 0);
            if (collider.effects & 1) {
                PlaySfxWithPosArgs(0x64A);
                if (self->velocityY > 0) {
                    self->posY.i.hi += collider.unk18;
                }
                if (self->velocityY < 0) {
                    self->posY.i.hi += collider.unk20;
                }
                self->hitboxState = 0;
                self->ext.venusWeedDart.unk8C = 0x20;
                SetStep(3);
            }
            if (self->hitFlags & 0x80) {
                entity = &PLAYER;
                self->ext.venusWeedDart.unk94 = entity->posX.i.hi - self->posX.i.hi;
                self->ext.venusWeedDart.unk96 = entity->posY.i.hi - self->posY.i.hi;
                self->ext.venusWeedDart.unk8C = 0;
                self->hitboxState = 0;
                SetStep(2);
                break;
            }
            if (self->unk44) {
                self->flags & FLAG_DEAD;    // Weird?
            }
            break;
        
        case 2:
            if (!(self->palette & 0x8000)) {
                self->ext.venusWeedDart.unk8C++;
                self->palette = self->ext.venusWeedDart.unk8C + 0x20A;
                
                if (self->palette > 0x219) {
                    self->palette = 0x219;
                }
            }
            if (self->ext.venusWeedDart.unk8C > 0x30) {
                self->flags |= 0x100;
            }
            entity = &PLAYER;
            self->posX.i.hi = entity->posX.i.hi - self->ext.venusWeedDart.unk94;
            self->posY.i.hi = entity->posY.i.hi - self->ext.venusWeedDart.unk96;
            break;
        
        case 3:
            if (!--self->ext.venusWeedDart.unk8C) {
                self->flags |= 0x100;
            }
            break;
    }
    
    if (self->flags & FLAG_DEAD) {
        entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (entity != NULL) {
            CreateEntityFromEntity(2U, self, entity);
            entity->params = 0;
        }
        DestroyEntity(self);
    }
}

Primitive* func_801AB548(Entity*, Primitive*);
extern EntityInit EntityInit_8018070C;

// E_ID_2D
// func_801ACEF4
// https://decomp.me/scratch/uQtVP
// PSP:func_psp_0923D008:No match
// PSP:https://decomp.me/scratch/zjZnY
void func_801ACEF4(Entity* self)
{
    Primitive* prim;    // s0
    Primitive* prim2;   // s1
    Primitive* prim3;   // s3
    s32 primIdx;        // s5
    Entity* entity;     // s2
    s16 var_s4;         // s4

    switch (self->step) {
        case 0:
            InitializeEntity(&EntityInit_8018070C);
            
            self->flags |= FLAG_UNK_2000 | FLAG_UNK_00200000;
            self->hitboxState = 0;
            self->palette = PAL_OVL(0x224);
            primIdx = g_api.AllocPrimitives(PRIM_GT4, 5);
            if (primIdx == -1) {
                DestroyEntity(self);
                break;
            } else {
                self->flags |= FLAG_HAS_PRIMS;
                self->primIndex = primIdx;
                prim = &g_PrimBuf[primIdx];
                self->ext.venusWeedTendrilSpike.unk7C = prim;
                entity = self->ext.venusWeedTendrilSpike.unkA4;
                entity--;
                prim = self->ext.venusWeedTendrilSpike.unk7C;
                prim = func_801AB548(entity, prim);
                for (prim2 = entity->ext.venusWeedTendrilSpike.unk7C; prim2 != NULL; prim2 = prim2->next, prim = prim3) {
                    prim3 = prim->next;
                    
                    *prim = *prim2;
                    prim->next = prim3;
                    prim->priority = prim2->priority + 1;
                }
            }
            entity = entity + 1;
            self->animCurFrame = entity->animCurFrame;
            self->zPriority = entity->zPriority + 1;
            // Fallthrough
        case 1:
            var_s4 = self->palette & 0xFFF;
            prim = self->ext.prim;
            while (prim != NULL) {
                prim->clut = var_s4;
                prim->drawMode = 2;
                prim = prim->next;
            }
            entity = self->ext.venusWeedTendrilSpike.unkA4;
            self->animCurFrame = entity->animCurFrame;
            self->palette++;
            var_s4 = self->palette & 0xFFF;
            if (var_s4 > 0x232) {
                DestroyEntity(self);
            } else {
                if (entity->entityId != 0x2A) {
                    DestroyEntity(self);
                }
            }
            break;
    }
}

s32 func_801AE70C(Primitive* prim, u8 arg1);
void StageNamePopupHelper(Primitive* prim)  // [Duplicate]
{
    u8 xPos;
    s32 i;
    s32 j;

    switch (prim->p3) {
    case 0:
        if (prim->p1 < 0x80) {
            if (--prim->p1 == 0) {
                prim->p3 = 1;
            }
        } else {
            if (++prim->p1 == 0) {
                prim->p3 = 2;
            }
        }

        if (prim->p3 != 0) {
            u8* dst = prim->p3 == 1 ? &prim->r1 : &prim->r0;
            for (i = 0; i < 2; i++) {
                for (j = 0; j < 3; j++) {
                    dst[j] = 0x50;
                }
                dst += 0x18;
            }
            prim->p2 = 0;
        }
        break;
    case 1:
        if (prim->p2 < 0x14) {
            prim->p2++;
        }
        xPos = prim->p2 / 5;
        prim->x2 = prim->x0 = prim->x0 + xPos;
        prim->x1 = prim->x1 + xPos;
        prim->x3 = prim->x0;
        func_801AE70C(prim, 4);
        break;
    case 2:
        if (prim->p2 < 0x14) {
            prim->p2++;
        }
        xPos = prim->p2 / 5;
        prim->x2 = prim->x0 = prim->x0 - xPos;
        prim->x1 = prim->x1 - xPos;
        prim->x3 = prim->x0;
        func_801AE70C(prim, 4);
        break;
    }
}

// POSSIBLE FILE BREAK

//#ifndef NON_MATCHING
INCLUDE_ASM("st/chi/nonmatchings/2B7CC", func_801AD2BC);    // EntityStageNamePopup()
//#else
// /*?*/ void func_801AD0EC(?*);                                // extern
// extern u8 D_8003BE40;
// extern s8 D_8019B3C0;
// extern s8 D_8019B3D0;
// extern u16 EntityInit_80180640;

// void func_801AD2BC(Entity* arg0)
// {
//     Primitive* temp_s0;
//     Primitive* temp_s0_2;
//     Primitive* temp_s0_3;
//     Primitive* temp_s0_6;
//     Primitive* var_s0;
//     Primitive* var_s0_10;
//     Primitive* var_s0_11;
//     Primitive* var_s0_2;
//     Primitive* var_s0_3;
//     Primitive* var_s0_6;
//     Primitive* var_s0_7;
//     Primitive* var_s0_8;
//     Primitive* var_s0_9;
//     s16 temp_a0_2;
//     s16 temp_a0_3;
//     s16 temp_v0;
//     s16 temp_v0_10;
//     s16 temp_v0_12;
//     s16 temp_v0_17;
//     s16 temp_v0_18;
//     s16 temp_v0_19;
//     s16 temp_v0_4;
//     s16 temp_v0_5;
//     s16 temp_v0_6;
//     s16 temp_v0_7;
//     s16 temp_v0_8;
//     s16 temp_v1_2;
//     s16 temp_v1_3;
//     s16 var_v0_2;
//     s16 var_v1;
//     s16 var_v1_2;
//     s32 temp_s0_4;
//     s32 temp_s0_5;
//     s32 temp_v0_15;
//     s32 temp_v0_20;
//     s32 temp_v0_21;
//     s32 temp_v0_22;
//     s32 temp_v0_3;
//     s32 var_a0;
//     s32 var_s0_4;
//     s32 var_s0_5;
//     s32 var_s1;
//     s32 var_s1_10;
//     s32 var_s1_11;
//     s32 var_s1_12;
//     s32 var_s1_13;
//     s32 var_s1_3;
//     s32 var_s1_4;
//     s32 var_s1_5;
//     s32 var_s1_6;
//     s32 var_s1_7;
//     s32 var_s1_8;
//     s32 var_s1_9;
//     s32 var_v0;
//     u16 temp_a0;
//     u16 temp_v0_2;
//     u16 temp_v1;
//     u16 temp_v1_4;
//     u8 temp_a1;
//     u8 temp_a1_2;
//     u8 temp_a2;
//     u8 temp_v0_11;
//     u8 temp_v0_13;
//     u8 temp_v0_14;
//     u8 temp_v0_16;
//     u8 temp_v0_9;
//     u8 var_a1;
//     u8 var_a1_2;
//     u8 var_s1_2;

//     temp_a0 = arg0->step;
//     switch (temp_a0) {                              // switch 1; irregular
//         case 0:                                     // switch 1
//             if ((g_DemoMode == Demo_None) && (D_8003BE40 == 0)) {
//                 InitializeEntity(&EntityInit_80180640);
//                 temp_v0 = g_api_AllocPrimitives(PRIM_GT4, 0x57);
//                 if (temp_v0 != -1) {
//                     var_s0 = &g_PrimBuf[temp_v0];
//                     arg0->primIndex = (s32) temp_v0;
//                     arg0->ext.prim = var_s0;
//                     arg0->flags |= 0x800000;
//                     if (var_s0 != NULL) {
//                         do {
//                             var_s0->drawMode = 8;
//                             var_s0 = var_s0->next;
//                         } while (var_s0 != NULL);
//                     }
//                     var_s0_2 = arg0->ext.prim;
//                     var_s1 = 0;
//                     do {
//                         temp_v0_2 = 0xC0 - var_s1;
//                         var_s1 += 1;
//                         var_s0_2->tpage = 0x11;
//                         var_s0_2->clut = 0x19F;
//                         var_s0_2->u2 = 4;
//                         var_s0_2->u0 = 4;
//                         var_s0_2->u3 = 0x78;
//                         var_s0_2->u1 = 0x78;
//                         var_s0_2->v1 = 0;
//                         var_s0_2->v0 = 0;
//                         var_s0_2->v3 = 0x28;
//                         var_s0_2->v2 = 0x28;
//                         var_s0_2->x0 = 0xC;
//                         var_s0_2->x2 = 0xC;
//                         var_s0_2->y0 = 0x9D;
//                         var_s0_2->y1 = 0x9D;
//                         var_s0_2->x1 = 0x80;
//                         var_s0_2->x3 = 0x80;
//                         var_s0_2->y2 = 0xC5;
//                         var_s0_2->y3 = 0xC5;
//                         var_s0_2->priority = temp_v0_2;
//                         var_s0_2->drawMode = 8;
//                         temp_s0 = var_s0_2->next;
//                         temp_s0->tpage = 0x11;
//                         temp_s0->clut = 0x19F;
//                         temp_s0->u2 = 8;
//                         temp_s0->u0 = 8;
//                         temp_s0->u3 = 0x7C;
//                         temp_s0->u1 = 0x7C;
//                         temp_s0->v1 = 0x40;
//                         temp_s0->v0 = 0x40;
//                         temp_s0->v3 = 0x68;
//                         temp_s0->v2 = 0x68;
//                         temp_s0->x0 = 0x80;
//                         temp_s0->x2 = 0x80;
//                         temp_s0->y0 = 0x9D;
//                         temp_s0->priority = temp_v0_2;
//                         temp_s0->y1 = 0x9D;
//                         temp_s0->x1 = 0xF4;
//                         temp_s0->x3 = 0xF4;
//                         temp_s0->y2 = 0xC5;
//                         temp_s0->y3 = 0xC5;
//                         temp_s0->drawMode = 8;
//                         var_s0_2 = temp_s0->next;
//                     } while (var_s1 < 2);
//                     var_s1_2 = 0;
//                     arg0->ext.generic.unk88.unk = var_s0_2;
//                     var_s0_2->u2 = 4;
//                     var_s0_2->u0 = 4;
//                     var_s0_2->u3 = 0x78;
//                     var_s0_2->u1 = 0x78;
//                     var_s0_2->tpage = 0x11;
//                     var_s0_2->clut = 0x19D;
//                     var_s0_2->v1 = 0;
//                     var_s0_2->v0 = 0;
//                     var_s0_2->v3 = 0x28;
//                     var_s0_2->v2 = 0x28;
//                     var_s0_2->x0 = 0xC;
//                     var_s0_2->x2 = 0xC;
//                     var_s0_2->y0 = 0x9D;
//                     var_s0_2->y1 = 0x9D;
//                     var_s0_2->x1 = 0x80;
//                     var_s0_2->x3 = 0x80;
//                     var_s0_2->y2 = 0xC5;
//                     var_s0_2->y3 = 0xC5;
//                     var_s0_2->priority = 0xBF;
//                     var_s0_2->drawMode = 8;
//                     temp_s0_2 = var_s0_2->next;
//                     temp_s0_2->clut = 0x19D;
//                     temp_s0_2->tpage = 0x11;
//                     temp_s0_2->u2 = 8;
//                     temp_s0_2->u0 = 8;
//                     temp_s0_2->u3 = 0x7C;
//                     temp_s0_2->u1 = 0x7C;
//                     temp_s0_2->v1 = 0x40;
//                     temp_s0_2->v0 = 0x40;
//                     temp_s0_2->v3 = 0x68;
//                     temp_s0_2->v2 = 0x68;
//                     temp_s0_2->x0 = 0x80;
//                     temp_s0_2->x2 = 0x80;
//                     temp_s0_2->y0 = 0x9D;
//                     temp_s0_2->y1 = 0x9D;
//                     temp_s0_2->x1 = 0xF4;
//                     temp_s0_2->x3 = 0xF4;
//                     temp_s0_2->y2 = 0xC5;
//                     temp_s0_2->y3 = 0xC5;
//                     temp_s0_2->priority = 0xBF;
//                     temp_s0_2->drawMode = 8;
//                     temp_s0_3 = temp_s0_2->next;
//                     arg0->ext.generic.unk84.unk = temp_s0_3;
//                     temp_s0_3->u0 = 0;
//                     temp_s0_3->u1 = 0x40;
//                     temp_s0_3->type = 3;
//                     temp_s0_3->tpage = 0x1A;
//                     temp_s0_3->clut = 0x15F;
//                     temp_s0_3->v0 = 0xC0;
//                     temp_s0_3->v1 = 0xC0;
//                     temp_s0_3->v2 = 0xFF;
//                     temp_s0_3->v3 = 0xFF;
//                     temp_s0_3->y0 = 0x9B;
//                     temp_s0_3->y1 = 0x9B;
//                     temp_s0_3->y2 = 0xC7;
//                     temp_s0_3->y3 = 0xC7;
//                     temp_s0_3->x0 = 0xC;
//                     temp_s0_3->x2 = 0xC;
//                     temp_s0_3->x1 = 0xF4;
//                     temp_s0_3->x3 = 0xF4;
//                     temp_s0_3->r0 = 0x10;
//                     temp_s0_3->g0 = 0x28;
//                     temp_s0_3->u2 = temp_s0_3->u0;
//                     temp_s0_3->u3 = temp_s0_3->u1;
//                     temp_s0_3->b0 = 0;
//                     temp_s0_3->r2 = 8;
//                     temp_s0_3->g2 = 0;
//                     temp_s0_3->b2 = 0x38;
//                     temp_s0_3->priority = 0xB0;
//                     temp_s0_3->drawMode = 0x1D;
//                     temp_s0_3->unk10 = (s32) temp_s0_3->unk4;
//                     temp_s0_3->unk28 = (s32) temp_s0_3->unk1C;
//                     var_s0_3 = temp_s0_3->next;
//                     arg0->ext.factory.parent = var_s0_3;
//                     var_v1 = 0x9D;
//                     do {
//                         temp_a0_2 = var_s1_2 + 0x9E;
//                         temp_a1 = var_s1_2;
//                         var_s1_2 += 1;
//                         var_s0_3->v3 = var_s1_2;
//                         var_s0_3->v2 = var_s1_2;
//                         var_s0_3->y0 = var_v1;
//                         var_s0_3->y1 = var_v1;
//                         var_s0_3->r0 = 0x78;
//                         var_s0_3->g0 = 0x78;
//                         var_s0_3->b0 = 0xA8;
//                         var_s0_3->y2 = temp_a0_2;
//                         var_s0_3->y3 = temp_a0_2;
//                         var_s0_3->v1 = temp_a1;
//                         var_s0_3->v0 = temp_a1;
//                         var_s0_3->priority = 0xC0;
//                         var_s0_3->tpage = 0x11;
//                         var_s0_3->clut = 0x19F;
//                         var_s0_3->x0 = 0xC;
//                         var_s0_3->x2 = 0xC;
//                         var_s0_3->x1 = 0x80;
//                         var_s0_3->x3 = 0x80;
//                         var_s0_3->u0 = 4;
//                         var_s0_3->u2 = 4;
//                         var_s0_3->u3 = 0x78;
//                         var_s0_3->u1 = 0x78;
//                         var_s0_3->drawMode = 0xC;
//                         var_s0_3->unk10 = (s32) var_s0_3->unk4;
//                         var_s0_3->unk1C = (s32) var_s0_3->unk4;
//                         var_s0_3->unk28 = (s32) var_s0_3->unk4;
//                         var_s0_3 = var_s0_3->next;
//                         var_v1 = var_s1_2 + 0x9D;
//                     } while ((s32) var_s1_2 < 0x28);
//                     var_s1_3 = 0;
//                     var_v1_2 = 0x9D;
//                     do {
//                         temp_a0_3 = var_s1_3 + 0x9E;
//                         temp_a1_2 = var_s1_3 + 0x40;
//                         var_s0_3->clut = 0x19F;
//                         var_s0_3->y0 = var_v1_2;
//                         var_s0_3->y1 = var_v1_2;
//                         var_s0_3->r0 = 0x78;
//                         var_s0_3->g0 = 0x78;
//                         var_s0_3->b0 = 0xA8;
//                         temp_a2 = var_s1_3 + 0x41;
//                         var_s0_3->y2 = temp_a0_3;
//                         var_s0_3->y3 = temp_a0_3;
//                         var_s1_3 += 1;
//                         var_s0_3->v1 = temp_a1_2;
//                         var_s0_3->v0 = temp_a1_2;
//                         var_s0_3->priority = 0xC0;
//                         var_s0_3->drawMode = 0xC;
//                         var_s0_3->tpage = 0x11;
//                         var_s0_3->x0 = 0x80;
//                         var_s0_3->x2 = 0x80;
//                         var_s0_3->x1 = 0xF4;
//                         var_s0_3->x3 = 0xF4;
//                         var_s0_3->u0 = 8;
//                         var_s0_3->u2 = 8;
//                         var_s0_3->u3 = 0x7C;
//                         var_s0_3->u1 = 0x7C;
//                         var_s0_3->v3 = temp_a2;
//                         var_s0_3->v2 = temp_a2;
//                         var_s0_3->unk10 = (s32) var_s0_3->unk4;
//                         var_s0_3->unk1C = (s32) var_s0_3->unk4;
//                         var_s0_3->unk28 = (s32) var_s0_3->unk4;
//                         var_s0_3 = var_s0_3->next;
//                         var_v1_2 = var_s1_3 + 0x9D;
//                     } while (var_s1_3 < 0x28);
//                     arg0->ext.generic.unk80.modeS32 = 0x20;
//                 case 1:                             // switch 1
//                     temp_v1 = arg0->step_s;
//                     switch (temp_v1) {
//                         case 0:
//                             temp_v0_3 = arg0->ext.generic.unk80.modeS32;
//                             if (temp_v0_3 != 0) {
//                                 arg0->ext.generic.unk80.modeS32 = temp_v0_3 - 1;
//                             } else {
//                                 temp_s0_4 = arg0->ext.generic.unk84.unk;
//                                 temp_s0_4->unk20 = 0x80;
//                                 temp_s0_4->unk8 = 0x80;
//                                 temp_s0_4->unk2C = 0x80;
//                                 temp_s0_4->unk14 = 0x80;
//                                 temp_s0_4->unk16 = 0xB1;
//                                 temp_s0_4->unkA = 0xB1;
//                                 temp_s0_4->unk2E = 0xB1;
//                                 temp_s0_4->unk22 = 0xB1;
//                                 temp_s0_4->unk32 = 0x15;
// block_78:
// block_79:
//                                 arg0->step_s += 1;
//                             }
//                             break;
//                         case 1:
//                             temp_s0_5 = arg0->ext.generic.unk84.unk;
//                             temp_v0_4 = temp_s0_5->unkA;
//                             var_a0 = 0;
//                             if (temp_v0_4 >= 0x9C) {
//                                 var_a0 = 1;
//                                 temp_v1_2 = temp_v0_4 - 4;
//                                 temp_s0_5->unkA = temp_v1_2;
//                                 temp_s0_5->unk16 = temp_v1_2;
//                                 temp_v0_5 = (u16) temp_s0_5->unk22 + 4;
//                                 temp_s0_5->unk22 = temp_v0_5;
//                                 temp_s0_5->unk2E = temp_v0_5;
//                             }
//                             temp_v0_6 = temp_s0_5->unk8;
//                             var_v0 = var_a0 & 0xFF;
//                             if (temp_v0_6 >= 0xD) {
//                                 temp_v1_3 = temp_v0_6 - 8;
//                                 temp_s0_5->unk8 = temp_v1_3;
//                                 temp_s0_5->unk20 = temp_v1_3;
//                                 temp_v0_7 = (u16) temp_s0_5->unk14 + 8;
//                                 temp_s0_5->unk14 = temp_v0_7;
//                                 temp_s0_5->unk2C = temp_v0_7;
//                                 var_v0 = (var_a0 | 1) & 0xFF;
//                             }
//                             if (var_v0 == 0) {
//                                 arg0->ext.generic.unk80.modeS32 = 0;
//                                 arg0->ext.factory.childId = 0;
//                                 arg0->ext.factory.unk92 = 0;
//                                 goto block_79;
//                             }
//                             break;
//                         case 2:
//                             temp_v0_8 = (u16) arg0->ext.factory.childId + 3;
//                             arg0->ext.factory.childId = temp_v0_8;
//                             var_s1_4 = 0;
//                             if (temp_v0_8 >= 0x80) {
//                                 arg0->step_s += 1;
//                             }
//                             var_s0_4 = arg0->ext.generic.unk88.unk;
//                             var_s0_4->unk32 = 0x75;
// loop_34:
//                             temp_v0_9 = (u8) arg0->ext.stub[0x14];
//                             var_s1_4 += 1;
//                             var_s0_4->unk2A = temp_v0_9;
//                             var_s0_4->unk29 = temp_v0_9;
//                             var_s0_4->unk28 = temp_v0_9;
//                             var_s0_4->unk1E = temp_v0_9;
//                             var_s0_4->unk1D = temp_v0_9;
//                             var_s0_4->unk1C = temp_v0_9;
//                             var_s0_4->unk12 = temp_v0_9;
//                             var_s0_4->unk11 = temp_v0_9;
//                             var_s0_4->unk10 = temp_v0_9;
//                             var_s0_4->unk6 = temp_v0_9;
//                             var_s0_4->unk5 = temp_v0_9;
//                             var_s0_4->unk4 = temp_v0_9;
//                             var_s0_4 = var_s0_4->unk0;
//                             if (var_s1_4 < 2) {
//                                 var_s0_4->unk32 = 0x75;
//                                 goto loop_34;
//                             }
//                             break;
//                         case 3:
//                             temp_v0_10 = (u16) arg0->ext.factory.childId - 2;
//                             arg0->ext.factory.childId = temp_v0_10;
//                             var_s1_5 = 0;
//                             if (temp_v0_10 & 0x8000) {
//                                 arg0->ext.factory.childId = 0;
//                             }
//                             var_s0_5 = arg0->ext.generic.unk88.unk;
//                             do {
//                                 var_s0_5->unk32 = 0x35;
//                                 temp_v0_11 = (u8) arg0->ext.stub[0x14];
//                                 var_s1_5 += 1;
//                                 var_s0_5->unk2A = temp_v0_11;
//                                 var_s0_5->unk29 = temp_v0_11;
//                                 var_s0_5->unk28 = temp_v0_11;
//                                 var_s0_5->unk1E = temp_v0_11;
//                                 var_s0_5->unk1D = temp_v0_11;
//                                 var_s0_5->unk1C = temp_v0_11;
//                                 var_s0_5->unk12 = temp_v0_11;
//                                 var_s0_5->unk11 = temp_v0_11;
//                                 var_s0_5->unk10 = temp_v0_11;
//                                 var_s0_5->unk6 = temp_v0_11;
//                                 var_s0_5->unk5 = temp_v0_11;
//                                 var_s0_5->unk4 = temp_v0_11;
//                                 var_s0_5 = var_s0_5->unk0;
//                             } while (var_s1_5 < 2);
//                             temp_v0_12 = arg0->ext.factory.childId;
//                             if (temp_v0_12 != 0) {
//                                 var_v0_2 = 0x80 - temp_v0_12;
//                             } else {
//                                 var_v0_2 = (u16) arg0->ext.factory.unk92 + 4;
//                             }
//                             arg0->ext.factory.unk92 = var_v0_2;
//                             var_s1_6 = 0;
//                             if (arg0->ext.factory.unk92 >= 0x80) {
//                                 arg0->ext.factory.unk92 = 0x80;
//                                 arg0->step_s += 1;
//                             }
//                             var_s0_6 = arg0->ext.prim;
//                             do {
//                                 var_s0_6->drawMode = 0x35;
//                                 temp_v0_13 = (u8) arg0->ext.stub[0x16];
//                                 var_s1_6 += 1;
//                                 var_s0_6->b3 = temp_v0_13;
//                                 var_s0_6->g3 = temp_v0_13;
//                                 var_s0_6->r3 = temp_v0_13;
//                                 var_s0_6->b2 = temp_v0_13;
//                                 var_s0_6->g2 = temp_v0_13;
//                                 var_s0_6->r2 = temp_v0_13;
//                                 var_s0_6->b1 = temp_v0_13;
//                                 var_s0_6->g1 = temp_v0_13;
//                                 var_s0_6->r1 = temp_v0_13;
//                                 var_s0_6->b0 = temp_v0_13;
//                                 var_s0_6->g0 = temp_v0_13;
//                                 var_s0_6->r0 = temp_v0_13;
//                                 var_s0_6 = var_s0_6->next;
//                             } while (var_s1_6 < 2);
//                             var_s1_7 = 0;
//                             var_s0_6->drawMode = 0x15;
// loop_48:
//                             temp_v0_14 = (u8) arg0->ext.stub[0x16];
//                             var_s1_7 += 1;
//                             var_s0_6->b3 = temp_v0_14;
//                             var_s0_6->g3 = temp_v0_14;
//                             var_s0_6->r3 = temp_v0_14;
//                             var_s0_6->b2 = temp_v0_14;
//                             var_s0_6->g2 = temp_v0_14;
//                             var_s0_6->r2 = temp_v0_14;
//                             var_s0_6->b1 = temp_v0_14;
//                             var_s0_6->g1 = temp_v0_14;
//                             var_s0_6->r1 = temp_v0_14;
//                             var_s0_6->b0 = temp_v0_14;
//                             var_s0_6->g0 = temp_v0_14;
//                             var_s0_6->r0 = temp_v0_14;
//                             var_s0_6 = var_s0_6->next;
//                             if (var_s1_7 < 2) {
//                                 var_s0_6->drawMode = 0x15;
//                                 goto loop_48;
//                             }
//                             break;
//                         case 4:
//                             arg0->ext.generic.unk88.unk->unk32 = 8;
//                             arg0->ext.generic.unk80.modeS32 = 0x40;
//                             arg0->step = 2;
//                             arg0->step_s = 0;
//                             D_8003BE40 = 1;
//                             break;
//                     }
//                 default:                            // switch 1
// block_84:
//                     FntPrint(&D_8019B3C0, arg0->step);
//                     FntPrint(&D_8019B3D0, arg0->step_s);
//                     return;
//                 }
//             }
// block_83:
//             DestroyEntity(arg0);
//             return;
//         case 2:                                     // switch 1
//             temp_v0_15 = arg0->ext.generic.unk80.modeS32 - 1;
//             arg0->ext.generic.unk80.modeS32 = temp_v0_15;
//             if (temp_v0_15 == 0) {
//                 arg0->step_s = 0;
//                 arg0->step = 3;
//             }
//             goto block_84;
//         case 3:                                     // switch 1
//             temp_v1_4 = arg0->step_s;
//             if (temp_v1_4 != 1) {
//                 if ((s32) temp_v1_4 < 2) {
//                     var_s1_8 = 0;
//                     if (temp_v1_4 != 0) {

//                     } else {
//                         var_s0_7 = arg0->ext.prim->next->next;
//                         do {
//                             var_s0_7->drawMode = 0x15;
//                             temp_v0_16 = arg0->ext.stub[0x16];
//                             var_s1_8 += 1;
//                             var_s0_7->b3 = temp_v0_16;
//                             var_s0_7->g3 = temp_v0_16;
//                             var_s0_7->r3 = temp_v0_16;
//                             var_s0_7->b2 = temp_v0_16;
//                             var_s0_7->g2 = temp_v0_16;
//                             var_s0_7->r2 = temp_v0_16;
//                             var_s0_7->b1 = temp_v0_16;
//                             var_s0_7->g1 = temp_v0_16;
//                             var_s0_7->r1 = temp_v0_16;
//                             var_s0_7->b0 = temp_v0_16;
//                             var_s0_7->g0 = temp_v0_16;
//                             var_s0_7->r0 = temp_v0_16;
//                             var_s0_7 = var_s0_7->next;
//                         } while (var_s1_8 < 2);
//                         temp_v0_17 = (u16) arg0->ext.factory.unk92 - 4;
//                         arg0->ext.factory.unk92 = temp_v0_17;
//                         if (temp_v0_17 & 0x8000) {
//                             arg0->ext.factory.unk92 = 0;
//                             goto block_79;
//                         }
//                     }
//                     goto block_84;
//                 }
//                 if (temp_v1_4 != 2) {
//                     if (temp_v1_4 != temp_a0) {
//                         goto block_84;
//                     }
//                     var_s0_8 = arg0->ext.factory.parent;
//                     if (var_s0_8 != NULL) {
//                         do {
//                             func_801AD0EC((?* ) var_s0_8);
//                             var_s0_8 = var_s0_8->next;
//                         } while (var_s0_8 != NULL);
//                     }
//                     temp_s0_6 = arg0->ext.generic.unk84.unk;
//                     temp_v0_18 = (u16) temp_s0_6->y0 + 2;
//                     temp_s0_6->y0 = temp_v0_18;
//                     temp_s0_6->y1 = temp_v0_18;
//                     temp_s0_6->x0 = (u16) temp_s0_6->x0 - 2;
//                     temp_v0_19 = (u16) temp_s0_6->y2 - 2;
//                     temp_s0_6->y2 = temp_v0_19;
//                     temp_s0_6->y3 = temp_v0_19;
//                     temp_s0_6->x2 = (u16) temp_s0_6->x2 - 2;
//                     temp_s0_6->x1 = (u16) temp_s0_6->x1 + 2;
//                     temp_s0_6->x3 = (u16) temp_s0_6->x3 + 2;
//                     if (temp_s0_6->y2 < temp_s0_6->y0) {
//                         goto block_83;
//                     }
//                     goto block_84;
//                 }
//                 var_s0_9 = arg0->ext.factory.parent;
//                 if (var_s0_9 != NULL) {
//                     do {
//                         func_801AD0EC((?* ) var_s0_9);
//                         var_s0_9 = var_s0_9->next;
//                     } while (var_s0_9 != NULL);
//                 }
//                 temp_v0_20 = arg0->ext.generic.unk80.modeS32 - 1;
//                 arg0->ext.generic.unk80.modeS32 = temp_v0_20;
//                 if (temp_v0_20 == 0) {
//                     goto block_78;
//                 }
//                 goto block_84;
//             }
//             var_s0_10 = arg0->ext.prim;
//             var_s1_9 = 1;
//             do {
//                 var_s0_10->drawMode = 8;
//                 var_s0_10 = var_s0_10->next;
//                 var_s1_9 += 1;
//             } while (var_s1_9 < 4);
//             var_s0_11 = arg0->ext.factory.parent;
//             var_s1_10 = 0;
//             var_a1 = 0 * 4;
//             do {
//                 var_s0_11->r0 = 0x80;
//                 var_s0_11->g0 = 0x80;
//                 var_s0_11->b0 = 0x80;
//                 var_s1_10 += 1;
//                 var_s0_11->unk10 = (s32) var_s0_11->unk4;
//                 var_s0_11->unk1C = (s32) var_s0_11->unk4;
//                 var_s0_11->unk28 = (s32) var_s0_11->unk4;
//                 var_s0_11->p1 = var_a1;
//                 var_s0_11->p2 = Random() & 3;
//                 var_s0_11->p3 = 0;
//                 var_s0_11->drawMode = 0x35;
//                 var_s0_11 = var_s0_11->next;
//                 var_a1 = var_s1_10 * 4;
//             } while (var_s1_10 < 0x14);
//             var_s1_11 = 0;
//             do {
//                 temp_v0_21 = 0x14 - var_s1_11;
//                 var_s1_11 += 1;
//                 var_s0_11->r0 = 0x80;
//                 var_s0_11->g0 = 0x80;
//                 var_s0_11->b0 = 0x80;
//                 var_s0_11->unk10 = (s32) var_s0_11->unk4;
//                 var_s0_11->unk1C = (s32) var_s0_11->unk4;
//                 var_s0_11->unk28 = (s32) var_s0_11->unk4;
//                 var_s0_11->p1 = (u8) -(temp_v0_21 * 4);
//                 var_s0_11->p2 = Random() & 3;
//                 var_s0_11->drawMode = 0x35;
//                 var_s0_11->p3 = 0;
//                 var_s0_11 = var_s0_11->next;
//             } while (var_s1_11 < 0x14);
//             var_s1_12 = 0;
//             var_a1_2 = 0 * 4;
//             do {
//                 var_s0_11->r0 = 0x80;
//                 var_s0_11->g0 = 0x80;
//                 var_s0_11->b0 = 0x80;
//                 var_s1_12 += 1;
//                 var_s0_11->unk10 = (s32) var_s0_11->unk4;
//                 var_s0_11->unk1C = (s32) var_s0_11->unk4;
//                 var_s0_11->unk28 = (s32) var_s0_11->unk4;
//                 var_s0_11->p1 = var_a1_2;
//                 var_s0_11->p2 = Random() & 3;
//                 var_s0_11->p3 = 0;
//                 var_s0_11->drawMode = 0x35;
//                 var_s0_11 = var_s0_11->next;
//                 var_a1_2 = var_s1_12 * 4;
//             } while (var_s1_12 < 0x14);
//             var_s1_13 = 0;
//             do {
//                 temp_v0_22 = 0x14 - var_s1_13;
//                 var_s1_13 += 1;
//                 var_s0_11->r0 = 0x80;
//                 var_s0_11->g0 = 0x80;
//                 var_s0_11->b0 = 0x80;
//                 var_s0_11->unk10 = (s32) var_s0_11->unk4;
//                 var_s0_11->unk1C = (s32) var_s0_11->unk4;
//                 var_s0_11->unk28 = (s32) var_s0_11->unk4;
//                 var_s0_11->p1 = (u8) -(temp_v0_22 * 4);
//                 var_s0_11->p2 = Random() & 3;
//                 var_s0_11->drawMode = 0x35;
//                 var_s0_11->p3 = 0;
//                 var_s0_11 = var_s0_11->next;
//             } while (var_s1_13 < 0x14);
//             arg0->ext.generic.unk80.modeS32 = 0x70;
//             goto block_79;
//     }
// }
// Warning: struct draculaPrimitive is not defined (only forward-declared)
//#endif
//#include "../e_stage_name.h"

//NOTE: The remaining functions are all contained in "../prim_helpers.h" but
//      UnkPrimHelper and PrimDecreaseBrightness don't match.
INCLUDE_ASM("st/chi/nonmatchings/2B7CC", func_801ADF40);    // UnkPrimHelper()
//INCLUDE_ASM("st/chi/nonmatchings/2B7CC", func_801AE328);    // UpdateAnimation()
s32 UpdateAnimation(u8* texAnimations, Primitive* prim) {
    s16 sp0;
    s16 tempUv;
    u8 new_var;
    u8* nextAnimation = texAnimations + ((prim->p1 * 5) & 0xFF);
    u8 new_var2;
    s32 retVal = 0;

    if (prim->p2 == 0) {
        if (*nextAnimation) {
            if (*nextAnimation == 0xFF) {
                return 0;
            }
            retVal = 0x80;
            prim->p2 = nextAnimation[0];
            ++nextAnimation;
            tempUv = nextAnimation[0] + (nextAnimation[1] << 8);
            nextAnimation += 2;
            sp0 = nextAnimation[0] + (nextAnimation[1] << 8);
            LOH(prim->u0) = tempUv;
            LOH(prim->u1) = tempUv + *((u8*)(&sp0));
            new_var = *((u8*)&sp0 + 1);
            LOH(prim->u3) = tempUv + sp0;
            LOH(prim->u2) = tempUv + (new_var << 8);
            ++prim->p1;
        } else {
            prim->p1 = 0;
            prim->p2 = 0;
            prim->p2 = texAnimations[0];
            tempUv = texAnimations[1] + (texAnimations[2] << 8);
            sp0 = texAnimations[3] + (texAnimations[4] << 8);
            LOH(prim->u0) = tempUv;
            LOH(prim->u1) = tempUv + (*(u8*)&sp0);
            new_var2 = *((u8*)&sp0 + 1);
            LOH(prim->u3) = tempUv + sp0;
            LOH(prim->u2) = tempUv + (new_var2 << 8);
            ++prim->p1;
            return 0;
        }
    }

    retVal |= 1;
    --prim->p2;
    return (retVal | 1) & 0xFF;
}
//INCLUDE_ASM("st/chi/nonmatchings/2B7CC", func_801AE478);    // FindFirstUnkPrim()
Primitive* FindFirstUnkPrim(Primitive* poly) {
    while (poly != NULL) {
        if (poly->p3 != 0) {
            poly = poly->next;
        } else {
            return poly;
        }
    }
    return NULL;
}
//INCLUDE_ASM("st/chi/nonmatchings/2B7CC", func_801AE4A8);    // FindFirstUnkPrim2()
Primitive* FindFirstUnkPrim2(Primitive* prim, u8 index) {

    Primitive* ret;
    int i;

    for (; prim; prim = prim->next) {
        if (!prim->p3) {
            ret = prim;
            for (i = 1; i < index; ++i) {
                prim = prim->next;
                if (!prim) {
                    return NULL;
                }
                if (prim->p3) {
                    break;
                }
            }
            if (i == index) {
                return ret;
            }
        }
    }
    return NULL;
}
//INCLUDE_ASM("st/chi/nonmatchings/2B7CC", func_801AE524);    // PrimToggleVisibility()
Primitive* PrimToggleVisibility(Primitive* firstPrim, s32 count) {
    Primitive* prim;
    s8 isVisible;
    s32 i;

    if (firstPrim->p3) {
        firstPrim->p3 = 0;
    } else {
        firstPrim->p3 = 1;
    }

    prim = firstPrim;
    for (i = 0; i < count; i++) {
        if (prim->p3) {
            prim->drawMode &= ~DRAW_HIDE;
            isVisible = false;
        } else {
            prim->drawMode |= DRAW_HIDE;
            isVisible = true;
        }

        prim = prim->next;
        if (prim == NULL)
            return 0;
        prim->p3 = isVisible;
    }

    return prim;
}
//INCLUDE_ASM("st/chi/nonmatchings/2B7CC", func_801AE5AC);    // PrimResetNext()
void PrimResetNext(Primitive* prim) {
    prim->p1 = 0;
    prim->p2 = 0;
    prim->p3 = 0;
    prim->next->x1 = 0;
    prim->next->y1 = 0;
    prim->next->y0 = 0;
    prim->next->x0 = 0;
    prim->next->clut = 0;
    LOHU(prim->next->u0) = 0;
    LOHU(prim->next->b1) = 0;
    LOHU(prim->next->r1) = 0;
    LOHU(prim->next->u1) = 0;
    prim->next->tpage = 0;
    LOHU(prim->next->r2) = 0;
    LOHU(prim->next->b2) = 0;
    prim->next->u2 = 0;
    prim->next->v2 = 0;
    prim->next->r3 = 0;
    prim->next->b3 = 0;
    prim->next->x2 = 0;
    prim->next->y2 = 0;
}
//TODO: Find first "init not started" prim?
//INCLUDE_ASM("st/chi/nonmatchings/2B7CC", func_801AE68C);    // UnkPolyFunc2()
void UnkPolyFunc2(Primitive* prim) {
    PrimResetNext(prim);
    prim->p3 = 8;
    prim->next->p3 = 1;
    prim->next->type = PRIM_LINE_G2;
    prim->next->drawMode = 0xA;
}
//INCLUDE_ASM("st/chi/nonmatchings/2B7CC", func_801AE6E0);    // UnkPolyFunc0()
void UnkPolyFunc0(Primitive* prim) {
    prim->p3 = 0;
    prim->drawMode = DRAW_HIDE;
    prim->next->p3 = 0;
    prim->next->type = PRIM_GT4;
    prim->next->drawMode = DRAW_HIDE;
}
INCLUDE_ASM("st/chi/nonmatchings/2B7CC", func_801AE70C);    // PrimDecreaseBrightness()
//#include "../prim_helpers.h"
