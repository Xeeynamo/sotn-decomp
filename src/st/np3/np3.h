#include "stage.h"

void CreateEntityFromCurrentEntity(u16, Entity*);
void ReplaceBreakableWithItemDrop(Entity*);
int func_801CD658();
void EntityPriceDrop(Entity* entity);
void EntityInventoryDrop(Entity* entity);

extern u16 D_80180A78[];
extern u16 D_80180A90[];
extern u16 D_80180AA8[];
extern u16 D_80180AB4[];
extern u16 D_80180ACC[];
extern u16 D_80180AD8[];
extern u16* D_80180AFC;
extern ObjInit2 D_80180C10[];
extern s16 D_80181A50[];
extern u8* D_801822B8;
extern u16* D_80182554;
extern u16* D_80182570;
extern u16* D_80182400;
extern u8* D_80182414;
extern u8 D_8003BE1C[]; // probably part of a struct
extern u8 D_8003BE1D[]; // probably part of a struct
extern PfnEntityUpdate PfnEntityUpdates[];