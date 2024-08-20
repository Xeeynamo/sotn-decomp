/*
 * Overlay: NZ0
 * Enemy: Axe Knight
 * Description: Low level Axe Knight
 */

#include "nz0.h"
#include "sfx.h"

typedef enum {
    AXE_KNIGHT_INIT,
    AXE_KNIGHT_IDLE,
    AXE_KNIGHT_WALK_TOWARDS_PLAYER,
    AXE_KNIGHT_WALK_AWAY_FROM_PLAYER,
    AXE_KNIGHT_STANDING_THROW,
    AXE_KNIGHT_DUCKING_THROW,
    AXE_KNIGHT_UNUSED, // Charge Attack missing step from the blue AxeKnight
    AXE_KNIGHT_ARCING_THROW, // Unused, present in the blue AxeKnight
    AXE_KNIGHT_DYING,
} EntityAxeKnightSteps;

extern u16 g_EAxeKnightInit[];
static s16 sensors_move[] = {0, 32, 8, 0};
static s16 sensors_ground[4][2] = {{0, 32}, {0, 4}, {8, -4}, {-16, 0}};
static s16 dead_particle_pos[][2] = {
    {-8, -4}, {8, -6}, {-2, 4}, {-1, -7}, {2, 8}, {11, -7}, {4, 6}, {-3, 0}};
static u16 unused[] = {
    0x0114, 0x020A, 0x030A, 0x0414, 0x030A, 0x020A, 0x0000, 0x0000, 0x0508,
    0x0608, 0x0708, 0x0D08, 0x0E08, 0x0F02, 0x1402, 0x1502, 0x1620, 0x1708,
    0x0000, 0x0000, 0x0508, 0x0608, 0x0708, 0x0808, 0x090A, 0x0A04, 0x0B04,
    0x0C04, 0x0000, 0x0000, 0x0E04, 0x0F04, 0x1004, 0x1104, 0x0000, 0x0000,
    0x0D08, 0x0E08, 0x0F01, 0x1001, 0x1101, 0x1220, 0x1308, 0x0000};
static u8 anim_walk[] = {0x1A, 0x18, 0x0A, 0x19, 0x0A, 0x1A, 0x1A,
                         0x1B, 0x0A, 0x1A, 0x0A, 0x19, 0x00};
static u8 anim_throw_duck[] = {
    0x08, 0x1C, 0x08, 0x1D, 0x08, 0x1E, 0x08, 0x1F, 0x0A, 0x20, 0x04, 0x21,
    0x04, 0x22, 0x04, 0x23, 0x00, 0x00, 0x00, 0x00, 0x08, 0x24, 0x08, 0x25,
    0x02, 0x26, 0x02, 0x27, 0x02, 0x28, 0x20, 0x29, 0x08, 0x2A, 0x00};
static u8 anim_throw_stand[] = {
    0x08, 0x1C, 0x08, 0x1D, 0x08, 0x1E, 0x08, 0x24, 0x08, 0x25, 0x02,
    0x26, 0x02, 0x2B, 0x02, 0x2C, 0x20, 0x2D, 0x08, 0x2E, 0x00, 0x00,
    0x00, 0x00, 0x04, 0x25, 0x04, 0x26, 0x04, 0x27, 0x04, 0x28, 0x00};
static u8 anim_die[] = {
    0x08, 0x20, 0x08, 0x21, 0x08, 0x22, 0x08, 0x23, 0xFF, 0x00};
static u8 hitboxes[][4] = {
    {0, 0, 0, 0},
    {0, 6, 8, 26},
    {0, 11, 8, 21},
    {0, 12, 8, 20},
};
static u8 hitbox_lookup[] = {
    0, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 3, 1, 1, 1, 3, 1,
    1, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 3, 1, 1, 1, 3, 1, 0};
static u8 steps[] = {AXE_KNIGHT_STANDING_THROW, AXE_KNIGHT_DUCKING_THROW,
                     AXE_KNIGHT_STANDING_THROW, AXE_KNIGHT_DUCKING_THROW,
                     AXE_KNIGHT_STANDING_THROW, AXE_KNIGHT_DUCKING_THROW,
                     AXE_KNIGHT_STANDING_THROW, AXE_KNIGHT_DUCKING_THROW};
