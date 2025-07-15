// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no2.h"

void func_us_801B3D8C(Entity* self)
{
    Entity* tempEntity;
    Primitive* tempPrim;
    s16 primY23;
    s16 primX02;
    s16 primX13;
    s16 primY01;
    s16 offsetX;
    s16 offsetY;
    s32 step;

    tempEntity = self;
    if (tempEntity->params != 0) {
        offsetX = 0x0;
        offsetY = -0x40;
    } else {
        offsetY = 0x58;
    }
    if (tempEntity->step == 0) {
        tempEntity->step += 1;
        if (tempEntity->params != 0) {
            tempEntity->primIndex = (s32) g_api_AllocPrimitives(PRIM_GT4, 0x20);
        } else {
            tempEntity->primIndex = (s32) g_api_AllocPrimitives(PRIM_GT4, 8);
        }
        if (tempEntity->primIndex == -1) {
            DestroyEntity(tempEntity);
            return;
        }
        tempEntity->flags = 0x04800000;
        tempPrim = &g_PrimBuf[tempEntity->primIndex];
        step = 0;

        while (tempPrim != NULL) {
            primX02 = ((step & 7) << 6) + offsetX;
            tempPrim->x2 = primX02;
            tempPrim->x0 = primX02;
            primX13 = (s16) tempPrim->x0 + 0x48;
            tempPrim->x3 = primX13;
            tempPrim->x1 = primX13;
            primY01 = offsetY + ((step >> 3) * 0x64);
            tempPrim->y0 = primY01;
            tempPrim->y1 = primY01; 
            primY23 = (u16) tempPrim->y0 + 0x6C;
            tempPrim->y2 = primY23;
            tempPrim->y3 = primY23;
            tempPrim->u0 = 0x80;
            tempPrim->v0 = 0;
            tempPrim->u1 = 0xC8;
            tempPrim->v1 = 0;
            tempPrim->u2 = 0x80;
            tempPrim->v2 = 0x68;
            tempPrim->u3 = 0xC8;
            tempPrim->v3 = 0x68;
            tempPrim->tpage = 0xF;
            tempPrim->clut = 0x36;
            tempPrim->priority = 0x10;
            tempPrim->drawMode = 0;
            step += 1;
            tempPrim = tempPrim->next;
        }
    }
}

INCLUDE_ASM("st/no2/nonmatchings/33D8C", func_us_801B3F30);

void EntityFrozenShadeCrystal(Entity* self) {
    if (!self->step) {
        InitializeEntity(g_EInitCommon);
        self->animSet = ANIMSET_OVL(2);
        self->animCurFrame = 1;
        self->zPriority = 0xA0;
    }
}

void func_us_801B41A4(void) {
    if (g_CurrentEntity->step == 0) {
        g_CurrentEntity->step += 1;
    }
    g_GpuBuffers[0].draw.r0 = 0x20;
    g_GpuBuffers[0].draw.g0 = 0x18;
    g_GpuBuffers[0].draw.b0 = 0x28;
    g_GpuBuffers[1].draw.r0 = 0x20;
    g_GpuBuffers[1].draw.g0 = 0x18;
    g_GpuBuffers[1].draw.b0 = 0x28;
}

INCLUDE_ASM("st/no2/nonmatchings/33D8C", func_us_801B4210);

INCLUDE_ASM("st/no2/nonmatchings/33D8C", func_801A2848);

INCLUDE_ASM("st/no2/nonmatchings/33D8C", func_801A2A58);

INCLUDE_ASM("st/no2/nonmatchings/33D8C", func_801A2C9C);

INCLUDE_ASM("st/no2/nonmatchings/33D8C", Entity3DHouseSpawner);

INCLUDE_ASM("st/no2/nonmatchings/33D8C", Entity3DBackgroundHouse);

INCLUDE_ASM("st/no2/nonmatchings/33D8C", func_us_801B4DA4);

INCLUDE_ASM("st/no2/nonmatchings/33D8C", func_us_801B52B4);

INCLUDE_ASM("st/no2/nonmatchings/33D8C", func_us_801B5368);

INCLUDE_ASM("st/no2/nonmatchings/33D8C", func_us_801B5578);

INCLUDE_ASM("st/no2/nonmatchings/33D8C", func_us_801B56A4);

INCLUDE_ASM("st/no2/nonmatchings/33D8C", func_us_801B5750);

INCLUDE_ASM("st/no2/nonmatchings/33D8C", func_us_801B5948);

INCLUDE_RODATA("st/no2/nonmatchings/33D8C", D_us_801B2E20);

INCLUDE_ASM("st/no2/nonmatchings/33D8C", func_us_801B59C4);

INCLUDE_ASM("st/no2/nonmatchings/33D8C", func_us_801B5FB8);

INCLUDE_ASM("st/no2/nonmatchings/33D8C", func_us_801B65A4);

INCLUDE_ASM("st/no2/nonmatchings/33D8C", func_us_801B6794);

INCLUDE_ASM("st/no2/nonmatchings/33D8C", func_us_801B68EC);

INCLUDE_ASM("st/no2/nonmatchings/33D8C", func_us_801B6E34);

INCLUDE_ASM("st/no2/nonmatchings/33D8C", func_us_801B72E8);

INCLUDE_ASM("st/no2/nonmatchings/33D8C", func_us_801B7580);
