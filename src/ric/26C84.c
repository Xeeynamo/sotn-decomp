#include "ric.h"

#include <animset.h>
#include <drawmode.h>

void func_80162C84(Entity* entity) {
    switch (entity->step) {
    case 0:
        entity->flags =
            0x100000 | FLAG_UNK_04000000 | FLAG_UNK_10000 | FLAG_UNK_08000000;
        entity->facingLeft = 1;
        entity->unk5A = 0x66;
        entity->zPriority = PLAYER.zPriority - 8;
        entity->palette = 0x8149;
        entity->animSet = ANIMSET_OVL(19);
        func_8015C920(&D_80154ED4);
        entity->velocityX = FIX(-1.75);
        entity->posY.i.hi = 0xBB;
        entity->posX.i.hi = 0x148;
        entity->ext.generic.unk7E.modeU16 = 0;
        entity->step++;
        break;

    case 1:
        if (entity->animFrameIdx == 0 && entity->animFrameDuration == 1) {
            g_api.PlaySfx(0x882);
        }
        if (entity->animFrameIdx == 4 && entity->animFrameDuration == 1) {
            g_api.PlaySfx(0x883);
        }

        entity->posX.val += entity->velocityX;
        if (((s16)entity->ext.generic.unk7E.modeU16 == 0) &&
            (entity->posX.i.hi < 256)) {
            g_api.PlaySfx(0x87D);
            entity->ext.generic.unk7E.modeU16++;
        }
        if (entity->posX.i.hi < 0xE0) {
            func_8015C920(&D_80154EF8);
            entity->velocityX = 0;
            entity->step++;
            CreateEntFactoryFromEntity(entity, FACTORY(0x400, 0), 0);
        }
        break;

    case 2:
        if (entity->animFrameIdx == 16) {
            g_api.PlaySfx(0x87E);
            entity->ext.generic.unk7C.s = 0x80;
            entity->step++;
        }
        break;

    case 3:
        entity->ext.generic.unk7C.s--;
        if ((entity->ext.generic.unk7C.s) == 0) {
            CreateEntFactoryFromEntity(entity, FACTORY(0, 30), 0);
            entity->step++;
        }
        break;

    case 4:
        break;
    }
}

const u32 rodataPadding_801569E4 = 0;

// same as DRA/func_8011BD48
bool func_80162E9C(Entity* entity) {
    s32 i = 16;
    s16 objId = entity->entityId;
    s16 params = entity->params;
    Entity* e;

    for (e = &g_Entities[i]; i < 64; i++, e++) {
        if ((objId == e->entityId) && (params == e->params) && (e != entity)) {
            return true;
        }
    }

    return false;
}

INCLUDE_ASM("ric/nonmatchings/26C84", func_80162EF8);

