#include "chi.h"

/*
 * File: 1CBA8.c
 * Overlay: CHI
 * Description: Abandoned Mine
 */

// [Entity]
extern EntityInit EntityInit_8018067C;
extern u16 g_Tilemap_scrollX_i_hi;

void func_8019CBA8(Entity* self) {
    s32 tileIdx;        // s2
    s32 primIdx;        // s6
    Primitive* prim;    // s0
    Collider collider;
    Entity* entity;
    
    s32 i;              // s1
    s16 s3;             // s3
    s16 s4;

    switch (self->step) {
    case 0:
        InitializeEntity(&EntityInit_8018067C);
        self->zPriority = 0x6A;
        if (self->params) {
            self->animCurFrame = 6;
            tileIdx = 0xDF;
        } else {
            self->animCurFrame = 5;
            tileIdx = 0xC0;
        }
        for (i = 0; i < 4; tileIdx += 0x20, i++) {
            g_Tilemap.fg[tileIdx] = 0x32E;
        }
        primIdx = g_api.AllocPrimitives(PRIM_GT4, 16);
        if (primIdx == -1) {
            return;
        }
        
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIdx;
        prim = &g_PrimBuf[primIdx];
        self->ext.prim = prim;
        
        prim->tpage = 0xF;
        prim->clut = 0x1B;
        if (self->params) {
            prim->u0 = prim->u2 = 0xE3;
            prim->u1 = prim->u3 = 0xD3;
        } else {
            prim->u0 = prim->u2 = 0xD4;
            prim->u1 = prim->u3 = 0xE4;
        }
        prim->v0 = prim->v1 = 0x9C;
        prim->v2 = prim->v3 = 0xDC;

        if (self->params) {
            s3 = 0x1F0;
        } else {
            s3 = 0;
        }
        s3 = s3 - g_Tilemap.scrollX.i.hi;
        prim->x0 = prim->x2 = s3;
        prim->x1 = prim->x3 = s3 + 0x10;
        
        prim->y0 = prim->y1 = 0x1C;
        prim->y2 = prim->y3 = 0x5C;
        prim->priority = 0x6B;
        prim->drawMode = 2;
        prim = prim->next;
        
        while (prim != NULL) {
            prim->type = 1;
            prim->u0 = prim->v0 = 1;
            prim->r0 = 0x20;
            prim->g0 = 0x40;
            prim->b0 = 0x20;
            prim->priority = 0x6C;
            prim->drawMode = 8;
            prim = prim->next;
        }
        return;
    case 1:
        if (!(g_pads->pressed & 0x1000)) {
            return;
        }
        self->step++;
        return;
    case 2:
        self->posY.val += self->velocityY;
        self->velocityY += 0x8000;
        s3 = self->posX.i.hi;
        s4 = self->posY.i.hi + 0x22;
        if (self->posY.i.hi <= 0x60) {
            return;
        }
        g_api.CheckCollision(s3, s4, &collider, 0);
        if (collider.effects == 0) {
            return;
        }
        
        self->posY.i.hi += collider.unk18;
        self->velocityY = -self->velocityY;
        self->velocityY /= 4;
        
        entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (entity != NULL) {
            CreateEntityFromEntity(6U, self, entity);
            entity->posX.i.hi += -8 + (Random() & 7) * 2;
            entity->posY.i.hi += 0x20;
            entity->params = 0x10;
        }
        if (self->velocityY <= -0x2000) {
            return;
        }
        self->step++;
        return;
    case 3:
        if (self->params) {
            tileIdx = 0xDF;
        } else {
            tileIdx = 0xC0;
        }
        for (i = 0; i < 4; tileIdx += 0x20, i++) {
            g_Tilemap.fg[tileIdx] = 0x3A1;
        }
        self->step++;
        return;
    case 4:
        self->posY.val -= 0x4000;

        if (!(g_Timer & 7)) {
            if ((g_Timer & 1)) {
                prim = self->ext.prim;
                prim = prim->next;
                prim = FindFirstUnkPrim(prim);
                if (prim != NULL) {
                    prim->p3 = 1;
                    
                    s3 = (self->posX.i.hi + (Random() & 0xF)) - 8;
                    s4 = 0x5C;
                    prim->x0 = s3;
                    prim->y0 = s4;
                    prim->drawMode = 2;
                }
            }
        }

        s4 = (0x7A - self->posY.i.hi) >> 4;
        if (self->params) {
            tileIdx = 0x13F;
        } else {
            tileIdx = 0x120;
        }
        
        for (i = 0; i < s4; tileIdx -= 0x20, i++) {
            g_Tilemap.fg[tileIdx] = 0x32E;
        }
        self->ext.factory.unk80 = 0x20;
        if (self->posY.i.hi < 0x3A) {
            self->step++;
        }
        /* fallthrough */
    case 5:
        prim = self->ext.prim;
        while (prim != NULL) {
            if (prim->p3) {
                prim->y0 += 2;
                if (prim->y0 > 0xA0) {
                    prim->drawMode = 8;
                    prim->p3 = 0;
                }
            }
            prim = prim->next;
        }
        if (--self->ext.factory.unk80) {
            return;
        }
        DestroyEntity(self);
        return;
    default:
        return;
    }
}

INCLUDE_ASM("st/chi/nonmatchings/1CBA8", func_8019D0D8);

INCLUDE_ASM("st/chi/nonmatchings/1CBA8", func_8019D1A8);    // [Entity]

INCLUDE_ASM("st/chi/nonmatchings/1CBA8", func_8019D9C8);    // [Entity]

#include "../random.h"

// POSSIBLE FILE BREAK

#include "../update.h"

// POSSIBLE FILE BREAK

INCLUDE_ASM("st/chi/nonmatchings/1CBA8", func_8019E1A0);    // UpdateStageEntities()
//#include "../update_stage_entities.h"

// POSSIBLE FILE BREAK

//#ifndef NON_MATCHING
INCLUDE_ASM("st/chi/nonmatchings/1CBA8", func_8019E2A8);    // HitDetection()
//#else
// typedef struct {
//     /* 0x00 */ char pad0[0x18];
//     /* 0x18 */ ? unk18;                             // inferred
//     /* 0x18 */ char pad18[0x1A];
//     /* 0x32 */ s16 unkAE;
// } ET_EntitySlot16;                                  // size = 0x34

// void func_8019F3C0(Entity*);                        // extern
// /*?*/ void func_801A7D78(s8*, ?);                            // extern
// extern /*?*/s32 D_8003BF7C;
// extern u16 D_80073412;
// extern s16 D_80073416;
// extern s8 D_80073420;
// extern Entity* D_80073490;
// extern /*?*/s32 D_80075718;
// extern Entity D_800762D8;
// extern Entity D_8007A958;
// extern /*?*/s32 D_8007C0D8;
// extern Entity D_8007D858;
// extern s32 D_80097410;
// extern s32 D_80097414;
// extern /*?*/s32 D_80180A4C;
// extern /*?*/s32 D_80180D6C;
// extern /*?*/s32 D_80180D70;
// extern /*?*/s32 D_80180D78;
// extern /*?*/s32 D_80180D80;
// extern /*?*/s32 D_80180D94;
// extern /*?*/s32 D_80180DA0;
// extern u16 D_80180DE0;
// extern Entity g_Entities_1;
// extern s32 g_Status_killCount;
// extern u8 g_Status_relics_11;
// extern u8 g_Status_relics_15;

