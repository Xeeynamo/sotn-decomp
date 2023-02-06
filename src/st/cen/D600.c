/*
 * File: D600.c
 * Overlay: CEN
 * Description: Center Cube Area (Final Boss)
 */

#include "common.h"
#include "stage.h"

extern s16 D_80180BBC[];
extern LayoutObject* D_8019C764;
extern LayoutObject* D_8019C768;
extern s16 D_8019D3B4;
extern s16 D_8019D3B6;
extern s32 D_8019D3B8;

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_8018D600);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_8018D6E0);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_8018D89C);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_8018DB18);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_8018DF0C);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_8018DF60);

void func_8018E124(s16 arg0) {
    RECT rect;

    rect.y = (arg0 * 12) + 384;
    rect.w = 64;
    rect.x = 0;
    rect.h = 12;
    ClearImage(&rect, 0, 0, 0);
}

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_8018E180);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_8018E238);

void func_8018E3BC(s32 arg0) {
    D_8019D3B8 = arg0 + 0x100000;
    D_8019D3B6 = 0;
    D_8019D3B4 = 1;
}

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_8018E3E8);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_8018E6C4);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_8018E7C8);

void func_8018F890(s16 arg0) {
    s16 temp_v0 = arg0 - *(s16*)&g_CurrentRoom.height;

    if (temp_v0 > 1) {
        g_CurrentRoom.height++;
    } else if (temp_v0 < -1) {
        g_CurrentRoom.height--;
    } else {
        g_CurrentRoom.height = arg0;
    }
}

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_8018F8EC);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_8018F95C);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_8019007C);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80190374);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_8019040C);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_801904B8);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80190540);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80190A78);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80190B64);

s32 Random(void) {
    g_randomNext = (g_randomNext * 0x01010101) + 1;
    return g_randomNext >> 0x18;
}

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80190E7C);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80191178);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80191280);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80192398);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80192A3C);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80192B00);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80192C18);

void func_80192D30(s16 arg0) {
    while (1) {
        if ((D_8019C764->posX != 0xFFFE) && ((s32)D_8019C764->posX >= arg0)) {
            break;
        }

        D_8019C764++;
    }
}

void func_80192D7C(s16 arg0) {
    while (true) {
        if (((D_8019C764->posX != 0xFFFF) &&
             ((arg0 >= D_8019C764->posX) || (D_8019C764->posX == 0xFFFE)))) {
            break;
        }
        D_8019C764--;
    }
}

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80192DD4);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80192ED0);

void func_80192FE4(s16 arg0) {
    while (true) {
        if ((D_8019C768->posY != 0xFFFE) && ((s32)D_8019C768->posY >= arg0)) {
            break;
        }

        D_8019C768++;
    }
}

void func_80193030(s16 arg0) {
    while (true) {
        if (((D_8019C768->posY != 0xFFFF) &&
             ((arg0 >= D_8019C768->posY) || (!(D_8019C768->posY != 0xFFFE))))) {
            break;
        }
        D_8019C768--;
    }
}

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80193088);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80193184);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80193298);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80193410);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_801934C4);

void CreateEntityFromEntity(u16 objectId, Entity* source, Entity* entity);
INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80193538);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_801935B4);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_8019362C);

void DestroyEntity(Entity* entity) {
    s32 i;
    s32 length;
    u32* ptr;

    if (entity->unk34 & 0x800000) {
        g_api.FreePolygons(entity->firstPolygonIndex);
    }

    ptr = (u32*)entity;
    length = sizeof(Entity) / sizeof(u32);
    for (i = 0; i < length; i++)
        *ptr++ = 0;
}

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_801942D0);

void func_8019434C(Entity* entity) {
    if (entity->objectRoomIndex) {
        u32 value = (entity->objectRoomIndex - 1);
        u16 index = value / 32;
        u16 bit = value % 32;
        g_entityDestroyed[index] |= 1 << bit;
    }
}

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80194394);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_8019444C);

/*
 * Returns the absolute distance from g_CurrentEntity to player in the X Axis
 */
s32 func_80194564(void) {
    s16 xDistance = g_CurrentEntity->posX.i.hi - PLAYER.posX.i.hi;

    if (xDistance < 0) {
        xDistance = -xDistance;
    }
    return xDistance;
}

/*
 * Returns the absolute distance from g_CurrentEntity to player in the Y Axis
 */
s32 func_801945A0(void) {
    s32 yDistance = g_CurrentEntity->posY.i.hi - PLAYER.posY.i.hi;

    if (yDistance < 0) {
        yDistance = -yDistance;
    }
    return yDistance;
}

s16 func_801945D4(void) {
    s16 var_a0 = g_CurrentEntity->posX.i.hi > PLAYER.posX.i.hi;

    if (g_CurrentEntity->posY.i.hi > PLAYER.posY.i.hi) {
        var_a0 |= 2;
    }
    return var_a0;
}

void func_80194618(void) {
    g_CurrentEntity->posX.val += g_CurrentEntity->accelerationX;
    g_CurrentEntity->posY.val += g_CurrentEntity->accelerationY;
}

