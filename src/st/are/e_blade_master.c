// SPDX-License-Identifier: AGPL-3.0-or-later
#include "are.h"

extern EInit g_EInitBladeMaster;
extern EInit D_us_80180B1C;
extern EInit g_EInitParticle;
extern u8 g_explosionBigAnim[];

static s16 D_us_80181B34[] = {0, 24, 0, 4, 8, -4, -16, 0};
static s16 D_us_80181B44[] = {0, 24, 12, 0};
static AnimateEntityFrame D_us_80181B4C[] = {
    {.duration = 10, .pose = 0x01},
    {.duration = 7, .pose = 0x02},
    {.duration = 10, .pose = 0x03},
    {.duration = 6, .pose = 0x04},
    {.duration = 7, .pose = 0x05},
    {.duration = 8, .pose = 0x04},
    POSE_LOOP(0)};
static AnimateEntityFrame D_us_80181B5C[] = {
    {.duration = 10, .pose = 0x03},
    {.duration = 5, .pose = 0x02},
    {.duration = 7, .pose = 0x01},
    {.duration = 4, .pose = 0x04},
    {.duration = 5, .pose = 0x05},
    {.duration = 6, .pose = 0x04},
    POSE_LOOP(0)};
static AnimateEntityFrame D_us_80181B6C[] = {
    {.duration = 2, .pose = 0x09},  {.duration = 2, .pose = 0x0A},
    {.duration = 2, .pose = 0x0B},  {.duration = 2, .pose = 0x0C},
    {.duration = 2, .pose = 0x0D},  {.duration = 8, .pose = 0x0E},
    {.duration = 1, .pose = 0x0F},  {.duration = 1, .pose = 0x10},
    {.duration = 1, .pose = 0x11},  {.duration = 1, .pose = 0x12},
    {.duration = 1, .pose = 0x13},  {.duration = 1, .pose = 0x14},
    {.duration = 2, .pose = 0x15},  {.duration = 8, .pose = 0x14},
    {.duration = 48, .pose = 0x15}, {.duration = 8, .pose = 0x13},
    {.duration = 8, .pose = 0x12},  POSE_END};
static AnimateEntityFrame D_us_80181B90[] = {
    {.duration = 3, .pose = 0x09},
    {.duration = 3, .pose = 0x0A},
    {.duration = 2, .pose = 0x0B},
    {.duration = 2, .pose = 0x0C},
    {.duration = 2, .pose = 0x0D},
    {.duration = 9, .pose = 0x0E},
    {.duration = 2, .pose = 0x16},
    {.duration = 2, .pose = 0x17},
    {.duration = 2, .pose = 0x18},
    {.duration = 4, .pose = 0x19},
    {.duration = 2, .pose = 0x1A},
    {.duration = 5, .pose = 0x0E},
    {.duration = 1, .pose = 0x1B},
    {.duration = 1, .pose = 0x1C},
    {.duration = 1, .pose = 0x1D},
    {.duration = 1, .pose = 0x1E},
    {.duration = 1, .pose = 0x1F},
    {.duration = 1, .pose = 0x20},
    {.duration = 1, .pose = 0x21},
    {.duration = 2, .pose = 0x22},
    {.duration = 5, .pose = 0x14},
    {.duration = 28, .pose = 0x15},
    {.duration = 8, .pose = 0x13},
    {.duration = 8, .pose = 0x12},
    POSE_END};
static AnimateEntityFrame D_us_80181BC4[] = {
    {.duration = 1, .pose = 0x0A},  {.duration = 1, .pose = 0x24},
    {.duration = 1, .pose = 0x25},  {.duration = 1, .pose = 0x26},
    {.duration = 1, .pose = 0x27},  {.duration = 1, .pose = 0x28},
    {.duration = 1, .pose = 0x29},  {.duration = 1, .pose = 0x2A},
    {.duration = 3, .pose = 0x37},  {.duration = 3, .pose = 0x38},
    {.duration = 3, .pose = 0x39},  {.duration = 31, .pose = 0x2B},
    {.duration = 1, .pose = 0x2A},  {.duration = 1, .pose = 0x29},
    {.duration = 1, .pose = 0x28},  {.duration = 1, .pose = 0x27},
    {.duration = 12, .pose = 0x26}, {.duration = 1, .pose = 0x25},
    {.duration = 1, .pose = 0x24},  POSE_END};
static AnimateEntityFrame D_us_80181BEC[] = {
    {.duration = 1, .pose = 0x2D},
    {.duration = 2, .pose = 0x2E},
    {.duration = 8, .pose = 0x2F},
    {.duration = 8, .pose = 0x30},
    {.duration = 8, .pose = 0x31},
    {.duration = 1, .pose = 0x2D},
    POSE_END};

