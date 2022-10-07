#include "pch.h"
#include "logbuffer.h"
#include "pipeserver.h"
#include "processmonitor.h"

ConnectionGuard::~ConnectionGuard(){
    DisconnectNamedPipe(pipeHandle);
}

HANDLE PipeServer::createNewPipe(LPCWSTR PipeName){
    const DWORD PipeAccess = PIPE_ACCESS_DUPLEX;
    const DWORD PipeMode = PIPE_READMODE_MESSAGE | PIPE_TYPE_MESSAGE | PIPE_WAIT;
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

void PipeServer::startServerLoop(){
    int calls = 0;
    while(true){
        qDebug() << calls++;
        DWORD connectionStatus = 0;
        DWORD error = 0;
        qDebug() << "Waiting for connection ...";
        connectionStatus = ConnectNamedPipe(pipeHandle,nullptr);
        error = GetLastError();
        ConnectionGuard connectionGuard(pipeHandle);
        if(connectionStatus == 0 && error != ERROR_PIPE_CONNECTED){
            qDebug() << "Failed to connect !";
            continue;
        }

        qDebug() << "Client connected !";

        const std::string commandStr = readDataFromPipe();
        qDebug() << QString::fromStdString("Received command <" + commandStr+">");
        std::pair<DWORD, Commands> command;
        try{
            command = getCommandAndPidFromRequest(commandStr);
        }
        catch(std::invalid_argument& e){
            qDebug("Invalid request !") ;
            continue;
        }
        switch(command.second){
        case Commands::SendPermission:
            try{
                std::string permission;
                permission += processMonitor->getCopyOfProcessInfoByPid(command.first).getPermissionsAsChar();
                if(writeToPipe(permission)){
                    qDebug() << "Permission sended !";
                }
                else{
                    qDebug() << "Failed to send permission !";
                    continue;
                }
            }
            catch(const std::out_of_range&){
                qDebug() << QString::fromStdString("processInfo not found with pid" + std::to_string(command.first));
                continue;
            }
        break;
        case Commands::ReceiveLog:
        {
            auto request = readDataFromPipe();
            logBuffer->addLogToTheBuffer(PipeServer::parseRequest(request));
        }
        break;
        default:
                qDebug() << "Unknown command !";
                continue;
        }
    }
}

std::string PipeServer::readDataFromPipe(){
    char buffer[BufferSize];
    std::string data = "";
    DWORD readCount = 0;
    BOOL readResult = FALSE;
    while(!readResult){
        readResult = ReadFile(pipeHandle, buffer, BufferSize , &readCount, NULL);
        if(GetLastError() != ERROR_MORE_DATA && readCount == 0){
            break;
        }
        std::copy(&buffer[0], &buffer[readCount - 1], back_inserter(data));
    }

    return data;
}

bool PipeServer::writeToPipe(const std::string& message){
    DWORD writeCount = 0;
    WriteFile(pipeHandle,
              message.c_str(),
              message.size(),
              &writeCount,
              NULL);
    if(writeCount != message.size()){
        qDebug() << QString("Failed to send all message");
        return false;
    }
    FlushFileBuffers(pipeHandle);
    return true;
}

std::pair<DWORD, Commands> PipeServer::getCommandAndPidFromRequest(const std::string& Request){

    std::pair<DWORD, Commands> returnValue{0, Commands::Unknown} ;
    size_t delimiterPos = Request.find("\n");

    if(delimiterPos == std::string::npos){
        throw std::invalid_argument("Can't split string on Pid and Command !");
    }

    std::string pidStr = Request.substr(0, delimiterPos);
    std::string commandStr = Request.substr(delimiterPos+1, std::string::npos);

    std::istringstream ss(&pidStr[0]);
    ss >> returnValue.first;

    std::ostringstream pidCheckStream;
    pidCheckStream << returnValue.first;

    if(returnValue.first == 0 || pidCheckStream.str().size() != pidStr.size()){
        throw std::invalid_argument("Can't get Pid from the string !");
    }

    if(commandStr == "SendPermission"){
        returnValue.second = Commands::SendPermission;
    }
    else if(commandStr == "ReceiveLog"){
        returnValue.second = Commands::ReceiveLog;
    }
    else{
        throw std::invalid_argument("Unknown command !");
    }

    return returnValue;
}

LogInfo PipeServer::parseRequest(std::string request){
    LogInfo logInfo(0);
    std::regex propertySegmentRegEx("(<[^<>/]+>[^<>/]+</[^<>/]+>)");
    std::smatch propertySegmentMatch;

    std::regex propertyMemberRegEx("([^<>/]+)");
    std::smatch propertyMemberMatch;

    while(std::regex_search(request, propertySegmentMatch, propertySegmentRegEx)){
        std::string propertySegment = propertySegmentMatch.str();
        //Get name of the property
        std::regex_search(propertySegment, propertyMemberMatch , propertyMemberRegEx);
        std::string propertyName = propertyMemberMatch[0].str();
        //Get value of the property
        propertySegment = propertyMemberMatch.suffix();
        std::regex_search(propertySegment, propertyMemberMatch , propertyMemberRegEx);
        std::string propertyValue = propertyMemberMatch[0].str();
        request = propertySegmentMatch.suffix();

        if(propertyName == "PID"){
            logInfo.pid = std::strtoul(propertyValue.c_str(), NULL, 10);
        }
        else if(propertyName == "FPATH"){
            logInfo.filePath = QString::fromStdString(propertyValue);
        }
        else if(propertyName == "OTYPE"){
            logInfo.operationType = QString::fromStdString(propertyValue);
        }
        else if(propertyName == "PREVIEW"){
            logInfo.preview = QString::fromStdString(propertyValue);
        }
        else if(propertyName == "FHANDLE"){
            logInfo.fileHandle = QString::fromStdString(propertyValue);
        }
        else if(propertyName == "RESULT"){
            logInfo.resultOfTheOperation = QString::fromStdString(propertyValue);
        }
        else if(propertyName == "NOB"){
            logInfo.numberOfBytes = std::strtoul(propertyValue.c_str(), NULL, 10);
        }
        else if(propertyName == "OFFSET"){
            logInfo.offset = std::strtoul(propertyValue.c_str(), NULL, 10);
        }
        else if(propertyName == "OTIME"){
            logInfo.operationTime = std::strtoul(propertyValue.c_str(), NULL, 10);
        }
    }
    if(logInfo.pid == 0){
        throw std::invalid_argument("Pid is not correct !");
    }
    return logInfo;
}
