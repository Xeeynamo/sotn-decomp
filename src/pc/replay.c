// SPDX-License-Identifier: AGPL-3.0-or-later
#include <game.h>
#include <psyz/input.h>
#include <psyz/log.h>
#include <psyz/video.h>
#include "pc.h"
#include <stdlib.h>
#include <string.h>

// Main recording header
#define RECORDING_MAGIC "SOTN"
#define RECORDING_VERSION 1

// Records architecture and operating system the recorded was generated from
#define CHUNK_MAGIC_OS "OS  "

// Reproduce command line arguments passed as CLI parameters
#define CHUNK_MAGIC_PARA "PARA"

// Reproduce inital game state
#define CHUNK_MAGIC_INIT "INIT"

// Intervaled input + drift check
#define CHUNK_MAGIC_PDRF "PDRF"

#define DEFAULT_RECORDING_PATH "recording.bin"

extern bool g_IsQuitRequested;

typedef struct {
    s16 posXHi;
    s16 posYHi;
    s32 stageId;
    s32 servant;
    u32 subWeapon;
    s32 level;
    u32 exp;
    s32 gold;
    s32 hp;
    s32 hpMax;
    s32 mp;
    s32 mpMax;
    s32 hearts;
    s32 heartsMax;
    u32 randomNext;
    u32 gameStep;
    u32 gameState;
    u32 cdStep;
} DriftRecord;

typedef struct {
    u32 randomNext;
    s32 playableCharacter;
    s32 playerX;
    s32 playerY;
    s32 stageId;
    s32 servant;
    u32 gameTimer;
    s32 gameClearFlag;
    u32 roomCount;
    u32 timer;
} InitScalars;

enum ReplayMode {
    REPLAY_MODE_NONE,
    REPLAY_MODE_RECORD,
    REPLAY_MODE_REPLAY,
};

static enum ReplayMode mode = REPLAY_MODE_NONE;
static FILE* file = NULL;
static bool didDrift = false;
static bool exitAfterReplay = false;
static bool fastReplay = false;

static unsigned pdrfFrameCount = 0;
static long pdrfCountFileOffset = 0;

static char* replayPadFrames = NULL;
static DriftRecord* replayDriftRecords = NULL;
static unsigned replayFrameCount = 0;
static unsigned replayFrameCursor = 0;

static void WriteChunkHeader(
    FILE* f, const char magic[4], unsigned version, unsigned length) {
    fwrite(magic, 1, 4, f);
    fwrite(&version, sizeof(version), 1, f);
    fwrite(&length, sizeof(length), 1, f);
}

static bool ReadChunkHeader(
    FILE* f, char magic[4], unsigned* version, unsigned* length) {
    if (fread(magic, 1, 4, f) != 4) {
        return false;
    }
    if (fread(version, sizeof(*version), 1, f) != 1) {
        return false;
    }
    if (fread(length, sizeof(*length), 1, f) != 1) {
        return false;
    }
    return true;
}

static void CaptureDriftRecord(DriftRecord* out) {
    out->posXHi = g_Entities[0].posX.i.hi;
    out->posYHi = g_Entities[0].posY.i.hi;
    out->stageId = g_StageId;
    out->servant = g_Servant;
    out->subWeapon = g_Status.subWeapon;
    out->level = g_Status.level;
    out->exp = g_Status.exp;
    out->gold = g_Status.gold;
    out->hp = g_Status.hp;
    out->hpMax = g_Status.hpMax;
    out->mp = g_Status.mp;
    out->mpMax = g_Status.mpMax;
    out->hearts = g_Status.hearts;
    out->heartsMax = g_Status.heartsMax;
    out->randomNext = g_randomNext;
    out->gameStep = g_GameStep;
    out->gameState = g_GameState;
    out->cdStep = g_CdStep;
}

