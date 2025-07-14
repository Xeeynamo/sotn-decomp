// SPDX-License-Identifier: AGPL-3.0-or-later
#include <stage.h>

static u8 foregroundAnim1[] = {64, 1, -1, 0};
static u8 foregroundAnim2[] = {64, 2, -1, 0};
static u8 foregroundAnim3[] = {64, 2, -1, 0};
static u8 foregroundAnim4[] = {64, 1, -1, 0};
static u8 foregroundAnim5[] = {64, 3, -1, 0};
static ObjInit eRoomForegroundInit[] = {
    {0x0006, 0x1EC, 0, 0, 0, DRAW_TPAGE, 0, foregroundAnim1},
    {0x000C, 0x1EC, 0, 0, 0, DRAW_TPAGE, 0, foregroundAnim3},
    {0x000C, 0x080, 0, 0, 0, DRAW_TPAGE, 0, foregroundAnim4},
    {0x0006, 0x1EC, 0, 0, 0, DRAW_TPAGE, 0, foregroundAnim2},
    {0x000C, 0x1EC, 0, 0, 0, DRAW_TPAGE, 0, foregroundAnim5},
    {0x000C, 0x080, 0, 0, 0, DRAW_TPAGE, 0, foregroundAnim4},
};

extern u16 g_EInitCommon[];

// params: Which foreground ObjInit to use
//         (> 4) These entries use an alternate hardcoded drawFlags and rotate
void EntityRoomForeground(Entity* entity) {
    ObjInit* objInit = &eRoomForegroundInit[entity->params];

    if (!entity->step) {
        InitializeEntity(g_EInitCommon);
        entity->animSet = objInit->animSet;
        entity->zPriority = objInit->zPriority;
        entity->unk5A = objInit->unk5A;
        entity->palette = objInit->palette;
        entity->drawFlags = objInit->drawFlags;
        entity->drawMode = objInit->drawMode;
        if (objInit->flags != 0) {
            entity->flags = objInit->flags;
        }
        if (entity->params > 4) {
            entity->drawFlags |= DRAW_COLORS;
            entity->rotate = 0x800;
        }
    }
    AnimateEntity(objInit->animFrames, entity);
}
