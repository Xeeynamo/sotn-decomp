// SPDX-License-Identifier: AGPL-3.0-or-later
#include "cat.h"

extern EInit g_EInitBoneArk;
extern EInit g_EInitBoneArkSkeleton;
extern EInit g_EInitBoneArkNeck;
extern EInit g_EInitBoneArkAttackEffects;
extern EInit g_EInitBoneArkProjectile;

static s16 sensors_skeleton[] = {0, 22, 4, 0};
static s16 sensors_ground[] = {0, 22, 0, 4, 8, -4, -16, 0};
static AnimateEntityFrame anim_skeleton_walk[] = {
    {.duration = 7, .pose = 0x01},
    {.duration = 7, .pose = 0x02},
    {.duration = 7, .pose = 0x03},
    {.duration = 7, .pose = 0x02},
    POSE_LOOP(0)};
static AnimateEntityFrame anim_skeleton_flee[] = {
    {.duration = 2, .pose = 0x27},
    {.duration = 2, .pose = 0x28},
    {.duration = 2, .pose = 0x29},
    {.duration = 2, .pose = 0x28},
    {.duration = 2, .pose = 0x27},
    {.duration = 2, .pose = 0x28},
    {.duration = 2, .pose = 0x29},
    {.duration = 2, .pose = 0x28},
    POSE_LOOP(0)};
static AnimateEntityFrame anim_skeleton_death[] = {
    {.duration = 16, .pose = 0x01}, {.duration = 5, .pose = 0x05},
    {.duration = 4, .pose = 0x06},  {.duration = 5, .pose = 0x07},
    {.duration = 4, .pose = 0x08},  {.duration = 5, .pose = 0x09},
    {.duration = 4, .pose = 0x0A},  {.duration = 5, .pose = 0x0B},
    {.duration = 5, .pose = 0x0C},  {.duration = 5, .pose = 0x0B},
    {.duration = 81, .pose = 0x0C}, POSE_END};
static AnimateEntityFrame anim_projectile[] = {
    {.duration = 2, .pose = 0x15},
    {.duration = 1, .pose = 0x19},
    {.duration = 2, .pose = 0x16},
    {.duration = 1, .pose = 0x19},
    {.duration = 2, .pose = 0x17},
    {.duration = 1, .pose = 0x19},
    {.duration = 2, .pose = 0x18},
    {.duration = 1, .pose = 0x19},
    POSE_LOOP(0)};
static AnimateEntityFrame anim_lightning[] = {
    {.duration = 1, .pose = 0x1B},
    {.duration = 1, .pose = 0x1C},
    {.duration = 2, .pose = 0x1D},
    {.duration = 3, .pose = 0x1E},
    {.duration = 2, .pose = 0x1F},
    {.duration = 1, .pose = 0x20},
    {.duration = 1, .pose = 0x21},
    {.duration = 2, .pose = 0x22},
    {.duration = 1, .pose = 0x23},
    {.duration = 2, .pose = 0x24},
    {.duration = 1, .pose = 0x25},
    {.duration = 1, .pose = 0x26},
    POSE_LOOP(0)};

