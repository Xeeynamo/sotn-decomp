// SPDX-License-Identifier: AGPL-3.0-or-later
#include "maria.h"

extern u8 D_pspeu_092E5B08[8];
extern s32 D_pspeu_092E5900;
extern Point16 D_pspeu_092E5B18[];

INCLUDE_ASM("maria_psp/nonmatchings/80", func_pspeu_092A6280);

INCLUDE_ASM("maria_psp/nonmatchings/80", func_pspeu_092A6740);

INCLUDE_ASM("maria_psp/nonmatchings/80", func_pspeu_092A6958);

INCLUDE_ASM("maria_psp/nonmatchings/80", func_pspeu_092A6A08);

extern AnimationFrame D_pspeu_092C0958[];
void func_pspeu_092A6E50(Entity* self) {
    Collider col;
    s32 var_s3;
    s32 var_s0;
    s32 var_s1;
    s32 var_s2;

    switch (self->step) {
    case 0:
        self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA |
                      FLAG_UNK_100000;
        self->unk5A = 0x14;
        self->zPriority = PLAYER.zPriority - 8;
        self->palette = PAL_WPN_CAT;
        self->animSet = ANIMSET_OVL(19);
        MarSetAnimation(D_pspeu_092C0958);
        self->facingLeft = PLAYER.facingLeft;
        self->velocityX = FIX(3.0);
        self->posX.i.hi = PLAYER.posX.i.hi;
        self->posY.i.hi = PLAYER.posY.i.hi;
        self->hitboxWidth = 18;
        self->hitboxHeight = 30;
        self->hitboxOffX = 0;
        self->hitboxOffY = -8;
        self->ext.maria092A6E50.unkB0 = 0;
        MarSetWeaponParams(self, 15, ELEMENT_HOLY, 2, 16, 16, 1, 0);
        self->ext.maria092A6E50.timer = 0;
        g_Player.unk7A = 1;
        self->ext.maria092A6E50.nBounce = 3;
        self->step = 2;
        self->ext.maria092A6E50.opacity = 128;
        break;
    case 1:
        self->velocityX += FIX(1.0);
        if (self->velocityX > FIX(3.0)) {
            self->velocityX = FIX(3.0);
        }
        if ((self->ext.maria092A6E50.timer % 10) == 0) {
            g_api.PlaySfx(SFX_QUIET_STEPS);
        }
        self->ext.maria092A6E50.timer++;
        func_pspeu_092A6A08(
            self, self->facingLeft ? -self->velocityX : self->velocityX, 0,
            &col);
        if (col.effects & EFFECT_SOLID || self->hitFlags == 1) {
            self->velocityX = FIX(-3.0);
            self->velocityY = FIX(-8.0);
            if (col.effects & EFFECT_SOLID) {
                self->ext.maria092A6E50.nBounce = 0;
            }
            if (self->ext.maria092A6E50.nBounce > 0) {
                self->ext.maria092A6E50.nBounce--;
                self->step = 3;
            } else {
                self->step = 4;
            }
            self->ext.maria092A6E50.timer = 0;
        } else {
            g_api.CheckCollision(self->posX.i.hi, self->posY.i.hi + 1, &col, 0);
            if (!(col.effects & EFFECT_UNK_0002)) {
                self->velocityY = FIX(-8.0);
                self->step = 2;
                self->ext.maria092A6E50.timer = 0;
            }
        }
        break;
    case 2:
    case 3:
        if (self->step == 2) {
            self->velocityX += FIX(1.0);
            if (self->velocityX > FIX(3.0)) {
                self->velocityX = FIX(3.0);
            }
        }
        self->velocityY += FIX(1.0);
        if (self->velocityY > FIX(4.0)) {
            self->velocityY = FIX(4.0);
        }
        func_pspeu_092A6A08(
            self, self->facingLeft ? -self->velocityX : self->velocityX,
            self->velocityY, &col);
        if (col.effects & EFFECT_UNK_0002) {
            var_s3 = func_pspeu_092A6958(
                self->posX.i.hi, self->posY.i.hi, self->velocityY >> 16);
            if (var_s3 != -1) {
                self->velocityX = FIX(3.0);
                self->posY.i.hi = var_s3;
                self->posY.i.lo = 0;
                self->step = 1;
                col.effects = EFFECT_NONE;
                self->hitFlags = 0;
            }
        }
        if ((col.effects & EFFECT_SOLID) || self->hitFlags == 1) {
            self->velocityX = FIX(-3.0);
            self->velocityY = FIX(-8.0);
            if (col.effects & EFFECT_SOLID) {
                self->ext.maria092A6E50.nBounce = 0;
            }
            if (self->ext.maria092A6E50.nBounce > 0) {
                self->ext.maria092A6E50.nBounce--;
                self->step = 3;
            } else {
                self->step = 4;
            }
        }
        break;
    case 4:
        self->hitboxState = 0;
        self->velocityY += FIX(1.0);
        if (self->velocityY > FIX(4.0)) {
            self->velocityY = FIX(4.0);
        }
        self->posX.val += self->facingLeft ? -self->velocityX : self->velocityX;
        self->posY.val += self->velocityY;
        self->ext.maria092A6E50.opacity -= 8;
        if (self->ext.maria092A6E50.opacity <= 0) {
            func_pspeu_092BEA38(self, 0);
            self->step = 5;
        } else {
            func_pspeu_092BEA38(self, self->ext.maria092A6E50.opacity);
        }
        break;
    case 5:
        g_Player.unk7A = 0;
        DestroyEntity(self);
        break;
    }
    if (self->step != 5) {
        if (self->posX.i.hi < -8 || self->posX.i.hi > 264 ||
            self->posY.i.hi > 264) {
            self->step = 5;
        }
    }
    self->hitFlags = 0;
}

