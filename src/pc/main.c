// SPDX-License-Identifier: AGPL-3.0-or-later
#include <game.h>
#include "pc.h"
#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const char* allowed_stages[] = {
    "no0",      "no1",      "lib",       "cat",      "no2",     "chi",
    "dai",      "np3",      "cen",       "no4",      "are",     "top",
    "nz0",      "nz1",      "wrp",       "no1_alt",  "no0_alt", "",
    "dre",      "nz0_demo", "nz1_demo",  "lib_demo", "bo7",     "mar",
    "bo6",      "bo5",      "bo4",       "bo3",      "bo2",     "bo1",
    "bo0",      "st0",      "rno0",      "rno1",     "rlib",    "rcat",
    "rno2",     "rchi",     "rdai",      "rno3",     "rcen",    "rno4",
    "rare",     "rtop",     "rnz0",      "rnz1",     "rwrp",    "",
    "",         "",         "",          "",         "",        "rnz1_demo",
    "rbo8",     "rbo7",     "rbo6",      "rbo5",     "rbo4",    "rbo3",
    "rbo2",     "rbo1",     "rbo0",      "",         "mad",     "no3",
    "iwa_load", "iga_load", "hagi_load", "sel",      "te1",     "te2",
    "te3",      "te4",      "te5",       "top_alt"};
static const char* allowed_players[] = {"alu", "ric", "mar"};
static const char* allowed_tests[] = {"sndlib"};
#define PARSE_PARAM(param, allowed) parseStrParam(param, allowed, LEN(allowed))
static int parseIntParam(const char* param) {
    long i = strtol(param, NULL, 10);
    if (i != LONG_MIN && i != LONG_MAX && i >= 0) {
        return (int)i;
    }
    return -1;
}
static int parseStrParam(
    const char* param, const char* allowedValues[], int n) {
    long i;
    if (isdigit(param[0])) {
        i = strtol(param, NULL, 10);
        if (i != LONG_MIN && i != LONG_MAX && i >= 0) {
            return (int)i;
        }
    } else {
        for (i = 0; i < n; i++) {
            if (allowedValues[i][0] == '\0') {
                continue;
            }
            if (!strcmp(param, allowedValues[i])) {
                return i;
            }
        }
    }
    return -1;
}
static void printHelp(void) {
    printf("Usage: ./sotn [OPTIONS]\n");
    printf("Options:\n");
    printf("  --disk <path>      file name of the second track\n");
    printf("  --stage <stage>    stage name or ID (e.g., nz0)\n");
    printf("  --player <name>    player name or ID (e.g. ric)\n");
    printf("  --scale <number>   game internal resolution integer scale "
           "(default 1)\n");
    printf("  --test <mode>      run automated tests\n");
    printf("         sndlib      test sound library\n");
    printf("  --record <path>    record controller input to a file\n");
    printf("  --replay <path>    replay controller input from a file\n");
    printf("  --replay-and-exit  quit automatically once the replay ends\n");
    printf("  --replay-fast      disable frame limit during replay\n");
    printf("  --help             show this help message\n");
}
static void printAllowedParams(const char* allowedValues[], int n) {
    int i;
    printf("allowed params are: ");
    for (i = 0; i < n - 1; i++) {
        if (allowedValues[i][0] == '\0') {
            continue;
        }
        printf("%s, ", allowedValues[i]);
    }
    printf("%s\n", allowedValues[i - 1]);
}
static bool parseArgs(
    struct InitGameParams* outParams, int argc, char* argv[]) {
    assert(!!outParams);
    outParams->diskPath = NULL;
    outParams->testMode = NO_TEST;
    outParams->stage = -1;
    outParams->player = -1;
    outParams->scale = 1;
    outParams->recordPath = NULL;
    outParams->replayPath = NULL;
    outParams->exitAfterReplay = false;
    outParams->replayBoundlessFramerate = false;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--help") == 0) {
            printHelp();
            exit(0);
        }
        if (strcmp(argv[i], "--disk") == 0 && i + 1 < argc) {
            outParams->diskPath = argv[++i];
        } else if (strcmp(argv[i], "--stage") == 0 && i + 1 < argc) {
            outParams->stage = PARSE_PARAM(argv[++i], allowed_stages);
            if (outParams->stage < 0) {
                printf("stage '%s' is invalid or not recognized\n", argv[i]);
                printAllowedParams(allowed_stages, LEN(allowed_stages));
                return false;
            }
        } else if (strcmp(argv[i], "--player") == 0 && i + 1 < argc) {
            outParams->player = PARSE_PARAM(argv[++i], allowed_players);
            if (outParams->player < 0) {
                printf("player '%s' is invalid or not recognized\n", argv[i]);
                printAllowedParams(allowed_players, LEN(allowed_players));
                return false;
            }
        } else if (strcmp(argv[i], "--scale") == 0 && i + 1 < argc) {
            outParams->scale = parseIntParam(argv[++i]);
            if (outParams->scale < 1 || outParams->scale > 8) {
                printf("invalid resolution scale %s\n", argv[i]);
                return false;
            }
        } else if (strcmp(argv[i], "--test") == 0 && i + 1 < argc) {
            outParams->testMode = PARSE_PARAM(argv[++i], allowed_tests) + 1;
            if (outParams->testMode < 0) {
                printf("test '%s' is invalid or not recognized\n", argv[i]);
                printAllowedParams(allowed_tests, LEN(allowed_tests));
                return false;
            }
        } else if (strcmp(argv[i], "--record") == 0 && i + 1 < argc) {
            outParams->recordPath = argv[++i];
        } else if (strcmp(argv[i], "--replay") == 0 && i + 1 < argc) {
            outParams->replayPath = argv[++i];
        } else if (strcmp(argv[i], "--replay-and-exit") == 0) {
            outParams->exitAfterReplay = true;
        } else if (strcmp(argv[i], "--replay-fast") == 0) {
            outParams->replayBoundlessFramerate = true;
        } else {
            printf("argument %s not recognized", argv[i]);
            return false;
        }
    }
    return true;
}

int Main(int argc, char* argv[]) {
    struct InitGameParams params;
    if (!parseArgs(&params, argc, argv)) {
        printHelp();
        return -1;
    }
    Psyz_VideoSetInternalResolution(params.scale);
    if (!InitGame(&params)) {
        return -1;
    }
    MainGame();
    ResetGame();
    if (params.replayPath && Replay_DidDrift()) {
        return -1;
    }
    return 0;
}

int main(int argc, char* argv[]) { return Main(argc, argv); }
