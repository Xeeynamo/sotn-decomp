// SPDX-License-Identifier: AGPL-3.0-only
#include <game.h>
#include <log.h>
#include "pc.h"
#include <stdlib.h>
#include <string.h>

u8* g_PlOvlSpritesheet[256];
static u8* sprite_data = NULL;

void InitPlayerArc(const struct FileUseContent* file) {
    int i;

    if (sprite_data) {
        free(sprite_data);
    }
    // this is not freed anywhere else, technically a memory leak but it's not
    DEBUGF("allocating %d bytes for ARC spritesheet", file->length);
    sprite_data = malloc(file->length);
    memcpy(sprite_data, file->content, file->length);

    // clean-up previously allocated data, only useful for memory sanity checks
    memset(g_PlOvlSpritesheet, 0, sizeof(g_PlOvlSpritesheet));

    const u32 BaseAddr = 0x8013C000;
    u32* ptr = (u32*)sprite_data + 8;
    for (i = 0; i < LEN(g_PlOvlSpritesheet); i++) {
        u32 psxPtr = *ptr++;
        // assume PSX ptr to not be in an unexptected range
        if (psxPtr < BaseAddr) {
            break;
        }

        size_t dataPos = psxPtr - BaseAddr;
        if (dataPos >= file->length) {
            break;
        }

        g_PlOvlSpritesheet[i] = sprite_data + dataPos;
    }
}
