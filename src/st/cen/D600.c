/*
 * File: D600.c
 * Overlay: CEN
 * Description: Center Cube Area (Final Boss)
 */

#include "cen.h"
#include "game.h"

// background block of rock
void EntityBackgroundBlock(Entity* self) {
    ObjInit2* obj = &D_80180490[self->params].animSet;

    if (self->step == 0) {
        InitializeEntity(g_eInitGeneric2);
        self->animSet = obj->animSet;
        self->zPriority = obj->zPriority;
        self->unk5A = obj->unk4.s;
        self->palette = obj->palette;
        self->drawFlags = obj->drawFlags;
        self->drawMode = obj->drawMode;

        if (obj->unkC != 0) {
            self->flags = obj->unkC;
        }

        if (self->params == 1) {
            self->rotY = 0x200;
            self->rotX = 0x200;
        }
    }
    AnimateEntity(obj->unk10, self);
}

INCLUDE_ASM("st/cen/nonmatchings/D600", EntityUnkId12);

void EntityUnkId01(Entity* self) {
    Entity* newEntity;
    u16* ptr;
    s32 j;
    s32 i;
    u16 params = self->params >> 0xC;

    if (self->step == 0) {
        InitializeEntity(D_80180404);
        self->zPriority = 0xB0;
        self->drawMode = D_801805B4[params];
        newEntity = &self[1];
        self->hitboxHeight = D_80180594[params];
        self->animSet = D_801805A4[params];
        DestroyEntity(newEntity);
        CreateEntityFromEntity(E_BACKGROUND_BLOCK, self, newEntity);
        if (params != 0) {
            self[1].posY.i.hi -= 32;
        } else {
            self[1].posY.i.hi -= 16;
        }
        newEntity->params = 1;
    }

    AnimateEntity(D_80180574[params], self);

    if (self->unk44 != 0) {
        g_api.PlaySfx(NA_SE_BREAK_CANDLE);
        newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (newEntity != 0) {
            CreateEntityFromCurrentEntity(E_EXPLOSION, newEntity);
            newEntity->params = D_8018059C[params] | 0x10;
        }

        for (ptr = &D_801805BC, i = 0; i < 4; i++) {
            newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (newEntity != 0) {
                CreateEntityFromEntity(0x80, self, newEntity);
                newEntity->posX.i.hi += *ptr;
                ptr++;
                newEntity->posY.i.hi = newEntity->posY.i.hi + *ptr;
                ptr++;
                if (params != 0) {
                    newEntity->posY.i.hi -= 20;
                }
                newEntity->params = i;
            }
        }

        if (params != 0) {
            for (j = 0; j < 3; j++) {
                newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (newEntity != 0) {
                    CreateEntityFromEntity(0x80, self, newEntity);
                    newEntity->posX.i.hi += *ptr;
                    ptr++;
                    newEntity->posY.i.hi += *ptr;
                    ptr++;
                    newEntity->params = j + 4;
                }
            }
        }
        ReplaceBreakableWithItemDrop(self);
        DestroyEntity(&self[1]);
    }
}

