#include "cen.h"

INCLUDE_ASM("st/cen/nonmatchings/18084", func_80198084);

extern u16 D_80180440[];
void EntityUnkId13(Entity* entity) {
    switch (entity->step) {
    case 0:
        InitializeEntity(D_80180440);
        entity->ext.generic.unk8C.modeU16.unk0 =
            entity->ext.generic.unk80.entityPtr->entityId;
    case 1:
        if (entity->ext.generic.unk7C.U8.unk0++ >= 5) {
            Entity* newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(E_EXPLOSION, entity, newEntity);
                newEntity->entityId = E_EXPLOSION;
                newEntity->pfnUpdate = EntityExplosion;
                newEntity->params = entity->params;
            }
            entity->ext.generic.unk7C.U8.unk0 = 0;
        }
        entity->posX.i.hi = entity->ext.generic.unk80.entityPtr->posX.i.hi;
        entity->posY.i.hi = entity->ext.generic.unk80.entityPtr->posY.i.hi;
        if (entity->ext.generic.unk80.entityPtr->entityId !=
            entity->ext.generic.unk8C.modeU16.unk0) {
            DestroyEntity(entity);
        }
        break;
    }
}

INCLUDE_ASM("st/cen/nonmatchings/18084", func_80198284);

#include "../entity_unkId15_spawner.h"

// ID 14
INCLUDE_ASM("st/cen/nonmatchings/18084", EntityExplosion14);

INCLUDE_ASM("st/cen/nonmatchings/18084", EntityUnkId15);

INCLUDE_ASM("st/cen/nonmatchings/18084", func_80198680);

INCLUDE_ASM("st/cen/nonmatchings/18084", func_801988B0);

