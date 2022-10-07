#pragma once
#include <windows.h>

class PipeHost
{
public:
    HANDLE createNewPipe(LPCWSTR PipeName);
    std::string readDataFromPipe(HANDLE& pipeHandle);
    bool writeToPipe(const std::string& message, HANDLE& pipeHandle);
    const DWORD BufferSize = 4096;
    const DWORD TimeOut = 0;
};