void func_8018DB18(Entity* self) {
    Entity* newEntity;
    Collider collider;
    Primitive* prim;
    s16 primIndex;
    s32 facing;
    s16 temp;
    s32 temp2;
    s32 temp3;

    switch (self->step) {
    case 0:
        InitializeEntity(D_80180404);
        self->zPriority = 0xB0;
        self->drawFlags = FLAG_DRAW_ROTZ;
        self->animCurFrame = self->params + 28;
        facing = GetSideToPlayer() & 1;

        temp = (Random() & 30) + 8;
        self->ext.generic.unk80.modeS16.unk0 = temp;
        if (self->facingLeft != 0) {
            self->ext.generic.unk80.modeS16.unk0 = -temp;
        }

        if (self->params >= 4) {
            self->ext.generic.unk80.modeS16.unk0 =
                -self->ext.generic.unk80.modeS16.unk0;
        }

        if (facing == 0) {
            self->velocityX = FIX(-1);
        } else {
            self->velocityX = FIX(1);
        }

        temp3 = 0x8000;
        temp2 = Random() << 8;
        self->velocityX = self->velocityX + temp3 - temp2;
        self->velocityY = FIX(-3);
        self->velocityY = (self->params >> 1) * 0x6000 - 0x30000;
        if (self->params == 6) {
            self->velocityX = 0;
            self->velocityY = 0;
            self->step = 2;
        }

        self->primIndex = 0;
        if (self->params == 0) {
            primIndex = g_api.AllocPrimitives(PRIM_GT4, 2);
            if (primIndex != -1) {
                prim = &g_PrimBuf[primIndex];
                self->primIndex = primIndex;
                self->flags |= FLAG_HAS_PRIMS;
                UnkPolyFunc2(prim);
                prim->tpage = 0x1A;
                prim->clut = 0x159;
                prim->u0 = prim->u2 = 0x40;
                prim->u1 = prim->u3 = 0x60;
                prim->v0 = prim->v1 = 0;
                prim->v2 = prim->v3 = 0x20;
                prim->next->x1 = self->posX.i.hi + 4;
                prim->next->y0 = self->posY.i.hi - 8;
                facing = LOH(prim->next->r2) = 32;
                LOH(prim->next->b2) = facing;
                prim->next->b3 = 16;
                prim->priority = 0xB2;
                prim->drawMode = 0x37;
            }
        }
        break;

    case 1:
        MoveEntity();
        self->rotZ += self->ext.generic.unk80.modeS16.unk0;
        self->velocityY += FIX(0.25);
        g_api.CheckCollision(
            self->posX.i.hi, self->posY.i.hi + 6, &collider, 0);
        if (collider.effects & 1) {
            self->posY.i.hi += collider.unk18;
            self->velocityY = -self->velocityY / 2;
            self->velocityX -= self->velocityX / 3;
            if (self->velocityY > FIX(-0.625)) {
                newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (newEntity != 0) {
                    CreateEntityFromEntity(
                        E_INTENSE_EXPLOSION, self, newEntity);
                    newEntity->params = 16;
                }
                DestroyEntity(self);
                break;
            }
        }

        if (self->primIndex != 0) {
            prim = &g_PrimBuf[self->primIndex];
            UnkPrimHelper(prim);
            LOH(prim->next->r2) = LOH(prim->next->b2) += 4;
            if (LOH(prim->next->r2) > 64) {
                prim->next->b3 += 252;
                if (prim->next->b3 == 0) {
                    g_api.FreePrimitives(self->primIndex);
                    self->primIndex = 0;
                    self->flags &= ~FLAG_HAS_PRIMS;
                }
            }
        }
        break;
    }
}

void func_8018DF0C(void) {
    D_8019D384 = 2;
    D_8019D382 = 2;
    D_8019D386 = 0;
    D_8019D38A = 0;
    D_8019D38E = 0;
    D_8019D38F = 8;
    D_8019D37E = D_8019D380 + 0x14;
}

s32 func_8018DF60(s32 textDialogue) {
    Primitive* prim;
    s16 firstPrimIndex;

    firstPrimIndex = g_api.AllocPrimitives(PRIM_SPRT, 7);
    g_Dialogue.primIndex[2] = firstPrimIndex;
    if (firstPrimIndex == -1) {
        g_Dialogue.primIndex[2] = 0;
        return 0;
    }
    g_Dialogue.nextCharDialogue = textDialogue;
    g_Dialogue.unk3C = 0;
    g_Dialogue.primIndex[1] = -1;
    g_Dialogue.primIndex[0] = -1;
    func_8018DF0C();

    //! FAKE:
    if (prim && prim) {
    }

    prim = g_Dialogue.prim[0] = &g_PrimBuf[g_Dialogue.primIndex[2]];

    prim->drawMode = DRAW_HIDE;
    prim = g_Dialogue.prim[1] = prim->next;

    prim->drawMode = DRAW_HIDE;
    prim = g_Dialogue.prim[2] = prim->next;

    prim->drawMode = DRAW_HIDE;
    prim = g_Dialogue.prim[3] = prim->next;

    prim->drawMode = DRAW_HIDE;
    prim = g_Dialogue.prim[4] = prim->next;

    prim->drawMode = DRAW_HIDE;
    prim = g_Dialogue.prim[5] = prim->next;

    prim->type = 4;
    prim->drawMode = DRAW_HIDE;

    prim = prim->next;
    prim->type = 3;
    prim->r0 = prim->r1 = prim->r2 = prim->r3 = 0xFF;
    prim->g0 = prim->g1 = prim->g2 = prim->g3 = 0;
    prim->b0 = prim->b1 = prim->b2 = prim->b3 = 0;
    prim->x0 = prim->x2 = 4;
    prim->x1 = prim->x3 = 0xF8;
    prim->priority = 0x1FD;
    prim->drawMode = DRAW_HIDE;

    prim = prim->next;
    prim->type = 1;
    prim->x0 = 3;
    prim->y0 = 0x2F;
    prim->v0 = 0x4A;
    prim->r0 = prim->g0 = prim->b0 = 0xFF;
    prim->priority = 0x1FC;
    prim->drawMode = DRAW_HIDE;
    return 1;
}

