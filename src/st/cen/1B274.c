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
        InitializeEntity(D_80180410);
        D_8008701E[primIndex * 0x1a] = 8;
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
        if (self->unk1A < 0x100) {
            self->unk1A = self->unk1C += 0x10;
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
        func_80194D08(self->ext.soulStealOrb.angle & 0xFFFF,
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

void EntityEnemyBlood(Entity* self) {
    int fakeTemp; // !TODO: !FAKE
    Primitive* prim;
    s32 var_a0_2;
    u16 params;
    s16 posX;
    s32 rnd;
    s32 i;

    switch (self->step) {
    case 0:
        i = g_api.func_800EDB58(17, 12);
        if (i != -1) {
            InitializeEntity(D_80180410);
            prim = &g_PrimBuf[i];
            self->primIndex = i;
            self->animSet = ANIMSET_DRA(0);
            params = self->params;
            self->hitboxState = 1;
            self->ext.generic.unk7C.s = 48;
            self->hitboxHeight = 8;
            self->zPriority = 0xC0;
            self->hitboxWidth = 0;
            self->flags |= FLAG_HAS_PRIMS;

            for (i = 12; i != 0;) {
                prim->x0 = self->posX.i.hi + ((Random() & (fakeTemp = 7)) - 5);
                rnd = (Random() & 7) - 5;
                prim->y0 = self->posY.i.hi + rnd;
                *(s32*)&prim->r1 = 0;
                *(s32*)&prim->x1 = 0;
                prim->u0 = 4;
                prim->v0 = 4;

                if (params != 0) {
                    func_80194D08(
                        0xCC0 + i * 64, ((Random() & 0xF) * 0x10) + 0x180);
                } else {
                    func_80194D08(
                        0xB40 - i * 64, ((Random() & 0xF) * 0x10) + 0x180);
                }

                *(s32*)&prim->u1 = self->velocityX;
                *(s32*)&prim->r2 = self->velocityY;

                var_a0_2 = *(s32*)&prim->u1;
                if (var_a0_2 <= -1) {
                    var_a0_2 += 0x3F;
                }

                *(s32*)&prim->r3 = -(var_a0_2 >> 6);
                *(s32*)&prim->x3 = -(*(s32*)&prim->r2 / 48) + 0xC00;

                prim->x2 = prim->y2 = (Random() & 7) + 7;
                prim->r0 = 128;
                prim->b0 = 16;
                prim->g0 = 0;
                prim->priority = self->zPriority;
                prim->blendMode = 2;
                i--;
                if (i != 0) {
                    prim++;
                }
            }

            if (params != 0) {
                self->velocityX = FIX(1.25);
                self->ext.generic.unk80.modeS32 = -0x200;
            } else {
                self->velocityX = FIX(-1.25);
                self->ext.generic.unk80.modeS32 = 0x200;
            }
            self->velocityY = 0;
            break;
        }
        DestroyEntity(self);
        break;

    case 1:
        if (!(--self->ext.generic.unk7C.u)) {
            DestroyEntity(self);
            break;
        }

        if (self->hitboxState != 0) {
            if (g_Player.unk0C & 0x02000000) {
                posX = self->posX.i.hi;
                self->velocityX += self->ext.generic.unk80.modeS32;

                MoveEntity(self); // argument pass necessary to match

                posX -= self->posX.i.hi;
                if (posX < 0) {
                    posX = -posX;
                }

                if (self->ext.generic.unk7C.u > 16) {
                    self->ext.generic.unk7E.modeU16 += posX;
                    self->hitboxWidth = self->ext.generic.unk7E.modeU16 / 2;
                    self->hitboxHeight =
                        (self->ext.generic.unk7E.modeU16 / 4) + 8;
                } else {
                    self->hitboxState = 0;
                }

                if (self->hitFlags != 0) {
                    if (g_Player.unk56 == 0) {
                        g_Player.unk56 = 1;
                        g_Player.unk58 = 8;
                        if (g_api.CheckEquipmentItemCount(0x3C, 4)) {
                            g_Player.unk58 *= 2;
                        }
                    }
                    g_Player.unk10++;
                    self->hitboxState = 0;
                }
            } else {
                self->hitboxState = 0;
            }
        }

        prim = &g_PrimBuf[self->primIndex];
        for (i = 12; i != 0; i--, prim++) {
            *(u16*)&prim->b1 = prim->x0;
            prim->y1 = prim->y0;
            *(s32*)&prim->u1 += *(s32*)&prim->r3;
            *(s32*)&prim->r2 += *(s32*)&prim->x3;
            *(s32*)&prim->r1 += *(s32*)&prim->u1;
            *(s32*)&prim->x1 += *(s32*)&prim->r2;
            *(s16*)&prim->x0 = *(s16*)&prim->b1;
            prim->y0 = prim->y1;
            prim->x2--;

            if ((prim->x2 == 0) && (prim->u0 != 0)) {
                prim->v0--;
                prim->u0--;
                if (!(prim->u0 & 1)) {
                    prim->x0++;
                    prim->y0++;
                }
                prim->x2 = *(s32*)&prim->y2;
            }
        }
    }
}

void EntityUnkId08(Entity* entity) {
    ObjInit2* objInit = &D_8018125C[entity->params];

    if (entity->step == 0) {
        InitializeEntity(D_80180458);
        entity->animSet = objInit->animSet;
        entity->zPriority = objInit->zPriority;
        entity->unk5A = objInit->unk4.s;
        entity->palette = objInit->palette;
        entity->unk19 = objInit->unk8;
        entity->blendMode = objInit->blendMode;
        if (objInit->unkC != 0) {
            entity->flags = objInit->unkC;
        }
        if (entity->params >= 5) {
            entity->rotAngle = 0x800;
            entity->unk19 = (u8)(entity->unk19 | 4);
        }
    }
    func_80194394(objInit->unk10, entity);
}

INCLUDE_ASM("asm/us/st/cen/nonmatchings/1B274", func_8019BBA4);

INCLUDE_ASM("asm/us/st/cen/nonmatchings/1B274", func_8019BED4);

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

void func_8019C674(POLY_GT4* poly) {
    poly->p3 = 0;
    poly->pad3 = 8;
    ((POLY_GT4*)poly->tag)->p3 = 0;
    ((POLY_GT4*)poly->tag)->code = 4;
    ((POLY_GT4*)poly->tag)->pad3 = 8;
}

s32 func_8019C6A0(s32 arg0, u8 arg1) {
    s32 var_v0;
    s32 ret = 0;
    u8* var_a0 = arg0 + 4;
    u8* var_v1;
    s32 i;

    for (i = 0; i < 4; i++) {
        var_v1 = var_a0;
        do {
            var_v0 = *var_v1 - arg1;

            if (var_v0 < 0) {
                var_v0 = 0;
            } else {
                ret |= 1;
            }

            *var_v1 = var_v0;
            var_v1++;
        } while (((s32)var_v1 < ((s32)var_a0 + 3)));

        var_a0 += 0xC;
    }

    return ret;
}