#include <stdio.h>
#include <stdlib.h>
#include "pc.h"

struct FileAsStringCbParams {
    bool (*callback)(const struct FileAsString*);
    void* param;
};
static bool _FileAsStringCb(const struct FileOpenRead* f) {
    void* content = malloc(f->length + 1);
    if (!content) {
        ERRORF("unable to allocate %d bytes for '%s'", f->length, f->filename);
        fclose(f);
        return false;
    }

    size_t bytesread = fread(content, 1, f->length, f->file);
    if (bytesread != f->length) {
        ERRORF("unable to read %d bytes for '%s'", f->length, f->filename);
        fclose(f);
        free(content);
        return false;
    }
    ((char*)content)[f->length] = '\0';

    struct FileAsStringCbParams* p = (struct FileAsStringCbParams*)f->param;
    struct FileAsString fc = {
        .filename = f->filename,
        .content = (const char*)content,
        .length = f->length + 1,
        .param = p->param,
    };
    bool r = p->callback(&fc);
    free(content);
    return true;
}

struct FileUseContentCbParams {
    bool (*callback)(const struct FileUseContent*);
    void* param;
};
static bool _FileUseContentCb(const struct FileOpenRead* f) {
    void* content = malloc(f->length);
    if (!content) {
        ERRORF("unable to allocate %d bytes for '%s'", f->length, f->filename);
        return false;
    }

    size_t bytesread = fread(content, 1, f->length, f->file);
    if (bytesread != f->length) {
        ERRORF("unable to read %d bytes for '%s'", f->length, f->filename);
        free(content);
        return false;
    }

    struct FileAsStringCbParams* p = (struct FileAsStringCbParams*)f->param;
    struct FileUseContent fc = {
        .filename = f->filename,
        .content = content,
        .length = f->length,
        .param = p->param,
    };
    bool r = p->callback(&fc);
    free(content);
    return r;
};

// Simply open a binary file and pass the handler to a reader callback by
// performing error handling and ensuring the file always gets closed.
// The callback will receive file name and file size, it will need to return
// true if successful.
bool FileOpenRead(
    bool (*cb)(const struct FileOpenRead*), const char* filename, void* param) {
    INFOF("open '%s'", filename);
    FILE* f = fopen(filename, "rb");
    if (f == NULL) {
        ERRORF("unable to open '%s'", filename);
        return false;
    }
    fseek(f, 0, SEEK_END);
    size_t len = ftell(f);
    fseek(f, 0, SEEK_SET);

    struct FileOpenRead s = {
        .filename = filename,
        .file = f,
        .length = len,
        .param = param,
    };
    bool r = cb(&s);
    fclose(f);
    return r;
}

// Read the content of a binary file into the specified buffer by maxlen bytes.
// The number of read bytes is returned; a negative value represents a failure.
int FileReadToBuf(const char* filename, void* dst, int offset, size_t maxlen) {
    INFOF("open '%s'", filename);
    FILE* f = fopen(filename, "rb");
    if (f == NULL) {
        ERRORF("unable to open '%s'", filename);
        return -1;
    }
    fseek(f, offset, SEEK_SET);
    size_t bytesRead = fread(dst, 1, maxlen, f);
    fclose(f);
    return (int)(bytesRead);
}

// Read the content of a file as a null-terminated string and pass it to
// the specified callback. The function will take care of both validation
// and allocation of the unmanaged resources.
// The callback needs to return true if the operation is successful.
bool FileAsString(bool (*cb)(const struct FileAsString* file),
                  const char* filename, void* param) {
    struct FileAsStringCbParams p = {cb, param};
    return FileOpenRead(_FileAsStringCb, filename, &p);
}

// Read the specified file into a buffer and pass it to the specified callback.
// The function will take care of both validation and deallocation.
// The callback needs to return true if the operation is successful.
bool FileUseContent(bool (*cb)(const struct FileUseContent* file, void* param),
                    const char* filename, void* param) {
    struct FileUseContentCbParams p = {cb, param};
    return FileOpenRead(_FileUseContentCb, filename, &p);
}
