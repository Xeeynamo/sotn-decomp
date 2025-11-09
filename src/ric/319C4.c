// SPDX-License-Identifier: AGPL-3.0-or-later
#include "ric.h"
#include "sfx.h"

// RIC Entity # 49. Comes from blueprint 57. Factory call in
// RicEntityCrashReboundStone. RicEntityCrashReboundStone is RIC Entity #48.
// Comes from blueprint 56. Blueprint 56 is subweapon 25. And subweapon 25 is
// the crash of subweapon 7. And subweapon 7 is the rebound stone. This is an
// entity spawned from the rebound stone crash.
static s32 angles_80155EE0[] = {0x00000F80, 0x00000100, 0x00000700, 0x00000880};
void func_8016D9C4(Entity* self) {
    PrimLineG2* prim;
    Primitive* prim2;
    s32 i;
    long angle;
    s32 var_s6;
    s32 var_s5;
    s32 var_s7;
    s32 brightness;

    switch (self->step) {
    case 0:
        self->primIndex = g_api.AllocPrimitives(PRIM_LINE_G2, 20);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags = FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_HAS_PRIMS;
        prim = (PrimLineG2*)&g_PrimBuf[self->primIndex];
        for (i = 0; i < 4; i++) {
            prim->preciseX.val = PLAYER.posX.val;
            prim->preciseY.val = PLAYER.posY.val - FIX(40);
            prim->priority = 194;
            prim->drawMode = DRAW_HIDE;
            prim->x0 = prim->x1 = PLAYER.posX.i.hi;
            prim->y0 = prim->y1 = PLAYER.posY.i.hi - 0x1C;
            prim->r0 = prim->g0 = prim->b0 = 0x80;
            prim->r1 = prim->g1 = prim->b1 = 0x70;
            prim->angle = angles_80155EE0[i];
            prim->delay = 1;
            prim = (PrimLineG2*)prim->next;
        }
        for (brightness = 0x80; i < 20; i++) {
            if (!(i % 4)) {
                brightness -= 0x10;
                switch (i / 4) {
                case 1:
                    self->ext.et_8016D9C4.lines[0] = prim;
                    break;
                case 2:
                    self->ext.et_8016D9C4.lines[1] = prim;
                    break;
                case 3:
                    self->ext.et_8016D9C4.lines[2] = prim;
                    break;
                case 4:
                    self->ext.et_8016D9C4.lines[3] = prim;
                    break;
                }
            }
            prim->priority = 0xC2;
            prim->drawMode = DRAW_HIDE;
            prim->x0 = prim->x1 = PLAYER.posX.i.hi;
            prim->y0 = prim->y1 = PLAYER.posY.i.hi - 0x1C;
            prim->r0 = prim->g0 = prim->b0 = brightness;
            prim->r1 = prim->g1 = prim->b1 = brightness - 0x10;
            prim = (PrimLineG2*)prim->next;
        }
        self->ext.et_8016D9C4.unk90 = 4;
        self->ext.et_8016D9C4.unk8C = self->ext.et_8016D9C4.unk8E = 0;
        g_api.PlaySfx(SFX_RIC_RSTONE_TINK);
        self->step++;
        break;
    case 1:
        self->ext.et_8016D9C4.unk8E = 1;
        switch (self->ext.et_8016D9C4.unk8C) {
        case 0:
            prim = (PrimLineG2*)&g_PrimBuf[self->primIndex];
            break;
        case 1:
            prim = self->ext.et_8016D9C4.lines[0];
            break;
        case 2:
            prim = self->ext.et_8016D9C4.lines[1];
            break;
        case 3:
            prim = self->ext.et_8016D9C4.lines[2];
            break;
        case 4:
            prim = self->ext.et_8016D9C4.lines[3];
            break;
        }
        for (i = 0; i < 4; i++) {
            prim->drawMode &= ~DRAW_HIDE;
            prim = (PrimLineG2*)prim->next;
        }
        self->ext.et_8016D9C4.unk8C++;
        if (self->ext.et_8016D9C4.unk8C > 4) {
            self->step++;
        }
        break;
    case 2:
        if (!self->ext.et_8016D9C4.unk90) {
            self->step++;
            break;
        }
        break;
    case 3:
        self->ext.et_8016D9C4.unk90++;
        if (self->ext.et_8016D9C4.unk90 > 4) {
            DestroyEntity(self);
            return;
        }
        break;
    }
    if (!self->ext.et_8016D9C4.unk8E) {
        return;
    }
    prim = (PrimLineG2*)&g_PrimBuf[self->primIndex];
    for (i = 0; i < 4; i++) {
        if (prim->delay) {
            prim->x1 = prim->x0;
            prim->y1 = prim->y0;
            prim->x0 = prim->preciseX.i.hi;
            prim->y0 = prim->preciseY.i.hi;
            var_s7 = ratan2(prim->preciseY.val, FIX(128) - prim->preciseX.val) &
                     0xFFF;
            angle = prim->angle - var_s7;
            if (labs(angle) > 0x800) {
                if (angle < 0) {
                    angle += 0x1000;
                } else {
                    angle -= 0x1000;
                }
            }
            if (angle >= 0) {
                if (angle > 0x80) {
                    var_s6 = 0x80;
                } else {
                    var_s6 = angle;
                }
                angle = var_s6;
            } else {
                if (angle < -0x80) {
                    var_s5 = -0x80;
                } else {
                    var_s5 = angle;
                }
                angle = var_s5;
            }
            prim->angle = prim->angle - angle;
            prim->angle &= 0xFFF;
            prim->velocityX.val = (rcos(prim->angle) << 4 << 4);
            prim->velocityY.val = -(rsin(prim->angle) << 4 << 4);
            prim->preciseX.val += prim->velocityX.val;
            prim->preciseY.val += prim->velocityY.val;
            self->posX.i.hi = prim->preciseX.i.hi;
            self->posY.i.hi = prim->preciseY.i.hi;
            RicCreateEntFactoryFromEntity(
                self, BP_CRASH_REBOUND_STONE_PARTICLES, 0);
            if (prim->preciseY.val < 0) {
                prim->delay = 0;
                prim->drawMode |= DRAW_HIDE;
                self->ext.et_8016D9C4.unk90--;
            }
        }
        prim = (PrimLineG2*)prim->next;
    }
    prim = self->ext.et_8016D9C4.lines[0];
    prim2 = &g_PrimBuf[self->primIndex];
    for (i = 0; i < 16; i++) {
        prim->x1 = prim->x0;
        prim->y1 = prim->y0;
        prim->x0 = prim2->x1;
        prim->y0 = prim2->y1;
        prim = (PrimLineG2*)prim->next;
        prim2 = prim2->next;
    }
}

// RIC Entity #50. Blueprint 58. Also created by rebound stone crash. Weird!
void RicEntityCrashReboundStoneExplosion(Entity* self) {
    Primitive* prim;
    s32 i;

    switch (self->step) {
    case 0:
        self->primIndex = g_api.AllocPrimitives(PRIM_G4, 0x10);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags = FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_HAS_PRIMS;
        prim = &g_PrimBuf[self->primIndex];
        for (i = 0; i < 0x10; i++) {
            prim->priority = 0xC2;
            prim->drawMode = DRAW_UNK_400 | DRAW_TPAGE2 | DRAW_TPAGE |
                             DRAW_COLORS | DRAW_TRANSP;
            prim->x0 = prim->x1 = 0x80;
            prim->y0 = prim->y1 = 0;
            prim = prim->next;
        }
        self->ext.reboundStoneCrashExplosion.unk7C = 0x40;
        self->ext.reboundStoneCrashExplosion.unk7E = 0;
        self->ext.reboundStoneCrashExplosion.unk84 = 0;
        self->ext.reboundStoneCrashExplosion.unk80 = 0x10;
        self->ext.reboundStoneCrashExplosion.unk82 = 8;
        g_api.PlaySfx(SFX_TELEPORT_BANG_B);
        self->step++;
        break;
    case 1:
        self->ext.reboundStoneCrashExplosion.unk84 += 0x20;
        if (self->ext.reboundStoneCrashExplosion.unk84 > 0x120) {
            self->ext.reboundStoneCrashExplosion.subweaponId =
                PL_W_CRASH_REBOUND_EXPLOSION;
            RicSetSubweaponParams(self);
            self->posX.val = FIX(128.0);
            self->posY.val = FIX(128.0);
            self->hitboxWidth = 0x80;
            self->hitboxHeight = 0x80;
            self->step++;
        }
        break;
    case 2:
        self->ext.reboundStoneCrashExplosion.unk86++;
        if (self->ext.reboundStoneCrashExplosion.unk86 == 5) {
            self->ext.reboundStoneCrashExplosion.unk80 = -0x18;
        } else if (self->ext.reboundStoneCrashExplosion.unk86 >= 0xF) {
            self->ext.reboundStoneCrashExplosion.unk82 = -0x18;
            self->step++;
        }
        break;
    case 3:
        break;
    case 4:
        DestroyEntity(self);
        return;
    }
    self->ext.reboundStoneCrashExplosion.unk7C +=
        self->ext.reboundStoneCrashExplosion.unk80;
    if (self->ext.reboundStoneCrashExplosion.unk7C > 0xFF) {
        self->ext.reboundStoneCrashExplosion.unk7C = 0xFF;
        self->ext.reboundStoneCrashExplosion.unk80 = 0;
    } else if (self->ext.reboundStoneCrashExplosion.unk7C < 0) {
        self->ext.reboundStoneCrashExplosion.unk7C =
            self->ext.reboundStoneCrashExplosion.unk80 = 0;
    }
    self->ext.reboundStoneCrashExplosion.unk7E +=
        self->ext.reboundStoneCrashExplosion.unk82;
    if (self->ext.reboundStoneCrashExplosion.unk7E > 0xFF) {
        self->ext.reboundStoneCrashExplosion.unk7E = 0xFF;
        self->ext.reboundStoneCrashExplosion.unk82 = 0;
    } else if (self->ext.reboundStoneCrashExplosion.unk7E < 0) {
        self->ext.reboundStoneCrashExplosion.unk7E =
            self->ext.reboundStoneCrashExplosion.unk82 = 0;
        self->step += 1;
    }
    prim = &g_PrimBuf[self->primIndex];
    for (i = 0; i < 16; i++) {
        prim->b0 = prim->b1 = self->ext.reboundStoneCrashExplosion.unk7C;
        prim->b2 = prim->b3 = self->ext.reboundStoneCrashExplosion.unk7E;
        prim->r0 = prim->r1 = prim->g0 = prim->g1 =
            self->ext.reboundStoneCrashExplosion.unk7C;
        prim->r2 = prim->r3 = prim->g2 = prim->g3 =
            self->ext.reboundStoneCrashExplosion.unk7E;
        if (self->step < 2) {
            prim->x2 =
                ((rcos(i << 7) * self->ext.reboundStoneCrashExplosion.unk84) >>
                 0xC) +
                0x80;
            prim->x3 = ((rcos((i + 1) << 7) *
                         self->ext.reboundStoneCrashExplosion.unk84) >>
                        0xC) +
                       0x80;
            prim->y2 =
                ((rsin(i << 7) * self->ext.reboundStoneCrashExplosion.unk84) >>
                 0xC);
            prim->y3 = ((rsin((i + 1) << 7) *
                         self->ext.reboundStoneCrashExplosion.unk84) >>
                        0xC);
        }
        prim = prim->next;
    }
}

