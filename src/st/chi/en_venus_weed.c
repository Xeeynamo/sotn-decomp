// SPDX-License-Identifier: AGPL-3.0-or-later
/*
 * File: en_venus_weed.c
 * Overlay: CHI
 * Description: ENTITY - Venus Weed
 */

#include "chi.h"

#define TENDRIL_COUNT 10

typedef enum VenusWeedStep {
    VENUS_WEED_INIT = 0,
    VENUS_WEED_DROP_TO_GROUND = 1,
    VENUS_WEED_THORNWEED_DISGUISE = 2,
    VENUS_WEED_GROW = 3,
    VENUS_WEED_IDLE = 4,
    VENUS_WEED_ATTACK = 5,
    VENUS_WEED_DEATH = 8,
};

typedef enum VenusWeedTendrilStep {
    VENUS_WEED_TENDRIL_INIT = 0,
    VENUS_WEED_TENDRIL_DROP_TO_GROUND = 1,
    VENUS_WEED_TENDRIL_MOVE_TO_RANDOM_POSITION = 2,
    VENUS_WEED_TENDRIL_ATTACK = 3,
    VENUS_WEED_TENDRIL_DEATH = 8,
};

typedef enum VenusWeedTendrilAttack_Substep {
    VENUS_WEED_TENDRIL_ATTACK_INIT = 0,
    VENUS_WEED_TENDRIL_ATTACK_DELAY = 1,
    VENUS_WEED_TENDRIL_ATTACK_CHARGE = 2,
    VENUS_WEED_TENDRIL_ATTACK_LAUNCH = 3,
};

extern signed short* sprites_chi_7[];

// func_801AB548
// https://decomp.me/scratch/yZqKn
// PSP:func_psp_0923A7F0:Match
// PSP:https://decomp.me/scratch/tPXxN
Primitive* SetupPrimsForEntitySpriteParts(Entity* entity, Primitive* prim) {
    s16 y;
    s32 spritePartCount;
    s16 x;
    u8 spriteU0;
    u8 spriteV0;
    s16* spriteData;
    s32 i;
    u8 spriteU1;
    s16 spriteDestX;
    s16 spriteDestY;
    s16 spriteDestW;
    s16 spriteDestH;
    s16 spriteFlags;
    u8 spriteV1;
    s32 xFlip;

    spriteData = sprites_chi_7[entity->animCurFrame];
    spritePartCount = *spriteData;
    spriteData++;

    for (i = 0; i < spritePartCount; i++, spriteData += 11) {
        spriteFlags = spriteData[0];
        spriteDestX = spriteData[1];
        spriteDestY = spriteData[2];
        spriteDestW = spriteData[3];
        spriteDestH = spriteData[4];

        // Adjust sprite position to respect sprite flags
        if (spriteFlags & 4) {
            spriteDestW -= 1;
            if (spriteFlags & 2) {
                spriteDestX += 1;
            }
        }
        if (spriteFlags & 8) {
            spriteDestH -= 1;
            if (spriteFlags & 1) {
                spriteDestY += 1;
            }
        }
        if (spriteFlags & 0x10) {
            spriteDestW -= 1;
            if (!(spriteFlags & 2)) {
                spriteDestX += 1;
            }
        }
        if (spriteFlags & 0x20) {
            spriteDestH -= 1;
            if (!(spriteFlags & 1)) {
                spriteDestY += 1;
            }
        }

        // Calculate sprite position to respect facing
        x = entity->posX.i.hi;
        y = entity->posY.i.hi;
        if (entity->facingLeft) {
            x -= spriteDestX;
        } else {
            x += spriteDestX;
        }
        y += spriteDestY;

        // Set sprite position to respect the above, plus sprite dimensions
        if (entity->facingLeft) {
            LOH(prim->x0) = x - spriteDestW + 1;
            LOH(prim->y0) = y;
            LOH(prim->x1) = x + 1;
            LOH(prim->y1) = y;
            LOH(prim->x2) = x - spriteDestW + 1;
            LOH(prim->y2) = y + spriteDestH;
            LOH(prim->x3) = x + 1;
            LOH(prim->y3) = y + spriteDestH;
        } else {
            LOH(prim->x0) = x;
            LOH(prim->y0) = y;
            LOH(prim->x1) = x + spriteDestW;
            LOH(prim->y1) = y;
            LOH(prim->x2) = x;
            LOH(prim->y2) = y + spriteDestH;
            LOH(prim->x3) = x + spriteDestW;
            LOH(prim->y3) = y + spriteDestH;
        }

        // Entity-relative clut
        prim->clut = entity->palette + spriteData[5];

        spriteU0 = spriteData[7];
        spriteV0 = spriteData[8];
        spriteU1 = spriteData[9];
        spriteV1 = spriteData[10];

        // Adjust sprite UVs to respect sprite flags
        if (spriteFlags & 4) {
            spriteU1--;
        }
        if (spriteFlags & 8) {
            spriteV1--;
        }
        if (spriteFlags & 0x10) {
            spriteU0++;
        }
        if (spriteFlags & 0x20) {
            spriteV0++;
        }

        // Set sprite UVs to respect the above, plus facing
        xFlip = (spriteFlags & 2) ^ entity->facingLeft;
        if (!xFlip) {
            if (!(spriteFlags & 1)) {
                prim->u0 = spriteU0;
                prim->v0 = spriteV0;
                prim->u1 = spriteU1;
                prim->v1 = spriteV0;
                prim->u2 = spriteU0;
                prim->v2 = spriteV1;
                prim->u3 = spriteU1;
                prim->v3 = spriteV1;
            } else {
                prim->u0 = spriteU0;
                prim->v0 = spriteV1 - 1;
                prim->u1 = spriteU1;
                prim->v1 = spriteV1 - 1;
                prim->u2 = spriteU0;
                prim->v2 = spriteV0 - 1;
                prim->u3 = spriteU1;
                prim->v3 = spriteV0 - 1;
            }
        } else {
            if (!(spriteFlags & 1)) {
                prim->u0 = spriteU1 - 1;
                prim->v0 = spriteV0;
                prim->u1 = spriteU0 - 1;
                prim->v1 = spriteV0;
                prim->u2 = spriteU1 - 1;
                prim->v2 = spriteV1;
                prim->u3 = spriteU0 - 1;
                prim->v3 = spriteV1;
            } else {
                prim->u0 = spriteU1 - 1;
                prim->v0 = spriteV1 - 1;
                prim->u1 = spriteU0 - 1;
                prim->v1 = spriteV1 - 1;
                prim->u2 = spriteU1 - 1;
                prim->v2 = spriteV0 - 1;
                prim->u3 = spriteU0 - 1;
                prim->v3 = spriteV0 - 1;
            }
        }

        prim->tpage = 0x14;
        // Entity-relative z priority
        prim->priority = entity->zPriority + 1;

        // Next!
        prim = prim->next;
    }
    return prim;
}

