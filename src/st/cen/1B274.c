#include "cen.h"

// The white flying orbs of energy that Alucard summons as part of the Soul
// Steal spell
void EntitySoulStealOrb(Entity* self) {
    Primitive* prim;
    s32 primIndex;
    u16 *temp_d, temp_e;
    s32 temp_a, temp_b;
    u16 angle;

    switch (self->step) {
    case 0:
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        InitializeEntity(g_InitializeData0);
        g_PrimBuf[primIndex].blendMode = BLEND_VISIBLE;
        self->primIndex = primIndex;
        self->animSet = ANIMSET_DRA(0);
        self->flags |= FLAG_HAS_PRIMS;
        angle = func_80194DC4(self, &PLAYER);
        temp_a = self->posY.i.hi < 113;
        temp_b = temp_a ^ 1;
        if (self->posX.i.hi < PLAYER.posX.i.hi) {
            temp_b = temp_a;
        }
        if (temp_b & 0xFFFF) {
            self->ext.soulStealOrb.angle = angle - D_801811C8[Random() & 7];
        } else {
            angle += D_801811C8[Random() & 7];
            self->ext.soulStealOrb.angle = angle;
        }
        self->ext.soulStealOrb.unk80 = 0x400;
        self->ext.soulStealOrb.unk7E = 0;
        self->hitboxState = 0;
        break;

    case 1:
        self->ext.soulStealOrb.unk82++;
        if (self->ext.soulStealOrb.unk82 == 16) {
            self->hitboxState = 1;
        }
        if (self->hitFlags != 0) {
            if (g_Player.unk56 == 0) {
                g_Player.unk56 = 1;
                g_Player.unk58 = 8;
            }
            DestroyEntity(self);
            return;
        }
        if (self->rotX < 0x100) {
            self->rotX = self->rotY += 0x10;
        }
        if (self->ext.soulStealOrb.unk7E < 0x200) {
            self->ext.soulStealOrb.unk7E += 2;
        }
        if (self->ext.soulStealOrb.unk80 < 0x800) {
            self->ext.soulStealOrb.unk80 += 4;
        }
        self->ext.soulStealOrb.angle = func_80194E44(
            self->ext.soulStealOrb.unk7E, self->ext.soulStealOrb.angle,
            func_80194DC4(self, &PLAYER));
        UnkEntityFunc0(self->ext.soulStealOrb.angle & 0xFFFF,
                       self->ext.soulStealOrb.unk80);
        MoveEntity(self); // argument pass necessary to match
        prim = &g_PrimBuf[self->primIndex];
        func_80194394(&D_80181238, self);
        angle = (float)(u32)self; // !FAKE
        prim->tpage = 0x18;
        prim->clut = 0x194;
        temp_d = &D_801811D8[(u16)((8 * (u16)self->animCurFrame) - 8)];
        prim->x0 = prim->x2 = self->posX.i.hi + *(temp_d++);
        prim->y0 = prim->y1 = self->posY.i.hi + *(temp_d++);
        prim->x1 = prim->x3 = prim->x0 + *(temp_d++);
        prim->y2 = prim->y3 = prim->y0 + *(temp_d++);
        prim->u0 = prim->u2 = *(temp_d++);
        prim->v0 = prim->v1 = *(temp_d++);
        prim->u1 = prim->u3 = *(temp_d++);
        prim->v2 = prim->v3 = *(temp_d++);
        prim->priority = self->zPriority;
        prim->blendMode = 0;
        break;
    }
}

#include "../entity_enemy_blood.h"

