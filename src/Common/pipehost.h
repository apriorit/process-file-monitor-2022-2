#pragma once
#include <windows.h>
#include <string>

class PipeHost
{
protected:
    static std::string readDataFromPipe(HANDLE& pipeHandle);
    static bool writeToPipe(const std::string& message, HANDLE& pipeHandle);
    static const DWORD BufferSize = 4096;
    static const DWORD TimeOut = 0;
    static const LPCWSTR PipeName;

    enum RequestProperty{
        Pid,
        Offset,
        NumberOfBytes,
        OperationTime,
        FilePath,
        OperationType,
        Preview,
        FileHande,
        ResultOfTheOperation,
        PropertiesCount
    };
};
