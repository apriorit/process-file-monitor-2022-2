#include "processmonitor.h"

bool operator<(const ProcessInfo& first , const ProcessInfo& second){
    return first.Pid < second.Pid;
}

void ProcessMonitor::updateProcessesTable() {

}

ProcessInfo ProcessMonitor::getCopyOfProcessInfoByIndex(const int index){
    return ProcessInfo(index,"test");
}

ProcessInfo ProcessMonitor::getCopyOfProcessInfoByPid(const int index){
    return ProcessInfo(index,"test");
}

std::set<ProcessInfo> ProcessMonitor::mergeProcessesSets(const std::set<ProcessInfo>& oldSet ,
                                                                const std::set<ProcessInfo>& newSet){
    return std::set<ProcessInfo>();
}

void ProcessMonitor::setProcessEditableField(const ProcessEditableFields field){

}

ProcessMonitor::~ProcessMonitor(){

}


