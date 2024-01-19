#include "ric.h"

// Entity ID 66. Made by blueprint 77 (the very last one).
// Created in 3 spots in 2 functions (total of 6 calls).
// DRA version is very similar.
void EntityTeleport(Entity* self) {
    Primitive* prim;
    s32 selfUnk7C;
    s32 selfUnk80;
    s32 yVar;
    s32 xVar;
    s32 upperParams;
    s32 i;
    s32 result;

    bool wasCase3 = false;
    bool var_s5 = false;

    upperParams = self->params & 0xFE00;
    FntPrint("pl_warp_flag:%02x\n", g_Player.unk1C);
    switch (self->step) {
    case 0:
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 36);
        if (self->primIndex == -1) {
            return;
        }
        self->flags = FLAG_UNK_08000000 | FLAG_UNK_04000000 | FLAG_HAS_PRIMS |
                      FLAG_UNK_10000;
        prim = &g_PrimBuf[self->primIndex];
        for (i = 0; i < 2; i++) {
            prim->x0 = 0xC0 * i;
            prim->g0 = 0;
            prim->b0 = 0;
            prim->r0 = 0;
            prim->y0 = 0;
            prim->u0 = 0xC0;
            prim->v0 = 0xF0;
            prim->type = 1;
            prim->priority = 0x1FD;
            prim->blendMode = 0x39;
            prim = prim->next;
        }
        for (i = 0; i < 2; i++) {
            prim->type = 3;
            prim->priority = 0x1F8;
            prim->blendMode = 0x31;
            prim = prim->next;
        }
        for (i = 0; i < 32; i++) {
            xVar = PLAYER.posX.i.hi + (rand() % 28) - 14;
            yVar = rand();
            yVar = 0xE0 - (yVar & 0x3F);
            D_80175000[i].unk0 = xVar;
            D_80175000[i].unk2 = yVar;
            prim->clut = 0x1BA;
            prim->tpage = 0x1A;
            prim->b0 = 0;
            prim->b1 = 0;
            prim->g0 = 0;
            prim->g1 = (rand() & 0x1F) + 1;
            prim->priority = 0x1F0;
            prim->blendMode = 8;
            prim->g2 = 0;
            prim = prim->next;
        }
        self->ext.teleport.unk7C = 0;
        self->ext.teleport.unk80 = 0x10;
        self->ext.teleport.unk88 = 0x80;
        if (self->params & 0x100) {
            var_s5 = true;
            self->ext.teleport.unk7C = 0x10;
            self->ext.teleport.unk80 = 0x100;
            self->ext.teleport.unk88 = 0x80;
            self->ext.teleport.unk90 = 0xFF;
            self->step = 0x14;
            g_api.PlaySfx(0x8BB);
        } else {
            self->ext.teleport.unk7C = 1;
            self->ext.teleport.unk90 = 0;
            self->ext.teleport.unk80 = 0x10;
            self->ext.teleport.unk88 = 0x80;
            self->step = 1;
            g_api.PlaySfx(0x635);
            g_api.PlaySfx(0x8BA);
        }
        break;
    case 1:
        self->ext.teleport.unk80 += 0x20;
        if (self->ext.teleport.unk80 >= 0x101) {
            self->step++;
        }
        break;
    case 2:
        if (++self->ext.teleport.unk7C >= 0x10) {
            self->ext.teleport.unk7C = 0x10;
            self->ext.teleport.unk84 = 0x80;
            self->step++;
        }
        break;
    case 3:
        wasCase3 = true;
        self->ext.teleport.unk88 += 4;
        if (self->ext.teleport.unk88 >= 0x100) {
            self->ext.teleport.unk88 = 0x100;
        }
        if (--self->ext.teleport.unk84 == 0) {
            PLAYER.palette = 0x810D;
            self->step++;
        }
        break;
    case 4:
        func_80166024();
        if (--self->ext.teleport.unk7C <= 0) {
            self->ext.teleport.unk7C = 0;
            self->step++;
        }
        break;
    case 5:
        var_s5 = true;
        func_80166024();
        self->ext.teleport.unk90 += 4;
        if (self->ext.teleport.unk90 >= 0x100) {
            self->ext.teleport.unk90 = 0xFF;
            self->ext.teleport.unk84 = 0x20;
            self->step++;
        }
        break;
    case 6:
        var_s5 = true;
        func_80166024();
        if (--self->ext.teleport.unk84 == 0) {
            self->ext.teleport.unk90 = 0;
            if (upperParams == 0) {
                D_80097C98 = 6;
            }
            if (upperParams == 0x200) {
                D_80097C98 = 4;
            }
            if (upperParams == 0x400) {
                D_80097C98 = 5;
            }
        }
        break;
    case 20:
        var_s5 = true;
        self->ext.teleport.unk90 = 0xFF;
        self->ext.teleport.unk84 = 0x20;
        self->step++;
        break;
    case 21:
        var_s5 = true;
        if (--self->ext.teleport.unk84 == 0) {
            self->step++;
        }
        break;
    case 22:
        var_s5 = true;
        self->ext.teleport.unk90 -= 4;
        if (self->ext.teleport.unk90 <= 0) {
            self->ext.teleport.unk90 = 0;
            self->step++;
        }
        break;
    case 23:
        if (--self->ext.teleport.unk7C < 2) {
            self->ext.teleport.unk7C = 0;
            self->ext.teleport.unk84 = 4;
            self->step++;
            g_Player.unk1C = 1;
            g_api.PlaySfx(0x636);
            DestroyEntity(self);
            return;
        }
        break;
    }
    selfUnk7C = self->ext.teleport.unk7C;
    selfUnk80 = self->ext.teleport.unk80;
    self->posX.i.hi = PLAYER.posX.i.hi;
    self->posY.i.hi = PLAYER.posY.i.hi;
    prim = &g_PrimBuf[self->primIndex];
    xVar = PLAYER.posX.i.hi;
    yVar = PLAYER.posY.i.hi;
    for (i = 0; i < 2; i++) {
        prim->r0 = prim->b0 = prim->g0 = self->ext.teleport.unk90;
        prim->blendMode |= BLEND_VISIBLE;
        if (var_s5) {
            prim->blendMode &= ~BLEND_VISIBLE;
        }
        prim = prim->next;
    }
    prim->x1 = prim->x3 = xVar;
    prim->x0 = prim->x2 = xVar - selfUnk7C;
    func_80165DD8(prim, self->ext.teleport.unk88, yVar, selfUnk80, upperParams);
    prim = prim->next;
    prim->x1 = prim->x3 = xVar;
    prim->x0 = prim->x2 = xVar + selfUnk7C;
    func_80165DD8(prim, self->ext.teleport.unk88, yVar, selfUnk80, upperParams);
    prim = prim->next;
    if (wasCase3) {
        for (i = 0; i < 32; i++) {
            switch (prim->g0) {
            case 0:
                if (--prim->g1 == 0) {
                    prim->g0++;
                }
                break;
            case 1:
                result =
                    func_8015FDB0(prim, D_80175000[i].unk0, D_80175000[i].unk2);
                D_80175000[i].unk2 -= 16;
                if (result < 0) {
                    prim->blendMode |= BLEND_VISIBLE;
                    prim->g0++;
                } else {
                    prim->blendMode &= ~BLEND_VISIBLE;
                }
                break;
            }
            prim = prim->next;
        }
        return;
    }

    // Potential bug? Should probably be doing prim = prim->next, right?
    for (i = 0; i < 32; i++) {
        prim->blendMode |= BLEND_VISIBLE;
    }
}