void func_801641A0(Entity* entity) {
    Primitive* prim;
    s16 primIndex;

    entity->posX.i.hi = PLAYER.posX.i.hi;
    entity->posY.i.hi = PLAYER.posY.i.hi - 8;
    switch (entity->step) {
    case 0:
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
        entity->primIndex = primIndex;
        if (primIndex != -1) {
            entity->ext.generic.unk7C.s = 16;
            entity->ext.generic.unk7E.modeU16 = 12;
            prim = &g_PrimBuf[entity->primIndex];
            prim->u0 = prim->u2 = 64;
            prim->v0 = prim->v1 = 192;
            prim->u1 = prim->u3 = 127;
            prim->v2 = prim->v3 = 255;
            prim->r0 = prim->g0 = prim->b0 = prim->r1 = prim->g1 = prim->b1 =
                prim->r2 = prim->g2 = prim->b2 = prim->r3 = prim->g3 =
                    prim->b3 = 128;
            prim->tpage = 0x1A;
            prim->clut = 0x160;
            prim->priority = PLAYER.zPriority + 8;
            prim->drawMode = 0x35;
            entity->flags = FLAG_UNK_40000 | FLAG_UNK_04000000 | FLAG_HAS_PRIMS;
            entity->step++;
            goto def;
        } else {
            DestroyEntity(entity);
            break;
        }

    case 1:
        entity->ext.generic.unk7C.s += 2;
        entity->ext.generic.unk7E.modeU16 += 2;
        if (entity->ext.generic.unk7C.s >= 57) {
            DestroyEntity(entity);
            break;
        }

    default:
    def:
        prim = &g_PrimBuf[entity->primIndex];
        prim->x0 = entity->posX.i.hi - entity->ext.generic.unk7C.s;
        prim->y0 = entity->posY.i.hi - entity->ext.generic.unk7E.modeU16;
        prim->x1 = entity->posX.i.hi + entity->ext.generic.unk7C.s;
        prim->y1 = entity->posY.i.hi - entity->ext.generic.unk7E.modeU16;
        prim->x2 = entity->posX.i.hi - entity->ext.generic.unk7C.s;
        prim->y2 = entity->posY.i.hi + entity->ext.generic.unk7E.modeU16;
        prim->x3 = entity->posX.i.hi + entity->ext.generic.unk7C.s;
        prim->y3 = entity->posY.i.hi + entity->ext.generic.unk7E.modeU16;
        if (prim->b3 >= 12) {
            prim->b3 += 244;
        }
        prim->r0 = prim->g0 = prim->b0 = prim->r1 = prim->g1 = prim->b1 =
            prim->r2 = prim->g2 = prim->b2 = prim->r3 = prim->g3 = prim->b3;
    }
}

