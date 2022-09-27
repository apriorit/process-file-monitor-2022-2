#include "pch.h"
#include "processmonitor.h"
#include "processesseeker.h"

void ProcessMonitor::updateProcessesTable() {
    std::vector<ProcessInfo> updatedProcesses = processesSeeker->getSystemProcesses();
    std::sort(updatedProcesses.begin(),updatedProcesses.end());
    processesInfo = mergeProcessesSortedLists(processesInfo, updatedProcesses);
    qDebug() << "Processes size "<< QVariant(processesInfo.size()) << "updatedProcesses size" << QVariant(updatedProcesses.size());
}

ProcessInfo ProcessMonitor::getCopyOfProcessInfoByIndex(const size_t Index) const{
    return processesInfo[Index];
}

ProcessInfo ProcessMonitor::getCopyOfProcessInfoByPid(const DWORD Pid) const{
    return getCopyOfProcessInfoByIndex(getIndexOfProcessBySpecyficPid(Pid));
}

void ProcessMonitor::setProcessEditableFieldByIndex(const size_t Index, const ProcessEditableFields field, const bool value){
    switch(field){
    case ProcessEditableFields::readPerm:
        processesInfo[Index].readPermission = value;
    break;
    case ProcessEditableFields::writePerm:
        processesInfo[Index].writePermission = value;
    break;
    case ProcessEditableFields::openPerm:
        processesInfo[Index].openPermission = value;
    break;
    case ProcessEditableFields::deletePerm:
        processesInfo[Index].deletePermission = value;
    break;
    case ProcessEditableFields::isMonitored:
        processesInfo[Index].isMonitored = value;
    break;
    case ProcessEditableFields::isDllInjected:
        processesInfo[Index].isDllInjected = value;
    break;
    }
}

void ProcessMonitor::setProcessEditableFieldByPid(const DWORD Pid, const ProcessEditableFields field, const bool value){
    setProcessEditableFieldByIndex(getIndexOfProcessBySpecyficPid(Pid), field, value);
}

size_t ProcessMonitor::getProcessesCount() const{
    return processesInfo.size();
}
std::vector<ProcessInfo> ProcessMonitor::mergeProcessesSortedLists(const std::vector<ProcessInfo>& oldProcesses ,
                                                                const std::vector<ProcessInfo>& currentProcesses){
    std::vector<ProcessInfo> updatedProcesses;
    auto itOld = oldProcesses.begin();
    auto itCurrent = currentProcesses.begin();

    while(itOld != oldProcesses.end() && itCurrent != currentProcesses.end()){
        if(*itOld == *itCurrent){
            updatedProcesses.push_back(*itOld);
            itOld++;
            itCurrent++;
        }
        else if (itOld->Pid > itCurrent->Pid
                || (itOld->Pid == itCurrent->Pid && itOld->Path != itCurrent->Path)){
            updatedProcesses.push_back(*itCurrent);
            itCurrent++;
        }
        else{
            itOld++;
        }
    }

    while(itCurrent != currentProcesses.end()){
        updatedProcesses.push_back(*itCurrent);
        itCurrent++;
    }

    return updatedProcesses;
}

ProcessMonitor::~ProcessMonitor(){}

size_t ProcessMonitor::getIndexOfProcessBySpecyficPid(const DWORD Pid) const{
    for(size_t i = 0 ; i < processesInfo.size() ; i++ ){
        if(Pid == processesInfo[i].Pid){
            return i;
        }
    }
    throw std::invalid_argument("There is no Process with given PID !");
}
