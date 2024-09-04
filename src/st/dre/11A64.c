REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
#include "sfx.h"
REDACTED
// puts garbled hp max up text on screen
void EntityUnkId11(Entity* entity) {
    ObjInit* obj = (ObjInit*)&D_80180528[entity->params * 10];
REDACTED
REDACTED
        InitializeEntity(g_eInitGeneric2);
        entity->animSet = obj->animSet;
REDACTED
        entity->unk5A = obj->unk5A;
REDACTED
        entity->drawFlags = obj->drawFlags;
        entity->drawMode = obj->drawMode;
REDACTED
REDACTED
            entity->flags = obj->unkC;
REDACTED
REDACTED
REDACTED
            entity->rotY = 0x200;
            entity->rotX = 0x200;
REDACTED
REDACTED
REDACTED
    AnimateEntity(obj->unk10, entity);
REDACTED

REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
    entity->unk6D[0] = 0;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            if (g_Tilemap.x != 0) {
                return;
            }
            break;
REDACTED
        case 6:
            if (g_pads->pressed & PAD_TRIANGLE) {
                g_Tilemap.x = 0;
                g_Tilemap.width = 1280;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            ret = GetSideToPlayer();
REDACTED
            if (phi_v1 != 0) {
REDACTED
            } else {
REDACTED
            }
REDACTED
REDACTED
REDACTED
            g_Tilemap.x = *(temp_v0_2++);
            g_Tilemap.y = *(temp_v0_2++);
            g_Tilemap.width = *(temp_v0_2++);
            g_Tilemap.height = *(temp_v0_2++);
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            entity->hitboxHeight = 16;
        } else {
            entity->hitboxWidth = 16;
REDACTED
REDACTED
REDACTED
REDACTED

extern u16 g_eBreakableInit[];
extern u8* g_eBreakableAnimations[];
extern u8 g_eBreakableHitboxes[];
extern u8 g_eBreakableExplosionTypes[];
extern u16 g_eBreakableanimSets[];
extern u8 g_eBreakableDrawModes[];
void EntityBreakable(Entity* entity) {
REDACTED
REDACTED
REDACTED
REDACTED
        AnimateEntity(g_eBreakableAnimations[temp_s0], entity);
REDACTED
            g_api.PlaySfx(SFX_CANDLE_HIT);
            temp_v0 = AllocEntity(&g_Entities[224], &g_Entities[256]);
REDACTED
                CreateEntityFromCurrentEntity(2, temp_v0);
REDACTED
REDACTED
            ReplaceBreakableWithItemDrop(entity);
REDACTED
REDACTED
        InitializeEntity(g_eBreakableInit);
        entity->zPriority = g_unkGraphicsStruct.g_zEntityCenter - 20;
        entity->drawMode = g_eBreakableDrawModes[temp_s0];
        entity->hitboxHeight = g_eBreakableHitboxes[temp_s0];
        entity->animSet = g_eBreakableanimSets[temp_s0];
REDACTED
REDACTED

// clouds in the background ID 0x18
REDACTED
REDACTED
REDACTED
REDACTED

REDACTED
REDACTED
        InitializeEntity(g_EInitGeneric);
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        prim = &g_PrimBuf[primIndex];
        self->primIndex = primIndex;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        prim->y0 = prim->y1 = 0x6E - g_Tilemap.scrollY.i.hi;
REDACTED
REDACTED
REDACTED
        prim->drawMode = DRAW_DEFAULT;
        LOW(prim->r1) = LOW(prim->r0);
        LOW(prim->r2) = LOW(prim->r0);
        LOW(prim->r3) = LOW(prim->r0);
REDACTED
        camX = -g_Tilemap.scrollX.i.hi;
        camY = 32 - g_Tilemap.scrollY.i.hi;
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
            prim->drawMode = DRAW_DEFAULT;
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
        if (g_pads[1].pressed & PAD_CIRCLE) {
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
