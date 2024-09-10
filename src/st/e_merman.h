// SPDX-License-Identifier: AGPL-3.0-or-later
/*
 * Entity: Merman
 * Stages: NO3, NP3
 */

typedef enum {
    MERMAN_INIT,
    MERMAN_SWIMMING_UP,
    MERMAN_SWIMMING = 3,
    MERMAN_JUMPING,
    MERMAN_WALKING_TOWARDS_PLAYER,
    MERMAN_SPIT_FIRE,
    MERMAN_LUNGE,
    MERMAN_FALLING,
    MERMAN_DYING,
} MermanSteps;

typedef enum {
    MERMAN_JUMPING_SETUP,
    MERMAN_JUMPING_UNDERWATER,
    MERMAN_JUMPING_IN_AIR,
    MERMAN_JUMPING_LANDING,
} MermanJumpingSubSteps;

typedef enum {
    MERMAN_WALKING_TOWARDS_START,
    MERMAN_WALKING_TOWARDS_PLAYER_WALKING,
} MermanWalkingTowardsPlayerSubSteps;

typedef enum {
    MERMAN_SPIT_FIRE_FACE_PLAYER,
    MERMAN_SPIT_FIRE_ATTACK,
} MermanSpitFireSubSteps;

typedef enum {
    MERMAN_LUNGE_START,
    MERMAN_LUNGE_SETUP,
    MERMAN_LUNGE_TOWARDS_PLAYER,
    MERMAN_LUNGE_STANDING,
} MermanLungeSubSteps;

typedef enum {
    MERMAN_DYING_SETUP,
    MERMAN_DYING_KNOCKEDBACK,
    MERMAN_DYING_END,
} MermanDyingSubSteps;