void RicEntityCrashReboundStone(Entity* entity) {
    switch (entity->step) {
    case 0:
        entity->flags = FLAG_UNK_20000 | FLAG_KEEP_ALIVE_OFFCAMERA;
        entity->step++;
        entity->ext.timer.t = 0x14;
        // fallthrough
    case 1:
        if (--entity->ext.timer.t) {
            break;
        }
    case 3:
    case 5:
        RicCreateEntFactoryFromEntity(entity, BP_57, 0);
        entity->step++;
    case 2:
    case 4:
    case 6:
        entity->ext.timer.t++;
        if (entity->ext.timer.t > 10) {
            entity->ext.timer.t = 0;
            entity->posX.val = FIX(128.0);
            entity->posY.val = 0;
            RicCreateEntFactoryFromEntity(entity, FACTORY(BP_EMBERS, 1), 0);
            entity->step++;
        }
        break;
    case 7:
        entity->ext.timer.t++;
        if (entity->ext.timer.t > 15) {
            DestroyEntity(entity);
            g_Player.unk4E = 1;
            RicCreateEntFactoryFromEntity(
                entity, BP_CRASH_REBOUND_STONE_EXPLOSION, 0);
        }
        break;
    }
}

#define BIBLE_PAGE_COUNT 6
#if defined(VERSION_PSP)
extern Point16 bible_pages_pos[BIBLE_PAGE_COUNT];
#else
static Point16 bible_pages_pos[BIBLE_PAGE_COUNT];
#endif
void RicEntityCrashBibleBeam(Entity* self) {
    Primitive* prim;
    s32 i;
    s32 var_s3;
    s32 psp_s3;
    s32 halfwidth;
    s32 hitboxOffX;
    s16 var_s7;

    switch (self->step) {
    case 0:
        self->primIndex = g_api.AllocPrimitives(PRIM_G4, BIBLE_PAGE_COUNT);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags =
            FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_HAS_PRIMS | FLAG_UNK_20000;
        if (self->facingLeft) {
            self->ext.bibleBeam.unk7C = -16;
            self->ext.bibleBeam.unk7E = -2;
        } else {
            self->ext.bibleBeam.unk7C = 16;
            self->ext.bibleBeam.unk7E = 2;
        }
        prim = &g_PrimBuf[self->primIndex];
        for (i = 0; i < BIBLE_PAGE_COUNT; i++) {
            var_s3 = i + 2;
            if (var_s3 >= BIBLE_PAGE_COUNT) {
                var_s3 -= 6;
            }
            prim->x0 = prim->x1 = bible_pages_pos[i].x;
            prim->y0 = prim->y1 = bible_pages_pos[i].y;
            prim->x2 = prim->x3 = bible_pages_pos[var_s3].x;
            prim->y2 = prim->y3 = bible_pages_pos[var_s3].y;
            prim->priority = 0xC2;
            prim->drawMode = DRAW_UNK_400 | DRAW_TPAGE2 | DRAW_TPAGE |
                             DRAW_COLORS | DRAW_TRANSP;
            prim = prim->next;
        }
        self->step++;
        break;
    case 1:
        self->ext.bibleBeam.unk80++;
        if (self->ext.bibleBeam.unk80 >= 0x3C) {
            self->ext.bibleBeam.subweaponId = PL_W_BIBLE_BEAM;
            RicSetSubweaponParams(self);
            g_api.PlaySfx(SFX_WEAPON_APPEAR);
            g_api.PlaySfx(SFX_TELEPORT_BANG_A);
            self->step++;
        }
        break;
    case 2:
        self->ext.bibleBeam.unk80++;
        self->ext.bibleBeam.unk7E += self->ext.bibleBeam.unk7C;
        var_s3 = bible_pages_pos[1].x + self->ext.bibleBeam.unk7E;
        if (var_s3 < -0x50 || var_s3 > 0x150) {
            self->step++;
        }
        break;
    case 3:
        self->ext.bibleBeam.unk80++;
        if (self->ext.bibleBeam.unk80 >= 0x78) {
            DestroyEntity(self);
            return;
        }
        break;
    }
    prim = &g_PrimBuf[self->primIndex];
    var_s7 = 0; // @bug: this is never unused
    for (i = 0; i < BIBLE_PAGE_COUNT; i++) {
        var_s3 = i + 2;
        if (var_s3 >= BIBLE_PAGE_COUNT) {
            var_s3 -= 6;
        }
        psp_s3 = i * 256;
        prim->r0 = prim->r1 =
            abs((rsin((self->ext.bibleBeam.unk80 * 20) + psp_s3) * 96) >> 0xc);
        prim->g0 = prim->g1 =
            abs((rsin((self->ext.bibleBeam.unk80 * 15) + psp_s3) * 96) >> 0xc);
        prim->b0 = prim->b1 =
            abs((rsin((self->ext.bibleBeam.unk80 * 10) + psp_s3) * 96) >> 0xc);
        psp_s3 = var_s3 * 256;
        prim->r2 = prim->r3 =
            abs((rsin((self->ext.bibleBeam.unk80 * 15) + psp_s3) * 96) >> 0xc);
        prim->g2 = prim->g3 =
            abs((rsin((self->ext.bibleBeam.unk80 * 10) + psp_s3) * 96) >> 0xc);
        prim->b2 = prim->b3 =
            abs((rsin((self->ext.bibleBeam.unk80 * 20) + psp_s3) * 96) >> 0xc);
        prim->x1 = bible_pages_pos[i].x;
        prim->y0 = prim->y1 = bible_pages_pos[i].y;
        prim->x3 = bible_pages_pos[var_s3].x;
        prim->y2 = prim->y3 = bible_pages_pos[var_s3].y;
        prim->x0 = bible_pages_pos[i].x + self->ext.bibleBeam.unk7E;
        prim->x2 = bible_pages_pos[var_s3].x + self->ext.bibleBeam.unk7E;
        if (var_s7 < abs(bible_pages_pos[i].y)) {
            var_s7 = abs(bible_pages_pos[i].y);
        }
        prim = prim->next;
    }
    self->hitboxOffX = self->facingLeft ? -(self->ext.bibleBeam.unk7E / 2)
                                        : (self->ext.bibleBeam.unk7E / 2);
    self->hitboxWidth = abs(self->hitboxOffX);
    self->hitboxHeight = var_s7 - self->posY.i.hi;
}

static s16 bible_page_angles[BIBLE_PAGE_COUNT] = {
    0x0400, 0x06AB, 0x0955, 0x0C00, 0x0EAB, 0x1155,
};
#if defined(VERSION_PSP)
extern s32 bible_pages_volume;
#else
static s32 bible_pages_volume;
#endif
void RicEntityCrashBible(Entity* self) {
    Primitive* prim;
    s32 i;
    s32 psp_s2;
    s16 psp_s4;
    s16 psp_s3;
    s32 psp_s6;
    s32 psp_s5;
    s32 sp3C;
    s32 sp48;
    s32 sp40;
    long sp44;
    long sp4C;
    s32 psp_s8;
    s32 psp_s7;

    switch (self->step) {
    case 0:
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 1 + BIBLE_PAGE_COUNT);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            g_Player.unk4E = 1;
            return;
        }
        self->flags =
            FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_HAS_PRIMS | FLAG_UNK_20000;
        self->posX.val = PLAYER.posX.val;
        self->posY.val = PLAYER.posY.val;
        self->velocityY = FIX(-4);
        if (self->facingLeft) {
            self->velocityX = FIX(12);
            self->ext.et_8016E9E4.unk88 = FIX(1.5);
            self->ext.et_8016E9E4.unk7E = -0x200;
        } else {
            self->velocityX = FIX(-12);
            self->ext.et_8016E9E4.unk88 = FIX(-1.5);
            self->ext.et_8016E9E4.unk7E = 0x200;
        }
        prim = &g_PrimBuf[self->primIndex];
        prim->tpage = 0x1E;
        prim->clut = 0x17F;
        prim->u0 = prim->u2 = 0x98;
        prim->v0 = prim->v1 = 0xD8;
        prim->u1 = prim->u3 = 0xA8;
        prim->v2 = prim->v3 = 0xF0;
        prim->priority = 0xC2;
        prim->drawMode = DRAW_HIDE;
        prim = prim->next;
        for (i = 0; i < BIBLE_PAGE_COUNT; i++) {
            prim->tpage = 0x1C;
            prim->clut = PAL_UNK_1AE;
            prim->u0 = prim->u2 = 0x20;
            prim->u1 = prim->u3 = 0x30;
            prim->v0 = prim->v1 = 0;
            prim->v2 = prim->v3 = 0x10;
            prim->priority = 0xC1;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
        self->ext.et_8016E9E4.unk84 = 0x40;
        bible_pages_volume = 0x60;
        self->step++;
        break;
    case 1:
        prim = &g_PrimBuf[self->primIndex];
        prim->drawMode &= ~DRAW_HIDE;
        self->step++;
    case 2:
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        self->velocityX -= self->ext.et_8016E9E4.unk88;
        self->velocityY -= FIX(0.5);
        self->ext.et_8016E9E4.unk82++;
        if (self->ext.et_8016E9E4.unk82 >= 8) {
            self->ext.et_8016E9E4.unk82 = 0;
            self->step++;
        }
        break;
    case 3:
        self->ext.et_8016E9E4.unk82++;
        if (self->ext.et_8016E9E4.unk82 > 5) {
            prim = &g_PrimBuf[self->primIndex];
            prim->clut = PAL_UNK_19F;
            prim->drawMode |=
                DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
            prim = prim->next;
            for (i = 0; i < BIBLE_PAGE_COUNT; i++) {
                prim->drawMode &= ~DRAW_HIDE;
                prim = prim->next;
            }
            self->ext.et_8016E9E4.unk82 = 0;
            self->step++;
        }
        break;
    case 4:
        self->ext.et_8016E9E4.unk84 -= 4;
        if (self->ext.et_8016E9E4.unk84 <= 0) {
            self->step++;
        }
        break;
    case 5:
        prim = &g_PrimBuf[self->primIndex];
        prim->drawMode |= DRAW_HIDE;
        self->step++;
    case 6:
        self->ext.et_8016E9E4.unk7C += 0x80;
        self->ext.et_8016E9E4.unk7C &= 0xFFF;
        self->ext.et_8016E9E4.unk80 += 4;
        if (self->ext.et_8016E9E4.unk80 >= 0x30) {
            self->step++;
        }
        break;
    case 7:
        self->ext.et_8016E9E4.unk7C += 0x80;
        self->ext.et_8016E9E4.unk7C &= 0xFFF;
        self->ext.et_8016E9E4.unk82++;
        if (self->ext.et_8016E9E4.unk82 >= 0x1E) {
            // create bible page beam
            RicCreateEntFactoryFromEntity(self, BP_CRASH_BIBLE_BEAM, 0);
            self->ext.et_8016E9E4.unk82 = 0;
            self->step++;
        }
        break;
    case 8:
        self->ext.et_8016E9E4.unk7C += 0x80;
        self->ext.et_8016E9E4.unk7C &= 0xFFF;
        self->ext.et_8016E9E4.unk82++;
        if (self->ext.et_8016E9E4.unk82 >= 0x60) {
            g_Player.unk4E = 1;
            self->step++;
        }
        break;
    case 9:
        self->ext.et_8016E9E4.unk7C += 0x80;
        self->ext.et_8016E9E4.unk7C &= 0xFFF;
        self->ext.et_8016E9E4.unk80 -= 2;
        if (self->ext.et_8016E9E4.unk80 <= 0) {
            DestroyEntity(self);
            return;
        }
        break;
    }
    // FAKE, needed for reg match
    if (self->ext.et_8016E9E4.unk7C == 0x100 ||
        self->ext.et_8016E9E4.unk7C == 0x500 ||
        self->ext.et_8016E9E4.unk7C == 0x900 ||
        self->ext.et_8016E9E4.unk7C == 0xD00) {
        if (self->step < 9) {
            g_api.PlaySfxVolPan(SFX_ARROW_SHOT_A, bible_pages_volume, 0);
            if (self->step >= 5) {
                bible_pages_volume -= 4;
            }
            if (bible_pages_volume < 0) {
                bible_pages_volume = 0;
            }
        }
    }

    prim = &g_PrimBuf[self->primIndex];
    psp_s4 = self->posX.i.hi;
    psp_s3 = self->posY.i.hi;
    prim->x0 = prim->x2 = psp_s4 - 8;
    prim->x1 = prim->x3 = psp_s4 + 8;
    prim->y0 = prim->y1 = psp_s3 - 12;
    prim->y2 = prim->y3 = psp_s3 + 12;
    prim->r0 = prim->g0 = prim->b0 = prim->r1 = prim->g1 = prim->b1 = prim->r2 =
        prim->g2 = prim->b2 = prim->r3 = prim->g3 = prim->b3 =
            self->ext.et_8016E9E4.unk84;
    prim = prim->next;

    sp44 = rsin(self->ext.et_8016E9E4.unk7E);
    sp4C = rcos(self->ext.et_8016E9E4.unk7E);
    for (i = 0; i < BIBLE_PAGE_COUNT; i++) {
        sp3C = 0;
        sp48 = (rsin(self->ext.et_8016E9E4.unk7C + bible_page_angles[i]) *
                self->ext.et_8016E9E4.unk80) >>
               0xC;
        sp40 = (rcos(self->ext.et_8016E9E4.unk7C + bible_page_angles[i]) *
                self->ext.et_8016E9E4.unk80) >>
               0xC;
        psp_s6 = (sp4C * sp3C + sp44 * sp40) >> 0xC;
        psp_s2 = (sp4C * sp40 - sp44 * sp3C) >> 0xC;
        psp_s5 = sp48;
        psp_s2 += 0x200;
        psp_s6 = (psp_s6 << 9) / psp_s2;
        psp_s5 = (psp_s5 << 9) / psp_s2;
        psp_s4 = self->posX.i.hi + psp_s6;
        psp_s3 = self->posY.i.hi + psp_s5;
        bible_pages_pos[i].x = psp_s4;
        bible_pages_pos[i].y = psp_s3;
        psp_s8 = 0x1000 / psp_s2;
        psp_s7 = 0x1000 / psp_s2;
        prim->x0 = prim->x2 = psp_s4 - psp_s8;
        prim->x1 = prim->x3 = psp_s4 + psp_s8;
        prim->y0 = prim->y1 = psp_s3 - psp_s7;
        prim->y2 = prim->y3 = psp_s3 + psp_s7;
        prim = prim->next;
    }
}

