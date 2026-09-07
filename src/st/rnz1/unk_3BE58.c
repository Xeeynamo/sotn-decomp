// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rnz1.h"

static s16 D_pspeu_09257C00[] = {0, 37, 0, 4, 8, -4, -16, 0};
static s16 D_pspeu_09257C10[] = {0, 37, 8, 0};
static s16 unused_sensors[] = {0, 8, 0, 4, 4, -4, -8, 0};
static AnimateEntityFrame anim_idle_holding_bomb[] = {{14, 1}, {14, 2}, {11, 3}, {10, 2}, POSE_LOOP(0)};
// Throw bomb and grab a new one from hammerspace
static AnimateEntityFrame anim_throw_bomb[] = {{16, 1}, {8, 2}, {30, 1}, {4, 4}, {3, 5}, {2, 6}, {2, 7}, {2, 8}, {1, 9}, {1, 8}, {3, 10}, {33, 8}, {6, 7}, {5, 6}, {5, 17}, {4, 18}, {4, 19}, {3, 20}, {14, 21}, {6, 24}, {6, 22}, {6, 23}, {4, 1}, {6, 2}, {8, 1}, POSE_END};
static AnimateEntityFrame anim_turnaround_bomb[] = {{8, 1}, {5, 11}, {9, 12}, {8, 13}, POSE_END};
// Take non-bomb hand and slide across body
static AnimateEntityFrame anim4[] = {{8, 14}, {8, 15}, {19, 16}, {5, 15}, POSE_END};
static AnimateEntityFrame anim_fastthrow_bomb[] = {{5, 1}, {3, 4}, {2, 5}, {2, 6}, {1, 7}, {7, 6}, {6, 17}, {5, 18}, {4, 19}, {2, 20}, {3, 21}, {8, 24}, {7, 22}, {7, 23}, {3, 1}, {6, 2}, {8, 1}, POSE_END};
static AnimateEntityFrame anim_bomb_fuse_sparks[] = {{4, 37}, {4, 38}, {4, 39}, {4, 40}, POSE_LOOP(0)};

static AnimateEntityFrame anim7[] = {{14, 41}, {14, 42}, {11, 43}, {10, 42}, POSE_LOOP(0)};
static AnimateEntityFrame anim8[] = {{14, 41}, {8, 42}, {26, 41}, {3, 44}, {2, 45}, {2, 46}, {2, 47}, {2, 48}, {1, 49}, {1, 48}, {3, 50}, {33, 48}, {6, 47}, {5, 46}, {5, 57}, {4, 58}, {4, 59}, {3, 60}, {6, 61}, {10, 64}, {8, 62}, {6, 63}, {3, 41}, {6, 42}, {4, 41}, POSE_END};
static AnimateEntityFrame anim9[] = {{8, 41}, {5, 51}, {9, 52}, {8, 53}, POSE_END};
static AnimateEntityFrame anim10[] = {{8, 54}, {8, 55}, {19, 56}, {5, 55}, POSE_END};
static AnimateEntityFrame anim11[] = {{5, 41}, {3, 44}, {2, 45}, {2, 46}, {1, 47}, {7, 46}, {6, 57}, {5, 58}, {4, 59}, {4, 60}, {3, 61}, {10, 64}, {8, 62}, {6, 63}, {3, 41}, {6, 42}, {4, 41}, POSE_END};
static AnimateEntityFrame anim_rock_shatter[] = {{1, 69}, {1, 70}, {1, 71}, POSE_END};
typedef enum {
    ANIM_IDLE,
    ANIM_TURNAROUND,
    ANIM_FAST_THROW,
    ANIM_THROW,
    ANIM_GUARD
} animIdx;
 static AnimateEntityFrame* animations[] = {anim_idle_holding_bomb, anim_turnaround_bomb, anim_fastthrow_bomb, anim_throw_bomb, anim4, anim7, anim9, anim11, anim8, anim10};