INCLUDE_ASM("ric/nonmatchings/2A060", func_80166784);

void func_8016779C(Entity* entity) {
    if (g_Player.unk46 == 0) {
        DestroyEntity(entity);
        return;
    }

    entity->facingLeft = PLAYER.facingLeft;
    if (entity->step == 0) {
        entity->flags = FLAG_UNK_20000 | FLAG_UNK_40000 | FLAG_UNK_04000000 |
                        FLAG_UNK_10000;
        entity->animSet = ANIMSET_OVL(18);
        entity->unk5A = 0x46;
        entity->palette = 0x8120;
        entity->zPriority = PLAYER.zPriority + 2;
    }

    if (PLAYER.step == 2) {
        if (PLAYER.facingLeft != 0) {
            entity->animCurFrame = D_80155CCC[D_80175080];
        } else {
            entity->animCurFrame = D_80155CB8[D_80175080];
        }
    } else if (PLAYER.step == 0) {
        if (PLAYER.facingLeft != 0) {
            entity->animCurFrame = D_80155CF4[D_80175080];
        } else {
            entity->animCurFrame = D_80155CE0[D_80175080];
        }
    } else if (PLAYER.facingLeft != 0) {
        entity->animCurFrame = D_80155D1C[D_80175080];
    } else {
        entity->animCurFrame = D_80155D08[D_80175080];
    }

    entity->posX.val = g_Entities->posX.val;
    entity->posY.val = PLAYER.posY.val;
}

