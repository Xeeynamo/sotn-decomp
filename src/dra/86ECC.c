#include "dra.h"
#include "objects.h"
#include "sfx.h"

void EntityHellfireHandler(Entity* self) {
    Primitive* prim;
    u16 selfPosX;
    s16 selfPosY;
    // These are probably adjustable variables but for now we don't
    // know what they are for so we just name them for their values
    s16 sixteen = 16;
    s16 four = 4;

    if (PLAYER.step != Player_SpellHellfire) {
        DestroyEntity(self);
        return;
    }
    // It should be possible to do FntPrint("light_timer:%02x\n", ...
    // but I seem to get rogue 00 bytes when compiling that
    FntPrint(&aLightTimer02x, self->ext.hellfireHandler.unk80);
    self->posX.i.hi = PLAYER.posX.i.hi;
    selfPosX = self->posX.i.hi;
    switch (self->step) {
    case 0:
        g_Player.unk5C = 0;
        self->primIndex = AllocPrimitives(PRIM_GT4, 1);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            g_Player.unk5C = -1;
            return;
        }
        self->flags = FLAG_UNK_04000000 | FLAG_HAS_PRIMS | FLAG_UNK_40000 |
                      FLAG_UNK_20000;
        self->posY.i.hi = 120;
        // I think this is to make the yellow laser beam?
        // it ends up looking like the library card effect.
        LoadImage(&D_800B0788, &D_800B06C8);
        LoadImage(&D_800B0790, &D_800B0728);
        prim = &g_PrimBuf[self->primIndex];
        prim->v0 = prim->v1 = prim->v2 = prim->v3 = 0xF8;
        prim->u0 = prim->u2 = 1;
        prim->u1 = prim->u3 = 0x30;
        prim->b3 = 0x80;
        prim->tpage = 0x11C;
        prim->blendMode = 0x331;
        prim->priority = self->zPriority = 0x1C0;
        PlaySfx(NA_SE_PL_WARP);
        self->step++;
        break;
    case 1:
        self->ext.hellfireHandler.unk7E += sixteen;
        if (self->ext.hellfireHandler.unk7E >= 0x80) {
            self->step++;
        }
        break;
    case 2:
        self->ext.hellfireHandler.unk7C += four;
        if (self->ext.hellfireHandler.unk7C >= 0x16) {
            self->ext.hellfireHandler.unk80 = 0x20;
            self->step++;
        }
        break;
    case 3:
        if (--self->ext.hellfireHandler.unk80 == 0) {
            PLAYER.palette = 0x810D;
            self->step++;
        }
        break;
    case 4:
        PLAYER.palette = 0x810D;
        self->ext.hellfireHandler.unk7C -= four * 2;
        if (self->ext.hellfireHandler.unk7C < 0) {
            self->ext.hellfireHandler.unk80 = 0x2A;
            self->step++;
            prim = &g_PrimBuf[self->primIndex];
            prim->blendMode |= 8;
            g_Player.unk5C = 1;
        }
        break;
    case 5:
        PLAYER.palette = 0x810D;
        if (self->ext.hellfireHandler.unk80 == 0x10) {
            CreateEntFactoryFromEntity(self, FACTORY(0, 38), 0);
        }
        if (--self->ext.hellfireHandler.unk80 == 0) {
            self->ext.hellfireHandler.unk7C = 0;
            self->step++;
            prim = &g_PrimBuf[self->primIndex];
            prim->blendMode &= ~BLEND_VISIBLE;
        }
        if (self->ext.hellfireHandler.unk80 == 2) {
            g_Player.unk5C = 2;
        }
        break;
    case 6:
        PLAYER.palette = 0x8100;
        self->ext.hellfireHandler.unk7C += four;
        if (self->ext.hellfireHandler.unk7C >= 0x16) {
            self->ext.hellfireHandler.unk80 = 0x60;
            self->step++;
        }
        break;
    case 7:
        if (self->ext.hellfireHandler.unk80 == 0x50) {
            g_Player.unk5C = 3;
        }
        if (self->ext.hellfireHandler.unk80 == 0x30) {
            // When you press up during hellfire, you get different fireballs.
            if (g_Player.padPressed & PAD_UP) {
                CreateEntFactoryFromEntity(self, FACTORY(0, 35), 0);
            } else {
                CreateEntFactoryFromEntity(self, FACTORY(0, 34), 0);
            }
        }
        if (self->ext.hellfireHandler.unk80 == 0x50) {
            CreateEntFactoryFromEntity(self, FACTORY(0xA00, 4), 0);
        }
        if (self->ext.hellfireHandler.unk80 < 0x48) {
            self->ext.hellfireHandler.unk7C -= four;
            if (self->ext.hellfireHandler.unk7C < 0) {
                self->ext.hellfireHandler.unk7C = 0;
            }
        }
        if (--self->ext.hellfireHandler.unk80 == 0x28) {
            DestroyEntity(self);
            return;
        }
        break;
    }

    self->posY.i.hi = 0x78;
    selfPosY = 0x78;
    prim = &g_PrimBuf[self->primIndex];
    if (g_GameTimer & 1) {
        prim->v0 = prim->v1 = prim->v2 = prim->v3 = 0xF8;
    } else {
        prim->v0 = prim->v1 = prim->v2 = prim->v3 = 0xFC;
    }
    prim->x0 = prim->x2 = selfPosX - self->ext.hellfireHandler.unk7C;
    prim->y1 = prim->y0 = selfPosY - self->ext.hellfireHandler.unk7E;
    prim->x1 = prim->x3 = selfPosX + self->ext.hellfireHandler.unk7C;
    prim->y2 = prim->y3 = selfPosY + self->ext.hellfireHandler.unk7E;
    if (self->step == 3) {
        if (prim->b3 < 0xF8) {
            prim->b3 += 4;
        }
        prim->r0 = prim->r1 = prim->r2 = prim->r3 = prim->g0 = prim->g1 =
            prim->g2 = prim->g3 = prim->b0 = prim->b1 = prim->b2 = prim->b3;
    }
    if (self->step == 7) {
        if (prim->b3 >= 0x21) {
            prim->b3 -= 0x20;
        }
        prim->r0 = prim->r1 = prim->r2 = prim->r3 = prim->g0 = prim->g1 =
            prim->g2 = prim->g3 = prim->b0 = prim->b1 = prim->b2 = prim->b3;
    }
    return;
}

