// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rlib.h"

extern EInit g_EInitBreakable;
extern AnimationFrame* g_RlibBreakableAnimations[];
extern u8 g_RlibBreakableHitboxHeights[];
extern u8 g_RlibBreakableExplosionTypes[];
extern u16 g_RlibBreakablePalettes[];
extern u16 g_RlibBreakableAnimSets[];
extern u8 g_RlibBreakableBlendModes[];
extern u16 g_RlibBreakableUnk5A[];
extern u16 g_RlibBreakableHitboxOffsetsY[];

#ifdef VERSION_PSP
extern s32 E_ID(UNK_1B);
extern s32 E_ID(UNK_28);
#endif

void EntityBreakable(Entity* self) {
    Entity* entity;
    u16 breakableType;

    breakableType = self->params >> 12;
    if (!self->step) {
        InitializeEntity(g_EInitBreakable);
        self->zPriority = g_unkGraphicsStruct.g_zEntityCenter - 20;
        if (breakableType < 5) {
            entity = self + 1;
            CreateEntityFromEntity(E_ID(UNK_1B), self, entity);
            entity->params = breakableType;
            entity->zPriority = self->zPriority;
        }
        self->blendMode = g_RlibBreakableBlendModes[breakableType];
        self->hitboxHeight = g_RlibBreakableHitboxHeights[breakableType];
        self->animSet = g_RlibBreakableAnimSets[breakableType];
        self->unk5A = g_RlibBreakableUnk5A[breakableType];
        self->palette = g_RlibBreakablePalettes[breakableType];
        self->hitboxOffY = g_RlibBreakableHitboxOffsetsY[breakableType];
    }
    AnimateEntity(g_RlibBreakableAnimations[breakableType], self);
    if (self->hitParams) {
        entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (entity != NULL) {
            CreateEntityFromCurrentEntity(E_EXPLOSION, entity);
            entity->params = g_RlibBreakableExplosionTypes[breakableType];
        }
        switch (breakableType) {
        case 2:
        case 3:
            PlaySfxPositional(SFX_GLASS_BREAK_E);
            break;
        case 9:
            entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (entity != NULL) {
                CreateEntityFromCurrentEntity(E_ID(UNK_28), entity);
                entity->params = 0x100;
            }
            g_api.PlaySfx(SFX_GLASS_BREAK_E);
            entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_PERSISTENT_ITEM_DROP, self, entity);
                entity->params = self->params & 0x1FF;
            }
            PreventEntityFromRespawning(self);
            DestroyEntity(self);
            return;
        case 7:
            g_api.PlaySfx(SFX_GLASS_BREAK_E);
            entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_PERSISTENT_ITEM_DROP, self, entity);
                entity->params = self->params & 0x1FF;
            }
            PreventEntityFromRespawning(self);
            DestroyEntity(self);
            return;
        case 8:
            g_api.PlaySfx(SFX_GLASS_BREAK_E);
            entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_PERSISTENT_ITEM_DROP, self, entity);
                entity->params = 3;
            }
            PreventEntityFromRespawning(self);
            DestroyEntity(self);
            return;
        default:
            g_api.PlaySfx(SFX_GLASS_BREAK_C);
            break;
        }
        ReplaceBreakableWithItemDrop(self);
    }
}

extern EInit g_EInitInteractable;
extern u8 D_us_80180824[];
extern u8 D_us_8018082C[];

void func_us_801AE7AC_from_lib(Entity* self) {
    Entity* breakable;

    if (!self->step) {
        InitializeEntity(g_EInitInteractable);
        self->blendMode = BLEND_TRANSP | BLEND_ADD;
        self->animSet = ANIMSET_OVL(2);
    }

    if (!self->params) {
        AnimateEntity(D_us_80180824, self);
    } else {
        AnimateEntity(D_us_8018082C, self);
    }

    breakable = self - 1;
    if (breakable->entityId != E_BREAKABLE) {
        if (!self->params) {
            self->animCurFrame = 0xD;
        } else {
            self->animCurFrame = 0xE;
        }
    }
}

INCLUDE_ASM("st/rlib/nonmatchings/unk_20AE8", func_us_801AE84C_from_lib);

INCLUDE_ASM("st/rlib/nonmatchings/unk_20AE8", func_us_801AF280_from_lib);

extern EInit g_EInitInteractable;
extern SVECTOR D_us_80180924;
extern SVECTOR D_us_8018092C;