void func_80194648(void) {
    if (g_CurrentEntity->accelerationY < FALL_TERMINAL_VELOCITY) {
        g_CurrentEntity->accelerationY += FALL_GRAVITY;
    }
}

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80194674);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_801948EC);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", AllocEntity);

s32 func_80194B34(u8 arg0, s16 arg1) { return D_80180BBC[arg0] * arg1; }

s16 func_80194B60(u8 arg0) { return D_80180BBC[arg0]; }

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80194B7C);

u8 func_80194BE8(s16 x, s16 y) { return ((ratan2(y, x) >> 4) + 0x40); }

u8 func_80194C20(Entity* arg0, Entity* arg1) {
    u16 x;
    u16 y;

    x = arg1->posX.i.hi - arg0->posX.i.hi;
    y = arg1->posY.i.hi - arg0->posY.i.hi;

    return func_80194BE8(x, y);
}

u16 func_80194C68(s16 x, s16 y) {
    x -= g_CurrentEntity->posX.i.hi;
    y -= g_CurrentEntity->posY.i.hi;

    return func_80194BE8(x, y);
}

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80194CB0);

void func_80194D08(u16 slope, s16 speed) {
    Entity* entity;
    s32 moveX;
    s32 moveY;

    moveX = rcos(slope) * speed;
    entity = g_CurrentEntity;

    if (moveX < 0) {
        moveX += 15;
    }

    entity->accelerationX = moveX >> 4;

    moveY = rsin(slope) * speed;
    entity = g_CurrentEntity;

    if (moveY < 0) {
        moveY += 15;
    }

    entity->accelerationY = moveY >> 4;
}

u16 func_80194D94(s16 arg0, s16 arg1) { return ratan2(arg1, arg0); }

u16 func_80194DC4(Entity* a, Entity* b) {
    s32 diffX = b->posX.i.hi - a->posX.i.hi;
    s32 diffY = b->posY.i.hi - a->posY.i.hi;
    return ratan2(diffY, diffX);
}

u16 func_80194DFC(s32 x, s32 y) {
    s16 diffX = x - (u16)g_CurrentEntity->posX.i.hi;
    s16 diffY = y - (u16)g_CurrentEntity->posY.i.hi;
    return ratan2(diffY, diffX);
}

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80194E44);

void func_80194EA4(u8 step) {
    Entity* entity = g_CurrentEntity;

    entity->step = step;
    entity->unk2E = 0;
    entity->animationFrameIndex = 0;
    entity->animationFrameDuration = 0;
}

void func_80194EC4(u8 arg0) {
    Entity* entity = g_CurrentEntity;

    entity->unk2E = arg0;
    entity->animationFrameIndex = 0;
    entity->animationFrameDuration = 0;
}

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80194EE0);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", InitializeEntity);

void func_80195070(Entity* entity) {
    if (entity->step == 0) {
        entity->step++;
    }
}

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80195098);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_801951C0);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80195318);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_8019565C);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80195714);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80195798);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_801958F4);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80195974);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80195A50);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80195B68);

void func_80195C0C(void) {
    g_api.PlaySfx(0x67A);
    g_api.func_800FE044(5, 0x8000);
    DestroyEntity(g_CurrentEntity);
}

void func_80195C5C(void) { DestroyEntity(g_CurrentEntity); }

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80195C84);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", EntityExplosion);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_801965F4);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80196698);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80196C80);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80196F30);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80197A00);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80197B28);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80198084);

extern u16 D_80180440[];
void func_80198174(Entity* entity) {
    switch (entity->step) {
    case 0:
        InitializeEntity(D_80180440);
        entity->unk8C.modeU16.unk0 = entity->unk80.entityPtr->objectId;
    case 1:
        if (entity->unk7C.U8.unk0++ >= 5) {
            Entity* newEntity =
                AllocEntity(D_8007D858, &D_8007D858[MaxEntityCount]);
            if (newEntity != NULL) {
                func_80193538(ENTITY_EXPLOSION, entity, newEntity);
                newEntity->objectId = ENTITY_EXPLOSION;
                newEntity->pfnUpdate = EntityExplosion;
                newEntity->subId = entity->subId;
            }
            entity->unk7C.U8.unk0 = 0;
        }
        entity->posX.i.hi = entity->unk80.entityPtr->posX.i.hi;
        entity->posY.i.hi = entity->unk80.entityPtr->posY.i.hi;
        if (entity->unk80.entityPtr->objectId != entity->unk8C.modeU16.unk0) {
            DestroyEntity(entity);
        }
        break;
    }
}

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80198284);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_801983B4);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_8019849C);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_8019858C);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80198680);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_801988B0);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_801989AC);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80198F2C);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_8019902C);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_801990F8);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_801991C0);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80199278);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80199450);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80199A30);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_8019A130);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_8019A328);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_8019A420);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_8019A5F0);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_8019B274);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_8019B608);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_8019BAB8);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_8019BBA4);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_8019BED4);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_8019C2BC);

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

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_8019C4B8);

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

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_8019C6A0);