// void func_8019E2A8(void)
// {
//     s32 sp20;
//     Entity* sp28;
//     u8 sp30;
//     EnemyDef* temp_s6_2;
//     Entity* temp_a0;
//     Entity* temp_a3;
//     Entity* temp_a3_2;
//     Entity* temp_v0_13;
//     Entity* temp_v0_14;
//     Entity* temp_v0_15;
//     Entity* temp_v0_3;
//     Entity* var_fp;
//     Entity* var_s1_2;
//     Entity* var_s1_3;
//     Entity* var_s1_4;
//     Entity* var_s3;
//     Primitive* var_s0_2;
//     Primitive* var_s0_5;
//     s16 temp_v0_12;
//     s16 temp_v0_7;
//     s16 temp_v0_9;
//     s16 temp_v1;
//     s16 temp_v1_11;
//     s16 temp_v1_5;
//     s16 temp_v1_6;
//     s16 temp_v1_7;
//     s16 temp_v1_8;
//     s16 temp_v1_9;
//     s16* var_s7;
//     s32 temp_a0_2;
//     s32 temp_s0_3;
//     s32 temp_s2;
//     s32 temp_s3;
//     s32 temp_s3_2;
//     s32 temp_s5_3;
//     s32 temp_v0_10;
//     s32 temp_v0_11;
//     s32 temp_v0_16;
//     s32 temp_v0_2;
//     s32 temp_v0_4;
//     s32 temp_v0_8;
//     s32 temp_v1_4;
//     s32 var_a0;
//     s32 var_s0;
//     s32 var_s0_3;
//     s32 var_v0;
//     s32 var_v0_4;
//     s32 var_v1;
//     s32 var_v1_2;
//     s32 var_v1_3;
//     s32* temp_s4;
//     s32* temp_s4_2;
//     s32* temp_s4_3;
//     s32* temp_s4_4;
//     s32* temp_s4_6;
//     s32* var_a2;
//     s32* var_a2_2;
//     s32* var_s4;
//     u16 temp_a1;
//     u16 temp_a1_2;
//     u16 temp_s0;
//     u16 temp_s2_2;
//     u16 temp_s2_3;
//     u16 temp_s5;
//     u16 temp_s5_2;
//     u16 temp_s6;
//     u16 temp_v0;
//     u16 temp_v0_6;
//     u16 var_a0_2;
//     u16 var_s2;
//     u16 var_s5;
//     u16 var_s5_2;
//     u16 var_v0_3;
//     u16* temp_s0_4;
//     u16* temp_s4_5;
//     u16* temp_s4_7;
//     u16* var_s0_4;
//     u32 temp_s0_2;
//     u32 temp_v0_5;
//     u32 temp_v1_12;
//     u32 var_s6;
//     u32 var_v0_2;
//     u32 var_v0_6;
//     u8 temp_a0_3;
//     u8 temp_a0_4;
//     u8 temp_a3_3;
//     u8 temp_v0_17;
//     u8 temp_v0_18;
//     u8 temp_v1_10;
//     u8 temp_v1_13;
//     u8 temp_v1_14;
//     u8 temp_v1_2;
//     u8 var_v0_5;
//     u8* var_a1;
//     u8* var_s1;
//     void* temp_v1_3;
//     void* var_v1_4;

