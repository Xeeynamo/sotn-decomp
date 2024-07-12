#ifndef GSTATE_H
#define GSTATE_H

typedef enum {
    Game_Init,
    Game_Title,
    Game_Play,
    Game_GameOver,
    Game_NowLoading,
    Game_VideoPlayback,
    Game_Unk6,
    Game_PrologueEnd,
    Game_MainMenu,
    Game_Ending,
    Game_Boot,
    Game_99 = 99,
} GameState;

extern GameState g_GameState;

typedef enum {
    // Clean-up and reset all the gameplay related memory
    Play_Reset = 0,
    // Re-initialize stage-specific resources
    Play_Init,
    // Set random seed if playing a demo
    Play_PrepareDemo,
    // Normal gameplay
    Play_Default,
    // Releases all the resources from the unloading stage
    Play_PrepareNextStage,
    // Load graphics for those stages without a CD room transition
    Play_LoadStageChr,
    // Wait until the previous operation is complete
    Play_WaitStageChr,
    // Load the sound effects specific for the selected stage
    Play_LoadStageSfx,
    // Wait until the previous operation is complete
    Play_WaitStageSfx,
    // Load the overlay program from the disk
    Play_LoadStagePrg,
    // Wait until the previous operation is complete
    Play_WaitStagePrg,
    // Used by the ST0 prologue scroll and now loading screen
    Play_16 = 16,

    // Deallocate stage resources
    Gameover_Init = 0,
    // Make screenshot and allocate 3D model for the melting foreground
    Gameover_AllocResources,
    // Wait for something...?
    Gameover_2,
    // Start loading game over graphics from the disk
    Gameover_3,
    // When the file is loaded, move it into the VRAM
    Gameover_4,
    // foreground melting
    Gameover_5,
    // Game over text starts brightening
    Gameover_6,
    // Start using Game Over textures that looks brighter
    Gameover_7,
    // Revert back to the slightly less bright Game Over text
    Gameover_8,
    // Game over screen fade out
    Gameover_9,
    // unknown
    Gameover_10,
    // Return to the title screen (if you are not in ST0)
    Gameover_11,

    Gameover_Alt = 99,
    Gameover_Init_Alt,
    Gameover_AllocResources_Alt,
    Gameover_2_Alt,
    Gameover_3_Alt,
    Gameover_11_Alt = 111,

    NowLoading_2 = 2,
} GameSteps;

extern u32 g_GameStep;

#endif // GSTATE_H
