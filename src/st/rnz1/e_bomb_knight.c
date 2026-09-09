// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rnz1.h"

/*

***************************

BIG NOTE:

The Rock Knight and Bomb Knight are exactly the same enemy.
Not a reskin, not a copy paste, but the same dude.
Create the entity with params of 0 or 1 to control it.
Every Rock Knight contains everything for a Bomb Knight,
and every Bomb Knight contains everything for a Rock Knight.
This file contains both the Rock and Bomb entities, always.

***************************


*/

static s16 sensors1[] = {0, 37, 0, 4, 8, -4, -16, 0};
static s16 sensors2[] = {0, 37, 8, 0};
static s16 unused_sensors[] = {0, 8, 0, 4, 4, -4, -8, 0};
static AnimateEntityFrame anim_idle_holding_bomb[] = {
    {14, 1}, {14, 2}, {11, 3}, {10, 2}, POSE_LOOP(0)};
// Throw bomb and grab a new one from hammerspace
static AnimateEntityFrame anim_throw_bomb[] = {
    {16, 1}, {8, 2},  {30, 1}, {4, 4},  {3, 5},   {2, 6},  {2, 7},
    {2, 8},  {1, 9},  {1, 8},  {3, 10}, {33, 8},  {6, 7},  {5, 6},
    {5, 17}, {4, 18}, {4, 19}, {3, 20}, {14, 21}, {6, 24}, {6, 22},
    {6, 23}, {4, 1},  {6, 2},  {8, 1},  POSE_END};
static AnimateEntityFrame anim_turnaround_bomb[] = {
    {8, 1}, {5, 11}, {9, 12}, {8, 13}, POSE_END};
// Take non-bomb hand and slide across body
static AnimateEntityFrame anim_flinch_bomb[] = {
    {8, 14}, {8, 15}, {19, 16}, {5, 15}, POSE_END};
static AnimateEntityFrame anim_fastthrow_bomb[] = {
    {5, 1},  {3, 4},  {2, 5},  {2, 6},  {1, 7},  {7, 6},
    {6, 17}, {5, 18}, {4, 19}, {2, 20}, {3, 21}, {8, 24},
    {7, 22}, {7, 23}, {3, 1},  {6, 2},  {8, 1},  POSE_END};
static AnimateEntityFrame anim_bomb_fuse_sparks[] = {
    {4, 37}, {4, 38}, {4, 39}, {4, 40}, POSE_LOOP(0)};

static AnimateEntityFrame anim_idle_holding_rock[] = {
    {14, 41}, {14, 42}, {11, 43}, {10, 42}, POSE_LOOP(0)};
static AnimateEntityFrame anim_throw_rock[] = {
    {14, 41}, {8, 42}, {26, 41}, {3, 44}, {2, 45},  {2, 46},  {2, 47},
    {2, 48},  {1, 49}, {1, 48},  {3, 50}, {33, 48}, {6, 47},  {5, 46},
    {5, 57},  {4, 58}, {4, 59},  {3, 60}, {6, 61},  {10, 64}, {8, 62},
    {6, 63},  {3, 41}, {6, 42},  {4, 41}, POSE_END};
static AnimateEntityFrame anim_turnaround_rock[] = {
    {8, 41}, {5, 51}, {9, 52}, {8, 53}, POSE_END};
static AnimateEntityFrame anim_flinch_rock[] = {
    {8, 54}, {8, 55}, {19, 56}, {5, 55}, POSE_END};
static AnimateEntityFrame anim_fastthrow_rock[] = {
    {5, 41}, {3, 44}, {2, 45}, {2, 46}, {1, 47}, {7, 46},
    {6, 57}, {5, 58}, {4, 59}, {4, 60}, {3, 61}, {10, 64},
    {8, 62}, {6, 63}, {3, 41}, {6, 42}, {4, 41}, POSE_END};
