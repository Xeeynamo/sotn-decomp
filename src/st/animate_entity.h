// SPDX-License-Identifier: AGPL-3.0-or-later
u8 AnimateEntity(u8 frames[], Entity* entity) {
    u16 flag;
    u16 currentFrameIndex;
    u8* currentFrame;

    flag = 0;
    currentFrameIndex = entity->pose * 2;
    currentFrame = frames + currentFrameIndex;

    if (!entity->poseTimer) {
        if (currentFrame[0]) {
            if (currentFrame[0] == 0xFF) {
                return 0;
            }

            entity->poseTimer = *currentFrame++;
            entity->animCurFrame = *currentFrame++;
            entity->pose++;
            flag |= 0x80;
        } else {
            entity->pose = 0;
            entity->poseTimer = 0;
            currentFrame = frames;
            entity->poseTimer = *currentFrame++;
            entity->animCurFrame = *currentFrame++;
            entity->pose++;
            return 0;
        }
    }

    entity->poseTimer--;
    entity->animCurFrame = currentFrame[-1];
    flag |= true;

    return flag;
}
