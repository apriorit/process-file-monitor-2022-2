#pragma once
#include "pipehost.h"

class LogInfo;

class HandleGuard{
public:
    HandleGuard(HANDLE& handleToGuard):handleToGuard{handleToGuard}{};
    ~HandleGuard(){CloseHandle(handleToGuard);}
private:
    HANDLE& handleToGuard;
};

class PipeClient : public PipeHost
{
public:
    static bool ReceivePermission(const DWORD Pid, char& permission);
    static bool SendLog(const LogInfo& logInfo);
    static std::string parseLogInfoIntoRequest(const LogInfo& logInfo);
private:
    static HANDLE OpenPipe(LPCWSTR pineName = PipeName);
};
