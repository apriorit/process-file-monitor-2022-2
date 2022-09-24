#include "pch.h"
#include "processmonitor.h"
#include "processesseeker.h"

ProcessInfo::ProcessInfo(int pid,const QString& Path):Pid{pid},
    Path{Path},
    Name{getNameFromThePath()}{}

QString ProcessInfo::getNameFromThePath(){
    std::string stdPath = Path.toStdString();
    std::size_t lastSeparator = stdPath.find_last_of("/\\");
    std::string name = stdPath.substr(lastSeparator+1);
    return QString::fromStdString(name);
}

bool ProcessInfo::settingsEquals(const ProcessInfo& other) const{
    return readPermission == other.readPermission
            && writePermission == other.writePermission
            && openPermission == other.openPermission
            && deletePermission == other.deletePermission
            && isMonitored == other.isMonitored
            && isDllInjected == other.isDllInjected;
}

bool operator<(const ProcessInfo& first , const ProcessInfo& second){
    return first.Pid < second.Pid;
}

bool operator==(const ProcessInfo& first , const ProcessInfo& second){
    return first.Pid == second.Pid
            && first.Path == second.Path
            && first.Name == second.Name;
}

void ProcessMonitor::updateProcessesTable() {
    processesSeeker->getSystemProcesses();
}

ProcessInfo ProcessMonitor::getCopyOfProcessInfoByIndex(const int index){
    return ProcessInfo(index,"test");
}

ProcessInfo ProcessMonitor::getCopyOfProcessInfoByPid(const int Pid){
    return ProcessInfo(Pid,"test");
}

std::vector<ProcessInfo> ProcessMonitor::mergeProcessesLists(const std::vector<ProcessInfo>& oldProcesses ,
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
        if (itOld->Pid > itCurrent->Pid
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

void ProcessMonitor::setProcessEditableField(const ProcessEditableFields field){

}

ProcessMonitor::~ProcessMonitor(){

}