/**
 * TODO: !FAKE
 * Needs to be refactored
 */
void func_80167964(Entity* entity) {
    /**
     * 0x5E was originally 0xBC in mips2c output
     * suggesting the size of the Entity struct
     */
    if (g_Player.unk46 != 0) {
        if (entity->step == 0) {
            entity->flags = FLAG_UNK_20000 | FLAG_UNK_40000 |
                            FLAG_UNK_04000000 | FLAG_UNK_10000;
        }
        if (!(entity->params & 0xFF00)) {
            *(&PLAYER.palette +
              (*(&D_80155D30 + (entity->animFrameDuration)) * 0x5E)) = 0x8140;
        }
        *(&PLAYER.ext.generic.unkA4 +
          (*(&D_80155D30 + (entity->animFrameDuration)) * 0x5E)) = 4;
        entity->animFrameDuration++;
        if (entity->animFrameDuration == 0xF) {
            DestroyEntity(entity);
        }
    } else {
        DestroyEntity(entity);
    }
}

void func_80167A58(Entity* self) {}

void func_80167A60(Entity* self) {}

void func_80167A68(Entity* self) {}

// Entity ID #35. Created by blueprint 40. No known FACTORY calls with
// blueprint 40. No known DRA match.
void func_80167A70(Entity* self) {
    s16_pair sp10[8];
    Primitive* prim;
    FakePrim* fakeprim;
    s32 velX;
    s32 i;
    u16 posY;
    u16 posX;
    u8 arrIndex;
    u8 randbit;

    switch (self->step) {
    case 0:
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 16);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        prim = &g_PrimBuf[self->primIndex];
        posX = self->posX.i.hi;
        posY = self->posY.i.hi;
        for (i = 0; prim != NULL; i++, prim = prim->next) {
            if (i < 8) {
                fakeprim = (FakePrim*)prim;
                fakeprim->x0 = posX;
                fakeprim->posX.i.hi = posX;
                sp10[i].unk0 = posX;
                fakeprim->y0 = posY;
                fakeprim->posY.i.hi = posY;
                sp10[i].unk2 = posY;
                // Random velocity from 0.25 to 0.5
                velX = (rand() & 0x3FFF) + FIX(0.25);
                fakeprim->velocityX = velX;
                if (i & 1) {
                    fakeprim->velocityX = -velX;
                }
                fakeprim->velocityY = -((rand() * 2) + FIX(2.5));
                fakeprim->blendMode = 0xA;
                fakeprim->type = 1;
            } else {
                prim->r0 = prim->r1 = prim->r2 = prim->r3 =
                    (rand() & 0xF) | 0x30;
                prim->b0 = prim->b1 = prim->b2 = prim->b3 = rand() | 0x80;
                prim->g0 = prim->g1 = prim->g2 = prim->g3 =
                    (rand() & 0x1F) + 0x30;
                randbit = rand() & 1;
                prim->blendMode = !(randbit) ? 6 : 0x37;
                posX = sp10[i - 8].unk0;
                posY = sp10[i - 8].unk2;
                arrIndex = i & 3;
                prim->u0 = arrIndex;
                prim->x0 = posX + D_80155D64[arrIndex][0];
                prim->y0 = posY + D_80155D64[arrIndex][1];
                prim->x1 = posX + D_80155D64[arrIndex][2];
                prim->y1 = posY + D_80155D64[arrIndex][3];
                prim->x3 = prim->x2 = posX + D_80155D64[arrIndex][4];
                prim->y3 = prim->y2 = posY + D_80155D64[arrIndex][5];
                prim->type = 3;
                prim->priority = PLAYER.zPriority + 2;
            }
        }
        self->flags = FLAG_UNK_08000000 | FLAG_HAS_PRIMS;
        self->ext.timer.t = 20;
        self->step++;
        return;

    case 1:
        if (--self->ext.timer.t == 0) {
            DestroyEntity(self);
            return;
        }
        prim = &g_PrimBuf[self->primIndex];
        for (i = 0; prim != NULL; i++, prim = prim->next) {
            if (i < 8) {
                fakeprim = (FakePrim*)prim;
                fakeprim->posX.i.hi = fakeprim->x0;
                fakeprim->posY.i.hi = fakeprim->y0;
                fakeprim->posX.val += fakeprim->velocityX.val;
                fakeprim->posY.val += fakeprim->velocityY.val;
                fakeprim->velocityY.val += FIX(36.0 / 128);
                sp10[i].unk0 = fakeprim->posX.i.hi;
                sp10[i].unk2 = fakeprim->posY.i.hi;
                fakeprim->x0 = fakeprim->posX.i.hi;
                fakeprim->y0 = fakeprim->posY.i.hi;
            } else {
                posX = sp10[i - 8].unk0;
                posY = sp10[i - 8].unk2;
                arrIndex = prim->u0;
                prim->x0 = posX + D_80155D64[arrIndex][0];
                prim->y0 = posY + D_80155D64[arrIndex][1];
                prim->x1 = posX + D_80155D64[arrIndex][2];
                prim->y1 = posY + D_80155D64[arrIndex][3];
                prim->x3 = prim->x2 = posX + D_80155D64[arrIndex][4];
                prim->y3 = prim->y2 = posY + D_80155D64[arrIndex][5];
            }
        }
    }
}