// Entity ID # 34. Created by blueprints 36, 37, 38, 39.
// Only difference in those blueprints is the "unk5" member of the blueprint.
// When the factory is made, unk5 loads into ext.factory.unk9A. This appears
// to create a delay before the factory actually creates the child.
// So 36, 37, 38, 39 create this entity with delay of 0, 4, 8, or 12 frames.
// All 4 are used in func_8015B348. 36 alone (for instant child) is used
// when Richter does an item crash without a subweapon, in func_8015D678.
// Creates a large semi-transparent circle around Richter which shrinks inward.
void EntityShrinkingPowerUpRing(Entity* self) {
    s16 selfX;
    s16 selfY;
    s16 rScale;
    s16 gScale;
    s16 bScale;
    s16 gOffset;
    s16 bOffset;
    s16 sp38;
    Primitive* prim1;
    Primitive* prim2;
    s32 baseAngle;
    s32 i;
    s16* loadedParams;
    s32 constE0 = 0xE0;

    u32 upperparams = self->params & 0x7F00;

    loadedParams = &D_8015519C[upperparams >> 8];
    rScale = loadedParams[2];
    gScale = loadedParams[3];
    bScale = loadedParams[4];
    gOffset = loadedParams[0];
    bOffset = loadedParams[1];
    self->posX.i.hi = PLAYER.posX.i.hi;
    self->posY.i.hi = PLAYER.posY.i.hi;
    switch (self->step) {
    case 0:
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 32);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags = FLAG_UNK_04000000 | FLAG_HAS_PRIMS | FLAG_UNK_40000 |
                      FLAG_UNK_10000;
        prim2 = prim1 = &g_PrimBuf[self->primIndex];
        for (i = 0; i < 16; i++) {
            prim1 = prim1->next;
        }
        for (i = 0; i < 16; i++) {
            prim2->u0 = ((rcos((s16)(i << 8)) * 2) >> 8) + 0x20;
            prim2->v0 = -((rsin((s16)(i << 8)) * 2) >> 8) - 0x21;
            prim2->u1 = ((rcos((s16)(i + 1 << 8)) * 2) >> 8) + 0x20;
            prim2->v1 = -((rsin((s16)(i + 1 << 8)) * 2) >> 8) - 0x21;
            prim1->u2 = prim1->u3 = 0x20;
            prim1->v2 = prim1->v3 = 0xDF;
            prim2->u2 = prim1->u0 = (prim2->u0 + prim1->u2) / 2;
            prim2->v2 = prim1->v0 = (prim2->v0 + prim1->v2) / 2;
            prim2->u3 = prim1->u1 = (prim2->u1 + prim1->u3) / 2;
            prim2->v3 = prim1->v1 = (prim2->v1 + prim1->v3) / 2;
            prim1->tpage = prim2->tpage = 0x1A;
            prim1->clut = prim2->clut = 0x15F;
            prim1->priority = prim2->priority = PLAYER.zPriority + 2;
            prim1->drawMode = prim2->drawMode = 0x235;
            prim2 = prim2->next;
            prim1 = prim1->next;
        }
        self->ext.ricPowerRing.unk80 = self->ext.ricPowerRing.unk82 = 0x280;
        self->ext.ricPowerRing.unk84 = self->ext.ricPowerRing.unk86 = 0x240;
        self->ext.ricPowerRing.unk8A = loadedParams[5];
        self->ext.ricPowerRing.unk88 = 0xC0;
        self->step += 1;
        break;
    case 1:
        self->ext.ricPowerRing.unk7E += 0x40;
        self->ext.ricPowerRing.unk86 -= 10;
        if (self->ext.ricPowerRing.unk86 < 0) {
            self->ext.ricPowerRing.unk86 = 0;
            self->ext.ricPowerRing.unk7C = 0x20;
            self->step += 1;
        }
        self->ext.ricPowerRing.unk84 = self->ext.ricPowerRing.unk86;
        self->ext.ricPowerRing.unk82 -= 5;
        self->ext.ricPowerRing.unk80 -= 5;
        break;
    case 2:
        self->ext.ricPowerRing.unk7E += 0x40;
        self->ext.ricPowerRing.unk82 -= 3;
        self->ext.ricPowerRing.unk80 -= 6;
        if (--self->ext.ricPowerRing.unk7C == 0) {
            self->step += 1;
        }
        break;
    case 3:
        self->ext.ricPowerRing.unk7E = self->ext.ricPowerRing.unk7E + 0x40;
        self->ext.ricPowerRing.unk82 = self->ext.ricPowerRing.unk82 - 3;
        self->ext.ricPowerRing.unk80 = self->ext.ricPowerRing.unk80 - 6;
        self->ext.ricPowerRing.unk88 -= 12;
        if (self->ext.ricPowerRing.unk88 < 0) {
            DestroyEntity(self);
            return;
        }
        break;
    }
    sp38 = self->ext.ricPowerRing.unk8A;
    selfX = self->posX.i.hi;
    selfY = self->posY.i.hi;
    prim2 = prim1 = &g_PrimBuf[self->primIndex];
    for (i = 0; i < 16; i++) {
        prim1 = prim1->next;
    }
    for (i = 0; i < 16; i++) {
        prim2->x0 =
            selfX + ((prim2->u0 - 0x20) * self->ext.ricPowerRing.unk80) / 0x100;
        prim2->y0 =
            selfY +
            ((prim2->v0 - constE0) * self->ext.ricPowerRing.unk82) / 0x100;
        prim2->x1 =
            selfX + ((prim2->u1 - 0x20) * self->ext.ricPowerRing.unk80) / 0x100;
        prim2->y1 =
            selfY +
            ((prim2->v1 - constE0) * self->ext.ricPowerRing.unk82) / 0x100;
        prim1->x2 =
            selfX +
            (((rcos(i + 1 << 8) * 2) >> 8) * self->ext.ricPowerRing.unk84) /
                0x100;
        prim1->y2 =
            selfY -
            (((rsin(i + 1 << 8) * 2) >> 8) * self->ext.ricPowerRing.unk86) /
                0x100;
        prim1->x3 =
            selfX +
            (((rcos(i + 2 << 8) * 2) >> 8) * self->ext.ricPowerRing.unk84) /
                0x100;
        prim1->y3 =
            selfY -
            (((rsin(i + 2 << 8) * 2) >> 8) * self->ext.ricPowerRing.unk86) /
                0x100;
        prim2->x2 = prim1->x0 = (prim2->x0 + prim1->x2) / 2;
        prim2->y2 = prim1->y0 = (prim2->y0 + prim1->y2) / 2;
        prim2->x3 = prim1->x1 = (prim2->x1 + prim1->x3) / 2;
        prim2->y3 = prim1->y1 = (prim2->y1 + prim1->y3) / 2;
        baseAngle = i * sp38;
        prim1->r0 = prim2->r2 =
            (((rsin((s16)(baseAngle + self->ext.ricPowerRing.unk7E)) +
               0x1000) >>
              7) *
             self->ext.ricPowerRing.unk88) /
            rScale;
        prim1->g0 = prim2->g2 =
            (((rsin((
                   s16)(baseAngle + (gOffset + self->ext.ricPowerRing.unk7E))) +
               0x1000) >>
              7) *
             self->ext.ricPowerRing.unk88) /
            gScale;
        prim1->b0 = prim2->b2 =
            (((rsin((
                   s16)(baseAngle + (bOffset + self->ext.ricPowerRing.unk7E))) +
               0x1000) >>
              7) *
             self->ext.ricPowerRing.unk88) /
            bScale;
        prim1->r1 = prim2->r3 =
            (((rsin((s16)(baseAngle + (sp38 + self->ext.ricPowerRing.unk7E))) +
               0x1000) >>
              7) *
             self->ext.ricPowerRing.unk88) /
            rScale;
        prim1->g1 = prim2->g3 =
            (((rsin((s16)(baseAngle +
                          (sp38 + (gOffset + self->ext.ricPowerRing.unk7E)))) +
               0x1000) >>
              7) *
             self->ext.ricPowerRing.unk88) /
            gScale;
        prim1->b1 = prim2->b3 =
            (((rsin((s16)(baseAngle +
                          (sp38 + (bOffset + self->ext.ricPowerRing.unk7E)))) +
               0x1000) >>
              7) *
             self->ext.ricPowerRing.unk88) /
            bScale;
        prim1->r2 = prim1->g2 = prim1->b2 = prim1->r3 = prim1->g3 = prim1->b3 =
            prim2->r0 = prim2->g0 = prim2->b0 = prim2->r1 = prim2->g1 =
                prim2->b1 = 0;
        prim2 = prim2->next;
        prim1 = prim1->next;
    }
}

