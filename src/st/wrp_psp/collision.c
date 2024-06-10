#include "../wrp/wrp.h"

INCLUDE_ASM("st/wrp_psp/psp/wrp_psp/collision", HitDetection);

extern u16 D_80180A6C[];
extern u16 D_801804A0[];

void EntityNumericDamage(Entity* self) {
    Primitive* s0_prim;
    s16 s1_x;
    u8 var_s3;
    s16 s2_y;
    u16 s4_iDigit;
    u16 s5_params;
    u16 var_s6;
    u16* s7_nDigits;
    s32 sp38;
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
        s5_params = self->params;
        s7_nDigits = &self->ext.ndmg.nDigits;
        if (!self->step_s) {
            InitializeEntity(D_801804A0);
            self->step = 0;
            if (s5_params == 0xC000) {
                self->ext.ndmg.nPrims++;
            } else {
                var_s6 = s5_params & 0x3FFF;

                // thousands
                s4_iDigit = var_s6 / 1000;
                if (s4_iDigit) {
                    self->ext.ndmg.nPrims++;
                    (*s7_nDigits)++;
                }
                self->ext.ndmg.digits[0] = s4_iDigit;

                // hundreds
                var_s6 -= s4_iDigit * 1000;
                s4_iDigit = var_s6 / 100;
                if (s4_iDigit || *s7_nDigits) {
                    self->ext.ndmg.nPrims++;
                    (*s7_nDigits)++;
                }
                self->ext.ndmg.digits[1] = s4_iDigit;

                // tens
                var_s6 -= s4_iDigit * 100;
                s4_iDigit = var_s6 / 10;
                if (s4_iDigit || *s7_nDigits) {
                    self->ext.ndmg.nPrims++;
                    (*s7_nDigits)++;
                }
                self->ext.ndmg.digits[2] = s4_iDigit;

                // units
                var_s6 -= s4_iDigit * 10;
                self->ext.ndmg.nPrims++;
                (*s7_nDigits)++;
                self->ext.ndmg.digits[3] = var_s6;

                if (s5_params & 0x4000) {
                    self->ext.ndmg.nPrims++;
                }
            }
        }

        sp38 = g_api.AllocPrimitives(PRIM_GT4, self->ext.ndmg.nPrims);
        if (sp38) {
            self->primIndex = sp38;
            self->flags |= FLAG_HAS_PRIMS;
            s0_prim = &g_PrimBuf[sp38];

            sp3e = 0;
            s4_iDigit = 4 - *s7_nDigits;
            var_s8 = -(*s7_nDigits) * 2;
            while (s0_prim != NULL) {
                if (!sp3e) {
                    sp3e++;
                    if ((s5_params & 0xC000) == 0xC000) {
                        s0_prim->u0 = s0_prim->u2 = 0x43;
                        s0_prim->u1 = s0_prim->u3 = 0x59;
                        s0_prim->v0 = s0_prim->v1 = 0x4A;
                        s0_prim->v2 = s0_prim->v3 = 0x52;
                        LOH(s0_prim->r2) = 0xB;
                        LOH(s0_prim->b2) = 5;
                        LOH(s0_prim->r1) = 0;
                        LOH(s0_prim->b1) = -0x10;
                    } else if (s5_params & 0x4000) {
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
                    if (s5_params & 0x4000) {
                        LOH(s0_prim->r2) = 3;
                        LOH(s0_prim->b2) = 5;
                    } else {
                        LOH(s0_prim->r2) = 0x17;
                        LOH(s0_prim->b2) = 0;
                    }

                    var_s3 = self->ext.ndmg.digits[s4_iDigit];
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
                    s4_iDigit++;
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
        s5_params = --self->ext.ndmg.timer;
        if (!s5_params) {
            DestroyEntity(self);
            return;
        }

        s5_params &= 1;
        s4_iDigit = (self->params >> 13) & 6;
        s5_params |= s4_iDigit;
        var_s6 = D_80180A6C[s5_params];
        s0_prim = &g_PrimBuf[self->primIndex];
        if (s4_iDigit && s4_iDigit != 4) {
            while (s0_prim != NULL) {
                if (self->ext.ndmg.timer >= 60) {
                    LOHU(s0_prim->r2)++;
                    LOHU(s0_prim->b2)++;
                } else if (self->ext.ndmg.timer >= 56) {
                    LOHU(s0_prim->r2)--;
                    LOHU(s0_prim->b2)--;
                }
                s1_x = self->posX.i.hi + LOH(s0_prim->r1);
                s2_y = self->posY.i.hi + LOH(s0_prim->b1);
                s0_prim->x0 = s0_prim->x2 = s1_x - LOHU(s0_prim->r2);
                s0_prim->x1 = s0_prim->x3 = s1_x + LOHU(s0_prim->r2);
                s0_prim->y0 = s0_prim->y1 = s2_y - LOHU(s0_prim->b2);
                s0_prim->y2 = s0_prim->y3 = s2_y + LOHU(s0_prim->b2);
                s0_prim->clut = var_s6;
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

                s1_x = self->posX.i.hi + LOH(s0_prim->r1);
                s2_y = self->posY.i.hi + LOH(s0_prim->b1) + 5 -
                       (LOHU(s0_prim->b2));
                s0_prim->x0 = s1_x - LOHU(s0_prim->r2);
                s0_prim->x1 = s1_x + LOHU(s0_prim->r2);
                s0_prim->x2 = s1_x - 3;
                s0_prim->x3 = s1_x + 3;
                s0_prim->y0 = s0_prim->y1 = s2_y;
                s0_prim->y2 = s0_prim->y3 = s2_y + LOHU(s0_prim->b2);
                s0_prim->clut = var_s6;

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
