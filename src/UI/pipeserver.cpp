#include "pch.h"
#include "logbuffer.h"
#include "pipeserver.h"
#include "processmonitor.h"

ConnectionGuard::~ConnectionGuard(){
    DisconnectNamedPipe(pipeHandle);
}

void PipeServer::startServerLoop(){
    OVERLAPPED overlappedStructure;
    HANDLE hEvents[2];
    overlappedStructure.hEvent = CreateEvent(NULL, FALSE , FALSE , NULL);
    hEvents[0] = overlappedStructure.hEvent;
    hEvents[1] = closeLoopEvent;
    while(true){
        ConnectNamedPipe(pipeHandle, &overlappedStructure);
        switch(WaitForMultipleObjects(2, hEvents, FALSE , INFINITE)){
        case WAIT_OBJECT_0:
        {
            ConnectionGuard connectionGuard(pipeHandle);
            DWORD error = GetLastError();
            if(error != ERROR_IO_PENDING && error != ERROR_PIPE_CONNECTED)
                continue;
            const std::string request = readDataFromPipe(pipeHandle);
            qDebug() << QString::fromStdString("Received request <" + request+">");
            if(sendPermission(request)) continue;
            if(receiveLog(request)) continue;
        }
        break;
        case WAIT_OBJECT_0 + 1:
            qDebug("Close event !");
            return;
        break;
        };
    }

}

void PipeServer::stopServerLoop(){
    SetEvent(closeLoopEvent);
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

HANDLE PipeServer::createNewPipe(LPCWSTR PipeName){
    const DWORD PipeAccess = PIPE_ACCESS_DUPLEX | FILE_FLAG_OVERLAPPED;
    const DWORD PipeMode = PIPE_READMODE_MESSAGE | PIPE_TYPE_MESSAGE;
    const DWORD Instances = 1;
    HANDLE pipeHandle = CreateNamedPipe(
                PipeName,
                PipeAccess,
                PipeMode,
                Instances,
                BufferSize,
                BufferSize,
                TimeOut,
                NULL);
    return pipeHandle;
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

LogInfo PipeServer::parseRequest(const std::string& request){
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
