#include "../dra/dra.h"

INCLUDE_ASM("dra/nonmatchings/262A0", DealDamage);

INCLUDE_ASM("dra/nonmatchings/262A0", func_psp_091030C8);

INCLUDE_ASM("dra/nonmatchings/262A0", func_psp_09103128);

INCLUDE_ASM("dra/nonmatchings/262A0", func_psp_091032C8);

INCLUDE_ASM("dra/nonmatchings/262A0", RenderTilemap);

// https://decomp.me/scratch/msJvI
INCLUDE_ASM("dra/nonmatchings/262A0", SetRoomForegroundLayer);

// https://decomp.me/scratch/yWihP
INCLUDE_ASM("dra/nonmatchings/262A0", SetRoomBackgroundLayer);

// https://decomp.me/scratch/DJTZ0
INCLUDE_ASM("dra/nonmatchings/262A0", LoadRoomLayer);

// stuff is moved around here vs. PS1

// seems to be unique to psp, called by LoadGfxAsync to get gfxBank
// https://decomp.me/scratch/DqKHA
INCLUDE_ASM("dra/nonmatchings/262A0", func_psp_09103E68);

// https://decomp.me/scratch/XOaDi
INCLUDE_ASM("dra/nonmatchings/262A0", func_800EAEA4);

// https://decomp.me/scratch/4RcwR
INCLUDE_ASM("dra/nonmatchings/262A0", ResetPendingGfxLoad);

// https://decomp.me/scratch/HDCYU
INCLUDE_ASM("dra/nonmatchings/262A0", LoadGfxAsync);

INCLUDE_ASM("dra/nonmatchings/262A0", func_psp_091040A0);

INCLUDE_ASM("dra/nonmatchings/262A0", DecompressWriteNibble);

INCLUDE_ASM("dra/nonmatchings/262A0", DecompressReadNibble);

// https://decomp.me/scratch/ylDoN
INCLUDE_ASM("dra/nonmatchings/262A0", DecompressData);

// https://decomp.me/scratch/BwdAt
INCLUDE_ASM("dra/nonmatchings/262A0", LoadPendingGfx);

// https://decomp.me/scratch/Bp68W
INCLUDE_ASM("dra/nonmatchings/262A0", func_800EB4F8);

INCLUDE_ASM("dra/nonmatchings/262A0", LoadEquipIcon);

INCLUDE_ASM("dra/nonmatchings/262A0", func_psp_09104810);

INCLUDE_ASM("dra/nonmatchings/262A0", func_psp_09104878);

INCLUDE_ASM("dra/nonmatchings/262A0", func_psp_091048B8);

INCLUDE_ASM("dra/nonmatchings/262A0", func_psp_09104958);

INCLUDE_ASM("dra/nonmatchings/262A0", func_psp_091049E8);

INCLUDE_ASM("dra/nonmatchings/262A0", func_psp_09104AA0);

INCLUDE_ASM("dra/nonmatchings/262A0", func_psp_09104C80);

INCLUDE_ASM("dra/nonmatchings/262A0", func_psp_09105200);

INCLUDE_ASM("dra/nonmatchings/262A0", func_psp_091052B8);