// clang-format off
// D_801817F4
static u8 PhysicsSensors[] = {
    0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x04, 0x00, 0x02, 0x00, 0xFC, 0xFF, 0xFC, 0xFF, 0x00, 0x00
};

// D_80181804
static s16 WalkSensors_Tendril[] = {
    0x0000, 0x0001, 0x0004, 0x0000
};

// Whips her hair around as she comes out of the flower
// D_8018180C
static u8 AnimFrames_Reveal[] = {
    0x01, 0x01, 0x0A, 0x03, 0x06, 0x04, 0x06, 0x05, 0x05, 0x06, 0x05, 0x07, 0x05, 0x08, 0x05, 0x09,
    0x05, 0x0A, 0x08, 0x0C, 0xFF, 0x00, 0x00, 0x00
};

// D_80181824
static u8 AnimFrames_FlowerAttackSpikesCharge[] = {
    0x04, 0x0C, 0x08, 0x0E, 0x04, 0x0F, 0x01, 0x10, 0xFF, 0x00, 0x00, 0x00
};

// D_80181830
static u8 AnimFrames_FlowerAttackSpikesLaunch[] = {
    0x03, 0x10, 0x08, 0x11, 0xFF, 0x00, 0x00, 0x00,
};

// D_80181838
static u8 AnimFrames_FlowerAttackSpikesReset[] = {
    0x12, 0x11, 0x02, 0x12, 0x02, 0x13, 0x04, 0x14, 0x04, 0x15, 0x6F, 0x16, 0x08, 0x13, 0x08, 0x12,
    0x08, 0x11, 0x08, 0x10, 0x20, 0x0F, 0x08, 0x0E, 0x04, 0x0C, 0xFF, 0x00,
};

// D_80181854
static u8 AnimFrames_FlowerPulse[] = {
    0x0A, 0x0B, 0x0A, 0x0C, 0x0A, 0x0D, 0x0A, 0x0C, 0x00, 0x00, 0x00, 0x00
};

// D_80181860
static u8 AnimFrames_FlowerAttackDartsCharge[] = {
    0x10, 0x17, 0x08, 0x18, 0x06, 0x19, 0x05, 0x1A, 0x04, 0x1B, 0x01, 0x1C, 0xFF, 0x00, 0x00, 0x00
};

// D_80181870
static u8 AnimFrames_FlowerAttackDartsLaunch[] = {
    0x14, 0x1C, 0x03, 0x1D, 0x02, 0x1E, 0x02, 0x1F, 0x02, 0x20, 0x02, 0x21, 0x2A, 0x1F, 0x05, 0x0F,
    0x05, 0x0E, 0x10, 0x0C, 0xFF, 0x00, 0x00, 0x00
};

// D_80181888
static u8 AnimFrames_TendrilAttackCharge[] = {
    0x01, 0x26, 0x04, 0x27, 0x04, 0x28, 0x04, 0x29, 0x02, 0x2A, 0x02, 0x2B, 0x02, 0x2C, 0x02, 0x2D,
    0x02, 0x2E, 0x02, 0x2F, 0x02, 0x30, 0x02, 0x31, 0x02, 0x32, 0x02, 0x33, 0x02, 0x34, 0x02, 0x35,
    0x02, 0x36, 0x03, 0x33, 0x03, 0x34, 0x03, 0x35, 0x03, 0x36, 0x04, 0x33, 0x04, 0x34, 0x04, 0x35,
    0x04, 0x36, 0x05, 0x33, 0x05, 0x34, 0x05, 0x35, 0x05, 0x36, 0x04, 0x33, 0x04, 0x34, 0x04, 0x35,
    0xFF, 0x00, 0x00, 0x00
};

// D_801818CC
static u8 AnimFrames_TendrilAttackLaunch[] = {
    0x03, 0x36, 0x03, 0x33, 0x02, 0x34, 0x01, 0x35, 0x04, 0x30, 0x04, 0x2F, 0x04, 0x2E, 0x05, 0x2D,
    0x05, 0x2C, 0x05, 0x2B, 0x05, 0x2A, 0x04, 0x29, 0x04, 0x28, 0x04, 0x27, 0x01, 0x26, 0xFF, 0x00
};

