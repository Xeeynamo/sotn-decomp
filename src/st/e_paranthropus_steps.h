// SPDX-License-Identifier: AGPL-3.0-or-later

enum ParanthropusStep {
    INIT = 0,
    FALL_TO_GROUND = 1,
    DIVE_RECOVERY = 2,
    WALK = 3,
    THROW_BONE = 4,
    SWING_BONE = 5,
    DIVE = 6,
    DEATH = 7,
    DEATH_EFFECTS = 8,
    DEATH_PARTS_VACUUM = 9,
    DEATH_SKULL_REMAINS = 11
};

void ParanthropusSetStep(u16 step) {
    g_CurrentEntity->pose = 0;
    g_CurrentEntity->poseTimer = 0;
    g_CurrentEntity->ext.paranthropus.unk7C = 0;
    g_CurrentEntity->ext.paranthropus.unk7E = false;
    g_CurrentEntity->step = step;
}