static AnimateEntityFrame anim_rock_shatter[] = {
    {1, 69}, {1, 70}, {1, 71}, POSE_END};
typedef enum {
    ANIM_IDLE,
    ANIM_TURNAROUND,
    ANIM_FAST_THROW,
    ANIM_THROW,
    ANIM_GUARD
} animIdx;
static AnimateEntityFrame* animations[] = {
    anim_idle_holding_bomb, anim_turnaround_bomb, anim_fastthrow_bomb,
    anim_throw_bomb,        anim_flinch_bomb,     anim_idle_holding_rock,
    anim_turnaround_rock,   anim_fastthrow_rock,  anim_throw_rock,
    anim_flinch_rock};
static s8 hitboxes[] = {
    0,  0,  0,  0,  1,  6,   15, 29, 1,  5,   15, 29, 1,  4,  15, 29, 0,  7, 15,
    29, -5, 10, 13, 26, -10, 10, 14, 26, -11, 10, 14, 26, 0,  5,  12, 31, 0, 6,
    14, 30, -1, 6,  14, 30,  -5, 9,  12, 26,  -1, 7,  14, 28, 1,  5,  14, 30};
static u8 hitboxOffsets[] = {0, 1, 2, 3,  4,  5,  5,  5,  6,  7,  6,  8, 8,
                             8, 9, 9, 10, 11, 11, 12, 13, 13, 13, 13, 13};
static s8 armHitboxes[] = {
    0,   0,   0, 0,  17,  -26, 4, 11, 16,  -27, 4, 11, 15,  -28, 4, 11,
    13,  -31, 4, 12, -3,  -20, 8, 7,  -79, -91, 0, 0,  9,   24,  4, 11,
    8,   24,  4, 11, 15,  -29, 4, 11, 18,  -28, 4, 11, 17,  -27, 4, 11,
    13,  -32, 4, 12, -84, -89, 0, 0,  -87, -89, 0, 0,  -92, -94, 0, 0,
    -90, -87, 0, 0,  -85, -87, 0, 0,  -88, -88, 0, 0,  -87, -88, 0, 0,
    -83, -88, 0, 0,  -83, -90, 0, 0,  -87, -90, 0, 0,  -91, -90, 0, 0,
    16,  -31, 7, 15, 15,  -32, 7, 15, 14,  -33, 7, 15, 10,  -36, 7, 15,
    8,   22,  4, 9,  -14, -26, 7, 15, -14, -36, 7, 15, -16, -31, 7, 15,
    14,  -34, 7, 15, 16,  -33, 7, 15, 18,  -4,  6, 9,  12,  -39, 7, 15};
static u8 bombArmHitboxOffsets[] = {0, 1, 2,  3,  4, 5, 6, 6, 7, 8, 7,  6, 6,
                                    6, 9, 10, 11, 6, 6, 6, 6, 6, 6, 12, 6};
static u8 rockArmHitboxOffsets[] = {24, 25, 26, 27, 5, 6, 6, 7, 28, 7,  29, 30,
                                    31, 32, 33, 25, 6, 6, 6, 6, 6,  34, 35, 6};

static AnimateEntityFrame anim_another_bomb_throw[] = {
    {4, 1}, {4, 2}, {4, 3}, {4, 4}, {4, 5}, {4, 6}, {2, 7}, {2, 8}, POSE_END};

