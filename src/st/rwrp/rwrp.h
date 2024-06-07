#ifndef RWRP_H
#define RWRP_H

#include "common.h"
#include "stage.h"

#define CASTLE_FLAG_BANK 0x00

// RWRP Sound IDs
#define SE_RWRP_ENTER 0x636
#define SE_RWRP_DEBRIS 0x644 // unused?

extern PfnEntityUpdate D_801803E0[];
extern u16 D_80180494[];
extern s16 D_80180A94[];
extern ObjInit2 D_80181134[];

void CreateEntityFromLayout(Entity*, LayoutEntity*);

// *** EntitySoulStealOrb properties START ***

extern u16 g_ESoulStealOrbAngles[];
extern s16 g_ESoulStealOrbSprt[];
extern u16 g_InitializeData0[];
extern u8 g_ESoulStealOrbAnim[];

// *** EntitySoulStealOrb properties END ***
extern u16 D_80180DC4[];
extern u16 D_80180DF4[];
extern u8* D_80180E08[];

extern u16 g_InitializeEntityData0[];

void InitializeEntity(u16 arg0[]);
void EntityUnkId14(Entity* entity);
void EntityUnkId15(Entity* entity);
void EntityExplosion(Entity* entity);

typedef enum {
    E_SHARED_END = E_DUMMY_10,
    E_UNK_11,
    E_UNK_12,
    E_UNK_13,
    E_ID_14,
    E_ID_15,
} EntityIDs;

#endif
