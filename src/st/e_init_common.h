// SPDX-License-Identifier: AGPL-3.0-or-later

EInit OVL_EXPORT(EInitObtainable) = {ANIMSET_DRA(3), 0, 0x00, 0x000, 1};
EInit OVL_EXPORT(EInitParticle) = {ANIMSET_DRA(3), 0, 0x00, 0x000, 2};
#ifndef HARD_LINK
EInit g_EInitSpawner = {ANIMSET_DRA(0), 0, 0x00, 0x000, 4};
EInit g_EInitInteractable = {ANIMSET_DRA(0), 0, 0x00, 0x000, 5};
EInit OVL_EXPORT(EInitUnkId13) = {ANIMSET_DRA(0), 0, 0x00, 0x000, 2};
EInit OVL_EXPORT(EInitLockCamera) = {ANIMSET_DRA(0), 0, 0x00, 0x000, 1};
EInit OVL_EXPORT(EInitCommon) = {ANIMSET_DRA(0), 0, 0x00, 0x000, 3};
EInit OVL_EXPORT(EInitDamageNum) = {ANIMSET_DRA(0), 0, 0x00, 0x000, 3};
#ifdef USE_ENEMY_3
EInit g_EInitEnemy3 = {ANIMSET_OVL(1), 0, 0x00, 0x000, 3};
#endif

#endif
