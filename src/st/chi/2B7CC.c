#include "chi.h"

/*
 * File: 2B7CC.c
 * Overlay: CHI
 * Description: Abandoned Mine
 */

#ifndef NON_MATCHING
//INCLUDE_ASM("st/chi/nonmatchings/2B7CC", func_801AB7CC);    // [Entity]
//#else
extern s32 D_801817F4;
extern s32 D_801818F8;
extern s32 D_80181904;

extern EntityInit EntityInit_80180700;

// E_ID_29
// func_801AB7CC
// https://decomp.me/scratch/QrYmQ
// PSP:func_psp_0923AE68:Match
// PSP:https://decomp.me/scratch/MjOOd
void func_801AB7CC(Entity* self)
{
    Entity* entity;       // s2
    s32 x;                // s3
    s32 primIdx;          // s6
    s32 y;                // s5
    Primitive* prim;      // s0
    s32 var_a3;           // s4
    s32 var_s2;           // s1
    s16 temp_v0_8;        // s7

    if ((self->flags & FLAG_DEAD) && (self->step < 8)) {
        SetStep(8);
    }
    
    switch (self->step) {
        case 0:
            InitializeEntity(&EntityInit_80180700);
            self->hitboxOffX = 1;
            self->hitboxOffY = -7;
            
            primIdx = g_api.AllocPrimitives(PRIM_GT4, 3);
            if (primIdx == -1) {
                DestroyEntity(self);
                return;
            }
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIdx;
            prim = &g_PrimBuf[primIdx];
            self->ext.prim = prim;
            
            for (var_s2 = 0; var_s2 < 2; var_s2++) {
                prim->tpage = 0x14;
                prim->clut = 0x21A;
                prim->u0 = prim->u2 = 0x48;
                prim->u1 = prim->u3 = 0x80;
                prim->v0 = prim->v1 = 0;
                prim->v2 = prim->v3 = 0x22;
                prim->priority = self->zPriority - 1;
                prim->drawMode = 8;
                
                prim = prim->next;
            }
            self->ext.chi_801ab7cc.prim = prim;
            prim->tpage = 0x14;
            prim->clut = 0x21A;
            prim->u0 = prim->u2 = 0;
            prim->u1 = prim->u3 = 0x18;
            prim->v0 = prim->v1 = 0x30;
            prim->v2 = prim->v3 = 0x52;
            prim->priority = self->zPriority - 2;
            prim->drawMode = 8;
            prim = prim->next;
            break;
        
        case 1:
            if (UpdatePhysicsState(&D_801817F4) & 1) {
                SetStep(2);
            }
            break;
        
        case 2:
            AnimateEntity(&D_801818F8, self);
            if (GetDistanceToPlayerX() < 0x70) {
                self->hitboxState = 0;
                SetStep(3);
            }
            if (self->flags & FLAG_DEAD) {
                entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (entity != NULL) {
                    CreateEntityFromEntity(2U, self, entity);
                    entity->posY.i.hi -= 4;
                    entity->params = 0;
                }
                
                PlaySfxWithPosArgs(0x693);
                DestroyEntity(self);
                return;
            }
            break;
        
        case 3:
            AnimateEntity(&D_80181904, self);
            var_a3 = 0;
            switch (self->step_s) {                
                case 0:
                    self->ext.factory.unk84++;
                    if (self->ext.factory.unk84 > 0x38) {
                        self->ext.factory.unk84 = 0x38;
                        var_a3 += 1;
                    }
                    self->ext.factory.unk86++;
                    if (self->ext.factory.unk86 > 0x22) {
                        self->ext.factory.unk86 = 0x22;
                        var_a3 += 1;
                    }
                    prim = self->ext.prim;
                    x = self->posX.i.hi;
                    y = self->posY.i.hi;
                    y -=self->ext.factory.unk86;
                    for (var_s2 = -1; var_s2 < 2; var_s2 += 2) {
                        prim->x0 = prim->x2 = x;
                        prim->x1 = prim->x3 = x + (self->ext.factory.unk84 * var_s2);
                        prim->y0 = prim->y1 = y;
                        prim->y2 = prim->y3 = self->posY.i.hi;
                        prim->drawMode = 2;
                        prim = prim->next;
                    }
                    if (var_a3 == 2) {
                        self->step_s++;
                    }
                    break;
                
                case 1:
                    self->ext.factory.unk88++;
                    if (self->ext.factory.unk88 > 0xC) {
                        self->ext.factory.unk88 = 0xC;
                        var_a3 += 1;
                    }
                    self->ext.factory.unk8A++;
                    if (self->ext.factory.unk8A > 0x22) {
                        self->ext.factory.unk8A = 0x22;
                        var_a3 += 1;
                    }
                    prim = self->ext.chi_801ab7cc.prim;
                    x = self->posX.i.hi;
                    y = self->posY.i.hi - self->ext.factory.unk8A;
                    prim->x0 = prim->x2 = x - self->ext.factory.unk88;
                    prim->x1 = prim->x3 = x + self->ext.factory.unk88;
                    prim->y0 = prim->y1 = y;
                    prim->y2 = prim->y3 = self->posY.i.hi;
                    prim->drawMode = 2;
                    if (var_a3 == 2) {
                        self->step_s++;
                    }
                    break;
                
                case 2:
                    entity = self + 1;
                    CreateEntityFromCurrentEntity(0x2A, entity);
                    entity->posX.i.hi = self->posX.i.hi;
                    entity->posY.i.hi = self->posY.i.hi - 0x1B;
                    entity->facingLeft = GetSideToPlayer() & 1;
                    entity->zPriority = (s32)self->zPriority;
                    self->step_s++;
                    break;
                
                case 3:
                    entity = (self + 2);
                    for (var_s2 = 0; var_s2 < 0xA; var_s2++, entity++) {
                        CreateEntityFromCurrentEntity(0x2B, entity);
                        entity->params = var_s2;
                        entity->zPriority = self->zPriority + 1;
                    }
                    self->step_s++;
                    break;
                
                case 4:
                    break;
            }
            break;
        
        case 4:
            AnimateEntity(&D_801818F8, self);
            break;
        
        case 5:
            if (self->ext.chi_801ab7cc.unk91) {
                self->ext.chi_801ab7cc.unk91 = false;
                self->ext.generic.unk8C.modeU16.unk0 = 0x30;
            }
            if (self->ext.chi_801ab7cc.unk8C) {
                AnimateEntity(&D_80181904, self);
                self->ext.chi_801ab7cc.unk8C--;
            }
            break;
        
        case 8:
            switch (self->step_s) {
                case 0:
                    self->ext.generic.unk8C.modeU16.unk2 = 0;
                    self->step_s++;
                    // fallthrough
                case 1:
                    if (!(g_Timer & 7)) {
                        self->palette += 1;
                        prim = self->ext.prim;
                        while (prim != NULL) {
                            prim->clut += 1;
                            prim = prim->next;
                        }
                        if (self->palette == 0x210) {
                            self->step_s++;
                        }
                    }
                    break;
                
                case 2:
                    var_a3 = 0;
                    self->ext.chi_801ab7cc.unk8C++;
                    if (self->ext.chi_801ab7cc.unk8C & 1) {
                        prim = self->ext.prim;
                        x = self->posX.i.hi;
                        if (self->ext.factory.unk84) {
                            self->ext.factory.unk84--;
                            if (self->ext.factory.unk84 < 0) {
                                self->ext.factory.unk84 = 0;
                            }
                        }
                        for (var_s2 = -1; var_s2 < 2; var_s2 += 2) {
                            prim->x1 = x + ((self->ext.factory.unk84 + 0x38) / 2 * var_s2);
                            prim->x3 = x + (self->ext.factory.unk84 * var_s2);
                            prim->y0++;
                            prim->y1++;
                            if (prim->y1 > prim->y2) {
                                prim->drawMode = 8;
                                var_a3 += 1;
                            }
                            prim = prim->next;
                        }
                    }
                    prim = self->ext.chi_801ab7cc.prim;
                    prim->y0 = ++prim->y1;
                    if (prim->y0 > prim->y2) {
                        prim->drawMode = 8;
                        var_a3 += 1;
                    }
                    if (var_a3 == 3) {
                        self->step_s += 1;
                    }
                    break;
                
                case 3:
                    entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                    if (entity != NULL) {
                        CreateEntityFromEntity(2U, self, entity);
                        entity->params = 2;
                        entity->posY.i.hi -= 0xC;
                    }
                    PlaySfxWithPosArgs(0x655);
                    PreventEntityFromRespawning(self);
                    DestroyEntity(self);
                    return;
            }
    }
        
    if (self->ext.chi_801ab7cc.unk8E) {
        temp_v0_8 = self->rotZ;                 // s7
        self->rotZ += 0x180;
        x = rcos(temp_v0_8) * 3 >> 0xC;         // s3
        y = rsin(temp_v0_8) * 3 >> 0xC;         // s5
        prim = self->ext.prim;                  // s0
        
        for (var_s2 = -1; var_s2 < 2; var_s2 += 2) {
            prim->x1 = self->posX.i.hi + (x + 0x38) * var_s2;
            prim->y1 = self->posY.i.hi - 0x22 + y * var_s2;

            prim = prim->next;
        }
        x /= 2;
        entity = self + 1;
        prim = self->ext.chi_801ab7cc.prim;
        self->ext.chi_801ab7cc.unk8E--;
        if (!self->ext.chi_801ab7cc.unk8E) {
            entity->posX.i.hi = self->posX.i.hi;
            prim->x0 = self->posX.i.hi - 0xC;
            prim->x1 = self->posX.i.hi + 0xC;
        } else {
            prim->x0 = self->posX.i.hi - 0xC + x;
            prim->x1 = self->posX.i.hi + 0xC + x;
            entity->posX.i.hi = self->posX.i.hi + x;
        }
    }
}
#endif

