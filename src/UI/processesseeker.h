#pragma once
#include "processinfo.h"
#include <windows.h>

class ProcessesStorage;

struct ProcessInfo;

class IProcessesSeeker{
public:
    virtual ProcessesStorage getSystemProcesses() = 0;
};

class ProcessesSeeker : public IProcessesSeeker
{
public:
    ProcessesStorage getSystemProcesses() override;
    ProcessesSeeker();
private:
    ProcessInfo ProcessFromPid(const DWORD Pid);
    std::vector<DWORD> getProcessesPids();
};