void func_8016F198(Entity* self) {
    const int PrimCount = 16;
#if defined(VERSION_PSP)
    const int MaxHeight = 248;
    const int HalfHeight = 128;
#else
    const int MaxHeight = 240;
    const int HalfHeight = 120;
#endif
    Primitive* prim;
    s32 i;
    s32 tpage;
    s32 angleX;
    s32 angleY;
    s16 startMod;
    s16 endMod;
    s16 sx;
    s16 ex;
    s16 sy;
    s16 ey;

    switch (self->step) {
    case 0:
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, PrimCount);
        if (self->primIndex == -1) {
            DestroyEntity(self);
#if !defined(VERSION_PSP)
            g_Player.unk4E = 1;
#endif
            return;
        }
        self->flags = FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_HAS_PRIMS;
        prim = &g_PrimBuf[self->primIndex];
        for (i = 0; i < 16; i++) {
            prim->priority = 0xC2;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
        self->step++;
        break;
    case 1:
        prim = &g_PrimBuf[self->primIndex];
        for (i = 0; i < 16; i++) {
            prim->drawMode &= ~DRAW_HIDE;
            prim = prim->next;
        }
        self->step++;
    case 2:
        self->ext.factory.unk7C++;
        if (self->ext.factory.unk7C >= 0x18) {
            self->step++;
        }
        break;
    case 3:
#if !defined(VERSION_PSP)
        g_Player.unk4E = 1;
#endif
        DestroyEntity(self);
        return;
    }
    if (!self->ext.factory.unk7C) {
        return;
    }
    if (
#if !defined(VERSION_PSP)
        g_CurrentBuffer == g_GpuBuffers
#else
        0
#endif
    ) {
        tpage = 0x104;
    } else {
        tpage = 0x100;
    }
    prim = &g_PrimBuf[self->primIndex];
    for (i = 0; i < PrimCount; i++) {
        angleX = rsin(i << 8);
        angleY = rcos(i << 8);
        startMod = self->ext.factory.unk7C * 8;
        endMod = 0;
        if (self->ext.factory.unk7C >= 4) {
            endMod = (self->ext.factory.unk7C - 4) * 8;
        }
        sx = ((angleY * startMod) >> 0xC) + 0x80;
        ex = ((angleY * endMod) >> 0xC) + 0x80;
        sy = ((angleX * startMod) >> 0xC) + HalfHeight;
        ey = ((angleX * endMod) >> 0xC) + HalfHeight;
        prim->x0 = sx = CLAMP(sx, 0, 0xFF);
        prim->x2 = ex = CLAMP(ex, 0, 0xFF);
        prim->y0 = sy = CLAMP(sy, 0, MaxHeight);
        prim->y2 = ey = CLAMP(ey, 0, MaxHeight);
        prim->u0 = 0xFF - prim->x0;
        prim->u2 = 0xFF - prim->x2;
        prim->v0 = MaxHeight - prim->y0;
        prim->v2 = MaxHeight - prim->y2;

        angleX = rsin((i + 1) << 8);
        angleY = rcos((i + 1) << 8);
        sx = ((angleY * startMod) >> 0xC) + 0x80;
        ex = ((angleY * endMod) >> 0xC) + 0x80;
        sy = ((angleX * startMod) >> 0xC) + HalfHeight;
        ey = ((angleX * endMod) >> 0xC) + HalfHeight;
        prim->x1 = sx = CLAMP(sx, 0, 0xFF);
        prim->x3 = ex = CLAMP(ex, 0, 0xFF);
        prim->y1 = sy = CLAMP(sy, 0, MaxHeight);
        prim->y3 = ey = CLAMP(ey, 0, MaxHeight);
        prim->u1 = 0xFF - prim->x1;
        prim->u3 = 0xFF - prim->x3;
        prim->v1 = MaxHeight - prim->y1;
        prim->v3 = MaxHeight - prim->y3;
#if defined(VERSION_PSP)
        prim->u0 = prim->u0 = CLAMP(prim->u0, 1, 0xFE);
        prim->u2 = prim->u2 = CLAMP(prim->u2, 1, 0xFE);
        prim->u1 = prim->u1 = CLAMP(prim->u1, 1, 0xFE);
        prim->u3 = prim->u3 = CLAMP(prim->u3, 1, 0xFE);
#endif

        prim->tpage = tpage;
        prim = prim->next;
    }
}