INCLUDE_ASM("st/chi/nonmatchings/2B7CC", func_801AC074);    // [Entity]

INCLUDE_ASM("st/chi/nonmatchings/2B7CC", func_801AC730);    // [Entity]

INCLUDE_ASM("st/chi/nonmatchings/2B7CC", func_801ACB6C);    // [Entity]

#ifndef NON_MATCHING
INCLUDE_ASM("st/chi/nonmatchings/2B7CC", func_801ACEF4);    // [Entity]
#else
// typedef struct {
//     /* 0x00 */ char pad0[0x28];
//     /* 0x28 */ ? unk28;                             // inferred
//     /* 0x28 */ char pad28[0xA];
//     /* 0x32 */ s16 unkAE;
// } ET_EntitySlot16;                                  // size = 0x34

// ?* func_801AB548(void*, Primitive*);                // extern
// extern u16 EntityInit_8018070C;

// void func_801ACEF4(Entity* arg0)
// {
//     ?* temp_t3;
//     ?* var_a2;
//     ?* var_a3;
//     ?* var_t0;
//     ?* var_t1;
//     Primitive* temp_t0;
//     Primitive* var_t0_2;
//     s16 temp_v0;
//     u16 temp_v0_2;
//     u16 temp_v1;
//     void* temp_s1;
//     void* temp_s1_2;
//     void* temp_s1_3;

//     temp_v1 = arg0->step;
//     switch (temp_v1) {                              // irregular
//         case 0:
//             InitializeEntity(&EntityInit_8018070C);
//             arg0->hitboxState = 0;
//             arg0->palette = 0x8224;
//             arg0->flags |= 0x202000;
//             temp_v0 = g_api_AllocPrimitives(PRIM_GT4, 5);
//             if (temp_v0 != -1) {
//                 temp_t0 = &g_PrimBuf[temp_v0];
//                 arg0->primIndex = (s32) temp_v0;
//                 arg0->ext.prim = temp_t0;
//                 temp_s1 = arg0->ext.heartDrop.unk[0xA] - 0xBC;
//                 arg0->flags |= 0x800000;
//                 var_t1 = temp_s1->unk7C;
//                 var_t0 = func_801AB548(temp_s1, temp_t0);
//                 if (var_t1 != NULL) {
//                     do {
//                         temp_t3 = var_t0->unk0;
//                         var_a3 = var_t0;
//                         var_a2 = var_t1;
// loop_6:
//                         var_a3->unk0 = var_a2->unk0;
//                         var_a3->unk4 = (s32) var_a2->unk4;
//                         var_a3->unk8 = (s32) var_a2->unk8;
//                         var_a3->unkC = (s32) var_a2->unkC;
//                         var_a2 += 0x10;
//                         var_a3 += 0x10;
//                         if (var_a2 != (var_t1 + 0x30)) {
//                             goto loop_6;
//                         }
//                         *var_a3 = *var_a2;
//                         var_t0->unk0 = temp_t3;
//                         var_t0->unk26 = (s16) (var_t1->unk26 + 1);
//                         var_t1 = var_t1->unk0;
//                         var_t0 = temp_t3;
//                     } while (var_t1 != NULL);
//                 }
//                 temp_s1_2 = temp_s1 + 0xBC;
//                 arg0->animCurFrame = temp_s1_2->unk56;
//                 arg0->zPriority = temp_s1_2->unk24 + 1;
//             case 1:
//                 var_t0_2 = arg0->ext.prim;
//                 if (var_t0_2 != NULL) {
//                     do {
//                         var_t0_2->clut = arg0->palette & 0xFFF;
//                         var_t0_2->drawMode = 2;
//                         var_t0_2 = var_t0_2->next;
//                     } while (var_t0_2 != NULL);
//                 }
//                 temp_s1_3 = arg0->ext.heartDrop.unk[0xA];
//                 temp_v0_2 = arg0->palette + 1;
//                 arg0->palette = temp_v0_2;
//                 arg0->animCurFrame = temp_s1_3->unk56;
//                 if (((temp_v0_2 & 0xFFF) >= 0x233) || (temp_s1_3->unk26 != 0x2A)) {
//                     goto block_14;
//                 }
//             } else {
// block_14:
//                 DestroyEntity(arg0);
//             }
//             return;
//     }
// }
#endif

