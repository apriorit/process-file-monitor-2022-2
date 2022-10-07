#pragma once
#include "pipehost.h"

class LogInfo;

class PipeClient : private PipeHost
{
public:
    static bool ReceivePermission(const DWORD Pid, HANDLE& pipeHandle, char& permission);
    static bool SendLog(const LogInfo& logInfo, HANDLE& pipeHandle);
    static std::string parseLogInfoIntoRequest(const LogInfo& logInfo);
};
