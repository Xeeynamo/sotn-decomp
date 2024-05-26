#include <stage.h>

void Update(void) {
    s16 i;
    Entity* entity;
    s32* unk;

    for (i = 0; i < LEN(g_ItemIconSlots); i++) {
        if (g_ItemIconSlots[i]) {
            g_ItemIconSlots[i]--;
        }
    }

    unk = &g_unkGraphicsStruct.unk10;
    if (*unk) {
        if (!--*unk) {
            g_api.FreePrimitives(g_unkGraphicsStruct.unk14);
        }
    }

    for (entity = &g_Entities[STAGE_ENTITY_START];
         entity < &g_Entities[TOTAL_ENTITY_COUNT]; entity++) {
        if (!entity->pfnUpdate)
            continue;

        if (entity->step) {
            s32 unk34 = entity->flags;
            if (unk34 & FLAG_DESTROY_IF_OUT_OF_CAMERA) {
                s16 posX = i = entity->posX.i.hi;
                s16 posY = entity->posY.i.hi;
                if (unk34 & FLAG_DESTROY_IF_BARELY_OUT_OF_CAMERA) {
                    if ((u16)(posX + 64) > 384 || (u16)(posY + 64) > 352) {
                        DestroyEntity(entity);
                        continue;
                    }
                } else {
                    if ((u16)(posX + 128) > 512 || (u16)(posY + 128) > 480) {
                        DestroyEntity(entity);
                        continue;
                    }
                }
            }

            if ((unk34 & 0x02000000)) {
                s16 posY = entity->posY.i.hi + g_Tilemap.scrollY.i.hi;
                s16 test = (LOHU(g_Tilemap.vSize) * 256) + 128;
                if (posY > test) {
                    DestroyEntity(entity);
                    continue;
                }
            }

            if (unk34 & 0xF) {
                entity->palette =
                    UNK_Invincibility0[(entity->nFramesInvincibility << 1) |
                                       (unk34 & 1)];
                entity->flags--;
                if ((entity->flags & 0xF) == 0) {
                    entity->palette = entity->hitEffect;
                    entity->hitEffect = 0;
                }
            }

            if (!(unk34 & 0x20000000) || (unk34 & 0x10000000) ||
                ((u16)(entity->posX.i.hi + 64) <= 384) &&
                    ((u16)(entity->posY.i.hi + 64) <= 352)) {
                if (!entity->stunFrames ||
                    (entity->stunFrames--, unk34 & 0x100000)) {
                    if (!D_800973FC || unk34 & 0x2100 ||
                        (unk34 & 0x200 && !(g_GameTimer & 3))) {
                        g_CurrentEntity = entity;
                        entity->pfnUpdate(entity);
                        entity->unk44 = 0;
                        entity->hitFlags = 0;
                    }
                }
            }
        } else {
            g_CurrentEntity = entity;
            entity->pfnUpdate(entity);
            entity->unk44 = 0;
            entity->hitFlags = 0;
        }
    }
}
