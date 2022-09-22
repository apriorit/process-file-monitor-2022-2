#include "processmonitor.h"
#include "processesseeker.h"
#include <string>

ProcessInfo::ProcessInfo(int pid,const QString& Path):Pid{pid},
    Path{Path},
    Name{getNameFromThePath()}{}

QString ProcessInfo::getNameFromThePath(){
    std::string stdPath = Path.toStdString();
    std::size_t lastSeparator = stdPath.find_last_of("/\\");
    std::string name = stdPath.substr(lastSeparator+1);
    return QString::fromStdString(name);
}

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


