#include "ric.h"

void DebugShowWaitInfo(const char* msg) {
    g_CurrentBuffer = g_CurrentBuffer->next;
    FntPrint(msg);
    if (g_DebugWaitInfoTimer++ & 4) {
        FntPrint("\no\n");
    }
    DrawSync(0);
    VSync(0);
    PutDrawEnv(&g_CurrentBuffer->draw);
    PutDispEnv(&g_CurrentBuffer->disp);
    FntFlush(-1);
}

void DebugInputWait(const char* msg) {
    while (PadRead(0))
        DebugShowWaitInfo(msg);
    while (PadRead(0) == 0)
        DebugShowWaitInfo(msg);
}

INCLUDE_ASM("asm/us/ric/nonmatchings/22380", func_8015E484);

void func_8015E7B4(Unkstruct_8010BF64* arg0) { // !FAKE:
    s32 temp = D_80154604;

    arg0->unk14 = temp;
    arg0->unk1C = temp = D_80154606;
    arg0->unk18 = D_801545EA[8] - 1;
    arg0->unk20 = D_801545EA[0] + 1;
}

INCLUDE_ASM("asm/us/ric/nonmatchings/22380", func_8015E800);

INCLUDE_ASM("asm/us/ric/nonmatchings/22380", func_8015EE28);

INCLUDE_ASM("asm/us/ric/nonmatchings/22380", func_8015F414);

INCLUDE_ASM("asm/us/ric/nonmatchings/22380", func_8015F680);

Entity* func_8015F8F8(s16 start, s16 end) {
    Entity* entity = &g_Entities[start];
    s16 i;

    for (i = start; i < end; i++, entity++) {
        if (entity->entityId == E_NONE) {
            return entity;
        }
    }
    return NULL;
}

Entity* func_8015F96C(s16 start, s16 end) {
    Entity* entity = &g_Entities[end - 1];
    s16 i;
    for (i = end - 1; i >= start; i--, entity--) {
        if (entity->entityId == E_NONE) {
            return entity;
        }
    }
    return NULL;
}

INCLUDE_ASM("asm/us/ric/nonmatchings/22380", func_8015F9F0);

void func_8015FA5C(s32 arg0) {
    D_80174FAC = D_80154674[arg0][0];
    D_80174FB0 = D_80154674[arg0][1];
    D_80174FB4 = D_80154674[arg0][2];
    D_80174FB8 = D_80154674[arg0][3];
}

void func_8015FAB8(Entity* entity) {
    u16 attack;
    SubweaponDef* subwpn = &D_80154688[entity->ext.generic.unkB0];

    if ((g_Player.D_80072F1A) != NULL) {
        attack = subwpn->attack * 2;
    } else {
        attack = subwpn->attack;
    }

    entity->attack = attack;
    entity->attackElement = subwpn->attackElement;
    entity->hitboxState = subwpn->sp1C;
    entity->nFramesInvincibility = subwpn->sp17;
    entity->unk58 = subwpn->sp18;
    entity->unk6A = subwpn->sp1E;
    entity->entityRoomIndex = subwpn->sp22;
    entity->attack = g_api.func_800FD664(entity->attack);
    func_8015F9F0(entity);
}

// We're playing as Richter and we used a subweapon (normal or crash)
s32 func_8015FB84(SubweaponDef* subwpn, s32 isItemCrash, s32 useHearts) {
    s32 pad[2]; // Needed so stack pointer moves properly
    u8 crashId;
    // Not an item crash. Just read the item in.
    if (isItemCrash == 0) {
        *subwpn = D_80154688[g_Status.subWeapon];
        if (g_Status.hearts >= subwpn->heartCost) {
            if (useHearts) {
                g_Status.hearts -= subwpn->heartCost;
            }
            return g_Status.subWeapon;
        }
    } else {
        // If it's a crash, load the subweapon by referencing our
        // subweapon's crash ID and loading that.
        crashId = D_80154688[g_Status.subWeapon].crashId;
        *subwpn = D_80154688[crashId];
        if (g_Status.hearts >= subwpn->heartCost) {
            if (useHearts) {
                g_Status.hearts -= subwpn->heartCost;
            }
            return g_Status.subWeapon;
        }
    }
    return -1;
}

INCLUDE_ASM("asm/us/ric/nonmatchings/22380", func_8015FDB0);

INCLUDE_ASM("asm/us/ric/nonmatchings/22380", func_8015FEA8);

