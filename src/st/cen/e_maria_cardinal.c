// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../cen/cen.h"

// bss
static s32 D_pspeu_092E5F18;
static s32 D_pspeu_092E5D18[0x40];

static s32 GetFireWingsPivotY(void) {
    switch (MARIA.step) {
    case PL_S_CROUCH:
        return -20;
    default:
        return -36;
    }
}

static AnimationFrame anim_fire_wings[] = {
    POSE(3, 9, 0),  POSE(3, 10, 0), POSE(3, 11, 0), POSE(3, 12, 0),
    POSE(3, 13, 0), POSE(3, 14, 0), POSE(3, 9, 0),  POSE(3, 10, 0),
    POSE(3, 11, 0), POSE(3, 12, 0), POSE_LOOP(0)};
void EntityMariaCardinalAttack(Entity* self) {
    switch (self->step) {
    case 0:
        self->flags = FLAG_UNK_100000 | FLAG_KEEP_ALIVE_OFFCAMERA |
                      FLAG_POS_CAMERA_LOCKED;
        self->unk5A = 0x51;
        self->blendMode = BLEND_TRANSP | BLEND_ADD;
        self->zPriority = MARIA.zPriority - 8;
        self->palette = PAL_WPN_CARDINAL;
        self->animSet = ANIMSET_WPN_CARDINAL;
        MarSetAnimation(anim_fire_wings);
        self->facingLeft = 0;
        self->velocityX = 0;
        self->posX.i.hi = MARIA.posX.i.hi;
        self->posY.i.hi = MARIA.posY.i.hi + 0x18 + GetFireWingsPivotY();
        self->scaleX = 0;
        self->scaleY = 0;
        self->drawFlags = ENTITY_SCALEX | ENTITY_SCALEY;
        self->hitboxWidth = 14;
        self->hitboxHeight = 16;
        self->hitboxOffX = 0;
        self->hitboxOffY = -20;
        self->ext.mariaCardinal.unkB0 = 0;
        MarSetWeaponParams(
            self, 36, ELEMENT_HOLY | ELEMENT_FIRE, 0, 16, 16, 1, 0);
        g_api.PlaySfx(SFX_FIREBALL_SHOT_B);
        g_Maria.unk7A = 1;
        self->ext.mariaCardinal.timer = 0;
        self->step++;
        break;
    case 1:
        self->posX.i.hi = MARIA.posX.i.hi;
        self->posY.i.hi = MARIA.posY.i.hi + 0x18 + GetFireWingsPivotY();
        self->hitboxOffY = -20;
        self->scaleX += 16;
        self->scaleY += 16;
        if (self->scaleX == 256) {
            self->step++;
        }
        break;
    case 2:
        self->posX.i.hi = MARIA.posX.i.hi;
        self->posY.i.hi = MARIA.posY.i.hi + 0x18 + GetFireWingsPivotY();
        self->hitboxOffY = -20;
        self->drawFlags = ENTITY_DEFAULT;
        self->ext.mariaCardinal.timer++;
        if (self->ext.mariaCardinal.timer >= 30) {
            self->step++;
        }
        break;
    case 3:
        g_Maria.unk7A = 0;
        g_Maria.unk66 = 0;
        DestroyEntity(self);
        break;
    }

    if (g_GameTimer & 1) {
        self->hitboxOffX = (self->hitboxWidth / 2) + 0x10;
    } else {
        self->hitboxOffX = -0x10;
    }

    if (MARIA.step != PL_S_CARDINAL_ATTACK && MARIA.step != PL_S_STAND) {
        self->step = 3;
    }
}

static AnimationFrame anim_cardinal_crash[] = {
    POSE(9, 3, 0), POSE(6, 4, 0), POSE(6, 5, 0), POSE(8, 6, 0),
    POSE(6, 7, 0), POSE(6, 8, 0), POSE_LOOP(0)};
