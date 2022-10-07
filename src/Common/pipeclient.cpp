#include "../UI/pch.h"
#include "pipeclient.h"
#include "loginfo.h"

bool PipeClient::ReceivePermission(const DWORD pid, HANDLE& pipeHandle, char& permission){
    if(writeToPipe(std::to_string(pid), pipeHandle)){
        std::string response = readDataFromPipe(pipeHandle);
        if(response.size() == 0) return false;
        permission = response[0];
        return true;
    }
    return false;
}

bool PipeClient::SendLog(const LogInfo& logInfo, HANDLE& pipeHandle){
    std::string request = parseLogInfoIntoRequest(logInfo);
    return writeToPipe(request, pipeHandle);
}

std::string PipeClient::parseLogInfoIntoRequest(const LogInfo& logInfo){
    std::string request = "";
    request += "<PID>" + std::to_string(logInfo.pid) + "</PID>";
    request += "<OFFSET>" + std::to_string(logInfo.offset) + "</OFFSET>";
    request += "<NOB>" + std::to_string(logInfo.numberOfBytes) + "</NOB>";
    request += "<OTIME>" + std::to_string(logInfo.operationTime) + "</OTIME>";
    request += "<FPATH>" + logInfo.filePath.toStdString() + "</FPATH>";
    request += "<OTYPE>" + logInfo.operationType.toStdString() + "</OTYPE>";
    request += "<PREVIEW>" + logInfo.preview.toStdString() + "</PREVIEW>";
    request += "<FHANDLE>" + logInfo.fileHandle.toStdString() + "</FHANDLE>";
    request += "<RESULT>" + logInfo.resultOfTheOperation.toStdString() + "</RESULT>";
    return request;
}