//     var_fp = saved_reg_fp;
//     var_a2 = (s32* )0x1F800000;
//     var_s4 = (s32* )0x1F8000C0;
//     sp28 = g_Entities;
//     if (1 != 0) {
//         var_a1 = &g_Entities->hitboxHeight;
//         do {
//             temp_v0 = var_a1->unk-B;
//             *var_a2 = (s32) temp_v0;
//             if ((temp_v0 != 0) && !(temp_v0 & 0x80)) {
//                 temp_v1 = var_a1->unk-45;
//                 *var_s4 = (s32) temp_v1;
//                 if (var_a1->unk-33 != 0) {
//                     var_v0 = temp_v1 - var_a1->unk-37;
//                 } else {
//                     var_v0 = var_a1->unk-37 + temp_v1;
//                 }
//                 *var_s4 = var_v0;
//                 temp_s3 = var_a1->unk-41 + var_a1->unk-35;
//                 if (((u32) (*var_s4 + 0x20) >= 0x141U) || ((u32) (temp_s3 + 0x20) >= 0x121U) || (temp_v1_2 = var_a1->unk-1, (temp_v1_2 == 0)) || (var_a1->unk0 == 0)) {
//                     *var_a2 = 0;
//                     goto block_13;
//                 }
//                 temp_s4 = var_s4 + 4;
//                 *temp_s4 = (s32) temp_v1_2;
//                 temp_s4_2 = temp_s4 + 4;
//                 *temp_s4_2 = temp_s3;
//                 temp_s4_3 = temp_s4_2 + 4;
//                 *temp_s4_3 = (s32) var_a1->unk0;
//                 var_s4 = temp_s4_3 + 4;
//             } else {
// block_13:
//                 var_s4 += 0x10;
//             }
//             var_a1 += 0xBC;
//             temp_a3 = &sp28[1];
//             sp28 = temp_a3;
//         } while ((u32) temp_a3 < (u32) &D_80075718);
//     }
//     sp28 = &D_800762D8;
//     if (1 != 0) {
//         var_s7 = &D_800762D8.hitPoints;
//         do {
//             temp_s5 = var_s7->unk-2;
//             if ((temp_s5 != 0) && (var_s7->unk8 != 0) && (var_s7->unk9 != 0) && (var_s0 = 0, ((var_s7->unk-A & 0x100) == 0))) {
//                 do {
//                     temp_v0_2 = var_s0 & 0xFFFF;
//                     temp_v1_3 = sp28 + temp_v0_2;
//                     var_s0 += 1;
//                     if (sp28->unk6D[temp_v0_2] != 0) {
//                         temp_v1_3->unk6D = (u8) (temp_v1_3->unk6D - 1);
//                     }
//                 } while ((u32) (var_s0 & 0xFFFF) < 0xBU);
//                 temp_s6 = var_s7->unk-3C;
//                 if (var_s7->unk-2A != 0) {
//                     var_v0_2 = temp_s6 - var_s7->unk-2E;
//                 } else {
//                     var_v0_2 = temp_s6 + var_s7->unk-2E;
//                 }
//                 var_s6 = var_v0_2;
//                 if (((u32) ((var_s6 + 0x1F) & 0xFFFF) < 0x13FU) && (temp_s2 = temp_s5 & 0x3E, (((u32) ((var_s7->unk-38 + var_s7->unk-2C + 0x1F) & 0xFFFF) < 0x11FU) != 0))) {
//                     sp30 = 0;
//                     temp_s3_2 = var_s7->unk9 - 1;
//                     sp20 = var_s7->unk8 - 1;
//                     if (temp_s2 != 0) {
//                         var_a2_2 = (s32* )0x1F800004;
//                         var_fp = &g_Entities_1;
//                         var_s4 = (s32* )0x1F8000D0;
//                         if (1 != 0) {
//                             var_s1 = &g_Entities_1.hitFlags;
// loop_33:
//                             temp_v1_4 = *var_a2_2;
//                             if ((temp_s2 & 0xFFFF & temp_v1_4) && (sp28->unk6D[var_s1->unk-E] == 0)) {
//                                 if (!(temp_v1_4 & 0x80)) {
//                                     temp_s4_4 = var_s4 + 4;
//                                     temp_s4_5 = temp_s4_4 + 4;
//                                     if ((u32) ((sp20 + *temp_s4_4) * 2) >= (u16) subroutine_arg6) {
//                                         temp_s4_6 = temp_s4_5 + 4;
//                                         var_s4 = temp_s4_6 + 4;
//                                         if ((u32) ((temp_s3_2 + *temp_s4_6) * 2) >= (u16) subroutine_arg6) {
//                                             temp_s0 = var_s1->unk22 & 0x7F;
//                                             if (!(var_s1->unk-14 & var_s7->unk-A & 0x100000)) {
//                                                 var_s1->unk70 = sp28;
//                                                 if (temp_s5 & 8) {
//                                                     var_s1->unk0 = 3;
//                                                 } else {
//                                                     var_s1->unk0 = 1;
//                                                 }
//                                                 var_v1 = temp_s0 & 0xFFFF;
//                                                 if ((temp_s0 & 0xFFFF) == 3) {
//                                                     if (var_s7->unk-A & 0x8000) {
//                                                         g_api_PlaySfx(0x611);
//                                                         var_s1->unk0 = 2;
//                                                         var_v1 = temp_s0 & 0xFFFF;
//                                                     }
//                                                 }
//                                                 if ((var_v1 == 4) && (var_s7->unk-A & 0x4000)) {
//                                                     g_api_PlaySfx(0x611);
//                                                     var_s1->unk0 = 2;
//                                                 }
//                                             }
//                                             var_s7->unk6 = temp_s0;
//                                             sp30 = 0xFF;
//                                         } else {
//                                             var_a2_2 += 4;
//                                             goto block_54;
//                                         }
//                                     } else {
//                                         var_a2_2 += 4;
//                                         var_s4 = temp_s4_5 + 8;
//                                         goto block_54;
//                                     }
//                                 } else {
//                                     sp30 = 0xFF;
//                                     var_s7->unk6 = (u16) (var_fp->hitEffect & 0x7F);
//                                 }
//                             } else {
//                                 var_a2_2 += 4;
//                                 var_s4 += 0x10;
// block_54:
//                                 var_fp += 0xBC;
//                                 var_s1 += 0xBC;
//                                 if ((u32) var_fp < (u32) &D_80075718) {
//                                     goto loop_33;
//                                 }
//                             }
//                         }
//                     }
//                     if (temp_s5 & 1) {
//                         if (sp30 == 0) {
//                             var_fp = g_Entities;
//                             var_s4 = (s32* )0x1F8000C0;
//                             if ((sp28->unk6D[D_80073412] == 0) && (*(s32* )0x1F800000 & 1)) {
//                                 var_s4 = (s32* )0x1F8000C8;
//                                 if ((u32) ((sp20 + *(s32* )0x1F8000C4) * 2) >= (u16) subroutine_arg6) {
//                                     var_s4 = (s32* )0x1F8000D0;
//                                     if ((u32) ((temp_s3_2 + *(s32* )0x1F8000CC) * 2) >= (u16) subroutine_arg6) {
//                                         temp_v1_5 = var_s7->unk2;
//                                         if ((temp_v1_5 != 0) && (D_80073416 < temp_v1_5)) {
//                                             D_80073490 = sp28;
//                                             if (temp_s5 & 8) {
//                                                 D_80073420 = 3;
//                                             } else {
//                                                 D_80073420 = 1;
//                                             }
//                                             g_Entities->unk44 = var_s7->unk4;
//                                             g_Entities->hitPoints = (s16) (u16) var_s7->unk2;
//                                         }
//                                         sp30 = 0xFF;
//                                         var_s7->unkA = 0x80U;
//                                         var_s7->unk6 = (u16) (g_Entities->hitEffect & 0x7F);
//                                     }
//                                 }
//                             }
//                             goto block_68;
//                         }
//                         goto block_69;
//                     }
// block_68:
//                     if (sp30 != 0) {
// block_69:
//                         temp_a0 = var_s7->unk1E;
//                         var_s3 = temp_a0;
//                         if (temp_a0 != NULL) {
//                             var_s3->unk44 = var_s7->unk6;
//                             var_s3->hitFlags = var_s7->unkA;
//                         } else {
//                             var_s3 = sp28;
//                         }
//                         if (!(var_s3->flags & 0x100) && (sp30 != 0)) {
//                             if ((subroutine_arg6 == 2) || ((subroutine_arg6 == 6) && (temp_s5 & 0x20))) {
//                                 temp_v0_3 = AllocEntity(&D_8007A958, &D_8007A958 + 0x1780);
//                                 if (temp_v0_3 != NULL) {
//                                     CreateEntityFromEntity(7U, sp28, temp_v0_3);
//                                 }
//                             }
//                             temp_s5_2 = *(&D_80180A4C + (var_s3->enemyId * 2));
//                             if (temp_s5_2 != 0) {
//                                 temp_v0_4 = temp_s5_2 + 0xFFFF;
//                                 temp_v0_5 = (u32) (temp_v0_4 & 0xFFFF) >> 3;
//                                 *(&D_8003BF7C + temp_v0_5) = *(&D_8003BF7C + temp_v0_5) | (1 << (temp_v0_4 & 7));
//                             }
//                             if ((g_Status_relics_15 & 2) && !(var_s3->flags & 0x01000000)) {
//                                 if (D_80097410 != 0) {
//                                     g_api_FreePrimitives(D_80097414);
//                                     D_80097410 = 0;
//                                 }
//                                 func_801A7D78(g_api_enemyDefs[var_s3->enemyId].name, 0);
//                                 var_s3->flags |= 0x01000000;
//                             }
//                             sp30 = 0;
//                             if ((!(var_s7->unk-2 & 8) || !(var_fp->hitboxState & 4)) && (var_s3->hitPoints != 0)) {
//                                 var_s5 = 0;
//                                 if (var_fp->attack != 0) {
//                                     if (!(var_fp->hitboxState & 0x80)) {
//                                         temp_s4_7 = var_s4 - 0x10;
//                                         temp_v0_6 = *temp_s4_7;
//                                         var_s4 = temp_s4_7 + 8;
//                                         temp_v0_7 = var_s6 + temp_v0_6;
//                                         var_s6 = (u32) (temp_v0_7 + ((u32) (temp_v0_7 << 0x10) >> 0x1F)) >> 1;
//                                     }
//                                     var_s0_2 = &g_PrimBuf[g_unkGraphicsStruct.D_800973F8];
//                                     if (var_s0_2 != NULL) {
// loop_93:
//                                         if (var_s0_2->drawMode == 8) {
//                                             var_s0_2->clut = 0x199;
//                                             temp_v0_8 = var_s6 + ((Random() & 7) - 0xD);
//                                             temp_v1_6 = temp_v0_8 - 3;
//                                             temp_v0_9 = temp_v0_8 + 0x1D;
//                                             var_s0_2->x2 = temp_v1_6;
//                                             var_s0_2->x0 = temp_v1_6;
//                                             var_s0_2->x3 = temp_v0_9;
//                                             var_s0_2->x1 = temp_v0_9;
//                                             temp_v0_10 = (Random() & 7) - 0xA;
//                                             var_s0_2->p1 = 0;
//                                             temp_v0_11 = subroutine_arg4 + temp_v0_10;
//                                             temp_v1_7 = temp_v0_11 - 3;
//                                             temp_v0_12 = temp_v0_11 + 0x1D;
//                                             var_s0_2->y1 = temp_v1_7;
//                                             var_s0_2->y0 = temp_v1_7;
//                                             var_s0_2->y3 = temp_v0_12;
//                                             var_s0_2->y2 = temp_v0_12;
//                                             if ((u16) var_s7->unk-1A < (u16) var_fp->zPriority) {
//                                                 var_v0_3 = var_fp->zPriority + 1;
//                                             } else {
//                                                 var_v0_3 = var_s7->unk-1A + 1;
//                                             }
//                                             var_s0_2->priority = var_v0_3;
//                                             var_s0_2->drawMode = 2;
//                                         } else {
//                                             var_s0_2 = var_s0_2->next;
//                                             if (var_s0_2 != NULL) {
//                                                 goto loop_93;
//                                             }
//                                         }
//                                     }
//                                     if (var_fp->attack != 0) {
//                                         var_s5 = 0;
//                                         if (var_s3->hitPoints != 0x7FFF) {
//                                             var_s5 = g_api_DealDamage(sp28, var_fp);
//                                             if (var_fp->hitboxState == 4) {
//                                                 var_s5 = 0;
//                                             }
//                                             if ((g_Status_relics_11 & 2) && !(var_s3->flags & 0x04000000)) {
//                                                 var_v1_2 = var_s5 & 0xFFFF;
//                                                 if (var_s5 & 0xFFFF) {
//                                                     temp_v0_13 = AllocEntity(&D_8007D858, &D_8007D858 + 0x1780);
//                                                     var_v1_2 = var_s5 & 0xFFFF;
//                                                     if (temp_v0_13 != NULL) {
//                                                         DestroyEntity(temp_v0_13);
//                                                         temp_v0_13->entityId = 4;
//                                                         temp_v0_13->pfnUpdate = func_8019F3C0;
//                                                         temp_v0_13->posX.i.hi = (s16) var_s6;
//                                                         temp_v0_13->params = var_s5;
//                                                         temp_v0_13->posY.i.hi = (s16) subroutine_arg4;
//                                                         goto block_109;
//                                                     }
//                                                 }
//                                             } else {
//                                                 goto block_109;
//                                             }
//                                         } else {
//                                             goto block_109;
//                                         }
//                                     } else {
//                                         var_s5 = 0;
//                                         goto block_109;
//                                     }
//                                 } else {
// block_109:
//                                     var_v1_2 = var_s5 & 0xFFFF;
//                                 }
//                                 if (var_v1_2 != 0xC000) {
//                                     if (var_s5 & 0x8000) {
//                                         sp30 = 9;
//                                         goto block_120;
//                                     }
//                                     temp_s2_2 = (u16) var_fp->attackElement;
//                                     var_s0_3 = 0;
//                                     if (temp_s2_2 & 0xFFC0) {
//                                         var_v1_3 = 0 & 0xFFFF;
// loop_115:
//                                         var_s0_3 += 1;
//                                         if (!(temp_s2_2 & *((var_v1_3 * 2) + &D_80180D80))) {
//                                             var_v1_3 = var_s0_3 & 0xFFFF;
//                                             if ((u32) (var_s0_3 & 0xFFFF) >= 0xAU) {
//                                                 var_v0_4 = var_s5 & 0xFFFF;
//                                             } else {
//                                                 goto loop_115;
//                                             }
//                                         } else {
//                                             sp30 = *(&D_80180D94 + var_v1_3);
//                                             goto block_120;
//                                         }
//                                     } else {
//                                         goto block_120;
//                                     }
//                                 } else {
//                                     var_s5 = 0;
//                                     var_s3->hitFlags |= 0x20;
// block_120:
//                                     var_v0_4 = var_s5 & 0xFFFF;
//                                 }
//                                 if (var_v0_4 != 0) {
//                                     if (var_s5 & 0x8000) {
//                                         temp_v1_8 = (u16) var_s3->hitPoints + (var_s5 & 0x3FFF);
//                                         var_s3->hitPoints = temp_v1_8;
//                                         temp_s2_3 = (u16) g_api_enemyDefs[var_s3->enemyId].hitPoints;
//                                         if ((s32) temp_s2_3 < temp_v1_8) {
//                                             var_s3->hitPoints = (s16) temp_s2_3;
//                                         }
//                                     } else {
//                                         temp_s5_3 = var_s5 & 0x3FFF;
//                                         if (var_s3->flags & 0x10) {
//                                             var_a0 = 0x705;
//                                             if (g_PlayableCharacter != 0) {

