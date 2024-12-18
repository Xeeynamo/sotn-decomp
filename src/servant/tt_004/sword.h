// SPDX-License-Identifier: AGPL-3.0-or-later
#include <servant.h>

typedef enum {
    SWORD_UNK_D1 = ENTITY_ID_SERVANT,
    SWORD_UNK_D2,
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
    s32 unk0;
    s16 unk4;
    s16 unk6;
    s32 unk8;
} SwordUnk_A0;

extern ServantDesc sword_ServantDesc;
