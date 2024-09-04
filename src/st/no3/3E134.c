REDACTED
REDACTED
REDACTED
REDACTED
    Tilemap* tilemap = &g_Tilemap;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        InitializeEntity(g_eInitGeneric2);
        entity->animSet = ANIMSET_OVL(1);
REDACTED
REDACTED
            entity->drawFlags =
                FLAG_DRAW_ROTX | FLAG_DRAW_ROTY | FLAG_DRAW_UNK8;
            entity->rotX = 0x180;
            entity->rotY = 0x180;
REDACTED
REDACTED
REDACTED
REDACTED
            entity->drawFlags = FLAG_DRAW_UNK8;
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
            g_api.PlaySfx(SE_TREE_BRANCH);
REDACTED
REDACTED
REDACTED
REDACTED
                entity->velocityX = FIX(8);
                entity->velocityY = FIX(3);
REDACTED
REDACTED
            entity->velocityX = FIX(10);
            entity->velocityY = FIX(1.625);
REDACTED
                newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
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
            animFlag = AnimateEntity(D_801819DC, entity);
            entity->velocityY -= 0xA00;
REDACTED
            animFlag = AnimateEntity(D_801819D0, entity);
            if (entity->velocityY > (s32)0xFFFE0000) {
                entity->velocityY -= FIX(0.03125);
REDACTED
REDACTED
REDACTED
        if ((entity->params == 0) && (tilemap->scrollX.i.hi > 0xD80)) {
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
        if (entity->velocityY > (s32)0xFFFE0000) {
            entity->velocityY -= FIX(0.03125);
REDACTED
        animFlag = AnimateEntity(D_801819D0, entity);
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
        PlaySfxPositional(SE_OWL_WING_FLAP);
REDACTED
REDACTED
REDACTED
// a single leaf from when the owl comes out in the intro
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        InitializeEntity(g_eInitGeneric2);
        entity->animSet = ANIMSET_OVL(1);
REDACTED
REDACTED
        entity->velocityX = D_801819E8[entity->params * 2];
        entity->velocityY = D_801819EC[entity->params * 2];
REDACTED
REDACTED
REDACTED
REDACTED
        if (entity->velocityX > 0) {
            entity->velocityX -= FIX(0.0625);
REDACTED
        if (entity->velocityY < FIX(1.0)) {
            entity->velocityY += 0x400;
REDACTED
        if (entity->velocityY > FIX(1.0)) {
            entity->velocityY -= 0x400;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
