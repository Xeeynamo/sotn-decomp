// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no1.h"

// Code in this file is very similar to entity_axe_knight.h
// but has some additional attacks and code not present in the lower
// level green axe knight

typedef enum {
    AXE_KNIGHT_INIT,
    AXE_KNIGHT_IDLE,
    AXE_KNIGHT_WALK_TOWARDS_PLAYER,
    AXE_KNIGHT_WALK_AWAY_FROM_PLAYER,
    AXE_KNIGHT_STANDING_THROW,
    AXE_KNIGHT_DUCKING_THROW,
    AXE_KNIGHT_CHARGE_ATTACK,
    AXE_KNIGHT_ARCING_THROW,
    AXE_KNIGHT_DYING,
} EntityAxeKnightSteps;

static s16 sensors_move[] = {0, 32, 8, 0};
static s16 sensors_ground[4][2] = {{0, 32}, {0, 4}, {8, -4}, {-16, 0}};
static s16 dead_particle_pos[][2] = {
    {-8, -4}, {8, -6}, {-2, 4}, {-1, -7}, {2, 8}, {11, -7}, {4, 6}, {-3, 0}};

static u8 anim_walk_alt[] = {0x14, 0x01, 0x0A, 0x02, 0x0A, 0x03, 0x14, 0x04,
                             0x0A, 0x03, 0x0A, 0x02, 0x00, 0x00, 0x00, 0x00};
static u8 anim_throw_stand_alt[] = {
    0x08, 0x05, 0x08, 0x06, 0x08, 0x07, 0x08, 0x0D, 0x08, 0x0E, 0x02, 0x0F,
    0x02, 0x14, 0x02, 0x15, 0x20, 0x16, 0x08, 0x17, 0x00, 0x00, 0x00, 0x00,
};
static u8 anim_throw_duck_alt[] = {
    0x08, 0x05, 0x08, 0x06, 0x08, 0x07, 0x08, 0x08, 0x0A, 0x09,
    0x04, 0x0A, 0x04, 0x0B, 0x04, 0x0C, 0x00, 0x00, 0x00, 0x00};
static u8 anim_charge_swing_alt[] = {
    0x04, 0x0E, 0x04, 0x0F, 0x04, 0x10, 0x04, 0x11, 0x00, 0x00, 0x00, 0x00};
static u8 anim_charge_final_slice_alt[] = {
    0x08, 0x0D, 0x08, 0x0E, 0x01, 0x0F, 0x01, 0x10,
    0x01, 0x11, 0x20, 0x12, 0x08, 0x13, 0x00, 0x00};
static u8 anim_walk[] = {0x1A, 0x18, 0x0A, 0x19, 0x0A, 0x1A, 0x1A,
                         0x1B, 0x0A, 0x1A, 0x0A, 0x19, 0x00};
static u8 anim_throw_duck[] = {
    0x08, 0x1C, 0x08, 0x1D, 0x08, 0x1E, 0x08, 0x1F, 0x0A, 0x20,
    0x04, 0x21, 0x04, 0x22, 0x04, 0x23, 0x00, 0x00, 0x00, 0x00};
static u8 anim_charge_final_slice[] = {
    0x08, 0x24, 0x08, 0x25, 0x02, 0x26, 0x02, 0x27,
    0x02, 0x28, 0x20, 0x29, 0x08, 0x2A, 0x00};
static u8 anim_throw_stand[] = {
    0x08, 0x1C, 0x08, 0x1D, 0x08, 0x1E, 0x08, 0x24, 0x08, 0x25, 0x02, 0x26,
    0x02, 0x2B, 0x02, 0x2C, 0x20, 0x2D, 0x08, 0x2E, 0x00, 0x00, 0x00, 0x00};
static u8 anim_charge_swing[] = {
    0x04, 0x25, 0x04, 0x26, 0x04, 0x27, 0x04, 0x28, 0x00};
static u8 anim_die[] = {
    0x08, 0x20, 0x08, 0x21, 0x08, 0x22, 0x08, 0x23, 0xFF, 0x00};

static s8 hitboxes[][4] = {
    {0, 0, 0, 0},
    {0, 6, 8, 26},
    {0, 11, 8, 21},
    {0, 12, 8, 20},
};
static u8 hitbox_lookup[] = {
    0, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 3, 1, 1, 1, 3, 1,
    1, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 3, 1, 1, 1, 3, 1, 0};
