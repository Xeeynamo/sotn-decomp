// SPDX-License-Identifier: AGPL-3.0-or-later
static u16 D_us_80181C1C[] = {0, 8, 0, 6, 8, -6, -16, 0};
static u16 D_us_80181C2C[] = {0, 31, 8, 0, 0, 16, 255, 0}; // unused
static u8 anim_owl_1[] = {64, 1, 12, 2, 12, 3, 12, 2, 0, 0};
static u8 anim_owl_2[] = {
    4, 1, 4, 2, 4, 3, 8, 7, 8, 4, 8, 5, 8, 6, 8, 7, 8, 3, 8, 2, 4, 1, -1, 0,
};
static u8 anim_owl_3[] = {4, 7, 4, 4, 4, 5, 4, 6, 4, 7, 4, 3, 0, 0};
static u8 anim_owl_4[] = {
    4, 1, 4, 2, 4, 3, 8, 7, 8, 4, 8, 5, 8, 6, 8, 7, -1, 0,
};
static u8 anim_owl_5[] = {8, 4, 8, 5, 8, 6, 8, 7, 0, 0};
static u8 anim_owl_6[] = {2, 4, 2, 5, 2, 6, 2, 7, 0, 0};
static u8 anim_owl_7[] = {8, 8, 8, 9, 8, 10, 8, 11, 0, 0};

