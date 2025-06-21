// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef DAI_H
#define DAI_H

#include "stage.h"

#define STAGE_IS_DAI
#define OVL_EXPORT(x) DAI_##x

#define STAGE_FLAG OVL_EXPORT(STAGE_FLAG)
#define SEALED_DOOR_PALETTE 0x245

enum DaiPalette {
    PAL_NONE = 0,
    PAL_UNKC9 = 0xC9,
    PAL_UNKCA = 0xCA,
    PAL_UNK200 = 0x200,
    PAL_UNK215 = 0x215,
    PAL_BONE_PILLAR = 0x216,
    PAL_BONE_PILLAR_FIRE = 0x221,
    PAL_UNK22A = 0x22A,
    PAL_UNK22B = 0x22B,
    PAL_BAT = 0x22C,
    PAL_UNK22F = 0x22F,
    PAL_UNK232 = 0x232,
    PAL_UNK234 = 0x234,
    PAL_UNK235 = 0x235,
};

enum DaiEntities {
    E_NONE,
    E_BREAKABLE,              // EntityUnkBreakable,
    E_EXPLOSION,              // EntityExplosion,
    E_PRIZE_DROP,             // EntityPrizeDrop,
    E_DAMAGE_DISPLAY,         // EntityDamageDisplay,
    E_RED_DOOR,               // DAI_EntityRedDoor,
    E_INTENSE_EXPLOSION,      // EntityIntenseExplosion,
    E_SOUL_STEAL_ORB,         // EntitySoulStealOrb,
    E_ROOM_FOREGROUND,        // EntityRoomForeground,
    E_STAGE_NAME_POPUP,       // EntityStageNamePopup,
    E_EQUIP_ITEM_DROP,        // EntityEquipItemDrop,
    E_RELIC_ORB,              // EntityRelicOrb,
    E_HEART_DROP,             // EntityHeartDrop,
    E_ENEMY_BLOOD,            // EntityEnemyBlood,
    E_MESSAGE_BOX,            // EntityMessageBox,
    E_DUMMY_F,                // EntityDummy,
    E_DUMMY_10,               // EntityDummy,
    E_BACKGROUND_BLOCK,       // DAI_EntityBackgroundBlock,
    E_LOCK_CAMERA,            // DAI_EntityLockCamera,
    E_UNK_13,                 // EntityUnkId13,
    E_EXPLOSION_VARIANTS,     // EntityExplosionVariants,
    E_GREY_PUFF,              // EntityGreyPuff,
    E_UNK_16,                 // func_us_801C0BA4,
    E_UNK_17,                 // func_us_801D97D0,
    E_UNK_18,                 // func_us_801D9F5C,
    E_UNK_19,                 // func_us_801C0F8C,
    E_UNK_1A,                 // func_us_801C1184,
    E_UNK_1B,                 // func_us_801C1298,
    E_UNK_1C,                 // func_us_801C1EE4,
    E_UNK_1D,                 // func_us_801C2068,
    E_UNK_1E,                 // func_us_801C220C,
    E_CLOUDS,                 // EntityClouds,
    E_UNK_20,                 // func_us_801C34FC,
    E_UNK_21,                 // func_us_801C23A4,
    E_UNK_22,                 // func_us_801C3164,
    E_UNK_23,                 // func_us_801C2534,
    E_UNK_24,                 // func_us_801C2CD4,
    E_UNK_25,                 // func_us_801C2FF0,
    E_UNK_26,                 // func_us_801C1E18,
    E_UNK_27,                 // func_us_801D1204,
    E_UNK_28,                 // func_us_801D1C24,
    E_BONE_PILLAR_HEAD,       // EntityBonePillarHead,
    E_BONE_PILLAR_FIRE,       // EntityBonePillarFireBreath,
    E_BONE_PILLAR_PIECES,     // EntityBonePillarDeathParts,
    E_BONE_PILLAR_SPIKE_BALL, // EntityBonePillarSpikeBall,
    E_UNK_2D,                 // func_us_801C3644,
    E_UNK_2E,                 // func_us_801C3D44,
    E_UNK_2F,                 // func_us_801C3850,
    E_UNK_30,                 // func_us_801C379C,
    E_UNK_31,                 // func_us_801C3ED8,
    E_UNK_32,                 // func_us_801D2FA4,
    E_UNK_33,                 // func_us_801D36EC,
    E_SKELETON_PIECES,        // EntitySkeletonPieces,
    E_UNK_35,                 // func_us_801D37C4,
    E_UNK_36,                 // func_us_801D3A40,
    E_BAT,                    // EntityBat,
    E_UNK_38,                 // func_us_801D3FD8,
    E_UNK_39,                 // func_us_801D43BC,
    E_SKELERANG,              // EntitySkelerang,
    E_SKELERANG_BOOMERANG,    // EntitySkelerangBoomerang,
    E_SKELERANG_UNKNOWN,      // EntitySkelerangUnknown,
    E_UNK_3D,                 // func_us_801D56F4,
    E_UNK_3E,                 // func_us_801D636C,
    E_UNK_3F,                 // func_us_801D64A0,
    E_UNK_40,                 // func_us_801D6FC8,
    E_UNK_41,                 // func_us_801D70A0,
    E_UNK_42,                 // func_us_801D3BD4,
    E_SEALED_DOOR,            // EntitySealedDoor,
    E_UNK_44,                 // func_801A8328,
    E_CUTSCENE,               // DAI_EntityCutscene,
    E_UNK_46,                 // func_us_801C5920,
    E_UNK_47,                 // func_us_801C5B88,
    E_MIST_DOOR,              // EntityMistDoor,
    NUM_ENTITIES,
};

extern EInit g_EInitBreakable;
extern EInit g_EInitObtainable;
extern EInit g_EInitParticle;
extern EInit g_EInitSpawner;
extern EInit g_EInitInteractable;
extern EInit g_EInitUnkId13;
extern EInit g_EInitLockCamera;
extern EInit g_EInitCommon;
// extern EInit g_EInitDamageNum;
// extern EInit g_EInit_801809A4;
extern EInit D_us_801809B0;
extern EInit D_us_801809BC;
// extern EInit g_EInit_801809C8;
extern EInit D_us_801809D4;
extern EInit D_us_801809E0;
extern EInit D_us_801809EC;
extern EInit g_EInitBonePillarHead;
extern EInit g_EInitBonePillarPieces;
extern EInit g_EInitBonePillarFireBreath;
extern EInit g_EInitBonePillarSpikeBall;
extern EInit D_us_80180A28;
extern EInit D_us_80180A34;
extern EInit D_us_80180A40;
extern EInit D_us_80180A4C;
extern EInit g_EInitBat;
extern EInit D_us_80180A64;
extern EInit D_us_80180A70;
extern EInit g_EInitSkelerang;
extern EInit g_EInitSkelerangBoomerang;
extern EInit D_us_80180A94;
extern EInit D_us_80180AA0;
extern EInit D_us_80180AAC;
extern EInit D_us_80180AB8;

#endif
