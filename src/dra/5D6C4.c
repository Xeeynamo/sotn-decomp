#include "common.h"
#include "dra.h"
#include "objects.h"
#include "sfx.h"

s32 func_800FD6C4(s32 equipTypeFilter) {
    s32 var_a0;
    s32 var_v1;
    s32 var_a1;

    switch (equipTypeFilter) {
    case 0:
        return 0xA9;
    case 1:
        var_a1 = 0;
        break;
    case 2:
        var_a1 = 1;
        break;
    case 3:
        var_a1 = 2;
        break;
    case 4:
        var_a1 = 3;
     default:
        break;
    }
    var_a0 = 0;
    var_v1 = 0;
    do {
        if(D_800A7734[var_v1].unk00 == var_a1)
        {
            var_a0 += 1;
        }
        var_v1 += 1;
    } while (var_v1 < 90);

    return var_a0;
}

const u32 rodataPadding_jpt_800FD6E0 = 0;

u8* func_800FD744(s32 equipTypeFilter) {
    u8* begin = g_InventoryOrder;
    if (equipTypeFilter != 0) {
        begin += 0xA9;
    }
    return begin;
}

u8* func_800FD760(s32 equipTypeFilter) {
    s8* begin = &g_Inventory;
    if (equipTypeFilter != 0) {
        begin += 0xA9;
    }
    return begin;
}

const char* GetEquipmentName(s32 equipTypeFilter, s32 equipId) {
    if (!equipTypeFilter) {
        return D_800A4B04[equipId].name;
    } else {
        return D_800A7718[equipId].name;
    }
}