static s32 throwTimers[] = {32, 0, 0, 128, 64, 0, 0, 0};
static Point16 explosionOffsets[] = {{12, 8}, {-12, 8}, {0, -2}};
typedef struct {
    s16 x;
    s16 y;
    u32 velX;
    u32 velY;
    s16 rotSpeed;
    s16 lifetime;
} deathParts;
static deathParts deathPartsData[] = {
    {0, -4, FIX(1.0 / 8), FIX(-0.5), 32, 34},
    {0, -24, 0, FIX(-1.75), 128, 32},
    {0, 0, 0, FIX(-0.25), 0, 28},
    {-8, -20, FIX(-0.5), FIX(-1.25), 96, 28},
    {8, -22, FIX(0.5), FIX(-(1 + 7.0 / 16)), -96, 30},
    {-4, 8, FIX(-0.25), FIX(-0.5), -64, 20},
    {4, 8, FIX(0.25), FIX(-3.0 / 8), 48, 22},
    {-16, -12, FIX(-5.0 / 8), FIX(-1), 96, 24},
    {16, -4, FIX(5.0 / 8), FIX(-(1 + 1.0 / 8)), -96, 26},
    {-12, 28, FIX(-1.0 / 8), FIX(-7.0 / 8), -32, 16},
    {12, 28, FIX(1.0 / 8), FIX(-3.0 / 4), 16, 18},
};
static s8 fuseSparksXY[] = {
    0,   0,   19,  -41, 18,  -43, 19, -45, 15, -49, -79, -91,
    -13, -37, -17, -49, -20, -43, 17, -46, 20, -45, 16,  -50};
static u8 fuseFrameMap[] = {
    0, 1, 2, 3, 4, 0, 0, 0, 0, 0, 0, 6, 7, 8, 9, 10, 10, 0, 0, 0, 0, 0, 0, 11, 0
};

extern EInit g_EInitBombKnight;
extern EInit g_EInitRockKnight;
extern EInit g_EInitBomb;
extern EInit g_EInitKnightDebris;
extern EInit g_EInitRock;

typedef enum {
    KNIGHT_INIT,
    KNIGHT_COLLCHECK,
    KNIGHT_WAIT,
    KNIGHT_IDLE,
    KNIGHT_TURNAROUND,
    KNIGHT_CLOSETHROW,
    KNIGHT_FARTHROW,
    KNIGHT_HIT,
    KNIGHT_DEAD
} BombKnightSteps;