// These do not look like obvious animation data
static u8 unused_1[] = {0x08, 0x00, 0x00, 0x00};
static u8 unused_2[] = {0x32, 0x00, 0x00, 0x00};
static u8 unused_3[] = {0x08, 0x00, 0x00, 0x00};
static u8 unused_4[] = {0x33, 0x00, 0x00, 0x00};
static u8 unused_5[] = {0x30, 0x00, 0x00, 0x00};
static u8 unused_6[] = {0x2D, 0x00, 0x00, 0x00};
static u8 unused_7[] = {0xFF, 0x00, 0x00, 0x00};

static AnimateEntityFrame D_us_80181C18[] = {
    {.duration = 1, .pose = 0x0A},
    {.duration = 2, .pose = 0x25},
    {.duration = 8, .pose = 0x26},
    {.duration = 6, .pose = 0x25},
    {.duration = 6, .pose = 0x24},
    {.duration = 6, .pose = 0x0A},
    POSE_END};
static AnimateEntityFrame D_us_80181C28[] = {
    {.duration = 6, .pose = 0x2D},  {.duration = 2, .pose = 0x2E},
    {.duration = 3, .pose = 0x35},  {.duration = 8, .pose = 0x36},
    {.duration = 3, .pose = 0x35},  {.duration = 2, .pose = 0x2E},
    {.duration = 64, .pose = 0x2D}, POSE_END};
static AnimateEntityFrame D_us_80181C38[] = {
    {.duration = 5, .pose = 0x06},
    {.duration = 5, .pose = 0x07},
    {.duration = 5, .pose = 0x08},
    POSE_LOOP(0)};
static AnimateEntityFrame D_us_80181C40[] = {
    {.duration = 1, .pose = 0x09},
    {.duration = 2, .pose = 0x0A},
    {.duration = 3, .pose = 0x0B},
    {.duration = 3, .pose = 0x0C},
    {.duration = 3, .pose = 0x0D},
    {.duration = 3, .pose = 0x0F},
    {.duration = 8, .pose = 0x05},
    {.duration = 8, .pose = 0x04},
    POSE_END};
static AnimateEntityFrame D_us_80181C54[] = {
    {.duration = 6, .pose = 0x04}, {.duration = 6, .pose = 0x05}, POSE_LOOP(0)};

// { hitboxOffX, hitboxOffY, hitboxWidth, hitboxHeight }
static s8 hitbox_dimensions[][4] = {
    {0, 0, 0, 0},     {-1, 2, 4, 23}, {3, 3, 8, 21},    {1, -5, 6, 17},
    {4, 3, 8, 21},    {1, 7, 8, 16},  {3, 6, 15, 8},    {-1, 15, 22, 6},
    {-56, -40, 0, 0}, {2, 2, 4, 21},  {-1, -3, 9, 9},   {-1, -13, 5, 20},
    {-3, -7, 14, 7},  {0, -3, 9, 9},  {-60, -32, 0, 0}, {0, -1, 8, 15}};

// This is indexed off the current animation frame
static u8 hitbox_indices[] = {
    0, 1, 1, 1, 2, 2, 3, 3,  3,  2,  2,  2,  2,  2, 2,  2, 2, 2, 4, 2,
    2, 2, 2, 2, 2, 2, 2, 2,  2,  2,  2,  2,  2,  2, 2,  2, 2, 5, 5, 5,
    6, 6, 7, 7, 8, 9, 9, 10, 11, 12, 13, 13, 14, 2, 15, 7, 7, 7};

// { hitboxOffX, hitboxOffY, hitboxWidth, hitboxHeight }
static s16 D_us_80181CD8[][4] = {
    {0x0000, 0x0000, 0x0000, 0x0000},
    {0xFFFC, 0x0010, 0x0016, 0x0006},
    {0xFFEC, 0xFFFF, 0x0011, 0x0012},
    {0xFFEC, 0xFFFF, 0x0011, 0x0012}};

// { hitboxOffX, hitboxOffY, hitboxWidth, hitboxHeight }
static s16 D_us_80181CF8[][4] = {
    {0x0000, 0x0000, 0x0000, 0x0000},
    {0xFFFB, 0xFFFC, 0x0008, 0x000B},
    {0xFFFB, 0xFFFC, 0x0008, 0x000B},
    {0xFFF9, 0xFFF7, 0x000C, 0x0012}};
