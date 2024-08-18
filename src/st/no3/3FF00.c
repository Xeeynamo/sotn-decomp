#include "no3.h"
#include "sfx.h"

void EntityRoomTransition2(Entity* self) {
    Entity* newEntity;
    Primitive* prim;
    // Used as both a loop variable and a temp
    s32 localVar;
    Entity* gents = g_Entities;
    Tilemap* tilemap = &g_Tilemap;

    if (self->ext.roomTransition2.unk80 == 0 && self->step < 4) {
        g_api.PlaySfx(SFX_DEATH_AMBIENCE);
        self->ext.roomTransition2.unk80 = 0x200;
    }
    self->ext.roomTransition2.unk80--;

    switch (self->step) {
    case 0:
        InitializeEntity(D_80180AD0);
        tilemap->y = 0xFC;
        g_Player.padSim = PAD_RIGHT;
        D_8003C8B8 = 0;
        g_Player.D_80072EFC = 1;
        D_801D7DD0 |= 0x100;
        break;

    case 1:
        // Evil use of local 'gents' instead of PLAYER
        if (gents->posX.i.hi < 52) {
            g_Entities[UNK_ENTITY_1].ext.alucardController.unk7C = 1;
            g_Player.padSim = PAD_RIGHT;
        } else {
            g_Player.padSim = 0;
            D_801D7DD0 |= 0x80;
            self->step++;
        }
        g_Player.D_80072EFC = 1;
        break;

    case 2:
        if (D_801D7DD0 & 0x20) {
            g_api.InitStatsAndGear(1);
            g_api.PlaySfx(SE_DEATH_SWIPES);
            for (localVar = 0; localVar < 6; localVar++) {
                newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (newEntity == NULL) {
                    break;
                }
                CreateEntityFromEntity(E_ID_59, gents, newEntity);
                newEntity->params = localVar;
            }
            g_Player.padSim = 0x10000;
            self->ext.roomTransition2.timer = 16;
            self->step++;
        }
        g_Player.D_80072EFC = 1;
        break;

    case 3:
        if (D_801D7DD0 & 0x40 && !(--self->ext.roomTransition2.timer)) {
            localVar = g_api.AllocPrimitives(PRIM_TILE, 1);
            if (localVar != -1) {
                prim = &g_PrimBuf[localVar];
                self->primIndex = localVar;
                self->flags |= FLAG_HAS_PRIMS;
                prim->u0 = 0xFF;
                prim->v0 = 0xFF;
                prim->priority = 0x50;
                prim->x0 = 0;
                prim->y0 = 0;
                prim->r0 = prim->b0 = prim->g0 = 0;
                prim->drawMode = 0x35;
                self->step++;
            } else {
                self->ext.roomTransition2.timer++;
            }
        }
        g_Player.padSim = 0;
        g_Player.D_80072EFC = 1;
        break;

    case 4:
        prim = &g_PrimBuf[self->primIndex];
        prim->r0 = prim->g0 = prim->b0 = prim->b0 + 8;
        if (prim->r0 >= 240) {
            self->step++;
            DestroyEntity(&g_Entities[208]);
            g_Tilemap.bg[0].flags |= 1;
            g_api.PlaySfx(0xA1);
            g_api.PlaySfx(0x30F);
        }
        g_Player.padSim = 0;
        g_Player.D_80072EFC = 1;
        break;

    case 5:
        prim = &g_PrimBuf[self->primIndex];
        prim->r0 = prim->g0 = prim->b0 = prim->b0 - 8;
        if (prim->r0 == 0) {
            DestroyEntity(self);
            gents = &g_Entities[192];
            tilemap->y = 0;
            D_8003C8B8 = 1;
            DestroyEntity(gents);
            CreateEntityFromCurrentEntity(E_BG_LIGHTNING, gents);
        }
        g_Player.padSim = 0;
        g_Player.D_80072EFC = 1;
        break;
    }
}