void EntityOwl(Entity* self) {
#define KNIGHT (self + 1)
// Invisible target entity
#define TARGET (self + 3)

    Collider collider;
    Entity* tempEntity;
    s16 dx, dy;
    s16 angle;

    if (self->step > 1 && self->step < 9 && (g_Timer & 0xF) == 0) {
        PlaySfxPositional(SFX_WING_FLAP_A);
    }
    if (self->ext.owl.unk80 & 0x20) {
        if (!(self->flags & FLAG_DEAD)) {
            SetStep(8);
            self->ext.owl.unk80 ^= 0x20;
        }
    }
    if (self->flags & FLAG_DEAD) {
        if (self->step < 9) {
            self->hitboxState = 0;
            self->animCurFrame = 12;
            self->velocityX = 0;
            self->velocityY = 0;
            PlaySfxPositional(SFX_OWL_DEATH);
            SetStep(9);
            KNIGHT->ext.owl.unk80 |= 8;
        }
    }
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitOwl);
        // Turns out the knight is spawned from the owl. Neat!
        CreateEntityFromEntity(E_OWL_KNIGHT, self, KNIGHT);
        CreateEntityFromEntity(E_OWL_TARGET, self, TARGET);
        break;
    case 1:
        AnimateEntity(anim_owl_1, self);
        tempEntity = KNIGHT;
        self->posX.i.hi = tempEntity->posX.i.hi;
        if (self->facingLeft) {
            self->posX.i.hi -= 10;
        } else {
            self->posX.i.hi += 10;
        }
        if (tempEntity->animCurFrame == 0x10) {
            self->posY.i.hi = tempEntity->posY.i.hi - 0x21;
        } else {
            self->posY.i.hi = tempEntity->posY.i.hi - 0x20;
        }
        if (tempEntity->hitParams) {
            SetStep(2);
        }
        if (self->ext.owl.unk80 & 1) {
            self->ext.owl.unk80 ^= 1;
            SetStep(3);
        }
        break;
    case 2:
        if (!AnimateEntity(anim_owl_2, self)) {
            SetStep(1);
        }
        break;
    case 3:
        if (!AnimateEntity(anim_owl_4, self)) {
            KNIGHT->ext.owl.unk80 |= 2;
            SetStep(4);
        }
        MoveEntity();
        if (self->pose == 6) {
            self->velocityY -= FIX(12.0 / 128);
        }
        if (self->pose >= 7) {
            self->velocityY += FIX(8.0 / 128);
        }
        break;
    case 4:
        MoveEntity();
        self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        AnimateEntity(anim_owl_5, self);
        dx = KNIGHT->posX.i.hi - self->posX.i.hi;
        dy = KNIGHT->posY.i.hi - self->posY.i.hi;
        if (KNIGHT->facingLeft) {
            dx -= 0x20;
        } else {
            dx += 0x20;
        }
        dy -= 0x40;
        switch (self->step_s) {
        case 0:
            dx = self->velocityX / 16;
            dy = self->velocityY / 16;
            self->ext.owl.unk84 = Ratan2Shifted(dx, dy);
            self->step_s++;
            break;
        case 1:
            TARGET->posX.i.hi = dx + self->posX.i.hi;
            TARGET->posY.i.hi = dy + self->posY.i.hi;
            angle = GetAngleBetweenEntitiesShifted(self, TARGET);
            self->ext.owl.unk84 =
                AdjustValueWithinThreshold(6, self->ext.owl.unk84, angle);
            SetEntityVelocityFromAngle(self->ext.owl.unk84, 0x20);
            if (self->velocityX > 0) {
                self->facingLeft = 1;
            } else {
                self->facingLeft = 0;
            }
            dx = abs(dx);
            dy = abs(dy);
            if (dx < 0x10 && dy < 0x10) {
                self->ext.owl.unk88 = 0x20;
                self->step_s++;
            }
            break;
        case 2:
            dx = abs(dx);
            dy = abs(dy);
            SetEntityVelocityFromAngle(
                self->ext.owl.unk84, self->ext.owl.unk88);
            self->ext.owl.unk88--;
            if (self->ext.owl.unk88 < 0) {
                self->ext.owl.unk88 = 0;
            }
            if (dx > 0x28 || dy > 0x28) {
                self->step_s--;
            }
            break;
        }
        if (self->ext.owl.unk80 & 8) {
            SetStep(6);
        }
        if (self->ext.owl.unk80 & 2) {
            SetStep(5);
            self->ext.owl.unk80 ^= 2;
        }
        if (self->ext.owl.unk80 & 4) {
            SetStep(7);
            self->ext.owl.unk80 ^= 4;
        }
        break;
    case 5:
        AnimateEntity(anim_owl_7, self);
        MoveEntity();
        switch (self->step_s) {
        case 0:
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            tempEntity = &PLAYER;
            dx = tempEntity->posX.i.hi - self->posX.i.hi;
            dy = tempEntity->posY.i.hi - self->posY.i.hi;
            dy -= 0x10;
            angle = ratan2(-dy, dx);
            self->velocityX = rcos(angle) * 0x30;
            self->velocityY = -rsin(angle) * 0x30;
            self->ext.owl.unk82 = 0x60;
            PlaySfxPositional(SFX_WEAPON_SWISH_C);
            self->step_s++;
            break;
        case 1:
            if (self->ext.owl.unk82 < 0x30) {
                self->velocityY -= FIX(0.09375);
            }
            if (!--self->ext.owl.unk82) {
                self->step_s++;
            }
            break;
        case 2:
            if (self->ext.owl.unk80 & 8) {
                SetStep(6);
            } else {
                KNIGHT->ext.owl.unk80 |= 2;
                SetStep(4);
            }
        }
        break;
    case 7:
        switch (self->step_s) {
        case 0:
            if (!AnimateEntity(anim_owl_5, self)) {
                self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            }
            MoveEntity();
            self->velocityY = FIX(-1.5);
            if (self->facingLeft) {
                self->velocityX = FIX(16.0 / 128);
            } else {
                self->velocityX = FIX(-16.0 / 128);
            }
            if (self->posY.i.hi < 0x30) {
                PlaySfxPositional(SFX_WEAPON_SWISH_C);
                self->step_s++;
            }
            break;
        case 1:
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            tempEntity = &PLAYER;
            dx = tempEntity->posX.i.hi - self->posX.i.hi;
            dy = tempEntity->posY.i.hi - self->posY.i.hi;
            angle = ratan2(-dy, dx);
            self->velocityX = rcos(angle) * 0x40;
            self->velocityY = -rsin(angle) * 0x40;
            self->animCurFrame = 4;
            self->pose = 0;
            self->poseTimer = 0;
            PlaySfxPositional(SFX_WEAPON_SWISH_C);
            self->step_s++;
            break;
        case 2:
            MoveEntity();
            if (self->posY.i.hi > 0x90) {
                self->step_s++;
            }
            break;
        case 3:
            AnimateEntity(anim_owl_6, self);
            MoveEntity();
            self->velocityY -= FIX(28.0 / 128);
            if (self->velocityY < FIX(-2)) {
                self->pose = 0;
                self->poseTimer = 0;
                self->step_s++;
            }
            break;
        case 4:
            AnimateEntity(anim_owl_5, self);
            MoveEntity();
            if (self->posY.i.hi < 0x60) {
                if (self->ext.owl.unk80 & 8) {
                    SetStep(6);
                } else {
                    KNIGHT->ext.owl.unk80 |= 2;
                    SetStep(4);
                }
                if (self->ext.owl.unk80 & 0x40) {
                    SetStep(7);
                }
            }
            break;
        }
        break;
    case 6:
        switch (self->step_s) {
        case 0:
            dx = KNIGHT->posX.i.hi - self->posX.i.hi;
            dy = KNIGHT->posY.i.hi - self->posY.i.hi;
            dy -= 0x40;
            angle = ratan2(-dy, dx);
            self->velocityX = rcos(angle) * 0x28;
            self->velocityY = -rsin(angle) * 0x28;
            if (self->velocityX > 0) {
                self->facingLeft = 1;
            } else {
                self->facingLeft = 0;
            }
            self->step_s++;
            break;
        case 1:
            AnimateEntity(anim_owl_7, self);
            MoveEntity();
            dx = KNIGHT->posX.i.hi - self->posX.i.hi;
            if (abs(dx) < 8) {
                self->ext.owl.unk84 = 0x400;
                self->step_s++;
            }
            break;
        case 2:
            AnimateEntity(anim_owl_5, self);
            MoveEntity();
            if (KNIGHT->facingLeft) {
                TARGET->posX.i.hi = KNIGHT->posX.i.hi - 10;
            } else {
                TARGET->posX.i.hi = KNIGHT->posX.i.hi + 10;
            }
            TARGET->posY.i.hi = KNIGHT->posY.i.hi - 0x20;
            angle = GetAngleBetweenEntitiesShifted(self, TARGET);
            self->ext.owl.unk84 =
                AdjustValueWithinThreshold(4, self->ext.owl.unk84, angle);
            SetEntityVelocityFromAngle(self->ext.owl.unk84, 0x10);
            dx = TARGET->posX.i.hi - self->posX.i.hi;
            dy = TARGET->posY.i.hi - self->posY.i.hi;
            if (dx > 0) {
                self->facingLeft = 1;
            } else {
                self->facingLeft = 0;
            }
            dx = abs(dx);
            dy = abs(dy);
            if (dx < 6 && dy < 6) {
                SetStep(1);
                self->velocityX = 0;
                self->velocityY = 0;
                self->facingLeft = KNIGHT->facingLeft;
                self->ext.owl.unk80 = 0;
                KNIGHT->ext.owl.unk80 = 1;
            }
            break;
        }
        break;
    case 8:
        switch (self->step_s) {
        case 0:
            dx = KNIGHT->posX.i.hi - self->posX.i.hi;
            dy = KNIGHT->posY.i.hi - self->posY.i.hi;
            if (KNIGHT->facingLeft) {
                dx += 0x20;
            } else {
                dx -= 0x20;
            }
            dy += 26;
            angle = ratan2(-dy, dx);
            self->velocityX = rcos(angle) * 0x30;
            self->velocityY = -rsin(angle) * 0x30;
            if (self->velocityX > 0) {
                self->facingLeft = 1;
            } else {
                self->facingLeft = 0;
            }
            PlaySfxPositional(SFX_WEAPON_SWISH_C);
            self->step_s++;
            break;
        case 1:
            MoveEntity();
            AnimateEntity(anim_owl_5, self);
            dy = KNIGHT->posY.i.hi - self->posY.i.hi;
            if (dy < 0x41) {
                dx = self->posX.i.hi;
                dy = self->posY.i.hi + 0x10;
                g_api.CheckCollision(dx, dy, &collider, 0);
                if (collider.effects & EFFECT_SOLID) {
                    self->posY.i.hi += collider.unk18;
                    self->step_s++;
                    if (KNIGHT->posX.i.hi > self->posX.i.hi) {
                        self->facingLeft = 1;
                    } else {
                        self->facingLeft = 0;
                    }
                }
            }
            break;
        case 2:
            AnimateEntity(anim_owl_3, self);
            if ((g_Timer & 7) == 7) {
                PlaySfxPositional(SFX_BONE_SWORD_SWISH_B);
            }
            if (self->ext.owl.unk80 & 0x40) {
                SetStep(7);
            }
            break;
        }
        break;
    case 9:
        switch (self->step_s) {
        case 0:
            if (UnkCollisionFunc3(D_us_80181C1C) & 1) {
                PlaySfxPositional(SFX_STOMP_HARD_B);
                self->animCurFrame = 0xD;
                if (self->posX.i.hi > KNIGHT->posX.i.hi) {
                    self->facingLeft = 1;
                } else {
                    self->facingLeft = 0;
                }
                self->step_s++;
                break;
            }
            self->velocityY -= FIX(0.125);
            break;
        case 1:
            if (self->ext.owl.unk80 & 0x10 || self->ext.owl.unk80 & 0x40) {
                self->ext.owl.unk82 = 0x80;
                self->step++;
            }
            break;
        }
        break;
    case 10:
        if (!--self->ext.owl.unk82 || !KNIGHT->entityId) {
            PlaySfxPositional(SFX_QUICK_STUTTER_EXPLODE_B);
            tempEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (tempEntity != NULL) {
                CreateEntityFromEntity(E_EXPLOSION, self, tempEntity);
                tempEntity->params = 2;
            }
            self->animCurFrame = 0;
            self->step = 24;
            KNIGHT->ext.owl.unk80 |= 0x10;
            DestroyEntity(self);
        }
        break;
    case 16:
