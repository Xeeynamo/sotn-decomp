REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
#include "sfx.h"
#include "../e_merman.h"
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
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
    if ((self->flags & FLAG_DEAD) && (self->step < MERMAN_DYING)) {
        PlaySfxPositional(0x71D);
        self->hitboxState = 0;
REDACTED
REDACTED
REDACTED
                CreateEntityFromEntity(E_EXPLOSION, self, newEntity);
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
REDACTED
        self->velocityY = FIX(-1);
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
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        if (!(collider.effects & EFFECT_WATER)) {
REDACTED
REDACTED
        break;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            self->velocityX = D_80182338[rnd].x;
            self->velocityY = D_80182338[rnd].y;
REDACTED
REDACTED
REDACTED
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
REDACTED
REDACTED
        camY = g_Tilemap.scrollY.i.hi;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        if (!(collider.effects & EFFECT_WATER)) {
            self->velocityY = FIX(0.5);
REDACTED
REDACTED
REDACTED
REDACTED
        posY += g_Tilemap.scrollY.i.hi;
REDACTED
            self->posY.i.hi = pos[4] - g_Tilemap.scrollY.i.hi - 24;
REDACTED
REDACTED
REDACTED
REDACTED
            if ((GetDistanceToPlayerX() >= 48) && !(Random() & 1)) {
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            self->velocityX = 0;
            self->velocityY = FIX(-8.5);
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            camY = g_Tilemap.scrollY.i.hi;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
                newEntity = AllocEntity(&g_Entities[232], &g_Entities[256]);
REDACTED
                    CreateEntityFromEntity(E_MERMAN_UNK0, self, newEntity);
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
                if (UnkCollisionFunc3(&D_8018235C) & 1) {
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
                self->velocityY += FIX(0.25);
REDACTED
REDACTED
REDACTED
            if (self->velocityY < 0) {
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
                newEntity = AllocEntity(&g_Entities[232], &g_Entities[256]);
REDACTED
                    CreateEntityFromEntity(E_MERMAN_UNK1, self, newEntity);
REDACTED
                    newEntity->velocityX = D_80182418[self->animFrameIdx];
REDACTED
REDACTED
                self->palette = PAL_DRA(0x2B2);
                if (self->velocityY > 0) {
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
REDACTED
REDACTED
REDACTED
REDACTED
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            if (self->facingLeft == 0) {
                self->velocityX = FIX(-0.375);
REDACTED
                self->velocityX = FIX(0.375);
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            colRet = UnkCollisionFunc2(&D_8018238C);
REDACTED
                self->facingLeft ^= 1;
REDACTED
            if (self->facingLeft == 0) {
                self->velocityX = FIX(-0.375);
REDACTED
                self->velocityX = FIX(0.375);
REDACTED
REDACTED
                self->posX.val += self->velocityX;
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
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            if (self->animFrameIdx == 4 && self->animFrameDuration == 0) {
                PlaySfxPositional(SFX_FIREBALL_SHOT_C);
REDACTED
REDACTED
                    CreateEntityFromEntity(E_MERMAN_UNK2, self, newEntity);
                    if (self->facingLeft != 0) {
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
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            if (self->facingLeft == 0) {
                self->velocityX = FIX(-5.0 / 2.0);
REDACTED
                self->velocityX = FIX(2.5);
REDACTED
REDACTED
            self->velocityY = FIX(-2);
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
            if (self->facingLeft != 0) {
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            if (collider.effects & EFFECT_SOLID) {
                self->velocityX = 0;
REDACTED
            UnkCollisionFunc5(&D_8018236C);
            if (self->facingLeft != 0) {
                self->velocityX -= FIX(0.03125);
REDACTED
                self->velocityX += FIX(0.03125);
REDACTED
REDACTED
REDACTED
                self->velocityX = 0;
                self->velocityY = FIX(2);
REDACTED
                UnkCollisionFunc3(&D_8018235C);
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
REDACTED
            UnkCollisionFunc3(&D_8018235C);
REDACTED
                self->velocityY = 0;
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
REDACTED
REDACTED
REDACTED
REDACTED
        self->velocityY += FIX(0.25);
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            self->ext.merman.palette = PAL_DRA(0x2BC);
            self->velocityY = 0;
REDACTED
REDACTED
REDACTED
            if (UnkCollisionFunc3(&D_8018237C) & 1) {
                if (!(GetSideToPlayer() & 1)) {
                    self->velocityX = FIX(-0.5);
REDACTED
                    self->velocityX = FIX(0.5);
REDACTED
REDACTED
REDACTED
            // fallthrough
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            if (!(g_Timer % 8)) {
REDACTED
                if (self->ext.merman.palette == PAL_DRA(0x2C0)) {
                    PlaySfxPositional(SFX_FM_EXPLODE_B);
REDACTED
REDACTED
                        CreateEntityFromEntity(E_MERMAN_UNK3, self, newEntity);
REDACTED
REDACTED
REDACTED
REDACTED
            if (self->ext.merman.palette >= PAL_DRA(0x2C5)) {
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
void EntityMermanFireball(Entity* self) {
REDACTED
REDACTED
REDACTED
        InitializeEntity(D_80180AD8);
REDACTED
REDACTED
REDACTED
REDACTED
        if (self->facingLeft != 0) {
            self->velocityX = FIX(1.5);
REDACTED
            self->velocityX = ~0x17FFF;
REDACTED
REDACTED
        self->drawFlags = FLAG_DRAW_ROTX | FLAG_DRAW_ROTY;
        self->rotY = self->rotX = 0x80;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            entity->drawFlags = FLAG_DRAW_ROTX | FLAG_DRAW_ROTY;
REDACTED
            entity->rotY = entity->rotX = 192;
REDACTED
REDACTED
        AnimateEntity(D_80182400, self);
REDACTED
REDACTED
        if (self->rotX < 0x100) {
            self->rotY = self->rotX += 8;
REDACTED
REDACTED
        if (self->flags & FLAG_DEAD) {
            entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
REDACTED
                CreateEntityFromEntity(E_EXPLOSION, self, entity);
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED

REDACTED
REDACTED
REDACTED
        InitializeEntity(D_80180ACC);
REDACTED
        self->hitboxState = 0;
REDACTED
        self->flags |= FLAG_UNK_2000;
REDACTED
REDACTED
    self->velocityY += FIX(0.15625);
    if (AnimateEntity(D_80182414, self) == 0) {
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        InitializeEntity(g_InitializeEntityData0);
REDACTED
        self->animSet = ANIMSET_DRA(2);
REDACTED
        self->velocityY = D_80182440[self->params];
REDACTED
REDACTED
REDACTED
REDACTED
        self->posY.val += self->velocityY;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
}
