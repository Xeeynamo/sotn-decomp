// SPDX-License-Identifier: AGPL-3.0-or-later
#include <game.h>
#include <psyz/log.h>
#include <psyz/video.h>
#include <stdio.h>
#include <stdlib.h>
#include "pc.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../../tools/psyz/psyz/tests/stb_image_write.h"

extern bool g_IsQuitRequested;

typedef enum {
    Transition_WaitForPlay,
    Transition_BeginTrip,
    Transition_WaitForDoorReady,
    Transition_WalkOut,
    Transition_WaitForDestination,
    Transition_WalkSaveCenter,
    Transition_WaitForSaveDrop,
    Transition_WalkSaveRight,
    Transition_JumpToSaveRightLedge,
    Transition_WalkSaveLeft,
    Transition_JumpToSaveLedge,
    Transition_WalkBack,
    Transition_WaitForReturn,
    Transition_Done,
} TransitionTestStep;

static bool s_CaptureFailed;

static int CountSaveBackdropPrimitives(void) {
    int count = 0;

    for (int i = 0; i < MAX_PRIM_COUNT; i++) {
        Primitive* prim = &g_PrimBuf[i];
        if (prim->type == PRIM_TILE && prim->priority == 0x1EB &&
            prim->u0 == 0x80 && prim->v0 == 0x20) {
            count++;
        }
    }
    return count;
}

static bool CaptureFrame(const char* path) {
    unsigned char* pixels;
    int width;
    int height;
    bool written;

    pixels = Psyz_VideoAllocCapturedFrame(&width, &height);
    if (!pixels) {
        ERRORF("failed to capture the rendered frame");
        return false;
    }
    written = stbi_write_png(path, width, height, 3, pixels, width * 3) != 0;
    free(pixels);
    if (!written) {
        ERRORF("failed to write capture '%s'", path);
        return false;
    }
    INFOF("captured rendered frame to '%s'", path);
    return true;
}

static RoomHeader* FindCurrentRoom(void) {
    RoomHeader* room = g_api.o.rooms;

    while (room->left != 0x40) {
        if (room->left == g_Tilemap.left && room->top == g_Tilemap.top &&
            room->right == g_Tilemap.right &&
            room->bottom == g_Tilemap.bottom) {
            return room;
        }
        room++;
    }
    return NULL;
}

static void FailTransitionTest(const char* reason) {
    ERRORF("Stage 15 transition test failed: %s", reason);
    s_CaptureFailed = true;
    g_IsQuitRequested = true;
}