// params 0 = projectile
// params 1 = lightning ball
void EntityBoneArkProjectile(Entity* self) {
    Primitive* prim;
    Entity* lightningBallEntity;
    s32 i;
    s32 primIndex;
    s16 projectileVelocity;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitBoneArkProjectile);
        self->drawFlags |= FLAG_DRAW_ROTATE;
        if (self->params) {
            self->drawFlags |= FLAG_DRAW_SCALEY | FLAG_DRAW_SCALEX;
            self->scaleX = self->scaleY = 0;
            self->animCurFrame = 0x1A;
            self->palette = PAL_OVL(PAL_BONE_ARK_LIGHTNING_BALL);
            lightningBallEntity = self->ext.boneArk.entity;
            self->zPriority = lightningBallEntity->zPriority - 2;
            self->ext.boneArk.unk8C.i.lo = 8;
            self->step = 16;
        } else {
            self->palette = PAL_OVL(PAL_BONE_ARK_PROJECTILE);
            self->ext.boneArk.projectileVelocity = FIX(8);
        }
        if (self->params) {
            primIndex = g_api.AllocPrimitives(PRIM_GT4, 2);
        } else {
            primIndex = g_api.AllocPrimitives(PRIM_GT4, 8);
        }

        if (primIndex != -1) {
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            self->ext.boneArk.prim = prim;
            while (prim != NULL) {
                UnkPolyFunc2(prim);
                prim->tpage = 0x1A;
                prim->u0 = 0;
                prim->u1 = 0x3F;
                prim->u2 = prim->u0;
                prim->u3 = prim->u1;
                prim->v0 = 0xC0;
                prim->v1 = prim->v0;
                prim->v2 = 0xFF;
                prim->v3 = prim->v2;
                prim->next->x1 = self->posX.i.hi;
                prim->next->y0 = self->posY.i.hi;
                if (self->params) {
                    prim->clut = PAL_DRA(PAL_BONE_ARK_LIGHTNING_PRIM);
                    prim->priority = self->zPriority - 1;
                    prim->drawMode =
                        DRAW_TPAGE | DRAW_COLORS | DRAW_UNK02 | DRAW_TRANSP;
                    prim->next->b3 = 0xC0;
                    LOH(prim->next->r2) = 0x40;
                    LOH(prim->next->b2) = 0x40;
                    prim->next->x2 = 0;
                    prim->next->y2 = 0;
                    prim->p3 |= 0x10;
                } else {
                    prim->clut = PAL_DRA(PAL_HELLFIRE_BEAST_CAST_TWO);
                    prim->priority = self->zPriority - 3;
                    prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS |
                                     DRAW_UNK02 | DRAW_TRANSP;
                    prim->next->b3 = 0x80;
                    LOH(prim->next->r2) = 0;
                    LOH(prim->next->b2) = 0;
                }
                prim = prim->next;
                prim = prim->next;
            }
        } else {
            if (self->params) {
                lightningBallEntity = self->ext.boneArk.entity;
                lightningBallEntity->ext.boneArk.entity = NULL;
            }
            DestroyEntity(self);
            return;
        }

        break;
    case 1:
        AnimateEntity(anim_projectile, self);
        MoveEntity();

        // Projectile decreases in speed as it travels
        self->ext.boneArk.projectileVelocity -= FIX(0.25);
        projectileVelocity = self->ext.boneArk.projectileVelocity >> 0xC;
        self->velocityX = rcos(self->ext.boneArk.unk94) * projectileVelocity;
        self->velocityY = -rsin(self->ext.boneArk.unk94) * projectileVelocity;

        // Once the projectile has completely stopped,
        // it explodes and spawns the lightning ball
        if (!self->ext.boneArk.projectileVelocity) {
            g_api.PlaySfx(SFX_FM_EXPLODE_B);
            self->palette = PAL_DRA(PAL_BONE_ARK_PROJECTILE_EXPLODE);
            self->drawFlags |= FLAG_DRAW_SCALEY | FLAG_DRAW_SCALEX;
            self->scaleX = self->scaleY = 0;
            self->pose = 0;
            self->poseTimer = 0;
            self->step_s = 0;
            self->ext.boneArk.unk90 = 0;

            // nb. likely this should be a different struct
            self->ext.boneArk.skeletonDied = 0x10;
            self->ext.boneArk.unk8C.i.lo = 0;
            self->step++;
            lightningBallEntity =
                AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (lightningBallEntity != NULL) {
                CreateEntityFromEntity(
                    E_BONE_ARK_PROJECTILE, self, lightningBallEntity);
                lightningBallEntity->params = 1;
                lightningBallEntity->ext.boneArk.entity = self;
                self->ext.boneArk.entity = lightningBallEntity;
            } else {
                self->ext.boneArk.entity = NULL;
            }
        }
        break;
    case 2:
        self->rotate += ROT(135);
        AnimateEntity(anim_lightning, self);
        switch (self->step_s) {
        case 0:
            self->scaleX += 0x10;
            self->scaleY = self->scaleX;
            if (self->scaleX == 0xC0) {
                self->step_s++;
            }
            break;
        case 1:
            self->scaleX += 4;
            self->scaleY = self->scaleX;
            if (self->scaleX == 0x100) {
                self->step_s++;
            }
            break;
        case 2:
            prim = self->ext.boneArk.prim;
            if (self->ext.boneArk.unk8C.i.lo % 2) {
                self->scaleX -= 0x20;
            } else {
                self->scaleX += 0x20;
            }
            self->scaleY = self->scaleX;
            self->ext.boneArk.unk8C.i.lo++;
            if (!(self->ext.boneArk.unk8C.i.lo & 0xF)) {
                g_api.PlaySfx(SFX_THUNDER_B);
            }
            if (self->ext.boneArk.unk8C.i.lo > 0x40) {
                self->drawMode |= DRAW_TPAGE2 | DRAW_TPAGE;
                self->drawFlags |= FLAG_DRAW_OPACITY;
                self->opacity = 0xC0;
                self->step_s = 0;
                LOH(prim->next->r2) = 0x40;
                LOH(prim->next->b2) = 0x40;
                self->ext.boneArk.unk90++;
                self->hitboxState = 0;
                g_api.PlaySfx(SFX_FM_THUNDER_EXPLODE);
                self->step++;
            }
            break;
        }

        if (!self->ext.boneArk.skeletonDied) {
            switch (self->ext.boneArk.unk90) {
            case 0:
                prim = self->ext.boneArk.prim;
                prim->next->x1 = self->posX.i.hi;
                prim->next->y0 = self->posY.i.hi;
                LOH(prim->next->r2) = 0x30;
                LOH(prim->next->b2) = 0x30;
                self->ext.boneArk.unk90++;
                break;
            case 1:
                prim = self->ext.boneArk.prim;
                LOH(prim->next->r2)++;
                LOH(prim->next->b2)++;
                if (LOH(prim->next->r2) > 0x40) {
                    self->hitboxState = 1;
                    self->ext.boneArk.unk90++;
                }
                break;
            case 2:
                if (!(g_Timer % 2)) {
                    LOH(prim->next->r2) = 0x40;
                    LOH(prim->next->b2) = 0x40;
                } else {
                    LOH(prim->next->r2) = 0x20;
                    LOH(prim->next->b2) = 0x20;
                }
                break;
            }
        } else {
            self->ext.boneArk.skeletonDied--;
        }
        break;
    case 3:
        if (self->animCurFrame) {
            AnimateEntity(anim_lightning, self);
        }
        self->opacity -= 4;
        self->scaleX += 0x20;
        self->scaleY -= 8;
        if (!self->opacity) {
            self->animCurFrame = 0;
        }

        prim = self->ext.boneArk.prim;
        switch (self->step_s) {
        case 0:
            if (!(g_Timer % 3)) {
                LOH(prim->next->r2)++;
                LOH(prim->next->b2)++;
                if (LOH(prim->next->r2) > 0x42) {
                    prim->next->b3 = 0x40;
                    prim->priority = self->zPriority;
                }

                if (LOH(prim->next->r2) == 0x48) {
                    self->step_s++;
                    self->ext.boneArk.unk8C.i.lo = 0x200;
                    if (self->ext.boneArk.entity != NULL) {
                        self->ext.boneArk.entity->step_s++;
                    }

                    prim = prim->next;
                    prim = prim->next;
                    i = 0;
                    while (prim != NULL) {
                        prim->u0 = 0x40;
                        prim->u1 = 0x7F;
                        prim->u2 = prim->u0;
                        prim->u3 = prim->u1;
                        prim->v0 = 0xC0;
                        prim->v1 = prim->v0;
                        prim->v2 = 0xFF;
                        prim->v3 = prim->v2;
                        LOH(prim->next->r2) = 0x40;
                        LOH(prim->next->b2) = 0x40;
                        prim->next->x2 = 0x1400 - (i << 9);
                        prim->next->y2 = 0x1400 - (i << 9);
                        prim->next->b3 = 0x80;
                        prim->next->x1 = self->posX.i.hi;
                        prim->next->y0 = self->posY.i.hi;
                        prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_HIDE |
                                         DRAW_COLORS | DRAW_UNK02 | DRAW_TRANSP;
                        prim->p3 |= 0x30;
                        prim->next->y3 = i * 0x180;
                        prim->next->r3 = i;
                        LOHU(prim->next->u3) = i * 8;
                        prim = prim->next;
                        prim = prim->next;
                        i++;
                    }
                }
            }
            break;
        case 1:
            if (LOH(prim->next->r2)) {
                LOH(prim->next->r2) -= 2;
                LOH(prim->next->b2) -= 2;
            }

            prim = prim->next;
            prim = prim->next;
            while (prim != NULL) {
                if (!LOHU(prim->next->u3)) {
                    prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS |
                                     DRAW_UNK02 | DRAW_TRANSP;
                    prim->next->x2 += 0x100;
                    prim->next->y2 += 0x100;
                    prim->next->b3 -= 4;
                    if (prim->next->r3 % 2) {
                        prim->next->x3 += 0x40;
                        prim->next->y3 += 0x80;
                        LOH(prim->next->tpage) += 0x20;
                    } else {
                        prim->next->x3 -= 0x40;
                        prim->next->y3 -= 0x80;
                        LOH(prim->next->tpage) -= 0x20;
                    }

                    if (!prim->next->b3) {
                        prim->drawMode = DRAW_HIDE;
                        LOHU(prim->next->u3)--;
                    }
                } else {
                    LOHU(prim->next->u3)--;
                }
                prim = prim->next;
                prim = prim->next;
            }

            if (!--self->ext.boneArk.unk8C.i.lo) {
                DestroyEntity(self);
                return;
            }
        }
        break;
    case 16:
        self->rotate += 2;
        switch (self->step_s) {
        case 0:
            if (!self->ext.boneArk.unk8C.i.lo) {
                self->scaleX += 0x10;
                self->scaleY = self->scaleX;
                if (self->scaleX == 0x100) {
                    self->step_s++;
                }
            } else {
                self->ext.boneArk.unk8C.i.lo--;
            }
        case 1:
            break;
        case 2:
            self->scaleX -= 0x10;
            self->scaleY -= 0x10;
            if (!self->scaleX) {
                self->animCurFrame = 0;
                self->drawFlags = FLAG_DRAW_DEFAULT;
                self->drawMode = DRAW_DEFAULT;
                self->step_s++;
            }
            break;
        case 3:
            prim = self->ext.boneArk.prim;
            prim->next->b3 -= 2;
            LOH(prim->next->tpage) += 0x128;
            if (!prim->next->b3) {
                DestroyEntity(self);
                return;
            }
            break;
        }

        if (self->step_s < 3) {
            prim = self->ext.boneArk.prim;
            prim->next->x2 = ((self->scaleX + 0x60) << 4);
            prim->next->y2 = ((self->scaleY + 0x60) << 4);
        }

        break;
    }

    prim = self->ext.boneArk.prim;
    while (prim != NULL) {
        if (prim->p3 & 8) {
            UnkPrimHelper(prim);
        }
        prim = prim->next;
    }
}

