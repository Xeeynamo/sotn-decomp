extern s32 unk14_yVel[];
extern u8 unk14_startFrame[];
extern u16 unk14_lifetime[];

// Appears to be related to some sort of explosion or puff of smoke.
// ID is 0x14.
void EntityUnkId14(Entity* entity) {
    if (entity->step == 0) {
        entity->velocityY = unk14_yVel[entity->ext.generic.unk94];
        entity->flags = FLAG_UNK_2000 | FLAG_UNK_04000000 | FLAG_UNK_08000000;
        entity->palette = 0x8195;
        entity->animSet = ANIMSET_DRA(2);
        entity->animCurFrame = unk14_startFrame[entity->params];
        entity->drawMode = DRAW_TPAGE;
        entity->step++;
    } else {
        entity->animFrameDuration++;
        entity->posY.val -= entity->velocityY;

        if (!(entity->animFrameDuration & 1)) {
            entity->animCurFrame++;
        }
        // Once the entity has outlived its lifetime, destroy it
        if (entity->animFrameDuration > unk14_lifetime[entity->params]) {
            DestroyEntity(entity);
        }
    }
}