#define DRIF_FIELD_MISMATCH(field)                                             \
    if (a->field != b->field) {                                                \
        WARNF("  ." #field " expected=%d actual=%d", (int)b->field,            \
              (int)a->field);                                                  \
        matched = false;                                                       \
    }

static bool DriftRecordsMatch(const DriftRecord* a, const DriftRecord* b) {
    bool matched = true;
    DRIF_FIELD_MISMATCH(posXHi);
    DRIF_FIELD_MISMATCH(posYHi);
    DRIF_FIELD_MISMATCH(stageId);
    DRIF_FIELD_MISMATCH(servant);
    DRIF_FIELD_MISMATCH(subWeapon);
    DRIF_FIELD_MISMATCH(level);
    DRIF_FIELD_MISMATCH(exp);
    DRIF_FIELD_MISMATCH(gold);
    DRIF_FIELD_MISMATCH(hp);
    DRIF_FIELD_MISMATCH(hpMax);
    DRIF_FIELD_MISMATCH(mp);
    DRIF_FIELD_MISMATCH(mpMax);
    DRIF_FIELD_MISMATCH(hearts);
    DRIF_FIELD_MISMATCH(heartsMax);
    DRIF_FIELD_MISMATCH(randomNext);
    DRIF_FIELD_MISMATCH(gameStep);
    DRIF_FIELD_MISMATCH(gameState);
    DRIF_FIELD_MISMATCH(cdStep);
    return matched;
}

static void WriteOsChunk(FILE* f) {
    char osName[8] = {0};
    char arch[8] = {0};

#if defined(_WIN32)
    strncpy(osName, "Windows", sizeof(osName));
#elif defined(__APPLE__)
    strncpy(osName, "macOS", sizeof(osName));
#elif defined(__linux__)
    strncpy(osName, "Linux", sizeof(osName));
#else
    strncpy(osName, "Unknown", sizeof(osName));
#endif

#if defined(__x86_64__) || defined(_M_X64)
    strncpy(arch, "x86_x64", sizeof(arch));
#elif defined(__i386__) || defined(_M_IX86)
    strncpy(arch, "i386", sizeof(arch));
#elif defined(__aarch64__) || defined(_M_ARM64)
    strncpy(arch, "ARM64", sizeof(arch));
#elif defined(__arm__) || defined(_M_ARM)
    strncpy(arch, "ARM", sizeof(arch));
#elif defined(__riscv)
    strncpy(arch, "RISC-V", sizeof(arch));
#else
    strncpy(arch, "Unknown", sizeof(arch));
#endif

    WriteChunkHeader(f, CHUNK_MAGIC_OS, 1, sizeof(osName) + sizeof(arch));
    fwrite(osName, 1, sizeof(osName), f);
    fwrite(arch, 1, sizeof(arch), f);
}

static void WriteParamChunk(FILE* f, const struct InitGameParams* params) {
    s32 stage = params->stage;
    s32 player = params->player;
    WriteChunkHeader(f, CHUNK_MAGIC_PARA, 1, sizeof(stage) + sizeof(player));
    fwrite(&stage, sizeof(stage), 1, f);
    fwrite(&player, sizeof(player), 1, f);
}

static void ApplyParaChunk(FILE* f, unsigned length) {
    long chunkEnd = ftell(f) + (long)length;
    s32 stage;
    s32 player;

    if (fread(&stage, sizeof(stage), 1, f) != 1 ||
        fread(&player, sizeof(player), 1, f) != 1) {
        WARNF("PARA chunk is malformed, skipping remaining bytes");
        fseek(f, chunkEnd, SEEK_SET);
        return;
    }

    g_GameParams.stage = stage;
    g_GameParams.player = player;

    fseek(f, chunkEnd, SEEK_SET);
}

