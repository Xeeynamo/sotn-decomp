#ifndef SPR_H
#define SPR_H

#include "xpt.h"
#include "def.h"
#include "mth.h"

#define SPR_SYNC_VB_OUT
#if 0
#define USE_SLAVE
#define USE_DSP
#define USE_INBETWEEN_OBJECT
#define USE_DEBUG_INFO
#endif
#define USE_ERASE_POLIGON

#define _PC_ 0
#define _INDIGO2_ 1
#define _SH_ 2

#define NO_EXIST 0
#define EXIST 1

#if defined(_PC)
#define _MACHINE _PC_
#define _DSP NO_EXIST
#define _MATH EXIST
#endif

#if defined(_INDIGO2)
#define _MACHINE _INDIGO2_
#define _DSP NO_EXIST
#define _MATH EXIST
#endif

#if defined(_SH)
#define _MACHINE _SH_
#define _DSP EXIST
#define _MATH NO_EXIST
#endif

#ifdef _SPR3_
#define _SPR2_
#endif

typedef void PARA_RTN(void* parm);
void SPR_InitSlaveSH(void);
void SPR_RunSlaveSH(PARA_RTN* routine, void* parm);
void SPR_WaitEndSlaveSH(void);

#define VRAM_SIZE 512 * 1024
#define FBUF_SIZE 256 * 1024

#define AUTO_FRAME_CHG 0
#define MANUAL_FRAME_CHG 1
#define NO_INTER_FRAME_CHG 2
#define NO_INTER_VBE_FRAME_CHG 3

#define SPR_FBCR_MANUAL 0x0003
#define SPR_FBCR_AUTO 0x0000
#define SPR_FBCR_ERASE 0x0002
#define SPR_FBCR_DIE 0x0008
#define SPR_FBCR_DIL 0x0004
#define SPR_FBCR_EOS 0x0010

#define SPR_TV_NORMAL 0
#define SPR_TV_HIRESO 1
#define SPR_TV_ROT16 2
#define SPR_TV_ROT8 3
#define SPR_TV_HDTV 4

#define SPR_TV_320X224 0
#define SPR_TV_320X240 1
#define SPR_TV_352X224 2
#define SPR_TV_352X240 3
#define SPR_TV_640X224 4
#define SPR_TV_640X240 5
#define SPR_TV_704X224 6
#define SPR_TV_704X240 7

#define SPR_W_TVMR 0x00000000
#define SPR_W_FBCR 0x00000002
#define SPR_W_PTMR 0x00000004
#define SPR_W_EWDR 0x00000006
#define SPR_W_EWLR 0x00000008
#define SPR_W_EWRR 0x0000000A
#define SPR_W_ENDR 0x0000000C
#define SPR_R_EDSR 0x00000010
#define SPR_R_LOPR 0x00000012
#define SPR_R_COPR 0x00000014
#define SPR_R_MODR 0x00000016

#define SPR_R_EXTEN 0x00000002
#define SPR_R_TVSTAT 0x00000004
#define SPR_R_VCNT 0x0000000A

#define VRAM_ADDR 0x25C00000
#define FBUF_ADDR 0x25C80000
#define VDP1_REG_BASE 0x25D00000
#define VDP2_REG_BASE 0x25F80000

struct SprSpStatus {
    Uint16 frameChgMode;
    Uint16 frameEraseMode;
    Uint16 vbInterval;
    Uint16 eraseData;
    Uint16 eraseLeftX;
    Uint16 eraseTopY;
    Uint16 eraseRightX;
    Uint16 eraseBotY;
};

typedef struct SprSpStatus SprSpStatus;

#define SPR_WRITE_REG(reg, val)                                                \
    *(volatile Uint16*)(VDP1_REG_BASE + (reg)) = (val)
#define SPR_READ_REG(reg) (*(volatile Uint16*)(VDP1_REG_BASE + (reg)))
#define SPR_SCLWRITE_REG(reg, val)                                             \
    *(volatile Uint16*)(VDP2_REG_BASE + (reg)) = (val)
#define SPR_SCLREAD_REG(reg) (*(volatile Uint16*)(VDP2_REG_BASE + (reg)))

#if 0
#else
extern Sint32 SpScreenX;
extern Sint32 SpScreenY;
extern volatile Uint16 SpFrameChgMode;
extern volatile Sint32 SpFrameEraseMode;
extern volatile Sint32 VBInterval;
extern volatile Sint32 VBIntervalCounter;
extern volatile Sint32 ReqDisplayFlag;
extern Uint16 SpTvMode;
extern Uint16 SpFbcrMode;
extern Uint16 SpDie;
extern Uint16 SpDil;
#endif

