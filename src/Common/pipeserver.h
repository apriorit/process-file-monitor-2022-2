#pragma once

#include <windows.h>
#include <QDebug>
#include "pipehost.h"

class ProcessMonitor;
class LogBuffer;
struct LogInfo;
enum class Commands{
    Unknown,
    SendPermission,
    ReceiveLog
};

class ConnectionGuard{
public:
    ConnectionGuard(HANDLE& pipeHandle):pipeHandle{pipeHandle}{}
    ~ConnectionGuard();

private:
    HANDLE pipeHandle;
};

class PipeServer  : private PipeHost
{
public:
    PipeServer(ProcessMonitor* processMonitor, LogBuffer* logBuffer)
        :processMonitor{processMonitor},
        logBuffer{logBuffer}{
        pipeHandle = createNewPipe(TEXT("\\\\.\\pipe\\ProcessMonitorApp"));
    }

    static std::pair<DWORD, Commands> getCommandAndPidFromRequest(const std::string& Request);
    static LogInfo parseRequest(std::string request);
    void startServerLoop();
private:
    bool SendPermission(const std::string& request);
    bool ReceiveLog(const std::string& request);
    HANDLE pipeHandle;

    ProcessMonitor* processMonitor;
    LogBuffer* logBuffer;
};
