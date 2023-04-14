/*
 * File: 8DF0.c
 * Overlay: RWRP
 * Description: All reverse warp rooms.
 */

#include "rwrp.h"

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/8DF0", func_80188DF0);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/8DF0", func_80188ED0);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/8DF0", func_8018908C);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/8DF0", func_801891C0);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/8DF0", func_80189E9C);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/8DF0", func_8018A168);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/8DF0", Update);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/8DF0", func_8018A494);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/8DF0", func_8018A59C);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/8DF0", func_8018B6B4);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/8DF0", func_8018BD58);

void CreateEntityWhenInVerticalRange(LayoutObject* layoutObj) {
    s16 yClose;
    s16 yFar;
    s16 posY;
    Entity* entity;

    posY = g_Camera_posY_i_hi;
    yClose = posY - 0x40;
    yFar = posY + 0x120;
    if (yClose < 0) {
        yClose = 0;
    }

    posY = layoutObj->posY;
    if (posY < yClose) {
        return;
    }

    if (yFar < posY) {
        return;
    }

    switch (layoutObj->objectId & 0xE000) {
    case 0x0:
        entity = &D_800762D8[(u8)layoutObj->objectRoomIndex];
        if (entity->objectId == 0) {
            func_8018BD58(entity, layoutObj);
        }
        break;
    case 0x8000:
        break;
    case 0xA000:
        entity = &D_800762D8[(u8)layoutObj->objectRoomIndex];
        func_8018BD58(entity, layoutObj);
        break;
    }
}

void CreateEntityWhenInHorizontalRange(LayoutObject* layoutObj) {
    s16 xClose;
    s16 xFar;
    s16 posX;
    Entity* entity;

    posX = g_Camera_posX_i_hi;
    xClose = posX - 0x40;
    xFar = posX + 0x140;
    if (xClose < 0) {
        xClose = 0;
    }

    posX = layoutObj->posX;
    if (posX < xClose) {
        return;
    }

    if (xFar < posX) {
        return;
    }

    switch (layoutObj->objectId & 0xE000) {
    case 0x0:
        entity = &D_800762D8[(u8)layoutObj->objectRoomIndex];
        if (entity->objectId == 0) {
            func_8018BD58(entity, layoutObj);
        }
        break;
    case 0x8000:
        break;
    case 0xA000:
        entity = &D_800762D8[(u8)layoutObj->objectRoomIndex];
        func_8018BD58(entity, layoutObj);
        break;
    }
}

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/8DF0", func_8018C04C);

void func_8018C098(s16 arg0) {
    while (true) {
        if ((D_80195A30->posX != 0xFFFF) &&
            ((arg0 >= D_80195A30->posX) || (D_80195A30->posX == 0xFFFE))) {
            break;
        }
        D_80195A30--;
    }
}

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/8DF0", func_8018C0F0);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/8DF0", func_8018C1EC);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/8DF0", func_8018C300);

void func_8018C34C(s16 arg0) {
    while (true) {
        if ((D_80195A34->posY != 0xFFFF) &&
            ((arg0 >= D_80195A34->posY) || (D_80195A34->posY == 0xFFFE))) {
            break;
        }
        D_80195A34--;
    }
}

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/8DF0", func_8018C3A4);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/8DF0", func_8018C4A0);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/8DF0", func_8018C5B4);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/8DF0", func_8018C72C);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/8DF0", func_8018C7E0);

void func_8018C854(u16 objectId, Entity* source, Entity* entity) {
    func_8018D580(entity);
    entity->objectId = objectId;
    entity->pfnUpdate = D_801803E0[objectId];
    entity->posX.i.hi = source->posX.i.hi;
    entity->posY.i.hi = source->posY.i.hi;
}

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/8DF0", func_8018C8D0);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/8DF0", func_8018C948);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/8DF0", func_8018D580);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/8DF0", func_8018D5EC);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/8DF0", func_8018D668);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/8DF0", func_8018D6B0);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/8DF0", func_8018D768);

