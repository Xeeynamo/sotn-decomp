// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rno4.h"

#ifndef VERSION_PC
INCLUDE_ASM("st/rno4/nonmatchings/unk_44B0C", EntityBreakable);

void func_us_801C123C_from_no4(Entity* self) {
#ifndef VERSION_PSP
    s32 pad[10];
    (void)pad;
#endif

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        self->animSet = ANIMSET_OVL(9);
        self->unk5A = 0x5B;
        self->palette = 0x25D;
        self->animCurFrame = 0x15;
        self->zPriority = 0x6A;
        self->step = 0x100;
        break;
    }
}

INCLUDE_ASM("st/rno4/nonmatchings/unk_44B0C", func_us_801C12B0_from_no4);

extern s16 g_BackgroundTileRects[];

void func_us_801C15F8_from_no4(Entity* self) {
    s32 scrollX;
    s32 scrollY;
    s16* ptr;
    s32 var_s5;
    s32 var_s4;
    s32 var_s3;
    s32 var_s2;
    s32 var_s1;
    Primitive* prim;
    s32 primIndex;
    s32 xOffset;
    s32 yOffset;
    s32 i;

    if (self->step) {
    } else {
        InitializeEntity(g_EInitInteractable);
        self->animSet = 0;
        self->ext.et_801C12B0.unk80 = 4;
        primIndex = g_api.AllocPrimitives(PRIM_TILE, 16);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.et_801C12B0.prim = prim;
        while (prim != NULL) {
            prim->r0 = 0x10;
            prim->g0 = 8;
            prim->b0 = 0x18;
            prim->priority = 0x9D;
            prim = prim->next;
        }
    }

    prim = self->ext.et_801C12B0.prim;
    ptr = &g_BackgroundTileRects[(self->params & 0xFF) * 4];
    i = (self->params >> 8) & 0xFF;
    scrollX = g_Tilemap.scrollX.i.hi - 0x10;
    scrollY = g_Tilemap.scrollY.i.hi - 0x10;
    xOffset = scrollX + 0x120;
    yOffset = scrollY + 0x100;

    for (; i > 0; i--) {
        var_s3 = *ptr++;
        var_s2 = var_s3 + *ptr++;
        if (scrollX >= var_s2 || xOffset < var_s3) {
            ptr += 2;
            continue;
        }

        var_s4 = *ptr++;
        var_s5 = *ptr++;
        if (var_s4 > scrollY && yOffset >= var_s5) {
            if (var_s3 < scrollX) {
                var_s3 = scrollX;
            }
            if (xOffset < var_s2) {
                var_s2 = xOffset;
            }

            var_s2 -= var_s3;
            var_s3 -= scrollX + 0x10;

            if (var_s5 < scrollY) {
                var_s5 = scrollY;
            }
            if (yOffset < var_s4) {
                var_s4 = yOffset;
            }

            var_s4 -= var_s5;
            var_s5 -= scrollY + 0x10;
            if (var_s4 >= 0x100) {
                var_s4 = 0xFF;
            }

            do {
                var_s1 = var_s2;
                if (var_s1 >= 0x100) {
                    var_s1 = 0xFF;
                }
                prim->u0 = var_s1;
                prim->v0 = var_s4;
                prim->x0 = var_s3;
                prim->y0 = var_s5;
                var_s3 += var_s1;
                var_s2 -= var_s1;
                prim->drawMode = DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;
                prim = prim->next;
            } while (var_s2 != 0);
        }
    }

    while (prim != NULL) {
        prim->drawMode = DRAW_HIDE;
        prim = prim->next;
    }
}

INCLUDE_ASM("st/rno4/nonmatchings/unk_44B0C", func_us_801C5364);

INCLUDE_ASM("st/rno4/nonmatchings/unk_44B0C", EntityBgColumnsParallax_from_no4);

INCLUDE_ASM("st/rno4/nonmatchings/unk_44B0C", func_us_801C1EE4_from_no4);

INCLUDE_ASM("st/rno4/nonmatchings/unk_44B0C", func_us_801C5C78);

INCLUDE_ASM("st/rno4/nonmatchings/unk_44B0C", func_us_801C5EE4);

