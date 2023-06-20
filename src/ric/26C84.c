#include "ric.h"

void func_80162C84(Entity* entity) {
    switch (entity->step) {
    case 0:
        entity->flags =
            0x100000 | FLAG_UNK_04000000 | FLAG_UNK_10000 | FLAG_UNK_08000000;
        entity->facing = 1;
        entity->unk5A = 0x66;
        entity->zPriority = PLAYER.zPriority - 8;
        entity->palette = 0x8149;
        entity->animSet = -0x7FED;
        func_8015C920(&D_80154ED4);
        entity->accelerationX = -0x1C000;
        entity->posY.i.hi = 0xBB;
        entity->posX.i.hi = 0x148;
        entity->ext.generic.unk7E.modeU16 = 0;
        entity->step++;
        break;

    case 1:
        if (LOW(entity->animFrameIdx) == 0x10000) {
            g_api.PlaySfx(0x882);
        }
        if (LOW(entity->animFrameIdx) == 0x10004) {
            g_api.PlaySfx(0x883);
        }

        entity->posX.val += entity->accelerationX;
        if (((s16)entity->ext.generic.unk7E.modeU16 == 0) &&
            (entity->posX.i.hi < 256)) {
            g_api.PlaySfx(0x87D);
            entity->ext.generic.unk7E.modeU16++;
        }
        if (entity->posX.i.hi < 0xE0) {
            func_8015C920(&D_80154EF8);
            entity->accelerationX = 0;
            entity->step++;
            func_801606BC(entity, 0x40000, 0);
        }
        break;

    case 2:
        if (entity->animFrameIdx == 16) {
            g_api.PlaySfx(0x87E);
            entity->ext.generic.unk7C.s = 0x80;
            entity->step++;
        }
        break;

    case 3:
        entity->ext.generic.unk7C.s--;
        if ((entity->ext.generic.unk7C.s) == 0) {
            func_801606BC(entity, 0x1E, 0);
            entity->step++;
        }
        break;

    case 4:
        break;
    }
}

const u32 rodataPadding_801569E4 = 0;

// same as DRA/func_8011BD48
bool func_80162E9C(Entity* entity) {
    s32 i = 16;
    s16 objId = entity->objectId;
    s16 subId = entity->subId;
    Entity* e;

    for (e = &g_Entities[i]; i < 64; i++, e++) {
        if ((objId == e->objectId) && (subId == e->subId) && (e != entity)) {
            return true;
        }
    }

    return false;
}

INCLUDE_ASM("asm/us/ric/nonmatchings/26C84", func_80162EF8);

void func_801641A0(Entity* entity) {
    POLY_GT4* poly;
    s16 firstPolygonIndex;

    entity->posX.i.hi = PLAYER.posX.i.hi;
    entity->posY.i.hi = PLAYER.posY.i.hi - 8;
    switch (entity->step) {
    case 0:
        firstPolygonIndex = g_api.AllocPrimitives(4, 1);
        entity->firstPolygonIndex = firstPolygonIndex;
        if (firstPolygonIndex != -1) {
            entity->ext.generic.unk7C.s = 16;
            entity->ext.generic.unk7E.modeU16 = 12;
            poly = &g_PrimBuf[entity->firstPolygonIndex];
            poly->u0 = poly->u2 = 64;
            poly->v0 = poly->v1 = 192;
            poly->u1 = poly->u3 = 127;
            poly->v2 = poly->v3 = 255;
            poly->r0 = poly->g0 = poly->b0 = poly->r1 = poly->g1 = poly->b1 =
                poly->r2 = poly->g2 = poly->b2 = poly->r3 = poly->g3 =
                    poly->b3 = 128;
            poly->tpage = 0x1A;
            poly->clut = 0x160;
            poly->pad2 = PLAYER.zPriority + 8;
            poly->pad3 = 0x35;
            entity->flags = 0x40000 | FLAG_UNK_04000000 | FLAG_FREE_POLYGONS;
            entity->step++;
            goto def;
        } else {
            func_80156C60(entity);
            break;
        }

    case 1:
        entity->ext.generic.unk7C.s += 2;
        entity->ext.generic.unk7E.modeU16 += 2;
        if (entity->ext.generic.unk7C.s >= 57) {
            func_80156C60(entity);
            break;
        }

    default:
    def:
        poly = &g_PrimBuf[entity->firstPolygonIndex];
        poly->x0 = entity->posX.i.hi - entity->ext.generic.unk7C.s;
        poly->y0 = entity->posY.i.hi - entity->ext.generic.unk7E.modeU16;
        poly->x1 = entity->posX.i.hi + entity->ext.generic.unk7C.s;
        poly->y1 = entity->posY.i.hi - entity->ext.generic.unk7E.modeU16;
        poly->x2 = entity->posX.i.hi - entity->ext.generic.unk7C.s;
        poly->y2 = entity->posY.i.hi + entity->ext.generic.unk7E.modeU16;
        poly->x3 = entity->posX.i.hi + entity->ext.generic.unk7C.s;
        poly->y3 = entity->posY.i.hi + entity->ext.generic.unk7E.modeU16;
        if (poly->b3 >= 12) {
            poly->b3 += 244;
        }
        poly->r0 = poly->g0 = poly->b0 = poly->r1 = poly->g1 = poly->b1 =
            poly->r2 = poly->g2 = poly->b2 = poly->r3 = poly->g3 = poly->b3;
    }
}

