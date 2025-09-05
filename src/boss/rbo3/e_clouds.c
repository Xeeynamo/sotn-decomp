// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rbo3.h"

static MedusaCloudsUVal cloudUVals[] = {
    {0x0000, 0x0000, 0x0000, 0x0000}, {0x8181, 0x81BE, 0x9E81, 0x9EBE},
    {0x81C1, 0x81FE, 0x9EC1, 0x9EFE}, {0xA181, 0xA1BE, 0xBE81, 0xBEBE},
    {0xA1C1, 0xA1FE, 0xBEC1, 0xBEFE}, {0xC181, 0xC1BE, 0xDE81, 0xDEBE},
    {0xE181, 0xE1BE, 0xFE81, 0xFEBE}};

static SVECTOR cloudVectorOne = {-128, 0, 0};
static SVECTOR cloudVectorTwo = {128, 0, 0};
static SVECTOR cloudVectorThree = {-128, 0, 256};
static SVECTOR cloudVectorFour = {128, 0, 256};

static u8 D_us_80181334[] = {
    0x05, 0x00, 0x06, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x06, 0x00, 0x00, 0x00, 0x05, 0x00, 0x06, 0x05, 0x00, 0x00, 0x06,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x05, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x06, 0x05, 0x00,
    0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x05,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00};

static u8 D_us_80181374[] = {
    0x04, 0x03, 0x03, 0x04, 0x02, 0x04, 0x03, 0x04, 0x01, 0x03, 0x02,
    0x03, 0x04, 0x02, 0x02, 0x04, 0x03, 0x02, 0x02, 0x03, 0x02, 0x04,
    0x03, 0x04, 0x02, 0x02, 0x04, 0x03, 0x01, 0x03, 0x02, 0x04, 0x01,
    0x01, 0x02, 0x01, 0x04, 0x04, 0x04, 0x04, 0x03, 0x02, 0x02, 0x03,
    0x02, 0x01, 0x02, 0x02, 0x01, 0x02, 0x02, 0x02, 0x03, 0x04, 0x02,
    0x02, 0x03, 0x03, 0x04, 0x02, 0x02, 0x04, 0x03, 0x04};

static u8 D_us_801813B4[] = {
    0x05, 0x00, 0x06, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x06, 0x00, 0x00, 0x00, 0x05, 0x00, 0x06, 0x05, 0x00, 0x00, 0x06,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x05, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x06, 0x05, 0x00,
    0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x05,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00};

static cloudData data[] = {
    {.unkPtr = D_us_80181334, .unk4 = 0x00E0, .priority = 0x1C},
    {.unkPtr = D_us_80181374, .unk4 = 0x0100, .priority = 0x18},
    {.unkPtr = D_us_801813B4, .unk4 = 0xFF80, .priority = 0x1C}};

static SVECTOR empty = {0};