//                                             } else {
//                                                 var_a0 = 0x62E;
//                                                 if (var_fp->hitEffect & 0x80) {

//                                                 } else {
//                                                     var_a0 = 0x678;
//                                                 }
//                                             }
//                                             g_api_PlaySfx(var_a0);
//                                         }
//                                         temp_v1_9 = var_s3->hitPoints;
//                                         temp_a0_2 = temp_s5_3 & 0xFFFF;
//                                         if (temp_v1_9 != 0x7FFE) {
//                                             if (temp_v1_9 < (temp_a0_2 * 2)) {
//                                                 var_v0_5 = var_s3->hitFlags | 3;
//                                             } else if (temp_v1_9 < (temp_a0_2 * 4)) {
//                                                 var_v0_5 = var_s3->hitFlags | 2;
//                                             } else {
//                                                 var_v0_5 = var_s3->hitFlags | 1;
//                                             }
//                                             var_s3->hitFlags = var_v0_5;
//                                             var_s3->hitPoints = (u16) var_s3->hitPoints - temp_s5_3;
//                                         }
//                                         if (((u16) var_fp->attackElement & 0x40) && (var_s3->hitboxState & 0x10)) {
//                                             temp_v0_14 = AllocEntity(&D_8007A958, &D_8007A958 + 0x1780);
//                                             if (temp_v0_14 != NULL) {
//                                                 CreateEntityFromEntity(0xDU, sp28, temp_v0_14);
//                                                 if ((s16) var_s7->unk-3C < (s16) var_s6) {
//                                                     temp_v0_14->params = 1;
//                                                 }
//                                                 temp_v0_14->posX.i.hi = (s16) var_s6;
//                                                 temp_v0_14->posY.i.hi = (s16) subroutine_arg4;
//                                                 temp_v0_14->zPriority = 0xC0;
//                                             }
//                                         }
//                                     }
//                                     var_s1_2 = var_s3;
//                                     if (var_s3->hitPoints > 0) {
//                                         temp_a1 = var_fp->enemyId;
//                                         var_v1_4 = var_s1_2 + temp_a1;
// loop_147:
//                                         temp_a0_3 = var_fp->nFramesInvincibility;
//                                         var_v1_4->unk6D = temp_a0_3;
//                                         if ((u32) var_s3 < (u32) var_s1_2) {
//                                             var_v1_4->unk6D = (u8) (temp_a0_3 + 1);
//                                         }
//                                         if (!(var_s7->unk-A & 0x400000)) {
//                                             var_s1_2->stunFrames = (s16) (u16) var_fp->stunFrames;
//                                         }
//                                         if ((var_s1_2->hitEffect == 0) && !(var_s1_2->flags & 0xF)) {
//                                             var_s1_2->hitEffect = var_s1_2->palette;
//                                         }
//                                         var_s1_2->nFramesInvincibility = sp30;
//                                         var_s1_2->flags |= 0xF;
//                                         var_s1_2 = var_s1_2->unk60;
//                                         if (var_s1_2 != NULL) {
//                                             var_v1_4 = var_s1_2 + temp_a1;
//                                             if (var_s1_2 == var_s3) {
//                                                 var_s7 += 0xBC;
//                                             } else {
//                                                 goto loop_147;
//                                             }
//                                         } else {
//                                             goto block_200;
//                                         }
//                                     } else {
//                                         goto block_157;
//                                     }
//                                 } else {
//                                     temp_v1_10 = var_s3->hitFlags;
//                                     if (!(temp_v1_10 & 0xF)) {
//                                         var_s3->hitFlags = temp_v1_10 | 0x10;
//                                     }
//                                     var_s1_3 = var_s3;
//                                     if ((var_s3->flags & 0x10) && (var_fp->attack != 0)) {
//                                         g_api_PlaySfx(0x611);
//                                     }
//                                     temp_a1_2 = var_fp->enemyId;
// loop_194:
//                                     temp_v1_11 = var_s7->unk0;
//                                     if ((temp_v1_11 != 0x7FFF) || (var_s1_3->hitPoints == temp_v1_11)) {
//                                         temp_a0_4 = var_fp->nFramesInvincibility;
//                                         var_s1_3->unk6D[temp_a1_2] = temp_a0_4;
//                                         if ((u32) var_s3 < (u32) var_s1_3) {
//                                             var_s1_3->unk6D[temp_a1_2] = temp_a0_4 + 1;
//                                         }
//                                     }
//                                     var_s1_3 = var_s1_3->unk60;
//                                     if ((var_s1_3 != NULL) && (var_s1_3 != var_s3)) {
//                                         goto loop_194;
//                                     }
//                                     goto block_200;
//                                 }
//                             } else {
// block_157:
//                                 PreventEntityFromRespawning(var_s3);
//                                 temp_s6_2 = &g_api_enemyDefs[var_s3->enemyId];
//                                 if (!(var_s3->hitFlags & 0x80)) {
//                                     g_api_func_800FE044((s32) temp_s6_2->exp, (s32) temp_s6_2->level);
//                                     if ((var_s3->flags & 0x1000) && (g_Status_killCount <= 0xF423E)) {
//                                         g_Status_killCount += 1;
//                                     }
//                                 }
//                                 temp_s0_2 = (u16) var_s3->unk34 & 0xC00;
//                                 var_s1_4 = var_s3;
//                                 if (temp_s0_2 != 0) {
//                                     temp_s0_3 = rand() & 0xFF;
//                                     var_s1_4 = var_s3;
//                                     if (temp_s0_3 < g_api_func_800FF460((s32) *(&D_80180D6C + (temp_s0_2 >> 0xA)))) {
//                                         temp_v0_15 = AllocEntity(&D_8007A958, &D_8007A958 + 0x1780);
//                                         var_s5_2 = 0;
//                                         if (temp_v0_15 != NULL) {
//                                             if (subroutine_arg6 == 5) {
//                                                 var_s0_4 = &D_80180DE0;
//                                                 temp_v1_12 = rand() & 0xFFF;
// loop_166:
//                                                 temp_s0_4 = var_s0_4 + 2;
//                                                 if ((u16) *var_s0_4 < temp_v1_12) {
//                                                     var_s0_4 = temp_s0_4 + 2;
//                                                     goto loop_166;
//                                                 }
//                                                 var_s2 = *temp_s0_4;
//                                                 var_v0_6 = var_s2 & 0xFFFF;
//                                             } else {
//                                                 temp_v0_16 = g_api_func_800FF494(temp_s6_2);
//                                                 if (temp_v0_16 & 0x40) {
//                                                     var_s2 = temp_s6_2->rareItemId;
//                                                     if (((var_s2 & 0xFFFF) == 0x173) && (g_IsTimeAttackUnlocked == 0)) {
//                                                         var_s2 = 0x16A;
//                                                         goto block_177;
//                                                     }
//                                                     var_s5_2 = *(&D_80180A4C + (var_s3->enemyId * 2));
//                                                     var_v0_6 = var_s2 & 0xFFFF;
//                                                 } else if (temp_v0_16 & 0x20) {
//                                                     var_s2 = temp_s6_2->uncommonItemId;
//                                                     var_v0_6 = var_s2 & 0xFFFF;
//                                                 } else {
//                                                     var_s2 = *(&D_80180DA0 + ((temp_v0_16 & 0xFFFF) * 2));
// block_177:
//                                                     var_v0_6 = var_s2 & 0xFFFF;
//                                                 }
//                                             }
//                                             var_a0_2 = 3;
//                                             if (var_v0_6 >= 0x80U) {
//                                                 var_s2 -= 0x80;
//                                                 var_a0_2 = 0xA;
//                                             }
//                                             CreateEntityFromEntity(var_a0_2, sp28, temp_v0_15);
//                                             temp_v0_15->ext.heartDrop.unk[6] = var_s5_2 & 0xFFFF;
//                                             temp_v0_15->params = var_s2;
//                                             temp_v0_15->velocityY = -0x38000;
//                                         }
//                                         var_s1_4 = var_s3;
//                                     }
//                                 }
// loop_183:
//                                 var_s1_4->flags = (var_s1_4->flags | 0x10C100) & 0xDFFFFFFF;
//                                 if (var_s1_4->hitEffect == 0) {
//                                     var_s1_4->hitEffect = var_s1_4->palette;
//                                 }
//                                 var_s1_4->nFramesInvincibility = sp30;
//                                 var_s1_4->flags |= 0xF;
//                                 var_s1_4 = var_s1_4->unk60;
//                                 if (var_s1_4 != NULL) {
//                                     if (var_s1_4 == var_s3) {
//                                         var_s7 += 0xBC;
//                                     } else {
//                                         goto loop_183;
//                                     }
//                                 } else {
//                                     goto block_200;
//                                 }
//                             }
//                         } else {
//                             goto block_200;
//                         }
//                     } else {
//                         goto block_200;
//                     }
//                 } else {
//                     goto block_200;
//                 }
//             } else {
// block_200:
//                 var_s7 += 0xBC;
//             }
//             temp_a3_2 = &sp28[1];
//             sp28 = temp_a3_2;
//         } while ((u32) temp_a3_2 < (u32) &D_8007C0D8);
//     }
//     var_s0_5 = &g_PrimBuf[g_unkGraphicsStruct.D_800973F8];
//     if (var_s0_5 != NULL) {
//         do {
//             if (var_s0_5->drawMode != 8) {
//                 temp_a3_3 = var_s0_5->p1;
//                 sp30 = temp_a3_3;
//                 temp_v0_17 = *(&D_80180D70 + sp30);
//                 temp_v1_13 = temp_v0_17 + 0x20;
//                 var_s0_5->u2 = temp_v0_17;
//                 var_s0_5->u0 = temp_v0_17;
//                 var_s0_5->u3 = temp_v1_13;
//                 var_s0_5->u1 = temp_v1_13;
//                 temp_v0_18 = *(&D_80180D78 + sp30);
//                 sp30 = temp_a3_3 + 1;
//                 temp_v1_14 = temp_v0_18 + 0x20;
//                 var_s0_5->v1 = temp_v0_18;
//                 var_s0_5->v0 = temp_v0_18;
//                 var_s0_5->v3 = temp_v1_14;
//                 var_s0_5->v2 = temp_v1_14;
//                 if (sp30 >= 7U) {
//                     var_s0_5->drawMode = 8;
//                 } else {
//                     var_s0_5->p1 = sp30;
//                 }
//             }
//             var_s0_5 = var_s0_5->next;
//         } while (var_s0_5 != NULL);
//     }
// }
//#endif
//#ifndef NON_MATCHING
INCLUDE_ASM("st/chi/nonmatchings/1CBA8", func_8019F3C0);    // EntityDamageDisplay()
//#else
// extern /*?*/s32 D_80180DFC;
// extern u16 EntityInit_80180670;
// extern s32 PLAYER_posY_val;