INCLUDE_ASM("asm/us/ric/nonmatchings/26C84", func_80164444);

INCLUDE_ASM("asm/us/ric/nonmatchings/26C84", func_80164DF8);

INCLUDE_ASM("asm/us/ric/nonmatchings/26C84", func_801656B0);

void func_80165DD8(POLY_GT4* poly, s32 colorIntensity, s32 y, s32 radius,
                   bool arg4) {
    s16 top = y - radius;
    s16 bottom = y + radius;
    s32 colorChannel;

    poly->y0 = poly->y1 = top;
    poly->y2 = poly->y3 = bottom;

    if (poly->y0 < 0) {
        poly->y0 = poly->y1 = 0;
    }

    if (poly->y0 > 240) {
        poly->y2 = poly->y3 = 240;
    }

    if (arg4 == 0) {
        colorChannel = colorIntensity * D_80155368[0];
        if (colorChannel < 0) {
            colorChannel += 255;
        }
        poly->r1 = poly->r3 = (u32)colorChannel >> 8;

        colorChannel = colorIntensity * D_80155368[1];
        if (colorChannel < 0) {
            colorChannel += 255;
        }
        poly->g1 = poly->g3 = (u32)colorChannel >> 8;

        colorChannel = colorIntensity * D_80155368[2];
        if (colorChannel < 0) {
            colorChannel += 255;
        }
        poly->b1 = poly->b3 = (u32)colorChannel >> 8;

        colorChannel = colorIntensity * D_80155368[3];
        if (colorChannel < 0) {
            colorChannel += 255;
        }
        poly->r0 = poly->r2 = (u32)colorChannel >> 8;

        colorChannel = colorIntensity * D_80155368[4];
        if (colorChannel < 0) {
            colorChannel += 255;
        }
        poly->g0 = poly->g2 = (u32)colorChannel >> 8;

        colorChannel = colorIntensity * D_80155368[5];
    } else {
        colorChannel = colorIntensity * D_80155368[0];
        if (colorChannel < 0) {
            colorChannel += 255;
        }
        poly->r1 = poly->r3 = (u32)colorChannel >> 8;

        colorChannel = colorIntensity * D_80155368[1];
        if (colorChannel < 0) {
            colorChannel += 255;
        }
        poly->g1 = poly->g3 = (u32)colorChannel >> 8;

        colorChannel = colorIntensity * D_80155368[2];
        if (colorChannel < 0) {
            colorChannel += 255;
        }
        poly->b1 = poly->b3 = (u32)colorChannel >> 8;

        colorChannel = colorIntensity * D_80155368[6];
        if (colorChannel < 0) {
            colorChannel += 255;
        }
        poly->r0 = poly->r2 = (u32)colorChannel >> 8;

        colorChannel = colorIntensity * D_80155368[7];
        if (colorChannel < 0) {
            colorChannel += 255;
        }
        poly->g0 = poly->g2 = (u32)colorChannel >> 8;
        colorChannel = colorIntensity * D_80155368[8];
    }
    if (colorChannel < 0) {
        colorChannel += 255;
    }
    poly->b0 = poly->b2 = (u32)colorChannel >> 8;
}

