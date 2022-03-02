#include "common.h"
#include "dra.h"

void DestroyEntity(Entity *);
s32 func_801B4C78();
void InitializeEntity(u16 *arg0);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801A7D64);

#ifndef NON_MATCHING
INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801A7E2C);
#else
bool func_801A7E2C(Entity *entity) {
    s16 distance;

    distance = D_800733DA - entity->posX.Data.high;
    if (distance < 0) {
        distance = -distance;
    }
    if (entity->hitboxWidth >= distance) {
        if ((s16)(D_800733DE - entity->posY.Data.high) < 0) {
            return true;
        }
    }

    return false;
}
#endif

#ifndef NON_MATCHING
INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", EntityLockCamera);
#else
extern u16 D_801805B0[];
extern u8 D_8018065C[];
extern u8 D_80180660[];
extern u16 D_80180664[];

void EntityLockCamera(Entity *entity) {
    s32 temp_v0_2;
    s32 temp_v1;
    u16 *temp_v1_2;
    u16 *temp_v1_5;
    u8 temp_s1;
    u8 temp_v0;
    s32 phi_v1;

    temp_s1 = entity->subId;
    if (entity->initState == 0) {
        InitializeEntity(D_801805B0);
        temp_v1 = temp_s1 & 0xFFFF;
        entity->unk3C = 1;
        temp_v0 = D_80180660[temp_v1];
        entity->unk7C = temp_v0;
        if (temp_v0) {
            entity->hitboxWidth = D_8018065C[temp_v1];
            entity->hitboxHeight = 20;
        } else {
            entity->hitboxWidth = 20;
            entity->hitboxHeight = D_8018065C[temp_v1];
        }
    }

    if (entity->subId & 0x100) {
        temp_v1_2 = &D_80180664[(((temp_s1 & 0xFFFF) * 4) & 0xFFFF)];
        g_CurrentRoomX = *temp_v1_2++;
        g_CurrentRoomY = *temp_v1_2++;
        g_CurrentRoomWidth = *temp_v1_2++;
        g_CurrentRoomHeight = *temp_v1_2++;
        DestroyEntity(entity);
        return;
    }

    if (func_801A7E2C(entity)) {
        temp_v0_2 = func_801B4C78();
        if (entity->unk7C) {
            phi_v1 = (temp_v0_2 & 2) * 2;
        } else {
            phi_v1 = (temp_v0_2 & 1) * 4;
        }

        temp_v1_5 = &D_80180664[(phi_v1 + temp_s1 * 8) & 0xFFFF];
        g_CurrentRoomX = *temp_v1_5++;
        g_CurrentRoomY = *temp_v1_5++;
        g_CurrentRoomWidth = *temp_v1_5++;
        g_CurrentRoomHeight = *temp_v1_5++;
    }
}
#endif

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801A805C);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801A8328);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801A8620);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801A8984);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801A89D8);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801A8B9C);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801A8BF8);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801A8CB0);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801A8E34);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801A8E60);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801A910C);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801A9210);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801AA218);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801AA290);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801AA8DC);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801AABA4);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801AACB4);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801AB0C8);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801AB5E4);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801ABBBC);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801AC458);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801AC564);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801AD430);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801AD530);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801AD658);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801AD838);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801AD8C0);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801ADAC8);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801ADB10);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801ADD60);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801AEFD8);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801AF154);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801AF380);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801AF6D0);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801AF774);

void func_801B0030(s32 arg0) {
    D_8003C734 = arg0;
    D_80073060 = 0;
    g_backbufferX = 0;
    g_backbufferY = 0;
}

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B0058);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B0180);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B01C0);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B01F8);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B0280);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B0324);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B0414);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B0464);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B101C);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B1198);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B11E8);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B1298);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B186C);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B189C);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B1B98);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B1CA0);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B2A3C);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", CreateEntity);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B31A4);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B32BC);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B33D4);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B3420);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B3478);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B3574);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B3688);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B36D4);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B372C);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B3828);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B393C);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B3AB4);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B3B68);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B3BDC);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B3C58);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B3CD0);

void DestroyEntity(Entity* item) {
    int i, length;
    u32* ptr;

    if (item->unk34 & 0x800000) {
        D_8003C7B4(item->unk64);
    }

    ptr = item;
    length = sizeof(Entity) / sizeof(s32);
    for (i = 0; i < length; i++)
        *ptr++ = 0;
}

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B4974);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B49F0);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B4A38);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B4AF0);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B4C08);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B4C44);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B4C78);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B4CBC);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B4CEC);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B4D18);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B4D5C);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B4FD4);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B51E4);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B53CC);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B542C);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B5458);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B5474);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B54E0);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B5518);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B5560);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B55A8);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B5600);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B568C);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B56BC);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B56F4);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B573C);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B5794);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B57B4);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B57D0);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", InitializeEntity);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B5948);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B5970);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B5A98);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B5BF0);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B5E38);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B5EC8);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B5F4C);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B60A8);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B615C);

void func_801B61D4(void) {
}

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B61DC);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B6204);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B6314);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B633C);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B6358);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B6B60);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B6C5C);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B6D34);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B7308);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B7B0C);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B7BFC);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B7D0C);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B7E3C);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B7F24);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B8014);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B8108);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B8338);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B8434);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B89B4);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B8AB4);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B8B80);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B8C48);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B8D00);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B8ED8);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B94B8);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B9BB8);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B9DB0);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801B9EA8);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801BA23C);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801BA6EC);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801BA7D8);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801BAB08);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801BB2AC);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801BB764);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801BC4D0);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801BC5C0);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801BD0C0);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801BD4A8);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801BD5F8);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801BD628);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801BD6A4);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801BD72C);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801BD80C);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801BD860);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801BD88C);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801BD8F0);

INCLUDE_ASM("asm/st/st0/nonmatchings/27D64", func_801BE1B4);
