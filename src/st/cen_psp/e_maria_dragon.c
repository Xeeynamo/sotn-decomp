// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../cen/cen.h"

// bss
static Point16 D_pspeu_092E5B18[0x80];
static s32 D_pspeu_092E5B10;
static u8 D_pspeu_092E5B08[8];
static s32 D_pspeu_092E5908[0x40];
static s32 D_pspeu_092E5900;

static AnimationFrame anim_maria_dragon[] = {
    POSE(4, 5, 0), POSE(2, 6, 0),  POSE(1, 7, 0),  POSE(1, 8, 0),
    POSE(1, 9, 0), POSE(2, 10, 0), POSE(4, 11, 0), POSE(1, 8, 0),
    POSE(1, 7, 0), POSE(1, 6, 0),  POSE_LOOP(0)};

static AnimationFrame anim_dragon_crash[] = {POSE(1, 1, 0), POSE_LOOP(0)};
static s32 D_pspeu_09276C48 = 16;

void EntityMariaDragonAttack(Entity* self) {
    switch (self->step) {
    case 0:
        self->flags = FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_UNK_100000;
        self->unk5A = 0x55;
        self->zPriority = MARIA.zPriority - 8;
        self->palette = PAL_WPN_DRAGON;
        self->animSet = ANIMSET_WPN_DRAGON;
        MarSetAnimation(anim_maria_dragon);
        self->facingLeft = MARIA.facingLeft;
        self->velocityX = 0;
        self->posX.i.hi = MARIA.posX.i.hi + (MARIA.facingLeft ? 32 : -32);
        self->posY.i.hi = MARIA.posY.i.hi - 8;
        self->ext.mariaDragon.y = self->posY.i.hi;
        self->hitboxWidth = 18;
        self->hitboxHeight = 20;
        self->hitboxOffX = 0;
        self->hitboxOffY = 0xC;
        self->ext.mariaDragon.unkB0 = 0;
        MarSetWeaponParams(self, 48, ELEMENT_HOLY, 0, 16, 16, 1, 0);
        g_Maria.unk7A = 1;
        self->ext.mariaDragon.timer = 0;
        self->step = 3;
        // fallthrough
    case 3:
        self->ext.mariaDragon.opacity += 16;
        if (self->ext.mariaDragon.opacity >= 128) {
            SetOpacity(self, 128);
            self->step = 1;
            break;
        }
        SetOpacity(self, self->ext.mariaDragon.opacity);
        break;
    case 1:
    case 2:
        if (self->step == 1) {
            self->posY.i.hi =
                self->ext.mariaDragon.y +
                ((-rsin(self->ext.mariaDragon.timer << 6) * 0x2A) / 0x1000);
            if (self->ext.mariaDragon.timer > D_pspeu_09276C48) {
                self->step = 2;
            }
        } else {
            self->posY.i.hi =
                self->ext.mariaDragon.y - 0x2A +
                ((-rsin(self->ext.mariaDragon.timer << 6) * 0xC) / 0x1000);
        }

        self->velocityX += FIX(0.25);
        if (self->velocityX > FIX(3)) {
            self->velocityX = FIX(3);
        }
        self->posX.val += self->facingLeft ? -self->velocityX : self->velocityX;
        if ((self->ext.mariaDragon.timer % 60) == 0) {
            g_api.PlaySfx(SFX_WING_FLAP_B);
        }

        self->ext.mariaDragon.timer++;
        if (self->posX.i.hi < -16 || self->posX.i.hi > 272) {
            self->step = 4;
        }
        break;
    case 4:
        g_Maria.unk7A = 0;
        DestroyEntity(self);
        break;
    }
}

static s32 NormalizeAngle(s32 angle) {
    angle %= 0x1000;
    if (angle < 0) {
        angle += 0x1000;
    }
    return angle;
}

static Entity* FindTarget(Entity* self) {
    Entity* e;
    s32 i;
    s32 var_s2;
    s32 found;

    found = 0;
    e = &g_Entities[0];

    for (i = 0; i < LEN(D_pspeu_092E5908); i++, e++) {
        D_pspeu_092E5908[i] = 0;
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
        if (e->hitPoints >= 0x7000) {
            continue;
        }
        if (e->flags & FLAG_UNK_80000) {
            found++;
            D_pspeu_092E5908[i] = 1;
        } else {
            e->flags |= FLAG_UNK_80000;
            return e;
        }
    }

    if (found) {
        var_s2 = D_pspeu_092E5B10 % LEN(D_pspeu_092E5908);
        for (i = 0; i < LEN(D_pspeu_092E5908); i++) {
            if (D_pspeu_092E5908[var_s2]) {
                e = &g_Entities[var_s2];
                D_pspeu_092E5B10 = (var_s2 + 1) % LEN(D_pspeu_092E5908);
                return e;
            }

            var_s2 = (var_s2 + 1) % LEN(D_pspeu_092E5908);
        }
    }
    return NULL;
}

