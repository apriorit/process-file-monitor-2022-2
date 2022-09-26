#include "pch.h"

int inject(DWORD PID, LPCSTR DllPath)
{
    DWORD err;
    int ret;

    // Open a handle to target process
    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, PID);
    if (hProcess == NULL)
    {
        err =  GetLastError();
        throw std::runtime_error("Couldn't open target process. Error code:" + std::to_string(err) + "\n");
    }

    // Allocate memory for the dllpath in the target process
    // length of the path string + null terminator
    LPVOID pDllPath = VirtualAllocEx(hProcess, 0, strlen(DllPath) + 1, MEM_COMMIT, PAGE_READWRITE);
    if (pDllPath  == NULL)
    {
        err =  GetLastError();
        throw std::runtime_error("Couldn't allocate memory in target process. Error code:" + std::to_string(err) + "\n");
    }

    // Write the path to the address of the memory just allocated
    // in the target process
    ret = WriteProcessMemory(hProcess, pDllPath, (LPVOID)DllPath, strlen(DllPath) + 1, 0);
    if (ret == 0)
    {
        err =  GetLastError();
        throw std::runtime_error("Couldn't write to memory in target process. Error code:" + std::to_string(err) + "\n");
    }

    // Create a remote thread in the target process which calls LoadLibraryA with
    // DllPath as argument -> program loads the dll
    HMODULE hKernel32 = GetModuleHandleA("Kernel32.dll");
    if (hKernel32 == NULL)
    {
        err =  GetLastError();
        throw std::runtime_error("Couldn't get Kernel32.dll module handle. Error code:" + std::to_string(err) + "\n");
    }

    FARPROC kernel32Address = GetProcAddress(hKernel32, "LoadLibraryA");
    if (kernel32Address == NULL)
    {
        err =  GetLastError();
        throw std::runtime_error("Couldn't get Kernel32.dll address. Error code:" + std::to_string(err) + "\n");
    }

    HANDLE hLoadThread = CreateRemoteThread(hProcess, 0, 0, (LPTHREAD_START_ROUTINE)kernel32Address, pDllPath, 0, 0);

    // Wait for the execution of the loader thread to complete
    WaitForSingleObject(hLoadThread, INFINITE);

    if (hLoadThread == NULL)
    {
        err =  GetLastError();
        throw std::runtime_error("Couldn't create remote thread. Error code:" + std::to_string(err) + "\n");
    }

    std::cout << "Dll path allocated at: " << pDllPath << std::endl;
    std::cin.get();

    // Free the memory allocated for the dll path
    ret = VirtualFreeEx(hProcess, pDllPath, strlen(DllPath) + 1, MEM_RELEASE);
    if (ret == 0)
    {
        err =  GetLastError();
        throw std::runtime_error("Couldn't free allocated memory in target process. Error code:" + std::to_string(err) + "\n");
    }

    return 0;
}