// Displays items took by Death in the cutscene
void EntityDeathStolenItem(Entity* self) {
    u16 params = self->params;
    u16 itemId = D_80181AD4[params];
    volatile char pad;
    Primitive* prim;
    s32 primIndex;
    u16 temp1;
    u16 temp3;
    u16 temp4;
    u16 temp6;
    s32 temp2;
    s32 temp8;
    u8 temp7;
    u8 temp5;

    switch (self->step) {
    case 0:
        InitializeEntity(g_eInitGeneric2);
        break;

    case 1:
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
        if (primIndex == -1) {
            break;
        }
        self->primIndex = primIndex;
        self->flags |= FLAG_HAS_PRIMS;

        if (itemId < NUM_HAND_ITEMS) {
            g_api.LoadEquipIcon(g_api.equipDefs[itemId].icon,
                                g_api.equipDefs[itemId].iconPalette, params);
        } else {
            itemId -= NUM_HAND_ITEMS;
            g_api.LoadEquipIcon(
                g_api.accessoryDefs[itemId].icon,
                g_api.accessoryDefs[itemId].iconPalette, params);
        }

        prim = &g_PrimBuf[primIndex];
        prim->tpage = 0x1A;
        prim->clut = params + 0x1D0;
        prim->r0 = prim->r1 = prim->r2 = prim->r3 = prim->g0 = prim->g1 =
            prim->g2 = prim->g3 = prim->b0 = prim->b1 = prim->b2 = prim->b3 =
                128;
        prim->priority = 0x80;
        prim->u0 = prim->u2 = (params & 7) << 4 | 1;
        prim->u1 = prim->u3 = (params & 7) << 4 | 0xF;
        prim->v0 = prim->v1 = (params & 0x18) << 1 | 0x81;
        prim->v2 = prim->v3 = (params & 0x18) << 1 | 0x8F;
        prim->drawMode = 8;
        self->step++;
        break;

    case 2:
        UnkEntityFunc0(D_80181AEC[params].x, D_80181AEC[params].y);
        self->ext.deathStolenItems.unk7C = 16;
        self->step++;
        break;

    case 3:
        self->ext.deathStolenItems.unk7C--;
        temp6 = self->ext.deathStolenItems.unk7C;
        MoveEntity();
        temp8 = (16 - temp6) * 7;
        if (temp8 < 0) {
            temp8 += 15;
        }
        prim = &g_PrimBuf[self->primIndex];
        temp1 = temp8 >> 4;
        prim->x0 = prim->x2 = self->posX.i.hi - temp1;
        prim->y0 = prim->y1 = self->posY.i.hi - temp1;
        prim->drawMode = 6;
        temp2 = temp1 << 1;
        prim->x1 = prim->x3 = prim->x0 + temp2;
        prim->y2 = prim->y3 = prim->y0 + temp2;
        if (temp6 == 0) {
            self->ext.deathStolenItems.unk7C = D_80181AE0[params];
            self->step++;
        }
        break;

    case 4:
        if (--self->ext.deathStolenItems.unk7C == 0) {
            self->ext.deathStolenItems.unk7C = 8;
            g_api.PlaySfx(SE_ITEM_YOINK);
            self->step++;
        }

        prim = &g_PrimBuf[self->primIndex];
        if (self->ext.deathStolenItems.unk7C & 2) {
            prim->r0 = prim->r1 = prim->r2 = prim->r3 = 192;
            prim->g0 = prim->g1 = prim->g2 = prim->g3 = prim->b0 = prim->b1 =
                prim->b2 = prim->b3 = 64;
        } else {
            prim->r0 = prim->r1 = prim->r2 = prim->r3 = prim->g0 = prim->g1 =
                prim->g2 = prim->g3 = prim->b0 = prim->b1 = prim->b2 =
                    prim->b3 = 128;
        }
        break;

    case 5:
        prim = &g_PrimBuf[self->primIndex];
        prim->y0 = prim->y1 = prim->y1 - 0x20;
        if (self->ext.deathStolenItems.unk7C >= 2) {
            temp3 = prim->x2;
            temp4 = prim->x3;
            prim->x2 = temp3 + 1;
            prim->x0 = temp3;
            prim->x3 = temp4 - 1;
            prim->x1 = temp4;
        }
        if (--self->ext.deathStolenItems.unk7C == 0) {
            self->ext.deathStolenItems.unk7C = 16;
            self->step++;
        }
        break;

    case 6:
        prim = &g_PrimBuf[self->primIndex];
        prim->y2 = prim->y3 = prim->y3 - 0x10;
        if (--self->ext.deathStolenItems.unk7C == 0) {
            self->step++;
            DestroyEntity(self);
        }
        break;
    }
}