// same as DRA/func_8011F074
void func_801601DC(Entity* entity) {
    s16 posX;
    s16 posY;

    switch (entity->step) {
    case 0:
        entity->flags = FLAG_UNK_20000 | FLAG_UNK_100000 | FLAG_UNK_08000000;
        entity->unk5A = 0x79;
        entity->animSet = ANIMSET_DRA(14);
        entity->zPriority = PLAYER.zPriority + 2;
        entity->palette = 0x819F;

        if (D_80174FFC & 1) {
            entity->blendMode = 0x70;
        } else {
            entity->blendMode = 0x10;
        }
        entity->unk1C = 0x40;
        entity->unk1A = 0x40;
        entity->unk4C = &D_80154924;
        D_80174FFC++;
        entity->unk6C = 0xFF;
        entity->unk19 = 0x33;
        posX = 10;
        posY = 15;
        entity->posY.i.hi = entity->posY.i.hi - posY + (rand() % 35);
        entity->posX.i.hi = entity->posX.i.hi - posX + (rand() % 20);
        entity->velocityY = -0x6000 - (rand() & 0x3FFF);
        entity->step++;
        break;

    case 1:
        if (entity->unk6C >= 17) {
            entity->unk6C += 248;
        }
        entity->posY.val += entity->velocityY;
        entity->unk1A += 8;
        entity->unk1C += 8;
        if (entity->animFrameDuration < 0) {
            func_80156C60(entity);
        }
        break;
    }
}

void func_801603B4(void) {}

void func_801603BC(void) {}

INCLUDE_ASM("asm/us/ric/nonmatchings/22380", func_801603C4);

Entity* func_801606BC(Entity* srcEntity, u32 arg1, s32 arg2) {
    /**
     * arg2 is unused, but needed to match other functions that call
     * this function, probably part of the code for a debug build
     */
    Entity* entity = func_8015F8F8(8, 0x10);

    if (entity != NULL) {
        func_80156C60(entity);
        entity->entityId = E_UNK_1;
        entity->ext.generic.unk8C.entityPtr = srcEntity;
        entity->posX.val = srcEntity->posX.val;
        entity->posY.val = srcEntity->posY.val;
        entity->facing = srcEntity->facing;
        entity->zPriority = srcEntity->zPriority;
        entity->params = arg1 & 0xFFF;
        entity->ext.generic.unkA0 = (arg1 >> 8) & 0xFF00;

        if (srcEntity->flags & FLAG_UNK_10000) {
            entity->flags |= FLAG_UNK_10000;
        }
    } else {
        return NULL;
    }
    return entity;
}

INCLUDE_ASM("asm/us/ric/nonmatchings/22380", func_80160788);

void func_80160C38(Entity* entity) {
    if (PLAYER.step != 23) {
        func_80156C60(entity);
    } else {
        entity->posX.i.hi = PLAYER.posX.i.hi;
        entity->posY.i.hi = PLAYER.posY.i.hi;
        entity->facing = PLAYER.facing;
        if (entity->step == 0) {
            entity->flags = FLAG_UNK_20000 | FLAG_UNK_40000 | FLAG_UNK_04000000;
            entity->hitboxOffX = 0x14;
            entity->hitboxOffY = 0xC;
            entity->hitboxHeight = 9;
            entity->hitboxWidth = 9;
            entity->ext.generic.unkB0 = 0x12;
            func_8015FAB8(entity);
            entity->ext.generic.unk7C.s = entity->hitboxState;
            entity->step++;
        }
        entity->hitboxState = entity->ext.generic.unk7C.s;
        if (PLAYER.animFrameIdx < 2) {
            entity->hitboxState = 0;
        }
        if (PLAYER.animFrameIdx >= 8) {
            func_80156C60(entity);
        }
    }
}

void func_80160D2C(Entity* self) {
    if (PLAYER.step != 26) {
        func_80156C60(self);
        return;
    }
    self->posX.i.hi = PLAYER.posX.i.hi;
    self->posY.i.hi = PLAYER.posY.i.hi;
    self->facing = PLAYER.facing;

    if (self->step == 0) {
        self->flags = FLAG_UNK_20000 | FLAG_UNK_40000 | FLAG_UNK_04000000;
        self->hitboxOffX = 0x14;
        self->hitboxHeight = 9;
        self->hitboxWidth = 9;
        self->ext.generic.unkB0 = 0x17;
        func_8015FAB8(self);
        self->step++;
    }

    if (PLAYER.animCurFrame == 140) {
        self->hitboxOffY = 0;
    }

    if (PLAYER.animCurFrame == 141) {
        self->hitboxOffY = 12;
    }

    if (self->hitFlags != 0) {
        g_Player.unk44 |= 0x80;
    } else {
        g_Player.unk44 &= ~0x80;
    }
    self->hitFlags = 0;
}

