// SPDX-License-Identifier: AGPL-3.0-or-later
u8 AnimateEntity(u8 frames[], Entity* entity) {
    u16 flag;
    u16 currentFrameIndex;
    u8* currentFrame;

    flag = 0;
    currentFrameIndex = entity->animFrameIdx * 2;
    currentFrame = frames + currentFrameIndex;

    if (!entity->animFrameDuration) {
        if (currentFrame[0]) {
            if (currentFrame[0] == 0xFF) {
                return 0;
            }

            entity->animFrameDuration = *currentFrame++;
            entity->animCurFrame = *currentFrame++;
            entity->animFrameIdx++;
            flag |= 0x80;
        } else {
            entity->animFrameIdx = 0;
            entity->animFrameDuration = 0;
            currentFrame = frames;
            entity->animFrameDuration = *currentFrame++;
            entity->animCurFrame = *currentFrame++;
            entity->animFrameIdx++;
            return 0;
        }
    }

    entity->animFrameDuration--;
    entity->animCurFrame = currentFrame[-1];
    flag |= true;

    return flag;
}
