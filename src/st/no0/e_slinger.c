#include "no0.h"

INCLUDE_ASM("st/no0/nonmatchings/e_slinger", func_us_801D75E4);

INCLUDE_ASM("st/no0/nonmatchings/e_slinger", func_us_801D7670);

extern u16 g_EInitSlingerPieces[];
extern u16 anim_bone_rot[];

// Bone parts that rotate and fall down when killed
// This is a duplicate of EntitySkeletonPieces and EntityBoneScimitarParts
void EntitySlingerPieces(Entity* self) {
    if (self->step) {
        self->ext.skeleton.explosionTimer--;
        if (self->ext.skeleton.explosionTimer & 0xFF) {
            self->rotZ += anim_bone_rot[self->params];
            FallEntity();
            MoveEntity();
            return;
        }

        self->entityId = E_EXPLOSION;
        self->pfnUpdate = (PfnEntityUpdate)EntityExplosion;
        self->params = 0;
        self->step = 0;
        return;
    }

    InitializeEntity(g_EInitSlingerPieces);
    self->drawFlags = FLAG_DRAW_ROTZ;
    self->animCurFrame = self->params + 15;

    if (self->facingLeft) {
        self->velocityX = -self->velocityX;
    }
}