void func_8018E124(s16 arg0) {
    RECT rect;

    rect.y = (arg0 * 12) + 384;
    rect.w = 64;
    rect.x = 0;
    rect.h = 12;
    ClearImage(&rect, 0, 0, 0);
}

void func_8018E180(void) {
    Primitive* prim;

    func_8018E124(g_Dialogue.nextCharY);
    prim = g_Dialogue.prim[g_Dialogue.nextCharY];
    prim->tpage = 0x10;
    prim->clut = g_Dialogue.clutIndex;
    prim->y0 = g_Dialogue.nextLineY;
    prim->u0 = 0;
    prim->x0 = g_Dialogue.startX;
    prim->x0 = prim->x0 + 4;
    prim->v0 = g_Dialogue.nextCharY * 0xC - 0x80;
    prim->u1 = 0xC0;
    prim->v1 = 0xC;
    prim->priority = 0x1FF;
    prim->drawMode = DRAW_DEFAULT;
}

// Creates primitives for the actor name at the head of the dialogue
void func_8018E238(u16 actorIndex, Entity* self) {
    Primitive* prim;
    s16 primIndex;
    s32 x;
    u16 chCount;
    const char* actorName;
    char ch;

    actorName = D_80180684[actorIndex];
    chCount = 0;
    while (true) {
        ch = *actorName++;
        if (ch == DIAG_EOL) {
            ch = *actorName++;
            if (ch == DIAG_EOS) {
                break;
            }
        }
        if (ch == MENUCHAR(' ')) {
            continue;
        }
        chCount++;
    }

    // Create chCount amount of sprites based on the actor name's letter count
    primIndex = g_api.AllocPrimitives(PRIM_SPRT, chCount);
    if (primIndex == -1) {
        DestroyEntity(self);
        return;
    }

    // Fill prims to render the actor name on screen
    prim = &g_PrimBuf[primIndex];
    g_Dialogue.primIndex[1] = primIndex;
    actorName = D_80180684[actorIndex];
    x = 0x38;
    while (prim != NULL) {
        ch = *actorName++;
        if (ch == MENUCHAR(' ')) {
            x += FONT_SPACE;
        } else {
            prim->type = PRIM_SPRT;
            prim->tpage = 0x1E;
            prim->clut = 0x196;
            prim->u0 = (ch & 0x0F) * FONT_W;
            prim->v0 = (ch & 0xF0) / (FONT_H / 4);
            prim->v1 = FONT_H;
            prim->u1 = FONT_W;
            prim->priority = 0x1FF;
            prim->drawMode = DRAW_HIDE;
            prim->x0 = x;
            prim->y0 = g_Dialogue.startY + 6;
            prim = prim->next;
            x += FONT_GAP;
        }
    }
}

void func_8018E3BC(s32 arg0) {
    g_Dialogue.unk40 = arg0 + 0x100000;
    g_Dialogue.timer = 0;
    g_Dialogue.unk3C = 1;
}

void func_8018E3E8(void) {
    Entity* entity;
    u16 startTimer;
    u8 entityIndex;

    g_Dialogue.timer++;
    // protect from overflows
    if (g_Dialogue.timer > 0xFFFE) {
        g_Dialogue.unk3C = 0;
        return;
    }

    while (true) {
        // Start the dialogue script only if the start timer has passed
        startTimer = (*g_Dialogue.unk40++ << 8) | *g_Dialogue.unk40++;
        if (g_Dialogue.timer < startTimer) {
            // Re-evaluate the condition at the next frame
            g_Dialogue.unk40 -= 2;
            return;
        }

        switch (*g_Dialogue.unk40++) {
        case 0:
            entityIndex = *g_Dialogue.unk40++;
            entity = &g_Entities[STAGE_ENTITY_START + entityIndex];
            DestroyEntity(entity);

            entity->entityId = *g_Dialogue.unk40++;
            entity->pfnUpdate = PfnEntityUpdates[entity->entityId - 1];
            entity->posX.i.hi = *g_Dialogue.unk40++ * 0x10;
            entity->posX.i.hi = *g_Dialogue.unk40++ | entity->posX.i.hi;
            entity->posY.i.hi = *g_Dialogue.unk40++ * 0x10;
            entity->posY.i.hi = *g_Dialogue.unk40++ | entity->posY.i.hi;
            entity->posX.i.hi -= g_Tilemap.scrollX.i.hi;
            entity->posY.i.hi -= g_Tilemap.scrollY.i.hi;
            break;

        case 1:
            entityIndex = *g_Dialogue.unk40++;
            entity = &g_Entities[STAGE_ENTITY_START + entityIndex];
            DestroyEntity(entity);
            break;

        case 2:
            if (!((D_8019D424 >> *g_Dialogue.unk40) & 1)) {
                g_Dialogue.unk40--;
                return;
            }
            D_8019D424 &= ~(1 << *g_Dialogue.unk40++);
            break;

        case 3:
            D_8019D424 |= 1 << *g_Dialogue.unk40++;
            break;
        }
    }
}