void func_80166024() {
    PLAYER.palette = 0x815E;
    PLAYER.blendMode = 0x70;
}

void func_80166044() {
    PLAYER.palette = 0x8120;
    PLAYER.blendMode = 0;
}

INCLUDE_ASM("asm/us/ric/nonmatchings/26C84", func_80166060);

INCLUDE_ASM("asm/us/ric/nonmatchings/26C84", func_80166784);

void func_8016779C(Entity* entity) {
    if (g_Player.unk46 == 0) {
        func_80156C60(entity);
        return;
    }

    entity->facing = PLAYER.facing;
    if (entity->step == 0) {
        entity->flags = 0x60000 | FLAG_UNK_04000000 | FLAG_UNK_10000;
        entity->animSet = -0x7FEE;
        entity->unk5A = 0x46;
        entity->palette = 0x8120;
        entity->zPriority = PLAYER.zPriority + 2;
    }

    if (PLAYER.step == 2) {
        if (PLAYER.facing != 0) {
            entity->animCurFrame = D_80155CCC[D_80175080];
        } else {
            entity->animCurFrame = D_80155CB8[D_80175080];
        }
    } else if (PLAYER.step == 0) {
        if (PLAYER.facing != 0) {
            entity->animCurFrame = D_80155CF4[D_80175080];
        } else {
            entity->animCurFrame = D_80155CE0[D_80175080];
        }
    } else if (PLAYER.facing != 0) {
        entity->animCurFrame = D_80155D1C[D_80175080];
    } else {
        entity->animCurFrame = D_80155D08[D_80175080];
    }

    entity->posX.val = g_Entities->posX.val;
    entity->posY.val = PLAYER.posY.val;
}

/**
 * TODO: !FAKE
 * Needs to be refactored
 */
void func_80167964(Entity* entity) {
    /**
     * 0x5E was originally 0xBC in mips2c output
     * suggesting the size of the Entity struct
     */
    if (g_Player.unk46 != 0) {
        if (entity->step == 0) {
            entity->flags = 0x60000 | FLAG_UNK_04000000 | FLAG_UNK_10000;
        }
        if (!(entity->subId & 0xFF00)) {
            *(&PLAYER.palette +
              (*(&D_80155D30 + (entity->animFrameDuration)) * 0x5E)) = 0x8140;
        }
        *(&PLAYER.ext.generic.unkA4 +
          (*(&D_80155D30 + (entity->animFrameDuration)) * 0x5E)) = 4;
        entity->animFrameDuration++;
        if (entity->animFrameDuration == 0xF) {
            func_80156C60(entity);
        }
    } else {
        func_80156C60(entity);
    }
}

void func_80167A58(void) {}

void func_80167A60(void) {}

void func_80167A68(void) {}

INCLUDE_ASM("asm/us/ric/nonmatchings/26C84", func_80167A70);

INCLUDE_ASM("asm/us/ric/nonmatchings/26C84", func_80167EC4);

INCLUDE_ASM("asm/us/ric/nonmatchings/26C84", func_801682B4);

s32 func_8016840C(s16 x, s16 y) {
    Collider collider;
    u16 temp;

    if (g_CurrentEntity->accelerationX != 0) {
        g_api.CheckCollision(g_CurrentEntity->posX.i.hi + y,
                             g_CurrentEntity->posY.i.hi + x, &collider, 0);
        if (g_CurrentEntity->accelerationX > 0) {
            temp = collider.unk14;
        } else {
            temp = collider.unk1C;
        }
        if (!(collider.effects & EFFECT_UNK_0002)) {
            return 0;
        }
    } else {
        return 0;
    }
    g_CurrentEntity->posX.i.lo = 0;
    g_CurrentEntity->posX.i.hi += temp;
    return 2;
}

INCLUDE_ASM("asm/us/ric/nonmatchings/26C84", func_801684D8);

INCLUDE_ASM("asm/us/ric/nonmatchings/26C84", func_80168A20);