extern AnimationFrame D_pspeu_092C0970[];
void func_pspeu_092A7560(Entity* self) {
    switch (self->step) {
    case 0:
        self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA |
                      FLAG_UNK_100000;
        self->unk5A = 0x14;
        self->zPriority = PLAYER.zPriority - 8;
        self->palette = PAL_WPN_CAT_CRASH;
        self->animSet = ANIMSET_OVL(19);
        MarSetAnimation(D_pspeu_092C0970);
        self->ext.maria092A7560.timer = 0;
        self->ext.maria092A7560.opacity = 0;
        self->ext.maria092A7560.unk46 = g_Player.unk46;
        self->step = 1;
        func_pspeu_092BF8B8(2);
        func_pspeu_092BEA38(self, 0);
        break;
    case 1:
        if (g_Player.unk5C == 1) {
            g_api.PlaySfx(SFX_VO_MAR_8F1);
            self->step = 3;
        }
        break;
    case 3:
        self->facingLeft = PLAYER.facingLeft;
        self->posX.i.hi = PLAYER.posX.i.hi;
        self->posY.i.hi = PLAYER.posY.i.hi + 24;
        self->ext.maria092A7560.opacity += 16;
        if (self->ext.maria092A7560.opacity >= 128) {
            func_pspeu_092BEA38(self, 128);
            self->ext.maria092A7560.opacity = 0;
            self->step = 2;
        } else {
            func_pspeu_092BEA38(self, self->ext.maria092A7560.opacity);
        }
        break;
    case 4:
        self->posX.i.hi += self->facingLeft ? -4 : 4;
        self->ext.maria092A7560.opacity -= 16;
        if (self->ext.maria092A7560.opacity <= 0) {
            func_pspeu_092BEA38(self, 0);
            self->ext.maria092A7560.opacity = 0;
            self->step = self->ext.maria092A7560.timer > 300 ? 5 : 3;
        } else {
            func_pspeu_092BEA38(self, self->ext.maria092A7560.opacity);
        }
        break;
    case 2:
        if (self->facingLeft != PLAYER.facingLeft) {
            self->ext.maria092A7560.opacity = 128;
            self->step = 4;
        } else {
            self->facingLeft = PLAYER.facingLeft;
            self->posX.i.hi = PLAYER.posX.i.hi;
            self->posY.i.hi = PLAYER.posY.i.hi + 24;
            if (self->ext.maria092A7560.timer > 300) {
                self->ext.maria092A7560.opacity = 128;
                self->step = 4;
            }
        }
        break;
    case 5:
        g_Player.unk5C = 0;
        DestroyEntity(self);
        break;
    }
    self->ext.maria092A7560.timer++;
    if (self->step != 5 && g_Player.padTapped & PAD_SQUARE) {
        MarCreateEntFactoryFromEntity(self, _BP_HOLYWATER_GLASS, 0);
    }
    self->ext.maria092A7560.unk46 = g_Player.unk46;
}

extern AnimationFrame D_pspeu_092C0988[];
void func_pspeu_092A7950(Entity* self) {
    switch (self->step) {
    case 0:
        self->flags = FLAG_UNK_100000 | FLAG_KEEP_ALIVE_OFFCAMERA |
                      FLAG_POS_CAMERA_LOCKED;
        self->unk5A = 0x14;
        self->zPriority = PLAYER.zPriority - 8;
        self->palette = PAL_WPN_CAT;
        self->animSet = ANIMSET_OVL(19);
        MarSetAnimation(D_pspeu_092C0988);
        self->facingLeft = PLAYER.facingLeft;
        self->velocityX = FIX(4);
        self->posX.i.hi = PLAYER.posX.i.hi;
        self->posY.i.hi = PLAYER.posY.i.hi + 24;
        self->hitboxWidth = 16;
        self->hitboxHeight = 32;
        self->hitboxOffX = 0;
        self->hitboxOffY = 0;
        self->ext.maria092A8AE8.unkB0 = 0;
        MarSetWeaponParams(
            self, 32, ELEMENT_CUT | ELEMENT_HOLY, 2, 16, 16, 1, 0);
        g_api.PlaySfx(SFX_ALUCARD_SWORD_SWISH);
        self->step = 1;
        return;
    case 1:
        self->posX.val += self->facingLeft ? -self->velocityX : self->velocityX;
        if (self->poseTimer < 0) {
            self->step = 2;
        }
        if (self->posX.i.hi < -16 || self->posX.i.hi > 272) {
            self->step = 2;
            return;
        }
        break;
    case 2:
        DestroyEntity(self);
        break;
    }
}

