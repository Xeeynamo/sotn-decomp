// SPDX-License-Identifier: AGPL-3.0-or-later

extern EInit g_EInitCommon;

#ifdef OVL_EXPORT
#define STAGE_BACKGROUND_BLOCK_INIT OVL_EXPORT(BackgroundBlockInit)
#else
#define STAGE_BACKGROUND_BLOCK_INIT BackgroundBlockInit
#endif
extern ObjInit2 STAGE_BACKGROUND_BLOCK_INIT[];

void EntityBackgroundBlock(Entity* self) {
    ObjInit2* objInit = &STAGE_BACKGROUND_BLOCK_INIT[self->params];
    if (!self->step) {
        InitializeEntity(g_EInitCommon);
        self->animSet = objInit->animSet;
        self->zPriority = objInit->zPriority;
#if defined(BG_FACING_LEFT_FIX)
        self->facingLeft = objInit->facingLeft;
        self->unk5A = objInit->unk5A;
#elif defined(VERSION_PSP)
        self->unk5A = LOHU(objInit->facingLeft);
#else
        self->unk5A = LOH(objInit->facingLeft);
#endif
        self->palette = objInit->palette;
        self->drawFlags = objInit->drawFlags;
        self->blendMode = objInit->blendMode;
        if (objInit->flags) {
            self->flags = objInit->flags;
        }
#ifdef BG_BLOCK_NEEDS_SCALE
        if (self->params == 1) {
            self->scaleX = self->scaleY = 0x200;
        }
#endif
    }
    AnimateEntity(objInit->animFrames, self);
}
