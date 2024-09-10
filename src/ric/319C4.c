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
    Primitive* prim;
    PrimLineG2* primLine;
    s32 i;
    s32 angleChange;
    s32 brightness;

    switch (self->step) {
    case 0:
        self->primIndex = g_api.AllocPrimitives(PRIM_LINE_G2, 20);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags = FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_HAS_PRIMS;
        primLine = (PrimLineG2*)&g_PrimBuf[self->primIndex];
        for (i = 0; i < 4; i++) {
            primLine->preciseX.val = PLAYER.posX.val;
            primLine->preciseY.val = PLAYER.posY.val - FIX(40);
            primLine->priority = 194;
            primLine->drawMode = DRAW_HIDE;
            primLine->x0 = primLine->x1 = PLAYER.posX.i.hi;
            primLine->y0 = primLine->y1 = PLAYER.posY.i.hi - 0x1C;
            primLine->r0 = primLine->g0 = primLine->b0 = 0x80;
            primLine->r1 = primLine->g1 = primLine->b1 = 0x70;
            primLine->angle = angles_80155EE0[i];
            primLine->delay = 1;
            primLine = (PrimLineG2*)primLine->next;
        }
        for (brightness = 0x80; i < 20; i++) {
            if ((i & 3) == 0) {
                brightness -= 0x10;
                switch (i / 4) {
                case 1:
                    self->ext.et_8016D9C4.lines[0] = primLine;
                    break;
                case 2:
                    self->ext.et_8016D9C4.lines[1] = primLine;
                    break;
                case 3:
                    self->ext.et_8016D9C4.lines[2] = primLine;
                    break;
                case 4:
                    self->ext.et_8016D9C4.lines[3] = primLine;
                    break;
                }
            }
            primLine->priority = 0xC2;
            primLine->drawMode = DRAW_HIDE;
            primLine->x0 = primLine->x1 = PLAYER.posX.i.hi;
            primLine->y0 = primLine->y1 = PLAYER.posY.i.hi - 0x1C;
            primLine->r0 = primLine->g0 = primLine->b0 = brightness;
            primLine->r1 = primLine->g1 = primLine->b1 = brightness - 0x10;
            primLine = (PrimLineG2*)primLine->next;
        }
        self->ext.et_8016D9C4.unk90 = 4;
        self->ext.et_8016D9C4.unk8E = 0;
        self->ext.et_8016D9C4.unk8C = 0;
        g_api.PlaySfx(SFX_RIC_RSTONE_TINK);
        self->step++;
        break;
    case 1:
        self->ext.et_8016D9C4.unk8E = 1;
        switch (self->ext.et_8016D9C4.unk8C) {
        case 0:
            primLine = (PrimLineG2*)&g_PrimBuf[self->primIndex];
            break;
        case 1:
            primLine = self->ext.et_8016D9C4.lines[0];
            break;
        case 2:
            primLine = self->ext.et_8016D9C4.lines[1];
            break;
        case 3:
            primLine = self->ext.et_8016D9C4.lines[2];
            break;
        case 4:
            primLine = self->ext.et_8016D9C4.lines[3];
            break;
        }
        for (i = 0; i < 4; i++) {
            primLine->drawMode &= ~DRAW_HIDE;
            primLine = (PrimLineG2*)primLine->next;
        }
        if (++self->ext.et_8016D9C4.unk8C >= 5) {
            self->step++;
        }
        break;
    case 2:
        if (self->ext.et_8016D9C4.unk90 == 0) {
            self->step++;
            break;
        }
        break;
    case 3:
        if (++self->ext.et_8016D9C4.unk90 >= 5) {
            DestroyEntity(self);
            return;
        }
        break;
    }
    if (self->ext.et_8016D9C4.unk8E == 0) {
        return;
    }
    primLine = (PrimLineG2*)&g_PrimBuf[self->primIndex];
    for (i = 0; i < 4; i++) {
        if (primLine->delay != 0) {
            primLine->x1 = primLine->x0;
            primLine->y1 = primLine->y0;
            primLine->x0 = primLine->preciseX.i.hi;
            primLine->y0 = primLine->preciseY.i.hi;
            angleChange =
                primLine->angle - (ratan2(primLine->preciseY.val,
                                          FIX(128) - primLine->preciseX.val) &
                                   0xFFF);
            if (abs(angleChange) > 0x800) {
                if (angleChange < 0) {
                    angleChange += 0x1000;
                } else {
                    angleChange -= 0x1000;
                }
            }
            if (angleChange >= 0) {
                if (angleChange >= 0x81) {
                    angleChange = 0x80;
                }
            } else if (angleChange < -0x80) {
                angleChange = -0x80;
            }
            primLine->angle = (primLine->angle - angleChange) & 0xFFF;
            primLine->velocityX.val = (rcos(primLine->angle) << 8);
            primLine->velocityY.val = -(rsin(primLine->angle) << 8);
            primLine->preciseX.val += primLine->velocityX.val;
            primLine->preciseY.val += primLine->velocityY.val;
            self->posX.i.hi = primLine->preciseX.i.hi;
            self->posY.i.hi = primLine->preciseY.i.hi;
            RicCreateEntFactoryFromEntity(
                self, BP_CRASH_REBOUND_STONE_PARTICLES, 0);
            if (primLine->preciseY.val < 0) {
                primLine->delay = 0;
                primLine->drawMode |= DRAW_HIDE;
                self->ext.et_8016D9C4.unk90--;
            }
        }
        primLine = (PrimLineG2*)primLine->next;
    }
    primLine = self->ext.et_8016D9C4.lines[0];
    prim = &g_PrimBuf[self->primIndex];
    for (i = 0; i < 16; i++) {
        primLine->x1 = primLine->x0;
        primLine->y1 = primLine->y0;
        primLine->x0 = prim->x1;
        primLine->y0 = prim->y1;
        primLine = (PrimLineG2*)primLine->next;
        prim = prim->next;
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
        self->ext.reboundStoneCrashExplosion.unk80 = 0x10;
        self->ext.reboundStoneCrashExplosion.unk7E = 0;
        self->ext.reboundStoneCrashExplosion.unk84 = 0;
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
        if (++self->ext.reboundStoneCrashExplosion.unk86 == 5) {
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
    if (self->ext.reboundStoneCrashExplosion.unk7C >= 0x100) {
        self->ext.reboundStoneCrashExplosion.unk7C = 0xFF;
        self->ext.reboundStoneCrashExplosion.unk80 = 0;
    } else if (self->ext.reboundStoneCrashExplosion.unk7C < 0) {
        self->ext.reboundStoneCrashExplosion.unk80 = 0;
        self->ext.reboundStoneCrashExplosion.unk7C = 0;
    }
    self->ext.reboundStoneCrashExplosion.unk7E +=
        self->ext.reboundStoneCrashExplosion.unk82;
    if (self->ext.reboundStoneCrashExplosion.unk7E >= 0x100) {
        self->ext.reboundStoneCrashExplosion.unk7E = 0xFF;
        self->ext.reboundStoneCrashExplosion.unk82 = 0;
    } else if (self->ext.reboundStoneCrashExplosion.unk7E < 0) {
        self->ext.reboundStoneCrashExplosion.unk82 = 0;
        self->ext.reboundStoneCrashExplosion.unk7E = 0;
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
        if (self->step < 2U) {
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
    return;
}

void RicEntityCrashReboundStone(Entity* entity) {
    switch (entity->step) {
    case 0:
        entity->flags = FLAG_UNK_20000 | FLAG_KEEP_ALIVE_OFFCAMERA;
        entity->ext.timer.t = 0x14;
        entity->step++;

    case 1:
        entity->ext.timer.t--;
        if ((entity->ext.timer.t) == 0) {
        case 3:
        case 5:
            RicCreateEntFactoryFromEntity(entity, BP_57, 0);
            entity->step++;
        case 2:
        case 4:
        case 6:
            entity->ext.timer.t++;
            if (entity->ext.timer.t >= 11) {
                entity->ext.timer.t = 0;
                entity->posX.val = FIX(128.0);
                entity->posY.val = 0;
                RicCreateEntFactoryFromEntity(entity, FACTORY(BP_EMBERS, 1), 0);
                entity->step++;
            }
        }
        break;

    case 7:
        entity->ext.timer.t++;
        if (entity->ext.timer.t >= 16) {
            DestroyEntity(entity);
            g_Player.unk4E = 1;
            RicCreateEntFactoryFromEntity(
                entity, BP_CRASH_REBOUND_STONE_EXPLOSION, 0);
        }
        break;
    }
}

#define BIBLE_PAGE_COUNT 6
static Point16 bible_pages_pos[BIBLE_PAGE_COUNT];
void RicEntityCrashBibleBeam(Entity* self) {
    Primitive* prim;
    s16 var_s7;
    s16 hitboxOffX;
    s32 temp_s0;
    s32 temp_s0_2;
    s32 halfwidth;
    s32 var_s3;
    s32 i;
    s32 temp_v1;

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
                var_s3 = i - 4;
            }
            prim->x0 = prim->x1 = bible_pages_pos[i].x;
            prim->y0 = prim->y1 = bible_pages_pos[i].y;
            prim->x2 = prim->x3 = bible_pages_pos[var_s3].x;
            prim->y2 = prim->y3 = bible_pages_pos[var_s3].y;
            prim->priority = 0xC2;
            prim->blendMode = 0x435;
            prim = prim->next;
        }
        self->step++;
        break;
    case 1:
        if (++self->ext.bibleBeam.unk80 >= 0x3C) {
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
        if (++self->ext.bibleBeam.unk80 >= 0x78) {
            DestroyEntity(self);
            return;
        }
        break;
    }
    var_s7 = 0;
    prim = &g_PrimBuf[self->primIndex];
    for (i = 0; i < BIBLE_PAGE_COUNT; i++) {
        var_s3 = i + 2;
        if (var_s3 >= BIBLE_PAGE_COUNT) {
            var_s3 = i - 4;
        }
        temp_v1 = (rsin((self->ext.bibleBeam.unk80 * 20) + (i << 8)) * 96);
        prim->r0 = prim->r1 = abs(temp_v1 >> 0xc);
        temp_v1 = rsin((self->ext.bibleBeam.unk80 * 15) + (i << 8)) * 96;
        prim->g0 = prim->g1 = abs(temp_v1 >> 0xc);
        temp_v1 = rsin((self->ext.bibleBeam.unk80 * 10) + (i << 8)) * 96;
        prim->b0 = prim->b1 = abs(temp_v1 >> 0xc);
        temp_v1 = rsin((self->ext.bibleBeam.unk80 * 15) + (var_s3 << 8)) * 96;
        prim->r2 = prim->r3 = abs(temp_v1 >> 0xc);
        temp_v1 = rsin((self->ext.bibleBeam.unk80 * 10) + (var_s3 << 8)) * 96;
        prim->g2 = prim->g3 = abs(temp_v1 >> 0xc);
        temp_v1 = rsin((self->ext.bibleBeam.unk80 * 20) + (var_s3 << 8)) * 96;
        prim->b2 = prim->b3 = abs(temp_v1 >> 0xc);
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
    halfwidth = self->ext.bibleBeam.unk7E / 2;
    hitboxOffX = !self->facingLeft ? halfwidth : -halfwidth;
    self->hitboxOffX = hitboxOffX;
    self->hitboxWidth = abs(hitboxOffX);
    self->hitboxHeight = var_s7 - self->posY.i.hi;
}

static s16 bible_page_angles[BIBLE_PAGE_COUNT] = {
    0x0400, 0x06AB, 0x0955, 0x0C00, 0x0EAB, 0x1155,
};
static s32 bible_pages_volume;
void RicEntityCrashBible(Entity* self) {
    Primitive* prim;
    s16 temp_a1_3;
    s16 temp_v0_6;
    s32 temp_s0_2;
    s32 temp_s5;
    s32 temp_s6;
    s32 temp_v0_4;
    s32 temp_v0_5;
    s32 i;
    s16 temp_a0;
    s16 temp_a1;

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
            prim->clut = 0x1AE;
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
        if (++self->ext.et_8016E9E4.unk82 >= 8) {
            self->ext.et_8016E9E4.unk82 = 0;
            self->step++;
        }
        break;
    case 3:
        if (++self->ext.et_8016E9E4.unk82 >= 6) {
            prim = &g_PrimBuf[self->primIndex];
            prim->clut = 0x19F;
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
        self->ext.et_8016E9E4.unk7C =
            (self->ext.et_8016E9E4.unk7C + 0x80) & 0xFFF;
        self->ext.et_8016E9E4.unk80 += 4;
        if (self->ext.et_8016E9E4.unk80 >= 0x30) {
            self->step++;
        }
        break;
    case 7:
        self->ext.et_8016E9E4.unk7C =
            (self->ext.et_8016E9E4.unk7C + 0x80) & 0xFFF;
        if (++self->ext.et_8016E9E4.unk82 >= 0x1E) {
            // create bible page beam
            RicCreateEntFactoryFromEntity(self, BP_CRASH_BIBLE_BEAM, 0);
            self->ext.et_8016E9E4.unk82 = 0;
            self->step++;
        }
        break;
    case 8:
        self->ext.et_8016E9E4.unk7C =
            (self->ext.et_8016E9E4.unk7C + 0x80) & 0xFFF;
        if (++self->ext.et_8016E9E4.unk82 >= 0x60) {
            g_Player.unk4E = 1;
            self->step++;
        }
        break;
    case 9:
        self->ext.et_8016E9E4.unk7C =
            (self->ext.et_8016E9E4.unk7C + 0x80) & 0xFFF;
        self->ext.et_8016E9E4.unk80 -= 2;
        if (self->ext.et_8016E9E4.unk80 <= 0) {
            DestroyEntity(self);
            return;
        }
        break;
    }
    // FAKE, needed for reg match
    temp_a1 = self->ext.et_8016E9E4.unk7C;
    if ((self->ext.et_8016E9E4.unk7C == 0x100) ||
        (self->ext.et_8016E9E4.unk7C == 0x500) ||
        (self->ext.et_8016E9E4.unk7C == 0x900) ||
        (self->ext.et_8016E9E4.unk7C == 0xD00)) {
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

    temp_a0 = self->posX.i.hi;
    temp_a1 = self->posY.i.hi;
    prim = &g_PrimBuf[self->primIndex];
    prim->x0 = prim->x2 = temp_a0 - 8;
    prim->x1 = prim->x3 = temp_a0 + 8;
    prim->y0 = prim->y1 = temp_a1 - 12;
    prim->y2 = prim->y3 = temp_a1 + 12;
    prim->r0 = prim->g0 = prim->b0 = prim->r1 = prim->g1 = prim->b1 = prim->r2 =
        prim->g2 = prim->b2 = prim->r3 = prim->g3 = prim->b3 =
            self->ext.et_8016E9E4.unk84;
    prim = prim->next;

    temp_s6 = rsin(self->ext.et_8016E9E4.unk7E);
    temp_s5 = rcos(self->ext.et_8016E9E4.unk7E);
    for (i = 0; i < BIBLE_PAGE_COUNT; i++) {
        temp_s0_2 = (rsin(self->ext.et_8016E9E4.unk7C + bible_page_angles[i]) *
                     self->ext.et_8016E9E4.unk80) >>
                    0xC;
        temp_v0_4 = (rcos(self->ext.et_8016E9E4.unk7C + bible_page_angles[i]) *
                     self->ext.et_8016E9E4.unk80) >>
                    0xC;
        temp_a1_3 =
            self->posX.i.hi + ((((temp_s6 * temp_v0_4) >> 0xC) << 9) /
                               (((temp_s5 * temp_v0_4) >> 0xC) + 0x200));
        temp_v0_6 =
            self->posY.i.hi +
            ((temp_s0_2 << 9) / (((temp_s5 * temp_v0_4) >> 0xC) + 0x200));
        temp_v0_5 = ((temp_s5 * temp_v0_4) >> 0xC) + 0x200;
        bible_pages_pos[i].x = temp_a1_3;
        bible_pages_pos[i].y = temp_v0_6;
        prim->x0 = prim->x2 = temp_a1_3 - 0x1000 / temp_v0_5;
        prim->x1 = prim->x3 = temp_a1_3 + 0x1000 / temp_v0_5;
        // FAKE, needed for reg match
        temp_a0 = (prim->y1 = temp_v0_6 - 0x1000 / temp_v0_5);
        prim->y0 = temp_a0;

        prim->y2 = prim->y3 = temp_v0_6 + 0x1000 / temp_v0_5;
        prim = prim->next;
    }
}

void func_8016F198(Entity* self) {
    const int PrimCount = 16;
    Primitive* prim;
    s16 unk7C;
    s16 temp_s6;
    s16 temp_a0;
    s16 temp_a1;
    s16 temp_a2;
    s16 temp_v1;
    s16 var_s0_2;
    s32 sine;
    s32 cosine;
    s32 i;
    u16 tpage;

    switch (self->step) {
    case 0:
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, PrimCount);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            g_Player.unk4E = 1;
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
        if (++self->ext.factory.unk7C >= 0x18) {
            self->step++;
        }
        break;
    case 3:
        g_Player.unk4E = 1;
        DestroyEntity(self);
        return;
    }
    if (self->ext.factory.unk7C == 0) {
        return;
    }
    if (g_CurrentBuffer == g_GpuBuffers) {
        tpage = 0x104;
    } else {
        tpage = 0x100;
    }
    prim = &g_PrimBuf[self->primIndex];
    for (i = 0; i < PrimCount; i++) {
        sine = rsin(i << 8);
        cosine = rcos(i << 8);
        unk7C = self->ext.factory.unk7C;
        var_s0_2 = 0;
        temp_s6 = unk7C * 8;
        if (unk7C >= 4) {
            var_s0_2 = (unk7C - 4) * 8;
        }
        temp_a1 = ((cosine * (s16)(unk7C * 8)) >> 0xC) + 0x80;
        temp_v1 = ((cosine * var_s0_2) >> 0xC) + 0x80;
        temp_a0 = ((sine * (s16)(unk7C * 8)) >> 0xC) + 0x78;
        temp_a2 = ((sine * var_s0_2) >> 0xC) + 0x78;

        temp_a1 = temp_a1 >= 0 ? MIN(temp_a1, 0xFF) : 0;
        prim->x0 = temp_a1;

        temp_v1 = temp_v1 >= 0 ? MIN(temp_v1, 0xFF) : 0;
        prim->x2 = temp_v1;

        temp_a0 = temp_a0 >= 0 ? MIN(temp_a0, 0xF0) : 0;
        prim->y0 = temp_a0;

        temp_a2 = temp_a2 >= 0 ? MIN(temp_a2, 0xF0) : 0;
        prim->y2 = temp_a2;

        prim->u0 = ~prim->x0;
        prim->u2 = ~prim->x2;
        prim->v0 = -0x10 - prim->y0;
        prim->v2 = -0x10 - prim->y2;

        sine = rsin((i + 1) << 8);
        cosine = rcos((i + 1) << 8);
        temp_a1 = ((cosine * temp_s6) >> 0xC) + 0x80;
        temp_v1 = ((cosine * var_s0_2) >> 0xC) + 0x80;
        temp_a0 = ((sine * temp_s6) >> 0xC) + 0x78;
        temp_a2 = ((sine * var_s0_2) >> 0xC) + 0x78;

        temp_a1 = temp_a1 >= 0 ? MIN(temp_a1, 0xFF) : 0;
        prim->x1 = temp_a1;

        temp_v1 = temp_v1 >= 0 ? MIN(temp_v1, 0xFF) : 0;
        prim->x3 = temp_v1;

        temp_a0 = temp_a0 >= 0 ? MIN(temp_a0, 0xF0) : 0;
        prim->y1 = temp_a0;

        temp_a2 = temp_a2 >= 0 ? MIN(temp_a2, 0xF0) : 0;
        prim->y3 = temp_a2;

        prim->tpage = tpage;
        prim->u1 = ~prim->x1;
        prim->u3 = ~prim->x3;
        prim->v1 = -0x10 - prim->y1;
        prim->v3 = -0x10 - prim->y3;
        prim = prim->next;
    }
}

// Entity ID #64, created by blueprint #72. This call is in
// RicEntitySubwpnStopwatch. When Richter has the stopwatch weapon, and uses it
// as a crash, it makes 4 floating stopwatches. When they are done they
// disappear in a spinning sparkle. This entity represents that sparkle. 4
// copies of this entity are made when the crash is done.
void RicEntityCrashStopwatchDoneSparkle(Entity* self) {
    Primitive* prim;
    u32 selfX;
    u32 selfY;
    s32 neg8cos;
    s32 neg8sin;
    s32 sinScaled;
    s32 cosScalDiv8;
    s32 sinScalDiv8;
    s32 sine;
    s32 cosScaled;
    s32 cosine;
    s32 rand_uCoord;
    s32 var_a1;
    s32 i;
    s32 var_v1;

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
        prim->drawMode =
            DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_UNK02 | DRAW_TRANSP;
        prim->priority = 0xC2;
        prim->u1 = prim->u3 = 0x3F;
        prim->tpage = 0x1A;
        prim->clut = 0x19F;
        prim->u0 = prim->u2 = 0;
        prim->v0 = prim->v1 = 0xC0;
        prim->v2 = prim->v3 = 0xFF;
        prim->r0 = prim->r1 = prim->r2 = prim->r3 = prim->g1 = prim->g2 =
            prim->g3 = 0x40;
        prim->b0 = prim->b1 = prim->b2 = prim->b3 = 0x80;

        prim = prim->next;
        prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_HIDE | DRAW_COLORS |
                         DRAW_UNK02 | DRAW_TRANSP;
        prim->priority = 0xC2;
        prim->tpage = 0x1A;
        prim->clut = 0x19F;
        prim->u0 = prim->u2 = 0x40;
        prim->u1 = prim->u3 = 0x7F;
        prim->v0 = prim->v1 = 0xC0;
        prim->v2 = prim->v3 = 0xFF;
        prim->r0 = prim->r1 = prim->r2 = prim->r3 = prim->g1 = prim->g2 =
            prim->g3 = 0x40;
        prim->b0 = prim->b1 = prim->b2 = prim->b3 = 0x80;

        prim = prim->next;
        prim->priority = 0xC2;
        prim->drawMode = DRAW_UNK_400 | DRAW_UNK_40 | DRAW_TPAGE2 | DRAW_TPAGE |
                         DRAW_HIDE | DRAW_COLORS | DRAW_UNK02 | DRAW_TRANSP;
        prim->tpage = 0x1A;
        prim->clut = 0x19F;
        prim->u0 = prim->u2 = 0xB;
        prim->u1 = prim->u3 = 0x35;
        prim->v0 = prim->v1 = 0xCB;
        prim->v2 = prim->v3 = 0xF5;
        prim->r0 = prim->r1 = prim->r2 = prim->r3 = prim->g1 = prim->g2 =
            prim->g3 = 0xCF;
        prim->b0 = prim->b1 = prim->b2 = prim->b3 = 0xFF;

        prim = prim->next;
        prim->priority = 0xC2;
        prim->drawMode = DRAW_UNK_400 | DRAW_UNK_40 | DRAW_TPAGE2 | DRAW_TPAGE |
                         DRAW_HIDE | DRAW_COLORS | DRAW_UNK02 | DRAW_TRANSP;
        prim->tpage = 0x1A;
        prim->clut = 0x19F;
        prim->u0 = prim->u2 = 0xB;
        prim->u1 = prim->u3 = 0x35;
        prim->v0 = prim->v1 = 0xCB;
        prim->v2 = prim->v3 = 0xF5;
        prim->r0 = prim->r1 = prim->r2 = prim->r3 = prim->g1 = prim->g2 =
            prim->g3 = 0xCF;
        prim->b0 = prim->b1 = prim->b2 = prim->b3 = 0xFF;

        self->ext.et_stopWatchSparkle.unk88 = prim->next;
        for (i = 0; i < 16; i++) {
            prim = prim->next;
            prim->priority = PLAYER.zPriority + 3;
            prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_HIDE |
                             DRAW_COLORS | DRAW_UNK02 | DRAW_TRANSP;
            prim->tpage = 0x1A;
            prim->clut = 0x194;
            rand_uCoord = rand() % 5 * 0x10;
            prim->v0 = prim->v1 = 0xC0;
            prim->v2 = prim->v3 = 0xD0;
            prim->r0 = prim->r1 = prim->r2 = prim->r3 = prim->g1 = prim->g2 =
                prim->g3 = prim->b0 = prim->b1 = prim->b2 = prim->b3 = 0x80;
            prim->u0 = prim->u2 = rand_uCoord - 0x70;
            prim->u1 = prim->u3 = prim->u0 + 0x10;
        }
        self->ext.et_stopWatchSparkle.unk7C = 4;
        self->ext.et_stopWatchSparkle.unk8C =
            self->ext.et_stopWatchSparkle.unk8E =
                self->ext.et_stopWatchSparkle.unk7E =
                    self->ext.et_stopWatchSparkle.unk80 =
                        self->ext.et_stopWatchSparkle.unk82 = 0;
        self->step++;
        break;
    case 1:
        if (++self->ext.et_stopWatchSparkle.unk7C >= 0x10) {
            self->ext.et_stopWatchSparkle.unk7E = 4;
            prim = g_PrimBuf[self->primIndex].next;
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
        if (--self->ext.et_stopWatchSparkle.unk7C <= 0) {
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
        self->ext.et_stopWatchSparkle.unk82 =
            (self->ext.et_stopWatchSparkle.unk82 + 0x80) & 0xFFF;
        self->ext.et_stopWatchSparkle.unk80 += 2;
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
        self->ext.et_stopWatchSparkle.unk82 =
            (self->ext.et_stopWatchSparkle.unk82 + 0x80) & 0xFFF;
        break;
    case 4:
        if (self->ext.et_stopWatchSparkle.unk8E == 0) {
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
        sine = rsin(self->ext.et_stopWatchSparkle.unk82);
        cosine = rcos(self->ext.et_stopWatchSparkle.unk82);
        cosScaled = cosine * self->ext.et_stopWatchSparkle.unk80;
        sinScaled = sine * self->ext.et_stopWatchSparkle.unk80;
        cosScalDiv8 = cosine * (self->ext.et_stopWatchSparkle.unk80 / 8);
        sinScalDiv8 = sine * (self->ext.et_stopWatchSparkle.unk80 / 8);

        prim = prim->next;
        prim->x0 = self->posX.i.hi + ((-cosScaled - -sinScaled) >> 0xC);
        prim->y0 = self->posY.i.hi + ((-sinScaled - cosScaled) >> 0xC);
        prim->x1 = self->posX.i.hi + ((cosScalDiv8 - -sinScalDiv8) >> 0xC);
        prim->y1 = self->posY.i.hi + ((sinScalDiv8 - cosScalDiv8) >> 0xC);
        prim->x2 = self->posX.i.hi + ((-cosScalDiv8 - sinScalDiv8) >> 0xC);
        prim->y2 = self->posY.i.hi + ((-sinScalDiv8 + cosScalDiv8) >> 0xC);
        prim->x3 = self->posX.i.hi + ((cosScaled - sinScaled) >> 0xC);
        prim->y3 = self->posY.i.hi + ((sinScaled + cosScaled) >> 0xC);

        prim = prim->next;
        prim->x0 = self->posX.i.hi + ((-cosScalDiv8 - -sinScalDiv8) >> 0xC);
        prim->y0 = self->posY.i.hi + ((-sinScalDiv8 - cosScalDiv8) >> 0xC);
        prim->x1 = self->posX.i.hi + ((cosScaled - -sinScaled) >> 0xC);
        prim->y1 = self->posY.i.hi + ((sinScaled - cosScaled) >> 0xC);
        prim->x2 = self->posX.i.hi + ((-cosScaled - sinScaled) >> 0xC);
        prim->y2 = self->posY.i.hi + ((-sinScaled + cosScaled) >> 0xC);
        prim->x3 = self->posX.i.hi + ((cosScalDiv8 - sinScalDiv8) >> 0xC);
        prim->y3 = self->posY.i.hi + ((sinScalDiv8 + cosScalDiv8) >> 0xC);
        break;
    case 3:
        sine = rsin(self->ext.et_stopWatchSparkle.unk82);
        cosine = rcos(self->ext.et_stopWatchSparkle.unk82);
        cosScaled = cosine * self->ext.et_stopWatchSparkle.unk80;
        sinScaled = sine * self->ext.et_stopWatchSparkle.unk80;
        cosScalDiv8 = cosine * (self->ext.et_stopWatchSparkle.unk80 / 8);
        sinScalDiv8 = sine * (self->ext.et_stopWatchSparkle.unk80 / 8);
        prim = prim->next;
        prim = prim->next;

        prim->x0 = self->posX.i.hi + ((-cosScaled - -sinScaled) >> 0xC);
        prim->y0 = self->posY.i.hi + ((-sinScaled - cosScaled) >> 0xC);
        prim->x1 = self->posX.i.hi + ((cosScalDiv8 - -sinScalDiv8) >> 0xC);
        prim->y1 = self->posY.i.hi + ((sinScalDiv8 - cosScalDiv8) >> 0xC);
        prim->x2 = self->posX.i.hi + ((-cosScalDiv8 - sinScalDiv8) >> 0xC);
        prim->y2 = self->posY.i.hi + ((-sinScalDiv8 + cosScalDiv8) >> 0xC);
        prim->x3 = self->posX.i.hi + ((cosScaled - sinScaled) >> 0xC);
        prim->y3 = self->posY.i.hi + ((sinScaled + cosScaled) >> 0xC);
        prim->r0 = prim->r1 = prim->r2 = prim->r3 = prim->g1 = prim->g2 =
            prim->g3 = self->ext.et_stopWatchSparkle.unk84 - 0x20;
        prim->b0 = prim->b1 = prim->b2 = prim->b3 =
            self->ext.et_stopWatchSparkle.unk84;

        prim = prim->next;
        prim->x0 = self->posX.i.hi + ((-cosScalDiv8 - -sinScalDiv8) >> 0xC);
        prim->y0 = self->posY.i.hi + ((-sinScalDiv8 - cosScalDiv8) >> 0xC);
        prim->x1 = self->posX.i.hi + ((cosScaled - -sinScaled) >> 0xC);
        prim->y1 = self->posY.i.hi + ((sinScaled - cosScaled) >> 0xC);
        prim->x2 = self->posX.i.hi + ((-cosScaled - sinScaled) >> 0xC);
        prim->y2 = self->posY.i.hi + ((-sinScaled + cosScaled) >> 0xC);
        prim->x3 = self->posX.i.hi + ((cosScalDiv8 - sinScalDiv8) >> 0xC);
        prim->y3 = self->posY.i.hi + ((sinScalDiv8 + cosScalDiv8) >> 0xC);
        prim->g1 = prim->g2 = prim->g3 =
            self->ext.et_stopWatchSparkle.unk84 - 0x20;
        prim->b0 = prim->b1 = prim->b2 = prim->b3 =
            self->ext.et_stopWatchSparkle.unk84;
        break;
    }
    if (self->ext.et_stopWatchSparkle.unk8E != 0) {
        prim = self->ext.et_stopWatchSparkle.unk88;
        self->ext.et_stopWatchSparkle.unk8E = 0;
        for (i = 0; i < 16; i++) {
            if (i == self->ext.et_stopWatchSparkle.unk8C) {
                if ((self->ext.et_stopWatchSparkle.unk90 > -0x20 &&
                     self->ext.et_stopWatchSparkle.unk90 < 0x120) &&
                    (self->ext.et_stopWatchSparkle.unk92 > -0x20 &&
                     self->ext.et_stopWatchSparkle.unk92 < 0x120)) {
                    prim->r0 = 0x80;
                    prim->drawMode &= ~DRAW_HIDE;
                    if (!(i & 3)) {
                        var_a1 = rand() % 0x200 + 0x200;
                    } else {
                        var_a1 = rand() % 0x80 + 0x80;
                    }
                    var_v1 = self->ext.et_stopWatchSparkle.unk86 -
                             self->ext.et_stopWatchSparkle.unk94;
                    if (abs(var_v1) >= 0x801) {
                        if (var_v1 < 0) {
                            var_v1 += 0x1000;
                        } else {
                            var_v1 -= 0x1000;
                        }
                    }
                    if (var_v1 > 0) {
                        var_a1 = -var_a1;
                    }
                    self->ext.et_stopWatchSparkle.unk86 =
                        (self->ext.et_stopWatchSparkle.unk86 + var_a1) & 0xFFF;
                    sine = rsin(self->ext.et_stopWatchSparkle.unk86);
                    cosine = rcos(self->ext.et_stopWatchSparkle.unk86);
                    neg8cos = -(cosine * 8);
                    neg8sin = -(sine * 8);
                    prim->x0 = (self->ext.et_stopWatchSparkle.unk90 +
                                (sine * 8 >> 0xC));
                    prim->y0 = (self->ext.et_stopWatchSparkle.unk92 +
                                ((neg8cos) >> 0xC));
                    prim->x1 = (self->ext.et_stopWatchSparkle.unk90 +
                                ((cosine * 16 - neg8sin) >> 0xC));
                    prim->y1 = (self->ext.et_stopWatchSparkle.unk92 +
                                ((sine * 16 + neg8cos) >> 0xC));
                    prim->x2 = (self->ext.et_stopWatchSparkle.unk90 +
                                (neg8sin >> 0xC));
                    prim->y2 = (self->ext.et_stopWatchSparkle.unk92 +
                                (cosine * 8 >> 0xC));
                    prim->x3 = (self->ext.et_stopWatchSparkle.unk90 +
                                ((cosine * 16 - sine * 8) >> 0xC));
                    prim->y3 = (self->ext.et_stopWatchSparkle.unk92 +
                                ((sine * 16 + cosine * 8) >> 0xC));
                    prim->r0 = 0x80;
                    self->ext.et_stopWatchSparkle.unk90 += (cosine * 16 >> 0xC);
                    self->ext.et_stopWatchSparkle.unk92 += (sine * 16 >> 0xC);
                    selfX = self->posX.i.hi;
                    selfY = self->posY.i.hi;
                    self->posX.i.hi = self->ext.et_stopWatchSparkle.unk90;
                    self->posY.i.hi = self->ext.et_stopWatchSparkle.unk92;
                    RicCreateEntFactoryFromEntity(self, BP_73, 0);
                    self->posX.i.hi = selfX;
                    self->posY.i.hi = selfY;
                } else {
                    prim->drawMode |= DRAW_HIDE;
                }
            } else {
                prim->r0 -= 8;
                if (prim->r0 < 0x20U) {
                    prim->drawMode |= DRAW_HIDE;
                }
            }
            prim->r1 = prim->r2 = prim->r3 = prim->g0 = prim->g1 = prim->g2 =
                prim->g3 = prim->b0 = prim->b1 = prim->b2 = prim->b3 = prim->r0;
            self->ext.et_stopWatchSparkle.unk8E |=
                ((prim->drawMode & DRAW_HIDE) ? 0 : 1);
            prim = prim->next;
        }
        if (++self->ext.et_stopWatchSparkle.unk8C >= 0x10) {
            self->ext.et_stopWatchSparkle.unk8C = 0;
        }
    }
}

void func_80170548(Entity* entity) {
    switch (entity->step) {
    case 0:
        entity->flags = FLAG_KEEP_ALIVE_OFFCAMERA;
        entity->ext.generic.unkB0 = 0x1E;
        RicSetSubweaponParams(entity);
        entity->hitboxWidth = 8;
        entity->hitboxHeight = 8;
        entity->step++;
        break;
    case 1:
        if (++entity->ext.timer.t >= 5) {
            DestroyEntity(entity);
        }
        break;
    }
}

void func_801705EC(Entity* entity) {
    u16 temp;

    switch (entity->step) {
    case 0:
        entity->flags = FLAG_KEEP_ALIVE_OFFCAMERA;
        entity->ext.et_80161FF0.unk7E = 0;
        entity->step++;
    case 1:
    case 3:
    case 5:
    case 7:
        temp = entity->ext.et_80161FF0.unk7E + 1;
        entity->ext.et_80161FF0.unk7E = temp;
        RicCreateEntFactoryFromEntity(
            entity, FACTORY(BP_SUBWPN_STOPWATCH, temp), 0);
        entity->ext.et_80161FF0.unk7C = 0;
        entity->step++;
        break;
    case 2:
    case 4:
    case 6:
        entity->ext.et_80161FF0.unk7C++;
        if (entity->ext.et_80161FF0.unk7C >= 16) {
            entity->step++;
        }
        break;
    case 8:
        DestroyEntity(entity);
        break;
    }
}

static s16 GetAguneaLightningAngle(u16* arg0, s16 arg1, s16 arg2, s16* arg3) {
    s16 temp_s3;
    s16 s3_offset = 0x80;
    s8 arg2_copy = arg2;

    temp_s3 = arg1 - s3_offset + rand() % 256;
    *arg3 = (rand() % 48) + 0x10;
    arg0[0] = arg0[1];
    arg0[2] = arg0[3];
    if (arg2 != 0) {
        arg0[1] = arg0[1] + ((rcos(temp_s3) * *arg3) >> 0xC);
        arg0[3] = arg0[3] + ((rsin(temp_s3) * *arg3) >> 0xC);
        if (arg2_copy & 1) {
            return GetAguneaLightningAngle(
                arg0, (temp_s3 - 0x140), arg2 / 2, arg3);
        } else {
            rand();
            rand();
            return GetAguneaLightningAngle(
                arg0, (temp_s3 + 0x140), (arg2 - 1) / 2, arg3);
        }
    } else {
        return temp_s3;
    }
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
    u16 sp10[4];
    s16 sp18;
    u16 sp20;
    s32 temp_s0;
    s16 angle;
    s32 angleCos;
    s32 angleSin;
    s16 xCoord;
    s16 yCoord;
    Primitive* prim;
    s32 i;
    s32 randomSeed;
    s16 var_s4;
    s16 var_s6;

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
            prim->clut = 0x194;
            prim->u0 = prim->u2 = (rand() % 5) * 0x10 - 0x70;
            prim->u1 = prim->u3 = prim->u0 + 0x20;
            if (rand() & 1) {
                prim->v0 = prim->v1 = 0xD0;
                prim->v2 = prim->v3 = 0xE0;
            } else {
                prim->v0 = prim->v1 = 0xE0;
                prim->v2 = prim->v3 = 0xD0;
            }
            prim->priority = 0xC1;
            prim->drawMode = DRAW_UNK_200 | DRAW_HIDE | DRAW_COLORS;
            prim->r0 = prim->g0 = prim->b0 = prim->r1 = prim->g1 = prim->b1 =
                prim->r2 = prim->g2 = prim->b2 = prim->r3 = prim->g3 =
                    prim->b3 = 0x80;
            prim = prim->next;
        }
        prim = &g_PrimBuf[self->primIndex];
        temp_s0 = self->params / 0x100 * 0x200;
        sp20 = (temp_s0)-0x100 + rand() % 0x200;
        randomSeed = rand();
        for (i = 0; i < 15; i++) {
            srand(randomSeed);
            sp10[1] = self->posX.i.hi;
            sp10[3] = self->posY.i.hi;
            angle = GetAguneaLightningAngle(&sp10, sp20, i, &sp18);
            xCoord = sp10[0];
            yCoord = sp10[2];
            var_s6 = (i == 0) ? 2 : 8;
            var_s4 = (i < 7) ? 8 : 2;

            angleCos = rcos(angle);
            angleSin = rsin(angle);
            prim->x0 = xCoord + (-(angleSin * -var_s6) >> 0xC);
            prim->y0 = yCoord + ((angleCos * -var_s6) >> 0xC);
            prim->x1 =
                xCoord + ((angleCos * sp18 - (angleSin * -var_s4)) >> 0xC);
            prim->y1 =
                yCoord + ((angleSin * sp18 + (angleCos * -var_s4)) >> 0xC);
            prim->x2 = xCoord + (-(angleSin * var_s6) >> 0xC);
            prim->y2 = yCoord + ((angleCos * var_s6) >> 0xC);
            prim->x3 =
                xCoord + ((angleCos * sp18 - (angleSin * var_s4)) >> 0xC);
            prim->y3 =
                yCoord + ((angleSin * sp18 + (angleCos * var_s4)) >> 0xC);
            prim = prim->next;
        }
        self->ext.et_8017091C.unk7E = 1;
        self->step++;
        return;
    case 1:
        prim = &g_PrimBuf[self->primIndex];
        for (i = 0; i < 15; i++) {
            prim->drawMode &= ~DRAW_HIDE;
            prim = prim->next;
        }
        self->step++;
    case 2:
        if (++self->ext.et_8017091C.unk7C >= 5) {
            prim = &g_PrimBuf[self->primIndex];
            for (i = 0; i < 15; i++) {
                prim->clut = 0x15F;
                prim->r0 = prim->g0 = prim->b0 = prim->r1 = prim->g1 =
                    prim->b1 = prim->r2 = prim->g2 = prim->b2 = prim->r3 =
                        prim->g3 = prim->b3 = 0xFF;
                prim->v0 = prim->v1 = prim->v0 - 0x10;
                // Seems fake but without this the registers get shuffled
                xCoord = prim->v2;
                prim->v2 = prim->v3 = xCoord - 0x10;
                prim = prim->next;
            }
            self->ext.et_8017091C.unk7C = 0;
            self->step++;
            return;
        }
        break;
    case 3:
    case 5:
        prim = &g_PrimBuf[self->primIndex];
        for (i = 0; i < 15; i++) {
            prim->clut = 0x194;
            prim = prim->next;
        }
        self->step++;
        return;
    case 4:
        prim = &g_PrimBuf[self->primIndex];
        for (i = 0; i < 15; i++) {
            prim->clut = 0x15F;
            prim = prim->next;
        }
        self->step++;
        return;
    case 6:
        prim = &g_PrimBuf[self->primIndex];
        for (i = 0; i < 15; i++) {
            prim->r0 = prim->g0 = prim->b0 = prim->r1 = prim->g1 = prim->b1 =
                prim->r2 = prim->g2 = prim->b2 = prim->r3 = prim->g3 =
                    prim->b3 = 0x60 - (self->ext.et_8017091C.unk7C * 4);
            prim = prim->next;
        }
        if (++self->ext.et_8017091C.unk7C >= 0x10) {
            DestroyEntity(self);
            return;
        }
        break;
    }
}

#define LIGHTNING_COUNT 8
static s32 g_AguneaParams[LIGHTNING_COUNT];
void RicEntityAguneaCircle(Entity* self) {
    Primitive* prim;
    s16 rand_angle;
    s16 xCoord;
    s16 yCoord;
    s32 quarterSelfY;
    s32 i;

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
        prim = &g_PrimBuf[self->primIndex];
        self->posX.i.hi = PLAYER.posX.i.hi;
        self->posY.i.hi = PLAYER.posY.i.hi - 0x20;
        quarterSelfY = self->posY.i.hi / 4;
        xCoord = self->posX.i.hi;
        yCoord = 0;
        for (i = 0; i < 4; i++) {
            prim->tpage = 0x1A;
            prim->clut = 0x194;
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
            prim->u0 = prim->u2 = (rand() % 6) * 0x10 - 0x70;
            prim->u1 = prim->u3 = prim->u0 + 0x10;
            if (rand() & 1) {
                prim->v0 = prim->v1 = 0xD0;
                prim->v2 = prim->v3 = 0xE0;
            } else {
                prim->v0 = prim->v1 = 0xE0;
                prim->v2 = prim->v3 = 0xD0;
            }
            prim->priority = 0xC2;
            prim->drawMode = 0x200 | DRAW_HIDE;
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
        if (++self->ext.aguneaCrash.unk7C >= 4) {
            self->ext.aguneaCrash.unk7C = 0;
            self->step++;
        }
        break;
    case 2:
        prim = &g_PrimBuf[self->primIndex];
        for (i = 0; i < self->ext.aguneaCrash.unk7C; i++) {
            prim = prim->next;
        }
        if (self->ext.aguneaCrash.unk7C == 0) {
            prim->drawMode = DRAW_UNK_200 | DRAW_TPAGE2 | DRAW_TPAGE |
                             DRAW_COLORS | DRAW_TRANSP;
            prim->tpage = 0x1A;
            prim->clut = 0x19F;
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
        if (++self->ext.aguneaCrash.unk7C >= 4) {
            // think this loop has to count down since we assign to i
            for (i = LIGHTNING_COUNT - 1; i >= 0; i--) {
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
        if (++self->ext.aguneaCrash.unk7C >= LIGHTNING_COUNT) {
            self->hitboxHeight = self->hitboxWidth = 0x80;
            self->ext.aguneaCrash.unk7C = 0;
            self->step++;
        }
        break;
    case 4:
        if (++self->ext.aguneaCrash.unk7C >= LIGHTNING_COUNT + 1) {
            self->step++;
        }
        break;
    case 5:
        self->ext.aguneaCrash.unk80 += 2;
        self->ext.aguneaCrash.unk82 -= 10;
        if (self->ext.aguneaCrash.unk82 <= 0) {
            self->hitboxHeight = self->hitboxWidth = 0;
            self->step++;
        }
        break;
    case 6:
        g_Player.unk4E = 1;
        DestroyEntity(self);
        return;
    }
    if (self->ext.aguneaCrash.unk7E != 0) {
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
    return;
}

void RicEntitySubwpnStopwatchCircle(Entity* self) {
    Primitive* prim;
    s16 temp_s0_4;
    s32 sine;
    s32 cosine;
    s32 i;
    s16 yCoord;
    s16 xCoord;

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
            prim->clut = 0x15F;
            prim->priority = self->zPriority = 0xC2;
            prim->drawMode = DRAW_UNK_400 | DRAW_TPAGE2 | DRAW_TPAGE |
                             DRAW_COLORS | DRAW_TRANSP;
            prim->u0 = ((rsin((s16)(i * 0x100)) << 5) >> 0xC) + 0x20;
            prim->v0 = -((rcos((s16)(i * 0x100)) << 5) >> 0xC) - 0x21;
            prim->u1 = ((rsin((s16)((i + 1) * 0x100)) << 5) >> 0xC) + 0x20;
            prim->v1 = -((rcos((s16)((i + 1) * 0x100)) << 5) >> 0xC) - 0x21;
            prim->v2 = prim->v3 = 0xE0;
            prim->u2 = prim->u3 = 0x20;
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
        if (++self->ext.et_stopwatchCircle.timer >= 0x1F) {
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
    return;
}

static u32 D_801758D0;
static Entity*
    D_801758D4[3]; // used by RicEntitySubwpnStopwatch, should never underflow
void RicEntitySubwpnStopwatch(Entity* self) {
    Primitive* prim;
    s16 firstmult;
    s16 secondmult;
    s16 var_a0;
    s16 var_a1;
    Entity* parent;
    s32 sine;
    s32 cosine;
    s32 var_s4;
    s32 var_s6;
    s32 ySub;
    s16 temp_v0;

    s32 temp_t1;
    s32 temp_a3;
    s32 temp_t2;
    s32 temp_a0_6;
    s32 temp_a2_3;
    s32 temp_a1_3;
    s32 temp_t0;
    s32 temp_v1_11;
    if (g_unkGraphicsStruct.unk0) {
        g_unkGraphicsStruct.D_800973FC = 0;
        if ((self->step > 0) && (self->step < 4)) {
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
        if (self->params & 0xFF00) {
            RicCreateEntFactoryFromEntity(self, BP_66, 0);
            D_801758D0 = self->ext.et_801719A4.unk94 = self->params >> 8;
            if (self->ext.et_801719A4.unk94 < 4) {
                D_801758D4[self->ext.et_801719A4.unk94 - 1] = self;
            }
            if (self->ext.et_801719A4.unk94 >= 2) {
                self->ext.et_801719A4.unk98 =
                    D_801758D4[self->ext.et_801719A4.unk94 - 2];
            }
        } else {
            RicCreateEntFactoryFromEntity(self, BP_STOPWATCH_RIPPLE, 0);
            self->ext.et_801719A4.unk94 = 0;
        }
        self->ext.et_801719A4.subweaponId = PL_W_STOPWATCH;
        RicSetSubweaponParams(self);
        g_api.PlaySfx(0x6AD);
        if (self->ext.et_801719A4.unk94 < 2) {
            g_unkGraphicsStruct.D_800973FC = 1;
        }
        self->step++;
        break;
    case 1:
        prim = &g_PrimBuf[self->primIndex];
        prim->drawMode &= ~DRAW_HIDE;
        self->ext.et_801719A4.unk84.val += 0x18000;
        if (self->ext.et_801719A4.unk84.val > 0x19FFFF) {
            self->step++;
        }
        break;
    case 2:
        self->ext.et_801719A4.unk84.val += 0xFFFF0000;
        if (self->ext.et_801719A4.unk84.val <= 0x100000) {
            self->ext.et_801719A4.unk7C = 5;
            g_api.PlaySfx(0x6A1);
            self->step++;
        }
        break;
    case 3:
        if (++self->ext.et_801719A4.unk7E >= 0x51) {
            g_api.PlaySfx(0x6A1);
            self->ext.et_801719A4.unk7E = 0;
            self->ext.et_801719A4.unk90 = 1;
            if (--self->ext.et_801719A4.unk7C < 0) {
                self->step++;
                break;
            }
        }

        if (self->ext.et_801719A4.unk7C < 5) {
            prim = g_PrimBuf[self->primIndex].next;
            if (self->ext.et_801719A4.unk7C >= 10) {
                self->ext.et_801719A4.unk92 = 1;
                // MISMATCH: Not using S4 for this
                var_s4 = 8 * (self->ext.et_801719A4.unk7C / 10);
                prim->u0 = prim->u2 = var_s4 + 0x18;
                prim->u1 = prim->u3 = var_s4 + 0x1E;
                prim->v0 = prim->v1 = 0x40;
                prim->v2 = prim->v3 = 0x49;
                prim->drawMode &= ~DRAW_HIDE;
                prim = prim->next;
            } else {
                self->ext.et_801719A4.unk92 = 0;
            }
            var_s4 = 8 * (self->ext.et_801719A4.unk7C % 10);
            if (var_s4 == 0) {
                var_s4 = 0x50;
            }
            prim->u0 = prim->u2 = var_s4 + 0x18;
            prim->u1 = prim->u3 = var_s4 + 0x1E;
            prim->v0 = prim->v1 = 0x40;
            prim->v2 = prim->v3 = 0x49;
            prim->drawMode &= ~DRAW_HIDE;
        }
        break;
    case 4:
        prim = &g_PrimBuf[self->primIndex];
        self->flags &= ~FLAG_POS_PLAYER_LOCKED;
        prim->priority = 0xC2;
        prim->drawMode &= ~DRAW_UNK_200;
        prim = prim->next;
        prim->drawMode |= DRAW_HIDE;
        prim = prim->next;
        prim->drawMode |= DRAW_HIDE;
        self->posX.i.hi += self->facingLeft ? 6 : -6;
        ySub = self->ext.et_801719A4.unk84.i.hi;
        self->posY.i.hi -= ySub;
        self->ext.et_801719A4.unk7C = 0;
        if (self->ext.et_801719A4.unk94 != 0) {
            self->step = 7;
            RicCreateEntFactoryFromEntity(self, BP_AGUNEA_THUNDER, 0);
        } else {
            self->step++;
        }
        break;
    case 5:
        if (++self->ext.et_801719A4.unk7C >= 4) {
            prim = &g_PrimBuf[self->primIndex];
            prim->clut = 0x15F;
            prim->g0 = prim->g1 = prim->g2 = prim->g3 = prim->r0 = prim->r1 =
                prim->r2 = prim->r3 = 0x40;
            prim->b0 = prim->b1 = prim->b2 = prim->b3 = 0x60;
            prim->drawMode |= DRAW_COLORS;
            g_api.PlaySfx(0x6A4);
            self->step++;
        }
        break;
    case 6:
        if (++self->ext.et_801719A4.unk7C >= 0xF) {
            RicCreateEntFactoryFromEntity(self, FACTORY(BP_EMBERS, 7), 0);
            self->step++;
        }
        break;
    case 7:
        if ((self->ext.et_801719A4.unk94 == 0) ||
            (self->ext.et_801719A4.unk94 == D_801758D0)) {
            g_unkGraphicsStruct.D_800973FC = 0;
        }
        if (self->ext.et_801719A4.unk94 != 0) {
            D_801758D4[self->ext.et_801719A4.unk94 - 1] = 0;
        }
        DestroyEntity(self);
        return;
    }
    if (self->step == 0) {
        return;
    }
    prim = &g_PrimBuf[self->primIndex];
    if (self->step < 5) {
        if (self->ext.et_801719A4.unk94 < 2) {
            var_s4 = PLAYER.posX.val + (PLAYER.facingLeft ? FIX(8) : FIX(-8));
            var_s6 = PLAYER.posY.val + FIX(-16);
        } else if (D_801758D4[self->ext.et_801719A4.unk94 - 2] != NULL) {
            var_s4 = self->ext.et_801719A4.unk98->posX.val +
                     (PLAYER.facingLeft ? FIX(16) : FIX(-16));
            var_s6 = self->ext.et_801719A4.unk98->posY.val + FIX(-16);
        } else {
            var_s4 = self->posX.val;
            var_s6 = self->posY.val;
        }
        self->posX.val += (var_s4 - self->posX.val) / 12;
        self->posY.val += (var_s6 - self->posY.val) / 4;
        if (self->ext.et_801719A4.unk94 < 2) {
            if (PLAYER.facingLeft != self->facingLeft) {
                if (abs(var_s4 - self->posX.val) < FIX(1)) {
                    self->facingLeft = PLAYER.facingLeft;
                } else if (!self->facingLeft) {
                    if (var_s4 < self->posX.val) {
                        self->facingLeft = PLAYER.facingLeft;
                    } else {
                        goto block_84;
                    }
                } else if (self->posX.val < var_s4) {
                    self->facingLeft = PLAYER.facingLeft;
                }
            }
        } else if (D_801758D4[self->ext.et_801719A4.unk94 - 2] != NULL) {
            parent = self->ext.et_801719A4.unk98;
            if (parent->facingLeft != self->facingLeft) {
                if (abs(var_s4 - self->posX.val) >= FIX(1)) {
                    if (!self->facingLeft) {
                        if (var_s4 < self->posX.val) {
                            self->facingLeft = parent->facingLeft;
                        } else {
                            goto block_84;
                        }
                    } else if (self->posX.val < var_s4) {
                        self->facingLeft = parent->facingLeft;
                    }
                } else {
                    self->facingLeft = parent->facingLeft;
                }
            }
        }
        if (self->facingLeft) {
            prim->u2 = 0x98;
            prim->u0 = 0x98;
            prim->u1 = prim->u3 = 0xA8;
        } else {
        block_84:
            prim->u2 = 0xA8;
            prim->u0 = 0xA8;
            prim->u1 = prim->u3 = 0x98;
        }
    }
    if (self->step < 3) {
        var_s4 = self->posX.i.hi + (self->facingLeft ? 6 : -6);
        var_s6 = self->posY.i.hi - self->ext.et_801719A4.unk84.i.hi;
        if (self->ext.et_801719A4.unk82 < 0x64) {
            self->ext.et_801719A4.unk82 += 4;
        }
        if (self->ext.et_801719A4.unk80 < 0x1000) {
            self->ext.et_801719A4.unk80 += 0x80;
        }
        firstmult = (self->ext.et_801719A4.unk82 * 8) / 100;
        secondmult = (self->ext.et_801719A4.unk82 * 0xC) / 100;
        sine = rsin(self->ext.et_801719A4.unk80);
        cosine = rcos(self->ext.et_801719A4.unk80);
        prim->x0 = var_s4 + ((cosine * -firstmult - sine * -secondmult) >> 0xC);
        prim->y0 = var_s6 + ((sine * -firstmult + cosine * -secondmult) >> 0xC);
        prim->x1 = var_s4 + ((cosine * firstmult - sine * -secondmult) >> 0xC);
        prim->y1 = var_s6 + ((sine * firstmult + cosine * -secondmult) >> 0xC);
        prim->x2 = var_s4 + ((cosine * -firstmult - sine * secondmult) >> 0xC);
        prim->x3 = var_s4 + ((cosine * firstmult - sine * secondmult) >> 0xC);
        prim->y2 = var_s6 + ((sine * -firstmult + cosine * secondmult) >> 0xC);
        prim->y3 = var_s6 + ((sine * firstmult + cosine * secondmult) >> 0xC);
    } else if (self->step < 5U) {
        if (self->ext.et_801719A4.unk84.val <= 0x100000) {
            if (self->ext.et_801719A4.unk90 != 0) {
                self->ext.et_801719A4.unk88 = (rand() % 0x40 + 0x200) * 0x100;
                self->ext.et_801719A4.unk90 = 0;
            } else {
                self->ext.et_801719A4.unk88 = (rand() % 0x80 + 0x100) * 0x100;
            }
            if (self->ext.et_801719A4.unk80 >= 0) {
                self->ext.et_801719A4.unk80 = -(rand() % 0x40 + 0x40);
            } else {
                self->ext.et_801719A4.unk80 = rand() % 0x40 + 0x40;
            }
        }
        self->ext.et_801719A4.unk84.val += self->ext.et_801719A4.unk88;
        self->ext.et_801719A4.unk88 -= 0x4000;
        var_s4 = self->posX.i.hi + (self->facingLeft ? 6 : -6);
        var_s6 = self->posY.i.hi - self->ext.et_801719A4.unk84.i.hi;
        sine = rsin(self->ext.et_801719A4.unk80);
        cosine = rcos(self->ext.et_801719A4.unk80);
        temp_t1 = cosine * 8;
        temp_a3 = -temp_t1;
        temp_t2 = sine * 0xC;
        temp_a0_6 = -temp_t2;
        temp_a2_3 = sine * 8;
        temp_a1_3 = -temp_a2_3;
        temp_t0 = cosine * 0xC;
        temp_v1_11 = -temp_t0;
        prim->x0 = var_s4 + ((temp_a3 - temp_a0_6) >> 0xC);
        prim->y0 = var_s6 + ((temp_a1_3 + temp_v1_11) >> 0xC);
        prim->x1 = var_s4 + ((temp_t1 - temp_a0_6) >> 0xC);
        prim->y1 = var_s6 + ((temp_a2_3 + temp_v1_11) >> 0xC);
        prim->x2 = var_s4 + ((temp_a3 - temp_t2) >> 0xC);
        prim->y2 = var_s6 + ((temp_a1_3 + temp_t0) >> 0xC);
        prim->x3 = var_s4 + ((temp_t1 - temp_t2) >> 0xC);
        prim->y3 = var_s6 + ((temp_a2_3 + temp_t0) >> 0xC);
    } else {
        temp_v0 = 8 - self->ext.et_801719A4.unk7C;
        var_a0 = temp_v0;
        if (temp_v0 <= 0) {
            var_a0 = 1;
        }
        var_a1 = ((self->ext.et_801719A4.unk7C << 0x10) >> 0xB) + 0xC;
        if (var_a1 >= 0x80) {
            var_a1 = 0x80;
        }
        prim->x0 = prim->x2 = self->posX.i.hi - var_a0;
        prim->x1 = prim->x3 = var_a0 + self->posX.i.hi;
        prim->y0 = prim->y1 = self->posY.i.hi - var_a1;
        prim->y2 = prim->y3 = var_a1 + self->posY.i.hi;
    }
    if (self->step < 4) {
        var_s6 = self->posY.i.hi - 0xE;
        if (self->ext.et_801719A4.unk92 != 0) {
            var_s4 = self->posX.i.hi + (self->facingLeft ? -10 : 4);
            prim = prim->next;
            if (self->ext.et_801719A4.unk7E < 8) {
                prim->x0 = prim->x2 =
                    var_s4 - (self->ext.et_801719A4.unk7E / 2);
                prim->x1 = prim->x3 =
                    var_s4 + (self->ext.et_801719A4.unk7E / 2);
                temp_t2 = 0xF;
                prim->y0 = prim->y1 =
                    var_s6 + (self->ext.et_801719A4.unk7E - temp_t2);
                prim->y2 = prim->y3 =
                    var_s6 - (self->ext.et_801719A4.unk7E - temp_t2);
            } else if (self->ext.et_801719A4.unk7E >= 0x44) {
                var_a0 = (0x4C - self->ext.et_801719A4.unk7E) / 2;
                if (var_a0 < 0) {
                    var_a0 = 0;
                }
                var_a1 = self->ext.et_801719A4.unk7E - 0x44;
                if (var_a1 >= 9) {
                    var_a1 = 8;
                }
                var_a1 += 8;
                prim->x0 = prim->x2 = var_s4 - var_a0;
                prim->x1 = prim->x3 = var_s4 + var_a0;
                prim->y0 = prim->y1 = var_s6 - var_a1;
                // FAKE horrible thing needed to match, secondmult should be
                // totally irrelevant here
                prim->y2 = prim->y3 = (secondmult = var_s6) + var_a1;
            } else {
                prim->x0 = prim->x2 = var_s4 - 4;
                prim->x1 = prim->x3 = var_s4 + 4;
                prim->y0 = prim->y1 = var_s6 - 8;
                prim->y2 = prim->y3 = var_s6 + 8;
            }
            var_s4 = self->posX.i.hi + (self->facingLeft ? -4 : 10);
            prim = prim->next;
            if (self->ext.et_801719A4.unk7E < 0xC) {
                var_a0 = (self->ext.et_801719A4.unk7E - 4) / 2;
                if (var_a0 < 0) {
                    var_a0 = 0;
                }
                var_a1 = 0xB - self->ext.et_801719A4.unk7E;
                if (var_a1 < 0) {
                    var_a1 = 0;
                }
                var_a1 += 8;
                prim->x0 = prim->x2 = var_s4 - var_a0;
                prim->x1 = prim->x3 = var_s4 + var_a0;
                prim->y0 = prim->y1 = var_s6 - var_a1;
                // FAKE horrible thing needed to match, secondmult should be
                // totally irrelevant here
                prim->y2 = prim->y3 = (secondmult = var_s6) + var_a1;
            } else if (self->ext.et_801719A4.unk7E < 0x48) {
                prim->x0 = prim->x2 = var_s4 - 4;
                prim->x1 = prim->x3 = var_s4 + 4;
                prim->y0 = prim->y1 = var_s6 - 8;
                prim->y2 = prim->y3 = var_s6 + 8;
            } else {
                prim->x0 = prim->x2 =
                    var_s4 - ((0x50 - self->ext.et_801719A4.unk7E) / 2);
                prim->x1 = prim->x3 =
                    var_s4 + ((0x50 - self->ext.et_801719A4.unk7E) / 2);
                temp_t2 = -0x40;
                prim->y0 = prim->y1 =
                    var_s6 - (self->ext.et_801719A4.unk7E + temp_t2);
                prim->y2 = prim->y3 =
                    var_s6 + (self->ext.et_801719A4.unk7E + temp_t2);
            }
        } else {
            var_s4 = self->posX.i.hi + (self->facingLeft ? -4 : 4);
            prim = prim->next;
            if (self->ext.et_801719A4.unk7E < 8) {
                prim->x0 = prim->x2 =
                    var_s4 - (self->ext.et_801719A4.unk7E / 2);
                prim->x1 = prim->x3 =
                    var_s4 + (self->ext.et_801719A4.unk7E / 2);
                temp_t2 = 0xF;
                prim->y0 = prim->y1 =
                    var_s6 + (self->ext.et_801719A4.unk7E - temp_t2);
                prim->y2 = prim->y3 =
                    var_s6 - (self->ext.et_801719A4.unk7E - temp_t2);
            } else if (self->ext.et_801719A4.unk7E >= 0x48) {
                prim->x0 = prim->x2 =
                    var_s4 - ((0x50 - self->ext.et_801719A4.unk7E) / 2);
                prim->x1 = prim->x3 =
                    var_s4 + ((0x50 - self->ext.et_801719A4.unk7E) / 2);
                temp_t2 = -0x40;
                prim->y0 = prim->y1 =
                    var_s6 - (self->ext.et_801719A4.unk7E + temp_t2);
                prim->y2 = prim->y3 =
                    var_s6 + (self->ext.et_801719A4.unk7E + temp_t2);
            } else {
                prim->x0 = prim->x2 = var_s4 - 5;
                prim->x1 = prim->x3 = var_s4 + 5;
                prim->y0 = prim->y1 = var_s6 - 8;
                prim->y2 = prim->y3 = var_s6 + 8;
            }
        }
    }
}

void RicEntitySubwpnBibleTrail(Entity* entity) {
    Primitive* prim;
    s32 ret;

    switch (entity->step) {
    case 0:
        ret = g_api.AllocPrimitives(PRIM_GT4, 1);
        entity->primIndex = ret;
        if (entity->primIndex == -1) {
            DestroyEntity(entity);
            return;
        }
        entity->flags =
            FLAG_UNK_20000 | FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_HAS_PRIMS;
        prim = &g_PrimBuf[entity->primIndex];
        prim->tpage = 0x1C;
        prim->clut = 0x19D;
        prim->u0 = prim->u2 = 0x20;
        prim->u1 = prim->u3 = 0x30;
        prim->v0 = prim->v1 = 0;
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
        if (++entity->ext.et_BibleSubwpn.unk7C > 5) {
            entity->step++;
        }
        entity->ext.et_BibleSubwpn.unk7E -= 8;
        break;
    case 2:
        DestroyEntity(entity);
        return;
    }
    prim = &g_PrimBuf[entity->primIndex];
    prim->r0 = prim->r1 = prim->r2 = prim->r3 = prim->g0 = prim->g1 = prim->g2 =
        prim->g3 = prim->b0 = prim->b1 = prim->b2 = prim->b3 =
            entity->ext.et_BibleSubwpn.unk7E;
}

void RicEntitySubwpnBible(Entity* self) {
    Primitive* prim;
    s16 left;
    s16 top;
    s16 bottom;
    s16 right;

    s32 sine;
    s32 cosine;
    s32 cos_s2;
    s32 sin_s3;
    s32 cos_s3;
    s32 sin_s2;

    s32 temp_a3;
    s32 temp_s2;
    s32 temp_s3;
    s32 temp_a1;

    s32 temp_v0;
    // Note: Not initialized in this function! will retain
    // value already held (due to being a saved register)
    s32 var_s4;

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
        self->ext.et_BibleSubwpn.unk84 = self->facingLeft ? 0x20 : -0x20;
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
        if (++self->ext.et_BibleSubwpn.unk7E >= 0x30) {
            self->step++;
        }
        break;
    case 3:
        if (++self->ext.et_BibleSubwpn.unk7C >= 0x12C) {
            self->flags &= ~FLAG_KEEP_ALIVE_OFFCAMERA;
            self->velocityX = self->facingLeft ? FIX(-12) : FIX(12);
            self->velocityY = FIX(-12);
            g_api.PlaySfx(0x6B2);
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
        sine = rsin(self->ext.et_BibleSubwpn.unk80);
        cosine = rcos(self->ext.et_BibleSubwpn.unk80);
        temp_s2 = (sine * self->ext.et_BibleSubwpn.unk7E) >> 0xC;
        temp_s3 = (cosine * self->ext.et_BibleSubwpn.unk7E) >> 0xC;
        cos_s2 = cosine * temp_s2;
        sin_s3 = sine * temp_s3;
        cos_s3 = cosine * temp_s3;
        temp_a1 = cos_s2 + sin_s3;
        sin_s2 = sine * temp_s2;
        temp_s2 = temp_a1 >> 0xC;
        temp_s3 = (cos_s3 - sin_s2) >> 0xC;
        sine = rsin(self->ext.et_BibleSubwpn.unk82);
        cosine = rcos(self->ext.et_BibleSubwpn.unk82);
        temp_a1 = ((cosine * temp_s2) + (sine * var_s4)) >> 0xC;
        temp_a3 = ((cosine * var_s4) - (sine * temp_s2)) >> 0xC;
        if (self->facingLeft) {
            temp_a3 = ((cosine * temp_a3) + (sine * temp_s3)) >> 0xC;
        } else {
            temp_a3 = ((cosine * temp_a3) - (sine * temp_s3)) >> 0xC;
        }

        self->ext.et_BibleSubwpn.unk80 += (self->facingLeft ? 0x80 : -0x80);
        self->ext.et_BibleSubwpn.unk80 &= 0xFFF;
        self->ext.et_BibleSubwpn.unk82 += self->ext.et_BibleSubwpn.unk84;
        if (abs(self->ext.et_BibleSubwpn.unk82) >= 0x200) {
            // temp_v0 needed because otherwise unk84 gets loaded with lhu
            // instead of lh
            temp_v0 = -self->ext.et_BibleSubwpn.unk84;
            self->ext.et_BibleSubwpn.unk84 = temp_v0;
        }
        self->posX.i.hi = PLAYER.posX.i.hi + temp_a1;
        self->posY.i.hi = PLAYER.posY.i.hi + temp_a3;
        self->zPriority = PLAYER.zPriority + (temp_s3 < 0 ? 2 : -2);
        break;
    case 2:
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        self->velocityY += FIX(-2);
        break;
    }
    if (self->ext.et_BibleSubwpn.unk86 != 0) {
        prim = &g_PrimBuf[self->primIndex];
        left = self->posX.i.hi - 8;
        right = self->posX.i.hi + 8;
        top = self->posY.i.hi - 12;
        bottom = self->posY.i.hi + 12;
        prim->x0 = prim->x2 = left;
        prim->x1 = prim->x3 = right;
        prim->y0 = prim->y1 = top;
        prim->y2 = prim->y3 = bottom;
        prim->priority = self->zPriority;
        RicCreateEntFactoryFromEntity(self, BP_BIBLE_TRAIL, 0);
        if (g_GameTimer % 10 == 0) {
            g_api.PlaySfx(BIBLE_SUBWPN_SWOOSH);
        }
    }
}