void EntityUnkId08(Entity* entity) {
    ObjInit2* objInit = &D_8018125C[entity->params];

    if (entity->step == 0) {
        InitializeEntity(D_80180458);
        entity->animSet = objInit->animSet;
        entity->zPriority = objInit->zPriority;
        entity->unk5A = objInit->unk4.s;
        entity->palette = objInit->palette;
        entity->drawFlags = objInit->drawFlags;
        entity->blendMode = objInit->blendMode;
        if (objInit->unkC != 0) {
            entity->flags = objInit->unkC;
        }
        if (entity->params >= 5) {
            entity->rotZ = 0x800;
            entity->drawFlags = (u8)(entity->drawFlags | FLAG_DRAW_ROTZ);
        }
    }
    func_80194394(objInit->unk10, entity);
}

void BottomCornerText(u8* str, u8 lower_left) {
    u8 toPrint[64];
    Primitive* prim;
    s32 i;
    u32 ch;
    u8* chIdx = &toPrint;

    u16 textWidth = 0;
    // serves two purposes, use #define for dual names
    u16 dualVar = 0;
#define charcount dualVar

    // Clear out the toPrint array
    for (i = 0; i < 64; i++) {
        *chIdx++ = 0;
    }
    // Reset array pointer
    chIdx = &toPrint;

    while (1) {
        i = 0;
        // Copy values from the incoming arg0 array to the local array, until we
        // get a 0xFF followed by a 0
        ch = *str++;
        if (ch == 0xFF) {
            ch = *str++;
            if (ch == 0) {
                break;
            }
        }
        *chIdx = ch;
        chIdx++;
        if (ch != 0) {
            charcount += 1;
            textWidth += 8;
        } else {
            textWidth += 4;
        }
    }

    g_BottomCornerTextPrims = g_api_AllocPrimitives(PRIM_SPRT, charcount + 4);
    if (g_BottomCornerTextPrims == -1) {
        return;
    }
#undef charcount

    prim = &g_PrimBuf[g_BottomCornerTextPrims];
    prim->type = 3;
    prim->b0 = prim->b1 = prim->b2 = prim->b3 = prim->g0 = prim->g1 = prim->g2 =
        prim->g3 = prim->r0 = prim->r1 = prim->r2 = prim->r3 = 0;

    if (lower_left) {
        prim->b0 = prim->b1 = 0xAF;
    } else {
        prim->g0 = prim->g1 = 0x5F;
    }

#define xpos dualVar
    if (lower_left) {
        xpos = 7;
        textWidth += 4;
    } else {
        xpos = 0xD4 - textWidth;
    }

    prim->x0 = prim->x2 = xpos;
    prim->x1 = prim->x3 = xpos + textWidth + 0x20;
    prim->y0 = prim->y1 = 0xD0;
    prim->y2 = prim->y3 = 0xDF;
    prim->priority = 0x1EE;
    prim->blendMode = 0x11;
    prim = prim->next;

    prim->tpage = 0x1F;
    prim->clut = 0x197;
    prim->x0 = xpos - 6;
    prim->y0 = 0xCB;
    prim->u0 = 0x80;
    prim->v0 = 0;
    prim->u1 = 0x10;
    prim->v1 = 0x18;
    prim->priority = 0x1EF;
    prim->blendMode = 0;
    prim = prim->next;

    prim->tpage = 0x1F;
    prim->clut = 0x197;
    prim->x0 = xpos + textWidth + 0x16;
    prim->y0 = 0xCB;
    prim->u0 = 0xA8;
    prim->v0 = 0;
    prim->u1 = 0x10;
    prim->v1 = 0x18;
    prim->priority = 0x1EF;
    prim->blendMode = 0;
    prim = prim->next;

    prim->type = 4;
    prim->y0 = prim->y1 = 0xCD;
    prim->tpage = 0x1F;
    prim->clut = 0x197;
    prim->y2 = prim->y3 = 0xE1;
    prim->u0 = prim->u2 = 0x98;
    prim->u1 = prim->u3 = 0x9C;
    prim->v0 = prim->v1 = 2;
    prim->x0 = prim->x2 = xpos + 0xA;
    prim->x1 = prim->x3 = xpos + textWidth + 0x18;
    prim->v2 = prim->v3 = 0x16;
    prim->priority = 0x1EF;
    prim->blendMode = 0;

    xpos += 0x10;

    // Reset array pointer
    chIdx = &toPrint;
    for (prim = prim->next; prim != NULL;) {
        ch = *chIdx++;
        if (ch != 0) {
            prim->x0 = xpos;
            prim->u0 = (ch & 0xF) * 8;
            prim->tpage = 0x1E;
            prim->clut = 0x196;
            prim->v0 = (ch & 0xF0) >> 1;
            prim->v1 = 8;
            prim->u1 = 8;
            prim->priority = 0x1F0;
            prim->blendMode = 0;
            prim->y0 = 0xD4;
            prim = prim->next;
            xpos += 8;
        } else {
            xpos += 4;
        }
    }
#undef xpos
    g_BottomCornerTextTimer = 0x130;
}