// Draws the charge lines which seek towards the attacking skull
static void DrawChargeLines(Primitive* prim) {
    Pos pos;
    s32 dx;
    s32 dy;
    u8 var_s2;

    switch (prim->p1) {
    case 0:
        var_s2 = (Random() & 0x1F);
        var_s2 = var_s2 + 0x70 + (g_CurrentEntity->rotate / 16);
        prim->x0 = g_CurrentEntity->posX.i.hi +
                   ((rcos((var_s2) * 0x10) * 0x78) >> 0xC);
        prim->y0 = g_CurrentEntity->posY.i.hi +
                   ((rsin((var_s2) * 0x10) * 0x78) >> 0xC);
        prim->x1 = prim->x0;
        prim->y1 = prim->y0;
        prim->x2 = 0;
        prim->y2 = 0;
        LOH(prim->u2) = 0;
        LOH(prim->u3) = 0;

        prim->r0 = 0x80;
        prim->g0 = 0x40;
        prim->b0 = 0x40;

        prim->r1 = 0x40;
        prim->g1 = 0x40;
        prim->b1 = 0x80;

        LOW(prim->u0) = 0;
        LOW(prim->u1) = 0;
        LOW(prim->r2) = 0;
        LOW(prim->x3) = 0;

        dx = (prim->x0 << 0x10) - g_CurrentEntity->posX.val;
        dy = (prim->y0 << 0x10) - g_CurrentEntity->posY.val;
        LOH(prim->r3) = ratan2(dy, -dx);
        prim->priority = g_CurrentEntity->zPriority - 2;
        prim->drawMode =
            DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_UNK02 | DRAW_TRANSP;
        prim->b3 = 0x2C;
        prim->p1 = 1;
        break;
    case 1:
        dx = (LOW(prim->u0) >> 0xC) * rcos(LOH(prim->r3));
        dy = -(LOW(prim->u0) >> 0xC) * rsin(LOH(prim->r3));
        pos.x.i.hi = prim->x0;
        pos.x.i.lo = prim->x2;
        pos.y.i.hi = prim->y0;
        pos.y.i.lo = prim->y2;
        pos.x.val += dx;
        pos.y.val += dy;
        prim->x0 = pos.x.i.hi;
        prim->x2 = pos.x.i.lo;
        prim->y0 = pos.y.i.hi;
        prim->y2 = pos.y.i.lo;
        LOW(prim->r2) += 0x100;
        LOW(prim->u0) += LOW(prim->r2) * 8;
        if (LOW(prim->u0) > 0x72000) {
            LOW(prim->r2) = -LOW(prim->r2);
        }
        if (LOW(prim->u0) < 0) {
            LOW(prim->u0) = 0x8000;
            LOW(prim->u1) = 0x8000;
        }
        LOW(prim->r2) += 0x100;
        dx = prim->x0 - g_CurrentEntity->posX.i.hi;
        dy = prim->y0 - g_CurrentEntity->posY.i.hi;
        if (abs(dx) < 4 && abs(dy) < 4) {
            prim->p1 = 2;
        }
        // fallthrough
    case 2:
        dx = (LOW(prim->u1) >> 0xC) * rcos(LOH(prim->r3));
        dy = -(LOW(prim->u1) >> 0xC) * rsin(LOH(prim->r3));
        pos.x.i.hi = prim->x1;
        pos.x.i.lo = LOH(prim->u2);
        pos.y.i.hi = prim->y1;
        pos.y.i.lo = LOH(prim->u3);
        pos.x.val += dx;
        pos.y.val += dy;
        prim->x1 = pos.x.i.hi;
        LOH(prim->u2) = pos.x.i.lo;
        prim->y1 = pos.y.i.hi;
        LOH(prim->u3) = pos.y.i.lo;
        if (prim->b3 < 0x28) {
            LOW(prim->x3) += 0x100;
            LOW(prim->u1) += LOW(prim->x3) * 8;
            if (LOW(prim->u1) > 0x72000) {
                LOW(prim->x3) = -LOW(prim->x3);
            }
            if (LOW(prim->u1) < 0) {
                LOW(prim->u1) = 0x8000;
            }
        }

        prim->b3--;
        dx = prim->x1 - g_CurrentEntity->posX.i.hi;
        dy = prim->y1 - g_CurrentEntity->posY.i.hi;
        if (abs(dx) < 8 && abs(dy) < 8) {
            prim->drawMode = DRAW_HIDE;
            prim->p3 = 0;
        }

        if (!prim->b3) {
            prim->drawMode = DRAW_HIDE;
            prim->p3 = 0;
        }

        break;
    }
}