void EntityMariaCardinalCrash(Entity* self) {
    s32 var_s0;

    switch (self->step) {
    case 0:
        self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA |
                      FLAG_UNK_100000;
        self->unk5A = 0x51;
        self->zPriority = 0x1C0;
        self->palette = PAL_WPN_CARDINAL;
        self->animSet = ANIMSET_WPN_CARDINAL;
        MarSetAnimation(anim_cardinal_crash);
        self->facingLeft = MARIA.facingLeft;
        if (MARIA.facingLeft) {
            var_s0 = 24;
        } else {
            var_s0 = -24;
        }
        self->posX.i.hi = MARIA.posX.i.hi + var_s0;
        self->posY.i.hi = MARIA.posY.i.hi + 24;
#if defined(VERSION_PC)
        g_Maria.unk20 = (signed long long)self;
#else
        g_Maria.unk20 = (s32)self;
#endif
        self->ext.mariaCardinal.timer = 0;
        self->ext.mariaCardinal.nSpawn = 0;
        self->ext.mariaCardinal.opacity = 0;
        self->step = 1;
        SpawnCrashSummon(1);
        SetOpacity(self, 0);
        break;
    case 1:
        if (g_Maria.unk5C == 1) {
            g_api.PlaySfx(SFX_VO_MAR_8F1 + MAR_SFX_OFFSET);
            self->step = 3;
        }
        break;
    case 3:
        self->ext.mariaCardinal.opacity += 16;
        if (self->ext.mariaCardinal.opacity >= 128) {
            SetOpacity(self, 128);
            self->step = 2;
        } else {
            SetOpacity(self, self->ext.mariaCardinal.opacity);
        }
        break;
    case 2:
        if (self->ext.mariaCardinal.timer > 300) {
            self->ext.mariaCardinal.opacity = 128;
            self->step = 4;
        }
        break;
    case 4:
        self->posY.i.hi -= 4;
        self->ext.mariaCardinal.opacity -= 16;
        if (self->ext.mariaCardinal.opacity <= 0) {
            SetOpacity(self, 0);
            self->step = 5;
        } else {
            SetOpacity(self, self->ext.mariaCardinal.opacity);
        }
        break;
    case 5:
        g_Maria.unk20 = 0;
        g_Maria.unk5C = 0;
        DestroyEntity(self);
        break;
    }
    self->ext.mariaCardinal.timer++;
    if (g_Maria.unk5C == 1 && self->step == 2 &&
        self->ext.mariaCardinal.timer < 240 &&
        (self->ext.mariaCardinal.timer % 5) == 0) {
        MarCreateEntFactoryFromEntity(self, BP_CARDINAL_CRASH_FIREBALL, 0);
        self->ext.mariaCardinal.nSpawn++;
    }
}

static s32 NormalizeAngle2(s32 angle) {
    angle %= 0x1000;
    if (angle < 0) {
        angle += 0x1000;
    }
    return angle;
}

static Entity* FindTarget2(Entity* self) {
    Entity* e;
    s32 i;
    s32 var_s2;
    s32 found;

    found = 0;
    e = &PLAYER;
    for (i = 0; i < LEN(D_pspeu_092E5D18); i++, e++) {
        D_pspeu_092E5D18[i] = 0;
        if (!e->entityId) {
            continue;
        }
        if (e->hitboxState == 0) {
            continue;
        }
        if (e->flags & FLAG_UNK_00200000) {
            continue;
        }
        if (e->posX.i.hi < -0x10 || e->posX.i.hi > 0x110) {
            continue;
        }
        if (e->posY.i.hi > 0xF0 || e->posY.i.hi < 0) {
            continue;
        }
        if (e->hitboxState & 8) {
            continue;
        }
        if (self->facingLeft && self->posX.i.hi < e->posX.i.hi) {
            continue;
        }
        if (!self->facingLeft && self->posX.i.hi > e->posX.i.hi) {
            continue;
        }
        if (e->hitPoints >= 0x7000) {
            continue;
        }
        if (e->flags & FLAG_UNK_80000) {
            found++;
            D_pspeu_092E5D18[i] = 1;
        } else {
            e->flags |= FLAG_UNK_80000;
            return e;
        }
    }
    if (found) {
        var_s2 = D_pspeu_092E5F18 % LEN(D_pspeu_092E5D18);
        for (i = 0; i < LEN(D_pspeu_092E5D18); i++) {
            if (D_pspeu_092E5D18[var_s2]) {
                e = &g_Entities[var_s2];
                D_pspeu_092E5F18 = (var_s2 + 1) % LEN(D_pspeu_092E5D18);
                return e;
            }
            var_s2 = (var_s2 + 1) % LEN(D_pspeu_092E5D18);
        }
    }
    return NULL;
}

