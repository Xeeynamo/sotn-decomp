#include <Windows.h>
#include <stdio.h>

__declspec(dllexport) int mainvar;

int main()
{
    HMODULE hDll = LoadLibraryA("./build/Debug/MyDLL.dll");
    if (hDll == NULL)
    {
        printf("Couldn't load\n");
        return 1;
    }

    int *dllvar = GetProcAddress(hDll, "dllvar");

    printf("dllvar is %d\n", *dllvar);

    void (*dllfunc)(void) = GetProcAddress(hDll, "dllfunc");

    dllfunc();
}