void SPR_Initial(Uint8** VRAM);
void SPR_SetTvMode(Uint16 mode, Uint16 screenSize, Uint16 doubleInterlace);
void SPR_GetStatus(SprSpStatus* spStatus);
void SPR_SetEraseData(
    Uint16 eraseData, Uint16 leftX, Uint16 topY, Uint16 rightX, Uint16 botY);
void SPR_WaitDrawEnd(void);
void SPR_SetEosMode(Sint32 eosFlag);
void sprMemCpyL(void* dst, void* src, int count);
void sprMemCpyW(void* dst, void* src, int count);

#ifdef _SPR2_

#define FIXED32_MIN 0x80000000
#define FIXED32_MAX 0x7fffffff

#define CTRL_END 0x8000
#define CTRL_SKIP 0x4000
#define CTRL_JUMP 0x3000
#define CTRL_ZOOM 0x0f00
#define CTRL_FUNC 0x000f
#define CTRL_DIR 0x0030

#define DRAW_COMPO 0x0003
#define DRAW_GOURAU 0x0004
#define DRAW_GOURAU_GRAY 0x0804
#define DRAW_COLOR 0x0038
#define DRAW_MESH 0x0100

#define COMPO_REP 0x0000
#define COMPO_SHADOW 0x0001
#define COMPO_HARF 0x0002
#define COMPO_TRANS 0x0003

#define FUNC_NORMALSP 0x0000
#define FUNC_SCALESP 0x0001
#define FUNC_DISTORSP 0x0002
#define FUNC_POLYGON 0x0004
#define FUNC_POLYLINE 0x0005
#define FUNC_LINE 0x0006
#define FUNC_SCLIP 0x0009
#define FUNC_UCLIP 0x0008
#define FUNC_LCOORD 0x000a
#define FUNC_TEXTURE 0x0004

#define JUMP_NEXT 0x0000
#define JUMP_ASSIGN 0x1000
#define JUMP_CALL 0x2000
#define JUMP_RETURN 0x3000
#define SKIP_NEXT 0x4000
#define SKIP_ASSIGN 0x5000
#define SKIP_CALL 0x6000
#define SKIP_RETURN 0x7000

#define ZOOM_NOPOINT 0x0000
#define ZOOM_TL 0x0500
#define ZOOM_TM 0x0600
#define ZOOM_TR 0x0700
#define ZOOM_ML 0x0900
#define ZOOM_MM 0x0a00
#define ZOOM_MR 0x0b00
#define ZOOM_BL 0x0c00
#define ZOOM_BM 0x0e00
#define ZOOM_BR 0x0f00

#define DIR_NOREV 0x0000
#define DIR_TBREV 0x0020
#define DIR_LRREV 0x0010
#define DIR_LRTBREV 0x0030

#define ECD_DISABLE 0x0080
#define SPD_DISABLE 0x0040
#define ECDSPD_DISABLE 0x00c0
#define UCLPIN_ENABLE 0x0400
#define UCLPOUT_ENABLE 0x0600
#define HSS_ENABLE 0x1000
#define PCLP_ENABLE 0x0800

#define COLOR_0 0x0000
#define COLOR_1 0x0008
#define COLOR_2 0x0010
#define COLOR_3 0x0018
#define COLOR_4 0x0020
#define COLOR_5 0x0028

#define NO_GOUR 0xffff

#define SPR_2DRAW_PRTY_ON 1
#define SPR_2DRAW_PRTY_OFF 0
#define SPR_2MOST_FAR 0
#define SPR_2MOST_NEAR 0x7fffffff

struct SprSpCmd {
    Uint16 control;
    Uint16 link;
    Uint16 drawMode;
    Uint16 color;
    Uint16 charAddr;
    Uint16 charSize;
    Sint16 ax;
    Sint16 ay;
    Sint16 bx;
    Sint16 by;
    Sint16 cx;
    Sint16 cy;
    Sint16 dx;
    Sint16 dy;
    Uint16 grshAddr;
    Uint16 dummy;
};

struct SprSpCmdR {
    Uint32 dummy[8];
};

struct SprGourTbl {
    Uint16 entry[4];
};

