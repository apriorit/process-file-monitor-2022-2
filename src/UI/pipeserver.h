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
        :pipeHandle{createNewPipe(PipeName)},
          closeLoopEvent{CreateEvent(NULL, FALSE , FALSE , NULL)},
          processMonitor{processMonitor},
          logBuffer{logBuffer}{}
    static std::pair<DWORD, Commands> getCommandAndPidFromRequest(const std::string& Request);
    static LogInfo parseRequest(const std::string& request);
    void startServerLoop();
    void stopServerLoop();
private:
    HANDLE createNewPipe(LPCWSTR PipeName);
    bool sendPermission(const std::string& request);
    bool receiveLog(const std::string& request);
    bool isStringANumber(const std::string& s);
    HANDLE pipeHandle;
    HANDLE closeLoopEvent;

    ProcessMonitor* processMonitor;
    LogBuffer* logBuffer;
};
