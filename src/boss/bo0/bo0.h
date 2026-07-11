// SPDX-License-Identifier: AGPL-3.0-or-later
#include <stage.h>

#define STAGE_IS_NO2
#define BOSS_IS_BO0
#define OVL_EXPORT(x) BO0_##x

enum OVL_EXPORT(Entities) {
    E_NONE,
    E_UNK_BREAKABLE,       // EntityUnkBreakable
    E_EXPLOSION,           // EntityExplosion
    E_PRIZE_DROP,          // EntityPrizeDrop
    E_DAMAGE_DISPLAY,      // EntityDamageDisplay
    E_RED_DOOR,            // OVL_EXPORT(EntityRedDoor)
    E_INTENSE_EXPLOSION,   // EntityIntenseExplosion
    E_SOUL_STEAL_ORB,      // EntitySoulStealOrb
    E_ROOM_FOREGROUND,     // EntityRoomForeground
    E_STAGE_NAME_POPUP,    // EntityStageNamePopup
    E_EQUIP_ITEM_DROP,     // EntityEquipItemDrop
    E_RELIC_ORB,           // EntityRelicOrb
    E_HEART_DROP,          // EntityHeartDrop
    E_ENEMY_BLOOD,         // EntityEnemyBlood
    E_MESSAGE_BOX,         // EntityMessageBox
    E_DUMMY_F,             // EntityDummy
    E_DUMMY_10,            // EntityDummy
    E_BACKGROUND_BLOCK,    // OVL_EXPORT(EntityBackgroundBlock)
    E_LOCK_CAMERA,         // OVL_EXPORT(EntityLockCamera)
    E_UNK_ID13,            // EntityUnkId13
    E_EXPLOSION_VARIANTS,  // EntityExplosionVariants
    E_GREY_PUFF,           // EntityGreyPuff
    E_SKELERANG,           // EntitySkelerang
    E_SKELERANG_BOOMERANG, // EntitySkelerangBoomerang
    E_SKELERANG_UNKNOWN,   // EntitySkelerangUnknown
    E_UNK_19,              // func_us_801B3D8C
    E_UNK_1A,              // func_us_801B3F30
    E_UNK_1B,              // func_us_801B4148
    E_UNK_1C,              // func_us_801B41A4
    E_UNK_1D,              // func_us_801B4210
    E_3D_BACKGROUND_HOUSE, // Entity3DBackgroundHouse
    E_3D_HOUSE_SPAWNER,    // Entity3DHouseSpawner
    E_UNK_20,              // func_us_801B4DA4/func_pspeu_09253CB8
    E_SPIKES,              // EntitySpikes
    E_SPIKES_PARTS,        // EntitySpikesParts
    E_SPIKES_DUST,         // EntitySpikesDust
    E_UNK_24,              // func_us_801ABFE0/func_pspeu_0924FDC0
    E_UNK_25,              // func_us_801AC894/func_pspeu_092509C0
    E_UNK_26,              // func_us_801AC54C/func_pspeu_09250568
    E_UNK_27,              // func_pspeu_0923CB80
    E_BIG_RED_FIREBALL,    // EntityBigRedFireball
    E_PRISONER,            // EntityPrisoner
    E_UNK_2A,              // func_us_801B001C/func_pspeu_0925D328
    E_UNK_2B,              // func_us_801AD338/func_pspeu_09258F58
    E_OLROX_AFTER_IMAGE,   // EntityOlroxAfterImage
    E_UNK_2D,              // func_us_801AFAF4/func_pspeu_0925CBE8
    E_UNK_2E,           // func_us_801AF8C0/func_pspeu_0925C938 (EntityPortal)
    E_UNK_2F,           // func_us_801AF604/func_pspeu_0925C580
    E_UNK_30,           // func_us_801AF31C/func_pspeu_0925C178
    E_UNK_31,           // func_us_801AE858/func_pspeu_0925B1B0
    E_UNK_32,           // func_us_801B0930/func_pspeu_09255288
    E_UNK_33,           // func_us_801B365C/func_pspeu_092611E8
    E_UNK_34,           // func_us_801B5470/func_pspeu_09264380
    E_UNK_35,           // func_us_801B551C/func_pspeu_09264460
    E_UNK_36,           // func_us_801B619C/func_pspeu_092657B8
    E_UNK_37,           // func_us_801B6CA4/func_pspeu_092667C8
    E_UNK_38,           // func_us_801B76E4/func_pspeu_09267730
    E_UNK_39,           // func_us_801B8D8C/func_pspeu_09256A10
    E_UNK_3A,           // func_us_801B9BEC/func_pspeu_09257F58
    E_UNK_3B,           // func_us_801B7BAC/func_pspeu_09267E48
    E_UNK_3C,           // func_us_801B7CC8/func_pspeu_09267FC0
    E_UNK_3D,           // func_us_801BA128/func_pspeu_09258688
    E_UNK_3E,           // func_us_801BA4AC/func_pspeu_09258B10
    E_LIFE_UP_SPAWN,    // EntityLifeUpSpawn
    E_OWL_KNIGHT,       // EntityOwlKnight
    E_OWL,              // EntityOwl
    E_OWL_KNIGHT_SWORD, // EntityOwlKnightSword
    E_OWL_TARGET,       // EntityOwlTarget
    E_BLOODY_ZOMBIE,    // EntityBloodyZombie
    E_BLOOD_DRIPS,      // EntityBloodDrips
    E_BLOOD_SPLATTER,   // EntityBloodSplatter
    E_UNK_47,           // func_us_801B72E8
    E_SPIKES_DAMAGE,    // EntitySpikesDamage
    E_UNK_49,           // func_pspeu_09269760
    E_UNK_4A,           // func_pspeu_09251648
    E_CHAIR,            // EntityChair
    E_UNK_4C,           // 0x00000000
    NUM_ENTITIES,
};

enum OVL_EXPORT(Palette) {
    PAL_NONE,
    PAL_SPIKES_DUST = 0x161,
    PAL_BREAKABLE = 0x219,
    PAL_UNK_21B = 0x21B,
    PAL_UNK_21C,
    PAL_UNK_237 = 0x237,
    PAL_PUFF_OPAQUE_OFFSET = 0x2E0,
};

extern EInit g_EInitInteractable;
extern EInit g_EInitCommon;

#ifdef VERSION_PSP
extern s32 E_ID(SPIKES_PARTS);
extern s32 E_ID(SPIKES_DUST);
extern s32 E_ID(SPIKES_DAMAGE);
extern s32 E_ID(PRISONER);
extern s32 E_ID(3D_BACKGROUND_HOUSE);
extern s32 E_ID(UNK_49);
#endif
