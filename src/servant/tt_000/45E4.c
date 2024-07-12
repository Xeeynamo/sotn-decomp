#include <layer.h>
#include <player.h>
#include <stage.h>
#include <servant.h>
#include <sfx.h>
#include <psxsdk/libc.h>

void CreateEventEntity(Entity* entityParent, s32 entityId, s32 params) {
    Entity* entity;
    s32 i;

    for (i = 0; i < 3; i++) {
        entity = &g_Entities[5 + i];
        if (!entity->entityId) {
            break;
        }
    }

    if (!entity->entityId) {
        DestroyEntity(entity);
        entity->entityId = entityId;
        entity->zPriority = entityParent->zPriority;
        entity->facingLeft = entityParent->facingLeft;
        entity->flags = FLAG_UNK_04000000;
        entity->posX.val = entityParent->posX.val;
        entity->posY.val = entityParent->posY.val;
        entity->ext.generic.unk8C.entityPtr = entityParent;
        entity->params = params;
    }
}

s32 func_801746A0(s32 arg0) {
    if (PLAYER.velocityY < 0 && !(g_Player.pl_vram_flag & 1)) {
        return 1;
    }

    if (PLAYER.velocityY > 0 && !(g_Player.pl_vram_flag & 2)) {
        return 1;
    }

    if (PLAYER.velocityX < 0 && !(g_Player.pl_vram_flag & 8))
        return 1;

    if (PLAYER.velocityX > 0 && !(g_Player.pl_vram_flag & 4))
        return 1;

    if (arg0 == 0)
        return 0;

    if (g_Player.unk50 != PLAYER.step || PLAYER.step != 0)
        return 1;

    if (g_Player.unk52 != PLAYER.step_s)
        return 1;

    if (PLAYER.step_s != 0 && PLAYER.step_s != 4)
        return 1;

    return 0;
}

#ifndef VERSION_PSP
s32 func_801747B8(void) {
    Entity* entity;
    s32 i;

    entity = &g_Entities[STAGE_ENTITY_START];
    for (i = 0; i < 0x80; i++, entity++) {
        if (entity->entityId == 0)
            continue;
        if (entity->hitboxState == 0)
            continue;
        if (entity->flags & FLAG_UNK_00200000)
            continue;
        if (entity->posX.i.hi < -16)
            continue;
        if (entity->posX.i.hi > 272)
            continue;
        if (entity->posY.i.hi > 240)
            continue;
        if (entity->posY.i.hi < 0)
            continue;
        if (entity->hitPoints < 0x7000)
            return 1;
    }
    return 0;
}
#endif

s32 func_80174864(void) {
    if (g_StageId >= STAGE_RNO0 && g_StageId < STAGE_RNZ1_DEMO) {
        if (D_8003C708.flags == 0x22) {
            return 1;
        }
        if (D_8003C708.flags == 0x20) {
            return 0;
        }
        return 2;
    } else {
        if (D_8003C708.flags == 0x22) {
            return 0;
        }

        if (D_8003C708.flags == 0x20) {
            return 1;
        }
        return 2;
    }
}

#ifdef VERSION_PSP
void func_092EC220(void) {
    memcpy((u8*)&D_8D1DC40, (u8*)&g_ServantDesc, sizeof(ServantDesc));
}
#endif