void EntityDeath(Entity* self) {
    Entity* newEntity = &self[1];
    Primitive* prim;
    s16 left, right;
    s32 primIndex;
    s32 x, y;
    s32 i;

    if ((self->step >= 4) && (self->step < 13)) {
        if (self->ext.death.moveTimer != 0) {
            self->ext.death.moveTimer--;
        } else {
            if (self->ext.death.moveDirection != 0) {
                self->ext.death.moveDirection = 0;
            } else {
                self->ext.death.moveDirection = 1;
            }
            self->ext.death.moveTimer = 127;
        }

        if (self->ext.death.moveDirection != 0) {
            self->velocityY += 0x200;
        } else {
            self->velocityY -= 0x200;
        }
        MoveEntity();
    }

    if ((self->step >= 13) && (self->step < 18)) {
        if (self->velocityY != 0) {
            if (self->velocityY < 0) {
                self->velocityY += 0x200;
            } else {
                self->velocityY -= 0x200;
            }
            MoveEntity();
        }
    }

    if (self->step >= 19) {
        self->velocityX -= 0xC00;
        self->velocityY -= FIX(0.15625);
        MoveEntity();
    }

    switch (self->step) {
    case 0:
        if (D_801D7DD0 & 0x80) {
            primIndex = g_api.AllocPrimitives(PRIM_GT4, 2);
            if (primIndex != -1) {
                InitializeEntity(g_eInitGeneric2);
                self->animSet = ANIMSET_OVL(8);
                self->palette = 0x2D6;
                self->unk5A = 0x44;
                self->primIndex = primIndex;
                self->animCurFrame = 0;
                self->ext.death.unk7C = 0;
                self->flags |= FLAG_HAS_PRIMS;
                DestroyEntity(newEntity);
                CreateEntityFromCurrentEntity(E_ID_5B, newEntity);
                prim = &g_PrimBuf[primIndex];

                for (i = 0; prim != NULL; i++) {
                    if (i != 0) {
                        prim->clut = self->palette;
                        prim->drawMode = 0x35;
                    } else {
                        prim->clut = 0x15F;
                        prim->drawMode = 0x55;
                    }
                    prim->tpage = self->unk5A >> 2;
                    prim->u0 = prim->u2 = 0x10;
                    prim->u1 = prim->u3 = 0x38;
                    prim->v0 = prim->v1 = 0xB0;
                    prim->v2 = prim->v3 = 0xFF;
                    prim->r0 = prim->r1 = prim->r2 = prim->r3 = prim->g0 =
                        prim->g1 = prim->g2 = prim->g3 = prim->b0 = prim->b1 =
                            prim->b2 = prim->b3 = 0;
                    prim->priority = self->zPriority + i + 1;
                    prim = prim->next;
                }
            }
        }
        break;

    case 1:
        if (AnimateEntity(D_80181BC8, self) == 0) {
            SetStep(2);
            self->drawFlags = FLAG_DRAW_ROTZ;
            self->rotZ = 0x1000;
            self->posY.i.hi += 16;
            self->animCurFrame = 0x3A;
            self->ext.death.posX = self->posX.i.hi;
            self->ext.death.posY = self->posY.i.hi;
        }
        break;

    case 2:
        self->rotZ -= 0x40;
        if (self->rotZ == 0) {
            SetStep(3);
            self->drawFlags = 0;
        }

        x = (0x1000 - self->rotZ) * 0x1D;
        if (x < 0) {
            x += 0xFFF;
        }
        self->posX.i.hi = self->ext.death.posX + (x >> 0xC);

        y = (0x1000 - self->rotZ) * 0x28;
        if (y < 0) {
            y += 0xFFF;
        }
        self->posY.i.hi = self->ext.death.posY - (y >> 0xC);

        if (!(self->rotZ & 0x70)) {
            newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (newEntity != 0) {
                CreateEntityFromCurrentEntity(E_ID_5E, newEntity);
                newEntity->rotZ = self->rotZ;
                newEntity->animCurFrame = 0x3A;
            }
        }
        break;

    case 3:
        if (AnimateEntity(D_80181BE0, self) == 0) {
            SetStep(4);
            g_api.PlaySfx(SE_VO_DEATH_LAUGH);
            self->ext.death.moveTimer = 64;
            self->ext.death.moveDirection = 0;
        }
        self->posX.i.hi = self->ext.death.posX;
        self->posY.i.hi = self->ext.death.posY - 16;
        break;

    case 4:
        prim = &g_PrimBuf[self->primIndex];
        self->ext.death.unk7C += 4;
        if (self->ext.death.unk7C == 96) {
            D_801D7DD0 |= 1;
        }

        if (self->ext.death.unk7C == 128) {
            while (prim != NULL) {
                prim->drawMode = 8;
                prim = prim->next;
            }
            self->animCurFrame = 16;
            self->ext.death.unk7C = 32;
            SetStep(5);
            break;
        }

        while (prim != NULL) {
            left = self->posX.i.hi - 14;
            right = self->posX.i.hi + 26;
            prim->x0 = prim->x2 = left;
            prim->x1 = prim->x3 = right;
            left = self->posY.i.hi - 40;
            right = self->posY.i.hi + 39;
            prim->y0 = prim->y1 = left;
            prim->y2 = prim->y3 = right;
            prim->r0 = prim->r1 = prim->r2 = prim->r3 = prim->g0 = prim->g1 =
                prim->g2 = prim->g3 = prim->b0 = prim->b1 = prim->b2 =
                    prim->b3 = self->ext.death.unk7C;
            prim = prim->next;
        }
        break;

    case 5:
        AnimateEntity(D_80181B34, self);
        if (--self->ext.death.unk7C == 0) {
            SetStep(6);
        }
        break;

    case 6:
        AnimateEntity(D_80181B28, self);
        if (D_801D7DD0 & 2) {
            SetStep(7);
        }
        break;

    case 7:
        if (AnimateEntity(D_80181B04, self) == 0) {
            SetStep(8);
        }
        if ((self->animCurFrame >= 7) && (self->animCurFrame < 11)) {
            newEntity->ext.death.unk7C = 2;
        } else {
            newEntity->ext.death.unk7C = 1;
        }

        if (D_801D7DD0 & 4) {
            SetStep(9);
        }
        break;

    case 8:
        AnimateEntity(D_80181B28, self);
        if (D_801D7DD0 & 4) {
            SetStep(9);
        }
        break;

    case 9:
        if (AnimateEntity(D_80181BB4, self) == 0) {
            SetStep(10);
        }
        newEntity->ext.death.unk7C = 1;

        if (D_801D7DD0 & 8) {
            SetStep(11);
        }
        break;

    case 10:
        AnimateEntity(D_80181B28, self);
        if (D_801D7DD0 & 8) {
            SetStep(11);
        }
        break;

    case 11:
        if (AnimateEntity(D_80181B94, self) == 0) {
            SetStep(12);
        }
        newEntity->ext.death.unk7C = 1;

        if (D_801D7DD0 & 0x10) {
            SetStep(13);
        }
        break;

    case 12:
        AnimateEntity(D_80181B28, self);
        if (D_801D7DD0 & 0x10) {
            SetStep(13);
        }
        break;

    case 13:
        if (AnimateEntity(D_80181B58, self) == 0) {
            SetStep(14);
        }
        newEntity->ext.death.unk7C = 1;
        break;

    case 14:
        if (AnimateEntity(D_80181B68, self) == 0) {
            g_api.PlaySfx(SE_VO_DEATH_STEALS);
            SetStep(15);
        }
        break;

    case 15:
        if (AnimateEntity(D_80181B70, self) == 0) {
            SetStep(16);
            D_801D7DD0 |= 0x20;
        }
        break;

    case 16:
        if (AnimateEntity(D_80181B74, self) == 0) {
            SetStep(18);
        }

        if (self->animCurFrame != 30) {
            newEntity->ext.death.unk7C = 1;
        }
        break;

    case 18:
        if (AnimateEntity(D_80181B84, self) == 0) {
            SetStep(19);
            g_api.PlaySfx(SE_VO_DEATH_LAUGH);
            self->velocityX = FIX(1.0);
            self->velocityY = FIX(5.0);
            self->ext.death.moveTimer = 0;
        }

        if (self->animCurFrame != 1) {
            newEntity->ext.death.unk7C = 2;
        } else {
            newEntity->ext.death.unk7C = 1;
        }
        break;

    case 19:
        AnimateEntity(D_80181B8C, self);
        if (self->animCurFrame == 1) {
            newEntity->ext.death.unk7C = 1;
        } else {
            newEntity->ext.death.unk7C = 2;
        }

        if ((self->ext.death.moveTimer & 3) == 0) {
            newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (newEntity != NULL) {
                CreateEntityFromCurrentEntity(E_ID_5E, newEntity);
                newEntity->animCurFrame = self->animCurFrame;
                newEntity->params = 1;
            }
            newEntity->ext.death.unk7C = 3;
        }
        self->ext.death.moveTimer++;

        if (self->posY.i.hi < -32) {
            D_801D7DD0 |= 0x40;
            DestroyEntity(self);
            DestroyEntity(&self[1]);
        }
        break;
    }
}