// D_801818EC
static u8 AnimFrames_TendrilBounce[] = {
    0x03, 0x22, 0x03, 0x23, 0x03, 0x24, 0x03, 0x25, 0x00, 0x00, 0x00, 0x00
};

// D_801818F8
static u8 AnimFrames_ThornweedDisguise[] = {
    0x05, 0x2A, 0x05, 0x2B, 0x05, 0x2C, 0x05, 0x2D, 0x00, 0x00, 0x00, 0x00
};

// D_80181904
static u8 AnimFrames_ThornweedQuickWiggle[] = {
    0x02, 0x2A, 0x02, 0x2B, 0x02, 0x2C, 0x02, 0x2D, 0x00, 0x00, 0x00, 0x00, 0x10, 0x0C, 0x0E, 0x0E,
    0x0C, 0x12, 0x0E, 0x13, 0x02, 0x14, 0x04, 0x15, 0x20, 0x16, 0xFF, 0x00
};

// D_80181920
static s8 HitboxData_Tendril[] = {
    0x00, 0x00, 0x00, 0x00, 0x01, 0xF9, 0x0C, 0x07, 0x00, 0xEA, 0x02, 0x17, 0x00, 0xD9, 0x02, 0x27
};

// D_80181930
static u8 HitboxIndices_Tendril[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x03,
    0x03, 0x03, 0x03, 0x03, 0x03, 0x00
};

// D_80181948
static s16 TendrilSpikeStartTimeOffset[] = {
    0x0000, 0x0010, 0x0024, 0x001C, 0x001C, 0x0024, 0x0010, 0x0000,
    0x0000, 0x0000
};
// clang-format on

// E_VENUS_WEED
// func_801AB7CC
// https://decomp.me/scratch/QrYmQ
// PSP:func_psp_0923AE68:Match
// PSP:https://decomp.me/scratch/MjOOd
void EntityVenusWeed(Entity* self) {
    // Sprites
    const int SpriteLeavesX = 0x48;
    const int SpriteLeavesY = 0x00;
    const int SpriteLeavesW = 0x38;
    const int SpriteLeavesH = 0x22;
    const int SpriteStemX = 0x00;
    const int SpriteStemY = 0x30;
    const int SpriteStemW = 0x18;
    const int SpriteStemH = 0x22;
    // Behaviour
    const int ActivateDistanceX = 0x70;
    const int LeavesWidthMax = 0x38;
    const int LeavesHeightMax = 0x22;
    const int StemWidthMax = 0xC;
    const int StemHeightMax = 0x22;
    const int FlowerOffsetY = 0x1B;
    const int WiggleLeavesSpeed = 0x180;
    const int AttackDuration = 0x30;
    const int DeathFinalClut = PAL_DRA(0x210);

    typedef enum Grow_Substep {
        GROW_LEAVES = 0,
        GROW_STEM = 1,
        GROW_FLOWER = 2,
        GROW_TENDRILS = 3,
        GROW_DONE = 4,
    };

    typedef enum Death_Substep {
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
    if ((self->flags & FLAG_DEAD) && (self->step < VENUS_WEED_DEATH)) {
        SetStep(VENUS_WEED_DEATH);
    }

    switch (self->step) {
    case VENUS_WEED_INIT:
        InitializeEntity(&g_EInitVenusWeedRoot);
        self->hitboxOffX = 1;
        self->hitboxOffY = -7;

        // 3 Prims: 2x Leaves (left/right) + Stem
        primIdx = g_api.AllocPrimitives(PRIM_GT4, 3);
        if (primIdx == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIdx;
        prim = &g_PrimBuf[primIdx];
        self->ext.prim = prim;

        // Leaves
        for (i = 0; i < 2; i++) {
            prim->tpage = 0x14;
            prim->clut = PAL_DRA(0x21A);
            prim->u0 = prim->u2 = SpriteLeavesX;
            prim->u1 = prim->u3 = SpriteLeavesX + SpriteLeavesW;
            prim->v0 = prim->v1 = SpriteLeavesY;
            prim->v2 = prim->v3 = SpriteLeavesY + SpriteLeavesH;
            prim->priority = self->zPriority - 1;
            prim->drawMode = DRAW_HIDE;

            prim = prim->next;
        }

        // Stem
        self->ext.venusWeed.stemPrim = prim;
        prim->tpage = 0x14;
        prim->clut = PAL_DRA(0x21A);
        prim->u0 = prim->u2 = SpriteStemX;
        prim->u1 = prim->u3 = SpriteStemX + SpriteStemW;
        prim->v0 = prim->v1 = SpriteStemY;
        prim->v2 = prim->v3 = SpriteStemY + SpriteStemH;
        prim->priority = self->zPriority - 2;
        prim->drawMode = DRAW_HIDE;

        prim = prim->next;
        break;

    case VENUS_WEED_DROP_TO_GROUND:
        if (UnkCollisionFunc3(&PhysicsSensors) & 1) {
            SetStep(VENUS_WEED_THORNWEED_DISGUISE);
        }
        break;

    case VENUS_WEED_THORNWEED_DISGUISE:
        AnimateEntity(&AnimFrames_ThornweedDisguise, self);
        if (GetDistanceToPlayerX() < ActivateDistanceX) {
            self->hitboxState = 0;
            SetStep(VENUS_WEED_GROW);
        }

        // Death check
        if (self->flags & FLAG_DEAD) {
            entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_EXPLOSION, self, entity);
                entity->posY.i.hi -= 4;
                entity->params = 0;
            }

            PlaySfxPositional(SFX_STUTTER_EXPLODE_LOW);
            DestroyEntity(self);
            return;
        }
        break;

    case VENUS_WEED_GROW:
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

            // Update prims to match
            prim = self->ext.prim;
            x = self->posX.i.hi;
            y = self->posY.i.hi;
            y -= self->ext.venusWeed.leavesHeight;
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

            // Update prim to match
            prim = self->ext.venusWeed.stemPrim;
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
            entity = self + 1; // Flower

            // Spawn flower
            CreateEntityFromCurrentEntity(E_VENUS_WEED_FLOWER, entity);
            entity->posX.i.hi = self->posX.i.hi;
            entity->posY.i.hi = self->posY.i.hi - FlowerOffsetY;

            // Face the player
            entity->facingLeft = GetSideToPlayer() & 1;
            entity->zPriority = (s32)self->zPriority;

            self->step_s++;
            break;

        case GROW_TENDRILS:
            entity = self + 2; // Tendrils start
            for (i = 0; i < TENDRIL_COUNT; i++, entity++) {
                CreateEntityFromCurrentEntity(E_VENUS_WEED_TENDRIL, entity);
                entity->params = i;
                entity->zPriority = self->zPriority + 1;
            }

            self->step_s++;
            break;

        case GROW_DONE:
            break;
        }
        break;

    case VENUS_WEED_IDLE: // Set by the flower entity (self + 1)
        AnimateEntity(&AnimFrames_ThornweedDisguise, self);
        break;

    case VENUS_WEED_ATTACK: // Set by the flower entity (self + 1)
        if (self->ext.venusWeed.triggerAttack) {
            self->ext.venusWeed.triggerAttack = false;
            self->ext.venusWeed.timer = AttackDuration;
        }
        if (self->ext.venusWeed.timer) {
            AnimateEntity(&AnimFrames_ThornweedQuickWiggle, self);
            self->ext.venusWeed.timer--;
        }
        break;

    case VENUS_WEED_DEATH:
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
                    prim->x1 =
                        x + (self->ext.venusWeed.leavesWidth + LeavesWidthMax) /
                                2 * i;
                    prim->x3 = x + (self->ext.venusWeed.leavesWidth * i);
                    prim->y0++;
                    prim->y1++;
                    if (prim->y1 > prim->y2) {
                        prim->drawMode = DRAW_HIDE;
                        checkCount += 1;
                    }
                    prim = prim->next;
                }
            }

            // Collapse stem
            prim = self->ext.venusWeed.stemPrim;
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

            PlaySfxPositional(SFX_EXPLODE_B);

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

        // Update stem and flower
        x /= 2;
        entity = self + 1; // Flower
        prim = self->ext.venusWeed.stemPrim;
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