struct SprGourTblR {
    Uint32 entry[2];
};

struct SprLookupTbl {
    Uint16 entry[16];
};

typedef Uint16 Vaddr;
typedef struct SprSpCmd SprSpCmd;
typedef struct SprSpCmdR SprSpCmdR;
typedef struct SprGourTbl SprGourTbl;
typedef struct SprGourTblR SprGourTblR;
typedef struct SprLookupTbl SprLookupTbl;
typedef struct SprAreaSize SprAreaSize;

typedef struct SprCharTbl SprCharTbl;
typedef struct SprDrawPrtyBlk SprDrawPrtyBlk;
typedef struct Spr2WorkArea Spr2WorkArea;

struct SprCharTbl {
    Vaddr addr;
    Uint16 xySize;
    Uint16 mode;
    Uint16 color;
    Uint16 size;
};

struct SprDrawPrtyBlk {
    Uint16 topNo;
    Uint16 botNo;
};

struct Spr2WorkArea {
    Uint16 commandMax;
    Uint16 gourTblMax;
    Uint16 lookupTblMax;
    Uint16 charMax;
    Uint16 drawPrtyBlkMax;
    SprCharTbl* charTbl;
    SprSpCmd* mstCmd;
    SprDrawPrtyBlk* mstDrawPrtyBlk;
    SprSpCmd* slvCmd;
    SprDrawPrtyBlk* slvDrawPrtyBlk;
    SprGourTbl* gourTbl;
};

struct SprAreaSize {
    Uint16 commandMax;
    Uint16 gourTblMax;
    Uint16 lookupTblMax;
    Uint16 charMax;
    Uint16 drawPrtyBlkMax;
    Uint16 useCommandCount;
    Uint16 charRemainBlkCount;
    Uint16 charNullBlkMaxSize;
};

extern Sint32 SpLCoordX;
extern Sint32 SpLCoordY;

#ifdef _SPR3_
#define SPR_2DefineWork(sp2WorkArea, sp2CommandMax, sp2GourTblMax,             \
                        sp2LookupTblMax, sp2CharMax, sp2DrawPrtyBlkMax)        \
    static SprCharTbl sp2CharTbl[sp2CharMax];                                  \
    static SprSpCmdR sp2MstSpCmd[sp2CommandMax / 2];                           \
    static SprDrawPrtyBlk sp2MstDrawPrtyBlk[sp2DrawPrtyBlkMax];                \
    static SprSpCmdR sp2SlvSpCmd[sp2CommandMax / 2];                           \
    static SprDrawPrtyBlk sp2SlvDrawPrtyBlk[sp2DrawPrtyBlkMax];                \
    static SprGourTblR sp2GourTbl[sp2GourTblMax + 32];                         \
    static Spr2WorkArea sp2WorkArea = {                                        \
        sp2CommandMax,          sp2GourTblMax + 32,                            \
        sp2LookupTblMax,        sp2CharMax,                                    \
        sp2DrawPrtyBlkMax,      sp2CharTbl,                                    \
        (SprSpCmd*)sp2MstSpCmd, sp2MstDrawPrtyBlk,                             \
        (SprSpCmd*)sp2SlvSpCmd, sp2SlvDrawPrtyBlk,                             \
        (SprGourTbl*)sp2GourTbl};
#else
#define SPR_2DefineWork(sp2WorkArea, sp2CommandMax, sp2GourTblMax,             \
                        sp2LookupTblMax, sp2CharMax, sp2DrawPrtyBlkMax)        \
    static SprCharTbl sp2CharTbl[sp2CharMax];                                  \
    static SprSpCmdR sp2MstSpCmd[sp2CommandMax];                               \
    static SprDrawPrtyBlk sp2MstDrawPrtyBlk[sp2DrawPrtyBlkMax];                \
    static SprGourTblR sp2GourTbl[sp2GourTblMax + 1];                          \
    static Spr2WorkArea sp2WorkArea = {                                        \
        sp2CommandMax,                                                         \
        sp2GourTblMax,                                                         \
        sp2LookupTblMax,                                                       \
        sp2CharMax,                                                            \
        sp2DrawPrtyBlkMax,                                                     \
        sp2CharTbl,                                                            \
        (SprSpCmd*)sp2MstSpCmd,                                                \
        sp2MstDrawPrtyBlk,                                                     \
        NULL,                                                                  \
        NULL,                                                                  \
        (SprGourTbl*)sp2GourTbl};
