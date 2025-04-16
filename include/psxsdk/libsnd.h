#ifndef LIBSND_H
#define LIBSND_H

#ifdef VERSION_PC
// crashes in SetTableSize otherwise
#define SS_SEQ_TABSIZ 192
#else
#define SS_SEQ_TABSIZ 176
#endif
#define SS_NOTICK 0x1000
#define SS_NOTICK0 0
#define SS_TICK60 1
#define SS_TICK240 2
#define SS_TICK120 3
#define SS_TICK50 4
#define SS_TICKVSYNC 5
#define SS_TICKMODE_MAX 6

#define SS_IMEDIATE 0
#define SS_IMMEDIATE 0
#define SS_WAIT_COMPLETED 1

#define SS_REV_TYPE_OFF 0
#define SS_REV_TYPE_ROOM 1
#define SS_REV_TYPE_STUDIO_A 2
#define SS_REV_TYPE_STUDIO_B 3
#define SS_REV_TYPE_STUDIO_C 4
#define SS_REV_TYPE_HALL 5
#define SS_REV_TYPE_SPACE 6
#define SS_REV_TYPE_ECHO 7
#define SS_REV_TYPE_DELAY 8
#define SS_REV_TYPE_PIPE 9

#define SS_SOFF 0
#define SS_SON 1
#define SS_MIX 0
#define SS_REV 1
#define SS_SERIAL_A 0
#define SS_SERIAL_B 1

// Closes the SEQ data holding the seq_acces_num that is no longer necessary.
extern void SsSeqClose(short seq_access_num);

/**
 * Sets the main volume value in voll and volr respectively.
 * Each can be set from 0 to 127.
 * It is essential to set it before SEQ data is played.
 */
extern void SsSetMVol(short voll, short volr);

// Carries out attribute setting relating to CD audio.
extern void SsSetSerialAttr(char s_num, char attr, char mode);
/**
 * Sets the CD volume value in voll and volr.
 * The volume value can be set from 0 to 127.
 */
extern void SsSetSerialVol(short s_num, short voll, short volr);

/**
 * Clears the area occupied by the reverb work
 * area corresponding to the reverb mode.
 * Returns 0 if successful.
 */
extern long SpuClearReverbWorkArea(long rev_mode // Reverb mode
);

/**
 * Initializes the sound system, without destroying data that has been
 * transferred to the sound buffer. Using Exec()-related functions, when a child
 * process wants to initialize the sound system with the sound buffer in its
 * current state, it should call SsInitHot() instead of calling SsInit().
 */
void SsInitHot(void);

/**
 * Declares the number of voices that the libsnd voice allocation management
 * system has access to. Other voices can be keyed on in libspu or via
 * SsUtKeyOnV(). Voice numbers are reserved from the lower end (from 0).
 * For example, if voices = 20, then:
 * (*) Voices 0-19 are used for allocation by libsnd.
 * (*) Voices 20-23 are available for libspu.
 *
 * Returns the set voice count if successful. Returns -1 if unsuccessful
 */
char SsSetReservedVoice(char voices // Voice count
);

/**
 * Sets the resolution of a tick. Call this function only once before calling
 * SsSeqOpen(), SsSepOpen() or SsStart() for the first time. When it is called
 * multiple times, correct operation cannot be guaranteed.
 */
void SsSetTickMode(long tick_mode // Tick mode
);

/**
 * Starts the sound system.When SsSetTickMode() is used to set
 * a mode that calls SsSeqCalledTbyT() automatically, this
 * function causes SsSeqCalledTbyT() to be called each tick.
 */
void SsStart(void);

/**
 * Keys on the voice specified by the voice number (0-23), the VAB number, the
 * program number (0-127), and the tone number (0-15) at the specified pitch and
 * volume, and returns the allocated voice number.
 */
short SsUtKeyOnV(
    short voice, // Voice number (0-23)
    short vabId, // VAB number (0-31) returned by SsVabOpenHead()
    short prog,  // Program number (0-127)
    short tone,  // Tone number (0-15)
    short note,  // Pitch specification in semitones (note number) (0-127)
    short fine,  // Detailed pitch specification (100/127 cents) (0-127)
    short voll,  // Volume, left (0-127)
    short volr   // Volume, right (0-127)
);

// Sets the left and right volumes of the specified voice, vc. Since libsnd uses
// an exponential volume calculation for sounds being keyed on, the input
// volumes voll and volr are modified as (vol * vol / 127).
// 0 if successful, -1 if unsuccessful.
short SsUtSetVVol(short vc,   // Voice number (0-23)
                  short voll, // Volume left (0-127)
                  short volr  // Volume right (0-127)
);

void SpuGetAllKeysStatus(s8* status);

// Specify the area of a SEQ/SEP data attribute table
void SsSetTableSize(
    char* table, // Pointer to SEQ/SEP data attribute table area variable
    short s_max, // Maximum times to open SEQ/SEP data (up to 32)
    short t_max  // Number of SEQ included in SEP
);

// Terminate SEQ data reading.
void SsSeqStop(short seq_access_num // SEQ access number
);

// Sets the output to monaural mode. Forces all libsnd keyed-on voices to have
// equivalent left and right volumes.Stereo mode is the system default mode.
void SsSetMono(void);

// Sets the output to stereo mode. The sound system default output is stereo.
void SsSetStereo(void);

// Open a VAB header and specify transfer address in sound buffer.
s32 /*short*/ SsVabOpenHeadSticky(
    u_char* addr, // Start address of VAB header (.VH) in main memory
    u_long vabid, // Desired VAB ID or -1
    u_long sbaddr // Start address in sound buffer where VabBody is to be
                  // transferred
);

// Starts transferring a VAB body in main memory, whose VAB header was opened
// with SsVabOpenHead(), to the sound buffer.
s32 /*short*/ SsVabTransBodyPartly(
    u_char* addr, // Pointer to starting address of the segment transfer buffer
    u_long bufsize, // Buffer size
    u_long vabid    // VAB ID
);

// Determines whether data transfer to SPU local memory has terminated
s32 /*short*/ SsVabTransCompleted(
    short immediateFlag // Transfer status recognition flag
);

// Set reverb type
void SsUtSetReverbType(short type);

// Turns on global Reverb at the type and depth set by SsUtSetReverbType() and
// SsUtSetReverbDepth().
void SsUtReverbOn(void);

// Set a reverb depth
void SsUtSetReverbDepth(
    short ldepth, // Left channel depth. Value between 0 and 127
    short rdepth  // Right channel depth. Value between 0 and 127
);

void SsUtSetReverbDelay(short delay);

#endif
