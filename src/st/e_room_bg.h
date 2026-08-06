// SPDX-License-Identifier: AGPL-3.0-or-later

extern EInit g_EInitCommon;

#if defined(BG_BLOCK_OBJINIT_PLAIN)
extern ObjInit OVL_EXPORT(BackgroundBlockInit)[];
#else
extern ObjInit2 OVL_EXPORT(BackgroundBlockInit)[];
#endif

void OVL_EXPORT(EntityBackgroundBlock)(Entity* self) {
#if defined(BG_BLOCK_OBJINIT_PLAIN)
    ObjInit* objInit = &OVL_EXPORT(BackgroundBlockInit)[self->params];
#else
    ObjInit2* objInit = &OVL_EXPORT(BackgroundBlockInit)[self->params];
#endif
    if (!self->step) {
        InitializeEntity(g_EInitCommon);
        self->animSet = objInit->animSet;
        self->zPriority = objInit->zPriority;
#if defined(BG_BLOCK_OBJINIT_PLAIN)
        self->unk5A = objInit->unk5A;
#elif defined(BG_FACING_LEFT_FIX)
        self->facingLeft = objInit->facingLeft;
        self->unk5A = objInit->unk5A;
#elif defined(VERSION_PSP)
        self->unk5A = LOHU(objInit->facingLeft);
#else
        self->unk5A = LOH(objInit->facingLeft);
#endif
        self->palette = objInit->palette;
        self->drawFlags = objInit->drawFlags;
#if defined(BG_BLOCK_OBJINIT_PLAIN)
        self->rotate = 0x800;
#endif
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