#endif

void SPR_2Initial(Spr2WorkArea* workArea);

void SPR_2Initial2(Spr2WorkArea* workArea);
void SPR_2SetTvMode(Uint16 mode, Uint16 screenSize, Uint16 doubleInterlace);
void SPR_2FrameChgIntr(Uint16);
void SPR_2FrameEraseData(Uint16);
void SPR_2SetGourTbl(Uint16, SprGourTbl*);
void SPR_2SetLookupTbl(Uint16, SprLookupTbl*);
#if 0
#else
int SPR_2SetChar(Uint16, Uint16, Uint16, Uint16, Uint16, Uint8*);
#endif
void SPR_2ClrChar(Uint16);
void SPR_2ClrAllChar(void);
Uint16 SPR_2GourTblNoToVram(Uint16);
Uint16 SPR_2LookupTblNoToVram(Uint16);
Uint16 SPR_2CharNoToVram(Uint16);
void SPR_2GetAreaSizeInfo(SprAreaSize* areaSizeInfo);
void SPR_2OpenCommand(Uint16);
void SPR_2CloseCommand(void);
void SPR_2FlushDrawPrty(void);
void SPR_2LocalCoord(Sint32, XyInt*);
void SPR_2SysClip(Sint32, XyInt*);
void SPR_2UserClip(Sint32, XyInt*);
void SPR_2Line(Sint32, Uint16, Uint16, XyInt*, Uint16);
void SPR_2PolyLine(Sint32, Uint16, Uint16, XyInt*, Uint16);
void SPR_2Polygon(Sint32, Uint16, Uint16, XyInt*, Uint16);
void SPR_2NormSpr(Sint32, Uint16, Uint16, Uint16, Uint16, XyInt*, Uint16);
void SPR_2ScaleSpr(Sint32, Uint16, Uint16, Uint16, Uint16, XyInt* xy, Uint16);
void SPR_2DistSpr(Sint32, Uint16, Uint16, Uint16, Uint16, XyInt* xy, Uint16);
void SPR_2Cmd(Sint32, SprSpCmd*);

#endif

#ifdef _SPR3_

typedef struct SprCluster SprCluster;
typedef struct SprObject3D SprObject3D;
typedef struct SprSurface SprSurface;
typedef struct SprInbetInf SprInbetInf;
typedef struct SprTexture SprTexture;
typedef struct Spr3dStatus Spr3dStatus;

typedef struct Spr3WorkArea Spr3WorkArea;

struct SprCluster {
    Uint16 no;
    Uint16 angleSeq;
    MthXyz angle;
    MthXyz point;
    SprObject3D* object;
    SprCluster* next;
    SprCluster* child;
    SprInbetInf* inbetInf;
    void (*transStart)(SprCluster*);

    void (*transEnd)(SprCluster*, SprObject3D*, MthMatrix*, MthXyz*);

    void* context;
};

struct SprObject3D {
    Uint16 no;
    Uint16 dispFlag;
    Uint16 vertCount;
    Uint16 surfaceCount;
    MthXyz* vertPoint;
    MthXyz* vertNormal;
    SprSurface* surface;
    MthXyz* surfaceNormal;
    void* filler;
    Uint16** shdIdxTbl;
    Fixed32 surfNormK;
    SprObject3D* next;
};

struct SprSurface {
    Uint16 vertNo[4];
    Uint16 drawMode;
    Uint16 color;
};

struct SprInbetInf {
    Sint32 vertCount;
    SprObject3D* fromObj;
    Uint16* fromVertNo;
    SprObject3D* toObj;
    Uint16* toVertNo;
    SprInbetInf* next;
};

struct SprTexture {
    Uint16 charNo;
    Uint16 colorMode;
    Uint16 color;
    Uint16 width;
    Uint16 height;
    Uint8* charData;
    SprLookupTbl* lookupTbl;
};

struct Spr3WorkArea {
    Uint16 objSurfMax;
    Uint16 objVertMax;
    Sint32* surfBright;
    Sint32* vertBright;
    MthXyz* coordView3D;
    XyInt* coord2D;
    MthXyz* coordWorld3D;
};

struct Spr3dStatus {
    MthXyz lightAngle;
    MthXyz viewCoordPoint;
    MthXyz viewPoint;
    MthXyz viewAngle;
    Sint32 viewAngleSeq;
    Sint32 zSortMode;
    Fixed32 zSortZMin;
    Fixed32 zSortZMax;
    Fixed32 clipZMin;
    Fixed32 clipZMax;
    Sint32 clipLevel;
    Sint32 unitPixelX;
    Sint32 unitPixelY;
};