// Entity ID #40. Created by blueprint 47. That factory comes from
// RichterHandleDamage.

void EntityHitByIce(Entity* self) {
    s32 i;
    Primitive* prim;
    s16 angle;
    s32 xShift1;
    s32 xShift2;
    s32 xShift3;
    s32 yShift1;
    s32 yShift2;
    s32 yShift3;
    s32 size;
    u32 primYshift;
    u16 selfX;
    u16 selfY;
    Point16* offset;
    bool sp18 = false;

    self->posX.i.hi = PLAYER.posX.i.hi;
    self->posY.i.hi = PLAYER.posY.i.hi;
    // This is badly written but it checks if 0x10000 is unset.
    sp18 = ((g_Player.unk0C & 0x10000) == sp18);
    switch (self->step) {
    case 0:
        self->primIndex = g_api.AllocPrimitives(PRIM_GT3, 24);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }

        self->flags = FLAG_HAS_PRIMS | FLAG_UNK_40000 | FLAG_UNK_20000;
        prim = &g_PrimBuf[self->primIndex];
        while (prim != NULL) {
            prim->r0 = prim->r1 = prim->r2 = prim->r3 = (rand() & 0xF) + 0x30;
            prim->b0 = prim->b1 = prim->b2 = prim->b3 = rand() | 0x80;
            prim->g0 = prim->g1 = prim->g2 = prim->g3 = (rand() & 0x1F) + 0x30;
            if (rand() & 1) {
                prim->drawMode = 0x335;
            } else {
                prim->drawMode = 0x315;
            }
            prim->type = 3;
            prim->priority = PLAYER.zPriority + 2;
            prim = prim->next;
        }
        // Weird repeated conditional
        if (PLAYER.velocityY != 0) {
            self->ext.hitbyice.unk7E = 1;
        }
        if (PLAYER.velocityY != 0) {
            if (PLAYER.facingLeft == 0) {
                self->rotZ = -0x100;
            } else {
                self->rotZ = 0x100;
            }
        } else {
            if (PLAYER.velocityX <= 0) {
                self->rotZ = 0xF80;
            } else {
                self->rotZ = 0x80;
            }
        }
        if (PLAYER.step == 0x10) {
            if (PLAYER.facingLeft == 0) {
                self->rotZ = -0x180;
            } else {
                self->rotZ = 0x180;
            }
            self->ext.hitbyice.unk80 = 1;
            self->ext.hitbyice.unk82 = 0x3C;
            if (self->params & 0x7F00) {
                self->ext.hitbyice.unk82 = 0x14;
            }
            self->ext.hitbyice.unk7E = 0;
        }
        self->step++;
        break;
    case 1:
        if (PLAYER.step == 0x10) {
            if ((PLAYER.animCurFrame & 0x7FFF) == 0x21) {
                if (PLAYER.facingLeft == 0) {
                    self->rotZ = -0x280;
                } else {
                    self->rotZ = 0x280;
                }
            }
            if ((PLAYER.animCurFrame & 0x7FFF) == 0x22) {
                if (PLAYER.facingLeft == 0) {
                    self->rotZ = -0x380;
                } else {
                    self->rotZ = 0x380;
                }
            }
            if ((PLAYER.animCurFrame & 0x7FFF) == 0x20) {
                if (PLAYER.facingLeft == 0) {
                    self->rotZ = -0x180;
                } else {
                    self->rotZ = 0x180;
                }
            }
        }
        if (self->ext.hitbyice.unk80 != 0 && --self->ext.hitbyice.unk82 == 0) {
            sp18 = true;
        }
        if ((self->ext.hitbyice.unk7E != 0) && (g_Player.pl_vram_flag & 0xC)) {
            sp18 = true;
        }
        if (sp18) {
            self->ext.hitbyice.unk7C = 0x40;
            if (self->ext.hitbyice.unk80 != 0) {
                self->ext.hitbyice.unk7C = 0x80;
            }
            self->step++;
        }
        break;
    case 2:
        if (--self->ext.hitbyice.unk7C == 0) {
            DestroyEntity(self);
            return;
        }
        break;
    }

    selfX = self->posX.i.hi;
    selfY = self->posY.i.hi;
    prim = &g_PrimBuf[self->primIndex];
    for (i = 0; i < 24; i++) {
        offset = D_80155244[i * 3];
        if (prim->u0 < 2) {
            size = SquareRoot12(
                ((offset->x * offset->x) + (offset->y * offset->y)) << 0xC);
            angle = self->rotZ + ratan2(offset->y, offset->x);
            xShift1 = (((rcos(angle) >> 4) * size) + 0x80000) >> 0x14;
            yShift1 = (((rsin(angle) >> 4) * size) + 0x80000) >> 0x14;
            prim->x0 = selfX + xShift1;
            prim->y0 = selfY + yShift1;

            offset = D_80155244[i * 3 + 1];
            size = SquareRoot12(
                ((offset->x * offset->x) + (offset->y * offset->y)) << 0xC);
            angle = self->rotZ + ratan2(offset->y, offset->x);
            xShift2 = (((rcos(angle) >> 4) * size) + 0x80000) >> 0x14;
            yShift2 = (((rsin(angle) >> 4) * size) + 0x80000) >> 0x14;
            prim->x1 = selfX + xShift2;
            prim->y1 = selfY + yShift2;

            offset = D_80155244[i * 3 + 2];
            size = SquareRoot12(
                ((offset->x * offset->x) + (offset->y * offset->y)) << 0xC);
            angle = self->rotZ + ratan2(offset->y, offset->x);
            xShift3 = (((rcos(angle) >> 4) * size) + 0x80000) >> 0x14;
            yShift3 = (((rsin(angle) >> 4) * size) + 0x80000) >> 0x14;
            prim->x2 = prim->x3 = selfX + xShift3;
            prim->y2 = prim->y3 = selfY + yShift3;
        }
        if ((prim->u0 == 0) && (sp18 != 0)) {
            prim->u0++;
            prim->v0 = (rand() & 15) + 1;
            if (self->ext.hitbyice.unk80 != 0) {
                prim->v0 = (rand() % 60) + 1;
            }
        }
        if (prim->u0 == 1) {
            if (--prim->v0 == 0) {
                prim->v0 = 0x20;
                prim->u2 = 0xF0;
                prim->u0++;
                if (self->ext.hitbyice.unk80 != 0) {
                    prim->v0 = (rand() & 31) + 0x28;
                }
            }
        }
        if (prim->u0 == 2) {
            if ((prim->u2 < 0x70) || (prim->u2 > 0xD0)) {
                prim->u2 += 4;
            }
            primYshift = (s8)prim->u2 >> 4;
            if (self->ext.hitbyice.unk80 != 0) {
                primYshift /= 2;
            }
            prim->y0 = primYshift + prim->y0;
            prim->y1 = primYshift + prim->y1;
            prim->y2 = primYshift + prim->y2;
            prim->y3 = primYshift + prim->y3;
            if (prim->r3 < 4) {
                prim->r3 -= 4;
            }
            if (prim->g3 < 4) {
                prim->g3 -= 4;
            }
            if (prim->b3 < 4) {
                prim->b3 -= 4;
            }
            prim->r0 = prim->r1 = prim->r2 = prim->r3;
            prim->b0 = prim->b1 = prim->b2 = prim->b3;
            prim->g0 = prim->g1 = prim->g2 = prim->g3;
            prim->drawMode |= 2;
            prim->drawMode &= ~0x300;
            if (--prim->v0 == 0) {
                prim->drawMode |= 8;
            }
        }
        prim = prim->next;
    }
}