void func_801274DC(Entity* entity) {
    switch (entity->step) {
    case 0:
        if (entity->params == 0) {
            PlaySfx(0x660);
        }
        entity->flags = FLAG_UNK_100000 | FLAG_UNK_08000000;
        entity->animSet = ANIMSET_DRA(9);
        entity->unk4C = &D_800B0798;
        entity->zPriority = PLAYER.zPriority + 2;
        entity->facingLeft = (PLAYER.facingLeft + 1) & 1;
        SetSpeedX(D_800B0830[entity->params]);
        entity->velocityY = D_800B083C[entity->params];
        entity->ext.generic.unk7C.s = 0x14;
        func_8011A328(entity, 2);
        entity->hitboxWidth = 4;
        entity->hitboxHeight = 4;
        entity->step++;
        break;

    case 1:
        if (entity->hitFlags == 0) {
            entity->ext.generic.unk7C.s--;
            if ((entity->ext.generic.unk7C.s) == 0) {
                entity->step++;
            }
            entity->posX.val += entity->velocityX;
            entity->posY.val += entity->velocityY;
            break;
        }
        DestroyEntity(entity);
        break;

    case 2:
        if (entity->hitFlags != 0) {
            DestroyEntity(entity);
            break;
        }
        entity->posX.val += entity->velocityX;
        break;
    }
}

// Entity ID 45. Created by factory blueprint 81.
// That blueprint is used in ControlBatForm, when step_s is 4.
// Also, when bat familiar shoots a fireball, the blueprint
// is used in func_80172C30.

void EntityBatFireball(Entity* self) {
    // This is a 1 when a bat familiar is shooting, and a 0
    // when the player (in bat form) is shooting the fireball.
    // Appears to have no impact on the behavior of this function.
    s8 params = (self->params >> 8) & 0x7F;

    switch (self->step) {
    case 0:
        PlaySfx(NA_SE_PL_BT_FIREBALL);
        self->flags = FLAG_UNK_08000000 | FLAG_UNK_100000;
        self->animSet = 9;
        self->unk4C = D_800B0798;
        self->zPriority = PLAYER.zPriority - 2;

        // Wow, this is weird logic! But it's in the assembly.
        if (params == 0) {
            self->facingLeft = (PLAYER.facingLeft + 1) & 1;
        }
        self->facingLeft = (PLAYER.facingLeft + 1) & 1;

        SetSpeedX(FIX(-3.5));
        self->drawFlags = 3;
        // Initial fireball size is 0x40 by 0x40
        self->rotX = self->rotY = 0x40;
        self->posX.val += self->velocityX * 2;
        self->posY.i.hi -= 4;
        func_8011A328(self, 9);
        self->hitboxWidth = 4;
        self->hitboxHeight = 8;
        g_Player.D_80072F14 = 4;
        self->step++;
        break;
    case 1:
        // Once the fireball hits something, destroy it.
        if (self->hitFlags != 0) {
            DestroyEntity(self);
            return;
        }
        self->posX.val += self->velocityX;
        // Much like the wing smash, these rot values are actually the size.
        // After shooting, the fireballs grow until they are 0x100 in size
        self->rotX += 0x10;
        self->rotY += 0x10;
        if (self->rotY >= 0x101) {
            self->rotY = 0x100;
        }
        if (self->rotX >= 0x181) {
            self->rotX = 0x180;
        }
    }
    return;
}

void func_80127840(Entity* entity) {
    switch (entity->step) {
    case 0:
        if (entity->params != 0) {
            PlaySfx(0x683);
        }

        entity->flags = FLAG_UNK_100000 | FLAG_UNK_08000000;

        if (entity->params != 0) {
            entity->posY.i.hi = entity->posY.i.hi + 16;
        } else {
            entity->posY.i.hi = entity->posY.i.hi - 4;
        }

        entity->animSet = ANIMSET_DRA(9);
        entity->rotZ = 0;
        entity->unk4C = &D_800B07C8;
        entity->drawFlags |= FLAG_DRAW_ROTZ;
        entity->zPriority = PLAYER.zPriority + 2;
        entity->facingLeft = (PLAYER.facingLeft + 1) & 1;
        SetSpeedX(-0x10);
        func_8011A328(entity, 2);
        entity->hitboxWidth = 8;
        entity->hitboxHeight = 8;
        entity->step++;
        break;

    case 1:
        if (entity->animFrameIdx >= 23) {
            if (!(g_GameTimer & 3)) {
                entity->rotZ += 0x400;
            }
            if (entity->velocityX < 0) {
                entity->velocityX -= FIX(0.09375);
            } else {
                entity->velocityX += FIX(0.09375);
            }
            if (!(g_GameTimer & 1) && (rand() & 1)) {
                CreateEntFactoryFromEntity(entity, FACTORY(0x100, 36), 0);
            }
            entity->posX.val += entity->velocityX;
            entity->posY.val += entity->velocityY;
        }
        break;
    }
}