// E_VENUS_WEED_FLOWER
// func_801AC074
// https://decomp.me/scratch/0O3ex
// PSP:func_psp_0923BB48:Match
// PSP:https://decomp.me/scratch/yUOcn
void EntityVenusWeedFlower(Entity* self) {
    const int HitboxOffsetX = 6;
    const int HitboxOffsetY = -16;
    const int HitboxWidth = 14;
    const int HitboxHeight = 14;
    const int AnimFrameInit = 1;
    const int GrowSpeed = 6;
    const int GrowLimit = 0x100;
    const int DartsSfxAnimFrameIdx = 3;
    const int DartsLaunchPosOffsetX = 0x18;
    const int DartsLaunchPosOffsetY = 0x18;
    const int DartsAngleLeft = 0x800;
    const int DartsAngleMaxUp = 0x380;
    const int DartsAngleMaxDown = 0x300;
    const int DartsAngleDelta = 0x60;
    const int DartsCount = 5;

    typedef enum Step {
        INIT = 0,
        GROW = 1,
        REVEAL = 2,
        IDLE = 3,
        SPIKES = 4,
        DARTS = 5,
        DEATH = 8,
    };

    typedef enum Spikes_Substep {
        SPIKES_INIT = 0,
        SPIKES_CHARGE = 1,
        SPIKES_SPAWN = 2,
        SPIKES_LAUNCH = 3,
        SPIKES_ANIM_RESET = 4,
        SPIKES_RESET_TO_IDLE = 5,
    };

    typedef enum Darts_Substep {
        DARTS_INIT = 0,
        DARTS_DELAY = 1,
        DARTS_CHARGE = 2,
        DARTS_LAUNCH = 3,
        DARTS_RESET_TO_IDLE = 4,
    };

    Entity* entity;
    s32 x;
    s16 rot;
    s32 i;
    s32 rotDelta;
    s32 spikeStartTimeOffsetIndex;
    s32 y;

    // Hurt check
    if (self->hitFlags & 3) {
        PlaySfxPositional(NA_SE_EN_VENUS_WEED_HURT);

        // Tell root to wiggle for a bit
        entity = self - 1; // Root
        entity->ext.venusWeed.wiggleT = 0x40;
    }
    // Death check
    if ((self->flags & FLAG_DEAD) && (self->step < DEATH)) {
        PlaySfxPositional(NA_SE_EN_VENUS_WEED_DEATH);
        SetStep(DEATH);
    }

    switch (self->step) {
    case INIT:
        InitializeEntity(&g_EInitVenusWeedFlower);
        self->hitboxOffX = HitboxOffsetX;
        self->hitboxOffY = HitboxOffsetY;
        self->hitboxWidth = HitboxWidth;
        self->hitboxHeight = HitboxHeight;
        self->animCurFrame = AnimFrameInit;
        self->drawFlags |= FLAG_DRAW_ROTX | FLAG_DRAW_ROTY;
        self->rotX = self->rotY = 0;
        self->hitboxState = 0;
        break;

    case GROW:
        self->rotX = self->rotY += GrowSpeed;
        if (self->rotX >= GrowLimit) {
            self->drawFlags = FLAG_DRAW_DEFAULT;
            self->hitboxState = 3;

            PlaySfxPositional(SFX_MAGIC_WEAPON_APPEAR_A);
            SetStep(REVEAL);
        }
        break;

    case REVEAL:
        if (AnimateEntity(AnimFrames_Reveal, self) == 0) {
            // Tell root to idle
            entity = self - 1; // Root
            entity->step = VENUS_WEED_IDLE;
            entity->step_s = 0;

            SetStep(IDLE);
        }
        break;

    case IDLE:
        // Init
        if (!self->step_s) {
            self->ext.venusWeedFlower.triggerAttack = 1;
            self->step_s++;
        }

        // Animate, occasionally turning to face player
        if (AnimateEntity(AnimFrames_FlowerPulse, self) == 0) {
            self->facingLeft = GetSideToPlayer() & 1;
        }

        // Only once, when entering IDLE state
        if (!--self->ext.venusWeedFlower.triggerAttack) {
            // Face player
            self->facingLeft = GetSideToPlayer() & 1;

            if (self->ext.venusWeedFlower.nextAttackIsDarts) {
                SetStep(DARTS);
            } else {
                SetStep(SPIKES);
            }
            self->ext.venusWeedFlower.nextAttackIsDarts ^=
                1; // Toggle between darts and tendril spikes attacks
            return;
        }
        break;

    case SPIKES:
        switch (self->step_s) {
        case SPIKES_INIT:
            // Set root entity to attack
            entity = self - 1; // Root
            entity->step = VENUS_WEED_ATTACK;
            entity->step_s = 0;

            // Set tendrils to attack
            entity = self + 1; // Tendrils start
            for (i = 0; i < TENDRIL_COUNT; i++, entity++) {
                entity->step = VENUS_WEED_TENDRIL_ATTACK;
                entity->step_s = VENUS_WEED_TENDRIL_ATTACK_INIT;
            }

            self->step_s++;
            // fallthrough
        case SPIKES_CHARGE:
            if (AnimateEntity(AnimFrames_FlowerAttackSpikesCharge, self) == 0) {
                SetSubStep(SPIKES_SPAWN);
            }
            break;

        case SPIKES_SPAWN:
            PlaySfxPositional(SFX_GLASS_SHARDS);

            // Spawn spikes
            entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_VENUS_WEED_SPIKE, self, entity);
                entity->facingLeft = self->facingLeft;
                entity->ext.venusWeedSpike.flower = self;
            }
            self->step_s++;
            // fallthrough
        case SPIKES_LAUNCH:
            if (AnimateEntity(AnimFrames_FlowerAttackSpikesLaunch, self) == 0) {
                entity = self + 1; // Tendrils start
                if (g_Timer & 1) {
                    spikeStartTimeOffsetIndex = 0;
                } else {
                    spikeStartTimeOffsetIndex = 4;
                }
                for (i = 0; i < TENDRIL_COUNT; i++, entity++) {
                    entity->ext.venusWeedTendril.spikeStartTimeOffsetIndex =
                        spikeStartTimeOffsetIndex + 1;
                    spikeStartTimeOffsetIndex++;
                    spikeStartTimeOffsetIndex &= 0x7;
                }
                SetSubStep(SPIKES_ANIM_RESET);
            }
            break;

        case SPIKES_ANIM_RESET: // Anim: Reset to idle
            if (AnimateEntity(AnimFrames_FlowerAttackSpikesReset, self) == 0) {
                SetSubStep(SPIKES_RESET_TO_IDLE);
            }
            break;

        case SPIKES_RESET_TO_IDLE:
            // Tell root to idle
            entity = self - 1; // Root
            entity->step = VENUS_WEED_IDLE;

            SetStep(IDLE);
            break;
        }

        // Cycle clut
        if (self->ext.venusWeedFlower.clutOffset) {
            entity = self - 1; // Root
            entity->ext.venusWeed.triggerAttack = true;
            if (!(self->palette & 0x8000)) {
                self->palette += self->ext.venusWeedFlower.clutOffset;
                if (self->palette > PAL_DRA(0x219)) {
                    self->palette = PAL_DRA(0x219);
                }
                self->ext.venusWeedFlower.clutOffset = 0;
                return;
            }
        }
        break;

    case DARTS:
        switch (self->step_s) {
        case DARTS_INIT:
            entity = self - 1; // Root
            entity->step = 6;  // Non-existent state: "Do nothing"
            entity->step_s = 0;

            self->step_s += 1;
            // fallthrough
        case DARTS_DELAY:
            if (AnimateEntity(AnimFrames_FlowerAttackDartsCharge, self) == 0) {
                SetSubStep(DARTS_CHARGE);
                return;
            }
            break;

        case DARTS_CHARGE:
            PlaySfxPositional(SFX_GLASS_SHARDS);
            entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_VENUS_WEED_SPIKE, self, entity);
                entity->facingLeft = self->facingLeft;
                entity->ext.venusWeedSpike.flower = self;
            }
            self->step_s++;
            // fallthrough
        case DARTS_LAUNCH:
            if (AnimateEntity(AnimFrames_FlowerAttackDartsLaunch, self) == 0) {
                self->step_s++;
            }
            if (!self->animFrameDuration &&
                self->animFrameIdx == DartsSfxAnimFrameIdx) {
                PlaySfxPositional(SFX_ARROW_SHOT_B);

                // Calculate launch start pos
                if (self->facingLeft) {
                    x = self->posX.i.hi - DartsLaunchPosOffsetX;
                } else {
                    x = self->posX.i.hi + DartsLaunchPosOffsetX;
                }
                y = self->posY.i.hi - DartsLaunchPosOffsetY;

                // Calculate launch angle and delta between darts
                entity = &PLAYER;
                rot = ratan2(entity->posY.i.hi - y, entity->posX.i.hi - x);
                if (self->facingLeft) {
                    if (rot < 0) { // Angled up
                        if (rot > -DartsAngleLeft + DartsAngleMaxUp) {
                            rot = -DartsAngleLeft + DartsAngleMaxUp;
                        }
                        rotDelta = -DartsAngleDelta; // More up
                    } else {                         // Angled down
                        if (rot < DartsAngleLeft - DartsAngleMaxDown) {
                            rot = DartsAngleLeft - DartsAngleMaxDown;
                        }
                        rotDelta = DartsAngleDelta; // More down
                    }
                } else if (rot < 0) { // Angled up
                    if (rot < -DartsAngleMaxUp) {
                        rot = -DartsAngleMaxUp;
                    }
                    rotDelta = DartsAngleDelta; // More up
                } else {                        // Angled down
                    if (rot > DartsAngleMaxDown) {
                        rot = DartsAngleMaxDown;
                    }
                    rotDelta = -DartsAngleDelta; // More down
                }

                // Spawn darts
                for (i = 0; i < DartsCount; i++) {
                    entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
                    if (entity != NULL) {
                        CreateEntityFromEntity(E_VENUS_WEED_DART, self, entity);
                        entity->rotZ = rot;
                        entity->params = i;
                        entity->posX.i.hi = x;
                        entity->posY.i.hi -= DartsLaunchPosOffsetY;
                    }
                    rot += rotDelta;
                }
                return;
            }
            break;

        case DARTS_RESET_TO_IDLE:
            entity = self - 1; // Root
            entity->step = VENUS_WEED_IDLE;

            SetStep(IDLE);
            return;
        }
        break;

    case DEATH:
        // Kill tendrils
        entity = self + 1; // Tendrils start
        for (i = 0; i < TENDRIL_COUNT; i++, entity++) {
            entity->flags |= FLAG_DEAD;
        }

        PlaySfxPositional(SFX_FM_EXPLODE_B);
        self->hitboxState = 0;

        entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (entity != NULL) {
            CreateEntityFromEntity(E_EXPLOSION, self, entity);
            entity->params = 3;
        }

        // Kill root
        entity = self - 1; // Root
        entity->flags |= FLAG_DEAD;

        DestroyEntity(self);
        break;
    }
}