void EntityUnkId5B(Entity* entity) {
    Entity* newEntity;

    entity->posX.i.hi = entity[-1].posX.i.hi;
    entity->posY.i.hi = entity[-1].posY.i.hi;

    switch (entity->step) {
    case 0:
        InitializeEntity(g_eInitGeneric2);
        entity->animSet = ANIMSET_OVL(8);
        entity->palette = 0x2D6;
        entity->animCurFrame = 0;
        entity->unk5A = 0x44;
        break;

    case 1:
        if (entity->ext.generic.unk7C.u != 0) {
            switch (entity->ext.generic.unk7C.u) {
            case 1:
                AnimateEntity(D_80181B40, entity);
                break;
            case 2:
                AnimateEntity(D_80181B4C, entity);
                break;
            case 3:
                AnimateEntity(D_80181B4C, entity);
                newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (newEntity == NULL) {
                    break;
                }
                CreateEntityFromCurrentEntity(E_ID_5E, newEntity);
                newEntity->animCurFrame = entity->animCurFrame;
                newEntity->params = 1;
                break;
            }
        } else {
            entity->animCurFrame = 0;
        }
    }
    entity->ext.generic.unk7C.s = 0;
}

void EntityUnkId5E(Entity* entity) {
    s16 animCurFrame;

    switch (entity->step) {
    case 0:
        animCurFrame = entity->animCurFrame;
        InitializeEntity(g_eInitGeneric2);
        entity->animCurFrame = animCurFrame;
        entity->animSet = ANIMSET_OVL(8);
        entity->palette = 0x2D6;
        entity->unk5A = 0x44;
        if (entity->params != 0) {
            entity->drawFlags = FLAG_DRAW_UNK8;
            entity->ext.generic.unk84.U16.unk0 = 0x40;
        } else {
            entity->drawFlags = FLAG_DRAW_ROTZ | FLAG_DRAW_UNK8;
            entity->ext.generic.unk84.U16.unk0 = 0x20;
        }
        entity->unk6C = 0x40;
        entity->drawMode = 0x30;
        break;

    case 1:
        if (!(--entity->ext.generic.unk84.U16.unk0)) {
            DestroyEntity(entity);
            break;
        }
        if (entity->params != 0) {
            entity->unk6C = (s8)entity->unk6C - 1;
        } else {
            entity->unk6C += -2;
        }
        break;
    }
}