// circle expands out of player
void EntityExpandingCircle(Entity* entity) {
    POLY_GT4* poly;
    s32 primIndex;

    if (PLAYER.facingLeft == 0) {
        entity->posX.i.hi = PLAYER.posX.i.hi - 10;
    } else {
        entity->posX.i.hi = PLAYER.posX.i.hi + 10;
    }
    entity->posY.i.hi = PLAYER.posY.i.hi + 2;

    switch (entity->step) {
    case 0:
        primIndex = AllocPrimitives(PRIM_GT4, 1);
        entity->primIndex = primIndex;
        if (primIndex != -1) {
            entity->ext.generic.unk7C.s = 22;
            entity->ext.generic.unk7E.modeU16 = 26;
            poly = &g_PrimBuf[entity->primIndex];
            poly->u2 = 64;
            poly->u3 = 127;
            poly->u1 = 127;
            poly->v1 = 192;
            poly->v0 = 192;
            poly->v3 = 255;
            poly->v2 = 255;
            poly->r3 = 128;
            poly->r2 = 128;
            poly->r1 = 128;
            poly->r0 = 128;
            poly->g3 = 128;
            poly->g2 = 128;
            poly->g1 = 128;
            poly->g0 = 128;
            poly->u0 = 64;
            poly->b3 = 64;
            poly->b2 = 64;
            poly->b1 = 64;
            poly->b0 = 64;
            poly->tpage = 0x1A;
            poly->clut = 0x15F;
            poly->pad2 = PLAYER.zPriority + 1;
            poly->pad3 = 0x35;
            entity->flags = FLAG_UNK_40000 | FLAG_UNK_04000000 | FLAG_HAS_PRIMS;
            entity->step++;
            break;
        }
        DestroyEntity(entity);
        return;

    case 1:
        entity->ext.generic.unk7C.s += 2;
        entity->ext.generic.unk7E.modeU16 += 2;
        if (entity->ext.generic.unk7C.s >= 0x39) {
            DestroyEntity(entity);
            return;
        }
        break;

    default:
        break;
    }

    poly = &g_PrimBuf[entity->primIndex];
    poly->x0 = entity->posX.i.hi - entity->ext.generic.unk7C.s;
    poly->y0 = entity->posY.i.hi - entity->ext.generic.unk7E.modeU16;
    poly->x1 = entity->posX.i.hi + entity->ext.generic.unk7C.s;
    poly->y1 = entity->posY.i.hi - entity->ext.generic.unk7E.modeU16;
    poly->x2 = entity->posX.i.hi - entity->ext.generic.unk7C.s;
    poly->y2 = entity->posY.i.hi + entity->ext.generic.unk7E.modeU16;
    poly->x3 = entity->posX.i.hi + entity->ext.generic.unk7C.s;
    poly->y3 = entity->posY.i.hi + entity->ext.generic.unk7E.modeU16;

    if (entity->ext.generic.unk7C.s >= 0x29) {
        poly->r3 += 244;
        poly->g3 += 244;
        poly->b3 += 250;
        poly->r0 = poly->r1 = poly->r2 = poly->r3;
        poly->g0 = poly->g1 = poly->g2 = poly->g3;
        poly->b0 = poly->b1 = poly->b2 = poly->b3;
    }
}

void func_80127CC8(Entity* entity) {
    POLY_GT4* poly;
    s32 ret;

    if (PLAYER.step != 34) {
        DestroyEntity(entity);
        return;
    }

    entity->posX.i.hi = PLAYER.posX.i.hi;

    switch (entity->step) {
    case 0:
        ret = AllocPrimitives(PRIM_G4, 1);
        entity->primIndex = ret;

        if (ret == -1) {
            DestroyEntity(entity);
            g_Player.unk5C = 0xFFFF;
            return;
        }

        entity->flags = FLAG_UNK_20000 | FLAG_UNK_40000 | FLAG_UNK_04000000 |
                        FLAG_HAS_PRIMS;
        poly = &g_PrimBuf[entity->primIndex];
        poly->r3 = 192;
        poly->r2 = 192;
        poly->r1 = 192;
        poly->r0 = 192;
        poly->g3 = 64;
        poly->g2 = 64;
        poly->g1 = 64;
        poly->g0 = 64;
        poly->b3 = 64;
        poly->b2 = 64;
        poly->b1 = 64;
        poly->b0 = 64;
        poly->pad3 = 0x315;
        entity->zPriority = 0x1C0;
        poly->pad2 = 0x1C0;
        entity->step++;
        break;

    case 1:
        if (entity->ext.generic.unk7C.s++ >= 0xE) {
            DestroyEntity(entity);
            return;
        }

    default:
        break;
    }
    poly = &g_PrimBuf[entity->primIndex];
    poly->x0 = poly->x2 = entity->posX.i.hi - 3;
    poly->y0 = 0;
    poly->y1 = 0;
    poly->x1 = poly->x3 = entity->posX.i.hi + 3;
    poly->y3 = 240;
    poly->y2 = 240;

    if (g_GameTimer & 1) {
        poly->pad3 = poly->pad3 | 8;
    } else {
        poly->pad3 = poly->pad3 & 0xFFF7;
    }
}

// These are a pair of helper functions used for the rebound stone rebounding.
// No clear reason why the first one puts the first line outside the
// if statement.

void ReboundStoneBounce1(s16 bounceAngle) {
    g_CurrentEntity->ext.reboundStone.stoneAngle =
        (bounceAngle * 2) - g_CurrentEntity->ext.reboundStone.stoneAngle;
    if (g_CurrentEntity->ext.reboundStone.unk82 == 0) {
        g_CurrentEntity->ext.reboundStone.unk80++;
        g_CurrentEntity->ext.reboundStone.unk82++;
    }
}

