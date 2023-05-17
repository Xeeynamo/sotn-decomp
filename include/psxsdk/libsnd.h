#ifndef LIBSND_H
#define LIBSND_H

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

/*
 * Not known
 */
void func_80026D4C(s16, short voll, short volr);

#endif
