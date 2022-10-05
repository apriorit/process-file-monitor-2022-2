#include "pch.h"
#include "processmonitor.h"
#include "processesseeker.h"
#include "processesstorage.h"
#include "mutexguard.h"

ProcessMonitor::ProcessMonitor(IProcessesSeeker* processesSeeker)
               :processesStorage{std::make_unique<ProcessesStorage>()},
               processesSeeker{processesSeeker}{};

void ProcessMonitor::updateProcessesTable() {
    MutexGuard guard(processesStorageMutex);
    auto update = processesSeeker->getSystemProcesses();
    processesStorage->update(update);
}

ProcessInfo ProcessMonitor::getCopyOfProcessInfoByIndex(const size_t Index){
    MutexGuard guard(processesStorageMutex);
    return processesStorage->getProcessByIndex(Index);
}

ProcessInfo ProcessMonitor::getCopyOfProcessInfoByPid(const DWORD Pid) {
    MutexGuard guard(processesStorageMutex);
    return processesStorage->getProcessByPid(Pid);
}

void ProcessMonitor::setProcessEditableField(ProcessInfo& process, const ProcessEditableFields field, const bool value){
    switch(field){
    case ProcessEditableFields::readPerm:
        process.readPermission = value;
    break;
    case ProcessEditableFields::writePerm:
        process.writePermission = value;
    break;
    case ProcessEditableFields::openPerm:
        process.openPermission = value;
    break;
    case ProcessEditableFields::deletePerm:
        process.deletePermission = value;
    break;
    case ProcessEditableFields::isMonitored:
        process.isMonitored = value;
    break;
    case ProcessEditableFields::isDllInjected:
        process.isDllInjected = value;
    break;
    }
    //TODO Send update to the hook if dll is not injected, inject it
}

void ProcessMonitor::setProcessEditableFieldByIndex(const size_t Index, const ProcessEditableFields field, const bool value){
    MutexGuard guard(processesStorageMutex);
    auto& process = processesStorage->getProcessByIndex(Index);
    setProcessEditableField(process, field , value);
}

void ProcessMonitor::setProcessEditableFieldByPid(const DWORD Pid, const ProcessEditableFields field, const bool value){
    MutexGuard guard(processesStorageMutex);
    auto& process = processesStorage->getProcessByPid(Pid);
    setProcessEditableField(process, field , value);
}

size_t ProcessMonitor::getProcessesCount(){
    MutexGuard guard(processesStorageMutex);
    return processesStorage->getSize();
}

ProcessMonitor::~ProcessMonitor(){}