void EntityBombKnight(Entity* self) {
    deathParts* deathOffset;
    Entity* other;
    s32 rock_knight_mode;
    s32 i;
    s32 offsetX;
    s8* hitbox;
    AnimateEntityFrame** animBlock;

    if ((self->flags & FLAG_DEAD) && (self->step < 8)) {
        PlaySfxPositional(SFX_ROCK_KNIGHT_DEATH);
        SetStep(KNIGHT_DEAD);
    }
    rock_knight_mode = self->params & 1;
    animBlock = animations + (rock_knight_mode * 5);
    switch (self->step) { /* irregular */
    case KNIGHT_INIT:
        if (!self->params) {
            InitializeEntity(g_EInitBombKnight);
            self->animCurFrame = 1; // bomb knight holding bomb
        } else {
            InitializeEntity(g_EInitRockKnight);
            self->animCurFrame = 41; // rock knight holding rock
        }
        other = self + 1;
        CreateEntityFromCurrentEntity(E_BOMB_KNIGHT_ARM, other);
        other->params = self->params;
        if (rock_knight_mode == 0) {
            other = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (other != NULL) {
                CreateEntityFromCurrentEntity(E_FUSE_SPARKS, other);
                other->ext.bombKnight.fuseParent = self;
                other->zPriority = ((self->zPriority) + 1);
            }
        }
        break;
    case KNIGHT_COLLCHECK:
        if (UnkCollisionFunc3(sensors1) & 1) {
            SetStep(KNIGHT_WAIT);
        }
        break;
    case KNIGHT_WAIT:
        if (GetDistanceToPlayerX() < 0x80) {
            self->facingLeft = ((GetSideToPlayer() & 1) ^ 1);
            SetStep(KNIGHT_IDLE);
        }
        break;
    case KNIGHT_IDLE:
        if (!self->step_s) {
            self->ext.bombKnight.throwTimer =
                throwTimers[self->ext.bombKnight.timerCycler];
            self->ext.bombKnight.timerCycler++;
            self->ext.bombKnight.timerCycler &= 7;
            self->step_s++;
        }
        AnimateEntity(animBlock[ANIM_IDLE], self);
        if (self->facingLeft != ((GetSideToPlayer() & 1) ^ 1)) {
            SetStep(KNIGHT_TURNAROUND);
        } else {
            UnkCollisionFunc2(sensors2);
            if ((self->facingLeft ^ (self->ext.bombKnight.playerClose)) != 0) {
                self->velocityX = FIX(0.375);
            } else {
                self->velocityX = FIX(-0.375);
            }
            if (self->params & 0x100) {
                self->velocityX = 0;
            }
            if (self->ext.bombKnight.throwTimer) {
                self->ext.bombKnight.throwTimer--;
            }
            if (GetDistanceToPlayerX() < 0x40) {
                self->ext.bombKnight.playerClose = 1;
            } else if (GetDistanceToPlayerX() > 0x70) {
                self->ext.bombKnight.playerClose = 0;
            } else if (!self->ext.bombKnight.throwTimer) {
                if (rock_knight_mode == 0) {
                    PlaySfxPositional(SFX_UNK_RNO4_75C);
                }
                if (GetDistanceToPlayerX() < 0x50) {
                    SetStep(KNIGHT_CLOSETHROW);
                } else {
                    SetStep(KNIGHT_FARTHROW);
                }
            }
            if (self->hitFlags & 3) {
                SetStep(KNIGHT_HIT);
            }
        }
        break;
    case KNIGHT_TURNAROUND:
        if (AnimateEntity(animBlock[ANIM_TURNAROUND], self) == 0) {
            self->facingLeft ^= 1;
            self->animCurFrame = 1;
            SetStep(KNIGHT_IDLE);
        }
        break;
    case KNIGHT_CLOSETHROW:
        if (AnimateEntity(animBlock[ANIM_FAST_THROW], self) == 0) {
            SetStep(KNIGHT_IDLE);
        }
        if ((!self->poseTimer) && ((self->pose) == 3)) {
            other = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (other != NULL) {
                if (rock_knight_mode != 0) {
                    CreateEntityFromEntity(E_THROWN_ROCK, self, other);
                    PlaySfxPositional(SFX_ROCK_KNIGHT_ATTACK);
                } else {
                    CreateEntityFromEntity(E_THROWN_BOMB, self, other);
                    PlaySfxPositional(SFX_ROCK_KNIGHT_PAIN);
                }
                if (self->facingLeft) {
                    other->posX.i.hi -= 8;
                } else {
                    other->posX.i.hi += 8;
                }
                other->posY.i.hi -= 40;
                other->facingLeft = self->facingLeft;
                other->params = 0;
            }
        }
        break;
    case KNIGHT_FARTHROW:
        if (AnimateEntity(animBlock[ANIM_THROW], self) == 0) {
            SetStep(3);
        }
        if ((!self->poseTimer) && ((self->pose) == 4)) {
            other = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (other != NULL) {
                if (rock_knight_mode != 0) {
                    CreateEntityFromEntity(E_THROWN_ROCK, self, other);
                    PlaySfxPositional(SFX_ROCK_KNIGHT_ATTACK);
                } else {
                    CreateEntityFromEntity(E_THROWN_BOMB, self, other);
                    PlaySfxPositional(SFX_ROCK_KNIGHT_PAIN);
                }
                if (self->facingLeft) {
                    other->posX.i.hi -= 8;
                } else {
                    other->posX.i.hi += 8;
                }
                other->posY.i.hi -= 40;
                other->facingLeft = self->facingLeft;
                other->params = 1;
            }
        }
        break;
    case KNIGHT_HIT:
        if (AnimateEntity(animBlock[ANIM_GUARD], self) == 0) {
            SetStep(3);
        }
        UnkCollisionFunc2(sensors2);
        if (self->facingLeft) {
            self->velocityX = FIX(-0.1875);
        } else {
            self->velocityX = FIX(0.1875);
        }
        break;
    case KNIGHT_DEAD:
        deathOffset = deathPartsData;
        for (i = 0; i < 11; i++, deathOffset++) {
            other = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (other != NULL) {
                CreateEntityFromEntity(E_DEATH_PARTS, self, other);
                other->params = i;
                if (rock_knight_mode != 0) {
                    other->params |= 0x100;
                }
                other->facingLeft = self->facingLeft;
                if (self->facingLeft) {
                    other->posX.i.hi -= deathOffset->x;
                } else {
                    other->posX.i.hi += deathOffset->x;
                }
                other->posY.i.hi += deathOffset->y;
            }
        }
        other = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (other != NULL) {
            CreateEntityFromEntity(E_EXPLOSION, self, other);
            other->params = 3;
            other->zPriority = ((self->zPriority) + 4);
        }
        PlaySfxPositional(SFX_FM_EXPLODE_B);
        DestroyEntity(self);
        return;
    case 255:
#include "../pad2_anim_debug.h"
        break;
    }
    hitbox = &hitboxes[0];
    if (rock_knight_mode != 0) {
        offsetX = hitboxOffsets[self->animCurFrame - 40];
    } else {
        offsetX = hitboxOffsets[self->animCurFrame];
    }
    hitbox += offsetX * 4;
    self->hitboxOffX = *hitbox++;
    self->hitboxOffY = *hitbox++;
    self->hitboxWidth = *hitbox++;
    self->hitboxHeight = *hitbox++;
}