// Entity ID #64, created by blueprint #72. This call is in
// RicEntitySubwpnStopwatch. When Richter has the ricStopWatch weapon, and uses
// it as a crash, it makes 4 floating ricStopWatches. When they are done they
// disappear in a spinning sparkle. This entity represents that sparkle. 4
// copies of this entity are made when the crash is done.
void RicEntityCrashStopwatchDoneSparkle(Entity* self) {
    s32 sp4C;
    s32 selfX;
    s32 selfY;
    s32 psp_s8;
    s32 psp_s7;
    s32 psp_s6;
    s32 psp_s5;
    s32 psp_s4;
    s32 i;
    s32 psp_s1;
    s32 psp_s2;
    Primitive* prim;

    switch (self->step) {
    case 0:
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 20);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags =
            FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_POS_CAMERA_LOCKED | FLAG_HAS_PRIMS;
        prim = &g_PrimBuf[self->primIndex];
        prim->priority = 0xC2;
        prim->drawMode =
            DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_UNK02 | DRAW_TRANSP;
        prim->tpage = 0x1A;
        prim->clut = PAL_UNK_19F;
        prim->u0 = prim->u2 = 0;
        prim->u1 = prim->u3 = 0x3F;
        prim->v0 = prim->v1 = 0xC0;
        prim->v2 = prim->v3 = 0xFF;
        // @bug: prim->g0 is not set, instead g2 is set twice
        prim->r0 = prim->r1 = prim->r2 = prim->r3 = prim->g1 = prim->g2 =
            prim->g2 = prim->g3 = 0x40;
        prim->b0 = prim->b1 = prim->b2 = prim->b3 = 0x80;

        prim = prim->next;
        prim->priority = 0xC2;
        prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_HIDE | DRAW_COLORS |
                         DRAW_UNK02 | DRAW_TRANSP;
        prim->tpage = 0x1A;
        prim->clut = PAL_UNK_19F;
        prim->u0 = prim->u2 = 0x40;
        prim->u1 = prim->u3 = 0x7F;
        prim->v0 = prim->v1 = 0xC0;
        prim->v2 = prim->v3 = 0xFF;
        prim->r0 = prim->r1 = prim->r2 = prim->r3 = prim->g1 = prim->g2 =
            prim->g2 = prim->g3 = 0x40;
        prim->b0 = prim->b1 = prim->b2 = prim->b3 = 0x80;

        prim = prim->next;
        prim->priority = 0xC2;
        prim->drawMode = DRAW_UNK_400 | DRAW_UNK_40 | DRAW_TPAGE2 | DRAW_TPAGE |
                         DRAW_HIDE | DRAW_COLORS | DRAW_UNK02 | DRAW_TRANSP;
        prim->tpage = 0x1A;
        prim->clut = PAL_UNK_19F;
        prim->u0 = prim->u2 = 0xB;
        prim->u1 = prim->u3 = 0x35;
        prim->v0 = prim->v1 = 0xCB;
        prim->v2 = prim->v3 = 0xF5;
        prim->r0 = prim->r1 = prim->r2 = prim->r3 = prim->g1 = prim->g2 =
            prim->g2 = prim->g3 = 0xCF;
        prim->b0 = prim->b1 = prim->b2 = prim->b3 = 0xFF;

        prim = prim->next;
        prim->priority = 0xC2;
        prim->drawMode = DRAW_UNK_400 | DRAW_UNK_40 | DRAW_TPAGE2 | DRAW_TPAGE |
                         DRAW_HIDE | DRAW_COLORS | DRAW_UNK02 | DRAW_TRANSP;
        prim->tpage = 0x1A;
        prim->clut = PAL_UNK_19F;
        prim->u0 = prim->u2 = 0xB;
        prim->u1 = prim->u3 = 0x35;
        prim->v0 = prim->v1 = 0xCB;
        prim->v2 = prim->v3 = 0xF5;
        prim->r0 = prim->r1 = prim->r2 = prim->r3 = prim->g1 = prim->g2 =
            prim->g2 = prim->g3 = 0xCF;
        prim->b0 = prim->b1 = prim->b2 = prim->b3 = 0xFF;

        self->ext.et_stopWatchSparkle.unk88 = prim->next;
        for (i = 0; i < 16; i++) {
            prim = prim->next;
            prim->priority = PLAYER.zPriority + 3;
            prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_HIDE |
                             DRAW_COLORS | DRAW_UNK02 | DRAW_TRANSP;
            prim->tpage = 0x1A;
            prim->clut = PAL_UNK_194;
            prim->u0 = prim->u2 = (rand() % 5 * 0x10) + 0x90;
            prim->u1 = prim->u3 = prim->u0 + 0x10;
            prim->v0 = prim->v1 = 0xC0;
            prim->v2 = prim->v3 = 0xD0;
            prim->r0 = prim->r1 = prim->r2 = prim->r3 = prim->g1 = prim->g2 =
                prim->g2 = prim->g3 = prim->b0 = prim->b1 = prim->b2 =
                    prim->b3 = 0x80;
        }
        self->ext.et_stopWatchSparkle.unk7C = 4;
        self->ext.et_stopWatchSparkle.unk7E =
            self->ext.et_stopWatchSparkle.unk80 =
                self->ext.et_stopWatchSparkle.unk82 = 0;
        self->ext.et_stopWatchSparkle.unk8C =
            self->ext.et_stopWatchSparkle.unk8E = 0;
        self->step++;
        break;
    case 1:
        self->ext.et_stopWatchSparkle.unk7C++;
        if (self->ext.et_stopWatchSparkle.unk7C >= 0x10) {
            self->ext.et_stopWatchSparkle.unk7E = 4;
            prim = &g_PrimBuf[self->primIndex];
            prim = prim->next;
            prim->drawMode &= ~DRAW_HIDE;
            prim = prim->next;
            prim->drawMode &= ~DRAW_HIDE;
            prim = prim->next;
            prim->drawMode &= ~DRAW_HIDE;
            self->ext.et_stopWatchSparkle.unk80 = 0x10;
            self->ext.et_stopWatchSparkle.unk82 = 0;
            g_api.PlaySfx(SFX_ELECTRICITY);
            self->step++;
        }
        break;
    case 2:
        self->ext.et_stopWatchSparkle.unk7C--;
        if (self->ext.et_stopWatchSparkle.unk7C <= 0) {
            prim = &g_PrimBuf[self->primIndex];
            prim->drawMode |= DRAW_HIDE;
            prim = prim->next;
            prim->drawMode |= DRAW_HIDE;
            self->ext.et_stopWatchSparkle.unk84 = 0xFF;
            self->ext.et_stopWatchSparkle.unk8E = 1;
            self->ext.et_stopWatchSparkle.unk86 =
                self->facingLeft ? 0xA00 : 0xE00;
            self->ext.et_stopWatchSparkle.unk94 =
                self->facingLeft ? 0x700 : 0x100;
            self->ext.et_stopWatchSparkle.unk90 = self->posX.i.hi;
            self->ext.et_stopWatchSparkle.unk92 = self->posY.i.hi;
            self->step++;
        }
        self->ext.et_stopWatchSparkle.unk7E += 2;
        self->ext.et_stopWatchSparkle.unk80 += 2;
        self->ext.et_stopWatchSparkle.unk82 += 0x80;
        self->ext.et_stopWatchSparkle.unk82 &= 0xFFF;
        break;
    case 3:
        self->ext.et_stopWatchSparkle.unk84 -= 0x10;
        if (self->ext.et_stopWatchSparkle.unk84 < 0x80) {
            prim = &g_PrimBuf[self->primIndex];
            prim = prim->next;
            prim = prim->next;
            prim->drawMode |= DRAW_HIDE;
            prim = prim->next;
            prim->drawMode |= DRAW_HIDE;
            self->step++;
        }
        self->ext.et_stopWatchSparkle.unk82 += 0x80;
        self->ext.et_stopWatchSparkle.unk82 &= 0xFFF;
        break;
    case 4:
        if (!self->ext.et_stopWatchSparkle.unk8E) {
            DestroyEntity(self);
            return;
        }
        break;
    }
    prim = &g_PrimBuf[self->primIndex];
    switch (self->step) {
    case 1:
        prim->x0 = prim->x2 =
            self->posX.i.hi - self->ext.et_stopWatchSparkle.unk7C;
        prim->x1 = prim->x3 =
            self->posX.i.hi + self->ext.et_stopWatchSparkle.unk7C;
        prim->y0 = prim->y1 =
            self->posY.i.hi - self->ext.et_stopWatchSparkle.unk7C;
        prim->y2 = prim->y3 =
            self->posY.i.hi + self->ext.et_stopWatchSparkle.unk7C;
        break;
    case 2:
        prim->x0 = prim->x2 =
            self->posX.i.hi - self->ext.et_stopWatchSparkle.unk7C;
        prim->x1 = prim->x3 =
            self->posX.i.hi + self->ext.et_stopWatchSparkle.unk7C;
        prim->y0 = prim->y1 =
            self->posY.i.hi - self->ext.et_stopWatchSparkle.unk7C;
        prim->y2 = prim->y3 =
            self->posY.i.hi + self->ext.et_stopWatchSparkle.unk7C;

        prim = prim->next;
        prim->x0 = prim->x2 =
            self->posX.i.hi - self->ext.et_stopWatchSparkle.unk7E;
        prim->x1 = prim->x3 =
            self->posX.i.hi + self->ext.et_stopWatchSparkle.unk7E;
        prim->y0 = prim->y1 =
            self->posY.i.hi - self->ext.et_stopWatchSparkle.unk7E;
        prim->y2 = prim->y3 =
            self->posY.i.hi + self->ext.et_stopWatchSparkle.unk7E;
        psp_s1 = rsin(self->ext.et_stopWatchSparkle.unk82);
        psp_s2 = rcos(self->ext.et_stopWatchSparkle.unk82);
        sp4C = psp_s2 * self->ext.et_stopWatchSparkle.unk80;
        psp_s8 = psp_s1 * self->ext.et_stopWatchSparkle.unk80;
        psp_s7 = psp_s2 * (self->ext.et_stopWatchSparkle.unk80 / 8);
        psp_s6 = psp_s1 * (self->ext.et_stopWatchSparkle.unk80 / 8);

        prim = prim->next;
        prim->x0 = self->posX.i.hi + ((-sp4C - -psp_s8) >> 0xC);
        prim->y0 = self->posY.i.hi + ((-psp_s8 + -sp4C) >> 0xC);
        prim->x1 = self->posX.i.hi + ((psp_s7 - -psp_s6) >> 0xC);
        prim->y1 = self->posY.i.hi + ((psp_s6 + -psp_s7) >> 0xC);
        prim->x2 = self->posX.i.hi + ((-psp_s7 - psp_s6) >> 0xC);
        prim->y2 = self->posY.i.hi + ((-psp_s6 + psp_s7) >> 0xC);
        prim->x3 = self->posX.i.hi + ((sp4C - psp_s8) >> 0xC);
        prim->y3 = self->posY.i.hi + ((psp_s8 + sp4C) >> 0xC);

        prim = prim->next;
        prim->x0 = self->posX.i.hi + ((-psp_s7 - -psp_s6) >> 0xC);
        prim->y0 = self->posY.i.hi + ((-psp_s6 + -psp_s7) >> 0xC);
        prim->x1 = self->posX.i.hi + ((sp4C - -psp_s8) >> 0xC);
        prim->y1 = self->posY.i.hi + ((psp_s8 + -sp4C) >> 0xC);
        prim->x2 = self->posX.i.hi + ((-sp4C - psp_s8) >> 0xC);
        prim->y2 = self->posY.i.hi + ((-psp_s8 + sp4C) >> 0xC);
        prim->x3 = self->posX.i.hi + ((psp_s7 - psp_s6) >> 0xC);
        prim->y3 = self->posY.i.hi + ((psp_s6 + psp_s7) >> 0xC);
        break;
    case 3:
        psp_s1 = rsin(self->ext.et_stopWatchSparkle.unk82);
        psp_s2 = rcos(self->ext.et_stopWatchSparkle.unk82);
        sp4C = psp_s2 * self->ext.et_stopWatchSparkle.unk80;
        psp_s8 = psp_s1 * self->ext.et_stopWatchSparkle.unk80;
        psp_s7 = psp_s2 * (self->ext.et_stopWatchSparkle.unk80 / 8);
        psp_s6 = psp_s1 * (self->ext.et_stopWatchSparkle.unk80 / 8);
        prim = prim->next;
        prim = prim->next;

        prim->x0 = self->posX.i.hi + ((-sp4C - -psp_s8) >> 0xC);
        prim->y0 = self->posY.i.hi + ((-psp_s8 + -sp4C) >> 0xC);
        prim->x1 = self->posX.i.hi + ((psp_s7 - -psp_s6) >> 0xC);
        prim->y1 = self->posY.i.hi + ((psp_s6 + -psp_s7) >> 0xC);
        prim->x2 = self->posX.i.hi + ((-psp_s7 - psp_s6) >> 0xC);
        prim->y2 = self->posY.i.hi + ((-psp_s6 + psp_s7) >> 0xC);
        prim->x3 = self->posX.i.hi + ((sp4C - psp_s8) >> 0xC);
        prim->y3 = self->posY.i.hi + ((psp_s8 + sp4C) >> 0xC);
        prim->r0 = prim->r1 = prim->r2 = prim->r3 = prim->g1 = prim->g2 =
            prim->g2 = prim->g3 = self->ext.et_stopWatchSparkle.unk84 - 0x20;
        prim->b0 = prim->b1 = prim->b2 = prim->b3 =
            self->ext.et_stopWatchSparkle.unk84;

        prim = prim->next;
        prim->x0 = self->posX.i.hi + ((-psp_s7 - -psp_s6) >> 0xC);
        prim->y0 = self->posY.i.hi + ((-psp_s6 + -psp_s7) >> 0xC);
        prim->x1 = self->posX.i.hi + ((sp4C - -psp_s8) >> 0xC);
        prim->y1 = self->posY.i.hi + ((psp_s8 + -sp4C) >> 0xC);
        prim->x2 = self->posX.i.hi + ((-sp4C - psp_s8) >> 0xC);
        prim->y2 = self->posY.i.hi + ((-psp_s8 + sp4C) >> 0xC);
        prim->x3 = self->posX.i.hi + ((psp_s7 - psp_s6) >> 0xC);
        prim->y3 = self->posY.i.hi + ((psp_s6 + psp_s7) >> 0xC);
        prim->g1 = prim->g2 = prim->g2 = prim->g3 =
            self->ext.et_stopWatchSparkle.unk84 - 0x20;
        prim->b0 = prim->b1 = prim->b2 = prim->b3 =
            self->ext.et_stopWatchSparkle.unk84;
        break;
    }
    if (self->ext.et_stopWatchSparkle.unk8E) {
        self->ext.et_stopWatchSparkle.unk8E = 0;
        prim = self->ext.et_stopWatchSparkle.unk88;
        for (i = 0; i < 16; i++) {
            if (i == self->ext.et_stopWatchSparkle.unk8C) {
                if (self->ext.et_stopWatchSparkle.unk90 < 0x120 &&
                    self->ext.et_stopWatchSparkle.unk90 > -0x20 &&
                    self->ext.et_stopWatchSparkle.unk92 < 0x120 &&
                    self->ext.et_stopWatchSparkle.unk92 > -0x20) {
                    prim->drawMode &= ~DRAW_HIDE;
                    prim->r0 = 0x80;
                    if (!(i % 4)) {
                        psp_s5 = rand() % 0x200 + 0x200;
                    } else {
                        psp_s5 = rand() % 0x80 + 0x80;
                    }
                    psp_s4 = self->ext.et_stopWatchSparkle.unk86 -
                             self->ext.et_stopWatchSparkle.unk94;
                    if (abs(psp_s4) > 0x800) {
                        if (psp_s4 < 0) {
                            psp_s4 += 0x1000;
                        } else {
                            psp_s4 -= 0x1000;
                        }
                    }
                    if (psp_s4 > 0) {
                        psp_s5 = -psp_s5;
                    }
                    self->ext.et_stopWatchSparkle.unk86 += psp_s5;
                    self->ext.et_stopWatchSparkle.unk86 &= 0xFFF;
                    psp_s1 = rsin(self->ext.et_stopWatchSparkle.unk86);
                    psp_s2 = rcos(self->ext.et_stopWatchSparkle.unk86);
                    prim->x0 = self->ext.et_stopWatchSparkle.unk90 +
                               (-(psp_s1 * -8) >> 0xC);
                    prim->y0 = self->ext.et_stopWatchSparkle.unk92 +
                               ((psp_s2 * -8) >> 0xC);
                    prim->x1 = self->ext.et_stopWatchSparkle.unk90 +
                               ((psp_s2 * 16 - psp_s1 * -8) >> 0xC);
                    prim->y1 = self->ext.et_stopWatchSparkle.unk92 +
                               ((psp_s1 * 16 + psp_s2 * -8) >> 0xC);
                    prim->x2 = self->ext.et_stopWatchSparkle.unk90 +
                               (-(psp_s1 * 8) >> 0xC);
                    prim->y2 = self->ext.et_stopWatchSparkle.unk92 +
                               (psp_s2 * 8 >> 0xC);
                    prim->x3 = self->ext.et_stopWatchSparkle.unk90 +
                               ((psp_s2 * 16 - psp_s1 * 8) >> 0xC);
                    prim->y3 = self->ext.et_stopWatchSparkle.unk92 +
                               ((psp_s1 * 16 + psp_s2 * 8) >> 0xC);
                    prim->r0 = 0x80;
                    self->ext.et_stopWatchSparkle.unk90 += (psp_s2 * 16) >> 0xC;
                    self->ext.et_stopWatchSparkle.unk92 += (psp_s1 * 16) >> 0xC;
                    selfX = self->posX.i.hi;
                    selfY = self->posY.i.hi;
                    self->posX.i.hi = self->ext.et_stopWatchSparkle.unk90;
                    self->posY.i.hi = self->ext.et_stopWatchSparkle.unk92;
                    RicCreateEntFactoryFromEntity(
                        self, BP_CRASH_STOPWATCH_LIGHTNING, 0);
                    self->posX.i.hi = selfX;
                    self->posY.i.hi = selfY;
                } else {
                    prim->drawMode |= DRAW_HIDE;
                }
            } else {
                prim->r0 -= 8;
                if (prim->r0 < 0x20) {
                    prim->drawMode |= DRAW_HIDE;
                }
            }
            prim->r1 = prim->r2 = prim->r3 = prim->g0 = prim->g1 = prim->g2 =
                prim->g3 = prim->b0 = prim->b1 = prim->b2 = prim->b3 = prim->r0;
            self->ext.et_stopWatchSparkle.unk8E |=
                prim->drawMode & DRAW_HIDE ? 0 : 1;
            prim = prim->next;
        }
        self->ext.et_stopWatchSparkle.unk8C++;
        if (self->ext.et_stopWatchSparkle.unk8C >= 0x10) {
            self->ext.et_stopWatchSparkle.unk8C = 0;
        }
    }
}

