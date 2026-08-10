// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rno0.h"

// Armor Lord fire wave helper
static void func_us_801D1184(Primitive* prim) {
switch (prim->next->u2) {
    case 0:
        prim->tpage = 0x1A;
        prim->clut = PAL_CC_FIRE_EFFECT;
        prim->u0 = 0xF0;
        prim->u1 = 0xFF;
        prim->u2 = prim->u0;
        prim->u3 = prim->u1;
        if (prim->next->r3) {
            prim->v0 = 0;
            prim->v1 = prim->v0;
            prim->v2 = 0xF;
            prim->v3 = prim->v2;
        } else {
            prim->v0 = 0x28;
            prim->v1 = prim->v0;
            prim->v2 = 0x37;
            prim->v3 = prim->v2;
        }
        prim->priority = g_CurrentEntity->zPriority + 2;
        prim->drawMode =
            DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_UNK02 | DRAW_TRANSP;
        prim->x0 -= 8;
        prim->x1 = prim->x0 + 16;
        prim->x2 = prim->x0;
        prim->x3 = prim->x1;
        prim->y0 -= 8;
        prim->y1 = prim->y0;
        prim->y2 = prim->y0 + 0x10;
        prim->y3 = prim->y2;
        PGREY(prim, 0) = 0xA0;
        PGREY(prim, 1) = 0xA0;
        PGREY(prim, 2) = 0xA0;
        PGREY(prim, 3) = 0xA0;
        prim->next->u2++;
        break;

    case 1:
        if (g_Timer % 4 == 0) {
            prim->y0++;
            prim->y1 = prim->y0;
            prim->y2 = prim->y0 + 0x10;
            prim->y3 = prim->y2;
        }
        prim->r0 -= 2;
        prim->g0 = prim->b0 = prim->r0;
        prim->r1 = prim->g1 = prim->b1 = prim->r0;
        prim->r2 = prim->g2 = prim->b2 = prim->r0;
        prim->r3 = prim->g3 = prim->b3 = prim->r0;
        if (prim->r0 < 0x10) {
            UnkPolyFunc0(prim);
            prim->next->u2 = 0;
        }
        break;
    }
}

