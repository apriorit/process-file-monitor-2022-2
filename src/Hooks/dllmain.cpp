#include "pch.h"
#include <iostream>
#include <thread>
#include <string.h>

static HANDLE (WINAPI * TrueCreateFileW)(LPCWSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes,
                                         DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile) = CreateFileW;

static BOOL (WINAPI * TrueReadFile)(HANDLE hFile, LPVOID lpBuffer, DWORD nNumberOfBytesToRead, LPDWORD lpNumberOfBytesRead,LPOVERLAPPED lpOverlapped) = ReadFile;

// https://stackoverflow.com/questions/4339960/how-do-i-convert-wchar-t-to-stdstring
std::string ConvertToString(const std::wstring& wstr)
{
    const int BUFF_SIZE = 7;

    if (MB_CUR_MAX >= BUFF_SIZE) throw std::invalid_argument("BUFF_SIZE too small");

    std::string result;
    bool shifts = std::wctomb(nullptr, 0);  // reset the conversion state

    for (const wchar_t wc : wstr)
    {
        std::array<char, BUFF_SIZE> buffer;
        const int ret = std::wctomb(buffer.data(), wc);
        if (ret < 0) throw std::invalid_argument("inconvertible wide characters in the current locale");
        buffer[ret] = '\0';  // make 'buffer' contain a C-style string
        result = result + std::string(buffer.data());
    }
    return result;
}

VOID displayDialog(std::string msg)
{    
    std::cout << msg << std::endl;
}

HANDLE WINAPI HookedCreateFileW(LPCWSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes,
                                DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile)
{
    HANDLE ret = TrueCreateFileW(lpFileName, dwDesiredAccess, dwShareMode, lpSecurityAttributes,
                                 dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);


    std::wstring ws(lpFileName);
    std::string fileName = ConvertToString(ws);

    auto access = GENERIC_READ | GENERIC_WRITE;

    if(fileName[1] == ':' && dwDesiredAccess & access)
    //if(dwDesiredAccess & 0x00000001)
    //if(dwDesiredAccess == FILE_READ_DATA || dwDesiredAccess == FILE_WRITE_DATA || dwDesiredAccess == DELETE)
    {
        std::thread t(&displayDialog, "[HookedCreateFileW] " + fileName + " " + std::to_string(dwDesiredAccess));
        t.detach();
    }


    return ret;
}

BOOL WINAPI HookedReadFile(HANDLE hFile, LPVOID lpBuffer, DWORD nNumberOfBytesToRead, LPDWORD lpNumberOfBytesRead,LPOVERLAPPED lpOverlapped)
{
    BOOL ret = TrueReadFile(hFile, lpBuffer, nNumberOfBytesToRead, lpNumberOfBytesRead,lpOverlapped);

    std::thread t(&displayDialog, "[HookedReadFile]");
    t.detach();

    return ret;
}

BOOL APIENTRY DllMain(HINSTANCE hinst, DWORD dwReason, LPVOID reserved)
{    
    AllocConsole();
    freopen("CONOUT$", "w", stdout);

    BOOL isHookSet;

    isHookSet = Mhook_SetHook((PVOID*)&TrueCreateFileW, (PVOID)HookedCreateFileW);
    //isHookSet = Mhook_SetHook((PVOID*)&TrueReadFile, (PVOID)HookedReadFile);
    return TRUE;
}
