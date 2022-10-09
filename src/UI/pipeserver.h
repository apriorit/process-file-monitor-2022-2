#pragma once

#include "../Common/pipehost.h"
#include <windows.h>
#include <QDebug>
#include <thread>

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
    PipeServer(ProcessMonitor* processMonitor, LogBuffer* logBuffer);
    ~PipeServer();
    static LogInfo parseRequest(const std::string& request);
    void startServerLoop();

private:
    HANDLE createNewPipe(LPCWSTR PipeName);
    bool sendPermission(const std::string& request);
    bool receiveLog(const std::string& request);
    bool isStringANumber(const std::string& s);
    HANDLE pipeHandle;
    HANDLE closeLoopEvent;
    std::thread serverThread;
    ProcessMonitor* processMonitor;
    LogBuffer* logBuffer;

};
