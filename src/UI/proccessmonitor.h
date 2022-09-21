#pragma once
#include <QString>

struct proccessInfo{
    proccessInfo(int pid,const QString& name)
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
};

class IProccessMonitor{
public:
    virtual void updateProccessesTable() = 0;
    virtual const proccessInfo& getProccessInfo(const int index) = 0;
    virtual ~IProccessMonitor();
};

class ProccessMonitor : public IProccessMonitor{};