// void func_8019F3C0(Entity* arg0)
// {
//     Primitive* var_a3;
//     Primitive* var_a3_2;
//     s16 temp_a0_5;
//     s16 temp_a0_6;
//     s16 temp_a1_3;
//     s16 temp_a2_2;
//     s16 temp_v0;
//     s16 temp_v0_4;
//     s16 temp_v1_7;
//     s16 var_t0;
//     s32 temp_a1;
//     s32 temp_a1_4;
//     s32 temp_a2;
//     s32 temp_t0;
//     s32 temp_t0_2;
//     s32 temp_v0_3;
//     s32 temp_v1_3;
//     s32 temp_v1_4;
//     s32 temp_v1_6;
//     s32 var_a0;
//     s32 var_t2;
//     s32 var_v0;
//     s32 var_v0_2;
//     s32 var_v1;
//     s8 temp_a0;
//     s8 temp_a0_2;
//     s8 temp_a0_3;
//     u16 temp_a0_4;
//     u16 temp_s1;
//     u16 temp_t0_3;
//     u16 temp_v1;
//     u16 temp_v1_2;
//     u16 temp_v1_5;
//     u16 var_v0_4;
//     u16 var_v0_5;
//     u16 var_v0_6;
//     u16 var_v1_2;
//     u16* temp_s2;
//     u8 temp_a1_2;
//     u8 temp_v0_2;
//     u8 var_v0_3;