// Created by blueprint #73.
// When Stopwatch crash ends, each of the 4 ricStopWatches shoots out a
// lightning Each lightning can harm enemies. This entity represents the
// attacking part of that lightning. It does not do any graphics and just has
// the hitbox. Not clear why this is a dedicated entity rather than having one
// entity that is graphics + hitbox for the lightning.
void RicEntityStopwatchCrashLightning(Entity* self) {
    switch (self->step) {
    case 0:
        self->flags = FLAG_KEEP_ALIVE_OFFCAMERA;
        self->ext.subweapon.subweaponId = PL_W_30;
        RicSetSubweaponParams(self);
        self->hitboxWidth = 8;
        self->hitboxHeight = 8;
        self->step++;
        break;
    case 1:
        self->ext.timer.t++;
        if (self->ext.timer.t > 4) {
            DestroyEntity(self);
        }
        break;
    }
}

void RicEntityCrashStopwatch(Entity* self) {
    // Kind of funny control flow.
    // On odd steps, we'll create a ricStopWatch, and on evens, we wait.
    // We end up producing the 4 individual ricStopWatches.
    switch (self->step) {
    case 0:
        self->flags = FLAG_KEEP_ALIVE_OFFCAMERA;
        self->ext.stopwatchCrash.index = 0;
        self->step++;
    case 1:
    case 3:
    case 5:
    case 7:
        self->ext.stopwatchCrash.index++;
        // This value becomes ext.ricStopWatch.crashIndex for each stopwatch.
        RicCreateEntFactoryFromEntity(
            self, FACTORY(BP_SUBWPN_STOPWATCH, self->ext.stopwatchCrash.index),
            0);
        self->ext.stopwatchCrash.timer = 0;
        self->step++;
        break;
    case 2:
    case 4:
    case 6:
        self->ext.stopwatchCrash.timer++;
        if (self->ext.stopwatchCrash.timer > 15) {
            self->step++;
        }
        break;
    case 8:
        DestroyEntity(self);
#if defined(VERSION_PSP)
        g_Player.unk4E = 1;
#endif
        break;
    }
}

static s16 GetAguneaLightningAngle(s16* arg0, s16 arg1, s16 arg2, s16* arg3) {
    arg1 += rand() % 256 - 0x80;
    *arg3 = (rand() % 48) + 0x10;
    arg0[0] = arg0[1];
    arg0[2] = arg0[3];
    if (arg2) {
        arg0[1] += (rcos(arg1) * *arg3) >> 0xC;
        arg0[3] += (rsin(arg1) * *arg3) >> 0xC;
        if (arg2 % 2) {
            return GetAguneaLightningAngle(arg0, arg1 - 0x140, arg2 / 2, arg3);
        } else {
            rand();
            rand();
            return GetAguneaLightningAngle(
                arg0, arg1 + 0x140, (arg2 - 1) / 2, arg3);
        }
    }
    return arg1;
}

static void AguneaShuffleParams(s32 bufSize, s32* buf) {
    s32 i, idx, swapTemp;

    for (i = bufSize - 1; i > 0; i--) {
        // Pick random index
        idx = rand() % bufSize;

        // Hold swap value temporarily
        swapTemp = buf[i];
        buf[i] = buf[idx];
        buf[idx] = swapTemp;
    }
}

// Agunea item crash lightning, created by RicEntityAguneaCircle, blueprint 68
void RicEntityAguneaLightning(Entity* self) {
    s16 sp20;
    s16 angle;
    s16 sp18;
    s32 randomSeed;
    s16 sp10[4];
    s16 xCoord;
    s16 yCoord;
    s16 psp_s6;
    s16 psp_s5;
    s32 psp_s4;
    s32 psp_s3;
    s32 i;
    Primitive* prim;

    switch (self->step) {
    case 0:
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 0xF);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags =
            FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_HAS_PRIMS | FLAG_POS_PLAYER_LOCKED;
        prim = &g_PrimBuf[self->primIndex];
        for (i = 0; i < 15; i++) {
            prim->tpage = 0x1A;
            prim->clut = PAL_UNK_194;
            xCoord = (rand() % 5) * 0x10;
            prim->u0 = prim->u2 = xCoord + 0x90;
            prim->u1 = prim->u3 = xCoord + 0xB0;
            if (rand() % 2) {
                prim->v0 = prim->v1 = 0xD0;
                prim->v2 = prim->v3 = 0xE0;
            } else {
                prim->v0 = prim->v1 = 0xE0;
                prim->v2 = prim->v3 = 0xD0;
            }
            prim->r0 = prim->g0 = prim->b0 = prim->r1 = prim->g1 = prim->b1 =
                prim->r2 = prim->g2 = prim->b2 = prim->r3 = prim->g3 =
                    prim->b3 = 0x80;
            prim->priority = 0xC1;
            prim->drawMode = DRAW_UNK_200 | DRAW_HIDE | DRAW_COLORS;
            prim = prim->next;
        }
        prim = &g_PrimBuf[self->primIndex];
        sp20 = ((self->params & 0xFF00) >> 8) * 0x200;
        sp20 += rand() % 0x200 - 0x100;
        randomSeed = rand() & PSP_RANDMASK;
        for (i = 0; i < 15; i++) {
            srand(randomSeed);
            sp10[1] = self->posX.i.hi;
            sp10[3] = self->posY.i.hi;
            angle = GetAguneaLightningAngle(sp10, sp20, i, &sp18);
            xCoord = sp10[0];
            yCoord = sp10[2];
            psp_s6 = !i ? 2 : 8;
            psp_s5 = (i < 7) ? 8 : 2;

            psp_s4 = rcos(angle);
            psp_s3 = rsin(angle);
            prim->x0 = xCoord + (-(psp_s3 * -psp_s6) >> 0xC);
            prim->y0 = yCoord + ((psp_s4 * -psp_s6) >> 0xC);
            prim->x1 = xCoord + ((psp_s4 * sp18 - (psp_s3 * -psp_s5)) >> 0xC);
            prim->y1 = yCoord + ((psp_s3 * sp18 + (psp_s4 * -psp_s5)) >> 0xC);
            prim->x2 = xCoord + (-(psp_s3 * psp_s6) >> 0xC);
            prim->y2 = yCoord + ((psp_s4 * psp_s6) >> 0xC);
            prim->x3 = xCoord + ((psp_s4 * sp18 - (psp_s3 * psp_s5)) >> 0xC);
            prim->y3 = yCoord + ((psp_s3 * sp18 + (psp_s4 * psp_s5)) >> 0xC);
            prim = prim->next;
        }
        self->ext.et_8017091C.unk7E = 1;
        self->step++;
        break;
    case 1:
        prim = &g_PrimBuf[self->primIndex];
        for (i = 0; i < 15; i++) {
            prim->drawMode &= ~DRAW_HIDE;
            prim = prim->next;
        }
        self->step++;
    case 2:
        self->ext.et_8017091C.unk7C++;
        if (self->ext.et_8017091C.unk7C > 4) {
            prim = &g_PrimBuf[self->primIndex];
            for (i = 0; i < 15; i++) {
                prim->v0 = prim->v1 = prim->v0 - 0x10;
                prim->v2 = prim->v3 = prim->v2 - 0x10;
                prim->clut = PAL_FILL_WHITE;
                prim->r0 = prim->g0 = prim->b0 = prim->r1 = prim->g1 =
                    prim->b1 = prim->r2 = prim->g2 = prim->b2 = prim->r3 =
                        prim->g3 = prim->b3 = 0xFF;
                prim = prim->next;
            }
            self->ext.et_8017091C.unk7C = 0;
            self->step++;
        }
        break;
    case 3:
    case 5:
        prim = &g_PrimBuf[self->primIndex];
        for (i = 0; i < 15; i++) {
            prim->clut = PAL_UNK_194;
            prim = prim->next;
        }
        self->step++;
        break;
    case 4:
        prim = &g_PrimBuf[self->primIndex];
        for (i = 0; i < 15; i++) {
            prim->clut = PAL_FILL_WHITE;
            prim = prim->next;
        }
        self->step++;
        break;
    case 6:
        prim = &g_PrimBuf[self->primIndex];
        for (i = 0; i < 15; i++) {
            prim->r0 = prim->g0 = prim->b0 = prim->r1 = prim->g1 = prim->b1 =
                prim->r2 = prim->g2 = prim->b2 = prim->r3 = prim->g3 =
                    prim->b3 = 0x60 - (self->ext.et_8017091C.unk7C * 4);
            prim = prim->next;
        }
        self->ext.et_8017091C.unk7C++;
        if (self->ext.et_8017091C.unk7C > 15) {
            DestroyEntity(self);
            return;
        }
        break;
    }
}

