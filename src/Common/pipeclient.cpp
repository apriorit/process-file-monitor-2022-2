#include "pipeclient.h"
#include "loginfo.h"

bool PipeClient::receivePermission(const DWORD pid, char& permission){
    HANDLE pipeHandle = openPipe(PipeName);
    if(pipeHandle == INVALID_HANDLE_VALUE) return false;
    HandleGuard pipeGuard(pipeHandle);
    if(writeToPipe(std::to_string(pid), pipeHandle)){
        std::string response = readDataFromPipe(pipeHandle);
        if(response.size() == 0) return false;
        permission = response[0];
        return true;
    }
    return false;
}

bool PipeClient::sendLog(const LogInfo& logInfo){
    HANDLE pipeHandle = openPipe(PipeName);
    if(pipeHandle == INVALID_HANDLE_VALUE) return false;
    HandleGuard pipeGuard(pipeHandle);
    std::string request = parseLogInfoIntoRequest(logInfo);
    return writeToPipe(request, pipeHandle);
}

std::string PipeClient::parseLogInfoIntoRequest(const LogInfo& logInfo){
    std::string request = "";
    request += std::to_string(logInfo.pid) + "?";
    request += std::to_string(logInfo.offset) + "?";
    request += std::to_string(logInfo.numberOfBytes) + "?";
    request += std::to_string(logInfo.operationTime) + "?";
    request += logInfo.filePath.toStdString() + "?";
    request += logInfo.operationType.toStdString() + "?";
    request += logInfo.preview.toStdString() + "?";
    request += logInfo.fileHandle.toStdString() + "?";
    request += logInfo.resultOfTheOperation.toStdString();
    return request;
}

HANDLE PipeClient::openPipe(const LPCWSTR pipeName){
    return CreateFile(pipeName,
                      GENERIC_READ | GENERIC_WRITE,
                      0,
                      NULL,
                      OPEN_EXISTING,
                      0,
                      NULL);
}