static bool IsTargetValid(Entity* entity) {
    if (entity == NULL) {
        return false;
    }
    if (entity->hitboxState == 0) {
        return false;
    }
    if (entity->posX.i.hi < -0x10) {
        return false;
    }
    if (entity->posX.i.hi > 0x110) {
        return false;
    }
    if (entity->posY.i.hi > 0xF0) {
        return false;
    }
    if (entity->posY.i.hi < 0) {
        return false;
    }
    if (entity->hitPoints >= 0x7000) {
        return false;
    }
    if (entity->hitPoints <= 0) {
        return false;
    }

    return true;
}

void EntityMariaDragonCrash(Entity* self) {
    s32 x;
    s32 y;
    s32 angle;
    s32 i;

    switch (self->step) {
    case 0:
        self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA |
                      FLAG_UNK_100000;
        self->unk5A = 0x55;
        self->zPriority = 0x1C0;
        self->palette = PAL_WPN_DRAGON_CRASH;
        self->animSet = ANIMSET_WPN_DRAGON;
        MarSetAnimation(anim_dragon_crash);
        self->facingLeft = 0;
        self->velocityX = 0;
        self->posX.i.hi = MARIA.posX.i.hi;
        self->posY.i.hi = MARIA.posY.i.hi - 32;
        self->rotate = 0;
        self->ext.mariaDragon.velocity = 1280;
        self->hitboxWidth = 24;
        self->hitboxHeight = 24;
        self->hitboxOffX = 0;
        self->hitboxOffY = 0;
        self->ext.mariaDragon.unkB0 = 0;
        MarSetWeaponParams(
            self, 25, ELEMENT_HOLY | ELEMENT_THUNDER, 2, 16, 16, 1, 0);
        D_pspeu_092E5900 = 0;
        self->ext.mariaDragon.timer = 0;
        self->step = 1;
        SpawnCrashSummon(4);
        self->ext.mariaDragon.opacity = 0;
        SetOpacity(self, 0);
        break;
    case 1:
        if (g_Maria.unk5C == 1) {
            MarCreateEntFactoryFromEntity(self, BP_DRAGON_CRASH_BODY_PART, 0);
            self->step = 2;
            g_api.PlaySfx(SFX_VO_MAR_8F1 + MAR_SFX_OFFSET);
        }
        self->drawFlags |= ENTITY_ROTATE;
        break;
    case 2:
        if (self->ext.mariaDragon.opacity < 128) {
            self->ext.mariaDragon.opacity += 8;
            SetOpacity(self, self->ext.mariaDragon.opacity);
        } else {
            SetOpacity(self, 128);
        }
        self->drawFlags |= ENTITY_ROTATE;
        {
            MATRIX m;
            VECTOR vTranslate = {0, 0, 0};
            VECTOR vVelocity;
            SVECTOR svVelocity;
            long out;
            if (!IsTargetValid(self->ext.mariaDragon.target)) {
                self->ext.mariaDragon.target = FindTarget(self);
            }
            if (self->ext.mariaDragon.target) {
                x = self->ext.mariaDragon.target->posX.i.hi;
                y = self->ext.mariaDragon.target->posY.i.hi;
            } else {
                x = MARIA.posX.i.hi;
                y = MARIA.posY.i.hi;
            }
            self->rotate = NormalizeAngle(self->rotate);
            angle = NormalizeAngle(
                ratan2(y - self->posY.i.hi, x - self->posX.i.hi));
            if (self->rotate < angle) {
                if (angle - self->rotate < 0x800) {
                    self->rotate += 0x40;
                } else {
                    self->rotate -= 0x40;
                }
            } else if (self->rotate - angle < 0x800) {
                self->rotate -= 0x40;
            } else {
                self->rotate += 0x40;
            }
            SetGeomOffset(0, 0);
            func_psp_089285A0(self->rotate, &m);
            TransMatrix(&m, &vTranslate);
            SetRotMatrix(&m);
            SetTransMatrix(&m);
            svVelocity.vx = self->ext.mariaDragon.velocity;
            svVelocity.vy = 0;
            svVelocity.vz = 0;
            RotTrans(&svVelocity, &vVelocity, &out);
            self->velocityX = vVelocity.vx << 8;
            self->velocityY = vVelocity.vy << 8;
            FntPrint("%08x : %08x\n", self->velocityX, self->velocityY);
            self->posX.val += self->velocityX;
            self->posY.val += self->velocityY;
            if ((self->ext.mariaDragon.timer % 120) == 0) {
                g_api.PlaySfx(SFX_HIPPOGRYPH_FIRE_ATTACK);
            }
            self->ext.mariaDragon.timer++;
            if (self->ext.mariaDragon.timer > 300) {
                self->step = 3;
            }
        }
        break;
    case 3:
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        self->ext.mariaDragon.timer++;
        if (self->ext.mariaDragon.timer > 300 &&
            (self->posX.i.hi < -0x100 || self->posX.i.hi > 0x200 ||
             self->posY.i.hi < -0x100 || self->posY.i.hi > 0x200)) {
            self->step = 4;
        }
        break;
    case 4:
        g_Maria.unk5C = 0;
        D_pspeu_092E5900 = 0;
        DestroyEntity(self);
        break;
    }

    if (g_Maria.unk5C == 1 && self->step != 4) {
        if (D_pspeu_092E5900 == 0x80) {
            for (i = 0; i < 0x40; i++) {
                D_pspeu_092E5B18[i].x = D_pspeu_092E5B18[i + 0x40].x;
                D_pspeu_092E5B18[i].y = D_pspeu_092E5B18[i + 0x40].y;
            }
            D_pspeu_092E5900 -= 0x40;
        }
        if (D_pspeu_092E5900 < 0x80) {
            D_pspeu_092E5B18[D_pspeu_092E5900].x =
                self->posX.i.hi + g_Tilemap.scrollX.i.hi;
            D_pspeu_092E5B18[D_pspeu_092E5900].y =
                self->posY.i.hi + g_Tilemap.scrollY.i.hi;
            D_pspeu_092E5900++;
        }
    }
}