#define LIGHTNING_COUNT 8
#if defined(VERSION_PSP)
extern s32 g_AguneaParams[LIGHTNING_COUNT];
#else
static s32 g_AguneaParams[LIGHTNING_COUNT];
#endif
void RicEntityAguneaCircle(Entity* self) {
    Primitive* prim;
    s16 rand_angle;
    s16 xCoord;
    s16 yCoord;
    s32 quarterSelfY;
    s32 i;
    s16 psp_s4;

    switch (self->step) {
    case 0:
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 4);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            g_Player.unk4E = 1;
            return;
        }
        self->flags =
            FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_HAS_PRIMS | FLAG_POS_PLAYER_LOCKED;
        self->posX.i.hi = PLAYER.posX.i.hi;
        self->posY.i.hi = PLAYER.posY.i.hi - 0x20;
        prim = &g_PrimBuf[self->primIndex];
        quarterSelfY = self->posY.i.hi / 4;
        xCoord = self->posX.i.hi;
        yCoord = 0;
        for (i = 0; i < 4; i++) {
            prim->tpage = 0x1A;
            prim->clut = PAL_UNK_194;
            prim->x0 = xCoord - 8;
            prim->x2 = xCoord + 8;
            prim->y0 = prim->y2 = yCoord;
            if (i < 3) {
                rand_angle = rand() % 0x100 + 0x380;
                xCoord += ((rcos(rand_angle) * quarterSelfY) >> 0xC);
                yCoord += ((rsin(rand_angle) * quarterSelfY) >> 0xC);
                prim->x1 = xCoord - 8;
                prim->x3 = xCoord + 8;
            } else {
                xCoord = self->posX.i.hi;
                yCoord = self->posY.i.hi;
                prim->x1 = xCoord - 4;
                prim->x3 = xCoord + 4;
            }
            prim->y1 = prim->y3 = yCoord;
            psp_s4 = (rand() % 6) * 0x10;
            prim->u0 = prim->u2 = psp_s4 + 0x90;
            prim->u1 = prim->u3 = psp_s4 + 0xA0;
            if (rand() % 2) {
                prim->v0 = prim->v1 = 0xD0;
                prim->v2 = prim->v3 = 0xE0;
            } else {
                prim->v0 = prim->v1 = 0xE0;
                prim->v2 = prim->v3 = 0xD0;
            }
            prim->priority = 0xC2;
            prim->drawMode = DRAW_UNK_200 | DRAW_HIDE;
            prim = prim->next;
        }
        self->ext.aguneaCrash.subweaponId = PL_W_CRASH_AGUNEA;
        RicSetSubweaponParams(self);
        self->step++;
        break;
    case 1:
        prim = &g_PrimBuf[self->primIndex];
        for (i = 0; i < self->ext.aguneaCrash.unk7C; i++) {
            prim = prim->next;
        }
        prim->drawMode &= ~DRAW_HIDE;
        self->ext.aguneaCrash.unk7C++;
        if (self->ext.aguneaCrash.unk7C >= 4) {
            self->ext.aguneaCrash.unk7C = 0;
            self->step++;
        }
        break;
    case 2:
        prim = &g_PrimBuf[self->primIndex];
        for (i = 0; i < self->ext.aguneaCrash.unk7C; i++) {
            prim = prim->next;
        }
        if (!self->ext.aguneaCrash.unk7C) {
            prim->drawMode = DRAW_UNK_200 | DRAW_TPAGE2 | DRAW_TPAGE |
                             DRAW_COLORS | DRAW_TRANSP;
            prim->tpage = 0x1A;
            prim->clut = PAL_UNK_19F;
            prim->u0 = prim->u2 = 0;
            prim->u1 = prim->u3 = 0x3F;
            prim->v0 = prim->v1 = 0xC0;
            prim->v2 = prim->v3 = 0xFF;
            prim->r0 = prim->g0 = prim->r1 = prim->g1 = prim->r2 = prim->g2 =
                prim->r3 = prim->g3 = 0x7F;
            prim->b0 = prim->b1 = prim->b2 = prim->b3 = 0xFF;
            self->ext.aguneaCrash.unk7E = 1;
            self->ext.aguneaCrash.unk80 = 2;
            self->ext.aguneaCrash.unk82 = 0x64;
        } else {
            self->ext.aguneaCrash.unk80 += 2;
            prim->drawMode |= DRAW_HIDE;
        }
        self->ext.aguneaCrash.unk7C++;
        if (self->ext.aguneaCrash.unk7C > 3) {
            // think this loop has to count down since we assign to i
            for (i = 0; i < LIGHTNING_COUNT; i++) {
                g_AguneaParams[i] = i;
            }
            AguneaShuffleParams(LIGHTNING_COUNT, &g_AguneaParams[0]);
            self->ext.aguneaCrash.unk7C = 0;
            g_api.PlaySfx(SFX_THUNDER_B);
            self->step++;
        }
        break;
    case 3:
        RicCreateEntFactoryFromEntity(
            self,
            FACTORY(BP_CRASH_AGUNEA_THUNDER,
                    g_AguneaParams[self->ext.aguneaCrash.unk7C]),
            0);
        self->ext.aguneaCrash.unk7C++;
        if (self->ext.aguneaCrash.unk7C > LIGHTNING_COUNT - 1) {
            self->hitboxWidth = 0x80;
            self->hitboxHeight = 0x80;
            self->ext.aguneaCrash.unk7C = 0;
            self->step++;
        }
        break;
    case 4:
        self->ext.aguneaCrash.unk7C++;
        if (self->ext.aguneaCrash.unk7C > LIGHTNING_COUNT) {
            self->step++;
        }
        break;
    case 5:
        self->ext.aguneaCrash.unk80 += 2;
        self->ext.aguneaCrash.unk82 -= 10;
        if (self->ext.aguneaCrash.unk82 <= 0) {
            self->hitboxWidth = 0;
            self->hitboxHeight = 0;
            self->step++;
        }
        break;
    case 6:
        g_Player.unk4E = 1;
        DestroyEntity(self);
        return;
    }
    if (self->ext.aguneaCrash.unk7E) {
        prim = &g_PrimBuf[self->primIndex];
        prim->x0 = prim->x2 = self->posX.i.hi - self->ext.aguneaCrash.unk80;
        prim->x1 = prim->x3 = self->posX.i.hi + self->ext.aguneaCrash.unk80;
        prim->y0 = prim->y1 = self->posY.i.hi - self->ext.aguneaCrash.unk80;
        prim->y2 = prim->y3 = self->posY.i.hi + self->ext.aguneaCrash.unk80;
        prim->r0 = prim->g0 = prim->r1 = prim->g1 = prim->r2 = prim->g2 =
            prim->r3 = prim->g3 = (self->ext.aguneaCrash.unk82 * 0x7F) / 100;
        prim->b0 = prim->b1 = prim->b2 = prim->b3 =
            (self->ext.aguneaCrash.unk82 * 0xFF) / 100;
    }
}

void RicEntitySubwpnStopwatchCircle(Entity* self) {
    s16 temp_s0_4;
    s16 psp_s4;
    s32 sine;
    s32 cosine;
    s16 xCoord;
    s16 yCoord;
    Primitive* prim;
    s32 i;

    switch (self->step) {
    case 0:
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 0x10);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_HAS_PRIMS;
        prim = &g_PrimBuf[self->primIndex];
        for (i = 0; i < 16; i++) {
            prim->tpage = 0x1A;
            prim->clut = PAL_FILL_WHITE;
            prim->priority = self->zPriority = 0xC2;
            prim->drawMode = DRAW_UNK_400 | DRAW_TPAGE2 | DRAW_TPAGE |
                             DRAW_COLORS | DRAW_TRANSP;
            psp_s4 = i * 0x100;
            prim->u0 = ((rsin(psp_s4) << 5) >> 0xC) + 0x20;
            prim->v0 = -((rcos(psp_s4) << 5) >> 0xC) + 0xDF;
            psp_s4 = (i + 1) * 0x100;
            prim->u1 = ((rsin(psp_s4) << 5) >> 0xC) + 0x20;
            prim->v1 = -((rcos(psp_s4) << 5) >> 0xC) + 0xDF;
            prim->u2 = prim->u3 = 0x20;
            prim->v2 = prim->v3 = 0xE0;
            prim->r0 = prim->r1 = prim->g0 = prim->g1 = prim->b0 = prim->b1 =
                0x40;
            prim->r2 = prim->r3 = prim->g2 = prim->g3 = 0;
            prim->b2 = prim->b3 = 0x20;
            prim = prim->next;
        }
        self->ext.et_stopwatchCircle.size = 0x20;
        self->step++;
        break;
    case 1:
        self->ext.et_stopwatchCircle.size += 0x18;
        self->ext.et_stopwatchCircle.timer++;
        if (self->ext.et_stopwatchCircle.timer > 0x1E) {
            DestroyEntity(self);
            return;
        }
    }
    xCoord = self->posX.i.hi;
    yCoord = self->posY.i.hi;
    prim = &g_PrimBuf[self->primIndex];
    for (i = 0; i < 16; i++) {
        sine = rsin(i * 0x100);
        cosine = rcos(i * 0x100);
        temp_s0_4 = self->ext.et_stopwatchCircle.size - 0x20;
        prim->x0 = xCoord + ((sine * self->ext.et_stopwatchCircle.size) >> 0xC);
        prim->y0 =
            yCoord - ((cosine * self->ext.et_stopwatchCircle.size) >> 0xC);
        prim->x2 = xCoord + ((sine * (temp_s0_4)) >> 0xC);
        prim->y2 = yCoord - ((cosine * temp_s0_4) >> 0xC);
        sine = rsin((i + 1) * 0x100);
        cosine = rcos((i + 1) * 0x100);
        prim->x1 = xCoord + ((sine * self->ext.et_stopwatchCircle.size) >> 0xC);
        prim->y1 =
            yCoord - ((cosine * self->ext.et_stopwatchCircle.size) >> 0xC);
        prim->x3 = xCoord + ((sine * temp_s0_4) >> 0xC);
        prim->y3 = yCoord - ((cosine * temp_s0_4) >> 0xC);
        prim = prim->next;
    }
}

