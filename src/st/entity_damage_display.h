extern u16 g_eDamageDisplayInit[]; // D_801804A0
extern u16 g_eDamageDisplayClut[]; // D_80180A6C

typedef struct NumericPrim {
    /* 0x00 */ struct NumericPrim* next;
#if defined(VERSION_PC) || defined(VERSION_PSP)
    u_long dummy;
#endif
    /* 0x04 */ u8 r0;
    /* 0x05 */ u8 g0;
    /* 0x06 */ u8 b0;
    /* 0x07 */ u8 type; // PrimitiveType
    /* 0x08 */ s16 x0;
    /* 0x0A */ s16 y0;
    /* 0x0C */ u8 u0;
    /* 0x0D */ u8 v0;
    /* 0x0E */ u16 clut;
    /* 0x10 */ s16 _xOffset;
    /* 0x12 */ s16 _yOffset;
    /* 0x14 */ s16 x1;
    /* 0x16 */ s16 y1;
    /* 0x18 */ u8 u1;
    /* 0x19 */ u8 v1;
    /* 0x1A */ u16 tpage;
    /* 0x1C */ u16 _width;
    /* 0x1E */ u16 _height;
    /* 0x20 */ s16 x2;
    /* 0x22 */ s16 y2;
    /* 0x24 */ u8 u2;
    /* 0x25 */ u8 v2;
    /* 0x26 */ u16 priority;
    /* 0x28 */ u32 unused28;
    /* 0x2C */ s16 x3;
    /* 0x2E */ s16 y3;
    /* 0x30 */ u8 u3;
    /* 0x31 */ u8 v3;
    /* 0x32 */ u16 drawMode;
} NumericPrim; /* size=0x34 */

// -    NumericPrim* prim;
// -    s16 x;
// -    s16 y;
// -    u8 singleDigit;
// -    u16 iDigit;
// -    u16 params;
// -    u16 clut;
// -    u16* nDigits;
// -    s16 xOffset;
// -    s32 primIndex;
// -    u16 primInitStep;
// +    Primitive* prim;
// +    s16 x;
// +    u8 singleDigit;
// +    s16 y;
// +    u16 iDigit;
// +    u16 params;
// +    u16 clut;
// +    u16* nDigits;
// +    s32 primIndex;
// +    u16 primInitStep;
// +    s16 xOffset;

