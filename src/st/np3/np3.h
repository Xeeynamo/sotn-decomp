#include "stage.h"

typedef enum {
    /* 0x00 */ E_NONE,
    /* 0x01 */ E_BREAKABLE,
    /* 0x02 */ E_EXPLOSION,
    /* 0x03 */ E_PRIZE_DROP,
    /* 0x04 */ E_NUMERIC_DAMAGE,
    /* 0x05 */ E_RED_DOOR,
    /* 0x06 */ E_INTENSE_EXPLOSION,
    /* 0x07 */ E_SOUL_STEAL_ORB,
    /* 0x08 */ E_ROOM_FOREGROUND,
    /* 0x09 */ E_STAGE_NAME_POPUP,
    /* 0x0A */ E_EQUIP_ITEM_DROP,
    /* 0x0B */ E_RELIC_ORB,
    /* 0x0C */ E_HEART_DROP,
    /* 0x0D */ E_ENEMY_BLOOD,
    /* 0x0E */ E_SAVE_GAME_POPUP,
    /* 0x0F */ E_DUMMY_0F,
    /* 0x10 */ E_DUMMY_10,

    /* 0x15 */ E_ID_15 = 0x15,

    /* 0x19 */ E_ID_19 = 0x19,
    /* 0x1E */ E_ID_1E = 0x1E,
    /* 0x27 */ E_ID_27 = 0x27,
    /* 0x3F */ E_BONE_SCIMITAR_HEAD = 0x3F,
    /* 0x4D */ E_ID_4D = 0x4D,
    /* 0x4F */ E_SLOGRA_SPEAR = 0x4F,
    /* 0x50 */ E_SLOGRA_SPEAR_PROJECTILE,
    /* 0x51 */ E_GAIBON,
    /* 0x53 */ E_GAIBON_SMALL_FIREBALL = 0x53,
    /* 0x54 */ E_GAIBON_BIG_FIREBALL,
} EntityIDs;

