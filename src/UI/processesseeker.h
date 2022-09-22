#ifndef PROCESSESSEEKER_H
#define PROCESSESSEEKER_H
#include "processmonitor.h"
#include <windows.h>

struct ProcessInfo;

class IProcessesSeeker{
public:
    virtual std::vector<ProcessInfo> getSystemProcesses() = 0;
};

class ProcessesSeeker : IProcessesSeeker
{
public:
    std::vector<ProcessInfo> getSystemProcesses() override;
    ProcessesSeeker();
private:
    ProcessInfo ProcessFromPid(const DWORD Pid);
};

#endif // PROCESSESSEEKER_H