void func_8019BED4(Primitive* arg0) {
    SVECTOR sp10; //FAKE, not really an svector
    SVECTOR stackpad;
    SVECTOR sp20;
    VECTOR sp28;
    SVECTOR sp38;
    SVECTOR sp40;
    SVECTOR sp48;
    SVECTOR sp50;
    MATRIX sp58;
    SVECTOR sp78;
    u16 temp_a0;
    u8 temp_v1_2;

    sp78 = D_8018D5F8;
    if (arg0->p3 & 8) {
        // Fake logic here, sp10 is not an SVECTOR but it matches.
        // tried using an f32 but couldn't get it to work.
        sp10.vy = arg0->next->x1;
        sp10.vx = arg0->next->y1;
        LOW(sp10.vx) += LOW(arg0->next->u0);
        arg0->next->x1 = sp10.vy;
        arg0->next->y1 = sp10.vx;
        LOW(arg0->next->x0) += LOW(arg0->next->r1);
    }
    temp_v1_2 = arg0->next->b3;
    LOH(arg0->r0) = LOH(arg0->r1) = LOH(arg0->r2) = LOH(arg0->r3) = temp_v1_2 | (temp_v1_2 << 8);
    arg0->b0 = arg0->b1 = arg0->b2 = arg0->b3 = temp_v1_2;
    sp28.vx = 0;
    sp28.vy = 0;
    sp28.vz = 0x400 - LOH(arg0->next->u1);
    RotMatrix(&sp78, &sp58);
    if (arg0->p3 & 0x20) {
        sp20.vx = arg0->next->x3;
        sp20.vy = arg0->next->y3;
        RotMatrixX(sp20.vx, &sp58);
        RotMatrixY(sp20.vy, &sp58);
    }
    sp20.vz = arg0->next->tpage;
    RotMatrixZ(sp20.vz, &sp58);
    TransMatrix(&sp58, &sp28);
    if (arg0->p3 & 0x10) {
        sp28.vx = (s32) arg0->next->x2;
        sp28.vy = (s32) arg0->next->y2;
        sp28.vz = 0x1000;
        ScaleMatrix(&sp58, &sp28.vx);
    }
    SetRotMatrix(&sp58);
    SetTransMatrix(&sp58);
    SetGeomScreen(0x400);
    SetGeomOffset(arg0->next->x1, arg0->next->y0);
    sp38.vx = -LOH(arg0->next->r2) / 2;
    sp38.vy = -LOH(arg0->next->b2) / 2;
    sp38.vz = 0;
    sp40.vx = LOH(arg0->next->r2) / 2;
    sp40.vy = -LOH(arg0->next->b2) / 2;
    sp40.vz = 0;
    sp48.vx = -LOH(arg0->next->r2) / 2;
    sp48.vy = LOH(arg0->next->b2) / 2;
    sp48.vz = 0;
    sp50.vx = LOH(arg0->next->r2) / 2;
    sp50.vy = LOH(arg0->next->b2) / 2;
    sp50.vz = 0;
    gte_ldv0(&sp38);
    gte_rtps();
    gte_stsxy(&arg0->x0); 
    gte_ldv0(&sp40);
    gte_rtps();
    gte_stsxy(&arg0->x1);
    gte_ldv0(&sp48);
    gte_rtps();
    gte_stsxy(&arg0->x2);
    gte_ldv0(&sp50);
    gte_rtps();
    gte_stsxy(&arg0->x3);
}

