// SPDX-License-Identifier: AGPL-3.0-or-later

extern EInit g_EInitParticle;

void EntityBreakableWallDebris(Entity* self) {
    Collider col;
    Entity* entity;
    s32 posX;
    s32 posY;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitParticle);
        self->drawFlags = ENTITY_ROTATE;
        self->animSet = ANIMSET_OVL(1);
        self->palette = PAL_FLAG(0xB);
        if (Random() & 1) {
            self->animCurFrame = 0x26;
        } else {
            self->animCurFrame = 0x27;
        }
        if (self->velocityX < 0) {
            self->facingLeft = 1;
        }
        /* fall through */

    case 1:
        MoveEntity();
        self->rotate += 0x20;
        if (self->params) {
            self->rotate += 0x20;
        }
        self->velocityY += FIX(0.125);

        posX = self->posX.i.hi;
        posY = self->posY.i.hi + 6;
        g_api.CheckCollision(posX, posY, &col, 0);
        if (col.effects & EFFECT_SOLID) {
            self->posY.i.hi += col.unk18;
            if (self->velocityY < FIX(1)) {
                entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (entity != NULL) {
                    CreateEntityFromEntity(E_INTENSE_EXPLOSION, self, entity);
                    entity->params = 0x10;
                }
                DestroyEntity(self);
                return;
            }
            self->velocityY = -self->velocityY / 2;
        }
        break;
    }
}