void ReboundStoneBounce2(s16 bounceAngle) {
    if (g_CurrentEntity->ext.reboundStone.unk82 == 0) {
        g_CurrentEntity->ext.reboundStone.stoneAngle =
            (bounceAngle * 2) - g_CurrentEntity->ext.reboundStone.stoneAngle;
        g_CurrentEntity->ext.reboundStone.unk80++;
        g_CurrentEntity->ext.reboundStone.unk82++;
    }
}
// Entity ID 20. Created by blueprint 24. This comes from BlueprintNum for
// the rebound stone SubweaponDef.
void EntitySubwpnReboundStone(Entity* self) {
    Collider collider;
    u16 playerX;
    u16 playerY;
    Primitive* prim;
    s32 colliderFlags;
    s32 i;
    s32 deltaX;
    s32 deltaY;
    s32 currX;
    s32 currY;

    s32 speed = 0x400;
    s32 facingLeft;

    self->ext.reboundStone.unk82 = 0;
    playerX = self->posX.i.hi;
    playerY = self->posY.i.hi;

    switch (self->step) {
    case 0:
        self->primIndex = AllocPrimitives(PRIM_LINE_G2, 16);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }

        for (i = 0, prim = &g_PrimBuf[self->primIndex]; prim != NULL;
             prim = prim->next, i++) {
            prim->r0 = prim->g0 = prim->b0 = prim->r1 = prim->g1 = prim->b1 =
                0xFF;
            prim->priority = PLAYER.zPriority + 2;
            prim->blendMode = 0x33;
            if (i != 0) {
                prim->blendMode |= BLEND_VISIBLE;
            }
            prim->x0 = prim->x1 = playerX;
            prim->y0 = prim->y1 = playerY;
            LOH(prim->u3) = 0x14;
        }
        self->flags = FLAG_UNK_08000000 | FLAG_UNK_04000000 | FLAG_HAS_PRIMS;
        self->zPriority = PLAYER.zPriority + 2;

        facingLeft = PLAYER.facingLeft;
        self->ext.reboundStone.stoneAngle = facingLeft == 0 ? 0xE80 : 0x980;
        self->ext.reboundStone.stoneAngle += (rand() & 0x7F) - 0x40;

        self->ext.reboundStone.lifeTimer = 0x40;
        func_8011A290(self);
        self->hitboxWidth = 4;
        self->hitboxHeight = 4;
        g_Player.D_80072F14 = 4;
        CheckCollision(self->posX.i.hi, self->posY.i.hi, &collider, 0);
        if (collider.effects & EFFECT_SOLID) {
            self->ext.reboundStone.unk84 = 4;
        }
        self->step += 1;
        PlaySfx(SUBWPN_THROW);
        break;

    case 1:
        deltaX = rcos(self->ext.reboundStone.stoneAngle) * 0x10;
        deltaY = -rsin(self->ext.reboundStone.stoneAngle) * 0x10;
        currX = self->posX.val;
        currY = self->posY.val;
        if (self->ext.reboundStone.unk84 == 0) {
            for (i = 0; i < 6; i++) {
                CheckCollision(
                    FIX_TO_I(currX), FIX_TO_I(currY + deltaY), &collider, 0);
                if (collider.effects & EFFECT_SOLID) {
                    colliderFlags =
                        collider.effects &
                        (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_2000 |
                         EFFECT_UNK_1000 | EFFECT_UNK_0800);
                    if (deltaY > 0) {
                        if ((colliderFlags == 0) ||
                            (collider.effects & EFFECT_UNK_0800)) {
                            ReboundStoneBounce1(0x800);
                        }
                        if (colliderFlags == EFFECT_UNK_8000) {
                            ReboundStoneBounce2(0x200);
                        }
                        if (colliderFlags ==
                            EFFECT_UNK_8000 + EFFECT_UNK_1000) {
                            ReboundStoneBounce2(0x12E);
                        }
                        if (colliderFlags ==
                            EFFECT_UNK_8000 + EFFECT_UNK_2000) {
                            ReboundStoneBounce2(0xA0);
                        }
                        if (colliderFlags ==
                            EFFECT_UNK_8000 + EFFECT_UNK_4000) {
                            ReboundStoneBounce2(0x600);
                        }
                        if (colliderFlags == EFFECT_UNK_8000 + EFFECT_UNK_4000 +
                                                 EFFECT_UNK_1000) {
                            ReboundStoneBounce2(0x6D2);
                        }
                        if (colliderFlags == EFFECT_UNK_8000 + EFFECT_UNK_4000 +
                                                 EFFECT_UNK_2000) {
                            ReboundStoneBounce2(0x760);
                        }
                    }
                    if (deltaY < 0) {
                        if ((colliderFlags == 0) ||
                            (colliderFlags & EFFECT_UNK_8000)) {
                            ReboundStoneBounce1(0x800);
                        }
                        if (colliderFlags == EFFECT_UNK_0800) {
                            ReboundStoneBounce2(0xE00);
                        }
                        if (colliderFlags ==
                            EFFECT_UNK_0800 + EFFECT_UNK_1000) {
                            ReboundStoneBounce2(0xED2);
                        }
                        if (colliderFlags ==
                            EFFECT_UNK_0800 + EFFECT_UNK_2000) {
                            ReboundStoneBounce2(0xF60);
                        }
                        if (colliderFlags ==
                            EFFECT_UNK_0800 + EFFECT_UNK_4000) {
                            ReboundStoneBounce2(0xA00);
                        }
                        if (colliderFlags == EFFECT_UNK_0800 + EFFECT_UNK_4000 +
                                                 EFFECT_UNK_1000) {
                            ReboundStoneBounce2(0x92E);
                        }
                        if (colliderFlags == EFFECT_UNK_0800 + EFFECT_UNK_4000 +
                                                 EFFECT_UNK_2000) {
                            ReboundStoneBounce2(0x8A0);
                        }
                    }
                }
                CheckCollision(
                    FIX_TO_I(currX + deltaX), FIX_TO_I(currY), &collider, 0);
                if (collider.effects & EFFECT_SOLID) {
                    colliderFlags =
                        collider.effects &
                        (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_2000 |
                         EFFECT_UNK_1000 | EFFECT_UNK_0800);
                    // Cases when traveling right
                    if (deltaX > 0) {
                        if ((colliderFlags == 0) ||
                            TEST_BITS(collider.effects, 0x4800) ||
                            TEST_BITS(collider.effects, 0xC000)) {
                            ReboundStoneBounce1(0x400);
                        }
                        if (colliderFlags == EFFECT_UNK_0800) {
                            ReboundStoneBounce2(0xE00);
                        }
                        if (colliderFlags ==
                            EFFECT_UNK_0800 + EFFECT_UNK_1000) {
                            ReboundStoneBounce2(0xED2);
                        }
                        if (colliderFlags ==
                            EFFECT_UNK_0800 + EFFECT_UNK_2000) {
                            ReboundStoneBounce2(0xF60);
                        }
                        if (colliderFlags == EFFECT_UNK_8000) {
                            ReboundStoneBounce2(0x200);
                        }
                        if (colliderFlags ==
                            EFFECT_UNK_8000 + EFFECT_UNK_1000) {
                            ReboundStoneBounce2(0x12E);
                        }
                        if (colliderFlags ==
                            EFFECT_UNK_8000 + EFFECT_UNK_2000) {
                            ReboundStoneBounce2(0xA0);
                        }
                    }
                    // Cases when traveling left
                    if (deltaX < 0) {
                        if ((colliderFlags == 0) ||
                            ((colliderFlags & 0x4800) == 0x800) ||
                            ((colliderFlags & 0xC000) == 0x8000)) {
                            ReboundStoneBounce1(0x400);
                        }
                        if (colliderFlags ==
                            EFFECT_UNK_0800 + EFFECT_UNK_4000) {
                            ReboundStoneBounce2(0xA00);
                        }
                        if (colliderFlags == EFFECT_UNK_0800 + EFFECT_UNK_4000 +
                                                 EFFECT_UNK_1000) {
                            ReboundStoneBounce2(0x92E);
                        }
                        if (colliderFlags == EFFECT_UNK_0800 + EFFECT_UNK_4000 +
                                                 EFFECT_UNK_2000) {
                            ReboundStoneBounce2(0x8A0);
                        }
                        if (colliderFlags ==
                            EFFECT_UNK_8000 + EFFECT_UNK_4000) {
                            ReboundStoneBounce2(0x600);
                        }
                        if (colliderFlags == EFFECT_UNK_8000 + EFFECT_UNK_4000 +
                                                 EFFECT_UNK_1000) {
                            ReboundStoneBounce2(0x6D2);
                        }
                        if (colliderFlags == EFFECT_UNK_8000 + EFFECT_UNK_4000 +
                                                 EFFECT_UNK_2000) {
                            ReboundStoneBounce2(0x760);
                        }
                    }
                }
                currX += deltaX;
                if (self->ext.reboundStone.unk82 != 0) {
                    goto block_93;
                }
                currY += deltaY;
            }
        } else {
            self->ext.reboundStone.unk84--;
        }
        if (self->ext.reboundStone.unk82 != 0) {
        block_93:
            CreateEntFactoryFromEntity(self, FACTORY(0, 10), 0);
            PlaySfx(REBOUND_STONE_BOUNCE);
        }
        if (self->posX.i.hi < -0x40 || self->posX.i.hi > 0x140 ||
            self->posY.i.hi < -0x40 || self->posY.i.hi > 0x140 ||
            self->ext.reboundStone.unk80 == 15) {
            self->step = 2;
        } else {
            deltaX =
                ((rcos(self->ext.reboundStone.stoneAngle) << 4) * speed) >> 8;
            self->posX.val += deltaX;
            deltaY =
                -((rsin(self->ext.reboundStone.stoneAngle) << 4) * speed) >> 8;
            self->posY.val += deltaY;
        }
        break;
    case 2:
        if (--self->ext.reboundStone.lifeTimer == 0) {
            DestroyEntity(self);
            return;
        }
        if (self->ext.reboundStone.lifeTimer == 0x20) {
            self->hitboxState = 0;
        }
        prim = &g_PrimBuf[self->primIndex];
        while (prim != NULL) {
            LOH(prim->u3) = 0;
            prim = prim->next;
        }
        break;
    }

    i = 0;
    prim = &g_PrimBuf[self->primIndex];
    colliderFlags = self->step == 2 ? 4 : 2; // reused var, not colliderFlags
    // cleaner to use previous 3 lines than to put them in the for's initializer
    for (; prim != NULL; i++, prim = prim->next) {
        if (self->ext.reboundStone.unk82 != 0) {
            if (i == self->ext.reboundStone.unk80) {
                prim->x0 = playerX;
                prim->y0 = playerY;
                prim->blendMode &= ~BLEND_VISIBLE;
                // unusual nesting of the same condition
                if (i == self->ext.reboundStone.unk80) {
                    prim->x1 = self->posX.i.hi;
                    prim->y1 = self->posY.i.hi;
                }
            }
        } else if (i == self->ext.reboundStone.unk80) {
            prim->x1 = self->posX.i.hi;
            prim->y1 = self->posY.i.hi;
        }
        if (!(prim->blendMode & BLEND_VISIBLE)) {
            if (LOH(prim->u3) != 0) {
                LOH(prim->u3)--;
            } else {
                // again not colliderFlags, seems to control stone fading
                if (colliderFlags < prim->b1) {
                    prim->b1 -= colliderFlags;
                }
                prim->r0 = prim->g0 = prim->b0 = prim->r1 = prim->g1 = prim->b1;
            }
        }
    }
}

