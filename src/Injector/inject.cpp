#include "pch.h"

int inject(DWORD PID, LPCSTR DllPath)
{
    // Open a handle to target process
    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, PID);

    // Allocate memory for the dllpath in the target process
    // length of the path string + null terminator
    LPVOID pDllPath = VirtualAllocEx(hProcess, 0, strlen(DllPath) + 1, MEM_COMMIT, PAGE_READWRITE);

    // Write the path to the address of the memory just allocated
    // in the target process
    WriteProcessMemory(hProcess, pDllPath, (LPVOID)DllPath, strlen(DllPath) + 1, 0);

    // Create a remote thread in the target process which calls LoadLibraryA with
    // DllPath as argument -> program loads the dll
    HANDLE hLoadThread = CreateRemoteThread(hProcess, 0, 0,
            (LPTHREAD_START_ROUTINE)GetProcAddress(GetModuleHandleA("Kernel32.dll"), "LoadLibraryA"), pDllPath, 0 ,0);

    // Wait for the execution of the loader thread to complete
    WaitForSingleObject(hLoadThread, INFINITE);

    std::cout << "Dll path allocated at: " << pDllPath << std::endl;
    std::cin.get();

    // Free the memory allocated for the dll path
    VirtualFreeEx(hProcess, pDllPath, strlen(DllPath) + 1, MEM_RELEASE);

    return 0;
}