s32 func_801AE70C(Primitive* prim, u8 arg1);
void StageNamePopupHelper(Primitive* prim)  // [Duplicate]
{
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
        func_801AE70C(prim, 4);
        break;
    case 2:
        if (prim->p2 < 0x14) {
            prim->p2++;
        }
        xPos = prim->p2 / 5;
        prim->x2 = prim->x0 = prim->x0 - xPos;
        prim->x1 = prim->x1 - xPos;
        prim->x3 = prim->x0;
        func_801AE70C(prim, 4);
        break;
    }
}

// POSSIBLE FILE BREAK

//#ifndef NON_MATCHING
INCLUDE_ASM("st/chi/nonmatchings/2B7CC", func_801AD2BC);    // EntityStageNamePopup()
//#else
// /*?*/ void func_801AD0EC(?*);                                // extern
// extern u8 D_8003BE40;
// extern s8 D_8019B3C0;
// extern s8 D_8019B3D0;
// extern u16 EntityInit_80180640;

// void func_801AD2BC(Entity* arg0)
// {
//     Primitive* temp_s0;
//     Primitive* temp_s0_2;
//     Primitive* temp_s0_3;
//     Primitive* temp_s0_6;
//     Primitive* var_s0;
//     Primitive* var_s0_10;
//     Primitive* var_s0_11;
//     Primitive* var_s0_2;
//     Primitive* var_s0_3;
//     Primitive* var_s0_6;
//     Primitive* var_s0_7;
//     Primitive* var_s0_8;
//     Primitive* var_s0_9;
//     s16 temp_a0_2;
//     s16 temp_a0_3;
//     s16 temp_v0;
//     s16 temp_v0_10;
//     s16 temp_v0_12;
//     s16 temp_v0_17;
//     s16 temp_v0_18;
//     s16 temp_v0_19;
//     s16 temp_v0_4;
//     s16 temp_v0_5;
//     s16 temp_v0_6;
//     s16 temp_v0_7;
//     s16 temp_v0_8;
//     s16 temp_v1_2;
//     s16 temp_v1_3;
//     s16 var_v0_2;
//     s16 var_v1;
//     s16 var_v1_2;
//     s32 temp_s0_4;
//     s32 temp_s0_5;
//     s32 temp_v0_15;
//     s32 temp_v0_20;
//     s32 temp_v0_21;
//     s32 temp_v0_22;
//     s32 temp_v0_3;
//     s32 var_a0;
//     s32 var_s0_4;
//     s32 var_s0_5;
//     s32 var_s1;
//     s32 var_s1_10;
//     s32 var_s1_11;
//     s32 var_s1_12;
//     s32 var_s1_13;
//     s32 var_s1_3;
//     s32 var_s1_4;
//     s32 var_s1_5;
//     s32 var_s1_6;
//     s32 var_s1_7;
//     s32 var_s1_8;
//     s32 var_s1_9;
//     s32 var_v0;
//     u16 temp_a0;
//     u16 temp_v0_2;
//     u16 temp_v1;
//     u16 temp_v1_4;
//     u8 temp_a1;
//     u8 temp_a1_2;
//     u8 temp_a2;
//     u8 temp_v0_11;
//     u8 temp_v0_13;
//     u8 temp_v0_14;
//     u8 temp_v0_16;
//     u8 temp_v0_9;
//     u8 var_a1;
//     u8 var_a1_2;
//     u8 var_s1_2;

