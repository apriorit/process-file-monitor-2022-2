#include "pch.h"
#include "logbuffer.h"
#include "pipeserver.h"
#include "processmonitor.h"

ConnectionGuard::~ConnectionGuard(){
    DisconnectNamedPipe(pipeHandle);
}

void PipeServer::startServerLoop(){
    int calls = 0;
    while(true){
        qDebug() << calls++;
        DWORD connectionStatus = 0;
        DWORD error = 0;
        connectionStatus = ConnectNamedPipe(pipeHandle,nullptr);
        error = GetLastError();
        ConnectionGuard connectionGuard(pipeHandle);
        if(connectionStatus == 0 && error != ERROR_PIPE_CONNECTED){
            continue;
        }
        const std::string request = readDataFromPipe(pipeHandle);
        qDebug() << QString::fromStdString("Received request <" + request+">");
        if(sendPermission(request)) continue;
        if(receiveLog(request)) continue;
    }
}

bool PipeServer::receiveLog(const std::string& request){
    int separatorsCount = std::count(request.begin(), request.end(), '?');
    if(PropertiesCount != separatorsCount + 1)
        return false;
    try{
        logBuffer->addLogToTheBuffer(PipeServer::parseRequest(request));
    }
    catch(const std::invalid_argument&){}
    return false;
}

bool PipeServer::sendPermission(const std::string& request){
    if(!isStringANumber(request)) return false;
    const DWORD pid = std::strtoul(request.c_str(), NULL , 10);
    if(pid == 0) return false;
    std::string permission;
    try{
        permission += processMonitor->getCopyOfProcessInfoByPid(pid).getPermissionsAsChar();
        return writeToPipe(permission, pipeHandle);
    }
    catch(const std::out_of_range&){
        return false;
    }
}

LogInfo PipeServer::parseRequest(std::string request){
    size_t begin = 0;
    size_t end = 0;
    LogInfo logInfo(0);
        for(int property = 0 ; property < PipeHost::PropertiesCount ; property++){
            end = request.find('?',begin);
            std::string propertyValue = request.substr(begin, end - begin);
            switch(property){
            case PipeHost::Pid:
                logInfo.pid = std::strtoul(propertyValue.c_str(), NULL, 10);
                break;
            case PipeHost::Offset:
                logInfo.offset = std::strtoul(propertyValue.c_str(), NULL, 10);
                break;
            case PipeHost::NumberOfBytes:
                logInfo.numberOfBytes = std::strtoul(propertyValue.c_str(), NULL, 10);
                break;
            case PipeHost::FilePath:
                logInfo.filePath = QString::fromStdString(propertyValue);
                break;
            case PipeHost::OperationType:
                logInfo.operationType = QString::fromStdString(propertyValue);
                break;
            case PipeHost::Preview:
                logInfo.preview = QString::fromStdString(propertyValue);
                break;
            case PipeHost::FileHande:
                logInfo.fileHandle = QString::fromStdString(propertyValue);
                break;
            case PipeHost::ResultOfTheOperation:
                logInfo.resultOfTheOperation = QString::fromStdString(propertyValue);
                break;
            case PipeHost::OperationTime:
                logInfo.operationTime = std::strtoul(propertyValue.c_str(), NULL, 10);
                break;
            }
            if(end == std::string::npos)break;
            begin = end + 1;

        }

    if(logInfo.pid == 0){
        throw std::invalid_argument("Pid is not correct !");
    }
    return logInfo;
}

bool PipeServer::isStringANumber(const std::string& s)
{
    return !s.empty() && s.find_first_not_of("0123456789") == std::string::npos;
}
