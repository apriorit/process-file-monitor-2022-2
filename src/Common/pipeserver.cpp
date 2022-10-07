#include "pch.h"
#include "../UI/logbuffer.h"
#include "pipeserver.h"
#include "../UI/processmonitor.h"
#include <regex>
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
        if(SendPermission(request)) continue;
        if(ReceiveLog(request)) continue;
    }
}

bool PipeServer::ReceiveLog(const std::string& request){
    std::regex receiveLogRegex("^(<[^<>/]+>[^<>/]+</[^<>/]+>)+$");
    if(std::regex_match(request, receiveLogRegex)){
        auto data = readDataFromPipe(pipeHandle);
        try{
            logBuffer->addLogToTheBuffer(PipeServer::parseRequest(request));
        }
        catch(const std::invalid_argument&){}
    }
    return false;
}

bool PipeServer::SendPermission(const std::string& request){
    std::regex sendPermissionRegex("^[0-9]+$");
    if(std::regex_match(request, sendPermissionRegex)){
        const DWORD pid = std::strtoul(request.c_str(), NULL , 10);
        std::string permission;
        try{
            permission += processMonitor->getCopyOfProcessInfoByPid(pid).getPermissionsAsChar();
            return writeToPipe(permission, pipeHandle);
        }
        catch(const std::out_of_range&){}
    }
    return false;
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
