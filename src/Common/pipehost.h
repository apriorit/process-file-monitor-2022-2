#pragma once
#include <windows.h>

class PipeHost
{
public:
    static HANDLE createNewPipe(LPCWSTR PipeName);
    static std::string readDataFromPipe(HANDLE& pipeHandle);
    static bool writeToPipe(const std::string& message, HANDLE& pipeHandle);
    static const DWORD BufferSize = 4096;
    static const DWORD TimeOut = 0;
};