INCLUDE_ASM("asm/us/st/cen/nonmatchings/1B274", func_8019C2BC);

POLY_GT4* func_8019C40C(POLY_GT4* poly) {
    while (poly != NULL) {
        if (poly->p3 != 0) {
            poly = (POLY_GT4*)poly->tag;
        } else {
            return poly;
        }
    }
    return NULL;
}

POLY_GT4* func_8019C43C(POLY_GT4* poly, u8 index) {
    if (poly) {
        s32 index_ = index;
    loop_2:
        if (poly->p3 == 0) {
            POLY_GT4* var_v0 = NULL;
            POLY_GT4* firstPoly = poly;
            s32 i = 1;
            if (i < index_) {
                do {
                    poly = (POLY_GT4*)poly->tag;
                    if (!poly)
                        return NULL;
                } while (poly->p3 == 0 && ++i < index);
            }
            var_v0 = firstPoly;
            if (i == index_)
                return var_v0;
        }
        poly = (POLY_GT4*)poly->tag;
        if (poly) {
            goto loop_2;
        }
    }
    return NULL;
}

Primitive* func_8019C4B8(Primitive* prim, s32 count) {
    s32 i;
    u8 p3;

    if (prim->p3 != 0) {
        prim->p3 = 0;
    } else {
        prim->p3 = 1;
    }

    for (i = 0; i < count; i++) {
        if (prim->p3 != 0) {
            prim->blendMode &= ~8;
            p3 = 0;
        } else {
            prim->blendMode |= 8;
            p3 = 1;
        }

        prim = prim->next;

        if (prim == NULL) {
            return NULL;
        }
        prim->p3 = p3;
    }
    return prim;
}

void func_8019C540(POLY_GT4* poly) {
    poly->p1 = 0;
    poly->p2 = 0;
    poly->p3 = 0;
    ((POLY_GT4*)poly->tag)->x1 = 0;
    ((POLY_GT4*)poly->tag)->y1 = 0;
    ((POLY_GT4*)poly->tag)->y0 = 0;
    ((POLY_GT4*)poly->tag)->x0 = 0;
    ((POLY_GT4*)poly->tag)->clut = 0;
    *(u16*)&((POLY_GT4*)poly->tag)->u0 = 0;
    *(u16*)&((POLY_GT4*)poly->tag)->b1 = 0;
    *(u16*)&((POLY_GT4*)poly->tag)->r1 = 0;
    *(u16*)&((POLY_GT4*)poly->tag)->u1 = 0;
    ((POLY_GT4*)poly->tag)->tpage = 0;
    *(u16*)&((POLY_GT4*)poly->tag)->r2 = 0;
    *(u16*)&((POLY_GT4*)poly->tag)->b2 = 0;
    ((POLY_GT4*)poly->tag)->u2 = 0;
    ((POLY_GT4*)poly->tag)->v2 = 0;
    ((POLY_GT4*)poly->tag)->r3 = 0;
    ((POLY_GT4*)poly->tag)->b3 = 0;
    ((POLY_GT4*)poly->tag)->x2 = 0;
    ((POLY_GT4*)poly->tag)->y2 = 0;
}

void func_8019C620(POLY_GT4* poly) {
    func_8019C540(poly);
    poly->p3 = 8;
    ((POLY_GT4*)poly->tag)->p3 = 1;
    ((POLY_GT4*)poly->tag)->code = 2;
    ((POLY_GT4*)poly->tag)->pad3 = 0xA;
}

#include "../unk_poly_func_0.h"

#include "../unk_loop_func.h"