static s8 hitboxes_2[][4] = {
    {0, 0, 0, 0},     {-72, -96, 0, 0}, {16, 16, 8, 8},   {8, -16, 8, 8},
    {8, -24, 8, 8},   {8, -32, 8, 8},   {-16, -36, 8, 8}, {-15, -9, 22, 8},
    {-14, 14, 22, 8}, {-11, 12, 18, 8}, {18, 16, 8, 8},   {-17, -35, 8, 8},
    {-14, -9, 22, 8}, {-13, 13, 22, 8}};
static u8 hitbox_2_lookup[] = {
    0, 0,  0,  0,  0, 0, 0, 0, 2, 0, 0, 0, 0,  3, 4, 5, 6, 7, 8,
    9, 0,  0,  0,  0, 0, 0, 0, 0, 0, 0, 0, 10, 0, 0, 0, 0, 3, 4,
    5, 11, 12, 13, 9, 0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0};

static u32 init_velocity_x[] = {FIX(2), FIX(2), FIX(1)};
static u32 init_velocity_y[] = {FIX(0), FIX(0), FIX(-4), FIX(0)};

// Weirdly, this function ONLY acts on prim->next, it does not act on prim.
// However, it does call functions on prim.
static void AxeKnightUnkFunc1(AxePrim* prim) {
    Collider collider;
    Entity* newEnt;
    s16 yVar;

    UnkPrimHelper((Primitive*)prim);
    switch (prim->next->step) {
    case 0:
        prim->next->unk0C = 0;
        prim->next->unk10 = -0x10000;
        prim->next->step = 1;
        prim->next->timer = 0x100;
        return;
    case 1:
        yVar = prim->next->y0 + (prim->next->unk1E / 3);
        g_api.CheckCollision(prim->next->x1, yVar, &collider, 0);
        if (collider.effects & EFFECT_SOLID) {
            prim->next->y0 += collider.unk18;
            if (prim->next->unk10 < 0x4000) {
                prim->next->timer = 1;
            }
            prim->next->unk10 = -prim->next->unk10;
            prim->next->unk10 -= prim->next->unk10 / 2;
        }
        prim->next->unk10 += 0x1800;
        prim->next->timer--;
        if (prim->next->timer == 0) {
            newEnt = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (newEnt != NULL) {
                CreateEntityFromCurrentEntity(E_EXPLOSION, newEnt);
                newEnt->posX.i.hi = prim->next->x1;
                newEnt->posY.i.hi = prim->next->y0;
                newEnt->params = 0;
            }
            g_api.PlaySfx(SFX_EXPLODE_B);
            UnkPolyFunc0((Primitive*)prim);
        }
        return;
    }
}

