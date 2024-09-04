REDACTED
#include "sfx.h"
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
    if ((self->flags & FLAG_DEAD) && (self->step < 4)) {
        PlaySfxPositional(SFX_EXPLODE_SMALL);
        self->hitboxState = 0;
REDACTED
        newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
REDACTED
            CreateEntityFromEntity(E_WARG_EXP_OPAQUE, self, newEntity);
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
REDACTED
        self->hitboxOffY = 0x10;
REDACTED
REDACTED
        if (g_Timer & 1) {
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        if (UnkCollisionFunc3(&D_80183CAC) & 1) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            self->hitboxOffY -= 2;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        temp_a0 = UnkCollisionFunc2(&D_80183CBC);
        if (self->facingLeft != 0) {
            self->velocityX = FIX(0.5);
REDACTED
            self->velocityX = FIX(-0.5);
REDACTED
REDACTED
REDACTED
            self->hitboxState = 0;
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
REDACTED
/*
 * An invisible entity that is responsible for spawning the "floor
 * zombies" that come up from the ground and swarm the player.
 * Every 32 to 95 frames, it will alternate spawning a zombie
 * on the right side or left side of the screen.
 * The exact position a zombie is spawned in is also randomized.
 */
void EntityZombieSpawner(Entity* self) {
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        self->ext.zombieSpawner.spawnDelay = 1;
        self->flags &= FLAG_UNK_2000;
REDACTED
REDACTED
    if (g_CastleFlags[0x37]) {
REDACTED
        if (--self->ext.zombieSpawner.spawnDelay == 0) {
            newEntity = AllocEntity(g_Entities + 160, g_Entities + 168);
REDACTED
                CreateEntityFromEntity(E_ZOMBIE, self, newEntity);
REDACTED
REDACTED
                if (self->ext.zombieSpawner.spawnSide != 0) {
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
                self->ext.zombieSpawner.spawnSide ^= 1;
REDACTED
                // Zombies are prevented from spawning too close to the
                // edges of the room.
                distCameraEntity =
                    g_Tilemap.scrollX.i.hi + newEntity->posX.i.hi;
                if ((distCameraEntity < (g_Tilemap.x + 128)) ||
                    ((g_Tilemap.width - 128) < distCameraEntity)) {
REDACTED
REDACTED
REDACTED
            self->ext.zombieSpawner.spawnDelay = (Random() & 0x3F) + 32;
REDACTED
REDACTED
REDACTED
