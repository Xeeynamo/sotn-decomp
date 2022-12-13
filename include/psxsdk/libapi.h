
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

extern void InitHeap(unsigned long*, unsigned long);
extern long Load(char*, struct EXEC*);
extern long Exec(struct EXEC*, long, char**);
// GPU_cw
extern void _bu_init(void);
extern long open(char*, unsigned long);
extern long lseek(long, long, long);
extern long read(long, void*, long);
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
extern long Krom2RawAdd(unsigned long);
extern void ChangeClearPAD(long);
extern void StopPAD(void);
int PAD_init(s32 /*??*/, s32* /*??*/);
// PAD_dr
extern void FlushCache(void);
extern void DeliverEvent(unsigned long, unsigned long);
extern long TestEvent(long);
extern long OpenEvent(unsigned long, long, long, long (*func)());
extern long EnableEvent(long);
// ChangeClearRCnt
extern void _96_remove(void);
extern long SetRCnt(unsigned long, unsigned short, long);
extern long StartRCnt(unsigned long);