// E_VENUS_WEED_TENDRIL
// params: Index in group
//         Used to slightly influence position
// func_801AC730
// https://decomp.me/scratch/dVIWY
// PSP:func_psp_0923C4E8:No match
// PSP:https://decomp.me/scratch/tbskC
void EntityVenusWeedTendril(Entity* self) {
    const int InitDistMinX = 0x18;
    const int InitDistRandRangeX = 0xF; // Must be a "full flags" value
    const int SpikeSfxAnimFrameIdx = 0xA;

    s32 x;
    s8* hitboxData;
    Entity* entity;
    u32 hitboxIndex;

    if ((self->flags & FLAG_DEAD) && (self->step < VENUS_WEED_TENDRIL_DEATH)) {
        SetStep(VENUS_WEED_TENDRIL_DEATH);
    }

    switch (self->step) {
    case VENUS_WEED_TENDRIL_INIT:
        InitializeEntity(&g_EInitVenusWeedTendril);
        self->animCurFrame = 0;
        break;

    case VENUS_WEED_TENDRIL_DROP_TO_GROUND:
        if (UnkCollisionFunc3(PhysicsSensors) & 1) {
            SetStep(VENUS_WEED_TENDRIL_MOVE_TO_RANDOM_POSITION);
        }
        break;

    case VENUS_WEED_TENDRIL_MOVE_TO_RANDOM_POSITION:
        // Calculate target x positions
        if (!self->step_s) {
            x = self->params * 2 - (TENDRIL_COUNT - 1);
            x = x * x;
            if (self->params < (TENDRIL_COUNT / 2)) {
                x = -x;
            }
            if (x > 0) {
                x += InitDistMinX;
            } else {
                x -= InitDistMinX;
            }
            x += (Random() & (InitDistRandRangeX * 2 + 1)) - InitDistRandRangeX;
            self->ext.venusWeedTendril.targetX = x;
            self->step_s++;
        }

        AnimateEntity(AnimFrames_TendrilBounce, self);
        UnkCollisionFunc2(WalkSensors_Tendril); // "Walk", respecting walls/etc

        // Set velocity according to remaining distance
        entity = self - 1 - self->params; // Flower
        x = entity->posX.i.hi + self->ext.venusWeedTendril.targetX;
        x -= self->posX.i.hi; // Remaining distance
        if (abs(x) < 2) {
            self->step_s--;
        } else if (x > 0) {
            self->velocityX = (abs(x) << 0xC) / 4; // * 1024
        } else {
            self->velocityX = (-(abs(x) << 0xC)) / 4; // * 1024
        }
        break;

    case VENUS_WEED_TENDRIL_ATTACK:
        switch (self->step_s) {
        case VENUS_WEED_TENDRIL_ATTACK_INIT:
            AnimateEntity(AnimFrames_TendrilBounce, self);
            if (self->ext.venusWeedTendril.spikeStartTimeOffsetIndex) {
                self->ext.venusWeedTendril.timer = TendrilSpikeStartTimeOffset
                    [self->ext.venusWeedTendril.spikeStartTimeOffsetIndex - 1];
                self->ext.venusWeedTendril.spikeStartTimeOffsetIndex = 0;
                SetSubStep(VENUS_WEED_TENDRIL_ATTACK_DELAY);
            }
            break;

        case VENUS_WEED_TENDRIL_ATTACK_DELAY:
            if (self->ext.venusWeedTendril.timer) {
                self->ext.venusWeedTendril.timer--;
                break;
            }
            self->step_s++;
            // Fallthrough
        case VENUS_WEED_TENDRIL_ATTACK_CHARGE:
            if (AnimateEntity(AnimFrames_TendrilAttackCharge, self) == 0) {
                SetSubStep(VENUS_WEED_TENDRIL_ATTACK_LAUNCH);
            }
            if (!self->animFrameDuration &&
                self->animFrameIdx == SpikeSfxAnimFrameIdx) {
                PlaySfxPositional(NA_SE_EN_VENUS_WEED_ATTACK_TENDRIL_SPIKE);
            }
            break;

        case VENUS_WEED_TENDRIL_ATTACK_LAUNCH:
            if (AnimateEntity(AnimFrames_TendrilAttackLaunch, self) == 0) {
                SetStep(VENUS_WEED_TENDRIL_MOVE_TO_RANDOM_POSITION);
            }
            break;
        }
        if (self->hitFlags & 0x80) {
            entity = self - 1 - self->params; // Flower
            entity->ext.venusWeedFlower.clutOffset++;
        }
        break;

    case VENUS_WEED_TENDRIL_DEATH:
        if (!self->step_s) {
            self->ext.venusWeedTendril.timer = self->params * 8 + 8;
            self->step_s++;
        }
        if (!--self->ext.venusWeedTendril.timer) {
            entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_EXPLOSION, self, entity);
                entity->params = 2;
                entity->posY.i.hi -= 0xC;
            }
            PlaySfxPositional(SFX_EXPLODE_B);
            DestroyEntity(self);
            return;
        }
        break;
    }

    // Update the hitbox based on the current animation frame
    hitboxData = HitboxData_Tendril;
    hitboxIndex = HitboxIndices_Tendril[self->animCurFrame - 0x22];
    hitboxData += hitboxIndex * 4; // 4 entries per index
    self->hitboxOffX = *hitboxData++;
    self->hitboxOffY = *hitboxData++;
    self->hitboxWidth = *hitboxData++;
    self->hitboxHeight = *hitboxData++;
}