typedef struct TComTbl TComTbl;
struct TComTbl {
    Fixed32 zSortBZMin;
    int zSftCnt;
    int zSortBlkCnt;
    Sint32 spriteDrawFlag;
    Sint32 otherDrawFlag;
    Sint32* unitPixel;
    Fixed32* clipRatio;
    Fixed32* clipZ;
    SprCharTbl* charTbl;
    Sint32* vertBright;
    MthXyz* coordView3D;
    XyInt* coord2D;
    int dispFlag;
    Uint16** shdIdxTbl;
    Uint32 gourGrayTopR;
    Uint32 lookupTblR;
    MthXyz* lightVector;
    MthMatrix* viewMatrix;
    MthMatrix* worldMatrix;
};

typedef struct T3Dto2D T3Dto2D;
struct T3Dto2D {
    int vertCount;
    int surfaceCount;
    SprSurface* surfInfo;
    MthXyz* vertPoint;
    MthXyz* surfaceNormal;
    MthXyz* vertNormal;
    MthXyz* coordView3D;
    XyInt* coord2D;
    Sint32* surfBright;
    Sint32* vertBright;
    MthXyz* coordWorld3D;
};

typedef struct T2DtoCmd T2DtoCmd;
struct T2DtoCmd {
    int surfaceCount;
    SprSurface* surface;
    Sint32* surfBright;
    Fixed32 zSortZMin;
    Fixed32 zSortZMax;
    SprDrawPrtyBlk* prtyTbl;
    SprSpCmd* cmdBuf;
    int outCmdPos;
    SprGourTbl* gourTblCur;
    Uint32 gourTblCurR;
};

typedef struct GetSurfNormPara GetSurfNormPara;
struct GetSurfNormPara {
    int surfaceCount;
    SprSurface* surface;
    MthXyz* vertPoint;
    Fixed32 surfNormK;
    MthXyz* surfaceNormal;
};

#define ROT_SEQ_ZYX 0x0000
#define ROT_SEQ_ZXY 0x0001
#define ROT_SEQ_YZX 0x0002
#define ROT_SEQ_YXZ 0x0003
#define ROT_SEQ_XYZ 0x0004
#define ROT_SEQ_XZY 0x0005

#define DISP_POLYGON 0x0000
#define DISP_POLYLINE 0x8000
#define DISP_MASK 0xc000
#define BOTH_FACE 0x1000

#define NO_SHADING 0x0000
#define FLAT_SHADING 0x0100
#define GOURAUD_SHADING 0x0200
#define SHADING_MASK 0x0300
#define INBETWEEN_OBJECT 0x0010

#define MATE_COLOR 0x0000
#define MATE_TEXTURE 0x4000
#define MATE_SHADING_TBL 0x8000
#define MATE_AUTO_SHADING 0xc000
#define MATE_MASK 0xc000

#define ZSORT_MIN 0x0000
#define ZSORT_MAX 0x1000
#define ZSORT_MID 0x2000
#define ZSORT_MASK 0x3000
#define ZSORT_FLOAT_MODE 0
#define ZSORT_FIXED_MODE 1

#define DRAW_MODE_MASK 0x07ff

#define SPR_3mac1(sp3ObjSurfMax) static Sint32 sp3SurfBright[sp3ObjSurfMax];

#ifdef SPR_3NEED_WORLD_VERT
#define SPR_3mac2(sp3ObjVertMax)                                               \
    static MthXyz sp3CoordView3D[sp3ObjVertMax];                               \
    static XyInt sp3Coord2D[sp3ObjVertMax];                                    \
    static Sint32 sp3VertBright[sp3ObjVertMax];                                \
    static MthXyz sp3CoordWorld3D[sp3ObjVertMax];
#else
#define SPR_3mac2(sp3ObjVertMax)                                               \
    static MthXyz sp3CoordView3D[sp3ObjVertMax];                               \
    static XyInt sp3Coord2D[sp3ObjVertMax];                                    \
    static Sint32 sp3VertBright[sp3ObjVertMax];
#endif