INCLUDE_ASM("asm/us/ric/nonmatchings/26C84", func_8016902C);

INCLUDE_ASM("asm/us/ric/nonmatchings/26C84", func_80169470);

INCLUDE_ASM("asm/us/ric/nonmatchings/26C84", func_80169704);

void func_80169C10(Entity* entity) {
    POLY_GT4* poly;
    s16 firstPolygonIndex;
    s32 PosX = 8;
    s32 PosY = 4;

    switch (entity->step) {
    case 0:
        firstPolygonIndex = g_api.AllocPrimitives(4, 1);
        entity->firstPolygonIndex = firstPolygonIndex;
        if (firstPolygonIndex != -1) {
            entity->flags = FLAG_UNK_08000000 | FLAG_FREE_POLYGONS;
            entity->accelerationY = 0x8000;
            entity->posX.i.hi =
                ((u16)entity->posX.i.hi - PosX) + (rand() & 0xF);
            entity->posY.i.hi =
                ((u16)entity->posY.i.hi - PosY) + (rand() & 0xF);
            poly = &g_PrimBuf[entity->firstPolygonIndex];
            poly->clut = 0x1B0;
            poly->tpage = 0x1A;
            poly->b0 = 0;
            poly->b1 = 0;
            poly->pad2 = entity->zPriority;
            poly->pad2 = poly->pad2 + 4;
            poly->pad3 = 0x31;
            func_8015FDB0(poly, entity->posX.i.hi, entity->posY.i.hi);
            entity->step++;
        } else {
            func_80156C60(entity);
        }
        break;

    default:
        entity->posY.val += entity->accelerationY;
        poly = &g_PrimBuf[entity->firstPolygonIndex];
        if (func_8015FDB0(poly, entity->posX.i.hi, entity->posY.i.hi) != 0) {
            func_80156C60(entity);
        }
        break;
    }
}

void func_80169D74(Entity* entity) {
    Multi temp;
    s16* ptr;

    switch (entity->step) {
    case 0:
        entity->flags = FLAG_UNK_04000000 | FLAG_UNK_08000000;
        entity->ext.generic.unk84.unk =
            entity->ext.generic.unk8C.entityPtr->ext.generic.unk84.unk;
        entity->animSet = -0x7FEF;
        entity->animCurFrame = D_80155E68[entity->subId];
        entity->unk5A = 0x66;
        entity->palette = 0x81B0;
        entity->blendMode = 0x10;
        entity->facing = PLAYER.facing;
        entity->zPriority = PLAYER.zPriority;
        entity->unk19 = 4;
        entity->unk1E = 0xC00;
        entity->step++;
        break;

    case 1:
        entity->unk1E -= 0x80;
        if (entity->ext.generic.unk8C.entityPtr->step == 7) {
            entity->step++;
            entity->ext.generic.unk7C.s = (entity->subId + 1) * 4;
        }
        break;

    case 2:
        entity->unk1E -= 0x80;
        entity->ext.generic.unk7C.s--;
        if (entity->ext.generic.unk7C.s == 0) {
            func_80156C60(entity);
            return;
        }
        break;
    }
    temp = entity->ext.generic.unk84;
    ptr = temp.unk + ((u16)entity->ext.generic.unk80.modeS16.unk0 * 4);
    entity->posX.i.hi = ptr[0] - g_Camera.posX.i.hi;
    entity->posY.i.hi = ptr[1] - g_Camera.posY.i.hi;
    entity->ext.generic.unk80.modeS16.unk0 =
        (entity->ext.generic.unk80.modeS16.unk0 + 1) & 0x3F;
}

INCLUDE_ASM("asm/us/ric/nonmatchings/26C84", func_80169F04);

INCLUDE_ASM("asm/us/ric/nonmatchings/26C84", func_8016A26C);

INCLUDE_ASM("asm/us/ric/nonmatchings/26C84", func_8016A974);

INCLUDE_ASM("asm/us/ric/nonmatchings/26C84", func_8016B0C0);

