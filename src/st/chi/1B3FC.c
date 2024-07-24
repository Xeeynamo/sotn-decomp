#include "stage.h"

/*
 * File: 1B3FC.c
 * Overlay: CHI
 * Description: Abandoned Mine
 */

void func_801A1F9C(void*);  // InitializeEntity()
void func_801A13BC(s32, void*); // AnimateEntity()
extern s32 D_80180664;
//static u8 D_80180730[] = {0x40, 0x01, 0xFF, 0x00};
//static u8 D_80180734[] = {0x02, 0x25, 0x02, 0x26};
//static ObjInit2 D_80180740[] = {
//    {0x0006, 0x01FA, 0x0000, 0x0000, 0x0000, 0x0010, 0x00000000, D_80180730},
//    {0x8001, 0x00C0, 0x0000, 0x0000, 0x0003, 0x0003, 0x00000000, D_80180734},
//};
extern ObjInit2 D_80180740[];

// EntityBackgroundBlock
void func_8019B3FC(Entity* entity) {
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

s32 func_801A15FC();    // GetSideToPlayer()
extern u16 D_80180658;
extern u8 D_80180798[];
extern u8 D_801807A0[];
extern u16 D_801807A8[];

// EntityUnkId12
void func_8019B4DC(Entity* entity) {
    s32 temp_v0;
    u16* temp_v0_2;
    u16 temp_s1 = entity->params;
    u16 var_v1;
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
            temp_v0 = func_801A15FC();
            var_v1 = entity->ext.generic.unk7C.s;
            if (var_v1 != 0) {
                var_v1 = (temp_v0 & 2) * 2;
            } else {
                var_v1 = (temp_v0 & 1) * 4;
            }
            unk = 8;
            temp_s1 = (temp_s1 * unk) + var_v1;
            temp_v0_2 = &D_801807A8[temp_s1];
            g_Tilemap.x = *(temp_v0_2++);
            g_Tilemap.y = *(temp_v0_2++);
            g_Tilemap.width = *(temp_v0_2++);
            g_Tilemap.height = *(temp_v0_2++);
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

void func_801A04EC(s32, void*); // CreateEntityFromCurrentEntity()
void func_801A0560(s32, void*, void*);  // CreateEntityFromEntity()
void func_801A128C(void*);  // DestroyEntity()
void* func_801A1AFC(s32*, void*);   // AllocEntity()
void func_801A2684(void*);  // ReplaceBreakableWithItemDrop()
extern s32 D_8007D858[];
extern s32 D_80180610;
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

#ifndef NON_MATCHING
INCLUDE_ASM("st/chi/nonmatchings/1B3FC", func_8019B914);
#else
s32 func_8019DE74();                                // extern
/*?*/ void func_801A1640();                                  // extern
/*?*/ void func_801ADF40(Primitive*);                        // extern
/*?*/ void func_801AE68C(Primitive*, s16);                   // extern

// CEN.func_8018DB18
void func_8019B914(Entity* entity)
{
    Collider collider;
    Primitive* prim;
    s16 primIndex;
    s32 temp_s0;
    s32 temp_v0_2;
    u16 temp_v0;
    u16 temp_v0_5;
    Entity* newEntity;
    s32 temp;

    switch (entity->step) {
    case 0:
        func_801A1F9C(&D_80180610);
        entity->zPriority = 0x70;
        entity->hitboxState = 0;
        entity->drawFlags = 4;
        entity->animCurFrame = entity->params + 28;
        temp_s0 = func_801A15FC() & 1;

        temp_v0 = (func_8019DE74() & 0x1E) + 8;
        entity->ext.generic.unk80.modeS16.unk0 = temp_v0;
        if (entity->facingLeft != 0) {
            entity->ext.generic.unk80.modeS16.unk0 = -(s16) temp_v0;
        }

        if (entity->params >= 4) {
            entity->ext.generic.unk80.modeS16.unk0 = -entity->ext.generic.unk80.modeS16.unk0;
        }

        if (temp_s0 == 0) {
            entity->velocityX = FIX(-1);
        } else {
            entity->velocityX = FIX(1);
        }

        temp = 0x8000;
        temp_v0_2 = func_8019DE74() << 8;
        entity->velocityX = entity->velocityX + temp - temp_v0_2;
        entity->velocityY = FIX(-3);
        entity->velocityY = (entity->params >> 1) * 0x6000 - 0x30000;
        if (entity->params == 6) {
            entity->velocityX = 0;
            entity->velocityY = 0;
            entity->step = 2;
        }
        entity->primIndex = 0;
        if (entity->params == 0) {
            primIndex = g_api_AllocPrimitives(PRIM_GT4, 2);
            if (primIndex != -1) {
                prim = &g_PrimBuf[primIndex];
                entity->primIndex = primIndex;
                entity->flags |= FLAG_HAS_PRIMS;
                func_801AE68C(prim, primIndex);
                prim->tpage = 0x1A;
                prim->clut = 0x159;
                prim->u2 = 0x40;
                prim->u0 = 0x40;
                prim->u3 = 0x60;
                prim->u1 = 0x60;
                prim->v1 = 0;
                prim->v0 = 0;
                prim->v3 = 0x20;
                prim->v2 = 0x20;
                prim->next->x1 = entity->posX.i.hi + 4;
                prim->next->y0 = entity->posY.i.hi - 8;
                LOH(prim->next->r2) = 0x20;
                LOH(prim->next->b2) = 0x20;
                prim->next->b3 = 0x10;
                prim->priority = 0x72;
                prim->drawMode = 0x37;
            }
        }
        break;
    case 1:
        func_801A1640();
        entity->rotZ += entity->ext.generic.unk80.modeS16.unk0;
        entity->velocityY += FIX(0.25);
        g_api_CheckCollision(entity->posX.i.hi, entity->posY.i.hi + 6, &collider, 0);
        if (collider.effects & 1) {
            entity->posY.i.hi += collider.unk18;
            entity->velocityY = -entity->velocityY / 2;
            entity->velocityX -= entity->velocityX / 3;
            if (entity->velocityY > FIX(-0.625)) {
                newEntity = func_801A1AFC(&D_8007D858[0], &D_8007D858[0x5E0]);
                if (newEntity != NULL) {
                    func_801A0560(6, entity, newEntity);
                    newEntity->params = 16;
                }
                func_801A128C(entity);
                break;
            }
        }

        if (entity->primIndex != 0) {
            prim = &g_PrimBuf[entity->primIndex];
            func_801ADF40(prim);
            LOH(prim->next->r2) = LOH(prim->next->b2) += 4;
            if (LOH(prim->next->r2) > 64) {
                prim->next->b3 += 252;
                if (prim->next->b3 == 0) {
                    g_api_FreePrimitives(entity->primIndex);
                    entity->primIndex = 0;
                    entity->flags &= ~FLAG_HAS_PRIMS;
                }
            }
        }
        break;
    }
}
#endif

#ifndef NON_MATCHING
INCLUDE_ASM("st/chi/nonmatchings/1B3FC", func_8019BD0C);
#else
typedef struct UnkStruct1 {
    s32 unk0;
    s8 unk4;
    u8 unk5;
    u8 unk6;
    u8 unk7;
    u8 unk8;
    u8 unk9;
    u16 unkA;
    s8 unkC;
    s8 unkD;
    u8 unkE;
    u8 unkF;
    s32 unk10;
    s32 unk14;
    s32 unk18;
    u8 unk1C;
    u8 unk1D;
    u8 unk1E;
    s8 unk1F;
    s32 unk20;
    u8 unk24;
    u8 unk25;
    u16 unk26;
    u8 unk28;
    u8 unk29;
    u8 unk2A;
    u8 unk2B;
    s32 unk2C;
    s16 unk30;
    u16 unk32;
} UnkStruct1;

extern s16 g_Tilemap_scrollY_i_hi;

void func_8019BD0C(struct UnkStruct1* arg0)
{
    s8 temp_v0;
    s16 tempA;
    s8 temp1F;
    s16 tempScroll;
    bool tempCond1;
    bool tempCond2;

    switch (arg0->unk2B) {
        case 1:
            temp_v0 = (func_8019DE74() & 1) + 1;
            arg0->unkC = temp_v0;
            arg0->unkD = temp_v0;
            arg0->unk4 = 0x60;
            arg0->unk5 = 0x80;
            arg0->unk6 = 0x30;
            arg0->unk26 = 0xA0;
            arg0->unk32 = 2;
            arg0->unk1F = (u8) ((func_8019DE74() & 0x1F) + 0x10);
            arg0->unk2B = 2U;
            // fallthrough
        case 2:
            tempA = arg0->unkA + 2;
            arg0->unkA = tempA;
            temp1F = arg0->unk1F - 1;
            arg0->unk1F = temp1F;
            tempScroll = g_Tilemap_scrollY_i_hi;
            tempCond1 = tempScroll + tempA >= 0xA1;
            tempCond2 = (temp1F & 0xFF) == 0;
            if (tempCond2 || tempScroll + tempA >= 0xA1) {
                arg0->unk32 = 8;
                arg0->unk2B = 0U;
            }
            return;
    }
}
#endif

#ifndef NON_MATCHING
INCLUDE_ASM("st/chi/nonmatchings/1B3FC", func_8019BDF8);
#else
extern u8 D_8003BE3C;
extern /*?*/s32 D_8018067C;

void func_8019BDF8(Entity* entity)
{
    s16 temp_3;

    switch (entity->step) {
        case 0:
            func_801A1F9C(&D_8018067C);

            temp_3 = 3;

            //sm volatile("" ::: "memory");

            entity->hitPoints = 0x7FFF;
            entity->animCurFrame = temp_3;
            entity->hitboxState = 3;
            entity->hitboxWidth = 6;
            entity->hitboxHeight = 8;

            //asm volatile("" ::: "memory");

            if (D_8003BE3C != 0) {
                entity->animCurFrame = 4;
            }
            // fallthrough
        case 1:
            if (entity->unk44 == 7) {
                g_api_PlaySfx(0x640);
                D_8003BE3C = 1;
                g_api_func_800F1FC4(0x50);
                entity->animCurFrame = 4;
                entity->step++;
            }
            return;
    }
}
#endif