void func_80160E4C(Entity* self) {
    if (PLAYER.step != 24) {
        func_80156C60(self);
    } else {
        self->posX.i.hi = PLAYER.posX.i.hi;
        self->posY.i.hi = PLAYER.posY.i.hi;
        self->facing = PLAYER.facing;
        if (self->step == 0) {
            self->flags = FLAG_UNK_20000 | FLAG_UNK_40000 | FLAG_UNK_04000000;
            self->hitboxHeight = 20;
            self->hitboxWidth = 20;
            self->hitboxOffY = 0;
            self->hitboxOffX = 0;
            self->ext.generic.unkB0 = 0x11;
            func_8015FAB8(self);
            self->step++;
        }
        if (PLAYER.animFrameIdx >= 19) {
            func_80156C60(self);
        }
    }
}

void func_80160F0C(Entity* self) {
    if (PLAYER.step != 8) {
        func_80156C60(self);
        return;
    }
    self->posX.i.hi = PLAYER.posX.i.hi;
    self->posY.i.hi = PLAYER.posY.i.hi;
    self->facing = PLAYER.facing;
    if (self->step == 0) {
        self->flags = FLAG_UNK_20000 | FLAG_UNK_40000 | FLAG_UNK_04000000;
        self->hitboxOffX = 0xC;
        self->hitboxOffY = -0x1A;
        self->hitboxWidth = 12;
        self->hitboxHeight = 12;
        self->ext.generic.unkB0 = 0x16;
        func_8015FAB8(self);
        self->step++;
    }
}

INCLUDE_ASM("asm/us/ric/nonmatchings/22380", func_80160FC4);

INCLUDE_ASM("asm/us/ric/nonmatchings/22380", func_8016147C);

void func_80161C2C(Entity* self) {
    u16 params = self->params;
    s16 paramsHi = self->params >> 8;
    s32 step = self->step;
    s32 rnd;

    switch (step) {
    case 0:
        if (paramsHi == 1) {
            self->unk1A = 0xC0;
            self->unk1C = 0xC0;
            self->unk19 = 3;
            self->animSet = ANIMSET_DRA(2);
            self->unk4C = D_80154E04;
        }

        if ((paramsHi == 0) || (paramsHi == 2)) {
            if (params & 3) {
                self->unk4C = D_80154DC8;
                self->unk1A = 0x120;
                self->unk1C = 0x120;
                self->unk19 = 3;
                self->animSet = ANIMSET_DRA(2);
            } else {
                self->animSet = ANIMSET_DRA(5);
                self->unk4C = D_80154C80;
                self->palette = 0x8170;
            }
        }
        self->flags = FLAG_UNK_20000 | FLAG_UNK_100000 | FLAG_UNK_08000000;

        if (rand() % 4) {
            self->zPriority = PLAYER.zPriority + 2;
        } else {
            self->zPriority = PLAYER.zPriority - 2;
        }

        if (paramsHi == 2) {
            self->posX.i.hi = PLAYER.posX.i.hi + (rand() % 44) - 22;
        } else {
            self->posX.i.hi = PLAYER.posX.i.hi + (rand() & 15) - 8;
        }

        rnd = rand() & 31;
        self->posY.i.hi = PLAYER.posY.i.hi + PLAYER.hitboxOffY + rnd - 16;
        self->velocityY = FIX(-0.5);
        self->velocityX = PLAYER.velocityX >> 2;
        self->step++;
        break;

    case 1:
        self->unk1A -= 4;
        self->unk1C -= 4;
        self->posY.val += self->velocityY;
        self->posX.val += self->velocityX;
        if ((self->animFrameIdx == 8) && (self->unk4C != D_80154C80)) {
            self->blendMode = 0x10;
            if (!(params & 1) && (self->animFrameDuration == step)) {
                func_801606BC(self, 0x40004, 0);
            }
        }

        if ((self->animFrameIdx == 16) && (self->unk4C == D_80154C80)) {
            self->blendMode = 0x10;
        }

        if (self->animFrameDuration < 0) {
            func_80156C60(self);
        }
        break;
    }
}

void func_80161EF8(Entity* self) {
    switch (self->step) {
    case 0:
        self->animSet = ANIMSET_DRA(2);
        self->unk4C = &D_80154E38;
        self->flags =
            FLAG_UNK_20000 | FLAG_UNK_100000 | FLAG_UNK_10000 | FLAG_UNK_40000;
        self->zPriority = PLAYER.zPriority + 4;
        self->velocityY = (rand() & 0x3FFF) - 0x10000;
        self->step++;
        break;

    case 1:
        if ((self->animFrameIdx == 6) &&
            (self->animFrameDuration == self->step) && (rand() & 1)) {
            func_801606BC(self, 4, 0);
        }
        self->posY.val += self->velocityY;
        if (self->animFrameDuration < 0) {
            func_80156C60(self);
        }
        break;
    }
}

