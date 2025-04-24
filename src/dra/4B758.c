// SPDX-License-Identifier: AGPL-3.0-or-later
#include "dra.h"
#include "dra_bss.h"

void func_800EB758(
    s16 pivotX, s16 pivotY, Entity* e, u8 flags, POLY_GT4* p, u8 flipX) {
    const int H_CENTER = FLT(STAGE_WIDTH / 2);
    s16 px, py;
    s16 dx, dy;
    s32 rot;
    s32 distance;
    s32 angle;
    s16 rx0, ry0;
    s16 rx1, ry1;
    s16 rx2, ry2;
    s16 rx3, ry3;
    s16 scaledValue;

    if (flipX) {
        px = pivotX - e->rotPivotX;
    } else {
        px = e->rotPivotX + pivotX;
    }
    py = pivotY + e->rotPivotY;

    if (flags & FLAG_DRAW_ROTX) {
        scaledValue = (e->rotX * (s16)(p->x0 - px) - 0x80000000) >> 8;
        p->x0 = p->x2 = scaledValue + px;
        scaledValue = (e->rotX * (s16)(p->x1 - px) - 0x80000000) >> 8;
        p->x1 = p->x3 = scaledValue + px;
    }
    if (flags & FLAG_DRAW_ROTY) {
        scaledValue = (e->rotY * (s16)(p->y0 - py) - 0x80000000) >> 8;
        p->y0 = p->y1 = scaledValue + py;
        scaledValue = (e->rotY * (s16)(p->y2 - py) - 0x80000000) >> 8;
        p->y2 = p->y3 = scaledValue + py;
    }
    if (flags & FLAG_DRAW_ROTZ) {
        if (flipX) {
            rot = -e->rotZ;
        } else {
            rot = e->rotZ;
        }

        dx = p->x0 - px;
        dy = p->y0 - py;
        distance = SquareRoot12((dx * dx + dy * dy) * FLT(1.0));
        angle = ratan2(dy, dx) + rot;
        rx0 = ((rcos(angle) >> 4) * distance + H_CENTER) >> 0x14;
        ry0 = ((rsin(angle) >> 4) * distance + H_CENTER) >> 0x14;
        p->x0 = rx0 + px;
        p->y0 = ry0 + py;

        dx = p->x1 - px;
        dy = p->y1 - py;
        distance = SquareRoot12((dx * dx + dy * dy) * FLT(1.0));
        angle = ratan2(dy, dx) + rot;
        rx1 = ((rcos(angle) >> 4) * distance + H_CENTER) >> 0x14;
        ry1 = ((rsin(angle) >> 4) * distance + H_CENTER) >> 0x14;
        p->x1 = rx1 + px;
        p->y1 = ry1 + py;

        dx = p->x2 - px;
        dy = p->y2 - py;
        distance = SquareRoot12((dx * dx + dy * dy) * 4096);
        angle = ratan2(dy, dx) + rot;
        rx2 = ((rcos(angle) >> 4) * distance + H_CENTER) >> 0x14;
        ry2 = ((rsin(angle) >> 4) * distance + H_CENTER) >> 0x14;
        p->x2 = rx2 + px;
        p->y2 = ry2 + py;

        dx = p->x3 - px;
        dy = p->y3 - py;
        distance = SquareRoot12((dx * dx + dy * dy) * 4096);
        angle = ratan2(dy, dx) + rot;
        rx3 = ((rcos(angle) >> 4) * distance + H_CENTER) >> 0x14;
        ry3 = ((rsin(angle) >> 4) * distance + H_CENTER) >> 0x14;
        p->x3 = rx3 + px;
        p->y3 = ry3 + py;
    }
}

void ResetEntityArray(void) {
    Entity* entity;
    u8* ch;
    s32 i;
    u32 j;

    entity = &g_Entities[0];
    for (i = 0; i < LEN(g_Entities); i++) {
        ch = (s8*)entity;
        for (j = 0; j < sizeof(Entity); j++) {
            *ch++ = 0;
        }
        entity++;
    }
}