void EntityDamageDisplay(Entity* self) {
    Primitive* prim;
    s16 x;
    u8 singleDigit;
    s16 y;
    u16 iDigit;
    u16 params;
    u16 clut;
    u16* nDigits;
    s32 primIndex;
    u16 primInitStep;
    s16 xOffset;

    if (self->ext.ndmg.unk88) {
        self->posX.val = g_Entities->posX.val;
        self->posY.val = PLAYER.posY.val + -FIX(16.0);
    }

    switch (self->step) {
    case 0:
        if (self->step_s == 9) {
            DestroyEntity(self);
            return;
        }
        params = self->params;
        nDigits = &self->ext.ndmg.nDigits;
        if (!self->step_s) {
            InitializeEntity(g_eDamageDisplayInit);
            self->step = 0;
            if (params == 0xC000) {
                self->ext.ndmg.nPrims++;
            } else {
                clut = params & 0x3FFF;

                // thousands
                iDigit = clut / 1000;
                if (iDigit) {
                    self->ext.ndmg.nPrims++;
                    (*nDigits)++;
                }
                self->ext.ndmg.digits[0] = iDigit;

                // hundreds
                clut -= iDigit * 1000;
                iDigit = clut / 100;
                if (iDigit || *nDigits) {
                    self->ext.ndmg.nPrims++;
                    (*nDigits)++;
                }
                self->ext.ndmg.digits[1] = iDigit;

                // tens
                clut -= iDigit * 100;
                iDigit = clut / 10;
                if (iDigit || *nDigits) {
                    self->ext.ndmg.nPrims++;
                    (*nDigits)++;
                }
                self->ext.ndmg.digits[2] = iDigit;

                // units
                clut -= iDigit * 10;
                self->ext.ndmg.nPrims++;
                (*nDigits)++;
                self->ext.ndmg.digits[3] = clut;

                if (params & 0x4000) {
                    self->ext.ndmg.nPrims++;
                }
            }
        }

        primIndex = g_api.AllocPrimitives(PRIM_GT4, self->ext.ndmg.nPrims);
        if (primIndex) {
            self->primIndex = primIndex;
            self->flags |= FLAG_HAS_PRIMS;
            prim = &g_PrimBuf[primIndex];

            primInitStep = 0;
            iDigit = 4 - *nDigits;
#if defined(VERSION_PSP)
            xOffset = -(*nDigits) * 2;
#else
            xOffset = *nDigits * -2;
#endif
            while (prim != NULL) {
                if (!primInitStep) {
                    primInitStep++;
                    if ((params & 0xC000) == 0xC000) {
                        prim->u0 = prim->u2 = 0x43;
                        prim->u1 = prim->u3 = 0x59;
                        prim->v0 = prim->v1 = 0x4A;
                        prim->v2 = prim->v3 = 0x52;
                        LOH(prim->r2) = 0xB;
                        LOH(prim->b2) = 5;
                        LOH(prim->r1) = 0;
                        LOH(prim->b1) = -0x10;
                    } else if (params & 0x4000) {
                        prim->u0 = prim->u2 = 0x20;
                        prim->u1 = prim->u3 = 0x42;
                        prim->v0 = prim->v1 = 0x4A;
                        prim->v2 = prim->v3 = 0x52;
                        LOH(prim->r2) = 0x11;
                        LOH(prim->b2) = 5;
                        LOH(prim->r1) = 0;
                        LOH(prim->b1) = -0x18;
                    } else {
                        continue;
                    }
                } else {
                    LOH(prim->r1) = xOffset;
                    LOH(prim->b1) = -0x10;
                    if (params & 0x4000) {
                        LOH(prim->r2) = 3;
                        LOH(prim->b2) = 5;
                    } else {
                        LOH(prim->r2) = 0x17;
                        LOH(prim->b2) = 0;
                    }

                    singleDigit = self->ext.ndmg.digits[iDigit];
                    if (singleDigit) {
                        singleDigit = singleDigit * 8 + 0x18;
                        prim->u0 = prim->u2 = singleDigit;
                        prim->u1 = prim->u3 = singleDigit + 6;
                    } else {
                        prim->u0 = prim->u2 = 0x68;
                        prim->u1 = prim->u3 = 0x6E;
                    }
                    prim->v0 = prim->v1 = 0x40;
                    prim->v2 = prim->v3 = 0x49;
                    xOffset += 4;
                    iDigit++;
                }
                prim->tpage = 0x1A;
                prim->priority = 0x1F8;
                prim->blendMode = 8;
                prim = prim->next;
            }
            self->step++;
            self->step_s = 0;
            self->ext.ndmg.timer = 64;
        }
        self->step_s++;
        break;
    case 1:
        params = --self->ext.ndmg.timer;
        if (!params) {
            DestroyEntity(self);
            return;
        }

        params &= 1;
        iDigit = (self->params >> 13) & 6;
        params |= iDigit;
        clut = g_eDamageDisplayClut[params];
        prim = &g_PrimBuf[self->primIndex];
        if (iDigit && iDigit != 4) {
            while (prim != NULL) {
                if (self->ext.ndmg.timer >= 60) {
                    LOHU(prim->r2)++;
                    LOHU(prim->b2)++;
                } else if (self->ext.ndmg.timer >= 56) {
                    LOHU(prim->r2)--;
                    LOHU(prim->b2)--;
                }
                x = self->posX.i.hi + LOH(prim->r1);
                y = self->posY.i.hi + LOH(prim->b1);
                prim->x0 = prim->x2 = x - LOHU(prim->r2);
                prim->x1 = prim->x3 = x + LOHU(prim->r2);
                prim->y0 = prim->y1 = y - LOHU(prim->b2);
                prim->y2 = prim->y3 = y + LOHU(prim->b2);
                prim->clut = clut;
                if (self->ext.ndmg.timer < 6) {
                    prim->blendMode = 0x13;
                } else {
                    prim->blendMode = 0x02;
                }
                prim = prim->next;
            }
            if (self->ext.ndmg.unk88 != 0) {
                return;
            }
            self->posY.val -= FIX(0.5);
        } else {
            while (prim != NULL) {
                if (LOHU(prim->r2) > 3) {
                    LOHU(prim->r2)--;
                }
                if (LOHU(prim->b2) < 10) {
                    LOHU(prim->b2)++;
                }

                x = self->posX.i.hi + LOH(prim->r1);
                y = self->posY.i.hi + LOH(prim->b1) + 5 -
                    (LOHU(prim->b2));
                prim->x0 = x - LOHU(prim->r2);
                prim->x1 = x + LOHU(prim->r2);
                prim->x2 = x - 3;
                prim->x3 = x + 3;
                prim->y0 = prim->y1 = y;
                prim->y2 = prim->y3 = y + LOHU(prim->b2);
                prim->clut = clut;

                if (self->ext.ndmg.timer < 6) {
                    prim->blendMode = 0x13;
                } else {
                    prim->blendMode = 0x02;
                }
                prim = prim->next;
            }
            self->posY.val -= FIX(0.5);
        }
        break;
    }
}