// Called by EntityAxeKnightBlue
extern s16* sprites_3[];
s32 func_us_801CA51C(Entity* axeKnight) {
    Entity* entity;
    Primitive* prim;
    s32 primIndex;
    s16 uCoord;
    s16 vCoord;
    u16 UV_thing;
    u8 flag;
    s16* dataPtr;
    s16 clutBase;

    switch (axeKnight->step_s) {
    case 0:
        clutBase = g_EInitAxeKnight[3];
        dataPtr = sprites_3[axeKnight->animCurFrame];
        primIndex = g_api.AllocPrimitives(PRIM_GT4, *dataPtr * 2);
        if (primIndex != -1) {
            axeKnight->flags |= FLAG_HAS_PRIMS;
            axeKnight->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            axeKnight->ext.axeknight.prim = prim;
            dataPtr++;
            // Prims appear to come in pairs here.
            // "prim" is a Primitive, while prim->next is an AxePrim.
            // Notice at the end of this loop we do ->next twice.
            while (prim != NULL) {
                UnkPolyFunc2(prim);
                dataPtr++;
                prim->next->x1 = axeKnight->posX.i.hi;
                if (axeKnight->facingLeft) {
                    prim->next->x1 -= *dataPtr++;
                } else {
                    prim->next->x1 += *dataPtr++;
                }
                prim->next->y0 = axeKnight->posY.i.hi + *dataPtr++;
                ((AxePrim*)prim->next)->unk1C = *dataPtr++;
                if (axeKnight->facingLeft) {
                    prim->next->x1 -= ((AxePrim*)prim->next)->unk1C / 2;
                } else {
                    prim->next->x1 += ((AxePrim*)prim->next)->unk1C / 2;
                }
                ((AxePrim*)prim->next)->unk1E = *dataPtr++;
                prim->next->y0 += ((AxePrim*)prim->next)->unk1E / 2;
                prim->clut = clutBase + *dataPtr++;
                if (axeKnight->params) {
                    prim->clut += 2;
                }
                UV_thing = axeKnight->unk5A;
                UV_thing += *dataPtr++;
                prim->tpage = 0x12;         // Leftover line, shows up in PSP
                prim->tpage = UV_thing / 4; // Masks off the lower two bits
                uCoord = (UV_thing & 1);
                uCoord = uCoord * 0x7F;
                vCoord = ((UV_thing & 2) >> 1);
                vCoord = vCoord * 0x7F;
                // uCoord and vCoord are each either 0 or 7F.
                if (axeKnight->facingLeft) {
                    prim->u1 = prim->u3 = uCoord + *dataPtr++;
                    prim->v0 = prim->v1 = vCoord + *dataPtr++;
                    prim->u0 = prim->u2 = uCoord + *dataPtr++;
                    prim->v2 = prim->v3 = vCoord + *dataPtr++;
                } else {
                    prim->u0 = prim->u2 = uCoord + *dataPtr++;
                    prim->v0 = prim->v1 = vCoord + *dataPtr++;
                    prim->u1 = prim->u3 = uCoord + *dataPtr++;
                    prim->v2 = prim->v3 = vCoord + *dataPtr++;
                }
                prim->priority = axeKnight->zPriority + 2;
                prim->drawMode = DRAW_UNK02;
                prim = prim->next;
                prim = prim->next;
            }
        } else {
            return 1;
        }
        g_api.PlaySfx(SFX_FM_EXPLODE_B);
        axeKnight->step_s++;
        break;
    case 1:
        flag = 0;
        for (prim = axeKnight->ext.axeknight.prim; prim != NULL;) {
            if (prim->p3 & 8) {
                AxeKnightUnkFunc1(prim);
                flag = 1;
            }
            prim = prim->next;
            prim = prim->next;
        }
        if (!flag) {
            return 1;
        }
        break;
    case 16:
        entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (entity != NULL) {
            CreateEntityFromEntity(E_UNK_ENTITY, axeKnight, entity);
        }
        PlaySfxPositional(SFX_FAST_STUTTER_EXPLODE);
        axeKnight->step_s++;
        break;
    case 17:
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 2);
        if (primIndex != -1) {
            axeKnight->flags |= FLAG_HAS_PRIMS;
            axeKnight->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            axeKnight->ext.axeknight.prim = prim;
            UnkPolyFunc2(prim);
            prim->tpage = 0x1A;
            prim->clut = 0x19D;
            prim->u0 = 0;
            prim->u1 = 0x3F;
            prim->u2 = prim->u0;
            prim->u3 = prim->u1;
            prim->v0 = 0xC0;
            prim->v1 = prim->v0;
            prim->v2 = 0xFF;
            prim->v3 = prim->v2;
            prim->priority = axeKnight->zPriority + 2;
            prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS |
                             DRAW_UNK02 | DRAW_TRANSP;
            prim->p3 = 8;
            prim->next->x1 = axeKnight->posX.i.hi;
            prim->next->y0 = axeKnight->posY.i.hi;
            ((AxePrim*)prim->next)->unk1C = 0;
            ((AxePrim*)prim->next)->unk1E = 0;
            prim->next->b3 = 0x80;
            axeKnight->ext.axeknight.unk88 = 0;
            PlaySfxPositional(SFX_NOISE_SWEEP_DOWN_A);
            axeKnight->step_s++;
            break;
        }
        return 1;
    case 18:
        if (axeKnight->ext.axeknight.unk88 > 6) {
            prim = axeKnight->ext.axeknight.prim;
            ((AxePrim*)prim->next)->unk1C += 0xE;
            ((AxePrim*)prim->next)->unk1E += 0xE;
            prim->next->b3 -= 4;
            UnkPrimHelper(prim);
        }

        if (++axeKnight->ext.axeknight.unk88 > 0xA) {
            axeKnight->step_s++;
        }
        break;
    case 19:
        prim = axeKnight->ext.axeknight.prim;
        ((AxePrim*)prim->next)->unk1C++;
        ((AxePrim*)prim->next)->unk1E++;
        prim->next->b3 -= 4;
        UnkPrimHelper(prim);

        if (!(g_Timer % 5)) {
            entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_INTENSE_EXPLOSION, axeKnight, entity);
                entity->posX.i.hi += (Random() & 0x1F) - 0x10;
                entity->posY.i.hi += (Random() & 0x1F) - 0x10;
            }
        }

        if (++axeKnight->ext.axeknight.unk88 > 0x26) {
            axeKnight->ext.axeknight.unk88 = 0;
            PlaySfxPositional(SFX_FAST_STUTTER_EXPLODE);
            axeKnight->step_s++;
            prim = axeKnight->ext.axeknight.prim;
            prim->drawMode = DRAW_UNK_40 | DRAW_TPAGE2 | DRAW_TPAGE |
                             DRAW_COLORS | DRAW_UNK02 | DRAW_TRANSP;
            ((AxePrim*)prim->next)->unk1C = 8;
            ((AxePrim*)prim->next)->unk1E = 8;
            prim->next->b3 = 0x40;
        }
        break;
    case 20:
        if (!(g_Timer % 8)) {
            entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_EXPLOSION, axeKnight, entity);
                entity->posX.i.hi += (Random() & 0xF) - 8;
                entity->posY.i.hi += (Random() & 0x1F);
                entity->params = 1;
            }
        }
        prim = axeKnight->ext.axeknight.prim;
        ((AxePrim*)prim->next)->unk1C += 0x10;
        ((AxePrim*)prim->next)->unk1E += 0x10;
        prim->next->b3 -= 3;
        UnkPrimHelper(prim);

        if (++axeKnight->ext.axeknight.unk88 > 0x14) {
            axeKnight->animSet = 0;
            axeKnight->ext.axeknight.unk88 = 0;
            axeKnight->step_s++;
            return 1;
        }

        break;
    }
    return 0;
}