typedef struct {
    s16 unk0;
    s16 animSet;
    s16 animCurFrame;
    u16 w;
    u16 h;
    s16 x;
    s16 y;
    s16 xPivot;
    s16 yPivot;
    u16 unused12;
    s32 index;
    s32 index2;
    u32 spriteSheetIdx;
    s32 flipX; // set to 2 when facing left, 0 when not
    s32 eDrawFlags;
    OT_TYPE* ot;
    POLY_GT4* poly;
} EntitiesRenderer;

void RenderEntities(void) {
    s16 polyX;
    s16 polyY;
    s32 animFrameFlags;
    Entity* entity;
    s16* animFrame; // might be a struct
    u8 uvRight;
    u8 uvTop;
    s32 tempFlagCheck;
    s16** spriteBank;
    u8* spriteData;
    PlayerDraw* plDraw;
    u16 palette;
    u16 pose;
    u8 uvLeft;
    u8 uvBottom;
    POLY_GT4* poly;
    EntitiesRenderer* r;
#ifdef VERSION_PC
    POLY_GT4 _poly;
    poly = &_poly;
    setPolyGT4(poly);
    EntitiesRenderer _r;
    r = &_r;
#else
    poly = (POLY_GT4*)SPAD(0);
    setPolyGT4(poly);
    // Put this right after that poly. The poly is different size on PSP.
    r = (EntitiesRenderer*)SP(sizeof(POLY_GT4));
#endif

    r->poly = &g_CurrentBuffer->polyGT4[g_GpuUsage.gt4];
    r->ot = g_CurrentBuffer->ot;

    for (r->index = 0, entity = &g_Entities[0]; r->index < LEN(g_Entities);
         r->index++, entity++) {
#ifdef VERSION_PSP
        if (entity->animSet == 0) {
            continue;
        }
        if (entity->animCurFrame == 0) {
            continue;
        }
        r->animSet = entity->animSet;
        r->animCurFrame = entity->animCurFrame;
#else
        if ((r->animSet = entity->animSet) == 0 |
            (r->animCurFrame = entity->animCurFrame) == 0) {
            continue;
        }
#endif
        r->eDrawFlags = entity->drawFlags;
        if (r->eDrawFlags & FLAG_BLINK && (r->index ^ g_Timer) & 1) {
            continue;
        }
        r->flipX = entity->facingLeft * 2;
        r->x = entity->posX.i.hi + g_backbufferX;
        r->y = entity->posY.i.hi + g_backbufferY;
        if (r->x < -512 || r->x > 512) {
            continue;
        }
        if (r->y < -512 || r->y > 512) {
            continue;
        }
        pose = r->animCurFrame & 0x7FFF;
        if (!pose) {
            continue;
        }
        if (r->animSet > 0) {
            animFrame = D_800A3B70[r->animSet][pose];
        } else {
            spriteBank = (s16**)g_api.o.spriteBanks;
            spriteBank = &spriteBank[r->animSet & 0x7FFF];
            spriteBank = (s16**)spriteBank[0];
            animFrame = spriteBank[pose];
        }
        r->spriteSheetIdx = *animFrame++;
        if (r->spriteSheetIdx & 0x8000) {
            plDraw = &g_PlayerDraw[entity->unk5A];
            r->flipX ^= (u16)plDraw->flipX;
            r->spriteSheetIdx &= 0x7FFF;
            if (r->animSet > 0) {
                if (r->animSet == 13) {
                    spriteData = (*g_PlOvlAluBatSpritesheet)[r->spriteSheetIdx];
                } else {
                    spriteData = ((u8**)SPRITESHEET_PTR)[r->spriteSheetIdx];
                }
            } else if ((r->animSet & 0x7FFF) == 1) {
// NOTE: Different on PSP and PS1. PS1 skips the *
#ifdef VERSION_PSP
                spriteData = (*g_api.o.unk2c)[r->spriteSheetIdx];
#else
                spriteData = g_api.o.unk2c[r->spriteSheetIdx];
#endif
            } else if ((r->animSet & 0x7FFF) == 16) {
#ifdef VERSION_PC
                spriteData = ((u8**)g_PlOvlSpritesheet)[r->spriteSheetIdx];
#else
                spriteData = ((u8**)SPRITESHEET_PTR)[r->spriteSheetIdx];
#endif
            } else {
// see above note
#ifdef VERSION_PSP
                spriteData = (*g_api.o.unk30)[r->spriteSheetIdx];
#else
                spriteData = g_api.o.unk30[r->spriteSheetIdx];
#endif
            }
            r->xPivot = animFrame[0] + spriteData[2];
            r->yPivot = animFrame[1] + spriteData[3];
            r->w = spriteData[0];
            r->h = spriteData[1];
            poly->tpage = plDraw->tpage;
            uvRight = (plDraw->rect0.x & 0x3F) * 4;
            uvTop = plDraw->rect0.y & 0xFF;
            uvLeft = uvRight + r->w;
            uvBottom = uvTop + r->h;
            if (!(r->animCurFrame & ANIM_FRAME_LOAD)) {
                plDraw->rect0.w = r->w / 4;
                plDraw->rect0.h = r->h;
                LoadImage(&plDraw->rect0, spriteData + 4);
                plDraw->rect1.x = plDraw->rect0.x + plDraw->rect0.w;
                plDraw->rect1.y = plDraw->rect0.y - 1;
                plDraw->rect1.w = 1;
                plDraw->rect1.h = plDraw->rect0.h + 4;
                ClearImage(&plDraw->rect1, 0, 0, 0);
                plDraw->rect2.x = plDraw->rect0.x - 1;
                plDraw->rect2.y = plDraw->rect0.y + plDraw->rect0.h;
                plDraw->rect2.w = plDraw->rect0.w + 2;
                plDraw->rect2.h = 4;
                ClearImage(&plDraw->rect2, 0, 0, 0);
            }
            if (r->flipX & 2) {
                polyX = r->x - r->xPivot;
            } else {
                polyX = r->x + r->xPivot;
            }
            polyY = r->y + r->yPivot;
            if (r->flipX) {
                poly->x0 = polyX - r->w + 1;
                poly->y0 = polyY;
                poly->x1 = polyX + 1;
                poly->y1 = polyY;
                poly->x2 = polyX - r->w + 1;
                poly->y2 = polyY + r->h;
                poly->x3 = polyX + 1;
                poly->y3 = polyY + r->h;
            } else {
                poly->x0 = polyX;
                poly->y0 = polyY;
                poly->x1 = polyX + r->w;
                poly->y1 = polyY;
                poly->x2 = polyX;
                poly->y2 = polyY + r->h;
                poly->x3 = polyX + r->w;
                poly->y3 = polyY + r->h;
            }
            if (r->flipX) {
                poly->u0 = uvLeft - 1;
                poly->v0 = uvTop;
                poly->u1 = uvRight - 1;
                poly->v1 = uvTop;
                poly->u2 = uvLeft - 1;
                poly->v2 = uvBottom;
                poly->u3 = uvRight - 1;
                poly->v3 = uvBottom;
            } else {
                poly->u0 = uvRight;
                poly->v0 = uvTop;
                poly->u1 = uvLeft;
                poly->v1 = uvTop;
                poly->u2 = uvRight;
                poly->v2 = uvBottom;
                poly->u3 = uvLeft;
                poly->v3 = uvBottom;
            }
            func_800EB758(r->x, r->y, entity, r->eDrawFlags, poly, r->flipX);
            palette = entity->palette;
            if (palette & 0x8000) {
                poly->clut = g_ClutIds[palette & 0x7FFF];
            } else {
                poly->clut = g_ClutIds[animFrame[2] + palette];
            }
            if (entity->drawMode) {
                setSemiTrans(poly, true);
                poly->tpage +=
                    entity->drawMode & (FLAG_DRAW_UNK40 | FLAG_DRAW_UNK20);
            } else {
                setSemiTrans(poly, false);
            }
            if (plDraw->enableColorBlend) {
                poly->r0 = plDraw->r0;
                poly->g0 = plDraw->b0;
                poly->b0 = plDraw->g0;
                poly->r1 = plDraw->r1;
                poly->g1 = plDraw->b1;
                poly->b1 = plDraw->g1;
                poly->r2 = plDraw->r2;
                poly->g2 = plDraw->b2;
                poly->b2 = plDraw->g2;
                poly->r3 = plDraw->r3;
                poly->g3 = plDraw->b3;
                poly->b3 = plDraw->g3;
                setShadeTex(poly, false);
            } else {
                if (r->eDrawFlags & FLAG_DRAW_UNK8) {
                    poly->r0 = poly->g0 = poly->b0 = poly->r1 = poly->g1 =
                        poly->b1 = poly->r2 = poly->g2 = poly->b2 = poly->r3 =
                            poly->g3 = poly->b3 = entity->unk6C;
                    if (r->eDrawFlags & FLAG_DRAW_UNK10) {
                        poly->r0 = poly->r1 = poly->r2 = poly->r3 = 0x80;
                    }
                    if (r->eDrawFlags & FLAG_DRAW_UNK20) {
                        poly->g0 = poly->g1 = poly->g2 = poly->g3 = 0x80;
                    }
                    if (r->eDrawFlags & FLAG_DRAW_UNK40) {
                        poly->b0 = poly->b1 = poly->b2 = poly->b3 = 0x80;
                    }
                    setShadeTex(poly, false);
                } else {
                    setShadeTex(poly, true);
                }
            }
            *r->poly = *poly;
            addPrim(&r->ot[entity->zPriority], r->poly);
            r->poly++;
            g_GpuUsage.gt4++;
        } else {
            for (r->index2 = 0; r->index2 < r->spriteSheetIdx; r->index2++,
                animFrame += 11) {
                if (g_GpuUsage.gt4 >= 0x300) {
                    break;
                }
                animFrameFlags = animFrame[0];
                poly->tpage = animFrame[6];
                poly->tpage += entity->unk5A;
                r->unk0 = poly->tpage & 3;
                poly->tpage >>= 2;
                r->xPivot = animFrame[1];
                r->yPivot = animFrame[2];
                r->w = animFrame[3];
                r->h = animFrame[4];
                if (animFrameFlags & 4) {
                    r->w--;
                    if (animFrameFlags & 2) {
                        r->xPivot++;
                    }
                }
                if (animFrameFlags & 8) {
                    r->h--;
                    if (animFrameFlags & 1) {
                        r->yPivot++;
                    }
                }
                if (animFrameFlags & 0x10) {
                    r->w--;
                    if (!(animFrameFlags & 2)) {
                        r->xPivot++;
                    }
                }
                if (animFrameFlags & 0x20) {
                    r->h--;
                    if (!(animFrameFlags & 1)) {
                        r->yPivot++;
                    }
                }
                if (entity->facingLeft) {
                    polyX = r->x - r->xPivot;
                } else {
                    polyX = r->x + r->xPivot;
                }
                polyY = r->y + r->yPivot;
                if (r->flipX != 0) {
                    poly->x0 = polyX - r->w + 1;
                    poly->y0 = polyY;
                    poly->x1 = polyX + 1;
                    poly->y1 = polyY;
                    poly->x2 = polyX - r->w + 1;
                    poly->y2 = polyY + r->h;
                    poly->x3 = polyX + 1;
                    poly->y3 = polyY + r->h;
                } else {
                    poly->x0 = polyX;
                    poly->y0 = polyY;
                    poly->x1 = polyX + r->w;
                    poly->y1 = polyY;
                    poly->x2 = polyX;
                    poly->y2 = polyY + r->h;
                    poly->x3 = polyX + r->w;
                    poly->y3 = polyY + r->h;
                }
                if (r->eDrawFlags &
                    (FLAG_DRAW_ROTX | FLAG_DRAW_ROTY | FLAG_DRAW_ROTZ)) {
#ifdef VERSION_PSP
                    if (!(animFrameFlags & 2)) {
                        if (entity->rotZ == 0x800) {
                            poly->x0++;
                            poly->x1++;
                            poly->x2++;
                            poly->x3++;
                        }
                    }
#endif
                    func_800EB758(
                        r->x, r->y, entity, r->eDrawFlags, poly, r->flipX);
                }
                palette = entity->palette;
                if (palette & 0x8000) {
                    poly->clut = g_ClutIds[palette & 0x7FFF];
                } else {
                    poly->clut = g_ClutIds[animFrame[5] + palette];
                }
                uvRight = animFrame[7];
                uvTop = animFrame[8];
                uvLeft = animFrame[9];
                uvBottom = animFrame[10];
                if (r->unk0 & 1) {
                    uvRight += 0x80;
                    uvLeft += 0x80;
                }
                if (r->unk0 & 2) {
                    uvTop += 0x80;
                    uvBottom += 0x80;
                }
                if (animFrameFlags & 4) {
                    uvLeft--;
                }
                if (animFrameFlags & 8) {
                    uvBottom--;
                }
                if (animFrameFlags & 0x10) {
                    uvRight++;
                }
                if (animFrameFlags & 0x20) {
                    uvTop++;
                }
                tempFlagCheck = (animFrameFlags & 2) ^ r->flipX;
                if (!tempFlagCheck) {
                    if (!(animFrameFlags & 1)) {
                        poly->u0 = uvRight;
                        poly->v0 = uvTop;
                        poly->u1 = uvLeft;
                        poly->v1 = uvTop;
                        poly->u2 = uvRight;
                        poly->v2 = uvBottom;
                        poly->u3 = uvLeft;
                        poly->v3 = uvBottom;
                    } else {
                        poly->u0 = uvRight;
                        poly->v0 = uvBottom - 1;
                        poly->u1 = uvLeft;
                        poly->v1 = uvBottom - 1;
                        poly->u2 = uvRight;
                        poly->v2 = uvTop - 1;
                        poly->u3 = uvLeft;
                        poly->v3 = uvTop - 1;
                    }
                } else if (!(animFrameFlags & 1)) {
                    poly->u0 = uvLeft - 1;
                    poly->v0 = uvTop;
                    poly->u1 = uvRight - 1;
                    poly->v1 = uvTop;
                    poly->u2 = uvLeft - 1;
                    poly->v2 = uvBottom;
                    poly->u3 = uvRight - 1;
                    poly->v3 = uvBottom;
                } else {
                    poly->u0 = uvLeft - 1;
                    poly->v0 = uvBottom - 1;
                    poly->u1 = uvRight - 1;
                    poly->v1 = uvBottom - 1;
                    poly->u2 = uvLeft - 1;
                    poly->v2 = uvTop - 1;
                    poly->u3 = uvRight - 1;
                    poly->v3 = uvTop - 1;
                }
                if (entity->drawMode) {
                    setSemiTrans(poly, true);
                    poly->tpage +=
                        entity->drawMode & (FLAG_DRAW_UNK40 | FLAG_DRAW_UNK20);
                } else {
                    setSemiTrans(poly, false);
                }
                if (r->eDrawFlags & FLAG_DRAW_UNK8) {
                    poly->r0 = poly->g0 = poly->b0 = poly->r1 = poly->g1 =
                        poly->b1 = poly->r2 = poly->g2 = poly->b2 = poly->r3 =
                            poly->g3 = poly->b3 = entity->unk6C;
                    if (r->eDrawFlags & FLAG_DRAW_UNK10) {
                        poly->r0 = poly->r1 = poly->r2 = poly->r3 = 0x80;
                    }
                    if (r->eDrawFlags & FLAG_DRAW_UNK20) {
                        poly->g0 = poly->g1 = poly->g2 = poly->g3 = 0x80;
                    }
                    if (r->eDrawFlags & FLAG_DRAW_UNK40) {
                        poly->b0 = poly->b1 = poly->b2 = poly->b3 = 0x80;
                    }
                    setShadeTex(poly, false);
                } else {
                    setShadeTex(poly, true);
                }
                *r->poly = *poly;
                polyX = entity->zPriority;
                if (animFrameFlags & 0x100) {
                    polyX += 4;
                }
                addPrim(&r->ot[polyX], r->poly);
                r->poly++;
                g_GpuUsage.gt4++;
                if (r->animSet == 0xF) {
                    if (g_GpuUsage.gt4 >= 0x300) {
                        break;
                    }

                    if (entity->facingLeft) {
                        polyX = 0x14 - PLAYER.posX.i.hi;
                    } else {
                        polyX = 0x2C - PLAYER.posX.i.hi;
                    }
                    polyY = 0x18 - PLAYER.posY.i.hi;
                    poly->x0 += polyX;
                    poly->x1 += polyX;
                    poly->x2 += polyX;
                    poly->x3 += polyX;
                    poly->y0 += polyY;
                    poly->y1 += polyY;
                    poly->y2 += polyY;
                    poly->y3 += polyY;
                    poly->clut = g_ClutIds[0x104];
                    *r->poly = *poly;
                    polyX = (entity->zPriority + 0x1A0) - PLAYER.zPriority;
                    if (animFrameFlags & 0x100) {
                        polyX += 4;
                    }
#if defined(VERSION_US)
                    setSemiTrans(poly, true);
                    poly->tpage += 0x20;
#endif
                    addPrim(&r->ot[polyX], r->poly);
                    r->poly++;
                    g_GpuUsage.gt4++;
                }
            }
        }
    }
}

