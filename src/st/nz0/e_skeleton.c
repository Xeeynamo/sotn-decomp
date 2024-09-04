REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
#include "sfx.h"
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
typedef enum {
    SKELETON_JUMPING,
    SKELETON_IN_AIR,
    SKELETON_LAND
} SkeletonJumpSubSteps;

static u8 anim_walk[] = {0x06, 0x01, 0x04, 0x02, 0x04, 0x03, 0x06,
                         0x04, 0x05, 0x05, 0x05, 0x06, 0x00};
static u8 anim_walk_backwards[] = {0x06, 0x01, 0x05, 0x06, 0x05, 0x05, 0x06,
                                   0x04, 0x04, 0x03, 0x04, 0x02, 0x00};
static u8 anim_throw_bone[] = {0x05, 0x07, 0x06, 0x08, 0x05, 0x09, 0x05,
                               0x0A, 0x05, 0x0B, 0x05, 0x0C, 0xFF, 0x00};
static u8 anim_jump1[] = {0x01, 0x01, 0x04, 0x0D, 0x04, 0x0E, 0x01, 0x01, 0x00};
static u8 anim_jump2[] = {
    0x01, 0x01, 0x04, 0x0D, 0x06, 0x0E, 0x04, 0x0D, 0x01, 0x01, 0x00};
static u16 anim_bone_rot[] = {0x0100, 0x0080, 0x0048, 0x0020, 0x0040, 0x0010};
static s8 dead_parts_selector[] = {0x30, 0x20, 0x14, 0x0C, 0x18, 0x10};
static s32 dead_parts_velocity_x[] = {
    FIX(.75), FIX(1.75), FIX(1.5), FIX(1), FIX(2), FIX(1.75)};
static s32 dead_parts_velocity_y[] = {
    FIX(-5), FIX(-3), FIX(-2), FIX(-3), FIX(-4), FIX(-.875)};
static u16 dead_parts_pos_x[] = {0 - 4, 0, 4, -4, -4, 4};
static u16 dead_parts_pos_y[] = {-16, -8, -4, -4, 9, 9};
static u8 attack_timer_cycles[2][4] = {
    {0x80, 0x08, 0x08, 0x40}, {0xF0, 0xC0, 0xA0, 0x80}};
static u32 bone_projectile_velocity_x[] = {
    FIX(-.125), FIX(-.5),  FIX(-1), FIX(-1.5),
    FIX(-2),    FIX(-2.5), FIX(-3), FIX(-3.5)};
static s16 sensors_ground[][2] = {{0, 19}, {0, 4}, {8, -4}, {-16, 0}};
static s16 sensors_special[] = {0, 19, 8, 0};
static s16 sensors_move[][2] = {{-12, 16}, {0, -16}, {0, -16}};