void func_us_801AF538_from_lib(Entity* self) {
    s32 primIndex;
    s16 x;
#ifdef VERSION_PSP
    struct {
        MATRIX matrix;
        VECTOR trans;
        long screenX;
        long screenZ;
        long screenY;
    } geometry;
#else
    struct {
        s32 pad[2];
        VECTOR trans;
        MATRIX matrix;
        s32 screenX;
        s32 screenY;
        s32 screenZ;
    } geometry;
    MATRIX* matrixPtr;
#endif
    Primitive* prim;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        primIndex = g_api_AllocPrimitives(PRIM_GT4, 4);
        if (primIndex != -1) {
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            self->ext.prim = prim;

            while (prim != NULL) {
                prim->tpage = 0xF;
                prim->clut = 0x34;
                prim->u0 = prim->u2 = 0x80;
                prim->u1 = prim->u3 = 0xF8;
                prim->v0 = prim->v1 = 0;
                prim->v2 = prim->v3 = 0x1C;
                prim->priority = 0x50;
                prim->drawMode = DRAW_UNK02;
                prim = prim->next;
            }
        } else {
            DestroyEntity(self);
            return;
        }

    case 1:
        SetGeomScreen(0x400);
        SetGeomOffset(0x80, self->posY.i.hi);
#ifdef VERSION_PSP
        RotMatrix(&D_us_8018092C, &geometry.matrix);
        geometry.trans.vx = self->posX.i.hi - 0x80;
        geometry.trans.vy = 0;
        geometry.trans.vz = 0x400;
        TransMatrix(&geometry.matrix, &geometry.trans);
        SetRotMatrix(&geometry.matrix);
        SetTransMatrix(&geometry.matrix);
        RotTransPers(&D_us_80180924, &geometry.screenX, &geometry.screenY,
                     &geometry.screenZ);
        x = (s16)geometry.screenX;
#else
        matrixPtr = &geometry.matrix;
        RotMatrix(&D_us_8018092C, matrixPtr);
        geometry.trans.vx = self->posX.i.hi - 0x80;
        geometry.trans.vy = 0;
        geometry.trans.vz = 0x400;
        TransMatrix(matrixPtr, &geometry.trans);
        SetRotMatrix(matrixPtr);
        SetTransMatrix(matrixPtr);
        RotTransPers(&D_us_80180924, &geometry.screenX, &geometry.screenY,
                     &geometry.screenZ);
        x = (s16)geometry.screenX;
#endif
        if (x > 0) {
            while (x >= -0x3F) {
                x -= 0x78;
            }
        } else {
            while (x < -0x80) {
                x += 0x78;
            }
        }

        prim = self->ext.prim;
        while (prim != NULL) {
            prim->x0 = prim->x2 = x;
            x += 0x78;
            prim->x1 = prim->x3 = x;
            prim->y0 = prim->y1 = self->posY.i.hi + 0x1C;
            prim->y2 = prim->y3 = self->posY.i.hi;
            prim->drawMode = DRAW_UNK02;
            prim = prim->next;
            if (x >= 0x101) {
                break;
            }
        }

        while (prim != NULL) {
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
        return;

    default:
        return;
    }
}

extern EInit g_EInitInteractable;
extern SVECTOR D_us_80180934;
extern SVECTOR D_us_8018093C;

void func_us_801AF7B8_from_lib(Entity* self) {
    Primitive* prim;
    Primitive* last;
    s32 primIndex;
    s16 x;
#ifdef VERSION_PSP
    long sz;
    long flag;
    long sxy;
    VECTOR trans;
    MATRIX matrix;
#else
    struct {
        s32 pad[2];
        VECTOR value;
    } transStorage;
    MATRIX matrix;
    long sxy;
    long sz;
    long flag;
#endif

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        primIndex = g_api_func_800EDB58(0x11, 0xA);
        if (primIndex != -1) {
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            self->ext.et_801AF774.prim1 = prim;

            while (prim != NULL) {
                prim->u0 = 0x18;
                prim->v0 = 0x40;
                prim->r0 = prim->g0 = prim->b0 = 0;
                prim->priority = 0x60;
                prim->drawMode = DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;
                last = prim;
                prim = prim->next;
            }

            prim = last;
            self->ext.et_801AF774.prim2 = prim;
            prim->u0 = 0xFF;
            prim->v0 = 0x30;
            prim->x0 = 0;
            prim->y0 = self->posY.i.hi + 0x70;
            prim->r0 = prim->g0 = prim->b0 = 0;
            prim->priority = 0x60;
            prim->drawMode = DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;
        } else {
            DestroyEntity(self);
            return;
        }
        /* fall through */
    case 1:
        SetGeomScreen(0x400);
        SetGeomOffset(0x80, self->posY.i.hi);
        RotMatrix(&D_us_8018093C, &matrix);
#ifdef VERSION_PSP
        trans.vx = self->posX.i.hi - 0x80;
        trans.vy = 0;
        trans.vz = 0x400;
        TransMatrix(&matrix, &trans);
#else
        transStorage.value.vx = self->posX.i.hi - 0x80;
        transStorage.value.vy = 0;
        transStorage.value.vz = 0x400;
        TransMatrix(&matrix, &transStorage.value);
#endif
        SetRotMatrix(&matrix);
        SetTransMatrix(&matrix);
        RotTransPers(&D_us_80180934, &sxy, &sz, &flag);
        x = (s16)sxy;

        if (x > 0) {
            while (x >= -0x3F) {
                x -= 0x38;
            }
        } else {
            while (x < -0x80) {
                x += 0x38;
            }
        }

        prim = self->ext.et_801AF774.prim1;
        while (prim != NULL) {
            prim->x0 = x;
            x += 0x38;
            prim->y0 = self->posY.i.hi;
            prim->drawMode = DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;
            prim = prim->next;
            if (x >= 0x101) {
                break;
            }
        }

        while (prim != NULL) {
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }

        prim = self->ext.et_801AF774.prim2;
        prim->u0 = 0xFF;
        prim->v0 = 0x30;
        prim->x0 = 0;
        prim->y0 = self->posY.i.hi + 0x40;
        prim->r0 = prim->g0 = prim->b0 = 0;
        prim->priority = 0x60;
        prim->drawMode = DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;
    }
}