AnimationFrame D_pspeu_092C09B0[];
void func_pspeu_092A7B80(Entity* self) {
    switch (self->step) {
    case 0:
        self->flags = FLAG_UNK_100000 | FLAG_KEEP_ALIVE_OFFCAMERA;
        self->unk5A = 0x15;
        self->zPriority = PLAYER.zPriority - 8;
        self->palette = PAL_WPN_DRAGON;
        self->animSet = ANIMSET_OVL(21);
        MarSetAnimation(D_pspeu_092C09B0);
        self->facingLeft = PLAYER.facingLeft;
        self->velocityX = 0;
        self->posX.i.hi = PLAYER.posX.i.hi + (PLAYER.facingLeft ? 32 : -32);
        self->posY.i.hi = PLAYER.posY.i.hi - 8;
        self->ext.maria092A7B80.y = self->posY.i.hi;
        self->hitboxWidth = 24;
        self->hitboxHeight = 32;
        self->hitboxOffX = 0;
        self->hitboxOffY = 0;
        self->ext.maria092A7B80.unkB0 = 0;
        MarSetWeaponParams(self, 42, ELEMENT_HOLY, 2, 16, 16, 1, 0);
        g_Player.unk7A = 1;
        self->ext.maria092A7B80.timer = 0;
        self->step = 2;
        // fallthrough
    case 2:
        self->ext.maria092A7B80.opacity += 16;
        if (self->ext.maria092A7B80.opacity >= 128) {
            func_pspeu_092BEA38(self, 128);
            self->step = 1;
            return;
        }
        func_pspeu_092BEA38(self, self->ext.maria092A7B80.opacity);
        break;
    case 1:
        self->velocityX += FIX(0.25);
        if (self->velocityX > FIX(3)) {
            self->velocityX = FIX(3);
        }
        self->posX.val += self->facingLeft ? -self->velocityX : self->velocityX;
        self->posY.i.hi =
            self->ext.maria092A7B80.y +
            -rsin(self->ext.maria092A7B80.timer << 6) * 0x18 / 0x1000;
        if ((self->ext.maria092A7B80.timer % 60) == 0) {
            g_api.PlaySfx(SFX_WING_FLAP_B);
        }
        self->ext.maria092A7B80.timer++;
        if (self->posX.i.hi < -16 || self->posX.i.hi > 272) {
            self->step = 3;
            return;
        }
        break;
    case 3:
        g_Player.unk7A = 0;
        DestroyEntity(self);
        break;
    }
}

static s32 func_pspeu_092A7F20(s32 angle) {
    angle %= 0x1000;
    if (angle < 0) {
        angle += 0x1000;
    }
    return angle;
}

extern s32 D_pspeu_092E5908[0x80];
extern s32 D_pspeu_092E5B10;
static Entity* func_pspeu_092A7F78(Entity* self) {
    Entity* e;
    s32 i;
    s32 var_s2;
    s32 found;

    found = 0;
    e = &g_Entities[STAGE_ENTITY_START];
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
                e = &g_Entities[var_s2 + 0x40];
                D_pspeu_092E5B10 = (var_s2 + 1) % LEN(D_pspeu_092E5908);
                return e;
            }
            var_s2 = (var_s2 + 1) % LEN(D_pspeu_092E5908);
        }
    }
    return NULL;
}