#include "pad2_anim_debug.h"
    }
}

u8 OwlKnightDeathAnim(void) {
    Primitive* prim;
    s32 primIndex;
    switch (g_CurrentEntity->step_s) {
    case 0:
        g_CurrentEntity->animCurFrame = 0;
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 2);
        // yes this has to be written this way
        if (primIndex != -1) {
            g_CurrentEntity->flags |= FLAG_HAS_PRIMS;
            g_CurrentEntity->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            g_CurrentEntity->ext.owl.unk7C = prim;
            while (prim != NULL) {
                prim->tpage = 0x12;
                prim->clut = g_EInitOwlKnight[3] + 1;
                prim->u0 = 0x48;
                prim->u1 = 0x70;
                prim->u2 = 0x48;
                prim->u3 = 0x70;

                if (g_CurrentEntity->facingLeft) {
                    prim->x0 = g_CurrentEntity->posX.i.hi + 13;
                    prim->x1 = prim->x0 - 40;
                    prim->x2 = prim->x0;
                    prim->x3 = prim->x1;
                } else {
                    prim->x0 = g_CurrentEntity->posX.i.hi - 13;
                    prim->x1 = prim->x0 + 40;
                    prim->x2 = prim->x0;
                    prim->x3 = prim->x1;
                }
                PRED(prim) = 0x80;
                PGRN(prim) = 0x80;
                PBLU(prim) = 0x80;
                prim->priority = g_CurrentEntity->zPriority;
                prim->drawMode = DRAW_UNK_400 | DRAW_COLORS | DRAW_UNK02;
                prim->p2 = 0;
                prim = prim->next;
            }
            prim = g_CurrentEntity->ext.owl.unk7C;
            prim->v0 = 0x80;
            prim->v1 = prim->v0;
            prim->v2 = prim->v0 + 10;
            prim->v3 = prim->v2;
            prim->y0 = g_CurrentEntity->posY.i.hi - 0x10;
            prim->y1 = prim->y0;
            prim->y2 = prim->y0 + 10;
            prim->y3 = prim->y2;
            prim->p2 = 0;
            prim->drawMode |= DRAW_TPAGE2 | DRAW_TPAGE | DRAW_TRANSP;
            prim = prim->next;

            prim->v0 = 0x8A;
            prim->v1 = prim->v0;
            prim->v2 = 0xB0;
            prim->v3 = prim->v2;
            prim->y0 = g_CurrentEntity->posY.i.hi - 6;
            prim->y1 = prim->y0;
            prim->y2 = prim->y0 + 38;
            prim->y3 = prim->y2;
        } else {
            return 1;
        }
        g_CurrentEntity->step_s++;
        break;
    case 1:
        prim = g_CurrentEntity->ext.owl.unk7C;
        PGREY(prim, 0) = 32;
        LOW(prim->r1) = LOW(prim->r0);
        PGREY(prim, 2) = 160;
        LOW(prim->r3) = LOW(prim->r2);
        g_CurrentEntity->step_s++;
        break;
    case 2:
        prim = g_CurrentEntity->ext.owl.unk7C;
        if (g_Timer % 6 == 0) {
            prim->y0++;
            prim->y1 = prim->y0;
        }
        if (g_Timer % 4 == 0) {
            prim->v0++;
            prim->v1 = prim->v0;
            prim->v2++;
            prim->v3 = prim->v2;
            prim->y3++;
            prim->y2 = prim->y3;
            prim->p2++;
            prim = prim->next;
            prim->v0++;
            prim->v1 = prim->v0;
            prim->y0++;
            prim->y1 = prim->y0;
        }
        if (prim->p2 <= 38) {
            break;
        }
        g_CurrentEntity->step_s++;
        break;
    case 3:
        prim = g_CurrentEntity->ext.owl.unk7C;
        if (PrimDecreaseBrightness(prim, 6) == 0) {
            return 1;
        }
    }
    return 0;
}

