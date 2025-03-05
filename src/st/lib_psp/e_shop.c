// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../lib/lib.h"

typedef struct {
    /* 0x0 */ u16 category;
    /* 0x2 */ u16 itemId;
    /* 0x4 */ u32 price;
} ShopItem;

/// the first 5 inventory categories are the same as
/// `EquipKind`. `EQUIP_RELIC` and `EQUIP_DOCUMENT` are
/// special and only used for inventory so far.
typedef enum {
    INVENTORY_HAND,
    INVENTORY_HEAD,
    INVENTORY_BODY,
    INVENTORY_CAPE,
    INVENTORY_ACCESSORY,
    INVENTORY_RELIC,
    INVENTORY_DOCUMENT,
} InventoryCategory;

extern const char D_psp_092A4880[];
extern u16 D_us_801814D4[];
extern ShopItem D_us_801814D8[];
extern u16 D_us_80181510[];
extern u32 D_us_801D415C[];
extern u32 D_us_801D425C[];
extern ShopItem D_us_801D4364[];

void func_us_801B245C(Primitive* arg0, u16 arg1, u16 arg2, u16 arg3, u16 arg4,
                      s32 arg5, s32 arg6) {
    Primitive* prim;
    s16 i;
    s16 offset;

    prim = arg0;
    for (i = 0; i < 6; i++) {
        arg0 = arg0->next;
    }
    for (i = 0; i < 2; i++) {
        offset = (rsin(arg1) * arg3) / 0x1000;
        if (i) {
            arg0->x1 = arg0->x3 = arg0->x0 + offset;
            if (arg5 & 1) {
                arg0->r0 = arg0->r1 = (arg2 / 2) + 0x30;
            } else {
                arg0->r0 = arg0->r1 = 0;
            }
            if (arg5 & 2) {
                arg0->r2 = arg0->r3 = (arg2 / 2) + 0x30;
            } else {
                arg0->r2 = arg0->r3 = 0;
            }
            if (arg5 & 4) {
                arg0->g0 = arg0->g1 = (arg2 / 2) + 0x30;
            } else {
                arg0->g0 = arg0->g1 = 0;
            }
            if (arg5 & 8) {
                arg0->g2 = arg0->g3 = (arg2 / 2) + 0x30;
            } else {
                arg0->g2 = arg0->g3 = 0;
            }
            if (arg5 & 0x10) {
                arg0->b0 = arg0->b1 = (arg2 / 2) + 0x30;
            } else {
                arg0->b0 = arg0->b1 = 0;
            }
            if (arg5 & 0x20) {
                arg0->b2 = arg0->b3 = (arg2 / 2) + 0x30;
            } else {
                arg0->b2 = arg0->b3 = 0;
            }
        } else {
            arg0->x0 = arg0->x2 = arg0->x1 - offset;
            if (arg5 & 1) {
                arg0->r0 = arg0->r1 = arg2 + 0x20;
            } else {
                arg0->r0 = arg0->r1 = 0;
            }
            if (arg5 & 2) {
                arg0->r2 = arg0->r3 = arg2 + 0x20;
            } else {
                arg0->r2 = arg0->r3 = 0;
            }
            if (arg5 & 4) {
                arg0->g0 = arg0->g1 = arg2 + 0x20;
            } else {
                arg0->g0 = arg0->g1 = 0;
            }
            if (arg5 & 8) {
                arg0->g2 = arg0->g3 = arg2 + 0x20;
            } else {
                arg0->g2 = arg0->g3 = 0;
            }
            if (arg5 & 0x10) {
                arg0->b0 = arg0->b1 = arg2 + 0x20;
            } else {
                arg0->b0 = arg0->b1 = 0;
            }
            if (arg5 & 0x20) {
                arg0->b2 = arg0->b3 = arg2 + 0x20;
            } else {
                arg0->b2 = arg0->b3 = 0;
            }
        }
        offset = (arg4 * rcos(g_CurrentEntity->ext.et_801B6F30.unk7E)) / 0x1000;
        if (i) {
            arg0->y1 = arg0->y0 - offset;
            arg0->y3 = arg0->y2 + offset;
            prim->x0 = arg0->x1;
            prim->y0 = arg0->y1;
            prim->x1 = arg0->x3;
            prim->y1 = arg0->y3;
            prim->drawMode = DRAW_DEFAULT;
            prim = prim->next;
        } else {
            arg0->y0 = arg0->y1 - offset;
            arg0->y2 = arg0->y3 + offset;
            prim->x0 = arg0->x0;
            prim->y0 = arg0->y0;
            prim->x1 = arg0->x2;
            prim->y1 = arg0->y2;
            prim->drawMode = DRAW_DEFAULT;
            prim = prim->next;
        }
        prim->x0 = arg0->x0;
        prim->y0 = arg0->y0;
        prim->x1 = arg0->x1;
        prim->y1 = arg0->y1;
        prim->drawMode = DRAW_DEFAULT;
        prim = prim->next;

        prim->x0 = arg0->x2;
        prim->y0 = arg0->y2;
        prim->x1 = arg0->x3;
        prim->y1 = arg0->y3;
        prim->drawMode = DRAW_DEFAULT;
        prim = prim->next;

        if (arg6) {
            arg0->drawMode =
                DRAW_UNK_400 | DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
        } else {
            arg0->drawMode = DRAW_UNK_400 | DRAW_COLORS;
        }
        arg0 = arg0->next;
    }
    for (i = 0; i < 2; i++) {
        offset = (rsin(arg1) * (arg3 - 8)) / 0x1000;
        if (i) {
            arg0->x1 = arg0->x3 = arg0->x0 + offset;
        } else {
            arg0->x0 = arg0->x2 = arg0->x1 - offset;
        }
        offset = (arg4 * rcos(arg1) * 3) / 0x4000;
        if (i) {
            arg0->y1 = arg0->y0 - offset;
            arg0->y3 = arg0->y2 + offset;
            PRED(arg0) = arg2 + 0x60;
            PGRN(arg0) = arg2 + 0x60;
            PBLU(arg0) = arg2 + 0x60;
        } else {
            arg0->y0 = arg0->y1 - offset;
            arg0->y2 = arg0->y3 + offset;
            PRED(arg0) = (arg2 * 2) + 0x40;
            PGRN(arg0) = (arg2 * 2) + 0x40;
            PBLU(arg0) = (arg2 * 2) + 0x40;
        }
#ifdef VERSION_PSP
        if (arg1 == 0x400) {
            if (i) {
                arg0->x1 = arg0->x3 = arg0->x0 + (arg0->u1 - arg0->u0);
            } else {
                arg0->x0 = arg0->x2 = arg0->x1 - (arg0->u1 - arg0->u0);
            }
            arg0->y2 = arg0->y3 = arg0->y0 + (arg0->v2 - arg0->v0);
        }
        arg0->drawMode = DRAW_DEFAULT;
#else
        arg0->drawMode = DRAW_COLORS;
#endif
        arg0 = arg0->next;
    }
}

