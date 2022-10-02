#include "pch.h"

static HFILE (WINAPI * TrueOpenFile)(LPCSTR lpFileName, LPOFSTRUCT lpReOpenBuff, UINT uStyle) = OpenFile;

HFILE WINAPI HookedOpenFile(LPCSTR lpFileName, LPOFSTRUCT lpReOpenBuff, UINT uStyle)
{
    MessageBox(0, L"Hello from HookedOpenFile!", L"Hello", MB_ICONINFORMATION);

    HFILE ret = TrueOpenFile(lpFileName, lpReOpenBuff, uStyle);

    return ret;
}

BOOL APIENTRY DllMain(HINSTANCE hinst, DWORD dwReason, LPVOID reserved)
{
    LONG error;
    (void)hinst;
    (void)reserved;

    if (DetourIsHelperProcess())
    {
        return TRUE;
    }


    if (dwReason == DLL_PROCESS_ATTACH)
    {
        MessageBox(0, L"Hello from Hook!", L"Hello", MB_ICONINFORMATION);

        DetourRestoreAfterWith();
        DetourTransactionBegin();
        DetourUpdateThread(GetCurrentThread());

        DetourAttach(&(PVOID&)TrueOpenFile, (PVOID&)HookedOpenFile);
        error = DetourTransactionCommit();

        if (error == NO_ERROR) {
            MessageBox(0, L"Detoured OpenFile()!", L"Success", MB_ICONINFORMATION);
        }
        else {
            MessageBox(0, L"Error detouring OpenFile()!", L"Error", MB_ICONINFORMATION);
        }
    }

    return TRUE;
}
