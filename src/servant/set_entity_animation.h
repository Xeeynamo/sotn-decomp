// SPDX-License-Identifier: AGPL-3.0-or-later
static void SetEntityAnimation(Entity* entity, AnimationFrame* anim) {
    if (entity->anim != anim) {
        entity->anim = anim;
        entity->pose = 0;
        entity->poseTimer = 0;
    }
}
