#include "pch.h"

BOOL APIENTRY DllMain( HMODULE hModule, DWORD ul_reason_for_call, LPVOID lprReserved)
{
    if (ul_reason_for_call == DLL_PROCESS_ATTACH)
    {
        MessageBox(0, L"Hello from Hook!", L"Hello", MB_ICONINFORMATION);
    }

    return TRUE;
}