static int func_pspeu_092A81C0(Entity* entity) {
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

extern AnimationFrame D_pspeu_092C09E0[];
void func_pspeu_092A82E0(Entity* self) {
    s32 x;
    s32 y;
    s32 angle;
    s32 i;

    switch (self->step) {
    case 0:
        self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA |
                      FLAG_UNK_100000;
        self->unk5A = 0x15;
        self->zPriority = 0x1C0;
        self->palette = PAL_WPN_DRAGON_CRASH;
        self->animSet = ANIMSET_OVL(21);
        MarSetAnimation(D_pspeu_092C09E0);
        self->facingLeft = 0;
        self->velocityX = 0;
        self->posX.i.hi = PLAYER.posX.i.hi;
        self->posY.i.hi = PLAYER.posY.i.hi - 32;
        self->rotZ = 0;
        self->ext.maria092A82E0.velocity = 1280;
        self->hitboxWidth = 24;
        self->hitboxHeight = 24;
        self->hitboxOffX = 0;
        self->hitboxOffY = 0;
        self->ext.maria092A82E0.unkB0 = 0;
        MarSetWeaponParams(
            self, 24, ELEMENT_HOLY | ELEMENT_THUNDER, 2, 40, 16, 1, 0);
        D_pspeu_092E5900 = 0;
        self->ext.maria092A82E0.timer = 0;
        self->step = 1;
        func_pspeu_092BF8B8(4);
        self->ext.maria092A82E0.opacity = 0;
        func_pspeu_092BEA38(self, 0);
        break;
    case 1:
        if (g_Player.unk5C == 1) {
            MarCreateEntFactoryFromEntity(self, _BP_NOT_IMPLEMENTED_1, 0);
            self->step = 2;
            g_api.PlaySfx(SFX_VO_MAR_8F1);
        }
        self->drawFlags |= FLAG_DRAW_ROTZ;
        break;
    case 2:
        if (self->ext.maria092A82E0.opacity < 128) {
            self->ext.maria092A82E0.opacity += 8;
            func_pspeu_092BEA38(self, self->ext.maria092A82E0.opacity);
        } else {
            func_pspeu_092BEA38(self, 128);
        }
        self->drawFlags |= FLAG_DRAW_ROTZ;
        {
            MATRIX m;
            VECTOR vTranslate = {0, 0, 0};
            VECTOR vVelocity;
            SVECTOR svVelocity;
            s32 out;
            if (func_pspeu_092A81C0(
                    *(Entity**)&self->ext.maria092A82E0.target) == 0) {
                self->ext.maria092A82E0.target = func_pspeu_092A7F78(self);
            }
            if (self->ext.maria092A82E0.target) {
                x = (*(Entity**)&self->ext.maria092A82E0.target)->posX.i.hi;
                y = (*(Entity**)&self->ext.maria092A82E0.target)->posY.i.hi;
            } else {
                x = PLAYER.posX.i.hi;
                y = PLAYER.posY.i.hi;
            }
            self->rotZ = func_pspeu_092A7F20(self->rotZ);
            angle = func_pspeu_092A7F20(
                ratan2(y - self->posY.i.hi, x - self->posX.i.hi));
            if (self->rotZ < angle) {
                if (angle - self->rotZ < 0x800) {
                    self->rotZ += 0x40;
                } else {
                    self->rotZ -= 0x40;
                }
            } else if (self->rotZ - angle < 0x800) {
                self->rotZ -= 0x40;
            } else {
                self->rotZ += 0x40;
            }
            SetGeomOffset(0, 0);
            func_89285A0(self->rotZ, &m);
            TransMatrix(&m, &vTranslate);
            SetRotMatrix(&m);
            SetTransMatrix(&m);
            svVelocity.vx = self->ext.maria092A82E0.velocity;
            svVelocity.vy = 0;
            svVelocity.vz = 0;
            func_892796C(&svVelocity, &vVelocity, &out);
            self->velocityX = vVelocity.vx << 8;
            self->velocityY = vVelocity.vy << 8;
            FntPrint("%08x : %08x\n", self->velocityX, self->velocityY);
            self->posX.val += self->velocityX;
            self->posY.val += self->velocityY;
            if ((self->ext.maria092A82E0.timer % 120) == 0) {
                g_api.PlaySfx(SFX_SWISHES_ECHO_REPEAT);
            }
            self->ext.maria092A82E0.timer++;
            if (self->ext.maria092A82E0.timer > 300) {
                self->step = 3;
            }
        }
        break;
    case 3:
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        self->ext.maria092A82E0.timer++;
        if (self->ext.maria092A82E0.timer > 300 &&
            (self->posX.i.hi < -0x100 || self->posX.i.hi > 0x200 ||
             self->posY.i.hi < -0x100 || self->posY.i.hi > 0x200)) {
            self->step = 4;
        }
        break;
    case 4:
        g_Player.unk5C = 0;
        D_pspeu_092E5900 = 0;
        DestroyEntity(self);
        break;
    }
    if (g_Player.unk5C == 1 && self->step != 4) {
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

extern AnimationFrame D_pspeu_092C09E0[];
void func_pspeu_092A8AE8(Entity* self) {
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
        self->unk5A = 0x15;
        self->zPriority = 0x1C0;
        self->palette = PAL_WPN_DRAGON_CRASH;
        self->animSet = ANIMSET_OVL(21);
        MarSetAnimation(D_pspeu_092C09E0);
        self->facingLeft = PLAYER.facingLeft;
        self->velocityX = 0;
        self->posX.i.hi = PLAYER.posX.i.hi;
        self->posY.i.hi = PLAYER.posY.i.hi;
        self->hitboxWidth = 24;
        self->hitboxHeight = 24;
        self->hitboxOffX = 0;
        self->hitboxOffY = 0;
        self->ext.maria092A8AE8.unkB0 = 0;
        MarSetWeaponParams(
            self, 24, ELEMENT_HOLY | ELEMENT_THUNDER, 2, 40, 16, 1, 0);
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
            prim->tpage = 5;
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
                    s32 out;
                    s32 angle;
                    angle = func_pspeu_092A7F20(
                        ratan2(spD0 - var_s5, spD4 - var_s6));
                    func_89285A0(angle, &m);
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
                        func_892796C(&sp40, &sp60, &out);
                        func_892796C(&svPosStart, &vPosStart, &out);
                        func_892796C(&sp50, &sp80, &out);
                        func_892796C(&svPosEnd, &vPosEnd, &out);
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
                        func_892796C(&svPosStart, &vPosStart, &out);
                        func_892796C(&svPosEnd, &vPosEnd, &out);
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
        if (g_Player.unk5C != 0) {
            return;
        }
        self->step = 2;
        break;
    case 2:
        DestroyEntity(self);
        break;
    }
}

static int func_pspeu_092A9250() {
    switch (PLAYER.step) {
    case PL_S_CROUCH:
        return -20;
    default:
        return -36;
    }
}

AnimationFrame D_pspeu_092C09F8[];
void func_pspeu_092A9288(Entity* self) {
    switch (self->step) {
    case 0:
        self->flags = FLAG_UNK_100000 | FLAG_KEEP_ALIVE_OFFCAMERA |
                      FLAG_POS_CAMERA_LOCKED;
        self->unk5A = 0x11;
        self->drawMode = DRAW_TPAGE | DRAW_TPAGE2;
        self->zPriority = PLAYER.zPriority - 8;
        self->palette = PAL_WPN_CARDINAL;
        self->animSet = ANIMSET_OVL(0x14);
        MarSetAnimation(D_pspeu_092C09F8);
        self->facingLeft = 0;
        self->velocityX = 0;
        self->posX.i.hi = PLAYER.posX.i.hi;
        self->posY.i.hi = PLAYER.posY.i.hi + 0x18 + func_pspeu_092A9250();
        self->rotX = 0;
        self->rotY = 0;
        self->drawFlags = FLAG_DRAW_ROTX | FLAG_DRAW_ROTY;
        self->hitboxWidth = 48;
        self->hitboxHeight = 40;
        self->hitboxOffX = 0;
        self->hitboxOffY = -20;
        self->ext.maria092A9288.unkB0 = 0;
        MarSetWeaponParams(
            self, 32, ELEMENT_HOLY | ELEMENT_FIRE, 2, 32, 16, 1, 0);
        g_api.PlaySfx(SFX_FIREBALL_SHOT_B);
        g_Player.unk7A = 1;
        self->ext.maria092A9288.timer = 0;
        self->step++;
        break;
    case 1:
        self->posX.i.hi = PLAYER.posX.i.hi;
        self->posY.i.hi = PLAYER.posY.i.hi + 0x18 + func_pspeu_092A9250();
        self->hitboxOffY = -20;
        self->rotX += 16;
        self->rotY += 16;
        if (self->rotX == 256) {
            self->step++;
        }
        break;
    case 2:
        self->posX.i.hi = PLAYER.posX.i.hi;
        self->posY.i.hi = PLAYER.posY.i.hi + 0x18 + func_pspeu_092A9250();
        self->hitboxOffY = -20;
        self->drawFlags = FLAG_DRAW_DEFAULT;
        self->ext.maria092A9288.timer++;
        if (self->ext.maria092A9288.timer >= 60) {
            self->step++;
        }
        break;
    case 3:
        g_Player.unk7A = 0;
        DestroyEntity(self);
        break;
    }
    if (PLAYER.step != PL_S_SUBWPN_28) {
        self->step = 3;
    }
}

extern AnimationFrame D_pspeu_092C0A28[];
void func_pspeu_092A95A8(Entity* self) {
    s32 var_s0;

    switch (self->step) {
    case 0:
        self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA |
                      FLAG_UNK_100000;
        self->unk5A = 0x11;
        self->zPriority = 0x1C0;
        self->palette = PAL_WPN_CARDINAL;
        self->animSet = ANIMSET_OVL(20);
        MarSetAnimation(D_pspeu_092C0A28);
        self->facingLeft = PLAYER.facingLeft;
        if (PLAYER.facingLeft) {
            var_s0 = 24;
        } else {
            var_s0 = -24;
        }
        self->posX.i.hi = PLAYER.posX.i.hi + var_s0;
        self->posY.i.hi = PLAYER.posY.i.hi + 24;
#if defined(VERSION_PC)
        g_Player.unk20 = (signed long long)self;
#else
        g_Player.unk20 = (s32)self;
#endif
        self->ext.maria092A95A8.timer = 0;
        self->ext.maria092A95A8.nSpawn = 0;
        self->ext.maria092A95A8.opacity = 0;
        self->step = 1;
        func_pspeu_092BF8B8(1);
        func_pspeu_092BEA38(self, 0);
        break;
    case 1:
        if (g_Player.unk5C == 1) {
            g_api.PlaySfx(SFX_VO_MAR_8F1);
            self->step = 3;
        }
        break;
    case 3:
        self->ext.maria092A95A8.opacity += 16;
        if (self->ext.maria092A95A8.opacity >= 128) {
            func_pspeu_092BEA38(self, 128);
            self->step = 2;
        } else {
            func_pspeu_092BEA38(self, self->ext.maria092A95A8.opacity);
        }
        break;
    case 2:
        if (self->ext.maria092A95A8.timer > 300) {
            self->ext.maria092A95A8.opacity = 128;
            self->step = 4;
        }
        break;
    case 4:
        self->posY.i.hi -= 4;
        self->ext.maria092A95A8.opacity -= 16;
        if (self->ext.maria092A95A8.opacity <= 0) {
            func_pspeu_092BEA38(self, 0);
            self->step = 5;
        } else {
            func_pspeu_092BEA38(self, self->ext.maria092A95A8.opacity);
        }
        break;
    case 5:
        g_Player.unk20 = 0;
        g_Player.unk5C = 0;
        DestroyEntity(self);
        break;
    }
    self->ext.maria092A95A8.timer++;
    if (g_Player.unk5C == 1 && self->step == 2 &&
        self->ext.maria092A95A8.timer < 240 &&
        (self->ext.maria092A95A8.timer % 5) == 0) {
        MarCreateEntFactoryFromEntity(self, _BP_VIBHUTI, 0);
        self->ext.maria092A95A8.nSpawn++;
    }
}

static s32 func_pspeu_092A9920(s32 arg0) {
    arg0 %= 0x1000;
    if (arg0 < 0) {
        arg0 += 0x1000;
    }
    return arg0;
}

extern s32 D_pspeu_092E5D18[0x80];
extern s32 D_pspeu_092E5F18;
static Entity* func_pspeu_092A9978(Entity* self) {
    Entity* e;
    s32 i;
    s32 var_s2;
    s32 found;

    found = 0;
    e = &g_Entities[STAGE_ENTITY_START];
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
                e = &g_Entities[var_s2 + 0x40];
                D_pspeu_092E5F18 = (var_s2 + 1) % LEN(D_pspeu_092E5D18);
                return e;
            }
            var_s2 = (var_s2 + 1) % LEN(D_pspeu_092E5D18);
        }
    }
    return NULL;
}