static void WriteInitChunk(FILE* f) {
    InitScalars scalars;
    unsigned statusSize = sizeof(PlayerStatus);
    unsigned castleMapSize = sizeof(g_CastleMap);
    unsigned settingsSize = sizeof(GameSettings);
    unsigned navSize = sizeof(MenuNavigation);
    unsigned length;

    scalars.randomNext = g_randomNext;
    scalars.playableCharacter = g_PlayableCharacter;
    scalars.playerX = g_PlayerX;
    scalars.playerY = g_PlayerY;
    scalars.stageId = g_StageId;
    scalars.servant = g_Servant;
    scalars.gameTimer = g_GameTimer;
    scalars.gameClearFlag = g_GameClearFlag;
    scalars.roomCount = g_RoomCount;
    scalars.timer = g_Timer;

    length = sizeof(scalars) + sizeof(unsigned) + statusSize +
             sizeof(unsigned) + castleMapSize + sizeof(unsigned) +
             settingsSize + sizeof(unsigned) + navSize;

    WriteChunkHeader(f, CHUNK_MAGIC_INIT, 1, length);
    fwrite(&scalars, sizeof(scalars), 1, f);

    fwrite(&statusSize, sizeof(statusSize), 1, f);
    fwrite(&g_Status, statusSize, 1, f);

    fwrite(&castleMapSize, sizeof(castleMapSize), 1, f);
    fwrite(g_CastleMap, castleMapSize, 1, f);

    fwrite(&settingsSize, sizeof(settingsSize), 1, f);
    fwrite(&g_Settings, settingsSize, 1, f);

    fwrite(&navSize, sizeof(navSize), 1, f);
    fwrite(&g_MenuNavigation, navSize, 1, f);
}

static void ApplyInitChunk(FILE* f, unsigned length) {
    InitScalars scalars;
    unsigned blobSize;
    long chunkEnd = ftell(f) + (long)length;

    if (fread(&scalars, sizeof(scalars), 1, f) != 1) {
        goto fail;
    }
    g_randomNext = scalars.randomNext;
    g_PlayableCharacter = scalars.playableCharacter;
    g_PlayerX = scalars.playerX;
    g_PlayerY = scalars.playerY;
    g_Servant = scalars.servant;
    g_GameTimer = scalars.gameTimer;
    g_GameClearFlag = scalars.gameClearFlag;
    g_RoomCount = scalars.roomCount;
    g_Timer = scalars.timer;

    if (fread(&blobSize, sizeof(blobSize), 1, f) != 1 ||
        blobSize != sizeof(PlayerStatus)) {
        goto fail;
    }
    if (fread(&g_Status, blobSize, 1, f) != 1) {
        goto fail;
    }

    if (fread(&blobSize, sizeof(blobSize), 1, f) != 1 ||
        blobSize != sizeof(g_CastleMap)) {
        goto fail;
    }
    if (fread(g_CastleMap, blobSize, 1, f) != 1) {
        goto fail;
    }

    if (fread(&blobSize, sizeof(blobSize), 1, f) != 1 ||
        blobSize != sizeof(GameSettings)) {
        goto fail;
    }
    if (fread(&g_Settings, blobSize, 1, f) != 1) {
        goto fail;
    }

    if (fread(&blobSize, sizeof(blobSize), 1, f) != 1 ||
        blobSize != sizeof(MenuNavigation)) {
        goto fail;
    }
    if (fread(&g_MenuNavigation, blobSize, 1, f) != 1) {
        goto fail;
    }

    fseek(f, chunkEnd, SEEK_SET);
    return;

fail:
    WARNF("INIT chunk is malformed, skipping remaining bytes");
    fseek(f, chunkEnd, SEEK_SET);
}

#define PDRF_FRAME_LEN (PSYZ_PAD_BUF_LEN + sizeof(DriftRecord))