#define PL_SPRT(x, y, flipx) (x), ((y) & 0x1FF) | ((flipx) << 9)
s16 D_800A21B8[] = {
    PL_SPRT(0x0201, 0x0101, false), PL_SPRT(0x0221, 0x0101, false),
    PL_SPRT(0x0231, 0x0101, false), PL_SPRT(0x0201, 0x0181, false),
    PL_SPRT(0x0201, 0x0101, false), PL_SPRT(0x0201, 0x0101, false),
    PL_SPRT(0x0201, 0x0101, false), PL_SPRT(0x0201, 0x0101, false),
    PL_SPRT(0x0001, 0x0101, false), PL_SPRT(0x0021, 0x0101, false),
    PL_SPRT(0x0001, 0x0181, false), PL_SPRT(0x0021, 0x0181, false),
    PL_SPRT(0x0221, 0x0181, false), PL_SPRT(0x0221, 0x0101, false),
    PL_SPRT(0x0221, 0x0181, false), PL_SPRT(0x0221, 0x0181, false),
    PL_SPRT(0x0101, 0x0101, false),
};

s16 unused_800A21FC[286] = {0};

void InitRenderer(void) {
    int i;
    POLY_GT4 *a1, *a2;
    SPRT_16 *b1, *b2;
    TILE *c1, *c2;
    LINE_G2 *d1, *d2;
    POLY_G4 *e1, *e2;
    SPRT *f1, *f2;
    POLY_GT3 *g1, *g2;
    PlayerDraw* plDraw;

    a1 = g_GpuBuffers[0].polyGT4;
    a2 = g_GpuBuffers[1].polyGT4;
    for (i = 0; i < 0x300; i++, a1++, a2++) {
        SetPolyGT4(a1);
        SetPolyGT4(a2);
    }

    b1 = g_GpuBuffers[0].sprite16;
    b2 = g_GpuBuffers[1].sprite16;
    for (i = 0; i < 0x280; i++, b1++, b2++) {
        SetSprt16(b1);
        SetSprt16(b2);
    }

    c1 = g_GpuBuffers[0].tiles;
    c2 = g_GpuBuffers[1].tiles;
    for (i = 0; i < 0x100; i++, c1++, c2++) {
        SetTile(c1);
        SetTile(c2);
    }

    d1 = g_GpuBuffers[0].lineG2;
    d2 = g_GpuBuffers[1].lineG2;
    for (i = 0; i < 0x100; i++, d1++, d2++) {
        SetLineG2(d1);
        SetLineG2(d2);
    }

    e1 = g_GpuBuffers[0].polyG4;
    e2 = g_GpuBuffers[1].polyG4;
    for (i = 0; i < 0x100; i++, e1++, e2++) {
        SetPolyG4(e1);
        SetPolyG4(e2);
    }

    f1 = g_GpuBuffers[0].sprite;
    f2 = g_GpuBuffers[1].sprite;
    for (i = 0; i < 0x200; i++, f1++, f2++) {
        SetSprt(f1);
        SetSprt(f2);
    }

    g1 = g_GpuBuffers[0].polyGT3;
    g2 = g_GpuBuffers[1].polyGT3;
    for (i = 0; i < 0x30; i++, g1++, g2++) {
        SetPolyGT3(g1);
        SetPolyGT3(g2);
    }

    for (plDraw = g_PlayerDraw, i = 0; i < 16; i++, plDraw++) {
        plDraw->rect0.x = D_800A21B8[i * 2 + 0];
        plDraw->rect0.y = D_800A21B8[i * 2 + 1] & 0x1FF;
        plDraw->flipX = (D_800A21B8[i * 2 + 1] >> 8) & 0xFE;
        plDraw->tpage = (plDraw->rect0.x >> 6) + 0x10;
    }
}