u8 func_801989AC(s32 arg0) {
    Collider collider;
    u32 bits_67;
    u32 bits_45;
    u32 bits_23;
    u8 bits_01;
    u16 collEff;

    MoveEntity();
    bits_67 = 0;
    bits_23 = 0;
    bits_45 = 0;
    bits_01 = arg0 & 3;
    collEff = 0;
    switch (bits_01) {
    case 0:
        g_CurrentEntity->posY.i.hi += 3;
        g_api.CheckCollision(g_CurrentEntity->posX.i.hi,
                             g_CurrentEntity->posY.i.hi, &collider, 0);
        if (collider.effects != 0) {
            collEff = collider.effects;
            g_CurrentEntity->posY.i.hi += collider.unk18;
            g_api.CheckCollision(
                g_CurrentEntity->posX.i.hi,
                (s16)(g_CurrentEntity->posY.i.hi - 4), &collider, 0);
            if (collider.effects & EFFECT_UNK_0002) {
                bits_67 = 0x40;
                if (g_CurrentEntity->velocityX > 0) {
                    bits_01 = 2;
                } else {
                    bits_01 = 3;
                    g_CurrentEntity->velocityX = -g_CurrentEntity->velocityX;
                }
                g_CurrentEntity->velocityY = -g_CurrentEntity->velocityX;
                g_CurrentEntity->velocityX = 0;
            }
        } else {
            bits_67 = 0x80;
            g_CurrentEntity->posX.val -= g_CurrentEntity->velocityX;
            if (g_CurrentEntity->velocityX > 0) {
                bits_01 = 3;
            } else {
                bits_01 = 2;
                g_CurrentEntity->velocityX = -g_CurrentEntity->velocityX;
            }
            g_CurrentEntity->velocityY = g_CurrentEntity->velocityX;
            g_CurrentEntity->velocityX = 0;
        }
        break;

    case 1:
        g_CurrentEntity->posY.i.hi -= 3;
        g_api.CheckCollision(g_CurrentEntity->posX.i.hi,
                             g_CurrentEntity->posY.i.hi, &collider, 0);
        if (collider.effects != 0) {
            collEff = collider.effects;
            g_CurrentEntity->posY.i.hi += collider.unk20;
            g_api.CheckCollision(
                g_CurrentEntity->posX.i.hi,
                (s16)(g_CurrentEntity->posY.i.hi + 4), &collider, 0);
            if (collider.effects & EFFECT_UNK_0002) {
                bits_67 = 0x40;
                if (g_CurrentEntity->velocityX > 0) {
                    bits_01 = 2;
                } else {
                    bits_01 = 3;
                    g_CurrentEntity->velocityX = -g_CurrentEntity->velocityX;
                }
                g_CurrentEntity->velocityY = g_CurrentEntity->velocityX;
                g_CurrentEntity->velocityX = 0;
            }
        } else {
            bits_67 = 0x80;
            g_CurrentEntity->posX.val -= g_CurrentEntity->velocityX;
            if (g_CurrentEntity->velocityX > 0) {
                bits_01 = 3;
            } else {
                bits_01 = 2;
                g_CurrentEntity->velocityX = -g_CurrentEntity->velocityX;
            }
            g_CurrentEntity->velocityY = -g_CurrentEntity->velocityX;
            g_CurrentEntity->velocityX = 0;
        }
        break;

    case 2:
        g_CurrentEntity->posX.i.hi += 3;
        g_api.CheckCollision(g_CurrentEntity->posX.i.hi,
                             g_CurrentEntity->posY.i.hi, &collider, 0);
        if (collider.effects != 0) {
            collEff = collider.effects;
            g_CurrentEntity->posX.i.hi += collider.unk14;
            g_api.CheckCollision((s16)(g_CurrentEntity->posX.i.hi - 4),
                                 g_CurrentEntity->posY.i.hi, &collider, 0);
            if (collider.effects & EFFECT_SOLID) {
                bits_67 = 0x40;
                if (g_CurrentEntity->velocityY > 0) {
                    bits_01 = 0;
                } else {
                    bits_01 = 1;
                    g_CurrentEntity->velocityY = -g_CurrentEntity->velocityY;
                }
                g_CurrentEntity->velocityX = -g_CurrentEntity->velocityY;
                g_CurrentEntity->velocityY = 0;
            }
        } else {
            bits_67 = 0x80;
            g_CurrentEntity->posY.val -= g_CurrentEntity->velocityY;
            if (g_CurrentEntity->velocityY > 0) {
                bits_01 = 1;
            } else {
                bits_01 = 0;
                g_CurrentEntity->velocityY = -g_CurrentEntity->velocityY;
            }
            g_CurrentEntity->velocityX = g_CurrentEntity->velocityY;
            g_CurrentEntity->velocityY = 0;
        }
        break;

    case 3:
        g_CurrentEntity->posX.i.hi -= 3;
        g_api.CheckCollision(g_CurrentEntity->posX.i.hi,
                             g_CurrentEntity->posY.i.hi, &collider, 0);
        if (collider.effects != 0) {
            collEff = collider.effects;
            g_CurrentEntity->posX.i.hi += collider.unk1C;
            g_api.CheckCollision((s16)(g_CurrentEntity->posX.i.hi + 4),
                                 g_CurrentEntity->posY.i.hi, &collider, 0);
            if (collider.effects & EFFECT_SOLID) {
                bits_67 = 0x40;
                if (g_CurrentEntity->velocityY > 0) {
                    bits_01 = 0;
                } else {
                    bits_01 = 1;
                    g_CurrentEntity->velocityY = -g_CurrentEntity->velocityY;
                }
                g_CurrentEntity->velocityX = g_CurrentEntity->velocityY;
                g_CurrentEntity->velocityY = 0;
            }
        } else {
            bits_67 = 0x80;
            g_CurrentEntity->posY.val -= g_CurrentEntity->velocityY;
            if (g_CurrentEntity->velocityY > 0) {
                bits_01 = 1;
            } else {
                bits_01 = 0;
                g_CurrentEntity->velocityY = -g_CurrentEntity->velocityY;
            }
            g_CurrentEntity->velocityX = -g_CurrentEntity->velocityY;
            g_CurrentEntity->velocityY = 0;
        }
    }

    if (collEff & EFFECT_UNK_8000) {
        bits_23 = 4;
    }
    if (collEff & EFFECT_UNK_1000) {
        bits_23 = 8;
    }
    if (collEff & EFFECT_UNK_2000) {
        bits_23 = 0xC;
    }
    if (collEff & EFFECT_UNK_0800) {
        bits_45 = 0x20;
    }
    if (collEff & EFFECT_UNK_4000) {
        bits_45 = 0x10;
    }
    bits_01 = (bits_45 + (bits_23 + (bits_67 + bits_01)));
    return bits_01;
}