static void LoadPdrfChunk(FILE* f, unsigned length) {
    long payloadStart = ftell(f);
    long chunkEnd = payloadStart + (long)length;
    unsigned frameCount;
    long fileEnd;
    unsigned i;

    if (fread(&frameCount, sizeof(frameCount), 1, f) != 1) {
        WARNF("PDRF chunk is malformed, skipping remaining bytes");
        fseek(f, chunkEnd, SEEK_SET);
        return;
    }

    fseek(f, 0, SEEK_END);
    fileEnd = ftell(f);
    if (length == 0 || chunkEnd > fileEnd) {
        chunkEnd = fileEnd;
        length = (u32)(chunkEnd - payloadStart);
        frameCount = (length - sizeof(frameCount)) / PDRF_FRAME_LEN;
        WARNF("PDRF chunk was not finalized with a clean shutdown; "
              "recovering %u frames from the rest of the file",
              frameCount);
    }
    fseek(f, payloadStart + sizeof(frameCount), SEEK_SET);

    replayPadFrames = malloc((size_t)frameCount * PSYZ_PAD_BUF_LEN);
    replayDriftRecords = malloc((size_t)frameCount * sizeof(DriftRecord));
    for (i = 0; i < frameCount; i++) {
        if (fread(&replayPadFrames[(size_t)i * PSYZ_PAD_BUF_LEN], 1,
                  PSYZ_PAD_BUF_LEN, f) != PSYZ_PAD_BUF_LEN ||
            fread(&replayDriftRecords[i], sizeof(DriftRecord), 1, f) != 1) {
            WARNF("PDRF chunk has fewer frames than declared; got %u of %u", i,
                  frameCount);
            frameCount = i;
            break;
        }
    }
    replayFrameCount = frameCount;
    replayFrameCursor = 0;

    fseek(f, chunkEnd, SEEK_SET);
}

static void ParseChunks(FILE* f) {
    char magic[4];
    unsigned version;
    unsigned length;

    while (ReadChunkHeader(f, magic, &version, &length)) {
        if (memcmp(magic, CHUNK_MAGIC_INIT, 4) == 0 && version == 1) {
            ApplyInitChunk(f, length);
        } else if (memcmp(magic, CHUNK_MAGIC_PARA, 4) == 0 && version == 1) {
            ApplyParaChunk(f, length);
        } else if (memcmp(magic, CHUNK_MAGIC_PDRF, 4) == 0 && version == 1) {
            LoadPdrfChunk(f, length);
        } else if (memcmp(magic, CHUNK_MAGIC_OS, 4) == 0) {
            fseek(f, length, SEEK_CUR);
        } else {
            WARNF("unrecognized recording chunk '%.4s' v%u, skipping %u bytes",
                  magic, version, length);
            fseek(f, length, SEEK_CUR);
        }
    }
}

// intervaled PAD0 input + drift detection record
static void RecordFrame(void) {
    char frame[PSYZ_PAD_BUF_LEN] = {0};
    Psyz_PadsGet(0, frame, sizeof(frame));
    fwrite(frame, 1, sizeof(frame), file);

    DriftRecord drift;
    CaptureDriftRecord(&drift);
    fwrite(&drift, sizeof(drift), 1, file);

    // ensure frame gets written in the event the game crashes right after
    fflush(file);
    pdrfFrameCount++;
}

static void ReplayFrameReal(void) {
    Psyz_PadsSet(
        0, &replayPadFrames[(size_t)replayFrameCursor * PSYZ_PAD_BUF_LEN],
        PSYZ_PAD_BUF_LEN);

    DriftRecord live;
    const DriftRecord* expected = &replayDriftRecords[replayFrameCursor];
    CaptureDriftRecord(&live);
    if (!didDrift && !DriftRecordsMatch(&live, expected)) {
        didDrift = true;
        WARNF("replay drifted from recording at frame %u; rest of the "
              "playthrough may be inaccurate",
              replayFrameCursor);
    }
    replayFrameCursor++;
}

static void ReplayFrame(void) {
    if (replayFrameCursor < replayFrameCount) {
        ReplayFrameReal();
    } else if (exitAfterReplay) {
        g_IsQuitRequested = true;
    } else if (fastReplay) {
        fastReplay = false;
        Psyz_VideoSetVsyncMode(PSYZ_VSYNC_AUTO);
    }
}