INCLUDE_ASM("ric/nonmatchings/2A060", func_80167EC4);

INCLUDE_ASM("ric/nonmatchings/2A060", func_801682B4);

s32 func_8016840C(s16 x, s16 y) {
    Collider collider;
    u16 temp;

    if (g_CurrentEntity->velocityX != 0) {
        g_api.CheckCollision(g_CurrentEntity->posX.i.hi + y,
                             g_CurrentEntity->posY.i.hi + x, &collider, 0);
        if (g_CurrentEntity->velocityX > 0) {
            temp = collider.unk14;
        } else {
            temp = collider.unk1C;
        }
        if (!(collider.effects & EFFECT_UNK_0002)) {
            return 0;
        }
    } else {
        return 0;
    }
    g_CurrentEntity->posX.i.lo = 0;
    g_CurrentEntity->posX.i.hi += temp;
    return 2;
}

INCLUDE_ASM("ric/nonmatchings/2A060", func_801684D8);

INCLUDE_ASM("ric/nonmatchings/2A060", func_80168A20);

INCLUDE_ASM("ric/nonmatchings/2A060", func_8016902C);

INCLUDE_ASM("ric/nonmatchings/2A060", func_80169470);

// ID 3. Created by blueprint 2.
INCLUDE_ASM("ric/nonmatchings/2A060", func_80169704);