static u16 D_us_80181CA8[] = {0, 31, 0, 6, 8, -6, -16, 0};
static s16 D_us_80181CB8[] = {0, 31, 8, 0};
static u8 anim_knight_1[] = {26, 16, 26, 17, 0, 0};
static u8 anim_knight_2[] = {4, 16, 6, 18, 36, 19, 70, 20, 4, 57, 4, 16, -1, 0};
static u8 anim_knight_3[] = {24, 16, 4, 57, 32, 18, 52, 19, 70, 16, -1, 0};
static u8 anim_knight_4[] = {
    4, 16, 8, 47, 8, 48, 8, 47, 8, 16, 8, 49, 8, 50, 8, 49, 4, 16, 0, 0,
};
static u8 anim_knight_5[] = {
    4, 16, 8, 49, 8, 50, 8, 49, 8, 16, 8, 47, 8, 48, 8, 47, 4, 16, 0, 0,
};
static u8 anim_knight_6[] = {2, 48, 2, 47, 4, 49, 4, 50, 2, 48, 0, 0};
static u8 anim_knight_7[] = {8, 16, 6, 57, 32, 58, 3, 36, 3, 59, 16, 28, -1, 0};
static u8 anim_knight_8[] = {
    4, 28, 8, 51, 8, 52, 8, 51, 8, 28, 8, 53, 8, 54, 8, 53, 4, 28, 0, 0,
};
static u8 anim_knight_9[] = {
    4, 28, 8, 53, 8, 54, 8, 53, 8, 28, 8, 51, 8, 52, 8, 51, 4, 28, 0, 0,
};
static u8 anim_knight_10[] = {
    8,  28, 6,  29, 8,  30, 34, 27, 1,  26, 1,  25, 1,  31, 70,
    32, 6,  31, 6,  25, 6,  26, 6,  30, 6,  29, 4,  28, -1, 0,
};
static u8 anim_knight_11[] = {
    8, 28, 6, 60, 6, 59, 6, 36, 6, 61, 6, 58, 6, 57, 6, 17, 8, 16, -1, 0,
};
static u8 anim_knight_12[] = {
    16, 30, 8,  35, 8, 36, 40, 37, 2, 38, 2,  39,
    1,  40, 56, 41, 4, 30, 4,  29, 8, 28, -1, 0,
};
static u8 anim_knight_13[] = {
    4, 30, 6, 35, 6, 36, 16, 37, 2, 38, 2, 39, 1, 40, 4, 41, -1, 0,
};
static u8 anim_knight_14[] = {
    16, 16, 6,  21, 6,  22, 6,  23, 56, 24, 3,  25, 3,  26, 44, 27, 1,  26, 1,
    25, 1,  31, 80, 32, 4,  31, 4,  25, 4,  26, 4,  30, 4,  29, 16, 28, -1, 0,
};
static u8 anim_knight_15[] = {
    8, 16, 8,  57, 72, 58, 2, 34, 2,  55, 2,  56,
    1, 40, 72, 41, 8,  30, 8, 29, 16, 28, -1, 0,
};
static u8 anim_knight_16[] = {8, 16, 8, 21, 8, 22, 16, 42, -1, 0};
static u8 anim_knight_17[] = {16, 42, 8, 22, 8, 21, 8, 16, -1, 0};
static s8 D_us_80181E08[] = {
    0, 0, 0, 0,  1, 3, 4, 28, 1, 7, 4, 24, 2, 7,  4,  24,
    3, 9, 4, 22, 2, 8, 4, 23, 2, 3, 4, 27, 0, 14, 12, 16,
};
static u8 D_us_80181E28[] = {
    0,  8,  8, 8,  8, 8, 9,  9,  10, 9,  10, 10, 10, 8, 10, 10, 10, 11,
    10, 12, 9, 13, 8, 8, 9,  10, 10, 14, 9,  10, 9,  9, 8,  8,  8,  8,
    8,  8,  8, 8,  8, 9, 13, 8,  9,  10, 8,  9,  11, 8, 8,  10,
};
static s16 D_us_80181E5C[] = {0x40, 0x60, 0x80, 0xA0};

