
extern void InitHeap (unsigned long *, unsigned long);
extern long Load(char *, struct EXEC *);
extern long Exec(struct EXEC *, long, char **);
// GPU_cw
extern void _bu_init(void);
extern long open(char *, unsigned long);
extern long lseek(long, long, long);
extern long read(long, void *, long);
extern long write(long, void *, long);
extern long close(long);
extern long format(char *);
extern struct DIRENTRY * firstfile(char *, struct DIRENTRY *);
extern struct DIRENTRY * nextfile(struct DIRENTRY *);
extern long erase(char *);
extern long Krom2RawAdd(unsigned long);
extern void ChangeClearPAD(long);
extern void StopPAD(void);
int PAD_init2(s32/*??*/, s32 */*??*/); 
// PAD_dr
extern void FlushCache(void);
extern void DeliverEvent(unsigned long, unsigned long);
extern long TestEvent(long);
extern long OpenEvent(unsigned long,long,long,long (*func)());
extern long EnableEvent(long);
// ChangeClearRCnt
extern void _96_remove(void);