// ash thrown when using vibhuti subweapon
void EntitySubwpnThrownVibhuti(Entity* self) {
    Collider collider;
    FakePrim* fakeprim;
    s16 fakeprimY;
    s16 collisionOffsetX;
    s16 randomAngle;
    s16 randomVelocity;
    s32 i;
    u16 selfX;
    u16 selfY;

    switch (self->step) {
    case 0:
        self->primIndex = func_800EDB58(PRIM_TILE_ALT, 13);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags = FLAG_UNK_08000000 | FLAG_HAS_PRIMS;
        func_8011A290(self);
        selfX = self->posX.i.hi;
        selfY = self->posY.i.hi;
        self->hitboxWidth = self->hitboxHeight = 4;
        self->ext.vibhuti.timer = 0x80;
        fakeprim = (FakePrim*)&g_PrimBuf[self->primIndex];
        fakeprimY = selfY - 8;
        while (1) {
            fakeprim->blendMode = 2;
            fakeprim->priority = PLAYER.zPriority + 2;
            if (fakeprim->next == NULL) {
                fakeprim->y0 = fakeprim->x0 = fakeprim->w = 0;
                fakeprim->blendMode &= ~BLEND_VISIBLE;
                break;
            }
            fakeprim->posX.i.hi = selfX;
            fakeprim->posY.i.hi = fakeprimY;
            fakeprim->posX.i.lo = fakeprim->posY.i.lo = 0;
            randomAngle = (rand() & 0xFF) + 0x100;
            randomVelocity = (rand() & 0xFF) + 0x80;
            fakeprim->velocityX.val =
                ((rcos(randomAngle) << 4) * randomVelocity >> 9) + FIX(0.5);
            fakeprim->velocityY.val =
                -((rsin(randomAngle) << 4) * randomVelocity >> 9);
            fakeprim->velocityX.val = (fakeprim->velocityX.val * 3) >> 1;
            if (self->facingLeft) {
                fakeprim->velocityX.val = -fakeprim->velocityX.val;
            }
            fakeprim->delay = 1;
            fakeprim->posY.i.hi -= 4;
            fakeprim->b0 = fakeprim->g0 = fakeprim->r0 = 0xFF;
            fakeprim->h = fakeprim->w = 2;
            fakeprim->x0 = fakeprim->posX.i.hi;
            fakeprim->y0 = fakeprim->posY.i.hi;
            fakeprim = fakeprim->next;
        }
        PlaySfx(SUBWPN_THROW);
        g_Player.D_80072F14 = 4;
        self->step++;
        break;
    case 1:
        if (self->facingLeft) {
            collisionOffsetX = -2;
        } else {
            collisionOffsetX = 2;
        }

        if (--self->ext.vibhuti.timer == 0) {
            DestroyEntity(self);
            return;
        }
        fakeprim = (FakePrim*)&g_PrimBuf[self->primIndex];
        i = 0;
        while (1) {
            if (fakeprim->next == NULL) {
                fakeprim->y0 = fakeprim->x0 = fakeprim->w = 0;
                fakeprim->blendMode &= ~BLEND_VISIBLE;
                break;
            }
            fakeprim->posX.i.hi = fakeprim->x0;
            fakeprim->posY.i.hi = fakeprim->y0;
            if (fakeprim->delay != 0) {
                if (fakeprim->velocityX.val != 0) {
                    fakeprim->posX.val += fakeprim->velocityX.val;
                    CheckCollision(fakeprim->posX.i.hi + collisionOffsetX,
                                   fakeprim->posY.i.hi, &collider, 0);
                    if (collider.effects & EFFECT_UNK_0002) {
                        fakeprim->velocityX.val = 0;
                    }
                }
                fakeprim->posY.val += fakeprim->velocityY.val;
                fakeprim->velocityY.val += FIX(12.0 / 128);
                if (fakeprim->velocityY.val > FIX(4)) {
                    fakeprim->velocityY.val = FIX(4);
                }
                if (fakeprim->velocityY.val > 0) {
                    CheckCollision(
                        fakeprim->posX.i.hi, fakeprim->posY.i.hi, &collider, 0);
                    if (collider.effects & EFFECT_SOLID) {
                        fakeprim->delay = 0;
                        fakeprim->posY.i.hi =
                            fakeprim->posY.i.hi + collider.unk18 - (i % 3 + 1);
                        fakeprim->w = fakeprim->h = 3;
                    }
                }
            }
            if ((self->ext.vibhuti.timer & 7) == i) {
                self->posX.i.hi = fakeprim->posX.i.hi;
                self->posY.i.hi = fakeprim->posY.i.hi;
                if (fakeprim->blendMode & BLEND_VISIBLE) {
                    self->hitboxHeight = 0;
                    self->hitboxWidth = 0;
                } else {
                    self->hitboxWidth = self->hitboxHeight = 4;
                }
                if (fakeprim->delay != 0) {
                    self->hitboxOffY = 0;
                } else {
                    self->hitboxOffY = -6;
                }
            }
            if ((self->hitFlags != 0) &&
                (((self->ext.vibhuti.timer + 1) & 7) == i)) {
                fakeprim->blendMode = BLEND_VISIBLE;
            }
            if ((self->ext.vibhuti.timer - 1) == i) {
                fakeprim->blendMode = BLEND_VISIBLE;
            }
            fakeprim->x0 = fakeprim->posX.i.hi;
            fakeprim->y0 = fakeprim->posY.i.hi;
            fakeprim = fakeprim->next;
            i++;
        }
        self->hitFlags = 0;
        break;
    }
}

