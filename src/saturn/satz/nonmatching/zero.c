// SPDX-License-Identifier: AGPL-3.0-or-later
#include <stdint.h>
#include "../../zero.h"
#include "../../lib/sys.h"
#include "../../saturn_hw.h"
#include "../../zero/sound.h"
#define _SPR2_
#include "../../lib/spr/spr.h"
#include "../../game.h"

void func_0600AA18(s32 arg0);

extern SprSpCmd* d_0605AEAC;

extern s32 DAT_06038A48;
extern s32 DAT_0605066C;
extern s32 DAT_06050604;
extern GfsDirName DAT_06059260[300];
extern u8 DAT_06057F70[];

extern s32 DAT_06050608;

extern s32 DAT_06064428;
void func_06011A6C(s32 arg0);
void func_0601298C(void);

extern u16 DAT_06039414[];
extern s32 DAT_06062254;
extern s32 DAT_06064204;

extern GfsHn DAT_0605064C;
extern s32 DAT_06050650;
extern u8* DAT_06050658;
extern s32 DAT_0605065C;
extern s32 DAT_06050660;
extern s32 DAT_06050664;
extern s32 DAT_06050670;

s32 QueueVramTransfer(u32 dst, void* src, s32 size);

#include "../../zero/overlay.h"

void* sotn_satz_load_target(void* dst);
int sotn_satz_install_overlay(
    const char* name, void* dst, u32 sector, s32* size);

typedef struct {
    GfsDirTbl tbl;
    GfsDirName names[300];
} LoadBufferDirTbl;

int cdb_read_sector(int32_t fad, uint8_t* out2048);

extern s32 DAT_060642E0;

extern u8 g_StageOvlArea[];
s32 func_0600C99C(u16* dst, s32 offset, u32 len);
s32 func_06008524(u32 dest, void* src, u32 cnt);

extern const s16 rsin_tbl[];

typedef struct {
    s32 state;
    s32 unk4;
    s16 x;
    s16 y;
    s16 unkC;
    s16 radiusX;
    s16 radiusY;
    s16 unk12;
    s16 angleStep;
    s16 angle[20];
} LoadingRing;
extern s32 DAT_06057CD0[20];
extern s32 DAT_06057D20[20];

#define SLOT_VRAM(slot) (0x25C00000 + DAT_0605AEC0[slot][0] * 8)

extern FileLoadEntry* DAT_06038BCC[];
extern char* DAT_06038BF4[];
extern const char* DAT_06048178[];
extern s32 DAT_06050654;
GfsHn func_06006720(Unk0600654C* req, s32 tmode, GfsTrFunc trfunc);

s32 func_06006E9C(s32* nsct, GfsHn gfs);

#define REC16(p, o) (*(u16*)((u8*)(p) + (o)))
#define REC32(p, o) (*(s32*)((u8*)(p) + (o)))

extern SprSpCmd* SpMstCmd;
extern SprSpCmd* d_0605AEAC;
extern s32 DAT_0603900C[];
extern s32 (*DAT_0603904C[])(Primitive* prim);

s32 func_06007B8C(s16* colors);
u16 func_06007BE0(s16* colors, s32 arg1);
u16 func_06007B34(SprLookupTbl* tbl);
#include "../../zero/text.h"

extern SprSpCmd* d_0605AEAC;

#include "../../lib/csh.h"

extern u16 DAT_06039414[];
extern s32 DAT_060642E0;
extern s32 DAT_06062254;
extern s32 DAT_06064204;

extern SprSpCmd* d_0605AEAC;
s32 func_0600B954(SprSpCmd* cmd, SpriteObject* obj, SpritePart* part, s32* pos);
s32 func_0600BA24(SprSpCmd* cmd, SpriteObject* obj, SpritePart* part, s32* pos);

#include "../../zero/fontmap.h"

static int direct_load(const char* name, s32 fid, void* dst, s32* size);
s32 func_06006A7C(s32* read);
static s32 GfsStep(s32 result);

static s32 GfsStepBegin(s32 kind);
void func_06006C00(char* path);

static void LoadListStart(s32 index);
static char* PlayerFile(s32 k);
static const char* StageMapFile(void);

u16 AllocSpriteCharVram(u16 colorMode, s32 unused, u16* size, void* data);

static void FadeColors(
    s16 fromR, s16 fromG, s16 fromB, s16 toR, s16 toG, s16 toB);

static void ColorOffsetSet(s16 value);
void func_06009CCC(void);

s16 func_0600AE30(u8* data, SaturnSpriteImage* images, s32 colorMode);
s16 func_0600AEE4(u16* palettes);
void func_0600C2EC(void);
static void sotn_satz_cmd_offset_vertex(SprSpCmd* cmd, s32 i, s16 dx, s16 dy);
s32 rsin(s32 angle);
s32 rcos(s32 angle);

static void SoundSetRequest(s32 fx);

static void SoundSetRequest2(s32 fx);

static void SoundPlayConfig(s32 channel, s32 config);
static void PlaySfxCommand(s32 cmd);
static void PlaySfxFadeAll(s32 withLast);

static void PlaySfxFade(s32 frames, s32 volumeFrames);
s32 func_06012C4C(u8 id, s32 offset);

static s16 RingOffset(s32 trig, s32 radius);

s32 func_06006170(void) {
    CdcPos pos;
    CdcStat stat;
    s32 ret = 0xFF;
    s32 result;

    switch (DAT_06050668) {
    case 0:
        DAT_06038A48 = 0;
        DAT_06050668 = 3;
        DAT_0605066C = 0;
    case 3:
        GFS_DIRTBL_TYPE(&DAT_0605AE80) = GFS_DIR_NAME;
        GFS_DIRTBL_DIRNAME(&DAT_0605AE80) = DAT_06059260;
        GFS_DIRTBL_NDIR(&DAT_0605AE80) = 300;
        result = GFS_Init(10, DAT_06057F70, &DAT_0605AE80);
        if (result >= 0) {
            ret = 1;
            DAT_06038A48 = 0;
        } else {
            if (result == -23 || result == -2) {
                SYS_EXECDMP();
            }
            if (result == -1 || result == -25) {
                DAT_06038A48++;
                DAT_06050668 = 1;
            } else {
                ret = 0;
            }
        }
        break;
    case 1:
        pos.ptype = 3;
        if (CDC_CdSeek(&pos) < 0) {
            DAT_06038A48++;
        } else {
            DAT_06050668++;
            DAT_06050604 = 0;
        }
        break;
    case 2:
        do {
            result = CDC_GetPeriStat(&stat);
        } while (result == -8);
        if (result < 0) {
            DAT_06050668 = 1;
            DAT_06038A48++;
        } else if (DAT_06050604++, (stat.status & 0xF) == 1) {
            DAT_06050668++;
        } else if (DAT_06050604 > 15) {
            DAT_06050668 = 1;
            DAT_06038A48++;
        }
        break;
    }
    if (DAT_06038A48 > 5) {
        ret = 0;
    }
    return ret;
}

