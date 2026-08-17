// SPDX-License-Identifier: AGPL-3.0-or-later
#include <game.h>
#include <cutscene.h>
#include <string.h>
#include "overlay.h"
#include "../pc.h"
#include "../../st/no4/no4.h"

extern AbbreviatedOverlay g_Overlay;
extern PfnEntityUpdate EntityUpdates[];
extern LayoutEntity* entityLayoutHorizontal[];
extern LayoutEntity* entityLayoutVertical[];
extern GAME_IMPORT PfnEntityUpdate* PfnEntityUpdates;
extern GAME_IMPORT LayoutEntity** g_pStObjLayoutHorizontal;
extern GAME_IMPORT LayoutEntity** g_pStObjLayoutVertical;

extern u8 cutscene_data_ferryman_left[];
extern u8 cutscene_data_ferryman_right[];
extern u8 gfx_portrait_ferryman[];

s16 D_us_80180F1A[] = {0x00C0};

static void UnsupportedWaterEntity(Entity* self) { DestroyEntity(self); }

void EntityAlucardWaterEffect(Entity* self) { UnsupportedWaterEntity(self); }
void EntitySplashWater(Entity* self) { UnsupportedWaterEntity(self); }
void EntitySurfacingWater(Entity* self) { UnsupportedWaterEntity(self); }
void EntitySideWaterSplash(Entity* self) { UnsupportedWaterEntity(self); }
void EntitySmallWaterDrop(Entity* self) { UnsupportedWaterEntity(self); }
void EntityWaterDrop(Entity* self) { UnsupportedWaterEntity(self); }

static void InitCutscenePc(void) {
    static const CutsceneSymbolRange symbols[] = {
        {cutscene_data_ferryman_left, 0x80185354, 0x63},
        {cutscene_data_ferryman_right, 0x801853b7, 0x49},
        {gfx_portrait_ferryman, 0x8018c300, 0xd80},
    };
    CutscenePcAlloc(symbols, LEN(symbols));
}

OVL_API void InitStage(Overlay* o) {
    memcpy(o, &g_Overlay, sizeof(AbbreviatedOverlay));
    PfnEntityUpdates = EntityUpdates;
    g_pStObjLayoutHorizontal = entityLayoutHorizontal;
    g_pStObjLayoutVertical = entityLayoutVertical;
    InitCutscenePc();
}