// ID 06
#include "../entity_intense_explosion.h"

INCLUDE_ASM("st/cen/nonmatchings/18084", func_8019902C);

INCLUDE_ASM("st/cen/nonmatchings/18084", func_801990F8);

void func_801991C0(void) {
    Entity* entity;
    s8 temp_s4 = Random() & 3;
    s16 temp_s3 = ((Random() & 0xF) << 8) - 0x800;
    s32 i;

    for (i = 0; i < 6; i++) {
        entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (entity != NULL) {
            CreateEntityFromEntity(2, g_CurrentEntity, entity);
            entity->ext.generic.unk84.U8.unk1 = 6 - i;
            entity->ext.generic.unk80.modeS16.unk0 = temp_s3;
            entity->ext.generic.unk84.U8.unk0 = temp_s4;
        }
    }
}

INCLUDE_ASM("st/cen/nonmatchings/18084", func_80199278);

INCLUDE_ASM("st/cen/nonmatchings/18084", func_80199450);

INCLUDE_ASM("st/cen/nonmatchings/18084", func_80199A30);

void ClutLerp(RECT* rect, u16 palIdxA, u16 palIdxB, s32 steps, u16 offset) {
    u16 buf[COLORS_PER_PAL];
    RECT bufRect;
    s32 factor;
    u32 t;
    u32 r, g, b;
    s32 i, j;
    u16 *palA, *palB;

    bufRect.x = rect->x;
    bufRect.w = COLORS_PER_PAL;
    bufRect.h = 1;

    palA = g_Clut + palIdxA * COLORS_PER_PAL;
    palB = g_Clut + palIdxB * COLORS_PER_PAL;

    for (i = 0; i < steps; i++) {
        factor = i * 4096 / steps;
        for (j = 0; j < COLORS_PER_PAL; j++) {
            r = (palA[j] & 0x1F) * (4096 - factor) + (palB[j] & 0x1F) * factor;
            g = ((palA[j] >> 5) & 0x1F) * (4096 - factor) +
                ((palB[j] >> 5) & 0x1F) * factor;
            b = ((palA[j] >> 10) & 0x1F) * (4096 - factor) +
                ((palB[j] >> 10) & 0x1F) * factor;

            t = palA[j] & 0x8000;
            t |= palB[j] & 0x8000;

            buf[j] = t | (r >> 12) | ((g >> 12) << 5) | ((b >> 12) << 10);
        }

        bufRect.y = rect->y + i;
        LoadImage(&bufRect, buf);
        D_8003C104[offset + i] = GetClut(bufRect.x, bufRect.y);
    }
}

void func_8019A328(s16 sfxId) {
    s32 var_a3;
    s32 temp_v0_2;
    s16 var_a2;
    s32 y;
    s16 var_v0_4;
    s16 var_v1;

    var_a3 = g_CurrentEntity->posX.i.hi - 128;
    var_a2 = (ABS(var_a3) - 32) >> 5;
    if (var_a2 > 8) {
        var_a2 = 8;
    } else if (var_a2 < 0) {
        var_a2 = 0;
    }
    if (var_a3 < 0) {
        var_a2 = -var_a2;
    }
    var_a3 = ABS(var_a3) - 96;
    y = g_CurrentEntity->posY.i.hi - 128;
    temp_v0_2 = ABS(y) - 112;
    var_v1 = var_a3;
    if (temp_v0_2 > 0) {
        var_v1 += temp_v0_2;
    }
    if (var_v1 < 0) {
        var_v0_4 = 0;
    } else {
        var_v0_4 = var_v1;
    }
    var_a3 = 127 - (var_v0_4 >> 1);
    if (var_a3 > 0) {
        g_api.func_80134714(sfxId, var_a3, var_a2);
    }
}