extern Primitive* FindFirstUnkPrim(Primitive* poly);
void EntityBoneArkAttackEffects(Entity* self) {
    Primitive* prim;
    Entity* entity;
    s32 primIndex;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitBoneArkAttackEffects);
        self->animCurFrame = 0x2A;
        self->palette = PAL_OVL(PAL_BONE_ARK_PROJECTILE);
        self->drawFlags =
            FLAG_DRAW_OPACITY | FLAG_DRAW_ROTATE | FLAG_DRAW_SCALEX;
        self->drawMode = DRAW_TPAGE2 | DRAW_TPAGE;
        self->scaleX = 0x100;
        self->opacity = 0;
        self->hitboxState = 0;
        self->zPriority = self->ext.boneArk.entity->zPriority + 1;
        primIndex = g_api.AllocPrimitives(PRIM_LINE_G2, 0x10);
        if (primIndex != -1) {
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            self->ext.boneArk.prim = prim;
            break;
        }

        entity = self->ext.boneArk.entity;
        entity->ext.boneArk.entity = NULL;
        DestroyEntity(self);
        break;
    case 1:
        entity = self->ext.boneArk.entity;
        self->posX.i.hi = entity->posX.i.hi;
        self->posY.i.hi = entity->posY.i.hi;
        self->rotate = entity->rotate;
        self->opacity++;
        if (!(g_Timer % 8)) {
            prim = self->ext.boneArk.prim;
            prim = FindFirstUnkPrim(prim);
            if (prim != NULL) {
                prim->p3 = 2;
                prim->p1 = 0;
            }
        }

        if (!(g_Timer & 0x1F)) {
            PlaySfxPositional(SFX_BONE_ARK_CHARGE_ATTACK);
        }

        prim = self->ext.boneArk.prim;
        while (prim != NULL) {
            if (prim->p3 & 2) {
                DrawChargeLines(prim);
            }
            prim = prim->next;
        }

        if (self->opacity > 0x78) {
            self->ext.boneArk.unk8C.i.lo = 0;
            self->step++;
        }
        break;
    case 2:
        entity = self->ext.boneArk.entity;
        self->posX.i.hi = entity->posX.i.hi;
        self->posY.i.hi = entity->posY.i.hi;
        self->rotate = entity->rotate;
        if (!self->step_s) {
            prim = self->ext.boneArk.prim;
            while (prim != NULL) {
                if (prim->p3 & 2) {
                    DrawChargeLines(prim);
                }
                prim = prim->next;
            }

            if (self->ext.boneArk.unk8C.i.lo++ > 0x20) {
                primIndex = self->primIndex;
                g_api.FreePrimitives(primIndex);
                self->flags &= ~FLAG_HAS_PRIMS;
                self->step_s++;
            }
        } else {
            self->opacity = 0x88;
        }
        break;
    case 3:
        self->scaleX += 4;
        self->opacity -= 4;
        if (self->opacity > 0xF0) {
            DestroyEntity(self);
        }
        break;
    }
}

