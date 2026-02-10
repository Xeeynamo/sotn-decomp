// SPDX-License-Identifier: AGPL-3.0-or-later
#include "mpeg_private.h"

s32 read_create(
    t_ringBuffer* pRing, SceMpegRingbuffer* pRB, StrFile* pStrFile) {
    pRing->pStrFile = pStrFile;
    pRing->pRingbuf = pRB;
    {
        static s32 statusFlag;
        pRing->statusFlag = &statusFlag;
    }
    pRing->decodeSleepSema =
        sceKernelCreateSema("decode_sleep_sema", 0, 0, 1, NULL);
    pRing->unk14 = (u8*)func_psp_0891275C(0x10000);
    pRing->pStrFile; // FAKE
    return 0;
}

bool D_psp_08B1FBC0 = false;
bool D_psp_08B1FBC4 = false;
u32 D_psp_08B1FBC8 = 0;

s32 read_reset(t_ringBuffer* pRing, s32 fileSize, s32 arg2) {
    *pRing->statusFlag = 0;
    pRing->dataLen = fileSize;
    pRing->unk1C.unk30 = arg2;
    D_psp_08B1FBC0 = false;
    D_psp_08B1FBC4 = false;
    return 0;
}

s32 read_delete(t_ringBuffer* pRing) {
    sceKernelDeleteSema(pRing->decodeSleepSema);
    if (pRing->unk14 != NULL) {
        func_psp_089127D8(pRing->unk14);
    }
    return 0;
}

bool func_psp_0891504C(void) { return func_psp_08915070(NULL); }

bool func_psp_08915070(t_ringBuffer* pRing) { return D_psp_08B1FBC4; }

s32 func_psp_08915088(t_ringBuffer* pRing) {
#undef MIN
#define MIN(a, b) ((a) < (b) ? (a) : (b))

    unkStruct2* temp_s0;
    u32 temp_s3;

    temp_s0 = &pRing->unk1C;
    temp_s3 = read_getCapacity(pRing);
    if (D_psp_08B1FBC4) {
        return 1;
    }
    if (temp_s3 < MIN(0x3C0, pRing->dataLen / 0x800)) {
        return 1;
    }
    if (((pRing->dataLen / 0x800) - (temp_s0->unk28 / 0x800)) <
        MIN(0x3C0, pRing->dataLen / 0x800)) {
        if (temp_s3 < (pRing->dataLen - temp_s0->unk28)) {
            return 1;
        }
    }
    return 0;
}

s32 func_psp_08915228(t_ringBuffer* pRing) {
    *pRing->statusFlag = 0xFF;
    return 0;
}

s32 read_getCapacity(t_ringBuffer* pRing) {
    return sceMpegRingbufferAvailableSize(pRing->pRingbuf);
}

bool func_psp_0891527C(t_ringBuffer* pRing) { return D_psp_08B1FBC0; }

void func_psp_08915294(
    unkStruct2* arg0, s32 arg1, u8* arg2, s32 arg3, u32 arg4, s32 arg5) {
    if (arg1 < 0) {
    }
    arg0->unk0 = 0;
    arg0->unk4 = 0;
    arg0->unk8 = arg5;
    arg0->unk10 = 0;
    arg0->unk24 = 0;
    arg0->unk14 = 0;
    arg0->unk1C = arg2;
    arg0->unk18 = arg3;
    arg0->unk20 = arg4;
    arg0->unk28 = 0;
}

u32 func_psp_08915324(unkStruct2* arg0) { return arg0->unk8; }

u32 func_psp_08915340(unkStruct2* arg0) { return arg0->unk4; }

void func_psp_0891535C(unkStruct2* arg0, s32 arg1) {
    arg0->unk4 += arg1;
    arg0->unk8 += arg1;
}

void func_psp_0891539C(unkStruct2* arg0, u32 arg1) {
    if (arg0->unk4 >= arg1) {
        arg0->unk4 -= arg1;
    } else {
        arg0->unk4 = 0;
    }
    arg0->unk10 += arg1;
    arg0->unk10 %= arg0->unk18;
    arg0->unk14 += arg1;
    arg0->unk28 += arg1;
}

u32 func_psp_08915454(unkStruct2* arg0) { return arg0->unk14; }

s32 ringbufferCallBack(void* pBuf, s32 iNum, void* CallbackData) {
    s32 iTypeSize = 0x800;

    volatile s32 iReadSize;
    StrFile* pStrFile;
    unkStruct2* temp_s0;

    pStrFile = (StrFile*)CallbackData;

    temp_s0 = pStrFile->unk8;
    if (iNum == 0) {
        return -1;
    }
    if (pStrFile->fd == -1) {
        return -2;
    }
    if (func_psp_089123B8() == 0) {
        return -3;
    }
    if (temp_s0->unk2C < func_psp_089125F8()) {
        return -3;
    }
    func_psp_08912608();
    if (func_psp_089123B8() == 0 || D_psp_08B1FBC8 != func_psp_089125F8()) {
        func_psp_08912640();
        return -3;
    }
    iReadSize = func_psp_0891689C(pStrFile, pBuf, iTypeSize * iNum);
    func_psp_08912640();
    if (iReadSize > 0) {
        func_psp_0891535C(temp_s0, iReadSize);
        temp_s0->unk24 = 0;
        temp_s0->unk0 += iReadSize;
        temp_s0->unk0 %= temp_s0->unk18;
        func_psp_0891539C(temp_s0, iReadSize * 0x800);
    } else {
        return -3;
    }
    if ((iReadSize % iTypeSize) != 0) {
        iReadSize % iTypeSize;
        return -3;
    }

    iReadSize = iReadSize / iTypeSize;
    return iReadSize;
}