s32 func_80128BBC(Unkstruct_80128BBC* arg0, u8 value) {
    u8 ret = 0;
    s32 i;
    s32 j;
    Unkstruct_80128BBC_Sub* temp = arg0->unk04;

    for (i = 0; i < 4; i++, temp++) {
        for (j = 0; j < 3; j++) {
            temp->unk00[j] -= value;

            if (temp->unk00[j] < 16) {
                temp->unk00[j] = 16;
            } else {
                ret |= 1;
            }
        }
    }
    return ret;
}

INCLUDE_ASM("dra/nonmatchings/86ECC", func_80128C2C);

INCLUDE_ASM("dra/nonmatchings/86ECC", func_801291C4);

INCLUDE_ASM("dra/nonmatchings/86ECC", func_80129864);

// opens hole in backround and spirit comes out (ID 0x40)
INCLUDE_ASM("dra/nonmatchings/86ECC", EntitySummonSpirit);

// expanding circle effect when activating stopwatch
INCLUDE_ASM("dra/nonmatchings/86ECC", EntityStopWatchExpandingCircle);

// stopwatch subweapon effect. stops enemies (Dra Entity 0x2A)
INCLUDE_ASM("dra/nonmatchings/86ECC", EntityStopWatch);

void func_8012B78C(Entity* entity) {
    POLY_GT4* poly;
    s32 ret;

    switch (entity->step) {
    case 0:
        ret = AllocPrimitives(PRIM_GT4, 1);
        entity->primIndex = ret;
        if (entity->primIndex != -1) {
            entity->flags = FLAG_UNK_20000 | FLAG_UNK_04000000 | FLAG_HAS_PRIMS;
            poly = &g_PrimBuf[entity->primIndex];
            poly->tpage = 0x1C;
            poly->clut = 0x19D;
            poly->u2 = 32;
            poly->u0 = 32;
            poly->u3 = 48;
            poly->u1 = 48;
            poly->v1 = 0;
            poly->v0 = 0;
            poly->v3 = 16;
            poly->v2 = 16;
            poly->x0 = poly->x2 = entity->posX.i.hi - 8;
            poly->x1 = poly->x3 = entity->posX.i.hi + 8;
            poly->y0 = poly->y1 = entity->posY.i.hi - 8;
            poly->y2 = poly->y3 = entity->posY.i.hi + 8;
            poly->pad2 = entity->zPriority;
            poly->pad3 = 0x115;
            entity->ext.generic.unk7E.modeU16 = 96;
            entity->step++;
        } else {
            DestroyEntity(entity);
            return;
        }
        break;

    case 1:
        if (++entity->ext.generic.unk7C.s > 5) {
            entity->step++;
        }
        entity->ext.generic.unk7E.modeU16 -= 8;
        break;

    case 2:
        DestroyEntity(entity);
        return;

    default:
        break;
    }
    poly = &g_PrimBuf[entity->primIndex];
    poly->r0 = poly->r1 = poly->r2 = poly->r3 = poly->g0 = poly->g1 = poly->g2 =
        poly->g3 = poly->b0 = poly->b1 = poly->b2 = poly->b3 =
            entity->ext.generic.unk7E.modeU8.unk0;
}

