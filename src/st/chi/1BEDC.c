#include "stage.h"

/*
 * File: 1BEDC.c
 * Overlay: CHI
 * Description: Abandoned Mine
 */

//#ifndef NON_MATCHING
//INCLUDE_ASM("st/chi/nonmatchings/1BEDC", func_8019BEDC);
//#else
extern u8 D_8003BE3C;
extern s32 D_8007D858[];
void* func_801AE478(Primitive*);                    // extern
extern /*?*/s32 D_8018067C;
extern u16 D_8018089C;
extern u16 D_801808B4;
extern u16 g_pads_1_pressed;

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

typedef struct UnkStruct2 {
    s32 unk0;
    s32 unk4;
    s16 unk8;
    s16 unkA;
    s32 unkC;
    s32 unk10;
    s32 unk14;
    s32 unk18;
    s32 unk1C;
    s32 unk20;
    s32 unk24;
    s16 unk28;
    u8 unk2A;
    u8 unk2B;
} UnkStruct2;

void func_8019BEDC(Entity* entity)
{
    Primitive* var_s0;
    Primitive* var_s0_2;
    s16 temp_s3;
    s16 temp_v0;
    s16 var_s2;
    s32 temp_s2;
    s32 temp_v0_2;
    s32 temp_v1_2;
    s32 temp_v1_3;
    s32 temp_v1_4;
    s32 temp_v1_5;
    s32 var_a1;
    s32 var_a1_2;
    s32 var_a3;
    s32 var_a3_2;
    s32 var_t0;
    s32 var_t0_2;
    s32 var_t1;
    u16 temp_a0;
    u16 temp_a0_2;
    u16 temp_v1;
    u16 var_v0;
    u16* var_a2;
    u16* var_a2_2;
    UnkStruct2* temp_v0_3;
    Entity* temp_entity;

    temp_v1 = entity->step;
    switch (temp_v1) {
        case 0:
            func_801A1F9C(&D_8018067C);
            entity->animCurFrame = 1U;
            var_a2 = &D_8018089C;
            var_t0 = 0x6D;
            if (D_8003BE3C != 0) {
                var_a2 = &D_8018089C + 0x18;
            }
            var_a3 = 0;
            do {
                var_a1 = 0;
loop_6:
                temp_v1_2 = var_a1 << 5;
                var_a1 += 1;
                temp_a0 = *var_a2;
                var_a2 += 2;
                *(temp_v1_2 + &g_Tilemap.fg[var_t0]) = temp_a0;
                if (var_a1 < 4) {
                    goto loop_6;
                }
                var_a3 += 1;
                var_t0 += 1;
            } while (var_a3 < 3);
            if (D_8003BE3C != 0) {
                entity->animCurFrame = 0U;
                entity->step = 0x10U;
                return;
            }
        default:
            return;
        case 1:
            if (D_8003BE3C != 0) {
block_16:
                entity->step = (u16) (entity->step + 1);
                return;
            }
            break;
        case 2:
            temp_v0 = g_api_AllocPrimitives(PRIM_TILE, 0x10);
            if (temp_v0 != -1) {
                var_s0 = &g_PrimBuf[temp_v0];
                entity->primIndex = (s32) temp_v0;
                entity->ext.generic.unk7C.s = var_s0;
                entity->flags = (s32) (entity->flags | 0x800000);
                if (var_s0 != NULL) {
                    do {
                        var_s0->drawMode = 8;
                        var_s0 = var_s0->next;
                    } while (var_s0 != NULL);
                }
                goto block_16;
            }
block_41:
            func_801A128C(entity);
            return;
        case 3:
            temp_v0_2 = entity->ext.generic.unk80.modeS16.unk0 + 1;
            entity->ext.generic.unk80.modeS16.unk0 = temp_v0_2;
            if (temp_v0_2 & 1) {
                var_v0 = entity->posY.i.hi + 1;
            } else {
                var_v0 = entity->posY.i.hi - 1;
            }
            entity->posY.i.hi = var_v0;
            if (!(entity->ext.generic.unk80.modeS16.unk0 & 7)) {
                g_api_PlaySfx(0x644);
            }
            func_801A1640();
            temp_v1_3 = entity->velocityX;
            if (temp_v1_3 < 0x4000) {
                entity->velocityX = (s32) (temp_v1_3 + 0x200);
            }
            temp_v0_3 = func_801AE478(entity->ext.generic.unk7C.s);
            if (temp_v0_3 != NULL) {
                temp_v0_3->unk2B = 1;
                temp_v1_4 = entity->posX.i.hi + (func_8019DE74() & 0x3F);
                var_s2 = temp_v1_4 - 0x18;
                if (var_s2 >= 0x101) {
                    var_s2 = temp_v1_4 - 0x28;
                }
                temp_v0_3->unk8 = var_s2;
                temp_v0_3->unkA = (s16) ((s16) entity->posY.i.hi - 0x20);
            }
            var_s0_2 = entity->ext.generic.unk7C.s;
            if (var_s0_2 != NULL) {
                do {
                    if (var_s0_2->p3 != 0) {
                        func_8019BD0C((UnkStruct1* ) var_s0_2);
                    }
                    var_s0_2 = var_s0_2->next;
                } while (var_s0_2 != NULL);
            }
            temp_s2 = entity->posX.i.hi - 0x18;
            temp_s3 = (s16) entity->posY.i.hi + 0x20;
            temp_entity = func_801A1AFC(D_8007D858, D_8007D858 + 0x1780);
            if (temp_entity != NULL) {
                func_801A04EC(0x15, temp_entity);
                temp_entity->posX.i.hi = (s16) (temp_s2 + (func_8019DE74() & 0x1F));
                temp_entity->posY.i.hi = temp_s3;
                temp_entity->params = (s16) (func_8019DE74() & 3);
                temp_entity->zPriority = 0xA0;
            }
            var_t1 = (s32) (entity->posX.i.hi - 0xE8) >> 4;
            var_t0_2 = 0x6D;
            if (var_t1 >= 4) {
                var_t1 = 3;
            }
            var_a2_2 = &D_801808B4;
            var_a3_2 = 0;
            if (var_t1 > 0) {
                do {
                    var_a1_2 = 0;
loop_38:
                    temp_v1_5 = var_a1_2 << 5;
                    var_a1_2 += 1;
                    temp_a0_2 = *var_a2_2;
                    var_a2_2 += 2;
                    *(temp_v1_5 + &g_Tilemap.fg[var_t0_2]) = temp_a0_2;
                    if (var_a1_2 < 4) {
                        goto loop_38;
                    }
                    var_a3_2 += 1;
                    var_t0_2 += 1;
                } while (var_a3_2 < var_t1);
            }
            if (entity->posX.i.hi >= 0x129) {
                goto block_41;
            }
            break;
        case 16:
            if (g_pads_1_pressed & 0x80) {
                if (entity->params == 0) {
                    entity->animCurFrame = (u16) (entity->animCurFrame + 1);
                    entity->params = (u16) (entity->params | 1);
                    goto block_46;
                }
            } else {
                entity->params = 0U;
block_46:
                if (g_pads_1_pressed & 0x20) {
                    if (entity->step_s == 0) {
                        entity->animCurFrame = (u16) (entity->animCurFrame - 1);
                        entity->step_s = (u16) (entity->step_s | 1);
                        return;
                    }
                } else {
                    entity->step_s = 0U;
                }
            }
            break;
    }
}
//#endif

INCLUDE_ASM("st/chi/nonmatchings/1BEDC", func_8019C31C);