/*
 * Overlay: NZ0
 * Enemy: Axe Knight
 * Description: Low level Axe Knight
 */

#include "nz0.h"
#include "sfx.h"

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
            func_801C29B0(SFX_EXPLODE_B);
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
        clutBase = D_80180C6A;
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
        func_801C29B0(SFX_FM_EXPLODE_B);
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
        SetStep(D_801822B4[(Random() & 7)]);
        g_CurrentEntity->ext.generic.unk80.modeS16.unk2 = 256;
    }
}

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

// green knight that throws axes
void EntityAxeKnight(Entity* self) {
    Entity* newEntity;
    u8 animStatus;
    s8* hitbox;
    s16 temp;

    if (self->flags & FLAG_DEAD) {
        if (self->step != AXE_KNIGHT_DYING) {
            func_801C29B0(NA_SE_VO_AXE_KNIGHT_SCREAM);
            func_801B3B78();
            self->hitboxState = 0;
            self->ext.generic.unk80.modeS16.unk0 = 65;
            self->zPriority -= 0x10;
            SetStep(AXE_KNIGHT_DYING);
        }
    }

    switch (self->step) {
    case AXE_KNIGHT_INIT:
        InitializeEntity(D_80180C64);
        self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        self->hitboxOffY = 10;
        self->ext.generic.unk7C.S8.unk1 = 0;
        self->ext.generic.unk80.modeS16.unk2 = 512;

    case AXE_KNIGHT_IDLE:
        if (func_801BCCFC(&D_80182188) & 1) {
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

        animStatus = AnimateEntity(D_80182210, self);
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

        if (func_801BCF74(&D_80182180) & 0x60) {
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

        animStatus = AnimateEntity(D_80182210, self);
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

        if (func_801BCF74(&D_80182180) & 0x60) {
            self->posX.val -= self->velocityX;
            self->velocityX = 0;
        }
        func_801C4550();
        break;

    case AXE_KNIGHT_STANDING_THROW:
        animStatus = AnimateEntity(D_80182244, self);
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
            func_801C29B0(NA_SE_VO_AXE_KNIGHT_THROW);
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
        animStatus = AnimateEntity(D_80182220, self);
        if (animStatus != 0) {
            if ((animStatus & 0x80) && (self->animFrameIdx == 6)) {
                func_801C29B0(NA_SE_VO_AXE_KNIGHT_THROW);
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
        animStatus = AnimateEntity(D_80182244, self);
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
            func_801C29B0(NA_SE_VO_AXE_KNIGHT_THROW);
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
                    newEntity->posX.i.hi += D_80182198[temp];
                    newEntity->posY.i.hi += D_8018219A[temp];
                }
            }
        }

        if (AnimateEntity(D_80182268, self) == 0) {
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
    hitbox = &D_80182284[self->animCurFrame][D_80182274];
    hitbox++;
    hitbox--;
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
        func_801C29B0(NA_SE_EN_AXE_KNIGHT_BREAK_AXE);
        EntityExplosionSpawn(0, 0);
        return;
    }

    switch (entity->step) {
    case 0:
        InitializeEntity(D_80180C70);
        entity->drawFlags = FLAG_DRAW_ROTZ;
        entity->velocityY = D_801822C8[entity->params];
        velocityX = D_801822BC[entity->params];

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
