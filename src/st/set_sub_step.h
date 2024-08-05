void SetSubStep(u8 subStep) {
    Entity* entity = g_CurrentEntity;

    entity->step_s = subStep;
    entity->animFrameIdx = 0;
    entity->animFrameDuration = 0;
}