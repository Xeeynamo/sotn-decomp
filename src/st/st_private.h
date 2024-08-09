#ifndef ST_PRIVATE_H
#define ST_PRIVATE_H

#include <stage.h>

#define LAYOUT_OBJ_START 0xfffe
#define LAYOUT_OBJ_END 0xffff

#define LAYOUT_OBJ_POSITION_FORWARD 0
#define LAYOUT_OBJ_POSITION_BACKWARD 1

// Follows the struct from LayoutEntity
#define LAYOUT_OBJ_POS_X 0
#define LAYOUT_OBJ_POS_Y 1
#define LAYOUT_OBJ_ID 2
#define LAYOUT_OBJ_SLOT 3
#define LAYOUT_OBJ_PARAMS 4

// TODO: are these necessary any longer?
/*
 * A pointer to the current element in `g_pStObjLayoutHorizontal`
 */
extern u16* g_LayoutObjHorizontal;
/*
 * A pointer to the current element in `g_pStObjLayoutVertical`
 */
extern u16* g_LayoutObjVertical;
/*
 * The direction last traversed in `g_pStObjLayoutHorizontal`
 */
extern u8 g_LayoutObjPosHorizontal;
/*
 * The direction last traversed in `g_pStObjLayoutVertical``
 */
extern u8 g_LayoutObjPosVertical;

#endif // ST_PRIVATE_H
