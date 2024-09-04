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
    s16 primIndex;
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
        self->drawMode = DRAW_TPAGE;
REDACTED
REDACTED
REDACTED
REDACTED
        self->hitboxOffY = -0x38;
        self->hitboxOffX = 0;
        self->hitboxState = 2;
REDACTED
        CreateEntityFromEntity(
            E_func_801C7884, self, &self[1]); // Create SubWeapon
REDACTED
REDACTED
REDACTED
REDACTED
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 2);
        if (primIndex == -1) {
REDACTED
REDACTED
REDACTED
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
REDACTED
        self->flags |= FLAG_HAS_PRIMS;
REDACTED
REDACTED
            prim->drawMode = DRAW_HIDE;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        if (!(g_Timer & 0xF)) {
REDACTED
REDACTED
                CreateEntityFromEntity(E_func_801C77B8, self, newEntity);
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
                    absRnd = abs(rnd);
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        if (self->hitFlags != 0) { // container got hit!
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        g_api.FreePrimitives(self->primIndex);
        self->flags &= ~FLAG_HAS_PRIMS;
        g_api.PlaySfx(SFX_MAGIC_GLASS_BREAK);
REDACTED
REDACTED
REDACTED
                CreateEntityFromEntity(E_func_801C7538, self, newEntity);
REDACTED
REDACTED
REDACTED
REDACTED
                newEntity->facingLeft = glassPieceTBL->facingLeft;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            newEntity = AllocEntity(
                &g_Entities[UNK_ENTITY_51], &g_Entities[UNK_ENTITY_100]);
REDACTED
                CreateEntityFromEntity(E_func_801C7654, self, newEntity);
REDACTED
REDACTED
REDACTED
REDACTED
                newEntity->rotZ = ratan2(rndPosY, rndPosX);
REDACTED
REDACTED
REDACTED
        PlaySfxPositional(SFX_GLASS_BREAK_E);
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
        InitializeEntity(D_80180CF4);
        entity->drawFlags = FLAG_DRAW_ROTZ;
REDACTED
REDACTED
        entity->velocityX = entity->ext.generic.unk84.S16.unk0 << 12;
        entity->velocityX += 0x8000 - (Random() << 8);
        entity->velocityY -= (Random() & 0x1F) << 12;
REDACTED
REDACTED
REDACTED
REDACTED
        entity->velocityY += FIX(0.125);
REDACTED
        if (entity->velocityX != 0) {
            if (entity->facingLeft == 0) {
                new_var = (u16)entity->rotZ - 16;
REDACTED
REDACTED
                var_v0 = entity->rotZ + 16;
REDACTED
        } else if (entity->facingLeft != 0) {
            var_v0 = entity->rotZ - 16;
REDACTED
            var_v0 = entity->rotZ + 16;
REDACTED
REDACTED
        entity->rotZ = var_v0;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
    Collider collider;
REDACTED
REDACTED
REDACTED
        InitializeEntity(g_InitializeEntityData0);
        entity->animSet = ANIMSET_DRA(2);
REDACTED
        entity->drawMode = 0x70;
        entity->velocityX = rcos(entity->rotZ) * 0x10;
        entity->velocityY = rsin(entity->rotZ) * 0x10;
REDACTED
REDACTED
REDACTED
        AnimateEntity(D_801825F0, entity);
REDACTED
        entity->velocityY += FIX(0.125);
REDACTED
        g_api.CheckCollision(
            entity->posX.i.hi, entity->posY.i.hi + 8, &collider.effects, 0);
REDACTED
        if (collider.effects & EFFECT_SOLID) {
            entity->drawFlags = FLAG_DRAW_ROTY;
            entity->rotY = 0x100;
            entity->velocityY = FIX(0.25);
            entity->velocityX *= 8;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        entity->rotY -= 8;
        if (!(entity->rotY << 0x10)) {
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
        InitializeEntity(D_80180CF4);
        entity->drawFlags = FLAG_DRAW_ROTX | FLAG_DRAW_ROTY;
        entity->rotY = 0x100;
        entity->rotX = 0x100;
        entity->velocityX = 0;
REDACTED
        entity->velocityY = D_80182600[entity->params];
REDACTED
REDACTED
REDACTED
REDACTED
        temp_v1_2 = entity->rotY - 8;
        entity->velocityY -= 0x400;
        entity->rotY = temp_v1_2;
        entity->rotX = temp_v1_2;
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
        InitializeEntity(g_InitializeData0);
        entity->hitboxState = 0;
REDACTED
REDACTED
REDACTED
        AnimateEntity(g_SubweaponAnimPrizeDrop[params], entity);
REDACTED
        entity->velocityY = rsin(entity->rotZ) * 2;
        entity->rotZ += 0x20;
REDACTED
REDACTED
            entity->entityId = E_PRIZE_DROP;
            entity->pfnUpdate = EntityPrizeDrop;
            entity->animFrameDuration = 0;
            entity->animFrameIdx = 0;
REDACTED
            entity->hitboxState = 1;
REDACTED
REDACTED
}