#if defined(VERSION_PSP)
extern u32 D_801758D0;
extern Entity* D_801758D4[3];
#else
static u32 D_801758D0;
static Entity* D_801758D4[3];
#endif
void RicEntitySubwpnStopwatch(Entity* self) {
    s32 sp4C;
    s32 psp_s6;
    s32 psp_s5;
    s16 psp_s4;
    s16 psp_s3;
    s32 psp_s2;
    s32 psp_s1;
    Primitive* prim;

    if (g_unkGraphicsStruct.pauseEnemies) {
        g_unkGraphicsStruct.D_800973FC = 0;
        if (self->step && self->step < 4) {
            self->step = 4;
        }
    }
    switch (self->step) {
    case 0:
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 3);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA |
                      FLAG_HAS_PRIMS | FLAG_UNK_20000;
        prim = &g_PrimBuf[self->primIndex];
        prim->tpage = 0x1E;
        prim->clut = 0x17F;
        prim->v0 = prim->v1 = 0xC0;
        prim->v2 = prim->v3 = 0xD8;
        if (self->facingLeft) {
            prim->u0 = prim->u2 = 0x98;
            prim->u1 = prim->u3 = 0xA8;
        } else {
            prim->u0 = prim->u2 = 0xA8;
            prim->u1 = prim->u3 = 0x98;
        }
        prim->priority = PLAYER.zPriority + 1;
        prim->drawMode = DRAW_UNK_100 | DRAW_HIDE | DRAW_UNK02;
        prim = prim->next;

        prim->tpage = 0x1A;
        prim->clut = 0x186;
        prim->priority = PLAYER.zPriority + 3;
        prim->drawMode = DRAW_UNK_100 | DRAW_HIDE | DRAW_UNK02;

        prim = prim->next;

        prim->tpage = 0x1A;
        prim->clut = 0x186;
        prim->priority = PLAYER.zPriority + 3;
        prim->drawMode = DRAW_UNK_100 | DRAW_HIDE | DRAW_UNK02;
        // This holds the index of the ricStopWatch, when created by the crash.
        // If it's 0, then we just used a normal stopwatch.
        if (self->params & 0xFF00) {
            sp4C = 0x185;
            RicCreateEntFactoryFromEntity(self, BP_66, 0);
            D_801758D0 = self->ext.ricStopWatch.crashIndex =
                (self->params >> 8) & 0xFF;
            if (self->ext.ricStopWatch.crashIndex < 4) {
                D_801758D4[self->ext.ricStopWatch.crashIndex - 1] = self;
            }
            if (self->ext.ricStopWatch.crashIndex > 1) {
                self->ext.ricStopWatch.unk98 =
                    D_801758D4[self->ext.ricStopWatch.crashIndex - 2];
            }
        } else {
            sp4C = 0x186;
            RicCreateEntFactoryFromEntity(self, BP_STOPWATCH_CIRCLE, 0);
            self->ext.ricStopWatch.crashIndex = 0;
        }
        self->ext.ricStopWatch.subweaponId = PL_W_STOPWATCH;
        RicSetSubweaponParams(self);
        g_api.PlaySfx(SFX_UI_ALERT_TINK);
        if (self->ext.ricStopWatch.crashIndex < 2) {
            g_unkGraphicsStruct.D_800973FC = 1;
        }
        self->step++;
        break;
    case 1:
        prim = &g_PrimBuf[self->primIndex];
        prim->drawMode &= ~DRAW_HIDE;
        self->ext.ricStopWatch.unk84.val += 0x18000;
        if (self->ext.ricStopWatch.unk84.val >= 0x1A0000) {
            self->step++;
        }
        break;
    case 2:
        self->ext.ricStopWatch.unk84.val += 0xFFFF0000;
        if (self->ext.ricStopWatch.unk84.val <= 0x100000) {
            self->ext.ricStopWatch.t = 5;
            g_api.PlaySfx(SFX_STOPWATCH_TICK);
            self->step++;
        }
        break;
    case 3:
        self->ext.ricStopWatch.unk7E++;
        if (self->ext.ricStopWatch.unk7E > 0x50) {
            g_api.PlaySfx(SFX_STOPWATCH_TICK);
            self->ext.ricStopWatch.unk7E = 0;
            self->ext.ricStopWatch.unk90 = 1;
            self->ext.ricStopWatch.t--;
            if (self->ext.ricStopWatch.t < 0) {
                self->step++;
                break;
            }
        }
        if (self->ext.ricStopWatch.t < 5) {
            prim = &g_PrimBuf[self->primIndex];
            prim = prim->next;
            if (self->ext.ricStopWatch.t >= 10) {
                self->ext.ricStopWatch.unk92 = 1;
                psp_s1 = 8 * (self->ext.ricStopWatch.t / 10);
                prim->u0 = prim->u2 = psp_s1 + 0x18;
                prim->v0 = prim->v1 = 0x40;
                prim->u1 = prim->u3 = psp_s1 + 0x1E;
                prim->v2 = prim->v3 = 0x49;
                prim->drawMode &= ~DRAW_HIDE;
                prim = prim->next;
            } else {
                self->ext.ricStopWatch.unk92 = 0;
            }
            psp_s1 = 8 * (self->ext.ricStopWatch.t % 10);
            if (psp_s1 == 0) {
                psp_s1 = 0x50;
            }
            prim->u0 = prim->u2 = psp_s1 + 0x18;
            prim->v0 = prim->v1 = 0x40;
            prim->u1 = prim->u3 = psp_s1 + 0x1E;
            prim->v2 = prim->v3 = 0x49;
            prim->drawMode &= ~DRAW_HIDE;
        }
        break;
    case 4:
        self->flags &= ~FLAG_POS_PLAYER_LOCKED;
        prim = &g_PrimBuf[self->primIndex];
        prim->priority = 0xC2;
        prim->drawMode &= ~DRAW_UNK_200;
        prim = prim->next;
        prim->drawMode |= DRAW_HIDE;
        prim = prim->next;
        prim->drawMode |= DRAW_HIDE;
        self->posX.i.hi += self->facingLeft ? 6 : -6;
        self->posY.i.hi -= self->ext.ricStopWatch.unk84.val >> 0x10;
        self->ext.ricStopWatch.t = 0;
        if (self->ext.ricStopWatch.crashIndex) {
            self->step = 7;
            RicCreateEntFactoryFromEntity(self, BP_AGUNEA_THUNDER, 0);
        } else {
            self->step++;
        }
        break;
    case 5:
        self->ext.ricStopWatch.t++;
        if (self->ext.ricStopWatch.t >= 4) {
            prim = &g_PrimBuf[self->primIndex];
            prim->clut = PAL_FILL_WHITE;
            prim->drawMode |= DRAW_COLORS;
            prim->r0 = prim->r1 = prim->r2 = prim->r3 = 0x40;
            prim->g0 = prim->g1 = prim->g2 = prim->g3 = 0x40;
            prim->b0 = prim->b1 = prim->b2 = prim->b3 = 0x60;
            g_api.PlaySfx(SFX_UI_SUBWEAPON_TINK);
            self->step++;
        }
        break;
    case 6:
        self->ext.ricStopWatch.t++;
        if (self->ext.ricStopWatch.t > 14) {
            RicCreateEntFactoryFromEntity(self, FACTORY(BP_EMBERS, 7), 0);
            self->step++;
        }
        break;
    case 7:
        if (self->ext.ricStopWatch.crashIndex == 0 ||
            self->ext.ricStopWatch.crashIndex == D_801758D0) {
            g_unkGraphicsStruct.D_800973FC = 0;
        }
        if (self->ext.ricStopWatch.crashIndex) {
            D_801758D4[self->ext.ricStopWatch.crashIndex - 1] = 0;
        }
        DestroyEntity(self);
        return;
    }
    if (!self->step) {
        return;
    }
    prim = &g_PrimBuf[self->primIndex];
    if (self->step < 5) {
        if (self->ext.ricStopWatch.crashIndex < 2) {
            psp_s1 = PLAYER.posX.val + (PLAYER.facingLeft ? FIX(8) : FIX(-8));
            psp_s2 = PLAYER.posY.val + FIX(-16);
        } else if (D_801758D4[self->ext.ricStopWatch.crashIndex - 2] != NULL) {
            if (
#if defined(VERSION_PSP)
                self->ext.ricStopWatch.unk98
#else
                1
#endif
            ) {
                psp_s1 = self->ext.ricStopWatch.unk98->posX.val +
                         (PLAYER.facingLeft ? FIX(16) : FIX(-16));
                psp_s2 = self->ext.ricStopWatch.unk98->posY.val + FIX(-16);
            } else {
                psp_s1 = self->posX.val;
                psp_s2 = self->posY.val;
            }
        } else {
            psp_s1 = self->posX.val;
            psp_s2 = self->posY.val;
        }
        self->posX.val += (psp_s1 - self->posX.val) / 12;
        self->posY.val += (psp_s2 - self->posY.val) / 4;
        if (self->ext.ricStopWatch.crashIndex < 2) {
            if (PLAYER.facingLeft != self->facingLeft) {
                if (abs(psp_s1 - self->posX.val) < FIX(1)) {
                    self->facingLeft = PLAYER.facingLeft;
                } else if (!self->facingLeft && psp_s1 < self->posX.val) {
                    self->facingLeft = PLAYER.facingLeft;
                } else if (self->facingLeft && self->posX.val < psp_s1) {
                    self->facingLeft = PLAYER.facingLeft;
                }
            }
        } else if (D_801758D4[self->ext.ricStopWatch.crashIndex - 2] != NULL) {
            if (
#if defined(VERSION_PSP)
                self->ext.ricStopWatch.unk98 &&
#endif
                self->ext.ricStopWatch.unk98->facingLeft != self->facingLeft) {
                if (abs(psp_s1 - self->posX.val) < FIX(1)) {
                    self->facingLeft = self->ext.ricStopWatch.unk98->facingLeft;
                } else if (!self->facingLeft && psp_s1 < self->posX.val) {
                    self->facingLeft = self->ext.ricStopWatch.unk98->facingLeft;
                } else if (self->facingLeft && self->posX.val < psp_s1) {
                    self->facingLeft = self->ext.ricStopWatch.unk98->facingLeft;
                }
            }
        }
        if (self->facingLeft) {
            prim->u0 = prim->u2 = 0x98;
            prim->u1 = prim->u3 = 0xA8;
        } else {
        block_84:
            prim->u0 = prim->u2 = 0xA8;
            prim->u1 = prim->u3 = 0x98;
        }
    }
    if (self->step < 3) {
        psp_s1 = self->posX.i.hi + (self->facingLeft ? 6 : -6);
        psp_s2 = self->posY.i.hi - (self->ext.ricStopWatch.unk84.val >> 0x10);
        if (self->ext.ricStopWatch.unk82 < 0x64) {
            self->ext.ricStopWatch.unk82 += 4;
        }
        if (self->ext.ricStopWatch.unk80 < 0x1000) {
            self->ext.ricStopWatch.unk80 += 0x80;
        }
        psp_s4 = (self->ext.ricStopWatch.unk82 * 8) / 100;
        psp_s3 = (self->ext.ricStopWatch.unk82 * 12) / 100;
        psp_s6 = rsin(self->ext.ricStopWatch.unk80);
        psp_s5 = rcos(self->ext.ricStopWatch.unk80);
        prim->x0 = psp_s1 + ((psp_s5 * -psp_s4 - psp_s6 * -psp_s3) >> 0xC);
        prim->y0 = psp_s2 + ((psp_s6 * -psp_s4 + psp_s5 * -psp_s3) >> 0xC);
        prim->x1 = psp_s1 + ((psp_s5 * psp_s4 - psp_s6 * -psp_s3) >> 0xC);
        prim->y1 = psp_s2 + ((psp_s6 * psp_s4 + psp_s5 * -psp_s3) >> 0xC);
        prim->x2 = psp_s1 + ((psp_s5 * -psp_s4 - psp_s6 * psp_s3) >> 0xC);
        prim->y2 = psp_s2 + ((psp_s6 * -psp_s4 + psp_s5 * psp_s3) >> 0xC);
        prim->x3 = psp_s1 + ((psp_s5 * psp_s4 - psp_s6 * psp_s3) >> 0xC);
        prim->y3 = psp_s2 + ((psp_s6 * psp_s4 + psp_s5 * psp_s3) >> 0xC);
    } else if (self->step < 5) {
        if (self->ext.ricStopWatch.unk84.val <= 0x100000) {
            if (self->ext.ricStopWatch.unk90) {
                self->ext.ricStopWatch.unk88 = (rand() % 0x40 + 0x200) * 0x100;
                self->ext.ricStopWatch.unk90 = 0;
            } else {
                self->ext.ricStopWatch.unk88 = (rand() % 0x80 + 0x100) * 0x100;
            }
            if (self->ext.ricStopWatch.unk80 >= 0) {
                self->ext.ricStopWatch.unk80 = -(rand() % 0x40 + 0x40);
            } else {
                self->ext.ricStopWatch.unk80 = rand() % 0x40 + 0x40;
            }
        }
        self->ext.ricStopWatch.unk84.val += self->ext.ricStopWatch.unk88;
        self->ext.ricStopWatch.unk88 -= 0x4000;
        psp_s1 = self->posX.i.hi + (self->facingLeft ? 6 : -6);
        psp_s2 = self->posY.i.hi - (self->ext.ricStopWatch.unk84.val >> 0x10);
        psp_s6 = rsin(self->ext.ricStopWatch.unk80);
        psp_s5 = rcos(self->ext.ricStopWatch.unk80);
        prim->x0 = psp_s1 + (((psp_s5 * -8) - (psp_s6 * -12)) >> 0xC);
        prim->y0 = psp_s2 + (((psp_s6 * -8) + (psp_s5 * -12)) >> 0xC);
        prim->x1 = psp_s1 + (((psp_s5 * 8) - (psp_s6 * -12)) >> 0xC);
        prim->y1 = psp_s2 + (((psp_s6 * 8) + (psp_s5 * -12)) >> 0xC);
        prim->x2 = psp_s1 + (((psp_s5 * -8) - (psp_s6 * 12)) >> 0xC);
        prim->y2 = psp_s2 + (((psp_s6 * -8) + (psp_s5 * 12)) >> 0xC);
        prim->x3 = psp_s1 + (((psp_s5 * 8) - (psp_s6 * 12)) >> 0xC);
        prim->y3 = psp_s2 + (((psp_s6 * 8) + (psp_s5 * 12)) >> 0xC);
    } else {
        psp_s4 = 8 - self->ext.ricStopWatch.t;
        if (psp_s4 <= 0) {
            psp_s4 = 1;
        }
#if defined(VERSION_PSP)
        psp_s3 = (self->ext.ricStopWatch.t << 5) + 0xC;
#else
        psp_s3 = (self->ext.ricStopWatch.t << 16 >> 11) + 0xC;
#endif
        if (psp_s3 >= 0x80) {
            psp_s3 = 0x80;
        }
        prim->x0 = prim->x2 = self->posX.i.hi - psp_s4;
        prim->x1 = prim->x3 = self->posX.i.hi + psp_s4;
        prim->y0 = prim->y1 = self->posY.i.hi - psp_s3;
        prim->y2 = prim->y3 = self->posY.i.hi + psp_s3;
    }
    if (self->step < 4) {
        psp_s2 = self->posY.i.hi - 0xE;
        if (self->ext.ricStopWatch.unk92) {
            psp_s1 = self->posX.i.hi - (self->facingLeft ? 10 : -4);
            prim = prim->next;
            if (self->ext.ricStopWatch.unk7E < 8) {
                prim->x0 = prim->x2 =
                    psp_s1 - (self->ext.ricStopWatch.unk7E / 2);
                prim->x1 = prim->x3 =
                    psp_s1 + (self->ext.ricStopWatch.unk7E / 2);
                prim->y0 = prim->y1 =
                    (psp_s2 - 8) - (7 - self->ext.ricStopWatch.unk7E);
                prim->y2 = prim->y3 =
                    (psp_s2 + 8) + (7 - self->ext.ricStopWatch.unk7E);
            } else if (self->ext.ricStopWatch.unk7E >= 0x44) {
                psp_s4 = (0x50 - (self->ext.ricStopWatch.unk7E + 4)) / 2;
                if (psp_s4 < 0) {
                    psp_s4 = 0;
                }
                psp_s3 = self->ext.ricStopWatch.unk7E - 0x44;
                if (psp_s3 > 8) {
                    psp_s3 = 8;
                }
                prim->x0 = prim->x2 = psp_s1 - psp_s4;
                prim->x1 = prim->x3 = psp_s1 + psp_s4;
                prim->y0 = prim->y1 = (psp_s2 - 8) - psp_s3;
                prim->y2 = prim->y3 = (psp_s2 + 8) + psp_s3;
            } else {
                prim->x0 = prim->x2 = psp_s1 - 4;
                prim->x1 = prim->x3 = psp_s1 + 4;
                prim->y0 = prim->y1 = psp_s2 - 8;
                prim->y2 = prim->y3 = psp_s2 + 8;
            }
            psp_s1 = self->posX.i.hi - (self->facingLeft ? 4 : -10);
            prim = prim->next;
            if (self->ext.ricStopWatch.unk7E < 0xC) {
                psp_s4 = (self->ext.ricStopWatch.unk7E - 4) / 2;
                if (psp_s4 < 0) {
                    psp_s4 = 0;
                }
                psp_s3 = 7 - (self->ext.ricStopWatch.unk7E - 4);
                if (psp_s3 < 0) {
                    psp_s3 = 0;
                }
                prim->x0 = prim->x2 = psp_s1 - psp_s4;
                prim->x1 = prim->x3 = psp_s1 + psp_s4;
                prim->y0 = prim->y1 = (psp_s2 - 8) - psp_s3;
                prim->y2 = prim->y3 = (psp_s2 + 8) + psp_s3;
            } else if (self->ext.ricStopWatch.unk7E >= 0x48) {
                prim->x0 = prim->x2 =
                    psp_s1 - ((0x50 - self->ext.ricStopWatch.unk7E) / 2);
                prim->x1 = prim->x3 =
                    psp_s1 + ((0x50 - self->ext.ricStopWatch.unk7E) / 2);
                prim->y0 = prim->y1 =
                    (psp_s2 - 8) - (-0x48 + self->ext.ricStopWatch.unk7E);
                prim->y2 = prim->y3 =
                    (psp_s2 + 8) + (-0x48 + self->ext.ricStopWatch.unk7E);
            } else {
                prim->x0 = prim->x2 = psp_s1 - 4;
                prim->x1 = prim->x3 = psp_s1 + 4;
                prim->y0 = prim->y1 = psp_s2 - 8;
                prim->y2 = prim->y3 = psp_s2 + 8;
            }
        } else {
            psp_s1 = self->posX.i.hi - (self->facingLeft ? 4 : -4);
            prim = prim->next;
            if (self->ext.ricStopWatch.unk7E < 8) {
                prim->x0 = prim->x2 =
                    psp_s1 - (self->ext.ricStopWatch.unk7E / 2);
                prim->x1 = prim->x3 =
                    psp_s1 + (self->ext.ricStopWatch.unk7E / 2);
                prim->y0 = prim->y1 =
                    (psp_s2 - 8) - (7 - self->ext.ricStopWatch.unk7E);
                prim->y2 = prim->y3 =
                    (psp_s2 + 8) + (7 - self->ext.ricStopWatch.unk7E);
            } else if (self->ext.ricStopWatch.unk7E >= 0x48) {
                prim->x0 = prim->x2 =
                    psp_s1 - ((0x50 - self->ext.ricStopWatch.unk7E) / 2);
                prim->x1 = prim->x3 =
                    psp_s1 + ((0x50 - self->ext.ricStopWatch.unk7E) / 2);
                prim->y0 = prim->y1 =
                    (psp_s2 - 8) - (-0x48 + self->ext.ricStopWatch.unk7E);
                prim->y2 = prim->y3 =
                    (psp_s2 + 8) + (-0x48 + self->ext.ricStopWatch.unk7E);
            } else {
                prim->x0 = prim->x2 = psp_s1 - 5;
                prim->x1 = prim->x3 = psp_s1 + 5;
                prim->y0 = prim->y1 = psp_s2 - 8;
                prim->y2 = prim->y3 = psp_s2 + 8;
            }
        }
    }
}

