#include "pch.h"
#include "processesseeker.h"
#include "processmonitor.h"

ProcessesSeeker::ProcessesSeeker()
{

}

ProcessInfo ProcessesSeeker::ProcessFromPid(const DWORD Pid){
    TCHAR szProcessName[MAX_PATH] = TEXT("<unknown>");

    HANDLE hProcess = OpenProcess( PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, Pid);

    if(NULL != hProcess){
        HMODULE hMod;
        DWORD cbNeeded;

        if(EnumProcessModules( hProcess, &hMod, sizeof(hMod),
                               &cbNeeded) ){

            GetModuleFileNameEx( hProcess, hMod, szProcessName,
                               sizeof(szProcessName)/sizeof(TCHAR));
        }

         std::wstring stdWProcessName(szProcessName);
         QString qProcessName = QString::fromStdWString(stdWProcessName);

         qDebug() << qProcessName;

         return ProcessInfo(Pid,qProcessName);
    }
    throw std::invalid_argument("Cannot open process");
}

std::vector<ProcessInfo> ProcessesSeeker::getSystemProcesses(){
    std::vector<ProcessInfo> currentRunningProcesses;
    DWORD aProcesses[1024], cbNeeded, cProcesses;
    unsigned int i;

    if(!EnumProcesses(aProcesses, sizeof(aProcesses),&cbNeeded)){
        return std::vector<ProcessInfo>();
    }

    cProcesses = cbNeeded / sizeof(DWORD);

    for(i = 0; i < cProcesses; i++){
        if(aProcesses[i] != 0 ){
            try{
                currentRunningProcesses.push_back(ProcessFromPid(aProcesses[i]));
            }
            catch(std::invalid_argument){
                continue;
            };
        }

    }
    return currentRunningProcesses;
}