extern Primitive* FindFirstUnkPrim2(Primitive* prim, u8 index);
// Armor Lord
static void func_us_801D1388(Primitive* prim) {
    Collider collider;
    Primitive* otherPrim;
    Entity* tempEntity;
    s16 dx;
    s16 posX, posY;

    if (g_Timer % 3 == 0) {
        u8 temp = prim->u0;
        prim->u0 = prim->u1;
        prim->u1 = temp;
        prim->u2 = prim->u0;
        prim->u3 = prim->u1;
    }
    switch (prim->next->u2) {
    case 0:
        prim->x0 = prim->x2;
        prim->x1 = prim->x3;
        prim->y0 = prim->y2;
        prim->y1 = prim->y3;
        prim->tpage = 0x14;
        prim->clut = PAL_ARMOR_LORD_UNK;
        prim->u0 = 0xE0;
        prim->u1 = 0xEF;
        prim->u2 = prim->u0;
        prim->u3 = prim->u1;
        prim->v0 = 0xD0;
        prim->v1 = prim->v0;
        prim->v2 = 0xD0;
        prim->v3 = prim->v2;
        PGREY(prim, 0) = 0x70;
        PGREY(prim, 1) = 0x70;
        PGREY(prim, 2) = 0x70;
        PGREY(prim, 3) = 0x70;
        prim->priority = g_CurrentEntity->zPriority + 2;
        prim->drawMode =
            DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_UNK02 | DRAW_TRANSP;
        prim->next->u2++;
        break;

    case 1:
        prim->v2 += 2;
        prim->v3 = prim->v2;
        prim->y0 -= 2;
        prim->y1 -= 2;
        if (g_CurrentEntity->facingLeft) {
            prim->x3++;
        } else {
            prim->x3--;
        }
        prim->x1 = prim->x3;
        posX = prim->x3;
        posY = prim->y3 + 1;
        g_api.CheckCollision(posX, posY, &collider, 0);
        if ((collider.effects & EFFECT_SOLID) == 0) {
            prim->next->r3 = 0;
            prim->next->u2 += 1;
            break;
        }
        if ((prim->v2 == 0xE0) && prim->next->r3) {
            otherPrim = g_CurrentEntity->ext.armorLord.prim;
            otherPrim = FindFirstUnkPrim2(otherPrim, 2);
            if (otherPrim != NULL) {
                UnkPolyFunc2(otherPrim);
                otherPrim->next->r3 = prim->next->r3 - 1;
                if (g_CurrentEntity->facingLeft) {
                    otherPrim->x2 = prim->x3 - 8;
                    otherPrim->x3 = otherPrim->x2 + 16;
                } else {
                    otherPrim->x2 = prim->x3 + 8;
                    otherPrim->x3 = otherPrim->x2 - 16;
                }
                otherPrim->y2 = prim->y3;
                otherPrim->y3 = otherPrim->y2;
            }
        }
        if (prim->v2 > 0xFD) {
            otherPrim = g_CurrentEntity->ext.armorLord.prim;
            otherPrim = FindFirstUnkPrim2(otherPrim, 2);
            if (otherPrim != NULL) {
                UnkPolyFunc2(otherPrim);
                otherPrim->next->g3 = 1;
                otherPrim->next->r3 = Random() & 1;
                if (g_CurrentEntity->facingLeft) {
                    otherPrim->x0 = prim->x1 - 0x10;
                } else {
                    otherPrim->x0 = prim->x1 + 0x10;
                }
                otherPrim->y0 = prim->y1 + 0x10;
            }
            prim->next->u2++;
        }
        break;

    case 2:
        prim->v2--;
        prim->v3 = prim->v2;
        prim->y0++;
        prim->y1++;
        prim->g0 -= 4;
        prim->b0 -= 2;
        prim->r1 = prim->r2 = prim->r3 = prim->r0;
        prim->g1 = prim->g2 = prim->g3 = prim->g0;
        prim->b1 = prim->b2 = prim->b3 = prim->b0;
        if (prim->v2 < 0xD2) {
            UnkPolyFunc0(prim);
            prim->next->u2 = 0;
        }
        break;
    }
    tempEntity = &PLAYER;
    if (g_CurrentEntity->facingLeft) {
        dx = prim->x3 - tempEntity->posX.i.hi;
    } else {
        dx = tempEntity->posX.i.hi - prim->x3;
    }
    if ((dx > 0) && !prim->next->v2 && (dx < 0x10)) {
        tempEntity = AllocEntity(&g_Entities[160], &g_Entities[192]);
        if (tempEntity != NULL) {
            CreateEntityFromCurrentEntity(E_ARMOR_LORD_UNK2, tempEntity);
            tempEntity->posX.i.hi = prim->x3;
            tempEntity->posY.i.hi = prim->y0;
            tempEntity->facingLeft = g_CurrentEntity->facingLeft;
            tempEntity->hitboxHeight = (prim->y2 - prim->y0) / 2;
            tempEntity->hitboxOffY = tempEntity->hitboxHeight + 8;
            tempEntity->ext.armorLord.prim = prim;
            prim->next->v2 = 1;
        }
    }
}

extern EInit g_EInitInteractable;

void EntityGuardianFireWave(Entity* self) {
    Primitive* prim;
    s32 primIndex;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        self->ext.armorLord.unk80 = 0;
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 0x1A);
        if (primIndex != -1) {
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            self->ext.armorLord.prim = prim;
            while (prim != NULL) {
                prim->drawMode = DRAW_HIDE;
                prim->p3 = 0;
                prim = prim->next;
            }
        } else {
            DestroyEntity(self);
            return;
        }
        prim = self->ext.armorLord.prim;
        prim = FindFirstUnkPrim2(prim, 2);
        if (prim != NULL) {
            UnkPolyFunc2(prim);
            prim->x2 = self->posX.i.hi;
            if (self->facingLeft) {
                prim->x3 = prim->x2 + 0x20;
            } else {
                prim->x3 = prim->x2 - 0x20;
            }
            prim->y2 = self->posY.i.hi + 0x28;
            prim->y3 = prim->y2;
            prim->next->r3 = 5;
            prim->next->g3 = 0;
        }

    case 1:
        prim = self->ext.armorLord.prim;
        while (prim != NULL) {
            if (prim->p3 & 8) {
                if (prim->next->g3) {
                    func_us_801D1184(prim);
                } else {
                    func_us_801D1388(prim);
                }
            }
            prim = prim->next;
        }
        if (self->ext.armorLord.unk80++ > 0x100) {
            DestroyEntity(self);
            return;
        }
    }
}

void Unused801C2C50(void) {}

INCLUDE_ASM("st/rno0/nonmatchings/e_armor_lord_guardian", func_us_801D1A9C_from_are);

INCLUDE_ASM("st/rno0/nonmatchings/e_armor_lord_guardian", func_us_801D1DAC_from_are);

INCLUDE_ASM("st/rno0/nonmatchings/e_armor_lord_guardian", EntityGuardian);

INCLUDE_ASM("st/rno0/nonmatchings/e_armor_lord_guardian", func_us_801D348C_from_are);

INCLUDE_ASM("st/rno0/nonmatchings/e_armor_lord_guardian", EntityArmorLordUnk2);