s32 func_060062F8(s32 fid, GfsDirTbl* dirtbl) {
    CdcPos pos;
    CdcStat stat;
    s32 ret = 0xFF;
    s32 result;

    switch (DAT_06050668) {
    case 0:
        DAT_06038A48 = 0;
        DAT_06050668 = 3;
        DAT_0605066C = 1;
    case 3:
        result = GFS_LoadDir(fid, dirtbl);
        if (result >= 0) {
            ret = 1;
            DAT_06038A48 = 0;
        } else {
            if (result == -23 || result == -2) {
                SYS_EXECDMP();
            }
            if (result == -1 || result == -25) {
                DAT_06038A48++;
                DAT_06050668 = 1;
            } else {
                ret = 0;
            }
        }
        break;
    case 1:
        pos.ptype = 3;
        if (CDC_CdSeek(&pos) < 0) {
            DAT_06038A48++;
        } else {
            DAT_06050668++;
            DAT_06050608 = 0;
        }
        break;
    case 2:
        do {
            result = CDC_GetPeriStat(&stat);
        } while (result == -8);
        if (result < 0) {
            DAT_06050668 = 1;
            DAT_06038A48++;
        } else if (DAT_06050608++, (stat.status & 0xF) == 1) {
            DAT_06050668++;
        } else if (DAT_06050608 > 15) {
            DAT_06050668 = 1;
            DAT_06038A48++;
        }
        break;
    }
    if (DAT_06038A48 > 5) {
        ret = 0;
    }
    return ret;
}

static int direct_load(const char* name, s32 fid, void* dst, s32* size) {
    GfsDirId rec;
    u8 sector[2048];
    s32 fad, bytes, done;

    if (strcmp(name, "KANJI.FON") && strcmp(name, "SUB_DISP.MAP")) {
        return 0;
    }
    if (fid < 0 || GFS_GetDirInfo(fid, &rec) < 0) {
        satz_die("%s: no directory record", name);
    }
    fad = GFS_DIR_FAD(&rec);
    bytes = GFS_DIR_SIZE(&rec);
    for (done = 0; done < bytes; done += 2048, fad++) {
        if (!cdb_read_sector(fad, sector)) {
            satz_die("%s: can't read sector %d", name, (int)fad);
        }
        memcpy(
            (u8*)dst + done, sector, bytes - done < 2048 ? bytes - done : 2048);
    }
    *size = bytes;
    return 1;
}

s32 func_06006574(Unk0600654C* req) {
    s32 phase, status;
    s32 fid = 0;
    s32 loaded = 0;

    while (func_06006EF8() != 0) {
    }
    func_06006C00(req->unk0);
    for (phase = 0; phase <= 2;) {
        status = 0xFF;
        if (phase == 0) {
            DAT_06050668 = 0;
            phase = 1;
        }
        if (phase == 1) {
            fid = GFS_NameToId((Sint8*)func_06006E14(req->unk0));
            if (GfsStepBegin(3)) {
                status = GfsStep(fid);
            } else {
                status = 0;
            }
        } else {
            if (DAT_06050668 == 0) {
                DAT_06038A48 = 0;
                DAT_06050668 = 1;
                DAT_0605066C = 4;
            }
            if (DAT_06050668 == 1) {
                if (sotn_satz_install_overlay(func_06006E14(req->unk0),
                                              req->unk4, req->unkA, &loaded)) {
                    status = 1;
                } else if (
                    direct_load(func_06006E14(req->unk0), fid,
                                sotn_satz_load_target(req->unk4), &loaded)) {
                    status = 1;
                } else {
                    loaded =
                        GFS_Load(fid, req->unkA,
                                 sotn_satz_load_target(req->unk4), req->unk8);
                    status = GfsStep(loaded) == 1 ? 1 : 0xFF;
                }
                if (status == 1) {
                    DAT_06038A48 = 0;
                } else {
                    DAT_06038A48++;
                }
            }
            if (DAT_06038A48 > 5) {
                status = 0;
            }
        }
        if (status == 1) {
            DAT_06050668 = 0;
            phase++;
        } else if (status == 0) {
            SYS_EXECDMP();
        }
    }
    return loaded;
}