void EntityBoneArkSkull(Entity* self) {
    Entity* entity;
    Entity* boneArkEntity;
    s16 angle;
    s16 dx;
    s16 dy;
    s32 primIndex;

    boneArkEntity = self - self->params;
    if (self->flags & FLAG_DEAD && self->step < 7) {
        PlaySfxPositional(SFX_QUICK_STUTTER_EXPLODE_B);
        self->animCurFrame = 0;
        self->hitboxState = 0;
        SetStep(7);
        boneArkEntity->ext.boneArk.headDying |= 1;
        if (self->flags & FLAG_HAS_PRIMS) {
            primIndex = self->primIndex;
            g_api.FreePrimitives(primIndex);
            self->flags &= ~FLAG_HAS_PRIMS;
        }

        if (self->ext.boneArk.entity != NULL) {
            entity = self->ext.boneArk.entity;
            DestroyEntity(entity);
        }
    }

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitBoneArkAttackEffects);
        self->ext.boneArk.unk80 = 0x800;
        self->zPriority = (self - self->params)->zPriority + 2;
        self->drawFlags |= FLAG_DRAW_ROTATE;
        self->ext.boneArk.unk82 = 8;
        break;
    case 1:
        self->ext.boneArk.unk80 += self->ext.boneArk.unk82;
        if (self->ext.boneArk.unk80 > (0x900 - boneArkEntity->rotate)) {
            self->ext.boneArk.unk82 = -8;
        }

        if (self->ext.boneArk.unk80 < (0x6D0 - boneArkEntity->rotate)) {
            self->ext.boneArk.unk82 = 8;
        }

        if (self->ext.boneArk.crouching) {
            self->ext.boneArk.unk8C.i.lo = 0x20;
            self->step_s = 0;
            self->step++;
        }
        break;
    case 2:
        switch (self->step_s) {
        case 0:
            entity = &PLAYER;
            dx = entity->posX.i.hi - self->posX.i.hi;
            dy = entity->posY.i.hi - self->posY.i.hi;
            dy -= 0x10;
            angle = ratan2(-dy, dx);
            angle += ROT(360);
            angle &= 0xF80;

            if (angle > (ROT(225) - boneArkEntity->rotate)) {
                angle = ROT(225) - boneArkEntity->rotate;
            }

            if (angle < (0x500 - boneArkEntity->rotate)) {
                angle = 0x500 - boneArkEntity->rotate;
            }

            angle &= 0xF00;
            self->ext.boneArk.unk94 = angle;
            self->step_s++;
            break;
        case 1:
            if (self->ext.boneArk.unk80 == self->ext.boneArk.unk94) {
                if (!--self->ext.boneArk.unk8C.i.lo) {
                    self->step++;
                    self->animCurFrame = 0xF;
                    boneArkEntity->ext.boneArk.unk90 |= 1;
                }
            } else if (self->ext.boneArk.unk80 > self->ext.boneArk.unk94) {
                self->ext.boneArk.unk80 -= 4;
            } else {
                self->ext.boneArk.unk80 += 4;
            }
            break;
        }
        break;
    case 3:
        entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (entity != NULL) {
            CreateEntityFromEntity(E_BONE_ARK_ATTACK_EFFECTS, self, entity);
            entity->ext.boneArk.entity = self;
            self->ext.boneArk.entity = entity;
        } else {
            self->ext.boneArk.entity = NULL;
        }
        self->step++;
        break;
    case 4:
        entity = self->ext.boneArk.entity;
        if (entity != NULL) {
            if (entity->opacity > 0x80) {
                boneArkEntity->ext.boneArk.unk90 |= 8;
                self->step++;
            }
        } else {
            boneArkEntity->ext.boneArk.unk90 |= 8;
            self->step++;
        }
        break;
    case 5:
        if (self->ext.boneArk.unk90) {
            g_api.PlaySfx(SFX_START_SLAM_B);
            entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_BONE_ARK_PROJECTILE, self, entity);
                entity->facingLeft = self->facingLeft;
                entity->ext.boneArk.unk94 = self->ext.boneArk.unk94;
                if (self->facingLeft) {
                    entity->posX.i.hi += 0x10;
                } else {
                    entity->posX.i.hi -= 0x10;
                }
            }
            boneArkEntity->ext.boneArk.unk90 = 0;
            self->ext.boneArk.unk90 = 0;
            self->step_s = 0;
            self->step++;
            entity = self->ext.boneArk.entity;
            if (entity != NULL) {
                entity->step++;
            }
        }
        break;
    case 6:
        switch (self->step_s) {
        case 0:
            self->ext.boneArk.unk80 -= 0x30;
            if (self->ext.boneArk.unk80 < self->ext.boneArk.unk94 - 0x300) {
                self->step_s++;
            }
            break;
        case 1:
            self->ext.boneArk.unk80 += 0x18;
            if (self->ext.boneArk.unk80 > self->ext.boneArk.unk94 + 0x100) {
                self->animCurFrame = 0xE;
                self->step_s++;
            }
            break;
        case 2:
            self->ext.boneArk.unk80 -= 8;
            if (self->ext.boneArk.unk80 < ROT(180) - boneArkEntity->rotate) {
                self->step = 1;
                self->step_s = 0;
            }
            break;
        }
        break;
    case 7:
        switch (self->step_s) {
        case 0:
            entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_EXPLOSION, self, entity);
                entity->params = 1;
            }
            self->step_s++;
            break;
        case 1:
            self->ext.boneArk.unk80 += self->ext.boneArk.unk82;
            if (self->ext.boneArk.unk80 > (ROT(225) - boneArkEntity->rotate)) {
                self->ext.boneArk.unk82 = -0x30;
            }
            if (self->ext.boneArk.unk80 < (ROT(90) - boneArkEntity->rotate)) {
                self->ext.boneArk.unk82 = 0x30;
            }
            break;
        }
        break;
    }
    self->rotate = ROT(180) - self->ext.boneArk.unk80;
    entity = self - 1;
    dx = (rcos(self->ext.boneArk.unk80) * 2) >> 0xC;
    dy = (rsin(self->ext.boneArk.unk80) * 2) >> 0xC;
    self->posX.i.hi = entity->posX.i.hi + dx;
    self->posY.i.hi = entity->posY.i.hi - dy;
}

void EntityBoneArkUpperNeck(Entity* self) {
    Entity* entity;
    Entity* boneArkEntity;
    s16 posX;
    s16 posY;

    boneArkEntity = self - self->params;
    entity = self + 1;
    if (boneArkEntity->ext.boneArk.headDying && self->step < 2) {
        self->ext.boneArk.unk8C.i.lo = 8;
        self->step = 2;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitBoneArkNeck);
        self->animCurFrame = 0x10;
        self->zPriority = (self - self->params)->zPriority + 1;
        // fallthrough
    case 1:
        // One piece is positioned off the bone ark entity,
        // the others are positioned off the prior neck piece in the chain
        if (self->params == 5) {
            entity = self - self->params;
        } else {
            entity = self - 1;
        }
        posX = (rcos(self->ext.boneArk.unk80) * 4) >> 0xC;
        posY = (rsin(self->ext.boneArk.unk80) * 4) >> 0xC;
        self->posX.i.hi = entity->posX.i.hi + posX;
        self->posY.i.hi = entity->posY.i.hi - posY;
        break;
    case 2:
        // Wait a short delay after the head explodes to also explode the neck
        if (!self->ext.boneArk.unk8C.i.lo) {
            entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_EXPLOSION, self, entity);
                entity->params = 0;
                entity->drawFlags |= FLAG_DRAW_ROTATE;
                entity->rotate = self->ext.boneArk.unk80 - ROT(90);
            }
            self->animCurFrame = 0;
            self->flags |= FLAG_DEAD;
            self->step_s++;
            if (self->step_s > 3) {
                // BUG: double assign to same field
                self->step = 1;
                self->step = 3;
            }
        } else {
            self->ext.boneArk.unk8C.i.lo--;
        }
        break;
    case 3:
        break;
    }
}

void EntityBoneArkLowerNeck(Entity* self) {
    Entity* siblingEntity;
    s32 dx;
    s32 dy;
    s16 angle;
    s32 xOffset;
    s32 yOffset;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitBoneArkNeck);
        self->animCurFrame += self->params - 1;
        // fallthrough
    case 1:
        // One piece is positioned off the bone ark entity,
        // the others are positioned off the prior neck piece in the chain
        siblingEntity = self - 1;
        dx = self->posX.val - siblingEntity->posX.val;
        dy = siblingEntity->posY.val - self->posY.val;
        xOffset = dx;
        yOffset = dy;
        dy -= FIX(1.5);
        dy -= (siblingEntity->ext.boneArk.unk8C.val << 8) >> 8;
        dx += (siblingEntity->ext.boneArk.unk88.val << 8) >> 8;

        angle = ((dx >> 0x10) * dx + (dy >> 0x10) * dy) >> 0x10;
        if (angle > 0x24) {
            angle = ratan2(dy, dx);
            dx = rcos(angle) * 4 * 16;
            dy = rsin(angle) * 4 * 16;
        }
        self->posX.val = siblingEntity->posX.val + dx;
        self->posY.val = siblingEntity->posY.val - dy;
        self->ext.boneArk.unk88.val = -(dx - xOffset);
        self->ext.boneArk.unk8C.val = -(yOffset - dy);
        break;
    }
}

