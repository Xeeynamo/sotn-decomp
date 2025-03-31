// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../dra/dra.h"
#include "../dra/dra_bss.h"

INCLUDE_ASM("dra_psp/psp/dra_psp/26948", func_psp_091032C8);

INCLUDE_ASM("dra_psp/psp/dra_psp/26948", RenderTilemap);

INCLUDE_ASM("dra_psp/psp/dra_psp/26948", SetRoomForegroundLayer);

INCLUDE_ASM("dra_psp/psp/dra_psp/26948", SetRoomBackgroundLayer);

INCLUDE_ASM("dra_psp/psp/dra_psp/26948", LoadRoomLayer);

INCLUDE_ASM("dra_psp/psp/dra_psp/26948", func_psp_09103E68);

INCLUDE_ASM("dra_psp/psp/dra_psp/26948", func_800EAEA4);

INCLUDE_ASM("dra_psp/psp/dra_psp/26948", ResetPendingGfxLoad);

INCLUDE_ASM("dra_psp/psp/dra_psp/26948", LoadGfxAsync);

typedef struct {
    s32* unk0;
    u16 unk4;
    u16 unk6;
    u16 unk8;
} unkStr_091040A0;

extern unkStr_091040A0 D_psp_091ED538[16];

s32 func_psp_091040A0(s32* arg0) {
    unkStr_091040A0* ptr;
    s32 i;
    s32 arg0_deref = *arg0;

    if (arg0_deref == 0) {
        return -1;
    }
    if (arg0_deref == -1) {
        return -1;
    }

    for (i = 0, ptr = D_psp_091ED538; i < LEN(D_psp_091ED538); i++, ptr++) {
        if (ptr->unk4 == 0) {
            ptr->unk4 = arg0_deref;
            ptr->unk6 = 0;
            ptr->unk8 = 0;
            ptr->unk0 = arg0 + 1;
            return i;
        }
    }
    return -1;
}

INCLUDE_ASM("dra_psp/psp/dra_psp/26948", DecompressWriteNibble);

INCLUDE_ASM("dra_psp/psp/dra_psp/26948", DecompressReadNibble);

INCLUDE_ASM("dra_psp/psp/dra_psp/26948", DecompressData);

INCLUDE_ASM("dra_psp/psp/dra_psp/26948", LoadPendingGfx);

INCLUDE_ASM("dra_psp/psp/dra_psp/26948", func_800EB4F8);

INCLUDE_ASM("dra_psp/psp/dra_psp/26948", LoadEquipIcon);

INCLUDE_ASM("dra_psp/psp/dra_psp/26948", func_psp_09104810);

INCLUDE_ASM("dra_psp/psp/dra_psp/26948", func_psp_09104878);

INCLUDE_ASM("dra_psp/psp/dra_psp/26948", func_psp_091048B8);
