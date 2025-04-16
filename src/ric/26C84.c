// SPDX-License-Identifier: AGPL-3.0-or-later
#include "ric.h"

// same as DRA/func_8011BD48
bool func_80162E9C(Entity* entity) {
    Entity* e;
    s32 i;
    s16 objId;
    s16 params;

    objId = entity->entityId;
    params = entity->params;
    for (e = &g_Entities[16], i = 16; i < STAGE_ENTITY_START; e++, i++) {
        if (objId == e->entityId && params == e->params && e != entity) {
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
    u8 xMargin;
    u8 yMargin;
    s16 angle;
    u8 wSprite;
    u8 hSprite;
    s16 width;
    s16 height;
    s16 selfX;
    s16 selfY;
    s32 i;
    Primitive* prim;
    s16 xPivot;
    s16 yPivot;
    s16 plSpriteIndex;
    s16 upperParams;
    s16 angleRedIndex;
    s16* sp44;
    u8* plSprite;
    s16* dataPtr;
    s16 angleGreenIndex;
    s16 angleBlueIndex;
    s16 redDivide;
    s16 blueDivide;
    s16 greenDivide;
    void* dummy48;

    if (!PLAYER.animSet || !(PLAYER.animCurFrame & 0x7FFF)) {
        DestroyEntity(self);
        return;
    }
    self->posY.i.hi = PLAYER.posY.i.hi;
    self->posX.i.hi = PLAYER.posX.i.hi;
    self->facingLeft = PLAYER.facingLeft;
    sp44 = D_92641C8[PLAYER.animCurFrame & 0x7FFF];
    sp44 = D_801530AC[PLAYER.animCurFrame & 0x7FFF];
    plSpriteIndex = *sp44++;
    plSpriteIndex &= 0x7FFF;
    selfX = self->posX.i.hi;
    selfY = self->posY.i.hi;
    plSprite = ((u8**)SPRITESHEET_PTR)[plSpriteIndex];
    xMargin = 4;
    yMargin = 1;
    wSprite = xMargin + plSprite[0];
    hSprite = yMargin + plSprite[1];
    width = wSprite - xMargin;
    height = hSprite - yMargin;
    xPivot = sp44[0] + plSprite[2];
    yPivot = sp44[1] + plSprite[3];

    self->rotZ = PLAYER.rotZ;
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
        self->flags = FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_HAS_PRIMS |
                      FLAG_POS_PLAYER_LOCKED | FLAG_UNK_20000 | FLAG_UNK_10000;
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
                if (g_Player.timers[PL_T_POISON] == 0) {
                    self->step++;
                }
                break;
            case 0x7001:
                if (g_Player.timers[PL_T_INVINCIBLE_SCENE] == 0) {
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
            self->step++;
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
        selfX = selfX - xPivot;
    } else {
        selfX = selfX + xPivot;
    }
    selfY = selfY + yPivot;
    prim = &g_PrimBuf[self->primIndex];
    for (i = 0; i < 8; i++) {
        if (upperParams & 0x40) {
            switch (i) {
            case 0:
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
                if (self->facingLeft) {
                    prim->x0 = prim->x1 = selfX;
                    prim->u0 = prim->u1 = xMargin;
                } else {
                    prim->x0 = prim->x1 = selfX;
                    prim->u0 = prim->u1 = xMargin;
                }
                prim->y0 = selfY + height;
                prim->y1 = selfY + height / 2;
                prim->v0 = yMargin + height;
                prim->v1 = yMargin + height / 2;
                break;
            case 7:
                if (self->facingLeft) {
                    prim->x0 = prim->x1 = selfX;
                    prim->u0 = prim->u1 = xMargin;
                } else {
                    prim->x0 = prim->x1 = selfX;
                    prim->u0 = prim->u1 = xMargin;
                }
                prim->y0 = selfY + height / 2;
                prim->y1 = selfY;
                prim->v0 = yMargin + height / 2;
                prim->v1 = yMargin;
                break;
            }
            if (self->facingLeft) {
                prim->x2 = prim->x3 =
                    selfX - width / 2 +
                    (((rcos(self->ext.playerBlink.unk82) >> 4) * 3) >> 0xC);
            } else {
                prim->x2 = prim->x3 =
                    selfX + width / 2 +
                    (((rcos(self->ext.playerBlink.unk82) >> 4) * 3) >> 0xC);
            }
            prim->y2 = prim->y3 =
                (selfY + height / 2) -
                ((rsin(self->ext.playerBlink.unk82) >> 4) * 3 << 1 >> 8);
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
        angleRedIndex = dataPtr[0];
        angleGreenIndex = dataPtr[2];
        angleBlueIndex = dataPtr[1];
        redDivide = dataPtr[4];
        greenDivide = dataPtr[6];
        blueDivide = dataPtr[5];
        if (upperParams & 0x40) {
            angle = D_80154F7C[(i + angleRedIndex) % 8];
            prim->r0 = ((rsin(angle) + 0x1000) >> 6) *
                       self->ext.playerBlink.unk90 / redDivide;
            angle = D_80154F7C[(i + angleGreenIndex) % 8];
            prim->g0 = ((rsin(angle) + 0x1000) >> 6) *
                       self->ext.playerBlink.unk90 / greenDivide;
            angle = D_80154F7C[(i + angleBlueIndex) % 8];
            prim->b0 = ((rsin(angle) + 0x1000) >> 6) *
                       self->ext.playerBlink.unk90 / blueDivide;
            angle = D_80154F7C[(i + angleRedIndex + 1) % 8];
            prim->r1 = ((rsin(angle) + 0x1000) >> 6) *
                       self->ext.playerBlink.unk90 / redDivide;
            angle = D_80154F7C[(i + angleGreenIndex + 1) % 8];
            prim->g1 = ((rsin(angle) + 0x1000) >> 6) *
                       self->ext.playerBlink.unk90 / greenDivide;
            angle = D_80154F7C[(i + angleBlueIndex + 1) % 8];
            prim->b1 = ((rsin(angle) + 0x1000) >> 6) *
                       self->ext.playerBlink.unk90 / blueDivide;
            prim->r2 = prim->g2 = prim->b2 = prim->r3 = prim->g3 = prim->b3 = 0;
            D_80154F7C[i] += self->ext.playerBlink.unk8A;
        } else {
            angle = D_80154F7C[(i + angleRedIndex) % 8];
            prim->r0 = prim->r1 = (((rsin(angle) + 0x1000) >> 6) *
                                   self->ext.playerBlink.unk90 / redDivide);
            angle = D_80154F7C[(i + angleGreenIndex) % 8];
            prim->g0 = prim->g1 = (((rsin(angle) + 0x1000) >> 6) *
                                   self->ext.playerBlink.unk90 / greenDivide);
            angle = D_80154F7C[(i + angleBlueIndex) % 8];
            prim->b0 = prim->b1 = (((rsin(angle) + 0x1000) >> 6) *
                                   self->ext.playerBlink.unk90 / blueDivide);
            angle = D_80154F7C[(i + angleRedIndex + 1) % 8];
            prim->r2 = prim->r3 = (((rsin(angle) + 0x1000) >> 6) *
                                   self->ext.playerBlink.unk90 / redDivide);
            angle = D_80154F7C[(i + angleGreenIndex + 1) % 8];
            prim->g2 = prim->g3 = (((rsin(angle) + 0x1000) >> 6) *
                                   self->ext.playerBlink.unk90 / greenDivide);
            angle = D_80154F7C[(i + angleBlueIndex + 1) % 8];
            prim->b2 = prim->b3 = (((rsin(angle) + 0x1000) >> 6) *
                                   self->ext.playerBlink.unk90 / blueDivide);
            D_80154F7C[i] += self->ext.playerBlink.unk8A;
        }
        prim->priority = PLAYER.zPriority + 2;
        prim = prim->next;
    }
    if ((upperParams & 0x3F) == 0 || (upperParams & 0x3F) == 7) {
        RicSetInvincibilityFrames(1, 10);
    }
}

void func_801641A0(Entity* self) {
    Primitive* prim;
    s16 primIndex;

    self->posX.i.hi = PLAYER.posX.i.hi - 0;
    self->posY.i.hi = PLAYER.posY.i.hi - 8;
    switch (self->step) {
    case 0:
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->ext.circleExpand.width = 16;
        self->ext.circleExpand.height = 12;
        prim = &g_PrimBuf[self->primIndex];
        prim->u0 = prim->u2 = 64;
        prim->v0 = prim->v1 = 192;
        prim->u1 = prim->u3 = 127;
        prim->v2 = prim->v3 = 255;
        PGREY(prim, 0) = PGREY(prim, 1) = PGREY(prim, 2) = PGREY(prim, 3) = 128;
        prim->tpage = 0x1A;
        prim->clut = 0x160;
        prim->priority = PLAYER.zPriority + 8;
        prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
        self->flags =
            FLAG_POS_PLAYER_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_HAS_PRIMS;
        self->step++;
        break;

    case 1:
        self->ext.circleExpand.width += 2;
        self->ext.circleExpand.height += 2;
        if (self->ext.circleExpand.width > 56) {
            DestroyEntity(self);
            return;
        }
        break;
    }

    prim = &g_PrimBuf[self->primIndex];
    prim->x0 = self->posX.i.hi - self->ext.circleExpand.width;
    prim->y0 = self->posY.i.hi - self->ext.circleExpand.height;
    prim->x1 = self->posX.i.hi + self->ext.circleExpand.width;
    prim->y1 = self->posY.i.hi - self->ext.circleExpand.height;
    prim->x2 = self->posX.i.hi - self->ext.circleExpand.width;
    prim->y2 = self->posY.i.hi + self->ext.circleExpand.height;
    prim->x3 = self->posX.i.hi + self->ext.circleExpand.width;
    prim->y3 = self->posY.i.hi + self->ext.circleExpand.height;
    if (prim->b3 >= 12) {
        prim->b3 -= 12;
    }
    // remember last element of PGREY(prim,3) is prim->b3
    PGREY(prim, 0) = PGREY(prim, 1) = PGREY(prim, 2) = PGREY(prim, 3);
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
void RicEntityShrinkingPowerUpRing(Entity* self) {
    s16 variant;
    s16 rMod;
    s16* loadedParams;
    s16 x;
    s16 gMod;
    s16 bMod;
    s16 gOffset;
    s16 bOffset;
    s16 angleStart;
    s16 y;
    s16 baseAngle;
    s32 i;
    s16 angle;
    Primitive* prim1;
    Primitive* prim2;

    variant = (self->params & 0x7F00) >> 8;
    loadedParams = D_8015519C[variant];
    rMod = loadedParams[2];
    gMod = loadedParams[3];
    bMod = loadedParams[4];
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
        self->flags = FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_HAS_PRIMS |
                      FLAG_POS_PLAYER_LOCKED | FLAG_UNK_10000;
        x = self->posX.i.hi;
        y = self->posY.i.hi;
        prim2 = prim1 = &g_PrimBuf[self->primIndex];
        for (i = 0; i < 16; i++) {
            prim1 = prim1->next;
        }
        for (i = 0; i < 16; i++) {
            angle = i << 8;
            prim2->u0 = (rcos(angle) >> 4 << 5 >> 8) + 0x20;
            prim2->v0 = -(rsin(angle) >> 4 << 5 >> 8) + 0xDF;
            angle = (i + 1) << 8;
            prim2->u1 = (rcos(angle) >> 4 << 5 >> 8) + 0x20;
            prim2->v1 = -(rsin(angle) >> 4 << 5 >> 8) + 0xDF;
            prim1->u2 = prim1->u3 = 0x20;
            prim1->v2 = prim1->v3 = 0xDF;
            prim2->u2 = prim1->u0 = (prim2->u0 + prim1->u2) / 2;
            prim2->v2 = prim1->v0 = (prim2->v0 + prim1->v2) / 2;
            prim2->u3 = prim1->u1 = (prim2->u1 + prim1->u3) / 2;
            prim2->v3 = prim1->v1 = (prim2->v1 + prim1->v3) / 2;
            prim1->tpage = prim2->tpage = 0x1A;
            prim1->clut = prim2->clut = 0x15F;
            prim1->priority = prim2->priority = PLAYER.zPriority + 2;
            prim1->drawMode = prim2->drawMode =
                DRAW_UNK_200 | DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS |
                DRAW_TRANSP;
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
        self->ext.ricPowerRing.unk7E += 0x40;
        self->ext.ricPowerRing.unk82 -= 3;
        self->ext.ricPowerRing.unk80 -= 6;
        self->ext.ricPowerRing.unk88 -= 12;
        if (self->ext.ricPowerRing.unk88 < 0) {
            DestroyEntity(self);
            return;
        }
        break;
    }
    angleStart = self->ext.ricPowerRing.unk8A;
    x = self->posX.i.hi;
    y = self->posY.i.hi;
    prim1 = prim2 = &g_PrimBuf[self->primIndex];
    for (i = 0; i < 16; i++) {
        prim1 = prim1->next;
    }
    for (i = 0; i < 16; i++) {
        prim2->x0 =
            x + (prim2->u0 - 0x20) * self->ext.ricPowerRing.unk80 / 0x100;
        prim2->y0 =
            y + (prim2->v0 - 0xE0) * self->ext.ricPowerRing.unk82 / 0x100;
        prim2->x1 =
            x + (prim2->u1 - 0x20) * self->ext.ricPowerRing.unk80 / 0x100;
        prim2->y1 =
            y + (prim2->v1 - 0xE0) * self->ext.ricPowerRing.unk82 / 0x100;
        prim1->x2 = x + (rcos((i + 1) << 8) >> 4 << 5 >> 8) *
                            self->ext.ricPowerRing.unk84 / 0x100;
        prim1->y2 = y - (rsin((i + 1) << 8) >> 4 << 5 >> 8) *
                            self->ext.ricPowerRing.unk86 / 0x100;
        prim1->x3 = x + (rcos((i + 2) << 8) >> 4 << 5 >> 8) *
                            self->ext.ricPowerRing.unk84 / 0x100;
        prim1->y3 = y - (rsin((i + 2) << 8) >> 4 << 5 >> 8) *
                            self->ext.ricPowerRing.unk86 / 0x100;
        prim2->x2 = prim1->x0 = (prim2->x0 + prim1->x2) / 2;
        prim2->y2 = prim1->y0 = (prim2->y0 + prim1->y2) / 2;
        prim2->x3 = prim1->x1 = (prim2->x1 + prim1->x3) / 2;
        prim2->y3 = prim1->y1 = (prim2->y1 + prim1->y3) / 2;
        baseAngle = i * angleStart;
        angle = self->ext.ricPowerRing.unk7E + baseAngle;
        prim1->r0 = prim2->r2 =
            ((rsin(angle) + 0x1000) >> 7) * self->ext.ricPowerRing.unk88 / rMod;
        angle = self->ext.ricPowerRing.unk7E + gOffset + baseAngle;
        prim1->g0 = prim2->g2 =
            ((rsin(angle) + 0x1000) >> 7) * self->ext.ricPowerRing.unk88 / gMod;
        angle = self->ext.ricPowerRing.unk7E + bOffset + baseAngle;
        prim1->b0 = prim2->b2 =
            ((rsin(angle) + 0x1000) >> 7) * self->ext.ricPowerRing.unk88 / bMod;
        angle = self->ext.ricPowerRing.unk7E + angleStart + baseAngle;
        prim1->r1 = prim2->r3 =
            ((rsin(angle) + 0x1000) >> 7) * self->ext.ricPowerRing.unk88 / rMod;
        angle = self->ext.ricPowerRing.unk7E + gOffset + angleStart + baseAngle;
        prim1->g1 = prim2->g3 =
            ((rsin(angle) + 0x1000) >> 7) * self->ext.ricPowerRing.unk88 / gMod;
        angle = self->ext.ricPowerRing.unk7E + bOffset + angleStart + baseAngle;
        prim1->b1 = prim2->b3 =
            ((rsin(angle) + 0x1000) >> 7) * self->ext.ricPowerRing.unk88 / bMod;
        prim2->r0 = prim2->g0 = prim2->b0 = prim2->r1 = prim2->g1 = prim2->b1 =
            0;
        prim1->r2 = prim1->g2 = prim1->b2 = prim1->r3 = prim1->g3 = prim1->b3 =
            0;
        prim2 = prim2->next;
        prim1 = prim1->next;
    }
}

// Entity ID #40. Created by blueprint 47. That factory comes from
// RicHandleHit.
static Point16 D_801551FC = {-2, -24};
static Point16 D_80155200 = {0, -8};
static Point16 D_80155204 = {2, 8};
static Point16 D_80155208 = {0, 24};
static Point16 D_8015520C = {6, -12};
static Point16 D_80155210 = {8, 0};
static Point16 D_80155214 = {7, 12};
static Point16 D_80155218 = {-8, -12};
static Point16 D_8015521C = {-9, 0};
static Point16 D_80155220 = {-7, 12};
static Point16 D_80155224 = {-14, -6};
static Point16 D_80155228 = {-15, 7};
static Point16 D_8015522C = {13, -7};
static Point16 D_80155230 = {16, 8};
static Point16 D_80155234 = {-7, -22};
static Point16 D_80155238 = {6, -21};
static Point16 D_8015523C = {-8, 21};
static Point16 D_80155240 = {7, 22};
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
    s16 x;
    s16 y;
    s32 i;
    bool terminateFlag;
    s16 deltaX;
    s16 deltaY;
    s16 yMod;
    s32 distance;
    s16 angle;
    Point16* pos;
    Primitive* prim;

    self->posX.i.hi = PLAYER.posX.i.hi;
    self->posY.i.hi = PLAYER.posY.i.hi;
    terminateFlag = 0;
    if (!(g_Player.status & PLAYER_STATUS_UNK10000)) {
        terminateFlag = 1;
    }
    switch (self->step) {
    case 0:
        self->primIndex = g_api.AllocPrimitives(PRIM_GT3, PrimCount);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags = FLAG_HAS_PRIMS | FLAG_POS_PLAYER_LOCKED | FLAG_UNK_20000;
        prim = &g_PrimBuf[self->primIndex];
        while (prim != NULL) {
            prim->r0 = prim->r1 = prim->r2 = prim->r3 = (rand() & 0x0F) + 0x30;
            prim->b0 = prim->b1 = prim->b2 = prim->b3 = (rand() & 0x7F) + 0x80;
            prim->g0 = prim->g1 = prim->g2 = prim->g3 = (rand() & 0x1F) + 0x30;
            if (rand() & 1) {
                prim->drawMode = DRAW_UNK_200 | DRAW_UNK_100 | DRAW_TPAGE2 |
                                 DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
            } else {
                prim->drawMode = DRAW_UNK_200 | DRAW_UNK_100 | DRAW_TPAGE |
                                 DRAW_COLORS | DRAW_TRANSP;
            }
            prim->type = PRIM_G4;
            prim->priority = PLAYER.zPriority + 2;
            prim = prim->next;
        }
        // Weird repeated conditional
        if (PLAYER.velocityY != 0) {
            self->ext.hitbyice.unk7E = 1;
        }
        if (PLAYER.velocityY != 0) {
            if (PLAYER.facingLeft) {
                self->rotZ = 0x100;
            } else {
                self->rotZ = -0x100;
            }
        } else {
            if (PLAYER.velocityX > 0) {
                self->rotZ = 0x80;
            } else {
                self->rotZ = 0xF80;
            }
        }
        if (PLAYER.step == PL_S_DEAD) {
            if (PLAYER.facingLeft) {
                self->rotZ = 0x180;
            } else {
                self->rotZ = -0x180;
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
                if (PLAYER.facingLeft) {
                    self->rotZ = 0x280;
                } else {
                    self->rotZ = -0x280;
                }
            }
            if ((PLAYER.animCurFrame & 0x7FFF) == 0x22) {
                if (PLAYER.facingLeft) {
                    self->rotZ = 0x380;
                } else {
                    self->rotZ = -0x380;
                }
            }
            if ((PLAYER.animCurFrame & 0x7FFF) == 0x20) {
                if (PLAYER.facingLeft) {
                    self->rotZ = 0x180;
                } else {
                    self->rotZ = -0x180;
                }
            }
        }
        if (self->ext.hitbyice.unk80 && --self->ext.hitbyice.unk82 == 0) {
            terminateFlag = true;
        }
        if (self->ext.hitbyice.unk7E && g_Player.vram_flag & 0xC) {
            terminateFlag = true;
        }
        if (terminateFlag) {
            self->ext.hitbyice.unk7C = 0x40;
            if (self->ext.hitbyice.unk80) {
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

    x = self->posX.i.hi;
    y = self->posY.i.hi;
    prim = &g_PrimBuf[self->primIndex];
    for (i = 0; i < PrimCount; i++) {
        pos = D_80155244[i * 3];
        if (prim->u0 < 2) {
            distance = SquareRoot12((pos->x * pos->x + pos->y * pos->y) << 0xC);
            angle = self->rotZ + ratan2(pos->y, pos->x);
            deltaX = (((rcos(angle) >> 4) * distance) + 0x80000) >> 0x14;
            deltaY = (((rsin(angle) >> 4) * distance) + 0x80000) >> 0x14;
            prim->x0 = x + deltaX;
            prim->y0 = y + deltaY;

            pos = D_80155244[i * 3 + 1];
            distance = SquareRoot12((pos->x * pos->x + pos->y * pos->y) << 0xC);
            angle = self->rotZ + ratan2(pos->y, pos->x);
            deltaX = (((rcos(angle) >> 4) * distance) + 0x80000) >> 0x14;
            deltaY = (((rsin(angle) >> 4) * distance) + 0x80000) >> 0x14;
            prim->x1 = x + deltaX;
            prim->y1 = y + deltaY;

            pos = D_80155244[i * 3 + 2];
            distance = SquareRoot12((pos->x * pos->x + pos->y * pos->y) << 0xC);
            angle = self->rotZ + ratan2(pos->y, pos->x);
            deltaX = (((rcos(angle) >> 4) * distance) + 0x80000) >> 0x14;
            deltaY = (((rsin(angle) >> 4) * distance) + 0x80000) >> 0x14;
            prim->x2 = prim->x3 = x + deltaX;
            prim->y2 = prim->y3 = y + deltaY;
        }
        if (prim->u0 == 0 && terminateFlag) {
            prim->u0++;
            prim->v0 = (rand() & 15) + 1;
            if (self->ext.hitbyice.unk80) {
                prim->v0 = (rand() % 60) + 1;
            }
        }
        if (prim->u0 == 1) {
            if (--prim->v0 == 0) {
                prim->u0++;
                prim->v0 = 0x20;
                prim->u2 = 0xF0;
                if (self->ext.hitbyice.unk80) {
                    prim->v0 = (rand() & 31) + 0x28;
                }
            }
        }
        if (prim->u0 == 2) {
            if (prim->u2 < 0x70 || prim->u2 > 0xD0) {
                prim->u2 += 4;
            }
            yMod = (s8)prim->u2 >> 4;
            if (self->ext.hitbyice.unk80) {
                yMod = yMod >> 1;
            }
            prim->y0 += yMod;
            prim->y1 += yMod;
            prim->y2 += yMod;
            prim->y3 += yMod;
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
            prim->drawMode |= DRAW_UNK02;
            prim->drawMode &= ~(DRAW_UNK_200 | DRAW_UNK_100);
            if (--prim->v0 == 0) {
                prim->drawMode |= DRAW_HIDE;
            }
        }
        prim = prim->next;
    }
}

static u16 lightning_clut[] = {0x194, 0x199};
void RicEntityHitByLightning(Entity* self) {
    s16 x;
    s16 y;
    s16 mul2;
    s32 i;
    s32 xMod;
    s32 yMod;
    bool terminate;
    s32 mul;
    s16 angle;
    Primitive* primPrev;
    Primitive* prim;

    terminate = false;
    if ((self->params & 0xFF00) == 0x100) {
        if ((++self->ext.hitbylightning.unk9C) > 0xA8) {
            terminate = true;
        }
    } else if ((self->params & 0xFF00) == 0x200) {
        if (++self->ext.hitbylightning.unk9C > 0x90) {
            terminate = true;
        }
    } else if (PLAYER.step != PL_S_HIT) {
        terminate = true;
    }
    switch (self->step) {
    case 0:
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 6);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }

        self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_HAS_PRIMS | FLAG_UNK_20000;
        self->ext.hitbylightning.unk7C =
            ((self->params & 0xF) << 9) + (rand() & 0x3F);
        self->ext.hitbylightning.unk80 = (rand() & PSP_RANDMASK);
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
            prim->drawMode = DRAW_UNK_100 | DRAW_TPAGE2 | DRAW_TPAGE |
                             DRAW_UNK02 | DRAW_TRANSP;
            prim = prim->next;
        }
        if ((PLAYER.velocityY != 0) && (PLAYER.step != PL_S_DEAD)) {
            self->ext.hitbylightning.unk92 = 1;
        }
        self->ext.hitbylightning.unk94 = 0x10;
        self->step++;
        break;
    case 1:
        self->ext.hitbylightning.unk7C =
            ((self->params & 0xF) << 9) + (rand() & 0x1FF);
        mul = rsin(self->ext.hitbylightning.unk80);
        self->ext.hitbylightning.unk80 += self->ext.hitbylightning.unk82;
        xMod = ((rcos(self->ext.hitbylightning.unk7C) * mul) >> 7) * 12;
        yMod = (-((rsin(self->ext.hitbylightning.unk7C) * mul) >> 7) * 7) << 1;
        self->posX.val = xMod + PLAYER.posX.val;
        self->posY.val = yMod + PLAYER.posY.val;
        if (self->ext.hitbylightning.unk92 && g_Player.vram_flag & 0xE) {
            terminate = true;
        }
        if (terminate) {
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
        mul = rsin(self->ext.hitbylightning.unk80);
        self->ext.hitbylightning.unk80 += self->ext.hitbylightning.unk82;
        xMod = ((rcos(self->ext.hitbylightning.unk7C) * mul) >> 7) *
               ((rand() % 8) + 8);
        yMod = -((rsin(self->ext.hitbylightning.unk7C) * mul) >> 7) *
                   ((rand() % 8) + 10) +
               self->ext.hitbylightning.unk98;
        self->posX.val = PLAYER.posX.val + xMod;
        self->posY.val = PLAYER.posY.val + yMod;
        self->ext.hitbylightning.unk98 -= 0x8000;
        prim = &g_PrimBuf[self->primIndex];
        break;
    }

    x = (self->posX.i.hi + (rand() & 7)) - 4;
    y = (self->posY.i.hi + (rand() & 0x1F)) - 0x18;
    mul2 = self->ext.hitbylightning.unk94;
    mul2 = (mul2 * rsin(self->ext.hitbylightning.unk80)) >> 0xC;
    prim = &g_PrimBuf[self->primIndex];
    for (i = 0; i < 5; i++) {
        primPrev = prim;
        prim = prim->next;
        *primPrev = *prim;
        primPrev->next = prim;
        primPrev->u0 = primPrev->u2 = (i * 0x10) + 0x90;
        primPrev->u1 = primPrev->u3 = ((i + 1) * 0x10) + 0x90;
        primPrev->v0 = primPrev->v1 = 0xC0;
        primPrev->v2 = primPrev->v3 = 0xCF;
    }
    prim->x0 = prim->x1;
    prim->y0 = prim->y1;
    prim->x2 = prim->x3;
    prim->y2 = prim->y3;
    angle = self->ext.hitbylightning.unk7C + 0x400;
    prim->x1 = x + (((rcos(angle) >> 4) * mul2) >> 8);
    prim->y1 = y - (((rsin(angle) >> 4) * mul2) >> 8);
    angle = self->ext.hitbylightning.unk7C - 0x400;
    prim->x3 = x + (((rcos(angle) >> 4) * mul2) >> 8);
    prim->y3 = y - (((rsin(angle) >> 4) * mul2) >> 8);
    angle = self->ext.hitbylightning.unk80 & 0xFFF;
    if (angle < 0x400) {
        prim->priority = PLAYER.zPriority + 2;
    } else if (angle < 0xC00) {
        prim->priority = PLAYER.zPriority - 2;
    } else {
        prim->priority = PLAYER.zPriority + 2;
    }
    prim->u0 = prim->u2 = (i << 4) + 0x90;
    prim->u1 = prim->u3 = ((i + 1) << 4) + 0x90;
    prim->v0 = prim->v1 = 0xC0;
    prim->v2 = prim->v3 = 0xCF;
}

// Corresponding DRA function is func_80124164
static s32 D_800AE270 = 255;
static s32 D_800AE274 = 255;
static s32 D_800AE278 = 255;
static s32 D_800AE27C = 127;
static s32 D_800AE280 = 127;
static s32 D_800AE284 = 63;
static s32 D_800AE288 = 127;
static s32 D_800AE28C = 63;
static s32 D_800AE290 = 127;
void func_80165DD8(
    Primitive* prim, s32 colorMul, s32 y, s32 radius, bool arg4) {
    prim->y0 = prim->y1 = y - radius;
    prim->y2 = prim->y3 = y + radius;
    if (prim->y0 < 0) {
        prim->y0 = prim->y1 = 0;
    }
    if (prim->y0 > 240) {
        prim->y2 = prim->y3 = 240;
    }
    if (arg4 == 0) {
        prim->r1 = prim->r3 = D_800AE270 * colorMul / 256;
        prim->g1 = prim->g3 = D_800AE274 * colorMul / 256;
        prim->b1 = prim->b3 = D_800AE278 * colorMul / 256;
        prim->r0 = prim->r2 = D_800AE27C * colorMul / 256;
        prim->g0 = prim->g2 = D_800AE280 * colorMul / 256;
        prim->b0 = prim->b2 = D_800AE284 * colorMul / 256;
    } else {
        prim->r1 = prim->r3 = D_800AE270 * colorMul / 256;
        prim->g1 = prim->g3 = D_800AE274 * colorMul / 256;
        prim->b1 = prim->b3 = D_800AE278 * colorMul / 256;
        prim->r0 = prim->r2 = D_800AE288 * colorMul / 256;
        prim->g0 = prim->g2 = D_800AE28C * colorMul / 256;
        prim->b0 = prim->b2 = D_800AE290 * colorMul / 256;
    }
}

void func_80166024() {
    PLAYER.palette = 0x815E;
    PLAYER.drawMode = DRAW_UNK_40 | DRAW_TPAGE2 | DRAW_TPAGE;
}

void func_80166044() {
    PLAYER.palette = 0x8120;
    PLAYER.drawMode = DRAW_DEFAULT;
}
