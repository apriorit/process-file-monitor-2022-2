#include "pch.h"
#include "pipehost.h"

HANDLE PipeHost::createNewPipe(LPCWSTR PipeName){
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

std::string PipeHost::readDataFromPipe(HANDLE& pipeHandle){
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

bool PipeHost::writeToPipe(const std::string& message , HANDLE& pipeHandle){
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
