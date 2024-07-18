#include "stage.h"

/*
 * File: 1B3FC.c
 * Overlay: CHI
 * Description: Abandoned Mine
 */

//#ifndef NON_MATCHING
//INCLUDE_ASM("st/chi/nonmatchings/1B3FC", func_8019B3FC);
//#else
/*?*/ void func_801A13BC(s32, void*);                        // extern
/*?*/ void func_801A1F9C(void*);                             // extern
extern /*?*/s32 D_80180664;
static u8 D_80180730[] = {0x40, 0x01, 0xFF, 0x00};
static u8 D_80180734[] = {0x02, 0x25, 0x02, 0x26};
static ObjInit2 D_80180740[] = {
    {0x0006, 0x01FA, 0x0000, 0x0000, 0x0000, 0x0010, 0x00000000, D_80180730},
    {0x8001, 0x00C0, 0x0000, 0x0000, 0x0003, 0x0003, 0x00000000, D_80180734},
};

// EntityBackgroundBlock
void func_8019B3FC(Entity* entity)
{
    ObjInit2* objInit = &D_80180740[entity->params];
    if (entity->step == 0) {
        func_801A1F9C(&D_80180664);
        entity->animSet = objInit->animSet;
        entity->zPriority = objInit->zPriority;
        entity->unk5A = objInit->unk4.u;
        entity->palette = objInit->palette;
        entity->drawFlags = objInit->drawFlags;
        entity->drawMode = objInit->drawMode;
        if (objInit->unkC != 0) {
            entity->flags = objInit->unkC;
        }
        if (entity->params == 1) {
            entity->rotY = 0x200;
            entity->rotX = 0x200;
        }
    }
    func_801A13BC(objInit->unk10, entity);
}
//#endif

//#ifndef NON_MATCHING
//INCLUDE_ASM("st/chi/nonmatchings/1B3FC", func_8019B4DC);
//#else
s32 func_801A15FC();                                // extern
extern /*?*/s32 D_80180658;
extern u8 D_80180798[];
extern u8 D_801807A0[];
extern u16 D_801807A8[];
extern s32 g_Tilemap_x;
extern s32 g_Tilemap_y;
extern s32 g_Tilemap_width;
extern s32 g_Tilemap_height;

// EntityUnkId12
void func_8019B4DC(Entity* entity)
{
    s32 temp_v0;
    u16 var_v1;
    u16 temp_s1 = entity->params;
    u16* temp_v0_2;
    u16 step;
    u16 unk;

    entity->unk6D[0] = 0;

    if (entity->step != 0) {
        switch (temp_s1) {
        case 4:
        case 5:
            if (g_Tilemap_x != 0) {
                return;
            }
            break;
        case 6:
            if (g_pads->pressed & PAD_TRIANGLE) {
                g_Tilemap_x = 0;
                g_Tilemap_width = 0x500;
                step = entity->step;
                step++;
                entity->step = step;
                return;
            }
            break;
        }

        if (entity->unk44 != 0) {
            temp_v0 = func_801A15FC();
            var_v1 = entity->ext.generic.unk7C.u;
            if (var_v1 != 0) {
                var_v1 = (temp_v0 & 2) * 2;
            } else {
                var_v1 = (temp_v0 & 1) * 4;
            }
            unk = 8;
            temp_s1 = (temp_s1 * unk) + var_v1;
            temp_v0_2 = &D_801807A8[temp_s1];
            g_Tilemap_x = (s32) *temp_v0_2++;
            g_Tilemap_y = (s32) *temp_v0_2++;
            g_Tilemap_width = (s32) *temp_v0_2++;
            g_Tilemap_height = (s32) *temp_v0_2++;
        }
    } else {
        func_801A1F9C(&D_80180658);
        entity->ext.generic.unk7C.s = D_801807A0[temp_s1];
        if (entity->ext.generic.unk7C.s != 0) {
            entity->hitboxWidth = D_80180798[temp_s1];
            entity->hitboxHeight = 16;
        } else {
            entity->hitboxWidth = 16;
            entity->hitboxHeight = D_80180798[temp_s1];
        }
    }
}
//#endif

//#ifndef NON_MATCHING
//INCLUDE_ASM("st/chi/nonmatchings/1B3FC", func_8019B698);
//#else
/*?*/ void func_801A04EC(s32, void*);                          // extern
/*?*/ void func_801A0560(s32, void*, void*);                   // extern
/*?*/ void func_801A128C(void*);                             // extern
void* func_801A1AFC(s32*, void*);                     // extern
/*?*/ void func_801A2684(void*);                             // extern
extern s32 D_8007D858[];
extern /*?*/s32 D_80180610;
extern s32 D_80180838[];
extern u8 D_80180858[];
extern u8 D_80180860[];
extern u16 D_80180868[];
extern u8 D_80180878[];
extern u16 D_80180880;

// EntityUnkId01
void func_8019B698(Entity* entity)
{
    u16* ptr;
    s32 i;
    u16 params = entity->params >> 0xC;
    Entity* newEntity;

    if (entity->step == 0) {
        func_801A1F9C(&D_80180610);
        entity->zPriority = 0x70;
        entity->drawMode = D_80180878[params];
        newEntity = &entity[1];
        entity->hitboxHeight = D_80180858[params];
        entity->animSet = D_80180868[params];
        func_801A128C(newEntity);
        func_801A0560(0x11, entity, newEntity);
        if (params != 0) {
            entity[1].posY.i.hi -= 32;
        } else {
            entity[1].posY.i.hi -= 16;
        }
        newEntity->params = 1;
    }

    func_801A13BC(D_80180838[params], entity);

    if (entity->unk44 != 0) {
        g_api_PlaySfx(SFX_WEAPON_62C);
        newEntity = func_801A1AFC(&D_8007D858[0], &D_8007D858[0x5E0]);
        if (newEntity != NULL) {
            func_801A04EC(2, newEntity);
            newEntity->params = D_80180860[params] | 0x10;
        }

        for (ptr = &D_80180880, i = 0; i < 4; i++) {
            newEntity = func_801A1AFC(&D_8007D858[0], &D_8007D858[0x5E0]);
            if (newEntity != NULL) {
                func_801A0560(0x1A, entity, newEntity);
                newEntity->posX.i.hi += *ptr++;
                newEntity->posY.i.hi += *ptr++;
                if (params != 0) {
                    newEntity->posY.i.hi -= 20;
                }
                newEntity->params = i;
            }
        }

        if (params != 0) {
            for (i = 0; i < 3; i++) {
                newEntity = func_801A1AFC(&D_8007D858[0], &D_8007D858[0x5E0]);
                if (newEntity != NULL) {
                    func_801A0560(0x1A, entity, newEntity);
                    newEntity->posX.i.hi += *ptr++;
                    newEntity->posY.i.hi += *ptr++;
                    newEntity->params = i + 4;
                }
            }
        }
        func_801A128C(&entity[1]);
        func_801A2684(entity);
    }
}
//#endif

INCLUDE_ASM("st/chi/nonmatchings/1B3FC", func_8019B914);

INCLUDE_ASM("st/chi/nonmatchings/1B3FC", func_8019BD0C);

INCLUDE_ASM("st/chi/nonmatchings/1B3FC", func_8019BDF8);

INCLUDE_ASM("st/chi/nonmatchings/1B3FC", func_8019BEDC);

INCLUDE_ASM("st/chi/nonmatchings/1B3FC", func_8019C31C);
