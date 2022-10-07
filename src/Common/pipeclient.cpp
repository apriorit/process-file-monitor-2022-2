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

}

std::string PipeClient::parseLogInfoIntoRequest(const LogInfo& logInfo){

}
