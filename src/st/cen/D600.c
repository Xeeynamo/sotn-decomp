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
        InitializeEntity(D_80180458);
        self->animSet = obj->animSet;
        self->zPriority = obj->zPriority;
        self->unk5A = obj->unk4.s;
        self->palette = obj->palette;
        self->unk19 = obj->unk8;
        self->blendMode = obj->blendMode;

        if (obj->unkC != 0) {
            self->flags = obj->unkC;
        }

        if (self->params == 1) {
            self->unk1C = 0x200;
            self->unk1A = 0x200;
        }
    }
    func_80194394(obj->unk10, self);
}

INCLUDE_ASM("asm/us/st/cen/nonmatchings/D600", EntityUnkId12);

void EntityUnkId01(Entity* self) {
    Entity* newEntity;
    u16* ptr;
    s32 j;
    s32 i;
    u16 params = self->params >> 0xC;

    if (self->step == 0) {
        InitializeEntity(D_80180404);
        self->zPriority = 0xB0;
        self->blendMode = D_801805B4[params];
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

    func_80194394(D_80180574[params], self);

    if (self->unk44 != 0) {
        g_api.PlaySfx(NA_SE_BREAK_CANDLE);
        newEntity = AllocEntity(D_8007D858, &D_8007D858[32]);
        if (newEntity != 0) {
            CreateEntityFromCurrentEntity(E_EXPLOSION, newEntity);
            newEntity->params = D_8018059C[params] | 0x10;
        }

        for (ptr = &D_801805BC, i = 0; i < 4; i++) {
            newEntity = AllocEntity(D_8007D858, &D_8007D858[32]);
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
                newEntity = AllocEntity(D_8007D858, &D_8007D858[32]);
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
        self->unk19 = 4;
        self->animCurFrame = self->params + 28;
        facing = GetSideToPlayer() & 1;

        temp = (Random() & 30) + 8;
        self->ext.generic.unk80.modeS16.unk0 = temp;
        if (self->facing != 0) {
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
                func_8019C620(prim, primIndex);
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
                prim->blendMode = 0x37;
            }
        }
        break;

    case 1:
        MoveEntity();
        self->rotAngle += self->ext.generic.unk80.modeS16.unk0;
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
            func_8019BED4(prim);
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

INCLUDE_ASM("asm/us/st/cen/nonmatchings/D600", func_8018DF60);

void func_8018E124(s16 arg0) {
    RECT rect;

    rect.y = (arg0 * 12) + 384;
    rect.w = 64;
    rect.x = 0;
    rect.h = 12;
    ClearImage(&rect, 0, 0, 0);
}

INCLUDE_ASM("asm/us/st/cen/nonmatchings/D600", func_8018E180);

INCLUDE_ASM("asm/us/st/cen/nonmatchings/D600", func_8018E238);

void func_8018E3BC(s32 arg0) {
    D_8019D3B8 = arg0 + 0x100000;
    D_8019D3B6 = 0;
    D_8019D3B4 = 1;
}

INCLUDE_ASM("asm/us/st/cen/nonmatchings/D600", func_8018E3E8);

INCLUDE_ASM("asm/us/st/cen/nonmatchings/D600", func_8018E6C4);

INCLUDE_ASM("asm/us/st/cen/nonmatchings/D600", EntityUnkId16);

void func_8018F890(s16 arg0) {
    s16 temp_v0 = arg0 - g_CurrentRoom.height;

    if (temp_v0 > 1) {
        g_CurrentRoom.height++;
    } else if (temp_v0 < -1) {
        g_CurrentRoom.height--;
    } else {
        g_CurrentRoom.height = arg0;
    }
}

void func_8018F8EC(u16 index) {
    Unkstruct8* t = &g_CurrentRoomTileLayout;
    u16 tilePos = 0x5B6;
    u16* tileLayoutPtr = &D_8018068C[index * 4];
    s32 i;
    s32 j;

    for (i = 0; i < 2; i++) {
        for (j = 0; j < 4; j++) {
            t->fg[tilePos] = *tileLayoutPtr;
            tileLayoutPtr++;
            tilePos++;
        }
        tilePos += 0x2C;
    }
}

// platform that lifts you into chamber, starts cutscene, gives you holy glasses
void EntityPlatform(Entity* self) {
    Unkstruct8* roomLayout = &g_CurrentRoomTileLayout;
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
    temp_s1 = player->posX.i.hi + g_Camera.posX.i.hi;
    temp_v0 = self->posY.i.hi + g_Camera.posY.i.hi;

    switch (self->step) {
    case 0:
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
        if (primIndex != -1) {
            InitializeEntity(D_80180434);
            self->animSet = ANIMSET_OVL(2);
            self->animCurFrame = 9;
            self->zPriority = 0x80;

            if (D_8003BDEC[216] != 0) {
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
            prim->blendMode = 2;
        }
        break;

    case 1:
        if ((GetDistanceToPlayerX() < 32) &&
            ((self->posY.i.hi - player->posY.i.hi) < 80)) {
            D_8003C8B8 = 0;
            *D_80097400 = 1;
            if (g_Player_unk0C & 1) {
                g_Player.D_80072EF4 = 8;
            } else if (g_Player_unk0C & 2) {
                g_Player.D_80072EF4 = 4;
            } else if (g_Player_unk0C & 4) {
                g_Player.D_80072EF4 = 2;
            } else if (temp_s1 > 384) {
                g_Player.D_80072EF4 = 0x8000;
            } else if (temp_s1 < 384) {
                g_Player.D_80072EF4 = 0x2000;
            } else {
                g_Player.D_80072EF4 = 0;
            }
            g_Entities[1].ext.generic.unk7C.S8.unk0 = 0;
            g_Player.D_80072EFC = 1;
            self->step++;
        }
        break;

    case 2:
        g_Player.D_80072EF4 = 0;
        if (g_Player_unk0C & 7) {
            if (g_blinkTimer & 1) {
                if (g_Player_unk0C & 1) {
                    g_Player.D_80072EF4 = 8;
                } else if (g_Player_unk0C & 2) {
                    g_Player.D_80072EF4 = 4;
                } else if (g_Player_unk0C & 4) {
                    g_Player.D_80072EF4 = 2;
                }
            }
        } else {
            if ((temp_a1 != 0) || (g_Player.pl_vram_flag & 1)) {
                if (temp_s1 > 384) {
                    g_Player.D_80072EF4 = 0x8000;
                } else if (temp_s1 < 384) {
                    g_Player.D_80072EF4 = 0x2000;
                }
                self->step++;
            }
        }
        g_Player.D_80072EFC = 1;
        break;

    case 3:
        if (g_Player.D_80072EF4 == 0x8000) {
            if (temp_s1 <= 384) {
                g_Player.D_80072EF4 = 0;
            }
        } else if ((g_Player.D_80072EF4 == 0x2000) && (temp_s1 >= 384)) {
            g_Player.D_80072EF4 = 0;
        }
        if (g_Player.D_80072EF4 == 0) {
            g_Player.D_80072EF4 = 0x8000;
            player->posX.i.hi = 384 - roomLayout->unkA;
            self->step++;
            g_api.PlaySfx(0x60D);
            D_8019D424 |= 1;
            roomLayout->unk48 = ((s16)roomLayout->unkE + 0x100);
            func_8018F8EC(0);
        }
        g_Player.D_80072EFC = 1;
        break;

    case 4:
        g_Player.D_80072EF4 = 0;
        g_Player.D_80072EFC = 1;
        player->posX.i.hi = 384 - roomLayout->unkA;
        if (temp_v0 > 496) {
            self->posY.i.hi--;
            player->posY.i.hi--;
            D_8009748E[0]--;
        } else {
            g_api.PlaySfx(0x64F);
            if (player->facing == 0) {
                g_Player.D_80072EF4 = 0x8000;
            }
            D_8019D424 |= 4;
            self->step++;
        }
        func_8018F890(0x200);
        break;

    case 5:
        func_8018F890(0x200);
        g_Player.D_80072EF4 = 0;
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
            g_api.PlaySfx(0x60D);
        }
        g_Player.D_80072EF4 = 0;
        g_Player.D_80072EFC = 1;
        break;

    case 7:
        if (temp_v0 < 592) {
            self->posY.i.hi++;
            player->posY.i.hi++;
            *D_8009748A += 1;
        } else {
            D_8003C8B8 = 1;
            if (*D_80097400 != 0) {
                *D_80097400 = 0;
            }
            g_Entities[1].ext.generic.unk7C.S8.unk0 = 1;
            self->step++;
            g_api.PlaySfx(0x64F);
        }
        func_8018F890(0x300);
        g_Player.D_80072EF4 = 0;
        g_Player.D_80072EFC = 1;
        break;

    case 8:
        func_8018F890(0x300);
        if (roomLayout->unk48 == 0x300) {
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
    prim->y2 = prim->y3 = 0x268 - roomLayout->unkE;
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
        if (D_8003BDEC[216] != 0) {
            DestroyEntity(self);
            return;
        }

        primIndex = g_api.AllocPrimitives(PRIM_G4, 2);
        if (primIndex != -1) {
            InitializeEntity(D_80180434);
            prim = &g_PrimBuf[primIndex];
            self->primIndex = primIndex;
            self->animSet = 0;
            temp_a2 = self->posX.i.hi - 112;
            temp_a3 = self->posX.i.hi + 112;
            temp_t0 = self->posX.i.hi - 32;
            temp_a0 = self->posX.i.hi + 32;
            self->flags |= FLAG_HAS_PRIMS;
            temp_v1 = 0x178 - g_Camera.posY.i.hi;
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
            prim->blendMode = 0x57;
            prim = prim->next;
            prim->x0 = prim->x2 = temp_t0;
            prim->x1 = prim->x3 = temp_a0;
            prim->y0 = prim->y1 = temp_a1;
            prim->y2 = prim->y3 = temp_v1 + 0x88;
            prim->r0 = prim->r1 = prim->g0 = prim->g1 = prim->b0 = prim->b1 =
                255;
            prim->r2 = prim->r3 = prim->g2 = prim->g3 = prim->b2 = prim->b3 = 0;
            prim->priority = 0x88;
            prim->blendMode = 0x57;
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
        prim->blendMode = BLEND_VISIBLE;
        prim = prim->next;
        prim->blendMode = BLEND_VISIBLE;
        self->step++;
        break;
    }
}

void EntityMaria(Entity* self) {
    if (self->step == 0) {
        /* Has player seen Maria Holy Glasses Cutscene? */
        if (D_8003BDEC[216] != 0) {
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
    prim->blendMode = 2;
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
    prim->blendMode = 2;
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
        CreateEntityFromCurrentEntity(E_ID1B, &self[-1]);
        self[-1].params = 1;
        CreateEntityFromCurrentEntity(E_ID1B, &self[-2]);
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
        prim->blendMode = BLEND_VISIBLE;
        prim = prim->next;

        while (prim != NULL) {
            prim->tpage = 0x12;
            prim->clut = 0x223;
            prim->priority = 0x6A;
            prim->blendMode = BLEND_VISIBLE;
            prim = prim->next;
        }

        if ((s16)(player->posY.i.hi + g_Camera.posY.i.hi) < 80) {
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
                if (ABS(posX) < 8) {
                    g_Entities[1].ext.stub[0x00] = 1;
                    g_Player.D_80072EFC = 2;
                    g_Player.D_80072EF4 = 0;
                    PLAYER.velocityX = 0;
                    PLAYER.velocityY = 0;
                    self->step = 2;
                }
            }
        }
        break;

    case 3:
        g_Player.D_80072EFC = 2;
        g_Player.D_80072EF4 = 0;
        switch (self->step_s) {
        case 0:
            self->posY.val += FIX(0.5);
            player->posY.i.hi++;
            posY = g_Camera.posY.i.hi + self->posY.i.hi;
            if ((g_blinkTimer % 16) == 0) {
                func_8019A328(0x60D);
            }
            if (posY == 0x74) {
                self->step_s++;
            }
            break;

        case 1:
            if (func_80194394(D_80180780, self) == 0) {
                self->animFrameIdx = 0;
                self->animFrameDuration = 0;
                g_Entities[1].ext.stub[0x00] = 0;
                self->step_s = 0;
                self->step = 1;
            }
            if (self->animFrameIdx == 4 && self->animFrameDuration == 0) {
                g_api.PlaySfx(0x675);
            }
        }
        break;

    case 2:
        g_Player.D_80072EFC = self->step;
        g_Player.D_80072EF4 = 0;

        switch (self->step_s) {
        case 0:
            if (func_80194394(D_80180768, self) == 0) {
                self->animFrameIdx = 0;
                self->animFrameDuration = 0;
                self->step_s++;
            }
            if (self->animFrameIdx == 4 && self->animFrameDuration == 0) {
                g_api.PlaySfx(0x675);
            }
            break;

        case 1:
            self->posY.val -= FIX(0.5);
            if ((g_blinkTimer % 16) == 0) {
                func_8019A328(0x60D);
            }
            break;

        case 2:
            if (func_80194394(&D_80180780, self) == 0) {
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
    prim->blendMode = 2;
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
        prim->blendMode = BLEND_VISIBLE;
        prim = prim->next;
    }

    if (ABS(self->posY.i.hi) > 384) {
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
            prim->blendMode = BLEND_VISIBLE;
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
        g_Player.D_80072EF4 = 0;
        self->posY.val += FIX(0.5);
        player->posY.i.hi = self->posY.i.hi + 4;
        g_Player.pl_vram_flag = 0x41;
        break;

    case 2:
        g_Player.D_80072EFC = self->step;
        g_Player.D_80072EF4 = 0;
        self->posY.val -= FIX(0.5);
        player->posY.i.hi = self->posY.i.hi + 4;
        g_Player.pl_vram_flag = 0x41;
        break;
    }
    prim = self->ext.prim;
    prim->x0 = prim->x2 = self->posX.i.hi - 8;
    prim->x1 = prim->x3 = self->posX.i.hi + 8;
    temp = self->posY.i.hi;
    prim->blendMode = 2;
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
        prim->blendMode = BLEND_VISIBLE;
        prim = prim->next;
    }

    if (ABS(self->posY.i.hi) > 384) {
        DestroyEntity(self);
    }
}