static void StartReplay(const struct InitGameParams* params) {
    char magic[4];
    unsigned version;

    file = fopen(params->replayPath, "rb");
    if (!file) {
        WARNF("failed to open '%s' for replay", params->replayPath);
        return;
    }
    if (fread(magic, 1, 4, file) != 4 || memcmp(magic, RECORDING_MAGIC, 4) ||
        fread(&version, sizeof(version), 1, file) != 1) {
        ERRORF("'%s' is not a valid recording file", params->replayPath);
        fclose(file);
        file = NULL;
        return;
    }
    if (version != RECORDING_VERSION) {
        ERRORF("'%s' has version %d but replay only accepts %d version",
               params->replayPath, version, RECORDING_VERSION);
        fclose(file);
        file = NULL;
        return;
    }
    ParseChunks(file);
    exitAfterReplay = params->exitAfterReplay;
    fastReplay = params->replayBoundlessFramerate;
    if (fastReplay) {
        Psyz_VideoSetVsyncMode(PSYZ_VSYNC_LIMITLESS);
    }
    mode = REPLAY_MODE_REPLAY;
}

static void StartRecording(const struct InitGameParams* params) {
    const char* path =
        params->recordPath ? params->recordPath : DEFAULT_RECORDING_PATH;
    file = fopen(path, "wb");
    if (!file) {
        WARNF("failed to open '%s' for recording", path);
        return;
    }
#if defined(__APPLE__) || defined(__linux__)
    int fd = fileno(file);
    if (fd >= 0) {
        // make fflush non-blocking, useful for very slow drives
        fcntl(fd, F_SETFL, fcntl(fd, F_GETFL, 0) | O_NONBLOCK);
    }
#endif
    fwrite(RECORDING_MAGIC, 1, 4, file);
    unsigned version = RECORDING_VERSION;
    fwrite(&version, sizeof(version), 1, file);

    WriteOsChunk(file);
    WriteParamChunk(file, params);
    WriteInitChunk(file);

    // we don't yet know how many frames the records will be, for now user 0.
    // if replaying will find a 0, it means the game likely crashed
    WriteChunkHeader(file, CHUNK_MAGIC_PDRF, 1, 0);
    pdrfCountFileOffset = ftell(file);
    unsigned placeholderFrameCount = 0;
    fwrite(&placeholderFrameCount, sizeof(placeholderFrameCount), 1, file);
    fflush(file);

    mode = REPLAY_MODE_RECORD;
}

void Replay_Init(const struct InitGameParams* params) {
    if (params->replayPath) {
        StartReplay(params);
    } else {
        // always record, useful for catching bugs
        StartRecording(params);
    }
}

void Replay_Reset(void) {
    if (mode == REPLAY_MODE_RECORD) {
        if (file) {
            fseek(file, pdrfCountFileOffset, SEEK_SET);
            fwrite(&pdrfFrameCount, sizeof(pdrfFrameCount), 1, file);
            fclose(file);
            file = NULL;
        }
        pdrfFrameCount = 0;
    } else if (mode == REPLAY_MODE_REPLAY) {
        if (file) {
            fclose(file);
            file = NULL;
        }
        free(replayPadFrames);
        replayPadFrames = NULL;
        free(replayDriftRecords);
        replayDriftRecords = NULL;
        replayFrameCount = 0;
        replayFrameCursor = 0;
        exitAfterReplay = false;
        fastReplay = false;
    }
    mode = REPLAY_MODE_NONE;
}

void Replay_OnFrame(void) {
    if (mode == REPLAY_MODE_RECORD) {
        RecordFrame();
    } else if (mode == REPLAY_MODE_REPLAY) {
        ReplayFrame();
    }
}

bool Replay_DidDrift(void) { return didDrift; }
