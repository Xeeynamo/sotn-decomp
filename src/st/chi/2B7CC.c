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