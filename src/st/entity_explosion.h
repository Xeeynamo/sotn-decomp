// SPDX-License-Identifier: AGPL-3.0-or-later
extern u16 g_EInitParticle[];
extern s32 g_ExplosionYVelocities[];
extern u8* g_ExplosionAnimations[];

// params: (& 0xFF) The explosion type
//         (& 0xF0) These explosion types use a different (hardcoded) palette
//                  and drawMode
//         (& 0xFF00) If non-zero, ((& 0xFF00) >> 8) will override zPriority
void EntityExplosion(Entity* entity) {
    if (!entity->step) {
        InitializeEntity(g_EInitParticle);
        entity->animFrameIdx = 0;
        entity->animFrameDuration = 0;
        entity->animSet = ANIMSET_DRA(2);
        entity->drawMode = DRAW_TPAGE2 | DRAW_TPAGE;
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

        if (!AnimateEntity(g_ExplosionAnimations[entity->params], entity)) {
            DestroyEntity(entity);
        }
    }
}
