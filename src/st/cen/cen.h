#ifndef CEN_H
#define CEN_H

#include "common.h"
#include "stage.h"

extern PfnEntityUpdate D_80180390[];
extern u16 D_80180410[];
extern u16 D_801805D8[];
extern s16 D_80180BBC[];
void CreateEntityFromCurrentEntity(u16 objectId, Entity* entity);
extern LayoutObject* D_8019C764;
extern LayoutObject* D_8019C768;
extern s16 D_8019D3B4;
extern s16 D_8019D3B6;
extern s32 D_8019D3B8;
#endif