INCLUDE_ASM("asm/us/ric/nonmatchings/22380", func_80161FF0);

void func_801623E0(Entity* entity) {
    POLY_GT4* poly;
    s16 primIndex;

    entity->posX.val = g_Entities->posX.val;
    entity->posY.val = PLAYER.posY.val;
    switch (entity->step) {
    case 0:
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
        entity->primIndex = primIndex;
        if (primIndex == -1) {
            func_80156C60(entity);
            return;
        }
        entity->ext.generic.unk7E.modeU16 = 32;
        entity->ext.generic.unk7C.s = 32;
        poly = &g_PrimBuf[entity->primIndex];
        poly->u2 = 64;
        poly->u0 = 64;
        poly->v1 = 192;
        poly->v0 = 192;
        poly->u3 = 127;
        poly->u1 = 127;
        poly->v3 = 255;
        poly->v2 = 255;
        poly->tpage = 0x1A;
        poly->clut = 0x13E;
        poly->pad2 = PLAYER.zPriority + 8;
        poly->pad3 = 0;
        entity->flags = FLAG_UNK_10000 | FLAG_UNK_40000 | FLAG_UNK_04000000 |
                        FLAG_HAS_PRIMS;
        entity->step++;
        break;

    case 1:
        entity->ext.generic.unk7C.s++;
        entity->ext.generic.unk7E.modeU16++;
        if (entity->ext.generic.unk7C.s >= 45) {
            func_80156C60(entity);
            return;
        }
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
    poly->clut = (LOH(g_blinkTimer) & 1) + 0x13E;
}

void func_80162604(Entity* entity) {
    POLY_GT4* poly;
    s16 primIndex;

    entity->posX.val = g_Entities->posX.val;
    entity->posY.val = PLAYER.posY.val;
    switch (entity->step) {
    case 0:
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
        entity->primIndex = primIndex;
        if (primIndex != -1) {
            entity->ext.generic.unk7E.modeU16 = 0;
            entity->ext.generic.unk7C.s = 0;
            poly = &g_PrimBuf[entity->primIndex];
            poly->v1 = 192;
            poly->v0 = 192;
            poly->u3 = 63;
            poly->u1 = 63;
            poly->v3 = 255;
            poly->v2 = 255;
            poly->tpage = 0x1A;
            poly->u2 = 0;
            poly->u0 = 0;
            poly->clut = 0x162;
            poly->pad2 = PLAYER.zPriority - 4;
            poly->pad3 = 0;
            entity->flags = FLAG_UNK_10000 | FLAG_UNK_40000 |
                            FLAG_UNK_04000000 | FLAG_HAS_PRIMS;
            entity->step++;
            goto def;
        } else {
            func_80156C60(entity);
            break;
        }

    case 1:
        entity->ext.generic.unk7C.s += 8;
        entity->ext.generic.unk7E.modeU16 += 8;
        if (entity->ext.generic.unk7C.s < 0x20) {
            goto def;
        }

    case 2:
        entity->step++;
        goto def;

    case 3:
        entity->ext.generic.unk7C.s -= 8;
        entity->ext.generic.unk7E.modeU16 -= 8;
        if (entity->ext.generic.unk7C.s >= 5) {
            goto def;
        } else {

            func_80156C60(entity);
        }
        break;

    def:
    default:
        poly = &g_PrimBuf[entity->primIndex];
        poly->x0 = entity->posX.i.hi - entity->ext.generic.unk7C.s;
        poly->y0 = entity->posY.i.hi - entity->ext.generic.unk7E.modeU16;
        poly->x1 = entity->posX.i.hi + entity->ext.generic.unk7C.s;
        poly->y1 = entity->posY.i.hi - entity->ext.generic.unk7E.modeU16;
        poly->x2 = entity->posX.i.hi - entity->ext.generic.unk7C.s;
        poly->y2 = entity->posY.i.hi + entity->ext.generic.unk7E.modeU16;
        poly->x3 = entity->posX.i.hi + entity->ext.generic.unk7C.s;
        poly->y3 = entity->posY.i.hi + entity->ext.generic.unk7E.modeU16;
        break;
    }
}

INCLUDE_ASM("asm/us/ric/nonmatchings/22380", func_80162870);

void func_80162C7C(void) {}
