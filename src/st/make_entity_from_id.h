// SPDX-License-Identifier: AGPL-3.0-or-later
extern PfnEntityUpdate PfnEntityUpdates[];
void MakeEntityFromId(u16 entityId, Entity* src, Entity* dst) {
    DestroyEntity(dst);
    dst->entityId = entityId;
    dst->pfnUpdate = PfnEntityUpdates[entityId - 1];
    dst->posX.i.hi = src->posX.i.hi;
    dst->posY.i.hi = src->posY.i.hi;
    dst->unk5A = src->unk5A;
    dst->zPriority = src->zPriority;
    dst->animSet = src->animSet;
    dst->flags = FLAG_UNK_2000 | FLAG_NOT_AN_ENEMY | FLAG_KEEP_ALIVE_OFFCAMERA |
                 FLAG_POS_CAMERA_LOCKED | FLAG_DESTROY_IF_BARELY_OUT_OF_CAMERA |
                 FLAG_DESTROY_IF_OUT_OF_CAMERA;

    if (src->palette & PAL_OVL_FLAG) {
        dst->palette = src->hitEffect;
    } else {
        dst->palette = src->palette;
    }
}