GfsHn func_06006720(Unk0600654C* req, s32 tmode, GfsTrFunc trfunc) {
    s32 step, status, result, nsct = 0, fid = 0, installed;
    GfsHn gfs = NULL;

    while (func_06006EF8() != 0) {
    }
    func_06006C00(req->unk0);
    if (sotn_satz_install_overlay(
            func_06006E14(req->unk0), req->unk4, req->unkA, &installed)) {
        DAT_0605064C = NULL;
        DAT_06050650 = DAT_06050654 = installed;
        DAT_06050670 = 0;
        return NULL;
    }
    for (step = 0; step <= 6;) {
        status = 0;
        switch (step) {
        case 0:
            DAT_06050668 = 0;
            step = 1;
        case 1:
            if (GfsStepBegin(3)) {
                fid = GFS_NameToId((Sint8*)func_06006E14(req->unk0));
                status = GfsStep(fid);
            }
            break;
        case 2:
        case 3:
        case 5:
            if (step == 3 && req->unkA == 0) {
                step = 4;
                continue;
            }
            status = 0xFF;
            if (DAT_06050668 == 0) {
                DAT_06038A48 = 0;
                DAT_06050668 = 1;
                DAT_0605066C = step == 2 ? 5 : step == 3 ? 6 : 8;
            } else if (DAT_06050668 != 1) {
                status = DAT_06038A48 > 5 ? 0 : 0xFF;
                break;
            }
            if (step == 2) {
                gfs = GFS_Open(fid);
                result = gfs != NULL ? 0 : -1;
            } else if (step == 3) {
                result = GFS_Seek(gfs, req->unkA, 0);
                if (result == -23 || result == -2) {
                    SYS_EXECDMP();
                }
            } else {
                result = GFS_NwCdRead(gfs, nsct);
                if (result == -23 || result == -2) {
                    SYS_EXECDMP();
                }
            }
            if (result >= 0) {
                DAT_06038A48 = 0;
                status = 1;
            } else {
                DAT_06038A48++;
            }
            if (status != 1 && DAT_06038A48 > 5) {
                status = 0;
            }
            break;
        case 4:
            if (!GfsStepBegin(7)) {
                break;
            }
            if (GfsStep(GFS_SetTmode(gfs, tmode)) != 1) {
                break;
            }
            if (trfunc != NULL) {
                GFS_SetTrFunc(gfs, trfunc);
            }
            if (req->unk8 == -1) {
                DAT_06050650 = DAT_06050654 = func_06006E9C(&nsct, gfs);
            } else {
                DAT_06050650 = DAT_06050654 = req->unk8;
                nsct = ((u32)req->unk8 + 0x7FF) >> 11;
            }
            status = 1;
            break;
        case 6:
            if (GfsStepBegin(9)) {
                status = GfsStep(GFS_SetTransPara(gfs, 10));
            }
            break;
        }
        if (status == 1) {
            DAT_06050668 = 0;
            step++;
        } else if (status == 0) {
            gfs = NULL;
            SYS_EXECDMP();
            break;
        }
    }
    if (gfs != NULL) {
        DAT_0605064C = gfs;
        DAT_06050658 = req->unk4;
        DAT_0605065C = req->unkC;
        DAT_06050660 = req->unk10;
    }
    DAT_06050670 = 0;
    return gfs;
}

s32 func_06006A7C(s32* read) {
    GfsHn gfs = DAT_0605064C;
    s32 result = 0;
    s32 done = 0;
    s32 nsct, size;
    s32 amode, ndata = 0;

    *read = 0;
    if (gfs == NULL) {
        return 0;
    }
    if (DAT_06050670 == 0) {
        DAT_06050670 = 1;
    }
    if (DAT_06050670 == 1) {
        if (DAT_0605065C > 0) {
            nsct = DAT_0605065C;
            size = DAT_0605065C * 0x800;
        } else {
            size = DAT_06050650;
            nsct = (size + 0x800) / 0x800;
        }
        if (size > DAT_06050650) {
            size = DAT_06050650;
        }
        DAT_06050664 = size;
        GFS_NwFread(gfs, nsct, DAT_06050658, size);
        DAT_06050670++;
    }
    if (DAT_06050670 == 2) {
        result = GFS_NwExecOne(gfs);
        if (result < 0) {
            if (result == -23 || result == -2) {
                SYS_EXECDMP();
            }
            return result;
        }
        if (result == 3) {
            return 3;
        }
        if (result == 0) {
            done = 1;
            ndata = DAT_06050664;
        } else {
            GFS_NwGetStat(gfs, &amode, &ndata);
            if (ndata >= DAT_06050664) {
                done = 1;
            }
        }
    }
    if (done) {
        DAT_06050650 -= ndata;
        if (!(DAT_06050660 & 1)) {
            DAT_06050658 += ndata / 4 * 4;
        }
        if (DAT_06050650 <= 0) {
            result = 0;
        }
        DAT_06050670 = 0;
        *read = ndata;
    }
    if (result == 0) {
        GFS_Close(gfs);
    }
    return result;
}

static s32 GfsStep(s32 result) {
    if (result >= 0) {
        return 1;
    }
    if (result == -23 || result == -2) {
        SYS_EXECDMP();
    }
    return 0;
}

static s32 GfsStepBegin(s32 kind) {
    if (DAT_06050668 == 0) {
        DAT_06050668 = 1;
        DAT_0605066C = kind;
    } else if (DAT_06050668 != 1) {
        return 0;
    }
    return 1;
}

void func_06006C00(char* path) {
    LoadBufferDirTbl* dir = (LoadBufferDirTbl*)g_WorkBuffer.load.data;
    char name[0x40];
    s32 i, len, step, result;
    s32 fid = 0;

    GFS_DIRTBL_TYPE(&dir->tbl) = GFS_DIR_NAME;
    GFS_DIRTBL_DIRNAME(&dir->tbl) = dir->names;
    GFS_DIRTBL_NDIR(&dir->tbl) = 300;
    DAT_06050668 = 0;
    if (!GfsStepBegin(2) || !GfsStep(GFS_SetDir(&DAT_0605AE80))) {
        return;
    }
    name[0] = 0;
    len = 0;
    for (i = 0; i <= 62; i++) {
        char c = path[i];
        if (c == '\\') {
            if (len == 0) {
                continue;
            }
            name[len] = 0;
            for (step = 0; step <= 3;) {
                switch (step) {
                case 0:
                    DAT_06050668 = 0;
                    step = 1;
                case 1:
                    if (!GfsStepBegin(3)) {
                        return;
                    }
                    fid = GFS_NameToId((Sint8*)func_06006E14(path));
                    result = GfsStep(fid);
                    break;
                case 2:
                    result = func_060062F8(fid, &dir->tbl);
                    break;
                default:
                    if (!GfsStepBegin(2)) {
                        return;
                    }
                    result = GfsStep(GFS_SetDir(&dir->tbl));
                    break;
                }
                if (result == 1) {
                    DAT_06050668 = 0;
                    step++;
                } else if (result == 0) {
                    return;
                }
            }
            len = 0;
        } else if (c == 0) {
            break;
        } else {
            name[len++] = c;
        }
    }
    func_06006E4C(path, (char*)DAT_0605060C);
}

static void LoadListStart(s32 index) {
    DAT_0605AE90.unk8 = DAT_06038BCC[index];
    DAT_0605AE90.unk4 = 0;
}