static u32 init_velocity_x[] = {FIX(2), FIX(2), FIX(1)};
static u32 init_velocity_y[] = {FIX(0), FIX(0), FIX(-4)};

// Weirdly, this function ONLY acts on prim->next, it does not act on prim.
// However, it does call functions on prim.
void func_801C3F9C(AxePrim* prim) {
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
            PlaySfxPositional(SFX_EXPLODE_B);
            UnkPolyFunc0((Primitive*)prim);
        }
        return;
    }
}

// Called by EntityAxeKnight
extern s16* sprites_nz0_3[];
s32 func_801C4198(Entity* axeKnight) {
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
        clutBase = g_EAxeKnightInit[3];
        dataPtr = sprites_nz0_3[axeKnight->animCurFrame];
        primIndex = g_api.AllocPrimitives(PRIM_GT4, *dataPtr * 2);
        if (primIndex != -1) {
            axeKnight->flags |= FLAG_HAS_PRIMS;
            axeKnight->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            axeKnight->ext.axeknight.prim = prim;
            dataPtr++;
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
                LOH(prim->next->r2) = *dataPtr++;
                if (axeKnight->facingLeft) {
                    prim->next->x1 -= LOH(prim->next->r2) / 2;
                } else {
                    prim->next->x1 += LOH(prim->next->r2) / 2;
                }
                LOH(prim->next->b2) = *dataPtr++;
                prim->next->y0 += LOH(prim->next->b2) / 2;
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
        PlaySfxPositional(SFX_FM_EXPLODE_B);
        axeKnight->step_s++;
        break;
    case 1:
        flag = 0;
        for (prim = axeKnight->ext.axeknight.prim; prim != NULL;) {
            if (prim->p3 & 8) {
                func_801C3F9C(prim);
                flag = 1;
            }
            prim = prim->next;
            prim = prim->next;
        }
        if (!flag) {
            return 1;
        }
        break;
    }
    return 0;
}

void func_801C4550(void) {
    if (g_CurrentEntity->ext.generic.unk80.modeS16.unk2 > 0) {
        g_CurrentEntity->ext.generic.unk80.modeS16.unk2 -= 3;
    } else {
        SetStep(steps[(Random() & 7)]);
        g_CurrentEntity->ext.generic.unk80.modeS16.unk2 = 256;
    }
}

