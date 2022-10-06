#include "pch.h"
#include "logbuffer.h"

std::vector<LogInfo> LogBuffer::getLogsFromTheBuffer(){
    std::lock_guard<std::mutex> guard(logMutex);
    return std::move(logs);
}
void LogBuffer::addLogToTheBuffer(LogInfo&& logInfo){
    std::lock_guard<std::mutex> guard(logMutex);
    logs.push_back(logInfo);
}
