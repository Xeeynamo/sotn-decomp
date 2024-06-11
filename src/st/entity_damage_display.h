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
// +    Primitive* s0_prim;
// +    s16 x;
// +    u8 var_s3;
// +    s16 y;
// +    u16 iDigit;
// +    u16 params;
// +    u16 clut;
// +    u16* nDigits;
// +    s32 primIndex;
// +    u16 sp3e;
// +    s16 var_s8;

void EntityDamageDisplay(Entity* self) {
    Primitive* s0_prim;
    s16 x;
    u8 var_s3;
    s16 y;
    u16 iDigit;
    u16 params;
    u16 clut;
    u16* nDigits;
    s32 primIndex;
    u16 sp3e;
    s16 var_s8;

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
            s0_prim = &g_PrimBuf[primIndex];

            sp3e = 0;
            iDigit = 4 - *nDigits;
#if defined(VERSION_PSP)
            var_s8 = -(*nDigits) * 2;
#else
            var_s8 = *nDigits * -2;
#endif
            while (s0_prim != NULL) {
                if (!sp3e) {
                    sp3e++;
                    if ((params & 0xC000) == 0xC000) {
                        s0_prim->u0 = s0_prim->u2 = 0x43;
                        s0_prim->u1 = s0_prim->u3 = 0x59;
                        s0_prim->v0 = s0_prim->v1 = 0x4A;
                        s0_prim->v2 = s0_prim->v3 = 0x52;
                        LOH(s0_prim->r2) = 0xB;
                        LOH(s0_prim->b2) = 5;
                        LOH(s0_prim->r1) = 0;
                        LOH(s0_prim->b1) = -0x10;
                    } else if (params & 0x4000) {
                        s0_prim->u0 = s0_prim->u2 = 0x20;
                        s0_prim->u1 = s0_prim->u3 = 0x42;
                        s0_prim->v0 = s0_prim->v1 = 0x4A;
                        s0_prim->v2 = s0_prim->v3 = 0x52;
                        LOH(s0_prim->r2) = 0x11;
                        LOH(s0_prim->b2) = 5;
                        LOH(s0_prim->r1) = 0;
                        LOH(s0_prim->b1) = -0x18;
                    } else {
                        continue;
                    }
                } else {
                    LOH(s0_prim->r1) = var_s8;
                    LOH(s0_prim->b1) = -0x10;
                    if (params & 0x4000) {
                        LOH(s0_prim->r2) = 3;
                        LOH(s0_prim->b2) = 5;
                    } else {
                        LOH(s0_prim->r2) = 0x17;
                        LOH(s0_prim->b2) = 0;
                    }

                    var_s3 = self->ext.ndmg.digits[iDigit];
                    if (var_s3) {
                        var_s3 = var_s3 * 8 + 0x18;
                        s0_prim->u0 = s0_prim->u2 = var_s3;
                        s0_prim->u1 = s0_prim->u3 = var_s3 + 6;
                    } else {
                        s0_prim->u0 = s0_prim->u2 = 0x68;
                        s0_prim->u1 = s0_prim->u3 = 0x6E;
                    }
                    s0_prim->v0 = s0_prim->v1 = 0x40;
                    s0_prim->v2 = s0_prim->v3 = 0x49;
                    var_s8 += 4;
                    iDigit++;
                }
                s0_prim->tpage = 0x1A;
                s0_prim->priority = 0x1F8;
                s0_prim->blendMode = 8;
                s0_prim = s0_prim->next;
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
        s0_prim = &g_PrimBuf[self->primIndex];
        if (iDigit && iDigit != 4) {
            while (s0_prim != NULL) {
                if (self->ext.ndmg.timer >= 60) {
                    LOHU(s0_prim->r2)++;
                    LOHU(s0_prim->b2)++;
                } else if (self->ext.ndmg.timer >= 56) {
                    LOHU(s0_prim->r2)--;
                    LOHU(s0_prim->b2)--;
                }
                x = self->posX.i.hi + LOH(s0_prim->r1);
                y = self->posY.i.hi + LOH(s0_prim->b1);
                s0_prim->x0 = s0_prim->x2 = x - LOHU(s0_prim->r2);
                s0_prim->x1 = s0_prim->x3 = x + LOHU(s0_prim->r2);
                s0_prim->y0 = s0_prim->y1 = y - LOHU(s0_prim->b2);
                s0_prim->y2 = s0_prim->y3 = y + LOHU(s0_prim->b2);
                s0_prim->clut = clut;
                if (self->ext.ndmg.timer < 6) {
                    s0_prim->blendMode = 0x13;
                } else {
                    s0_prim->blendMode = 0x02;
                }
                s0_prim = s0_prim->next;
            }
            if (self->ext.ndmg.unk88 != 0) {
                return;
            }
            self->posY.val -= FIX(0.5);
        } else {
            while (s0_prim != NULL) {
                if (LOHU(s0_prim->r2) > 3) {
                    LOHU(s0_prim->r2)--;
                }
                if (LOHU(s0_prim->b2) < 10) {
                    LOHU(s0_prim->b2)++;
                }

                x = self->posX.i.hi + LOH(s0_prim->r1);
                y = self->posY.i.hi + LOH(s0_prim->b1) + 5 -
                    (LOHU(s0_prim->b2));
                s0_prim->x0 = x - LOHU(s0_prim->r2);
                s0_prim->x1 = x + LOHU(s0_prim->r2);
                s0_prim->x2 = x - 3;
                s0_prim->x3 = x + 3;
                s0_prim->y0 = s0_prim->y1 = y;
                s0_prim->y2 = s0_prim->y3 = y + LOHU(s0_prim->b2);
                s0_prim->clut = clut;

                if (self->ext.ndmg.timer < 6) {
                    s0_prim->blendMode = 0x13;
                } else {
                    s0_prim->blendMode = 0x02;
                }
                s0_prim = s0_prim->next;
            }
            self->posY.val -= FIX(0.5);
        }
        break;
    }
}