//     temp_a0 = arg0->step;
//     switch (temp_a0) {                              // switch 1; irregular
//         case 0:                                     // switch 1
//             if ((g_DemoMode == Demo_None) && (D_8003BE40 == 0)) {
//                 InitializeEntity(&EntityInit_80180640);
//                 temp_v0 = g_api_AllocPrimitives(PRIM_GT4, 0x57);
//                 if (temp_v0 != -1) {
//                     var_s0 = &g_PrimBuf[temp_v0];
//                     arg0->primIndex = (s32) temp_v0;
//                     arg0->ext.prim = var_s0;
//                     arg0->flags |= 0x800000;
//                     if (var_s0 != NULL) {
//                         do {
//                             var_s0->drawMode = 8;
//                             var_s0 = var_s0->next;
//                         } while (var_s0 != NULL);
//                     }
//                     var_s0_2 = arg0->ext.prim;
//                     var_s1 = 0;
//                     do {
//                         temp_v0_2 = 0xC0 - var_s1;
//                         var_s1 += 1;
//                         var_s0_2->tpage = 0x11;
//                         var_s0_2->clut = 0x19F;
//                         var_s0_2->u2 = 4;
//                         var_s0_2->u0 = 4;
//                         var_s0_2->u3 = 0x78;
//                         var_s0_2->u1 = 0x78;
//                         var_s0_2->v1 = 0;
//                         var_s0_2->v0 = 0;
//                         var_s0_2->v3 = 0x28;
//                         var_s0_2->v2 = 0x28;
//                         var_s0_2->x0 = 0xC;
//                         var_s0_2->x2 = 0xC;
//                         var_s0_2->y0 = 0x9D;
//                         var_s0_2->y1 = 0x9D;
//                         var_s0_2->x1 = 0x80;
//                         var_s0_2->x3 = 0x80;
//                         var_s0_2->y2 = 0xC5;
//                         var_s0_2->y3 = 0xC5;
//                         var_s0_2->priority = temp_v0_2;
//                         var_s0_2->drawMode = 8;
//                         temp_s0 = var_s0_2->next;
//                         temp_s0->tpage = 0x11;
//                         temp_s0->clut = 0x19F;
//                         temp_s0->u2 = 8;
//                         temp_s0->u0 = 8;
//                         temp_s0->u3 = 0x7C;
//                         temp_s0->u1 = 0x7C;
//                         temp_s0->v1 = 0x40;
//                         temp_s0->v0 = 0x40;
//                         temp_s0->v3 = 0x68;
//                         temp_s0->v2 = 0x68;
//                         temp_s0->x0 = 0x80;
//                         temp_s0->x2 = 0x80;
//                         temp_s0->y0 = 0x9D;
//                         temp_s0->priority = temp_v0_2;
//                         temp_s0->y1 = 0x9D;
//                         temp_s0->x1 = 0xF4;
//                         temp_s0->x3 = 0xF4;
//                         temp_s0->y2 = 0xC5;
//                         temp_s0->y3 = 0xC5;
//                         temp_s0->drawMode = 8;
//                         var_s0_2 = temp_s0->next;
//                     } while (var_s1 < 2);
//                     var_s1_2 = 0;
//                     arg0->ext.generic.unk88.unk = var_s0_2;
//                     var_s0_2->u2 = 4;
//                     var_s0_2->u0 = 4;
//                     var_s0_2->u3 = 0x78;
//                     var_s0_2->u1 = 0x78;
//                     var_s0_2->tpage = 0x11;
//                     var_s0_2->clut = 0x19D;
//                     var_s0_2->v1 = 0;
//                     var_s0_2->v0 = 0;
//                     var_s0_2->v3 = 0x28;
//                     var_s0_2->v2 = 0x28;
//                     var_s0_2->x0 = 0xC;
//                     var_s0_2->x2 = 0xC;
//                     var_s0_2->y0 = 0x9D;
//                     var_s0_2->y1 = 0x9D;
//                     var_s0_2->x1 = 0x80;
//                     var_s0_2->x3 = 0x80;
//                     var_s0_2->y2 = 0xC5;
//                     var_s0_2->y3 = 0xC5;
//                     var_s0_2->priority = 0xBF;
//                     var_s0_2->drawMode = 8;
//                     temp_s0_2 = var_s0_2->next;
//                     temp_s0_2->clut = 0x19D;
//                     temp_s0_2->tpage = 0x11;
//                     temp_s0_2->u2 = 8;
//                     temp_s0_2->u0 = 8;
//                     temp_s0_2->u3 = 0x7C;
//                     temp_s0_2->u1 = 0x7C;
//                     temp_s0_2->v1 = 0x40;
//                     temp_s0_2->v0 = 0x40;
//                     temp_s0_2->v3 = 0x68;
//                     temp_s0_2->v2 = 0x68;
//                     temp_s0_2->x0 = 0x80;
//                     temp_s0_2->x2 = 0x80;
//                     temp_s0_2->y0 = 0x9D;
//                     temp_s0_2->y1 = 0x9D;
//                     temp_s0_2->x1 = 0xF4;
//                     temp_s0_2->x3 = 0xF4;
//                     temp_s0_2->y2 = 0xC5;
//                     temp_s0_2->y3 = 0xC5;
//                     temp_s0_2->priority = 0xBF;
//                     temp_s0_2->drawMode = 8;
//                     temp_s0_3 = temp_s0_2->next;
//                     arg0->ext.generic.unk84.unk = temp_s0_3;
//                     temp_s0_3->u0 = 0;
//                     temp_s0_3->u1 = 0x40;
//                     temp_s0_3->type = 3;
//                     temp_s0_3->tpage = 0x1A;
//                     temp_s0_3->clut = 0x15F;
//                     temp_s0_3->v0 = 0xC0;
//                     temp_s0_3->v1 = 0xC0;
//                     temp_s0_3->v2 = 0xFF;
//                     temp_s0_3->v3 = 0xFF;
//                     temp_s0_3->y0 = 0x9B;
//                     temp_s0_3->y1 = 0x9B;
//                     temp_s0_3->y2 = 0xC7;
//                     temp_s0_3->y3 = 0xC7;
//                     temp_s0_3->x0 = 0xC;
//                     temp_s0_3->x2 = 0xC;
//                     temp_s0_3->x1 = 0xF4;
//                     temp_s0_3->x3 = 0xF4;
//                     temp_s0_3->r0 = 0x10;
//                     temp_s0_3->g0 = 0x28;
//                     temp_s0_3->u2 = temp_s0_3->u0;
//                     temp_s0_3->u3 = temp_s0_3->u1;
//                     temp_s0_3->b0 = 0;
//                     temp_s0_3->r2 = 8;
//                     temp_s0_3->g2 = 0;
//                     temp_s0_3->b2 = 0x38;
//                     temp_s0_3->priority = 0xB0;
//                     temp_s0_3->drawMode = 0x1D;
//                     temp_s0_3->unk10 = (s32) temp_s0_3->unk4;
//                     temp_s0_3->unk28 = (s32) temp_s0_3->unk1C;
//                     var_s0_3 = temp_s0_3->next;
//                     arg0->ext.factory.parent = var_s0_3;
//                     var_v1 = 0x9D;
//                     do {
//                         temp_a0_2 = var_s1_2 + 0x9E;
//                         temp_a1 = var_s1_2;
//                         var_s1_2 += 1;
//                         var_s0_3->v3 = var_s1_2;
//                         var_s0_3->v2 = var_s1_2;
//                         var_s0_3->y0 = var_v1;
//                         var_s0_3->y1 = var_v1;
//                         var_s0_3->r0 = 0x78;
//                         var_s0_3->g0 = 0x78;
//                         var_s0_3->b0 = 0xA8;
//                         var_s0_3->y2 = temp_a0_2;
//                         var_s0_3->y3 = temp_a0_2;
//                         var_s0_3->v1 = temp_a1;
//                         var_s0_3->v0 = temp_a1;
//                         var_s0_3->priority = 0xC0;
//                         var_s0_3->tpage = 0x11;
//                         var_s0_3->clut = 0x19F;
//                         var_s0_3->x0 = 0xC;
//                         var_s0_3->x2 = 0xC;
//                         var_s0_3->x1 = 0x80;
//                         var_s0_3->x3 = 0x80;
//                         var_s0_3->u0 = 4;
//                         var_s0_3->u2 = 4;
//                         var_s0_3->u3 = 0x78;
//                         var_s0_3->u1 = 0x78;
//                         var_s0_3->drawMode = 0xC;
//                         var_s0_3->unk10 = (s32) var_s0_3->unk4;
//                         var_s0_3->unk1C = (s32) var_s0_3->unk4;
//                         var_s0_3->unk28 = (s32) var_s0_3->unk4;
//                         var_s0_3 = var_s0_3->next;
//                         var_v1 = var_s1_2 + 0x9D;
//                     } while ((s32) var_s1_2 < 0x28);
//                     var_s1_3 = 0;
//                     var_v1_2 = 0x9D;
//                     do {
//                         temp_a0_3 = var_s1_3 + 0x9E;
//                         temp_a1_2 = var_s1_3 + 0x40;
//                         var_s0_3->clut = 0x19F;
//                         var_s0_3->y0 = var_v1_2;
//                         var_s0_3->y1 = var_v1_2;
//                         var_s0_3->r0 = 0x78;
//                         var_s0_3->g0 = 0x78;
//                         var_s0_3->b0 = 0xA8;
//                         temp_a2 = var_s1_3 + 0x41;
//                         var_s0_3->y2 = temp_a0_3;
//                         var_s0_3->y3 = temp_a0_3;
//                         var_s1_3 += 1;
//                         var_s0_3->v1 = temp_a1_2;
//                         var_s0_3->v0 = temp_a1_2;
//                         var_s0_3->priority = 0xC0;
//                         var_s0_3->drawMode = 0xC;
//                         var_s0_3->tpage = 0x11;
//                         var_s0_3->x0 = 0x80;
//                         var_s0_3->x2 = 0x80;
//                         var_s0_3->x1 = 0xF4;
//                         var_s0_3->x3 = 0xF4;
//                         var_s0_3->u0 = 8;
//                         var_s0_3->u2 = 8;
//                         var_s0_3->u3 = 0x7C;
//                         var_s0_3->u1 = 0x7C;
//                         var_s0_3->v3 = temp_a2;
//                         var_s0_3->v2 = temp_a2;
//                         var_s0_3->unk10 = (s32) var_s0_3->unk4;
//                         var_s0_3->unk1C = (s32) var_s0_3->unk4;
//                         var_s0_3->unk28 = (s32) var_s0_3->unk4;
//                         var_s0_3 = var_s0_3->next;
//                         var_v1_2 = var_s1_3 + 0x9D;
//                     } while (var_s1_3 < 0x28);
//                     arg0->ext.generic.unk80.modeS32 = 0x20;
//                 case 1:                             // switch 1
//                     temp_v1 = arg0->step_s;
//                     switch (temp_v1) {
//                         case 0:
//                             temp_v0_3 = arg0->ext.generic.unk80.modeS32;
//                             if (temp_v0_3 != 0) {
//                                 arg0->ext.generic.unk80.modeS32 = temp_v0_3 - 1;
//                             } else {
//                                 temp_s0_4 = arg0->ext.generic.unk84.unk;
//                                 temp_s0_4->unk20 = 0x80;
//                                 temp_s0_4->unk8 = 0x80;
//                                 temp_s0_4->unk2C = 0x80;
//                                 temp_s0_4->unk14 = 0x80;
//                                 temp_s0_4->unk16 = 0xB1;
//                                 temp_s0_4->unkA = 0xB1;
//                                 temp_s0_4->unk2E = 0xB1;
//                                 temp_s0_4->unk22 = 0xB1;
//                                 temp_s0_4->unk32 = 0x15;
// block_78:
// block_79:
//                                 arg0->step_s += 1;
//                             }
//                             break;
//                         case 1:
//                             temp_s0_5 = arg0->ext.generic.unk84.unk;
//                             temp_v0_4 = temp_s0_5->unkA;
//                             var_a0 = 0;
//                             if (temp_v0_4 >= 0x9C) {
//                                 var_a0 = 1;
//                                 temp_v1_2 = temp_v0_4 - 4;
//                                 temp_s0_5->unkA = temp_v1_2;
//                                 temp_s0_5->unk16 = temp_v1_2;
//                                 temp_v0_5 = (u16) temp_s0_5->unk22 + 4;
//                                 temp_s0_5->unk22 = temp_v0_5;
//                                 temp_s0_5->unk2E = temp_v0_5;
//                             }
//                             temp_v0_6 = temp_s0_5->unk8;
//                             var_v0 = var_a0 & 0xFF;
//                             if (temp_v0_6 >= 0xD) {
//                                 temp_v1_3 = temp_v0_6 - 8;
//                                 temp_s0_5->unk8 = temp_v1_3;
//                                 temp_s0_5->unk20 = temp_v1_3;
//                                 temp_v0_7 = (u16) temp_s0_5->unk14 + 8;
//                                 temp_s0_5->unk14 = temp_v0_7;
//                                 temp_s0_5->unk2C = temp_v0_7;
//                                 var_v0 = (var_a0 | 1) & 0xFF;
//                             }
//                             if (var_v0 == 0) {
//                                 arg0->ext.generic.unk80.modeS32 = 0;
//                                 arg0->ext.factory.childId = 0;
//                                 arg0->ext.factory.unk92 = 0;
//                                 goto block_79;
//                             }
//                             break;
//                         case 2:
//                             temp_v0_8 = (u16) arg0->ext.factory.childId + 3;
//                             arg0->ext.factory.childId = temp_v0_8;
//                             var_s1_4 = 0;
//                             if (temp_v0_8 >= 0x80) {
//                                 arg0->step_s += 1;
//                             }
//                             var_s0_4 = arg0->ext.generic.unk88.unk;
//                             var_s0_4->unk32 = 0x75;
// loop_34:
//                             temp_v0_9 = (u8) arg0->ext.stub[0x14];
//                             var_s1_4 += 1;
//                             var_s0_4->unk2A = temp_v0_9;
//                             var_s0_4->unk29 = temp_v0_9;
//                             var_s0_4->unk28 = temp_v0_9;
//                             var_s0_4->unk1E = temp_v0_9;
//                             var_s0_4->unk1D = temp_v0_9;
//                             var_s0_4->unk1C = temp_v0_9;
//                             var_s0_4->unk12 = temp_v0_9;
//                             var_s0_4->unk11 = temp_v0_9;
//                             var_s0_4->unk10 = temp_v0_9;
//                             var_s0_4->unk6 = temp_v0_9;
//                             var_s0_4->unk5 = temp_v0_9;
//                             var_s0_4->unk4 = temp_v0_9;
//                             var_s0_4 = var_s0_4->unk0;
//                             if (var_s1_4 < 2) {
//                                 var_s0_4->unk32 = 0x75;
//                                 goto loop_34;
//                             }
//                             break;
//                         case 3:
//                             temp_v0_10 = (u16) arg0->ext.factory.childId - 2;
//                             arg0->ext.factory.childId = temp_v0_10;
//                             var_s1_5 = 0;
//                             if (temp_v0_10 & 0x8000) {
//                                 arg0->ext.factory.childId = 0;
//                             }
//                             var_s0_5 = arg0->ext.generic.unk88.unk;
//                             do {
//                                 var_s0_5->unk32 = 0x35;
//                                 temp_v0_11 = (u8) arg0->ext.stub[0x14];
//                                 var_s1_5 += 1;
//                                 var_s0_5->unk2A = temp_v0_11;
//                                 var_s0_5->unk29 = temp_v0_11;
//                                 var_s0_5->unk28 = temp_v0_11;
//                                 var_s0_5->unk1E = temp_v0_11;
//                                 var_s0_5->unk1D = temp_v0_11;
//                                 var_s0_5->unk1C = temp_v0_11;
//                                 var_s0_5->unk12 = temp_v0_11;
//                                 var_s0_5->unk11 = temp_v0_11;
//                                 var_s0_5->unk10 = temp_v0_11;
//                                 var_s0_5->unk6 = temp_v0_11;
//                                 var_s0_5->unk5 = temp_v0_11;
//                                 var_s0_5->unk4 = temp_v0_11;
//                                 var_s0_5 = var_s0_5->unk0;
//                             } while (var_s1_5 < 2);
//                             temp_v0_12 = arg0->ext.factory.childId;
//                             if (temp_v0_12 != 0) {
//                                 var_v0_2 = 0x80 - temp_v0_12;
//                             } else {
//                                 var_v0_2 = (u16) arg0->ext.factory.unk92 + 4;
//                             }
//                             arg0->ext.factory.unk92 = var_v0_2;
//                             var_s1_6 = 0;
//                             if (arg0->ext.factory.unk92 >= 0x80) {
//                                 arg0->ext.factory.unk92 = 0x80;
//                                 arg0->step_s += 1;
//                             }
//                             var_s0_6 = arg0->ext.prim;
//                             do {
//                                 var_s0_6->drawMode = 0x35;
//                                 temp_v0_13 = (u8) arg0->ext.stub[0x16];
//                                 var_s1_6 += 1;
//                                 var_s0_6->b3 = temp_v0_13;
//                                 var_s0_6->g3 = temp_v0_13;
//                                 var_s0_6->r3 = temp_v0_13;
//                                 var_s0_6->b2 = temp_v0_13;
//                                 var_s0_6->g2 = temp_v0_13;
//                                 var_s0_6->r2 = temp_v0_13;
//                                 var_s0_6->b1 = temp_v0_13;
//                                 var_s0_6->g1 = temp_v0_13;
//                                 var_s0_6->r1 = temp_v0_13;
//                                 var_s0_6->b0 = temp_v0_13;
//                                 var_s0_6->g0 = temp_v0_13;
//                                 var_s0_6->r0 = temp_v0_13;
//                                 var_s0_6 = var_s0_6->next;
//                             } while (var_s1_6 < 2);
//                             var_s1_7 = 0;
//                             var_s0_6->drawMode = 0x15;
// loop_48:
//                             temp_v0_14 = (u8) arg0->ext.stub[0x16];
//                             var_s1_7 += 1;
//                             var_s0_6->b3 = temp_v0_14;
//                             var_s0_6->g3 = temp_v0_14;
//                             var_s0_6->r3 = temp_v0_14;
//                             var_s0_6->b2 = temp_v0_14;
//                             var_s0_6->g2 = temp_v0_14;
//                             var_s0_6->r2 = temp_v0_14;
//                             var_s0_6->b1 = temp_v0_14;
//                             var_s0_6->g1 = temp_v0_14;
//                             var_s0_6->r1 = temp_v0_14;
//                             var_s0_6->b0 = temp_v0_14;
//                             var_s0_6->g0 = temp_v0_14;
//                             var_s0_6->r0 = temp_v0_14;
//                             var_s0_6 = var_s0_6->next;
//                             if (var_s1_7 < 2) {
//                                 var_s0_6->drawMode = 0x15;
//                                 goto loop_48;
//                             }
//                             break;
//                         case 4:
//                             arg0->ext.generic.unk88.unk->unk32 = 8;
//                             arg0->ext.generic.unk80.modeS32 = 0x40;
//                             arg0->step = 2;
//                             arg0->step_s = 0;
//                             D_8003BE40 = 1;
//                             break;
//                     }
//                 default:                            // switch 1
// block_84:
//                     FntPrint(&D_8019B3C0, arg0->step);
//                     FntPrint(&D_8019B3D0, arg0->step_s);
//                     return;
//                 }
//             }
// block_83:
//             DestroyEntity(arg0);
//             return;
//         case 2:                                     // switch 1
//             temp_v0_15 = arg0->ext.generic.unk80.modeS32 - 1;
//             arg0->ext.generic.unk80.modeS32 = temp_v0_15;
//             if (temp_v0_15 == 0) {
//                 arg0->step_s = 0;
//                 arg0->step = 3;
//             }
//             goto block_84;
//         case 3:                                     // switch 1
//             temp_v1_4 = arg0->step_s;
//             if (temp_v1_4 != 1) {
//                 if ((s32) temp_v1_4 < 2) {
//                     var_s1_8 = 0;
//                     if (temp_v1_4 != 0) {

