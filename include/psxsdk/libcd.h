
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
int CdSync(int mode, u_char* result);
int CdReady(int mode, u_char* result);
CdlCB CdSyncCallback(CdlCB func);
CdlCB CdReadyCallback(CdlCB func);
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
void(*CdDataCallback(void (*func)()));
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