static Point32 D_us_80181D18[] = {
    {.x = FIX(2.0), .y = FIX(-4.5)}, {.x = FIX(1.0), .y = FIX(-4)}};

static void func_us_801C375C(void) {
    Entity* player;
    s32 posX;

    g_CurrentEntity->facingLeft = (GetSideToPlayer() & 1) ^ 1;
    player = &PLAYER;
    posX = g_CurrentEntity->posX.i.hi - player->posX.i.hi;
    if (g_CurrentEntity->facingLeft) {
        posX = -posX;
    }

    if (posX < 0x71) {
        if (player->facingLeft == g_CurrentEntity->facingLeft) {
            if (player->step == 1) {
                g_CurrentEntity->ext.bladeMaster.unk82 += 1;
            } else {
                g_CurrentEntity->ext.bladeMaster.unk82 = 0;
            }
        } else {
            g_CurrentEntity->ext.bladeMaster.unk82 = 0;
        }

        if (g_CurrentEntity->ext.bladeMaster.unk82 > 2) {
            SetStep(13);
            g_CurrentEntity->ext.bladeMaster.unk82 = 0;
            return;
        }

        if (posX < 0x2C) {
            SetStep(9);
        }
    }
}

void EntityBladeMaster(Entity* self) {
    Entity* entity;
    s32 i;
    Entity* player;
    s8* ptr;
    s32 posX;
    s32 animResult;

    FntPrint("BLADES_STEP %x\n", self->step);
    FntPrint("check %x\n", self->ext.bladeMaster.unk82);

    if (self->flags & FLAG_DEAD) {
        self->hitboxState = 0;
        entity = self + 1;
        DestroyEntity(entity);
        SetStep(15);
    }

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitBladeMaster);
        entity = self + 1;
        CreateEntityFromCurrentEntity(E_UNK_23, entity);
        break;
    case 1:
        if (UnkCollisionFunc3(D_us_80181B34) & 1) {
            SetStep(2);
        }
        break;
    case 2:
        self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        AnimateEntity(D_us_80181C54, self);
        if (GetDistanceToPlayerX() < 0x80) {
            SetStep(3);
        }
        break;
    case 3:
        if (!self->step_s) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            self->ext.bladeMaster.unk84 = 2;
            self->step_s++;

            if (self->facingLeft) {
                self->velocityX = FIX(1.5);
            } else {
                self->velocityX = FIX(-1.5);
            }
        }
        animResult = AnimateEntity(D_us_80181B4C, self);
        if (self->pose < 4) {
            UnkCollisionFunc2(D_us_80181B44);
        }
        if (!animResult) {
            self->ext.bladeMaster.unk84--;
        }

        if (!self->ext.bladeMaster.unk84) {
            SetStep(4);
        }

        func_us_801C375C();
        break;
    case 4:
        if (!self->step_s) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            self->ext.bladeMaster.unk84 = 1;
            self->step_s++;

            if (self->facingLeft) {
                self->velocityX = FIX(-1.5);
            } else {
                self->velocityX = FIX(1.5);
            }
        }
        if (!AnimateEntity(D_us_80181B5C, self)) {
            self->ext.bladeMaster.unk84--;
        }

        if (self->pose < 4) {
            UnkCollisionFunc2(D_us_80181B44);
        }

        if (!self->ext.bladeMaster.unk84) {
            SetStep(3);
        }

        func_us_801C375C();
        break;
    case 9:
        if (!AnimateEntity(D_us_80181B90, self)) {
            SetStep(4);
        }

        if (!self->poseTimer && self->pose == 0xB) {
            PlaySfxPositional(SFX_WHIP_TWIRL_SWISH);
        }

        break;
    case 13:
        self->animCurFrame = 0xA;
        player = &PLAYER;
        if (player->facingLeft == self->facingLeft) {
            if (player->step == 1) {
                self->ext.bladeMaster.unk82++;
            }
        } else {
            self->ext.bladeMaster.unk82 = 0;
            SetStep(8);
            break;
        }

        if (self->ext.bladeMaster.unk82 > 0x18) {
            self->ext.bladeMaster.unk82 = 0;
            SetStep(5);
        }

        if (PLAYER.step_s & 0x40) {
            if (PLAYER.step == 2) {
                SetStep(6);
            } else {
                SetStep(7);
            }
        }
        break;
    case 5:
        switch (self->step_s) {
        case 0:
            if (self->facingLeft) {
                self->velocityX = FIX(2.0);
            } else {
                self->velocityX = FIX(-2.0);
            }
            self->velocityY = FIX(-7.0);
            self->animCurFrame = 0x2D;
            self->step_s++;
            break;
        case 1:
            if (self->velocityY > FIX(-1.0)) {
                AnimateEntity(D_us_80181BEC, self);
            }

            if (UnkCollisionFunc3(D_us_80181B34) & 1) {
                PlaySfxPositional(SFX_STOMP_HARD_B);
                SetStep(0xB);
            }
            break;
        }
        break;
    case 11:
        if (!AnimateEntity(D_us_80181C18, self)) {
            SetStep(4);
        }
        break;
    case 7:
        switch (self->step_s) {
        case 0:
            if (self->facingLeft) {
                self->velocityX = FIX(4.0);
            } else {
                self->velocityX = FIX(-4.0);
            }

            PlaySfxPositional(SFX_SCRAPE_B);
            self->step_s++;
            // fallthrough
        case 1:
            AnimateEntity(D_us_80181BC4, self);
            UnkCollisionFunc2(D_us_80181B44);
            self->velocityX -= self->velocityX / 32;
            if (abs(self->velocityX) < 0x6000) {
                SetStep(4);
            }
            break;
        }
        break;
    case 6:
        switch (self->step_s) {
        case 0:
            if (self->facingLeft) {
                self->velocityX = FIX(1.5);
            } else {
                self->velocityX = FIX(-1.5);
            }
            self->velocityY = FIX(-5.0);
            self->step_s++;
            break;
        case 1:
            AnimateEntity(D_us_80181C28, self);
            if (UnkCollisionFunc3(D_us_80181B34) & 1) {
                PlaySfxPositional(SFX_STOMP_HARD_C);
                SetStep(0xB);
            }
            break;
        }
        break;
    case 8:
        switch (self->step_s) {
        case 0:
            if (self->facingLeft) {
                self->velocityX = FIX(2.5);
            } else {
                self->velocityX = FIX(-2.5);
            }
            self->velocityY = 0;
            PlaySfxPositional(SFX_QUIET_STEPS);
            self->step_s++;
            // fallthrough
        case 1:
            UnkCollisionFunc2(D_us_80181B44);
            AnimateEntity(D_us_80181C38, self);
            player = &PLAYER;
            if (self->facingLeft == player->facingLeft) {
                SetStep(5);
            } else {
                posX = self->posX.i.hi - player->posX.i.hi;
                if (self->facingLeft) {
                    posX = -posX;
                }

                if (posX < 0) {
                    SetStep(12);
                } else if (posX < 0x30) {
                    SetStep(10);
                }
            }
            break;
        }
        break;
    case 12:
        if (!AnimateEntity(D_us_80181C40, self)) {
            SetStep(4);
        }

        UnkCollisionFunc2(D_us_80181B44);
        self->velocityX -= self->velocityX / 8;
        break;
    case 10:
        if (!self->step_s) {
            entity = self + 1;
            entity->ext.bladeMaster.unk85 = 1;
            self->step_s++;
        }
        if (!AnimateEntity(D_us_80181B6C, self)) {
            SetStep(4);
        }

        if (!self->poseTimer && self->pose == 7) {
            PlaySfxPositional(SFX_BONE_THROW);
        }

        if (self->animCurFrame == 0x15) {
            entity = self + 1;
            entity->ext.bladeMaster.unk85 = 0;
        }

        UnkCollisionFunc2(D_us_80181B44);
        self->velocityX -= self->velocityX / 16;
        break;
    case 15:
        for (i = 0; i < 2; i++) {
            entity =
                AllocEntity(&g_Entities[224], &g_Entities[TOTAL_ENTITY_COUNT]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_UNK_24, self, entity);
                entity->facingLeft = self->facingLeft;
                entity->params = i;
            }
        }
        PlaySfxPositional(SFX_SKELETON_DEATH_B);
        DestroyEntity(self);
        // NOTE: This skips the final hitbox code outside the switch!
        return;
    case 255: // TODO: pad2_anim_debug
        FntPrint("charal %x\n", self->animCurFrame);
        if (g_pads[1].pressed & PAD_SQUARE) {
            if (self->params) {
                break;
            }
            self->animCurFrame++;
            self->params |= 1;
        } else {
            self->params = 0;
        }
