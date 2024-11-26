// SPDX-License-Identifier: AGPL-3.0-or-later
static void CollectSubweapon(u16 subWeaponIdx) {
    Entity* player = &PLAYER;
    u16 subWeapon;

    g_api.PlaySfx(SFX_ITEM_PICKUP);
    subWeapon = g_Status.subWeapon;
#if defined STAGE_IS_RBO3
    g_Status.subWeapon = aluric_subweapons_idx[subWeaponIdx];
#else
    g_Status.subWeapon = aluric_subweapons_idx[subWeaponIdx - 14];
#endif

    if (subWeapon == g_Status.subWeapon) {
        subWeapon = 1;
        g_CurrentEntity->unk6D[0] = 0x10;
    } else {
        subWeapon = aluric_subweapons_id[subWeapon];
        g_CurrentEntity->unk6D[0] = 0x60;
    }

    if (subWeapon) {
        g_CurrentEntity->params = subWeapon;
        g_CurrentEntity->posY.i.hi = player->posY.i.hi + 12;
#if defined VERSION_BETA || STAGE == STAGE_ST0
        g_CurrentEntity->step = 7;
        g_CurrentEntity->step_s = 0;
#else
        SetStep(7);
#endif
        g_CurrentEntity->velocityY = FIX(-2.5);
        g_CurrentEntity->animCurFrame = 0;
        g_CurrentEntity->ext.equipItemDrop.unk8A = 5;
        if (player->facingLeft != 1) {
            g_CurrentEntity->velocityX = FIX(-2);
            return;
        }
        g_CurrentEntity->velocityX = FIX(2);
        return;
    }
    DestroyEntity(g_CurrentEntity);
}
