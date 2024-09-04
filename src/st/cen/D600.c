REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
#include "game.h"
#include "sfx.h"

// background block of rock
void EntityBackgroundBlock(Entity* self) {
    ObjInit* obj = &D_80180490[self->params].animSet;

    if (self->step == 0) {
        InitializeEntity(g_eInitGeneric2);
        self->animSet = obj->animSet;
        self->zPriority = obj->zPriority;
        self->unk5A = obj->unk5A;
        self->palette = obj->palette;
        self->drawFlags = obj->drawFlags;
        self->drawMode = obj->drawMode;

        if (obj->unkC != 0) {
            self->flags = obj->unkC;
        }

REDACTED
            self->rotY = 0x200;
            self->rotX = 0x200;
        }
    }
    AnimateEntity(obj->unk10, self);
}

extern u16 g_EntityUnkId12TilemapProps[];
extern u16 g_EntityUnkId12Init[];
extern u8 g_EntityUnkId12Data[];
extern u8 g_EntityUnkId12Hitbox[];

#include "../entity_unk_id12.h"
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
        self->drawMode = D_801805B4[params];
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
    AnimateEntity(D_80180574[params], self);
REDACTED
REDACTED
        g_api.PlaySfx(SFX_CANDLE_HIT);
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
        ReplaceBreakableWithItemDrop(self);
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
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        self->drawFlags = FLAG_DRAW_ROTZ;
REDACTED
        facing = GetSideToPlayer() & 1;
REDACTED
REDACTED
REDACTED
        if (self->facingLeft != 0) {
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            self->velocityX = FIX(-1);
REDACTED
            self->velocityX = FIX(1);
REDACTED
REDACTED
REDACTED
REDACTED
        self->velocityX = self->velocityX + temp3 - temp2;
        self->velocityY = FIX(-3);
        self->velocityY = (self->params >> 1) * 0x6000 - 0x30000;
REDACTED
            self->velocityX = 0;
            self->velocityY = 0;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            primIndex = g_api.AllocPrimitives(PRIM_GT4, 2);
            if (primIndex != -1) {
REDACTED
                self->primIndex = primIndex;
                self->flags |= FLAG_HAS_PRIMS;
                UnkPolyFunc2(prim);
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
                prim->drawMode = 0x37;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        self->rotZ += self->ext.generic.unk80.modeS16.unk0;
        self->velocityY += FIX(0.25);
        g_api.CheckCollision(
            self->posX.i.hi, self->posY.i.hi + 6, &collider, 0);
REDACTED
REDACTED
            self->velocityY = -self->velocityY / 2;
            self->velocityX -= self->velocityX / 3;
            if (self->velocityY > FIX(-0.625)) {
                newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
REDACTED
                    CreateEntityFromEntity(
                        E_INTENSE_EXPLOSION, self, newEntity);
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            UnkPrimHelper(prim);
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