#ifdef BUTTON_SYMBOL
        if (g_pads[1].pressed & BUTTON_SYMBOL) {
#else
        if (g_pads[1].pressed & PAD_CIRCLE) {
#endif
            if (self->step_s) {
                break;
            }
            self->animCurFrame--;
            self->step_s |= 1;
        } else {
            self->step_s = 0;
        }
        break;
    }

    i = hitbox_indices[self->animCurFrame];
    ptr = hitbox_dimensions[i];
    self->hitboxOffX = *ptr++;
    self->hitboxOffY = *ptr++;
    self->hitboxWidth = *ptr++;
    self->hitboxHeight = *ptr++;
}

void func_us_801C41EC(Entity* self) {
    s32 parentAnimFrame;
    s16* ptr;
    Entity* parent;

    if (!self->step) {
        InitializeEntity(D_us_80180B1C);
    }

    parent = self - 1;
    self->posX.val = parent->posX.val;
    self->posY.val = parent->posY.val;
    self->facingLeft = parent->facingLeft;
    parentAnimFrame = parent->animCurFrame;
    if (self->ext.bladeMaster.unk85) {
        parentAnimFrame -= 0x10;
        if (parentAnimFrame < 0) {
            parentAnimFrame = 0;
        }
        if (parentAnimFrame > 3) {
            parentAnimFrame = 0;
        }
        ptr = *D_us_80181CF8;
    } else {
        parentAnimFrame -= 0x1D;
        if (parentAnimFrame < 0) {
            parentAnimFrame = 0;
        }

        if (parentAnimFrame > 3) {
            parentAnimFrame = 0;
        }
        ptr = *D_us_80181CD8;
    }

    ptr = &ptr[parentAnimFrame * 4];
    self->hitboxOffX = *ptr++;
    self->hitboxOffY = *ptr++;
    self->hitboxWidth = *ptr++;
    self->hitboxHeight = *ptr++;
    if (parent->entityId != 0x22) {
        DestroyEntity(self);
    }
}