// Animates the portrait size of the actor by enlarging or shrinking it
void func_8018E6C4(u8 ySteps) {
    Primitive* prim;
    s32 primIndex;
    s32 i;

    primIndex = g_Dialogue.nextCharY + 1;
    while (primIndex >= 5) {
        primIndex -= 5;
    }
    if (g_CurrentEntity->step_s == 0) {
        prim = g_Dialogue.prim[primIndex];
        prim->v1 -= ySteps;
        prim->v0 += ySteps;
        if (prim->v1 == 0) {
            g_CurrentEntity->step_s++;
            prim->drawMode = DRAW_HIDE;
        }
    }

    for (i = 0; i < 5; i++) {
        if (i != primIndex) {
            prim = g_Dialogue.prim[i];
            prim->y0 -= ySteps;
        }
    }
    g_Dialogue.portraitAnimTimer++;
}

INCLUDE_ASM("st/cen/nonmatchings/D600", EntityUnkId16);

void func_8018F890(s16 arg0) {
    s16 temp_v0 = arg0 - g_Tilemap.height;

    if (temp_v0 > 1) {
        g_Tilemap.height++;
    } else if (temp_v0 < -1) {
        g_Tilemap.height--;
    } else {
        g_Tilemap.height = arg0;
    }
}

void func_8018F8EC(u16 index) {
    Tilemap* tilemap = &g_Tilemap;
    u16 tilePos = 0x5B6;
    u16* tileLayoutPtr = &D_8018068C[index * 4];
    s32 i;
    s32 j;

    for (i = 0; i < 2; i++) {
        for (j = 0; j < 4; j++) {
            tilemap->fg[tilePos] = *tileLayoutPtr;
            tileLayoutPtr++;
            tilePos++;
        }
        tilePos += 0x2C;
    }
}

