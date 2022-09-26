#pragma once
#include "processinfo.h"
#include <windows.h>

struct ProcessInfo;

class IProcessesSeeker{
public:
    virtual std::vector<ProcessInfo> getSystemProcesses() = 0;
};

class ProcessesSeeker : public IProcessesSeeker
{
public:
    std::vector<ProcessInfo> getSystemProcesses() override;
    ProcessesSeeker();
private:
    ProcessInfo ProcessFromPid(const DWORD Pid);
    std::vector<DWORD> getProcessesPids();
};
