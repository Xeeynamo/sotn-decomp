// SPDX-License-Identifier: AGPL-3.0-or-later
extern u16 g_InitDataEnt13[];

void EntityUnkId13(Entity* self) {
    switch (self->step) {
    case 0:
        InitializeEntity(g_InitDataEnt13);
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
        // We just follow the location of our parent
        self->posX.i.hi = self->ext.ent13.parent->posX.i.hi;
        self->posY.i.hi = self->ext.ent13.parent->posY.i.hi;
        // Tests if the parent's ID is different from what it was when we were
        // created. I suspect this is to check for the parent being destroyed.
        if (self->ext.ent13.parent->entityId != self->ext.ent13.parentId) {
            DestroyEntity(self);
        }
        break;
    }
}
