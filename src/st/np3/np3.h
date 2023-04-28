#include "stage.h"

extern void CreateEntityFromCurrentEntity(u16, Entity*);
extern void ReplaceBreakableWithItemDrop(Entity*);
extern s32 func_801BCB5C(u16* arg0);
extern s32 func_801BD308(u16* hitSensors, s16 sensorCount);
extern s32 func_801BD588(Entity* arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 GetPlayerDistanceX(void);
extern void func_801C2598(s16 arg0);
extern s32 func_801CD658();
extern void EntityPrizeDrop(Entity* entity);
extern void EntityEquipItemDrop(Entity* entity);
extern POLY_GT4* func_801D2470(POLY_GT4* poly);
extern u16 D_80180A48[];
extern u16 D_80180A54[];
extern u16 D_80180A60[];
extern u16 D_80180A6C[];
extern u16 D_80180A78[];
extern u16 D_80180A90[];
extern u16 D_80180AA8[];
extern u16 D_80180AB4[];
extern u16 D_80180ACC[];
extern u16 D_80180AD8[];
extern u16 D_80180AF0[];
extern u16* D_80180AFC;
extern u16 D_80180B08[];
extern u16 D_80180B50[];
extern u16 D_80180B5C[];
extern u16 D_80180B68[];
extern u16 D_80180B74[];
extern u16 D_80180B80[];
extern ObjInit2 D_80180C10[];
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
extern u8 D_8018120C[]; // this could be a struct
extern const u8 D_80181214[];
extern s16 D_80181220[][2];
extern const u8* D_801813D4;
extern const u8* D_801813E4;
extern s8 D_80181454[];
extern u8 D_8018148C[];
extern const u8 D_801815E0[];
extern const u8* D_801815EC;
extern const u8* D_801815FC;
extern u16 D_80181618[];
extern u16 D_8018164C[];
extern s16 D_80181A50[];
extern u16 D_80181E74[];
extern s32 D_80181E80[];
extern const u8* D_80181F2C[];
extern s32 D_80181FDC[];
extern u8 D_80181FF4[];
extern u16 D_80181FF8[];
extern s16* D_80182000;
extern const u8 D_801822B0[];
extern u8* D_801822B8;
extern u8* D_801822C0;
extern u16* D_80182400;
extern u8* D_80182414;
extern s32 D_80182440[];
extern u8 D_80182454[];
extern u16 D_80182458[];
extern s16 D_801824B8[];
extern s32 D_80182540;
extern s32 D_80182548;
extern u16* D_80182554;
extern u16* D_80182570;
extern u8 D_8018258C[];
extern u8 D_80182594[];
extern u8 D_801825A8[];
extern u8 D_801825BC[];
extern u16 D_801825CC;

// *** EntityBloodyZombie properties START ***

typedef enum {
    BLOODY_ZOMBIE_INIT,
    BLOODY_ZOMBIE_WALK,
    BLOODY_ZOMBIE_UNK_2,
    BLOODY_ZOMBIE_CHASE,
    BLOODY_ZOMBIE_ATTACK,
    BLOODY_ZOMBIE_TAKE_HIT = 6,
    BLOODY_ZOMBIE_DYING = 8,
    BLOODY_ZOMBIE_DESTROY
} EntityBloodyZombieSteps;

extern u16 D_80180B38[]; // InitProps
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
extern PfnEntityUpdate PfnEntityUpdates[];
LayoutObject* D_801D276C;
extern u16 D_801D33F4[];
