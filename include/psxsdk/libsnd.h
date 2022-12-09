#ifndef LIBSND_H
#define LIBSND_H

// Closes the SEQ data holding the seq_acces_num that is no longer necessary.
extern void SsSeqClose(short seq_access_num);

/*
 * Sets the main volume value in voll and volr respectively.
 * Each can be set from 0 to 127.
 * It is essential to set it before SEQ data is played.
 */
extern void SsSetMVol(short voll, short volr);

// Carries out attribute setting relating to CD audio.
extern void SsSetSerialAttr(char s_num, char attr, char mode);
/*
 * Sets the CD volume value in voll and volr.
 * The volume value can be set from 0 to 127.
 */
extern void SsSetSerialVol(short s_num, short voll, short volr);

#endif