void func_us_801CAD20(void) {
    u8 steps[] = {AXE_KNIGHT_STANDING_THROW, AXE_KNIGHT_STANDING_THROW,
                  AXE_KNIGHT_STANDING_THROW, AXE_KNIGHT_STANDING_THROW,
                  AXE_KNIGHT_DUCKING_THROW,  AXE_KNIGHT_DUCKING_THROW,
                  AXE_KNIGHT_DUCKING_THROW,  AXE_KNIGHT_CHARGE_ATTACK};
    if (GetDistanceToPlayerY() < 0x20) {
        if (g_CurrentEntity->ext.axeknight.unk82 > 0) {
            g_CurrentEntity->ext.axeknight.unk82 -= 3;
        } else {
            SetStep(steps[(Random() & 7)]);
            g_CurrentEntity->ext.axeknight.unk82 = 256;
        }
    } else {
        if (g_CurrentEntity->ext.axeknight.unk82 > 0) {
            g_CurrentEntity->ext.axeknight.unk82--;
        } else {
            SetStep(7);
            g_CurrentEntity->ext.axeknight.unk82 = 256;
        }
    }
}

void EntityAxeKnightBlue(Entity* self) {
    Entity* nextEntity;
    Entity* newEntity;
    s8* hitbox;
    s32 velX;
    s32 i;
    s16 temp;
    u8 animStatus;

    if (self->hitPoints < 8 && self->ext.axeknight.unk7D) {
        self->animCurFrame += 0x17;
        self->ext.axeknight.unk7D = 0;
        newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (newEntity != NULL) {
            for (i = 0; i < 2; i++) {
                CreateEntityFromEntity(E_EXPLOSION, self, newEntity);
                if (self->facingLeft) {
                    newEntity->posX.i.hi += 0xC;
                } else {
                    newEntity->posX.i.hi -= 0xC;
                }
                newEntity->posY.i.hi += (i * 8) - 8;
                newEntity->params = 2;
            }
        }
    }

    if (self->flags & FLAG_DEAD && self->step != AXE_KNIGHT_DYING) {
        PlaySfxPositional(NA_SE_VO_AXE_KNIGHT_SCREAM);
        self->hitboxState = 0;
        self->zPriority -= 0x10;
        self->ext.axeknight.unk80 = 65;
        SetStep(AXE_KNIGHT_DYING);
        if (Random() & 1) {
            self->step_s = 0x10;
            self->ext.axeknight.unk80 = 0;
        } else {
            self->step_s = 0;
        }
    }

    switch (self->step) {
    case AXE_KNIGHT_INIT:
        InitializeEntity(g_EInitAxeKnight);
        self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        self->hitboxOffY = 10;
        if (self->params) {
            self->palette += 2;
        }
        self->ext.axeknight.unk7D = 1;
        self->ext.axeknight.unk82 = 512;
        nextEntity = self + 1;
        CreateEntityFromEntity(E_AXE_KNIGHT_AXE_2, self, nextEntity);
        break;

    case AXE_KNIGHT_IDLE:
        if (UnkCollisionFunc3(sensors_ground) & 1) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            SetStep(AXE_KNIGHT_WALK_TOWARDS_PLAYER);
        }
        break;

    case AXE_KNIGHT_WALK_TOWARDS_PLAYER:
        if (!self->step_s) {
            if (self->facingLeft) {
                self->velocityX = FIX(0.3125);
            } else {
                self->velocityX = FIX(-0.3125);
            }
            self->step_s++;
        }

        if (self->ext.axeknight.unk7D) {
            animStatus = AnimateEntity(anim_walk_alt, self);
        } else {
            animStatus = AnimateEntity(anim_walk, self);
        }

        if (!animStatus) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            if (self->facingLeft) {
                self->velocityX = FIX(0.3125);
            } else {
                self->velocityX = FIX(-0.3125);
            }

            if (GetDistanceToPlayerX() < 96) {
                SetStep(AXE_KNIGHT_WALK_AWAY_FROM_PLAYER);
                self->ext.axeknight.unk7C = 1;
            }
        }

        if (self->animFrameIdx == 1 || self->animFrameIdx == 4) {
            if (self->facingLeft) {
                self->velocityX += 0x600;
            } else {
                self->velocityX -= 0x600;
            }
        } else if (self->facingLeft) {
            self->velocityX -= 0x600;
        } else {
            self->velocityX += 0x600;
        }

        if (UnkCollisionFunc2(sensors_move) & 0x60) {
            self->posX.val -= self->velocityX;
            self->velocityX = 0;
        }
        func_us_801CAD20();
        break;

    case AXE_KNIGHT_WALK_AWAY_FROM_PLAYER:
        if (!self->step_s) {
            if (self->facingLeft) {
                self->velocityX = FIX(-0.375);
            } else {
                self->velocityX = FIX(0.375);
            }
            self->step_s++;
        }

        if (self->ext.axeknight.unk7D) {
            animStatus = AnimateEntity(anim_walk_alt, self);
        } else {
            animStatus = AnimateEntity(anim_walk, self);
        }

        if (!animStatus) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            if (self->facingLeft) {
                self->velocityX = FIX(-0.375);
            } else {
                self->velocityX = FIX(0.375);
            }

            if (GetDistanceToPlayerX() > 80) {
                SetStep(AXE_KNIGHT_WALK_TOWARDS_PLAYER);
                self->ext.axeknight.unk7C = 0;
            }
        }

        if (self->animFrameIdx == 1 || self->animFrameIdx == 4) {
            if (self->facingLeft) {
                self->velocityX -= 0x400;
            } else {
                self->velocityX += 0x400;
            }
        } else if (self->facingLeft) {
            self->velocityX += 0x400;
        } else {
            self->velocityX -= 0x400;
        }

        if (UnkCollisionFunc2(sensors_move) & 0x60) {
            self->posX.val -= self->velocityX;
            self->velocityX = 0;
        }
        func_us_801CAD20();
        break;

    case AXE_KNIGHT_STANDING_THROW:
        if (self->ext.axeknight.unk7D) {
            animStatus = AnimateEntity(anim_throw_stand_alt, self);
        } else {
            animStatus = AnimateEntity(anim_throw_stand, self);
        }
        if (!animStatus) {
            if (GetDistanceToPlayerX() > 88) {
                SetStep(AXE_KNIGHT_WALK_TOWARDS_PLAYER);
                self->ext.axeknight.unk7C = 0;
            } else {
                SetStep(AXE_KNIGHT_WALK_AWAY_FROM_PLAYER);
                self->ext.axeknight.unk7C = 1;
            }
        } else if ((animStatus & 0x80) && (self->animFrameIdx == 7)) {
            PlaySfxPositional(NA_SE_VO_AXE_KNIGHT_THROW);
            PlaySfxPositional(SFX_WHIP_TWIRL_SWISH);
            newEntity = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (newEntity != NULL) {
                CreateEntityFromCurrentEntity(E_AXE_KNIGHT_AXE, newEntity);
                newEntity->facingLeft = self->facingLeft;
                newEntity->posY.i.hi -= 12;
                if (newEntity->facingLeft) {
                    newEntity->posX.i.hi += 8;
                } else {
                    newEntity->posX.i.hi -= 8;
                }
            }
        }
        break;

    case AXE_KNIGHT_DUCKING_THROW:
        if (self->ext.axeknight.unk7D) {
            animStatus = AnimateEntity(anim_throw_duck_alt, self);
        } else {
            animStatus = AnimateEntity(anim_throw_duck, self);
        }

        if (!animStatus) {
            if (GetDistanceToPlayerX() > 0x58) {
                SetStep(2);
                self->ext.axeknight.unk7C = 0;
            } else {
                SetStep(3);
                self->ext.axeknight.unk7C = 1;
            }
        } else if ((animStatus & 0x80) && (self->animFrameIdx == 6)) {
            PlaySfxPositional(NA_SE_VO_AXE_KNIGHT_THROW);
            PlaySfxPositional(SFX_WHIP_TWIRL_SWISH);
            newEntity = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (newEntity != NULL) {
                CreateEntityFromCurrentEntity(E_AXE_KNIGHT_AXE, newEntity);
                newEntity->facingLeft = self->facingLeft;
                newEntity->params = 1;
                newEntity->posY.i.hi += 12;
                if (newEntity->facingLeft) {
                    newEntity->posX.i.hi += 8;
                } else {
                    newEntity->posX.i.hi -= 8;
                }
            }
        }
        break;

    case AXE_KNIGHT_CHARGE_ATTACK:
        switch (self->step_s) {
        case 0:
            self->ext.axeknight.unk80 = 0x20;
            self->animCurFrame = 4;
            self->step_s += 1;
            break;

        case 1:
            if (self->ext.axeknight.unk80) {
                self->ext.axeknight.unk80--;
            } else {
                self->ext.axeknight.unk80 = 0x40;
                if (self->facingLeft) {
                    self->velocityX = FIX(2.5);
                } else {
                    self->velocityX = FIX(-2.5);
                }
                self->step_s++;
            }
            break;

        case 2:
            if (self->ext.axeknight.unk7D) {
                animStatus = AnimateEntity(anim_charge_swing_alt, self);
            } else {
                animStatus = AnimateEntity(anim_charge_swing, self);
            }

            if (!self->ext.axeknight.unk80 || GetDistanceToPlayerX() < 0x20) {
                PlaySfxPositional(0x766);
                self->animFrameIdx = 0;
                self->animFrameDuration = 0;
                self->step_s++;
            } else {
                self->ext.axeknight.unk80--;
            }
            if (UnkCollisionFunc2(sensors_move) & 0x60) {
                self->posX.val -= self->velocityX;
                self->velocityX = 0;
            }
            break;
        case 3:
            if (self->ext.axeknight.unk7D) {
                animStatus = AnimateEntity(anim_charge_final_slice_alt, self);
            } else {
                animStatus = AnimateEntity(anim_charge_final_slice, self);
            }

            if (!animStatus) {
                self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
                if (GetDistanceToPlayerX() > 0x58) {
                    SetStep(2);
                    self->ext.axeknight.unk7C = 0;
                } else {
                    SetStep(3);
                    self->ext.axeknight.unk7C = 1;
                }
            } else {
                velX = self->velocityX;
                if (velX) {
                    if (velX < 0) {
                        velX += FIX(0.25);
                    } else {
                        velX -= FIX(0.25);
                    }

                    self->velocityX = velX;

                    if (UnkCollisionFunc2(sensors_move) & 0x60) {
                        self->posX.val -= self->velocityX;
                        self->velocityX = 0;
                    }
                }
            }
            break;
        }
        break;

    case AXE_KNIGHT_ARCING_THROW:
        if (self->ext.axeknight.unk7D) {
            animStatus = AnimateEntity(anim_throw_stand_alt, self);
        } else {
            animStatus = AnimateEntity(anim_throw_stand, self);
        }

        if (!animStatus) {
            if (GetDistanceToPlayerX() > 88) {
                SetStep(AXE_KNIGHT_WALK_TOWARDS_PLAYER);
                self->ext.axeknight.unk7C = 0;
            } else {
                SetStep(AXE_KNIGHT_WALK_AWAY_FROM_PLAYER);
                self->ext.axeknight.unk7C = 1;
            }
        } else if ((animStatus & 0x80) && (self->animFrameIdx == 7)) {
            PlaySfxPositional(NA_SE_VO_AXE_KNIGHT_THROW);
            PlaySfxPositional(SFX_WHIP_TWIRL_SWISH);
            newEntity = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (newEntity != NULL) {
                CreateEntityFromCurrentEntity(E_AXE_KNIGHT_AXE, newEntity);
                newEntity->facingLeft = self->facingLeft;
                newEntity->params = 2;
                newEntity->posY.i.hi -= 40;
                if (newEntity->facingLeft) {
                    newEntity->posX.i.hi += 16;
                } else {
                    newEntity->posX.i.hi -= 16;
                }
            }
        }
        break;

    case AXE_KNIGHT_DYING:
        if (self->ext.axeknight.unk80) {
            temp = --self->ext.axeknight.unk80;
            if (!(temp & 7)) {
                newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (newEntity != NULL) {
                    CreateEntityFromEntity(E_EXPLOSION, self, newEntity);
                    temp >>= 3;
                    newEntity->params = 2;
                    newEntity->posX.i.hi += dead_particle_pos[temp][0];
                    newEntity->posY.i.hi += dead_particle_pos[temp][1];
                }
            }
        }

        if (!AnimateEntity(anim_die, self)) {
            if (func_us_801CA51C(self)) {
                DestroyEntity(self);
                return;
            }

            if (self->step_s < 16) {
                self->animCurFrame = 0;
            }
        }
        break;
    }

    hitbox = hitboxes[0];
    hitbox += hitbox_lookup[self->animCurFrame] * 4;
    self->hitboxOffX = *hitbox++;
    self->hitboxOffY = *hitbox++;
    self->hitboxWidth = *hitbox++;
    self->hitboxHeight = *hitbox++;
}

