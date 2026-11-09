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

extern s32 DAT_060643BC;
extern s32 DAT_06064224;
extern s32 DAT_06063BEC;
extern s32 DAT_06064428;
void func_06011A6C(s32 arg0);
void func_0601298C(void);

extern u16 DAT_06039414[];
extern u32 D_06041270[4];
extern u32 D_06041288;
extern s32 DAT_06062254;
extern s32 DAT_06063C24;
extern s32 DAT_06064204;
extern s32 DAT_060642CC;
extern CdcStat DAT_060644D0;
extern Uint8* snd_adr_sys_int_work;

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

extern s32 DAT_06057C3C;
extern s32 DAT_06057C40;
extern s32 DAT_06057C38;
extern s32 DAT_060642E0;
s32 func_06016B9C(GfsHn gfs, void* dst, s32 size);

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
extern s8 DAT_0606225C;
extern s16 DAT_06064228;
extern s32 DAT_06063E74;
extern s16 DAT_06062264;
extern s32 DAT_06063BF4;
extern s32 DAT_06062368;
extern s32 DAT_0606224C;
extern s32 DAT_06062230[2];
extern s32 DAT_06062380[2];
extern s32 DAT_06063E7C;
extern s32 DAT_06064200;
extern u32 DAT_06063EAC;
extern s32 DAT_060642E0;
extern s32 DAT_06063C04;
extern s32 DAT_060641F8;
extern u32 DAT_06063BE8;
extern u32 DAT_0606421C;
extern SndPcmChgPrm DAT_060643B0;
extern s32 DAT_060440F8;
extern s32 DAT_060440FC;
extern s32 DAT_06064340;
extern u32 DAT_0606420C;
extern s32 DAT_06062254;
extern u16 g_SaturnSoundValues512[512];
extern SndPcmChgPrm DAT_06064440;
extern s32 DAT_06044110;
extern s32 DAT_06044114;
extern s32 DAT_06043C4C;
extern s32 DAT_06063BF0;
extern s32 DAT_06064204;
extern SndSeqStat DAT_06064478;

void func_06012474(void);
void func_060145F8(u8* arg0, s32 arg1, s32 arg2, s16 arg3, s32 arg4, s32 arg5);
void func_06014658(u8* arg0, s32 arg1, s32 arg2, s32 arg3);
void func_060146A4(u8* arg0, s32 arg1, s32 arg2, s16 arg3, s16 arg4, s32 arg5,
                   s32 arg6, s32 arg7, s32 arg8);