void EntityThrownBomb(Entity* self) {
    Collider coll;
    Entity* other;

    s32 collX, collY;
    s32 i;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitBomb);
        self->animCurFrame = 36;
        other = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (other != NULL) {
            CreateEntityFromCurrentEntity(E_FUSE_SPARKS, other);
            other->ext.bombKnight.fuseParent = self;
            other->zPriority = ((self->zPriority) + 1);
        }
        if (self->params == 0) {
            self->velocityX = FIX(1.0);
        } else {
            self->velocityX = FIX(2.0);
        }
        self->velocityY = FIX(-2.0);
        if (!self->facingLeft) {
            self->velocityX = -self->velocityX;
        }
        break;
    case 1:
        MoveEntity();
        self->velocityY += FIX(0.125);
        self->rotate += ROT(11.25);
        if (g_Timer & 2) {
            self->palette = 0x236;
        } else {
            self->palette = PAL_FLAG(PAL_CC_RED_EFFECT_A);
        }
        collX = self->posX.i.hi;
        collY = self->posY.i.hi + 4;
        g_api.CheckCollision(collX, collY, &coll, 0);
        if (coll.effects & EFFECT_SOLID) {
            SetStep(2);
        }
        if ((self->hitboxState) == 2) {
            if (self->hitFlags) {
                SetStep(2);
            }
        } else if (self->hitFlags & 3) {
            self->hitFlags = 0;
            self->velocityX = -self->velocityX;
            self->velocityY += FIX(-2);
            other = AllocEntity(&g_Entities[0x20], &g_Entities[0x2F]);
            if (other != NULL) {
                DestroyEntity(other);
                // This is a really weird thing to do.
                // We copy ourself into an other, set it as a death parts,
                // and then destroy our self.
                *other = *self;
                other->entityId = E_DEATH_PARTS;
                other->drawFlags |= ENTITY_ROTATE;
                other->hitboxState = 2;
                other->attackElement = ELEMENT_FIRE;
                other->nFramesInvincibility = 0x10;
                other->stunFrames = 4;
                other->hitEffect = 1;
                other->ext.bombKnight.unkB2_WTF = 0;
                other->flags =
                    FLAG_POS_CAMERA_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA;
                g_api.func_80118894(other);
                DestroyEntity(self);
                return;
            }
        } else if (self->hitFlags) {
            SetStep(2);
        }
        break;
    case 2:
        switch (self->step_s) { /* switch 2*/
        case 0:                 /* switch 2 */
            self->animSet = ANIMSET_OVL(12);
            self->palette = 0x23A;
            if ((self->hitboxState) == 2) {
                self->palette = 0x23B;
            } else {
                self->hitboxState = 1;
            }
            self->unk5A = 0x4A;
            self->animCurFrame = 1;
            self->blendMode = BLEND_ADD | BLEND_TRANSP;
// please konami what are you doing, other doesn't even exist yet
#ifdef VERSION_US
            other->drawFlags = ENTITY_DEFAULT;
#else
            self->drawFlags = ENTITY_DEFAULT;
#endif
            self->hitboxWidth = self->hitboxHeight = 20;
            for (i = 0; i < 3; i++) {
                other = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (other != NULL) {
                    CreateEntityFromEntity(E_EXPLOSION, self, other);
                    other->params = 1;
                    other->posX.i.hi += explosionOffsets[i].x;
                    other->posY.i.hi += explosionOffsets[i].y;
                }
            }
            PlaySfxPositional(SFX_FM_EXPLODE_B);
            self->step_s += 1;
            /* fallthrough */
        case 1: /* switch 2 */
            if (self->pose > 5) {
                self->hitboxState = 0;
            }
            if (AnimateEntity(anim_another_bomb_throw, self) == 0) {
                DestroyEntity(self);
            }
            break;
        }
        break;
    }
}

