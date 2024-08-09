#include "np3.h"

void func_801B246C(Entity* self) {
    ObjInit2* temp_s0 = &D_80180C10[self->params];

    if (self->step == 0) {
        InitializeEntity(g_eInitGeneric2);
        self->animSet = temp_s0->animSet;
        self->zPriority = temp_s0->zPriority;
        self->facingLeft = temp_s0->unk4.U8.unk0;
        self->unk5A = temp_s0->unk4.U8.unk1;
        self->palette = temp_s0->palette;
        self->drawFlags = temp_s0->drawFlags;
        self->drawMode = temp_s0->drawMode;
        if (temp_s0->unkC != 0) {
            self->flags = temp_s0->unkC;
        }
    }

    AnimateEntity(temp_s0->unk10, self);
}

static u8 D_80180D98[] = {0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x50, 0x20};
static u8 D_80180DA0[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
static u16 D_80180DA8[] = {
    0x0000, 0x0000, 0x0600, 0x0100, 0x0000, 0x0000, 0x0600, 0x01FC,
    0x0000, 0x00FC, 0x0600, 0x01FC, 0x0000, 0x0000, 0x0600, 0x01FC,
    0x0000, 0x00FC, 0x0600, 0x0300, 0x0000, 0x00FC, 0x0600, 0x01FC,
    0x0000, 0x00FC, 0x0600, 0x0300, 0x0000, 0x0200, 0x0600, 0x0300,
    0x0000, 0x01FC, 0x0500, 0x02FC, 0x0000, 0x0000, 0x0500, 0x0400,
    0x0000, 0x0000, 0x0500, 0x0400, 0x0000, 0x01FC, 0x0500, 0x02FC,
    0x00F0, 0x01FC, 0x0310, 0x02FC, 0x00F0, 0x01FC, 0x0310, 0x02FC,
};

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
            phi_v1 = entity->ext.generic.unk7C.s;
            if (phi_v1 != 0) {
                phi_v1 = (ret & 2) * 2;
            } else {
                phi_v1 = (ret & 1) * 4;
            }
            unk = 8;
            temp_s1 = (temp_s1 * unk) + phi_v1;
            temp_v0_2 = &D_80180DA8[temp_s1];
            g_Tilemap.x = *(temp_v0_2++);
            g_Tilemap.y = *(temp_v0_2++);
            g_Tilemap.width = *(temp_v0_2++);
            g_Tilemap.height = *(temp_v0_2++);
        }
    } else {
        InitializeEntity(D_80180A84);
        entity->ext.generic.unk7C.s = D_80180DA0[temp_s1];
        if (entity->ext.generic.unk7C.s != 0) {
            entity->hitboxWidth = D_80180D98[temp_s1];
            entity->hitboxHeight = 16;
        } else {
            entity->hitboxWidth = 16;
            entity->hitboxHeight = D_80180D98[temp_s1];
        }
    }
}