void EntityHitByLightning(Entity* self) {
    Primitive* prevPrim;
    Primitive* prim;
    s16 temp_s0;
    s32 temp_s2;
    s16 xBase;
    s16 yBase;

    s16 tempAngle;
    s32 i;
    s16 temp_s1_2;
    s32 xOffset;
    s32 yOffset;
    bool var_s0 = false;

    if ((self->params & 0xFF00) == 0x100) {
        var_s0 = (++self->ext.hitbylightning.unk9C) > 0xA8;
    } else if ((self->params & 0xFF00) == 0x200) {
        if (++self->ext.hitbylightning.unk9C >= 0x91) {
            var_s0 = true;
        }
    } else if (PLAYER.step != 10) {
        var_s0 = true;
    }
    switch (self->step) {
    case 0:
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 6);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }

        self->flags = FLAG_UNK_08000000 | FLAG_HAS_PRIMS | FLAG_UNK_20000;
        self->ext.hitbylightning.unk7C =
            ((self->params & 0xF) << 9) + (rand() & 0x3F);
        self->ext.hitbylightning.unk80 = rand();
        self->ext.hitbylightning.unk82 = (rand() & 0x1FF) + 0x100;
        prim = &g_PrimBuf[self->primIndex];
        while (prim != NULL) {
            prim->x0 = prim->x1 = prim->x2 = prim->x3 = self->posX.i.hi;
            prim->y0 = prim->y1 = prim->y2 = prim->y3 = self->posY.i.hi;
            prim->tpage = 0x1A;
            prim->clut = D_80155364[rand() & 1];
            prim->priority = PLAYER.zPriority - 2;
            prim->r0 = prim->g0 = prim->b0 = prim->r1 = prim->g1 = prim->b1 =
                prim->r2 = prim->g2 = prim->b2 = prim->r3 = prim->g3 =
                    prim->b3 = 0x80;
            prim->drawMode = 0x133;
            prim = prim->next;
        }
        if ((PLAYER.velocityY != 0) && (PLAYER.step != 0x10)) {
            self->ext.hitbylightning.unk92 = 1;
        }
        self->ext.hitbylightning.unk94 = 0x10;
        self->step++;
        break;
    case 1:
        self->ext.hitbylightning.unk7C =
            ((self->params & 0xF) << 9) + (rand() & 0x1FF);
        temp_s2 = rsin(self->ext.hitbylightning.unk80);
        self->ext.hitbylightning.unk80 += self->ext.hitbylightning.unk82;
        xOffset = ((rcos(self->ext.hitbylightning.unk7C) * temp_s2) >> 7) * 12;
        yOffset =
            ((rsin(self->ext.hitbylightning.unk7C) * temp_s2) >> 7) * -7 << 1;
        self->posX.val = xOffset + PLAYER.posX.val;
        self->posY.val = yOffset + PLAYER.posY.val;
        if ((self->ext.hitbylightning.unk92 != 0) &&
            (g_Player.pl_vram_flag & 0xE)) {
            var_s0 = true;
        }
        if (var_s0) {
            self->ext.hitbylightning.unk90 = (rand() & 0xF) + 0x10;
            self->step++;
        }
        break;
    case 2:
        if (--self->ext.hitbylightning.unk90 == 0) {
            DestroyEntity(self);
            return;
        }
        if (self->ext.hitbylightning.unk94 > 0) {
            self->ext.hitbylightning.unk94--;
        }
        self->ext.hitbylightning.unk7C =
            ((self->params & 0xF) << 9) + (rand() & 0xFF);
        temp_s2 = rsin(self->ext.hitbylightning.unk80);
        self->ext.hitbylightning.unk80 += self->ext.hitbylightning.unk82;
        xOffset = (((rcos(self->ext.hitbylightning.unk7C) * temp_s2) >> 7) *
                   ((rand() % 8) + 8));
        yOffset = (-((rsin(self->ext.hitbylightning.unk7C) * temp_s2) >> 7) *
                   ((rand() % 8) + 0xA)) +
                  self->ext.generic.unk98;
        self->posX.val = xOffset + PLAYER.posX.val;
        self->posY.val = yOffset + PLAYER.posY.val;
        self->ext.generic.unk98 -= 0x8000;

        break;
    }

    xBase = (self->posX.i.hi + (rand() & 7)) - 4;
    yBase = (self->posY.i.hi + (rand() & 0x1F)) - 0x18;
    temp_s1_2 = self->ext.hitbylightning.unk94;
    temp_s1_2 = (temp_s1_2 * rsin(self->ext.hitbylightning.unk80)) >> 0xC;
    prim = &g_PrimBuf[self->primIndex];
    for (i = 0; i < 5; i++) {
        prevPrim = prim;
        prim = prim->next;
        *prevPrim = *prim;
        prevPrim->next = prim;
        prevPrim->u0 = prevPrim->u2 = (i * 0x10) - 0x70;
        prevPrim->u1 = prevPrim->u3 = ((i + 1) * 0x10) - 0x70;
        prevPrim->v0 = prevPrim->v1 = 0xC0;
        prevPrim->v2 = prevPrim->v3 = 0xCF;
    }
    prim->x0 = prim->x1;
    prim->y0 = prim->y1;
    prim->x2 = prim->x3;
    prim->y2 = prim->y3;
    temp_s0 = self->ext.hitbylightning.unk7C + 0x400;
    prim->x1 = xBase + (((rcos(temp_s0) >> 4) * temp_s1_2) >> 8);
    prim->y1 = yBase - (((rsin(temp_s0) >> 4) * temp_s1_2) >> 8);
    temp_s0 = self->ext.hitbylightning.unk7C - 0x400;
    prim->x3 = xBase + (((rcos(temp_s0) >> 4) * temp_s1_2) >> 8);
    prim->y3 = yBase - (((rsin(temp_s0) >> 4) * temp_s1_2) >> 8);

    // FAKE: Annoying repeat of the access and bitmask
    tempAngle = self->ext.hitbylightning.unk80 & 0xFFF;
    if (((tempAngle) >= 0x400) &&
        ((self->ext.hitbylightning.unk80 & 0xFFF) < 0xC00)) {
        prim->priority = PLAYER.zPriority - 2;
    } else {
        prim->priority = PLAYER.zPriority + 2;
    }
    prim->u0 = prim->u2 = (i << 4) - 0x70;
    prim->v0 = prim->v1 = 0xC0;
    // FAKE but needed to duplicate the sll 4 instruction
    tempAngle = i;
    prim->u1 = prim->u3 = (tempAngle << 4) - 0x60;
    prim->v2 = prim->v3 = 0xCF;
}