static char* PlayerFile(s32 k) {
    if (DAT_0605CEAC != 0 && g_PlayableCharacter == 1) {
        return DAT_06038BF4[9 + k];
    }
    return DAT_06038BF4[g_PlayableCharacter * 3 + k];
}

static const char* StageMapFile(void) {
    u16 stage = g_CurrentRoom.stageID;
    s32 reverse = stage & 0x20;

    if (D_8003C730 == 0) {
        g_CurrentRoom.unk8 = 0;
        if ((stage & 0xDF) == 9) {
            if ((u32)D_8006C374 > 11) {
                g_CurrentRoom.unk8 = 1;
            }
            return DAT_06048178[(reverse ? 13 : 4) + g_CurrentRoom.unk8];
        }
        if ((stage & 0xDF) == 6) {
            if (D_8006C374 == 6 || D_8006C374 == 0x29) {
                g_CurrentRoom.unk8 = 1;
            }
            return DAT_06048178[(reverse ? 9 : 0) + g_CurrentRoom.unk8];
        }
    } else {
        if ((stage & 0xDF) == 9) {
            return DAT_06048178[(reverse ? 13 : 4) + g_CurrentRoom.unk8];
        }
        if ((stage & 0xDF) == 6) {
            return DAT_06048178[(reverse ? 9 : 0) + g_CurrentRoom.unk8];
        }
        if ((stage & 0xDF) == 3) {
            return DAT_06048178[(reverse ? 16 : 7) + g_CurrentRoom.unk8];
        }
    }
    if ((u32)(D_8006C374 - 0xA8) <= 1) {
        g_CurrentRoom.unk8 = 1;
        return DAT_06048178[3];
    }
    return g_StageFileRecords[stage].map;
}

s32 QueueVramTransfer(u32 dst, void* src, s32 size) {
    s32 i;

    for (i = 0; i < DAT_06057770; i++) {
        if (DAT_060576B0[i].src == src && DAT_060576B0[i].dst == dst &&
            DAT_060576B0[i].size == size) {
            return 1;
        }
    }
    if (DAT_06057770 > 15) {
        return 0;
    }
    DAT_060576B0[i].src = src;
    DAT_060576B0[i].dst = dst;
    DAT_060576B0[i].size = size;
    DAT_06057770++;
    return 1;
}

void FlushVramTransfers(void) {
    s32 i;

    for (i = 0; i < DAT_06057770; i++) {
        DMA_ScuMemCopy(satz_bus_pointer(DAT_060576B0[i].dst),
                       DAT_060576B0[i].src, DAT_060576B0[i].size);
        while (DMA_ScuResult() == 2) {
        }
    }
}

static void FadeColors(
    s16 fromR, s16 fromG, s16 fromB, s16 toR, s16 toG, s16 toB) {
    DAT_06057774[0] = fromR;
    DAT_06057774[1] = fromG;
    DAT_06057774[2] = fromB;
    DAT_06057774[3] = toR;
    DAT_06057774[4] = toG;
    DAT_06057774[5] = toB;
}

static void ColorOffsetSet(s16 value) {
    DAT_0605778C = value;
    DAT_0605778A = value;
    DAT_06057788 = value;
}

void func_06009CCC(void) {
    UNK_0605c680* cam = &DAT_0605c680;
    s32 oldX = cam->unk4;
    s32 oldY = cam->unkC;
    s32 x = g_Tilemap.scrollX.i.hi << 16;
    s32 y = g_Tilemap.scrollY.i.hi << 16;

    cam->unk8 = oldX;
    cam->unk10 = oldY;
    cam->unk4 = x;
    cam->unk3C = cam->unk34;
    cam->unkC = y;
    cam->unk40 = cam->unk38;
    cam->unk34 = (DAT_0605C100 << 16) + x;
    cam->unk38 = (DAT_0605CD80 << 16) + y;
    cam->unk18 = cam->g_ScrollDeltaX;
    cam->g_ScrollDeltaX = x - oldX;
    cam->unk20 = cam->g_ScrollDeltaY;
    cam->g_ScrollDeltaY = y - oldY;
}

u16 func_0600A77C(u16 frame, u16 mode, SaturnSpriteImage* images) {
    u8* record;
    u8* slot;
    s32 i, j, k;
    s32 second = 0;
    s32 alt, keep;
    u16 bank;

    if (mode == 0) {
        for (i = 0; i < 2; i++) {
            slot = (u8*)DAT_0605D910 + i * 0x124 + 0xA8;
            for (k = 0; k < 3; k++, slot += 0x24) {
                for (j = REC16(slot, 0xC); j <= 4; j++) {
                    REC16(slot, 0x10 + j * 2) = 0xFFFF;
                }
                REC32(slot, 8) = 0;
                REC16(slot, 0xE) = 0;
                REC16(slot, 0xC) = 0;
            }
            if (DAT_060579A4 == 0) {
                break;
            }
        }
        return 0;
    }
    if (mode & 0x10) {
        second = 1;
        if (DAT_060579A4 == 0) {
            return 0xFFFF;
        }
        record = (u8*)DAT_0605D910 + 0x124;
    } else {
        record = (u8*)DAT_0605D910;
    }
    if (mode & 0x40) {
        u16* keys = (u16*)(record + 0x14 + (mode & 15) * 20);
        for (i = 0; i < 5; i++) {
            if (keys[i] == frame) {
                return keys[i + 5];
            }
        }
        return 0xFFFF;
    }
    keep = (mode >> 5) & 1;
    bank = mode & 15;
    alt = 0;
    if (bank == 6) {
        bank = 3;
        alt = 1;
    } else if (bank == 5) {
        alt = 1;
        bank = 1;
    }
    if (bank != 1) {
        if (bank < 1 || bank > 4) {
            return 0;
        }
        slot = record + (alt ? 0xF0 : 0xA8);
        if (REC16(record, 2) == bank) {
            REC16(slot, 0xC)++;
            return (u16)((u16)((u32)REC32(slot, 4) >> 3) +
                         (s16)images->characterOffsetUnits);
        }
        if (REC16(record, 2) == 1) {
            func_0600AA18(second ? 2 : 0);
        }
        func_0600A650(record, frame, bank, second);
        REC16(record, 2) = bank;
        return (u16)((u16)((u32)REC32(slot, 4) >> 3) +
                     (s16)images->characterOffsetUnits);
    }
    slot = record + 0xA8;
    if (DAT_060579A0 != 0) {
        REC32(slot, 8) = 0;
        REC16(slot, 0xC) = 0;
        REC16(slot, 0xE) = 0;
    }
    if (alt) {
        slot = record + 0xCC;
        if (DAT_060579A0 != 0) {
            REC32(slot, 8) = 0;
            REC16(slot, 0xC) = 0;
            REC16(slot, 0xE) = 0;
        }
    }
    DAT_060579A0 = 0;
    i = REC16(slot, 0xC);
    if (!keep && REC16(record, 2) == 1 && REC16(slot, 0xE) == 0 &&
        REC16(slot, 0x10 + i * 2) == frame) {
        u16 ret = REC16(slot, 0x1A + i * 2);
        REC16(record, 0xB4)++;
        REC16(record, 0xD8)++;
        return ret;
    }
    REC32(record, 8) = REC32(record, 4);
    if (second) {
        i = (u16)func_0600A350(record, frame, alt, (u16*)images);
    } else {
        i = (u16)func_0600A490(record, frame, alt, g_PlayableCharacter);
    }
    REC16(record, 2) = 1;
    return i;
}