void RicEntitySubwpnBibleTrail(Entity* entity) {
    Primitive* prim;

    switch (entity->step) {
    case 0:
        entity->primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
        if (entity->primIndex == -1) {
            DestroyEntity(entity);
            return;
        }
        entity->flags =
            FLAG_UNK_20000 | FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_HAS_PRIMS;
        prim = &g_PrimBuf[entity->primIndex];
        prim->tpage = 0x1C;
        prim->clut = PAL_UNK_19D;
        prim->u0 = prim->u2 = 0x20;
        prim->v0 = prim->v1 = 0;
        prim->u1 = prim->u3 = 0x30;
        prim->v2 = prim->v3 = 0x10;
        prim->x0 = prim->x2 = entity->posX.i.hi - 8;
        prim->x1 = prim->x3 = entity->posX.i.hi + 8;
        prim->y0 = prim->y1 = entity->posY.i.hi - 8;
        prim->y2 = prim->y3 = entity->posY.i.hi + 8;
        prim->priority = entity->zPriority;
        prim->drawMode = DRAW_UNK_100 | DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
        entity->ext.et_BibleSubwpn.unk7E = 0x60;
        entity->step++;
        break;
    case 1:
        entity->ext.et_BibleSubwpn.unk7C++;
        if (entity->ext.et_BibleSubwpn.unk7C > 5) {
            entity->step++;
        }
        entity->ext.et_BibleSubwpn.unk7E -= 8;
        break;
    case 2:
        DestroyEntity(entity);
        return;
    }
    prim = &g_PrimBuf[entity->primIndex];
    PCOL(prim) = entity->ext.et_BibleSubwpn.unk7E;
}

void RicEntitySubwpnBible(Entity* self) {
    Primitive* prim;
    s32 sp48;
    s32 sp44;
    s32 sp40;
    s16 selfX;
    s16 selfY;
    s32 sp3C;
    s32 psp_s8;
    s32 psp_s7;
    s32 psp_s6;
    s32 psp_s5;
    s32 psp_s4;
    s32 psp_s3;
    s32 psp_s2;
    s32 psp_s1;

// This variable is uninitialized. It's an error for PSP compiler.
// Maybe they tossed this "= 0" line as a quick workaround.
#if defined(VERSION_PSP)
    psp_s4 = 0;
#endif
    switch (self->step) {
    case 0:
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags =
            FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_HAS_PRIMS | FLAG_UNK_20000;
        prim = &g_PrimBuf[self->primIndex];
        prim->tpage = 0x1E;
        prim->clut = 0x17F;
        prim->u0 = prim->u2 = 0x98;
        prim->v0 = prim->v1 = 0xD8;
        prim->u1 = prim->u3 = 0xA8;
        prim->v2 = prim->v3 = 0xF0;
        prim->priority = PLAYER.zPriority + 1;
        prim->drawMode = DRAW_UNK_100 | DRAW_HIDE;
        if (self->facingLeft) {
            sp44 = 0x20;
        } else {
            sp44 = -0x20;
        }
        self->ext.et_BibleSubwpn.unk84 = sp44;
        self->ext.et_BibleSubwpn.subweaponId = PL_W_BIBLE;
        RicSetSubweaponParams(self);
        self->hitboxWidth = 6;
        self->hitboxHeight = 6;
        self->step++;
        break;
    case 1:
        prim = &g_PrimBuf[self->primIndex];
        prim->drawMode &= ~DRAW_HIDE;
        self->ext.et_BibleSubwpn.unk86++;
        self->step++;
    case 2:
        self->ext.et_BibleSubwpn.unk7C++;
        self->ext.et_BibleSubwpn.unk7E++;
        if (self->ext.et_BibleSubwpn.unk7E >= 0x30) {
            self->step++;
        }
        break;
    case 3:
        self->ext.et_BibleSubwpn.unk7C++;
        if (self->ext.et_BibleSubwpn.unk7C >= 0x12C) {
            self->flags &= ~FLAG_KEEP_ALIVE_OFFCAMERA;
            if (self->facingLeft) {
                sp40 = FIX(-12);
            } else {
                sp40 = FIX(12);
            }
            self->velocityX = sp40;
            self->velocityY = FIX(-12);
            g_api.PlaySfx(SFX_BIBLE_SCRAPE);
            self->ext.et_BibleSubwpn.unk86++;
            self->step++;
        }
        break;
    }
    switch (self->ext.et_BibleSubwpn.unk86) {
    case 0:
        break;
    case 1:
        // All this logic is a mess, could use a cleanup
        psp_s2 = rsin(self->ext.et_BibleSubwpn.unk80);
        psp_s1 = rcos(self->ext.et_BibleSubwpn.unk80);
        psp_s5 = (psp_s2 * self->ext.et_BibleSubwpn.unk7E) >> 0xC;
        psp_s3 = (psp_s1 * self->ext.et_BibleSubwpn.unk7E) >> 0xC;
        psp_s7 = (psp_s1 * psp_s5 + psp_s2 * psp_s3);
        sp48 = (psp_s1 * psp_s3 - psp_s2 * psp_s5);
        psp_s5 = psp_s7 >> 0xC;
        psp_s3 = sp48 >> 0xC;
        psp_s2 = rsin(self->ext.et_BibleSubwpn.unk82);
        psp_s1 = rcos(self->ext.et_BibleSubwpn.unk82);
        psp_s7 = ((psp_s1 * psp_s5) + (psp_s2 * psp_s4)) >> 0xC;
        psp_s6 = ((psp_s1 * psp_s4) - (psp_s2 * psp_s5)) >> 0xC;
        psp_s4 = psp_s6;
        if (self->facingLeft) {
            psp_s6 = ((psp_s1 * psp_s4) + (psp_s2 * psp_s3)) >> 0xC;
        } else {
            psp_s6 = ((psp_s1 * psp_s4) - (psp_s2 * psp_s3)) >> 0xC;
        }
        self->ext.et_BibleSubwpn.unk80 += self->facingLeft ? 0x80 : -0x80;
        self->ext.et_BibleSubwpn.unk80 &= 0xFFF;
        self->ext.et_BibleSubwpn.unk82 += self->ext.et_BibleSubwpn.unk84;
        if (abs(self->ext.et_BibleSubwpn.unk82) >= 0x200) {
            self->ext.et_BibleSubwpn.unk84 *= -1;
        }
        self->posX.i.hi = PLAYER.posX.i.hi + psp_s7;
        self->posY.i.hi = PLAYER.posY.i.hi + psp_s6;
        self->zPriority = PLAYER.zPriority + (psp_s3 < 0 ? 2 : -2);
        break;
    case 2:
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        self->velocityY += FIX(-2);
        break;
    }
    if (self->ext.et_BibleSubwpn.unk86) {
        selfX = self->posX.i.hi;
        selfY = self->posY.i.hi;
        prim = &g_PrimBuf[self->primIndex];
        prim->x0 = prim->x2 = selfX - 8;
        prim->x1 = prim->x3 = selfX + 8;
        prim->y0 = prim->y1 = selfY - 12;
        prim->y2 = prim->y3 = selfY + 12;
        prim->priority = self->zPriority;
        RicCreateEntFactoryFromEntity(self, BP_BIBLE_TRAIL, 0);
        if (g_GameTimer % 10 == 0) {
            g_api.PlaySfx(BIBLE_SUBWPN_SWOOSH);
        }
    }
}