INCLUDE_ASM("st/rno4/nonmatchings/unk_44B0C", func_us_801C2850_from_no4);

INCLUDE_ASM("st/rno4/nonmatchings/unk_44B0C", func_us_801C2B78_from_no4);

INCLUDE_ASM("st/rno4/nonmatchings/unk_44B0C", func_us_801C2E60_from_no4);

INCLUDE_ASM("st/rno4/nonmatchings/unk_44B0C", func_us_801C3160_from_no4);

void func_us_801C34EC_from_no4(Entity* self) {
    extern s16 g_BackgroundParticleParams[];
    s32 scrollX;
    s16 xOffset;
    s16 randX;
    s16 randY;
    s16 tpage;
    s32 yOffset;
    s32 scrollY;
    s16* ptr;
    s32 primIndex;
    Primitive* prim;

    if (!self->step) {
        InitializeEntity(g_EInitInteractable);
        self->animSet = 0;
        primIndex = g_api.AllocPrimitives(PRIM_TILE, 0x40);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.et_801C12B0.prim = prim;
        while (prim != NULL) {
            prim->priority = 0x9B;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
    }

    ptr = &g_BackgroundParticleParams[self->params * 5];
    xOffset = *ptr++;
    randX = *ptr++;
    yOffset = *ptr++;
    randY = *ptr++;
    tpage = *ptr;

    prim = self->ext.et_801C12B0.prim;
    scrollX = g_Tilemap.scrollX.i.hi;
    scrollY = g_Tilemap.scrollY.i.hi;
    self->ext.et_801C12B0.unk80++;

    if (scrollY < 0xF0) {
        yOffset -= scrollY;
        while (prim != NULL) {
            if (prim->drawMode == DRAW_HIDE) {
                prim->r0 = prim->b0 = prim->g0 = 0x80;
                prim->y0 = yOffset + (rand() % randY);
                prim->x0 = (xOffset - scrollX) + (rand() % randX);
                prim->x1 = 0;
                LOH(prim->r1) = 0;
                prim->u0 = prim->v0 = 2;
                LOW(prim->u1) = 0;
                prim->tpage = tpage;
                prim->drawMode = DRAW_UNK02;
                break;
            }
            prim = prim->next;
        }
    }

    prim = self->ext.et_801C12B0.prim;
    while (prim != NULL) {
        if (prim->drawMode != DRAW_HIDE) {
            LOH(prim->b1) = prim->x0;
            LOW(prim->r1) += LOW(prim->u1);
            prim->x0 = LOH(prim->b1);
            prim->r0 -= 8;
            prim->b0 = prim->g0 = prim->r0;
            if (prim->r0 < 8) {
                prim->drawMode = DRAW_HIDE;
            }
        }
        prim = prim->next;
    }
}

void func_us_801C37C8_from_no4(Entity* self) {
    extern s16 g_BackgroundBlockX0;
    extern s16 g_BackgroundBlockX1;
    extern s16 g_BackgroundBlockX2;
    extern s16 g_BackgroundBlockX3;
    extern s16 g_BackgroundBlockX4;
    extern s16 g_BackgroundBlockX5;
    Primitive* prim;
    s32 scrollX;
    s32 scrollY;
    s32 xOffset;
    s32 primIndex;
    s32 clut;
    s32 randomValue;
    s32 clutValue;

    if (!self->step) {
        InitializeEntity(g_EInitInteractable);
        self->animSet = 0;
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->ext.et_801C12B0.clut = 0;
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.et_801C12B0.prim = prim;
        prim->tpage = 0xF;
        prim->v0 = prim->v1 = 0x7F;
        prim->v2 = prim->v3 = 1;
        prim->priority = 0x9C;
        prim->drawMode = DRAW_HIDE;
    }

    randomValue = rand() & 0x1F;
    scrollX = randomValue - 0x10;
    g_BackgroundBlockX0 = randomValue + 0xB20;
    g_BackgroundBlockX1 = 0x180 - scrollX;
    g_BackgroundBlockX2 = randomValue + 0x3C;
    g_BackgroundBlockX3 = randomValue + 0x7B0;
    g_BackgroundBlockX4 = 0x70 - scrollX;
    g_BackgroundBlockX5 = randomValue + 0x2A0;

    clutValue = *((volatile u32*)&self->ext.et_801C12B0.clut) + 1;
    *((volatile u32*)&self->ext.et_801C12B0.clut) = clutValue;
    if (clutValue >= 0xE) {
        *((volatile u32*)&self->ext.et_801C12B0.clut) = 0;
    }

    clut = self->ext.et_801C12B0.clut + 0xA0;
    prim = self->ext.et_801C12B0.prim;
    scrollX = g_Tilemap.scrollX.i.hi;
    scrollY = g_Tilemap.scrollY.i.hi;

    if (scrollX < 0x898) {
        xOffset = 0x828 - scrollX;
        if (xOffset < 0x100) {
            prim->u0 = prim->u2 = 0x11;
            prim->u1 = prim->u3 = 0x80;
        } else {
            prim->drawMode = DRAW_HIDE;
            return;
        }
    } else if (scrollX < 0xAE8) {
        xOffset = 0xA78 - scrollX;
        if (xOffset < 0x100) {
            prim->u0 = prim->u2 = 0x80;
            prim->u1 = prim->u3 = 0x11;
        } else {
            prim->drawMode = DRAW_HIDE;
            return;
        }
    } else {
        prim->drawMode = DRAW_HIDE;
        return;
    }

    prim->clut = clut;
    prim->x0 = prim->x2 = xOffset;
    prim->x1 = prim->x3 = xOffset + 0x6F;
    prim->y0 = prim->y1 = 0xD1 - scrollY;
    prim->y2 = prim->y3 = prim->y0 + 0x7F;
    prim->drawMode = DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;
}

INCLUDE_ASM("st/rno4/nonmatchings/unk_44B0C", func_us_801C3A04_from_no4);

INCLUDE_ASM("st/rno4/nonmatchings/unk_44B0C", func_us_801C3CC4_from_no4);

INCLUDE_ASM("st/rno4/nonmatchings/unk_44B0C", func_us_801C3FB0_from_no4);

INCLUDE_ASM("st/rno4/nonmatchings/unk_44B0C", func_us_801C4228_from_no4);

void EntityWaterBox(Entity* self) {
    Entity* player;
    u16 collision;
    if (!self->step) {
        InitializeEntity(g_EInitInteractable);
        self->animSet = ANIMSET_OVL(1);
        self->animCurFrame = 6;
        if (g_CastleFlags[NO4_WATER_BLOCKED]) {
            self->posX.i.hi = 0x720 - g_Tilemap.scrollX.i.hi;
        } else {
            self->posX.i.hi = 0x760 - g_Tilemap.scrollX.i.hi;
        }
    }

    player = &PLAYER;
    collision = GetPlayerCollisionWith(self, 0x10, 0x11, 5);
    if ((collision & 1) && (g_Player.vram_flag & TOUCHING_GROUND)) {
        if (self->posX.i.hi > player->posX.i.hi) {
            if ((g_pads[0].pressed & PAD_RIGHT) && (PLAYER.step == 1)) {
                if (self->ext.timer.t) {
                    self->ext.timer.t--;
                    return;
                }
                if (self->posX.i.hi + g_Tilemap.scrollX.i.hi < 0x7A0) {
                    self->posX.i.hi++;
                    player->posX.i.hi++;
                }
                self->ext.timer.t = 3;
            }
        } else {
            if ((g_pads[0].pressed & PAD_LEFT) && (PLAYER.step == 1)) {
                if (self->ext.timer.t) {
                    self->ext.timer.t--;
                    return;
                }
                if (self->posX.i.hi + g_Tilemap.scrollX.i.hi > 0x720) {
                    self->posX.i.hi--;
                    player->posX.i.hi--;
                    if (self->posX.i.hi + g_Tilemap.scrollX.i.hi == 0x720) {
                        g_CastleFlags[NO4_WATER_BLOCKED] = 1;
                    }
                }
                self->ext.timer.t = 3;
            }
        }
    }
}

INCLUDE_ASM("st/rno4/nonmatchings/unk_44B0C", func_us_801C81C8);

void EntityFloatingIcePlatform(Entity* self) {
    extern u16 g_FloatingIcePlatformHitbox[];
    u16* hitboxPtr;
    u16 collision;
    Entity* player;
    s16 prevPosY;
    s16 dx, dy;
    u16 hitboxIndex;

    player = &PLAYER;
    hitboxIndex = self->params;

    if (!self->step) {
        InitializeEntity(g_EInitCommon);
        self->animSet = ANIMSET_OVL(1);
        self->animCurFrame = hitboxIndex + 25;
        self->drawFlags = ENTITY_ROTATE;
        self->ext.floatingIcePlatform.baseY =
            self->posY.i.hi + g_Tilemap.scrollY.i.hi;
    }

    hitboxPtr = &g_FloatingIcePlatformHitbox[hitboxIndex * 2];

    prevPosY = self->posY.i.hi;
    self->posY.i.hi =
        self->ext.floatingIcePlatform.baseY - g_Tilemap.scrollY.i.hi +
        self->ext.floatingIcePlatform.bobOffset;
#ifdef VERSION_PSP
    collision = GetPlayerCollisionWith(self, hitboxPtr[0], hitboxPtr[1], 4);
#else
    collision = GetPlayerCollisionWith(self, *hitboxPtr++, *hitboxPtr, 4);
#endif
    self->posY.i.hi = prevPosY;
    self->ext.floatingIcePlatform.previousBobOffset =
        self->ext.floatingIcePlatform.bobOffset;

    dx = self->posX.i.hi - player->posX.i.hi;

    if (collision) {
        if (self->ext.floatingIcePlatform.bobOffset < 4) {
            self->ext.floatingIcePlatform.bobOffset++;
        }
    } else {
        if (self->ext.floatingIcePlatform.bobOffset) {
            self->ext.floatingIcePlatform.bobOffset--;
        }
    }

    dy = self->ext.floatingIcePlatform.bobOffset;
    if (dx < 0) {
        prevPosY = (dx * dy * -0x100) / 56;
    } else {
        prevPosY = (dx * dy * 0x100) / 56;
    }

    self->posY.i.hi = self->ext.floatingIcePlatform.baseY -
                      g_Tilemap.scrollY.i.hi + (dy - prevPosY / 256);

    if (collision) {
        dy = dy - self->ext.floatingIcePlatform.previousBobOffset;
        player->posY.i.hi += dy;
        g_unkGraphicsStruct.shoveX.i.hi += dy;
    }

    prevPosY = -prevPosY;
    if (collision || dy) {
        if (dx < 0) {
            self->rotate = ratan2(prevPosY, -0x3800);
            self->rotate = (self->rotate - 0x800) & 0xFFF;
            return;
        }
        self->rotate = ratan2(prevPosY, 0x3800);
    } else {
        self->rotate = 0;
    }
}

INCLUDE_ASM("st/rno4/nonmatchings/unk_44B0C", func_us_801C4BD8_from_no4);

INCLUDE_ASM("st/rno4/nonmatchings/unk_44B0C", func_us_801C8668);

void RNO4_Unused801C8704(void) {}

void func_us_801C870C(Entity* self) {
    s16 i;
    u16* tilemap;

    if (!self->params) {
        tilemap = &g_Tilemap.fg[0x143];
    } else {
        tilemap = &g_Tilemap.fg[0x53];
    }

    for (i = 0; i < 10; i++) {
        *tilemap++ = 0;
    }
}

void RNO4_Unused801C8768(void) {}

void RNO4_Unused801C8770(void) {}

INCLUDE_ASM("st/rno4/nonmatchings/unk_44B0C", EntityBoatElevatorChains);

void RNO4_Unused801C8BD4(void) {}

void RNO4_Unused801C8BDC(void) {}

void LoadFerrymanGateTiles(void) {
    extern u16 g_FerrymanGateTiles[];
    u16* tileData;
    Tilemap* tilemap = &g_Tilemap;
    s16 tileIndex = 0xF89;
    s32 i;
    tileData = g_FerrymanGateTiles;

    for (i = 0; i < 7; i++) {
        tilemap->fg[tileIndex] = *tileData++;
        tileIndex++;
        tilemap->fg[tileIndex] = *tileData++;
        tileIndex += 0xCF;
    }
}

void func_us_801C8C54(Entity* self) {
    LoadFerrymanGateTiles();
    DestroyEntity(self);
}

INCLUDE_ASM("st/rno4/nonmatchings/unk_44B0C", func_us_801A071C_from_bo3);

INCLUDE_ASM("st/rno4/nonmatchings/unk_44B0C", func_us_801A07CC_from_bo3);

void func_us_801C5518_from_no4(Entity* self) {
    extern s16 g_PlayerVelocityTriggerBounds[];
    Entity* player;
    u16 diff;
    s16* dataPtr;

    player = &PLAYER;

    if (!self->step) {
        InitializeEntity(g_EInitInteractable);
        self->animSet = 0;
    }

    dataPtr = &g_PlayerVelocityTriggerBounds[self->params * 4];

    diff = player->posX.i.hi + g_Tilemap.scrollX.i.hi - *dataPtr++;
    if (diff > *dataPtr++) {
        return;
    }
    diff = player->posY.i.hi + g_Tilemap.scrollY.i.hi - *dataPtr++;
    if (diff > *dataPtr++) {
        return;
    }
    if (player->velocityY < 0) {
        player->velocityY *= 7;
        player->velocityY /= 8;
    } else if (player->velocityY > 0) {
        player->nFramesInvincibility = 1;
    }
}

INCLUDE_ASM("st/rno4/nonmatchings/unk_44B0C", func_us_801C9048);

INCLUDE_ASM("st/rno4/nonmatchings/unk_44B0C", func_us_801C909C);

extern s32 g_ExplosionVariantVelocity[];
extern u8 g_ExplosionVariantFrames[];
extern u16 g_ExplosionVariantDurations[];

void EntityExplosionVariants(Entity* self) {
    if (!self->step) {
        self->velocityY =
            g_ExplosionVariantVelocity[self->ext.destructAnim.index];
        self->flags =
            FLAG_UNK_2000 | FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_POS_CAMERA_LOCKED;
        self->palette = PAL_FLAG(PAL_UNK_195);
        self->animSet = ANIMSET_DRA(2);
        self->animCurFrame = g_ExplosionVariantFrames[self->params];
        self->blendMode = BLEND_TRANSP;
        self->step++;
        return;
    }

    self->posY.val -= self->velocityY;
    ++self->poseTimer;
    if ((self->poseTimer % 2) == 0) {
        self->animCurFrame++;
    }
    if (self->poseTimer > g_ExplosionVariantDurations[self->params]) {
        DestroyEntity(self);
    }
}

void EntityGreyPuff(Entity* self) {
    extern s16 g_GreyPuffScale[];
    extern s32 g_GreyPuffVelocity[];

    if (!self->step) {
        self->flags =
            FLAG_UNK_2000 | FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_POS_CAMERA_LOCKED;
        self->palette = PAL_FLAG(PAL_UNK_195);
        self->animSet = ANIMSET_DRA(5);
        self->animCurFrame = 1;
        self->blendMode = BLEND_TRANSP;
        self->drawFlags = ENTITY_SCALEX | ENTITY_SCALEY;
        self->scaleX = g_GreyPuffScale[self->params];
        self->scaleY = self->scaleX;
        self->velocityY = g_GreyPuffVelocity[self->params];
        self->step++;
    } else {
        self->posY.val -= self->velocityY;
        self->poseTimer++;
        if ((self->poseTimer % 2) == 0) {
            self->animCurFrame++;
        }
        if (self->poseTimer > 36) {
            DestroyEntity(self);
        }
    }
}

void EntityIntenseExplosion(Entity* self) {
    if (!self->step) {
        InitializeEntity(g_EInitParticle);
        self->palette = 0x8170;
        self->animSet = 5;
        self->animCurFrame = 1;
        self->blendMode = BLEND_ADD | BLEND_TRANSP;
        if (self->params & 0xF0) {
            self->palette = 0x8195;
            self->blendMode = BLEND_TRANSP;
        }
        if (self->params & 0xFF00) {
            self->zPriority = (u16)((self->params & 0xFF00) >> 8);
        }
        self->zPriority += 8;
        return;
    }

    self->poseTimer++;
    self->posY.val -= FIX(0.25);

    if (!((u16)self->poseTimer & 1)) {
        self->animCurFrame++;
    }

    if (self->poseTimer >= 0x25) {
        DestroyEntity(self);
    }
}
#endif

void PlaySfxPositional(s16 sfxId) {
    s32 posX, posY;
    s16 sfxPan;
    s16 sfxVol;

    posX = g_CurrentEntity->posX.i.hi - 128;
    sfxPan = (abs(posX) - 32) >> 5;
    if (sfxPan > 8) {
        sfxPan = 8;
    } else if (sfxPan < 0) {
        sfxPan = 0;
    }
    if (posX < 0) {
        sfxPan = -sfxPan;
    }
    sfxVol = abs(posX) - 96;
    posY = abs(g_CurrentEntity->posY.i.hi - 128) - 112;
    if (posY > 0) {
        sfxVol += posY;
    }
    if (sfxVol < 0) {
        sfxVol = 0;
    }
    sfxVol = 127 - (sfxVol >> 1);
    if (sfxVol > 0) {
        g_api.PlaySfxVolPan(sfxId, sfxVol, sfxPan);
    }
}

#ifndef VERSION_PC
void EntityBreakableCrystalFloor(Entity* self) {
    extern s16 g_BreakableCrystalFloorTiles[];
    Entity* newEntity;
    s16* tileLayoutPtr;
    s32 tilePos;
    s32 i;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        self->hitboxWidth = 0x10;
        self->hitboxHeight = 0x10;
        self->hitboxState = 2;
        if (g_CastleFlags[RNO4_SECRET_CEILING_OPEN]) {
            i = 0x12;
        } else {
            i = 0;
        }
        tileLayoutPtr = &g_BreakableCrystalFloorTiles[i];
        tilePos = 0x2C;
        tilePos = 0x2C;
        (&g_BgLayers[0].layout[tilePos])[-1] = 0x3FE;
        (&g_BgLayers[0].layout[tilePos])[-2] = 0x3FF;
        (&g_BgLayers[0].layout[tilePos])[-17] = 0x401;
        (&g_BgLayers[0].layout[tilePos])[-18] = 0x402;
        for (i = 0; i < 2; i++, tileLayoutPtr += 3) {
            (&g_Tilemap.fg[tilePos])[0] = tileLayoutPtr[0];
            (&g_Tilemap.fg[tilePos])[-1] = tileLayoutPtr[1];
            (&g_Tilemap.fg[tilePos])[-2] = tileLayoutPtr[2];
            tilePos -= 0x10;
        }
        if (g_CastleFlags[RNO4_SECRET_CEILING_OPEN]) {
            DestroyEntity(self);
            return;
        }
        /* fallthrough */
    case 1:
        if (self->hitFlags) {
            PlaySfxPositional(SFX_WALL_DEBRIS_B);
            self->step++;
        }
        break;
    case 2:
        self->ext.breakable.breakCount++;
        tileLayoutPtr =
            &g_BreakableCrystalFloorTiles[self->ext.breakable.breakCount * 6];
        tilePos = 0x2C;
        for (i = 0; i < 2; i++, tileLayoutPtr += 3) {
            (&g_Tilemap.fg[tilePos])[0] = tileLayoutPtr[0];
            (&g_Tilemap.fg[tilePos])[-1] = tileLayoutPtr[1];
            (&g_Tilemap.fg[tilePos])[-2] = tileLayoutPtr[2];
            tilePos -= 0x10;
        }
        newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (newEntity != NULL) {
            CreateEntityFromEntity(E_EXPLOSION, self, newEntity);
            newEntity->params = 0x11;
        }
        self->ext.breakable.resetTimer = 0x20;
        self->step += 1;
        if (self->ext.breakable.breakCount == 3) {
            newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(E_EXPLOSION, self, newEntity);
                newEntity->params = 0x13;
            }
            g_CastleFlags[RNO4_SECRET_CEILING_OPEN] = 1;
            g_api.RevealSecretPassageAtPlayerPositionOnMap(0xCA);
            DestroyEntity(self);
            return;
        }
        break;
    case 3:
        if (!--self->ext.breakable.resetTimer) {
            self->step = 1;
            return;
        }
        break;
    }
}

INCLUDE_ASM("st/rno4/nonmatchings/unk_44B0C", EntityBreakableWall);
#endif
