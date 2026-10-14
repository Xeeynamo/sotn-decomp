// SPDX-License-Identifier: AGPL-3.0-or-later
#include "bo3.h"

extern EInit g_EInitInteractable;
extern EInit g_EInitParticle;
extern EInit g_EInitCommon;

#include "../../st/cavern_bg_effects.h"

static u8 water_spray_anim[] = {1, 7, 1, 8, 1, 9, 0, 0};

void EntityWaterSpray(Entity* self) {
    s16* var_s2;
    s16* var_s1;

    if (!self->step) {
        InitializeEntity(g_EInitInteractable);
        self->animSet = ANIMSET_OVL(1);
        self->palette = 0x44;
        self->drawFlags = ENTITY_MASK_R;
        self->posX.i.hi = 0x712 - g_Tilemap.scrollX.i.hi;
        if (g_CastleFlags[NO4_WATER_BLOCKED]) {
            self->ext.et_waterAlcove.waterHeight = 0x40;
        } else {
            self->ext.et_waterAlcove.waterHeight = 0;
        }
    }

    AnimateEntity(water_spray_anim, self);

    if (g_CastleFlags[NO4_WATER_BLOCKED]) {
        if (self->ext.et_waterAlcove.waterHeight < 0x40) {
            if (!(self->ext.et_waterAlcove.unk8E & 0x7)) {
                self->ext.et_waterAlcove.waterHeight++;
                if (self->ext.et_waterAlcove.waterHeight == 0x14) {
                    g_CastleFlags[NO4_WATER_BLOCKED]++;
                }
                if (self->ext.et_waterAlcove.waterHeight == 0x34) {
                    g_CastleFlags[NO4_WATER_BLOCKED]++;
                }
            }
            self->ext.et_waterAlcove.unk8E++;
        }
    }

    var_s2 = water_tile_rects;
    var_s1 = water_surface_lines;
    var_s2 += 0x36;
    var_s1 += 0x43;

    *var_s2 = 0xB1 - self->ext.et_waterAlcove.waterHeight;
    *var_s1 = 0xB0 - self->ext.et_waterAlcove.waterHeight;

    if (self->ext.et_waterAlcove.waterHeight >= 0x40) {
        DestroyEntity(self);
    }
}

static u16 ice_platform_hitboxes[] = {0x30, 0x10, 0x28, 0x10, 0x18, 0x10};

void EntityFloatingIcePlatform(Entity* self) {
    u16* hitboxPtr;
    u16 hitboxIndex;

    hitboxIndex = self->params;
    if (!self->step) {
        InitializeEntity(g_EInitCommon);
        self->animSet = ANIMSET_OVL(1);
        self->animCurFrame = hitboxIndex + 25;
    }

    hitboxPtr = &ice_platform_hitboxes[hitboxIndex * 2];
#ifdef VERSION_PSP
    GetPlayerCollisionWith(self, hitboxPtr[0], hitboxPtr[1], 4);
#else
    GetPlayerCollisionWith(self, *hitboxPtr++, *hitboxPtr, 4);
#endif
}
