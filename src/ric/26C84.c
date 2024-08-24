#include "ric.h"

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

// EntityPlayerBlinkWhite (Richter's version).
// Same general logic flow as in DRA but lots of missing cases.
static s32 D_80154F7C[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
static s16 D_80154FBC[][10] = {
    {0, 0, 0, 0x15F, 0x0100, 0x0100, 0x0100, 0x0060, 0x31, 0x200},
    {0, 2, 6, 0x15F, 0x0100, 0x0100, 0x0100, 0x0040, 0x31, 0x200},
    {0, 0, 0, 0x15F, 0x0100, 0x7000, 0x7000, 0x0040, 0x31, 0x200},
    {0, 0, 0, 0x15F, 0x0100, 0x7000, 0x0200, 0x0010, 0x31, 0x200},
    {0, 0, 0, 0x15F, 0x0100, 0x7000, 0x7000, 0x0010, 0x31, 0x200},
    {0, 0, 0, 0x15F, 0x0100, 0x7000, 0x0200, 0x7000, 0x31, 0x200},
    {0, 0, 0, 0x15F, 0x0100, 0x7000, 0x0100, 0x7002, 0x31, 0x100},
    {0, 0, 0, 0x15F, 0x0100, 0x0100, 0x7000, 0x0070, 0x31, 0x200},
    {0, 0, 0, 0x15F, 0x0100, 0x7000, 0x0200, 0x7006, 0x31, 0x200},
    {0, 0, 0, 0x15F, 0x0200, 0x0200, 0x0400, 0x7001, 0x31, 0x200},
    {0, 0, 0, 0x166, 0x0100, 0x0100, 0x0100, 0x7005, 0x31, 0x200},
    {0, 0, 0, 0x102, 0x0100, 0x7000, 0x7000, 0x0040, 0x31, 0x200},
    {0, 0, 0, 0x15F, 0x0100, 0x7100, 0x0100, 0x7005, 0x31, 0x200},
    {0, 0, 0, 0x15F, 0x0100, 0x0100, 0x0100, 0x7005, 0x31, 0x200},
    {0, 0, 0, 0x102, 0x0100, 0x7000, 0x0200, 0x0040, 0x31, 0x200},
    {0, 0, 0, 0x102, 0x0100, 0x7000, 0x0100, 0x0040, 0x31, 0x200},
    {0, 0, 0, 0x102, 0x0100, 0x0100, 0x7000, 0x0000, 0x31, 0x200},
    {0, 0, 0, 0x102, 0x0400, 0x0100, 0x0400, 0x0000, 0x31, 0x200},
    {0, 0, 0, 0x15F, 0x0100, 0x0100, 0x7000, 0x0000, 0x31, 0x200},
    {0, 0, 0, 0x15F, 0x0200, 0x0800, 0x0800, 0x7007, 0x31, 0x200},
    {0, 0, 0, 0x102, 0x0100, 0x0100, 0x0100, 0x0000, 0x31, 0x200},
    {0, 0, 0, 0x15F, 0x00C0, 0x00C0, 0x0100, 0x0010, 0x31, 0x200},
    {8, 0, 8, 0x165, 0x0100, 0x0100, 0x0100, 0x7007, 0x51, 0x200},
    {0, 0, 0, 0x168, 0x7100, 0x7100, 0x0200, 0x7007, 0x31, 0x200}};
void RicEntityPlayerBlinkWhite(Entity* self) {
    Primitive* prim;
    u8 xMargin;
    u8 yMargin;
    u8 wSprite;
    u8 hSprite;
    s16 xPivot;
    s16 yPivot;
    s16 width;
    s16 height;
    s16 selfX;
    s16 selfY;
    s32 i;
    u16 upperParams;
    s16* dataPtr;
    s16 angleIdx1;
    s16 angleIdx2;
    s16 angleIdx3;
    s16 angleDivide1;
    s16 angleDivide3;
    s16 angleDivide2;
    s16* temp_v1;
    u8* plSprite;
    s16 rotz;

    if (PLAYER.animSet == 0 || (PLAYER.animCurFrame & 0x7FFF) == 0) {
        DestroyEntity(self);
        return;
    }
    self->posY.i.hi = PLAYER.posY.i.hi;
    self->posX.i.hi = PLAYER.posX.i.hi;
    self->facingLeft = PLAYER.facingLeft;
    rotz = PLAYER.rotZ;
    selfY = self->posY.i.hi;
    selfX = self->posX.i.hi;
    temp_v1 = D_801530AC[PLAYER.animCurFrame & 0x7FFF];
    // Don't miss the temp_v1++ here!
    plSprite = ((u8**)SPRITESHEET_PTR)[*temp_v1++ & 0x7FFF];
    xMargin = 4;
    yMargin = 1;
    wSprite = xMargin + plSprite[0];
    hSprite = yMargin + plSprite[1];
    width = wSprite - xMargin;
    height = hSprite - yMargin;

    xPivot = temp_v1[0] + plSprite[2];
    yPivot = temp_v1[1] + plSprite[3];

    self->rotZ = rotz;
    self->drawFlags = PLAYER.drawFlags;
    self->rotX = PLAYER.rotX;
    self->rotY = PLAYER.rotY;
    self->rotPivotY = PLAYER.rotPivotY;
    self->rotPivotX = PLAYER.rotPivotX;
    upperParams = (self->params & 0x7F00) >> 8;
    dataPtr = D_80154FBC[upperParams & 0x3F];
    switch (self->step) {
    case 0:
        if (func_80162E9C(self) != 0) {
            DestroyEntity(self);
            return;
        }
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 8);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags = FLAG_UNK_04000000 | FLAG_HAS_PRIMS | FLAG_UNK_40000 |
                      FLAG_UNK_20000 | FLAG_UNK_10000;
        prim = &g_PrimBuf[self->primIndex];
        for (i = 0; i < 8; i++) {
            D_80154F7C[i] = i << 9;
            prim->tpage = 0x18;
            prim->clut = dataPtr[3];
            prim->r0 = prim->b0 = prim->g0 = prim->r1 = prim->b1 = prim->g1 =
                prim->r2 = prim->b2 = prim->g2 = prim->r3 = prim->b3 =
                    prim->g3 = 0x80;
            prim->priority = PLAYER.zPriority + 2;
            prim->drawMode =
                dataPtr[8] + DRAW_UNK_200 + DRAW_UNK_100 + DRAW_COLORS;
            prim = prim->next;
        }
        self->ext.playerBlink.unk8A = dataPtr[9];
        self->ext.playerBlink.unk90 = 0;
        self->step += 1;
        break;
    case 1:
        self->ext.playerBlink.unk90 += 0xA;
        if (self->ext.playerBlink.unk90 > 0x100) {
            self->ext.playerBlink.unk90 = 0x100;
            self->ext.playerBlink.unk80 = dataPtr[7];
            self->step += 1;
        }
        break;
    case 2:
        if (dataPtr[7] >= 0x7000) {
            switch ((u32)dataPtr[7]) {
            case 0x7000:
                if (g_Player.D_80072F00[PL_T_POISON] == 0) {
                    self->step++;
                }
                break;
            case 0x7001:
                if (g_Player.D_80072F00[PL_T_INVINCIBLE] == 0) {
                    self->step++;
                }
                break;
            case 0x7007:
            case 0x7002:
                if (PLAYER.step != PL_S_HIT) {
                    self->step++;
                }
                break;
            case 0x7005:
            case 0x7006:
                if (PLAYER.step_s == 3) {
                    self->step++;
                }
                break;
            case 0x7003:
            case 0x7004:

                break;
            }
            self->ext.playerBlink.unk80 = 8;
        }
        if (--self->ext.playerBlink.unk80 == 0) {
            self->step += 1;
        }
        break;
    case 3:
        self->ext.playerBlink.unk90 -= 10;
        if (self->ext.playerBlink.unk90 < 0) {
            DestroyEntity(self);
            return;
        }
        break;
    }
    self->ext.playerBlink.unk82 += self->ext.playerBlink.unk8A;
    if (self->facingLeft) {
        selfX -= xPivot;
    } else {
        selfX += xPivot;
    }
    selfY += yPivot;
    prim = &g_PrimBuf[self->primIndex];
    for (i = 0; i < 8; i++) {
        if (upperParams & 0x40) {
            switch (i) {
            case 0:
                do {
                    if (self->facingLeft) {
                        prim->x0 = selfX;
                        prim->x1 = selfX - width / 2;
                        prim->u0 = xMargin;
                        prim->u1 = xMargin + width / 2;
                    } else {
                        prim->x0 = selfX;
                        prim->x1 = selfX + width / 2;
                        prim->u0 = xMargin;
                        prim->u1 = xMargin + width / 2;
                    }
                    prim->y0 = prim->y1 = selfY;
                    prim->v0 = prim->v1 = yMargin;
                } while (0);
                break;
            case 1:
                if (self->facingLeft) {
                    prim->x0 = selfX - width / 2;
                    prim->x1 = selfX - width;
                    prim->u0 = xMargin + width / 2;
                    prim->u1 = xMargin + width;
                } else {
                    prim->x0 = selfX + width / 2;
                    prim->x1 = selfX + width;
                    prim->u0 = xMargin + width / 2;
                    prim->u1 = xMargin + width;
                }
                prim->y0 = prim->y1 = selfY;
                prim->v0 = prim->v1 = yMargin;
                break;
            case 2:
                if (self->facingLeft) {
                    prim->x0 = prim->x1 = selfX - width;
                    prim->u0 = prim->u1 = xMargin + width;
                } else {
                    prim->x0 = prim->x1 = selfX + width;
                    prim->u0 = prim->u1 = xMargin + width;
                }
                prim->y0 = selfY;
                prim->y1 = selfY + height / 2;
                prim->v0 = yMargin;
                prim->v1 = yMargin + height / 2;
                break;
            case 3:
                if (self->facingLeft) {
                    prim->x0 = prim->x1 = selfX - width;
                    prim->u0 = prim->u1 = xMargin + width;
                } else {
                    prim->x0 = prim->x1 = selfX + width;
                    prim->u0 = prim->u1 = xMargin + width;
                }

                prim->y0 = selfY + height / 2;
                prim->y1 = selfY + height;
                prim->v0 = yMargin + height / 2;
                prim->v1 = yMargin + height;
                break;
            case 4:
                if (self->facingLeft) {
                    prim->x0 = selfX - width;
                    prim->x1 = selfX - width / 2;
                    prim->u0 = xMargin + width;
                    prim->u1 = xMargin + width / 2;
                } else {
                    prim->x0 = selfX + width;
                    prim->x1 = selfX + width / 2;
                    prim->u0 = xMargin + width;
                    prim->u1 = xMargin + width / 2;
                }
                prim->y0 = prim->y1 = selfY + height;
                prim->v0 = prim->v1 = yMargin + height;
                break;
            case 5:
                if (self->facingLeft) {
                    prim->x0 = selfX - width / 2;
                    prim->x1 = selfX;
                    prim->u0 = xMargin + width / 2;
                    prim->u1 = xMargin;
                } else {
                    prim->x0 = selfX + width / 2;
                    prim->x1 = selfX;
                    prim->u0 = xMargin + width / 2;
                    prim->u1 = xMargin;
                }
                prim->y0 = prim->y1 = selfY + height;
                prim->v0 = prim->v1 = yMargin + height;
                break;
            case 6:

                prim->x0 = prim->x1 = selfX;

                prim->u0 = prim->u1 = xMargin;
                prim->y0 = selfY + height;
                prim->y1 = selfY + height / 2;
                prim->v0 = yMargin + height;
                prim->v1 = yMargin + height / 2;
                break;
            case 7:
                prim->x0 = prim->x1 = selfX;
                prim->u0 = prim->u1 = xMargin;
                prim->y0 = selfY + height / 2;
                prim->y1 = selfY;
                prim->v0 = yMargin + height / 2;
                prim->v1 = yMargin;
                break;
            }
            if (self->facingLeft) {
                prim->x2 = prim->x3 =
                    selfX - width / 2 +
                    ((rcos(self->ext.playerBlink.unk82) >> 4) * 3 >> 0xC);
            } else {
                prim->x2 = prim->x3 =
                    selfX + width / 2 +
                    ((rcos(self->ext.playerBlink.unk82) >> 4) * 3 >> 0xC);
            }
            prim->y2 = prim->y3 =
                (selfY + height / 2) -
                ((rsin(self->ext.playerBlink.unk82) >> 4) * 3 >> 7);
            prim->u2 = prim->u3 = xMargin + width / 2;
            prim->v2 = prim->v3 = yMargin + height / 2;
        } else {
            if (self->facingLeft) {
                prim->x0 = prim->x2 = (selfX - width) + 1;
                prim->x1 = prim->x3 = selfX + 1;
            } else {
                prim->x0 = prim->x2 = selfX;
                prim->x1 = prim->x3 = selfX + width;
            }
            prim->y0 = prim->y1 = selfY + height * i / 8;
            prim->y2 = prim->y3 = selfY + height * (i + 1) / 8;
            if (self->facingLeft) {
                prim->u0 = prim->u2 = wSprite - 1;
                prim->u1 = prim->u3 = xMargin - 1;
            } else {
                prim->u0 = prim->u2 = xMargin;
                prim->u1 = prim->u3 = wSprite;
            }
            prim->v0 = prim->v1 = yMargin + height * i / 8;
            prim->v2 = prim->v3 = yMargin + height * (i + 1) / 8;
        }
        angleIdx1 = dataPtr[0];
        angleIdx2 = dataPtr[2];
        angleIdx3 = dataPtr[1];
        angleDivide1 = dataPtr[4];
        angleDivide2 = dataPtr[6];
        angleDivide3 = dataPtr[5];
        // clang-format off
        if (upperParams & 0x40) {
            prim->r0 = (((rsin((s16)D_80154F7C[(i + angleIdx1) % 8]) + 0x1000) >> 6) * self->ext.playerBlink.unk90 / angleDivide1);
            prim->g0 = (((rsin((s16)D_80154F7C[(i + angleIdx2) % 8]) + 0x1000) >> 6) * self->ext.playerBlink.unk90 / angleDivide2);
            prim->b0 = (((rsin((s16)D_80154F7C[(i + angleIdx3) % 8]) + 0x1000) >> 6) * self->ext.playerBlink.unk90 / angleDivide3);
            prim->r1 = (((rsin((s16)D_80154F7C[(i + angleIdx1 + 1) % 8]) + 0x1000) >> 6) * self->ext.playerBlink.unk90 / angleDivide1);
            prim->g1 = (((rsin((s16)D_80154F7C[(i + angleIdx2 + 1) % 8]) + 0x1000) >> 6) * self->ext.playerBlink.unk90 / angleDivide2);
            prim->b1 = (((rsin((s16)D_80154F7C[(i + angleIdx3 + 1) % 8]) + 0x1000) >> 6) * self->ext.playerBlink.unk90 / angleDivide3);
            prim->r2 = prim->g2 = prim->b2 = prim->r3 = prim->g3 = prim->b3 = 0;
            D_80154F7C[i] += self->ext.playerBlink.unk8A;
        } else {
            prim->r0 = prim->r1 =(((rsin((s16)D_80154F7C[(i + angleIdx1) % 8]) + 0x1000) >> 6) * self->ext.playerBlink.unk90 / angleDivide1);
            prim->g0 = prim->g1 =(((rsin((s16)D_80154F7C[(i + angleIdx2) % 8]) + 0x1000) >> 6) * self->ext.playerBlink.unk90 / angleDivide2);
            prim->b0 = prim->b1 =(((rsin((s16)D_80154F7C[(i + angleIdx3) % 8]) + 0x1000) >> 6) * self->ext.playerBlink.unk90 / angleDivide3);
            prim->r2 = prim->r3 =(((rsin((s16)D_80154F7C[(i + angleIdx1 + 1) % 8]) + 0x1000) >> 6) * self->ext.playerBlink.unk90 / angleDivide1);
            prim->g2 = prim->g3 =(((rsin((s16)D_80154F7C[(i + angleIdx2 + 1) % 8]) + 0x1000) >> 6) * self->ext.playerBlink.unk90 / angleDivide2);
            prim->b2 = prim->b3 =(((rsin((s16)D_80154F7C[(i + angleIdx3 + 1) % 8]) + 0x1000) >> 6) * self->ext.playerBlink.unk90 / angleDivide3);
            D_80154F7C[i] += self->ext.playerBlink.unk8A;
        }
        // clang-format on
        prim->priority = PLAYER.zPriority + 2;
        prim = prim->next;
    }
    if (((upperParams & 0x3F) == 0) || ((upperParams & 0x3F) == 7)) {
        func_8015CAD4(1, 10);
    }
}

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
// All 4 are used in RicHandleDeadPrologue. 36 alone (for instant child) is used
// when Richter does an item crash without a subweapon, in RicDoCrash.
// Creates a large semi-transparent circle around Richter which shrinks inward.
static s16 D_8015519C[][6] = {
    {0x0000, 0x0000, 0x0100, 0x0100, 0x0100, 0x0100},
    {0x0500, 0x0A00, 0x0100, 0x0100, 0x0100, 0x0000},
    {0x0000, 0x0000, 0x0100, 0x7000, 0x7000, 0x0200},
    {0x0000, 0x0000, 0x7100, 0x7100, 0x0100, 0x1000},
    {0x0000, 0x0000, 0x7100, 0x0100, 0x7000, 0x0800},
    {0x0000, 0x0000, 0x0100, 0x7100, 0x0100, 0x0400},
    {0x0500, 0x0A00, 0x0100, 0x0100, 0x0100, 0x0100},
    {0x0500, 0x0A00, 0x0100, 0x0200, 0x7100, 0x0100}};
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
    s32 constE0 = 0xE0;
    u32 upperparams = self->params & 0x7F00;
    s16* loadedParams = &D_8015519C[upperparams >> 8];

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
        self->step++;
        break;

    case 1:
        self->ext.ricPowerRing.unk7E += 0x40;
        self->ext.ricPowerRing.unk86 -= 10;
        if (self->ext.ricPowerRing.unk86 < 0) {
            self->ext.ricPowerRing.unk86 = 0;
            self->ext.ricPowerRing.unk7C = 0x20;
            self->step++;
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
            self->step++;
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
// RicHandleHit.
static Point16 D_801551FC = {0xFFFE, 0xFFE8};
static Point16 D_80155200 = {0x0000, 0xFFF8};
static Point16 D_80155204 = {0x0002, 0x0008};
static Point16 D_80155208 = {0x0000, 0x0018};
static Point16 D_8015520C = {0x0006, 0xFFF4};
static Point16 D_80155210 = {0x0008, 0x0000};
static Point16 D_80155214 = {0x0007, 0x000C};
static Point16 D_80155218 = {0xFFF8, 0xFFF4};
static Point16 D_8015521C = {0xFFF7, 0x0000};
static Point16 D_80155220 = {0xFFF9, 0x000C};
static Point16 D_80155224 = {0xFFF2, 0xFFFA};
static Point16 D_80155228 = {0xFFF1, 0x0007};
static Point16 D_8015522C = {0x000D, 0xFFF9};
static Point16 D_80155230 = {0x0010, 0x0008};
static Point16 D_80155234 = {0xFFF9, 0xFFEA};
static Point16 D_80155238 = {0x0006, 0xFFEB};
static Point16 D_8015523C = {0xFFF8, 0x0015};
static Point16 D_80155240 = {0x0007, 0x0016};
static Point16* D_80155244[] = {
    &D_801551FC, &D_8015520C, &D_80155200, &D_8015520C, &D_80155210,
    &D_80155200, &D_80155210, &D_80155204, &D_80155200, &D_80155210,
    &D_80155214, &D_80155204, &D_80155214, &D_80155208, &D_80155204,
    &D_80155204, &D_80155208, &D_80155220, &D_80155204, &D_80155220,
    &D_8015521C, &D_80155200, &D_80155204, &D_8015521C, &D_80155200,
    &D_8015521C, &D_80155218, &D_80155200, &D_80155218, &D_801551FC,
    &D_8015520C, &D_8015522C, &D_80155210, &D_8015522C, &D_80155230,
    &D_80155210, &D_80155230, &D_80155214, &D_80155210, &D_80155218,
    &D_8015521C, &D_80155224, &D_8015521C, &D_80155228, &D_80155224,
    &D_8015521C, &D_80155220, &D_80155228, &D_801551FC, &D_80155218,
    &D_80155234, &D_801551FC, &D_80155238, &D_8015520C, &D_80155208,
    &D_8015523C, &D_80155220, &D_80155214, &D_80155240, &D_80155208,
    &D_80155234, &D_80155218, &D_80155224, &D_80155238, &D_8015522C,
    &D_8015520C, &D_80155228, &D_80155220, &D_8015523C, &D_80155230,
    &D_80155240, &D_80155214};
void RicEntityHitByIce(Entity* self) {
    const int PrimCount = LEN(D_80155244) / 3;
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
        self->primIndex = g_api.AllocPrimitives(PRIM_GT3, PrimCount);
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
            if (!PLAYER.facingLeft) {
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
        if (PLAYER.step == PL_S_DEAD) {
            if (!PLAYER.facingLeft) {
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
        if (PLAYER.step == PL_S_DEAD) {
            if ((PLAYER.animCurFrame & 0x7FFF) == 0x21) {
                if (!PLAYER.facingLeft) {
                    self->rotZ = -0x280;
                } else {
                    self->rotZ = 0x280;
                }
            }
            if ((PLAYER.animCurFrame & 0x7FFF) == 0x22) {
                if (!PLAYER.facingLeft) {
                    self->rotZ = -0x380;
                } else {
                    self->rotZ = 0x380;
                }
            }
            if ((PLAYER.animCurFrame & 0x7FFF) == 0x20) {
                if (!PLAYER.facingLeft) {
                    self->rotZ = -0x180;
                } else {
                    self->rotZ = 0x180;
                }
            }
        }
        if (self->ext.hitbyice.unk80 && !--self->ext.hitbyice.unk82) {
            sp18 = true;
        }
        if ((self->ext.hitbyice.unk7E) && (g_Player.pl_vram_flag & 0xC)) {
            sp18 = true;
        }
        if (sp18) {
            self->ext.hitbyice.unk7C = 0x40;
            if (self->ext.hitbyice.unk80) {
                self->ext.hitbyice.unk7C = 0x80;
            }
            self->step++;
        }
        break;
    case 2:
        if (!--self->ext.hitbyice.unk7C) {
            DestroyEntity(self);
            return;
        }
        break;
    }

    selfX = self->posX.i.hi;
    selfY = self->posY.i.hi;
    prim = &g_PrimBuf[self->primIndex];
    for (i = 0; i < PrimCount; i++) {
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

static s16 lightning_clut[] = {0x194, 0x199};
void RicEntityHitByLightning(Entity* self) {
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
            prim->clut = lightning_clut[rand() & 1];
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
static s32 D_80155368[] = {255, 255, 255, 127, 127, 63, 127, 63, 127};
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
