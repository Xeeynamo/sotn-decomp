#ifndef LIBSPU_H
#define LIBSPU_H

#define SPU_VOICE_VOLL (0x01 << 0)        // volume (left)
#define SPU_VOICE_VOLR (0x01 << 1)        // volume (right)
#define SPU_VOICE_VOLMODEL (0x01 << 2)    // volume mode (left)
#define SPU_VOICE_VOLMODER (0x01 << 3)    // volume mode (right)
#define SPU_VOICE_PITCH (0x01 << 4)       // tone (pitch setting)
#define SPU_VOICE_NOTE (0x01 << 5)        // tone (note setting)
#define SPU_VOICE_SAMPLE_NOTE (0x01 << 6) // waveform data sample note
#define SPU_VOICE_WDSA (0x01 << 7)        // waveform data start address
#define SPU_VOICE_ADSR_AMODE (0x01 << 8)  // ADSR Attack rate mode
#define SPU_VOICE_ADSR_SMODE (0x01 << 9)  // ADSR Sustain rate mode
#define SPU_VOICE_ADSR_RMODE (0x01 << 10) // ADSR Release rate mode
#define SPU_VOICE_ADSR_AR (0x01 << 11)    // ADSR Attack rate
#define SPU_VOICE_ADSR_DR (0x01 << 12)    // ADSR Decay rate
#define SPU_VOICE_ADSR_SR (0x01 << 13)    // ADSR Sustain rate
#define SPU_VOICE_ADSR_RR (0x01 << 14)    // ADSR Release rate
#define SPU_VOICE_ADSR_SL (0x01 << 15)    // ADSR Sustain level
#define SPU_VOICE_LSAX (0x01 << 16)       // start address for loop
#define SPU_VOICE_ADSR_ADSR1 (0x01 << 17) // ADSR adsr1 for `VagAtr'
#define SPU_VOICE_ADSR_ADSR2 (0x01 << 18) // ADSR adsr2 for `VagAtr'

#define SPU_REV_MODE (0x01 << 0)      // mode setting
#define SPU_REV_DEPTHL (0x01 << 1)    // reverb depth (left)
#define SPU_REV_DEPTHR (0x01 << 2)    // reverb depth (right)
#define SPU_REV_DELAYTIME (0x01 << 3) // Delay Time  (ECHO, DELAY only)
#define SPU_REV_FEEDBACK (0x01 << 4)  // Feedback    (ECHO only)

#define SPU_OFF 0
#define SPU_ON 1

#ifndef __SPU_IRQCALLBACK_PROC
#define __SPU_IRQCALLBACK_PROC
typedef void (*SpuIRQCallbackProc)(void);
#endif

typedef struct {
    short left;  // left channel
    short right; // right channel
} SpuVolume;

typedef struct {
    /* 0x00 */ unsigned long voice; // each voice is a bit value
    /* 0x04 */ unsigned long mask;  // settings attribute bit (invalid with Get)
    /* 0x08 */ SpuVolume volume;    // volume
    /* 0x0C */ SpuVolume volmode;   // volume mode
    /* 0x10 */ SpuVolume volumex;   // current volume (invalid with Set)
    /* 0x14 */ unsigned short pitch;       // tone (pitch setting)
    /* 0x16 */ unsigned short note;        // tone (note setting)
    /* 0x18 */ unsigned short sample_note; // tone (note setting)
    /* 0x1A */ short envx;         // current envelope value (invalid with Set)
    /* 0x1C */ unsigned long addr; // waveform data start address
    /* 0x20 */ unsigned long loop_addr; // loop start address
    /* 0x24 */ long a_mode;             // Attack rate mode
    /* 0x28 */ long s_mode;             // Sustain rate mode
    /* 0x2C */ long r_mode;             // Release rate mode
    /* 0x30 */ unsigned short ar;       // Attack rate
    /* 0x32 */ unsigned short dr;       // Decay rate
    /* 0x34 */ unsigned short sr;       // Sustain rate
    /* 0x36 */ unsigned short rr;       // Release rate
    /* 0x38 */ unsigned short sl;       // Sustain level
    /* 0x3A */ unsigned short adsr1;    // adsr1 for `VagAtr'
    /* 0x3C */ unsigned short adsr2;    // adsr2 for `VagAtr'
} SpuVoiceAttr;                         // size=0x3E

typedef struct {
    unsigned long mask; // settings mask
    long mode;          // reverb mode
    SpuVolume depth;    // reverb depth
    long delay;         // Delay Time  (ECHO, DELAY only)
    long feedback;      // Feedback    (ECHO only)
} SpuReverbAttr;

extern long SpuSetTransferMode(long mode);
extern unsigned long SpuWrite(unsigned char* addr, unsigned long size);

extern long SpuSetReverbModeParam(SpuReverbAttr* attr);

extern void SpuSetVoiceAttr(SpuVoiceAttr* arg);
extern void SpuSetKey(long on_off, unsigned long voice_bit);

extern long SpuMallocWithStartAddr(unsigned long addr, long size);

extern SpuIRQCallbackProc SpuSetIRQCallback(SpuIRQCallbackProc);

#endif
