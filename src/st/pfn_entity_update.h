// SPDX-License-Identifier: AGPL-3.0-or-later

// NOTE: include this AFTER the stage entity is included
// this is to ensure OVL_EXPORT is defined

extern PfnEntityUpdate EntityUpdates[];

#if defined(VERSION_PSP) || defined(VERSION_PC)

extern GAME_IMPORT PfnEntityUpdate* PfnEntityUpdates;

// A horizontally ordered array with head and tail sigils in the 1st field
extern GAME_IMPORT LayoutEntity** g_pStObjLayoutHorizontal;
#define OBJ_LAYOUT_HORIZONTAL g_pStObjLayoutHorizontal

// A vertically ordered array with head and tail sigils in the 1st field
extern GAME_IMPORT LayoutEntity** g_pStObjLayoutVertical;
#define OBJ_LAYOUT_VERTICAL g_pStObjLayoutVertical
#else

#define PfnEntityUpdates EntityUpdates

// A horizontally ordered array with head and tail sigils in the 1st field
extern LayoutEntity* entityLayoutHorizontal[];
#define OBJ_LAYOUT_HORIZONTAL entityLayoutHorizontal

// A vertically ordered array with head and tail sigils in the 1st field
extern LayoutEntity* entityLayoutVertical[];
#define OBJ_LAYOUT_VERTICAL entityLayoutVertical

#endif
