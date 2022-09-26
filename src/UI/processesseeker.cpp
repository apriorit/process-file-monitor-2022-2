#include "pch.h"
#include "processesseeker.h"
#include "processinfo.h"

ProcessesSeeker::ProcessesSeeker(){}

ProcessInfo ProcessesSeeker::ProcessFromPid(const DWORD Pid){
    TCHAR processName[MAX_PATH] = TEXT("<unknown>");
    HANDLE hProcess = OpenProcess( PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, Pid);

    if(NULL != hProcess){
         GetModuleFileNameEx( hProcess, NULL, processName,
                               sizeof(processName)/sizeof(TCHAR));
         std::wstring stdWProcessName(processName);
         QString qProcessName = QString::fromStdWString(stdWProcessName);

         return ProcessInfo(Pid,qProcessName);
    }
    throw std::invalid_argument("Failed to open a process");
}

std::vector<DWORD> ProcessesSeeker::getProcessesPids(){
    DWORD sizeOfProcessesBuffer = 128;
    std::vector<DWORD> processesPids;

    while(true){
        DWORD processesBuffer[sizeOfProcessesBuffer];
        DWORD returnedByteCount = 0;
        if(!EnumProcesses(processesBuffer, sizeof(processesBuffer),&returnedByteCount)){
            return std::vector<DWORD>();
        }
        DWORD processesAddedToArrayCount = returnedByteCount / sizeof(DWORD);
        if(sizeOfProcessesBuffer == processesAddedToArrayCount){
            sizeOfProcessesBuffer *= 2;
        }
        else{
            processesPids.assign(processesBuffer,processesBuffer+processesAddedToArrayCount);
            break;
        }
    }
    return processesPids;
}

std::vector<ProcessInfo> ProcessesSeeker::getSystemProcesses(){  
    const auto processesPids = getProcessesPids();
    std::vector<ProcessInfo> currentRunningProcesses;
    currentRunningProcesses.reserve(processesPids.size());

    for(const auto Pid : processesPids){
        if(Pid == 0)
            continue;
        try{
            currentRunningProcesses.push_back(ProcessFromPid(Pid));
        }
        catch(const std::invalid_argument&){
            continue;
        };
    }
    return currentRunningProcesses;
}