static int func_pspeu_092A9C28(Entity* entity) {
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
    entity->ext.maria092A9E88.pos1.x = x;
    entity->ext.maria092A9E88.pos1.y = y;
    entity->ext.maria092A9E88.pos2.x = x;
    entity->ext.maria092A9E88.pos2.y = y;
    entity->ext.maria092A9E88.pos3.x = x;
    entity->ext.maria092A9E88.pos3.y = y;
    entity->ext.maria092A9E88.pos4.x = x;
    entity->ext.maria092A9E88.pos4.y = y;
}

static void func_pspeu_092A9DE8(Entity* entity, s32 x, s32 y) {
    entity->ext.maria092A9E88.pos4.x = entity->ext.maria092A9E88.pos3.x;
    entity->ext.maria092A9E88.pos4.y = entity->ext.maria092A9E88.pos3.y;
    entity->ext.maria092A9E88.pos3.x = entity->ext.maria092A9E88.pos2.x;
    entity->ext.maria092A9E88.pos3.y = entity->ext.maria092A9E88.pos2.y;
    entity->ext.maria092A9E88.pos2.x = entity->ext.maria092A9E88.pos1.x;
    entity->ext.maria092A9E88.pos2.y = entity->ext.maria092A9E88.pos1.y;
    entity->ext.maria092A9E88.pos1.x = x;
    entity->ext.maria092A9E88.pos1.y = y;
}

