// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"

typedef struct EquipMenuHelper {
    s32 equipTypeFilter;
    s32 index;
    s32 isAccessory;
} EquipMenuHelper;

EquipMenuHelper g_EquipMenuHelper[] = {
    {EQUIP_HAND, 0, false},     {EQUIP_HAND, 0, false},
    {EQUIP_HAND, 0, false},     {EQUIP_HEAD, 0, true},
    {EQUIP_ARMOR, 1, true},     {EQUIP_CAPE, 2, true},
    {EQUIP_ACCESSORY, 3, true}, {EQUIP_ACCESSORY, 3, true},
};
