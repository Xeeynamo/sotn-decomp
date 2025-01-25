#ifndef LIBCD_H
#define LIBCD_H

#include <types.h>

/* Location */
typedef struct {
    u_char minute;
    u_char second;
    u_char sector;
    u_char track;
} CdlLOC;

/* Attenuator */
typedef struct {
    u_char val0; /* volume for CD(L) -> SPU (L) */
    u_char val1; /* volume for CD(L) -> SPU (R) */
    u_char val2; /* volume for CD(R) -> SPU (L) */
    u_char val3; /* volume for CD(R) -> SPU (R) */
} CdlATV;

typedef struct {
    u_short id;
    u_short type;
    u_short secCount;
    u_short nSectors;
    u_long frameCount;
    u_long frameSize;

    u_short width;
    u_short height;
    u_long dummy1;
    u_long dummy2;
    CdlLOC loc;
} StHEADER;

/* Low Level File System for CdSearchFile() */
#define CdlMAXFILE 64 /* max number of files in a directory */
#define CdlMAXDIR 128 /* max number of total directories */
#define CdlMAXLEVEL 8 /* max levels of directories */

/*
 * CD-ROM Primitive Commands
 */
#define CdlNop 0x01
#define CdlSetloc 0x02
#define CdlPlay 0x03
#define CdlForward 0x04
#define CdlBackward 0x05
#define CdlReadN 0x06
#define CdlStandby 0x07
#define CdlStop 0x08
#define CdlPause 0x09
#define CdlMute 0x0b
#define CdlDemute 0x0c
#define CdlSetfilter 0x0d
#define CdlSetmode 0x0e
#define CdlGetparam 0x0f
#define CdlGetlocL 0x10
#define CdlGetlocP 0x11
#define CdlGetTN 0x13
#define CdlGetTD 0x14
#define CdlSeekL 0x15
#define CdlSeekP 0x16
#define CdlReadS 0x1B

/*
 * CD-ROM Mode (used int CdlSetmode)
 */
// Normal Streaming
#define CdlModeStream 0x100
// SUB HEADER information includes
#define CdlModeStream2 0x120
// normal speed	1: double speed
#define CdlModeSpeed 0x80
// 0: ADPCM off		1: ADPCM on
#define CdlModeRT 0x40
// 2048 byte		1: 2340byte
#define CdlModeSize1 0x20
// 0: -			1: 2328byte
#define CdlModeSize0 0x10
// 0: Channel off	1: Channel on
#define CdlModeSF 0x08
// 0: Report off	1: Report on
#define CdlModeRept 0x04
// AutoPause off	1: AutoPause on
#define CdlModeAP 0x02
// 0: CD-DA off		1: CD-DA on
#define CdlModeDA 0x01

#define CdlModeSpeedNormal 0
#define CdlModeSpeedDouble 1

/*
 * Status Contents
 */
#define CdlStatPlay 0x80      /* playing CD-DA */
#define CdlStatSeek 0x40      /* seeking */
#define CdlStatRead 0x20      /* reading data sectors */
#define CdlStatShellOpen 0x10 /* once shell open */
#define CdlStatSeekError 0x04 /* seek error detected */
#define CdlStatStandby 0x02   /* spindle motor rotating */
#define CdlStatError 0x01     /* command error detected */

/*
 * Interrupts
 */
#define CdlNoIntr 0x00      /* No interrupt */
#define CdlDataReady 0x01   /* Data Ready */
#define CdlComplete 0x02    /* Command Complete */
#define CdlAcknowledge 0x03 /* Acknowledge (reserved) */
#define CdlDataEnd 0x04     /* End of Data Detected */
#define CdlDiskError 0x05   /* Error Detected */

typedef struct {
    CdlLOC pos;    /* file location */
    u_long size;   /* file size */
    char name[16]; /* file name (body) */
} CdlFILE;

typedef void (*CdlCB)(u_char, u_char*);

void def_cbsync(u_char intr, u_char* result);
void def_cbready(u_char intr, u_char* result);
void def_cbread(u_char intr, u_char* result);

int CdInit(void);
int CdStatus(void);
int CdMode(void);
int CdLastCom(void);
int CdReset(int mode);
void CdFlush(void);
int CdSetDebug(int level);
char* CdComstr(u_char com);
char* CdIntstr(u_char intr);
int CdSync(int mode, u_char* result);
int CdReady(int mode, u_char* result);
long CdSyncCallback(void (*func)(void));
long CdReadyCallback(void (*func)(void));

// Issues direct primitive commands to the CD-ROM subsystem
int CdControl(u_char com, u_char* param, u_char* result);
int CdControlB(u_char com, u_char* param, u_char* result);
int CdControlF(u_char com, u_char* param);

/*
 * Sets the audio volume for CD audio (CD-DA, ADPCM).
 * Return value: 1
 */
int CdMix(CdlATV* vol // Pointer to attenuator volume
);

int CdGetSector(void* madr, int size);
long CdDataCallback(void (*func)());
CdlLOC* CdIntToPos(int i, CdlLOC* p);
int CdPosToInt(CdlLOC* p);
CdlFILE* CdSearchFile(CdlFILE* fp, char* name);
int CdRead(int sectors, u_long* buf, int mode);
int CdReadSync(int mode, u_char* result);
CdlCB CdReadCallback(CdlCB func);
int CdRead2(long mode);

void StClearRing(void);
void StSetStream(u_long mode, u_long start_frame, u_long end_frame,
                 void (*func1)(), void (*func2)());

void StSetMask(u_long mask, u_long start, u_long end);
u_long StGetNext(u_long** addr, u_long** header);
u_long StFreeRing(u_long* base);
int StGetBackloc(CdlLOC* loc);
void StSetRing(u_long* ring_addr, u_long ring_size1);
void StUnSetRing(void);

#endif // LIBCD_H