static void TransitionTest_OnFrame(void) {
    typedef struct {
        u8 destinationX;
        u8 destinationY;
        u8 row;
        s16 startX;
        s16 startY;
        bool leaveRight;
        bool useStockDoor;
        bool isSaveRoom;
        const char* label;
        const char* captureSuffix;
    } RoundTrip;
    static const RoundTrip trips[] = {
        {13, 44, 44, 232, 128, true, false, false, "room 0/1 boundary",
         "room1"},
        {21, 44, 44, 232, 128, true, false, false, "ordinary-room chain",
         "room3"},
        {3, 45, 45, 24, 128, false, true, false, "bottom-left door",
         "bottom-left"},
        {3, 44, 44, 24, 128, false, true, false, "top-left door", "top-left"},
        {13, 45, 45, 232, 128, true, false, true, "save-room door",
         "save-room"},
    };
    static TransitionTestStep step;
    static unsigned readyFrames;
    static unsigned waitFrames;
    static unsigned tripIndex;
    static RoomHeader homeRoom;
    static RoomHeader destinationRoom;
    static u8 stageId;
    static s32 startCastleX;
    static s32 startCastleY;
    static s32 landingStartY;
    static s32 saveLedgeY;
    static bool saveHasRightLedge;
    static u8 boostedRoomLeft;
    RoomHeader* current;
    RoomHeader* target;
    const RoundTrip* trip = &trips[tripIndex];
    s32 castleX;
    s32 castleY;

    if (g_GameState != Game_Play || g_GameStep != Play_Default ||
        g_GameEngineStep != Engine_Normal) {
        readyFrames = 0;
        return;
    }

    switch (step) {
    case Transition_WaitForPlay:
        if (++readyFrames < 120) {
            return;
        }
        current = FindCurrentRoom();
        if (!current) {
            FailTransitionTest("current room header was not found");
            return;
        }
        stageId = g_StageId;
        homeRoom = *current;
        tripIndex = 0;
        boostedRoomLeft = 0xFF;
        readyFrames = 0;
        step = Transition_BeginTrip;
        return;

    case Transition_BeginTrip:
        if (++readyFrames < 20) {
            return;
        }
        current = FindCurrentRoom();
        target = NULL;
        {
            RoomHeader* room = g_api.o.rooms;
            while (room->left != 0x40) {
                if (trip->destinationX >= room->left &&
                    trip->destinationX <= room->right &&
                    trip->destinationY >= room->top &&
                    trip->destinationY <= room->bottom) {
                    target = room;
                    break;
                }
                room++;
            }
        }
        if (!current || !target || current->left != homeRoom.left ||
            current->top != homeRoom.top || current->right != homeRoom.right ||
            current->bottom != homeRoom.bottom) {
            FailTransitionTest("round trip did not begin in room 0");
            return;
        }
        destinationRoom = *target;
        boostedRoomLeft = 0xFF;
        g_Tilemap.scrollX.i.hi =
            trip->leaveRight ? g_Tilemap.width - 256 : g_Tilemap.x;
        g_Tilemap.scrollY.i.hi = (trip->row - current->top) << 8;
        PLAYER.posX.i.hi = trip->startX;
        g_PlayerX = g_Tilemap.scrollX.i.hi + trip->startX;
        g_PlayerY = g_Tilemap.scrollY.i.hi + trip->startY;
        PLAYER.posY.i.hi = trip->startY;
        PLAYER.velocityX = 0;
        PLAYER.velocityY = 0;
        PLAYER.step = Player_Stand;
        PLAYER.step_s = 0;
        g_Player.padSim = 0;
        g_Player.demo_timer = 1;
        startCastleX = (current->left << 8) + g_PlayerX;
        startCastleY = (current->top << 8) + g_PlayerY;
        INFOF("testing Stage 15 %s round trip from castle=(%d,%d) "
              "to (%u,%u)-(%u,%u)",
              trip->label, startCastleX, startCastleY, target->left,
              target->top, target->right, target->bottom);
        if (trip->useStockDoor) {
            waitFrames = 0;
            step = Transition_WaitForDoorReady;
            return;
        }
        waitFrames = 0;
        step = Transition_WalkOut;
        return;

    case Transition_WaitForDoorReady: {
        Entity* door = NULL;
        for (Entity* entity = &g_Entities[STAGE_ENTITY_START];
             entity < &g_Entities[TOTAL_ENTITY_COUNT]; entity++) {
            if (entity->entityId == 5 && entity->step == 1 &&
                entity->primIndex >= 0 && (entity->flags & FLAG_HAS_PRIMS)) {
                door = entity;
                break;
            }
        }
        if (door != NULL) {
            PLAYER.facingLeft = 1;
            g_Player.padSim = 0;
            g_Player.demo_timer = 1;
            waitFrames = 0;
            INFOF("Stage 15 %s stock EntityRedDoor ready", trip->label);
            step = Transition_WalkOut;
            return;
        }
        if (++waitFrames > 120) {
            FailTransitionTest("stock EntityRedDoor did not initialize");
        }
        return;
    }

    case Transition_WalkOut:
        if (g_StageId != stageId) {
            FailTransitionTest("door changed stages");
            return;
        }
        if (g_Tilemap.left == destinationRoom.left &&
            g_Tilemap.top == destinationRoom.top &&
            g_Tilemap.right == destinationRoom.right &&
            g_Tilemap.bottom == destinationRoom.bottom) {
            castleX = (g_Tilemap.left << 8) + g_PlayerX;
            castleY = (g_Tilemap.top << 8) + g_PlayerY;
            INFOF("Stage 15 %s entered naturally at screen=(%d,%d), "
                  "room-local=(%d,%d), castle=(%d,%d), scroll=(%d,%d)",
                  trip->label, PLAYER.posX.i.hi, PLAYER.posY.i.hi, g_PlayerX,
                  g_PlayerY, castleX, castleY, g_Tilemap.scrollX.i.hi,
                  g_Tilemap.scrollY.i.hi);
            if ((trip->leaveRight && PLAYER.posX.i.hi >= 64) ||
                (!trip->leaveRight && PLAYER.posX.i.hi <= 192)) {
                FailTransitionTest("Alucard entered on the wrong side");
                return;
            }
            PLAYER.velocityX = 0;
            g_Player.padSim = 0;
            g_Player.demo_timer = 1;
            landingStartY = g_PlayerY;
            readyFrames = 0;
            step = Transition_WaitForDestination;
            return;
        }
        current = FindCurrentRoom();
        if (trip->destinationX == 21 && current != NULL &&
            current->left != homeRoom.left &&
            current->left != destinationRoom.left &&
            boostedRoomLeft != current->left) {
            boostedRoomLeft = current->left;
            g_Tilemap.scrollX.i.hi = g_Tilemap.width - 256;
            PLAYER.posX.i.hi = 232;
            g_PlayerX = g_Tilemap.scrollX.i.hi + PLAYER.posX.i.hi;
        }
        g_Player.padSim = trip->leaveRight ? PAD_RIGHT : PAD_LEFT;
        g_Player.demo_timer = 1;
        if (++waitFrames % 60 == 0) {
            INFOF("Stage 15 %s walking out: room=(%u,%u)-(%u,%u), "
                  "engine=%d player=(%d,%d) world=(%d,%d)",
                  trip->label, g_Tilemap.left, g_Tilemap.top, g_Tilemap.right,
                  g_Tilemap.bottom, g_GameEngineStep, PLAYER.posX.i.hi,
                  PLAYER.posY.i.hi, g_PlayerX, g_PlayerY);
        }
        if (waitFrames > 600) {
            FailTransitionTest("Alucard did not walk through the door");
        }
        return;

    case Transition_WaitForDestination:
        if (g_StageId != stageId || g_Tilemap.left != destinationRoom.left ||
            g_Tilemap.top != destinationRoom.top ||
            g_Tilemap.right != destinationRoom.right ||
            g_Tilemap.bottom != destinationRoom.bottom) {
            FailTransitionTest("Alucard left the destination before returning");
            return;
        }
        g_Player.padSim = 0;
        if (PLAYER.posY.i.hi > DISP_STAGE_H + 32 ||
            g_PlayerY > landingStartY + 64) {
            INFOF("Stage 15 fall: startY=%d playerY=%d worldY=%d",
                  landingStartY, PLAYER.posY.i.hi, g_PlayerY);
            FailTransitionTest("player fell after a door transition");
            return;
        }
        if (++readyFrames < 30) {
            return;
        }
        if (!((g_Player.colFloor[1].effects | g_Player.colFloor[2].effects |
               g_Player.colFloor[3].effects) &
              EFFECT_SOLID)) {
            FailTransitionTest(
                "player had no floor support 30 frames after a door");
            return;
        }
        if (g_GameParams.capturePath) {
            char path[512];
            snprintf(path, sizeof(path), "%s.%s.png", g_GameParams.capturePath,
                     trip->captureSuffix);
            if (!CaptureFrame(path)) {
                FailTransitionTest("could not capture special room");
                return;
            }
        }
        readyFrames = 0;
        if (trip->isSaveRoom && CountSaveBackdropPrimitives() != 4) {
            FailTransitionTest(
                "save room did not initialize exactly one controller");
            return;
        }
        waitFrames = 0;
        if (trip->isSaveRoom) {
            saveLedgeY = g_PlayerY;
            {
                u16 tile = g_Tilemap.fg[10 * 16 + 13];
                saveHasRightLedge =
                    (g_Tilemap.tileDef->collision[tile] & EFFECT_SOLID) != 0;
                INFOF("Stage 15 save right ledge: %s",
                      saveHasRightLedge ? "present" : "missing");
            }
            step = Transition_WalkSaveCenter;
        } else {
            boostedRoomLeft = 0xFF;
            step = Transition_WalkBack;
        }
        return;

    case Transition_WalkSaveCenter:
        g_Player.padSim = PAD_RIGHT;
        g_Player.demo_timer = 1;
        if (PLAYER.posX.i.hi >= 80) {
            g_Player.padSim = 0;
            g_Player.demo_timer = 1;
            waitFrames = 0;
            step = Transition_WaitForSaveDrop;
            return;
        }
        if (++waitFrames > 180) {
            FailTransitionTest("Alucard could not walk toward the save orb");
        }
        return;

    case Transition_WaitForSaveDrop:
        g_Player.padSim = 0;
        g_Player.demo_timer = 1;
        if (((g_Player.colFloor[1].effects | g_Player.colFloor[2].effects |
              g_Player.colFloor[3].effects) &
             EFFECT_SOLID) &&
            PLAYER.velocityY == 0) {
            INFOF("Stage 15 save-room center landed at worldY=%d "
                  "(ledge=%d, drop=%d)",
                  g_PlayerY, saveLedgeY, g_PlayerY - saveLedgeY);
            if (g_PlayerY - saveLedgeY < 24 || g_PlayerY - saveLedgeY > 40) {
                FailTransitionTest(
                    "save-room center did not have the expected lower floor");
                return;
            }
            if (g_GameParams.capturePath) {
                char path[512];
                snprintf(path, sizeof(path), "%s.save-room-lower.png",
                         g_GameParams.capturePath);
                if (!CaptureFrame(path)) {
                    FailTransitionTest(
                        "could not capture the lower save-room floor");
                    return;
                }
            }
            waitFrames = 0;
            step = Transition_WalkSaveRight;
            return;
        }
        if (++waitFrames > 120) {
            FailTransitionTest("Alucard did not land in the save-room center");
        }
        return;

    case Transition_WalkSaveRight:
        g_Player.padSim = PAD_RIGHT;
        g_Player.demo_timer = 1;
        if (saveHasRightLedge && PLAYER.posX.i.hi >= 184) {
            waitFrames = 0;
            step = Transition_JumpToSaveRightLedge;
            return;
        }
        if (PLAYER.posX.i.hi >= 224) {
            if (g_PlayerY < saveLedgeY + 24) {
                FailTransitionTest(
                    "save room had an unexpected raised right ledge");
                return;
            }
            INFOF("Stage 15 save-room right side reached on lower floor");
            if (g_GameParams.capturePath) {
                char path[512];
                snprintf(path, sizeof(path), "%s.save-room-right.png",
                         g_GameParams.capturePath);
                if (!CaptureFrame(path)) {
                    FailTransitionTest(
                        "could not capture the save room's right side");
                    return;
                }
            }
            waitFrames = 0;
            step = Transition_WalkSaveLeft;
            return;
        }
        if (++waitFrames > 240) {
            FailTransitionTest(
                "Alucard got stuck crossing the lower save-room floor");
        }
        return;

    case Transition_JumpToSaveRightLedge:
        g_Player.padSim = PAD_RIGHT | PAD_CROSS;
        g_Player.demo_timer = 1;
        if (PLAYER.posX.i.hi > 216 && g_PlayerY <= saveLedgeY + 8) {
            INFOF("Stage 15 Saturn save-room right ledge reached naturally");
            if (g_GameParams.capturePath) {
                char path[512];
                snprintf(path, sizeof(path), "%s.save-room-right.png",
                         g_GameParams.capturePath);
                if (!CaptureFrame(path)) {
                    FailTransitionTest(
                        "could not capture the Saturn save-room right ledge");
                    return;
                }
            }
            waitFrames = 0;
            step = Transition_WalkSaveLeft;
            return;
        }
        if (++waitFrames > 240) {
            FailTransitionTest(
                "Alucard could not reach the Saturn save-room right ledge");
        }
        return;

    case Transition_WalkSaveLeft:
        g_Player.padSim = PAD_LEFT;
        g_Player.demo_timer = 1;
        if (PLAYER.posX.i.hi < 72 && g_PlayerY >= saveLedgeY + 24) {
            INFOF("Stage 15 save-room lower floor crossed in both directions");
            waitFrames = 0;
            step = Transition_JumpToSaveLedge;
            return;
        }
        if (++waitFrames > 240) {
            FailTransitionTest(
                "Alucard could not leave the save room's right ledge");
        }
        return;

    case Transition_JumpToSaveLedge:
        g_Player.padSim = PAD_LEFT | PAD_CROSS;
        g_Player.demo_timer = 1;
        if (PLAYER.posX.i.hi < 40 && g_PlayerY <= saveLedgeY + 8) {
            INFOF("Stage 15 save-room left ledge regained naturally");
            g_Player.padSim = 0;
            g_Player.demo_timer = 1;
            waitFrames = 0;
            step = Transition_WalkBack;
            return;
        }
        if (++waitFrames > 240) {
            FailTransitionTest(
                "Alucard could not jump back onto the save-room ledge");
        }
        return;

    case Transition_WalkBack:
        if (g_StageId != stageId) {
            FailTransitionTest("return walk changed stages");
            return;
        }
        if (g_Tilemap.left == homeRoom.left && g_Tilemap.top == homeRoom.top &&
            g_Tilemap.right == homeRoom.right &&
            g_Tilemap.bottom == homeRoom.bottom) {
            castleX = (g_Tilemap.left << 8) + g_PlayerX;
            castleY = (g_Tilemap.top << 8) + g_PlayerY;
            INFOF("Stage 15 %s returned naturally at screen=(%d,%d), "
                  "room-local=(%d,%d), castle=(%d,%d), scroll=(%d,%d), "
                  "delta=(%d,%d)",
                  trip->label, PLAYER.posX.i.hi, PLAYER.posY.i.hi, g_PlayerX,
                  g_PlayerY, castleX, castleY, g_Tilemap.scrollX.i.hi,
                  g_Tilemap.scrollY.i.hi, castleX - startCastleX,
                  castleY - startCastleY);
            if (abs(castleX - startCastleX) > 64 ||
                abs(castleY - startCastleY) > 64) {
                FailTransitionTest(
                    "Alucard did not return near the same doorway position");
                return;
            }
            if ((!trip->leaveRight && g_PlayerX >= 64) ||
                (trip->leaveRight && g_PlayerX <= g_Tilemap.width - 64)) {
                FailTransitionTest(
                    "Alucard returned on the wrong side of room 0");
                return;
            }
            PLAYER.velocityX = 0;
            g_Player.padSim = 0;
            g_Player.demo_timer = 1;
            readyFrames = 0;
            step = Transition_WaitForReturn;
            return;
        }
        current = FindCurrentRoom();
        if (trip->destinationX == 21 && current != NULL &&
            current->left != homeRoom.left &&
            current->left != destinationRoom.left &&
            boostedRoomLeft != current->left) {
            boostedRoomLeft = current->left;
            g_Tilemap.scrollX.i.hi = g_Tilemap.x;
            PLAYER.posX.i.hi = 24;
            g_PlayerX = g_Tilemap.scrollX.i.hi + PLAYER.posX.i.hi;
        }
        g_Player.padSim = trip->leaveRight ? PAD_LEFT : PAD_RIGHT;
        g_Player.demo_timer = 1;
        if (++waitFrames > 600) {
            FailTransitionTest("Alucard did not walk back through the door");
        }
        return;

    case Transition_WaitForReturn:
        g_Player.padSim = 0;
        if (++readyFrames < 30) {
            return;
        }
        if ((!trip->leaveRight &&
             abs(g_Tilemap.scrollX.i.hi - g_Tilemap.x) > 4) ||
            (trip->leaveRight &&
             abs(g_Tilemap.scrollX.i.hi - (g_Tilemap.width - 256)) > 4) ||
            abs(g_Tilemap.scrollY.i.hi - (trip->row - homeRoom.top) * 256) >
                4) {
            FailTransitionTest("room 0 camera returned to the wrong doorway");
            return;
        }
        if (trip->isSaveRoom && g_GameParams.capturePath) {
            char path[512];
            snprintf(path, sizeof(path), "%s.save-room-return.png",
                     g_GameParams.capturePath);
            if (!CaptureFrame(path)) {
                FailTransitionTest("could not capture the post-save return");
                return;
            }
        }
        if (trip->isSaveRoom && CountSaveBackdropPrimitives() != 0) {
            FailTransitionTest(
                "save controller primitives survived the room transition");
            return;
        }
        INFOF("Stage 15 %s round trip passed", trip->label);
        tripIndex++;
        if (tripIndex == LEN(trips)) {
            step = Transition_Done;
            g_IsQuitRequested = true;
        } else {
            readyFrames = 0;
            step = Transition_BeginTrip;
        }
        return;

    case Transition_Done:
        return;
    }
}

void Capture_OnFrame(void) {
    static unsigned readyFrames;
    static bool captured;

    if (g_GameParams.transitionTest) {
        TransitionTest_OnFrame();
        return;
    }
    if (!g_GameParams.capturePath || captured) {
        return;
    }
    if (g_GameState != Game_Play || g_GameStep != Play_Default) {
        readyFrames = 0;
        return;
    }
    if (++readyFrames < 120) {
        return;
    }

    captured = true;
    if (!CaptureFrame(g_GameParams.capturePath)) {
        s_CaptureFailed = true;
    }
    g_IsQuitRequested = true;
}

bool Capture_DidFail(void) { return s_CaptureFailed; }