// book rotates around player
void EntitySubwpnBible(Entity* self) {
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

    s32 var_s4;

    switch (self->step) {
    case 0:
        self->primIndex = AllocPrimitives(PRIM_GT4, 1);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags = FLAG_UNK_04000000 | FLAG_HAS_PRIMS | FLAG_UNK_20000;
        prim = &g_PrimBuf[self->primIndex];
        prim->tpage = 0x1E;
        prim->clut = 0x17F;
        prim->u0 = prim->u2 = 0x98;
        prim->v0 = prim->v1 = 0xD8;
        prim->u1 = prim->u3 = 0xA8;
        prim->v2 = prim->v3 = 0xF0;
        prim->priority = PLAYER.zPriority + 1;
        prim->blendMode = 0x108;
        self->ext.et_BibleSubwpn.unk84 = self->facingLeft ? 0x20 : -0x20;
        func_8011A290(self);
        self->hitboxWidth = 6;
        self->hitboxHeight = 6;
        self->step++;
        break;
    case 1:
        prim = &g_PrimBuf[self->primIndex];
        prim->blendMode &= ~BLEND_VISIBLE;
        self->ext.et_BibleSubwpn.unk86++;
        g_Player.D_80072F14 = 4;
        self->step++;
    case 2:
        self->ext.et_BibleSubwpn.unk7C++;
        if (++self->ext.et_BibleSubwpn.unk7E >= 0x30) {
            self->step++;
        }
        break;
    case 3:
        if (++self->ext.et_BibleSubwpn.unk7C >= 0x12C) {
            self->flags &= ~FLAG_UNK_04000000;
            self->velocityX = self->facingLeft ? FIX(-12) : FIX(12);
            self->velocityY = FIX(-12);
            PlaySfx(0x6B2);
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
        if (self->facingLeft != 0) {
            temp_a3 = ((cosine * temp_a3) + (sine * temp_s3)) >> 0xC;
        } else {
            temp_a3 = ((cosine * temp_a3) - (sine * temp_s3)) >> 0xC;
        }

        self->ext.et_BibleSubwpn.unk80 += (self->facingLeft ? 0x80 : -0x80);
        self->ext.et_BibleSubwpn.unk80 &= 0xFFF;
        self->ext.et_BibleSubwpn.unk82 += self->ext.et_BibleSubwpn.unk84;
        if (ABS(self->ext.et_BibleSubwpn.unk82) >= 0x200) {
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
        CreateEntFactoryFromEntity(self, 0x4F, 0);
        if (g_GameTimer % 10 == 0) {
            PlaySfx(BIBLE_SUBWPN_SWOOSH);
        }
    }
}

// echo of bat effect
INCLUDE_ASM("dra/nonmatchings/86ECC", EntityBatEcho);

INCLUDE_ASM("dra/nonmatchings/86ECC", func_8012C600);

bool WolfFormFinished(void) {
    if (PLAYER.step_s == 0) {
        return false;
    }
    if (PLAYER.step_s == 8) {
        return false;
    }
    if (D_80097448[1] != 0 && !IsRelicActive(RELIC_HOLY_SYMBOL) ||
        g_Player.padTapped & PAD_R2 ||
        HandleTransformationMP(FORM_WOLF, REDUCE) < 0) {
        SetPlayerStep(Player_Unk25);
        func_8010DA48(0xCA);
        D_800AFDA6[0] = 1;
        PLAYER.palette = 0x810D;
        g_Player.unk66 = 0;
        g_Player.unk68 = 0;
        CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0x2400, 44), 0);
        PLAYER.velocityY >>= 1;
        return true;
    }
    return false;
}

void func_8012C97C(void) {
    if (g_Entities[PLAYER_CHARACTER].step_s == 0) {
        return;
    }
    if (g_Entities[PLAYER_CHARACTER].step_s >= 8 &&
        g_Entities[PLAYER_CHARACTER].step_s < 10) {
        return;
    }
    if (D_80097448[1] < 13) {
        return;
    }
    if (!IsRelicActive(RELIC_HOLY_SYMBOL)) {
        return;
    }
    if (!IsRelicActive(RELIC_SKILL_OF_WOLF)) {
        return;
    }
    if (g_Player.pl_vram_flag & 1) {
        return;
    }
    if (!(g_Player.padPressed & PAD_TRIANGLE)) {
        return;
    }
    if (D_80138440 != 0) {
        return;
    }

    PLAYER.step_s = 9;
    D_800B0914 = 0;
    func_8010DA48(0xEC);
    PLAYER.velocityY = 0;
}

void func_8012CA64(void) {
    u32 var_a0;

    PLAYER.step_s = 1;
    D_800B0914 = 0;

    if (g_Player.pl_vram_flag & 0x20) {
        var_a0 = 0xDF;
    } else {
        var_a0 = 0xDE;
    }
    func_8010DA48(var_a0);

    PLAYER.velocityY = 0;
    PLAYER.velocityX /= 2;

    D_800B0918 = 0x200;
    if (g_Player.pl_vram_flag & 0x40) {
        D_800B0914 = 1;
        func_8010DA48(0xE9U);
    }
}

void func_8012CB0C(void) {
    PLAYER.ext.generic.unkAC = 0xDE;
    PLAYER.velocityY = 0;
    D_800B0914 = 0;
    PLAYER.animFrameIdx = 0;
    PLAYER.animFrameDuration = 0;
    PLAYER.step_s = 7;
}

void func_8012CB4C(void) {
    PLAYER.step_s = 2;
    if ((PLAYER.facingLeft != 0 && g_Player.padPressed & PAD_RIGHT) ||
        (PLAYER.facingLeft == 0 && g_Player.padPressed & PAD_LEFT)) {
        func_8010DA48(0xE1);
        D_800B0914 = 0;
        D_8013842C = 0;
        return;
    } else if (D_8013842C != 0) {
        func_8010DA48(0xE2);
        D_800B0914 = 2;
        SetSpeedX(0x20000);
        return;
    } else {
        func_8010DA48(0xE0);
        D_800B0914 = 1;
        D_8013842C = 0xC;
    }
}

void func_8012CC30(s32 arg0) {
    if (arg0 == 0) {
        D_80138444 = 1;
        if (g_ButtonCombo[COMBO_QCF].buttonsCorrect == COMBO_COMPLETE &&
            IsRelicActive(RELIC_SKILL_OF_WOLF) &&
            CastSpell(SPELL_WOLF_CHARGE)) {
            func_8010E27C();
            PLAYER.step_s = 2;
            D_800B0914 = 4;
            SetSpeedX(0x50000);
            g_CurrentEntity->velocityY = 0;
            func_8010DA48(0xEDU);
            LearnSpell(4);
        }
    } else {
        D_80138444 = 1;
    }
}

