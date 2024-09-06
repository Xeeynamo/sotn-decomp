// SPDX-License-Identifier: AGPL-3.0-or-later
extern u16 g_InitializeEntityData0[];
extern s32 g_ExplosionYVelocities[];
extern u8* g_ExplosionAnimations[];

// when `AnimateEntity` is not declared, the default declaration
// is used which assumes a 32 bit return type. This prototype
// can be forced by setting MISSING_ANIMATE_ENTITY_PROTOTYPE
typedef u32 (*AnimateEntityMissingProto)(u8[], Entity*);

void EntityExplosion(Entity* entity) {
    if (!entity->step) {
        InitializeEntity(g_InitializeEntityData0);
        entity->animFrameIdx = 0;
        entity->animFrameDuration = 0;
        entity->animSet = ANIMSET_DRA(2);
        entity->drawMode = 0x30;
        if (entity->params & 0xF0) {
            entity->palette = PAL_OVL(0x195);
            entity->drawMode = DRAW_TPAGE;
        }

        if (entity->params & 0xFF00) {
            entity->zPriority = (entity->params & 0xFF00) >> 8;
        }
        entity->params &= 15;
        entity->velocityY = g_ExplosionYVelocities[entity->params];
    } else {
        entity->posY.val += entity->velocityY;

#ifdef MISSING_ANIMATE_ENTITY_PROTOTYPE
        if (!((AnimateEntityMissingProto)AnimateEntity)(
                g_ExplosionAnimations[entity->params], entity)) {
#else
        if (!AnimateEntity(g_ExplosionAnimations[entity->params], entity)) {
#endif
            DestroyEntity(entity);
        }
    }
}