void func_80169C10(Entity* entity) {
    Primitive* prim;
    s16 primIndex;
    s32 PosX = 8;
    s32 PosY = 4;

    switch (entity->step) {
    case 0:
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
        entity->primIndex = primIndex;
        if (primIndex != -1) {
            entity->flags = FLAG_UNK_08000000 | FLAG_HAS_PRIMS;
            entity->velocityY = FIX(0.5);
            entity->posX.i.hi =
                ((u16)entity->posX.i.hi - PosX) + (rand() & 0xF);
            entity->posY.i.hi =
                ((u16)entity->posY.i.hi - PosY) + (rand() & 0xF);
            prim = &g_PrimBuf[entity->primIndex];
            prim->clut = 0x1B0;
            prim->tpage = 0x1A;
            prim->b0 = 0;
            prim->b1 = 0;
            prim->priority = entity->zPriority;
            prim->priority = prim->priority + 4;
            prim->blendMode = 0x31;
            func_8015FDB0(prim, entity->posX.i.hi, entity->posY.i.hi);
            entity->step++;
        } else {
            DestroyEntity(entity);
        }
        break;

    default:
        entity->posY.val += entity->velocityY;
        prim = &g_PrimBuf[entity->primIndex];
        if (func_8015FDB0(prim, entity->posX.i.hi, entity->posY.i.hi) != 0) {
            DestroyEntity(entity);
        }
        break;
    }
}

void func_80169D74(Entity* entity) {
    Multi temp;
    s16* ptr;

    switch (entity->step) {
    case 0:
        entity->flags = FLAG_UNK_04000000 | FLAG_UNK_08000000;
        entity->ext.generic.unk84.unk =
            entity->ext.generic.unk8C.entityPtr->ext.generic.unk84.unk;
        entity->animSet = ANIMSET_OVL(17);
        entity->animCurFrame = D_80155E68[entity->params];
        entity->unk5A = 0x66;
        entity->palette = 0x81B0;
        entity->blendMode = 0x10;
        entity->facingLeft = PLAYER.facingLeft;
        entity->zPriority = PLAYER.zPriority;
        entity->drawFlags = FLAG_DRAW_ROTZ;
        entity->rotZ = 0xC00;
        entity->step++;
        break;

    case 1:
        entity->rotZ -= 0x80;
        if (entity->ext.generic.unk8C.entityPtr->step == 7) {
            entity->step++;
            entity->ext.generic.unk7C.s = (entity->params + 1) * 4;
        }
        break;

    case 2:
        entity->rotZ -= 0x80;
        entity->ext.generic.unk7C.s--;
        if (entity->ext.generic.unk7C.s == 0) {
            DestroyEntity(entity);
            return;
        }
        break;
    }
    temp = entity->ext.generic.unk84;
    ptr = temp.unk + ((u16)entity->ext.generic.unk80.modeS16.unk0 * 4);
    entity->posX.i.hi = ptr[0] - g_Tilemap.cameraX.i.hi;
    entity->posY.i.hi = ptr[1] - g_Tilemap.cameraY.i.hi;
    entity->ext.generic.unk80.modeS16.unk0 =
        (entity->ext.generic.unk80.modeS16.unk0 + 1) & 0x3F;
}

INCLUDE_ASM("ric/nonmatchings/2A060", func_80169F04);

INCLUDE_ASM("ric/nonmatchings/2A060", func_8016A26C);

INCLUDE_ASM("ric/nonmatchings/2A060", func_8016A974);

INCLUDE_ASM("ric/nonmatchings/2A060", func_8016B0C0);

void func_8016B8E8(s32 arg0) {
    g_CurrentEntity->ext.generic.unk7C.s =
        (arg0 << 0x10 >> 0xF) - g_CurrentEntity->ext.generic.unk7C.s;
    if (g_CurrentEntity->ext.generic.unk80.modeS16.unk2 == 0) {
        g_CurrentEntity->ext.generic.unk80.modeS16.unk0++;
        g_CurrentEntity->ext.generic.unk80.modeS16.unk2++;
    }
}

