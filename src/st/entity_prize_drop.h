// SPDX-License-Identifier: AGPL-3.0-or-later

// if self->params & 0x8000 then the item will not disappear
// ST0 seems to contain the earliest known version of this entity.
// MAD has some very minor enhancements that brings it closer to the US build,
// such as Life/Heart upgrade drops.
// US essentially adds castle flags for unique drops
// PSP iterates on top of the US version by adding drops for Maria
// PSP ST0 iterates on top of ST0 with the only change on CollectDummy params
void EntityPrizeDrop(Entity* self) {
    Primitive* prim;
    u16 itemId;
    s16 index;
    s32 primIndex;
    Collider collider;

    // if self->params & 0x8000 then the item will not disappear
    itemId = self->params & 0x7FFF;
    if (self->step) {
#if defined(VERSION_PSP) && STAGE != STAGE_ST0
        if (g_PlayableCharacter == PLAYER_MARIA) {
            AnimateEntity(g_MariaSubweaponAnimPrizeDrop[itemId], self);
        } else {
            AnimateEntity(g_SubweaponAnimPrizeDrop[itemId], self);
        }
#else
        AnimateEntity(g_SubweaponAnimPrizeDrop[itemId], self);
#endif
    }
#if defined(VERSION_US) && STAGE != STAGE_ST0
    if (self->step > 1 && self->step < 5 && self->hitFlags) {
#else
    if (self->step && self->step < 5 && self->hitFlags) {
#endif
        self->step = 5;
    }
#if STAGE == STAGE_ST0
    self->palette = 0x100;
#else
    self->palette = 0;
#endif
    if (self->unk6D[0] >= 0x18 && !(g_GameTimer & 2) && self->params != 1) {
        self->palette = 0x815F;
    }
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitObtainable);
        self->zPriority = g_unkGraphicsStruct.g_zEntityCenter - 0x14;
        self->drawMode = DRAW_DEFAULT;
#if STAGE == STAGE_ST0
        if (itemId > 22) {
#else
        if (itemId > 23) {
#endif
            itemId = self->params = 0;
        }

#if defined(VERSION_PSP) && STAGE != STAGE_ST0
        if (g_PlayableCharacter == PLAYER_MARIA && itemId >= 0xE &&
            itemId < 23) {
            switch (itemId) {
            case 14:
                itemId = self->params = 15;
                break;
            case 15:
                itemId = self->params = 14;
                break;
            case 21:
                itemId = self->params = 16;
                break;
            case 17:
                itemId = self->params = 17;
                break;
            case 19:
                itemId = 19;
                self->params = 19;
                break;
            default:
                itemId = self->params = 0;
                break;
            }
        }
#endif

#if defined(VERSION_PSP) && STAGE != STAGE_ST0
        if (itemId >= 14 && itemId < 23 &&
            g_PlayableCharacter != PLAYER_MARIA) {
            s32 subWeaponId = aluric_subweapons_id[g_Status.subWeapon];
            if (itemId == subWeaponId) {
                itemId = 1;
                self->params = 1;
            }
        }
#else
        if (itemId >= 14 && itemId < 23 &&
            itemId == aluric_subweapons_id[g_Status.subWeapon]) {
            itemId = 1;
            self->params = 1;
        }
#endif
        if (!itemId || itemId == 2) {
            self->hitboxWidth = 4;
        }
        break;
    case 1:
        g_api.CheckCollision(self->posX.i.hi, self->posY.i.hi, &collider, 0);
        if (collider.effects & EFFECT_NOTHROUGH_PLUS) {
            DestroyEntity(self);
        } else {
            self->step++;
#if !defined(VERSION_BETA) && STAGE != STAGE_ST0
            index = self->ext.equipItemDrop.castleFlag;
            if (index) {
                index--;
                g_CastleFlags[(index >> 3) + COLLECT_FLAGS_START] |=
                    1 << (index & 7);
            }
#endif
        }
        if (!itemId) {
            self->ext.equipItemDrop.fallSpeed = FIX(-1);
            self->ext.equipItemDrop.gravity = 0x800;
        }
        break;
    case 2:
#if STAGE == STAGE_ST0
        if (self->velocityX < 0) {
#else
        if (self->velocityY < 0) {
#endif
            g_api.CheckCollision(
                self->posX.i.hi, self->posY.i.hi - 7, &collider, 0);
            if (collider.effects & EFFECT_NOTHROUGH) {
                self->velocityY = 0;
            }
        }
        MoveEntity();
        g_api.CheckCollision(
            self->posX.i.hi, self->posY.i.hi + 7, &collider, 0);
        if (itemId) {
            if (collider.effects & EFFECT_NOTHROUGH && self->velocityY > 0) {
                self->velocityX = 0;
                self->velocityY = 0;
                self->posY.i.hi += collider.unk18;
                self->ext.equipItemDrop.aliveTimer = 0xF0;
                self->step++;
            } else {
                FallEntity();
            }
            CheckFieldCollision(D_80180EB8, 2);
        } else if (collider.effects & EFFECT_NOTHROUGH) {
            self->posY.i.hi += collider.unk18;
            self->ext.equipItemDrop.aliveTimer = 0x60;
            self->step++;
        } else {
            PrizeDropFall();
        }
        break;
    case 3:
        PrizeDropFall2(itemId);
        if (!(self->params & 0x8000) && !--self->ext.equipItemDrop.aliveTimer) {
            if (itemId) {
                self->ext.equipItemDrop.aliveTimer = 80;
            } else {
                self->ext.equipItemDrop.aliveTimer = 64;
            }
            self->step++;
        }
        break;
    case 4:
        PrizeDropFall2(itemId);
        if (--self->ext.equipItemDrop.aliveTimer) {
            if (self->ext.equipItemDrop.aliveTimer & 2) {
                self->animCurFrame = 0;
            }
        } else {
            DestroyEntity(self);
            return;
        }
        break;
    case 5:
        if (itemId < 2) {
            CollectHeart(itemId);
        } else if (itemId < 12) {
            CollectGold(itemId);
#if STAGE != STAGE_ST0
        } else if (itemId == 12) {
            CollectHeartVessel();
#endif
        } else if (itemId < 14) {
#if defined VERSION_BETA || (STAGE == STAGE_ST0 && !defined(VERSION_PSP))
            // this is only allowed in BETA PSX and ST0 PSX, not on ST0 PSP
            // probably due to a compilation error fix
            CollectDummy();
#else
            CollectDummy(itemId);
#endif
        } else if (itemId < 23) {
            CollectSubweapon(itemId);
#if STAGE != STAGE_ST0
        } else if (itemId == 23) {
            CollectLifeVessel();
#endif
        } else {
            DestroyEntity(self);
            return;
        }
        break;
#if !defined(VERSION_BETA) && STAGE != STAGE_ST0
    case 6:
#endif
    case 7:
        switch (self->step_s) {
        case 0:
            self->animCurFrame = 0;
#if defined(VERSION_PSP) && STAGE != STAGE_ST0
            if (itemId >= 14 && itemId < 23) {
                s32 subWeaponId;
                if (g_PlayableCharacter == PLAYER_MARIA) {
                    subWeaponId = maria_subweapons_id[g_Status.D_80097C40];
                    if (itemId == subWeaponId) {
                        itemId = 1;
                        self->params = 1;
                    }
                } else {
                    subWeaponId = aluric_subweapons_id[g_Status.subWeapon];
                    if (itemId == subWeaponId) {
                        itemId = 1;
                        self->params = 1;
                    }
                }
            }
#else
            if (itemId >= 14 && itemId < 23 &&
                itemId == aluric_subweapons_id[g_Status.subWeapon]) {
                itemId = 1;
                self->params = 1;
            }
#endif
            primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
            if (primIndex != -1) {
                self->primIndex = primIndex;
                self->flags |= FLAG_HAS_PRIMS;
                prim = &g_PrimBuf[primIndex];
                prim->tpage = 0x1A;
                prim->clut = 0x170;
#if defined VERSION_BETA || STAGE == STAGE_ST0
                prim->u0 = prim->u2 = 0;
                prim->u1 = prim->u3 = 0x20;
                prim->v0 = prim->v1 = 0;
                prim->v2 = prim->v3 = 0x20;
                prim->r0 = prim->r1 = prim->r2 = prim->r3 = 128;
                prim->g0 = prim->g1 = prim->g2 = prim->g3 = 128;
                prim->b0 = prim->b1 = prim->b2 = prim->b3 = 128;
#else
                prim->u0 = prim->u2 = prim->v0 = prim->v1 = 0;
                prim->u1 = prim->u3 = prim->v2 = prim->v3 = 0x20;
                prim->r0 = prim->r1 = prim->r2 = prim->r3 = prim->g0 =
                    prim->g1 = prim->g2 = prim->g3 = prim->b0 = prim->b1 =
                        prim->b2 = prim->b3 = 128;
#endif
                prim->drawMode = DRAW_HIDE;
                prim->priority = self->zPriority + 1;
                self->step_s++;
            }
            break;
        case 1:
            MoveEntity();
            g_api.CheckCollision(
                self->posX.i.hi, self->posY.i.hi + 7, &collider, 0);
            if (collider.effects & EFFECT_NOTHROUGH && self->velocityY > 0) {
                self->velocityX = 0;
                self->velocityY = 0;
                self->posY.i.hi += collider.unk18;
                self->step_s++;
            } else {
                FallEntity();
            }
            CheckFieldCollision(D_80180EB8, 2);
            self->animCurFrame = 0;
            if (self->ext.equipItemDrop.unk8A) {
                self->ext.equipItemDrop.unk8A--;
            } else {
                prim = &g_PrimBuf[self->primIndex];
                prim->x0 = prim->x2 = self->posX.i.hi - 1;
                prim->x1 = prim->x3 = self->posX.i.hi + 1;
                prim->y0 = prim->y1 = self->posY.i.hi - 1;
                prim->y2 = prim->y3 = self->posY.i.hi + 1;
                prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS |
                                 DRAW_UNK02 | DRAW_TRANSP;
            }
            break;
        case 2:
            PrizeDropFall2(itemId);
            prim = &g_PrimBuf[self->primIndex];
            self->ext.equipItemDrop.unk8A++;
            if (self->ext.equipItemDrop.unk8A < 17) {
                index = self->ext.equipItemDrop.unk8A;
                self->animCurFrame = 0;
            } else {
                index = 32 - self->ext.equipItemDrop.unk8A;
                prim->r0 = prim->r1 = prim->r2 = prim->r3 -= 8;
                prim->g0 = prim->g1 = prim->g2 = prim->g3 -= 8;
                prim->b0 = prim->b1 = prim->b2 = prim->b3 -= 8;
            }
            prim->x0 = prim->x2 = self->posX.i.hi - index;
            prim->x1 = prim->x3 = self->posX.i.hi + index;
            prim->y0 = prim->y1 = self->posY.i.hi - index;
            prim->y2 = prim->y3 = self->posY.i.hi + index;
            if (self->ext.equipItemDrop.unk8A == 32) {
                g_api.FreePrimitives(self->primIndex);
                self->flags &= ~FLAG_HAS_PRIMS;
                self->ext.equipItemDrop.aliveTimer = 208;
                self->step = 3;
                self->step_s = 0;
            }
            break;
        }
        break;
    }
}
