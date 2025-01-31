// SPDX-License-Identifier: AGPL-3.0-or-later
#include <stage.h>

static u8 foregroundAnim1[] = {0x40, 0x01, 0xFF, 0x00};
static u8 foregroundAnim2[] = {0x40, 0x02, 0xFF, 0x00};
static u8 foregroundAnim3[] = {0x40, 0x02, 0xFF, 0x00};
static u8 foregroundAnim4[] = {0x40, 0x01, 0xFF, 0x00};
static u8 foregroundAnim5[] = {0x40, 0x03, 0xFF, 0x00};
static ObjInit eRoomForegroundInit[] = {
    {0x0006, 0x01EC, 0x0000, 0x0000, 0x00, 0x10, 0, foregroundAnim1},
    {0x000C, 0x01EC, 0x0000, 0x0000, 0x00, 0x10, 0, foregroundAnim3},
    {0x000C, 0x0080, 0x0000, 0x0000, 0x00, 0x10, 0, foregroundAnim4},
    {0x0006, 0x01EC, 0x0000, 0x0000, 0x00, 0x10, 0, foregroundAnim2},
    {0x000C, 0x01EC, 0x0000, 0x0000, 0x00, 0x10, 0, foregroundAnim5},
    {0x000C, 0x0080, 0x0000, 0x0000, 0x00, 0x10, 0, foregroundAnim4},
};

extern u16 g_EInitCommon[];

// params: Which foreground ObjInit to use
//         (> 4) These entries use an alternate hardcoded drawFlags and rotZ
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
            entity->rotZ = 0x800;
        }
    }
    AnimateEntity(objInit->animFrames, entity);
}