// green knight that throws axes
void EntityAxeKnight(Entity* self) {
    Entity* newEntity;
    u8 animStatus;
    s8* hitbox;
    s16 temp;

    if (self->flags & FLAG_DEAD) {
        if (self->step != AXE_KNIGHT_DYING) {
            PlaySfxPositional(NA_SE_VO_AXE_KNIGHT_SCREAM);
            func_801B3B78();
            self->hitboxState = 0;
            self->ext.generic.unk80.modeS16.unk0 = 65;
            self->zPriority -= 0x10;
            SetStep(AXE_KNIGHT_DYING);
        }
    }

    switch (self->step) {
    case AXE_KNIGHT_INIT:
        InitializeEntity(g_EAxeKnightInit);
        self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        self->hitboxOffY = 10;
        self->ext.generic.unk7C.S8.unk1 = 0;
        self->ext.generic.unk80.modeS16.unk2 = 512;

    case AXE_KNIGHT_IDLE:
        if (func_801BCCFC(sensors_ground) & 1) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            SetStep(AXE_KNIGHT_WALK_TOWARDS_PLAYER);
        }
        break;

    case AXE_KNIGHT_WALK_TOWARDS_PLAYER:
        if (self->step_s == 0) {
            if (self->facingLeft == 0) {
                self->velocityX = FIX(-0.1875);
            } else {
                self->velocityX = FIX(0.1875);
            }
            self->step_s++;
        }

        animStatus = AnimateEntity(anim_walk, self);
        if (self->animFrameDuration == 0) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        }

        if (animStatus == 0) {
            if (self->facingLeft == 0) {
                self->velocityX = FIX(-0.1875);
            } else {
                self->velocityX = FIX(0.1875);
            }
            if (GetDistanceToPlayerX() < 96) {
                SetStep(AXE_KNIGHT_WALK_AWAY_FROM_PLAYER);
                self->ext.generic.unk7C.S8.unk0 = 1;
            }
        }

        if ((self->animFrameIdx == 1) || (self->animFrameIdx == 4)) {
            if (self->facingLeft == 0) {
                self->velocityX -= 0x300;
            } else {
                self->velocityX += 0x300;
            }
        } else if (self->facingLeft != 0) {
            self->velocityX -= 0x300;
        } else {
            self->velocityX += 0x300;
        }

        if (UnkCollisionFunc2(sensors_move) & 0x60) {
            self->posX.val -= self->velocityX;
            self->velocityX = 0;
        }
        func_801C4550();
        break;

    case AXE_KNIGHT_WALK_AWAY_FROM_PLAYER:
        if (self->step_s == 0) {
            if (self->facingLeft == 0) {
                self->velocityX = FIX(0.1875);
            } else {
                self->velocityX = FIX(-0.1875);
            }
            self->step_s++;
        }

        animStatus = AnimateEntity(anim_walk, self);
        if (self->animFrameDuration == 0) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        }
        if (animStatus == 0) {
            if (self->facingLeft == 0) {
                self->velocityX = FIX(0.1875);
            } else {
                self->velocityX = FIX(-0.1875);
            }

            if (GetDistanceToPlayerX() > 80) {
                SetStep(AXE_KNIGHT_WALK_TOWARDS_PLAYER);
                self->ext.generic.unk7C.S8.unk0 = 0;
            }
        }

        if ((self->animFrameIdx == 1) || (self->animFrameIdx == 4)) {
            if (self->facingLeft == 0) {
                self->velocityX += 0x200;
            } else {
                self->velocityX -= 0x200;
            }
        } else if (self->facingLeft != 0) {
            self->velocityX += 0x200;
        } else {
            self->velocityX -= 0x200;
        }

        if (UnkCollisionFunc2(sensors_move) & 0x60) {
            self->posX.val -= self->velocityX;
            self->velocityX = 0;
        }
        func_801C4550();
        break;

    case AXE_KNIGHT_STANDING_THROW:
        animStatus = AnimateEntity(anim_throw_stand, self);
        if (animStatus == 0) {
        label:
            if (GetDistanceToPlayerX() < 89) {
                SetStep(AXE_KNIGHT_WALK_AWAY_FROM_PLAYER);
                self->ext.generic.unk7C.S8.unk0 = 1;
            } else {
                SetStep(AXE_KNIGHT_WALK_TOWARDS_PLAYER);
                self->ext.generic.unk7C.S8.unk0 = 0;
            }
        } else if ((animStatus & 0x80) && (self->animFrameIdx == 7)) {
            PlaySfxPositional(NA_SE_VO_AXE_KNIGHT_THROW);
            newEntity = AllocEntity(g_Entities + 160, g_Entities + 192);
            if (newEntity != NULL) {
                CreateEntityFromCurrentEntity(E_AXE_KNIGHT_AXE, newEntity);
                newEntity->facingLeft = self->facingLeft;
                newEntity->posY.i.hi -= 12;
                if (newEntity->facingLeft != 0) {
                    newEntity->posX.i.hi += 8;
                } else {
                    newEntity->posX.i.hi -= 8;
                }
            }
        }
        break;

    case AXE_KNIGHT_DUCKING_THROW:
        animStatus = AnimateEntity(anim_throw_duck, self);
        if (animStatus != 0) {
            if ((animStatus & 0x80) && (self->animFrameIdx == 6)) {
                PlaySfxPositional(NA_SE_VO_AXE_KNIGHT_THROW);
                newEntity = AllocEntity(g_Entities + 160, g_Entities + 192);
                if (newEntity != NULL) {
                    CreateEntityFromCurrentEntity(E_AXE_KNIGHT_AXE, newEntity);
                    newEntity->facingLeft = self->facingLeft;
                    newEntity->params = 1;
                    newEntity->posY.i.hi += 12;
                    if (newEntity->facingLeft != 0) {
                        newEntity->posX.i.hi += 8;
                    } else {
                        newEntity->posX.i.hi -= 8;
                    }
                }
            }
        } else {
            goto label;
        }
        break;

    case AXE_KNIGHT_ARCING_THROW: // unused
        animStatus = AnimateEntity(anim_throw_stand, self);
        if (animStatus == 0) {
            if (GetDistanceToPlayerX() > 88) {
                SetStep(AXE_KNIGHT_WALK_TOWARDS_PLAYER);
                self->ext.generic.unk7C.S8.unk0 = 0;
            } else {
                SetStep(AXE_KNIGHT_WALK_AWAY_FROM_PLAYER);
                self->ext.generic.unk7C.S8.unk0 = 1;
            }
            break;
        }

        if ((animStatus & 0x80) && (self->animFrameIdx == 7)) {
            PlaySfxPositional(NA_SE_VO_AXE_KNIGHT_THROW);
            newEntity = AllocEntity(g_Entities + 160, g_Entities + 192);
            if (newEntity != NULL) {
                CreateEntityFromCurrentEntity(E_AXE_KNIGHT_AXE, newEntity);
                newEntity->facingLeft = self->facingLeft;
                newEntity->params = 2;
                newEntity->posY.i.hi -= 40;
                if (newEntity->facingLeft != 0) {
                    newEntity->posX.i.hi += 16;
                } else {
                    newEntity->posX.i.hi -= 16;
                }
            }
        }
        break;

    case AXE_KNIGHT_DYING:
        if (self->ext.generic.unk80.modeS16.unk0 != 0) {
            temp = --self->ext.generic.unk80.modeS16.unk0;
            if (!(self->ext.generic.unk80.modeS16.unk0 & 7)) {
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

        if (AnimateEntity(anim_die, self) == 0) {
            if (func_801C4198(self) != 0) {
                DestroyEntity(self);
                return;
            }
            if (self->step_s < 16) {
                self->animCurFrame = 0;
            }
        }
        break;
    }
    hitbox = hitboxes;
    hitbox += hitbox_lookup[self->animCurFrame] * 4;
    self->hitboxOffX = *hitbox++;
    self->hitboxOffY = *hitbox++;
    self->hitboxWidth = hitbox[0];
    self->hitboxHeight = hitbox[1];
}