void func_0600AB60(void) {
    s32 i;

    for (i = 0; i <= 6; i++) {
        ((s32*)DAT_0605D910)[35 + i] = SLOT_VRAM(i + 3);
    }
    ((s32*)DAT_0605D910)[43] = SLOT_VRAM(3);
    ((s32*)DAT_0605D910)[42] = 0x8C00;
    ((s32*)DAT_0605D910)[52] = SLOT_VRAM(2);
    ((s32*)DAT_0605D910)[51] = 0x1400;
    ((s32*)DAT_0605D910)[61] = SLOT_VRAM(6);
    ((s32*)DAT_0605D910)[60] = 0x5000;
    if (DAT_06064668 != NULL) {
        ((s32*)DAT_0605D910)[69] = DAT_06064668[1].sourceOffset;
        ((s32*)DAT_0605D910)[70] = DAT_06064668[1].byteCount;
        ((s32*)DAT_0605D910)[71] = DAT_06064668[2].sourceOffset;
        ((s32*)DAT_0605D910)[72] = DAT_06064668[2].byteCount;
    }
}

void InitPaletteRemapLuts(void) {
    s32 i;

    memset(DAT_0605D910, 0, 0x248);
    func_0600AA18(0);
    func_0600AA18(2);
    for (i = 0; i <= 0xFF; i++) {
        DAT_060577A0[i] = i;
        DAT_060578A0[i] = 0;
    }
    for (i = 10; i <= 0xFF; i += 0x10) {
        DAT_060577A0[i] = (u16)i & 0xF0;
        DAT_060578A0[i] = 10;
    }
    for (i = 0; i <= 0xF; i++) {
        DAT_060577A0[0xA0 + i] = i;
        DAT_060578A0[0xA0 + i] = 0xA0;
    }
    DAT_060577A0[0xAA] = 0;
    DAT_060578A0[0xAA] = 0xAA;
}

s16 func_0600AE30(u8* data, SaturnSpriteImage* images, s32 colorMode) {
    u16 size[2];
    s16 first;

    size[0] = images->storedWidth * 2;
    size[1] = images->storedHeight * 2;
    first = AllocSpriteCharVram((u16)colorMode, 0, size, data);
    for (images++; images->storedWidth != 0; images++) {
        size[0] = images->storedWidth * 2;
        size[1] = images->storedHeight * 2;
        AllocSpriteCharVram(
            (u16)colorMode, 0, size,
            data != NULL ? data + images->characterOffsetUnits * 8 : NULL);
    }
    return first;
}

s16 func_0600AEE4(u16* palettes) {
    u16 header = palettes[0];
    s32 count = header & 0x0FFF;
    s32 i;
    u16 first;

    if ((header & 0xF000) == 0x4000) {
        first = func_06007B8C((s16*)(palettes + 1));
        for (i = 1; i < count; i++) {
            func_06007B8C((s16*)(palettes + 1 + i * 16));
        }
    } else if ((header & 0xF000) == 0x2000) {
        first = func_06007BE0((s16*)(palettes + 1), 0);
        for (i = 1; i < count; i++) {
            func_06007BE0((s16*)(palettes + 1 + i * 16), 0);
        }
    } else {
        count = header;
        first = func_06007B34((SprLookupTbl*)(palettes + 1));
        for (i = 1; i < count; i++) {
            func_06007B34((SprLookupTbl*)(palettes + 1 + i * 16));
        }
    }
    return first;
}

SpriteObject* AllocSpriteObject(void) {
    SpriteObject* obj;

    if (g_SpriteObjectsInUse > 0xFF) {
        return NULL;
    }
    obj = g_SpriteObjectFreeList;
    g_SpriteObjectFreeList = obj->next;
    g_SpriteObjectsInUse++;
    obj->flags = 0;
    obj->slotAndStreamId &= 0xFF00;
    obj->rotate = 0;
    obj->scaleX = 0x40;
    obj->scaleY = 0x40;
    obj->unk0C = 0;
    obj->unk0D = 0x80;
    obj->zPriority = 0x80;
    obj->subPixelX = 0;
    obj->subPixelY = 0;
    obj->posX = 0x02000000;
    obj->posY = 0x01000000;
    return obj;
}

void func_0600B254(void) {
    SpriteObject* obj;
    SpritePart* part;
    s32 i;

    memset(g_SpriteObjectPool, 0, sizeof(SpriteObject) * 256);
    obj = g_SpriteObjectPool;
    g_SpriteObjectFreeList = obj;
    obj->slotAndStreamId = 0;
    for (i = 1; i <= 0xFF; i++) {
        obj[1].slotAndStreamId = i << 8;
        obj->next = obj + 1;
        obj++;
    }
    obj->next = NULL;
    g_SpriteListCount = 0;
    g_SpriteObjectsInUse = 0;

    memset(g_SpritePartPool, 0, sizeof(SpritePart) * SPRITE_PART_MAX);
    part = g_SpritePartPool;
    g_SpritePartFreeList = part;
    for (i = 1; i <= SPRITE_PART_MAX - 1; i++) {
        part->next = part + 1;
        part++;
    }
    part->next = NULL;
    g_SpritePartsInUse = 0;
    g_SpriteListHead = NULL;
    g_SpriteListTail = NULL;
    if (g_PlayableCharacter != 0) {
        ((s32*)DAT_0605D910)[3] = 1;
    }
    func_0600AA18(0);
    func_0600AA18(2);
    DAT_060579A4 = NULL;
}