void EntityAxeKnightRotateAxe(void) {
    if (g_CurrentEntity->params != 0) {
        g_CurrentEntity->rotZ += 0x80;
    } else {
        g_CurrentEntity->rotZ -= 0x80;
    }

    g_CurrentEntity->rotZ &= 0xFFF;
}

void EntityAxeKnightThrowingAxe(Entity* self) {
    s32 velocityX;

    if (self->flags & FLAG_DEAD) {
        EntityExplosionSpawn(0, 0);
        PlaySfxPositional(SFX_WEAPON_BREAK);
        return;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitAxeKnightAxe);
        self->drawFlags = FLAG_DRAW_ROTZ;
        self->velocityY = init_velocity_y[self->params];
        velocityX = init_velocity_x[self->params];

        if (self->facingLeft) {
            self->velocityX = velocityX;
        } else {
            self->velocityX = -velocityX;
        }

        self->ext.timer.t = -0x40;

        if (self->params == 2) {
            self->step++;
            return;
        }
        break;

    case 1:
        EntityAxeKnightRotateAxe();
        if (0 <= self->ext.timer.t && self->ext.timer.t < 0x20) {
            if (self->facingLeft) {
                self->velocityX -= FIX(0.125);
            } else {
                self->velocityX += FIX(0.125);
            }
        }

        self->ext.timer.t++;
        MoveEntity();
        break;

    case 2:
        EntityAxeKnightRotateAxe();
        self->velocityY += FIX(0.125);
        MoveEntity();
        break;
    }
}

void func_us_801CBA30(Entity* self) {
    Entity* parent;
    s8* hitbox;
    u32 index;

    if (!self->step) {
        InitializeEntity(g_EInitAxeKnightAxe);
        self->animSet = 0;
        self->animCurFrame = 0;
        self->hitboxState = 1;
        self->hitPoints = 0x7FFF;
        self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA |
                      FLAG_NOT_AN_ENEMY | FLAG_UNK_00200000 | FLAG_UNK_2000;
    }
    parent = self - 1;
    self->facingLeft = parent->facingLeft;
    self->posX.i.hi = parent->posX.i.hi;
    self->posY.i.hi = parent->posY.i.hi;
    hitbox = *hitboxes_2;
    index = hitbox_2_lookup[parent->animCurFrame];
    hitbox += index * 4;
    self->hitboxOffX = *hitbox++;
    self->hitboxOffY = *hitbox++;
    self->hitboxWidth = *hitbox++;
    self->hitboxHeight = *hitbox++;

    if (parent->entityId != 0x20) {
        DestroyEntity(self);
    }
}