//                     } else {
//                         var_s0_7 = arg0->ext.prim->next->next;
//                         do {
//                             var_s0_7->drawMode = 0x15;
//                             temp_v0_16 = arg0->ext.stub[0x16];
//                             var_s1_8 += 1;
//                             var_s0_7->b3 = temp_v0_16;
//                             var_s0_7->g3 = temp_v0_16;
//                             var_s0_7->r3 = temp_v0_16;
//                             var_s0_7->b2 = temp_v0_16;
//                             var_s0_7->g2 = temp_v0_16;
//                             var_s0_7->r2 = temp_v0_16;
//                             var_s0_7->b1 = temp_v0_16;
//                             var_s0_7->g1 = temp_v0_16;
//                             var_s0_7->r1 = temp_v0_16;
//                             var_s0_7->b0 = temp_v0_16;
//                             var_s0_7->g0 = temp_v0_16;
//                             var_s0_7->r0 = temp_v0_16;
//                             var_s0_7 = var_s0_7->next;
//                         } while (var_s1_8 < 2);
//                         temp_v0_17 = (u16) arg0->ext.factory.unk92 - 4;
//                         arg0->ext.factory.unk92 = temp_v0_17;
//                         if (temp_v0_17 & 0x8000) {
//                             arg0->ext.factory.unk92 = 0;
//                             goto block_79;
//                         }
//                     }
//                     goto block_84;
//                 }
//                 if (temp_v1_4 != 2) {
//                     if (temp_v1_4 != temp_a0) {
//                         goto block_84;
//                     }
//                     var_s0_8 = arg0->ext.factory.parent;
//                     if (var_s0_8 != NULL) {
//                         do {
//                             func_801AD0EC((?* ) var_s0_8);
//                             var_s0_8 = var_s0_8->next;
//                         } while (var_s0_8 != NULL);
//                     }
//                     temp_s0_6 = arg0->ext.generic.unk84.unk;
//                     temp_v0_18 = (u16) temp_s0_6->y0 + 2;
//                     temp_s0_6->y0 = temp_v0_18;
//                     temp_s0_6->y1 = temp_v0_18;
//                     temp_s0_6->x0 = (u16) temp_s0_6->x0 - 2;
//                     temp_v0_19 = (u16) temp_s0_6->y2 - 2;
//                     temp_s0_6->y2 = temp_v0_19;
//                     temp_s0_6->y3 = temp_v0_19;
//                     temp_s0_6->x2 = (u16) temp_s0_6->x2 - 2;
//                     temp_s0_6->x1 = (u16) temp_s0_6->x1 + 2;
//                     temp_s0_6->x3 = (u16) temp_s0_6->x3 + 2;
//                     if (temp_s0_6->y2 < temp_s0_6->y0) {
//                         goto block_83;
//                     }
//                     goto block_84;
//                 }
//                 var_s0_9 = arg0->ext.factory.parent;
//                 if (var_s0_9 != NULL) {
//                     do {
//                         func_801AD0EC((?* ) var_s0_9);
//                         var_s0_9 = var_s0_9->next;
//                     } while (var_s0_9 != NULL);
//                 }
//                 temp_v0_20 = arg0->ext.generic.unk80.modeS32 - 1;
//                 arg0->ext.generic.unk80.modeS32 = temp_v0_20;
//                 if (temp_v0_20 == 0) {
//                     goto block_78;
//                 }
//                 goto block_84;
//             }
//             var_s0_10 = arg0->ext.prim;
//             var_s1_9 = 1;
//             do {
//                 var_s0_10->drawMode = 8;
//                 var_s0_10 = var_s0_10->next;
//                 var_s1_9 += 1;
//             } while (var_s1_9 < 4);
//             var_s0_11 = arg0->ext.factory.parent;
//             var_s1_10 = 0;
//             var_a1 = 0 * 4;
//             do {
//                 var_s0_11->r0 = 0x80;
//                 var_s0_11->g0 = 0x80;
//                 var_s0_11->b0 = 0x80;
//                 var_s1_10 += 1;
//                 var_s0_11->unk10 = (s32) var_s0_11->unk4;
//                 var_s0_11->unk1C = (s32) var_s0_11->unk4;
//                 var_s0_11->unk28 = (s32) var_s0_11->unk4;
//                 var_s0_11->p1 = var_a1;
//                 var_s0_11->p2 = Random() & 3;
//                 var_s0_11->p3 = 0;
//                 var_s0_11->drawMode = 0x35;
//                 var_s0_11 = var_s0_11->next;
//                 var_a1 = var_s1_10 * 4;
//             } while (var_s1_10 < 0x14);
//             var_s1_11 = 0;
//             do {
//                 temp_v0_21 = 0x14 - var_s1_11;
//                 var_s1_11 += 1;
//                 var_s0_11->r0 = 0x80;
//                 var_s0_11->g0 = 0x80;
//                 var_s0_11->b0 = 0x80;
//                 var_s0_11->unk10 = (s32) var_s0_11->unk4;
//                 var_s0_11->unk1C = (s32) var_s0_11->unk4;
//                 var_s0_11->unk28 = (s32) var_s0_11->unk4;
//                 var_s0_11->p1 = (u8) -(temp_v0_21 * 4);
//                 var_s0_11->p2 = Random() & 3;
//                 var_s0_11->drawMode = 0x35;
//                 var_s0_11->p3 = 0;
//                 var_s0_11 = var_s0_11->next;
//             } while (var_s1_11 < 0x14);
//             var_s1_12 = 0;
//             var_a1_2 = 0 * 4;
//             do {
//                 var_s0_11->r0 = 0x80;
//                 var_s0_11->g0 = 0x80;
//                 var_s0_11->b0 = 0x80;
//                 var_s1_12 += 1;
//                 var_s0_11->unk10 = (s32) var_s0_11->unk4;
//                 var_s0_11->unk1C = (s32) var_s0_11->unk4;
//                 var_s0_11->unk28 = (s32) var_s0_11->unk4;
//                 var_s0_11->p1 = var_a1_2;
//                 var_s0_11->p2 = Random() & 3;
//                 var_s0_11->p3 = 0;
//                 var_s0_11->drawMode = 0x35;
//                 var_s0_11 = var_s0_11->next;
//                 var_a1_2 = var_s1_12 * 4;
//             } while (var_s1_12 < 0x14);
//             var_s1_13 = 0;
//             do {
//                 temp_v0_22 = 0x14 - var_s1_13;
//                 var_s1_13 += 1;
//                 var_s0_11->r0 = 0x80;
//                 var_s0_11->g0 = 0x80;
//                 var_s0_11->b0 = 0x80;
//                 var_s0_11->unk10 = (s32) var_s0_11->unk4;
//                 var_s0_11->unk1C = (s32) var_s0_11->unk4;
//                 var_s0_11->unk28 = (s32) var_s0_11->unk4;
//                 var_s0_11->p1 = (u8) -(temp_v0_22 * 4);
//                 var_s0_11->p2 = Random() & 3;
//                 var_s0_11->drawMode = 0x35;
//                 var_s0_11->p3 = 0;
//                 var_s0_11 = var_s0_11->next;
//             } while (var_s1_13 < 0x14);
//             arg0->ext.generic.unk80.modeS32 = 0x70;
//             goto block_79;
//     }
// }
// Warning: struct draculaPrimitive is not defined (only forward-declared)
//#endif
//#include "../e_stage_name.h"