static int IsTargetValid2(Entity* entity) {
    if (entity == NULL) {
        return 0;
    }
    if (entity->hitboxState == 0) {
        return 0;
    }
    if (entity->posX.i.hi < -0x10) {
        return 0;
    }
    if (entity->posX.i.hi > 0x110) {
        return 0;
    }
    if (entity->posY.i.hi > 0xF0) {
        return 0;
    }
    if (entity->posY.i.hi < 0) {
        return 0;
    }
    if (entity->hitPoints >= 0x7000) {
        return 0;
    }
    if (entity->hitPoints <= 0) {
        return 0;
    }
    return 1;
}

static void func_pspeu_092A9D48(Entity* entity, s32 x, s32 y) {
    entity->ext.mariaCardinalCrash.pos1.x = x;
    entity->ext.mariaCardinalCrash.pos1.y = y;
    entity->ext.mariaCardinalCrash.pos2.x = x;
    entity->ext.mariaCardinalCrash.pos2.y = y;
    entity->ext.mariaCardinalCrash.pos3.x = x;
    entity->ext.mariaCardinalCrash.pos3.y = y;
    entity->ext.mariaCardinalCrash.pos4.x = x;
    entity->ext.mariaCardinalCrash.pos4.y = y;
}

static void func_pspeu_092A9DE8(Entity* entity, s32 x, s32 y) {
    entity->ext.mariaCardinalCrash.pos4.x =
        entity->ext.mariaCardinalCrash.pos3.x;
    entity->ext.mariaCardinalCrash.pos4.y =
        entity->ext.mariaCardinalCrash.pos3.y;
    entity->ext.mariaCardinalCrash.pos3.x =
        entity->ext.mariaCardinalCrash.pos2.x;
    entity->ext.mariaCardinalCrash.pos3.y =
        entity->ext.mariaCardinalCrash.pos2.y;
    entity->ext.mariaCardinalCrash.pos2.x =
        entity->ext.mariaCardinalCrash.pos1.x;
    entity->ext.mariaCardinalCrash.pos2.y =
        entity->ext.mariaCardinalCrash.pos1.y;
    entity->ext.mariaCardinalCrash.pos1.x = x;
    entity->ext.mariaCardinalCrash.pos1.y = y;
}

static AnimationFrame anim_cardinal_crash_fireball[] = {
    POSE(0, 1, 0), POSE_LOOP(0)};