extern void CreateEntityFromCurrentEntity(u16, Entity*);
extern void ReplaceBreakableWithItemDrop(Entity*);
extern void func_801BAFA0(s16);
extern void func_801BB044(s16);
extern void func_801BB140(s16);
extern void func_801BB2F8(s16);
extern void func_801BB3F4(s16);
extern s32 func_801BD308(u16* hitSensors, s16 sensorCount);
extern s32 func_801BD588(Entity* arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 GetDistanceToPlayerX(void);
extern s32 func_801CD658();
extern void EntityPrizeDrop(Entity* entity);
extern void EntityEquipItemDrop(Entity* entity);
extern Primitive* func_801D2470(Primitive* poly);
extern u16 g_eBreakableInit[];
extern u8* g_eBreakableAnimations[8];
extern u8 g_eBreakableHitboxes[];
extern u8 g_eBreakableExplosionTypes[];
extern u16 g_eBreakableanimSets[];
extern u8 g_eBreakableBlendModes[];
extern u16 D_80180A48[];
extern u16 D_80180A54[];
extern u16 D_80180A60[];
extern u16 D_80180A6C[];
extern u16 D_80180A78[];
extern u16 D_80180A84[];
extern u16 D_80180A90[];
extern u16 D_80180AA8[];
extern u16 D_80180AB4[];
extern u16 D_80180AC0[];
extern u16 D_80180ACC[];
extern u16 D_80180AD8[];
extern u16 D_80180AF0[];
extern u16 D_80180AFC[];
extern u16 D_80180AFC[];
extern u16 D_80180B08[];
extern u16 D_80180B20[];
extern u16 D_80180B50[];
extern u16 D_80180B5C[];
extern u16 D_80180B68[];
extern u16 D_80180B74[];
extern u16 D_80180B80[];
extern u16 D_80180B98[];
extern u16 D_80180BB0[];
extern ObjInit2 D_80180C10[];
extern u8 D_80180D98[];
extern u8 D_80180DA0[];
extern u16 D_80180DA8[];
extern SVEC4 D_80180F6C;
extern MATRIX D_80180F9C;
extern SVECTOR* D_80180FD4[];
extern u8 D_80180FE0[];
extern u16 D_80180FF8;
extern s16 D_80181098[][2];
extern s16 D_801810A8[];
extern SVECTOR D_801810B8[];
extern u16 D_801810F8[];
extern s32 g_TrapDoorFlag; // 0 = Closed, 1 = Open
extern const u8 D_80181108[];
extern u16 D_80181120[];
extern u16 D_8018112C[];
extern u16 D_80181144[];
extern u16 D_8018115C[]; // this could be a struct
extern u16 D_80181168[];
extern u16 D_80181180[];
extern u16 D_801811AA[];
extern u16 D_801811E6[];
extern u16 D_80181204[];

// *** Merman properties START ***

extern u16 D_80181230[];     // pos TBL
extern Point32 D_80182224[]; // accel_x TBL
extern u8 D_80182244[];      // timers
extern s32 D_80182248;       // Collision data
extern s32 D_80182258;       // Collision data
extern u16 D_80182268;       // Collision data
extern u8 D_80182270[];      // Animation
extern u8 D_8018227C[];      // Animation
extern u8 D_80182294[];      // Animation
extern u8 D_8018229C[];      // Animation
extern Point32 D_80182338[];
extern u8 D_80182358[];
extern s16 D_8018235C;
extern s16 D_8018236C;
extern s16 D_8018237C;
extern s16 D_8018238C;
extern u8 D_80182394[]; // animation
extern u8 D_801823AC[]; // animation
extern u8 D_801823BC[]; // animation
extern u8 D_801823D0[]; // animation
extern u8 D_801823DC[]; // animation
extern u8 D_801823EC[]; // animation
extern s32 D_80182418[];

// *** EntityMerman properties END ***

// *** EntitySlogra properties START ***

extern u16 D_80180B44[]; // Init
extern s32 D_801812CC;   // killed in entrance local flag
extern s32 D_801812D0;   // some collision data
extern u16 D_801812E0;   // some collision data
extern u8 D_801812E8[];  // animation
extern u8 D_801812F4[];  // animation
extern u8 D_80181300[];  // animation
extern u8 D_80181310[];  // animation
extern u8 D_8018131C[];  // animation
extern u8 D_80181328[];  // animation
extern u8 D_80181348[];  // animation
extern u8 D_8018135C[];  // animation
extern u8 D_80181370[];  // animation
extern u8 D_8018137C[];  // animation
extern u8 D_80181388[];  // animation
extern u8 D_8018139C[];  // animation
extern u8 D_801813B4[];  // animation
extern u8 D_801813C4[];  // animation
extern u8 D_801813CC[];  // animation
extern s32 D_801813EC[];
extern u8 D_8018142C[];

// *** EntitySlogra properties END ***

// *** EntityGaibon properties START ***

extern u16 D_80180B68[]; // Init
extern u16 D_80180B6E;   // Gaibon's palette data
extern s32 D_801812CC;   // killed in entrance local flag
extern s32 D_801814B4;   // Some collision data
extern u8 D_801814C4;    // Animation
extern u8 D_801814D8;    // Animation
extern u8 D_8018150C;    // Animation
extern u8 D_80181520;    // Animation
extern u8 D_80181534;    // Animation
extern u8 D_80181540;    // Animation
extern u8 D_80181550;    // Animation
extern u8 D_80181564;    // Animation
extern u8 D_80181570;    // Animation
extern u8 D_80181578;    // Animation
extern s32 D_80181584[]; // Hitbox related
extern u8 D_801815B4[];  // Hitbox related

// *** EntityGaibon properties END ***

extern u8 D_8018120C[]; // this could be a struct
extern const u8 D_80181214[];
extern s16 D_80181220[][2];
extern u8 D_801813D4[];
extern u8 D_801813E4[];
extern s8 D_80181454[];
extern u8 D_8018148C[];
extern u8 D_801815E0[];
extern u8 D_801815EC[];
extern u8 D_801815FC[];
extern u16 D_80181618[];
extern u16 UNK_Invincibility0[];
extern s16 D_80181A50[];
extern u16 D_80181D80[];
extern u16 D_80181DB0[];
extern const u32* D_80181DC4[];
extern const s32 c_GoldPrizes[];
extern u16 D_80181E74[];
extern s8 c_HeartPrizes[];
extern u8 D_80181EA8[];
extern s32 D_80181E80[];
extern const u8* D_80181F2C[];
extern s16 D_80181FB4[];
extern u32 D_80181FC4[];
extern s32 D_80181FDC[];
extern u8 D_80181FF4[];
extern u16 D_80181FF8[];
extern s16* D_80182000;
extern u8 D_80182008[];
extern u8 D_801822A4[];
extern const u8 D_801822B0[];
extern u8 D_801822B8[];
extern u8 D_801822C0[];
extern u8 D_80182400[];
extern u8 D_80182414[];
extern s32 D_80182440[];
extern u8 D_80182454[];
extern u16 D_80182458[];
extern s16 D_801824B8[];
extern s32 D_80182540;
extern s32 D_80182548;
extern u8 D_80182554[];
extern u8 D_80182570[];
extern u8 D_8018258C[];
extern u8 D_80182594[];
extern u8 D_801825A8[];
extern u8 D_801825BC[];
extern u16 D_801825CC;

// *** EntityBoneScimitar properties START ***

extern u16 D_80180AE4[];    // Init
extern s32 D_80182460;      // Flag for special bone scimitar to appear or not
extern u8 D_80182464[];     // animation: Walking Forward
extern u8 D_80182474[];     // animation: Walking Backwards
extern u8 D_80182484[];     // animation: Swing Sword
extern u8 D_801824A0[];     // animation: Jumping
extern u8 D_801824AC[];     // animation: Landing
extern s8 D_801824C8[];     // Skeleton parts array selector
extern s32 D_801824D0[];    // Skeleton parts velocityX
extern s32 D_801824EC[];    // Skeleton parts velocityY
extern u16 D_80182508[];    // Skeleton parts posX
extern u16 D_80182518[];    // Skeleton parts posY
extern s8 D_80182528[2][4]; // Skeleton attack timer cycle
extern s32 D_80182530;

// *** EntityBoneScimitar properties END ***

// *** EntityBloodyZombie properties START ***

extern u16 D_80180B38[]; // InitProps
extern u8 D_801D2770;
extern u8 D_801D2774;
extern LayoutEntity* D_801D2768;
extern LayoutEntity* D_801D276C;
extern u16 UNK_Update0[];
extern s32 D_801825D4;
extern u16 D_801825E4[];
extern u8 D_801825EC[]; // Animation: Walking
extern u8 D_801825FC[]; // Animation: Bloody Zombie sword slash
extern u8 D_80182620[]; // Animation: Recoil from being hit
extern u8 D_80182634[]; // Animation: Dying
extern u8 D_8018267C[]; // Animation: Walking faster
// unk80 Walking direction timer
// unk84 BloodSplatter facing

// *** EntityBloodyZombie properties END ***

extern s32 D_8018268C;
extern s32 D_801826A4;
extern s32 D_801826C4;
extern PfnEntityUpdate PfnEntityUpdates[];
extern u8 D_80182914[];
extern u8 D_80182935[];

// *** EntitySoulStealOrb properties START ***

extern u16 D_8018205C[]; // NOTE(sestren): Random angle offsets?
extern u16 D_8018206C[]; // NOTE(sestren): Animation frame properties?
extern u16 D_801820CC[];

// *** EntitySoulStealOrb properties END ***

extern SVECTOR D_801B1EA0;