// platform that lifts you into chamber, starts cutscene, gives you holy glasses
void EntityPlatform(Entity* self) {
    Tilemap* tilemap = &g_Tilemap;
    Entity* player = &PLAYER;
    Primitive* prim;
    s16 primIndex;
    s16 temp_a0;
    s16 temp_s1;
    s16 temp_v0;
    s16 temp_v1_4;
    u16 temp_a1;

    self->posY.i.hi -= 8;
    temp_a1 = func_80195318(self, 0x20, 0x11, 4);
    temp_s1 = player->posX.i.hi + g_Tilemap.scrollX.i.hi;
    temp_v0 = self->posY.i.hi + g_Tilemap.scrollY.i.hi;

    switch (self->step) {
    case 0:
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
        if (primIndex != -1) {
            InitializeEntity(g_EInitGeneric);
            self->animSet = ANIMSET_OVL(2);
            self->animCurFrame = 9;
            self->zPriority = 0x80;

            if (g_CastleFlags[216] != 0) {
                self->step = 9;
            }

            func_8018F8EC(0);
            prim = &g_PrimBuf[primIndex];
            self->primIndex = primIndex;
            self->flags |= FLAG_HAS_PRIMS;
            prim->tpage = 0xF;
            prim->clut = 2;
            prim->u0 = prim->u2 = 0xA0;
            prim->u1 = prim->u3 = 0xB0;
            prim->v0 = prim->v1 = 0xA1;
            prim->v2 = prim->v3 = 0xA7;
            prim->priority = 0x7F;
            prim->drawMode = 2;
        }
        break;

    case 1:
        if ((GetDistanceToPlayerX() < 32) &&
            ((self->posY.i.hi - player->posY.i.hi) < 80)) {
            D_8003C8B8 = 0;
            g_unkGraphicsStruct.unk0 = 1;
            if (g_Player.unk0C & PLAYER_STATUS_BAT_FORM) {
                g_Player.padSim = PAD_R1;
            } else if (g_Player.unk0C & PLAYER_STATUS_MIST_FORM) {
                g_Player.padSim = PAD_L1;
            } else if (g_Player.unk0C & PLAYER_STATUS_WOLF_FORM) {
                g_Player.padSim = PAD_R2;
            } else if (temp_s1 > 384) {
                g_Player.padSim = PAD_LEFT;
            } else if (temp_s1 < 384) {
                g_Player.padSim = PAD_RIGHT;
            } else {
                g_Player.padSim = 0;
            }
            g_Entities[1].ext.generic.unk7C.S8.unk0 = 0;
            g_Player.D_80072EFC = 1;
            self->step++;
        }
        break;

    case 2:
        g_Player.padSim = 0;
        if (g_Player.unk0C & PLAYER_STATUS_TRANSFORM) {
            if (g_Timer & 1) {
                if (g_Player.unk0C & PLAYER_STATUS_BAT_FORM) {
                    g_Player.padSim = PAD_R1;
                } else if (g_Player.unk0C & PLAYER_STATUS_MIST_FORM) {
                    g_Player.padSim = PAD_L1;
                } else if (g_Player.unk0C & PLAYER_STATUS_WOLF_FORM) {
                    g_Player.padSim = PAD_R2;
                }
            }
        } else {
            if ((temp_a1 != 0) || (g_Player.pl_vram_flag & 1)) {
                if (temp_s1 > 384) {
                    g_Player.padSim = PAD_LEFT;
                } else if (temp_s1 < 384) {
                    g_Player.padSim = PAD_RIGHT;
                }
                self->step++;
            }
        }
        g_Player.D_80072EFC = 1;
        break;

    case 3:
        if (g_Player.padSim == 0x8000) {
            if (temp_s1 <= 384) {
                g_Player.padSim = 0;
            }
        } else if ((g_Player.padSim == 0x2000) && (temp_s1 >= 384)) {
            g_Player.padSim = 0;
        }
        if (g_Player.padSim == 0) {
            g_Player.padSim = PAD_LEFT;
            player->posX.i.hi = 384 - tilemap->scrollX.i.hi;
            self->step++;
            g_api.PlaySfx(SE_CEN_ELEVATOR_MOVE);
            D_8019D424 |= 1;
            tilemap->height = ((s16)tilemap->scrollY.i.hi + 0x100);
            func_8018F8EC(0);
        }
        g_Player.D_80072EFC = 1;
        break;

    case 4:
        g_Player.padSim = 0;
        g_Player.D_80072EFC = 1;
        player->posX.i.hi = 384 - tilemap->scrollX.i.hi;
        if (temp_v0 > 496) {
            self->posY.i.hi--;
            player->posY.i.hi--;
            D_80097488.y.i.hi--;
        } else {
            g_api.PlaySfx(SE_CEN_PLATFORM_STOP);
            if (player->facingLeft == 0) {
                g_Player.padSim = PAD_LEFT;
            }
            D_8019D424 |= 4;
            self->step++;
        }
        func_8018F890(0x200);
        break;

    case 5:
        func_8018F890(0x200);
        g_Player.padSim = 0;
        g_Player.D_80072EFC = 1;

        if (D_8019D424 & 8) {
            CreateEntityFromCurrentEntity(E_EQUIP_ITEM_DROP, &g_Entities[204]);
            g_Entities[204].params = NUM_HAND_ITEMS + ITEM_HOLY_GLASSES;
            g_Entities[204].step = 5;
            g_Entities[204].flags = 0;
            self->step++;
        }
        break;

    case 6:
        if (D_8019D424 & 2) {
            self->step++;
            g_api.PlaySfx(SE_CEN_ELEVATOR_MOVE);
        }
        g_Player.padSim = 0;
        g_Player.D_80072EFC = 1;
        break;

    case 7:
        if (temp_v0 < 592) {
            self->posY.i.hi++;
            player->posY.i.hi++;
            D_80097488.x.i.hi++;
        } else {
            D_8003C8B8 = 1;
            if (g_unkGraphicsStruct.unk0 != 0) {
                g_unkGraphicsStruct.unk0 = 0;
            }
            g_Entities[1].ext.generic.unk7C.S8.unk0 = 1;
            self->step++;
            g_api.PlaySfx(SE_CEN_PLATFORM_STOP);
        }
        func_8018F890(0x300);
        g_Player.padSim = 0;
        g_Player.D_80072EFC = 1;
        break;

    case 8:
        func_8018F890(0x300);
        if (tilemap->height == 0x300) {
            self->step++;
        }
        break;

    case 9:
        break;
    }

    prim = &g_PrimBuf[self->primIndex];
    temp_a0 = self->posX.i.hi - 8;
    temp_v1_4 = self->posX.i.hi + 8;
    self->posY.i.hi += 8;
    prim->x0 = prim->x2 = temp_a0;
    prim->x1 = prim->x3 = temp_v1_4;
    prim->y0 = prim->y1 = self->posY.i.hi + 15;
    prim->y2 = prim->y3 = 0x268 - tilemap->scrollY.i.hi;
}