// E_VENUS_WEED_DART
// params: Index in group
//         Slightly influences acceleration
// func_801ACB6C
// https://decomp.me/scratch/AyVyt
// PSP:func_psp_0923CAC8:Match
// PSP:https://decomp.me/scratch/qBeC0
void EntityVenusWeedDart(Entity* self) {
    const int AnimFrameIndexInit = 0x37;
    const int StartSpeed = 0x8000;
    const int SpeedMax = 0x60000;
    const int AccelInc = 0x800;
    const int AccelMax = 0x10000;
    const int ClutIdxWallHit = 0x20;
    const int ClutIdxPlayerHit = 0x00;
    const int ClutIdxMax = 0x30;

    typedef enum Step {
        INIT = 0,
        FLY = 1,
        DECAY = 2,
        DEATH = 3,
    };

    Collider collider;
    Entity* entity;
    s16 rot;
    s32 x;
    s32 speed;
    s32 y;

    switch (self->step) {
    case INIT:
        InitializeEntity(&g_EInitVenusWeedDart);
        self->animCurFrame = AnimFrameIndexInit;
        self->drawFlags = FLAG_DRAW_ROTZ;
        rot = self->rotZ;
        self->hitboxOffX = (rcos(rot) * 6) >> 0xC;
        self->hitboxOffY = (rsin(rot) * 6) >> 0xC;
        self->ext.venusWeedDart.nextPosDeltaX = rcos(rot) << 3 >> 0xC;
        self->ext.venusWeedDart.nextPosDeltaY = rsin(rot) << 3 >> 0xC;
        self->ext.venusWeedDart.speed = StartSpeed;
        // fallthrough
    case FLY:
        MoveEntity();

        rot = self->rotZ;
        speed = self->ext.venusWeedDart.speed;
        self->velocityX = (speed * rcos(rot)) >> 0xC;
        self->velocityY = (speed * rsin(rot)) >> 0xC;
        self->ext.venusWeedDart.speed += self->ext.venusWeedDart.accel;
        self->ext.venusWeedDart.accel += (self->params + 1) * AccelInc;
        if (self->ext.venusWeedDart.accel > AccelMax) {
            self->ext.venusWeedDart.accel = AccelMax;
        }
        if (self->ext.venusWeedDart.speed > SpeedMax) {
            self->ext.venusWeedDart.speed = SpeedMax;
        }

        x = self->posX.i.hi + self->ext.venusWeedDart.nextPosDeltaX;
        y = self->posY.i.hi + self->ext.venusWeedDart.nextPosDeltaY;
        g_api_CheckCollision(x, y, &collider, 0);
        if (collider.effects & 1) {
            PlaySfxPositional(SFX_STOMP_HARD_E);
            // Correct position to be against the edge
            if (self->velocityY > 0) {
                self->posY.i.hi += collider.unk18;
            }
            if (self->velocityY < 0) {
                self->posY.i.hi += collider.unk20;
            }
            self->hitboxState = 0;
            self->ext.venusWeedDart.clutIndex = ClutIdxWallHit;
            SetStep(DEATH);
        }
        if (self->hitFlags & 0x80) {
            entity = &PLAYER;
            self->ext.venusWeedDart.nextPosDeltaX =
                entity->posX.i.hi - self->posX.i.hi;
            self->ext.venusWeedDart.nextPosDeltaY =
                entity->posY.i.hi - self->posY.i.hi;
            self->ext.venusWeedDart.clutIndex = ClutIdxPlayerHit;
            self->hitboxState = 0;
            SetStep(DECAY);
            break;
        }
        if (self->hitParams) {
            self->flags & FLAG_DEAD; // Weird?
        }
        break;

    case DECAY:
        if (!(self->palette & 0x8000)) {
            self->ext.venusWeedDart.clutIndex++;
            self->palette = self->ext.venusWeedDart.clutIndex + PAL_DRA(0x20A);

            if (self->palette > PAL_DRA(0x219)) {
                self->palette = PAL_DRA(0x219);
            }
        }
        if (self->ext.venusWeedDart.clutIndex > ClutIdxMax) {
            self->flags |= FLAG_DEAD;
        }

        // Stick to player
        entity = &PLAYER;
        self->posX.i.hi =
            entity->posX.i.hi - self->ext.venusWeedDart.nextPosDeltaX;
        self->posY.i.hi =
            entity->posY.i.hi - self->ext.venusWeedDart.nextPosDeltaY;
        break;

    case DEATH:
        if (!--self->ext.venusWeedDart.clutIndex) {
            self->flags |= FLAG_DEAD;
        }
        break;
    }

    // Death check
    if (self->flags & FLAG_DEAD) {
        entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (entity != NULL) {
            CreateEntityFromEntity(E_EXPLOSION, self, entity);
            entity->params = 0;
        }
        DestroyEntity(self);
    }
}