#ifdef SPR_3NEED_WORLD_VERT
#define SPR_3mac3(sp3WorkArea, sp3ObjSurfMax, sp3ObjVertMax)                   \
    static Spr3WorkArea sp3WorkArea = {                                        \
        sp3ObjSurfMax,  sp3ObjVertMax, sp3SurfBright,  sp3VertBright,          \
        sp3CoordView3D, sp3Coord2D,    sp3CoordWorld3D};
#else
#define SPR_3mac3(sp3WorkArea, sp3ObjSurfMax, sp3ObjVertMax)                   \
    static Spr3WorkArea sp3WorkArea = {                                        \
        sp3ObjSurfMax,  sp3ObjVertMax, sp3SurfBright, sp3VertBright,           \
        sp3CoordView3D, sp3Coord2D,    NULL};
#endif

#define SPR_3DefineWork(sp3WorkArea, sp3ObjSurfMax, sp3ObjVertMax)             \
    SPR_3mac1(sp3ObjSurfMax) SPR_3mac2(sp3ObjVertMax)                          \
        SPR_3mac3(sp3WorkArea, sp3ObjSurfMax, sp3ObjVertMax)

#ifdef USE_DEBUG_INFO
extern int dbgComputePol;
extern int dbgDrawPol;
#endif

void SPR_3Initial(Spr3WorkArea* workArea);
void SPR_3SetLight(Uint16 moveKind, MthXyz* lightAngle);
void SPR_3SetView(Uint16 moveKind, MthXyz* viewPoint, MthXyz* viewAngle,
                  Uint16 angleSeq, MthXyz* viewCoordPoint);
void SPR_3MoveCluster(
    SprCluster* cluster, Uint16 moveKind, MthXyz* angle, MthXyz* point);
void SPR_3DrawModel(SprCluster* rootCluster);
void SPR_3Flush(void);
void SPR_3SetTexture(SprTexture* texture);
void SPR_3ChangeTexColor(Uint16 charNo, Uint16 color, SprLookupTbl* lookupTbl);
void SPR_3ClrTexture(SprTexture* texture);
void SPR_3SetZSortMinMax(
    Uint16 pZSortMode, Fixed32 pZSortZMin, Fixed32 pZSortZMax);
void SPR_3SetClipLevel(Uint16 pClipLevel, Fixed32 pClipZMin, Fixed32 pClipZMax);
void SPR_3SetPixelCount(Uint16 pixelCountX, Uint16 pixelCountY);
void SPR_3GetStatus(Spr3dStatus* spr3dStatus);
void SPR_3CallAllCluster(SprCluster* cluster, void (*userFunc)(SprCluster*));
void SPR_3SetSurfNormVect(SprObject3D* obj);
void SPR_3SetDrawSpeed(Sint32 hssFlag, Sint32 eosFlag, Sint32 pclpFlag);
void SPR_3AllCoordTransClipPers(
    MthMatrix* matrix, MthXyz* src, MthXyz* ans, XyInt* ans2D, int vertCnt,
    Sint32* unitPixel, Fixed32* clipRatio, Fixed32* clipZ);
void SPR_3AllCoordTrans(
    MthMatrix* matrix, MthXyz* src, int vertCnt, MthXyz* ans);
void SPR_3AllSurfaceBright(
    MthMatrix* matrix, SprSurface* surfInfo, MthXyz* surfaceNormal,
    Sint32* surfaceBright, MthXyz* lightVector, Sint32 surfCnt,
    MthXyz* coordView3D);
void SPR_3AllVertBright(
    MthMatrix* matrix, MthXyz* vertNormal, Sint32* vertBright,
    MthXyz* lightVector, Sint32 vertCnt);

#define MTX_OP_CLEAR 1
#define MTX_OP_REV_Z 2
#define MTX_OP_MOV_XYZ 3
#define MTX_OP_ROT_X 4
#define MTX_OP_ROT_Y 5
#define MTX_OP_ROT_Z 6
#define MTX_OP_END 7

typedef struct SprDspMatrixOp {
    Fixed32 x;
    Fixed32 y;
    Fixed32 z;
    Sint32 opCode;
} SprDspMatrixOp;

typedef struct SprDspMatrixParm {
    MthMatrix* inputMatrix;
    MthMatrix* outputMatrix;
    SprDspMatrixOp op[15];
} SprDspMatrixParm;

void SPR_3MatrixCompoInit(void);
void SPR_3MatrixCompoExec(SprDspMatrixParm* dspMatrixParm);
void SPR_3MatrixCompoCheck(void);

#endif

#endif
#define SLAVE
