void DestroyServantEntity(Entity* self)
{
    switch (self->params) {
    case 15:
        IsServantDestroyed = 1;
        break;
    }
    DestroyEntity(self);
}