extern AnimationFrame D_pspeu_092C0A48[];
void func_pspeu_092A9E88(Entity* self) {
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
    parent = *(Entity**)&g_Player.unk20;
    switch (self->step) {
    case 0: {
        if (g_Player.unk5C == 0 || parent == NULL) {
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
        self->unk5A = 0x11;
        self->zPriority = 0x1C0;
        self->palette = PAL_WPN_CARDINAL;
        self->animSet = ANIMSET_OVL(20);
        MarSetAnimation(D_pspeu_092C0A48);
        self->facingLeft = parent->facingLeft;
        self->posX.i.hi = parent->posX.i.hi + (self->facingLeft ? 37 : -37);
        self->posY.i.hi = parent->posY.i.hi - 52;
        func_pspeu_092A9D48(self, self->posX.i.hi, self->posY.i.hi);
        self->ext.maria092A9E88.defaultTargetX =
            self->posX.i.hi + (self->facingLeft ? -200 : 200);
        self->ext.maria092A9E88.defaultTargetY = self->posY.i.hi;
        if (parent->ext.maria092A9E88.defaultTargetY & 1) {
            self->ext.maria092A9E88.angle = (rand() % 0x400) / 2;
            yStart = -(rand() % 24);
        } else {
            self->ext.maria092A9E88.angle = 0x400 - (rand() % 0x400) / 2;
            yStart = rand() % 24;
        }

        self->posY.i.hi += self->facingLeft ? yStart : -yStart;
        self->ext.maria092A9E88.angle += (self->facingLeft ? 0 : 0x800) - 0x200;
        self->hitboxWidth = 16;
        self->hitboxHeight = 16;
        self->hitboxOffX = 0;
        self->hitboxOffY = 0;
        self->ext.maria092A9E88.unkB0 = 0;
        MarSetWeaponParams(
            self, 32, ELEMENT_HOLY | ELEMENT_FIRE, 2, 28, 16, 1, 0);
        self->ext.maria092A9E88.timer = 0;
        self->ext.maria092A9E88.velocityX = (rand() % 384) + 0x80;
        self->step = 1;
        g_api.PlaySfx(SFX_UNK_FIRE_WHOOSH);
    } break;
    case 1: {
        self->ext.maria092A9E88.timer++;
        {
            MATRIX m;
            VECTOR vTransform = {0, 0, 0};
            VECTOR vVelocity;
            SVECTOR svVelocity;
            s32 sp48;
            if (self->ext.maria092A9E88.timer < 35) {
                if (func_pspeu_092A9C28(self->ext.maria092A9E88.target) == 0) {
                    self->ext.maria092A9E88.target = func_pspeu_092A9978(self);
                }
                if (self->ext.maria092A9E88.target) {
                    targetX = self->ext.maria092A9E88.target->posX.i.hi;
                    targetY = self->ext.maria092A9E88.target->posY.i.hi;
                    if (abs(targetX - self->posX.i.hi) < 16 &&
                        abs(targetY - self->posY.i.hi) < 16) {
                        self->ext.maria092A9E88.timer = 35;
                    }
                } else {
                    targetX = self->ext.maria092A9E88.defaultTargetX;
                    targetY = self->ext.maria092A9E88.defaultTargetY;
                }
                self->ext.maria092A9E88.angle =
                    func_pspeu_092A9920(self->ext.maria092A9E88.angle);
                angle = func_pspeu_092A9920(ratan2(
                    targetY - self->posY.i.hi, targetX - self->posX.i.hi));
                if (self->ext.maria092A9E88.angle < angle) {
                    if (angle - self->ext.maria092A9E88.angle < 0x800) {
                        self->ext.maria092A9E88.angle += 0x50;
                    } else {
                        self->ext.maria092A9E88.angle -= 0x50;
                    }
                } else {
                    if (self->ext.maria092A9E88.angle - angle < 0x800) {
                        self->ext.maria092A9E88.angle -= 0x50;
                    } else {
                        self->ext.maria092A9E88.angle += 0x50;
                    }
                }
                self->ext.maria092A9E88.velocityX += acceleration;
                if (self->ext.maria092A9E88.velocityX > 0x400) {
                    self->ext.maria092A9E88.velocityX = 0x400;
                }
            } else {
                self->ext.maria092A9E88.velocityX += initialAcceleration;
            }
            SetGeomOffset(0, 0);
            func_89285A0(self->ext.maria092A9E88.angle, &m);
            TransMatrix(&m, &vTransform);
            SetRotMatrix(&m);
            SetTransMatrix(&m);
            svVelocity.vx = self->ext.maria092A9E88.velocityX;
            svVelocity.vy = 0;
            svVelocity.vz = 0;
            func_892796C(&svVelocity, &vVelocity, &sp48);
            self->velocityX = vVelocity.vx << 8;
            self->velocityY = vVelocity.vy << 8;
            self->posX.val += self->velocityX;
            self->posY.val += self->velocityY;
            if (self->ext.maria092A9E88.timer % 2 == 0) {
                func_pspeu_092A9DE8(self, self->posX.i.hi, self->posY.i.hi);
            } else {
                self->ext.maria092A9E88.pos1.x = self->posX.i.hi;
                self->ext.maria092A9E88.pos1.y = self->posY.i.hi;
            }
            prim = &g_PrimBuf[self->primIndex];
            for (i = 0; i < 4; i++) {
                color = -0x80;
                prim->clut = 0x11A;
                prim->priority = self->zPriority;
                prim->drawMode = DRAW_DEFAULT;
                switch (i) {
                case 0:
                    x = self->ext.maria092A9E88.pos1.x;
                    y = self->ext.maria092A9E88.pos1.y;
                    break;
                case 1:
                    x = self->ext.maria092A9E88.pos2.x;
                    y = self->ext.maria092A9E88.pos2.y;
                    break;
                case 2:
                    x = self->ext.maria092A9E88.pos3.x;
                    y = self->ext.maria092A9E88.pos3.y;
                    break;
                case 3:
                    x = self->ext.maria092A9E88.pos4.x;
                    y = self->ext.maria092A9E88.pos4.y;
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
                    prim->tpage = 4;
                } else {
                    prim->u0 = 0x98;
                    prim->v0 = 0x38;
                    prim->u1 = 0xA7;
                    prim->v1 = 0x38;
                    prim->u2 = 0x98;
                    prim->v2 = 0x47;
                    prim->u3 = 0xA7;
                    prim->v3 = 0x47;
                    prim->tpage = 0x24;
                    prim->drawMode |= FLAG_DRAW_ROTX | FLAG_DRAW_ROTZ;
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
            if (self->ext.maria092A9E88.timer > 35 &&
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

extern AnimationFrame D_pspeu_092C0A50[];
void func_pspeu_092AAA38(Entity* self) {
    switch (self->step) {
    case 0:
        self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA |
                      FLAG_UNK_100000;
        self->unk5A = 0x10;
        self->zPriority = PLAYER.zPriority - 8;
        self->palette = PAL_WPN_TURTLE;
        self->animSet = ANIMSET_OVL(18);
        MarSetAnimation(D_pspeu_092C0A50);
        self->facingLeft = PLAYER.facingLeft;
        self->velocityX = 0;
        self->ext.maria092AAA38.x = 0;
        self->posX.i.hi = PLAYER.posX.i.hi + self->ext.maria092AAA38.x;
        self->posY.i.hi = PLAYER.posY.i.hi + 24;
        self->hitboxWidth = 24;
        self->hitboxHeight = 48;
        self->hitboxOffX = 0;
        self->hitboxOffY = 0;
        self->attack = 255;
        self->attackElement = 0;
        self->hitboxState = 4;
        self->nFramesInvincibility = 6;
        self->stunFrames = 0;
        self->hitEffect = 1;
        self->entityRoomIndex = 1;
        g_Player.unk7A = 1;
        self->ext.maria092AAA38.timer = 0;
        self->step++;
        break;
    case 1:
        self->posX.i.hi = PLAYER.posX.i.hi + self->ext.maria092AAA38.x;
        self->posY.i.hi = PLAYER.posY.i.hi + 24;
        self->ext.maria092AAA38.timer++;
        if (self->ext.maria092AAA38.timer >= 180) {
            self->step++;
        }
        break;
    case 2:
        g_Player.unk7A = 0;
        DestroyEntity(self);
        break;
    }
}

extern AnimationFrame D_pspeu_092C0A60[];
void func_pspeu_092AAC80(Entity* self) {
    s32 x;

    switch (self->step) {
    case 0:
        self->flags = FLAG_UNK_100000 | FLAG_KEEP_ALIVE_OFFCAMERA |
                      FLAG_POS_CAMERA_LOCKED;
        self->unk5A = 0x10;
        self->zPriority = PLAYER.zPriority - 6;
        self->palette = PAL_WPN_TURTLE;
        self->animSet = ANIMSET_OVL(18);
        MarSetAnimation(D_pspeu_092C0A60);
        self->facingLeft = PLAYER.facingLeft;
        if (PLAYER.facingLeft) {
            x = -74;
        } else {
            x = 74;
        }
        self->posX.i.hi = PLAYER.posX.i.hi + x;
        self->posY.i.hi = PLAYER.posY.i.hi - 16;
        self->rotX = 0;
        self->rotY = 0;
        self->drawFlags |= FLAG_DRAW_ROTX | FLAG_DRAW_ROTY;
        g_Player.unk28 = NULL;
#if defined(VERSION_PC)
        g_Player.unk20 = (signed long long)self;
#else
        g_Player.unk20 = (s32)self;
#endif
        g_Player.unk24 = 0;
        self->ext.maria092AAC80.timer = 0;
        self->ext.maria092AAC80.timer2 = 0;
        g_Player.unk2C = -1;
        self->step = 1;
        func_pspeu_092BF8B8(3);
        func_pspeu_092BEA38(self, 0);
        return;
    case 1:
        if (g_Player.unk5C == 1) {
            g_api.PlaySfx(SFX_VO_MAR_8F1);
            MarCreateEntFactoryFromEntity(self, _BP_CRASH_CROSSES_ONLY, 0);
            self->step = 3;
        }
        break;
    case 3:
        self->ext.maria092AAC80.timer2 += 16;
        if (self->ext.maria092AAC80.timer2 >= 128) {
            func_pspeu_092BEA38(self, 0x80);
            self->step = 2;
            return;
        }
        func_pspeu_092BEA38(self, self->ext.maria092AAC80.timer2);
        break;
    case 2:
        if (self->rotX < 256) {
            self->rotX += 16;
            self->rotY += 16;
        } else {
            self->drawFlags &= ~(FLAG_DRAW_ROTX | FLAG_DRAW_ROTY);
        }
        if ((self->ext.maria092AAC80.timer % 60) == 0) {
            g_api.PlaySfx(SFX_MAGIC_NOISE_SWEEP);
        }
        self->ext.maria092AAC80.timer++;
        if (self->ext.maria092AAC80.timer >= 0xFF) {
            self->step = 5;
        }
        break;
    case 5:
        if (self->rotX > 0x80) {
            self->drawFlags |= FLAG_DRAW_ROTX | FLAG_DRAW_ROTY | FLAG_DRAW_ROTZ;
            self->rotX -= 0x20;
            self->rotY -= 0x20;
            self->rotZ += 0xF78;
            return;
        }
        self->ext.maria092AAC80.timer2 = 0x80;
        self->step = 4;
        break;
    case 4:
        self->ext.maria092AAC80.timer2 -= 0x10;
        if (self->ext.maria092AAC80.timer2 <= 0) {
            func_pspeu_092BEA38(self, 0);
            self->drawFlags |= FLAG_DRAW_ROTZ | FLAG_DRAW_ROTY | FLAG_DRAW_ROTX;
            self->step = 6;
            func_pspeu_092BFEB0(g_Player.unk20);
            g_Player.unk2C = 0xB4;
            return;
        }
        func_pspeu_092BEA38(self, self->ext.maria092AAC80.timer2);
        self->drawFlags |= FLAG_DRAW_ROTX | FLAG_DRAW_ROTY | FLAG_DRAW_ROTZ;
        break;
    case 6:
        if (g_Player.unk28 == NULL) {
            self->step = 7;
            self->ext.maria092AAC80.timer3 = 0;
            return;
        }
        if (g_Player.unk2C == 0) {
            g_api.PlaySfx(SFX_HEALTH_PICKUP);
            g_Player.unk56 = 1;
            g_Player.unk58 = g_Player.unk24;
            self->step = 7;
            self->ext.maria092AAC80.timer3 = 0;
            return;
        }
        g_Player.unk2C--;
        break;
    case 7:
        self->ext.maria092AAC80.timer3++;
        if (self->ext.maria092AAC80.timer3 > 60) {
            g_Player.unk28 = NULL;
            g_Player.unk20 = 0;
            g_Player.unk5C = 0;
            DestroyEntity(self);
        }
        break;
    }
}

AnimationFrame D_pspeu_092C0A58[];
void func_pspeu_092AB1C0(Entity* self) {
    Entity* entity;
    s32 x;

    entity = *(Entity**)&g_Player.unk20;
    switch (self->step) {
    case 0:
        self->flags = FLAG_UNK_100000 | FLAG_KEEP_ALIVE_OFFCAMERA |
                      FLAG_POS_CAMERA_LOCKED;
        self->unk5A = 0x10;
        self->zPriority = PLAYER.zPriority - 7;
        self->palette = PAL_WPN_TURTLE;
        self->animSet = ANIMSET_OVL(18);
        MarSetAnimation(D_pspeu_092C0A58);
        self->facingLeft = 0;
        self->velocityX = 0;
        self->ext.maria092AB1C0.rotation = 0xF0;
        if (entity == NULL) {
            if (PLAYER.facingLeft) {
                x = -74;
            } else {
                x = 74;
            }
            self->posX.i.hi = PLAYER.posX.i.hi + x;
            self->posY.i.hi = PLAYER.posY.i.hi - 0x10;
        } else {
            self->posX.i.hi = entity->posX.i.hi;
            self->posY.i.hi = entity->posY.i.hi;
        }
        self->rotX = 0;
        self->rotY = 0;
        self->drawFlags |= FLAG_DRAW_ROTX | FLAG_DRAW_ROTY;
        self->drawMode |= DRAW_TPAGE;
        self->drawFlags |= FLAG_DRAW_ROTZ | FLAG_DRAW_UNK8;
        self->rotZ = 0;
        self->unk6C = 0x80;
        self->hitboxWidth = 48;
        self->hitboxHeight = 48;
        self->hitboxOffX = 0;
        self->hitboxOffY = 0;
        self->ext.maria092AB1C0.unkB0 = 0;
        MarSetWeaponParams(
            self, 5, ELEMENT_WATER | ELEMENT_HOLY, 2, 32, 0, 2, 0);
        self->ext.maria092AB1C0.hitboxState = self->hitboxState;
        self->hitboxState = 0;
        self->ext.maria092AB1C0.timer = 0;
        self->step = 1;
        self->rotZ += 0x1000 - (0x1000 / self->ext.maria092AB1C0.rotation);
        return;
    case 1:
        if (self->rotX < 256) {
            self->rotX += 16;
            self->rotY += 16;
        } else {
            self->hitboxState = self->ext.maria092AB1C0.hitboxState;
            self->drawFlags &= ~(FLAG_DRAW_ROTX | FLAG_DRAW_ROTY);
        }
        self->ext.maria092AB1C0.timer++;
        if (self->ext.maria092AB1C0.timer >= 240) {
            self->hitboxState = 0;
            self->step = 2;
        }
        if (self->ext.maria092AB1C0.timer % 8 == 0) {
            self->ext.maria092AB1C0.rotation -= 5;
        }
        self->rotZ += 0x1000 - (0x1000 / self->ext.maria092AB1C0.rotation);
        return;
    case 2:
        if (self->ext.maria092AB1C0.rotation >= 65) {
            self->ext.maria092AB1C0.rotation -= 5;
        } else {
            self->step = 3;
        }
        self->rotZ += 0x1000 - (0x1000 / self->ext.maria092AB1C0.rotation);
        return;
    case 3:
        if (self->rotX > 0) {
            self->rotX -= 8;
            self->rotY -= 8;
            self->drawFlags |= FLAG_DRAW_ROTX | FLAG_DRAW_ROTY;
        } else {
            self->step = 4;
        }
        self->rotZ += 0x1000 - (0x1000 / self->ext.maria092AB1C0.rotation);
        return;
    case 4:
        DestroyEntity(self);
        return;
    }
}