// Renders the flying pieces of ark which burst into flames
static void RenderDeathParts(Primitive* prim) {
    Entity* newEntity;

    switch (prim->next->u2) {
    case 0:
        LOW(prim->next->u0) = (prim->next->r3 % 2) * 0x18000 - 0x8000 - 0x4000;
        LOW(prim->next->u0) += ((Random() & 3) << 0xD) - 0x4000;
        LOW(prim->next->r1) = -0x40000;
        LOW(prim->next->r1) -= (prim->next->r3 >> 1) << 0xD;
        LOW(prim->next->r1) += ((Random() & 3) << 0xE) - 0x8000;
        prim->next->u2 = 1;
        break;
    case 1:
        UnkPrimHelper(prim);
        if (prim->next->r3 % 2) {
            LOH(prim->next->tpage) += 0xD0 - ((prim->next->r3 >> 1) * 0x60);
            prim->next->x3 += ((Random() & 3) * 0x10) + 0x100;
            prim->next->y3 += ((Random() & 3) * 0x10) + 0x20;
        } else {
            LOH(prim->next->tpage) -= 0xD0 - ((prim->next->r3 >> 1) * 0x60);
            prim->next->x3 -= ((Random() & 3) * 0x10) + 0x100;
            prim->next->y3 -= ((Random() & 3) * 0x10) + 0x20;
        }

        LOW(prim->next->r1) += 0x3000 - ((prim->next->r3 >> 1) << 0xC);
        if (LOW(prim->next->r1) > ((prim->next->r3 >> 1) << 0xF) + 0x34000) {
            newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (newEntity != NULL) {
                CreateEntityFromCurrentEntity(E_EXPLOSION, newEntity);

                if (prim->next->r3 >> 1) {
                    newEntity->params = 2;
                } else {
                    newEntity->params = 3;
                }

                newEntity->facingLeft = prim->next->r3 % 2;
                newEntity->posX.i.hi = prim->next->x1;
                newEntity->posY.i.hi = prim->next->y0;
            }
            UnkPolyFunc0(prim);
        }
        break;
    }
}

typedef enum BoneArkStep {
    INIT = 0,
    IDLE_WALK = 1,
    CROUCHING = 2,
    CHARGING = 3,
    SHOT_FIRED = 4,
    DEATH = 8
};