void func_8019A420(Primitive* prim) {
    u8 xPos;
    s32 i;
    s32 j;

    switch (prim->p3) {
    case 0:
        if (prim->p1 < 0x80) {
            if (--prim->p1 == 0) {
                prim->p3 = 1;
            }
        } else {
            if (++prim->p1 == 0) {
                prim->p3 = 2;
            }
        }

        if (prim->p3 != 0) {
            u8* dst = prim->p3 == 1 ? &prim->r1 : &prim->r0;
            for (i = 0; i < 2; i++) {
                for (j = 0; j < 3; j++) {
                    dst[j] = 0x50;
                }
                dst += 0x18;
            }
            prim->p2 = 0;
        }
        break;
    case 1:
        if (prim->p2 < 0x14) {
            prim->p2++;
        }
        xPos = prim->p2 / 5;
        prim->x2 = prim->x0 = prim->x0 + xPos;
        prim->x1 = prim->x1 + xPos;
        prim->x3 = prim->x0;
        UnkLoopFunc(prim, 4);
        break;
    case 2:
        if (prim->p2 < 0x14) {
            prim->p2++;
        }
        xPos = prim->p2 / 5;
        prim->x2 = prim->x0 = prim->x0 - xPos;
        prim->x1 = prim->x1 - xPos;
        prim->x3 = prim->x0;
        UnkLoopFunc(prim, 4);
        break;
    }
}

