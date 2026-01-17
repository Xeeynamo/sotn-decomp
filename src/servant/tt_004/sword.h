// SPDX-License-Identifier: AGPL-3.0-or-later
#define NO_SERVANT_CLUT
#include <servant.h>

#define OVL_EXPORT(x) TT_004_##x

typedef enum {
    SWORD_DEFAULT = ENTITY_ID_SERVANT,
    SWORD_CIRCLE_ATTACK,
    SWORD_UNK_D3,
    SWORD_UNK_D4,
    SWORD_UNK_D5,
    SWORD_UNK_D6,
    SWORD_UNK_D7,
    SWORD_UNK_D8,
    SWORD_UNK_D9,
    SWORD_UNK_DA,
    SWORD_UNK_DB,
    SWORD_UNK_DC,
    SWORD_UNK_DD,
    SWORD_UNK_DE,
    SWORD_UNK_DF,
} SwordEntityId;

typedef struct {
    s32 unk0; // flag checked by `UpdateServantDefault`, changes at level 70
    s32 unk4;
    s32 unk8; // flag checked by `CheckSwordLevel`, changes at level 90
} SwordUnk_A0;

extern u16 g_ServantClut[16];
extern s32 g_PlaySfxStep;
