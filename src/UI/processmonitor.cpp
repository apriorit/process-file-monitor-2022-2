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

bool operator==(const ProcessInfo& first , const ProcessInfo& second){
    return first.Pid == second.Pid
            && first.Path == second.Path
            && first.Name == second.Name
            && first.closePermission == second.closePermission
            && first.deletePermission == second.deletePermission
            && first.openPermission == second.openPermission
            && first.readPermission == second.readPermission
            && first.writePermission == second.writePermission
            && first.isDllInjected == second.isDllInjected
            && first.isMonitored == second.isMonitored;
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
        if (itOld->Pid > itCurrent->Pid
                || (itOld->Pid == itCurrent->Pid && itOld->Path != itCurrent->Path)){
            updatedProcesses.push_back(*itCurrent);
            itCurrent++;
        }
        else if(itOld->Pid == itCurrent->Pid){
            updatedProcesses.push_back(*itOld);
            itOld++;
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