u16 func_us_801B29C4(void);
INCLUDE_ASM("st/lib_psp/psp/lib_psp/e_shop", func_us_801B29C4);

void func_us_801B2BE4(Entity* self) {
    Primitive* prim;
    s32 i;
    s16 itemId;
    s16 tempVar;
    ShopItem* ptr;
    s32 primIndex;

#ifndef VERSION_PSP
    if (g_CastleFlags[MET_MARIA_AFTER_HIPPOGRYPH]) {
        FntPrint("HIP ");
    }
    if (g_CastleFlags[RICHTER_CS_AFTER_M_AND_W]) {
        FntPrint("ARE ");
    }
    if (g_Status.relics[RELIC_SOUL_OF_BAT] & RELIC_FLAG_FOUND) {
        FntPrint("BAT ");
    }
    if (g_CastleFlags[MET_MARIA_IN_CEN]) {
        FntPrint("CEN ");
    }
    if (g_CastleFlags[INVERTED_CASTLE_UNLOCKED]) {
        FntPrint("REV ");
    }
    if (g_CastleFlags[DEATH_FIGHT_CS]) {
        FntPrint("DET ");
    }
    if (g_api.TimeAttackController(
            TIMEATTACK_EVENT_GALAMOTH_DEFEAT, TIMEATTACK_GET_RECORD)) {
        FntPrint("GAR ");
    }
    FntPrint("\n");
#endif

    switch (self->step) {
    case 0:
        primIndex = g_api.AllocPrimitives(PRIM_G4, 0xD);
        if (primIndex != -1) {
            InitializeEntity(g_EInitCommon);
            i = 0;
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            while (prim != NULL) {
                if (i < 6) {
                    prim->type = PRIM_LINE_G2;
                    prim->r0 = prim->r1 = 0x80;
                    prim->g0 = prim->g1 = 0x80;
                    prim->b0 = prim->b1 = 0x80;
                    prim->priority = 0x1FC;
                    prim->drawMode = DRAW_HIDE;
                } else if (i < 8) {
                    prim->x0 = prim->x1 = prim->x2 = prim->x3 = 0x80;
                    prim->y0 = prim->y1 = 0x18;
                    prim->y2 = prim->y3 = 0x78;
                    prim->priority = 0x1FA;
                    prim->drawMode = DRAW_HIDE;
                } else if (i < 10) {
                    prim->type = PRIM_GT4;
#ifdef VERSION_PSP
                    prim->tpage = 0x110;
#else
                    prim->tpage = 0x114;
#endif
                    prim->u0 = prim->u2 = (i - 8) * 0x6C + 8;
                    prim->u1 = prim->u3 = prim->u0 + 0x6C;
                    prim->v0 = prim->v1 = 0xD;
                    prim->v2 = prim->v3 = 0x61;
                    prim->x0 = prim->x1 = prim->x2 = prim->x3 = 0x80;
                    prim->y0 = prim->y1 = 0x1E;
                    prim->y2 = prim->y3 = 0x72;
                    prim->priority = 0x1FC;
                    prim->drawMode = DRAW_HIDE;
                } else if (i == 10) {
                    prim->x0 = prim->x2 = 0x11;
                    prim->x1 = prim->x3 = 0xEF;
                    prim->y0 = prim->y1 = 0x2B;
                    prim->y2 = prim->y3 = 0x37;
                    PRED(prim) = 0x40;
                    PGRN(prim) = 0x10;
                    PBLU(prim) = 0x10;
                    prim->priority = 0x1FB;
                    prim->drawMode = DRAW_HIDE;
                } else {
                    prim->type = PRIM_GT4;
                    prim->tpage = 0x1E;
                    prim->clut = 0x17F;
                    prim->u0 = prim->u2 = 0x58;
                    prim->u1 = prim->u3 = 0x60;
                    prim->v0 = prim->v1 = (i - 11) * 8 + 0x70;
                    prim->v2 = prim->v3 = 0x78 - (i - 11) * 8;
                    prim->x0 = prim->x2 = 0x7C;
                    prim->x1 = prim->x3 = prim->x0 + 8;
                    prim->y0 = prim->y1 = (i - 11) * 0x60 + 0x14;
                    prim->y2 = prim->y3 = prim->y0 + 8;
                    prim->priority = 0x1FC;
                    prim->drawMode = DRAW_HIDE;
                }
                prim = prim->next;
                i++;
            }
        }
        break;

    case 1:
        if (g_CutsceneFlags & 0x400) {
            SetStep(2);
            if (self->params) {
                // if showing the selling menu
                ptr = D_us_801814D8;
            } else {
                // if showing the buying menu
                self->ext.et_801B6F30.unk88 = func_us_801B29C4();
                ptr = D_us_801D4364;
            }
            for (i = 0; i < 64; i++) {
                itemId = ptr->itemId;
                switch (ptr->category) {
                case INVENTORY_HAND:
                    tempVar = g_Status.equipHandCount[itemId];
                    if (g_Status.equipment[LEFT_HAND_SLOT] == itemId) {
                        tempVar++;
                    }
                    if (g_Status.equipment[RIGHT_HAND_SLOT] == itemId) {
                        tempVar++;
                    }
                    D_us_801D425C[i] = 99 - tempVar;
                    break;

                case INVENTORY_HEAD:
                    tempVar = g_Status.equipBodyCount[itemId];
                    if (g_Status.equipment[HEAD_SLOT] == itemId) {
                        tempVar++;
                    }
                    D_us_801D425C[i] = 99 - tempVar;
                    break;

                case INVENTORY_BODY:
                    tempVar = g_Status.equipBodyCount[itemId];
                    if (g_Status.equipment[ARMOR_SLOT] == itemId) {
                        tempVar++;
                    }
                    D_us_801D425C[i] = 99 - tempVar;
                    break;

                case INVENTORY_CAPE:
                    tempVar = g_Status.equipBodyCount[itemId];
                    if (g_Status.equipment[CAPE_SLOT] == itemId) {
                        tempVar++;
                    }
                    D_us_801D425C[i] = 99 - tempVar;
                    break;

                case INVENTORY_ACCESSORY:
                    tempVar = g_Status.equipBodyCount[itemId];
                    if (self->params) {
                        D_us_801D425C[i] = tempVar;
                    } else {
                        if (g_Status.equipment[ACCESSORY_1_SLOT] == itemId) {
                            tempVar++;
                        }
                        if (g_Status.equipment[ACCESSORY_2_SLOT] == itemId) {
                            tempVar++;
                        }
                        D_us_801D425C[i] = 99 - tempVar;
                        break;
                    }
                    break;

                case INVENTORY_RELIC:
                    itemId = D_us_801814D4[itemId];
                    if (g_Status.relics[itemId] & RELIC_FLAG_FOUND) {
                        D_us_801D425C[i] = 0;
                    } else {
                        D_us_801D425C[i] = 1;
                    }
                    break;

                default:
                    D_us_801D425C[i] = 1;
                    break;
                }
                if (D_us_801D425C[i]) {
                    D_us_801D415C[i] = 1;
                } else {
                    D_us_801D415C[i] = 0;
                }
                ptr++;
            }
            self->ext.et_801B6F30.unk7C = 0;
            self->ext.et_801B6F30.unk7E = 0;
            self->ext.et_801B6F30.unk80 = 0;
            self->ext.et_801B6F30.unk82 = 0;
        }
        break;

    case 2:
        self->ext.et_801B6F30.unk7C++;
        self->ext.et_801B6F30.unk7E += 0x40;
        prim = &g_PrimBuf[self->primIndex];
        func_us_801B245C(prim, self->ext.et_801B6F30.unk7E,
                         self->ext.et_801B6F30.unk7C * 2, 0x74, 0x20, 8, 1);
        if (self->ext.et_801B6F30.unk7C == 0x10) {
            if (self->params) {
                SetStep(5);
            } else {
                SetStep(3);
            }
        }
        break;

    case 3:
        tempVar = g_pads[0].repeat;
        FntPrint(D_psp_092A4880, self->ext.et_801B6F30.unk82);
        if (tempVar & PAD_DOWN) {
            if (self->ext.et_801B6F30.unk80 < 6) {
                g_api.PlaySfx(SFX_UI_MOVE);
                self->ext.et_801B6F30.unk80++;
            } else if (
                self->ext.et_801B6F30.unk82 < self->ext.et_801B6F30.unk88) {
                g_api.PlaySfx(SFX_UI_MOVE);
                self->ext.et_801B6F30.unk82++;
            }
        } else if (tempVar & PAD_UP) {
            if (self->ext.et_801B6F30.unk80 > 0) {
                g_api.PlaySfx(SFX_UI_MOVE);
                self->ext.et_801B6F30.unk80--;
            } else if (self->ext.et_801B6F30.unk82) {
                g_api.PlaySfx(SFX_UI_MOVE);
                self->ext.et_801B6F30.unk82--;
            }
        } else if (tempVar & (PAD_R1 + PAD_R2)) {
            if (self->ext.et_801B6F30.unk80 < 6) {
                g_api.PlaySfx(SFX_UI_MOVE);
                self->ext.et_801B6F30.unk80 = 6;
            } else if (
                self->ext.et_801B6F30.unk82 < self->ext.et_801B6F30.unk88) {
                g_api.PlaySfx(SFX_UI_MOVE);
                self->ext.et_801B6F30.unk82 += 7;
                if (self->ext.et_801B6F30.unk82 > self->ext.et_801B6F30.unk88) {
                    self->ext.et_801B6F30.unk82 = self->ext.et_801B6F30.unk88;
                }
            }
        } else if (tempVar & (PAD_L1 + PAD_L2)) {
            if (self->ext.et_801B6F30.unk80 > 0) {
                g_api.PlaySfx(SFX_UI_MOVE);
                self->ext.et_801B6F30.unk80 = 0;
            } else if (self->ext.et_801B6F30.unk82) {
                g_api.PlaySfx(SFX_UI_MOVE);
                if (self->ext.et_801B6F30.unk82 > 7) {
                    self->ext.et_801B6F30.unk82 -= 7;
                } else {
                    self->ext.et_801B6F30.unk82 = 0;
                }
            }
        }
        itemId = self->ext.et_801B6F30.unk82 + self->ext.et_801B6F30.unk80;
        if (tempVar & PAD_RIGHT) {
            if (D_us_801D415C[itemId] < D_us_801D425C[itemId]) {
                g_api.PlaySfx(SFX_UI_MOVE);
                D_us_801D415C[itemId]++;
            }
        } else if (tempVar & PAD_LEFT) {
            if (D_us_801D415C[itemId] > 1) {
                g_api.PlaySfx(SFX_UI_MOVE);
                D_us_801D415C[itemId]--;
            }
        }
        tempVar = g_pads[0].tapped;
#ifdef VERSION_PSP
        if (tempVar & D_psp_08B42050) {
#else
        if (tempVar & PAD_CROSS) {
#endif
            if (g_Status.gold <
                    D_us_801D415C[itemId] * D_us_801D4364[itemId].price ||
                !D_us_801D415C[itemId]) {
                g_api.PlaySfx(SFX_UI_ERROR);
            } else {
                g_Status.gold -=
                    D_us_801D415C[itemId] * D_us_801D4364[itemId].price;
                switch (D_us_801D4364[itemId].category) {
                case INVENTORY_HAND:
                    tempVar = EQUIP_HAND;
                    break;
                case INVENTORY_HEAD:
                    tempVar = EQUIP_HEAD;
                    break;
                case INVENTORY_BODY:
                    tempVar = EQUIP_ARMOR;
                    break;
                case INVENTORY_CAPE:
                    tempVar = EQUIP_CAPE;
                    break;
                case INVENTORY_ACCESSORY:
                    tempVar = EQUIP_ACCESSORY;
                    break;
                }
                if (D_us_801D4364[itemId].category < NUM_EQUIP_KINDS) {
                    for (i = 0; i < D_us_801D415C[itemId]; i++) {
                        g_api.AddToInventory(D_us_801D4364[itemId].itemId,
                                             (enum EquipKind)tempVar);
                    }
                } else {
                    if (D_us_801D4364[itemId].category == INVENTORY_RELIC) {
                        g_api.func_800FE044(
                            D_us_801814D4[D_us_801D4364[itemId].itemId],
                            0x2000);
                    } else {
                        if (D_us_801D4364[itemId].itemId) {
                            g_api.LearnSpell(
                                D_us_80181510[D_us_801D4364[itemId].itemId -
                                              1]);
                        } else {
                            // castle map
                            g_api.func_800F2288(0);
                            g_CastleFlags[BOUGHT_CASTLE_MAP] = 1;
                        }
                    }
                }
                D_us_801D425C[itemId] -= D_us_801D415C[itemId];
                if (D_us_801D425C[itemId]) {
                    D_us_801D415C[itemId] = 1;
                } else {
                    D_us_801D415C[itemId] = 0;
                }
                SetStep(4);
                g_api.PlaySfx(SFX_UI_CONFIRM);
            }
#ifdef VERSION_PSP
        } else if (tempVar & D_psp_08B42054) {
#else
        } else if (tempVar & PAD_TRIANGLE) {
#endif
            SetStep(7);
        }
        prim = &g_PrimBuf[self->primIndex];
        for (i = 0; i < 10; i++) {
            prim = prim->next;
        }
        prim->y0 = prim->y1 = (self->ext.et_801B6F30.unk80 * 0xC) + 0x1F;
        prim->y2 = prim->y3 = prim->y0 + 0xC;
        prim->drawMode = DRAW_COLORS;

        prim = prim->next;
        if (self->ext.et_801B6F30.unk82) {
            prim->drawMode = DRAW_DEFAULT;
        } else {
            prim->drawMode = DRAW_HIDE;
        }

        prim = prim->next;
        if (self->ext.et_801B6F30.unk82 < self->ext.et_801B6F30.unk88) {
            prim->drawMode = DRAW_DEFAULT;
        } else {
            prim->drawMode = DRAW_HIDE;
        }
        break;

    case 4:
        switch (self->step_s) {
        case 0:
            if (g_api.func_80131F68()) {
                g_api.PlaySfx(SET_STOP_MUSIC);
                self->step_s++;
            } else {
                self->step_s++;
            }
            break;

        case 1:
            if (!g_api.func_80131F68()) {
                g_CutsceneFlags |= 0x800;
                g_api.PlaySfx(NA_VO_ML_THANKS);
                SetStep(3);
            }
            break;
        }
        break;

    case 5:
        tempVar = g_pads[0].repeat;
        if (tempVar & PAD_DOWN) {
            if (self->ext.et_801B6F30.unk80 < 6) {
                g_api.PlaySfx(SFX_UI_MOVE);
                self->ext.et_801B6F30.unk80++;
            } else if (self->ext.et_801B6F30.unk82 < 0) {
                g_api.PlaySfx(SFX_UI_MOVE);
                self->ext.et_801B6F30.unk82++;
            }
        } else if (tempVar & PAD_UP) {
            if (self->ext.et_801B6F30.unk80 > 0) {
                g_api.PlaySfx(SFX_UI_MOVE);
                self->ext.et_801B6F30.unk80--;
            } else if (self->ext.et_801B6F30.unk82) {
                g_api.PlaySfx(SFX_UI_MOVE);
                self->ext.et_801B6F30.unk82--;
            }
        }
        itemId = self->ext.et_801B6F30.unk82 + self->ext.et_801B6F30.unk80;
        if (tempVar & PAD_RIGHT) {
            if (D_us_801D415C[itemId] < D_us_801D425C[itemId]) {
                g_api.PlaySfx(SFX_UI_MOVE);
                D_us_801D415C[itemId]++;
            }
        } else if (tempVar & PAD_LEFT) {
            if (D_us_801D415C[itemId] > 1) {
                g_api.PlaySfx(SFX_UI_MOVE);
                D_us_801D415C[itemId]--;
            }
        }
        tempVar = g_pads[0].tapped;
#ifdef VERSION_PSP
        if (tempVar & D_psp_08B42050) {
#else
        if (tempVar & PAD_CROSS) {
#endif
            if (D_us_801D415C[itemId] == 0) {
                g_api.PlaySfx(SFX_UI_ERROR);
            } else {
                g_Status.gold +=
                    D_us_801D415C[itemId] * D_us_801814D8[itemId].price;
                if (g_Status.gold > 999999) {
                    g_Status.gold = 999999;
                }
                ptr = &D_us_801814D8[itemId];
                g_Status.equipBodyCount[ptr->itemId] -= D_us_801D415C[itemId];
                D_us_801D425C[itemId] -= D_us_801D415C[itemId];
                D_us_801D415C[itemId] = 0;
                SetStep(6);
                g_api.PlaySfx(SFX_UI_CONFIRM);
            }
#ifdef VERSION_PSP
        } else if (tempVar & D_psp_08B42054) {
#else
        } else if (tempVar & PAD_TRIANGLE) {
#endif
            SetStep(7);
        }
        prim = &g_PrimBuf[self->primIndex];
        for (i = 0; i < 10; i++) {
            prim = prim->next;
        }
        prim->y0 = prim->y1 = (self->ext.et_801B6F30.unk80 * 0xC) + 0x1F;
        prim->y2 = prim->y3 = prim->y0 + 0xC;
        prim->drawMode = DRAW_COLORS;

        prim = prim->next;
        if (self->ext.et_801B6F30.unk82) {
            prim->drawMode = DRAW_DEFAULT;
        } else {
            prim->drawMode = DRAW_HIDE;
        }

        prim = prim->next;
        if (self->ext.et_801B6F30.unk82 < 0) {
            prim->drawMode = DRAW_DEFAULT;
        } else {
            prim->drawMode = DRAW_HIDE;
        }
        break;

    case 6:
        switch (self->step_s) {
        case 0:
            if (g_api.func_80131F68()) {
                g_api.PlaySfx(SET_STOP_MUSIC);
                self->step_s++;
            } else {
                self->step_s++;
            }
            break;

        case 1:
            if (!g_api.func_80131F68()) {
                g_CutsceneFlags |= 0x800;
                g_api.PlaySfx(NA_VO_ML_THANKS);
                SetStep(5);
            }
            break;
        }
        break;

    case 7:
        if ((g_CutsceneFlags & 0x200) == 0) {
            prim = &g_PrimBuf[self->primIndex];
            for (i = 0; i < 10; i++) {
                prim = prim->next;
            }
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;

            prim->drawMode = DRAW_HIDE;
            prim = prim->next;

            prim->drawMode = DRAW_HIDE;
            self->ext.et_801B6F30.unk7E = 0x400;
            self->ext.et_801B6F30.unk7C = 0x10;
            self->step++;
            g_CutsceneFlags |= 0x200;
        }
        break;

    case 8:
        self->ext.et_801B6F30.unk7C--;
        self->ext.et_801B6F30.unk7E -= 0x40;
        prim = &g_PrimBuf[self->primIndex];
        func_us_801B245C(prim, self->ext.et_801B6F30.unk7E,
                         self->ext.et_801B6F30.unk7C * 2, 0x74, 0x20, 8, 1);
        if (self->ext.et_801B6F30.unk7C == 1) {
            g_CutsceneFlags &= ~0x400;
        }
        if (!self->ext.et_801B6F30.unk7C) {
            DestroyEntity(self);
        }
        break;
    }
}

Primitive* func_us_801B3EC8(Primitive* prim, u32 number, u16 maxDigits) {
    s32 i;
    s32 currentDigit;

    bool hasADigit = false;
    for (currentDigit = maxDigits - 1; currentDigit >= 0; currentDigit--) {
        u32 digitValue = number;
        for (i = 0; i < currentDigit; i++) {
            digitValue /= 10;
        }
        if (digitValue != 0) {
            if (digitValue < 10) {
                prim->u0 = digitValue * 8;
                prim->v0 = 8;
            } else {
                prim->u0 = 0x28;
                prim->v0 = 0x10;
            }
            for (i = 0; i < currentDigit; i++) {
                digitValue *= 10;
            }
            number -= digitValue;
            hasADigit = true;
            prim->drawMode = DRAW_DEFAULT;
        } else if (hasADigit || currentDigit == 0) {
            prim->u0 = 0;
            prim->v0 = 8;
            prim->drawMode = DRAW_DEFAULT;
        } else {
            prim->drawMode = DRAW_HIDE;
        }
        prim = prim->next;
    }
    return prim;
}

Primitive* func_us_801B3FB4(Primitive* prim, u8* str, u16 length, s32 arg3) {
    u8 ch;
    s32 i;
    u32 max;
    u8* chPtr;

    chPtr = str;
    max = 0;
    for (i = 0; i < length; i++) {
#ifdef VERSION_PSP
        if (*chPtr == 0xFF) {
            break;
        }
        chPtr++;
        max++;
    }
    for (i = 0; i < max; i++) {
#endif
        ch = *str++;
        prim->u0 = (ch & 0xF) * 8;
        prim->v0 = (ch & 0xF0) >> 1;
        if (arg3 != 0) {
            prim->drawMode = DRAW_DEFAULT;
        }
        prim = prim->next;
    }
#ifdef VERSION_PSP
    for (; i < length; i++) {
        prim->drawMode = DRAW_HIDE;
        prim = prim->next;
    }
#endif
    return prim;
}

void func_us_801B4010(u16* arg0) {
    *arg0++ = g_Status.equipment[0];
    *arg0++ = g_Status.equipment[1];
    *arg0++ = g_Status.equipment[2];
    *arg0++ = g_Status.equipment[3];
    *arg0++ = g_Status.equipment[4];
    *arg0++ = g_Status.equipment[5];
    *arg0 = g_Status.equipment[6];
}