void func_0600B4C4(SpriteObject* obj) {
    SprSpCmd cmd = {0};
    SaturnSpriteImage img;
    s32 pos[2];
    SpritePart* part = obj->parts;
    SaturnSpriteImage* images = obj->images;
    u32 mode = obj->unk0C;
    u32 stream = obj->slotAndStreamId;
    u32 slot, flags, charBase, clutBase, colorBank, count, z, halfBit, attr,
        draw, clut;
    u16 color;
    s32 ok;
    s32 i;

    if (stream & 0x80) {
        mode |= 0x8000;
    }
    stream &= 0x7F;
    DAT_060579A0 = 1;
    slot = obj->slotAndStreamId >> 8;
    if ((mode & 0x80) && ((slot ^ g_Timer) & 1)) {
        return;
    }
    if (mode & 0x8000) {
        cmd.grshAddr = SPR_2GourTblNoToVram(slot);
    } else if (mode & 8) {
        u32 shade = obj->unk0D >> 3;
        u32 r = (mode & 0x10) ? 16 : shade;
        u32 g = (mode & 0x20) ? 16 : shade;
        u32 b = (mode & 0x40) ? 16 : shade;
        u16 c = 0x8000 + (b << 10) + (g << 5) + r;

        SpGourTbl[slot].entry[3] = c;
        SpGourTbl[slot].entry[2] = c;
        SpGourTbl[slot].entry[1] = c;
        SpGourTbl[slot].entry[0] = c;
        cmd.grshAddr = SPR_2GourTblNoToVram(slot);
    }

    flags = obj->flags;
    charBase = obj->charBase;
    clutBase = obj->clutBase;
    pos[0] = obj->posX + (obj->subPixelX << 16) - (DAT_0605CD5C << 16);
    pos[1] = obj->posY + (obj->subPixelY << 16) - (DAT_0605C65C << 16);
    count = (flags >> 8) & 0x3F;
    colorBank = flags & 7;
    z = obj->zPriority;
    halfBit = clutBase & 0x4000;
    for (i = 0; i < (s32)count; i++, part = part->next) {
        attr = part->attributes;
        if (attr & 0x40) {
            continue;
        }
        img = images[part->imageIndex];
        if (stream != 0) {
            cmd.charAddr = func_0600A77C(part->imageIndex, stream, &img);
            if (cmd.charAddr == 0xFFFF) {
                continue;
            }
            if (flags & 8) {
                continue;
            }
        } else {
            cmd.charAddr = DAT_0605AEC0[charBase][0] + img.characterOffsetUnits;
        }
        if ((flags & 0x40) || ((attr >> 13) & 1)) {
            ok = func_0600BA24(&cmd, obj, part, pos);
        } else {
            ok = func_0600B954(&cmd, obj, part, pos);
        }
        if (ok == 0) {
            continue;
        }

        draw = flags >> 14;
        if (draw == 0) {
            draw = (attr & 0xC000) >> 14;
        }
        draw |= halfBit ? 0x480 : 0x488;
        if ((flags & 0x80) || (attr & 0x80)) {
            draw |= 0x100;
        }
        if ((mode & 0x8008) && !halfBit) {
            draw |= 4;
        }
        cmd.drawMode = draw;

        clut = clutBase & 0x7FFF;
        if (!(clutBase >> 15)) {
            clut += (attr >> 8) & 0x1F;
        }
        if (clut & 0x4000) {
            color = LocalLookupTblNoToVram(clut & 0xFFF);
        } else {
            color = SPR_2LookupTblNoToVram(clut & 0xFFF);
        }
        if (halfBit) {
            color |= colorBank << 12;
        }
        cmd.color = color;
        cmd.charSize = (img.storedWidth << 6) | (img.storedHeight * 2);

        z += attr & 15;
        if (SpMstCmdPos <= 0x277) {
            SPR_2Cmd(z, &cmd);
            d_0605AEAC++;
        }
    }
}

s32 func_0600B954(
    SprSpCmd* cmd, SpriteObject* obj, SpritePart* part, s32* pos) {
    u16 flags = obj->flags;
    u16 attributes = part->attributes;
    SaturnSpriteImage image = obj->images[part->imageIndex];
    s32 x = (s16)(pos[0] >> 16) - image.storedWidth;
    s32 y = (s16)(pos[1] >> 16) - image.storedHeight;

    x += (flags & 0x10) ? -part->offsetX : part->offsetX;
    y += (flags & 0x20) ? -part->offsetY : part->offsetY;
    cmd->ax = x;
    cmd->ay = y;
    if (x > 319 || x + image.storedWidth * 2 <= 0 || y > 239 ||
        y + image.storedHeight * 2 <= 0) {
        return 0;
    }
    cmd->control = ((flags ^ attributes) & 0x30) | 0x1000;
    return 1;
}

void func_0600C2EC(void) {
    SaturnSpriteResource* bank;
    s32 i;
    u16 slot;
    u16 table;

    DAT_0605AEA8 = DAT_06038FD6;
    DAT_0605AEB0 = DAT_06038FD8;
    for (i = 0; (bank = DAT_060645EC[i]) != NULL; i++) {
        if (bank->palettes != NULL) {
            bank->flags = func_0600AEE4(bank->palettes);
        }
    }
    slot = g_SaturnSharedSpriteBank0Resource.flags + 15;
    if (slot & 0x4000) {
        table = LocalLookupTblNoToVram(slot & 0x0FFF);
    } else {
        table = SPR_2LookupTblNoToVram(slot & 0x0FFF);
    }
    DAT_06038DBC = table * 8 + 0x25C00000;
}