// Only when bomb is held, not when thrown
void EntityBombFuseSparks(Entity* self) {
    s32 animFrame;
    s8* xyPtr;
    Entity* knight;

    switch (self->step) { /* irregular */
    case 0:
        InitializeEntity(g_EInitBombKnight);
        /* fallthrough */
    case 1:
        AnimateEntity(anim_bomb_fuse_sparks, self);
        knight = self->ext.bombKnight.fuseParent;
        self->facingLeft = knight->facingLeft;
        self->posX.i.hi = knight->posX.i.hi;
        self->posY.i.hi = knight->posY.i.hi;
        animFrame = knight->animCurFrame;
        if (animFrame == 36) {
            self->posY.i.hi -= 8;
            return;
        }

        xyPtr = &fuseSparksXY[0];
        animFrame = fuseFrameMap[animFrame];
        if (animFrame == 0) {
            self->animCurFrame = 0;
        }
        xyPtr += animFrame * 2;
        if (knight->facingLeft) {
            self->posX.i.hi -= *xyPtr++;
        } else {
            self->posX.i.hi += *xyPtr++;
        }
        self->posY.i.hi += *xyPtr++;
        if (knight->entityId != E_BOMB_KNIGHT) {
            DestroyEntity(self);
        }
    }
}

void EntityThrownRock(Entity* self) {
    Collider coll;
    Entity* fragment;
    s32 collX, collY;
    s32 i;

    if ((self->flags & FLAG_DEAD) && (self->step != 2)) {
        self->hitboxState = 0;
        PlaySfxPositional(SFX_WALL_DEBRIS_A);
        SetStep(2);
    }
    switch (self->step) { /* irregular */
    case 0:
        InitializeEntity(g_EInitRock);
        if (self->params == 0) {
            self->velocityX = FIX(1.0);
        } else {
            self->velocityX = FIX(2.0);
        }
        self->velocityY = FIX(-2.0);
        if (!self->facingLeft) {
            self->velocityX = -self->velocityX;
        }
        /* fallthrough */
    case 1:
        MoveEntity();
        self->velocityY += FIX(0.125);
        collX = self->posX.i.hi;
        collY = self->posY.i.hi + 8;
        g_api.CheckCollision(collX, collY, &coll, 0);
        if (coll.effects & EFFECT_SOLID) {
            PlaySfxPositional(SFX_WALL_DEBRIS_A);
            self->hitboxState = 0;
            SetStep(2);
        }
        break;
    case 2:
        if (AnimateEntity(&anim_rock_shatter, self) == 0) {
            for (i = 0; i < 7; i++) {
                fragment = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (fragment != NULL) {
                    CreateEntityFromEntity(E_ROCK_PIECE, self, fragment);
                    fragment->params = Random() & 7;
                }
            }
            self->pfnUpdate = EntityExplosion;
            self->step = 0;
            self->params = 0x13;
            self->pose = 0;
            self->poseTimer = 0;
        }
        break;
    }
}