static s8 D_pspeu_09257D78[] = {0, 0, 0, 0, 1, 6, 15, 29, 1, 5, 15, 29, 1, 4, 15, 29};
static s8 D_us_8018228C[] = {0, 7, 15, 29, -5, 10, 13, 26, -10, 10, 14, 26, -11, 10, 14, 26, 0, 5, 12, 31, 0, 6, 14, 30, -1, 6, 14, 30, -5, 9, 12, 26, -1, 7, 14, 28, 1, 5, 14, 30};
static u8 D_us_801822B4[] = {0, 1, 2, 3, 4, 5, 5, 5, 6, 7, 6, 8, 8, 8, 9, 9, 10, 11, 11, 12, 13, 13, 13, 13, 13};
static s8 D_us_801822D0[] = {0, 0, 0, 0, 17, -26, 4, 11, 16, -27, 4, 11, 15, -28, 4, 11, 13, -31, 4, 12, -3, -20, 8, 7, -79, -91, 0, 0, 9, 24, 4, 11, 8, 24, 4, 11, 15, -29, 4, 11, 18, -28, 4, 11, 17, -27, 4, 11, 13, -32, 4, 12, -84, -89, 0, 0, -87, -89, 0, 0, -92, -94, 0, 0, -90, -87, 0, 0, -85, -87, 0, 0, -88, -88, 0, 0, -87, -88, 0, 0, -83, -88, 0, 0, -83, -90, 0, 0, -87, -90, 0, 0, -91, -90, 0, 0, 16, -31, 7, 15, 15, -32, 7, 15, 14, -33, 7, 15, 10, -36, 7, 15, 8, 22, 4, 9, -14, -26, 7, 15, -14, -36, 7, 15, -16, -31, 7, 15, 14, -34, 7, 15};
static s8 D_us_80182354[] = {16, -33, 7, 15, 18, -4, 6, 9, 12, -39, 7, 15};
static u8 D_us_80182360[] = {0, 1, 2, 3, 4, 5, 6, 6, 7, 8, 7, 6, 6, 6, 9, 10, 11, 6, 6, 6, 6, 6, 6, 12, 6};
static u8 D_us_8018237C[] = {24, 25, 26, 27, 5, 6, 6, 7, 28, 7, 29, 30, 31, 32, 33, 25, 6, 6, 6, 6, 6, 34, 35, 6};

static AnimateEntityFrame anim_another_bomb_throw[] = {{4, 1}, {4, 2}, {4, 3}, {4, 4}, {4, 5}, {4, 6}, {2, 7}, {2, 8}, POSE_END};

static s32 D_pspeu_09257EB0[] = {32, 0, 0, 128, 64, 0, 0, 0};
static Point16 D_us_801823C8[] = {{12, 8}, {-12, 8}, {0, -2}};
typedef struct{
    s16 x;
    s16 y;
    s32 velX;
    s32 velY;
    s16 rotSpeed;
    s16 lifetime;
} deathParts;
static deathParts D_us_801823D4[] = {
    {0,    -4,  FIX(1.0/8),          FIX(-0.5),  32, 34},
    {0,   -24,           0,         FIX(-1.75), 128, 32},
    {0,     0,           0,         FIX(-0.25),   0, 28},
    {-8,  -20,   FIX(-0.5),         FIX(-1.25),  96, 28},
    {8,   -22,    FIX(0.5), FIX(-(1 + 7.0/16)), -96, 30},
    {-4,    8,  FIX(-0.25),          FIX(-0.5), -64, 20},
    {4,     8,   FIX(0.25),        FIX(-3.0/8),  48, 22},
    {-16, -12, FIX(-5.0/8),            FIX(-1),  96, 24},
    {16,   -4,  FIX(5.0/8), FIX(- (1 + 1.0/8)), -96, 26},
    {-12,  28, FIX(-1.0/8),        FIX(-7.0/8), -32, 16},
    {12,   28,  FIX(1.0/8),        FIX(-3.0/4),  16, 18},
};
static s8 D_us_80182484[] = {0, 0, 19, -41, 18, -43, 19, -45, 15, -49, -79, -91, -13, -37, -17, -49, -20, -43, 17, -46, 20, -45, 16, -50};
static u8 D_us_8018249C[] = {0, 1, 2, 3, 4, 0, 0, 0, 0, 0, 0, 6, 7, 8, 9, 10, 10, 0, 0, 0, 0, 0, 0, 11};