void func_0600C6E4(s32 arg0) {
    s32 i;

    if (arg0 == 0) {
        func_0600C99C((u16*)g_StageOvlArea, 0x13B00, 0x3600);
        func_06008524(0x25F00600, g_StageOvlArea, 0x200);
        QueueVramTransfer(VRAM_ADDR + SPR_2LookupTblNoToVram(16) * 8,
                          g_StageOvlArea + 0x200, 32);
        QueueVramTransfer(
            VRAM_ADDR + DAT_0605AEC0[2][0] * 8, g_StageOvlArea + 0x300, 0x2380);
    } else if (arg0 == 1) {
        func_0600C99C((u16*)g_WorkBuffer.load.data, 0x13B00, 0x2D00);
        for (i = 0; i <= 1; i++) {
            if (i == 0) {
                QueueVramTransfer(VRAM_ADDR + SPR_2LookupTblNoToVram(16) * 8,
                                  g_WorkBuffer.load.data + 0x220, 32);
            } else {
                QueueVramTransfer(VRAM_ADDR + DAT_0605AEC0[2][0] * 8,
                                  g_WorkBuffer.load.data + 0x2680, 0x600);
            }
        }
    }
}

static void sotn_satz_cmd_offset_vertex(SprSpCmd* cmd, s32 i, s16 dx, s16 dy) {
    switch (i) {
    case 0:
        cmd->ax -= dx;
        cmd->ay -= dy;
        break;
    case 1:
        cmd->bx -= dx;
        cmd->by -= dy;
        break;
    case 2:
        cmd->cx -= dx;
        cmd->cy -= dy;
        break;
    case 3:
        cmd->dx -= dx;
        cmd->dy -= dy;
        break;
    }
}

void func_0600DE38(void) {
    Primitive* prim;
    SprSpCmd cmd;
    SprSpCmd* emitted;
    u32 flags = 0;
    s32 start, end, accept, type = 0;
    s32 i, j;
    u16 gour;

    if (DAT_0605CD5C == 0 && DAT_0605C65C == 0) {
        flags = 0x80000000;
    }
    start = SpMstCmdPos;
    if (DAT_0605C6D8.a >= 0) {
        func_06009010((u8*)&DAT_0605C6D8);
        DAT_0605C6D8.a--;
    }
    for (i = 0, prim = g_PrimBuf; i < 0x200; i++, prim++) {
        flags = (flags & 0xFFFF0000) | prim->drawMode;
        if (flags & 8) {
            continue;
        }
        accept = 1;
        if (!(flags & 0x800)) {
            type = prim->type & 0xF;
            accept = DAT_0603904C[type](prim);
        }
        if (!accept) {
            continue;
        }
        emitted = d_0605AEAC;
        if (SpMstCmdPos <= 0x277) {
            cmd.control = prim->type;
            cmd.link = prim->priority;
            cmd.drawMode = prim->unk4;
            cmd.color = prim->unk6;
            cmd.charAddr = prim->unk8;
            cmd.charSize = prim->unkA;
            cmd.ax = prim->x0;
            cmd.ay = prim->y0;
            cmd.bx = prim->x1;
            cmd.by = prim->y1;
            cmd.cx = prim->x2;
            cmd.cy = prim->y2;
            cmd.dx = prim->x3;
            cmd.dy = prim->y3;
            cmd.grshAddr = prim->unk1C;
            cmd.dummy = prim->drawMode;
            SPR_2Cmd((u16)prim->priority, &cmd);
            d_0605AEAC++;
        }
        if (flags & 0x80002080) {
            continue;
        }
        for (j = 0; j < DAT_0603900C[type]; j++) {
            sotn_satz_cmd_offset_vertex(
                emitted, j, (s16)DAT_0605CD5C, (s16)DAT_0605C65C);
        }
    }
    end = SpMstCmdPos;
    gour = SPR_2GourTblNoToVram(0);
    for (i = start; i < end; i++) {
        SpMstCmd[i].grshAddr += gour;
    }
}

s32 rsin(s32 angle) {
    s32 a = angle & 0xFFF;

    if (a <= 0x3FF) {
        return rsin_tbl[a];
    }
    if (a <= 0x7FF) {
        return rsin_tbl[0x7FF - a];
    }
    if (a <= 0xBFF) {
        return -rsin_tbl[a - 0x800];
    }
    return -rsin_tbl[0xFFF - a];
}

s32 rcos(s32 angle) {
    s32 a = angle & 0xFFF;

    if (a <= 0x3FF) {
        return rsin_tbl[0x3FF - a];
    }
    if (a <= 0x7FF) {
        return -rsin_tbl[a - 0x400];
    }
    if (a <= 0xBFF) {
        return -rsin_tbl[0xBFF - a];
    }
    return rsin_tbl[a - 0xC00];
}

void rsincos(s32 angle, s32* sinOut, s32* cosOut) {
    s32 a = angle & 0xFFF;

    if (a <= 0x3FF) {
        *sinOut = rsin_tbl[a];
        *cosOut = rsin_tbl[0x3FF - a];
    } else if (a <= 0x7FF) {
        *sinOut = rsin_tbl[0x7FF - a];
        *cosOut = -rsin_tbl[a - 0x400];
    } else if (a <= 0xBFF) {
        *sinOut = -rsin_tbl[a - 0x800];
        *cosOut = -rsin_tbl[0xBFF - a];
    } else {
        *sinOut = -rsin_tbl[0xFFF - a];
        *cosOut = rsin_tbl[a - 0xC00];
    }
}

u32 SquareRoot0(s32 value) {
    u32 x = value;
    u32 bits, root, step, next;

    if (x == 0) {
        return 0;
    }
    bits = 1;
    for (step = x; step > 1; step >>= 1) {
        bits++;
    }
    root = 1u << ((bits - 1) >> 1);
    for (step = root >> 1; step != 0; step >>= 1) {
        next = root + step;
        if (next * next <= x) {
            root = next;
        }
    }
    return root;
}

static void SoundSetRequest(s32 fx) {
    func_0601269C();
    if (DAT_06064354 == 0) {
        DAT_06064354 = 2;
        DAT_06064324 = fx;
    }
}

