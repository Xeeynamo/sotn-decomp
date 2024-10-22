// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef RBO3_H
#define RBO3_H

#include <game.h>
#include <stage.h>

#define OVL_EXPORT(x) RBO3_##x

typedef enum {
    /* 0x00 */ E_NONE,
    /* 0x01 */ E_BREAKABLE,
    /* 0x02 */ E_EXPLOSION,
    /* 0x11 */ E_MEDUSA,
    /* 0x18 */ UNK_ENTITY_24 = 24,
    /* 0x19 */ UNK_ENTITY_25,
    /* 0x1A */ UNK_ENTITY_26,
    /* 0x1B */ UNK_ENTITY_27,
} EntityIDs;

extern u16 g_EInitCommon[];

#endif // RBO3_H