void EntityMariaCardinalCrashFireball(Entity* self) {
    s32 acceleration;
    s32 initialAcceleration;
    s32 yStart;
    MATRIX sp74;
    VECTOR sp64;
    VECTOR sp54;
    SVECTOR sp4C;
    s32 angle;
    s32 targetX;
    s32 targetY;
    Entity* parent;
    s8 color;
    s32 i;
    s32 x;
    s32 y;
    Primitive* prim;

    acceleration = 64;
    initialAcceleration = 115;
    parent = (Entity*)g_Maria.unk20;
    switch (self->step) {
    case 0: {
        if (g_Maria.unk5C == 0 || parent == NULL) {
            DestroyEntity(self);
            return;
        }
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 4);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags =
            FLAG_HAS_PRIMS | FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_POS_CAMERA_LOCKED;
        self->unk5A = 0x51;
        self->zPriority = 0x1C0;
        self->palette = PAL_WPN_CARDINAL;
        self->animSet = ANIMSET_WPN_CARDINAL;
        MarSetAnimation(anim_cardinal_crash_fireball);
        self->facingLeft = parent->facingLeft;
        self->posX.i.hi = parent->posX.i.hi + (self->facingLeft ? 37 : -37);
        self->posY.i.hi = parent->posY.i.hi - 52;
        func_pspeu_092A9D48(self, self->posX.i.hi, self->posY.i.hi);
        self->ext.mariaCardinalCrash.defaultTargetX =
            self->posX.i.hi + (self->facingLeft ? -200 : 200);
        self->ext.mariaCardinalCrash.defaultTargetY = self->posY.i.hi;
        if (parent->ext.mariaCardinalCrash.defaultTargetY & 1) {
            self->ext.mariaCardinalCrash.angle = (rand() % 0x400) / 2;
            yStart = -(rand() % 24);
        } else {
            self->ext.mariaCardinalCrash.angle = 0x400 - (rand() % 0x400) / 2;
            yStart = rand() % 24;
        }

        self->posY.i.hi += self->facingLeft ? yStart : -yStart;
        self->ext.mariaCardinalCrash.angle +=
            (self->facingLeft ? 0 : 0x800) - 0x200;
        self->hitboxWidth = 16;
        self->hitboxHeight = 16;
        self->hitboxOffX = 0;
        self->hitboxOffY = 0;
        self->ext.mariaCardinalCrash.unkB0 = 0;
        MarSetWeaponParams(
            self, 32, ELEMENT_HOLY | ELEMENT_FIRE, 2, 16, 16, 1, 0);
        self->ext.mariaCardinalCrash.timer = 0;
        self->ext.mariaCardinalCrash.velocityX = (rand() % 384) + 0x80;
        self->step = 1;
        g_api.PlaySfx(SFX_PSP_MARIA_CARDINAL_CRASH);
    } break;
    case 1: {
        self->ext.mariaCardinalCrash.timer++;
        {
            MATRIX m;
            VECTOR vTransform = {0, 0, 0};
            VECTOR vVelocity;
            SVECTOR svVelocity;
            long sp48;
            if (self->ext.mariaCardinalCrash.timer < 35) {
                if (IsTargetValid2(self->ext.mariaCardinalCrash.target) == 0) {
                    self->ext.mariaCardinalCrash.target = FindTarget2(self);
                }
                if (self->ext.mariaCardinalCrash.target) {
                    targetX = self->ext.mariaCardinalCrash.target->posX.i.hi;
                    targetY = self->ext.mariaCardinalCrash.target->posY.i.hi;
                    if (abs(targetX - self->posX.i.hi) < 16 &&
                        abs(targetY - self->posY.i.hi) < 16) {
                        self->ext.mariaCardinalCrash.timer = 35;
                    }
                } else {
                    targetX = self->ext.mariaCardinalCrash.defaultTargetX;
                    targetY = self->ext.mariaCardinalCrash.defaultTargetY;
                }
                self->ext.mariaCardinalCrash.angle =
                    NormalizeAngle2(self->ext.mariaCardinalCrash.angle);
                angle = NormalizeAngle2(ratan2(
                    targetY - self->posY.i.hi, targetX - self->posX.i.hi));
                if (self->ext.mariaCardinalCrash.angle < angle) {
                    if (angle - self->ext.mariaCardinalCrash.angle < 0x800) {
                        self->ext.mariaCardinalCrash.angle += 0x50;
                    } else {
                        self->ext.mariaCardinalCrash.angle -= 0x50;
                    }
                } else {
                    if (self->ext.mariaCardinalCrash.angle - angle < 0x800) {
                        self->ext.mariaCardinalCrash.angle -= 0x50;
                    } else {
                        self->ext.mariaCardinalCrash.angle += 0x50;
                    }
                }
                self->ext.mariaCardinalCrash.velocityX += acceleration;
                if (self->ext.mariaCardinalCrash.velocityX > 0x400) {
                    self->ext.mariaCardinalCrash.velocityX = 0x400;
                }
            } else {
                self->ext.mariaCardinalCrash.velocityX += initialAcceleration;
            }
            SetGeomOffset(0, 0);
            func_psp_089285A0(self->ext.mariaCardinalCrash.angle, &m);
            TransMatrix(&m, &vTransform);
            SetRotMatrix(&m);
            SetTransMatrix(&m);
            svVelocity.vx = self->ext.mariaCardinalCrash.velocityX;
            svVelocity.vy = 0;
            svVelocity.vz = 0;
            RotTrans(&svVelocity, &vVelocity, &sp48);
            self->velocityX = vVelocity.vx << 8;
            self->velocityY = vVelocity.vy << 8;
            self->posX.val += self->velocityX;
            self->posY.val += self->velocityY;
            if (self->ext.mariaCardinalCrash.timer % 2 == 0) {
                func_pspeu_092A9DE8(self, self->posX.i.hi, self->posY.i.hi);
            } else {
                self->ext.mariaCardinalCrash.pos1.x = self->posX.i.hi;
                self->ext.mariaCardinalCrash.pos1.y = self->posY.i.hi;
            }
            prim = &g_PrimBuf[self->primIndex];
            for (i = 0; i < 4; i++) {
                color = -0x80;
                prim->clut = (PAL_WPN_CARDINAL) & 0x136;
                prim->priority = self->zPriority;
                prim->drawMode = DRAW_DEFAULT;
                switch (i) {
                case 0:
                    x = self->ext.mariaCardinalCrash.pos1.x;
                    y = self->ext.mariaCardinalCrash.pos1.y;
                    break;
                case 1:
                    x = self->ext.mariaCardinalCrash.pos2.x;
                    y = self->ext.mariaCardinalCrash.pos2.y;
                    break;
                case 2:
                    x = self->ext.mariaCardinalCrash.pos3.x;
                    y = self->ext.mariaCardinalCrash.pos3.y;
                    break;
                case 3:
                    x = self->ext.mariaCardinalCrash.pos4.x;
                    y = self->ext.mariaCardinalCrash.pos4.y;
                    break;
                }
                prim->x0 = x - 8;
                prim->y0 = y - 8;
                prim->x1 = x + 8;
                prim->y1 = y - 8;
                prim->x2 = x - 8;
                prim->y2 = y + 8;
                prim->x3 = x + 8;
                prim->y3 = y + 8;
                if (i == 0) {
                    prim->u0 = 0xB8;
                    prim->v0 = 0x68;
                    prim->u1 = 0xCF;
                    prim->v1 = 0x68;
                    prim->u2 = 0xB8;
                    prim->v2 = 0x7F;
                    prim->u3 = 0xCF;
                    prim->v3 = 0x7F;
                    prim->tpage = 0x14;
                } else {
                    prim->u0 = 0x98;
                    prim->v0 = 0x38;
                    prim->u1 = 0xA7;
                    prim->v1 = 0x38;
                    prim->u2 = 0x98;
                    prim->v2 = 0x47;
                    prim->u3 = 0xA7;
                    prim->v3 = 0x47;
                    prim->tpage = 0x34;
                    prim->drawMode |= ENTITY_SCALEX | ENTITY_ROTATE;
                    if (i == 1) {
                        color = -0x80;
                    } else if (i == 2) {
                        color = 0x60;
                    } else if (i == 3) {
                        color = 0x40;
                    }
                }
                prim->r0 = prim->r1 = prim->r2 = prim->r3 = color;
                prim->g0 = prim->g1 = prim->g2 = prim->g3 = color;
                prim->b0 = prim->b1 = prim->b2 = prim->b3 = color;
                prim = prim->next;
            }
            if (self->ext.mariaCardinalCrash.timer > 35 &&
                (self->posX.i.hi < -16 || self->posX.i.hi > 272)) {
                self->step = 2;
            }
        }
    } break;
    case 2:
        DestroyEntity(self);
        break;
    }
}