void func_06014724(u8* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_060120A0(void);
void func_06013538(u8* arg0, u16* arg1, u16* arg2, u32 arg3, s16* arg4,
                   s16* arg5, s32* arg6, s32* arg7);
s32 func_06014C20(void);
s32 func_06017F28(void);
void func_06016614(void);
void func_06016D84(void);
void func_06016E84(void);
void func_060174D8(void);
void func_06011F58(void);
void func_06012054(void);
void func_06012954(void);
s32 func_06011B28(s32 arg0);
s32 func_06014F3C(s32 arg0);
s32 func_06015140(s32 arg0);
s32 func_060155CC(s32 arg0);
void func_06015E68(void);
void func_06016644(void);
s32 func_06016C60(void);
s32 func_0601701C(s32 arg0);
s32 func_06018034(s32 arg0);

#define PCM_SRC_SIZE 0x6000
#define PCM_RING_SIZE 0xC000

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
static void MusicBankFlag(s32 music, s8 value);
s32 func_060129BC(s32 arg0);
s32 func_06012C4C(u8 id, s32 offset);

void func_060133CC(u8* src, u32* dst, u32 count, s16* pred, s32* index);
void func_060139C4(void);
s32 func_0601476C(s32 arg0);
s32 func_06014B80(s32 arg0);
s32 func_06014D44(u32 arg0);
static u8* PcmBuf(s32 i);

static u8* PcmSrcAddr(u32 pos);
static void ClearPcmSlot(u32 x);
static void StartPcmChannel7(void);
static void QueueSplit(void);
static void ClearSoundRam(u32 addr, u32 n);
static void slave_snd_ram_copy(u8* dst, const void* src, u32 count);

static void slave_snd_ram_clear(u8* dst, u32 count);
void sotn_snd_ram_copy(u8* dst, const void* src, u32 count);
static void slave_pcm_refill(s32 remain);
static void slave_pcm_rewind(void);
static void slave_pcm_ring_mark(void);
void sotn_snd_ram_clear(u8* dst, u32 count);

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

void func_06010400(void) {
    s32 cmd, i, result, mode;

    if (DAT_060644C5 == 0) {
        if (DAT_06064398 != 0) {
            DAT_06064398--;
        } else if ((u8)DAT_060644A0 != 0) {
            DAT_060644A0--;
        } else {
            DAT_060644C5 = 1;
            func_060125EC();
        }
    }
    if (DAT_060644A8 != 0) {
        if (DAT_06064420 != 0) {
            DAT_06064420--;
        } else {
            SND_StopSeq(7);
            DAT_060644A8 = 0;
        }
    }
    if (DAT_06064401 != 0) {
        if (DAT_060642D8 != 0) {
            DAT_060642D8--;
        } else {
            SND_StopSeq(6);
            DAT_06064401 = 0;
        }
    }
    if (DAT_060643C7 != 0) {
        SND_SetSeqPan(7, 0, (u8)DAT_0606436E);
        DAT_060643C7 = 0;
    }
    if (DAT_0606440C != 0) {
        SND_SetSeqPan(6, 0, (u8)DAT_060644E6);
        DAT_0606440C = 0;
    }
    if (DAT_06064354 == 2) {
        func_060126D4(1);
        DAT_06064354 = 3;
    }
    if (DAT_06064354 == 3) {
        func_060126D4(0);
    }
    if (DAT_060644AC == 2) {
        func_060127F0(1);
        DAT_060644AC = 3;
    }
    if (DAT_060644AC == 3) {
        func_060127F0(0);
    }
    if (DAT_060641D8 == 1) {
        if (DAT_06063BEC != 0) {
            SND_ChgMixPrm(0, 0, 31);
            SND_ChgMixPrm(1, 0, 15);
            func_060129BC(1);
            DAT_06063BEC = 0;
        }
        result = func_060129BC(0);
        D_06041270[2] = result;
        if (result == -1) {
            DAT_060641D8 = 0;
        }
        if (result == 0) {
            DAT_060641D8 = 0;
        }
    }
    if (DAT_0606440D != 0) {
        return;
    }

    cmd = DAT_06064250[0];
    if (cmd == 0 || DAT_06064414 != DAT_0606423A) {
        return;
    }
    for (i = 0; i <= 30; i++) {
        DAT_06064250[i] = DAT_06064250[i + 1];
    }
    DAT_060642CC = 0;

    if ((u32)(cmd - 1) <= 0x2FF) {
        if (DAT_06064214 == 0 && DAT_06063BE0 == 0) {
            if (DAT_06062280 == 0) {
                return;
            }
            if ((u32)cmd >=
                (((u32)DAT_06039414[2] << 16) | DAT_06039414[3]) + 1) {
                return;
            }
            DAT_06062254 = cmd;
            DAT_06064214 = 1;
            DAT_06064204 = 1;
            DAT_060623BC = 0;
            DAT_06062248 = 0;
            DAT_0606423C = 0;
            DAT_06064350 = 0;
            DAT_060642E8 = 0;
            DAT_060644C2 = 0;
            DAT_06063BD8 = 0;
        } else if (DAT_060641DC == 0 || DAT_06064210 == 0) {
            DAT_060641DC = cmd;
            DAT_06064210 = 0;
        }
        return;
    }
    if ((u32)(cmd + 0x20000000) <= 0x00FFFFFF) {
        if (DAT_06062258 != cmd) {
            if (DAT_06062258 == -1) {
                DAT_0606422C = 0;
                DAT_06063C18 = 0;
            }
            DAT_06062258 = cmd;
            DAT_060641E0 = 1;
            DAT_06063BE0 = 1;
            DAT_060641F4 = 0;
            DAT_06063EB4 = 0;
            DAT_06062248 = 0;
            DAT_060644C1 = 0;
            DAT_060644DC = 0;
            DAT_06064400 = 0;
            DAT_06064330 = 0;
            DAT_060644C5 = 1;
            DAT_06064398 = 0;
            DAT_06064474 = 0;
            DAT_06064378 = 0;
            DAT_0606442C = 0;
            if (func_06012DFC() != 0) {
                DAT_06063BFC = 1;
                DAT_060641DC = 0;
                DAT_06064210 = 0;
                DAT_06062248 = 0;
                DAT_060642E8 = 0;
                DAT_060644C2 = 0;
            }
            DAT_06063BD8 = 0;
        }
        DAT_06063C24 = 0;
        return;
    }

    switch ((u32)cmd) {
    case 0xF0000001:
        DAT_06064388 = 1;
        break;
    case 0xF0000002:
        DAT_06064388 = 2;
        break;
    case 0xF0000005:
        HW_WRITE8(snd_adr_sys_int_work + 3, 0x80);
        break;
    case 0xF0000006:
        HW_WRITE8(snd_adr_sys_int_work + 3, 0);
        break;
    case 0xF000000A:
        DAT_06063BD0 = 1;
        DAT_06063EB4 = 0;
        DAT_06064400 = 0;
        DAT_06064330 = 0;
        DAT_060644C5 = 1;
        DAT_06064398 = 0;
        DAT_06063BD8 = 0;
        DAT_06063BFC = 1;
        DAT_060641DC = 0;
        DAT_06064210 = 0;
        DAT_06062248 = 0;
        break;
    case 0xF0000010:
        if (DAT_06063BE0 != 0) {
            DAT_06064474 = 1;
            DAT_06064378 = 0;
            DAT_060644C5 = 1;
            func_060122C0(10);
        } else if (DAT_06064214 != 0) {
            DAT_060642E8 = 1;
            DAT_060644C2 = 0;
            func_060123D4(10);
        } else {
            DAT_06064474 = 0;
            DAT_06064378 = 0;
        }
        break;
    case 0xF0000011:
        if (DAT_06062248 != 0) {
            DAT_060644C2 = 1;
            DAT_060642E8 = 0;
            func_06012428(10);
            break;
        }
        if (DAT_06064214 != 0 || DAT_06064330 == 0) {
            break;
        }
        CDC_GetCurStat(&DAT_060644D0);
        if ((DAT_060644D0.status & 0xF) == 2) {
            DAT_06064398 = 80;
        }
        if (DAT_0606440E != 0) {
            DAT_06064398 = 100;
            DAT_0606440E = 0;
        }
        func_06012358(10);
        DAT_06064378 = 1;
        DAT_06064474 = 0;
        DAT_06064330 = 0;
        break;
    case 0xF00000A1:
        SND_SetSeqVl(6, 1, 1);
        DAT_060642D8 = 150;
        DAT_06064401 = 1;
        break;
    case 0xF00000A2:
    case 0xF00000A3:
        SND_StopSeq(6);
        break;
    case 0xF00000A4:
        mode = DAT_060643E0[6];
        if ((u32)(mode - 0x2B4) <= 1 || mode == 0x2B6 || mode == 0) {
            break;
        }
        SoundPlayConfig(6, mode);
        DAT_0606440C = 1;
        break;
    case 0xF00000A5:
        SND_SetSeqVl(7, 1, 1);
        DAT_06064420 = 150;
        DAT_060644A8 = 1;
        DAT_060643E0[7] = 0;
        break;
    case 0xF00000A6:
        SND_StopSeq(7);
        DAT_060643E0[7] = 0;
        break;
    case 0xF00000A7:
        SND_StopSeq(7);
        break;
    case 0xF00000A8:
        if (DAT_060643E0[7] != 0) {
            SoundPlayConfig(7, DAT_060643E0[7]);
            DAT_060643C7 = 1;
        }
        break;
    case 0xF0000800:
        func_0601269C();
        if (DAT_06064354 == 0) {
            DAT_06064354 = 2;
        }
        break;
    case 0xF0000801:
        func_0601269C();
        break;
    case 0xF0000804:
        func_060126B8();
        if (DAT_060644AC == 0) {
            DAT_060644AC = 2;
        }
        break;
    case 0xF0000805:
        func_060126B8();
        break;
    case 0xF0000807:
        SoundSetRequest(0xF00000E0);
        break;
    case 0xF0000808:
        SoundSetRequest(0xF00000E1);
        break;
    case 0xF0000809:
        SoundSetRequest(0xF00000E2);
        break;
    case 0xF000080A:
        SoundSetRequest(0xF00000E3);
        break;
    case 0xF000080B:
        SoundSetRequest(0xF00000E4);
        break;
    case 0xF000080C:
        SoundSetRequest(0xF00000E5);
        break;
    case 0xF000080D:
        SoundSetRequest2(0xF00000D0);
        break;
    case 0xF000080E:
        SoundSetRequest2(0xF00000D1);
        break;
    case 0xF000080F:
        SoundSetRequest2(0xF00000D2);
        break;
    case 0xF0000810:
        SoundSetRequest(0xF00000E6);
        SoundSetRequest(0xF00000E7);
        break;
    case 0xF0000811:
        SoundSetRequest(0xF00000E7);
        break;
    case 0xF0000812:
        SoundSetRequest(0xF00000E8);
        break;
    case 0xFE000001:
        SND_SetSeqVl(0, 1, (u8)DAT_060643A0);
        SND_SetSeqVl(1, 1, (u8)DAT_060643A0);
        break;
    case 0xFE000002:
        SND_SetSeqVl(2, 1, (u8)DAT_060643A0);
        SND_SetSeqVl(3, 1, (u8)DAT_060643A0);
        break;
    case 0xFE000003:
        SND_SetSeqVl(4, 1, (u8)DAT_060643A0);
        SND_SetSeqVl(5, 1, (u8)DAT_060643A0);
        break;
    case 0xFE000004:
        SND_SetSeqVl(6, 1, (u8)DAT_060643A0);
        DAT_060642D8 = 150;
        DAT_06064401 = 1;
        break;
    case 0xFE000005:
        SND_SetSeqVl(7, 1, (u8)DAT_060643A0);
        DAT_06064420 = 150;
        DAT_060644A8 = 1;
        DAT_060643E0[7] = 0;
        break;
    case 0xFE000006:
        func_06012290(DAT_060642F4);
        break;
    case 0xFE000008:
        SND_StopSeq(0);
        SND_StopSeq(1);
        SND_StopSeq(2);
        SND_StopSeq(3);
        break;
    case 0xFE000009:
        SND_StopSeq(4);
        SND_StopSeq(5);
        SND_StopSeq(6);
        SND_StopSeq(7);
        DAT_060643E0[6] = 0;
        DAT_060643E0[7] = 0;
        if (DAT_060644C0 == 1) {
            DAT_060644C0 = 2;
        }
        break;
    case 0xFE00000A:
        DAT_0606435C = 1;
        break;
    case 0xFE00000E:
    case 0xFE00000F:
    case 0xFE000010:
    case 0xFE000011:
        func_060110C0();
        break;
    case 0xFE000090:
        if (DAT_06063BE0 == 5) {
            func_060121F0(DAT_06064428);
            DAT_0606442C = 1;
        } else if (DAT_06064214 == 5) {
            func_06012260(DAT_06064428);
        } else if (DAT_06063BE0 != 0) {
            DAT_06063BD0 = 1;
            DAT_06063EB4 = 0;
            DAT_06064400 = 0;
            DAT_06064330 = 0;
            DAT_060644C5 = 1;
            DAT_06064398 = 0;
            DAT_0606442C = 1;
        } else if (DAT_06064214 != 0) {
            DAT_06063BFC = 1;
            DAT_060641DC = 0;
            DAT_06064210 = 0;
            DAT_06062248 = 0;
            DAT_06063BD8 = 0;
        }
        break;
    }
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

void PlaySfx(s32 sfxId) {
    u32 id = sfxId;
    s32 music, sfx, voice;
    SaturnSoundConfig* config;
    s32 pending, i;
    u32 slot;

    if (id == 0x687) {
        DAT_0606440D = 1;
        return;
    }
    music = id - 0xB00;
    if ((u32)music <= 0xFF) {
        if (DAT_060641D8 != 0) {
            return;
        }
        DAT_060644C8 = func_06012C4C(g_SaturnSoundFiles[music].bank, 0);
        DAT_06064224 = music;
        DAT_06063BEC = 1;
        DAT_060641D8 = 1;
        DAT_06063BD8 = 0;
        return;
    }
    sfx = id - 0x600;
    if ((u32)sfx <= 0x3FF) {
        DAT_060643BC = sfx;
        config = &g_SaturnSoundConfigs[sfx];
        if (config->unk0 == 8) {
            if (DAT_06064300 != 0 && config->unk4 < (u8)DAT_060644C3) {
                return;
            }
            DAT_060644C3 = config->unk4;
            PlaySfxCommand(config->unk3);
            return;
        }
        pending = DAT_06064414 - DAT_0606423A;
        if (DAT_06064414 != DAT_0606423A && pending != 0) {
            for (i = 0; i != pending + 0x80; i++) {
                s32 back = DAT_06064414 - i;
                slot = back > 0 ? back - 1 : back + 0x7F;
                if (*(u16*)&DAT_06063ED0[slot][0] == (u32)DAT_060643BC) {
                    return;
                }
                if (i + 1 == DAT_06064414 - DAT_0606423A) {
                    break;
                }
            }
        }
        slot = DAT_06064414;
        *(u16*)&DAT_06063ED0[slot][0] = (u16)DAT_060643BC;
        if (DAT_060644C4 == 0) {
            DAT_06063ED0[slot][2] = 0;
            DAT_06063ED0[slot][3] = 64;
            DAT_06063ED0[slot][4] = 0;
        } else {
            DAT_06063ED0[slot][2] = (u8)DAT_06064230;
            DAT_06063ED0[slot][3] = (u8)DAT_060643C4;
            DAT_06063ED0[slot][4] = 1;
        }
        DAT_06064414++;
        if (DAT_06064414 == 0x80) {
            DAT_06064414 = 0;
        }
        return;
    }
    voice = (id & 0xFFF) - 0x581;
    if ((u32)voice <= 0x7E) {
        PlaySfxCommand((id & 0xFFF) - 0x580);
        return;
    }
    if (id != 0 && id <= 0x580) {
        func_06011A6C(id > 0x33C ? id - 0x33C : id);
        if (id > 0x33C) {
            id -= 0x33C;
        }
    }
    if (id + 0x20000000 <= 0x00FFFFFF) {
        func_06011A6C(id);
    }
    switch (id) {
    case 0xF0000001:
    case 0xF0000002:
    case 0xF0000005:
    case 0xF0000006:
    case 0xF000000A:
    case 0xF0000010:
    case 0xF0000011:
    case 0xF00000A1:
    case 0xF00000A2:
    case 0xF00000A3:
    case 0xF00000A4:
    case 0xF00000A5:
    case 0xF00000A6:
    case 0xF00000A7:
    case 0xF00000A8:
    case 0xF0000800:
    case 0xF0000801:
    case 0xF0000804:
    case 0xF0000805:
    case 0xF0000807:
    case 0xF0000808:
    case 0xF0000809:
    case 0xF000080A:
    case 0xF000080B:
    case 0xF000080C:
    case 0xF000080D:
    case 0xF000080E:
    case 0xF000080F:
    case 0xF0000810:
    case 0xF0000811:
    case 0xF0000812:
    case 0xFE00000A:
        func_06011A6C(id);
        break;
    case 0xF0000008:
        func_06011A6C(0xFE000008);
        func_06011A6C(0xFE000009);
        func_06011A6C(0xFE00000A);
        break;
    case 0xF000000B:
        func_06012FB4();
        func_06011A6C(0xFE00000A);
        func_06011A6C(0xF000000A);
        func_06011A6C(0xFE000008);
        func_06011A6C(0xFE000009);
        DAT_060644C0 = 1;
        break;
    case 0xF000000E:
        func_06011A6C(0xFE00000E);
        func_06011A6C(0xFE000010);
        break;
    case 0xF000000F:
        func_06011A6C(0xFE00000F);
        func_06011A6C(0xFE000011);
        break;
    case 0xF0000080:
        PlaySfxFade(10, 15);
        break;
    case 0xF0000081:
        PlaySfxFade(20, 40 / 3);
        break;
    case 0xF0000082:
        PlaySfxFade(60, 120 / 3);
        break;
    case 0xF0000083:
        PlaySfxFade(120, 240 / 3);
        break;
    case 0xF0000084:
        PlaySfxFade(180, 360 / 3);
        break;
    case 0xF0000090:
        DAT_06064428 = 10;
        func_06011A6C(0xFE000090);
        break;
    case 0xF0000091:
        DAT_06064428 = 20;
        func_06011A6C(0xFE000090);
        break;
    case 0xF0000092:
        DAT_06064428 = 60;
        func_06011A6C(0xFE000090);
        break;
    case 0xF0000093:
        DAT_06064428 = 120;
        func_06011A6C(0xFE000090);
        break;
    case 0xF0000094:
        DAT_06064428 = 180;
        func_06011A6C(0xFE000090);
        break;
    case 0xF00000A0:
        DAT_060643A0 = 1;
        PlaySfxFadeAll(0);
        break;
    }
}

static void MusicBankFlag(s32 music, s8 value) {
    if (music == 0) {
        DAT_06064404[0] = value;
    } else if ((u32)music > 2 && music != 0x33) {
        DAT_06064404[2] = value;
    } else {
        DAT_06064404[1] = value;
    }
}

s32 func_060129BC(s32 arg0) {
    s32 sctsz, nsct, lstsz, amode;
    s32 music, result;

    if (arg0 != 0) {
        D_06041288 = 0;
        return 1;
    }
    if (D_06041288 == 0) {
        if (DAT_06063BD4 != 0 && DAT_06063EB4 == 0) {
            return 1;
        }
        if (DAT_06063BE0 == 5 && DAT_0606238C == 0) {
            return 1;
        }
        music = DAT_06064224;
        if ((u32)music <= 56) {
            DAT_0606223C =
                func_06017F5C((char*)g_SaturnSoundFiles[music].filename);
            if (DAT_0606223C == NULL) {
                MusicBankFlag(music, 0);
                return -1;
            }
        }
        GFS_GetFileSize(DAT_0606223C, &sctsz, &nsct, &lstsz);
        DAT_06057C40 = (nsct - 1) * sctsz + lstsz;
        if (DAT_06064224 == 0xB8) {
            DAT_06057C3C = DAT_0606441C;
        } else {
            DAT_06064470 = DAT_06064224;
            DAT_06057C3C = DAT_060644C8;
        }
        D_06041288 = 1;
    }
    if (D_06041288 == 1) {
        if (DAT_06063BD4 != 0 && DAT_06063EB4 == 0) {
            return 1;
        }
        if (DAT_06063BE0 == 5 && DAT_0606238C == 0) {
            return 1;
        }
        if (func_06016B9C(DAT_0606223C, (void*)(unsigned long)(u32)DAT_06057C3C,
                          DAT_06057C40) == -1) {
            DAT_0606223C = NULL;
            MusicBankFlag(DAT_06064224, 0);
            return -1;
        }
        D_06041288 = 2;
    }
    if (D_06041288 != 2) {
        return D_06041288;
    }
    result = GFS_NwExecOne(DAT_0606223C);
    DAT_060642E0 = result;
    if (result == -1) {
        return result;
    }
    if (result != 0) {
        return 1;
    }
    GFS_NwGetStat(DAT_0606223C, &amode, &DAT_06057C38);
    DAT_06057C3C += 0xC000;
    DAT_060623B0[2] |= 2;
    DAT_06057C40 -= DAT_06057C38;
    if (DAT_06057C40 > 0) {
        D_06041288 = 1;
        return 1;
    }
    PcmClose(DAT_0606223C, 2);
    DAT_0606223C = NULL;
    DAT_060623B0[2] &= ~2;
    D_06041288 = 0;
    MusicBankFlag(DAT_06064224, 1);
    return 0;
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

void func_060139C4(void) {
    s32 pan;
    s32 cfgIdx;
    s32 vol;
    s32 i;
    s32 slot;
    s32 ret;
    s32 sub;
    s32 idx;
    s32 kind;
    volatile SoundRequest* req;
    volatile SoundRequest* dst;
    SaturnSoundConfig* cfg;
    s8* row;

    satz_set_sr(satz_get_sr() | 0xF0);
    HW_WRITE16(0xFFFFFEE2, 0);
    HW_WRITE16(0xFFFFFE60, 0);
    HW_WRITE8(0xFFFFFE10, 1);
    CSH_Init(0);
    for (;;) {
        CSH_AllClr();
        while (!(HW_READ8(0xFFFFFE11) & 0x80)) {
            satz_idle();
        }
        HW_WRITE8(0xFFFFFE11, 0);

        if (DAT_06043C4C != 0) {
            DAT_06043C4C = 0;
            for (i = 0; i < 8; i++) {
                if (DAT_06064310[i] != 0x40) {
                    SND_SetSeqPan((u8)i, 0, (u8)DAT_06064310[i]);
                    DAT_06064310[i] = 0x40;
                }
            }
            goto after_music_cmd;
        }
        DAT_06043C4C = 1;
        if ((u8)DAT_0606440D == 0) {
            if ((u8)DAT_06064414 == (u8)DAT_0606423A) {
                goto after_music_cmd;
            }
            row = DAT_06063ED0[(u8)DAT_0606423A];
            cfgIdx = *(u16*)row;
            pan = (u8)row[3];
            if (row[4] == 0) {
                vol = g_SaturnSoundConfigs[cfgIdx].unk1;
            } else {
                vol = (g_SaturnSoundConfigs[cfgIdx].unk1 * (u8)row[2]) / 127;
            }
            DAT_0606423A++;
            if (DAT_0606423A == 0x80) {
                DAT_0606423A = 0;
            }
        } else {
            cfgIdx = 0x87;
            pan = 64;
            vol = g_SaturnSoundConfigs[0x87].unk1;
            DAT_0606440D = 0;
        }

        vol = func_06011B28(vol);
        if (cfgIdx <= 0xFF) {
            if (DAT_06064404[0] == 0) {
                goto after_music_cmd;
            }
        } else if (cfgIdx <= 0x12F) {
            if (DAT_06064404[1] == 0 || DAT_06064404[0] == 0) {
                goto after_music_cmd;
            }
        } else {
            if (DAT_06064404[2] == 0 || DAT_06064404[0] == 0) {
                goto after_music_cmd;
            }
        }

        cfg = &g_SaturnSoundConfigs[cfgIdx];
        switch (cfg->unk2) {
        case 1:
            DAT_060644A8 = 0;
            SND_SetSeqVl(7, (u8)vol, 0);
            SND_StartSeq_DR(7, cfg->unk0, cfg->unk3, cfg->unk4);
            DAT_060644B0 = cfg->unk1;
            DAT_060643E0[7] = cfgIdx;
            DAT_06064310[7] = (s16)pan;
            DAT_0606436E = (s16)pan;
            break;
        case 2:
            SND_StopSeq(7);
            DAT_060643E0[7] = 0;
            break;
        case 3:
            DAT_06064401 = 0;
            SND_SetSeqVl(6, (u8)vol, 0);
            SND_StartSeq_DR(6, cfg->unk0, cfg->unk3, cfg->unk4);
            DAT_060643E0[6] = cfgIdx;
            DAT_06064310[6] = (s16)pan;
            DAT_060644E6 = (s16)pan;
            break;
        case 0:
        case 5:
        case 9:
            for (slot = 0; slot <= 5; slot++) {
                if (DAT_060643E0[slot] == cfgIdx) {
                    SND_StartSeq_DR((u8)slot, cfg->unk0, cfg->unk3, cfg->unk4);
                    SND_SetSeqVl((u8)slot, (u8)vol, 0);
                    DAT_06064310[slot] = (s16)pan;
                    goto after_music_cmd;
                }
            }
            for (slot = 0; slot <= 5; slot++) {
                SND_GetSeqStat(&DAT_06064478, (u8)slot);
                if (SND_SEQ_STAT_MODE(DAT_06064478) == 0) {
                    SND_SetSeqVl((u8)slot, (u8)vol, 0);
                    SND_StartSeq_DR((u8)slot, cfg->unk0, cfg->unk3, cfg->unk4);
                    DAT_060643E0[slot] = cfgIdx;
                    DAT_060644B8[slot] = cfg->unk4;
                    DAT_06064310[slot] = (s16)pan;
                    goto after_music_cmd;
                }
            }
            for (slot = 0; slot <= 5; slot++) {
                if (cfg->unk4 > (u8)DAT_060644B8[slot]) {
                    goto steal_slot;
                }
            }
            for (slot = 0; slot <= 5; slot++) {
                if (cfg->unk4 == (u8)DAT_060644B8[slot]) {
                    goto steal_slot;
                }
            }
            break;
        steal_slot:
            SND_StartSeq_DR((u8)slot, cfg->unk0, cfg->unk3, cfg->unk4);
            SND_SetSeqVl((u8)slot, (u8)vol, 0);
            DAT_060643E0[slot] = cfgIdx;
            DAT_060644B8[slot] = cfg->unk4;
            DAT_06064310[slot] = (s16)pan;
            break;
        default:
            break;
        }

    after_music_cmd:
        if (DAT_06063BD8 == 0) {
            if (DAT_06063BD0 != 0) {
                func_06011F58();
                DAT_06063BD0 = 0;
            }
            switch (DAT_06063BE0) {
            case 1:
                if (DAT_060641F4 == 0) {
                    if (DAT_060641E0 != 0) {
                        func_0601476C(1);
                        DAT_060641E0 = 0;
                    }
                    ret = func_0601476C(0);
                    if (ret == -1) {
                        DAT_06063BE0 = 0;
                    } else if (ret == 0) {
                        if (DAT_060641D4 == -1) {
                            func_06014F3C(1);
                        } else {
                            func_06015140(1);
                        }
                        DAT_06063BE0 = 2;
                    }
                } else {
                    if (DAT_060641E0 != 0) {
                        func_06014B80(1);
                        DAT_060641E0 = 0;
                    }
                    ret = func_06014B80(0);
                    if (ret == -1) {
                        DAT_06063BE0 = 0;
                    } else {
                        DAT_06063BE0 = 2;
                    }
                }
                break;
            case 2:
            case 3:
            case 4:
            case 5:
                if (DAT_06063BE0 - 3 <= 2) {
                    if (DAT_060641D4 == -1) {
                        func_06014F3C(0);
                    } else {
                        func_06015140(0);
                    }
                }
                break;
            case 7:
                func_06011F58();
                DAT_06063BE0 = 0;
                break;
            case 8:
                if (DAT_060641D4 == -1) {
                    ret = func_06014F3C(0);
                } else {
                    ret = func_06015140(0);
                }
                if (ret == 0) {
                    DAT_06063BE0 = 0;
                }
                break;
            default:
                break;
            }

            if (DAT_06063BF0 != 0) {
                func_06012054();
                DAT_06063BF0 = 0;
            }
            if (DAT_06063BFC != 0) {
                func_060120A0();
                DAT_06063BFC = 0;
            }

            switch (DAT_06064214) {
            case 1:
                if (DAT_06064204 != 0) {
                    func_06014D44(0);
                    DAT_06064204 = 0;
                }
                if (DAT_060623BC == 0) {
                    ret = func_06014D44(DAT_06062254);
                    if (ret == -1) {
                        DAT_06064214 = 0;
                    } else if (ret == 0) {
                        DAT_06064214 = 2;
                    }
                    func_060155CC(1);
                } else {
                    ret = func_06014C20();
                    if (ret == -1) {
                        DAT_06064214 = 0;
                    } else {
                        DAT_06064214 = 2;
                    }
                }
                break;
            case 2:
            case 3:
            case 4:
            case 5:
                if ((DAT_06064214 & 0x0F) == 5) {
                    func_060155CC(0);
                }
                break;
            case 7:
                func_060120A0();
                DAT_0606423C = 0;
                break;
            case 8:
                ret = func_060155CC(0);
                if (ret == 0) {
                    DAT_06064214 = ret;
                }
                break;
            default:
                break;
            }

            if (DAT_0606435C != 0) {
                func_06012954();
                DAT_0606435C = 0;
            }

            switch (DAT_06064300) {
            case 1:
                if (DAT_0606433C != 0) {
                    func_0601701C(0);
                    DAT_0606433C = 0;
                }
                if (DAT_06064334 == 0) {
                    ret = func_0601701C(DAT_060642F8);
                    if (ret == -1) {
                        DAT_06064300 = 0;
                    } else if (ret == 0) {
                        DAT_06064300 = 2;
                    }
                } else {
                    ret = func_06017F28();
                    if (ret == -1) {
                        DAT_06064300 = 0;
                    } else if (ret == 0) {
                        DAT_06064300 = 2;
                    }
                }
                break;
            case 7:
                func_06012954();
                DAT_06064430 = 0;
                break;
            case 8:
                DAT_06064300 = 0;
                break;
            default:
                break;
            }
        }

        if (DAT_06063E70 == 0) {
            func_06016C60();
            func_06016614();
        }
        if (DAT_06062250 == 0) {
            func_06016D84();
            func_06016644();
        }
        if (DAT_06064234 == 0) {
            func_06016E84();
            func_060174D8();
        }

        if (DAT_06064328 != DAT_06062368 || DAT_06064380 != 0 ||
            DAT_060644DC != 0) {
            DAT_06064328 = DAT_06062368;
            sub = DAT_06062368;
            if (DAT_060644C1 == 1) {
                sub = 0;
            }
            if (DAT_06063BE0 > 3) {
                SND_PRM_TL(DAT_060643B0) =
                    func_06018034((u32)(0x7FFF - sub) >> 7);
                SND_ChgPcmTL(&DAT_060643B0);
            }
            if (DAT_06064380 != 0) {
                DAT_06064380--;
            }
            if (DAT_060644DC != 0) {
                DAT_060644DC--;
            }
        }
        if (DAT_06064418 != (s32)DAT_06064498 || DAT_060643C6 != 0) {
            DAT_06064418 = DAT_06064498;
            if (DAT_06064214 > 3) {
                SND_PRM_TL(DAT_06064440) =
                    func_06018034((u32)(0x7FFF - DAT_06064498) >> 7);
                SND_ChgPcmTL(&DAT_06064440);
            }
            if (DAT_060643C6 != 0) {
                DAT_060643C6--;
            }
        }
        if (DAT_060642F0 != (s32)DAT_0606448C || DAT_06064379 != 0) {
            DAT_060642F0 = DAT_0606448C;
            if ((u32)DAT_06064300 > 3) {
                SND_PRM_TL(DAT_06064460) =
                    func_06018034((u32)(0x7FFF - DAT_0606448C) >> 7);
                SND_ChgPcmTL(&DAT_06064460);
            }
            if (DAT_06064379 != 0) {
                DAT_06064379--;
            }
        }

        for (i = 0; i < 4; i++) {
            req = &DAT_06063C30[i];
            if (req->unk0 == 0) {
                continue;
            }
            kind = req->unk4;
            if (kind == 1) {
                func_060133CC(req->unk8, (u32*)(unsigned long)(u32)req->unkC,
                              req->unk10, (s16*)&req->unk24, (s32*)&req->unk1C);
                req->unk0 = 0;
                if (i > kind) {
                    dst = &DAT_06063C30[i - 2];
                    dst->unk24 = req->unk24;
                    dst->unk1C = req->unk1C;
                }
            } else if (kind == 2) {
                func_06013538(req->unk8, (u16*)(unsigned long)(u32)req->unkC,
                              (u16*)(unsigned long)((u32)req->unkC + 0x4000),
                              req->unk10, (s16*)&req->unk24, (s16*)&req->unk26,
                              (s32*)&req->unk1C, (s32*)&req->unk20);
                req->unk0 = 0;
                if (i > 1) {
                    dst = &DAT_06063C30[i - 2];
                    dst->unk24 = req->unk24;
                    dst->unk1C = req->unk1C;
                    dst->unk26 = req->unk26;
                    dst->unk20 = req->unk20;
                }
            }
        }
    }
}

static u8* PcmBuf(s32 i) { return i ? DAT_06062270.unk4 : DAT_06062270.unk0; }

static u8* PcmSrcAddr(u32 pos) {
    return PcmBuf(pos / PCM_SRC_SIZE) + pos % PCM_SRC_SIZE;
}

static void ClearPcmSlot(u32 x) {
    ClearSoundRam(DAT_06063C0C + 2 * x, 0x800);
    ClearSoundRam(DAT_06063C0C + 2 * x + 0x4000, 0x800);
}

static void StartPcmChannel7(void) {
    SndPcmStartPrm sprm;

    DAT_06064380 = 2;
    SND_PRM_MODE(sprm) = 0x80;
    SND_PRM_SADR(sprm) = 0x7800;
    SND_PRM_SIZE(sprm) = 0x2000;
    SND_PRM_NUM(DAT_060643B0) = 7;
    SND_PRM_TL(DAT_060643B0) = 255;
    SND_PRM_LEV(DAT_060643B0) = 7;
    SND_PRM_PAN(DAT_060643B0) = 0;
    SND_PRM_PICH(DAT_060643B0) = 0;
    SND_L_EFCT_IN(DAT_060643B0) = 0;
    SND_L_EFCT_LEV(DAT_060643B0) = 0;
    SND_R_EFCT_IN(DAT_060643B0) = 0;
    SND_R_EFCT_LEV(DAT_060643B0) = 0;
    SND_StartPcmTL(&sprm, &DAT_060643B0);
    DAT_060641FC = 0;
}

static void QueueSplit(void) {
    u32 pos = DAT_06063EAC;
    u32 split = DAT_06063BE8;
    u32 x = DAT_0606421C;

    func_06014724(PcmSrcAddr(pos), DAT_06063C0C + 2 * x, (split & 0x3FF) >> 1,
                  DAT_06062368, 0);
    func_060146A4(PcmSrcAddr(split), DAT_06063C0C + 2 * x + 2 * (split & 0x3FF),
                  0x200 - ((split & 0x3FF) >> 1), DAT_06064228, DAT_06062264,
                  DAT_06063E74, DAT_06063BF4, DAT_06062368, 2);
}

void func_06015E68(void) {
    SndPcmPlayAdr pcmAdr;
    u32 pending;
    u32 x;
    u32 rem;

    switch (DAT_06063BE0 & 0xF) {
    case 2:
        if (DAT_0606225C != 0) {
            func_060146A4(PcmSrcAddr(DAT_06063EAC), DAT_06063C0C, 0x200, 0, 0,
                          0, 0, DAT_06062368, 0);
            DAT_0606225C = 0;
        } else if (
            DAT_06064200 != 0 && DAT_06063EAC == ((DAT_06063BE8 >> 10) << 10)) {
            QueueSplit();
            DAT_06064200 = 0;
        } else {
            func_06014724(
                PcmSrcAddr(DAT_06063EAC), DAT_06063C0C, 0x200, DAT_06062368, 0);
        }
        DAT_06062238 -= 0x200;
        DAT_06063EAC = (DAT_06063EAC + 0x400) % PCM_RING_SIZE;
        DAT_0606421C = 0x400;
        goto tail;
    case 3:
        if (DAT_06064200 != 0 && DAT_06063EAC == ((DAT_06063BE8 >> 10) << 10)) {
            QueueSplit();
            DAT_06064200 = 0;
        } else {
            func_06014724(
                PcmSrcAddr(DAT_06063EAC), DAT_06063C0C + 2 * DAT_0606421C,
                0x200, DAT_06062368, 0);
        }
        DAT_06062238 -= 0x200;
        DAT_06063EAC = (DAT_06063EAC + 0x400) % PCM_RING_SIZE;
        DAT_0606421C += 0x400;
        goto tail;
    case 4:
        StartPcmChannel7();
        DAT_06063BE0++;
        return;
    case 5:
        SND_GetPcmPlayAdr(&pcmAdr, 7);
        x = DAT_0606421C;
        if (pcmAdr.radr == (x >> 12) && (x & 0xFFF) == 0) {
            return;
        }
        if (DAT_06062230[DAT_06063E7C] == 0) {
            ClearPcmSlot(x);
            DAT_0606421C = (DAT_0606421C + 0x400) & 0x1FFF;
            return;
        }
        if (DAT_06064200 != 0 && DAT_06063EAC == ((DAT_06063BE8 >> 10) << 10)) {
            QueueSplit();
            DAT_06064200 = 0;
        } else {
            func_06014724(
                PcmSrcAddr(DAT_06063EAC), DAT_06063C0C + 2 * DAT_0606421C,
                0x200, DAT_06062368, 0);
        }
        DAT_06062238 -= 0x200;
        DAT_06063EAC = (DAT_06063EAC + 0x400) % PCM_RING_SIZE;
        DAT_0606421C = (DAT_0606421C + 0x400) & 0x1FFF;
        rem = DAT_06063EAC % PCM_SRC_SIZE;
        if (rem == 0) {
            DAT_06062230[DAT_06063E7C] = rem;
            DAT_06063E7C = (DAT_06063E7C + 1) & 1;
        }
        return;
    case 6:
        SND_GetPcmPlayAdr(&pcmAdr, 7);
        x = DAT_0606421C;
        if (pcmAdr.radr != (x >> 12)) {
            ClearPcmSlot(x);
            DAT_06063BE0++;
            return;
        }
        if ((x & 0xF00) != 0) {
            ClearPcmSlot(x);
            DAT_0606421C = (DAT_0606421C + 0x400) & 0x1FFF;
        }
        return;
    case 7:
        SND_StopPcm2(0);
        return;
    default:
        return;
    }
tail:
    rem = DAT_06063EAC % PCM_SRC_SIZE;
    if (rem == 0) {
        DAT_06062230[DAT_06063E7C] = rem;
        DAT_06063E7C = (DAT_06063E7C + 1) & 1;
    }
    DAT_06063BE0++;
}

void func_06016644(void) {
    SndPcmPlayAdr adr;
    SndPcmStartPrm sprm;
    u32 st;
    s32 n;
    s32 flag;
    u32 idx;

    st = (DAT_06064214 & 0xF) - 2;
    if (st > 5) {
        return;
    }
    switch (st) {
    case 0:
        DAT_060440FC = 0;
        flag = DAT_0606227C;
        if (flag != 0) {
            func_060145F8(DAT_06062244, DAT_06063EBC, 0x100, 0, 0, 1);
            DAT_06063C04 = (DAT_06063C04 + 0x100) & 0x3FFF;
            DAT_06063EB0 -= 0x100;
            DAT_0606420C = 0x200;
            DAT_0606227C = 0;
            goto next;
        }
        n = DAT_06063EB0;
        if (n == 0) {
            goto empty;
        }
        if ((u32)n > 0x100) {
            func_06014658(DAT_06062244 + DAT_06063C04,
                          DAT_06063EBC + 2 * DAT_0606420C, 0x100, 1);
            DAT_06063EB0 -= 0x100;
            DAT_06063C04 = (DAT_06063C04 + 0x100) & 0x3FFF;
            DAT_0606420C = (DAT_0606420C + 0x200) & 0x1FFF;
            goto next;
        }
        func_06014658(
            DAT_06062244 + DAT_06063C04, DAT_06063EBC + 2 * DAT_0606420C, n, 1);
        if (0x100 - n != 0) {
            ClearSoundRam(DAT_06063EBC + 2 * DAT_0606420C + n * 4, 0x100 - n);
        }
        DAT_06063C04 += n;
        DAT_06063EB0 = flag;
        DAT_0606420C = (DAT_0606420C + 0x200) & 0x1FFF;
        DAT_06064214 += 2;
        goto check;
    case 1:
        n = DAT_06063EB0;
        if (n == 0) {
            goto empty;
        }
        if ((u32)n > 0x100) {
            func_06014658(DAT_06062244 + DAT_06063C04,
                          DAT_06063EBC + 2 * DAT_0606420C, 0x100, 1);
            DAT_06063EB0 -= 0x100;
            DAT_06063C04 = (DAT_06063C04 + 0x100) & 0x3FFF;
        } else {
            func_06014658(DAT_06062244 + DAT_06063C04,
                          DAT_06063EBC + 2 * DAT_0606420C, n, 1);
            if (0x100 - n != 0) {
                ClearSoundRam(
                    DAT_06063EBC + 2 * DAT_0606420C + n * 4, 0x100 - n);
            }
            DAT_06063C04 += n;
            DAT_06063EB0 = 0;
        }
        DAT_0606420C = (DAT_0606420C + 0x200) & 0x1FFF;
        goto next;
    empty:
        DAT_06064214 = 7;
        goto check;
    case 2:
        DAT_060643C6 = 2;
        sprm.mode = 0;
        sprm.sadr = 0x7800;
        sprm.size = 0x2000;
        DAT_06064440.num = 6;
        DAT_06064498 = g_SaturnSoundValues512[(u32)DAT_06062254 & 0xFFFFF];
        DAT_06063EA8 = DAT_06064498;
        if (DAT_06064350 != 0) {
            DAT_06064498 = 0;
        }
        DAT_06064440.t_lev = 0xFF;
        DAT_06064440.lev = 7;
        DAT_06064440.pan = 0;
        DAT_06064440.pich = 0x7800;
        DAT_06064440.l_efct_in = 0;
        DAT_06064440.l_efct_lev = 0;
        DAT_06064440.r_efct_in = 0;
        DAT_06064440.r_efct_lev = 0;
        SND_StartPcmTL(&sprm, &DAT_06064440);
        DAT_06064214 += 1;
        if (DAT_06063EB0 == 0) {
            DAT_06064214 += 1;
        }
        return;
    case 3:
        SND_GetPcmPlayAdr(&adr, 6);
        idx = DAT_0606420C;
        if (adr.radr == (idx >> 12) && (idx & 0xFFF) == 0) {
            return;
        }
        if (DAT_06062380[DAT_060641F8] == 0) {
            ClearSoundRam(DAT_06063EBC + 2 * idx, 0x400);
            DAT_0606420C = (DAT_0606420C + 0x200) & 0x1FFF;
            return;
        }
        n = DAT_06063EB0;
        if (n == 0) {
            goto check;
        }
        if ((u32)n > 0x100) {
            func_06014658(
                DAT_06062244 + DAT_06063C04, DAT_06063EBC + 2 * idx, 0x100, 1);
            DAT_06063EB0 -= 0x100;
            DAT_06063C04 = (DAT_06063C04 + 0x100) & 0x3FFF;
            DAT_0606420C = (DAT_0606420C + 0x200) & 0x1FFF;
            goto check;
        }
        func_06014658(
            DAT_06062244 + DAT_06063C04, DAT_06063EBC + 2 * idx, n, 1);
        if (0x100 - n != 0) {
            ClearSoundRam(DAT_06063EBC + 2 * DAT_0606420C + n * 4, 0x100 - n);
        }
        DAT_06063C04 += n;
        DAT_06063EB0 = 0;
        DAT_0606420C = (DAT_0606420C + 0x200) & 0x1FFF;
        goto next;
    case 4:
        SND_GetPcmPlayAdr(&adr, 6);
        idx = DAT_0606420C;
        if (adr.radr != (idx >> 12)) {
            ClearSoundRam(DAT_06063EBC + 2 * idx, 0x400);
            DAT_060440F8 = DAT_0606420C + 0x200;
            DAT_060440FC = 1;
        } else if ((idx & 0xF00) != 0) {
            ClearSoundRam(DAT_06063EBC + 2 * idx, 0x400);
            DAT_0606420C = (DAT_0606420C + 0x200) & 0x1FFF;
        }
        if (DAT_060440FC == 1) {
            if (adr.radr == (DAT_0606420C >> 12)) {
                DAT_06064214 += 1;
                return;
            }
            ClearSoundRam(DAT_06063EBC + 2 * DAT_060440F8, 0x400);
            DAT_060440F8 = (DAT_060440F8 + 0x200) & 0x1FFF;
        }
        return;
    case 5:
        SND_StopPcm2(1);
        return;
    }
    return;
next:
    DAT_06064214 += 1;
check:
    idx = DAT_06063C04 & 0x1FFF;
    if (idx == 0) {
        DAT_06062380[DAT_060641F8] = idx;
        DAT_060641F8 = (DAT_060641F8 + 1) & 1;
    }
}

static void ClearSoundRam(u32 addr, u32 n) {
    static const u8 zero[0x400];
    u32 done;

    for (done = 0; done < n; done += sizeof(zero)) {
        satz_bus_store(addr + done, zero,
                       n - done < sizeof(zero) ? n - done : sizeof(zero));
    }
}

s32 func_06016C60(void) {
    s32 r2;

    if (DAT_06063BE0 == 5) {
        s32 step = DAT_0606422C;

        if (step != 0) {
            DAT_06063C18 += step;
            if ((u32)DAT_060641EC > (u32)DAT_06063C18) {
                DAT_0606224C = 0;
            } else {
                if (DAT_06062258 == -1) {
                    DAT_06063BE0 = 6;
                } else {
                    DAT_0606224C = 1;
                }
                DAT_06063C18 = DAT_060641EC;
                DAT_0606422C = 0;
            }
        } else if ((s32)DAT_06062388 != 0) {
            if (DAT_06063C18 > (s32)DAT_06062388) {
                DAT_06063C18 -= (s32)DAT_06062388;
            } else {
                DAT_06062388 = step;
                DAT_06063C18 = step;
            }
        }
        if (DAT_060641EC >= (u32)DAT_06063C18) {
            r2 = DAT_060641EC - (u32)DAT_06063C18;
        } else {
            r2 = 0;
        }
        DAT_06062368 = r2;
    }

    if (DAT_06064388 == 1) {
        if (DAT_0606446C > 40) {
            DAT_0606446C -= 2;
        }
    } else if (DAT_06064388 == 2) {
        DAT_0606446C += 2;
        if (DAT_0606446C > 100) {
            DAT_0606446C = 100;
            DAT_06064388 = 0;
        }
    } else {
        goto skip_scale;
    }
    DAT_06062368 = (u32)((u32)DAT_06062368 * (u32)DAT_0606446C) / 100;
skip_scale:
    if (DAT_06062368 == 0 && DAT_06064358 == 1) {
        DAT_06064358 = 0;
        func_06012474();
    }
    return 0;
}

static void slave_snd_ram_copy(u8* dst, const void* src, u32 count) {
    satz_bus_store(satz_bus_address(dst), src, count);
}

static void slave_snd_ram_clear(u8* dst, u32 count) {
    static const u8 zero[0x400];
    u32 done;

    for (done = 0; done < count; done += sizeof(zero)) {
        satz_bus_store(
            satz_bus_address(dst + done), zero,
            count - done < sizeof(zero) ? count - done : sizeof(zero));
    }
}

void sotn_snd_ram_copy(u8* dst, const void* src, u32 count) {
    slave_snd_ram_copy(dst, src, count);
}

static void slave_pcm_refill(s32 remain) {
    s32 chunk;

    while (remain != 0) {
        chunk = DAT_06064340 - DAT_06064394;
        DAT_06064360 = chunk;
        DAT_060644E8 = (u8*)DAT_060644E8 - chunk;
        if ((u32)chunk >= (u32)remain) {
            slave_snd_ram_copy(
                DAT_06064480 + DAT_0606434C, DAT_060644E8, remain);
            DAT_060644E8 = (u8*)DAT_060644E8 + remain;
            DAT_06064408 = (DAT_06064408 + remain) & 0x1FFF;
            DAT_06064360 -= remain;
            DAT_0606434C = (DAT_0606434C + remain) & 0x1FFF;
            remain = 0;
        } else {
            slave_snd_ram_copy(
                DAT_06064480 + DAT_0606434C, DAT_060644E8, chunk);
            DAT_060644E8 = (u8*)DAT_060644E8 + DAT_06064360;
            DAT_0606434C = (DAT_0606434C + DAT_06064360) & 0x1FFF;
            DAT_06064408 = (DAT_06064408 + DAT_06064360) & 0x1FFF;
            remain -= DAT_06064360;
            DAT_06064360 = 0;
        }
    }
}

static void slave_pcm_rewind(void) {
    s32 chunk;

    if (DAT_06064360 == 0) {
        chunk = DAT_06064340 - DAT_06064394;
        DAT_06064360 = chunk;
        DAT_060644E8 = (u8*)DAT_060644E8 - chunk;
    }
}

static void slave_pcm_ring_mark(void) {
    s32 offset = DAT_06064408 & 0x1FFF;

    if (offset == 0) {
        DAT_06064490[DAT_06064484] = offset;
        DAT_06064484 = (DAT_06064484 + 1) & 1;
    }
}

void func_06017988(void) {
    SndPcmPlayAdr pcm_adr;
    s32 pending;
    s32 remain;
    u32 count;
    u32 state;

    state = DAT_06064300 & 0xF;
    if (state - 2 > 5) {
        return;
    }
    switch (state) {
    case 2:
        DAT_06044110 = 0;
        DAT_06044114 = 0;
        remain = 0;
        pending = DAT_06064238;
        count = DAT_06064360;
        if (pending != 0) {
            if (count > 0x800) {
                slave_snd_ram_copy(
                    DAT_06064480 + DAT_0606434C, DAT_060644E8, 0x800);
                DAT_060644E8 = (u8*)DAT_060644E8 + 0x800;
                DAT_06064408 = (DAT_06064408 + 0x800) & 0x1FFF;
                DAT_06064360 -= 0x800;
                DAT_0606434C = 0x800;
                DAT_06064238 = 0;
                DAT_06064300 = 4;
            } else {
                slave_snd_ram_copy(
                    DAT_06064480 + DAT_0606434C, DAT_060644E8, count);
                DAT_060644E8 = (u8*)DAT_060644E8 + count;
                remain = 0x800 - count;
                DAT_06064408 = (DAT_06064408 + count) & 0x1FFF;
                DAT_0606434C = count;
                DAT_06064360 = 0;
                DAT_06064238 = 0;
                DAT_06064300 = 4;
            }
        } else if (count != 0) {
            if (count > 0x800) {
                slave_snd_ram_copy(
                    DAT_06064480 + DAT_0606434C, DAT_060644E8, 0x800);
                DAT_060644E8 = (u8*)DAT_060644E8 + 0x800;
                DAT_06064360 -= 0x800;
                DAT_06064408 = (DAT_06064408 + 0x800) & 0x1FFF;
                DAT_0606434C = (DAT_0606434C + 0x800) & 0x1FFF;
                DAT_06064300 = 4;
            } else {
                slave_snd_ram_copy(
                    DAT_06064480 + DAT_0606434C, DAT_060644E8, count);
                DAT_060644E8 = (u8*)DAT_060644E8 + count;
                remain = 0x800 - count;
                DAT_06064408 = (DAT_06064408 + count) & 0x1FFF;
                DAT_0606434C = (DAT_0606434C + count) & 0x1FFF;
                DAT_06064360 = 0;
                DAT_06064300 = 4;
            }
        }
        slave_pcm_refill(remain);
        slave_pcm_rewind();
        slave_pcm_ring_mark();
    case 4:
        DAT_06064379 = 2;
        SND_PRM_MODE(DAT_06064368) = SND_MD_8;
        SND_PRM_SADR(DAT_06064368) = 0x7600;
        SND_PRM_SIZE(DAT_06064368) = 0x2000;
        SND_PRM_NUM(DAT_06064460) = 5;
        SND_PRM_LEV(DAT_06064460) = 7;
        SND_PRM_PAN(DAT_06064460) = 0;
        SND_PRM_PICH(DAT_06064460) = DAT_0606447C;
        SND_L_EFCT_IN(DAT_06064460) = 0;
        SND_L_EFCT_LEV(DAT_06064460) = (u8)DAT_060642D0;
        SND_R_EFCT_IN(DAT_06064460) = 0;
        SND_R_EFCT_LEV(DAT_06064460) = (u8)DAT_060642D0;
        SND_PRM_TL(DAT_06064460) = -1;
        SND_StartPcmTL(&DAT_06064368, &DAT_06064460);
        DAT_06064300++;
        if (DAT_06064360 == 0) {
            DAT_06064300++;
        }
        break;
    case 5:
        SND_GetPcmPlayAdr(&pcm_adr, 5);
        if (pcm_adr.radr == ((u32)DAT_0606434C >> 12) &&
            (DAT_0606434C & 0xFFF) == 0) {
            break;
        }
        remain = 0;
        count = DAT_06064360;
        if (count != 0) {
            if (count > 0x800) {
                slave_snd_ram_copy(
                    DAT_06064480 + DAT_0606434C, DAT_060644E8, 0x800);
                DAT_060644E8 = (u8*)DAT_060644E8 + 0x800;
                DAT_06064360 -= 0x800;
                DAT_06064408 = (DAT_06064408 + 0x800) & 0x1FFF;
                DAT_0606434C = (DAT_0606434C + 0x800) & 0x1FFF;
            } else {
                slave_snd_ram_copy(
                    DAT_06064480 + DAT_0606434C, DAT_060644E8, count);
                DAT_060644E8 = (u8*)DAT_060644E8 + count;
                remain = 0x800 - count;
                DAT_06064408 += count;
                DAT_0606434C = (DAT_0606434C + count) & 0x1FFF;
                DAT_06064360 = 0;
            }
        }
        slave_pcm_refill(remain);
        slave_pcm_rewind();
        if ((DAT_06064408 & 0x1FFF) == 0) {
            DAT_06064490[DAT_06064484] = 0;
            DAT_06064484 = (DAT_06064484 + 1) & 1;
        }
        break;
    case 6:
        SND_GetPcmPlayAdr(&pcm_adr, 5);
        if (pcm_adr.radr != ((u32)DAT_0606434C >> 12)) {
            slave_snd_ram_clear(DAT_06064480 + DAT_0606434C, 0x800);
            DAT_06044110 = (DAT_0606434C + 0x800) & 0x1FFF;
            DAT_06044114 = 1;
        } else if (DAT_0606434C & 0x800) {
            slave_snd_ram_clear(DAT_06064480 + DAT_0606434C, 0x800);
            DAT_0606434C = (DAT_0606434C + 0x800) & 0x1FFF;
        }
        if (DAT_06044114 == 1) {
            if (pcm_adr.radr == ((u32)DAT_0606434C >> 12)) {
                DAT_06064300++;
            } else {
                slave_snd_ram_clear(DAT_06064480 + DAT_06044110, 0x800);
                DAT_06044110 = (DAT_06044110 + 0x800) & 0x1FFF;
            }
        }
        break;
    case 7:
        SND_StopPcm2(5);
        break;
    }
}

void sotn_snd_ram_clear(u8* dst, u32 count) { slave_snd_ram_clear(dst, count); }

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

#define R16(p, o) (*(u16*)((u8*)(p) + (o)))
#define R32(p, o) (*(s32*)((u8*)(p) + (o)))
extern u8 DAT_0604B5E0[];

static u16 StreamSlotPatterns(
    u8* slot, u32 vram, u8* src, s32 size, u16 frame) {
    u16 chr;

    vram += R32(slot, 8);
    QueueVramTransfer(vram, src, size);
    chr = (u16)(vram >> 3);
    R16(slot, 0xE) = 1;
    R16(slot, 0x10 + R16(slot, 0xC) * 2) = frame;
    R16(slot, 0x1A + R16(slot, 0xC) * 2) = chr;
    R32(slot, 8) += size;
    R16(slot, 0xC)++;
    return chr;
}

u16 func_0600A490(u8* record, u16 frame, s32 flag, s32 playableCharacter) {
    SaturnPlayerGraphicsRecord* gfx;
    u8* slot = record + 0xA8;
    u8* src;
    u8* dst2;
    s32 size;
    u16 chr0, chr1;

    if (playableCharacter == 1 || playableCharacter == 2) {
        gfx = &DAT_06064668[frame];
    } else {
        gfx = &DAT_06064668[frame + 3];
    }
    src = g_WorkBuffer.load.data + R32(slot, 8);
    dst2 = DAT_0604B5E0 + R32(slot, 8);
    size = DecompressLZSS(
        sotn_satz_retail_address(gfx->sourceOffset), src, gfx->byteCount);
    if (R32(record, 0xC) != 0) {
        MapBytesThroughLut(src, dst2, size);
    } else {
        func_0600A5FC(src, src, dst2, size);
    }
    chr0 = StreamSlotPatterns(
        slot, R32(record, 0x8C + R32(record, 8) * 4), src, size, frame);
    chr1 = StreamSlotPatterns(
        record + 0xCC, R32(record + 0xCC, 4), dst2, size, frame);
    return flag ? chr1 : chr0;
}

void func_0600B12C(SpriteObject* dst, SpriteObject* src) {
    SpritePart* d = dst->parts;
    SpritePart* s = src->parts;
    s32 count = (src->flags >> 8) & 0x3F;

    while (d != NULL && s != NULL) {
        d->attributes = s->attributes;
        d->offsetX = s->offsetX;
        d->offsetY = s->offsetY;
        d->imageIndex = s->imageIndex;
        d->rotate = s->rotate;
        d->scaleX = s->scaleX;
        d->scaleY = s->scaleY;
        d = d->next;
        s = s->next;
        if (--count <= 0) {
            break;
        }
    }
    dst->flags = src->flags;
    dst->slotAndStreamId =
        (dst->slotAndStreamId & 0xFF00) | (src->slotAndStreamId & 0xFF);
    dst->charBase = src->charBase;
    dst->clutBase = src->clutBase;
    dst->rotate = src->rotate;
    dst->scaleX = src->scaleX;
    dst->scaleY = src->scaleY;
    dst->unk0C = src->unk0C;
    dst->unk0D = src->unk0D;
    dst->zPriority = src->zPriority;
    dst->subPixelX = src->subPixelX;
    dst->subPixelY = src->subPixelY;
    dst->posX = src->posX;
    dst->posY = src->posY;
}

s32 func_0600BA24(
    SprSpCmd* cmd, SpriteObject* obj, SpritePart* part, s32* pos) {
    u16 flags = obj->flags;
    u16 attributes = part->attributes;
    SaturnSpriteImage image = obj->images[part->imageIndex];
    s32 x = pos[0];
    s32 y = pos[1];
    s32 m[4];
    MthXy offset;
    s32 scale, rotate, angle, base;
    s16 ax, bx, cx, dx, lo, hi;

    m[1] = 0;
    m[2] = 0;
    scale = (flags & 0x40) ? obj->scaleX : 0x40;
    if (scale == 0x40) {
        m[0] = image.storedWidth << 16;
        offset.x = part->offsetX << 16;
    } else {
        m[0] = (image.storedWidth * scale) << 10;
        offset.x = (part->offsetX * scale) << 10;
    }
    scale = (flags & 0x40) ? obj->scaleY : 0x40;
    if (scale == 0x40) {
        m[3] = image.storedHeight << 16;
        offset.y = part->offsetY << 16;
    } else {
        m[3] = (image.storedHeight * scale) << 10;
        offset.y = (part->offsetY * scale) << 10;
    }
    rotate = (flags & 0x40) ? obj->rotate : 0;
    angle = (s16)(part->rotate + rotate);
    if (rotate != 0) {
        RotateVec2(&offset, rotate);
    }
    if (angle != 0) {
        func_0600BCE0(m, angle);
    }
    if (flags & 0x10) {
        m[0] = -m[0];
        m[2] = -m[2];
        x -= offset.x;
    } else {
        x += offset.x;
    }
    if (flags & 0x20) {
        m[1] = -m[1];
        m[3] = -m[3];
        y -= offset.y;
    } else {
        y += offset.y;
    }

    base = x - m[2] + 0x8000;
    cmd->ax = ax = (u32)(base - m[0]) >> 16;
    cmd->bx = bx = (u32)(base + m[0]) >> 16;
    base = x + m[2] + 0x8000;
    cmd->cx = cx = (u32)(base + m[0]) >> 16;
    cmd->dx = dx = (u32)(base - m[0]) >> 16;
    if (m[2] > 0) {
        lo = ax < bx ? ax : bx;
        hi = cx >= dx ? cx : dx;
    } else {
        lo = cx < dx ? cx : dx;
        hi = ax >= bx ? ax : bx;
    }
    if (hi < 0 || lo > 319) {
        return 0;
    }
    base = y - m[3] + 0x8000;
    cmd->ay = ax = (u32)(base - m[1]) >> 16;
    cmd->by = bx = (u32)(base + m[1]) >> 16;
    base = y + m[3] + 0x8000;
    cmd->cy = cx = (u32)(base + m[1]) >> 16;
    cmd->dy = dx = (u32)(base - m[1]) >> 16;
    if (m[3] > 0) {
        lo = ax < bx ? ax : bx;
        hi = cx >= dx ? cx : dx;
    } else {
        lo = cx < dx ? cx : dx;
        hi = ax >= bx ? ax : bx;
    }
    if (hi < 0 || lo > 239) {
        return 0;
    }
    cmd->control = (attributes & 0x30) | 0x1002;
    return 1;
}
