// SPDX-License-Identifier: AGPL-3.0-or-later
extern u16 D_80180DC4[];
static void CollectSubweapon(u16 subWeaponIdx) {
    Entity* player = &PLAYER;
    u16 subWeapon;

    g_api.PlaySfx(SFX_ITEM_PICKUP);
    if (g_PlayableCharacter == PLAYER_MARIA) {
        subWeapon = g_Status.D_80097C40;
    } else {
        subWeapon = g_Status.subWeapon;
    }

    if (g_PlayableCharacter == PLAYER_MARIA) {
        g_Status.D_80097C40 = maria_subweapons_idx[subWeaponIdx - 14];
        func_90E4C90();
    } else {
        g_Status.subWeapon = aluric_subweapons_idx[subWeaponIdx - 14];
    }

    if (g_PlayableCharacter != PLAYER_MARIA &&
            subWeapon == g_Status.subWeapon ||
        g_PlayableCharacter == PLAYER_MARIA &&
            subWeapon == g_Status.D_80097C40) {
        subWeapon = 1;
        g_CurrentEntity->unk6D[0] = 0x10;
    } else {
        if (g_PlayableCharacter == PLAYER_MARIA) {
            subWeapon = maria_subweapons_id[subWeapon];
        } else {
            subWeapon = aluric_subweapons_id[subWeapon];
        }
        g_CurrentEntity->unk6D[0] = 0x60;
    }

    if (subWeapon) {
        g_CurrentEntity->params = subWeapon;
        g_CurrentEntity->posY.i.hi = player->posY.i.hi + 12;
        SetStep(7);
        g_CurrentEntity->velocityY = FIX(-2.5);
        g_CurrentEntity->animCurFrame = 0;
        g_CurrentEntity->ext.equipItemDrop.sparkleTimer = 5;
        if (player->facingLeft ^ 1) {
            g_CurrentEntity->velocityX = FIX(-2);
        } else {
            g_CurrentEntity->velocityX = FIX(2);
        }
    } else {
        DestroyEntity(g_CurrentEntity);
    }
}
