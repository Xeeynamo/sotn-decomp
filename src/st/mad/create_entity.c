#include "mad.h"

// BSS START size = 0x16
static u16* g_LayoutObjHorizontal;
static u16* g_LayoutObjVertical;
static u8 g_LayoutObjPosHorizontal;
STATIC_PAD_BSS(3);
static u8 g_LayoutObjPosVertical;
STATIC_PAD_BSS(3);
// END BSS

#include "../st_private.h"

#include "../create_entity_from_layout.h"
#include "../create_entity_in_range.h"
#include "../find_entity_horizontal.h"
#include "../create_entities_right.h"

/*
 * n.b.! This is different from every other stage's `CreateEntitiesToTheLeft`.
 * It will at most create 1 entity to the left and then exit with the horizontal
 * array pointer updated to the next element in the sequence.
 */
void CreateEntitiesToTheLeft(s16 posX) {
    u8 flag;
    s32 expected = 0;

    if (posX < 0) {
        posX = 0;
    }

    if (g_LayoutObjPosHorizontal == LAYOUT_OBJ_POSITION_FORWARD) {
        FindFirstEntityToTheLeft(posX - g_ScrollDeltaX);
        g_LayoutObjPosHorizontal = LAYOUT_OBJ_POSITION_BACKWARD;
    }

    if (g_LayoutObjHorizontal[LAYOUT_OBJ_POS_X] == LAYOUT_OBJ_START ||
        g_LayoutObjHorizontal[LAYOUT_OBJ_POS_X] < posX) {
        return;
    }

    flag = (g_LayoutObjHorizontal[LAYOUT_OBJ_SLOT] >> 8) + 0xff;
    expected = 0;
    if (flag == 0xFF ||
        ((g_entityDestroyed[flag >> 5] & (1 << (flag & 0x1f))) == expected)) {
        CreateEntityWhenInVerticalRange(g_LayoutObjHorizontal);
    }
    g_LayoutObjHorizontal -= 5;
}

#include "../find_entity_vertical.h"
#include "../create_entities_vertical.h"
#include "../init_room_entities.h"
#include "../update_room_position.h"
#include "../create_entity_from_entity.h"