//     if (arg0->ext.factory.unk88 != 0) {
//         arg0->posX.val = g_Entities->posX.val;
//         arg0->posY.val = PLAYER_posY_val + 0xFFF00000;
//     }
//     temp_v1 = arg0->step;
//     switch (temp_v1) {                              // irregular
//         case 0:
//             temp_v1_2 = arg0->step_s;
//             if (temp_v1_2 != 9) {
//                 temp_s1 = arg0->params;
//                 temp_s2 = arg0 + 0x7E;
//                 if (temp_v1_2 == 0) {
//                     InitializeEntity(&EntityInit_80180670);
//                     arg0->step = 0;
//                     if ((temp_s1 & 0xFFFF) != 0xC000) {
//                         temp_a0 = (temp_s1 & 0x3FFF) / 1000;
//                         temp_a1 = temp_a0 & 0xFFFF;
//                         var_v0 = temp_a1 << 5;
//                         if (temp_a1 != 0) {
//                             arg0->ext.timer.t += 1;
//                             arg0->ext.factory.unk7E += 1;
//                             var_v0 = temp_a1 << 5;
//                         }
//                         temp_t0 = (temp_s1 & 0x3FFF) - ((((var_v0 - temp_a1) * 4) + temp_a1) * 8);
//                         arg0->ext.stub[4] = temp_a0;
//                         temp_a0_2 = (temp_t0 & 0xFFFF) / 100;
//                         if ((temp_a0_2 & 0xFFFF) || (var_v1 = temp_a0_2 & 0xFFFF, (arg0->ext.factory.unk7E != 0))) {
//                             arg0->ext.timer.t += 1;
//                             arg0->ext.factory.unk7E += 1;
//                             var_v1 = temp_a0_2 & 0xFFFF;
//                         }
//                         temp_t0_2 = temp_t0 - (var_v1 * 0x64);
//                         arg0->ext.stub[5] = temp_a0_2;
//                         temp_a0_3 = (temp_t0_2 & 0xFFFF) / 10;
//                         if ((temp_a0_3 & 0xFFFF) || (*temp_s2 != 0)) {
//                             arg0->ext.timer.t += 1;
//                             *temp_s2 += 1;
//                         }
//                         arg0->ext.stub[6] = temp_a0_3;
//                         arg0->ext.timer.t += 1;
//                         *temp_s2 += 1;
//                         arg0->ext.stub[7] = temp_t0_2 - ((temp_a0_3 & 0xFFFF) * 0xA);
//                         if (temp_s1 & 0x4000) {
//                             goto block_17;
//                         }
//                     } else {
// block_17:
//                         arg0->ext.timer.t += 1;
//                     }
//                 }
//                 temp_v0 = g_api_AllocPrimitives(PRIM_GT4, (s32) arg0->ext.timer.t);
//                 if (temp_v0 != 0) {
//                     var_a3 = &g_PrimBuf[temp_v0];
//                     var_t2 = 0;
//                     arg0->primIndex = (s32) temp_v0;
//                     arg0->flags |= 0x800000;
//                     var_a0 = 4 - *temp_s2;
//                     var_t0 = -(*temp_s2 * 2);
//                     if (var_a3 != NULL) {
//                         temp_v1_3 = temp_s1 & 0x4000;
//                         var_v0_2 = 0 & 0xFFFF;
//                         do {
//                             if (var_v0_2 == 0) {
//                                 var_t2 += 1;
//                                 if ((temp_s1 & 0xC000) == 0xC000) {
//                                     var_a3->u2 = 0x43;
//                                     var_a3->u0 = 0x43;
//                                     var_a3->u3 = 0x59;
//                                     var_a3->u1 = 0x59;
//                                     var_a3->v1 = 0x4A;
//                                     var_a3->v0 = 0x4A;
//                                     var_a3->v3 = 0x52;
//                                     var_a3->v2 = 0x52;
//                                     var_a3->unk1C = 0xB;
//                                     var_a3->unk1E = 5;
//                                     var_a3->unk10 = 0;
//                                     var_a3->unk12 = -0x10;
//                                     goto block_33;
//                                 }
//                                 if (temp_v1_3 != 0) {
//                                     var_a3->u2 = 0x20;
//                                     var_a3->u0 = 0x20;
//                                     var_a3->u3 = 0x42;
//                                     var_a3->u1 = 0x42;
//                                     var_a3->unk1C = 0x11;
//                                     var_a3->v1 = 0x4A;
//                                     var_a3->v0 = 0x4A;
//                                     var_a3->v3 = 0x52;
//                                     var_a3->v2 = 0x52;
//                                     var_a3->unk1E = 5;
//                                     var_a3->unk10 = 0;
//                                     var_a3->unk12 = -0x18;
//                                     goto block_33;
//                                 }
//                             } else {
//                                 var_a3->unk10 = var_t0;
//                                 var_a3->unk12 = -0x10;
//                                 if (temp_v1_3 != 0) {
//                                     var_a3->unk1C = 3;
//                                     var_a3->unk1E = 5;
//                                 } else {
//                                     var_a3->unk1C = 0x17;
//                                     var_a3->unk1E = 0;
//                                 }
//                                 temp_v0_2 = (arg0 + (var_a0 & 0xFFFF))->unk80;
//                                 temp_v0_3 = temp_v0_2 * 8;
//                                 if (temp_v0_2 != 0) {
//                                     temp_a1_2 = temp_v0_3 + 0x18;
//                                     var_v0_3 = temp_v0_3 + 0x1E;
//                                     var_a3->u2 = temp_a1_2;
//                                     var_a3->u0 = temp_a1_2;
//                                 } else {
//                                     var_a3->u2 = 0x68;
//                                     var_a3->u0 = 0x68;
//                                     var_v0_3 = 0x6E;
//                                 }
//                                 var_a3->u3 = var_v0_3;
//                                 var_a3->u1 = var_v0_3;
//                                 var_t0 += 4;
//                                 var_a0 += 1;
//                                 var_a3->v1 = 0x40;
//                                 var_a3->v0 = 0x40;
//                                 var_a3->v3 = 0x49;
//                                 var_a3->v2 = 0x49;
// block_33:
//                                 var_a3->tpage = 0x1A;
//                                 var_a3->priority = 0x1F8;
//                                 var_a3->drawMode = 8;
//                                 var_a3 = var_a3->next;
//                             }
//                             var_v0_2 = var_t2 & 0xFFFF;
//                         } while (var_a3 != NULL);
//                     }
//                     arg0->step_s = 0;
//                     arg0->ext.factory.unk84 = 0x40;
//                     arg0->step += 1;
//                 }
//                 arg0->step_s += 1;
//                 return;
//             }
// block_38:
//             DestroyEntity(arg0);
//             return;
//         case 1:
//             temp_a0_4 = arg0->ext.factory.unk84 + 0xFFFF;
//             arg0->ext.factory.unk84 = temp_a0_4;
//             if (!(temp_a0_4 & 0xFFFF)) {
//                 goto block_38;
//             }
//             var_a3_2 = &g_PrimBuf[arg0->primIndex];
//             temp_v1_4 = ((u16) arg0->params >> 0xD) & 6;
//             temp_t0_3 = *(&D_80180DFC + ((temp_v1_4 | (temp_a0_4 & 1)) * 2));
//             if ((temp_v1_4 != 0) && (temp_v1_4 != 4)) {
//                 if (var_a3_2 != NULL) {
//                     do {
//                         temp_v1_5 = arg0->ext.factory.unk84;
//                         if (temp_v1_5 >= 0x3CU) {
//                             var_v0_4 = var_a3_2->unk1C + 1;
//                             var_v1_2 = var_a3_2->unk1E + 1;
//                             goto block_47;
//                         }
//                         if (temp_v1_5 >= 0x38U) {
//                             var_v0_4 = var_a3_2->unk1C + 0xFFFF;
//                             var_v1_2 = var_a3_2->unk1E + 0xFFFF;
// block_47:
//                             var_a3_2->unk1C = var_v0_4;
//                             var_a3_2->unk1E = var_v1_2;
//                         }
//                         temp_v1_6 = arg0->posX.i.hi + var_a3_2->unk10;
//                         temp_a1_3 = temp_v1_6 - var_a3_2->unk1C;
//                         temp_a0_5 = var_a3_2->unk1C + temp_v1_6;
//                         var_a3_2->clut = temp_t0_3;
//                         var_a3_2->x2 = temp_a1_3;
//                         var_a3_2->x0 = temp_a1_3;
//                         var_a3_2->x3 = temp_a0_5;
//                         var_a3_2->x1 = temp_a0_5;
//                         temp_a2 = arg0->posY.i.hi + var_a3_2->unk12;
//                         temp_v1_7 = var_a3_2->unk1E + temp_a2;
//                         var_a3_2->y3 = temp_v1_7;
//                         var_a3_2->y2 = temp_v1_7;
//                         temp_v0_4 = temp_a2 - var_a3_2->unk1E;
//                         var_a3_2->y1 = temp_v0_4;
//                         var_a3_2->y0 = temp_v0_4;
//                         var_v0_5 = 0x13;
//                         if ((u16) arg0->ext.factory.unk84 >= 6U) {
//                             var_v0_5 = 2;
//                         }
//                         var_a3_2->drawMode = var_v0_5;
//                         var_a3_2 = var_a3_2->next;
//                     } while (var_a3_2 != NULL);
//                 }
//                 if (arg0->ext.factory.unk88 != 0) {
//                     return;
//                 }
//                 goto block_61;
//             }
//             if (var_a3_2 != NULL) {
//                 do {
//                     if ((u16) var_a3_2->unk1C >= 4U) {
//                         var_a3_2->unk1C = (u16) (var_a3_2->unk1C - 1);
//                     }
//                     if ((u16) var_a3_2->unk1E < 0xAU) {
//                         var_a3_2->unk1E = (u16) (var_a3_2->unk1E + 1);
//                     }
//                     var_a3_2->clut = temp_t0_3;
//                     temp_a0_6 = (arg0->posY.i.hi + var_a3_2->unk12) - (var_a3_2->unk1E - 5);
//                     temp_a2_2 = var_a3_2->unk1E + temp_a0_6;
//                     var_a3_2->y1 = temp_a0_6;
//                     var_a3_2->y0 = temp_a0_6;
//                     var_a3_2->y3 = temp_a2_2;
//                     var_a3_2->y2 = temp_a2_2;
//                     temp_a1_4 = arg0->posX.i.hi + var_a3_2->unk10;
//                     var_a3_2->x1 = temp_a1_4 + var_a3_2->unk1C;
//                     var_a3_2->x0 = temp_a1_4 - var_a3_2->unk1C;
//                     var_a3_2->x2 = temp_a1_4 - 3;
//                     var_a3_2->x3 = temp_a1_4 + 3;
//                     var_v0_6 = 0x13;
//                     if ((u16) arg0->ext.factory.unk84 >= 6U) {
//                         var_v0_6 = 2;
//                     }
//                     var_a3_2->drawMode = var_v0_6;
//                     var_a3_2 = var_a3_2->next;
//                 } while (var_a3_2 != NULL);
//             }
// block_61:
//             arg0->posY.val -= 0x8000;
//             return;
//     }
// }
//#endif
//#include "../entity_damage_display.h"
//#include "../collision.h"

