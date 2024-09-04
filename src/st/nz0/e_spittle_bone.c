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
    if ((self->flags & FLAG_DEAD) && (self->step < 3)) {
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        self->drawFlags = FLAG_DRAW_ROTZ;
        self->rotZ = 0;
        self->flags &= ~(FLAG_UNK_2000 | 0x200);
        self->facingLeft = self->params;
REDACTED
REDACTED
REDACTED
        if (UnkCollisionFunc3(&D_801824CC) & 1) {
REDACTED
REDACTED
REDACTED
            newEntity->facingLeft = self->facingLeft;
REDACTED
            if (self->facingLeft != 0) {
                self->velocityX = FIX(1);
REDACTED
REDACTED
                self->velocityX = FIX(-1);
REDACTED
REDACTED
            newEntity->velocityX = self->velocityX;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        AnimateEntity(D_80182524, self);
REDACTED
            UnkCollisionFunc4(self->ext.spittleBone.unk7C);
REDACTED
            self->rotZ += self->ext.spittleBone.unk80;
REDACTED
REDACTED
                self->rotZ = self[1].rotZ;
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
        self->hitboxOffX = (u32)rsin(self->rotZ) >> 8;
        self->hitboxOffY = -(rcos(self->rotZ) * 16) >> 0xC;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
                MakeEntityFromId(E_SPITTLEBONE, self, newEntity);
                newEntity->facingLeft = self->facingLeft;
                newEntity->flags = FLAG_UNK_2000 | FLAG_UNK_08000000 |
                                   FLAG_DESTROY_IF_BARELY_OUT_OF_CAMERA |
                                   FLAG_DESTROY_IF_OUT_OF_CAMERA;
REDACTED
REDACTED
                newEntity->drawFlags |= 4;
                newEntity->rotZ = self->rotZ;
REDACTED
                newEntity->velocityX = D_80182504[i];
                newEntity->velocityY = 0xFFFD0000 - ((Random() & 3) << 0xF);
REDACTED
REDACTED
REDACTED
REDACTED
        newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
REDACTED
            CreateEntityFromEntity(E_EXPLOSION, self, newEntity);
REDACTED
            newEntity->posX.i.hi += -(rsin(self->rotZ) * 0x10) >> 0xC;
            newEntity->posY.i.hi += -(rcos(self->rotZ) * 0x10) >> 0xC;
REDACTED
        PlaySfxPositional(SFX_SKELETON_DEATH_C);
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        self->velocityY += FIX(0.15625);
REDACTED
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
    s16 rotZ;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        InitializeEntity(g_EInitGeneric);
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        temp4 = UnkCollisionFunc4(self->ext.spittleBone.unk7C);
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
                rotZ = D_801824E4[temp1];
REDACTED
                rotZ = D_801824DC[temp4 & 3];
REDACTED
REDACTED
            if (self->facingLeft != 0) {
                rotZ = -rotZ;
REDACTED
REDACTED
            self->rotZ = rotZ;
            rotZ -= prevEntity->rotZ;
REDACTED
            if (rotZ > 0x800) {
                rotZ -= 0x1000;
REDACTED
            if (rotZ < -0x800) {
                rotZ += 0x1000;
REDACTED
REDACTED
            temp3 = rotZ;
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
    s16 primIndex;
REDACTED
REDACTED
    s32 u0, v0, r0, b0, drawMode;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        self->rotX = 0;
        self->rotY = 0;
REDACTED
REDACTED
REDACTED
REDACTED
        if ((entity->rotZ & 0xFFF) == 0x800) {
            if (entity->facingLeft != 0) {
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            self->rotX += 16;
            self->rotY += 20;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        self->rotY = 0x140;
        self->rotX = 0x100;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        self->velocityY += FIX(0.0625);
REDACTED
        if (collider.effects != 0) {
            PlaySfxPositional(NA_SE_EN_SPITTLEBONE_ACID_SPLAT);
            EntityUnkId14Spawner(self, 1, 2, 0, 0, 5, 0);
REDACTED
            self->hitboxState = 0;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        primIndex = g_api.AllocPrimitives(PRIM_TILE, 9);
        if (primIndex == -1) {
REDACTED
REDACTED
REDACTED
        prim = &g_PrimBuf[primIndex];
        self->primIndex = primIndex;
REDACTED
        self->flags |= FLAG_HAS_PRIMS;
REDACTED
            for (u0 = 1, v0 = 2, r0 = 0x20, b0 = 0xc0, drawMode = 0x33, i = 0;
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
                prim->drawMode = drawMode;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        self->rotY -= 0x14;
        if (self->rotY < 0) {
            self->rotY = 0;
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
                g_api.CheckCollision(
                    prim->x0, (s16)(prim->y0 + 16), &collider, 0);
                if (collider.effects != 0) {
                    prim->drawMode = DRAW_HIDE;
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