// Black layer that covers room interior and lights up when cutscene starts
void EntityRoomDarkness(Entity* self) {
    Primitive* prim;
    s16 primIndex;
    s16 temp_a1;
    s16 temp_a2;
    s16 temp_a3;
    s16 temp_t0;
    s16 temp_a0;
    s16 temp_v0;
    s16 temp_v1;

    switch (self->step) {
    case 0:
        /* Has player seen Maria Holy Glasses Cutscene? */
        if (g_CastleFlags[216] != 0) {
            DestroyEntity(self);
            return;
        }

        primIndex = g_api.AllocPrimitives(PRIM_G4, 2);
        if (primIndex != -1) {
            InitializeEntity(g_EInitGeneric);
            prim = &g_PrimBuf[primIndex];
            self->primIndex = primIndex;
            self->animSet = 0;
            temp_a2 = self->posX.i.hi - 112;
            temp_a3 = self->posX.i.hi + 112;
            temp_t0 = self->posX.i.hi - 32;
            temp_a0 = self->posX.i.hi + 32;
            self->flags |= FLAG_HAS_PRIMS;
            temp_v1 = 0x178 - g_Tilemap.scrollY.i.hi;
            temp_v0 = temp_v1 - 0x58;
            temp_a1 = temp_v1 + 0x68;
            self->posY.i.hi = temp_v1;
            prim->y0 = prim->y1 = temp_v0;
            prim->x0 = prim->x2 = temp_a2;
            prim->x1 = prim->x3 = temp_a3;
            prim->y2 = prim->y3 = temp_a1;
            prim->r0 = prim->r1 = prim->r2 = prim->r3 = prim->g0 = prim->g1 =
                prim->g2 = prim->g3 = prim->b0 = prim->b1 = prim->b2 =
                    prim->b3 = 255;
            prim->priority = 0x88;
            prim->drawMode = 0x57;
            prim = prim->next;
            prim->x0 = prim->x2 = temp_t0;
            prim->x1 = prim->x3 = temp_a0;
            prim->y0 = prim->y1 = temp_a1;
            prim->y2 = prim->y3 = temp_v1 + 0x88;
            prim->r0 = prim->r1 = prim->g0 = prim->g1 = prim->b0 = prim->b1 =
                255;
            prim->r2 = prim->r3 = prim->g2 = prim->g3 = prim->b2 = prim->b3 = 0;
            prim->priority = 0x88;
            prim->drawMode = 0x57;
        }
        break;

    case 1:
        if (D_8019D424 & 4) {
            prim = &g_PrimBuf[self->primIndex];
            prim->r0 = prim->r1 = prim->r2 = prim->r3 = prim->g0 = prim->g1 =
                prim->g2 = prim->g3 = prim->b0 = prim->b1 = prim->b2 =
                    prim->b3 -= 1;
            prim = prim->next;
            prim->r1 = prim->g0 = prim->g1 = prim->b0 = prim->b1 = prim->r0 =
                prim->b1 - 1;
            if (prim->r0 == 0) {
                self->step++;
            }
        }
        break;

    case 2:
        prim = &g_PrimBuf[self->primIndex];
        prim->drawMode = DRAW_HIDE;
        prim = prim->next;
        prim->drawMode = DRAW_HIDE;
        self->step++;
        break;
    }
}

void EntityMaria(Entity* self) {
    if (self->step == 0) {
        /* Has player seen Maria Holy Glasses Cutscene? */
        if (g_CastleFlags[216] != 0) {
            DestroyEntity(self);
            return;
        }
        InitializeEntity(D_80180428);
        self->flags = FLAG_UNK_08000000;
        self->animSet = ANIMSET_OVL(1);
        self->animCurFrame = 10;
        self->unk5A = 0x48;
        self->palette = 0x210;
        self->zPriority = 0x80;
    }
}

s16 func_8019040C(Primitive* prim, s16 arg1) {
    s16 ret = arg1;
    s16 temp_v0;

    prim->x2 = arg1;
    prim->x0 = arg1;
    ret += 0x20;
    prim->drawMode = 2;
    prim->v0 = prim->v1 = 0x50;
    prim->v2 = prim->v3 = 0x60;
    prim->y0 = prim->y1 = 0x2C;
    prim->y2 = prim->y3 = 0x3C;
    prim->u0 = prim->u2 = 2;

    if (ret > 0xB0) {
        temp_v0 = 0xB2 - arg1;
        prim->u1 = prim->u3 = temp_v0;
        ret = 0;
        prim->x1 = prim->x3 = 0xB0;
    } else {
        prim->u1 = prim->u3 = 0x22;
        prim->x1 = prim->x3 = ret;
    }
    return ret;
}

