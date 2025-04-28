SECTIONS
{
    __romPos = 0;
    _gp = 0x0;
    game_ROM_START = __romPos;
    game_VRAM = ADDR(.game);
    .game 0x06066000 : AT(game_ROM_START) SUBALIGN(2)
    {
        game_TEXT_START = .;
        build/saturn/game.o(.text);
        game_TEXT_END = .;
        game_TEXT_SIZE = ABSOLUTE(game_TEXT_END - game_TEXT_START);
    }
    __romPos += SIZEOF(.game);
    __romPos = ALIGN(__romPos, 16);
    game_ROM_END = __romPos;
    game_VRAM_END = .;

    /DISCARD/ :
    {
        *(*);
    }
}
