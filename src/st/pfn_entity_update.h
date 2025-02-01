// SPDX-License-Identifier: AGPL-3.0-or-later

// NOTE: include this AFTER the stage entity is included
// this is to ensure OVL_EXPORT is defined

#if defined(VERSION_PSP) || defined(VERSION_PC)

extern PfnEntityUpdate OVL_EXPORT(EntityUpdates)[];
extern PfnEntityUpdate* PfnEntityUpdates;

// A horizontally ordered array with head and tail sigils in the 1st field
extern LayoutEntity** g_pStObjLayoutHorizontal;
#define OBJ_LAYOUT_HORIZONTAL g_pStObjLayoutHorizontal

// A vertically ordered array with head and tail sigils in the 1st field
extern LayoutEntity** g_pStObjLayoutVertical;
#define OBJ_LAYOUT_VERTICAL g_pStObjLayoutVertical
#else

extern PfnEntityUpdate OVL_EXPORT(EntityUpdates)[];
#define PfnEntityUpdates OVL_EXPORT(EntityUpdates)

// A horizontally ordered array with head and tail sigils in the 1st field
extern LayoutEntity* OVL_EXPORT(pStObjLayoutHorizontal)[];
#define OBJ_LAYOUT_HORIZONTAL OVL_EXPORT(pStObjLayoutHorizontal)

// A vertically ordered array with head and tail sigils in the 1st field
extern LayoutEntity* OVL_EXPORT(pStObjLayoutVertical)[];
#define OBJ_LAYOUT_VERTICAL OVL_EXPORT(pStObjLayoutVertical)

#endif
