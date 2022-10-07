#pragma once
#include "../UI/loginfo.h"

class PipeClient
{
public:
    PipeClient();
    char ReceivePermission(const DWORD Pid);
    bool SendLog(const LogInfo& logInfo);
};