void func_8012CCE4(void) {
    PLAYER.velocityY = FIX(-3.5);
    if ((PLAYER.step_s == 2) & (D_800B0914 == 2)) {
        func_8010DA48(0xE7);
        // Might be possible to rewrite this block to reduce duplication with
        // some clever && and ||
        if (PLAYER.facingLeft) {
            if ((g_Player.pl_vram_flag & 0xF000) == 0xC000) {
                PLAYER.velocityY = -(ABS(PLAYER.velocityX) + FIX(3.5));
            }
            if ((g_Player.pl_vram_flag & 0xF000) == 0x8000) {
                PLAYER.velocityY = FIX(-0.5);
            }
        } else {
            if ((g_Player.pl_vram_flag & 0xF000) == 0x8000) {
                PLAYER.velocityY = -(ABS(PLAYER.velocityX) + FIX(3.5));
            }
            if ((g_Player.pl_vram_flag & 0xF000) == 0xC000) {
                PLAYER.velocityY = FIX(-0.5);
            }
        }
        D_800B0914 = 2;
    } else if (
        (g_Player.padPressed & (PAD_RIGHT | PAD_LEFT)) &&
        ((PLAYER.step_s != 2) || (D_800B0914 != 0)) && (PLAYER.step_s != 9)) {
        func_8010DA48(0xE7);
        D_800B0914 = 1;
        if (g_Player.padPressed & PAD_UP) {
            PLAYER.velocityY = FIX(-4.875);
        }
    } else {
        func_8010DA48(0xE6);
        D_800B0914 = 0;
        if (g_Player.padPressed & PAD_UP) {
            PLAYER.velocityY = FIX(-4.875);
        }
    }
    PLAYER.step_s = 4;
    D_80138430 += 0x80;
}

void func_8012CED4(void) {
    if (PLAYER.step_s == 2 && D_800B0914 == PLAYER.step_s) {
        func_8010DA48(0xE7);
        D_800B0914 = 1;
    } else {
        func_8010DA48(0xE8);
        SetSpeedX(0x10000);
        D_800B0914 = 0;
        if (D_80138438 & 0x40) {
            PLAYER.animFrameIdx = 4;
            PLAYER.velocityX = 0;
            PLAYER.animFrameDuration = 1;
        }
    }
    PLAYER.step_s = 5;
    g_Player.D_80072F0A = 8;
    PLAYER.velocityY = 0;
    D_80138430 -= 0x100;
}

void func_8012CFA8(void) {
    func_8010DA48(0xEA);
    PLAYER.step_s = 6;
    D_800B0914 = 0;
    PLAYER.velocityX = 0;
    g_Player.D_80072F0A = 8;
}

void func_8012CFF0(void) {
    PLAYER.step_s = 3;
    func_8010DA48(0xE3);
    D_800B0914 = 0;
}

void func_8012D024(void) {
    s32 separation;
    DecelerateX(0x2000);
    if (g_Player.padTapped & PAD_CROSS) {
        func_8012CCE4();
        return;
    }
    if (!(g_Player.pl_vram_flag & 1)) {
        func_8012CED4();
        return;
    }
    if (g_Player.padTapped & PAD_SQUARE) {
        func_8012CC30(0);
        return;
    }
    if (g_Player.padPressed & (PAD_RIGHT | PAD_LEFT)) {
        func_8012CB4C();
        return;
    }
    if (g_Player.padPressed & PAD_DOWN) {
        func_8012CFF0();
        return;
    }
    if (D_800B0914 != 0) {
        return;
    }
    separation = (PLAYER.posY.i.hi - g_Entities[17].posY.i.hi);
    if (ABS(separation) < 4 && --D_800B0918 == 0) {
        D_800B0914 = 1;
        func_8010DA48(0xE9);
        return;
    }
    if (g_Player.pl_vram_flag & 0x40) {
        D_800B0914 = 1;
        func_8010DA48(0xE9);
    }
}

void func_8012D178(void) {
    s32 var_v0;

    if (g_Player.padTapped & PAD_CROSS) {
        func_8012CCE4();
    } else if (!(g_Player.pl_vram_flag & 1)) {
        func_8012CFA8();
    } else {
#if defined(VERSION_US)
        if (PLAYER.facingLeft != 0) {
            var_v0 = g_Player.padPressed & PAD_LEFT;
        } else {
            var_v0 = g_Player.padPressed & PAD_RIGHT;
        }
#elif defined(VERSION_HD)
        var_v0 = g_Player.padPressed & (PAD_LEFT | PAD_RIGHT);
#endif
        if (var_v0 != 0) {
            func_8012CB4C();
        } else if (g_Player.unk04 & 0x40) {
            func_8012CA64();
        } else if (g_GameTimer % 6 == 0) {
            CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0x100, 69), 0);
        }
    }
}

void func_8012D28C(bool exitEarly) {
    bool bitNotFound;
    s32 i;

    func_80102CD8(2);
    PlaySfx(0x644);
    PLAYER.velocityX = 0;
    g_Player.D_80072EFC = 0x20;
    g_Player.D_80072EF4 = 0;
    // Odd logic, if we exit early, we force an R2-tap. Strange!
    if (exitEarly) {
        g_Player.padTapped = PAD_R2;
        WolfFormFinished();
        return;
    }
    // Start a routine where we look through this array for a value.
    bitNotFound = 0;
    for (i = 3; i < 7; i++) {
        if ((g_Player.colliders2[i].effects & EFFECT_UNK_0002)) {
            break;
        }
    }
    // If we made it through that loop without finding one, skip i=7,8,9
    // and keep searching.
    if (i == 7) {
        for (i = 10; i < 14; i++) {
            if ((g_Player.colliders2[i].effects & EFFECT_UNK_0002)) {
                break;
            }
        }
    }
    // If we even made it through that one, then conclude the bit was not found.
    if (i == 14) {
        bitNotFound++;
    }

    SetSpeedX(FIX(1));
    CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0x900, 4), 0);
    D_800B0914 = 0;
    // Finally make use of that bit to control if X is positive or negative.
    if (bitNotFound) {
        func_8012CED4();
        SetSpeedX(FIX(1));
    } else {
        func_8012CFA8();
        SetSpeedX(FIX(-1));
    }
    PLAYER.velocityY = FIX(-3.5);
}