//NOTE: The remaining functions are all contained in "../prim_helpers.h" but
//      UnkPrimHelper and PrimDecreaseBrightness don't match.
INCLUDE_ASM("st/chi/nonmatchings/2B7CC", func_801ADF40);    // UnkPrimHelper()
//INCLUDE_ASM("st/chi/nonmatchings/2B7CC", func_801AE328);    // UpdateAnimation()
s32 UpdateAnimation(u8* texAnimations, Primitive* prim) {
    s16 sp0;
    s16 tempUv;
    u8 new_var;
    u8* nextAnimation = texAnimations + ((prim->p1 * 5) & 0xFF);
    u8 new_var2;
    s32 retVal = 0;

    if (prim->p2 == 0) {
        if (*nextAnimation) {
            if (*nextAnimation == 0xFF) {
                return 0;
            }
            retVal = 0x80;
            prim->p2 = nextAnimation[0];
            ++nextAnimation;
            tempUv = nextAnimation[0] + (nextAnimation[1] << 8);
            nextAnimation += 2;
            sp0 = nextAnimation[0] + (nextAnimation[1] << 8);
            LOH(prim->u0) = tempUv;
            LOH(prim->u1) = tempUv + *((u8*)(&sp0));
            new_var = *((u8*)&sp0 + 1);
            LOH(prim->u3) = tempUv + sp0;
            LOH(prim->u2) = tempUv + (new_var << 8);
            ++prim->p1;
        } else {
            prim->p1 = 0;
            prim->p2 = 0;
            prim->p2 = texAnimations[0];
            tempUv = texAnimations[1] + (texAnimations[2] << 8);
            sp0 = texAnimations[3] + (texAnimations[4] << 8);
            LOH(prim->u0) = tempUv;
            LOH(prim->u1) = tempUv + (*(u8*)&sp0);
            new_var2 = *((u8*)&sp0 + 1);
            LOH(prim->u3) = tempUv + sp0;
            LOH(prim->u2) = tempUv + (new_var2 << 8);
            ++prim->p1;
            return 0;
        }
    }

    retVal |= 1;
    --prim->p2;
    return (retVal | 1) & 0xFF;
}
//INCLUDE_ASM("st/chi/nonmatchings/2B7CC", func_801AE478);    // FindFirstUnkPrim()
Primitive* FindFirstUnkPrim(Primitive* poly) {
    while (poly != NULL) {
        if (poly->p3 != 0) {
            poly = poly->next;
        } else {
            return poly;
        }
    }
    return NULL;
}
//INCLUDE_ASM("st/chi/nonmatchings/2B7CC", func_801AE4A8);    // FindFirstUnkPrim2()
Primitive* FindFirstUnkPrim2(Primitive* prim, u8 index) {

    Primitive* ret;
    int i;

    for (; prim; prim = prim->next) {
        if (!prim->p3) {
            ret = prim;
            for (i = 1; i < index; ++i) {
                prim = prim->next;
                if (!prim) {
                    return NULL;
                }
                if (prim->p3) {
                    break;
                }
            }
            if (i == index) {
                return ret;
            }
        }
    }
    return NULL;
}
//INCLUDE_ASM("st/chi/nonmatchings/2B7CC", func_801AE524);    // PrimToggleVisibility()
Primitive* PrimToggleVisibility(Primitive* firstPrim, s32 count) {
    Primitive* prim;
    s8 isVisible;
    s32 i;

    if (firstPrim->p3) {
        firstPrim->p3 = 0;
    } else {
        firstPrim->p3 = 1;
    }

    prim = firstPrim;
    for (i = 0; i < count; i++) {
        if (prim->p3) {
            prim->drawMode &= ~DRAW_HIDE;
            isVisible = false;
        } else {
            prim->drawMode |= DRAW_HIDE;
            isVisible = true;
        }

        prim = prim->next;
        if (prim == NULL)
            return 0;
        prim->p3 = isVisible;
    }

    return prim;
}
//INCLUDE_ASM("st/chi/nonmatchings/2B7CC", func_801AE5AC);    // PrimResetNext()
void PrimResetNext(Primitive* prim) {
    prim->p1 = 0;
    prim->p2 = 0;
    prim->p3 = 0;
    prim->next->x1 = 0;
    prim->next->y1 = 0;
    prim->next->y0 = 0;
    prim->next->x0 = 0;
    prim->next->clut = 0;
    LOHU(prim->next->u0) = 0;
    LOHU(prim->next->b1) = 0;
    LOHU(prim->next->r1) = 0;
    LOHU(prim->next->u1) = 0;
    prim->next->tpage = 0;
    LOHU(prim->next->r2) = 0;
    LOHU(prim->next->b2) = 0;
    prim->next->u2 = 0;
    prim->next->v2 = 0;
    prim->next->r3 = 0;
    prim->next->b3 = 0;
    prim->next->x2 = 0;
    prim->next->y2 = 0;
}
//TODO: Find first "init not started" prim?
//INCLUDE_ASM("st/chi/nonmatchings/2B7CC", func_801AE68C);    // UnkPolyFunc2()
void UnkPolyFunc2(Primitive* prim) {
    PrimResetNext(prim);
    prim->p3 = 8;
    prim->next->p3 = 1;
    prim->next->type = PRIM_LINE_G2;
    prim->next->drawMode = 0xA;
}
//INCLUDE_ASM("st/chi/nonmatchings/2B7CC", func_801AE6E0);    // UnkPolyFunc0()
void UnkPolyFunc0(Primitive* prim) {
    prim->p3 = 0;
    prim->drawMode = DRAW_HIDE;
    prim->next->p3 = 0;
    prim->next->type = PRIM_GT4;
    prim->next->drawMode = DRAW_HIDE;
}
INCLUDE_ASM("st/chi/nonmatchings/2B7CC", func_801AE70C);    // PrimDecreaseBrightness()
//#include "../prim_helpers.h"
