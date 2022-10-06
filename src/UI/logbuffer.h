#pragma once
#include "loginfo.h"
#include <mutex>

class LogBuffer
{
public:
    std::vector<LogInfo> getLogsFromTheBuffer();
    void addLogToTheBuffer(LogInfo&& logInfo);

private:
    std::vector<LogInfo> logs;
    std::mutex logMutex;
};
