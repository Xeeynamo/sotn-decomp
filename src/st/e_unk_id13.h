// SPDX-License-Identifier: AGPL-3.0-or-later

// EntityParticleTrail as a possible name here?
// params: The E_EXPLOSION params to use for the trail
void EntityUnkId13(Entity* self) {
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitUnkId13);
        self->ext.ent13.parentId = self->ext.ent13.parent->entityId;
    case 1:
        if (self->ext.ent13.fiveFrameCounter++ > 4) {
            Entity* newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(E_EXPLOSION, self, newEntity);
                newEntity->entityId = E_EXPLOSION;
                newEntity->pfnUpdate = EntityExplosion;
                newEntity->params = self->params;
            }
            self->ext.ent13.fiveFrameCounter = 0;
        }
        self->posX.i.hi = self->ext.ent13.parent->posX.i.hi;
        self->posY.i.hi = self->ext.ent13.parent->posY.i.hi;
        if (self->ext.ent13.parent->entityId != self->ext.ent13.parentId) {
            DestroyEntity(self);
        }
        break;
    }
}