void func_801C13F8() {
    Entity* entity;
    s16 temp_s3;
    s8 temp_s4;
    s32 i;

    temp_s4 = Random() & 3;
    temp_s3 = ((Random() & 0xF) << 8) - 0x800;

    for (i = 0; i < 6; i++) {
        entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (entity != NULL) {
            // Make a EntityWargExplosionPuffOpaque
            CreateEntityFromEntity(E_WARG_EXP_OPAQUE, g_CurrentEntity, entity);
            entity->params = 2;
            entity->ext.wargpuff.unk89 = 6 - i;
            entity->ext.wargpuff.unk84 = temp_s3;
            entity->ext.wargpuff.unk88 = temp_s4;
        }
    }
}

// A single "puff" of the warg explosion animation, opaque
void EntityWargExplosionPuffOpaque(Entity* self) {
    Unkstruct_80180FE0* obj;
    s32 velocityX;
    s32 velocityY;
    s32 params;
    s32 temp_s0;
    s32 adjVelocityX;
    s32 adjVelocityY;
    u32 temp_v0;
    s32 rnd;

    switch (self->step) {
    case 0:
        InitializeEntity(g_InitializeEntityData0);
        params = self->params & 0xF;
        obj = &D_80181C5C[params];
        self->palette = obj->palette + 0xD0;
        self->drawMode = obj->drawMode;
        self->animSet = obj->animSet;
        self->unk5A = obj->unk2;
        self->ext.wargpuff.unk80 = obj->unk8;
        self->step = params + 1;

        temp_v0 = self->params & 0xFF00;
        if (temp_v0 != 0) {
            self->zPriority = temp_v0 >> 8;
        }

        if (self->params & 0xF0) {
            self->palette = 0x819F;
            self->drawMode = DRAW_TPAGE;
            self->facingLeft = 1;
        }
        break;

    case 1:
        MoveEntity();
        self->velocityY = FIX(1.0);
        if (AnimateEntity((u8*)self->ext.wargpuff.unk80, self) == 0) {
            DestroyEntity(self);
        }
        break;

    case 2:
        if (AnimateEntity((u8*)self->ext.wargpuff.unk80, self) != 0) {
            switch (self->step_s) {
            case 0:
                self->drawFlags = FLAG_DRAW_UNK8;
                self->unk6C = 0x80;
                self->step_s++;
                break;

            case 1:
                if (self->animFrameIdx == 5) {
                    self->step_s++;
                }
                break;

            case 2:
                self->unk6C += 0xFC;
                break;
            }
        } else {
            DestroyEntity(self);
        }
        break;

    case 3:
        if (self->step_s == 0) {
            self->drawFlags |= 4;
            switch (self->ext.wargpuff.unk88) {
            case 1:
                if (self->ext.wargpuff.unk89 >= 0x4) {
                    self->ext.wargpuff.unk89 += 0xFD;
                    self->ext.wargpuff.unk84 -= 0x800;
                }
                break;

            case 2:
                self->ext.wargpuff.unk84 =
                    (u16)self->ext.wargpuff.unk84 +
                    ((u8)self->ext.wargpuff.unk89 * 0xC0);
                break;
            }
            self->ext.wargpuff.unk84 = self->ext.wargpuff.unk84 & 0xFFF;
            self->rotZ = self->ext.generic.unk84.S16.unk0 & 0xFFF;
            temp_s0 = self->ext.generic.unk88.U8.unk1 * 0x140;
            temp_s0 /= 28;
            self->velocityX = temp_s0 * rsin(self->ext.wargpuff.unk84);
            self->velocityY = -(temp_s0 * rcos(self->ext.wargpuff.unk84));
            self->step_s++;
        }

        if (self->animFrameIdx >= 13) {
            velocityX = self->velocityX;
            if (velocityX < 0) {
                adjVelocityX = velocityX + 3;
            } else {
                adjVelocityX = velocityX;
            }
            self->velocityX = velocityX - (adjVelocityX >> 2);

            velocityY = self->velocityY;
            if (velocityY < 0) {
                adjVelocityY = velocityY + 3;
            } else {
                adjVelocityY = velocityY;
            }
            self->velocityY = velocityY - (adjVelocityY >> 2);
        }
        MoveEntity();
        if (AnimateEntity((u8*)self->ext.wargpuff.unk80, self) == 0) {
            DestroyEntity(self);
        }
        break;

    case 4:
        if (self->step_s == 0) {
            rnd = Random();
            self->velocityY = FIX(-0.75);
            self->facingLeft = rnd & 1;
            self->rotX = 0xC0;
            self->drawFlags |= 1;
            self->step_s++;
        }
        MoveEntity();
        if (AnimateEntity((u8*)self->ext.wargpuff.unk80, self) == 0) {
            DestroyEntity(self);
        }
        break;
    }
}
