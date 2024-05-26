#include "np3.h"

u8 func_801C02F4(s16* arg0, u8 facing) {
    u8 ret = 0;
    Collider collider;
    s16 posX, posY;

    while (*arg0 != 0xFF) {
        ret <<= 1;

        posX = facing ? (g_CurrentEntity->posX.i.hi + *arg0++)
                      : (g_CurrentEntity->posX.i.hi - *arg0++);
        posY = g_CurrentEntity->posY.i.hi + *arg0++;

        g_api.CheckCollision(posX, posY, &collider, 0);

        if (collider.effects & EFFECT_SOLID) {
            ret |= 1;
        }
    }

    return ret;
}

void func_801C03E4(Entity* entity) {
    switch (entity->step) {
    case 0:
        InitializeEntity(D_80180A78);
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

void func_801C04F4(
    Entity* self, u8 count, u8 params, s32 x, s32 y, u8 arg5, s16 xGap) {
    Entity* newEntity;
    s32 i;
    s16 newX = self->posX.i.hi + x;
    s16 newY = self->posY.i.hi + y;

    for (i = 0; i < count; i++) {
        newEntity = AllocEntity(&g_Entities[160], &g_Entities[192]);
        if (newEntity != NULL) {
            newEntity->posX.i.hi = newX + xGap * i;
            newEntity->posY.i.hi = newY;
            newEntity->entityId = E_ID_14;
            newEntity->pfnUpdate = func_801C070C;
            newEntity->params = params;
            newEntity->ext.generic.unk94 = arg5 + i;
            newEntity->rotY = newEntity->rotX = D_80181FA4[arg5 + i];
            newEntity->drawFlags = FLAG_DRAW_ROTX | FLAG_DRAW_ROTY;
            newEntity->zPriority = self->zPriority + 1;
        }
    }
}

#include "../entity_unkId15_spawner.h"

void func_801C070C(Entity* entity) {
    if (entity->step == 0) {
        entity->velocityY = D_80181FDC[entity->ext.generic.unk94];
        entity->flags = FLAG_UNK_2000 | FLAG_UNK_04000000 | FLAG_UNK_08000000;
        entity->palette = 0x8195;
        entity->animSet = ANIMSET_DRA(2);
        entity->animCurFrame = D_80181FF4[entity->params];
        entity->drawMode = DRAW_TPAGE;
        entity->step++;
    } else {
        entity->animFrameDuration++;
        entity->posY.val -= entity->velocityY;

        if (!(entity->animFrameDuration & 1)) {
            entity->animCurFrame++;
        }

        if (D_80181FF8[entity->params] < (s32)entity->animFrameDuration) {
            DestroyEntity(entity);
        }
    }
}

void EntityUnkId15(Entity* entity) {
    u16 temp_v0;
    u32 temp2;

    if (entity->step == 0) {
        entity->flags = FLAG_UNK_2000 | FLAG_UNK_04000000 | FLAG_UNK_08000000;
        entity->palette = 0x8195;
        entity->animSet = ANIMSET_DRA(5);
        entity->animCurFrame = 1;
        entity->drawMode = DRAW_TPAGE;
        entity->drawFlags = FLAG_DRAW_ROTX | FLAG_DRAW_ROTY;
        temp_v0 = D_80181FB4[entity->params];
        entity->rotX = temp_v0;
        entity->rotY = temp_v0;
        temp2 = D_80181FC4[entity->params];
        entity->step += 1;
        entity->velocityY = temp2;
    } else {
        entity->animFrameDuration++;
        entity->posY.val -= entity->velocityY;

        if (!(entity->animFrameDuration & 1)) {
            entity->animCurFrame++;
        }

        if (entity->animFrameDuration >= 0x25) {
            DestroyEntity(entity);
        }
    }
}

void func_801C08F0(Entity* self) {
    s16 primIndex;
    Primitive* prim;

    switch (self->step) {
    case 0:
        InitializeEntity(g_InitializeEntityData0);
        primIndex = g_api.AllocPrimitives(PRIM_LINE_G2, 1);
        if (primIndex != -1) {
            prim = &g_PrimBuf[primIndex];
            self->primIndex = primIndex;
            self->hitboxState = 0;
            *(s32*)&self->ext.generic.unk7C = prim;
            self->flags |= FLAG_HAS_PRIMS;
            while (prim != NULL) {
                prim->x0 = prim->x1 = self->posX.i.hi;
                prim->y0 = prim->y1 = self->posY.i.hi;
                prim->r0 = 64;
                prim->r1 = 0;
                prim->g0 = 64;
                prim->g1 = 0;
                prim->b0 = 255;
                prim->b1 = 16;
                prim->priority = self->zPriority + 1;
                prim->drawMode |= 0x37;
                prim = prim->next;
            }
        }
        break;

    case 1:
        prim = (Primitive*)*(s32*)&self->ext.generic.unk7C.s;
        if (func_801C02F4(&D_80182000, 0) & 255) {
            prim->y1 += 2;
            if (self->step_s == 0) {
                func_801C04F4(self, 1, 2, 0, 0, 3, 0);
                self->step_s = 1;
            }
        } else {
            self->velocityY += 0x400;
            self->posY.val += self->velocityY;
            if ((prim->y0 - prim->y1) >= 9) {
                prim->y1 = prim->y0 - 8;
            }
        }

        prim->x0 = self->posX.i.hi;
        prim->x1 = self->posX.i.hi;
        prim->y0 = self->posY.i.hi;

        if (prim->y0 < prim->y1) {
            g_api.FreePrimitives(self->primIndex);
            DestroyEntity(self);
        }
        break;
    }
}

bool func_801C0B20(Point16* unk) {
    Collider collider;

    FallEntity();
    g_CurrentEntity->posX.val += g_CurrentEntity->velocityX;
    g_CurrentEntity->posY.val += g_CurrentEntity->velocityY;

    if (g_CurrentEntity->velocityY >= 0) {
        s16 posX = g_CurrentEntity->posX.i.hi;
        s16 posY = g_CurrentEntity->posY.i.hi;
        posX += unk->x;
        posY += unk->y;
        g_api.CheckCollision(posX, posY, &collider, 0);
        if (collider.effects & EFFECT_SOLID) {
            g_CurrentEntity->posY.i.hi += collider.unk18;
            g_CurrentEntity->velocityY = -g_CurrentEntity->velocityY / 2;
            if (g_CurrentEntity->velocityY > FIX(-1.0)) {
                return true;
            }
        }
    }
    return false;
}

u8 func_801C0C1C(s32 arg0) {
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

#include "../entity_intense_explosion.h"

void func_801C129C(Entity* entity) {
    if (entity->step == 0) {
        InitializeEntity(g_InitializeEntityData0);
        entity->unk6C = 0xF0;
        entity->rotX = 0x1A0;
        entity->rotY = 0x1A0;
        entity->animSet = ANIMSET_DRA(8);
        entity->animCurFrame = 1;
        entity->zPriority += 0x10;

        if (entity->params != 0) {
            entity->palette = entity->params;
        } else {
            entity->palette = 0x8160;
        }

        entity->step++;
    } else {
        MoveEntity();
        if (!AnimateEntity(D_80182008, entity)) {
            DestroyEntity(entity);
        }
    }
}

void func_801C1368(u16 entityId, Entity* src, Entity* dst) {
    DestroyEntity(dst);
    dst->entityId = entityId;
    dst->pfnUpdate = PfnEntityUpdates[entityId - 1];
    dst->posX.i.hi = src->posX.i.hi;
    dst->posY.i.hi = src->posY.i.hi;
    dst->unk5A = src->unk5A;
    dst->zPriority = src->zPriority;
    dst->animSet = src->animSet;
    dst->flags = FLAG_UNK_2000 | FLAG_UNK_01000000 | FLAG_UNK_04000000 |
                 FLAG_UNK_08000000 | FLAG_DESTROY_IF_BARELY_OUT_OF_CAMERA |
                 FLAG_DESTROY_IF_OUT_OF_CAMERA;

    if (src->palette & 0x8000) {
        dst->palette = src->hitEffect;
    } else {
        dst->palette = src->palette;
    }
}

void func_801C1848(void) {
    s32 temp_s3;
    s8 temp_s4;
    Entity* entity;
    s32 i;

    temp_s4 = Random() & 3;
    temp_s3 = ((Random() & 0xF) << 8) - 0x800;

    for (i = 0; i < 6; i++) {
        entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (entity != NULL) {
            CreateEntityFromEntity(E_EXPLOSION, g_CurrentEntity, entity);
            entity->ext.generic.unk84.U8.unk1 = 6 - i;
            entity->ext.generic.unk80.modeS16.unk0 = temp_s3;
            entity->ext.generic.unk84.U8.unk0 = temp_s4;
        }
    }
}

void func_801C14E8(Entity* self) {
    s32 velocityX;
    s32 velocityY;
    s32 temp;

    if (self->step == 0) {
        InitializeEntity(g_InitializeEntityData0);
        self->animSet = ANIMSET_DRA(2);
        self->palette = 0x81B6;
        self->unk6C = 0x70;
        self->zPriority = 192;
        self->drawFlags |= 0xC;
        self->drawMode |= 0x30;

        switch (self->ext.generic.unk84.U8.unk0) {
        case 1:
            if (self->ext.generic.unk84.U8.unk1 >= 4) {
                self->ext.generic.unk84.U8.unk1 += 253;
                self->ext.generic.unk80.modeS16.unk0 -= 0x800;
            }
            break;

        case 2:
            self->ext.generic.unk80.modeS16.unk0 +=
                self->ext.generic.unk84.U8.unk1 * 192;
            break;
        }

        self->rotZ = self->ext.generic.unk80.modeS16.unk0 &= 0xFFF;
        temp = (self->ext.generic.unk84.U8.unk1 * 320) / 24;
        self->velocityX = temp * rsin(self->ext.generic.unk80.modeS16.unk0);
        self->velocityY = -(temp * rcos(self->ext.generic.unk80.modeS16.unk0));
    }

    if (self->animFrameIdx >= 13) {
        velocityX = self->velocityX;
        if (velocityX < 0) {
            velocityX += 3;
        }

        velocityY = self->velocityY;
        self->velocityX = (velocityX >> 2) * 3;
        if (velocityY < 0) {
            velocityY += 3;
        }
        self->velocityY = (velocityY >> 2) * 3;
    }

    MoveEntity();

    if (AnimateEntity(D_80181EA8, self) == 0) {
        DestroyEntity(self);
    }
}

INCLUDE_ASM("st/np3/nonmatchings/402F4", func_801C16C0);

INCLUDE_ASM("st/np3/nonmatchings/402F4", func_801C1CA0);

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
        g_ClutIds[offset + i] = GetClut(bufRect.x, bufRect.y);
    }
}

void func_801C2598(s16 sfxId) {
    s32 var_a3;
    s32 temp_v0_2;
    s16 var_a2;
    s32 y;
    s16 var_v0_4;
    s16 var_v1;

    var_a3 = g_CurrentEntity->posX.i.hi - 128;
    var_a2 = (abs(var_a3) - 32) >> 5;
    if (var_a2 > 8) {
        var_a2 = 8;
    } else if (var_a2 < 0) {
        var_a2 = 0;
    }
    if (var_a3 < 0) {
        var_a2 = -var_a2;
    }
    var_a3 = abs(var_a3) - 96;
    y = g_CurrentEntity->posY.i.hi - 128;
    temp_v0_2 = abs(y) - 112;
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

#include "../entity_stage_name_popup.h"

// The white flying orbs of energy that Alucard summons as part of the Soul
// Steal spell
void EntitySoulStealOrb(Entity* self) {
    Primitive* prim;
    s32 primIndex;
    u16* temp_d;
    u16 temp_e;
    s32 temp_a;
    s32 temp_b;
    u16 angle;
    switch (self->step) {
    case 0:
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        InitializeEntity(g_InitializeData0);
        g_PrimBuf[primIndex].drawMode = DRAW_HIDE;
        self->primIndex = primIndex;
        self->animSet = ANIMSET_DRA(0);
        self->flags |= FLAG_HAS_PRIMS;
        angle = func_801BD034(self, &g_Entities[PLAYER_CHARACTER]);
        temp_a = self->posY.i.hi < 113;
        temp_b = temp_a ^ 1;
        if (self->posX.i.hi < g_Entities[PLAYER_CHARACTER].posX.i.hi) {
            temp_b = temp_a;
        }
        if (temp_b & 0xFFFF) {
            self->ext.soulStealOrb.angle = angle - D_8018205C[Random() & 7];
        } else {
            angle += D_8018205C[Random() & 7];
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
            self->rotX = (self->rotY += 0x10);
        }
        if (self->ext.soulStealOrb.unk7E < 0x200) {
            self->ext.soulStealOrb.unk7E += 2;
        }
        if (self->ext.soulStealOrb.unk80 < 0x800) {
            self->ext.soulStealOrb.unk80 += 4;
        }
        self->ext.soulStealOrb.angle = func_801BD0B4(
            self->ext.soulStealOrb.unk7E, (u16)self->ext.soulStealOrb.angle,
            0xffff & func_801BD034(self, &g_Entities[PLAYER_CHARACTER]));
        UnkEntityFunc0(self->ext.soulStealOrb.angle & 0xFFFF,
                       self->ext.soulStealOrb.unk80);
        MoveEntity(self);
        prim = &g_PrimBuf[self->primIndex];
        AnimateEntity(&D_801820CC, self);
        angle = (float)((u32)self);
        prim->tpage = 0x18;
        prim->clut = 0x194;
        temp_d = &D_8018206C[(u16)((8 * ((u16)self->animCurFrame)) - 8)];
        prim->x0 = (prim->x2 = self->posX.i.hi + (*(temp_d++)));
        prim->y0 = (prim->y1 = self->posY.i.hi + (*(temp_d++)));
        prim->x1 = (prim->x3 = prim->x0 + (*(temp_d++)));
        prim->y2 = (prim->y3 = prim->y0 + (*(temp_d++)));
        prim->u0 = (prim->u2 = *(temp_d++));
        prim->v0 = (prim->v1 = *(temp_d++));
        prim->u1 = (prim->u3 = *(temp_d++));
        prim->v2 = (prim->v3 = *(temp_d++));
        prim->priority = self->zPriority;
        prim->drawMode = DRAW_DEFAULT;
        break;
    }
}

#include "../entity_enemy_blood.h"

extern ObjInit2 D_801820F0[];
void EntityRoomForeground(Entity* entity) {
    ObjInit2* objInit = &D_801820F0[entity->params];

    if (entity->step == 0) {
        InitializeEntity(g_eInitGeneric2);
        entity->animSet = objInit->animSet;
        entity->zPriority = objInit->zPriority;
        entity->unk5A = objInit->unk4.s;
        entity->palette = objInit->palette;
        entity->drawFlags = objInit->drawFlags;
        entity->drawMode = objInit->drawMode;
        if (objInit->unkC != 0) {
            entity->flags = objInit->unkC;
        }
        if (entity->params >= 5) {
            entity->rotZ = 0x800;
            entity->drawFlags |= 4;
        }
    }
    AnimateEntity(objInit->unk10, entity);
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

    g_unkGraphicsStruct.unk14 = g_api.AllocPrimitives(PRIM_SPRT, charcount + 4);
    if (g_unkGraphicsStruct.unk14 == -1) {
        return;
    }
#undef charcount

    prim = &g_PrimBuf[g_unkGraphicsStruct.unk14];
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
    prim->drawMode = 0x11;
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
    prim->drawMode = DRAW_DEFAULT;
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
    prim->drawMode = DRAW_DEFAULT;
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
    prim->drawMode = DRAW_DEFAULT;

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
            prim->drawMode = DRAW_DEFAULT;
            prim->y0 = 0xD4;
            prim = prim->next;
            xpos += 8;
        } else {
            xpos += 4;
        }
    }
#undef xpos
    g_unkGraphicsStruct.unk10 = 0x130;
}

INCLUDE_ASM("st/np3/nonmatchings/402F4", func_801C4144);

// ID 0x2C
INCLUDE_ASM("st/np3/nonmatchings/402F4", func_801C424C);
