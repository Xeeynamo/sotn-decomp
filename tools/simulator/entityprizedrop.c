#include "sotn.h"

// if self->subId & 0x8000 then the item will not disappear
// self->ext.generic.unk80.modeS8.unk0: frames left before the prize disappear
u16 D_8018044C[] = {
    0x0003, 0x0000, 0x0000, 0x0000, 0x0001, 0x0000,
};
u32 D_80180608[] = {
    0x00000000, 0x00000200, 0x00000400, 0x00000600, 0x00000800, 0x00000A00,
    0x00000C00, 0x00000E00, 0x00001000, 0x00001200, 0x00001400, 0x00001600,
    0x00001800, 0x00001A00, 0x00001C00, 0x00001E00,
};
u16 D_80180DF4[] = {
    0x0000, 0x000E, 0x000F, 0x0011, 0x0010,
    0x0013, 0x0012, 0x0014, 0x0015, 0x0016,
};
s16 D_80180C94[] = {
    0x0E01,
    0x0000,
};
s16 D_80180C98[] = {
    0x0302, 0x0406, 0x0505, 0x0605, 0x0704, 0x0803, 0x0904, 0x0A05,
    0x0B05, 0x0C06, 0x0307, 0x0406, 0x0505, 0x0605, 0x0704, 0x0803,
    0x0904, 0x0A05, 0x0B05, 0x0C06, 0x0D02, 0x0000,
};
s16 D_80180CC4[] = {
    0x1404, 0x1507, 0x1606, 0x1703, 0x1803, 0x1906, 0x1502, 0x0000,
};
s16 D_80180CD4[] = {
    0x1A01,
    0x0000,
};
s16 D_80180CD8[] = {
    0x1B01,
    0x0000,
};
s16 D_80180CDC[] = {
    0x1C01,
    0x0000,
};
s16 D_80180CE0[] = {
    0x1D01,
    0x0000,
};
s16 D_80180CE4[] = {
    0x1E01,
    0x0000,
};
s16 D_80180CE8[] = {
    0x1F01,
    0x0000,
};
s16 D_80180CEC[] = {
    0x2001,
    0x0000,
};
s16 D_80180CF0[] = {
    0x2101,
    0x0000,
};
s16 D_80180CF4[] = {
    0x2202, 0x2302, 0x2402, 0x2502, 0x2602,
    0x2702, 0x2802, 0x2902, 0x0000, 0x0000,
};
s16 D_80180D08[] = {
    0x0F1A, 0x1006, 0x1104, 0x1202, 0x1104, 0x1006, 0x0000, 0x0000,
};
s16 D_80180D18[] = {
    0x1301,
    0x0000,
};
s16 D_80180D1C[] = {
    0x2A05, 0x2B05, 0x2C05, 0x2D05, 0x2E05,
    0x2F05, 0x3005, 0x3105, 0x0000, 0x0000,
};
s16 D_80180D30[] = {
    0x3205, 0x3305, 0x3405, 0x3505, 0x3605,
    0x3705, 0x3805, 0x3905, 0x0000, 0x0000,
};
s16 D_80180D44[] = {
    0x3A05, 0x3B05, 0x3C05, 0x3D05, 0x3E05,
    0x3F05, 0x4005, 0x4105, 0x0000, 0x0000,
};
s16 D_80180D58[] = {
    0x4205, 0x4305, 0x4405, 0x4505, 0x4605,
    0x4705, 0x4805, 0x4905, 0x0000, 0x0000,
};
s16 D_80180D6C[] = {
    0x4A05, 0x4B05, 0x4C05, 0x4D05, 0x4E05,
    0x4F05, 0x5005, 0x5105, 0x0000, 0x0000,
};
s16 D_80180D80[] = {
    0x5205, 0x5305, 0x5405, 0x5505, 0x5605,
    0x5705, 0x5805, 0x5905, 0x0000, 0x0000,
};
s16 D_80180D94[] = {
    0x5A05, 0x5B05, 0x5C05, 0x5D05, 0x5E05,
    0x5F05, 0x6005, 0x6105, 0x0000, 0x0000,
};
s16 D_80180DA8[] = {
    0x6205, 0x6305, 0x6405, 0x6505, 0x6605,
    0x6705, 0x6805, 0x6905, 0x0000, 0x0000,
};
s16 D_80180DBC[] = {
    0x6A05,
    0x6B05,
    0x6C05,
    0x6D05,
};