void EntityRockPiece(Entity* self) {
    s32 speed;
    s16 angle;

    if (!self->step) {
        InitializeEntity(g_EInitKnightDebris);
        self->animCurFrame = self->params + 72;
        speed = (Random() & 0x1F) + 0x10;
        angle = (Random() * 6) + ROT(202.5);
        self->velocityX = speed * rcos(angle);
        self->velocityY = speed * rsin(angle);
    }
    MoveEntity();
    self->velocityY += FIX(0.125);
}

void EntityKnightDeathParts(Entity* self) {
    deathParts* temp_s0;

    if (!self->step) {
        InitializeEntity(g_EInitKnightDebris);
        if (self->params & 0x100) {
            self->palette += 2;
            self->params &= 0xFF;
        }
        self->animCurFrame = self->params + 0x19;
        self->drawFlags = ENTITY_ROTATE;
        if (GetSideToPlayer() & 1) {
            self->velocityX = FIX(1.0);
        } else {
            self->velocityX = FIX(-1.0);
        }
        temp_s0 = &deathPartsData[0];
        temp_s0 += self->params;
        if (self->facingLeft) {
            self->velocityX -= temp_s0->velX;
        } else {
            self->velocityX += temp_s0->velX;
        }
        self->velocityY += temp_s0->velY;
        self->ext.bombKnight.deathPartLife = temp_s0->lifetime;
    }
    MoveEntity();
    self->velocityY += FIX(0.15625);
    temp_s0 = &deathPartsData[0];
    temp_s0 += self->params;
    self->rotate += temp_s0->rotSpeed;
    if (!--self->ext.bombKnight.deathPartLife) {
        if (Random() & 1) {
            PlaySfxPositional(SFX_EXPLODE_D);
        } else {
            PlaySfxPositional(SFX_FM_EXPLODE_B);
        }
        self->step = 0;
        self->pfnUpdate = EntityExplosion;
        self->params = 1;
        self->drawFlags = ENTITY_DEFAULT;
    }
}

void EntityBombKnightArm(Entity* self) {
    Entity* other;
    s32 offsetX;
    s8* hitbox;

    if (!self->step) {
        InitializeEntity(g_EInitBombKnight);
#ifdef VERSION_US
        self->flags |= FLAG_UNK_00200000 | FLAG_UNK_2000;
#endif
        self->animSet = 0;
        self->animCurFrame = 0;
        self->parent = self - 1;
        self->nextPart = self - 1;
    }
    other = self - 1;
    self->facingLeft = other->facingLeft;
    self->posX.i.hi = other->posX.i.hi;
    self->posY.i.hi = other->posY.i.hi;
    hitbox = armHitboxes;
    if (self->params) {
        offsetX = rockArmHitboxOffsets[other->animCurFrame - 40];
    } else {
        offsetX = bombArmHitboxOffsets[other->animCurFrame];
    }
    hitbox += offsetX * 4;
    self->hitboxOffX = *hitbox++;
    self->hitboxOffY = *hitbox++;
    self->hitboxWidth = *hitbox++;
    self->hitboxHeight = *hitbox++;
    if (other->entityId != E_BOMB_KNIGHT) {
        DestroyEntity(self);
    }
}
