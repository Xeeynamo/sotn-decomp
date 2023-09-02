#include "sel.h"

void func_801B642C(void) {
    D_801BC360 = 2;
    D_801BC35E = 2;
    D_801BC362 = 0;
    D_801BC366 = 0;
    D_801BC36A = 0;
    D_801BC36B = 8;
    D_801BC35A = D_801BC35C + 0x14;
}

s32 func_801B6480(s32 textDialogue) {
    Primitive* prim;
    s16 firstPrimIndex;

    firstPrimIndex = g_api.AllocPrimitives(PRIM_SPRT, 7);
    g_Dialogue.primIndex[2] = firstPrimIndex;
    if (firstPrimIndex == -1) {
        g_Dialogue.primIndex[2] = 0;
        return 0;
    }
    g_Dialogue.nextCharDialogue = textDialogue;
    g_Dialogue.unk3C = 0;
    g_Dialogue.primIndex[1] = -1;
    g_Dialogue.primIndex[0] = -1;
    func_801B642C();

    //! FAKE:
    if (prim && prim) {
    }

    prim = g_Dialogue.prim[0] = &g_PrimBuf[g_Dialogue.primIndex[2]];

    prim->blendMode = BLEND_VISIBLE;
    prim = g_Dialogue.prim[1] = prim->next;

    prim->blendMode = BLEND_VISIBLE;
    prim = g_Dialogue.prim[2] = prim->next;

    prim->blendMode = BLEND_VISIBLE;
    prim = g_Dialogue.prim[3] = prim->next;

    prim->blendMode = BLEND_VISIBLE;
    prim = g_Dialogue.prim[4] = prim->next;

    prim->blendMode = BLEND_VISIBLE;
    prim = g_Dialogue.prim[5] = prim->next;

    prim->type = PRIM_GT4;
    prim->blendMode = BLEND_VISIBLE;

    prim = prim->next;
    prim->type = PRIM_G4;
    prim->b0 = prim->b1 = 0x7F;
    prim->b2 = prim->b3 = 0;
    prim->g0 = prim->g1 = prim->g2 = prim->g3 = 0;
    prim->r0 = prim->r1 = prim->r2 = prim->r3 = 0;
    prim->x0 = prim->x2 = 4;
    prim->x1 = prim->x3 = 0xF8;
    prim->priority = 0x1FD;
    prim->blendMode = BLEND_VISIBLE;

    prim = prim->next;
    prim->type = 1;
    prim->r0 = prim->g0 = prim->b0 = 16;
    prim->x0 = 3;
    prim->y0 = 0x2F;
    prim->v0 = 0x4A;
    prim->priority = 0x1FC;
    prim->blendMode = BLEND_VISIBLE;
    return 1;
}

void func_801B6648(s16 yOffset) {
    RECT rect;

    rect.y = (yOffset * 12) + 384;
    rect.w = 64;
    rect.x = 0;
    rect.h = 12;
    ClearImage(&rect, 0, 0, 0);
}

void func_801B66A4(void) {
    Primitive* prim;

    func_801B6648(g_Dialogue.nextCharY);
    prim = g_Dialogue.prim[g_Dialogue.nextCharY];
    prim->tpage = 0x10;
    prim->clut = g_Dialogue.clutIndex;
    prim->y0 = g_Dialogue.nextLineY;
    prim->u0 = 0;
    prim->x0 = g_Dialogue.startX;
    prim->x0 = prim->x0 + 4;
    prim->v0 = g_Dialogue.nextCharY * 0xC - 0x80;
    prim->u1 = 0xC0;
    prim->v1 = 0xC;
    prim->priority = 0x1FF;
    prim->blendMode = 0;
}

INCLUDE_ASM("asm/us/st/sel/nonmatchings/3642C", func_801B675C);

void func_801B68E0(s32 arg0) {
    D_801BC394 = arg0 + 0x100000;
    D_801BC392 = 0;
    D_801BC390 = 1;
}

void func_801B690C(u8 ySteps, Entity* self) {
    s32 primIndex = g_Dialogue.nextCharY + 1;
    Primitive* prim;
    s32 i;

    while (primIndex >= 5) {
        primIndex -= 5;
    }

    if (self->step_s == 0) {
        prim = g_Dialogue.prim[primIndex];
        prim->v1 -= ySteps;
        prim->v0 = ySteps + prim->v0;
        if (prim->v1 == 0) {
            self->step_s++;
            prim->blendMode = 8;
        }
    }

    for (i = 0; i < 5; i++) {
        if (i != primIndex) {
            prim = g_Dialogue.prim[i];
            prim->y0 -= ySteps;
        }
    }
    g_Dialogue.portraitAnimTimer++;
}

INCLUDE_ASM("asm/us/st/sel/nonmatchings/3642C", func_801B69F8);

INCLUDE_ASM("asm/us/st/sel/nonmatchings/3642C", func_801B76F0);

void func_801B786C(s16 arg0) {
    RECT rect;
    rect.x = 0x200;
    rect.y = arg0 * 16;
    rect.w = 0x80;
    rect.h = 0x10;

    ClearImage(&rect, 0, 0, 0);
}

INCLUDE_ASM("asm/us/st/sel/nonmatchings/3642C", func_801B78BC);

INCLUDE_ASM("asm/us/st/sel/nonmatchings/3642C", func_801B79D4);

