#include "pch.h"
#include "pipeserver.h"

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

void PipeServer::serverLoop(){
    while(true){
        DWORD connectionStatus = 0;
        DWORD error = 0;
        qDebug() << "Waiting for connection ...";
        connectionStatus = ConnectNamedPipe(pipeHandle,nullptr);
        error = GetLastError();

        if(connectionStatus == 0 && error != ERROR_PIPE_CONNECTED){
            qDebug() << "Failed to connect !";
            continue;
        }

        ConnectionGuard connectionGuard(pipeHandle);

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
                if(writeToPipe("5")){
                    qDebug() << "Permission sended !";
                }
                else{
                    qDebug() << "Failed to send permission !";
                    continue;
                }
            break;
            case Commands::ReceiveLog:
                auto log = readDataFromPipe();
                qDebug() << QString("Received log ") + QString::fromStdString(log);
            break;
            defualt:
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
