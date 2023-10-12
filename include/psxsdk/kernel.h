#ifndef KERNEL_H
#define KERNEL_H

#define DescMask 0xff000000
#define DescTH DescMask
#define DescHW 0xf0000000
#define DescEV 0xf1000000
#define DescRC 0xf2000000
#define DescUEV 0xf3000000 /* User event */
#define DescSW 0xf4000000  /* BIOS */

#define HwVBLANK (DescHW | 0x01) /* VBLANK */
#define HwGPU (DescHW | 0x02)    /* GPU */
#define HwCdRom (DescHW | 0x03)  /* CDROM Decorder */
#define HwDMAC (DescHW | 0x04)   /* DMA controller */
#define HwRTC0 (DescHW | 0x05)   /* RTC0 */
#define HwRTC1 (DescHW | 0x06)   /* RTC1 */
#define HwRTC2 (DescHW | 0x07)   /* RTC2 */
#define HwCNTL (DescHW | 0x08)   /* Controller */
#define HwSPU (DescHW | 0x09)    /* SPU */
#define HwPIO (DescHW | 0x0a)    /* PIO */
#define HwSIO (DescHW | 0x0b)    /* SIO */

#define HwCPU (DescHW | 0x10)    /* Exception */
#define HwCARD (DescHW | 0x11)   /* memory card */
#define HwCARD_0 (DescHW | 0x12) /* memory card */
#define HwCARD_1 (DescHW | 0x13) /* memory card */
#define SwCARD (DescSW | 0x01)   /* memory card */
#define SwMATH (DescSW | 0x02)   /* libmath */

#define RCntCNT0 (DescRC | 0x00) /* �\���s�N�Z�� */
#define RCntCNT1 (DescRC | 0x01) /* �������� */
#define RCntCNT2 (DescRC | 0x02) /* �V�X�e���N���b�N�W���� */
#define RCntCNT3 (DescRC | 0x03) /* �������� �^�[�Q�b�g�l�͂P�ɌŒ� */

#define RCntMdINTR 0x1000
#define RCntMdNOINTR 0x2000
#define RCntMdSC 0x0001
#define RCntMdSP 0x0000
#define RCntMdFR 0x0000
#define RCntMdGATE 0x0010

#define EvSpCZ 0x0001      /* counter becomes zero */
#define EvSpINT 0x0002     /* interrupted */
#define EvSpIOE 0x0004     /* end of i/o */
#define EvSpCLOSE 0x0008   /* file was closed */
#define EvSpACK 0x0010     /* command acknowledged */
#define EvSpCOMP 0x0020    /* command completed */
#define EvSpDR 0x0040      /* data ready */
#define EvSpDE 0x0080      /* data end */
#define EvSpTIMOUT 0x0100  /* time out */
#define EvSpUNKNOWN 0x0200 /* unknown command */
#define EvSpIOER 0x0400    /* end of read buffer */
#define EvSpIOEW 0x0800    /* end of write buffer */
#define EvSpTRAP 0x1000    /* general interrupt */
#define EvSpNEW 0x2000     /* new device */
#define EvSpSYSCALL 0x4000 /* system call instruction */
#define EvSpERROR 0x8000   /* error happned */
#define EvSpPERROR 0x8001  /* previous write error happned */
#define EvSpEDOM 0x0301    /* domain error in libmath */
#define EvSpERANGE 0x0302  /* range error in libmath */

#define EvMdINTR 0x1000
#define EvMdNOINTR 0x2000

#define EvStUNUSED 0x0000
#define EvStWAIT 0x1000
#define EvStACTIVE 0x2000
#define EvStALREADY 0x4000

#define TcbMdRT 0x1000  /* reserved by system */
#define TcbMdPRI 0x2000 /* reserved by system */

#define TcbStUNUSED 0x1000
#define TcbStACTIVE 0x4000

struct DIRENTRY {
    /* 0x00 */ char name[20];
    /* 0x14 */ long attr;
    /* 0x18 */ long size;
    /* 0x1C */ struct DIRENTRY* next;
    /* 0x20*/ long head;
    /* 0x24 */ char system[4];
}; // size = 0x28

void EnterCriticalSection(void);
void ExitCriticalSection(void);

long _card_info(long chan);
long _card_clear(long chan);
long _card_load(long chan);
void InitCARD(long val);
long StartCARD(void);

#endif
