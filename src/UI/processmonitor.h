#pragma once
#include <QString>

struct ProcessInfo{
    ProcessInfo(int pid,const QString& name)
        :Pid{pid},
        Name{name}{}
    const int Pid;
    const QString Name;
    bool readPermission = true;
    bool writePermission = true;
    bool openPermission = true;
    bool closePermission = true;
    bool deletePermission = true;
    bool isMonitored = false;
    bool isInjected = false;

    friend bool operator<(const ProcessInfo& first , const ProcessInfo& second);
};



class IProcessMonitor{
public:
    virtual void updateProcessesTable() = 0;
    virtual const ProcessInfo& getProcessInfo(const int index) = 0;
    virtual ~IProcessMonitor();
};

class ProcessMonitor : public IProcessMonitor{

};
