extern u16 g_ENumericDamageInit[];
extern u16 g_ENumericDamageClut[];
void EntityNumericDamage(Entity* self) {
    Primitive* prim;
    s16 x;
    s16 y;
    u8 singleDigit;
    u16 iDigit;
    u16 params;
    u16 clut;
    u16* nDigits;
    s16 xOffset;
    s32 primIndex;
    u16 primInitStep;

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
            InitializeEntity(g_ENumericDamageInit);
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
            xOffset = *nDigits * -2;
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
        clut = g_ENumericDamageClut[params];
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
            self->posY.val -= 0x8000;
        } else {
            while (prim != NULL) {
                if (LOHU(prim->r2) >= 4) {
                    LOHU(prim->r2)--;
                }
                if (LOHU(prim->b2) < 10) {
                    LOHU(prim->b2)++;
                }
                x = self->posX.i.hi + LOH(prim->r1);
                y = self->posY.i.hi + LOH(prim->b1) + 5 - (LOHU(prim->b2));
                prim->x0 = x - LOHU(prim->r2);
                prim->x1 = x + LOHU(prim->r2);
                prim->y0 = prim->y1 = y;
                prim->y2 = prim->y3 = y + LOH(prim->b2);
                prim->clut = clut;
                prim->x2 = x - 3;
                prim->x3 = x + 3;
                if (self->ext.ndmg.timer < 6) {
                    prim->blendMode = 0x13;
                } else {
                    prim->blendMode = 0x02;
                }
                prim = prim->next;
            }
            self->posY.val -= 0x8000;
        }
        break;
    }
}
