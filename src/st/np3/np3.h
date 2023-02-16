#include "stage.h"

void CreateEntityFromCurrentEntity(u16, Entity*);
void ReplaceBreakableWithItemDrop(Entity*);
s32 func_801BCB5C(u16* arg0);
s16 func_801BD308(u16* arg0, s32 arg1);
s32 func_801BC7D4(void);
int func_801CD658();
void EntityPriceDrop(Entity* entity);
void EntityInventoryDrop(Entity* entity);

extern u16 D_80180A54[];
extern u16 D_80180A78[];
extern u16 D_80180A90[];
extern u16 D_80180AA8[];
extern u16 D_80180AB4[];
extern u16 D_80180ACC[];
extern u16 D_80180AD8[];
extern u16 D_80180AF0[];
extern u16* D_80180AFC;
extern ObjInit2 D_80180C10[];
extern s16 D_80181A50[];
extern u8* D_801822B8;
extern u8* D_801822C0;
extern s32 D_80182440[];
extern u8 D_80182454[];
extern u16 D_80182458[];
extern s16 D_801824B8[];
extern s32 D_80182540;
extern s32 D_80182548;
extern u16* D_80182554;
extern u16* D_80182570;
extern u16* D_80182400;
extern u8* D_80182414;
extern u8 D_8003BE1C[]; // probably part of a struct
extern u8 D_8003BE1D[]; // probably part of a struct
extern PfnEntityUpdate PfnEntityUpdates[];