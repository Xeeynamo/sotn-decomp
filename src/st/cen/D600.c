/*
 * File: D600.c
 * Overlay: CEN
 * Description: Center Cube Area (Final Boss)
 */

#include "common.h"
#include "stage.h"

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_8018D600);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_8018D6E0);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_8018D89C);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_8018DB18);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_8018DF0C);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_8018DF60);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_8018E124);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_8018E180);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_8018E238);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_8018E3BC);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_8018E3E8);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_8018E6C4);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_8018E7C8);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_8018F890);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_8018F8EC);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_8018F95C);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_8019007C);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80190374);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_8019040C);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_801904B8);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80190540);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80190A78);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80190B64);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80190E4C);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80190E7C);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80191178);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80191280);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80192398);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80192A3C);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80192B00);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80192C18);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80192D30);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80192D7C);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80192DD4);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80192ED0);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80192FE4);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80193030);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80193088);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80193184);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80193298);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80193410);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_801934C4);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80193538);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_801935B4);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_8019362C);

void func_80194264(Entity* entity) {
    s32 i;
    s32 length;
    u32* ptr;

    if (entity->unk34 & 0x800000) {
        g_pfnFreePolygons(entity->firstPolygonIndex);
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

s32 func_80194564(void) {
    s16 value = D_8006C3B8->posX.Data.high - D_800733DA;

    if (value < 0) {
        value = -value;
    }
    return value;
}

s32 func_801945A0(void) {
    s32 value = D_8006C3B8->posY.Data.high - g_EntityArray[PLAYER_CHARACTER].posY.Data.high;

    if (value < 0) {
        value = -value;
    }
    return value;
}

s16 func_801945D4(void) {
    s16 var_a0 = D_8006C3B8->posX.Data.high > D_800733DA;

    if (D_8006C3B8->posY.Data.high > g_EntityArray[PLAYER_CHARACTER].posY.Data.high) {
        var_a0 |= 2;
    }
    return var_a0;
}

void func_80194618(void) {
    D_8006C3B8->posX.value += D_8006C3B8->accelerationX;
    D_8006C3B8->posY.value += D_8006C3B8->accelerationY;
}

void func_80194648(void) {
    if (D_8006C3B8->accelerationY < FALL_TERMINAL_VELOCITY) {
        D_8006C3B8->accelerationY += FALL_GRAVITY;
    }
}

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80194674);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_801948EC);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80194AD4);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80194B34);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80194B60);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80194B7C);

u8 func_80194BE8(s16 x, s16 y) { return ((ratan2(y, x) >> 4) + 0x40); }

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80194C20);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80194C68);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80194CB0);

void func_80194D08(u16 slope, s16 speed) {
    Entity* entity;
    s32 moveX;
    s32 moveY;

    moveX = rcos(slope) * speed;
    entity = D_8006C3B8;

    if (moveX < 0) {
        moveX += 15;
    }

    entity->accelerationX = moveX >> 4;

    moveY = rsin(slope) * speed;
    entity = D_8006C3B8;

    if (moveY < 0) {
        moveY += 15;
    }

    entity->accelerationY = moveY >> 4;
}

u16 func_80194D94(s16 arg0, s16 arg1) { return ratan2(arg1, arg0); }

u16 func_80194DC4(Entity* a, Entity* b) {
    s32 diffX = b->posX.Data.high - a->posX.Data.high;
    s32 diffY = b->posY.Data.high - a->posY.Data.high;
    return ratan2(diffY, diffX);
}

u16 func_80194DFC(s32 x, s32 y) {
    s16 diffX = x - (u16)D_8006C3B8->posX.Data.high;
    s16 diffY = y - (u16)D_8006C3B8->posY.Data.high;
    return ratan2(diffY, diffX);
}

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80194E44);

void func_80194EA4(u8 initState) {
    Entity* entity;

    entity = D_8006C3B8;
    entity->initState = initState;
    entity->unk2E = 0;
    entity->animationFrameIndex = 0;
    entity->animationFrameDuration = 0;
}

void func_80194EC4(u8 arg0) {
    Entity* entity;

    entity = D_8006C3B8;
    entity->unk2E = arg0;
    entity->animationFrameIndex = 0;
    entity->animationFrameDuration = 0;
}

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80194EE0);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80194F74);

void func_80195070(Entity* arg0) {
    if (arg0->initState == 0) {
        arg0->initState++;
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

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80195C0C);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80195C5C);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80195C84);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_801964F8);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_801965F4);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80196698);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80196C80);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80196F30);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80197A00);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80197B28);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80198084);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80198174);

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

void func_8019C540(unkStruct3* arg0) {
    arg0->unk12.data1.unk1 = 0;
    arg0->unk1E.data1.unk1 = 0;
    arg0->unk2B = 0;
    arg0->unk0->unk14 = 0;
    arg0->unk0->unk16 = 0;
    arg0->unk0->unkA = 0;
    arg0->unk0->unk8 = 0;
    arg0->unk0->unkE = 0;
    arg0->unk0->unkC = 0;
    arg0->unk0->unk12.data = 0;
    arg0->unk0->unk10.data = 0;
    arg0->unk0->unk18 = 0;
    arg0->unk0->unk1A = 0;
    arg0->unk0->unk1C.data = 0;
    arg0->unk0->unk1E.data = 0;
    arg0->unk0->unk24 = 0;
    arg0->unk0->unk25 = 0;
    arg0->unk0->unk28 = 0;
    arg0->unk0->unk2A = 0;
    arg0->unk0->unk20 = 0;
    arg0->unk0->unk22 = 0;
}

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_8019C620);

void func_8019C674(unkStruct3* arg0) {
    arg0->unk2B = 0;
    arg0->unk32 = 8;
    arg0->unk0->unk2B = 0;
    arg0->unk0->unk7 = 4;
    arg0->unk0->unk32 = 8;
}

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_8019C6A0);
