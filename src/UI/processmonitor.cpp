#include "pch.h"
#include "processmonitor.h"
#include "processesseeker.h"
#include "processesstorage.h"

ProcessMonitor::ProcessMonitor(IProcessesSeeker* processesSeeker)
               :processesStorage{std::make_unique<ProcessesStorage>()},
               processesSeeker{processesSeeker}{};

void ProcessMonitor::updateProcessesTable() {
    auto update = processesSeeker->getSystemProcesses();
    processesStorage->update(update);
}

ProcessInfo ProcessMonitor::getCopyOfProcessInfoByIndex(const size_t Index) const{
    return processesStorage->getProcessByIndex(Index);
}

ProcessInfo ProcessMonitor::getCopyOfProcessInfoByPid(const DWORD Pid) const{
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
}

void ProcessMonitor::setProcessEditableFieldByIndex(const size_t Index, const ProcessEditableFields field, const bool value){
    auto& process = processesStorage->getProcessByIndex(Index);
    setProcessEditableField(process, field , value);
}

void ProcessMonitor::setProcessEditableFieldByPid(const DWORD Pid, const ProcessEditableFields field, const bool value){
    auto& process = processesStorage->getProcessByPid(Pid);
    setProcessEditableField(process, field , value);
}

size_t ProcessMonitor::getProcessesCount() const{
    return processesStorage->getSize();
}

ProcessMonitor::~ProcessMonitor(){}