extern u16 g_EInitGeneric[];
void EntityStageNamePopup(Entity* self) {
    u8 pad[100];
    Primitive* prim;
    s16 primIndex;
    u8 var_a0;
    s32 i;
    s32 blendMode;

    switch (self->step) {
    case 0:
        if (g_DemoMode != Demo_None ||
            g_CastleFlags[CASTLE_FLAG_BANK + 2] != 0) {
            DestroyEntity(self);
            return;
        }

        InitializeEntity(g_EInitGeneric);
        primIndex = g_api_AllocPrimitives(PRIM_GT4, 0x57);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        prim = &g_PrimBuf[primIndex];
        self->primIndex = primIndex;
        self->ext.stpopup.prim = prim;
        self->flags |= 0x800000;
        while (prim != NULL) {
            prim->blendMode = 8;
            prim = prim->next;
        }
        prim = self->ext.stpopup.prim;
        for (i = 0; i < 2; i++) {
            prim->tpage = 0x11;
            prim->clut = 0x19F;
            prim->u0 = prim->u2 = 4;
            prim->u1 = prim->u3 = 0x78;
            prim->v0 = prim->v1 = 0;
            prim->v2 = prim->v3 = 0x28;
            prim->x2 = prim->x0 = 0xC;
            prim->y1 = prim->y0 = 0x9D;
            prim->x3 = prim->x1 = 0x80;
            prim->y3 = prim->y2 = 0xC5;
            prim->priority = 0xC0 - i;
            prim->blendMode = 8;
            prim = prim->next;

            prim->tpage = 0x11;
            prim->clut = 0x19F;
            prim->u0 = prim->u2 = 8;
            prim->u1 = prim->u3 = 0x7C;
            prim->v0 = prim->v1 = 0x40;
            prim->v2 = prim->v3 = 0x68;
            prim->x2 = prim->x0 = 0x80;
            prim->y1 = prim->y0 = 0x9D;
            prim->x3 = prim->x1 = 0xF4;
            prim->y3 = prim->y2 = 0xC5;
            prim->priority = 0xC0 - i;
            prim->blendMode = 8;
            prim = prim->next;
        }

        i = 0;
        self->ext.stpopup.unk88 = prim;
        prim->tpage = 0x11;
        prim->clut = 0x19D;
        prim->u0 = prim->u2 = 4;
        prim->u1 = prim->u3 = 0x78;
        prim->v0 = prim->v1 = 0;
        prim->v2 = prim->v3 = 0x28;
        prim->x2 = prim->x0 = 0xC;
        prim->y1 = prim->y0 = 0x9D;
        prim->x3 = prim->x1 = 0x80;
        prim->y3 = prim->y2 = 0xC5;
        prim->priority = 0xBF;
        prim->blendMode = 8;
        prim = prim->next;

        prim->clut = 0x19D;
        prim->tpage = 0x11;
        prim->u0 = prim->u2 = 8;
        prim->u1 = prim->u3 = 0x7C;
        prim->v0 = prim->v1 = 0x40;
        prim->v2 = prim->v3 = 0x68;
        prim->x2 = prim->x0 = 0x80;
        prim->y1 = prim->y0 = 0x9D;
        prim->x3 = prim->x1 = 0xF4;
        prim->y3 = prim->y2 = 0xC5;
        prim->priority = 0xBF;
        prim->blendMode = 8;
        prim = prim->next;

        self->ext.stpopup.unk84 = prim;
        prim->type = 3;
        prim->tpage = 0x1A;
        prim->clut = 0x15F;
        prim->u0 = 0;
        prim->u1 = 0x40;
        prim->u2 = prim->u0;
        prim->u3 = prim->u1;
        prim->v1 = prim->v0 = 0xC0;
        prim->v3 = prim->v2 = 0xFF;
        prim->y1 = prim->y0 = 0x9B;
        prim->y3 = prim->y2 = 0xC7;
        prim->x2 = prim->x0 = 0xC;
        prim->x3 = prim->x1 = 0xF4;
        prim->r0 = 0x10;
        prim->g0 = 0x28;
        prim->b0 = 0;
        prim->r2 = 8;
        prim->g2 = 0;
        prim->b2 = 0x38;
        prim->priority = 0xB0;
        prim->blendMode = 0x1D;
        LOW(prim->r1) = LOW(prim->r0);
        LOW(prim->r3) = LOW(prim->r2);
        prim = prim->next;

        self->ext.stpopup.unk8C = prim;
        for (i = 0; i < 0x28; i++) {
            prim->tpage = 0x11;
            prim->clut = 0x19F;
            prim->v2 = prim->v3 = i + 1;
            prim->y1 = prim->y0 = i + 0x9D;
            prim->r0 = 0x78;
            prim->g0 = 0x78;
            prim->b0 = 0xA8;
            prim->y3 = prim->y2 = i + 0x9E;
            prim->v0 = prim->v1 = i;
            prim->x2 = prim->x0 = 0xC;
            prim->x3 = prim->x1 = 0x80;
            prim->u2 = prim->u0 = 4;
            prim->u1 = prim->u3 = primIndex = 0x78; // FAKE
            prim->priority = 0xC0;
            prim->blendMode = 0xC;
            LOW(prim->r1) = LOW(prim->r0);
            LOW(prim->r2) = LOW(prim->r0);
            LOW(prim->r3) = LOW(prim->r0);
            prim = prim->next;
        }
        for (i = 0; i < 0x28; i++) {
            prim->tpage = 0x11;
            prim->clut = 0x19F;
            prim->y1 = prim->y0 = i + 0x9D;
            prim->y3 = prim->y2 = i + 0x9E;
            prim->v0 = prim->v1 = i + 0x40;
            prim->x2 = prim->x0 = 0x80;
            prim->x3 = prim->x1 = 0xF4;
            prim->u2 = prim->u0 = 8;
            prim->u1 = prim->u3 = 0x7C;
            prim->v2 = prim->v3 = i + 0x41;
            prim->r0 = 0x78;
            prim->g0 = 0x78;
            prim->b0 = 0xA8;
            prim->priority = 0xC0;
            prim->blendMode = 0xC;
            LOW(prim->r1) = LOW(prim->r0);
            LOW(prim->r2) = LOW(prim->r0);
            LOW(prim->r3) = LOW(prim->r0);
            prim = prim->next;
        }
        self->ext.stpopup.unk80 = 0x20;
    case 1:
        switch (self->step_s) {
        case 0:
            if (self->ext.stpopup.unk80 != 0) {
                self->ext.stpopup.unk80--;
            } else {
                prim = self->ext.stpopup.unk84;
                prim->x0 = prim->x2 = 0x80;
                prim->x1 = prim->x3 = 0x80;
                prim->y0 = prim->y1 = 0xB1;
                prim->y2 = prim->y3 = 0xB1;
                prim->blendMode = 0x15;
                self->step_s++;
            }
            break;
        case 1:
            prim = self->ext.stpopup.unk84;
            var_a0 = 0;
            if (prim->y0 >= 0x9C) {
                var_a0 = 1;
                prim->y1 = prim->y0 = prim->y0 - 4;
                prim->y3 = prim->y2 = prim->y2 + 4;
            }
            if (prim->x0 >= 0xD) {
                var_a0 |= 1;
                prim->x2 = prim->x0 = prim->x0 - 8;
                prim->x3 = prim->x1 = prim->x1 + 8;
            }
            if (var_a0 == 0) {
                self->ext.stpopup.unk80 = 0;
                self->ext.stpopup.unk90 = 0;
                self->ext.stpopup.unk92 = 0;
                self->step_s++;
            }
            break;
        case 2:
            self->ext.stpopup.unk90 += 3;
            if (self->ext.stpopup.unk90 >= 0x80) {
                self->step_s++;
            }
            prim = self->ext.stpopup.unk88;
            for (i = 0; i < 2; i++) {
                prim->blendMode = 0x75;
                prim->r0 = prim->g0 = prim->b0 = prim->r1 = prim->g1 =
                    prim->b1 = prim->r2 = prim->g2 = prim->b2 = prim->r3 =
                        prim->g3 = prim->b3 = self->ext.stpopup.unk90;
                prim = prim->next;
            }
            break;
        case 3:
            self->ext.stpopup.unk90 -= 2;
            if (self->ext.stpopup.unk90 < 0) {
                self->ext.stpopup.unk90 = 0;
            }
            prim = self->ext.stpopup.unk88;
            for (i = 0; i < 2; i++) {
                prim->blendMode = 0x35;
                prim->r0 = prim->g0 = prim->b0 = prim->r1 = prim->g1 =
                    prim->b1 = prim->r2 = prim->g2 = prim->b2 = prim->r3 =
                        prim->g3 = prim->b3 = self->ext.stpopup.unk90;
                prim = prim->next;
            }
            if (self->ext.stpopup.unk90 != 0) {
                self->ext.stpopup.unk92 = 0x80 - self->ext.stpopup.unk90;
            } else {
                self->ext.stpopup.unk92 += 4;
            }
            if (self->ext.stpopup.unk92 >= 0x80) {
                self->ext.stpopup.unk92 = 0x80;
                self->step_s++;
            }
            prim = self->ext.stpopup.prim;
            for (i = 0; i < 2; i++) {
                prim->blendMode = 0x35;
                prim->r0 = prim->g0 = prim->b0 = prim->r1 = prim->g1 =
                    prim->b1 = prim->r2 = prim->g2 = prim->b2 = prim->r3 =
                        prim->g3 = prim->b3 = self->ext.stpopup.unk92;
                prim = prim->next;
            }
            for (i = 0; i < 2; i++) {
                prim->blendMode = 0x15;
                prim->r0 = prim->g0 = prim->b0 = prim->r1 = prim->g1 =
                    prim->b1 = prim->r2 = prim->g2 = prim->b2 = prim->r3 =
                        prim->g3 = prim->b3 = self->ext.stpopup.unk92;
                prim = prim->next;
            }
            break;
        case 4:
            prim = self->ext.stpopup.unk88;
            prim->blendMode = 8;
            // self->ext.stpopup.unk88 = 8;
            self->ext.stpopup.unk80 = 0x40;
            self->step = 2;
            self->step_s = 0;
            g_CastleFlags[CASTLE_FLAG_BANK + 2] = 1;
            break;
        }
        break;
    case 2:
        self->ext.stpopup.unk80--;
        if (self->ext.stpopup.unk80 == 0) {
            self->step_s = 0;
            self->step = 3;
        }
        break;
    case 3:
        switch (self->step_s) {
        case 0:
            prim = self->ext.stpopup.prim;
            prim = prim->next;
            prim = prim->next;
            for (i = 0; i < 2; i++) {
                prim->blendMode = 0x15;
                prim->r0 = prim->g0 = prim->b0 = prim->r1 = prim->g1 =
                    prim->b1 = prim->r2 = prim->g2 = prim->b2 = prim->r3 =
                        prim->g3 = prim->b3 = self->ext.stpopup.unk92;
                prim = prim->next;
            }
            self->ext.stpopup.unk92 -= 4;
            if (self->ext.stpopup.unk92 < 0) {
                self->ext.stpopup.unk92 = 0;
                self->step_s++;
                break;
            }
            break;
        case 1:
            prim = self->ext.stpopup.prim;
            for (i = 0; i < 4; i++) {
                prim->blendMode = 8;
                prim = prim->next;
            }

            prim = self->ext.stpopup.unk8C;
            for (i = 0; i < 0x14; i++) {
                prim->r0 = 0x80;
                prim->g0 = 0x80;
                prim->b0 = 0x80;
                blendMode = 0x35;
                LOW(prim->r1) = LOW(prim->r0);
                LOW(prim->r2) = LOW(prim->r0);
                LOW(prim->r3) = LOW(prim->r0);
                prim->p1 = i * 4;
                prim->p2 = Random() & 3;
                prim->p3 = 0;
                prim->blendMode = blendMode;
                prim = prim->next;
            }

            for (i = 0; i < 0x14; i++) {
                prim->r0 = 0x80;
                prim->g0 = 0x80;
                prim->b0 = 0x80;
                LOW(prim->r1) = LOW(prim->r0);
                LOW(prim->r2) = LOW(prim->r0);
                LOW(prim->r3) = LOW(prim->r0);
                prim->p1 = -((0x14 - i) * 4);
                prim->p2 = Random() & 3;
                prim->p3 = 0;
                prim->blendMode = 0x35;
                prim = prim->next;
            }

            for (i = 0; i < 0x14; i++) {
                prim->r0 = 0x80;
                prim->g0 = 0x80;
                prim->b0 = 0x80;
                blendMode = 0x35;
                LOW(prim->r1) = LOW(prim->r0);
                LOW(prim->r2) = LOW(prim->r0);
                LOW(prim->r3) = LOW(prim->r0);
                prim->p1 = i * 4;
                prim->p2 = Random() & 3;
                prim->p3 = 0;
                prim->blendMode = blendMode;
                prim = prim->next;
            }

            for (i = 0; i < 0x14; i++) {
                prim->r0 = 0x80;
                prim->g0 = 0x80;
                prim->b0 = 0x80;
                LOW(prim->r1) = LOW(prim->r0);
                LOW(prim->r2) = LOW(prim->r0);
                LOW(prim->r3) = LOW(prim->r0);
                prim->p1 = -((0x14 - i) * 4);
                prim->p2 = Random() & 3;
                prim->p3 = 0;
                prim->blendMode = 0x35;
                prim = prim->next;
            }

            self->ext.stpopup.unk80 = 0x70;
            self->step_s++;
            break;
        case 2:
            prim = self->ext.stpopup.unk8C;
            while (prim != NULL) {
                func_8019A420(prim);
                prim = prim->next;
            }
            self->ext.stpopup.unk80--;
            if (self->ext.stpopup.unk80 == 0) {
                self->step_s++;
            }
            break;
        case 3:
            prim = self->ext.stpopup.unk8C;
            while (prim != NULL) {
                func_8019A420(prim);
                prim = prim->next;
            }
            prim = self->ext.stpopup.unk84;
            prim->y0 += 2;
            prim->y1 = prim->y0;
            prim->y2 -= 2;
            prim->y3 = prim->y2;
            prim->x0 -= 2;
            prim->x1 += 2;
            prim->x2 -= 2;
            prim->x3 += 2;
            if (prim->y2 < prim->y0) {
                DestroyEntity(self);
                return;
            }
            break;
        }
        break;
    }
    FntPrint("t_step   %x\n", self->step);
    FntPrint("t_step_s %x\n", self->step_s);
}
