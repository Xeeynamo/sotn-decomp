#ifndef LIBAPI_H
#define LIBAPI_H

struct EXEC {
    unsigned long pc0;
    unsigned long gp0;
    unsigned long t_addr;
    unsigned long t_size;
    unsigned long d_addr;
    unsigned long d_size;
    unsigned long b_addr;
    unsigned long b_size;
    unsigned long s_addr;
    unsigned long s_size;
    unsigned long sp, fp, gp, ret, base;
};

extern void InitHeap(void*, unsigned long);
extern long Load(char*, struct EXEC*);
extern long Exec(struct EXEC*, long, char**);
// GPU_cw
extern void _bu_init(void);

/*
 * Opens a device for low-level input/output and returns
 * the descriptor. Returns -1 on failure.
 */
extern long open(char* devname, // Pointer to a filename
                 int flag       // Open mode
);

extern long lseek(long, long, long);

/*
 * Reads n bytes from the descriptor
 * fd to the are specified by buf.
 * Returns the actual number of bytes
 * read into the are. An error returns -1
 */
extern long read(long fd,   // File descriptor
                 void* buf, // Pointer to read buffer address
                 long n     // Number of bytes to read
);
extern long write(long, void*, long);

/*
 * Close releases the file descriptor.
 * fd is returned when successful, and -1 in all other cases.
 */
extern int close(int fd // File descriptor
);

/*
 * Initializes the file system
 * Returns 1 if successful, 0 in all other cases.
 */
extern long format(char* fs // File system name
);

extern struct DIRENTRY* firstfile(char*, struct DIRENTRY*);
extern struct DIRENTRY* nextfile(struct DIRENTRY*);
extern long erase(char*);
extern void ChangeClearPAD(long);
extern void StopPAD(void);
int PAD_init(s32 /*??*/, s32* /*??*/);
// PAD_dr
extern void FlushCache(void);
extern void DeliverEvent(unsigned long, unsigned long);

/*
 * Checks to see whether or not the event specified by the descriptor
 * event has occurred. If so, the function restores the event state to
 * EvStACTIVE.
 * Returns 1 if the event is found to have occurred, 0 otherwise.
 */
extern long TestEvent(unsigned long event // Event descriptor
);
extern long OpenEvent(unsigned long, long, long, long (*func)());
extern long EnableEvent(long);
// ChangeClearRCnt
extern void _96_remove(void);
extern long SetRCnt(unsigned long, unsigned short, long);
extern long StartRCnt(unsigned long);
extern long GetRCnt(unsigned long);
extern long StopRCnt(unsigned long);
extern long ResetRCnt(unsigned long);

#endif