s32 read_func(s32 args, void* argp) {
#undef MIN
#define MIN(a, b) ((a) < (b) ? (a) : (b))

    static t_ringBuffer* pRing;
    static StrFile* pStrFile;
    static unkStruct2* D_psp_08B1FBD4;
    static s32 D_psp_08B1FBD8;

    s32 readSize[1];
    s32 capacitySize[1];
    s32 packNum[1];

    pRing = (t_ringBuffer*)argp;
    pStrFile = pRing->pStrFile;
    D_psp_08B1FBD4 = &pRing->unk1C;
    pRing->pStrFile->unk8 = &pRing->unk1C;
    pStrFile->unk4 = 0;
    D_psp_08B1FBD4->unk2C = func_psp_089125F8();
    func_psp_08915294(D_psp_08B1FBD4, pStrFile->fd, pRing->unk14, 0x10000,
                      pRing->dataLen, pRing->unk1C.unk30);
    while (*pRing->statusFlag != 0xFF) {
        readSize[0] = 0;
        sceKernelDelayThreadCB(16666);
        if (func_psp_089123B8() != 0) {
            capacitySize[0] = sceMpegRingbufferAvailableSize(pRing->pRingbuf);
            if (*pRing->statusFlag == 0) {
                if (D_psp_08B1FBD4->unk2C < func_psp_089125F8()) {
                    func_psp_08916830(pStrFile);
                    D_psp_08B1FBD4->unk2C = func_psp_089125F8();
                    pStrFile->unk4 = 1;
                }
                if (pStrFile->unk4 == 1 || pStrFile->fd == -1) {
                    func_psp_08912608();
                    if ((D_psp_08B1FBD8 = func_psp_08916724(
                             pStrFile, &pStrFile->unk16, PSP_O_RDONLY)) >= 0) {
                        pStrFile->unk4 = 2;
                    }
                    func_psp_08912640();
                    continue;
                }
                if (pStrFile->unk4 == 2) {
                    func_psp_08912608();
                    if ((D_psp_08B1FBD8 = func_psp_089168E8(
                             pStrFile, D_psp_08B1FBD4->unk8, PSP_SEEK_SET)) >=
                        0) {
                        D_psp_08B1FBC8 = func_psp_089125F8();
                        pStrFile->unk4 = 0;
                    }
                    func_psp_08912640();
                    continue;
                }
            }
            if ((*pRing->statusFlag == 0 || *pRing->statusFlag == 2) &&
                capacitySize[0] > 0 &&
                func_psp_08915340(D_psp_08B1FBD4) <
                    MIN(0x3C0000, pRing->dataLen)) {
                packNum[0] =
                    MIN(((pRing->dataLen - func_psp_08915324(D_psp_08B1FBD4)) /
                         0x800),
                        capacitySize[0]);
                if (packNum[0] >= 0x20) {
                    packNum[0] = 0x20;
                }
                if (packNum[0] > 0) {
                    readSize[0] = sceMpegRingbufferPut(
                        pRing->pRingbuf, packNum[0], capacitySize[0]);
                    if (readSize[0] < 0) {
                        pRing->pRingbuf;
                        switch (readSize[0]) {
                        case -1:
                            break;
                        case -2:
                            pStrFile->unk4 = 1;
                            break;
                        case -3:
                            func_psp_08916830(pStrFile);
                            pStrFile->unk4 = 1;
                            break;
                        }
                    }
                }
            } else {
                readSize[0] = 0;
            }
        } else {
            func_psp_08916830(pStrFile);
            pStrFile->unk4 = 1;
        }
        if (*pRing->statusFlag == 0) {
            if (func_psp_08915324(D_psp_08B1FBD4) >= pRing->dataLen) {
                *pRing->statusFlag = 2;
            }
        }
        if (!D_psp_08B1FBC4 && *pRing->statusFlag == 2) {
            if (func_psp_08915454(D_psp_08B1FBD4) >=
                func_psp_08915324(D_psp_08B1FBD4)) {
                D_psp_08B1FBC4 = true;
            }
        }
        if (!D_psp_08B1FBC0) {
            if (func_psp_08915454(D_psp_08B1FBD4) >=
                MIN(0x3C0000, pRing->dataLen)) {
                D_psp_08B1FBC0 = true;
            }
        }
    }
    sceKernelExitThread(0);
    return 0;
}