static void SkeletonAttackCheck(Entity* self) {
    if ((UnkCollisionFunc2(sensors_special) & 0x60) == 0x60) {
        self->posX.val -= self->velocityX;
REDACTED
REDACTED
    if (!(UnkCollisionFunc(sensors_move, LEN(sensors_move)) & 2)) {
        if ((--self->ext.skeleton.attackTimer) == 0) {
            SetStep(SKELETON_ATTACK);
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
    if (self->flags & FLAG_DEAD) {
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        self->ext.skeleton.attackTimer = 80; // Skeleton attack timer cycle
        self->ext.skeleton.facingLeft = 0;   // Facing init
        self->ext.skeleton.attackTimerIndex = 0;
REDACTED
REDACTED
        if (UnkCollisionFunc3(sensors_ground) != 0) {
REDACTED
REDACTED
REDACTED
REDACTED
        self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        self->ext.skeleton.facingLeft = self->facingLeft;
        AnimateEntity(anim_walk, self);
REDACTED
        if (self->ext.skeleton.facingLeft == 0) {
            self->velocityX = FIX(-0.5);
REDACTED
            self->velocityX = FIX(0.5);
REDACTED
REDACTED
        if (GetDistanceToPlayerX() < 76) {
REDACTED
REDACTED
        SkeletonAttackCheck(self);
REDACTED
REDACTED
        self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        self->ext.skeleton.facingLeft = self->facingLeft ^ 1;
        AnimateEntity(anim_walk_backwards, self);
REDACTED
        if (self->ext.skeleton.facingLeft == 0) {
            self->velocityX = FIX(-0.5);
REDACTED
            self->velocityX = FIX(0.5);
REDACTED
REDACTED
        if (GetDistanceToPlayerX() > 92) {
REDACTED
REDACTED
        SkeletonAttackCheck(self);
REDACTED
REDACTED
        animStatus = AnimateEntity(anim_throw_bone, self);
REDACTED
REDACTED
            self->ext.skeleton.attackTimerIndex++;
            self->ext.skeleton.attackTimer =
                attack_timer_cycles[self->params & 1]
                                   [self->ext.skeleton.attackTimerIndex & 3];
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
                newEntity = AllocEntity(g_Entities + 160, g_Entities + 192);
REDACTED
                    PlaySfxPositional(NA_SE_EN_SKELETON_THROW_BONE);
                    CreateEntityFromCurrentEntity(
                        E_SKELETON_THROWN_BONE, newEntity);
                    if (self->facingLeft) {
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
                    newEntity->facingLeft = self->facingLeft;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        case SKELETON_JUMPING:
            if (!(AnimateEntity(anim_jump1, self) & 1)) {
                u8 facing_ = self->ext.skeleton.facingLeft;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
                    self->velocityX = FIX(-2);
REDACTED
                    self->velocityX = FIX(2);
REDACTED
REDACTED
                self->velocityY = FIX(-3);
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        case SKELETON_IN_AIR:
            if (UnkCollisionFunc3(sensors_ground) != 0) {
REDACTED
REDACTED
            CheckFieldCollision(sensors_move, 2);
REDACTED
        case SKELETON_LAND:
            if (AnimateEntity(anim_jump2, self) & 1) {
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        PlaySfxPositional(SFX_SKELETON_DEATH_C);
REDACTED
REDACTED
REDACTED
                CreateEntityFromCurrentEntity(E_SKELETON_PIECES, newEntity);
                newEntity->facingLeft = self->facingLeft;
REDACTED
                newEntity->ext.skeleton.explosionTimer = dead_parts_selector[i];
                if (self->facingLeft) {
                    newEntity->posX.i.hi -= dead_parts_pos_x[i];
REDACTED
                    newEntity->posX.i.hi += dead_parts_pos_x[i];
REDACTED
                newEntity->posY.i.hi += dead_parts_pos_y[i];
                newEntity->velocityX = dead_parts_velocity_x[i];
                newEntity->velocityY = dead_parts_velocity_y[i];
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
void EntitySkeletonPieces(Entity* self) { // From skeleton death explosion
    if (self->step) {
        self->ext.skeleton.explosionTimer--;
        if (self->ext.skeleton.explosionTimer & 0xFF) {
            self->rotZ += anim_bone_rot[self->params];
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        self->entityId = E_EXPLOSION;
        self->pfnUpdate = (PfnEntityUpdate)EntityExplosion;
        self->params = 0;
        self->step = 0;
REDACTED
REDACTED
REDACTED
REDACTED
    self->drawFlags = FLAG_DRAW_ROTZ;
    self->animCurFrame = self->params + 15;
REDACTED
    if (self->facingLeft) {
        self->velocityX = -self->velocityX;
REDACTED
REDACTED
REDACTED
void EntitySkeletonThrownBone(Entity* self) { // Bone Projectile from Skeleton
    s32 velocityX;
REDACTED
REDACTED
    if (self->step) {
        if (self->flags & FLAG_DEAD) {
            EntityExplosionSpawn(0, 0);
REDACTED
REDACTED
REDACTED
        self->rotZ += 0x80;
        self->velocityY += 0x2400;
REDACTED
REDACTED
        if (self->posY.i.hi > 240) {
            DestroyEntity(self);
REDACTED
REDACTED
REDACTED
        self->posY.val -= FIX(0.0625);
        xDistanceToPlayer = GetDistanceToPlayerX();
REDACTED
        xDistanceToPlayer = MAX(xDistanceToPlayer, 7);
        velocityX = bone_projectile_velocity_x[xDistanceToPlayer];
        xDistanceToPlayer = self->facingLeft;
REDACTED
REDACTED
            velocityX = -velocityX;
REDACTED
REDACTED
        self->velocityY = FIX(-4.5);
        self->velocityX = velocityX;
        self->drawFlags = FLAG_DRAW_ROTZ;
REDACTED
REDACTED
REDACTED
// Unclear if this has a way to run. Not called, and not in
// the main entity list.
void func_801C6678(Entity* self) {
    if (self->step == 0) {
REDACTED
        self->rotX = 0x120;
        self->rotY = 0x200;
        self->unk6C = 0;
        self->hitboxState = 0;
        self->drawFlags = self->drawFlags | 0xB;
REDACTED
REDACTED
REDACTED
    self->facingLeft = self[-1].facingLeft;
    self->zPriority = self[-1].zPriority - 1;
    self->animCurFrame = self[-1].animCurFrame;
    self->posX.i.hi = self[-1].posX.i.hi;
    self->posY.i.hi = self[-1].posY.i.hi - 20;
REDACTED
    if (self[-1].entityId != E_SKELETON) {
        DestroyEntity(self);
REDACTED
}