void func_us_801C4300(Entity* self) {
    Collider collider;
    Entity* newEntity;
    s32 posX;
    s32 posY;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitBladeMaster);
        self->hitboxState = 0;
        self->flags |=
            FLAG_DESTROY_IF_OUT_OF_CAMERA | FLAG_UNK_00200000 | FLAG_UNK_2000;
        if (self->params) {
            self->animCurFrame = 0x2C;
        } else {
            self->animCurFrame = 0x34;
        }
        self->velocityX = D_us_80181D18[self->params].x;
        self->velocityY = D_us_80181D18[self->params].y;
        if ((GetSideToPlayer() & 1) ^ 1) {
            self->velocityX = -self->velocityX;
        }
        self->step += self->params;
        break;
    case 1:
        if (!self->step_s) {
            self->ext.bladeMaster.unk80 = 0x18;
            self->step_s++;
        }
        MoveEntity();
        self->velocityY += FIX(0.1875);
        if (!--self->ext.bladeMaster.unk80) {
            newEntity =
                AllocEntity(&g_Entities[224], &g_Entities[TOTAL_ENTITY_COUNT]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(E_EXPLOSION, self, newEntity);
                newEntity->params = 1;
            }
            DestroyEntity(self);
        }
        break;
    case 2:
        MoveEntity();
        self->velocityY += FIX(0.21875);
        posX = self->posX.i.hi;
        posY = self->posY.i.hi + 0x10;
        g_api.CheckCollision(posX, posY, &collider, 0);
        if (collider.effects & EFFECT_SOLID) {
            self->animCurFrame = 0;
            self->posY.i.hi += 0x10;
            self->ext.bladeMaster.unk80 = 0x60;
            self->step++;
        }
        break;
    case 3:
        if (!(self->ext.bladeMaster.unk80 & 0xF)) {
            newEntity =
                AllocEntity(&g_Entities[224], &g_Entities[TOTAL_ENTITY_COUNT]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(E_UNK_25, self, newEntity);
                newEntity->zPriority = self->zPriority + 1;
            }
        }

        if (!(self->ext.bladeMaster.unk80 & 7)) {
            if (Random() & 1) {
                PlaySfxPositional(SFX_EXPLODE_E);
            } else {
                PlaySfxPositional(SFX_EXPLODE_F);
            }
        }

        if (!--self->ext.bladeMaster.unk80) {
            DestroyEntity(self);
        }
        break;
    }
}

void func_us_801C45B0(Entity* self) {
    if (!self->step) {
        InitializeEntity(g_EInitParticle);
        self->pose = 0;
        self->poseTimer = 0;
        self->animSet = 2;
        self->drawMode = DRAW_TPAGE2 | DRAW_TPAGE;
        self->velocityY = FIX(-3.0);
        return;
    }

    self->posY.val += self->velocityY;
    if (!AnimateEntity(g_explosionBigAnim, self)) {
        DestroyEntity(self);
    }
}
