#include "../wrp/wrp.h"

INCLUDE_ASM("st/wrp_psp/psp/wrp_psp/e_misc", EntityRelicOrb);

void EntityHeartDrop(Entity* self) {
    u16 index;
    u8 value;
    PfnEntityUpdate update;

    if (!self->step) {
        index = self->ext.heartDrop.unkB4 = self->params + 0x118;
        value = g_CastleFlags[(index >> 3) + 0x100] >> (index & 7);
        if (value & 1) {
            DestroyEntity(self);
            return;
        }

        index -= 0x118;
        index = ((u16*)D_80180608)[index];
        if (index < 128) {
            self->ext.heartDrop.update = EntityPrizeDrop;
        } else {
            self->ext.heartDrop.update = EntityEquipItemDrop;
            index -= 128;
        }
        self->params = index + 0x8000;
    } else {
        index = self->ext.heartDrop.unkB4;
        if (self->step < 5) {
            if (self->hitFlags) {
                g_CastleFlags[(index >> 3) + 0x100] |= 1 << (index & 7);
                self->step = 5;
            }
        }
    }
    update = self->ext.heartDrop.update;
    update(self);
}

INCLUDE_ASM("st/wrp_psp/psp/wrp_psp/e_misc", EntityMessageBox);

extern u16 D_8018047C[];
void func_8018F510(Entity* entity) {
    switch (entity->step) {
    case 0:
        InitializeEntity(D_8018047C);
        entity->ext.generic.unk8C.modeU16.unk0 =
            entity->ext.generic.unk80.entityPtr->entityId;
    case 1:
        if (entity->ext.generic.unk7C.U8.unk0++ > 4) {
            Entity* newEntity =
                (Entity*)AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(E_EXPLOSION, entity, newEntity);
                newEntity->entityId = E_EXPLOSION;
                newEntity->pfnUpdate = EntityExplosion;
                newEntity->params = entity->params;
            }
            entity->ext.generic.unk7C.U8.unk0 = 0;
        }
        entity->posX.i.hi = entity->ext.generic.unk80.entityPtr->posX.i.hi;
        entity->posY.i.hi = entity->ext.generic.unk80.entityPtr->posY.i.hi;
        if (entity->ext.generic.unk80.entityPtr->entityId !=
            entity->ext.generic.unk8C.modeU16.unk0) {
            DestroyEntity(entity);
        }
        break;
    }
}

extern s32 D_80181020[];
extern u8 D_80181038[];
extern u16 D_8018103C[];

void func_8018F838(Entity* self) {
    if (!self->step) {
        self->velocityY = D_80181020[self->ext.generic.unk94];
        self->flags = FLAG_UNK_2000 | FLAG_UNK_04000000 | FLAG_UNK_08000000;
        self->palette = PAL_OVL(0x195);
        self->animSet = ANIMSET_DRA(2);
        self->animCurFrame = D_80181038[self->params];
        self->drawMode = DRAW_TPAGE;
        self->step++;
    } else {
        self->posY.val -= self->velocityY;
        ++self->animFrameDuration;
        if (!(self->animFrameDuration % 2)) {
            self->animCurFrame++;
        }

        if (self->animFrameDuration > D_8018103C[self->params]) {
            DestroyEntity(self);
        }
    }
}

INCLUDE_ASM("st/wrp_psp/psp/wrp_psp/e_misc", EntityUnkId15);

extern u16 D_80180458[];
void EntityIntenseExplosion(Entity* self) {
    if (!self->step) {
        InitializeEntity(D_80180458);
        self->palette = PAL_OVL(0x170);
        self->animSet = ANIMSET_DRA(5);
        self->animCurFrame = 1;
        self->drawMode = 0x30;
        if (self->params & 0xF0) {
            self->palette = PAL_OVL(0x195);
            self->drawMode = DRAW_TPAGE;
        }

        if (self->params & 0xFF00) {
            self->zPriority = (self->params & 0xFF00) >> 8;
        }
        self->zPriority += 8;
    } else {
        self->animFrameDuration++;
        self->posY.val -= FIX(0.25);
        if ((self->animFrameDuration % 2) == 0) {
            self->animCurFrame++;
        }

        if (self->animFrameDuration > 36) {
            DestroyEntity(self);
        }
    }
}

void func_801916C4(s16 sfxId) {
    s32 posX;
    s32 posY;
    s16 arg2;
    s16 arg1;

    posX = g_CurrentEntity->posX.i.hi - 128;
    arg2 = (abs(posX) - 32) >> 5;
    if (arg2 > 8) {
        arg2 = 8;
    } else if (arg2 < 0) {
        arg2 = 0;
    }
    if (posX < 0) {
        arg2 = -arg2;
    }
    arg1 = abs(posX) - 96;
    posY = abs(g_CurrentEntity->posY.i.hi - 128) - 112;
    if (posY > 0) {
        arg1 += posY;
    }
    if (arg1 < 0) {
        arg1 = 0;
    }
    arg1 = 127 - (arg1 >> 1);
    if (arg1 > 0) {
        g_api.func_80134714(sfxId, arg1, arg2);
    }
}