void func_8016B92C(s16 arg0) {
    if (g_CurrentEntity->ext.generic.unk80.modeS16.unk2 == 0) {
        g_CurrentEntity->ext.generic.unk7C.s =
            (arg0 * 2) - g_CurrentEntity->ext.generic.unk7C.s;
        g_CurrentEntity->ext.generic.unk80.modeS16.unk0++;
        g_CurrentEntity->ext.generic.unk80.modeS16.unk2++;
    }
}

INCLUDE_ASM("ric/nonmatchings/2A060", func_8016B97C);

INCLUDE_ASM("ric/nonmatchings/2A060", func_8016C1BC);

s32 RicPrimDecreaseBrightness(Primitive* prim, u8 amount) {
    u8 isEnd;
    s32 i;
    s32 j;
    u8* pColor;

    isEnd = 0;
    pColor = &prim->r0;
    for (i = 0; i < 4; i++, pColor += OFF(Primitive, r1) - OFF(Primitive, r0)) {
        for (j = 0; j < 3; j++) {
            pColor[j] -= amount;

            if (pColor[j] < 16) {
                pColor[j] = 16;
            } else {
                isEnd |= 1;
            }
        }
    }
    return isEnd;
}

INCLUDE_ASM("ric/nonmatchings/2A060", func_8016C734);

INCLUDE_ASM("ric/nonmatchings/2A060", func_8016CC74);

void func_8016D328(Entity* entity) {
    s16 primIndex;
    s32 newVelocity;

    switch (entity->step) {
    case 0:
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
        entity->primIndex = primIndex;
        if (primIndex != -1) {
            entity->flags = FLAG_UNK_08000000 | FLAG_HAS_PRIMS;
            entity->posX.val =
                entity->ext.generic.unk8C.entityPtr->ext.generic.unk84.unk;
            entity->posY.val =
                entity->ext.generic.unk8C.entityPtr->ext.generic.unk88.unk;
            entity->facingLeft = entity->ext.generic.unk8C.entityPtr->ext
                                     .generic.unk8C.modeU16.unk0;
            entity->ext.generic.unkB0 = 0x18;
            func_8015FAB8(entity);
            entity->unk5A = 0x79;
            entity->animSet = ANIMSET_DRA(14);
            entity->palette = 0x819E;
            entity->unk4C = &D_80155EA8;
            entity->blendMode = 0x30;
            entity->drawFlags = FLAG_DRAW_UNK8;
            entity->unk6C = 0x60;
            entity->hitboxWidth = 8;
            entity->hitboxHeight = 8;
            entity->flags |= FLAG_UNK_100000;
            newVelocity = (rand() % 512) + 0x300;
            entity->velocityX = rcos(newVelocity) * 32;
            entity->velocityY = -(rsin(newVelocity) * 32);
            entity->step++;
        } else {
            DestroyEntity(entity);
        }
        break;

    case 1:
        if (++entity->ext.generic.unk7C.s >= 39) {
            DestroyEntity(entity);
        } else {
            entity->posX.val += entity->velocityX;
            entity->posY.val += entity->velocityY;
        }
        break;
    }
}

INCLUDE_ASM("ric/nonmatchings/2A060", func_8016D4D8);

void func_8016D920(Entity* entity) {
    switch (entity->step) {
    case 0:
        entity->flags = FLAG_UNK_04000000;
        entity->ext.generic.unkB0 = 0x19;
        func_8015FAB8(entity);
        entity->hitboxWidth = 4;
        entity->hitboxHeight = 4;
        entity->step++;
        break;

    case 1:
        if (++entity->ext.generic.unk7C.s >= 4) {
            DestroyEntity(entity);
        }
        break;
    }
}

INCLUDE_ASM("ric/nonmatchings/2A060", func_8016D9C4);

INCLUDE_ASM("ric/nonmatchings/2A060", func_8016DF74);