s32 func_8018D880(void) {
    s16 temp_v1 = g_CurrentEntity->posX.i.hi - PLAYER.posX.i.hi;

    if (temp_v1 >> 16) {
        temp_v1 = -temp_v1;
    }
    return temp_v1;
}

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/8DF0", func_8018D8BC);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/8DF0", func_8018D8F0);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/8DF0", func_8018D934);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/8DF0", func_8018D964);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/8DF0", func_8018D990);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/8DF0", func_8018DC08);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/8DF0", func_8018DDF0);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/8DF0", func_8018DE50);

s16 func_8018DE7C(u8 arg0) { return D_80180A94[arg0]; }

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/8DF0", func_8018DE98);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/8DF0", func_8018DF04);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/8DF0", func_8018DF3C);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/8DF0", func_8018DF84);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/8DF0", func_8018DFCC);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/8DF0", func_8018E024);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/8DF0", func_8018E0B0);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/8DF0", func_8018E0E0);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/8DF0", func_8018E118);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/8DF0", func_8018E160);

void func_8018E1C0(s32 arg0) {
    g_CurrentEntity->step = arg0 & 0xFF;
    g_CurrentEntity->unk2E = 0;
    g_CurrentEntity->animFrameIdx = 0;
    g_CurrentEntity->animFrameDuration = 0;
}

void func_8018E1E0(s32 arg0) {
    g_CurrentEntity->unk2E = arg0 & 0xFF;
    g_CurrentEntity->animFrameIdx = 0;
    g_CurrentEntity->animFrameDuration = 0;
}

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/8DF0", func_8018E1FC);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/8DF0", func_8018E290);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/8DF0", func_8018E38C);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/8DF0", func_8018E3B4);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/8DF0", func_8018E4DC);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/8DF0", func_8018E634);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/8DF0", func_8018E978);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/8DF0", func_8018EA30);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/8DF0", func_8018EAB4);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/8DF0", func_8018EC10);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/8DF0", func_8018EC90);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/8DF0", func_8018ED6C);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/8DF0", func_8018EE84);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/8DF0", func_8018EF28);

void func_8018EF78(void) { func_8018D580(g_CurrentEntity); }

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/8DF0", func_8018EFA0);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/8DF0", func_8018F814);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/8DF0", func_8018F910);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/8DF0", func_8018F9B4);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/8DF0", func_8018FF9C);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/8DF0", func_8019024C);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/8DF0", func_80190D1C);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/8DF0", func_80190E44);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/8DF0", func_801913A0);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/8DF0", func_80191490);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/8DF0", func_801915A0);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/8DF0", func_801916D0);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/8DF0", func_801917B8);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/8DF0", func_801918A8);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/8DF0", func_8019199C);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/8DF0", func_80191BCC);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/8DF0", func_80191CC8);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/8DF0", func_80192248);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/8DF0", func_80192348);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/8DF0", func_80192414);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/8DF0", func_801924DC);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/8DF0", func_80192594);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/8DF0", func_8019276C);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/8DF0", func_80192D4C);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/8DF0", func_8019344C);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/8DF0", func_80193644);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/8DF0", func_8019373C);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/8DF0", func_8019390C);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/8DF0", func_80194590);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/8DF0", func_80194924);

void func_80194DD4(Entity* entity) {
    ObjInit2* objInit = &D_80181134[entity->subId];

    if (entity->step == 0) {
        func_8018E290(D_80180494);
        entity->animSet = objInit->animSet;
        entity->zPriority = objInit->zPriority;
        entity->unk5A = objInit->unk4.s;
        entity->palette = objInit->palette;
        entity->unk19 = objInit->unk8;
        entity->blendMode = objInit->blendMode;
        if (objInit->unkC != 0) {
            entity->flags = objInit->unkC;
        }
        if (entity->subId >= 5) {
            entity->unk1E = 0x800;
            entity->unk19 = (u8)(entity->unk19 | 4);
        }
    }
    func_8018D6B0(objInit->unk10, entity);
}

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/8DF0", func_80194EC0);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/8DF0", func_801951F0);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/8DF0", func_801955D8);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/8DF0", func_80195728);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/8DF0", func_80195758);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/8DF0", func_801957D4);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/8DF0", func_8019585C);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/8DF0", func_8019593C);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/8DF0", func_80195990);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/8DF0", func_801959BC);