extern Primitive* FindFirstUnkPrim2(Primitive* prim, u8 index);
void EntityBoneArk(Entity* self) {
    s16 xOffset;
    s16 yOffset;

    Primitive* prim;
    s32 i;
    Entity* entity;
    s16 var_s3;
    s16 angle;
    u8 var_s5;
    s32 primIndex;
    s32 dx;
    s32 dy;
    s32 pad[9];

    FntPrint("main_step %x\n", self->step);
    FntPrint("main_step_s %x\n", self->step_s);
    FntPrint("hd_flag %x\n", self->ext.boneArk.headDying);
    if (self->ext.boneArk.headDying && self->step < DEATH) {
        SetStep(DEATH);
    }

    switch (self->step) {
    case INIT:
        InitializeEntity(g_EInitBoneArk);
        self->drawFlags |= FLAG_DRAW_ROTATE;
        self->hitboxState = 0;
        self->rotate = 0;
        self->animCurFrame = 0xD;

        // Spawn the two skeletons which hold the ark
        entity = self - 1;
        CreateEntityFromEntity(E_BONE_ARK_SKELETON, self, entity);
        entity->posX.i.hi -= 0x18;
        entity->params = 1;
        entity->ext.boneArk.skeletonPosX = entity->posX.i.hi;
        entity->ext.boneArk.skeletonPosY = entity->posY.i.hi - 0x14;

        entity = self - 2;
        CreateEntityFromEntity(E_BONE_ARK_SKELETON, self, entity);
        entity->posX.i.hi += 0x16;
        entity->params = 2;
        entity->ext.boneArk.skeletonPosX = entity->posX.i.hi;
        entity->ext.boneArk.skeletonPosY = entity->posY.i.hi - 0x14;

        // Spawn 4 lower neck pieces that dangle below the ark
        for (i = 1; i < 5; i++) {
            entity = &self[i];
            CreateEntityFromEntity(E_BONE_ARK_LOWER_NECK, self, entity);
            entity->params = i;
        }

        // Spawn 4 upper neck pieces that support the skull
        for (i = 5; i < 9; i++) {
            entity = &self[i];
            CreateEntityFromEntity(E_BONE_ARK_UPPER_NECK, self, entity);
            entity->params = i;
        }

        // Spawn the skull
        entity = self + 9;
        CreateEntityFromEntity(E_BONE_ARK_SKULL, self, entity);
        entity->params = 9;

        self->ext.boneArk.unk88.i.lo = 0x400;
        self->ext.boneArk.unk82 = -0x18;
        self->ext.boneArk.unk8C.i.lo = 0x100;
        self->step_s = 1;
        // fallthrough
    case IDLE_WALK:
        entity = &PLAYER;
        if (!self->step_s) {
            self->ext.boneArk.unk8C.i.lo = 0x80;
            (self - 1)->step_s &= 16;
            (self - 2)->step_s &= 16;
            if (entity->posX.i.hi > self->posX.i.hi) {
                self->ext.boneArk.walkingRight = 1;
            } else {
                self->ext.boneArk.walkingRight = 0;
            }
            self->step_s++;
        }

        angle = self->posX.i.hi - entity->posX.i.hi;
        if ((u16)angle < 0x40) {
            (self - 1)->step_s &= 16;
            (self - 2)->step_s &= 16;
            self->ext.boneArk.walkingRight = 1;
        }

        self->ext.boneArk.unk88.i.lo += self->ext.boneArk.unk82;
        if (self->ext.boneArk.unk88.i.lo > ROT(180) - self->rotate) {
            self->ext.boneArk.unk82 = -0x18;
        }

        if (self->ext.boneArk.unk88.i.lo < -self->rotate) {
            self->ext.boneArk.unk82 = 0x18;
        }

        if (!--self->ext.boneArk.unk8C.i.lo) {
            self->step_s = 0;
            if ((u16)angle < 0xC0) {
                self->step++;
                (self - 1)->ext.boneArk.crouching = 1;
                (self - 2)->ext.boneArk.crouching = 1;
                (self + 9)->ext.boneArk.crouching = 1;
            }
        }

        break;
    case CROUCHING:
        angle = self->ext.boneArk.unk88.i.lo - (ROT(180) - self->rotate);
        if (abs(angle) < 8) {
            self->ext.boneArk.unk90 |= 1;
            self->step++;
        } else if (self->ext.boneArk.unk88.i.lo > (ROT(180) - self->rotate)) {
            self->ext.boneArk.unk88.i.lo -= 8;
        } else {
            self->ext.boneArk.unk88.i.lo += 8;
        }

        break;
    case CHARGING:
        if (self->ext.boneArk.unk90 == 0xF) {
            (self - 1)->ext.boneArk.crouching = 0;
            (self - 2)->ext.boneArk.crouching = 0;
            (self + 9)->ext.boneArk.crouching = 0;
            (self + 9)->ext.boneArk.unk90 = 1;
            self->step_s = 0;
            self->step++;
        }
        break;
    case SHOT_FIRED:
        switch (self->step_s) {
        case 0:
            if (!self->ext.boneArk.unk90) {
                self->ext.boneArk.unk88.i.lo -= 0x80;
                if (self->ext.boneArk.unk88.i.lo < -self->rotate) {
                    self->step_s++;
                }
            }
            break;
        case 1:
            self->ext.boneArk.unk88.i.lo += 8;
            if (self->ext.boneArk.unk88.i.lo > (ROT(90) - self->rotate)) {
                self->step_s++;
            }
            break;
        case 2:
            self->step_s = 0;
            self->step = 1;
            break;
        }
        break;
    case DEATH:
        switch (self->step_s) {
        case 0:
            self->ext.boneArk.unk88.i.lo += self->ext.boneArk.unk82;
            if (self->ext.boneArk.unk88.i.lo > ROT(225)) {
                self->ext.boneArk.unk82 = -0x40;
            }

            if (self->ext.boneArk.unk88.i.lo < 0x100) {
                self->ext.boneArk.unk82 = 0x40;
            }

            entity = self + 5;
            if (entity->step == 3) {
                self->step_s++;
            }
            break;
        case 1:
            PlaySfxPositional(SFX_FM_THUNDER_EXPLODE);
            entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_EXPLOSION, self, entity);
                entity->params = 1;
            }

            (self - 1)->ext.boneArk.unk90 = 0xFF;
            (self - 2)->ext.boneArk.unk90 = 0xFF;
            primIndex = g_api.AllocPrimitives(PRIM_GT4, 8);
            if (primIndex != -1) {
                self->flags |= FLAG_HAS_PRIMS;
                self->primIndex = primIndex;
                prim = &g_PrimBuf[primIndex];
                self->ext.boneArk.prim = prim;

                for (i = 0; i < 4; i++) {
                    prim = self->ext.boneArk.prim;
                    prim = FindFirstUnkPrim2(prim, 2);
                    if (prim != NULL) {
                        UnkPolyFunc2(prim);
                        prim->tpage = 0x12;
                        prim->clut = PAL_DRA(PAL_BONE_ARK_PROJECTILE_EXPLODE);
                        prim->u0 = (i % 2) * 0x28 + 0x30;
                        prim->u1 = prim->u0 + 0x28;
                        prim->u2 = prim->u0;
                        prim->u3 = prim->u1;
                        prim->v0 = (i >> 1) * 0xC;
                        prim->v1 = prim->v0;
                        prim->v2 = prim->v0 + 0xC;
                        prim->v3 = prim->v2;
                        prim->next->x1 = self->posX.i.hi;
                        prim->next->y0 = self->posY.i.hi;
                        prim->next->b3 = 0x80;
                        prim->next->tpage = self->rotate;
                        prim->next->r3 = i;
                        LOH(prim->next->r2) = 0x28;
                        LOH(prim->next->b2) = 0xC;
                        prim->priority = self->zPriority;
                        prim->drawMode = DRAW_UNK02;
                        // nb. this looks like a copy paste mistake
                        // this is overwritten by the loop iteration
                        prim = prim->next;
                    }
                }
            } else {
                self->ext.boneArk.prim = NULL;
            }

            for (i = 1; i < 10; i++) {
                entity = &self[i];
                DestroyEntity(entity);
            }

            self->animCurFrame = 0;
            self->step_s++;
            break;
        case 2:
            var_s5 = 0;
            prim = self->ext.boneArk.prim;
            while (prim != NULL) {
                if (prim->p3 & 8) {
                    var_s5 |= 1;
                    RenderDeathParts(prim);
                }
                prim = prim->next;
            }

            if (!var_s5) {
                PreventEntityFromRespawning(self);
                DestroyEntity(self);
                return;
            }

            break;
        }
        break;
    case 16:
#include "../pad2_anim_debug.h"
    }

    xOffset = (((self - 1)->ext.boneArk.skeletonPosX +
                (self - 2)->ext.boneArk.skeletonPosX) /
               2) +
              3;
    yOffset = ((self - 1)->ext.boneArk.skeletonPosY +
               (self - 2)->ext.boneArk.skeletonPosY) /
              2;
    self->posX.i.hi = xOffset;
    self->posY.i.hi = yOffset;
    dx = (self - 2)->ext.boneArk.skeletonPosX -
         (self - 1)->ext.boneArk.skeletonPosX;
    dy = (self - 2)->ext.boneArk.skeletonPosY -
         (self - 1)->ext.boneArk.skeletonPosY;
    angle = ratan2(dy, dx);
    self->rotate = angle;

    var_s3 = self->ext.boneArk.unk88.i.lo;
    angle = -self->rotate;
    angle = (var_s3 - angle) / 4;
    for (i = 5; i < 7; i++) {
        entity = &self[i];
        var_s3 = var_s3 - angle;
        entity->ext.boneArk.unk80 = var_s3 + self->rotate;
    }

    var_s3 = -self->rotate;
    angle = ((self + 9)->ext.boneArk.unk80 - var_s3) / 3;
    for (i = 7; i < 9; i++) {
        entity = &self[i];
        var_s3 = var_s3 + angle;
        entity->ext.boneArk.unk80 = var_s3 + self->rotate;
    }
}

// nb. This must be defined after pad2_anim_debug.h to align PSP data
static s16 skeleton_yOffsets[] = {
    10, -20, -21, -22, -8, -20, -19, -8, -6, 0, 4, 8, 10, 0, 0, 0};

