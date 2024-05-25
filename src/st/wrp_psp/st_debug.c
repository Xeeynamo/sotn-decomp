#include <game.h>

extern ObjInit2 D_801804E0[];
extern u16 g_eInitGeneric2[];

void func_80186FD0(Entity* self) {
    ObjInit2* objInit = &D_801804E0[self->params];
    if (!self->step) {
        InitializeEntity(g_eInitGeneric2);
        self->animSet = objInit->animSet;
        self->zPriority = objInit->zPriority;
        self->unk5A = objInit->unk4.u;
        self->palette = objInit->palette;
        self->drawFlags = objInit->drawFlags;
        self->drawMode = objInit->drawMode;

        if (objInit->unkC) {
            self->flags = objInit->unkC;
        }

        if (self->params == 1) {
            self->rotX = self->rotY = 0x0200;
        }
    }

    AnimateEntity(objInit->unk10, self);
}

u16 D_80180488[];
u8 D_80180528[];
u8 D_80180530[];
u16 D_80180538[];

void func_801870B0(Entity* entity) {
    u16 var_s0;
    u16 params;
    u16* tilemapProps;

    entity->unk6D[0] = 0;
    params = entity->params;
    if (entity->step) {
        switch (params) {
        case 4:
        case 5:
            if (g_Tilemap.x) {
                return;
            }
            break;
        case 6:
            if (g_pads->pressed & PAD_TRIANGLE) {
                g_Tilemap.x = 0;
                g_Tilemap.width = 1280;
                entity->step++;
                return;
            }
            break;
        }

        if (entity->unk44) {
            var_s0 = GetSideToPlayer();
            if (entity->ext.generic.unk7C.u) {
                var_s0 &= 2;
                var_s0 *= 2;
            } else {
                var_s0 &= 1;
                var_s0 *= 4;
            }
            params = (params << 3) + var_s0;
            tilemapProps = &D_80180538[params];
            g_Tilemap.x = *tilemapProps++;
            g_Tilemap.y = *tilemapProps++;
            g_Tilemap.width = *tilemapProps++;
            g_Tilemap.height = *tilemapProps;
        }
    } else {
        InitializeEntity(D_80180488);
        var_s0 = entity->ext.generic.unk7C.u = D_80180530[params];
        if (var_s0) {
            entity->hitboxWidth = D_80180528[params];
            entity->hitboxHeight = 16;
        } else {
            entity->hitboxWidth = 16;
            entity->hitboxHeight = D_80180528[params];
        }
    }
}
