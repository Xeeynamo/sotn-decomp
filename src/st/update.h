// SPDX-License-Identifier: AGPL-3.0-or-later
#include <stage.h>

extern u16 UNK_Invincibility0[];

void Update(void) {
    s16 x;
    Entity* e;
    s32 flags;
    s16 y;
    s16 iFramePalette;

    for (x = 0; x < LEN(g_ItemIconSlots); x++) {
        if (g_ItemIconSlots[x]) {
            g_ItemIconSlots[x]--;
        }
    }

    if (g_unkGraphicsStruct.BottomCornerTextTimer) {
        if (!--g_unkGraphicsStruct.BottomCornerTextTimer) {
            g_api.FreePrimitives(g_unkGraphicsStruct.BottomCornerTextPrims);
        }
    }

    for (e = &g_Entities[STAGE_ENTITY_START];
         e < &g_Entities[TOTAL_ENTITY_COUNT]; e++) {
        if (!e->pfnUpdate)
            continue;

        if (e->step) {
            flags = e->flags;
            if (flags & FLAG_DESTROY_IF_OUT_OF_CAMERA) {
                x = e->posX.i.hi;
                y = e->posY.i.hi;
                if (flags & FLAG_DESTROY_IF_BARELY_OUT_OF_CAMERA) {
                    if (x < -64 || x > 320 || y < -64 || y > 288) {
                        DestroyEntity(e);
                        continue;
                    }
                } else {
                    if (x < -128 || x > 384 || y < -128 || y > 352) {
                        DestroyEntity(e);
                        continue;
                    }
                }
            }

            if (flags & FLAG_UNK_02000000) {
                x = e->posY.i.hi + g_Tilemap.scrollY.i.hi;
#if defined(VERSION_PSP)
                y = (s16)g_Tilemap.vSize * 256 + 128;
#else
                y = (u16)g_Tilemap.vSize * 256 + 128;
#endif
                if (x > y) {
                    DestroyEntity(e);
                    continue;
                }
            }

            if (flags & 0xF) {
                iFramePalette = e->nFramesInvincibility << 1;
                iFramePalette += (flags & 1);
                e->palette = UNK_Invincibility0[iFramePalette];
                if (!(--e->flags & 0xF)) {
                    e->palette = e->hitEffect;
                    e->hitEffect = 0;
                }
            }

            if (!(flags & FLAG_UNK_20000000) || (flags & FLAG_UNK_10000000) ||
                (e->posX.i.hi >= -64 && e->posX.i.hi <= 320 &&
                 e->posY.i.hi >= -64 && e->posY.i.hi <= 288)) {
                if (!e->stunFrames ||
                    (e->stunFrames--, flags & FLAG_UNK_100000)) {
                    if (!g_unkGraphicsStruct.D_800973FC ||
                        flags & (FLAG_UNK_2000 | FLAG_DEAD) ||
                        (flags & FLAG_UNK_200 && !(g_GameTimer & 3))) {
                    process_entity:
                        g_CurrentEntity = e;
                        e->pfnUpdate(e);
                        e->unk44 = 0;
                        e->hitFlags = 0;
                        continue;
                    }
                }
            }
        } else {
            goto process_entity;
        }
    }
}
