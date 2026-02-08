#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <thread>
#include <cstdint>
#include <cstdio>

#include <iostream>
#include "hooks/hooks.h"

void hack_thread(HMODULE hModule)
{
    hooks::setup();

    while (!(GetAsyncKeyState(VK_DELETE) & 1)) {
        Sleep(10);
    }

    hooks::destroy();
    FreeLibraryAndExitThread(hModule, 0);
}





BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason, LPVOID)
{
    if (reason == DLL_PROCESS_ATTACH) {
        DisableThreadLibraryCalls(hModule);
        CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)hack_thread, hModule, 0, nullptr);
    }
    return TRUE;
}