s16 func_801904B8(Primitive* prim, s16 arg1) {
    prim->u0 = prim->u2 = 0x50;
    prim->u1 = prim->u3 = 0x60;
    prim->drawMode = 2;
    prim->x0 = prim->x2 = g_CurrentEntity->posX.i.hi - 8;
    prim->x1 = prim->x3 = g_CurrentEntity->posX.i.hi + 8;
    prim->y2 = prim->y3 = arg1;
    arg1 -= 32;
    prim->v2 = prim->v3 = 38;
    prim->v0 = prim->v1 = 6;
    prim->y0 = prim->y1 = arg1;
    return arg1;
}

// Elevator when not moving (ID 1A)
void EntityElevatorStationary(Entity* self) {
    Entity* player = &PLAYER;
    Primitive* prim;
    s16 primIndex;
    s16 posX, posY;
    s16 temp;

    switch (self->step) {
    case 0:
        InitializeEntity(D_8018047C);
        self->animCurFrame = 3;
        self->zPriority = player->zPriority + 2;
        CreateEntityFromCurrentEntity(E_ID_1B, &self[-1]);
        self[-1].params = 1;
        CreateEntityFromCurrentEntity(E_ID_1B, &self[-2]);
        self[-2].params = 2;
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 12);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        prim = &g_PrimBuf[primIndex];
        self->primIndex = primIndex;
        self->ext.prim = prim;
        self->flags |= FLAG_HAS_PRIMS;
        prim->tpage = 0x12;
        prim->clut = 0x223;
        temp = prim->v1 = prim->u0 = prim->u2 = 0x28;
        prim->v2 = prim->v3 = prim->u1 = prim->u3 = 0x38;
        prim->v0 = temp;
        prim->priority = 0x6B;
        prim->drawMode = DRAW_HIDE;
        prim = prim->next;

        while (prim != NULL) {
            prim->tpage = 0x12;
            prim->clut = 0x223;
            prim->priority = 0x6A;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }

        if ((s16)(player->posY.i.hi + g_Tilemap.scrollY.i.hi) < 80) {
            self->posY.i.hi = player->posY.i.hi;
            player->posX.i.hi = self->posX.i.hi;
            self->animCurFrame = 10;
            g_Entities[1].ext.stub[0x00] = 1;
            SetStep(3);
        }
        break;

    case 1:
        if (*(u8*)&self[-1].ext.stub[0x4]) {
            posX = self->posX.i.hi - player->posX.i.hi;
            if (g_pads[0].pressed & PAD_UP) {
                if (abs(posX) < 8) {
                    g_Entities[1].ext.stub[0x00] = 1;
                    g_Player.D_80072EFC = 2;
                    g_Player.padSim = 0;
                    PLAYER.velocityX = 0;
                    PLAYER.velocityY = 0;
                    self->step = 2;
                }
            }
        }
        break;

    case 3:
        g_Player.D_80072EFC = 2;
        g_Player.padSim = 0;
        switch (self->step_s) {
        case 0:
            self->posY.val += FIX(0.5);
            player->posY.i.hi++;
            posY = g_Tilemap.scrollY.i.hi + self->posY.i.hi;
            if ((g_Timer % 16) == 0) {
                func_8019A328(SE_CEN_ELEVATOR_MOVE);
            }
            if (posY == 0x74) {
                self->step_s++;
            }
            break;

        case 1:
            if (AnimateEntity(D_80180780, self) == 0) {
                self->animFrameIdx = 0;
                self->animFrameDuration = 0;
                g_Entities[1].ext.stub[0x00] = 0;
                self->step_s = 0;
                self->step = 1;
            }
            if (self->animFrameIdx == 4 && self->animFrameDuration == 0) {
                g_api.PlaySfx(SE_CEN_ELEVATOR_DOOR);
            }
        }
        break;

    case 2:
        g_Player.D_80072EFC = self->step;
        g_Player.padSim = 0;

        switch (self->step_s) {
        case 0:
            if (AnimateEntity(D_80180768, self) == 0) {
                self->animFrameIdx = 0;
                self->animFrameDuration = 0;
                self->step_s++;
            }
            if (self->animFrameIdx == 4 && self->animFrameDuration == 0) {
                g_api.PlaySfx(SE_CEN_ELEVATOR_DOOR);
            }
            break;

        case 1:
            self->posY.val -= FIX(0.5);
            if ((g_Timer % 16) == 0) {
                func_8019A328(SE_CEN_ELEVATOR_MOVE);
            }
            break;

        case 2:
            if (AnimateEntity(&D_80180780, self) == 0) {
                self->animFrameIdx = 0;
                self->animFrameDuration = 0;
                g_Entities[1].ext.stub[0x00] = 0;
                self->step_s = 0;
                self->step = 1;
            }
            break;
        }
    }
    prim = self->ext.prim;
    prim->x0 = prim->x2 = self->posX.i.hi - 8;
    prim->x1 = prim->x3 = self->posX.i.hi + 8;
    temp = self->posY.i.hi;
    prim->drawMode = 2;
    prim->y2 = prim->y3 = temp - 0x1F;
    prim->y0 = prim->y1 = temp - 0x2F;
    prim = prim->next;

    posY = self->posY.i.hi - 40;
    while (prim != NULL) {
        posY = func_801904B8(prim, posY);
        prim = prim->next;
        if (posY <= 0) {
            break;
        }
    }

    while (prim != NULL) {
        prim->drawMode = DRAW_HIDE;
        prim = prim->next;
    }

    if (abs(self->posY.i.hi) > 384) {
        DestroyEntity(self);
    }
}

