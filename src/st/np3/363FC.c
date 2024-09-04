REDACTED
REDACTED
// Make a EntityWargExplosionPuffOpaque
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            // Make a EntityWargExplosionPuffOpaque
            CreateEntityFromEntity(E_WARG_EXP_OPAQUE, g_CurrentEntity, entity);
            entity->params = 2;
            entity->ext.wargpuff.unk89 = 6 - i;
            entity->ext.wargpuff.unk84 = temp_s3;
            entity->ext.wargpuff.unk88 = temp_s4;
        }
    }
}

REDACTED
    Unkstruct_80180FE0* obj;
    s32 velocityX;
    s32 velocityY;
    s32 params;
    s32 temp_s0;
    s32 adjVelocityX;
    s32 adjVelocityY;
    u32 temp_v0;
    s32 rnd;

    switch (self->step) {
    case 0:
        InitializeEntity(g_InitializeEntityData0);
        params = self->params & 0xF;
REDACTED
REDACTED
        self->drawMode = obj->drawMode;
REDACTED
REDACTED
        self->ext.wargpuff.unk80 = obj->unk8;
        self->step = params + 1;

        temp_v0 = self->params & 0xFF00;
        if (temp_v0 != 0) {
            self->zPriority = temp_v0 >> 8;
        }

        if (self->params & 0xF0) {
            self->palette = 0x819F;
            self->drawMode = DRAW_TPAGE;
            self->facingLeft = 1;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        if (AnimateEntity((u8*)self->ext.wargpuff.unk80, self) == 0) {
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        if (AnimateEntity((u8*)self->ext.wargpuff.unk80, self) != 0) {
REDACTED
REDACTED
                self->drawFlags = FLAG_DRAW_UNK8;
                self->unk6C = 0x80;
                self->step_s++;
                break;

            case 1:
                if (self->animFrameIdx == 5) {
                    self->step_s++;
                }
                break;

            case 2:
                self->unk6C += 0xFC;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            self->drawFlags |= 4;
            switch (self->ext.wargpuff.unk88) {
REDACTED
                if (self->ext.wargpuff.unk89 >= 0x4) {
                    self->ext.wargpuff.unk89 += 0xFD;
                    self->ext.wargpuff.unk84 -= 0x800;
REDACTED
REDACTED
REDACTED
REDACTED
                self->ext.wargpuff.unk84 =
                    (u16)self->ext.wargpuff.unk84 +
                    ((u8)self->ext.wargpuff.unk89 * 0xC0);
REDACTED
REDACTED
            self->ext.wargpuff.unk84 = self->ext.wargpuff.unk84 & 0xFFF;
            self->rotZ = self->ext.wargpuff.unk84 & 0xFFF;
            temp_s0 = self->ext.wargpuff.unk89 * 0x140;
REDACTED
            self->velocityX = temp_s0 * rsin(self->ext.wargpuff.unk84);
            self->velocityY = -(temp_s0 * rcos(self->ext.wargpuff.unk84));
            self->step_s++;
        }

        if (self->animFrameIdx >= 13) {
            velocityX = self->velocityX;
            if (velocityX < 0) {
                adjVelocityX = velocityX + 3;
            } else {
                adjVelocityX = velocityX;
            }
            self->velocityX = velocityX - (adjVelocityX >> 2);

            velocityY = self->velocityY;
            if (velocityY < 0) {
                adjVelocityY = velocityY + 3;
            } else {
                adjVelocityY = velocityY;
            }
            self->velocityY = velocityY - (adjVelocityY >> 2);
        }
        MoveEntity();
        if (AnimateEntity((u8*)self->ext.wargpuff.unk80, self) == 0) {
REDACTED
REDACTED
REDACTED
REDACTED
    case 4:
        if (self->step_s == 0) {
            rnd = Random();
            self->velocityY = FIX(-0.75);
            self->facingLeft = rnd & 1;
            self->rotX = 0xC0;
            self->drawFlags |= 1;
REDACTED
REDACTED
REDACTED
        if (AnimateEntity((u8*)self->ext.wargpuff.unk80, self) == 0) {
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