static void SoundSetRequest2(s32 fx) {
    func_060126B8();
    if (DAT_060644AC == 0) {
        DAT_060644AC = 2;
    }
    DAT_06064324 = fx;
}

static void SoundPlayConfig(s32 channel, s32 config) {
    SaturnSoundConfig* c = &g_SaturnSoundConfigs[config];
    SND_StartSeq_DR(channel, c->unk0, c->unk3, c->unk4);
}

static void PlaySfxCommand(s32 cmd) {
    if (DAT_06064300 != 0) {
        func_0601298C();
    }
    DAT_060642F8 = cmd;
    DAT_06064300 = 1;
    DAT_0606433C = 1;
    DAT_06064334 = 0;
    DAT_06063BD8 = 0;
    DAT_06064430 = 0;
    switch (g_SaturnSoundCommands[cmd].unk0) {
    case 0:
        DAT_06064394 = -1;
        break;
    case 2:
        DAT_0606435C = 1;
        DAT_060642E4 = 0;
        DAT_060643CC = 0;
        break;
    default:
        DAT_06064394 = 0;
        break;
    }
}

static void PlaySfxFadeAll(s32 withLast) {
    func_06011A6C(0xFE000090);
    DAT_060643A0 = 1;
    func_06011A6C(0xFE000001);
    func_06011A6C(0xFE000002);
    func_06011A6C(0xFE000003);
    func_06011A6C(0xFE000004);
    func_06011A6C(0xFE000005);
    if (withLast) {
        func_06011A6C(0xFE000006);
    }
}

static void PlaySfxFade(s32 frames, s32 volumeFrames) {
    DAT_06064428 = frames;
    DAT_060642F4 = volumeFrames;
    PlaySfxFadeAll(1);
}

s32 func_06012C4C(u8 id, s32 offset) {
    u32 entry = 0x25A00500;
    s32 want = id + offset;

    if (id != 0xFF) {
        while (HW_READ8(entry) != want) {
            if (HW_READ8(entry) == 0xFF) {
                return 0;
            }
            entry += 8;
        }
    }
    return 0x25A00000 + ((HW_READ8(entry + 1) << 16) |
                         (HW_READ8(entry + 2) << 8) | HW_READ8(entry + 3));
}

static s16 RingOffset(s32 trig, s32 radius) {
    return (s16)(trig * radius / 320);
}

void func_06019A7C(s32* ring_, s32 x_, s32 y_, s32 stop) {
    LoadingRing* ring = (LoadingRing*)ring_;
    s16 x = (s16)x_, y = (s16)y_;
    SprSpCmd cmd;
    s32 i, next;
    s16 ax, ay, bx, by;

    switch (ring->state) {
    case 0:
        for (i = 0; i <= 19; i++) {
            ring->angle[i] = i << 8;
            DAT_06057CD0[i] = i * 8 + 0xA0;
            DAT_06057D20[i] = (i + 1) * 8 + 0xA0;
        }
        ring->x = x;
        ring->y = y;
        ring->unkC = 0;
        ring->radiusX = 4;
        ring->radiusY = 4;
        ring->unk12 = 0;
        ring->angleStep = 32;
        ring->state++;
        break;
    case 1:
        if (stop != 0) {
            ring->state = 0;
            return;
        }
        if ((g_pads[0].pressed & 0x1000) && ++ring->radiusX > 64) {
            ring->radiusX = 64;
        }
        if ((g_pads[0].pressed & 0x2000) && --ring->radiusX < -64) {
            ring->radiusX = -64;
        }
        if ((g_pads[0].pressed & 0x8000) && ++ring->radiusY > 64) {
            ring->radiusY = 64;
        }
        if ((g_pads[0].pressed & 0x4000) && --ring->radiusY < -64) {
            ring->radiusY = -64;
        }
        break;
    }

    for (i = 0; i <= 19; i++) {
        cmd.control = 0x1002;
        cmd.drawMode = 0x1488;
        cmd.color = SPR_2LookupTblNoToVram(16);
        cmd.charAddr = DAT_0605AEC0[2][0] + i * 12;
        cmd.charSize = 0x118;
        ay = RingOffset(-(rsin(ring->angle[i]) >> 5), ring->radiusX);
        ax = RingOffset(rcos(ring->angle[i]) >> 5, ring->radiusY);
        next = (i + 1) % 20;
        by = RingOffset(-(rsin(ring->angle[next]) >> 5), ring->radiusX);
        bx = RingOffset(rcos(ring->angle[next]) >> 5, ring->radiusY);
        cmd.ax = (s16)DAT_06057CD0[i] + ring->x + ax - 160;
        cmd.bx = (s16)DAT_06057D20[i] + ring->x + bx - 160;
        cmd.cx = cmd.bx;
        cmd.dx = cmd.ax;
        cmd.ay = ring->y + ay;
        cmd.by = ring->y + by;
        cmd.cy = by + 0x18 + ring->y;
        cmd.dy = ay + 0x18 + ring->y;
        ring->angle[i] += ring->angleStep;
        if (SpMstCmdPos <= 0x277) {
            SPR_2Cmd(0x80, &cmd);
            d_0605AEAC++;
        }
    }
    cmd.control = 0x1000;
    cmd.drawMode = 0x4A0;
    cmd.color = 0x300;
    cmd.charAddr = DAT_0605AEC0[2][0] + 0xF0;
    cmd.charSize = 0x1038;
    cmd.ax = 0xA8;
    cmd.ay = 0xA0;
    if (SpMstCmdPos <= 0x277) {
        SPR_2Cmd(127, &cmd);
        d_0605AEAC++;
    }
}

void func_0601AC48(void) {
    void** tables = (void**)&g_StageOverlayData.layerCompressedSizes;

    switch (g_CurrentRoom.stageID & 0xDF) {
    case 0x03:
    case 0x06:
    case 0x09:
    case 0x0B:
        tables += g_CurrentRoom.unk8 * 5;
        break;
    }
    DAT_0606459C = (u8*)g_StageOverlayData.rooms;
    DAT_060645F4 = tables[0];
    DAT_06064654 = tables[1];
    DAT_0606466C = tables[2];
    DAT_060645C8 = tables[3];
    DAT_060645B8 = tables[4];
}

void func_06030DF0(void) {}

#include <stdarg.h>