void EntityClouds(Entity* self) {
#ifdef VERSION_PC
    u8 sp[SP_LEN];
#endif
    Primitive* prim;
    Primitive* primTwo;
    MedusaCloudsUVal* uVals;
    u8* var_s4;
    s32 var_s3;
    s32 i;
    s32 j;
    s32 var_s8;
    SVECTOR* vector;

    s32 sp5C;
    s32 sp58;
    s32 priority;
    s32 primIndex;
    s32 posX;
    s32 sp48;
    long sp44;
    MATRIX* matrix;
    u8* sp3C;
    s16* sp38;
    cloudData* cloudData;

    if (!self->step) {
        InitializeEntity(g_EInitInteractable);
        primIndex = g_api.func_800EDB58(PRIM_GT4, 0x60);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.clouds.prim = prim;

        while (prim != NULL) {
            prim->tpage = 0xF;
            prim->clut = 0xC0;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
    }

    self->ext.clouds.unk84.val += FIX(1);
    self->ext.clouds.unk8C += FIX(2);
    self->ext.clouds.unk94 += 0;
    self->ext.clouds.unk88 += FIX(5);
    self->ext.clouds.unk90 += FIX(3);
    self->ext.clouds.unk98 += FIX(5);

    g_GpuBuffers[0].draw.r0 = 0x20;
    g_GpuBuffers[0].draw.g0 = 0x10;
    g_GpuBuffers[0].draw.b0 = 0x60;
    g_GpuBuffers[1].draw.r0 = 0x20;
    g_GpuBuffers[1].draw.g0 = 0x10;
    g_GpuBuffers[1].draw.b0 = 0x60;

    matrix = (MATRIX*)SP(0);
    uVals = cloudUVals;
    primTwo = (Primitive*)SP(0x20);

    for (i = 0; i < 7; primTwo++, uVals++, i++) {
        primTwo->tpage = 0xF;
        primTwo->clut = 0xC0;
        LOH(primTwo->u0) = uVals->u0;
        LOH(primTwo->u1) = uVals->u1;
        LOH(primTwo->u2) = uVals->u2;
        LOH(primTwo->u3) = uVals->u3;
    }

    vector = (SVECTOR*)SP(0x1E0);
    vector[0] = cloudVectorOne;
    vector[1] = cloudVectorTwo;
    vector[2] = cloudVectorThree;
    vector[3] = cloudVectorFour;

    var_s4 = (u8*)SP(0x2C0);
    var_s4[3] = 4;
    var_s4[7] = 4;

    SetGeomScreen(0x100);
    SetGeomOffset(0x80, 0x60);
    RotMatrix(&empty, matrix);
    SetRotMatrix(matrix);
    cloudData = data;
    sp38 = &self->ext.clouds.unk84.i.hi;
    prim = self->ext.clouds.prim;

    for (i = 0; i < 3; i++, cloudData++, sp38 += 4) {
        posX = self->posX.i.hi + *sp38;
        posX %= 0x800;
        priority = cloudData->priority;
        var_s3 = cloudData->unk4;
        gte_ldty(var_s3);
        for (sp5C = 0; sp5C < 8; sp5C++) {
            var_s3 = sp5C * 0x100 + 0x1C0;
            sp44 = (u16)sp38[2];
            var_s3 -= sp44 % 0x100;
            gte_ldtz(var_s3);
            sp44 = (sp5C + (sp44 / 0x100)) % 8;
            sp3C = (cloudData->unkPtr + sp44 * 8);
            var_s3 -= 0x1C0;

            var_s8 = FIX(8) - var_s3 * 0xA0;
            var_s4[0] = var_s8 >> 12;
            var_s4[4] = (var_s8 - 0x8000 - 0x2000) >> 12;

            var_s8 = FIX(8) - var_s3 * 0xB0;
            var_s4[1] = var_s8 >> 12;
            var_s4[5] = (var_s8 - 0x8000 - 0x3000) >> 12;

            var_s8 = FIX(8) - (var_s3 << 7);
            var_s4[2] = var_s8 >> 12;
            var_s4[6] = (var_s8 - 0x8000) >> 12;

            sp48 = posX;
            j = 0;
            sp58 = -1;
            while (1) {
                sp48 += sp58 << 8;
                j += sp58;
                j &= 7;
                var_s3 = sp3C[j];
                if (var_s3 == 0) {
                    continue;
                }

                gte_ldtx(sp48);
                gte_ldv0(&vector[3]);
                gte_rtps();
                primTwo = &((Primitive*)(SP(0x20)))[var_s3];
                primTwo->drawMode = DRAW_COLORS;
                gte_stsxy((long*)&primTwo->x3);
                gte_ldv3c(vector);
                gte_rtpt();
                if (primTwo->y3 < 0) {
                    primTwo->drawMode = DRAW_HIDE;
                    break;
                }
                if (primTwo->x3 < 0) {
                    primTwo->drawMode = DRAW_HIDE;
                    if (sp58 < 0) {
                        sp58 += 2;
                        sp48 = posX - 0x100;
                        j = 7;
                    }
                    continue;
                }

                LOW(primTwo->r0) = LOW(primTwo->r1) = LOW(var_s4[0]);
                LOW(primTwo->r2) = LOW(primTwo->r3) = LOW(var_s4[4]);
                primTwo->priority = priority;
                gte_stsxy3_gt3(primTwo);

                if (primTwo->x2 > 0x100) {
                    primTwo->drawMode = DRAW_HIDE;
                    if (sp58 > 0) {
                        break;
                    } else {
                        continue;
                    }
                } else {
                    // Possible FAKE: this cast to/from s32/Primitive* is odd
                    var_s3 = (s32)prim->next;
                    *prim = *primTwo;

                    prim->next = (Primitive*)var_s3;
                    prim = prim->next;
                    if (prim == NULL) {
                        return;
                    }
                }
            }
        }
    }

    for (j = 0; prim != NULL; j++, prim = prim->next) {
        prim->drawMode = DRAW_HIDE;
    }
}
