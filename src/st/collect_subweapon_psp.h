// SPDX-License-Identifier: AGPL-3.0-or-later
extern u16 D_80180DC4[];
extern u32 D_091CF6DC;
extern u32 D_091CF698;
static void CollectSubweapon(u16 subWeaponIdx) {
    Entity* player = &PLAYER;
    u16 subWeapon;

    g_api.PlaySfx(SFX_ITEM_PICKUP);
    if (g_PlayableCharacter == PLAYER_MARIA) {
        subWeapon = D_091CF6DC;
    } else {
        subWeapon = D_091CF698;
    }

    if (g_PlayableCharacter == PLAYER_MARIA) {
        D_091CF6DC = maria_subweapons_idx[subWeaponIdx - 14];
        func_90E4C90();
    } else {
        D_091CF698 = aluric_subweapons_idx[subWeaponIdx - 14];
    }

    if (g_PlayableCharacter != PLAYER_MARIA && subWeapon == D_091CF698 ||
        g_PlayableCharacter == PLAYER_MARIA && subWeapon == D_091CF6DC) {
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
        g_CurrentEntity->ext.equipItemDrop.unk8A = 5;
        if (player->facingLeft ^ 1) {
            g_CurrentEntity->velocityX = FIX(-2);
        } else {
            g_CurrentEntity->velocityX = FIX(2);
        }
    } else {
        DestroyEntity(g_CurrentEntity);
    }
}
