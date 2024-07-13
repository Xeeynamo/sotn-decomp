/*
 * File: 8DF0.c
 * Overlay: RWRP
 * Description: All reverse warp rooms.
 */

#include "rwrp.h"

extern ObjInit2 D_801804E0[];

void func_80188DF0(Entity* arg0) {
    ObjInit2* temp_s1;
    u32 temp_v0;

    temp_s1 = &D_801804E0[arg0->params];
    if (arg0->step == 0) {
        InitializeEntity(g_eInitGeneric2);
        arg0->animSet = (s16)temp_s1->animSet;
        arg0->zPriority = temp_s1->zPriority;
        arg0->unk5A = (u16)temp_s1->unk4.s;
        arg0->palette = temp_s1->palette;
        arg0->drawFlags = temp_s1->drawFlags;
        arg0->drawMode = temp_s1->drawMode;
        temp_v0 = temp_s1->unkC;
        if (temp_v0 != 0) {
            arg0->flags = (s32)temp_v0;
        }
        if (arg0->params == 1) {
            arg0->rotY = 0x200;
            arg0->rotX = 0x200;
        }
    }
    AnimateEntity((s32)temp_s1->unk10, arg0);
}

extern u16 D_80180538[];
extern u16 D_80180488[];
extern u8 D_80180530[];
extern u8 D_80180528[];

void EntityUnkId12(Entity* entity) {
    s32 ret;
    u16* temp_v0_2;
    u16 temp_s1 = entity->params;
    u16 phi_v1;
    u16 unk;

    entity->unk6D[0] = 0;

    if (entity->step != 0) {
        switch (temp_s1) {
        case 4:
        case 5:
            if (g_Tilemap.x != 0) {
                return;
            }
            break;

        case 6:
            if (g_pads->pressed & PAD_TRIANGLE) {
                g_Tilemap.x = 0;
                g_Tilemap.width = 1280;
                entity->step++;
                return;
            }
            break;
        }

        if (entity->unk44 != 0) {
            ret = GetSideToPlayer();
            phi_v1 = entity->ext.ent12.unk7C;
            if (phi_v1 != 0) {
                phi_v1 = (ret & 2) * 2;
            } else {
                phi_v1 = (ret & 1) * 4;
            }
            unk = 8;
            temp_s1 = (temp_s1 * unk) + phi_v1;
            temp_v0_2 = &D_80180538[temp_s1];
            g_Tilemap.x = *(temp_v0_2++);
            g_Tilemap.y = *(temp_v0_2++);
            g_Tilemap.width = *(temp_v0_2++);
            g_Tilemap.height = *(temp_v0_2++);
        }
    } else {
        InitializeEntity(D_80180488);
        entity->ext.ent12.unk7C = D_80180530[temp_s1];
        if (entity->ext.ent12.unk7C != 0) {
            entity->hitboxWidth = D_80180528[temp_s1];
            entity->hitboxHeight = 16;
        } else {
            entity->hitboxWidth = 16;
            entity->hitboxHeight = D_80180528[temp_s1];
        }
    }
}

extern u8* D_801805B8[];
extern Entity D_8007D858;
extern char D_801805E0;
extern u16 D_80180440[];
extern u8 D_801805F8[];
extern u8 D_801805D8[];
extern u16 D_801805E8[];
void EntityBreakable(Entity* entity) {
    Entity* temp_v0;
    u16 temp_s0 = entity->params >> 0xC;

    if (entity->step != 0) {
        AnimateEntity(D_801805B8[temp_s0], entity);
        if (entity->unk44 != 0) {
            g_api.PlaySfx(NA_SE_BREAK_CANDLE);
            temp_v0 = AllocEntity(&D_8007D858, &D_8007D858 + 32);
            if (temp_v0 != NULL) {
                CreateEntityFromCurrentEntity(2, temp_v0);
                temp_v0->params = (&D_801805E0)[temp_s0];
            }
            ReplaceBreakableWithItemDrop(entity);
        }
    } else {
        InitializeEntity(D_80180440);
        entity->zPriority = g_unkGraphicsStruct.g_zEntityCenter.unk - 20;
        entity->drawMode = D_801805F8[temp_s0];
        entity->hitboxHeight = D_801805D8[temp_s0];
        entity->animSet = D_801805E8[temp_s0];
    }
}

INCLUDE_ASM("st/rwrp/nonmatchings/8DF0", EntityRWarpRoom);
