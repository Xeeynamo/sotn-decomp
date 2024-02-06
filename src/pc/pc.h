#ifndef PC_H
#define PC_H

#define LEN(x) ((s32)(sizeof(x) / sizeof(*(x))))

#define VERSION_PC
#define VERSION_US
#define VERSION "us"

#include <stdio.h>
#include <log.h>

#define DISP_WIDTH 256
#define DISP_HEIGHT 256
#define SCREEN_SCALE 2

#define VRAM_W 1024
#define VRAM_H 512
#define VRAM_STRIDE 2048

typedef struct {
    const char* path;
    const void* content;
    size_t length;
} FileLoad;

typedef struct {
    const char* path;
    const char* content;
    size_t length;
    void* param;
} FileStringified;

bool FileRead(bool (*cb)(FILE* file), const char* path);
bool FileStringify(
    bool (*cb)(FileStringified* file), const char* path, void* param);
bool FileUseContent(
    bool (*cb)(FileLoad* file, void* param), const char* path, void* param);

const char* AnsiToSotnMenuString(const char* str);

#endif
