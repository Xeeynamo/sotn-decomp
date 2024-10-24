// SPDX-License-Identifier: AGPL-3.0-or-later
/*
 * File: en_collect.c
 * Overlay: CHI
 * Description: ENTITY - Prize Collection
 */

// D_80181024: D_80180C94
// D_80181028: D_80180C98
// D_80181054: D_80180CC4
// D_80181064: D_80180CD4
// D_80181068: D_80180CD8
// D_8018106C: D_80180CDC
// D_80181070: D_80180CE0
// D_80181074: D_80180CE4
// D_80181078: D_80180CE8
// D_8018107C: D_80180CEC
// D_80181080: D_80180CF0
// D_80181084: D_80180CF4
// D_80181098: D_80180D08
// D_801810A8: D_80180D18
// D_801810AC: D_80180D1C
// D_801810C0: D_80180D30
// D_801810D4: D_80180D44
// D_801810E8: D_80180D58
// D_801810FC: D_80180D6C
// D_80181110: D_80180D80
// D_80181124: D_80180D94
// D_80181138: D_80180DA8
// D_8018114C: D_80180DBC
// D_80181160: D_80180DD0
// D_80181170: aluric_subweapons_idx
// D_80181184: aluric_subweapons_id
// D_80181198: g_goldCollectTexts
// D_801811C0: c_GoldPrizes
// D_801811E8: g_SubweaponAnimPrizeDrop
// D_80181248: D_80180EB8
// D_80181250: c_HeartPrizes
// D_80181254: g_ExplosionYVelocities
// D_80181268: D_80180ED8
// D_8018127C: g_bigRedFireballAnim
// D_80181298: D_80180F08
// D_801812C8: D_80180F38
// D_801812FC: D_80180F6C
// D_80181300: g_ExplosionAnimations
// func_801A273C: func_8018CAB0
// func_801A27C0: func_8018CB34
// func_801A291C: CollectHeart
// func_801A299C: CollectGold
// func_801A2A78: CollectSubweapon
// func_801A2B90: CollectHeartVessel
// func_801A2C34: CollectLifeVessel
// func_801A2C84: DestroyCurrentEntity
// func_801A2CAC: [E_PRIZE_DROP] EntityPrizeDrop
// func_801A3520: [E_EXPLOSION] EntityExplosion
// func_801A361C: BlinkItem
// func_801A36C0: [E_EQUIP_ITEM_DROP] EntityEquipItemDrop
#include "../e_collect.h"