void EntityMariaDragonCrashBodyPart(Entity* self) {
    s32 xStart;
    s32 xEnd;
    s32 yStart;
    s32 yEnd;
    s32 var_s6;
    s32 var_s5;
    s32 u;
    s32 v;
    s32 var_s2;
    s32 i;
    Primitive* prim;

    switch (self->step) {
    case 0:
        self->primIndex =
            g_api.AllocPrimitives(PRIM_GT4, LEN(D_pspeu_092E5B08));
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags = FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_HAS_PRIMS;
        self->unk5A = 0x55;
        self->zPriority = 0x1C0;
        self->palette = PAL_WPN_DRAGON_CRASH;
        self->animSet = ANIMSET_WPN_DRAGON;
        MarSetAnimation(anim_dragon_crash);
        self->facingLeft = MARIA.facingLeft;
        self->velocityX = 0;
        self->posX.i.hi = MARIA.posX.i.hi;
        self->posY.i.hi = MARIA.posY.i.hi;
        self->hitboxWidth = 24;
        self->hitboxHeight = 24;
        self->hitboxOffX = 0;
        self->hitboxOffY = 0;
        self->ext.mariaDragon.unkB0 = 0;
        MarSetWeaponParams(
            self, 32, ELEMENT_HOLY | ELEMENT_THUNDER, 2, 16, 16, 1, 0);
        for (i = 0; i < LEN(D_pspeu_092E5B08); i++) {
            D_pspeu_092E5B08[i] = 0;
        }
        self->step = 1;
        // fallthrough
    case 1:
        xStart = 0;
        xEnd = 0;
        yStart = 0;
        yEnd = 0;
        prim = &g_PrimBuf[self->primIndex];
        var_s2 = D_pspeu_092E5900 - 1;
        for (i = 0; i < LEN(D_pspeu_092E5B08); i++) {
            prim->tpage = 0x15;
            prim->clut = self->palette & 0x3FF;
            prim->priority = self->zPriority;
            if (var_s2 >= 7) {
                var_s6 = D_pspeu_092E5B18[var_s2].x - g_Tilemap.scrollX.i.hi;
                var_s5 = D_pspeu_092E5B18[var_s2].y - g_Tilemap.scrollY.i.hi;
                var_s2 -= 7;
                if (var_s2 < 0) {
                    var_s2 = 0;
                }
                {
                    s32 spD4 =
                        D_pspeu_092E5B18[var_s2].x - g_Tilemap.scrollX.i.hi;
                    s32 spD0 =
                        D_pspeu_092E5B18[var_s2].y - g_Tilemap.scrollY.i.hi;
                    MATRIX m;
                    VECTOR spA0 = {0, 0, 0};
                    VECTOR vPosEnd;
                    VECTOR sp80;
                    VECTOR vPosStart;
                    VECTOR sp60;
                    SVECTOR svPosEnd;
                    SVECTOR sp50;
                    SVECTOR svPosStart;
                    SVECTOR sp40;
                    long out;
                    s32 angle;
                    angle =
                        NormalizeAngle(ratan2(spD0 - var_s5, spD4 - var_s6));
                    func_psp_089285A0(angle, &m);
                    SetGeomOffset(var_s6, var_s5);
                    TransMatrix(&m, &spA0);
                    SetRotMatrix(&m);
                    SetTransMatrix(&m);
                    if (i == 0) {
                        sp40.vx = -16;
                        sp40.vy = -16;
                        sp40.vz = 0;
                        svPosStart.vx = 16;
                        svPosStart.vy = -16;
                        svPosStart.vz = 0;
                        sp50.vx = -16;
                        sp50.vy = 16;
                        sp50.vz = 0;
                        svPosEnd.vx = 16;
                        svPosEnd.vy = 16;
                        svPosEnd.vz = 0;
                        RotTrans(&sp40, &sp60, &out);
                        RotTrans(&svPosStart, &vPosStart, &out);
                        RotTrans(&sp50, &sp80, &out);
                        RotTrans(&svPosEnd, &vPosEnd, &out);
                        prim->x0 = sp60.vx;
                        prim->y0 = sp60.vy;
                        prim->x1 = vPosStart.vx;
                        prim->y1 = vPosStart.vy;
                        prim->x2 = sp80.vx;
                        prim->y2 = sp80.vy;
                        prim->x3 = vPosEnd.vx;
                        prim->y3 = vPosEnd.vy;
                    } else {
                        svPosStart.vx = 16;
                        svPosStart.vy = -16;
                        svPosStart.vz = 0;
                        svPosEnd.vx = 16;
                        svPosEnd.vy = 16;
                        svPosEnd.vz = 0;
                        RotTrans(&svPosStart, &vPosStart, &out);
                        RotTrans(&svPosEnd, &vPosEnd, &out);
                        prim->x0 = xStart;
                        prim->y0 = yStart;
                        prim->x1 = vPosStart.vx;
                        prim->y1 = vPosStart.vy;
                        prim->x2 = xEnd;
                        prim->y2 = yEnd;
                        prim->x3 = vPosEnd.vx;
                        prim->y3 = vPosEnd.vy;
                    }
                    xStart = vPosStart.vx;
                    yStart = vPosStart.vy;
                    xEnd = vPosEnd.vx;
                    yEnd = vPosEnd.vy;
                }

                if (i == 7) {
                    u = 0xE0;
                    v = 0x20;
                } else if (i == 6) {
                    u = 0xE0;
                    v = 0;
                } else {
                    u = 0x80;
                    v = 0;
                }

                prim->u1 = u;
                prim->v1 = v + 0x1F;
                prim->u0 = u + 0x1F;
                prim->v0 = v + 0x1F;
                prim->u3 = u;
                prim->v3 = v;
                prim->u2 = u + 0x1F;
                prim->v2 = v;
                prim->drawMode = DRAW_DEFAULT;
                D_pspeu_092E5B08[i] += 0x10;
                if (D_pspeu_092E5B08[i] < 0x80) {
                    prim->drawMode |=
                        DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
                } else {
                    D_pspeu_092E5B08[i] = 0x80;
                }
                prim->r0 = prim->r1 = prim->r2 = prim->r3 = D_pspeu_092E5B08[i];
                prim->g0 = prim->g1 = prim->g2 = prim->g3 = D_pspeu_092E5B08[i];
                prim->b0 = prim->b1 = prim->b2 = prim->b3 = D_pspeu_092E5B08[i];
            } else {
                prim->drawMode = DRAW_HIDE;
            }
            prim = prim->next;
        }

        if (g_Maria.unk5C != 0) {
            return;
        }
        self->step = 2;
        break;
    case 2:
        DestroyEntity(self);
        break;
    }
}