void EntityBoneArkSkeleton(Entity* self) {
    Entity* otherSkeletonEntity;
    Entity* boneArkEntity;
    Entity* newEntity;
    u8 collisionDetected;

    typedef enum Step {
        INIT = 0,
        DROP_TO_GROUND = 1,
        WALK = 2,
        CROUCH = 3,
        STAND = 4,
        FLEE = 5,
        DEATH = 6,
        POST_DEATH = 7
    };

    boneArkEntity = &self[self->params];
    if (self->params == 1) {
        otherSkeletonEntity = self - 1;
    } else {
        otherSkeletonEntity = self + 1;
    }

    if (self->ext.boneArk.unk90 == 0xFF) {
        if (!(self->flags & FLAG_DEAD)) {
            self->facingLeft = GetSideToPlayer() & 1;
            SetStep(FLEE);
            self->hitboxHeight = 0x12;
            self->hitboxOffY = 0;
            self->flags |= FLAG_DESTROY_IF_OUT_OF_CAMERA |
                           FLAG_DESTROY_IF_BARELY_OUT_OF_CAMERA;
        }
    }

    if (self->flags & FLAG_DEAD && self->step < DEATH) {
        PlaySfxPositional(SFX_RED_SKEL_COLLAPSE);
        self->hitboxState = 0;
        self->ext.boneArk.unk8C.i.hi = 0;
        self->velocityX = 0;
        otherSkeletonEntity->velocityX = 0;
        otherSkeletonEntity->step_s |= 16;
        if (!self->ext.boneArk.skeletonDied) {
            otherSkeletonEntity->ext.boneArk.skeletonDied = 1;
        }
        SetStep(DEATH);
    }

    switch (self->step) {
    case INIT:
        InitializeEntity(g_EInitBoneArkSkeleton);
        self->zPriority = boneArkEntity->zPriority + 1 - self->params;
        // fallthrough
    case DROP_TO_GROUND:
        if (UnkCollisionFunc3(sensors_ground) & 1) {
            self->pose = self->params;
            self->step++;
        }
        break;
    case WALK:
        if (!self->step_s) {
            if (boneArkEntity->ext.boneArk.walkingRight) {
                self->velocityX = FIX(0.375);
            } else {
                self->velocityX = FIX(-0.375);
            }

            // When one skeleton is dead the movement speed is halved
            if (self->ext.boneArk.skeletonDied) {
                self->velocityX /= 2;
            }

            if (self->params == 2) {
                otherSkeletonEntity->step_s = 0;
            }
            self->step_s++;
        }

        AnimateEntity(anim_skeleton_walk, self);
        collisionDetected = UnkCollisionFunc2(sensors_skeleton);
        if (collisionDetected & 0x80) {
            if (self->params == 1) {
                otherSkeletonEntity->posX.val -= otherSkeletonEntity->velocityX;
            } else {
                otherSkeletonEntity->step_s |= 16;
            }
            otherSkeletonEntity->velocityX = 0;
            self->step_s &= 16;
            otherSkeletonEntity->step_s &= 16;
            boneArkEntity->ext.boneArk.walkingRight ^= 1;
        }

        if (self->ext.boneArk.crouching) {
            self->velocityX = 0;
            SetStep(CROUCH);
        }

        break;
    case CROUCH:
        switch (self->step_s) {
        case 0:
            self->ext.boneArk.unk8C.i.lo = self->params * 0x10;
            self->step_s++;
            // fallthrough
        case 1:
            if (!--self->ext.boneArk.unk8C.i.lo) {
                self->hitboxHeight = 0xE;
                self->hitboxOffY = 7;
                self->animCurFrame = 4;
                self->ext.boneArk.unk8C.i.hi = 0xD;
                self->step_s++;
            }
            break;
        case 2:
            if (!self->ext.boneArk.unk8C.i.hi) {
                boneArkEntity->ext.boneArk.unk90 |= 1 << self->params;
                SetStep(STAND);
            } else {
                self->ext.boneArk.unk8C.i.hi--;
            }
            break;
        }
        break;
    case STAND:
        if (boneArkEntity->step == IDLE_WALK) {
            self->hitboxHeight = 0x12;
            self->hitboxOffY = 0;
            SetStep(DROP_TO_GROUND);
        }
        break;
    case FLEE:
        self->ext.boneArk.unk90 = 0;
        switch (self->step_s) {
        case 16:
        case 0:
            collisionDetected = UnkCollisionFunc2(sensors_skeleton);
            if (!AnimateEntity(anim_skeleton_flee, self)) {
                self->facingLeft = GetSideToPlayer() & 1;
            }

            if (collisionDetected == 0xFF) {
                self->facingLeft ^= 1;
                self->pose = 0;
                self->poseTimer = 0;
            }

            // If skeleton has escaped the edge of the room
            // do a little hop and escape
            if (collisionDetected == 0x80) {
                PlaySfxPositional(SFX_BLIPS_A);
                self->velocityY = FIX(-4.0);
                self->step_s++;
            }

            if (self->facingLeft) {
                self->velocityX = FIX(1.5);
            } else {
                self->velocityX = FIX(-1.5);
            }
            break;
        case 17:
        case 1:
            if (UnkCollisionFunc3(sensors_ground) & 1) {
                self->step_s--;
            }
            break;
        }
        break;
    case DEATH:
        if (!AnimateEntity(anim_skeleton_death, self)) {
            PlaySfxPositional(SFX_FM_STUTTER_EXPLODE);
            self->animCurFrame = 0;
            newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(E_EXPLOSION, self, newEntity);
                newEntity->posY.i.hi += 0xA;
                newEntity->params = 2;
            }
            otherSkeletonEntity->step_s = 0;
            self->step++;
        }
        break;
    case POST_DEATH:
        UnkCollisionFunc2(sensors_skeleton);
        self->velocityX = otherSkeletonEntity->velocityX;
        if (self->ext.boneArk.crouching) {
            boneArkEntity->ext.boneArk.unk90 |= 1 << self->params;
            self->ext.boneArk.crouching = 0;
        }

        if (boneArkEntity->entityId != E_BONE_ARK) {
            DestroyEntity(self);
            return;
        }

        break;
    }

    self->ext.boneArk.skeletonPosX = self->posX.i.hi;
    self->ext.boneArk.skeletonPosY =
        (self->posY.i.hi + skeleton_yOffsets[self->animCurFrame]) -
        self->ext.boneArk.unk8C.i.hi;
}
