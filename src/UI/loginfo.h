#pragma once
#include <windows.h>
#include <QString>

struct LogInfo{
    LogInfo(const DWORD pid);
    LogInfo() = default;
    QString filePath = "";
    QString operationType = "";
    QString preview = "";
    QString fileHandle = "";
    QString resultOfTheOperation = "";
    DWORD pid;
    DWORD numberOfBytes = 0;
    DWORD offset = 0;
    DWORD operationTime = 0;

    friend bool operator==(const LogInfo& first, const LogInfo& second);
};