void func_801B80F0(void) {
    EnterCriticalSection();
    g_EvSwCardEnd = OpenEvent(SwCARD, EvSpIOE, EvMdNOINTR, NULL);
    g_EvSwCardErr = OpenEvent(SwCARD, EvSpERROR, EvMdNOINTR, NULL);
    g_EvSwCardTmo = OpenEvent(SwCARD, EvSpTIMOUT, EvMdNOINTR, NULL);
    g_EvSwCardNew = OpenEvent(SwCARD, EvSpNEW, EvMdNOINTR, NULL);
    g_EvHwCardEnd = OpenEvent(HwCARD, EvSpIOE, EvMdNOINTR, NULL);
    g_EvHwCardErr = OpenEvent(HwCARD, EvSpERROR, EvMdNOINTR, NULL);
    g_EvHwCardTmo = OpenEvent(HwCARD, EvSpTIMOUT, EvMdNOINTR, NULL);
    g_EvHwCardNew = OpenEvent(HwCARD, EvSpNEW, EvMdNOINTR, NULL);
    ExitCriticalSection();
    EnableEvent(g_EvSwCardEnd);
    EnableEvent(g_EvSwCardErr);
    EnableEvent(g_EvSwCardTmo);
    EnableEvent(g_EvSwCardNew);
    EnableEvent(g_EvHwCardEnd);
    EnableEvent(g_EvHwCardErr);
    EnableEvent(g_EvHwCardTmo);
    EnableEvent(g_EvHwCardNew);
}

s32 _peek_event_with_retry(void) {
    if (TestEvent(g_EvSwCardEnd) == 1) {
        return 1;
    } else if (TestEvent(g_EvSwCardErr) == 1) {
        return 2;
    } else if (TestEvent(g_EvSwCardTmo) == 1) {
        return 3;
    } else if (TestEvent(g_EvSwCardNew) == 1) {
        return 4;
    } else if (D_801BC2F8-- < 0) {
        return 2;
    }
    return 0;
}

s32 _peek_event(void) {
    if (TestEvent(g_EvSwCardEnd) == 1) {
        return 1;
    } else if (TestEvent(g_EvSwCardErr) == 1) {
        return 2;
    } else if (TestEvent(g_EvSwCardTmo) == 1) {
        return 3;
    } else if (TestEvent(g_EvSwCardNew) == 1) {
        return 4;
    }
    return 0;
}

void _clear_event(void) {
    TestEvent(g_EvSwCardEnd);
    TestEvent(g_EvSwCardErr);
    TestEvent(g_EvSwCardTmo);
    TestEvent(g_EvSwCardNew);
}

s32 _card_event_x(void) {
    while (1) {
        if (TestEvent(g_EvHwCardEnd) == 1) {
            return 1;
        } else if (TestEvent((u32)g_EvHwCardErr) == 1) {
            return 2;
        } else if (TestEvent((u32)g_EvHwCardTmo) == 1) {
            return 3;
        } else if (TestEvent((u32)g_EvHwCardNew) == 1) {
            return 4;
        }
    }
}

void _clear_event_x(void) {
    TestEvent(g_EvHwCardEnd);
    TestEvent(g_EvHwCardErr);
    TestEvent(g_EvHwCardTmo);
    TestEvent(g_EvHwCardNew);
}

void func_801B84F0(void) { D_801D6B20 = 0; }

void func_801B8500(void) {
    D_801BC650 = 0;
    D_801BC8C8 = 0;
}

INCLUDE_ASM("asm/us/st/sel/nonmatchings/3642C", func_801B8518);

s32 func_801B8714(s32 arg0) { return D_801BC654[arg0 * 0x9E]; }

INCLUDE_ASM("asm/us/st/sel/nonmatchings/3642C", func_801B873C);

#ifndef NON_MATCHING
INCLUDE_ASM("asm/us/st/sel/nonmatchings/3642C", func_801B881C);
#else
extern volatile u8 D_801BC658[];
u8 func_801B881C(s32 arg0, s32 arg1) {
    s32 idx = arg0 * 0x9E * 4;
    return D_801BC658[idx + arg1];
}
#endif

s32 MemcardReadFile(
    s32 slot, s32 block, const char* name, void* data, s32 saveLen) {
    char savePath[32];
    s32 fd;
    s32 actualSaveLen;

    sprintf(savePath, g_MemcardSavePath, slot, block, name);
    if (saveLen == 0) {
        actualSaveLen = 0x2B8;
    } else {
        actualSaveLen = saveLen * 0x2000;
    }

    fd = open(savePath, O_RDONLY | O_NOWAIT);
    if (fd == -1) {
        return -1;
    }

    D_801BC2FC = fd;
    _clear_event();
    read(fd, data, actualSaveLen);
    return 0;
}

s32 MemcardWriteFile(
    s32 slot, s32 block, const char* name, void* data, s32 flags, s32 create) {
    s8 savePath[32];
    s32 len;
    s32 fd;

    sprintf(savePath, &g_MemcardSavePath, slot, block, name);

    // known PSX bug: when creating a a file with open(), any read or write
    // will immediately fail. The workaround is to close the file and open
    // it again.
    if (create == 1) {
        fd = open(savePath, (flags << 0x10) | O_CREAT);
        if (fd == -1) {
            return -2;
        } else {
            close(fd);
        }
    }

    len = flags << 0xD;
    fd = open(savePath, O_WRONLY | O_NOWAIT);

    if (fd == -1) {
        return -1;
    } else {
        D_801BC2FC = fd;
        _clear_event();
        write(fd, data, len);
    }
    return 0;
}

s32 MemcardEraseFile(s32 slot, s32 block, const char* name) {
    char buf[0x20];
    sprintf(buf, g_MemcardSavePath, slot, block, name);
    return -(erase(buf) == 0);
}

s32 func_801B8A10(s32 nCardSlot) {
    s32 unk = _peek_event();

    if (unk == 0) {
        return 0;
    }

    close(D_801BC2FC);
    if (unk != 1) {
        return -3;
    }

    D_8006C3AC |= unk << nCardSlot;
    return 1;
}
