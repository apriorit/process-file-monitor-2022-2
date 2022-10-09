#pragma once

#include "../Common/pipehost.h"
#include <windows.h>
#include <QDebug>

class ProcessMonitor;

class LogBuffer;

struct LogInfo;

enum class Commands{
    Unknown,
    sendPermission,
    receiveLog
};

class ConnectionGuard{
public:
    ConnectionGuard(HANDLE& pipeHandle):pipeHandle{pipeHandle}{}
    ~ConnectionGuard();

private:
    HANDLE pipeHandle;
};

class PipeServer  : public PipeHost
{
public:
    PipeServer(ProcessMonitor* processMonitor, LogBuffer* logBuffer)
        :processMonitor{processMonitor},
        logBuffer{logBuffer}{

        pipeHandle = createNewPipe(PipeName);
    }

    static std::pair<DWORD, Commands> getCommandAndPidFromRequest(const std::string& Request);
    static LogInfo parseRequest(const std::string& request);
    void startServerLoop();
private:
    HANDLE createNewPipe(LPCWSTR PipeName);
    bool sendPermission(const std::string& request);
    bool receiveLog(const std::string& request);
    bool isStringANumber(const std::string& s);
    HANDLE pipeHandle;

    ProcessMonitor* processMonitor;
    LogBuffer* logBuffer;
};
