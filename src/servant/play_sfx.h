// SPDX-License-Identifier: AGPL-3.0-or-later
void ProcessSfxState(Entity* entity) {
    switch (entity->step) {
    case 0:
        entity->flags = FLAG_UNK_20000 | FLAG_KEEP_ALIVE_OFFCAMERA;
        if (g_CutsceneHasControl != 0) {
            g_PlaySfxStep = 99;
            DestroyEntity(entity);
            return;
        }
        if (g_api.CdSoundCommandQueueEmpty() != 0) {
            g_api.PlaySfx(SET_UNK_10);
            entity->step++;
        }
        break;

    case 1:
        if (g_api.func_80133950() != 0) {
            entity->step++;
        }
        break;
    case 2:
        g_api.PlaySfx(entity->params);
        entity->step++;
        break;

    case 3:
        if (g_api.func_80131F68() != 0) {
            entity->step++;
        }
        break;

    case 4:
        if (g_api.func_80131F68() == 0) {
            entity->step++;
        }
        break;

    case 5:
        if ((*(s32*)&D_8003C708.flags & (FLAG_UNK_40 | FLAG_UNK_20)) != 0) {
            g_PlaySfxStep = 99;
            DestroyEntity(entity);
            return;
        }
        if (g_api.CdSoundCommandQueueEmpty() != 0) {
            g_api.PlaySfx(SET_UNK_11);
            entity->step++;
        }
        break;

    case 6:
        if (g_api.func_80133950() != 0) {
            g_PlaySfxStep = 99;
            DestroyEntity(entity);
            return;
        }
        break;

    case 7:
        g_api.PlaySfx(SET_STOP_MUSIC);
        entity->step = 4;
        break;

    case 8:
        g_PlaySfxStep = 99;
        DestroyEntity(entity);
        return;
    }

    g_PlaySfxStep = entity->step;
}
