#include "pch.h"
#include "processinfo.h"

ProcessInfo::ProcessInfo(DWORD pid,const QString& Path)
    :Pid{pid},
    Path{Path},
    Name{QFileInfo(Path).fileName()}{}

bool ProcessInfo::settingsEquals(const ProcessInfo& other) const{
    return readPermission == other.readPermission
            && writePermission == other.writePermission
            && openPermission == other.openPermission
            && deletePermission == other.deletePermission
            && isMonitored == other.isMonitored
            && isDllInjected == other.isDllInjected;
}

char ProcessInfo::getPermissionsAsChar(){
    char permission = 0;
    if(readPermission) permission+=1;
    if(writePermission) permission+=2;
    if(openPermission) permission+=4;
    if(deletePermission) permission+=8;
    if(isMonitored) permission+=16;

    return permission;
}

bool operator<(const ProcessInfo& first , const ProcessInfo& second){
    return first.Pid < second.Pid;
}

bool operator==(const ProcessInfo& first , const ProcessInfo& second){
    return first.Pid == second.Pid
            && first.Path == second.Path;
}
