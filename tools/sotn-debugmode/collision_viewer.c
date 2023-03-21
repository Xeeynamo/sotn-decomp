#include <game.h>

// borrowing first part of CheckCollision
u8 GetColType(s32 x, s32 y)
{
    s32 absX;
    s32 absY;
    u8 colType;
    int new_var;
    // g_Camera.posX.i.lo doesn't seem to work like I expect
    u16* cameraX = (u16*)0x80073074;
    u16* cameraY = (u16*)0x8007307C;
    absX = x + *cameraX;
    absY = y + *cameraY;
    new_var = 0x10;
    if ((((absX < 0) || (((u32)absX) >= (g_CurrentRoom.hSize << 8))) ||
         (absY < 0)) ||
        (((u32)absY) >= (g_CurrentRoomVSize << 8))) {
        colType = 0;
    } else {

        // 16x16 blocks
        u16 colTile = g_CurrentRoomTileLayout
                          .fg[(absX >> 4) +
                              (((absY >> 4) * g_CurrentRoom.hSize) * new_var)];
        colType = D_80073088->collision[colTile];
    }
    return colType;
}

void CollisionDebug(void)
{
    int x;
    int y;
    u8 colType;

    // skip first 4 rows since we are stuck with their FntOpen settings
    for(y = 16*4; y < 224; y+= 16)
    {
        // skip first column since we are stuck with their FntOpen settings
        FntPrint(" ", colType);
        for(x = 16; x < 256; x+=16)
        {
            colType = GetColType(x, y);

            // skip empty tiles
            if (colType == 0)
            {
                FntPrint("  ", colType);
            }
            else {
                FntPrint("%02x", colType);
            }
        }
        FntPrint("\n\n");
    }
    FntFlush(-1);
}
