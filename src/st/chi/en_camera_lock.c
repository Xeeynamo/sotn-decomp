/*
 * File: en_camera_lock.c
 * Overlay: CHI
 * Description: ENTITY - Camera lock
 * Locks the camera as if it's constrained to specific room dimensions. Once the
 * trigger volume is hit by the player, the camera unlocks to new room dimensions.
 * Useful for preventing the camera from scrolling over hidden rooms.
 */

#include "chi.h"

// D_80180798
static u8 D_80180798[] = {32, 32, 32, 32, 32, 32, 80, 32};
// D_801807A0
static u8 D_801807A0[] = {0, 0, 0, 0, 0, 0, 0, 0};

// D_801807A8
static u16 D_801807A8[] = {
    0x0000, 0x0000, 0x0600, 0x0100, 0x0000, 0x0000, 0x0600, 0x01FC,
    0x0000, 0x00FC, 0x0600, 0x01FC, 0x0000, 0x0000, 0x0600, 0x01FC,
    0x0000, 0x00FC, 0x0600, 0x0300, 0x0000, 0x00FC, 0x0600, 0x01FC,
    0x0000, 0x00FC, 0x0600, 0x0300, 0x0000, 0x0200, 0x0600, 0x0300,
    0x0000, 0x01FC, 0x0500, 0x02FC, 0x0000, 0x0000, 0x0500, 0x0400,
    0x0000, 0x0000, 0x0500, 0x0400, 0x0000, 0x01FC, 0x0500, 0x02FC,
    0x00F0, 0x01FC, 0x0310, 0x02FC, 0x00F0, 0x01FC, 0x0310, 0x02FC,
};

extern u16 EntityInit_80180658;
extern u8 D_80180798[];     // Trigger long dimension size
extern u8 D_801807A0[];     // Trigger long dimension is horizontal
extern u16 D_801807A8[];

// [Needs shared file changes to be moved to shared file]
// E_CAMERA_LOCK
// func_8019B4DC
void EntityCameraLock(Entity* entity) {
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

        if (entity->hitParams != 0) {
            temp_v0 = GetSideToPlayer();
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
        InitializeEntity(&EntityInit_80180658);
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