#include "../create_entity.h"

INCLUDE_ASM("st/chi/nonmatchings/1CBA8", func_801A05DC);    // EntityIsNearPlayer2()
INCLUDE_ASM("st/chi/nonmatchings/1CBA8", func_801A0654);    // EntityRedDoor()
//#include "../e_red_door.h"

#include "../entity.h"

INCLUDE_ASM("st/chi/nonmatchings/1CBA8", func_801A1474);    // [Duplicate]

// "Current entity" functions?
#include "../get_distance_to_player_x.h"
#include "../get_distance_to_player_y.h"
#include "../get_side_to_player.h"
#include "../move_entity.h"
#include "../fall_entity.h"

INCLUDE_ASM("st/chi/nonmatchings/1CBA8", func_801A169C);    // [Duplicate]

INCLUDE_ASM("st/chi/nonmatchings/1CBA8", func_801A1914);    // [Duplicate]

#include "../../alloc_entity.h"

INCLUDE_ASM("st/chi/nonmatchings/1CBA8", func_801A1B5C);    // [Duplicate]

INCLUDE_ASM("st/chi/nonmatchings/1CBA8", func_801A1B88);    // [Duplicate]

INCLUDE_ASM("st/chi/nonmatchings/1CBA8", func_801A1BA4);    // [Duplicate]

INCLUDE_ASM("st/chi/nonmatchings/1CBA8", func_801A1C10);    // [Duplicate]

INCLUDE_ASM("st/chi/nonmatchings/1CBA8", func_801A1C48);    // [Duplicate]

INCLUDE_ASM("st/chi/nonmatchings/1CBA8", func_801A1C90);    // [Duplicate]

#include "../adjust_value_within_threshold.h"
#include "../unk_entity_func0.h"

INCLUDE_ASM("st/chi/nonmatchings/1CBA8", func_801A1DBC);    // [Duplicate]

#include "../get_angle_between_entities.h"
INCLUDE_ASM("st/chi/nonmatchings/1CBA8", func_801A1E24);    // [Duplicate]
#include "../get_normalized_angle.h"

#include "../set_step.h"
#include "../set_sub_step.h"

INCLUDE_ASM("st/chi/nonmatchings/1CBA8", func_801A1F08);    // EntityExplosionSpawn()
//#include "../entity_explosion_spawn.h"

#include "../init_entity.h"
#include "../entity_dummy.h"

INCLUDE_ASM("st/chi/nonmatchings/1CBA8", func_801A20C0);    // [Duplicate]

#include "../check_field_collision.h"
#include "../get_player_collision_with.h"

INCLUDE_ASM("st/chi/nonmatchings/1CBA8", func_801A2684);    // ReplaceBreakableWithItemDrop()
//#include "../replace_breakable_with_item_drop.h"

INCLUDE_ASM("st/chi/nonmatchings/1CBA8", func_801A273C);    // [Duplicate]
INCLUDE_ASM("st/chi/nonmatchings/1CBA8", func_801A27C0);    // [Duplicate]
INCLUDE_ASM("st/chi/nonmatchings/1CBA8", func_801A291C);    // CollectHeart()
INCLUDE_ASM("st/chi/nonmatchings/1CBA8", func_801A299C);    // CollectGold()
INCLUDE_ASM("st/chi/nonmatchings/1CBA8", func_801A2A78);    // CollectSubweapon()
INCLUDE_ASM("st/chi/nonmatchings/1CBA8", func_801A2B90);    // CollectHeartVessel()
INCLUDE_ASM("st/chi/nonmatchings/1CBA8", func_801A2C34);    // CollectLifeVessel()
INCLUDE_ASM("st/chi/nonmatchings/1CBA8", func_801A2C84);    // DestroyCurrentEntity()

// POSSIBLE FILE BREAK