void EntityAxeKnightRotateAxe(void) {
    if (g_CurrentEntity->params != 0) {
        g_CurrentEntity->rotZ += 0x80;
    } else {
        g_CurrentEntity->rotZ -= 0x80;
    }

    g_CurrentEntity->rotZ &= 0xFFF;
}

void EntityAxeKnightThrowingAxe(Entity* entity) {
    s32 velocityX;

    if (entity->flags & FLAG_DEAD) {
        PlaySfxPositional(SFX_WEAPON_BREAK);
        EntityExplosionSpawn(0, 0);
        return;
    }

    switch (entity->step) {
    case 0:
        InitializeEntity(D_80180C70);
        entity->drawFlags = FLAG_DRAW_ROTZ;
        entity->velocityY = init_velocity_y[entity->params];
        velocityX = init_velocity_x[entity->params];

        if (entity->facingLeft == 0) {
            entity->velocityX = -velocityX;
        } else {
            entity->velocityX = velocityX;
        }

        entity->ext.generic.unk7C.s = -0x40;

        if (entity->params == 2) {
            entity->step++;
            return;
        }
        break;

    case 1:
        EntityAxeKnightRotateAxe();
        if ((u16)entity->ext.generic.unk7C.s < 0x20) {
            if (entity->facingLeft != 0) {
                entity->velocityX -= FIX(0.125);
            } else {
                entity->velocityX += FIX(0.125);
            }
        }

        entity->ext.generic.unk7C.s++;
        MoveEntity();
        break;

    case 2:
        EntityAxeKnightRotateAxe();
        entity->velocityY += FIX(0.125);
        MoveEntity();
        break;
    }
}