extern EInit g_EInitBombKnight;
extern EInit g_EInitRockKnight;
extern EInit D_us_80180C48;
extern EInit D_us_80180C54;
extern EInit D_us_80180C60;

void EntityBombKnight(Entity* self) {
    deathParts* deathOffset;
    Entity* other;
    s32 rock_knight_mode;
    s32 i;
    s32 offsetX;
    s8* hitbox;
    AnimateEntityFrame** animBlock;

    if ((self->flags & 0x100) && (self->step < 8)) {
        PlaySfxPositional(0x75D);
        SetStep(8);
    }
    rock_knight_mode = self->params & 1;
    animBlock = animations + (rock_knight_mode * 5);
    switch (self->step) {                              /* irregular */
    case 0x0:
        if (!self->params) {
            InitializeEntity(g_EInitBombKnight);
            self->animCurFrame = 1; // bomb knight holding bomb
        } else {
            InitializeEntity(g_EInitRockKnight);
            self->animCurFrame = 0x29; // rock knight holding rock
        }
        other = self + 1;
        CreateEntityFromCurrentEntity(0x47, other);
        other->params = self->params;
        if (rock_knight_mode == 0) {
            other = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (other != NULL) {
                CreateEntityFromCurrentEntity(0x44, other);
                other->ext.ILLEGAL.u32[3] = (u32) self;
                other->zPriority = ((self->zPriority) + 1);
            }
        }
        break;
    case 0x1:
        if (UnkCollisionFunc3(&D_pspeu_09257C00) & 1) {
            SetStep(2);
        }
        break;
    case 0x2:
        if (GetDistanceToPlayerX() < 0x80) {
            self->facingLeft = (( GetSideToPlayer() & 1) ^ 1);
            SetStep(3);
        }
        break;
    case 0x3:
        if (!self->step_s) {
            self->ext.ILLEGAL.s16[3] = D_pspeu_09257EB0[self->ext.ILLEGAL.u8[9]];
            self->ext.ILLEGAL.u8[9]++;
            self->ext.ILLEGAL.u8[9] &= 7;
            self->step_s++;
        }
        AnimateEntity(animBlock[ANIM_IDLE], self);
        if (self->facingLeft != ((GetSideToPlayer() & 1) ^ 1)) {
            SetStep(4);
        } else {
            UnkCollisionFunc2(&D_pspeu_09257C10);
            if ((self->facingLeft ^ (self->ext.ILLEGAL.u8[8])) != 0) {
                self->velocityX = 0x6000;
            } else {
                self->velocityX = -0x6000;
            }
            if (self->params & 0x100) {
                self->velocityX = 0;
            }
            if (self->ext.ILLEGAL.s16[3]) {
                self->ext.ILLEGAL.s16[3]--;
            }
            if (GetDistanceToPlayerX() < 0x40) {
                self->ext.ILLEGAL.u8[8] = 1;
            } else if (GetDistanceToPlayerX() > 0x70) {
                self->ext.ILLEGAL.u8[8] = 0;
            } else if (!self->ext.ILLEGAL.s16[3]) {
                if (rock_knight_mode == 0) {
                    PlaySfxPositional(0x75C);
                }
                if (GetDistanceToPlayerX() < 0x50) {
                    SetStep(5);
                } else {
                    SetStep(6);
                }
            }
            if (self->hitFlags & 3) {
                SetStep(7);
            }
        }
        break;
    case 0x4:
        if (AnimateEntity(animBlock[ANIM_TURNAROUND], self) == 0) {
            self->facingLeft ^= 1;
            self->animCurFrame = 1;
            SetStep(3);
        }
        break;
    case 0x5:
        if (AnimateEntity(animBlock[ANIM_FAST_THROW], self) == 0) {
            SetStep(3);
        }
        if ((!self->poseTimer) && ((self->pose) == 3)) {
            other = AllocEntity(&g_Entities[0xA0], &g_Entities[0xC0]);
            if (other != NULL) {
                if (rock_knight_mode != 0) {
                    CreateEntityFromEntity(0x45, self, other);
                    PlaySfxPositional(0x75A);
                } else {
                    CreateEntityFromEntity(0x42, self, other);
                    PlaySfxPositional(0x75B);
                }
                if (self->facingLeft) {
                    other->posX.i.hi -= 8;
                } else {
                    other->posX.i.hi += 8;
                }
                other->posY.i.hi -= 0x28;
                other->facingLeft = self->facingLeft;
                other->params = 0;
            }
        }
        break;
    case 0x6:
        if (AnimateEntity(animBlock[ANIM_THROW], self) == 0) {
            SetStep(3);
        }
        if ((!self->poseTimer) && ((self->pose) == 4)) {
            other = AllocEntity(&g_Entities[0xA0], &g_Entities[0xC0]);
            if (other != NULL) {
                if (rock_knight_mode != 0) {
                    CreateEntityFromEntity(0x45, self, other);
                    PlaySfxPositional(0x75A);
                } else {
                    CreateEntityFromEntity(0x42, self, other);
                    PlaySfxPositional(0x75B);
                }
                if (self->facingLeft) {
                    other->posX.i.hi -= 8;
                } else {
                    other->posX.i.hi += 8;
                }
                other->posY.i.hi -= 0x28;
                other->facingLeft = self->facingLeft;
                other->params = 1;
            }
        }
        break;
    case 0x7:
        if (AnimateEntity(animBlock[ANIM_GUARD], self) == 0) {
            SetStep(3);
        }
        UnkCollisionFunc2(&D_pspeu_09257C10);
        if (self->facingLeft) {
            self->velocityX = -0x3000;
        } else {
            self->velocityX = 0x3000;
        }
        break;
    case 0x8:
        deathOffset = &D_us_801823D4;
        for(i = 0; i < 11; i++, deathOffset++) {
            other = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (other != NULL) {
                CreateEntityFromEntity(0x43, self, other);
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
            CreateEntityFromEntity(2, self, other);
            other->params = 3;
            other->zPriority = ((self->zPriority) + 4);
        }
        PlaySfxPositional(0x65B);
        DestroyEntity(self);
        return;
    case 0xFF:
        #include "../pad2_anim_debug.h"
        break;
    }
    hitbox = &D_pspeu_09257D78[0];
    if (rock_knight_mode != 0) {
        offsetX = D_us_801822B4[self->animCurFrame - 40];
    } else {
        offsetX = D_us_801822B4[self->animCurFrame];
    }
    hitbox += offsetX * 4;
    self->hitboxOffX = *hitbox++;
    self->hitboxOffY = *hitbox++;
    self->hitboxWidth = *hitbox++;
    self->hitboxHeight = *hitbox++;
}


void func_us_801BC650(Entity* self) {
    Collider sp2C;
    Entity* other;

    s32 collX, collY;
    s32 var_s1;

    switch (self->step) {                              /* switch 1; irregular */
    case 0:                                         /* switch 1 */
        InitializeEntity(D_us_80180C48);
        self->animCurFrame = 0x24;
        other = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (other != NULL) {
            CreateEntityFromCurrentEntity(0x44, other);
            other->ext.ILLEGAL.u32[3] = (u32) self;
            other->zPriority = ((self->zPriority) + 1);
        }
        if (self->params == 0) {
            self->velocityX = 0x10000;
        } else {
            self->velocityX = 0x20000;
        }
        self->velocityY = -0x20000;
        if (!self->facingLeft) {
            self->velocityX = -self->velocityX;
        }
        return;
    case 1:                                         /* switch 1 */
        MoveEntity();
        self->velocityY += 0x2000;
        self->rotate += 0x80;
        if (g_Timer & 2) {
            self->palette = 0x236;
        } else {
            self->palette = 0x8166;
        }
        collX = self->posX.i.hi;
        collY = self->posY.i.hi + 4;
        g_api.CheckCollision(collX, collY, &sp2C, 0);
        if (sp2C.effects & 1) {
            SetStep(2);
        }
        if ((self->hitboxState) == 2) {
            if (self->hitFlags) {
                SetStep(2);
                return;
            }
        } else if (self->hitFlags & 3) {
            self->hitFlags = 0;
            self->velocityX = -self->velocityX;
            self->velocityY += 0xFFFE0000;
            other = AllocEntity(&g_Entities[0x20], &g_Entities[0x2F]);
            if (other != NULL) {
                DestroyEntity(other);
                *other = *self;
                other->entityId = 0x43;
                other->drawFlags |= 4;
                other->hitboxState = 2;
                other->attackElement = 0x8000;
                other->nFramesInvincibility = 0x10;
                other->stunFrames = 4;
                other->hitEffect = 1;
                other->ext.ILLEGAL.u16[0x1B] = 0;
                other->flags = 0x0C000000;
                g_api.func_80118894(other);
                DestroyEntity(self);
                return;
            }
        } else if (self->hitFlags) {
            SetStep(2);
            return;
        }
        break;
    case 2:                                         /* switch 1 */
        switch (self->step_s) {                        /* switch 2; irregular */
        case 0:                                     /* switch 2 */
            self->animSet = -0x7FF4;
            self->palette = 0x23A;
            if ((self->hitboxState) == 2) {
                self->palette = 0x23B;
            } else {
                self->hitboxState = 1;
            }
            self->unk5A = 0x4A;
            self->animCurFrame = 1;
            self->blendMode = 0x30;
            // please konami what are you doing, other doesn't even exist yet
            #ifdef VERSION_US
            other->drawFlags = 0;
            #else
            self->drawFlags = 0;
            #endif
            self->hitboxWidth = self->hitboxHeight = 20;
            for(var_s1 = 0; var_s1 < 3; var_s1++) {
                other = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (other != NULL) {
                    CreateEntityFromEntity(2, self, other);
                    other->params = 1;
                    other->posX.i.hi += D_us_801823C8[var_s1].x;
                    other->posY.i.hi += D_us_801823C8[var_s1].y;
                }
            }
            PlaySfxPositional(0x65B);
            self->step_s += 1;
            /* fallthrough */
        case 1:                                     /* switch 2 */
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

void func_us_801BCA5C(Entity* self) {
    s32 animFrame;
    s8* xyPtr;
    Entity* other;
    

    switch (self->step) {                              /* irregular */
    case 0:
        InitializeEntity(g_EInitBombKnight);
        /* fallthrough */
    case 1:
        AnimateEntity(anim_bomb_fuse_sparks, self);
        other = (Entity*)self->ext.ILLEGAL.u32[3];
        self->facingLeft = other->facingLeft;
        self->posX.i.hi = other->posX.i.hi;
        self->posY.i.hi = other->posY.i.hi;
        animFrame = other->animCurFrame;
        if (animFrame == 0x24) {
            self->posY.i.hi -= 8;
            return;
        }
        
        xyPtr = &D_us_80182484;
        animFrame = D_us_8018249C[animFrame];
        if (animFrame == 0) {
            self->animCurFrame = 0;
        }
        xyPtr += animFrame * 2;
        if (other->facingLeft) {
            self->posX.i.hi -= *xyPtr++;
        } else {
            self->posX.i.hi += *xyPtr++;
        }
        self->posY.i.hi += *xyPtr++;
        if (other->entityId != 0x41) {
            DestroyEntity(self);
        }
    }
}

void func_us_801BCB9C(Entity* self) {
    Collider sp2C;
    Entity* other;
    s32 collX, collY;
    s32 var_s1;

    if ((self->flags & 0x100) && (self->step != 2)) {
        self->hitboxState = 0;
        PlaySfxPositional(0x643);
        SetStep(2);
    }
    switch (self->step) {                              /* irregular */
    case 0:
        InitializeEntity(D_us_80180C60);
        if (self->params == 0) {
            self->velocityX = 0x10000;
        } else {
            self->velocityX = 0x20000;
        }
        self->velocityY = -0x20000;
        if (!self->facingLeft) {
            self->velocityX = -self->velocityX;
        }
        /* fallthrough */
    case 1:
        MoveEntity();
        self->velocityY += 0x2000;
        collX = self->posX.i.hi;
        collY = self->posY.i.hi + 8;
        g_api.CheckCollision(collX, collY, &sp2C, 0);
        if (sp2C.effects & 1) {
            PlaySfxPositional(0x643);
            self->hitboxState = 0;
            SetStep(2);
        }
        return;
    case 2:
        if (AnimateEntity(&anim_rock_shatter, self) == 0) {
            for(var_s1 = 0; var_s1 < 7; var_s1++) {
                other = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (other != NULL) {
                    CreateEntityFromEntity(0x46, self, other);
                    other->params = Random() & 7;
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

void func_us_801BCD80(Entity* self) {
    s32 speed;
    s16 angle;

    if (!self->step) {
        InitializeEntity(D_us_80180C54);
        self->animCurFrame = self->params + 72;
        speed = (Random() & 0x1F) + 0x10;
        angle = (Random() * 6) + 0x900;
        self->velocityX = speed * rcos(angle);
        self->velocityY = speed * rsin(angle);
    }
    MoveEntity();
    self->velocityY += 0x2000;
}

void func_us_801BCE4C(Entity* self) {
    s32 var_a0;
    u16 temp_v1;
    deathParts* temp_s0;

    if (!self->step) {
        InitializeEntity(D_us_80180C54);
        if (self->params & 0x100) {
            self->palette += 2;
            self->params &= 0xFF;
        }
        self->animCurFrame = self->params + 0x19;
        self->drawFlags = 4;
        if (GetSideToPlayer() & 1) {
            self->velocityX = 0x10000;
        } else {
            self->velocityX = -0x10000;
        }
        temp_s0 = &D_us_801823D4;
        temp_s0 += self->params;
        if (self->facingLeft) {
            self->velocityX -= temp_s0->velX;
        } else {
            self->velocityX += temp_s0->velX;
        }
        self->velocityY += temp_s0->velY;
        self->ext.ILLEGAL.s16[2] = temp_s0->lifetime;
    }
    MoveEntity();
    self->velocityY += 0x2800;
    temp_s0 = &D_us_801823D4;
    temp_s0 += self->params;
    self->rotate += temp_s0->rotSpeed;
    if (!--self->ext.ILLEGAL.s16[2]) {
        if (Random() & 1) {
            PlaySfxPositional(0x657);
        } else {
            PlaySfxPositional(0x65B);
        }
        self->step = 0;
        self->pfnUpdate = EntityExplosion;
        self->params = 1;
        self->drawFlags = 0;
    }
}

void func_us_801BCFC8(Entity* self) {
    Entity* other;
    s32 offsetX;
    s8* hitbox;

    if (!self->step) {
        InitializeEntity(g_EInitBombKnight);
        self->flags |= 0x202000;
        self->animSet = 0;
        self->animCurFrame = 0;
        self->parent = self - 1;
        self->nextPart = self - 1;
    }
    other = self - 1;
    self->facingLeft = other->facingLeft;
    self->posX.i.hi = other->posX.i.hi;
    self->posY.i.hi = other->posY.i.hi;
    hitbox = D_us_801822D0;
    if (self->params) {
        offsetX = D_us_8018237C[other->animCurFrame - 40];
    } else {
        offsetX = D_us_80182360[other->animCurFrame];
    }
    hitbox += offsetX * 4;
    self->hitboxOffX = *hitbox++;
    self->hitboxOffY = *hitbox++;
    self->hitboxWidth = *hitbox++;
    self->hitboxHeight = *hitbox++;
    if (other->entityId != 0x41) {
        DestroyEntity(self);
    }
}