INCLUDE_ASM("st/chi/nonmatchings/1CBA8", func_801A2CAC);    // EntityPrizeDrop()
INCLUDE_ASM("st/chi/nonmatchings/1CBA8", func_801A3520);    // EntityExplosion()
//#include "../entity_explosion.h"
#include "../blink_item.h"
INCLUDE_ASM("st/chi/nonmatchings/1CBA8", func_801A36C0);    // EntityEquipItemDrop()
//#include "../e_collect.h"

#include "../blit_char.h"

INCLUDE_ASM("st/chi/nonmatchings/1CBA8", func_801A3F58);    // EntityRelicOrb()
//#include "../entity_relic_orb.h"

INCLUDE_ASM("st/chi/nonmatchings/1CBA8", func_801A4A28);    // EntityHeartDrop()

INCLUDE_ASM("st/chi/nonmatchings/1CBA8", func_801A4B50);    // EntityMessageBox()
//#include "../entity_message_box.h"

#include "../check_coll_offsets.h"

INCLUDE_ASM("st/chi/nonmatchings/1CBA8", func_801A519C);    // EntityUnkId13()
//#include "../entity_unkId13.h"

INCLUDE_ASM("st/chi/nonmatchings/1CBA8", func_801A52AC);    // EntityUnkId14Spawner()
//#include "../entity_unkId14_spawner.h"

INCLUDE_ASM("st/chi/nonmatchings/1CBA8", func_801A53DC);    // EntityUnkId15Spawner()
//#include "../entity_unkId15_spawner.h"

INCLUDE_ASM("st/chi/nonmatchings/1CBA8", func_801A54C4);    // EntityUnkId14()
//#include "../entity_unkId14.h"

INCLUDE_ASM("st/chi/nonmatchings/1CBA8", func_801A55B4);    // EntityUnkId15()
//#include "../entity_unkId15.h"

INCLUDE_ASM("st/chi/nonmatchings/1CBA8", func_801A56A8);    // EntityOlroxDrool()
//#include "../entity_olrox_drool.h"

INCLUDE_ASM("st/chi/nonmatchings/1CBA8", func_801A58D8);    // [Duplicate]

INCLUDE_ASM("st/chi/nonmatchings/1CBA8", func_801A59D4);    // [Duplicate]

INCLUDE_ASM("st/chi/nonmatchings/1CBA8", func_801A5F54);    // EntityIntenseExplosion()
//#include "../entity_intense_explosion.h"

INCLUDE_ASM("st/chi/nonmatchings/1CBA8", func_801A6054);    // [Duplicate]

// [Duplicate]
void func_801A6120(u16 entityId, Entity* src, Entity* dst)
{
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

INCLUDE_ASM("st/chi/nonmatchings/1CBA8", func_801A61E8);    // [Duplicate]

INCLUDE_ASM("st/chi/nonmatchings/1CBA8", func_801A62A0);    // EntityBigRedFireball()
//#include "../entity_big_red_fireball.h"

INCLUDE_ASM("st/chi/nonmatchings/1CBA8", func_801A6478);    // UnkRecursivePrimFunc1()
//#include "../unk_recursive_primfunc_1.h"

INCLUDE_ASM("st/chi/nonmatchings/1CBA8", func_801A6A58);    // UnkRecursivePrimFunc2()
//#include "../unk_recursive_primfunc_2.h"

#include "../clut_lerp.h"

#include "../play_sfx_with_pos_args.h"

INCLUDE_ASM("st/chi/nonmatchings/1CBA8", func_801A7448);    // EntitySoulStealOrb()
//#include "../entity_soul_steal_orb.h"

INCLUDE_ASM("st/chi/nonmatchings/1CBA8", func_801A77DC);    // EntityEnemyBlood()
//#include "../entity_enemy_blood.h"

INCLUDE_ASM("st/chi/nonmatchings/1CBA8", func_801A7C8C);    // EntityRoomForeground()
//#include "../e_room_fg.h"

#include "../bottom_corner_text.h"

INCLUDE_ASM("st/chi/nonmatchings/1CBA8", func_801A80A8);

// POSSIBLE FILE BREAK

INCLUDE_ASM("st/chi/nonmatchings/1CBA8", func_801A813C);    // [Entity]

INCLUDE_ASM("st/chi/nonmatchings/1CBA8", func_801A8DE8);    // [Entity]

INCLUDE_ASM("st/chi/nonmatchings/1CBA8", func_801A8EAC);    // [Entity]

INCLUDE_ASM("st/chi/nonmatchings/1CBA8", func_801A93D4);    // [Entity]

INCLUDE_ASM("st/chi/nonmatchings/1CBA8", func_801A9588);    // [Entity]

INCLUDE_ASM("st/chi/nonmatchings/1CBA8", func_801A97C8);    // [Entity]

INCLUDE_ASM("st/chi/nonmatchings/1CBA8", func_801A9D40);    // [Entity]

INCLUDE_ASM("st/chi/nonmatchings/1CBA8", func_801A9E94);    // [Entity]

INCLUDE_ASM("st/chi/nonmatchings/1CBA8", func_801AA020);    // [Entity]

INCLUDE_ASM("st/chi/nonmatchings/1CBA8", func_801AA390);    // [Entity]

INCLUDE_ASM("st/chi/nonmatchings/1CBA8", func_801AB0C0);    // [Entity]

INCLUDE_ASM("st/chi/nonmatchings/1CBA8", func_801AB548);

// POSSIBLE FILE BREAK

INCLUDE_ASM("st/chi/nonmatchings/1CBA8", func_801AB7CC);    // [Entity]

INCLUDE_ASM("st/chi/nonmatchings/1CBA8", func_801AC074);    // [Entity]

INCLUDE_ASM("st/chi/nonmatchings/1CBA8", func_801AC730);    // [Entity]

INCLUDE_ASM("st/chi/nonmatchings/1CBA8", func_801ACB6C);    // [Entity]

INCLUDE_ASM("st/chi/nonmatchings/1CBA8", func_801ACEF4);    // [Entity]

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
INCLUDE_ASM("st/chi/nonmatchings/1CBA8", func_801AD2BC);    // EntityStageNamePopup()
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
INCLUDE_ASM("st/chi/nonmatchings/1CBA8", func_801ADF40);    // UnkPrimHelper()
//INCLUDE_ASM("st/chi/nonmatchings/1CBA8", func_801AE328);    // UpdateAnimation()
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
//INCLUDE_ASM("st/chi/nonmatchings/1CBA8", func_801AE478);    // FindFirstUnkPrim()
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
//INCLUDE_ASM("st/chi/nonmatchings/1CBA8", func_801AE4A8);    // FindFirstUnkPrim2()
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
//INCLUDE_ASM("st/chi/nonmatchings/1CBA8", func_801AE524);    // PrimToggleVisibility()
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
//INCLUDE_ASM("st/chi/nonmatchings/1CBA8", func_801AE5AC);    // PrimResetNext()
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
//INCLUDE_ASM("st/chi/nonmatchings/1CBA8", func_801AE68C);    // UnkPolyFunc2()
void UnkPolyFunc2(Primitive* prim) {
    PrimResetNext(prim);
    prim->p3 = 8;
    prim->next->p3 = 1;
    prim->next->type = PRIM_LINE_G2;
    prim->next->drawMode = 0xA;
}
//INCLUDE_ASM("st/chi/nonmatchings/1CBA8", func_801AE6E0);    // UnkPolyFunc0()
void UnkPolyFunc0(Primitive* prim) {
    prim->p3 = 0;
    prim->drawMode = DRAW_HIDE;
    prim->next->p3 = 0;
    prim->next->type = PRIM_GT4;
    prim->next->drawMode = DRAW_HIDE;
}
INCLUDE_ASM("st/chi/nonmatchings/1CBA8", func_801AE70C);    // PrimDecreaseBrightness()
//#include "../prim_helpers.h"