// Corresponding DRA function is func_80124164
void func_80165DD8(
    POLY_GT4* poly, s32 colorIntensity, s32 y, s32 radius, bool arg4) {
    s16 top = y - radius;
    s16 bottom = y + radius;
    s32 colorChannel;

    poly->y0 = poly->y1 = top;
    poly->y2 = poly->y3 = bottom;

    if (poly->y0 < 0) {
        poly->y0 = poly->y1 = 0;
    }

    if (poly->y0 > 240) {
        poly->y2 = poly->y3 = 240;
    }

    if (arg4 == 0) {
        colorChannel = colorIntensity * D_80155368[0];
        if (colorChannel < 0) {
            colorChannel += 255;
        }
        poly->r1 = poly->r3 = (u32)colorChannel >> 8;

        colorChannel = colorIntensity * D_80155368[1];
        if (colorChannel < 0) {
            colorChannel += 255;
        }
        poly->g1 = poly->g3 = (u32)colorChannel >> 8;

        colorChannel = colorIntensity * D_80155368[2];
        if (colorChannel < 0) {
            colorChannel += 255;
        }
        poly->b1 = poly->b3 = (u32)colorChannel >> 8;

        colorChannel = colorIntensity * D_80155368[3];
        if (colorChannel < 0) {
            colorChannel += 255;
        }
        poly->r0 = poly->r2 = (u32)colorChannel >> 8;

        colorChannel = colorIntensity * D_80155368[4];
        if (colorChannel < 0) {
            colorChannel += 255;
        }
        poly->g0 = poly->g2 = (u32)colorChannel >> 8;

        colorChannel = colorIntensity * D_80155368[5];
    } else {
        colorChannel = colorIntensity * D_80155368[0];
        if (colorChannel < 0) {
            colorChannel += 255;
        }
        poly->r1 = poly->r3 = (u32)colorChannel >> 8;

        colorChannel = colorIntensity * D_80155368[1];
        if (colorChannel < 0) {
            colorChannel += 255;
        }
        poly->g1 = poly->g3 = (u32)colorChannel >> 8;

        colorChannel = colorIntensity * D_80155368[2];
        if (colorChannel < 0) {
            colorChannel += 255;
        }
        poly->b1 = poly->b3 = (u32)colorChannel >> 8;

        colorChannel = colorIntensity * D_80155368[6];
        if (colorChannel < 0) {
            colorChannel += 255;
        }
        poly->r0 = poly->r2 = (u32)colorChannel >> 8;

        colorChannel = colorIntensity * D_80155368[7];
        if (colorChannel < 0) {
            colorChannel += 255;
        }
        poly->g0 = poly->g2 = (u32)colorChannel >> 8;
        colorChannel = colorIntensity * D_80155368[8];
    }
    if (colorChannel < 0) {
        colorChannel += 255;
    }
    poly->b0 = poly->b2 = (u32)colorChannel >> 8;
}

void func_80166024() {
    PLAYER.palette = 0x815E;
    PLAYER.drawMode = 0x70;
}

void func_80166044() {
    PLAYER.palette = 0x8120;
    PLAYER.drawMode = DRAW_DEFAULT;
}
