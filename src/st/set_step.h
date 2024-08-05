void SetStep(u8 step) {
    Entity* entity = g_CurrentEntity;

    entity->step = step;
    entity->step_s = 0;
    entity->animFrameIdx = 0;
    entity->animFrameDuration = 0;
}