void func_8016B8E8(s32 arg0) {
    g_CurrentEntity->ext.generic.unk7C.s =
        (arg0 << 0x10 >> 0xF) - g_CurrentEntity->ext.generic.unk7C.s;
    if (g_CurrentEntity->ext.generic.unk80.modeS16.unk2 == 0) {
        g_CurrentEntity->ext.generic.unk80.modeS16.unk0++;
        g_CurrentEntity->ext.generic.unk80.modeS16.unk2++;
    }
}

void func_8016B92C(s16 arg0) {
    if (g_CurrentEntity->ext.generic.unk80.modeS16.unk2 == 0) {
        g_CurrentEntity->ext.generic.unk7C.s =
            (arg0 * 2) - g_CurrentEntity->ext.generic.unk7C.s;
        g_CurrentEntity->ext.generic.unk80.modeS16.unk0++;
        g_CurrentEntity->ext.generic.unk80.modeS16.unk2++;
    }
}

INCLUDE_ASM("asm/us/ric/nonmatchings/26C84", func_8016B97C);

INCLUDE_ASM("asm/us/ric/nonmatchings/26C84", func_8016C1BC);

s32 func_8016C6C4(Unkstruct_80128BBC* arg0, u8 value) {
    u8 ret = 0;
    s32 i;
    s32 j;
    Unkstruct_80128BBC_Sub* temp = arg0->unk04;

    for (i = 0; i < 4; i++, temp++) {
        for (j = 0; j < 3; j++) {
            temp->unk00[j] -= value;

            if (temp->unk00[j] < 16) {
                temp->unk00[j] = 16;
            } else {
                ret |= 1;
            }
        }
    }
    return ret;
}

INCLUDE_ASM("asm/us/ric/nonmatchings/26C84", func_8016C734);

INCLUDE_ASM("asm/us/ric/nonmatchings/26C84", func_8016CC74);

void func_8016D328(Entity* entity) {
    s16 firstPolygonIndex;
    s32 acceleration;

    switch (entity->step) {
    case 0:
        firstPolygonIndex = g_api.AllocPrimitives(4, 1);
        entity->firstPolygonIndex = firstPolygonIndex;
        if (firstPolygonIndex != -1) {
            entity->flags = FLAG_UNK_08000000 | FLAG_FREE_POLYGONS;
            entity->posX.val =
                entity->ext.generic.unk8C.entityPtr->ext.generic.unk84.unk;
            entity->posY.val =
                entity->ext.generic.unk8C.entityPtr->ext.generic.unk88.unk;
            entity->facing = entity->ext.generic.unk8C.entityPtr->ext.generic
                                 .unk8C.modeU16.unk0;
            entity->ext.generic.unkB0 = 0x18;
            func_8015FAB8(entity);
            entity->unk5A = 0x79;
            entity->animSet = 0xE;
            entity->palette = 0x819E;
            entity->unk4C = &D_80155EA8;
            entity->blendMode = 0x30;
            entity->unk19 = 8;
            entity->unk6C = 0x60;
            entity->hitboxWidth = 8;
            entity->hitboxHeight = 8;
            entity->flags |= 0x100000;
            acceleration = (rand() % 512) + 0x300;
            entity->accelerationX = rcos(acceleration) * 32;
            entity->accelerationY = -(rsin(acceleration) * 32);
            entity->step++;
        } else {
            func_80156C60(entity);
        }
        break;

    case 1:
        if (++entity->ext.generic.unk7C.s >= 39) {
            func_80156C60(entity);
        } else {
            entity->posX.val += entity->accelerationX;
            entity->posY.val += entity->accelerationY;
        }
        break;
    }
}

INCLUDE_ASM("asm/us/ric/nonmatchings/26C84", func_8016D4D8);

void func_8016D920(Entity* entity) {
    switch (entity->step) {
    case 0:
        entity->flags = FLAG_UNK_04000000;
        entity->ext.generic.unkB0 = 0x19;
        func_8015FAB8(entity);
        entity->hitboxWidth = 4;
        entity->hitboxHeight = 4;
        entity->step++;
        break;

    case 1:
        if (++entity->ext.generic.unk7C.s >= 4) {
            func_80156C60(entity);
        }
        break;
    }
}

INCLUDE_ASM("asm/us/ric/nonmatchings/26C84", func_8016D9C4);

INCLUDE_ASM("asm/us/ric/nonmatchings/26C84", func_8016DF74);