void EntityOwlKnight(Entity* self) {
// Owl is in previous slot (see KNIGHT above)
#define OWL (self - 1)
#define SWORD (self + 1)

    Entity* tempEntity;
    s16 dx;
    u8 miscTemp;
    s8* hitboxPtr;
    s16 dx_2;
    s32 index;

    if (self->ext.owl.unk80 & 8) {
        if (!(self->flags & FLAG_DEAD)) {
            SetStep(13);
            self->ext.owl.unk80 ^= 8;
        }
    }
    if (self->flags & FLAG_DEAD) {
        if (self->step < 17) {
            tempEntity = SWORD;
            DestroyEntity(tempEntity);
            OWL->ext.owl.unk80 |= 0x20;
            self->hitboxState = 0;
            self->ext.owl.unk82 = 0x60;
            PlaySfxPositional(SFX_OWL_KNIGHT_DEATH);
            SetStep(17);
        }
    }
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitOwlKnight);
        CreateEntityFromEntity(E_OWL_KNIGHT_SWORD, self, SWORD);
        self->hitboxOffX = -1;
        self->zPriority -= 2;
        self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        OWL->facingLeft = self->facingLeft;
        break;
    case 1:
        if (UnkCollisionFunc3(D_us_80181CA8) & 1) {
            SetStep(2);
        }
        break;
    case 2:
        AnimateEntity(anim_knight_1, self);
        self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        OWL->facingLeft = self->facingLeft;
        switch (self->step_s) {
        case 0:
            dx = GetDistanceToPlayerX();
            if ((dx < 0x68) && (GetDistanceToPlayerY() < 0x80)) {
                OWL->ext.owl.unk80 |= 1;
                self->step_s++;
            }
            break;
        case 1:
            if (self->ext.owl.unk80 & 2) {
                self->ext.owl.unk80 ^= 2;
                SetStep(3);
            }
        }
        break;
    case 3:
        if (!AnimateEntity(anim_knight_2, self)) {
            SetStep(12);
        }
        if (!self->step_s && self->pose == 4) {
            tempEntity = &PLAYER;
            dx = OWL->posX.i.hi - tempEntity->posX.i.hi;
            if (dx < 0) {
                dx = -dx;
            }
            if (dx > 0x50) {
                OWL->ext.owl.unk80 |= 2;
            } else {
                OWL->ext.owl.unk80 |= 4;
            }
            PlaySfxPositional(SFX_OWL_KNIGHT_TAUNT);
            self->step_s++;
        }
        break;
    case 12:
        dx = GetDistanceToPlayerX();
        self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        if (dx < 0x40) {
            SetStep(4);
        } else {
            SetStep(11);
        }
        break;
    case 4:
        if (!self->step_s) {
            PlaySfxPositional(SFX_WEAPON_SWISH_A);
            self->step_s++;
        }
        if (!AnimateEntity(anim_knight_7, self)) {
            dx = GetDistanceToPlayerX();
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            if (dx > 0x50) {
                SetStep(10);
            } else {
                SetStep(8);
            }
        }
        break;
    case 5:
        if (!self->step_s) {
            PlaySfxPositional(SFX_WEAPON_SWISH_A);
            self->step_s++;
        }
        if (!AnimateEntity(anim_knight_11, self)) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            dx = GetDistanceToPlayerX();
            if (dx > 0x90) {
                OWL->ext.owl.unk80 |= 8;
                SetStep(6);
            } else {
                if (self->ext.owl.unk80 & 2) {
                    self->ext.owl.unk80 ^= 2;
                    SetStep(3);
                } else {
                    SetStep(11);
                }
            }
        }
        break;
    case 6:
        AnimateEntity(anim_knight_3, self);
        self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        if (self->ext.owl.unk80 & 1) {
            self->ext.owl.unk80 ^= 1;
            SetStep(2);
        }
        break;
    case 8:
        if (!self->step_s) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            self->velocityX = 0;
            self->step_s++;
        }
        if (!AnimateEntity(anim_knight_10, self)) {
            dx = GetDistanceToPlayerX();
            if (dx > 0x48) {
                SetStep(5);
            } else {
                SetStep(10);
            }
            if (self->ext.owl.unk80 & 0x10) {
                SetStep(10);
            }
        }
        UnkCollisionFunc2(D_us_80181CB8);
        self->velocityX -= self->velocityX / 16;
        if (abs(self->velocityX) < FIX(0.5)) {
            self->velocityX = 0;
        }
        if (!self->poseTimer && self->pose == 7) {
            PlaySfxPositional(SFX_WHIP_TWIRL_SWISH);
            PlaySfxPositional(SFX_SCRAPE_B);
            self->velocityX = FIX(-3);
            if (self->ext.owl.unk80 & 0x10) {
                self->velocityX -= FIX(2); // now it's -5
            }
            if (self->facingLeft) {
                EntityGreyPuffSpawner(self, 5, 3, 12, 32, 0, -4);
                self->velocityX = -self->velocityX;
            } else {
                EntityGreyPuffSpawner(self, 5, 3, -12, 32, 0, 4);
            }
        }
        break;
    case 7:
        if (!AnimateEntity(anim_knight_12, self)) {
            SetStep(10);
        }
        UnkCollisionFunc2(D_us_80181CB8);
        self->velocityX -= self->velocityX / 8;
        if (abs(self->velocityX) < FIX(0.5)) {
            self->velocityX = 0;
        }
        if (!self->poseTimer && self->pose == 5) {
            PlaySfxPositional(SFX_WHIP_TWIRL_SWISH);
            PlaySfxPositional(SFX_OWL_KNIGHT_ATTACK);
            self->velocityX = FIX(-6.0);
            if (self->facingLeft) {
                EntityGreyPuffSpawner(self, 5, 3, 16, 32, 0, -6);
                self->velocityX = -self->velocityX;
            } else {
                EntityGreyPuffSpawner(self, 5, 3, -16, 32, 0, 6);
            }
        }
        break;
    case 10:
        if (!self->step_s) {
            self->ext.owl.unk82 = D_us_80181E5C[Random() & 3];
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            self->ext.owl.unk8C = 1;
            if (self->ext.owl.unk80 & 0x10) {
                self->ext.owl.unk8C = 0;
                self->ext.owl.unk82 /= 4;
            }
            self->step_s++;
        }
        if (self->ext.owl.unk8C) {
            miscTemp = AnimateEntity(anim_knight_9, self);
        } else {
            miscTemp = AnimateEntity(anim_knight_8, self);
        }
        if (!miscTemp) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        }
        UnkCollisionFunc2(D_us_80181CB8);
        if (self->facingLeft ^ self->ext.owl.unk8C) {
            self->velocityX = FIX(0.5);
        } else {
            self->velocityX = FIX(-0.5);
        }
        if (self->ext.owl.unk8C) {
            self->velocityX -= self->velocityX / 16;
        }
        dx = GetDistanceToPlayerX();
        if (dx > 0x80) {
            if (self->ext.owl.unk8C) {
                self->pose = 9 - self->pose;
            }
            self->ext.owl.unk8C = 0;
        }
        if (!--self->ext.owl.unk82) {
            dx = GetDistanceToPlayerX();
            if (dx > 0x48) {
                SetStep(5);
            } else {
                SetStep(8);
            }
            if (self->ext.owl.unk80 & 0x10) {
                if (dx > 0x70) {
                    SetStep(10);
                } else if (dx < 0x48) {
                    SetStep(7);
                } else {
                    SetStep(8);
                }
            }
        }
        break;
    case 11:
        if (!self->step_s) {
            self->ext.owl.unk82 = D_us_80181E5C[Random() & 3];
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            self->ext.owl.unk8C = 1;
            self->step_s++;
        }
        UnkCollisionFunc2(D_us_80181CB8);
        if (self->ext.owl.unk8C) {
            miscTemp = AnimateEntity(anim_knight_5, self);
        } else {
            miscTemp = AnimateEntity(anim_knight_4, self);
        }
        if (!miscTemp) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        }
        if (self->facingLeft ^ self->ext.owl.unk8C) {
            self->velocityX = FIX(0.5);
        } else {
            self->velocityX = FIX(-0.5);
        }
        if (self->ext.owl.unk8C) {
            self->velocityX -= self->velocityX / 16;
        }
        dx = GetDistanceToPlayerX();
        miscTemp = self->ext.owl.unk8C;
        if (dx > 0x70) {
            miscTemp = 0;
        }
        if (dx < 0x40) {
            miscTemp = 1;
        }
        if (self->ext.owl.unk8C != miscTemp) {
            self->pose = 9 - self->pose;
        }
        self->ext.owl.unk8C = miscTemp;
        if (!--self->ext.owl.unk82) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            if (dx > 0xA0) {
                self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
                OWL->ext.owl.unk80 |= 8;
                SetStep(6);
            } else if (dx < 0x40) {
                SetStep(15);
            } else {
                if (self->ext.owl.unk80 & 2) {
                    self->ext.owl.unk80 ^= 2;
                    SetStep(3);
                } else {
                    self->ext.owl.unk82 = 0x20;
                }
            }
        }
        break;
    case 15:
        if (!AnimateEntity(anim_knight_14, self)) {
            SetStep(10);
        }
        if (!self->poseTimer && self->pose == 5) {
            PlaySfxPositional(SFX_WEAPON_SWISH_A);
        }
        UnkCollisionFunc2(D_us_80181CB8);
        self->velocityX -= self->velocityX / 16;
        if (abs(self->velocityX) < FIX(0.5)) {
            self->velocityX = 0;
        }
        if (!self->poseTimer && self->pose == 11) {
            PlaySfxPositional(SFX_OWL_KNIGHT_ATTACK);
            self->velocityX = FIX(-3.0);
            if (self->facingLeft) {
                EntityGreyPuffSpawner(self, 5, 3, 12, 32, 0, -4);
                self->velocityX = -self->velocityX;
            } else {
                EntityGreyPuffSpawner(self, 5, 3, -12, 32, 0, 4);
            }
        }
        break;
    case 13:
        switch (self->step_s) {
        case 0:
            if (!(self->ext.owl.unk80 & 4)) {
                self->step_s++;
            } else if (!AnimateEntity(anim_knight_11)) {
                self->flags ^= 0x4;
                self->step_s++;
            }
            break;
        case 1:
            dx_2 = OWL->posX.i.hi - self->posX.i.hi;
            if (dx_2 < 0) {
                self->velocityX = FIX(-1.5);
                self->facingLeft = 0;
            } else {
                self->velocityX = FIX(1.5);
                self->facingLeft = 1;
            }
            self->ext.owl.unk82 = 0x200;
            self->step_s++;
            break;
        case 2:
            AnimateEntity(anim_knight_6, self);
            miscTemp = UnkCollisionFunc2(D_us_80181CB8);
            if (miscTemp & 0x80) {
                self->ext.owl.unk82 = 1;
            }
            miscTemp = (GetSideToPlayer() & 1) ^ 1;
            if (self->facingLeft == miscTemp && GetDistanceToPlayerX() < 0x28) {
                self->pose = 0;
                self->poseTimer = 0;
                self->velocityX = 0;
                self->step_s++;
            }
            self->ext.owl.unk82--;
            dx_2 = OWL->posX.i.hi - self->posX.i.hi;
            if (dx_2 < 0) {
                dx_2 = -dx_2;
            }
            if (dx_2 < 12 || !self->ext.owl.unk82) {
                OWL->ext.owl.unk80 |= 0x10;
                self->ext.owl.unk82 = 0x100;
                SetSubStep(4);
            }
            break;
        case 3:
            if (!AnimateEntity(anim_knight_13, self)) {
                self->pose = 0;
                self->poseTimer = 0;
                self->step_s = 1;
            }
            UnkCollisionFunc2(D_us_80181CB8);
            self->velocityX -= self->velocityX / 8;
            if (abs(self->velocityX) < FIX(0.5)) {
                self->velocityX = 0;
            }
            if (self->pose == 5 && !self->poseTimer) {
                self->velocityX = FIX(-6.0);
                if (self->facingLeft) {
                    self->velocityX = -self->velocityX;
                }
            }
            break;
        case 4:
            AnimateEntity(anim_knight_16, self);
            if (!self->poseTimer && self->pose == 2) {
                PlaySfxPositional(SFX_OWL_KNIGHT_REACT);
            }
            if (!--self->ext.owl.unk82) {
                SetSubStep(5);
            }
            break;
        case 5:
            if (!AnimateEntity(anim_knight_17, self)) {
                self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
                SetStep(16);
            }
            break;
        }
        break;
    case 14:
        SWORD->attack *= 2;
        if (!AnimateEntity(anim_knight_12, self)) {
            SWORD->attack /= 2;
            SetStep(10);
        }
        break;
    case 16:
        switch (self->step_s) {
        case 0:
            if (!AnimateEntity(anim_knight_4, self)) {
                self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            }
            if (self->facingLeft) {
                self->velocityX = FIX(0.5);
            } else {
                self->velocityX = FIX(-0.5);
            }
            UnkCollisionFunc2(D_us_80181CB8);
            dx = GetDistanceToPlayerX();
            if (dx < 0x50) {
                SetSubStep(1);
            }
            break;
        case 1:
            if (!AnimateEntity(anim_knight_15, self)) {
                SetStep(10);
            }
            UnkCollisionFunc2(D_us_80181CB8);
            self->velocityX -= self->velocityX / 8;
            if (abs(self->velocityX) < FIX(0.5)) {
                self->velocityX = 0;
            }
            if (!self->poseTimer && self->pose == 5) {
                PlaySfxPositional(SFX_WHIP_TWIRL_SWISH);
                PlaySfxPositional(SFX_OWL_KNIGHT_ATTACK);
                self->velocityX = FIX(-8.0);
                if (self->facingLeft) {
                    EntityGreyPuffSpawner(self, 5, 3, 32, 32, 0, -6);
                    self->velocityX = -self->velocityX;
                } else {
                    EntityGreyPuffSpawner(self, 5, 3, -32, 32, 0, 6);
                }
            }
            break;
        }
        break;
    case 17:
        if (g_Timer % 8 == 0) {
            PlaySfxPositional(SFX_EXPLODE_SMALL);
            tempEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (tempEntity != NULL) {
                CreateEntityFromEntity(E_INTENSE_EXPLOSION, self, tempEntity);
                tempEntity->posX.i.hi += (Random() & 0x1F) - 16;
                tempEntity->posY.i.hi += (Random() & 0x1F) - 16;
            }
        }
        AnimateEntity(anim_knight_16, self);
        if (!--self->ext.owl.unk82) {
            PlaySfxPositional(SFX_NOISE_SWEEP_DOWN_A);
            SetStep(18);
        }
        break;
    case 18:
        if (OwlKnightDeathAnim()) {
            OWL->ext.owl.unk80 |= 0x40;
            DestroyEntity(self);
            return;
        }
        break;
    case 32:
#include "pad2_anim_debug.h"
    }
    hitboxPtr = D_us_80181E08;
    index = self->animCurFrame - 0xF;
    index = D_us_80181E28[index] - 7;
    if (index < 0) {
        index = 0;
    }
    hitboxPtr += index * 4;
    self->hitboxOffX = *hitboxPtr++;
    self->hitboxOffY = *hitboxPtr++;
    self->hitboxWidth = *hitboxPtr++;
    self->hitboxHeight = *hitboxPtr++;
}

static s8 D_us_80181E64[] = {
    0,   0,  0,  0,  0,   0,  0,  0, -8,  3,  18, 1, -4,  2,  18, 1,
    0,   2,  18, 1,  -22, 2,  18, 1, -21, 6,  18, 1, -27, -7, 23, 4,
    -16, -6, 32, 10, -27, -1, 23, 4, 0,   -2, 18, 1, -4,  -2, 18, 1,
};
static u8 D_us_80181E94[] = {
    0, 5, 5,  5,  5,  5,  5, 5,  5,  5,  6, 7, 8, 5, 5, 5, 9, 10,
    5, 5, 14, 15, 5,  11, 5, 12, 5,  5,  5, 5, 5, 5, 5, 5, 5, 5,
    5, 5, 5,  5,  13, 5,  5, 5,  14, 14, 0, 5, 0, 0, 0, 5,
};

// The sword sprite is part of the owl knight, this handles the sword hitbox
void EntityOwlKnightSword(Entity* self) {
    s32 index;
    s8* hitboxPtr;
    Entity* parent;

    if (!self->step) {
        InitializeEntity(g_EInitOwlKnightSword);
    }
    parent = self - 1;
    self->facingLeft = parent->facingLeft;
    self->posX.i.hi = parent->posX.i.hi;
    self->posY.i.hi = parent->posY.i.hi;
    hitboxPtr = D_us_80181E64;
    index = parent->animCurFrame - 0xF;
    index = D_us_80181E94[index] - 4;
    if (index < 0) {
        index = 0;
    }
    hitboxPtr += index * 4;
    self->hitboxOffX = *hitboxPtr++;
    self->hitboxOffY = *hitboxPtr++;
    self->hitboxWidth = *hitboxPtr++;
    self->hitboxHeight = *hitboxPtr++;
    if (parent->entityId != E_OWL_KNIGHT) {
        DestroyEntity(self);
    }
}

void EntityOwlTarget(Entity* self) {
    if (!self->step) {
        InitializeEntity(g_EInitInteractable);
    }
}