void EntityUnkId1B(Entity* self) {
    Entity* entity = &self[self->params];
    s32 step = self->step;

    switch (self->step) {
    case 0:
        InitializeEntity(D_8018047C);
        if (self->params & 16) {
            self->animCurFrame = self->params & 15;
            self->zPriority = 0x6A;
            self->step = 2;
            return;
        }
        self->animCurFrame = 0;
        break;

    case 1:
        self->posX.i.hi = entity->posX.i.hi;
        if (self->params == step) {
            self->posY.i.hi = entity->posY.i.hi + 35;
            self->ext.generic.unk80.modeS8.unk0 = func_80195318(self, 12, 8, 4);
        } else {
            self->posY.i.hi = entity->posY.i.hi - 24;
            self->ext.generic.unk80.modeS8.unk0 = func_80195318(self, 12, 8, 6);
        }
        break;
    }
}

// Elevator when moving, fixes player into position (ID 1C)
void EntityMovingElevator(Entity* self) {
    Entity* player = &PLAYER;
    Primitive* prim;
    s16 primIndex;
    s32 step;
    s16 posY;
    s16 temp;

    switch (self->step) {
    case 0:
        InitializeEntity(D_8018047C);
        self->animCurFrame = 3;
        self->zPriority = player->zPriority + 2;
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 12);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        prim = &g_PrimBuf[primIndex];
        self->primIndex = primIndex;
        self->ext.prim = prim;
        self->flags |= FLAG_HAS_PRIMS;
        while (prim != NULL) {
            prim->tpage = 0x12;
            prim->u0 = prim->u2 = 0x50;
            prim->u1 = prim->u3 = 0x60;
            prim->v0 = prim->v1 = 6;
            prim->v2 = prim->v3 = 0x26;
            prim->clut = 0x223;
            prim->priority = 0x6A;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }

        if (player->posY.i.hi > 192) {
            step = 2;
            self->posY.i.hi = player->posY.i.hi;
            player->posX.i.hi = self->posX.i.hi;
        } else {
            step = 3;
            self->posY.i.hi = player->posY.i.hi;
            player->posX.i.hi = self->posX.i.hi;
        }

        self->animCurFrame = 10;
        g_Entities[1].ext.stub[0x00] = 1;
        SetStep(step);
        break;

    case 3:
        g_Player.D_80072EFC = 2;
        g_Player.padSim = 0;
        self->posY.val += FIX(0.5);
        player->posY.i.hi = self->posY.i.hi + 4;
        g_Player.pl_vram_flag = 0x41;
        break;

    case 2:
        g_Player.D_80072EFC = self->step;
        g_Player.padSim = 0;
        self->posY.val -= FIX(0.5);
        player->posY.i.hi = self->posY.i.hi + 4;
        g_Player.pl_vram_flag = 0x41;
        break;
    }
    prim = self->ext.prim;
    prim->x0 = prim->x2 = self->posX.i.hi - 8;
    prim->x1 = prim->x3 = self->posX.i.hi + 8;
    temp = self->posY.i.hi;
    prim->drawMode = 2;
    prim->y2 = prim->y3 = temp - 0x1F;
    prim->y0 = prim->y1 = temp - 0x2F;
    prim = prim->next;

    posY = self->posY.i.hi - 40;

    while (prim != NULL) {
        posY = func_801904B8(prim, posY);
        prim = prim->next;
        if (posY <= 0) {
            break;
        }
        prim = prim->next;
    }

    while (prim != NULL) {
        prim->drawMode = DRAW_HIDE;
        prim = prim->next;
    }

    if (abs(self->posY.i.hi) > 384) {
        DestroyEntity(self);
    }
}
