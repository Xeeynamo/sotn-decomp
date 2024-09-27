// SPDX-License-Identifier: AGPL-3.0-or-later
void SetEntityAnimation(Entity* entity, AnimationFrame* anim) {
    if (entity->anim != anim) {
        entity->anim = anim;
        entity->animFrameIdx = 0;
        entity->animFrameDuration = 0;
    }
}