u16 D_80180DC4[] = {
    0x6E05, 0x6F05, 0x7005, 0x7105, 0x0000, 0x0000,
};
s16 D_80180DD0[] = {
    0x8F01, 0x0000, 0xFCFC, 0xFC04, 0x04FC, 0x0404, 0x0080, 0x0000, 0x0001,
    0x0002, 0x0004, 0x0003, 0x0006, 0x0005, 0x0007, 0x0008, 0x0009, 0x0000,
};
s16* D_80180E58[] = {
    D_80180C94, D_80180C98, D_80180CC4, D_80180CD4, D_80180CD8, D_80180CDC,
    D_80180CE0, D_80180CE4, D_80180CE8, D_80180CEC, D_80180CF0, D_80180CF4,
    D_80180D08, D_80180D18, D_80180D58, D_80180D44, D_80180D1C, D_80180D30,
    D_80180D6C, D_80180D80, D_80180D94, D_80180DA8, D_80180DBC, D_80180DD0,
};
u16 D_80180EB8[] = {
    0xFFFA,
    0x0004,
    0x0000,
    0xFFF8,
};

void EntityPrizeDrop(Entity* self) {
    Collider collider;
    Primitive* prim;
    s16 firstPrimIndex;
    s16 var_a2;
    u16 itemId;
    s16 temp_a0;

    itemId = self->subId & 0x7FFF;
    if (self->step != 0) {
        AnimateEntity(D_80180E58[itemId], self);
    }
    if (self->step - 2 < 3U && self->unk48 != 0) {
        self->step = 5;
    }
    self->palette = 0;
    if ((u8)self->unk6D >= 0x18 && !(D_8003C8C4 & 2) && self->subId != 1) {
        self->palette = 0x815F;
    }
    switch (self->step) {
    case 0:
        InitializeEntity(D_8018044C);
        self->zPriority = g_zEntityCenter.S16.unk0 - 0x14;
        self->blendMode = 0;
        if (itemId >= 0x18) {
            self->subId = 0;
            itemId = 0;
        }
        if (itemId > 13 && itemId < 23 &&
            itemId == D_80180DF4[g_Status.subWeapon]) {
            self->subId = itemId = 1;
        }
        if (itemId == 0 || itemId == 2) {
            self->hitboxWidth = 4;
        }
        break;

    case 1:
        g_api.CheckCollision(self->posX.i.hi, self->posY.i.hi, &collider, 0);
        if (collider.unk0 & 7) {
            DestroyEntity(self);
        } else {
            self->step++;
            if (LOH(self->ext.generic.unk94) != 0) {
                temp_a0 = LOH(self->ext.generic.unk94) - 1;
                g_zEntityCenter.S16 = g_zEntityCenter.S16;
                D_8003BF9C[temp_a0 >> 3] |= 1 << (temp_a0 & 7);
            }
        }
        if (itemId == 0) {
            self->ext.generic.unk84.unk = -0x10000;
            self->ext.generic.unk88.S16.unk0 = 0x800;
        }
        break;

    case 2:
        if (self->accelerationY < 0) {
            g_api.CheckCollision(self->posX.i.hi, self->posY.i.hi - 7,
                                 &collider, 0);
            if (collider.unk0 & 5) {
                self->accelerationY = 0;
            }
        }
        MoveEntity();
        g_api.CheckCollision(self->posX.i.hi, self->posY.i.hi + 7, &collider,
                             0);
        if (itemId != 0) {
            if (collider.unk0 & 5 && self->accelerationY > 0) {
                self->accelerationX = 0;
                self->accelerationY = 0;
                self->posY.i.hi += collider.unk18;
                self->ext.generic.unk80.modeS8.unk0 = 0xF0;
                self->step++;
            } else {
                FallEntity();
            }
            func_8018C55C(D_80180EB8, 2);
        } else if (collider.unk0 & 5) {
            self->posY.i.hi += collider.unk18;
            self->ext.generic.unk80.modeS8.unk0 = 0x60;
            self->step++;
        } else {
            func_8018CAB0();
        }
        break;

    case 3:
        func_8018CB34(itemId);
        if (!(self->subId & 0x8000) &&
            --self->ext.generic.unk80.modeS8.unk0 == 0) {
            self->ext.generic.unk80.modeS8.unk0 = itemId == 0 ? 0x40 : 0x50;
            self->step++;
        }
        break;

    case 4:
        func_8018CB34(itemId);
        if (--self->ext.generic.unk80.modeS8.unk0) {
            if (self->ext.generic.unk80.modeS8.unk0 & 2) {
                self->animCurFrame = 0;
            }
        } else {
            DestroyEntity(self);
            return;
        }
        break;

    case 5:
        // if (itemId == 0 || itemId == 1) {
        //     CollectHeart(itemId);
        // } else if (itemId < 12) {
        //     CollectGold(itemId);
        // } else if (itemId == 12) {
        //     CollectHeartVessel();
        // } else if (itemId < 14) {
        //     DestroyCurrentEntity();
        // } else if (itemId < 23) {
        //     CollectSubweapon(itemId);
        // } else if (itemId == 23) {
        //     CollectLifeVessel();
        // } else {
        //     DestroyEntity(self);
        //     return;
        // }
        // break;

    case 6:
    case 7:
        switch (self->step_s) {
        case 0:
            self->animCurFrame = 0;
            if (itemId > 13 && itemId < 23) {
                if (itemId == D_80180DF4[g_Status.subWeapon]) {
                    self->subId = itemId = 1;
                }
            }
            firstPrimIndex = g_api.AllocPrimitives(4, 1);
            if (firstPrimIndex != -1) {
                self->firstPolygonIndex = firstPrimIndex;
                self->flags |= 0x800000;
                prim = &g_PrimBuf[firstPrimIndex];
                prim->tpage = 0x1A;
                prim->clut = 0x170;
                prim->v2 = prim->v3 = 0x20;
                prim->u1 = prim->u3 = 0x20;
                prim->v0 = prim->v1 = 0;
                prim->u0 = prim->u2 = 0;
                prim->b0 = prim->b1 = prim->b2 = prim->b3 = 0x80;
                prim->g0 = prim->g1 = prim->g2 = prim->g3 = 0x80;
                prim->r0 = prim->r1 = prim->r2 = prim->r3 = 0x80;
                prim->blendMode = 8;
                prim->priority = self->zPriority + 1;
                self->step_s++;
            }
            break;

        case 1:
            MoveEntity();
            g_api.CheckCollision(self->posX.i.hi, self->posY.i.hi + 7,
                                 &collider, 0);
            if (collider.unk0 & 5 && self->accelerationY > 0) {
                self->accelerationX = 0;
                self->accelerationY = 0;
                self->posY.i.hi += collider.unk18;
                self->step_s++;
            } else {
                FallEntity();
            }
            func_8018C55C(D_80180EB8, 2);
            self->animCurFrame = 0;
            if (self->ext.generic.unk88.S16.unk2 != 0) {
                self->ext.generic.unk88.S16.unk2--;
            } else {
                prim = &g_PrimBuf[self->firstPolygonIndex];
                prim->x0 = prim->x2 = self->posX.i.hi - 1;
                prim->x1 = prim->x3 = self->posX.i.hi + 1;
                prim->y0 = prim->y1 = self->posY.i.hi - 1;
                prim->y2 = prim->y3 = self->posY.i.hi + 1;
                prim->blendMode = 0x37;
            }
            break;

        case 2:
            func_8018CB34(itemId);
            prim = &g_PrimBuf[self->firstPolygonIndex];
            self->ext.generic.unk88.S16.unk2++;
            if (self->ext.generic.unk88.S16.unk2 < 0x11) {
                var_a2 = self->ext.generic.unk88.S16.unk2;
                self->animCurFrame = 0;
            } else {
                var_a2 = 0x20 - self->ext.generic.unk88.S16.unk2;
                prim->r0 = prim->r1 = prim->r2 = prim->r3 = prim->r3 - 8;
                prim->g0 = prim->g1 = prim->g2 = prim->g3 = prim->g3 - 8;
                prim->b0 = prim->b1 = prim->b2 = prim->b3 = prim->b3 - 8;
            }
            prim->x0 = prim->x2 = self->posX.i.hi - var_a2;
            prim->x1 = prim->x3 = self->posX.i.hi + var_a2;
            prim->y0 = prim->y1 = self->posY.i.hi - var_a2;
            prim->y2 = prim->y3 = self->posY.i.hi + var_a2;
            if (self->ext.generic.unk88.S16.unk2 == 0x20) {
                g_api.FreePrimitives(self->firstPolygonIndex);
                self->ext.generic.unk80.modeS8.unk0 = 0xD0;
                self->step = 3;
                self->step_s = 0;
                self->flags &= ~0x800000;
            }
            break;
        }

        break;
    }
}