// E_VENUS_WEED_SPIKE
// params: Index in group
// func_801ACEF4
// https://decomp.me/scratch/uQtVP
// PSP:func_psp_0923D008:No match
// PSP:https://decomp.me/scratch/zjZnY
void EntityVenusWeedSpike(Entity* self) {
    const int SpikeParts = 5;

    typedef enum Step {
        INIT = 0,
        EXTEND = 1,
    };

    Primitive* prim;
    Primitive* primItr;
    Primitive* primNext;
    s32 primIdx;
    Entity* entity;
    s16 clut;

    switch (self->step) {
    case INIT:
        InitializeEntity(&g_EInitVenusWeedFlower);

        self->flags |= FLAG_UNK_2000 | FLAG_UNK_00200000;
        self->hitboxState = 0;
        self->palette = PAL_OVL(0x224);

        primIdx = g_api.AllocPrimitives(PRIM_GT4, SpikeParts);
        if (primIdx == -1) {
            DestroyEntity(self);
            break;
        } else {
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIdx;
            prim = &g_PrimBuf[primIdx];
            self->ext.venusWeedSpike.firstPart = prim;

            entity = self->ext.venusWeedSpike.flower;
            entity--; // Root
            prim = self->ext.venusWeedSpike.firstPart;

            // Draw sprite parts
            prim = SetupPrimsForEntitySpriteParts(entity, prim);
            // Above returns the following prim

            // Copy prims to a later index (while maintaining linked list order)
            for (primItr = entity->ext.venusWeedSpike.firstPart;
                 primItr != NULL; primItr = primItr->next, prim = primNext) {
                primNext = prim->next;

                *prim = *primItr;
                prim->next = primNext;
                prim->priority = primItr->priority + 1;
            }
        }

        // Update to match flower
        entity = entity + 1; // Flower
        self->animCurFrame = entity->animCurFrame;
        self->zPriority = entity->zPriority + 1;
        // Fallthrough
    case EXTEND:
        clut = self->palette & 0xFFF;

        prim = self->ext.venusWeedSpike.firstPart;
        while (prim != NULL) {
            prim->clut = clut;
            prim->drawMode = DRAW_UNK02;

            prim = prim->next;
        }

        // Update to match flower
        entity = self->ext.venusWeedSpike.flower;
        self->animCurFrame = entity->animCurFrame;
        self->palette++;
        clut = self->palette & 0xFFF;
        if (clut > PAL_DRA(0x232)) {
            DestroyEntity(self);
        } else {
            if (entity->entityId != E_VENUS_WEED_FLOWER) {
                DestroyEntity(self);
            }
        }
        break;
    }
}
