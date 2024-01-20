#include <stdio.h>

__declspec(dllexport) int dllvar = 1111;

__declspec(dllimport) int mainvar;


 __declspec(dllexport) void dllfunc()
{
    printf("hello from dll\n");

    // doesn't work
    // mainvar = 1;
}