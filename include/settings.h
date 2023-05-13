// Set custom values to override the original game values

// Enable some micro optimizations to make the code more efficient
#define USE_MICRO_OPTIMIZATIONS 0

// The PSX allows to select which speed to use when reading from the disk.
// The two modes are Normal and Double. The normal uses 1x speed at 150kB/s
// while the double uses the 2x speed at 300kB/s.
#define USE_CD_SPEED_DOUBLE 0

#if USE_MICRO_OPTIMIZATIONS == 0
// use the slower memcpy from the PSX SDK
#define MEMCPY memcpy
#else
// use a much faster memcpy
#define MEMCPY fast_memcpy
// TODO not sure where to store the new fast_memcpy
#endif