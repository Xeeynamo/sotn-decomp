// SPDX-License-Identifier: AGPL-3.0-or-later
#include "mad.h"

static u8 foregroundAnim1[] = {64, 1, -1, 0};
static u8 foregroundAnim2[] = {64, 2, -1, 0};
static u8 foregroundAnim3[] = {64, 1, -1, 0};
static ObjInit eRoomForegroundInit[] = {
    {0x0006, 0x1EC, 0, 0, 0, BLEND_TRANSP, 0, foregroundAnim1},
    {0x000C, 0x1EC, 0, 0, 0, BLEND_TRANSP, 0, foregroundAnim2},
    {0x000C, 0x080, 0, 0, 0, BLEND_TRANSP, 0, foregroundAnim3},
};

void EntityRoomForeground(Entity* entity) {
    ObjInit* obj = &eRoomForegroundInit[entity->params];

    if (entity->step == 0) {
        InitializeEntity(g_EInitCommon);
        entity->animSet = obj->animSet;
        entity->zPriority = obj->zPriority;
        entity->unk5A = obj->unk5A;
        entity->palette = obj->palette;
        entity->drawFlags = obj->drawFlags;
        entity->blendMode = obj->blendMode;
        if (obj->flags != 0) {
            entity->flags = obj->flags;
        }
    }
    AnimateEntity(obj->animFrames, entity);
}
