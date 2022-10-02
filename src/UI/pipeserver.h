#pragma once

#include <windows.h>
#include <QDebug>

class ProcessMonitor;
class LogModel;

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

class PipeServer
{
public:
    PipeServer(){
        pipeHandle = createNewPipe(TEXT("\\\\.\\pipe\\ProcessMonitorApp"));
        serverLoop();
    }
    static std::pair<DWORD, Commands> getCommandAndPidFromRequest(const std::string& Request);
private:
    HANDLE createNewPipe(LPCWSTR PipeName);
    void serverLoop();
    std::string readDataFromPipe();
    bool writeToPipe(const std::string& message);
    const DWORD BufferSize = 4096;
    const DWORD TimeOut = 0;
    HANDLE pipeHandle;

    ProcessMonitor* processMonitor;
    LogModel* logModel;
};