void func_us_801AFA80_from_lib(Entity* self) {
    extern u16 g_EInitInteractable[];
    extern Point16 D_us_801809CC[];
    extern SVECTOR D_us_80180944;
    extern SVECTOR D_us_801809DC;
    extern u8* D_us_801809BC[];

    long p, flag;
    u8 pad[4];
    long sxy;
    VECTOR trans;
    MATRIX m;
    Primitive* prim;
    s32 primIndex;
    s32 i, j;
    u8* ptr;
    s16 posX, posY;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        self->posX.i.hi =
            D_us_801809CC[self->params].x - g_Tilemap.scrollX.i.hi;
        self->posY.i.hi =
            D_us_801809CC[self->params].y - g_Tilemap.scrollY.i.hi;
        primIndex = g_api.func_800EDB58(PRIM_GT4, 0x10);
        if (primIndex != -1) {
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            self->ext.prim = prim;
            for (i = 0; prim != NULL; i++) {
                prim->tpage = 0xF;
                prim->clut = 0x2F;
                if (i % 2) {
                    prim->u0 = prim->u2 = 0x88;
                    prim->u1 = prim->u3 = 0xFE;
                } else {
                    prim->u0 = prim->u2 = 0xFE;
                    prim->u1 = prim->u3 = 0x88;
                }
                prim->v0 = prim->v1 = 0xFE;
                prim->v2 = prim->v3 = 0x80;
                prim->priority = 0x20;
                prim->drawMode = DRAW_UNK02;
                prim = prim->next;
            }
        } else {
            DestroyEntity(self);
            return;
        }
        g_GpuBuffers[0].draw.r0 = 0x40;
        g_GpuBuffers[0].draw.g0 = 0x38;
        g_GpuBuffers[0].draw.b0 = 0x28;
        g_GpuBuffers[1].draw.r0 = 0x40;
        g_GpuBuffers[1].draw.g0 = 0x38;
        g_GpuBuffers[1].draw.b0 = 0x28;

    case 1:
        SetGeomScreen(0x400);
        SetGeomOffset(0x80, 0x80);
        RotMatrix(&D_us_801809DC, &m);
        trans.vx = self->posX.i.hi - 0x80;
        trans.vy = self->posY.i.hi - 0x80;
        trans.vz = 0x400;
        TransMatrix(&m, &trans);
        SetRotMatrix(&m);
        SetTransMatrix(&m);
        RotTransPers(&D_us_80180944, &sxy, &p, &flag);
        posX = sxy & 0xFFFF;
        posY = sxy >> 0x10;
        prim = self->ext.prim;
        ptr = D_us_801809BC[self->params];
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 4; j++) {
                prim->drawMode = DRAW_DITHERING | DRAW_COLORS;
                prim->x0 = prim->x2 = posX + (j * 0x78) - 0xF0;
                if (prim->x0 > 0x100) {
                    prim->drawMode = DRAW_HIDE;
                }
                prim->x1 = prim->x3 = posX + (j * 0x78) - 0x78;
                if (prim->x1 < 0) {
                    prim->drawMode = DRAW_HIDE;
                }
                prim->y0 = prim->y1 = posY + (i * 0x80) - 0x100;
                if (prim->y0 > 0x100) {
                    prim->drawMode = DRAW_HIDE;
                }
                prim->y2 = prim->y3 = posY + (i * 0x80) - 0x80;
                if (prim->y2 < 0) {
                    prim->drawMode = DRAW_HIDE;
                }
                PGREY(prim, 0) = *(ptr + i * 5 + j + 0);
                PGREY(prim, 1) = *(ptr + i * 5 + j + 1);
                PGREY(prim, 2) = *(ptr + (i + 1) * 5 + j + 0);
                PGREY(prim, 3) = *(ptr + (i + 1) * 5 + j + 1);
                prim = prim->next;
            }
        }
    }
}

INCLUDE_ASM("st/rlib/nonmatchings/unk_20AE8", func_us_801AE8E8_from_lib);
